# Contributing to Mk

Thank you for your interest in contributing to Mk. This page covers everything you need to know before submitting code: how to set up the build environment, what coding conventions the project uses, how files and functions must be named, and how to submit a pull request.

---

## Table of contents

1. [Prerequisites and build instructions](#1-prerequisites-and-build-instructions)
2. [Repository layout](#2-repository-layout)
3. [Coding conventions](#3-coding-conventions)
   * 3.1 [Language standard](#31-language-standard)
   * 3.2 [File header](#32-file-header)
   * 3.3 [Naming rules](#33-naming-rules)
   * 3.4 [Formatting](#34-formatting)
   * 3.5 [Function structure](#35-function-structure)
   * 3.6 [Comments](#36-comments)
4. [Adding a new source file](#4-adding-a-new-source-file)
   * 4.1 [Module structure](#41-module-structure)
   * 4.2 [Steps to add a function](#42-steps-to-add-a-function)
5. [Submitting a pull request](#5-submitting-a-pull-request)

---

## 1. Prerequisites and build instructions

Prerequisites, toolchain setup, build targets, and flashing instructions are maintained in the project README to avoid duplication. Refer to the [README](https://github.com/EmbSoft3/Mk#readme) before setting up your environment.

---

## 2. Repository layout

```
Mk/
├── Flasher/
│   └── Jlink/                  J-Link startup script
├── Includes/
│   ├── Application/            Graphical engine, application and shell headers
│   ├── Dispatcher/             Input event dispatcher headers
│   ├── FileSystem/             FAT file system headers
│   ├── Loader/                 ELF loader headers
│   ├── Mcu/                    MCU-specific headers (STM32F74xxx)
│   │   └── Stm32f74xxx/
│   │       ├── Binary/         Binary utility helpers
│   │       ├── Bsp/
│   │       │   ├── Drivers/
│   │       │   │   ├── Gpio/           GPIO pin driver
│   │       │   │   ├── I2c/            I2C peripheral driver
│   │       │   │   ├── Mmc/            SD/MMC controller driver
│   │       │   │   ├── Qspi/           QUADSPI external flash driver
│   │       │   │   │   └── Micron/     Micron NOR flash specific commands
│   │       │   │   └── Usb/
│   │       │   │       ├── Host/
│   │       │   │       │   ├── Hcd/    Host controller driver
│   │       │   │       │   ├── Hid/    HID class driver
│   │       │   │       │   │   └── Control/
│   │       │   │       │   │       ├── Axis/       Analog axis
│   │       │   │       │   │       ├── Button/     Button controls
│   │       │   │       │   │       ├── Consumer/   Consumer controls
│   │       │   │       │   │       ├── HatSwitch/  Hat switch
│   │       │   │       │   │       ├── Joystick/   Joystick
│   │       │   │       │   │       ├── Key/        Keyboard keys
│   │       │   │       │   │       ├── Keyboard/   Keyboard device
│   │       │   │       │   │       ├── Led/        LED outputs
│   │       │   │       │   │       ├── Mouse/      Mouse device
│   │       │   │       │   │       ├── Pointer/    Pointer controls
│   │       │   │       │   │       ├── Stick/      Analog stick
│   │       │   │       │   │       ├── Throttle/   Throttle axis
│   │       │   │       │   │       └── Wheel/      Wheel controls
│   │       │   │       │   └── Msc/    Mass Storage class driver
│   │       │   │       ├── Isr/        USB interrupt service routines
│   │       │   │       └── Port/       USB OTG port configuration
│   │       │   ├── Engine/
│   │       │   │   ├── Application/    Application lifecycle engine
│   │       │   │   ├── Chromart/       DMA2D (Chrom-ART) accelerator
│   │       │   │   ├── Color/          Color management
│   │       │   │   ├── Container/      Widget container management
│   │       │   │   ├── Display/        LTDC display controller
│   │       │   │   ├── Events/         Display engine events
│   │       │   │   ├── Factory/        Widget factory (container registration)
│   │       │   │   ├── Font/           Font rendering
│   │       │   │   ├── Graphics/       2D drawing primitives
│   │       │   │   ├── Image/          Image loading and rendering
│   │       │   │   ├── Maths/          Fixed-point math helpers
│   │       │   │   ├── Objects/        Built-in widget objects
│   │       │   │   ├── Parser/         Resource / script parser
│   │       │   │   ├── Request/        Display engine request queue
│   │       │   │   └── Utils/          Engine utility functions
│   │       │   ├── Memory/
│   │       │   │   └── Page/           SDRAM / SRAM page allocator
│   │       │   └── System/             System initialisation
│   │       ├── Dma/            DMA stream configuration helpers
│   │       ├── Kernel/         Scheduler, tasks, SVC, SysTick, PendSV
│   │       ├── Peripherals/    STM32F74xxx peripheral register definitions
│   │       └── Termio/         Terminal I/O 
│   ├── Shell/                  Shell headers
│   ├── Utils/                  Utility headers
│   ├── mk.h                    Top-level include (kernel types and macros)
│   ├── mk_api.h                Public API umbrella header
│   └── mk_id.h                 Task and module identifiers
├── Make/
│   ├── linker.ld               Linker script
│   └── makefile                Build system
├── Sources/                    C and ASM source files, mirroring Includes/
└── Storage/
    └── mk/                     Files placed on the target storage device at runtime
```

Each subsystem has a parallel structure: one header file per public function in `Includes/`, one source file per function in `Sources/`. The file name is the function name. For example, `mk_dispatcher_handleMouse` is declared in `Includes/Dispatcher/Handler/Mouse/mk_dispatcher_handleMouse.h` and defined in `Sources/Dispatcher/Handler/Mouse/mk_dispatcher_handleMouse.c`.

---

## 3. Coding conventions

All contributions must follow the conventions described below. The compiler is configured with an extensive set of `-W` flags; code that does not compile cleanly at warning level will not be accepted. The full list of compiler flags is available in [`CMakeLists.txt`](../CMakeLists.txt).

### 3.1 Language standard

The project compiles under **C18** (`-std=c18`) in a freestanding environment (`-ffreestanding -nostdinc -nodefaultlibs -nostdlib`). The standard library is not available. Use only the types and functions defined within the project itself.

External libraries are **not permitted** in the kernel or any of its subsystems, in order to preserve the self-contained philosophy of the project. External libraries may however be used freely in standalone applications built on top of Mk.

### 3.2 File header

Every `.c` and `.h` file must begin with the standard BSD-3-Clause header block, followed by Doxygen `@file`, `@brief`, and `@date` tags. Use the copyright year that matches the date of creation.

```c
/**
*
* @copyright Copyright (C) <year> <author>. All rights reserved.
*
* This file is part of Mk.
*
* Mk is free software. Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following conditions are
* met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*    2. Redistributions in binary form must reproduce the above copyright notice,
*       this list of conditions and the following disclaimer in the documentation
*       and/or other materials provided with the distribution.
*    3. Neither the name of the copyright holder nor the names of its contributors
*       may be used to endorse or promote products derived from this software
*       without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* @file mk_module_myFunction.c
* @brief Définition de la fonction mk_module_myFunction.
* @date <dd mmm. yyyy>
*
*/
```

### 3.3 Naming rules

The project enforces strict, systematic naming. Every identifier carries a prefix that encodes its kind and the subsystem it belongs to.

**Types**

| Kind | Prefix | Example |
|---|---|---|
| Struct / typedef | `T_mk` | `T_mkMouse`, `T_mkDispatcherHandler` |
| Enum | `T_mk` | `T_mkCtrlEvent` |
| Enum constant | `K_MK_` | `K_MK_EVENT_PRESS`, `K_MK_CONTROL_MOUSE` |
| Macro constant | `K_MK_` | `K_MK_FIELD_REFRESH_ENABLED` |

**Functions and variables**

| Scope | Prefix | Example |
|---|---|---|
| Global function | `mk_` | `mk_dispatcher_handleMouse` |
| Static (file-scope) function | `mk_` | `mk_dispatcher_handleMouseButton` |
| Global variable | `g_mk` | `g_mkDisplay`, `g_mkTermioHandler` |
| Local variable | `l_` | `l_result`, `l_mouse` |
| Function parameter | `p_` | `p_handler`, `p_message`, `p_mouse` |

Function names follow a `mk_<module>_<verb><Object>` pattern. The module segment mirrors the directory structure: `mk_dispatcher_handleMouse`, `mk_hid_mouse_getCoord`, `mk_volume_dispatch`.

### 3.4 Formatting

- **Indentation**: 3 spaces. No tabs.
- **Single exit point**: every function must have exactly one `return` statement, placed at the end of the function body. This is required to keep the control flow predictable during debugging.

```c
T_mkCode mk_module_doSomething ( T_mkFoo* p_foo, uint32_t p_value )
{
   /* Declaration of the return variable */
   T_mkCode l_result = K_MK_OK;

   /* Declaration of a working variable */
   uint32_t l_count = 0;

   /* If the parameter is valid */
   if ( p_foo != K_MK_NULL )
   {
      /* Main processing */
      l_count = p_value + 1;
      l_result = mk_module_helper ( p_foo, l_count );
   }
   /* Otherwise */
   else
   {
      /* Update of the return variable */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Return */
   return ( l_result );
}
```

### 3.5 Function structure

Every function follows the same skeleton:

1. **Return variable declaration** — the variable name is free, but it must be initialized with a value of type `T_mkCode` (not necessarily `K_MK_OK`; use whichever default is appropriate for the function). The function may return either a single `T_mkCode` value or a combination of `T_mkCode` values.
2. **Other local variable declarations** — all at the top of the function body, before any statements.

Unused parameters must be suppressed explicitly with a cast to `void` at the end of the function body, grouped under the comment `/* Suppress warning */`:

```c
   /* Suppress warning */
   ( void ) p_unusedParam;
```

### 3.6 Comments

**Public function documentation**: every public function declared in a `.h` file must be documented using the same Doxygen header block used for all functions in the project. The language of the documentation must be either **French or English exclusively** — do not mix both languages within the same file.

Implicit `else` branches are not allowed. If an else branch intentionally performs no operation, it must explicitly contain the comment /* Do nothing */.

```c
   else
   {
      /* Do nothing */
   }
```

---

## 4. Adding a new source file

### 4.1 Module structure

Every module is composed of a fixed set of header files and one source file per public function. No `#include` directive is permitted inside any `.h` file — all inclusions are done exclusively in `.c` files.

**Header files** (in `Includes/<module>/`):

| File | Role |
|---|---|
| `mk_<module>_types.h` | Type definitions (`T_mk*` structs and enums) used by the module. |
| `mk_<module>_constants.h` | Constants and enum values (`K_MK_*`) used by the module. |
| `mk_<module>.h` | Public function prototypes — the interface exposed to the rest of the OS. |
| `mk_<module>_data.h` | Declarations of global variables (`g_mk*`) owned by the module. |
| `mk_<module>_private.h` | Private function prototypes — internal helpers not accessible outside the module. |

**Source files** (in `Sources/<module>/`): one file per function, named after the function it defines: `mk_<module>_<myFunction>.c`.
Global variables (`g_mk*`) owned by the module are declared in a dedicated `mk_<module>_data.c` file.

### 4.2 Steps to add a function

1. **Create the function headers structure** in the appropriate `Includes/` subdirectory. Wrap the entire content in an include guard named after the file in upper snake case: e.g.`MK_<MODULE>_TYPES_H` for file mk_<module>_types.

2. **Declare the function** in `mk_<module>.h` (public) or `mk_<module>_private.h` (private) depending on whether the function is part of the module's external interface.

3. **Create the source file** in the mirrored `Sources/` subdirectory: `mk_<module>_<myFunction>.c`. 

---

## 5. Submitting a pull request

1. **Fork** the repository and create a branch from `main` with a descriptive name: `feature/usb-audio-class` or `fix/dispatcher-hatswitch-idle`.

2. **One concern per pull request.** Do not mix refactoring, new features, and bug fixes in a single PR. If you spot an unrelated issue while working, file a separate issue or PR.

3. **Build passes.** The CI check runs `cmake --build --preset ${{ matrix.preset }}`. A PR that introduces any compiler warning or error will not be merged.

4. **Conventions are respected.** Review §3 and §4 before submitting. Pay particular attention to the naming prefixes, the function skeleton, and the `/* Do nothing */` pattern — reviewers will flag deviations.

5. **Description.** In the PR body, briefly describe what the change does, why it is needed, and — for bug fixes — how to reproduce the issue before the fix.

