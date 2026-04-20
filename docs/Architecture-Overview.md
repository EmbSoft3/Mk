# Architecture Overview

Mk is a bare-metal operating system built from scratch for the STM32F746 (Cortex-M7 @ 216 MHz).
It is written in C18 and ARM Thumb-2 assembly with no external dependencies. This page describes
the overall structure of the system: its layered architecture, memory layout, privilege model, boot
sequence, and the internal tasks that keep it running.

---

## Table of contents

1. [Architecture](#1-architecture)
   - 1.1 [Foundation](#11-foundation)
   - 1.2 [Subsystems](#12-subsystems)
   - 1.3 [System Platform](#13-system-platform)
2. [Memory map](#2-memory-map)
   - 2.1 [Key linker symbols](#21-key-linker-symbols)
   - 2.2 [Section placement macros](#22-section-placement-macros)
3. [Privilege model — TEE via MPU](#3-privilege-model--tee-via-mpu)
   - 3.1 [Privilege transition](#31-privilege-transition)
   - 3.2 [MPU region configuration](#32-mpu-region-configuration)
4. [Boot sequence](#4-boot-sequence)
5. [System tasks](#5-system-tasks)
6. [Module overview](#6-module-overview)

---

## 1. Architecture

Mk is organized into three layers: Foundation for core hardware and OS services, Subsystems for system services, and System Platform for applications and graphics.:

```
╔═════════════════════════════════════════════════════════════════════╗
║  SYSTEM PLATFORM  (Native Application)                              ║
║                                                                     ║
║   ┌─────────────┐             ┌──────────┐              ┌────────┐  ║
║   │  Supervisor │             │   Home   │              │ Shell  │  ║
║   │   (faults)  │             │ (screen) │              │        │  ║
║   └─────────────┘             └──────────┘              └────────┘  ║
╠═════════════════════════════════════════════════════════════════════╣
║  SUBSYSTEMS                                                         ║
║                                                                     ║
║  ┌────────────┐   ┌──────────────┐   ┌───────────┐   ┌───────────┐  ║
║  │ Dispatcher │   │  ELF Loader  │   │ FAT File  │   │   USB     │  ║
║  │            │   │  + S-Record  │   │  System   │   │   Stack   │  ║
║  │            │   │              │   │           │   │           │  ║
║  │            │   │              │   │           │   │           │  ║
║  └────────────┘   └──────────────┘   └───────────┘   └───────────┘  ║
║                                                                     ║
║  ┌───────────────────────────────────────────────────────────────┐  ║
║  │  Graphical Engine (BSP Engine)                                │  ║
║  │  ChromART · LCD · Containers · Objects · Fonts · Color · Vect │  ║
║  └───────────────────────────────────────────────────────────────┘  ║
╠═════════════════════════════════════════════════════════════════════╣
║  FOUNDATION  (no dependency on anything above)                      ║
║                                                                     ║
║  ┌──────────────────────┐   ┌──────────────┐   ┌────────────────┐   ║
║  │       Kernel         │   │ BSP Drivers  │   │  Binary · Math │   ║
║  │  Scheduler · Mutex   │   │  GPIO · I2C  │   │  Vect 2D · ASM │   ║
║  │  Event · Mail · Pool │   │  USB · MMC   │   │                │   ║
║  │  SVC · TEE · MPU     │   │  QSPI        │   │                │   ║
║  └──────────────────────┘   └──────────────┘   └────────────────┘   ║
║                                                                     ║
║  ┌──────────────────────────────────────────────────────────────┐   ║
║  │  STM32F74xxx Peripherals — NVIC · FPU · DMA · RTC · SDRAM    │   ║
║  └──────────────────────────────────────────────────────────────┘   ║
╚═════════════════════════════════════════════════════════════════════╝
                  STM32F746G — Cortex-M7 @ 216 MHz
```

### 1.1 Foundation

The kernel, BSP drivers, and hand-written ASM routines (binary, math, 2D vectors) have no
dependency on any other Mk module. They form the stable base on which everything else is built.

### 1.2 Subsystems

The subsystems (Dispatcher, ELF Loader, FAT File System, USB Stack, Graphical Engine) are
**not independent from each other**, but their coupling is controlled. They share data structure
definitions through `_types.h` and `_constants.h` headers — they know each other's types so they
can pass data around — but they do not call each other's API functions. For example:

- `FileSystem` includes `mk_dispatcher_types.h` and `mk_display_events_types.h` — it knows what
  a dispatcher event looks like, but it never calls a dispatcher function.
- `Dispatcher` includes `mk_loader_types.h` — it can reference a loader structure, but the loader
  does not call back into the dispatcher.
- `ELF Loader` includes display container and field types — it populates graphical structures, but
  does not drive the rendering pipeline itself.

This pattern keeps the subsystems decoupled at the **call level** while allowing data to flow
between them without copying or opaque interfaces.

### 1.3 System Platform

Supervisor, Home and Shell form a tightly coupled application platform. `Supervisor` includes
`mk_home.h` (full API), `Home` includes `mk_supervisor.h` (full API), and `Shell` includes
Supervisor types. These three components are designed as a single integrated system application
and their mutual dependencies are deliberate.

---

## 2. Memory map

The STM32F746 exposes several distinct memory buses. Mk maps its sections to exploit each bus's
specific characteristics (latency, bandwidth, DMA accessibility).

| Region | Base address | Size | Contents |
|--------|-------------|------|---------|
| `K_FLASH_ITCM` | `0x00200000` | 896 KB | Firmware: `.text`, `.rodata`, ISR vector table, fonts |
| `K_FLASH_ITCM_SYMBOLS` | `0x002C0000` | 128 KB | Kernel API symbol table (written by sym2srec) |
| `K_FLASH_AXIM` | `0x08000000` | 1 MB | Mirror of FLASH via AXI bus (not used directly) |
| `K_ITCM_RAM` | `0x00000000` | 16 KB | Instruction TCM — zero-latency execution |
| `K_DTCM_RAM` | `0x20000000` | 64 KB | Data TCM — zero-latency read/write |
| `K_SRAM1` — unprivileged | `0x20010000` | ~68 KB | Unprivileged data, unprivileged DMA, process stacks |
| `K_SRAM1` — privileged | `0x20021000` | ~172 KB | Privileged DMA buffers (USB, I2C, MMC…) |
| `K_SRAM2` | `0x2004C000` | 16 KB | Privileged memory — kernel structures only |
| `K_QSPI_FLASH` | `0x90000000` | 16 MB | Font bitmaps, graphical resources |
| `K_MK_BANK5` (SDRAM) | `0xC0000000` | 8 MB | Frame buffers (graphical engine) + application memory pages |

### 2.1 Key linker symbols

The linker script (`Mk/Make/linker.ld`) exports symbols that the kernel reads at runtime to
configure the MPU regions and to initialize memory:

| Symbol | Value | Purpose |
|--------|-------|---------|
| `K_MK_UNPRIVILEGED_DATA_BASE_ADDR` | `0x20010000` | Start of unprivileged SRAM1 segment |
| `K_MK_UNPRIVILEGED_DMA_DATA_BASE_ADDR` | `0x20018000` | Start of unprivileged DMA area (SRAM1) |
| `K_STACK_BASE_ADDR` | `0x2001FC00` | Process stack (PSP) base |
| `K_MK_PRIVILEGED_DMA_DATA_BASE_ADDR` | `0x20021000` | Start of privileged DMA area (SRAM1) |
| `K_MK_PRIVILEGED_DATA_BASE_ADDR` | `0x2004C000` | Start of privileged SRAM2 |
| `K_MK_INTERNAL_SYMBOLS_BASE_ADDR` | `0x002C0000` | Symbol table base |
| `K_MK_BANK5_START_ADDR` | `0xC0000000` | Start of SDRAM (FMC Bank 5) |

### 2.2 Section placement macros

Variables are placed in their target section using GCC attributes defined in
`mk_memory_constants.h`. The kernel and BSP use these macros to enforce the privilege boundary at
compile time:

```c
// Privileged — accessible by kernel tasks only (SRAM2)
K_MK_PRIVILEGED_MEMORY          T_mkScheduler g_mkScheduler;

// Unprivileged — accessible by all tasks (SRAM1)
K_MK_UNPRIVILEGED_MEMORY        T_mkDisplayManager g_mkDisplay;

// DMA-safe — cache-coherent areas for peripheral transfers
K_MK_PRIVILEGED_DMA_MEMORY      uint8_t g_mkUsbBuf[...];
K_MK_UNPRIVILEGED_DMA_MEMORY    uint8_t g_mkFatBuf[...];

// Font bitmaps — mapped to QSPI FLASH (read-only, XIP)
K_MK_PRIVILEGED_FONT_MEMORY     const uint8_t g_mkFont24px[];
```

---

## 3. Privilege model — TEE via MPU

Mk implements a **Trusted Execution Environment** without an MMU by exploiting the Cortex-M7 MPU
(8 configurable regions). The CPU operates in two distinct execution modes:

```
  ┌──────────────────────────────────┐
  │   Handler mode                   │  ← Kernel, ISR handlers, SVC
  │   MSP — Main Stack Pointer       │
  │   Always privileged              │
  │   Access: SRAM1 + SRAM2 + FLASH  │
  ├──────────────────────────────────┤
  │   Thread mode — privileged       │  ← Privileged tasks (native apps, system tasks)
  │   PSP — Process Stack Pointer    │
  │   Access: SRAM1 + SRAM2 + FLASH  │
  ├──────────────────────────────────┤
  │   Thread mode — unprivileged     │  ← Unprivileged tasks (external apps)
  │   PSP — Process Stack Pointer    │
  │   Access: SRAM1 only             │
  └──────────────────────────────────┘
```

All tasks — privileged or not — run in Thread mode using the **Process Stack Pointer (PSP)**.
This is enforced by the EXC_RETURN value (`0xFFFFFFFD` / `0xFFFFFFED` for floating tasks)
written into each task's initial stack frame at creation. Only Handler mode uses MSP.

### 3.1 Privilege transition

A task calls a kernel API function (e.g., `mk_mutex_take()`). The function calls
`_mk_svc_call` which:

1. Reads the IPSR register to determine whether execution is in Thread or Handler mode.
2. In Thread mode: issues `SVC #0x00` to trigger the SVC exception.
3. In Handler mode: sets the `SVCALLPENDED` bit in `SHCRS` to queue the call safely.

The SVC handler then validates the caller's privilege level before executing the kernel primitive.

```c
// Any task — privileged or unprivileged, Thread mode, using PSP
T_mkCode l_result = mk_mutex_take(l_mutex, K_MK_TASK_WAIT_FOREVER);
//                  └── internally calls _mk_svc_call → SVC #0 → kernel validates → executes
```

### 3.2 MPU region configuration

The Cortex-M7 MPU provides 8 configurable regions, numbered 0–7. All 8 are used by Mk.
Regions are evaluated in descending order of index: a higher-numbered region takes precedence
over a lower-numbered one when their address ranges overlap. Region 0 acts as a global default
that covers the entire 4 GB address space; every other region overrides it for its specific range.

| # | Name | Base address | Size | Memory type | Fetch | Privilege | Unprivilege | Purpose |
|---|------|-------------|------|-------------|----|-----------|-------------|---------|
| 0 | Global default | `0x00000000` | 4 GB | Device, not-shareable | False | RW | RO | Catch-all — ordered, buffered, no execution |
| 1 | FLASH ITCM | `0x00200000` | 1 MB | Normal, non-cacheable | True | RW | RO | Kernel code, tables and symbol table |
| 2 | DTCM RAM | `0x20000000` | 64 KB | Normal, non-cacheable | False | RW | RO | Data TCM — zero-latency kernel data |
| 3 | SRAM1 — unprivileged | `0x20010000` | 64 KB | Normal, WB/WA | False | RW | RW | Application memory (L1 D-Cache enabled) |
| 4 | SRAM1 — DMA/stack | `0x20018000` | 32 KB | Normal, non-cacheable | False | RW | RW | DMA buffers, BSS, .data, process stack |
| 5 | Main stack (MSP) | `0x2001FC00` | 4 KB | Normal, WB/WA | False | RW | — | Handler mode stack — kernel/ISR only |
| 6 | FMC Bank 1 | `0x60000000` | 256 MB | Normal, WB/WA | True | RW | RW | External NOR/PSRAM |
| 7 | FMC Bank 5 — SDRAM | `0xC0000000` | 256 MB | Device, not-shareable | True | RW | RW | SDRAM — frame buffers, ELF application pages |

> **Note — QSPI FLASH and SRAM2.** Neither has a dedicated MPU region. Both fall under the
> global default (region 0): Device type, privileged RW / unprivileged RO, FETCH=False.
> QSPI resources (fonts, bitmaps) are therefore readable by all tasks but not executable.
> SRAM2 privileged data is readable in unprivileged mode but unwritable, which is acceptable
> since write attempts from an application will trigger a MemFault.

> **Note — FLASH ITCM region.** The single 1 MB MPU region covers both the firmware code
> (`0x00200000–0x002BFFFF`, 896 KB) and the kernel API symbol table
> (`0x002C0000–0x002DFFFF`, 128 KB). The two are configured identically so splitting them
> into two regions would bring no benefit.

> **Note — SDRAM as Device type.** Configuring SDRAM as Device rather than Normal disables
> D-Cache for that region. This avoids any cache coherency issue with the LCD DMA (ChromART)
> that writes directly into the frame buffers located in SDRAM, at the cost of raw CPU access
> performance.

Any access violation (wrong privilege level, write to a read-only region, instruction fetch from
an XN region) triggers a **MemFault**. The Supervisor handles it by terminating the faulting
application — the kernel and all other applications remain unaffected.

---

## 4. Boot sequence

The Reset Handler (`_vector_resetHandler` in `mk_peripheral_vector_ResetHandler.asm`) runs
immediately after power-on before any C code. It performs the following steps in assembly:

```
Reset
  │
  ├── 1. Zero-fill unprivileged BSS (.bss)
  ├── 2. Zero-fill privileged BSS (.mk_privileged_bss_memory)
  ├── 3. Copy unprivileged .data from FLASH → SRAM1
  ├── 4. Copy privileged .data from FLASH → SRAM1
  ├── 5. Fill Main Stack with sentinel pattern (0x55555555)
  ├── 6. Fill Process Stack with sentinel pattern
  │
  └── Call mk_system_init()
        │
        ├── Clock init (HSE → PLL → 216 MHz SYSCLK)
        ├── NVIC priority groups configuration
        ├── MPU configuration (8 regions)
        ├── FPU enable (CP10/CP11 full access)
        ├── I-Cache / D-Cache enable
        ├── Peripheral init (GPIO, I2C, USB, MMC, QSPI, SDRAM)
        │
        └── Kernel start
              ├── Create privileged system tasks (Supervisor, Dispatcher, Display, USB, FAT…)
              ├── Start SysTick → triggers PendSV on each tick
              └── Scheduler takes over → first task executes
```

---

## 5. System tasks

Mk creates a fixed set of internal tasks at startup. External applications are loaded on demand
by the Supervisor and run as additional tasks — privileged or unprivileged depending on the
privilege level of the task declared in their application descriptor.

**Native applications** (Supervisor, Home, Shell) are built alongside the kernel and embedded
directly in the firmware image. They are started automatically at boot and are always present.

| Task | Type | Privilege | Priority | Role |
|------|------|-----------|----------|------|
| **Supervisor** | Native | Privileged, Floating | Highest (9) | Fault handling, application lifecycle |
| **Display** | System | - | - | Graphics pipeline|
| -- Handler | System | Privileged, Floating | 8 | Graphical request management |
| -- Privileged Listener | System | Privileged, Floating | 7 | Dispatches input events to privileged containers |
| -- Unprivileged Listener | System | Unprivileged, Floating | 6 | Dispatches input events to unprivileged containers |
| -- Privileged Painter | System | Privileged, Floating | 5 | Renders privileged graphical containers |
| -- Unprivileged Painter | System | Unprivileged, Floating | 4 | Renders unprivileged graphical containers |
| **Callback** | System | - | 6 | Asynchronous callback execution |
| -- Privileged | System | Privileged, Floating | 6 | Executes callback functions posted by privileged tasks |
| -- Unprivileged | System | Unprivileged, Floating | 6 | Executes callback functions posted by unprivileged tasks |
| **Dispatcher** | System | Privileged | 3 | HID event collection and routing to the graphical engine |
| **File System** | System | Privileged | 2 | File system request management |
| -- Default FileSytem Task [4] | System | Privileged | 2 | FAT16/32 read/write, non-concurrent access arbitration |
| -- Shared FileSystem Task | System | Privileged | 2 | FAT16/32 read/write, concurrent access arbitration |
| **USB** | System | Privileged | 2 | USB host controller |
| -- OTGHS (host) | System | Privileged | 2 | USB enumeration, HUB |
| -- OTGFS (host) | System | Privileged | 2 | Not implemented |
| -- HID | System | Privileged | 2 | HID class drivers |
| -- MSC | System | Privileged | 2 | MSC class drivers |
| **Termio** | System | Privileged | 2 | Terminal I/O (peripheral I/O tasks) |
| -- I2C | System | Privileged | 2 | I2C bus controller (event + error) |
| -- GPIO | System | Privileged | 2 | GPIO controller |
| -- MMC | System | Privileged | 2 | Driver SD/MMC |
| **Shell** | Native | Privileged | 2 | CLI — built-in and external commands |
| **Application** | System | Privileged, Floating | 1 | Home screen UI, shell |
| -- Home | Native | Privileged, Floating | 1 | Home screen UI, application list |
| **Idle** | System | Privileged | Lowest (0) | Idle Task |

**External applications**:

| Task | Type | Privilege | Priority | Role |
|------|------|-----------|----------|------|
| External app | Application | Privileged or Unprivileged | 1 (default) | Dynamically loaded ELF applications |

The Display subsystem is deliberately split into two painter/listener pairs — one privileged, one
unprivileged — so that native UI elements (e.g., the status bar drawn by the Supervisor) are
always rendered regardless of what external applications do.

---

## 6. Module overview

| Module | Source path | Description |
|--------|-------------|-------------|
| BSP / Graphical Engine | `Bsp/Engine/` | ChromART, LCD, containers, fonts, objects, color, 2D vectors |
| BSP / Drivers | `Bsp/Drivers/` | GPIO, I2C, USB, MMC, QSPI drivers |
| Peripherals | `Peripherals/` | NVIC, MPU, FPU, DMA, RTC, Math, Binary |
| File System | `FileSystem/` | FAT16/32, multi-partition, full R/W API |
| Kernel | `Kernel/` | Scheduler, mutex, semaphore, event, mailbox, pool, SVC, callbacks |
| Application | `Application/` | Home UI, Supervisor (fault handling + recovery) |
| Utils | `Utils/` | String, Unicode, INI parser, general algorithms |
| Dispatcher | `Dispatcher/` | 14 HID control handlers + event routing |
| Shell | `Shell/` | CLI — built-in and external commands |
| Loader | `Loader/` | ELF32 dynamic loader + S-Record parser |

---

## See also

- [Writing your first application](Writing-Your-First-Application) — step-by-step guide from descriptor to running application
- [Kernel internals](Kernel-API) — tasks, memory pools, synchronisation objects
- [Work with files and storage](File-System) — disk, volume and file API
- [Build a graphical application](Graphical-Engine) — containers, widgets, painters, listeners
- [Handle input events](Event-System) — listeners, keyboard, mouse, joystick and HID events
- [Load and run external programs](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
- [Use or extend the Shell](Shell-and-Commands) — external shell commands, console I/O API
