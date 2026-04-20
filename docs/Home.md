# Mk Wiki

**Mk** is a bare-metal operating system built from scratch for the STM32F746G-Eval2 board.
This wiki covers everything you need to understand, build, and extend it.

---

## Where do you want to start?

| I want to… | Go to |
|------------|-------|
| Understand how Mk is structured | [Architecture Overview](Architecture-Overview) |
| Write my first application | [Writing Your First Application](Writing-Your-First-Application) |
| Learn the kernel API (tasks, mutex, events…) | [Kernel API](Kernel-API) |
| Load and run external programs | [ELF Loader](ELF-Loader) |
| Work with files and storage | [File System](File-System) |
| Use USB devices | [USB Stack](USB-Stack) |
| Build a graphical application | [Graphical Engine](Graphical-Engine) |
| Handle keyboard, mouse and input events | [Event System](Event-System) |
| Use or extend the shell | [Shell & Commands](Shell-and-Commands) |
| Report a bug or contribute | [Contributing](Contributing) |

---

## Documentation

### Getting started
- [Architecture Overview](Architecture-Overview) — Layered structure, memory map, TEE model
- [Writing Your First Application](Writing-Your-First-Application) — Step-by-step guide with full code examples

### Kernel
- [Kernel API](Kernel-API) — Tasks, mutex, semaphores, events, mailboxes, memory pools, callbacks

### Subsystems
- [ELF Loader](ELF-Loader) — Dynamic loading, relocation, symbol resolution, the sym2srec tool
- [File System](File-System) — FAT16/32, multi-partition, concurrent access, full API reference
- [USB Stack](USB-Stack) — Host stack, supported device classes (HUB, HID, MSC), adding new classes
- [Graphical Engine](Graphical-Engine) — Containers, fields, layers, console, fonts, Unicode, BMP images
- [Event System](Event-System) — Listeners, containers, keyboard, mouse, joystick and HID events

### Tools & shell
- [Shell & Commands](Shell-and-Commands) — Built-in commands, writing external commands

### Contributing
- [Contributing](Contributing) — Build setup, coding conventions, bug reports, pull requests

---

## Prerequisites

| Item | Requirement |
|------|-------------|
| Hardware | STM32F746G-Eval2 evaluation board |
| Toolchain | [GNU Arm Embedded Toolchain 10.3-2021.10](https://developer.arm.com/downloads/-/gnu-rm) |
| Build tool | GNU Make 4.x |
| Flasher | J-Link (script provided in `Mk/Flasher/Jlink/`) |
| Storage | FAT-formatted SD card or USB drive |

---

## Project links

- 📦 [Source repository](https://github.com/EmbSoft3/Mk)
- 🐚 [Shell application example](https://github.com/EmbSoft3/Shell)
- 🔧 [sym2srec tool](https://github.com/EmbSoft3/Sym2srec)
