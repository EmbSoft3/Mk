# Handle keyboard, mouse and input events

This page describes how input events are delivered to fields and containers in the Mk graphical engine, and how to write listener callbacks that react to mouse, keyboard, and joystick input.

---

## Table of contents

1. [Event pipeline overview](#1-event-pipeline-overview)
2. [Event identifiers](#2-event-identifiers)
   - 2.1 [Control types](#21-control-types)
   - 2.2 [Event identifiers](#22-event-identifiers)
3. [Listener model](#3-listener-model)
   - 3.1 [Listener signature](#31-listener-signature)
   - 3.2 [Container listener vs field listener](#32-container-listener-vs-field-listener)
4. [Mouse events](#4-mouse-events)
   - 4.1 [Mouse structure](#41-mouse-structure)
   - 4.2 [Movement and position](#42-movement-and-position)
   - 4.3 [Button events](#43-button-events)
5. [Keyboard events](#5-keyboard-events)
   - 5.1 [Keyboard structure](#51-keyboard-structure)
   - 5.2 [Key events and the ctrlId field](#52-key-events-and-the-ctrlid-field)
6. [Joystick events](#6-joystick-events)
   - 6.1 [Joystick structure](#61-joystick-structure)
   - 6.2 [Events](#62-Events)
7. [Connect and disconnect events](#7-Connect-disconnect-mount-and-unmount-events)
8. [Triggering repaints from a listener](#8-triggering-repaints-from-a-listener)
9. [Working example](#9-working-example)

---

## 1. Event pipeline overview

Input events flow from hardware to listener callbacks through a fixed pipeline:

```
 USB device (HID keyboard / mouse / joystick)
        │
        ▼
 USB HID task
 USB MSC task (mount/unmount volumes)
        │
        ▼
 Dispatcher task
   • builds T_mkCtrlEvent
   • routes to listener mailbox (depth 8)
        │
        ▼
 Listener task (privileged, priority 7)  /  Unprivileged listener (priority 6)
        │
        ▼
 mk_display_listenContainer()
   • iterates all active fields in all containers
   • calls mk_field_inside() to determine spatial hit
   • updates field.focus / field.cursor
   • invokes container listener callback
   • invokes field listener callback (if set)
        │
        ▼
 Application listener callback
```

**USB HID** devices (keyboard, mouse, joystick, gamepad) produce raw HID reports decoded into `T_mkKeyboard`, `T_mkMouse`, and `T_mkJoystick` structures. **USB MSC** devices (mass storage) produce `K_MK_EVENT_MOUNT` and `K_MK_EVENT_UNMOUNT` events when volumes are mounted or unmounted.

The dispatcher runs at approximately 100 Hz for pointer events and on each HID report for keyboard events.

---

## 2. Event identifiers

### 2.1 Control types

| Constant | Value | Device |
|---|---|---|
| `K_MK_CONTROL_MOUSE` | 1 | HID mouse |
| `K_MK_CONTROL_KEYBOARD` | 2 | HID keyboard |
| `K_MK_CONTROL_JOYSTICK` | 3 | HID joystick or gamepad |
| `K_MK_CONTROL_MSC` | 5 | USB Mass Storage Class device |

### 2.2 Event identifiers

All constants are defined in `mk_display_events_types.h`.

**Mouse events**

| Constant | Trigger |
|---|---|
| `K_MK_EVENT_MOVE` | Pointer position changed |
| `K_MK_EVENT_PRESS` | Button pressed |
| `K_MK_EVENT_RELEASE` | Button released |
| `K_MK_EVENT_CLICK` | Press and release within the timeout |
| `K_MK_EVENT_DOUBLE_CLICK` | Double press and release within the timeout |
| `K_MK_EVENT_VSCROLL` | Vertical mouse wheel rotated |
| `K_MK_EVENT_HSCROLL` | Horizontal mouse wheel rotated |
| `K_MK_EVENT_CONNECT` | Mouse connected |
| `K_MK_EVENT_DISCONNECT` | Mouse disconnected |

**Keyboard events**

| Constant | Trigger |
|---|---|
| `K_MK_EVENT_KEY_DOWN` | Physical key pressed (scancode) |
| `K_MK_EVENT_KEY_HOLD` | Physical Key held down (auto-repeat) |
| `K_MK_EVENT_KEY_UP` | Physical key released |
| `K_MK_EVENT_CHAR_DOWN` | Printable character pressed (Unicode codepoint in `key`) |
| `K_MK_EVENT_CHAR_HOLD` | Printable character held (auto-repeat) |
| `K_MK_EVENT_CHAR_UP` | Printable character released |
| `K_MK_EVENT_KEY_POSTFAIL` | Key could not be registered (internal error) |
| `K_MK_EVENT_KEY_ROLLOVER` | Too many simultaneous keys (rollover limit reached) |
| `K_MK_EVENT_CONNECT` | Keyboard connected |
| `K_MK_EVENT_DISCONNECT` | Keyboard disconnected |

**Joystick events**

| Constant | Trigger |
|---|---|
| `K_MK_EVENT_MOVE` | Pointer position changed |
| `K_MK_EVENT_THROTTLE` | Throttle position changed |
| `K_MK_EVENT_PRESS` | Button pressed |
| `K_MK_EVENT_RELEASE` | Button released |
| `K_MK_EVENT_CLICK` | Press and release within the timeout |
| `K_MK_EVENT_DOUBLE_CLICK` | Double press and release within the timeout |
| `K_MK_EVENT_HAT_SWITCH_DOWN` | Hat switch moved to a new direction |
| `K_MK_EVENT_HAT_SWITCH_UP` | Hat switch released |
| `K_MK_EVENT_CONNECT` | Joystick connected |
| `K_MK_EVENT_DISCONNECT` | Joystick disconnected |

**Field events**

| Constant | Trigger |
|---|---|
| `K_MK_EVENT_ENTER` | Pointer entered the field's bounding box |
| `K_MK_EVENT_EXIT` | Pointer left the field's bounding box |
| `K_MK_EVENT_XPRESS` | Button pressed inside a field, no position check needed |
| `K_MK_EVENT_XRELEASE` | Button released inside a field, no position check needed |
| `K_MK_EVENT_XCLICK` | Click inside a field, no position check needed |
| `K_MK_EVENT_DOUBLE_XCLICK` | Double click inside a field, no position check needed |

**File system events**

| Constant | Trigger |
|---|---|
| `K_MK_EVENT_MOUNT` | Volume mounted and accessible |
| `K_MK_EVENT_UNMOUNT` | Volume unmounted or device removed |

---

## 3. Listener model

### 3.1 Listener signature

Both container and field listeners share the same function signature:

```c
T_mkCode myListener(T_mkContainer* p_container,
                    T_mkField*     p_field,
                    T_mkCtrlId     p_ctrlId,
                    T_mkAddr       p_ctrl,
                    T_mkCtrlEvent  p_evt,
                    uint32_t       p_id);
```

| Parameter | Description |
|---|---|
| `p_container` | The container that owns the field involved in the event |
| `p_field` | The field associated with the event (see §3.2) |
| `p_ctrlId` | Type of device (`K_MK_CONTROL_*`) |
| `p_ctrl` | Pointer to the device state structure; cast according to `p_ctrlId` |
| `p_evt` | Event identifier (`K_MK_EVENT_*`) |
| `p_id` | Device index among devices of the same class |

The callback must return `K_MK_OK`. 

### 3.2 Container listener vs field listener

**Container listener** — registered at `mk_container_create`. Called for every event that touches any field in the container. `p_field` points to the field actually involved in the event (the field under the cursor, or the focused field for keyboard events).

**Field listener** — registered via `mk_field_setListener` or a widget-specific equivalent. Called only when the event targets that specific field. `p_field` points to the specific field associated with the event.

A listener is executed only if `field.activity == K_MK_FIELD_ACTIF`, regardless of the field's visibility. An invisible but active field still receives events.

---

## 4. Mouse events

### 4.1 Mouse structure

When `p_ctrlId == K_MK_CONTROL_MOUSE`, `p_ctrl` points to a `T_mkMouse`:

```c
struct T_mkMouse
{
    T_mkMouseLayer layer;   /* control type (K_MK_CONTROL_MOUSE) and unique id */
    T_mkAxis2      axis;    /* pointer position and relative displacement */
    T_mkWheel      wheel;   /* vertical scroll wheel */
    T_mkWheel      acPan;   /* horizontal pan (AC Pan) */
    T_mkButton*    button;  /* linked list of buttons */
    T_mkCursor     cursor;  /* graphical cursor object */
};

struct T_mkAxis2
{
    T_mkAxisRect rectangle; /* bounding plane (x, y, width, height as real32_t) */
    int32_t      dx;        /* relative displacement on X since last report */
    int32_t      dy;        /* relative displacement on Y since last report */
    real32_t     x;         /* current absolute position on X (pixels) */
    real32_t     y;         /* current absolute position on Y (pixels) */
    real32_t     resolution;
};

struct T_mkWheel
{
    int32_t delta;          /* displacement since last report */
};

struct T_mkButton                /* one node of the button linked list */
{
    T_mkButton*      nextButton; /* next button, or NULL */
    T_mkButtonState  state;      /* state.value: 1 = pressed, 0 = released */
    T_mkButtonLayer  layer;      /* layer.id: button identifier, layer.type: button type */
    T_mkButtonTick   tick;       /* timing data for click / double-click generation */
};
```

The absolute cursor position is in `mouse->axis.x` and `mouse->axis.y` (`real32_t`, in pixels, bounded to the screen rectangle). The relative displacement since the last HID report is in `mouse->axis.dx` and `mouse->axis.dy` (`int32_t`).

Buttons are accessed by walking the linked list starting at `mouse->button`. `button->state.value` holds the current pressed state (1 = pressed, 0 = released) and `button->layer.id` identifies the button. When a button event is delivered, `p_id` in the listener callback carries `button->layer.id` of the button that triggered the event.

---

### 4.2 Movement and position

`K_MK_EVENT_MOVE` fires whenever the pointer position changes. `K_MK_EVENT_ENTER` and `K_MK_EVENT_EXIT` bracket the time the cursor spends inside a field's bounding box. The check against the field boundary is done by the engine using `mk_field_inside(p_field, mouse->axis.x, mouse->axis.y)`.

For `K_MK_EVENT_MOVE`, `K_MK_EVENT_ENTER`, and `K_MK_EVENT_EXIT`, `p_id` is 0.

```c
if (p_ctrlId == K_MK_CONTROL_MOUSE)
{
    T_mkMouse* mouse = (T_mkMouse*) p_ctrl;

    if (p_evt == K_MK_EVENT_ENTER)
    {
        /* Cursor entered the field — update hover state and trigger repaint */
        mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_ENABLED);
    }
    else if (p_evt == K_MK_EVENT_EXIT)
    {
        /* Cursor left the field — remove hover state and trigger repaint */
        mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_ENABLED);
    }
    else if (p_evt == K_MK_EVENT_MOVE)
    {
        /* mouse->axis.x, mouse->axis.y: current absolute position */
        /* mouse->axis.dx, mouse->axis.dy: relative displacement since last report */
    }
}
```

---

### 4.3 Button events

The engine provides two sets of button events:

**Position-aware events** (`K_MK_EVENT_PRESS`, `K_MK_EVENT_RELEASE`, `K_MK_EVENT_CLICK`, `K_MK_EVENT_DOUBLE_CLICK`) are dispatched to all active fields regardless of cursor position. The listener is responsible for verifying the cursor location if needed, for example by calling `mk_field_inside`.

**Field-targeted events** (`K_MK_EVENT_XPRESS`, `K_MK_EVENT_XRELEASE`, `K_MK_EVENT_XCLICK`, `K_MK_EVENT_DOUBLE_XCLICK`) are delivered by the engine only to the field that currently has focus (cursor over it). No position check is required in the listener.

**Click timing** — `K_MK_EVENT_CLICK` (and its X variant) is generated only if the release occurs within `K_MK_EVENT_CLICK_TIMEOUT` milliseconds of the press. A `K_MK_EVENT_DOUBLE_CLICK` is generated when two press/release sequences occur within `K_MK_EVENT_DOUBLE_CLICK_TIMEOUT` milliseconds. If these timing conditions are not met, only `PRESS` and `RELEASE` are generated.

For all button events, `p_id` carries the `button->layer.id` of the button involved (e.g. 1 = left button, 2 = right button, 3 = middle button, depending on the HID descriptor of the mouse).

```c
if (p_ctrlId == K_MK_CONTROL_MOUSE)
{
    if (p_evt == K_MK_EVENT_XCLICK)
    {
        /* p_id identifies which button was clicked */
        if (p_id == 1)   /* left button */
            handleLeftClick();
        else if (p_id == 2)   /* right button */
            handleRightClick();
    }
    else if (p_evt == K_MK_EVENT_DOUBLE_XCLICK)
    {
        if (p_id == 1)
            handleDoubleClick();
    }
}
```

---

### 4.4 Scroll events

`K_MK_EVENT_VSCROLL` fires when the vertical scroll wheel moves. `K_MK_EVENT_HSCROLL` fires when the horizontal pan control (AC Pan) moves. For both events, `p_id` is 0.

The scroll amount is read from `mouse->wheel.delta` for vertical scroll and `mouse->acPan.delta` for horizontal pan. A negative `delta` means scrolling upward (or left), a positive `delta` means scrolling downward (or right).

```c
if (p_ctrlId == K_MK_CONTROL_MOUSE)
{
    T_mkMouse* mouse = (T_mkMouse*) p_ctrl;

    if (p_evt == K_MK_EVENT_VSCROLL)
    {
        if (mouse->wheel.delta < 0)
            scrollUp();
        else if (mouse->wheel.delta > 0)
            scrollDown();
    }
    else if (p_evt == K_MK_EVENT_HSCROLL)
    {
        if (mouse->acPan.delta < 0)
            scrollLeft();
        else if (mouse->acPan.delta > 0)
            scrollRight();
    }
}
```

---

## 5. Keyboard events

### 5.1 Keyboard structure

When `p_ctrlId == K_MK_CONTROL_KEYBOARD`, `p_ctrl` points to a `T_mkKeyboard`:

```c
struct T_mkKeyboard
{
    T_mkKeyboardLayer  layer;      /* control type (K_MK_CONTROL_KEYBOARD), unique id,
                                      keyboard layout (AZERTY/QWERTY…), country code */
    T_mkKeyCode*       modifier;   /* linked list of modifier keys (Ctrl, Shift, Alt, GUI…)
                                      T_mkKeyCode is a typedef for T_mkButton */
    T_mkKey*           input;      /* linked list of currently pressed keys */
    T_mkUTFKey*        output;     /* pointer to the T_mkUTFKey of the last processed key */
    T_mkLed*           indicator;  /* keyboard LED state (Caps Lock, Num Lock, Scroll Lock) */
    T_mkSpKey          specialKey; /* bitfield: capslock, numlock, scrolllock state */
    T_mkKeyboardLookup lookup;     /* pointer to the active keymap table */
};

struct T_mkKey               /* one node of the input linked list */
{
    T_mkButton button;       /* button state (pressed/released, timing for hold) */
    T_mkUTFKey key;          /* key codes for this entry */
};

struct T_mkUTFKey            /* key code payload */
{
    uint16_t scancode;       /* USB HID scancode (HID Usage Tables §10) */
    uint8_t  padding8;
    uint8_t  ascii;          /* ASCII code (8-bit) */
    uint32_t utf8;           /* UTF-8 codepoint */
    uint32_t utf16;          /* UTF-16 codepoint */
    uint32_t utf32;          /* UTF-32 codepoint */
};

struct T_mkSpKey             /* special key state bitfield */
{
    unsigned_t capslock:1;
    unsigned_t numlock:1;
    unsigned_t scrolllock:1;
    unsigned_t reserved:29;
};
```

For all key events (`KEY_DOWN`, `KEY_HOLD`, `KEY_UP`, `CHAR_DOWN`, `CHAR_HOLD`, `CHAR_UP`), **`p_id` carries the USB HID scancode** of the key that triggered the event.

`keyboard->output` points to the `T_mkUTFKey` of the last processed key. It is valid for the entire duration of the callback and provides the scancode as well as the Unicode codepoints (`utf8`, `utf16`, `utf32`) resulting from the keyboard layout and active modifiers. This pointer is particularly useful on `CHAR_*` events to retrieve the printable character.

`keyboard->modifier` is a linked list of `T_mkKeyCode` (aliased to `T_mkButton`) nodes, one per modifier key (Ctrl, Shift, Alt, GUI…). Walk the list and check `node->state.value == 1` to test whether a given modifier is currently held.

This is the pattern used in the [Pong listener](https://github.com/EmbSoft3/Pong/blob/main/Pong/Sources/Pong/mk_pong_listenPlayground.c) to drive paddles — `p_id` is checked directly against the scancode constant:

```c
if (p_ctrlId == K_MK_CONTROL_KEYBOARD)
{
    if (p_id == K_MK_KEYBOARD_UP_ARROW)
        g_pong.rightPaddle.dy = -K_MK_PONG_PADDLE_SPEED;
    else if (p_id == K_MK_KEYBOARD_DOWN_ARROW)
        g_pong.rightPaddle.dy = +K_MK_PONG_PADDLE_SPEED;
}
```

Since the listener is called on `KEY_DOWN`, `KEY_HOLD`, and `KEY_UP`, reading `p_id` directly always reflects the current key at each call.

---

### 5.2 Key events

| Event | Trigger | `p_id` | `keyboard->output` |
|---|---|---|---|
| `K_MK_EVENT_KEY_DOWN` | Physical key pressed | HID scancode | valid — layout not applied |
| `K_MK_EVENT_KEY_HOLD` | Key held (auto-repeat) | HID scancode | valid |
| `K_MK_EVENT_KEY_UP` | Physical key released | HID scancode | valid |
| `K_MK_EVENT_CHAR_DOWN` | Printable character pressed | HID scancode | valid — `utf32` holds the Unicode codepoint |
| `K_MK_EVENT_CHAR_HOLD` | Printable character held | HID scancode | valid |
| `K_MK_EVENT_CHAR_UP` | Printable character released | HID scancode | valid |
| `K_MK_EVENT_KEY_POSTFAIL` | Key registration failed | — | — |
| `K_MK_EVENT_KEY_ROLLOVER` | Too many simultaneous keys | — | — |
| `K_MK_EVENT_CONNECT` | Keyboard connected | — | — |
| `K_MK_EVENT_DISCONNECT` | Keyboard disconnected | — | — |

Use `KEY_*` events for navigation keys, function keys, and non-printable keys — check `p_id` against `K_MK_KEYBOARD_*` scancode constants. Use `CHAR_*` events for text input — read the Unicode codepoint from `keyboard->output->utf32`.

```c
if (p_ctrlId == K_MK_CONTROL_KEYBOARD)
{
    T_mkKeyboard* keyboard = (T_mkKeyboard*) p_ctrl;

    if (p_evt == K_MK_EVENT_KEY_DOWN)
    {
        /* p_id is the HID scancode */
        if (p_id == K_MK_KEYBOARD_LEFT_ARROW)
            moveCursorLeft();
    }
    else if (p_evt == K_MK_EVENT_CHAR_DOWN)
    {
        /* keyboard->output->utf32 is the Unicode codepoint after layout + modifiers */
        appendCharacter(keyboard->output->utf32);
    }
}
```

---

## 6. Joystick events

### 6.1 Joystick structure

When `p_ctrlId == K_MK_CONTROL_JOYSTICK`, `p_ctrl` points to a `T_mkJoystick`:

```c
struct T_mkJoystick
{
    T_mkJoystickLayer layer;      /* control type (K_MK_CONTROL_JOYSTICK) and unique id */
    T_mkStick3        stick;      /* 3-axis stick with rotation axes */
    T_mkThrottle      throttle;   /* single-axis throttle/slider control */
    T_mkHatSwitch     hatSwitch;  /* directional hat switch (D-pad) */
    T_mkLed*          indicator;  /* linked list of LED indicators */
    T_mkButton*       button;     /* linked list of buttons */
};

struct T_mkStick3
{
    T_mkStickCoord current;  /* raw HID values: x, y, z, rx, ry, rz (int32_t) */
    T_mkStickCoord last;     /* previous raw values */

    real32_t x, y, z;        /* modulated absolute position on each translation axis */
    real32_t dx, dy, dz;     /* variation since last report on each translation axis */
    real32_t rx, ry, rz;     /* modulated absolute position on each rotation axis */
};

struct T_mkThrottle
{
    int32_t value;      /* current throttle position */
    int32_t lastValue;  /* previous position */
    int32_t min;        /* minimum reported value */
    int32_t max;        /* maximum reported value */
};

struct T_mkHatSwitch
{
    int32_t value;      /* current hat switch direction */
    int32_t lastValue;  /* previous direction */
    int32_t min;        /* minimum valid direction value */
    int32_t max;        /* maximum valid direction value */
};
```

---

### 6.2 Events

The joystick dispatcher generates separate events for each control. All events carry `p_ctrl` pointing to the `T_mkJoystick`.

| Event | Source | `p_id` |
|---|---|---|
| `K_MK_EVENT_MOVE` | Stick: any of x/y/z/rx/ry/rz changed | 0 |
| `K_MK_EVENT_THROTTLE` | Throttle value changed | 0 |
| `K_MK_EVENT_HAT_SWITCH_DOWN` | Hat switch moved to a direction | `hatSwitch.value` (new direction) |
| `K_MK_EVENT_HAT_SWITCH_UP` | Hat switch released from a direction | `hatSwitch.lastValue` (previous direction) |
| `K_MK_EVENT_PRESS` | Button pressed | `button->layer.id` |
| `K_MK_EVENT_RELEASE` | Button released | `button->layer.id` |
| `K_MK_EVENT_CLICK` | Button clicked (within timeout) | `button->layer.id` |
| `K_MK_EVENT_DOUBLE_CLICK` | Button double-clicked | `button->layer.id` |
| `K_MK_EVENT_CONNECT` | Joystick connected | — |
| `K_MK_EVENT_DISCONNECT` | Joystick disconnected | — |

On `K_MK_EVENT_MOVE`, read the modulated positions and variations from `joystick->stick`. A dead zone should be applied to ignore small deviations around the neutral position. On `K_MK_EVENT_HAT_SWITCH_DOWN`, `p_id` carries the new direction value.

```c
if (p_ctrlId == K_MK_CONTROL_JOYSTICK)
{
    T_mkJoystick* joystick = (T_mkJoystick*) p_ctrl;

    if (p_evt == K_MK_EVENT_MOVE)
    {
        real32_t x = joystick->stick.x;
        real32_t y = joystick->stick.y;

        /* Dead zone: ignore values close to neutral */
        if      (x >  0.5f) moveRight();
        else if (x < -0.5f) moveLeft();
        if      (y >  0.5f) moveDown();
        else if (y < -0.5f) moveUp();
    }
    else if (p_evt == K_MK_EVENT_THROTTLE)
    {
        setThrottle(joystick->throttle.value);
    }
    else if (p_evt == K_MK_EVENT_HAT_SWITCH_DOWN)
    {
        /* p_id is the new hat switch direction value */
        handleDPadPress((int32_t) p_id);
    }
    else if (p_evt == K_MK_EVENT_HAT_SWITCH_UP)
    {
        /* p_id is the direction that was just released */
        handleDPadRelease((int32_t) p_id);
    }
    else if (p_evt == K_MK_EVENT_PRESS)
    {
        /* p_id is button->layer.id of the pressed button */
        if (p_id == 1) handleFire();
        if (p_id == 2) handleJump();
    }
}
```

---

## 7. Connect, disconnect, mount and unmount events

### 7.1 USB device connection — CONNECT and DISCONNECT

`K_MK_EVENT_CONNECT` and `K_MK_EVENT_DISCONNECT` are generated when a USB peripheral is physically connected or disconnected. They are sent for every type of USB HID device and for USB mass storage disks.

| `p_ctrlId` | Trigger | `p_ctrl` type |
|---|---|---|
| `K_MK_CONTROL_MOUSE` | Mouse plugged/unplugged | `T_mkMouse*` |
| `K_MK_CONTROL_KEYBOARD` | Keyboard plugged/unplugged | `T_mkKeyboard*` |
| `K_MK_CONTROL_JOYSTICK` | Joystick plugged/unplugged | `T_mkJoystick*` |
| `K_MK_CONTROL_DISK` | MSC disk attached/detached | `T_mkDisk*` |

For HID devices, the system handles the `CONNECT` event internally before forwarding it to the application: on mouse connect, the graphical cursor is initialised and added to the display container; on mouse disconnect, the cursor is removed. The `CONNECT`/`DISCONNECT` events are then forwarded to the application listener so that the application can react — for example by enabling or disabling UI elements that depend on the presence of the device.

For `K_MK_CONTROL_DISK`, `K_MK_EVENT_CONNECT` fires once the disk has been successfully enumerated by the MSC driver and is ready to be used. `K_MK_EVENT_DISCONNECT` fires when the disk object is deleted, which happens when the USB device is removed. `p_id` is `disk->layer.id` in both cases.

```c
if (p_ctrlId == K_MK_CONTROL_MOUSE)
{
    if (p_evt == K_MK_EVENT_CONNECT)
    {
        /* Mouse is available — p_ctrl points to the initialised T_mkMouse */
        enableMouseUI();
    }
    else if (p_evt == K_MK_EVENT_DISCONNECT)
    {
        /* Mouse removed — disable any UI that depended on it */
        disableMouseUI();
    }
}
else if (p_ctrlId == K_MK_CONTROL_DISK)
{
    T_mkDisk* disk = (T_mkDisk*) p_ctrl;

    if (p_evt == K_MK_EVENT_CONNECT)
    {
        /* Disk is ready — volumes may follow shortly with MOUNT events */
    }
    else if (p_evt == K_MK_EVENT_DISCONNECT)
    {
        /* Disk removed */
    }
}
```

---

### 7.2 File system volume — MOUNT and UNMOUNT

`K_MK_EVENT_MOUNT` and `K_MK_EVENT_UNMOUNT` are generated by the file system layer when a partition (volume) is mounted or unmounted. They are independent from the physical device connection: a disk can be connected (`CONNECT`) and then have each of its partitions mounted (`MOUNT`) as separate events. Similarly, partitions are unmounted (`UNMOUNT`) before the disk is disconnected (`DISCONNECT`).

For these events `p_ctrlId` is always `K_MK_CONTROL_VOLUME` and `p_ctrl` points to a `T_mkVolume`.

```c
else if (p_ctrlId == K_MK_CONTROL_VOLUME)
{
    T_mkVolume* volume = (T_mkVolume*) p_ctrl;

    if (p_evt == K_MK_EVENT_MOUNT)
    {
        /* A new partition is available — file I/O can now be performed on it */
    }
    else if (p_evt == K_MK_EVENT_UNMOUNT)
    {
        /* Partition is about to be removed — close any open files on it */
    }
}
```

A typical sequence when a USB flash drive is inserted then removed:

```
K_MK_EVENT_CONNECT    (K_MK_CONTROL_DISK,   T_mkDisk*)    ← disk enumerated
K_MK_EVENT_MOUNT      (K_MK_CONTROL_VOLUME, T_mkVolume*)  ← partition 1 mounted
[... file I/O ...]
K_MK_EVENT_UNMOUNT    (K_MK_CONTROL_VOLUME, T_mkVolume*)  ← partition 1 unmounted
K_MK_EVENT_DISCONNECT (K_MK_CONTROL_DISK,   T_mkDisk*)    ← disk removed
```

---

## 8. Triggering repaints from a listener

A listener runs in the listener task and must not call `mk_graphics_*` functions directly. To schedule a visual update in response to an event, call `mk_field_setRefresh` on the fields that need repainting:

```c
mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_ENABLED);
```

This is thread-safe: the painter task checks the refresh counter on the next frame and calls the painter callback if the counter is non-zero.

To update multiple fields simultaneously:

```c
mk_field_setRefresh(&app->label.field,      K_MK_FIELD_REFRESH_ENABLED);
mk_field_setRefresh(&app->background.field, K_MK_FIELD_REFRESH_ENABLED);
```

---

## 9. Working example

The sketch below shows a minimal application that echoes keyboard input into a `T_mkTextField`. Characters typed generate `K_MK_EVENT_CHAR_DOWN` events; the Unicode codepoint is read from `keyboard->output->utf32` and appended to a display buffer. Navigation keys (`Backspace`, `Enter`) are handled via `K_MK_EVENT_KEY_DOWN` by checking `p_id` against the corresponding scancode constants.

```c
/* ------------------------------------------------------------------ */
/* Application state                                                   */
/* ------------------------------------------------------------------ */

typedef struct {
    T_mkContainer* container;
    T_mkScreen     background;
    T_mkTextField  output;
    uint32_t       buf [256];   /* UTF-32 output buffer */
    uint32_t       len;         /* current number of codepoints */
} T_mkEchoApp;

static T_mkEchoApp g_echoApp;

/* ------------------------------------------------------------------ */
/* Container listener                                                  */
/* ------------------------------------------------------------------ */

static T_mkCode echoApp_listen (T_mkContainer* p_container,
                                T_mkField*     p_field,
                                T_mkCtrlId     p_ctrlId,
                                T_mkAddr       p_ctrl,
                                T_mkCtrlEvent  p_evt,
                                uint32_t       p_id)
{
    T_mkCode         l_result = K_MK_OK;
    T_mkApplication* l_app    = mk_container_getOwner (p_container);
    T_mkEchoApp*     l_state  = (T_mkEchoApp*) mk_application_getArg (l_app);

    if (p_ctrlId == K_MK_CONTROL_KEYBOARD)
    {
        T_mkKeyboard* l_keyboard = (T_mkKeyboard*) p_ctrl;

        /* Printable character: append its UTF-32 codepoint to the buffer */
        if (p_evt == K_MK_EVENT_CHAR_DOWN)
        {
            if (l_state->len < (sizeof (l_state->buf) / sizeof (uint32_t)) - 1)
            {
                l_state->buf [l_state->len]     = l_keyboard->output->utf32;
                l_state->buf [l_state->len + 1] = 0;
                l_state->len++;

                mk_textField_setString (&l_state->output, (T_str8) l_state->buf);
                mk_field_setRefresh (&l_state->output.field, K_MK_FIELD_REFRESH_ENABLED);
            }
        }

        /* Navigation keys: p_id carries the HID scancode */
        else if ((p_evt == K_MK_EVENT_KEY_DOWN) || (p_evt == K_MK_EVENT_KEY_HOLD))
        {
            if (p_id == K_MK_KEYBOARD_BACKSPACE)
            {
                if (l_state->len > 0)
                {
                    l_state->len--;
                    l_state->buf [l_state->len] = 0;

                    mk_textField_setString (&l_state->output, (T_str8) l_state->buf);
                    mk_field_setRefresh (&l_state->output.field, K_MK_FIELD_REFRESH_ENABLED);
                }
            }
            else if (p_id == K_MK_KEYBOARD_ENTER)
            {
                /* Clear the output buffer on Enter */
                mk_utils_memset ((T_str8) l_state->buf, 0, sizeof (l_state->buf));
                l_state->len = 0;

                mk_textField_setString (&l_state->output, (T_str8) l_state->buf);
                mk_field_setRefresh (&l_state->output.field, K_MK_FIELD_REFRESH_ENABLED);
            }
            else
            {
                /* Ne rien faire */
            }
        }
        else
        {
            /* Ne rien faire */
        }
    }
    else
    {
        /* Ne rien faire */
    }

    /* Suppression warnings */
    (void) p_field;

    return (l_result);
}

/* ------------------------------------------------------------------ */
/* Application entry point                                             */
/* ------------------------------------------------------------------ */

void echoApp_main (T_mkAddr p_arg)
{
    T_mkEchoApp* l_app = &g_echoApp;
    (void) p_arg;

    T_mkTextStyle l_style = {
        K_MK_NULL,                    /* font: NULL -> engine default font  */
        K_MK_FONT_UTF32,              /* fontEncoding: UTF-32 buffer        */
        K_MK_TEXT_CENTER_JUSTIFIED,   /* verticalAlignment                  */
        K_MK_TEXT_LEFT_JUSTIFIED,     /* horizontalAlignment                */
        0, 0, 0, 20,                  /* marginTop, Bottom, Right, Left     */
        { 0x00, 0xFF, 0xFF, 0xFF }    /* color: T_mkARGB {b, g, r, a} white */
    };

    /* --- Container --- */
    mk_container_create (&l_app->container, 0, echoApp_listen, K_MK_NULL);

    /* --- Background screen --- */
    mk_screen_init         (&l_app->background);
    mk_screen_setPosition  (&l_app->background, 0.0f, 0.0f);
    mk_screen_setDimension (&l_app->background, 640, 480);
    mk_screen_setLayer     (&l_app->background, K_MK_GRAPHICS_FOREGROUND);
    mk_screen_setZIndex    (&l_app->background, 0);
    mk_screen_setVisibility(&l_app->background, K_MK_FIELD_VISIBLE);
    mk_screen_setActivity  (&l_app->background, K_MK_FIELD_INACTIF);
    mk_screen_setPainter   (&l_app->background, mk_screen_defaultPainter);
    mk_container_addField  (l_app->container, &l_app->background.field, K_MK_NULL);

    /* --- Output label --- */
    mk_utils_memset ((T_str8) l_app->buf, 0, sizeof (l_app->buf));
    l_app->len = 0;

    mk_textField_init          (&l_app->output);
    mk_textField_setPosition   (&l_app->output, 20.0f, 220.0f);
    mk_textField_setDimension  (&l_app->output, 600, 40);
    mk_textField_setLayer      (&l_app->output, K_MK_GRAPHICS_FOREGROUND);
    mk_textField_setZIndex     (&l_app->output, 1);
    mk_textField_setVisibility (&l_app->output, K_MK_FIELD_VISIBLE);
    mk_textField_setActivity   (&l_app->output, K_MK_FIELD_INACTIF);
    mk_textField_setPainter    (&l_app->output, mk_textField_defaultPainter);
    mk_textField_setStyle      (&l_app->output, &l_style);
    mk_textField_setString     (&l_app->output, (T_str8) l_app->buf);
    mk_container_addField      (l_app->container, &l_app->output.field, K_MK_NULL);

    /* --- Register container in the factory --- */
    mk_factory_addContainer (l_app->container, K_MK_NULL);

    /* Application event loop */
    while (1)
    {
        mk_task_sleep (100);
    }
}
```

`T_mkTextStyle` fields in order: `font`, `fontEncoding`, `verticalAlignment`, `horizontalAlignment`, `marginTop`, `marginBottom`, `marginRight`, `marginLeft`, `color` (`T_mkARGB` as `{ b, g, r, a }`). Passing `K_MK_NULL` for `font` instructs the default painter to fall back to the engine's built-in font (`g_mkDisplay.defaultFont`). The encoding is set to `K_MK_FONT_UTF32` to match the `uint32_t` output buffer; `keyboard->output->utf32` holds the codepoint after the keyboard layout and active modifiers have been applied.

Keyboard events are broadcast by the dispatcher to all active containers regardless of field focus, so no mouse interaction is needed to receive them. Calling `mk_field_setRefresh` with `K_MK_FIELD_REFRESH_ENABLED` after modifying the string resets the repaint counter to `K_MK_DISPLAY_FRAME_BUFFER_NUMBER` (8), ensuring every frame buffer in the ring is updated before painting stops.

---

## See also

- [Writing your first application](Writing-Your-First-Application) — step-by-step guide from descriptor to running application
- [Build a graphical application](Graphical-Engine) — containers, widgets, painters, listeners
- [ELF Loader](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
