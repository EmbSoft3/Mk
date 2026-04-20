# Use USB devices (USB Stack)

This page documents the USB host stack of the Mk kernel. It covers the three layers that compose the stack — the Host Controller Driver (HCD), the Human Interface Device class (HID), and the Mass Storage Class (MSC) — as well as the interrupt model, the device enumeration sequence, the static memory model, and the application-level event delivery mechanism.

---

## Table of contents

1. [Architecture overview](#1-architecture-overview)
2. [OTG core](#2-otg-core)
3. [Task hierarchy and termio model](#3-task-hierarchy-and-termio-model)
4. [Host Controller Driver (HCD)](#4-host-controller-driver-hcd)
   - 4.1 [Key data structures](#41-key-data-structures)
   - 4.2 [Interrupt service routines](#42-interrupt-service-routines)
   - 4.3 [Device enumeration sequence](#43-device-enumeration-sequence)
   - 4.4 [Hub management and SPLIT transactions](#44-hub-management-and-split-transactions)
   - 4.5 [Pipe mechanism](#45-pipe-mechanism)
   - 4.6 [Static memory pool](#46-static-memory-pool)
5. [HID layer](#5-hid-layer)
   - 5.1 [Report descriptor parser](#51-report-descriptor-parser)
   - 5.2 [Application controls](#52-application-controls)
   - 5.3 [Polling and input dispatching](#53-polling-and-input-dispatching)
   - 5.4 [LED and output reports](#54-led-and-output-reports)
   - 5.5 [API reference](#55-api-reference)
6. [Application event model](#6-application-event-model)
7. [MSC layer](#7-msc-layer)
   - 7.1 [Bulk-Only Transport and SCSI](#71-bulk-only-transport-and-scsi)
   - 7.2 [Disk abstraction and filesystem bridge](#72-disk-abstraction-and-filesystem-bridge)
   - 7.3 [API reference](#73-api-reference)
8. [Static memory model](#8-static-memory-model)

---

## 1. Architecture overview

The USB stack is a purely **host-mode** stack. The system acts as a USB host and enumerates devices connected to its ports. The STM32F74xxx provides two USB OTG peripheral cores (OTGHS and OTGFS); only the **OTGHS core is currently implemented**. The OTGFS core is under development.

The stack is organized in three independent layers that communicate exclusively through the kernel message-passing primitives (`T_mkMail`). There is no shared-state coupling between layers; each layer owns its own device list and pool.

```
 ┌────────────────────────────────────────────────────────┐
 │                 Application / Dispatcher               │
 │           (receives T_mkDispatcherMessage)             │
 └───────────────┬───────────────────────┬────────────────┘
                 │                       │
      ┌──────────▼──────┐     ┌──────────▼──────┐
      │   HID terminal  │     │   MSC terminal  │
      │  (mk_hid_task)  │     │  (mk_msc_task)  │
      └──────────┬──────┘     └──────────┬──────┘
                 │                       │
      ┌──────────▼───────────────────────▼──────┐
      │         HCD terminal (mk_usbhs)         │
      │      T_mkHCDHandler  ·  T_mkHCDDevice   │
      └──────────────────────┬──────────────────┘
                             │
┌────────────────────────────▼───────────────────────────┐
│                   USB OTG HS peripheral                │
│       ISR → mk_event_set → portEvent/channelEvent      │
└────────────────────────────────────────────────────────┘
```

At the bottom, the ISR converts hardware interrupts into kernel events. The HCD task consumes those events, enumerates devices, and notifies the HID and MSC terminals via mailboxes. Each class terminal then manages its own device lifecycle and communicates state changes upward to the application-level dispatcher.

---

## 2. OTG core

Only the **USB OTG HS** (`K_USB_OTGHS`) core is currently implemented.

| Peripheral | Identifier | Channels | FIFO Rx | FIFO Tx | Stack size |
|---|---|---|---|---|---|
| USB OTG HS | `K_USB_OTGHS` | 16 | 512 bytes | 256 bytes | 512 words |

The active mode (host or device) is determined at runtime by reading the **ID pin** state. When the ID pin interrupt fires, the HCD task reads the pin level, selects host or device mode, and either enters the host event loop or self-destructs and relaunches in device mode.

The relevant timeouts are:

| Constant | Value | Purpose |
|---|---|---|
| `K_MK_USB_RESET_TIMEOUT` | 250 ms | Maximum duration of a USB port reset |
| `K_MK_USB_RESET_TICK` | 55 ms | Nominal reset pulse duration |
| `K_MK_USB_BUSY_TIMEOUT` | 50 ms | Timeout waiting for PHY FIFO availability |
| `K_MK_USB_FIFO_TIMEOUT` | 50 ms | Timeout waiting for Rx FIFO data |

---

## 3. Task hierarchy and termio model

The USB stack is structured around the `termio` subsystem. A **terminal** (`T_mkTermio`) is a kernel abstraction that couples a task to a hardware peripheral. The USB stack spawns its terminal hierarchy at boot.

### OTGHS task tree

| Terminal | Task entry point | Priority |
|---|---|---|
| HCD | `mk_usbhs_taskHostMode` | `K_MK_TERMIO_TASK_PRIORITY` = 2 |
| HID | `mk_hid_task` | `K_MK_TERMIO_TASK_PRIORITY` |
| MSC | `mk_msc_task` | `K_MK_TERMIO_TASK_PRIORITY` |
| Dispatcher | internal | `K_MK_TERMIO_DISPATCHER_PRIORITY` = 3 |

```
 mk_usbhs_taskHostMode          (HCD terminal, K_MK_TERMIO_TASK_PRIORITY)
   ├── mk_hid_task               (HID terminal)
   └── mk_msc_task               (MSC terminal)
         └── Filesystem bridge   (mk_disk_* requests via T_mkMSCRequestArea)
```

The HCD task starts first. Before entering its event loop it signals `K_MK_TERMIO_FLAG_USBHS` and waits on `K_MK_TERMIO_FLAG_MSC | K_MK_TERMIO_FLAG_HID` (AND condition), ensuring no USB message is posted to HID or MSC mailboxes before those terminals have initialized their message queues.

### Mode switching

If the ID pin changes state while the system is running (e.g., a USB cable is plugged in with the ID wire connected), the HCD task:

1. Destroys the full device tree (`mk_hcd_handleDisconnect`).
2. Calls `mk_hcd_handleHostMode`, which relaunches itself as a device-mode task.
3. The current task self-destructs via `mk_termio_delete`.

All internal data structures are allocated on the task's stack or in the DMA-privileged pool, so destruction is clean with no memory leak.

---

## 4. Host Controller Driver (HCD)

The HCD is the lowest software layer. It owns the USB hardware registers, services the ISR, enumerates devices, manages hubs, and exposes a **pipe** API that HID and MSC use to perform USB transfers.

### 4.1 Key data structures

#### `T_mkHCDHandler`

The root object of an HCD instance. One handler per OTG core.

| Field | Type | Description |
|---|---|---|
| `bus` | `T_mkAddr` | Hardware base address (`K_USB_OTGHS`) |
| `packetBuf` | `uint8_t[64]` | Scratch buffer for control transfers (default MPS) |
| `sofTable` | `uint8_t[16]` | Per-channel NYET back-off counters |
| `channelTable` | `uint8_t[16]` | Channel allocation bitmap |
| `channelEvent` | `T_mkEvent*[16]` | One kernel event register per channel, used by the ISR |
| `portEvent` | `T_mkEvent*` | Port-level events (connect, disconnect, enable, overcurrent, ID pin, refresh) |
| `channelMutex` | `T_mkMutex*` | Protects channel allocation against concurrent HID/MSC tasks |
| `device` | `T_mkHCDDevice*` | First device on the bus (root of the device tree) |
| `hubList` | `T_mkHCDList` | Tree of hubs and attached devices |
| `resetTick` | `uint32_t` | Reset pulse duration |

#### `T_mkHCDDevice`

Represents one USB device. Devices are chained in two orthogonal linked lists: a flat circular list for enumeration order (`next`/`previous`) and a tree structure for hub topology (`nextDevice`/`previousDevice`, `nextHubDevice`/`previousHubDevice`).

| Field | Description |
|---|---|
| `layer.deviceAddr` | USB address (1–127) |
| `layer.speed` | LS / FS / HS |
| `layer.hubAddr` | Address of the hub this device is behind |
| `layer.portNumber` | Port number on that hub |
| `layer.hubSplitAddr` | Hub responsible for SPLIT transactions |
| `state` | `T_mkHCDDeviceState` — see state machine below |
| `flag.event` | Kernel event set when the device can be safely deallocated |
| `deviceDescriptor` | USB device descriptor |
| `configurationDescriptor` | Active configuration descriptor |
| `interfaceDescriptor*` | Linked list of all interface + endpoint descriptors |

#### `T_mkHCDDeviceState`

```
ATTACHED  →  ADDRESSED  →  CONFIGURED  →  DISPATCHED
                                        ↓
                               NOT_VALID / OVERCURRENT / DISCONNECTED
```

| State | Value | Meaning |
|---|---|---|
| `K_MK_HCD_DEVICE_ATTACHED_STATE` | 0 | Device detected, before SET_ADDRESS |
| `K_MK_HCD_DEVICE_ADDRESSED_STATE` | 1 | SET_ADDRESS complete |
| `K_MK_HCD_DEVICE_CONFIGURED_STATE` | 2 | SET_CONFIGURATION complete |
| `K_MK_HCD_DEVICE_DISPATCHED_STATE` | 4 | Handed off to a class terminal (HID or MSC) |
| `K_MK_HCD_DEVICE_NOT_VALID` | 8 | Enumeration failed |
| `K_MK_HCD_DEVICE_OVERCURRENT` | 16 | Bus overcurrent detected |
| `K_MK_HCD_DEVICE_DISCONNECTED` | 32 | Disconnected |

### 4.2 Interrupt service routines

One ISR entry point exists: `mk_usbhs_interrupt`. It follows this structure:

1. Read the USB core's interrupt status register.
2. For **port-level** events (connect, disconnect, enable, overcurrent, SOF, ID pin), set bits in `p_handler->portEvent` using `mk_event_set`. The HCD task is unblocked via `mk_event_wait(..., K_MK_TASK_WAIT_FOREVER)`.
3. For **channel-level** events (transfer complete, channel halted, error flags), set bits in `p_handler->channelEvent[n]`. The task that submitted the transfer (HID or MSC via pipe) is unblocked.

The ISR does minimal work — it clears the hardware interrupt, records the status, and signals a kernel event. All logic runs in task context.

### 4.3 Device enumeration sequence

The enumeration is event-driven. The `mk_hcd_handleHostEvent` function dispatches five event types:

```
portEvent bits:
  CONNECTED   → mk_hcd_handleConnect   → assert reset pulse
  ENABLED     → mk_hcd_handleEnable    → run enumeration
  DISCONNECTED→ mk_hcd_handleDisconnect→ tear down device tree
  OVERCURRENT → mk_hcd_handleOvercurrent
  REFRESH     → mk_hcd_handleRefresh   → poll hubs
```

The full enumeration sequence triggered by `ENABLED` is:

```
1. mk_pool_allocSafe(g_mkHCDPool.devicePool)   → allocate T_mkHCDDevice
2. Read port speed (LS/FS/HS)
3. mk_hcd_openPipe(EP0, control, MPS=8)        → channel for control transfers
4. GET_DESCRIPTOR(device, 8 bytes)             → read real MPS
5. SET_ADDRESS(1..127)
6. GET_DESCRIPTOR(device, full)
7. GET_DESCRIPTOR(qualifier)                   → HS devices only
8. GET_DESCRIPTOR(configuration)
9. GET_DESCRIPTOR(all interfaces + endpoints)
10. SET_CONFIGURATION(bConfigurationValue)
11. For each interface:
    - if bInterfaceClass == HID  → post T_mkHCDMessage to HID mailbox
    - if bInterfaceClass == MSC  → post T_mkHCDMessage to MSC mailbox
    - if bInterfaceClass == HUB  → mk_hcd_initHub, add to hubList
12. device->state = K_MK_HCD_DEVICE_DISPATCHED_STATE
```

Steps 4–10 use a single dedicated control pipe kept open permanently in the HCD task. Since HID and MSC tasks can also open channels, the `channelMutex` ensures serialized channel allocation. The maximum number of simultaneous open channels is 16 (OTGHS), tracked in `channelTable`.

### 4.4 Hub management and SPLIT transactions

The system supports up to **8 hubs** (`K_MK_HCD_MAX_HUB_NUMBER`). Hubs are enumerated like any other device; when a HUB class interface is detected, `mk_hcd_initHub` runs to obtain the hub descriptor and power all ports.

Every 128 ms (`K_MK_HCD_HUB_REFRESH_TIMEOUT`), the `REFRESH` event triggers `mk_hcd_handleRefresh`, which reads the hub status change endpoint and processes port status events (connect, disconnect, enable, overcurrent) on each port.

**SPLIT transactions** allow a HS host to communicate with LS or FS devices connected through a HS hub. The `T_mkHCDDeviceLayer` structure stores both `hubAddr`/`portNumber` (the direct parent) and `hubSplitAddr`/`portSplitNumber` (the HS hub responsible for SPLIT). The pipe layer selects full-speed or SPLIT packet sending (`mk_hcd_sendSplitPacket`) based on the device's speed and hub topology.

The `sofTable` in `T_mkHCDHandler` implements per-channel back-off after a NYET response, preventing the host from flooding a HS hub that is busy translating to FS.

### 4.5 Pipe mechanism

```c
typedef enum T_mkHCDPipeEndpointType
{
   K_MK_HCD_ENDPOINT_CONTROL     = 0x0,
   K_MK_HCD_ENDPOINT_ISOCHRONOUS = 0x1,  /* not yet implemented */
   K_MK_HCD_ENDPOINT_BULK        = 0x2,
   K_MK_HCD_ENDPOINT_INTERRUPT   = 0x3
} T_mkHCDPipeEndpointType;
```

> **Note:** Isochronous transfers are not yet implemented. Only Control, Bulk, and Interrupt endpoint types are operational.

A **pipe** (`T_mkHCDPipe`) is a lightweight configuration structure, not a persistent object — it lives on the caller's stack and is passed by pointer to transfer functions. It describes one endpoint:

| Field | Description |
|---|---|
| `channel` | Allocated HW channel number (0–15) |
| `endpointType` | CONTROL / BULK / INTERRUPT / ISOCHRONOUS |
| `endpointDirection` | `K_MK_HCD_ENDPOINT_IN` or `K_MK_HCD_ENDPOINT_OUT` |
| `endpointNumber` | EP0–EP8 |
| `endpointMaxPacketSize` | MPS in bytes |
| `token` | PID to use for the next packet (DATA0/DATA1/SETUP) |
| `numberOfPackets` | Computed by the transfer layer (max 1023) |
| `timeout` | Transfer timeout in ms |
| `status` | Last transfer status (see `T_mkHCDPipeStatus`) |

The `status` field is a bitmask that covers: successful transfer (`FLAG_XFER`), channel halt (`FLAG_CHH`), AHB DMA error, STALL, NAK, ACK, NYET, transaction error (CRC / timeout / stuffing / EOP), Babble, frame overrun, DATA toggle error, and higher-level codes (`TRANSFER_ABORTED`, `TRANSFER_DONE`, `TRANSFER_DISABLED`, `TRANSFER_RESTART_SPLIT`).

A typical transfer sequence:

```c
mk_hcd_openPipe(handler, &pipe, K_MK_HCD_ENDPOINT_INTERRUPT, epNum, mps, timeout);
mk_hcd_sendPacket(handler, &pipe, buf, length);   // blocks on channelEvent
mk_hcd_closePipe(handler, &pipe);
```

`sendPacket` internally calls `mk_event_wait` on `channelEvent[pipe.channel]`, yielding the CPU until the ISR signals completion or error.

### 4.6 Static memory pool

All HCD objects are allocated from `g_mkHCDPool`, a single `T_mkHCDPool` instance in DMA-privileged memory:

| Object | Max count | Pool member |
|---|---|---|
| `T_mkHCDDevice` | 32 (`K_MK_HCD_MAX_DEVICE_NUMBER`) | `devicePool` |
| `T_mkHCDInterfaceDescriptor` | 64 (2 × devices) | `interfacePool` |
| `T_mkHCDEndpointDescriptor` | 192 (3 × interfaces) | `endpointPool` |
| Hub descriptors | 8 (`K_MK_HCD_MAX_HUB_NUMBER`) | part of `devicePool` |

There is no dynamic allocation (no `malloc`). All pools are statically declared at link time and managed by the kernel `mk_pool_*` API with thread-safe `mk_pool_allocSafe`.

---

## 5. HID layer

The HID terminal (`mk_hid_task`) receives enumeration messages from the HCD, parses each device's report descriptor, builds an in-memory object model of all controls exposed by the device, and then enters a polling loop that reads input reports and dispatches events to the application.

### 5.1 Report descriptor parser

When a HID device is dispatched by the HCD, the terminal:

1. Retrieves the HID descriptor from the interface descriptor chain.
2. Opens an interrupt IN pipe on the device's interrupt endpoint.
3. Issues a `GET_DESCRIPTOR(HID_REPORT)` control transfer.
4. Feeds the raw descriptor bytes to the **report descriptor parser**.

The parser processes HID item tokens (Main, Global, Local items) according to the HID 1.11 specification. It maintains a parser state machine with:
- A **global table** (`T_mkHIDTable`) for the current global item state (logical min/max, physical min/max, report size, report count, usage page).
- A **local table** for transient items (usages, designators, strings, usage min/max).
- A **collection stack** for nested Application / Physical / Logical collections.
- A **report pool** (`K_MK_HID_POOL_MAX_REPORT_NUMBER = 32`) for allocating `T_mkHIDReport` instances.
- An **item pool** (`K_MK_HID_POOL_MAX_ITEM_NUMBER = 512`) for allocating `T_mkHIDItem` instances.

Each `INPUT`, `OUTPUT`, or `FEATURE` main item allocates a `T_mkHIDReport`, which is then **routed** by the router (`mk_hid_router_*`) to one of the concrete control types — mouse, keyboard, joystick, LED — based on the Usage Page and Usage identifiers of its items.

The maximum packet size accepted from a HID device is 1024 bytes (`K_MK_HID_MAX_PACKET_SIZE`).

### 5.2 Application controls

The parser produces a typed object graph. The supported application-level control types are:

| Type | Struct | Pool size | Contents |
|---|---|---|---|
| Mouse | `T_mkMouse` | 10 | `T_mkAxis2` (X/Y), `T_mkWheel` (vertical + AC Pan), `T_mkButton*` list, `T_mkCursor` |
| Keyboard | `T_mkKeyboard` | 10 | Modifier key state, `T_mkKey*` scan code list, `T_mkUTFKey*` output, `T_mkLed*` indicators, layout |
| Joystick | `T_mkJoystick` | 4 | `T_mkStick3` (X/Y/Z), `T_mkThrottle`, `T_mkHatSwitch`, `T_mkLed*`, `T_mkButton*` |

Every control structure begins with a two-field `layer` header — `type` (control kind identifier) and `id` (unique instance number within that kind). The dispatcher uses these fields to route messages without knowing the concrete type.

The keyboard layout is configurable at runtime (`T_mkKeyboardType`): `K_MK_KEYBOARD_QWERTY_US` or `K_MK_KEYBOARD_AZERTY_FR`. The active layout selects the lookup table (`T_mkKeyboardLookup`) used to convert HID scancodes to UTF key codes. The country code reported by the device descriptor is also stored in `layer.countryCode` and can be overridden via `mk_hid_keyboard_setCountryCode`.

### 5.3 Polling and input dispatching

After successful initialization, the HID task enters a periodic polling loop. Every `K_MK_HID_REFRESH_TIMEOUT` milliseconds (10 ms), it:

1. Issues a blocking `READ` on each registered HID device's interrupt IN pipe.
2. Receives the raw input report byte array.
3. Calls `mk_hid_parseInput`, which iterates the report's `T_mkHIDItem` list and extracts field values by bit-shifting the raw bytes according to each item's `reportSize` and `reportOffset`.
4. Compares each field value against its previous value to detect changes.
5. For each change, calls `mk_hid_dispatchMessage(report, ctrlEvent)`.

`mk_hid_dispatchMessage` assembles a `T_mkDispatcherMessage`:

```c
typedef struct T_mkDispatcherMessage {
    T_mkAddr appCtrl;   // pointer to T_mkMouse / T_mkKeyboard / etc.
    uint16_t ctrlEvt;   // T_mkCtrlEvent value
    uint32_t tick;      // mk_getTick() at detection time
};
```

and posts it to the **dispatcher** terminal's mailbox (`K_MK_DISPATCHER_MESSAGE_NUMBER = 8` slots). Since the dispatcher's priority (`K_MK_TERMIO_DISPATCHER_PRIORITY = 3`) is higher than the HID task's priority, the message is delivered synchronously by reference — no copy of the control state is made, which is safe because the HID task will not modify the control state until the dispatcher has processed the message.

The dispatcher then forwards a `T_mkListenerMessage` to the registered application listener.

### 5.4 LED and output reports

Keyboard and joystick LEDs (`T_mkLed`) support write-back via `mk_hid_led_*` functions. Writing a LED state causes the HID layer to issue a `SET_REPORT(OUTPUT)` control transfer on EP0, updating the physical device indicator.

### 5.5 API reference

#### Mouse

```c
T_mkCode mk_hid_mouse_getID        (T_mkMouse* p_mouse, uint16_t* p_id);
T_mkCode mk_hid_mouse_getCoord     (T_mkMouse* p_mouse, real32_t* p_x, real32_t* p_y);
T_mkCode mk_hid_mouse_getWheel     (T_mkMouse* p_mouse, int32_t* p_wheel);
T_mkCode mk_hid_mouse_getACPan     (T_mkMouse* p_mouse, int32_t* p_acPan);
T_mkCode mk_hid_mouse_setRectangle (T_mkMouse* p_mouse, real32_t p_x, real32_t p_y,
                                    real32_t p_width, real32_t p_height);
```

`mk_hid_mouse_setRectangle` constrains the cursor's movement area. The `T_mkCursor` embedded in `T_mkMouse` is updated by the HID layer on each input event and reflects the absolute screen position of the cursor.

#### Keyboard

```c
T_mkCode mk_hid_keyboard_getID          (T_mkKeyboard* p_keyboard, uint16_t* p_id);
T_mkCode mk_hid_keyboard_setCountryCode (T_mkKeyboard* p_keyboard, uint16_t p_countryCode);
```

#### Joystick

```c
T_mkCode mk_hid_joystick_getID       (T_mkJoystick* p_joystick, uint16_t* p_id);
T_mkCode mk_hid_joystick_getStick    (T_mkJoystick* p_joystick, T_mkStick3* p_stick);
T_mkCode mk_hid_joystick_getThrottle (T_mkJoystick* p_joystick, T_mkThrottle* p_throttle);
```

#### LED

```c
T_mkCode mk_hid_led_getID (T_mkLed* p_led, uint16_t* p_id);
void mk_hid_led_toogle ( T_mkLed* p_led, uint16_t p_id );
```

---

## 6. Application event model

The full chain from hardware input to application callback is:

```
  USB interrupt (ISR)
       │  mk_event_set(channelEvent[n])
       ▼
  HID task — mk_hid_parseInput
       │  mk_hid_dispatchMessage(report, ctrlEvent)
       │  mk_mail_post → dispatcher mailbox
       ▼
  Dispatcher task (priority 3, higher than HID)
       │  T_mkDispatcherMessage { appCtrl*, ctrlEvt, tick }
       │  mk_mail_post → listener mailbox
       ▼
  Application listener
       │  receives T_mkListenerMessage
       │  reads T_mkMouse / T_mkKeyboard / T_mkJoystick by pointer
       ▼
  Application logic
```

The `ctrlEvt` field in `T_mkDispatcherMessage` is a value from `T_mkCtrlEvent`:

| Event | Value | Meaning |
|---|---|---|
| `K_MK_EVENT_NO` | 0 | No change |
| `K_MK_EVENT_PRESS` / `K_MK_EVENT_ON` | 1 | Button pressed / control activated |
| `K_MK_EVENT_XPRESS` | 2 | Extended press (auto-repeat) |
| `K_MK_EVENT_RELEASE` / `K_MK_EVENT_OFF` / `K_MK_EVENT_PUSH` | 3 | Button released |
| `K_MK_EVENT_CLICK` | 5 | Single click |
| `K_MK_EVENT_DOUBLE_CLICK` | 7 | Double click |
| `K_MK_EVENT_MOVE` | 9 | Pointer moved |
| `K_MK_EVENT_VSCROLL` | 12 | Vertical scroll |
| `K_MK_EVENT_HSCROLL` | 13 | Horizontal scroll |
| `K_MK_EVENT_CONNECT` | 14 | Device connected |
| `K_MK_EVENT_DISCONNECT` | 15 | Device disconnected |
| `K_MK_EVENT_KEY_DOWN` | 18 | Key pressed |
| `K_MK_EVENT_KEY_ROLLOVER` | 16 | Rollover error |

The dispatcher mailbox has a depth of 8 (`K_MK_DISPATCHER_MESSAGE_NUMBER`). Since the dispatcher has a higher priority than the HID task, it normally drains the queue faster than the HID task fills it. However, a slow application listener can cause back-pressure; messages arriving when the queue is full are dropped.

---

## 7. MSC layer

The MSC terminal (`mk_msc_task`) manages USB Mass Storage Class devices. It implements the **Bulk-Only Transport (BBB)** protocol with SCSI command set, and acts as the hardware backend of the Mk filesystem by exposing a `T_mkDisk`-compatible interface.

### 7.1 Bulk-Only Transport and SCSI

Every SCSI command exchange follows the CBW → Data → CSW sequence:

```
Host                    Device
 │──── CBW (31 bytes) ──────▶│  Command Block Wrapper
 │◀─── Data (optional) ──────│  or Host→Device data
 │◀─── CSW (13 bytes) ───────│  Command Status Wrapper
```

The CBW is implemented by `T_mkMSCommandBlockWrapper` (field `bmCBWFlags` distinguishes direction: `K_MK_MSC_CMD_BLOC_WRAPPER_HOST_TO_DEVICE = 0x00`, `DEVICE_TO_HOST = 0x80`). The CSW contains a 4-byte tag matching the CBW, byte residue, and status code.

The SCSI commands implemented are:

| Command | Source file |
|---|---|
| INQUIRY | `mk_msc_postInquiryRequest.c` |
| MODE SENSE (6) | `mk_msc_postModeSenseRequest.c` |
| READ CAPACITY (10) | `mk_msc_postReadCapacityRequest.c` |
| READ FORMAT CAPACITIES | `mk_msc_postReadFormatCapacitiesRequest.c` |
| READ (10) | `mk_msc_postReadRequest.c` |
| READ (16) | `mk_msc_postRead64Request.c` |
| WRITE (10) | `mk_msc_postWriteRequest.c` |
| WRITE (16) | `mk_msc_postWrite64Request.c` |
| REQUEST SENSE | `mk_msc_postRequestSenseRequest.c` |
| TEST UNIT READY | `mk_msc_postTestUnitReadyRequest.c` |

READ/WRITE (16) variants support LBA addresses up to 64 bits, covering devices larger than 2 TB.

The maximum number of logical units per device is 16 (`K_MK_MSC_MAX_LUN`).

### 7.2 Disk abstraction and filesystem bridge

The MSC layer exposes each LUN as a `T_mkDisk` object. The filesystem stack issues read/write requests by posting a `T_mkDiskRequest` message to the MSC terminal's request mailbox (`T_mkMSCRequestArea`). The MSC handler:

1. Dequeues the `T_mkDiskRequest`.
2. Translates it to the appropriate SCSI READ/WRITE command.
3. Executes the Bulk-Only transfer via the device's bulk IN/OUT pipes.
4. On completion, either resumes the calling task (synchronous path, for privileged tasks) or triggers the registered `T_mkCallback` (asynchronous path, for unprivileged tasks).

The callback signature for disk operations is:

```c
void f_callback(T_mkCode p_err, T_mkAddr p_buf,
                uint32_t p_numberOfBlock, uint32_t p_bytesTransfered);
```

The polling interval of the MSC handler is `K_MK_MSC_REFRESH_TIMEOUT` = 100 ms for device status refresh; actual disk I/O is triggered on demand.

### 7.3 API reference

The MSC layer does not expose a direct user-facing API for disk I/O; transfers are initiated through the filesystem layer which posts requests to the MSC mailbox. Application code interacts with MSC storage exclusively through the filesystem API documented on the **[Work with files and storage](File-System)** wiki page.

---

## 8. Static memory model

All USB objects are allocated from statically declared pools, with no use of `malloc`. Every pool global is placed in the `K_MK_PRIVILEGED_DMA_MEMORY` section, which maps to an SRAM region accessible by the USB OTG core's DMA engine. This is mandatory: the peripheral writes received data directly into the pool buffers, so they must be reachable from the DMA bus master.

The ten pool objects are described below, grouped by layer.

### HCD layer — `T_mkHCDPool` (`g_mkHCDPool`)

`T_mkHCDPool` is a compound pool that manages the four enumeration descriptor types through a single backing buffer of `K_MK_HCD_POOL_SIZE` words.

| Sub-pool | Object type | Max instances | Capacity constant |
|---|---|---|---|
| `g_mkHCDPool.devicePool` | `T_mkHCDDevice` | 32 | `K_MK_HCD_MAX_DEVICE_NUMBER` |
| `g_mkHCDPool.interfacePool` | `T_mkHCDInterfaceDescriptor` | 64 | `K_MK_HCD_MAX_INTERFACE_NUMBER` (= 2 × devices) |
| `g_mkHCDPool.endpointPool` | `T_mkHCDEndpointDescriptor` | 192 | `K_MK_HCD_MAX_ENDPOINT_NUMBER` (= 3 × interfaces) |
| `g_mkHCDPool.hubPool` | `T_mkHCDHubDescriptor` | 8 | `K_MK_HCD_MAX_HUB_NUMBER` |

### HID layer — `T_mkHIDPool` (`g_mkHIDPool`)

`T_mkHIDPool` is a compound pool backed by a single `K_MK_HID_POOL_SIZE`-word buffer, carved into four sub-pools at initialisation.

| Sub-pool | Object type | Max instances | Capacity constant |
|---|---|---|---|
| `g_mkHIDPool.devicePool` | `T_mkHIDDevice` | 16 | `K_MK_HID_MAX_DEVICE_NUMBER` (= devices >> 1) |
| `g_mkHIDPool.itemPool` | `T_mkHIDItem` | 512 | `K_MK_HID_POOL_MAX_ITEM_NUMBER` |
| `g_mkHIDPool.itemStatePool` | `T_mkHIDLocalTable` | 5 | `K_MK_HID_POOL_MAX_LOCAL_TABLE_NUMBER` |
| `g_mkHIDPool.reportPool` | `T_mkHIDReport` | 32 | `K_MK_HID_POOL_MAX_REPORT_NUMBER` |

### HID control pools

Each HID control type has its own flat pool, with a `heap[]` array embedded directly in the pool struct.

| Global | Pool type | Object type | Max instances | Capacity constant |
|---|---|---|---|---|
| `g_mkMousePool` | `T_mkMousePool` | `T_mkMouse` | 10 | `K_MK_MOUSE_NUMBER` |
| `g_mkKeyboardPool` | `T_mkKeyboardPool` | `T_mkKeyboard` | 10 | `K_MK_KEYBOARD_NUMBER` |
| `g_mkJoystickPool` | `T_mkJoystickPool` | `T_mkJoystick` | 4 | `K_MK_JOYSTICK_NUMBER` |
| `g_mkButtonPool` | `T_mkButtonPool` | `T_mkButton` | 96 | `K_MK_BUTTON_NUMBER` |
| `g_mkConsumerPool` | `T_mkConsumerPool` | `T_mkConsumerControl` | 10 | `K_MK_CONSUMER_NUMBER` |
| `g_mkKeyPool` | `T_mkKeyPool` | `T_mkKey` | 32 | `K_MK_KEY_NUMBER` |
| `g_mkLedPool` | `T_mkLedPool` | `T_mkLed` | 16 | `K_MK_LED_NUMBER` |

### MSC layer — `T_mkMSCPool` (`g_mkMSCPool`)

`T_mkMSCPool` holds a single sub-pool backed by a `K_MK_MSC_POOL_SIZE`-word buffer.

| Sub-pool | Object type | Max instances | Capacity constant |
|---|---|---|---|
| `g_mkMSCPool.pool` | `T_mkMSCDevice` | 16 | `K_MK_MSC_MAX_DEVICE_NUMBER` (= devices >> 1) |

### Notes on pool sizing

The `T_mkHIDItem` pool (`K_MK_HID_POOL_MAX_ITEM_NUMBER = 512`) is the most significant cost. Each item encodes one field from the report descriptor — logical range, physical range, bit offset, bit size, usage — and complex devices (multi-axis joysticks, gaming mice with 20+ buttons) can consume hundreds of items. The 512-item limit is an architectural ceiling; a device whose descriptor produces more than 512 items will be rejected during parsing.

The `K_MK_HID_POOL_MAX_LOCAL_TABLE_NUMBER = 5` limit on `T_mkHIDLocalTable` reflects the parser's state stack depth. A report descriptor that nests more than five `Collection` scopes will exhaust this pool during parsing.

---

## See also

- [Architecture Overview](Architecture-Overview) — system layers, memory map, privilege model, boot sequence
- [Kernel internals](Kernel-API) — tasks, memory pools, synchronisation objects
- [Work with files and storage](File-System) — disk, volume and file API
