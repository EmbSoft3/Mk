# Mk

**Mk** is a bare-metal operating system built from scratch for the **STM32F746G-Eval2** board.
It targets the **STM32F74xxx** and **STM32F75xxx** MCU families and provides a complete software
ecosystem: a preemptive kernel, a dynamic ELF loader, a FAT file system, a multitasking USB stack,
a graphical engine with Unicode support, and an interactive shell — all written in C18 and ARM
assembly, with no external dependencies.

> ⚠️ This project is under active development. Some features and documentation sections are still
> being completed.

## Features

### Kernel
- Preemptive, priority-based multitasking scheduler (fixed-priority, O(1) selection via CLZ)
- Trusted Execution Environment (TEE) using the Cortex-M7 MPU:
  - **Handler mode** (privileged): full access to protected memory and system resources
  - **Thread mode** (unprivileged): restricted access — any violation triggers a fault and terminates the offending task
- Synchronization primitives: mutex (with priority inheritance), semaphore, event flags, mailbox
- Fixed-size memory pools — no variable-size dynamic allocation, eliminating heap fragmentation entirely
- Synchronous and asynchronous callback execution system
- Structured fault handling: HardFault, MemFault, BusFault, UsageFault, stack overflow detection

### Dynamic ELF Loader
Mk can load and execute external `.elf` files at runtime, relocated into 64 KB pages of external
SDRAM. Programs reference Mk's own API symbols directly via `extern` — the full kernel symbol table
is embedded in the firmware at a fixed address — so external applications require no copy of the
kernel API in their own binary. Shared libraries can be added to overcome the 64 KB page limit.

See the [sym2srec](https://github.com/EmbSoft3/Sym2srec/wiki) tool for details on the symbol
embedding mechanism.

### File System
- FAT32 with multi-partition support
- Concurrent access from multiple tasks (per-volume mutex)
- Full API: `open`, `close`, `read`, `write`, `seek`, `tell`, `eof`, `stat`, `rename`, `unlink`,
  `chmod`, `expand`, `truncate`, directory browsing
- Supports SD/MMC cards and USB Mass Storage Class (MSC) devices

### USB Stack
- Multitasking USB host stack built on the STM32F7 OTG peripheral
- Supported device classes: HUB, HID (keyboard, mouse, joystick, gamepad), MSC
- Designed for extensibility — new device classes can be added without modifying the core stack

### Graphical Engine
- Hardware-accelerated 2D rendering via the Cortex-M7 ChromART (DMA2D) unit
- Drawing primitives: rectangles, circles, lines, arcs
- Image rendering: BMP 24-bit and 32-bit
- Full Unicode text rendering: ASCII, UTF-8, UTF-16, UTF-32
- Font manager: native fonts stored in FLASH/QSPI; additional fonts can be loaded at runtime into RAM
- UI object library: buttons, text fields, edit fields, progress bars, 2D graphs, cursors, layers
- Event-driven application model: painting callbacks and input-listening callbacks

### Shell
Built-in interactive shell with support for both native and dynamically loaded commands:

| Command | Description |
|---------|-------------|
| `ls` | List directory contents |
| `cd` | Change current directory |
| `pwd` | Print working directory |
| `lsdsk` | List mounted disks and partitions |
| `launch` | Load and run an external `.elf` application |
| `install` / `uninstall` | Install or remove an application |
| `terminate` | Stop a running application |
| `getapps` | List installed applications |

---

## Architecture

Mk is organized into well-separated layers:

```
┌──────────────────────────────────────────────────────┐
│                  Applications                        │  Home UI, Supervisor, Shell
├──────────────────────────────────────────────────────┤
│              Dispatcher / Event system               │  HID, GPIO, Disk events
├──────────────────────────────────────────────────────┤
│         File System │ ELF Loader │ USB Stack         │
├──────────────────────────────────────────────────────┤
│                  Kernel (RTOS)                       │  Scheduler, sync, pools
├──────────────────────────────────────────────────────┤
│          BSP / Graphical Engine / Drivers            │  STM32F7-specific HAL
├──────────────────────────────────────────────────────┤
│               Peripheral Abstraction                 │  GPIO, DMA, USB OTG, LTDC…
└──────────────────────────────────────────────────────┘
          STM32F746G — Cortex-M7 @ 216 MHz
```

---

## Build

### Requirements

- [GNU Arm Embedded Toolchain 10.3-2021.10](https://developer.arm.com/downloads/-/gnu-rm)
- GNU Make 4.x

### Steps

1. Open `Mk/Make/makefile` and set `TOOLCHAIN_PATH` to your ARM toolchain installation directory.
2. Clean any previous build artifacts:
   ```
   make clean
   ```
3. Build the firmware:
   ```
   make all
   ```
   This produces `Mk.elf` (debug symbols) and `Mk-Strip.elf` (stripped, ready to flash), along with
   `Mk.srec` containing the embedded symbol table.

> **Note:** The default build configuration uses `-Ofast`. Use the `Debug` target for a `-O0`
> build with full debug symbols:
> ```
> make Debug
> ```

### Compiler versions used

| Tool | Version |
|------|---------|
| `arm-none-eabi-gcc` | 10.3.1 20210824 (GNU Arm Embedded Toolchain 10.3-2021.10) |
| `arm-none-eabi-g++` | 10.3.1 20210824 (GNU Arm Embedded Toolchain 10.3-2021.10) |
| `make` | GNU Make 4.4.1 (Windows32) |

### Flashing

A J-Link script is provided in `Mk/Flasher/Jlink/`. Connect the STM32F746G-Eval2 board and run it
with J-Link Commander.

---

## Screenshots

| Boot | Shell |
|------|-------|
| ![startup](Screenshots/screenshot_startup.bmp) | ![shell](Screenshots/screenshot_shell.bmp) |

| Home screen | File manager |
|-------------|--------------|
| ![home](Screenshots/screenshot_home.bmp) | ![manager](Screenshots/screenshot_manager.bmp) |

| File manager (2) | Pong |
|------------------|------|
| ![manager2](Screenshots/screenshot_manager_2.bmp) | ![pong](Screenshots/screenshot_pong.bmp) |

---

## Future developments

Given the scope of the project, it was published without all the desired 
features. Below is a list of features that will be added in the future :

 - Add file system access rights
 - Add sound to the graphics engine (USB isochronous transfers)
 - Add touch events to the graphics engine
 - Add a TCP/IP stack

This list is not exhaustive, and includes only the main features.

---

## Roadmap

The following features are planned for future releases:

- [ ] File system access rights
- [ ] Touch input support in the graphical engine
- [ ] Audio output via USB isochronous transfers
- [ ] TCP/IP networking stack

---

## License

Copyright © 2024 **Mathieu Renard**. All rights reserved.

This project is licensed under the **BSD 3-Clause License** — see the [LICENSE](LICENSE) file for
details.



