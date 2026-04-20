# Load and run external programs

This page covers the full lifecycle of a dynamic application in Mk: how the loader
deploys a `.elf` binary into RAM, how to manage applications from the Supervisor
shell, and how to drive the same operations programmatically from another application.

---

## Table of contents

1. [Application lifecycle](#1-application-lifecycle)
2. [What the loader does](#2-what-the-loader-does)
3. [Shell commands](#3-shell-commands)
   - 3.1 [get-apps — list installed applications](#31-get-apps--list-installed-applications)
   - 3.2 [install — load a binary from storage](#32-install--load-a-binary-from-storage)
   - 3.3 [launch — start an installed application](#33-launch--start-an-installed-application)
   - 3.4 [terminate — stop a running application](#34-terminate--stop-a-running-application)
   - 3.5 [uninstall — remove an application from the system](#35-uninstall--remove-an-application-from-the-system)
4. [Programmatic API](#4-programmatic-api)
   - 4.1 [Querying the application list](#41-querying-the-application-list)
   - 4.2 [Reading application parameters](#42-reading-application-parameters)
   - 4.3 [Installing applications](#43-installing-applications)
   - 4.4 [Launching, closing and uninstalling](#44-launching-closing-and-uninstalling)
   - 4.5 [Updating metadata and input attributes](#45-updating-metadata-and-input-attributes)
   - 4.6 [Return codes](#46-return-codes)

---

## 1. Application lifecycle

A dynamic application progresses through three states:

```
  ┌─────────────────────────────────────────────────────────┐
  │                                                         │
  │   [file on storage]                                     │
  │         │                                               │
  │  install / mk_application_installDynamic()              │
  │         │                                               │
  │         ▼                                               │
  │   INSTALLED  ◀────────────────────────────────┐         │
  │         │                         close /     │         │
  │  launch / mk_application_launch() terminate   │         │
  │         │                         (stops      │         │
  │         ▼                          running)   │         │
  │   RUNNING  ────────────────────────────────── ┘         │
  │         │                                               │
  │  uninstall / mk_application_uninstall()                 │
  │         │                                               │
  │         ▼                                               │
  │   [removed from system]                                 │
  └─────────────────────────────────────────────────────────┘
```

| State | Meaning |
| --- | --- |
| `K_MK_APPLICATION_STATE_INSTALLED` | Binary loaded into SDRAM, registered in the application list, not yet running |
| `K_MK_APPLICATION_STATE_RUNNING` | Entry-point task created and executing |
| `K_MK_APPLICATION_STATE_UNINSTALLED` | Being removed — transient state during `mk_application_uninstall()` |

An application can be stopped (moved back from RUNNING to INSTALLED) with `close` or
`terminate` without being uninstalled. It can then be re-launched.

---

## 2. What the loader does

When a dynamic application is installed via `mk_application_installDynamic()`, the
loader performs the following steps automatically:

1. **Opens the `.elf` file** from the specified path on the FAT storage volume.
2. **Allocates a dedicated 64 KB SDRAM page** (`deploymentAddr`) from the system
   memory pool.
3. **Loads all ELF sections** (`.text`, `.data`, `.bss`, `.descriptor`…) into the
   page, performing address relocation so that all internal references point to the
   correct load addresses.
4. **Resolves external symbols** against the Mk kernel API table — every call to a
   public kernel function (e.g. `mk_task_sleep`, `mk_event_set`) is patched to point
   to the running kernel's implementation.
5. **Loads any required shared libraries** recursively from the same directory as the
   `.elf` file, each into its own SDRAM page.
6. **Reads the `T_mkApplicationDynamicHeader`** from the base of the page (`.descriptor`
   section), validates the magic number, and copies the descriptor, metadata and
   command-line arguments into the `T_mkApplication` structure.
7. **Assigns a numeric PID** to the application derived from its pool slot index.
8. **Registers the application** in the system-wide application list (event
   `K_MK_EVENT_INSTALL` is dispatched to the Home screen).

The loader validates the following fields before accepting the binary. If any check
fails, the SDRAM page is freed and `K_MK_ERROR_UNEXPECTED` is returned:

| Check | Requirement |
| --- | --- |
| `header.magicNumber` | Must equal `K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER` |
| `header.version` | Must be non-zero |
| `descriptor.type` | Must have bit `K_MK_APPLICATION_TYPE_DYNAMIC` set |
| `descriptor.stackAddr` | Must be non-null |
| `descriptor.stackSize` | Must be non-zero |
| `descriptor.entryPoint` | Must be non-null |

---

## 3. Shell commands

Open the Supervisor shell with **Alt + S** from anywhere in the UI.

### 3.1 `get-apps` — list installed applications

```
get-apps [<PID>]
```

Lists all installed applications. Provide a PID to display a single entry.

Each line shows:

```
[PID-007]   [DYN]   pongGameRelease.elf      [..]
[PID-002]   [STA]   Home                     [..]
```

| Column | Content |
| --- | --- |
| `[PID-NNN]` | Numeric application identifier |
| `[DYN]` / `[STA]` | Dynamic (loaded from storage) or static (compiled into firmware) |
| Name | `.elf` filename for dynamic apps, `metadata.name` for static apps |

### 3.2 `install` — load a binary from storage

```
install <elf-file> [-s "<arguments>"] [-l]
```

Reads the `.elf` file from storage, deploys it into a dedicated SDRAM page, and
registers it. The path can be absolute or relative to the current shell directory.

| Option | Description |
| --- | --- |
| *(none)* | Install only — application appears in Home but does not start |
| `-s "<args>"` | Set the command-line argument string passed to the application's entry point (enclose in double quotes if it contains spaces) |
| `-l` | Install **and** immediately launch the application |

**Examples:**

```
install pongGameRelease.elf
install /sdcard/apps/pongGameRelease.elf
install blinkLedRelease.elf -s "500"
install blinkLedRelease.elf -s "500" -l
```

### 3.3 `launch` — start an installed application

```
launch <PID>
```

Creates the entry-point task of an already-installed application and transitions it to
the RUNNING state. Use `get-apps` to find the PID.

```
launch 7
```

### 3.4 `terminate` — stop a running application

```
terminate <PID>
```

Closes the application: its entry-point task is destroyed, all containers are
automatically removed from the factory, and all memory pages (deployment, gfx, mem)
are freed. The application returns to the INSTALLED state and can be relaunched.

```
terminate 7
```

### 3.5 `uninstall` — remove an application from the system

```
uninstall <PID>
```

If the application is currently running it is first closed, then unregistered from
the application list and its SDRAM deployment page is freed. Static applications
(compiled into firmware) cannot be uninstalled.

```
uninstall 7
```

---

## 4. Programmatic API

The same operations are available as C functions, callable from any privileged task.
All functions that interact with the Display engine accept a `T_mkCallback*` parameter:
pass `K_MK_NULL` for a synchronous blocking call, or a valid callback pointer for a
non-blocking asynchronous call.

When asynchronous, the completion callback signature is:

```c
void my_callback(T_mkCode p_result, T_mkApplication* p_application);
```

`p_application` is `K_MK_NULL` on uninstall (the application object has been freed).
For `mk_application_close()`, `mk_application_launch()`, `mk_application_setMetadata()`
and `mk_application_setAttributes()`, the callback signature omits `p_application`:

```c
void my_callback(T_mkCode p_result);
```

### 4.1 Querying the application list

```c
/* Head of the global application list */
T_mkApplication* l_first = mk_application_getFirst();

/* Currently visible foreground application */
T_mkApplication* l_current = mk_application_getCurrent();

/* First application started at boot */
T_mkApplication* l_main = mk_application_getMain();

/* Find by PID */
T_mkApplication* l_app = mk_application_getById(7);

/* Counters */
uint32_t l_installed = mk_application_getNumberOfInstalledApps();
uint32_t l_running   = mk_application_getNumberOfRunningApps();
```

To iterate over all installed applications:

```c
T_mkApplication* l_app = mk_application_getFirst();
while (l_app != K_MK_NULL)
{
    /* inspect l_app->layer.id, l_app->metadata.name, l_app->state … */
    l_app = l_app->next;
}
```

| Function | Description |
| --- | --- |
| `mk_application_getFirst()` | Returns the head of the doubly-linked application list, or `K_MK_NULL` if no application is installed. |
| `mk_application_getCurrent()` | Returns the foreground application currently displayed. |
| `mk_application_getMain()` | Returns the first application launched at system startup. |
| `mk_application_getById(id)` | Returns the application whose PID equals `id`, or `K_MK_NULL` if not found. |
| `mk_application_getNumberOfInstalledApps()` | Returns the total number of installed applications (INSTALLED + RUNNING). |
| `mk_application_getNumberOfRunningApps()` | Returns the number of applications currently in the RUNNING state. |

### 4.2 Reading application parameters

```c
/* Retrieve the entry-point argument of an application */
T_mkAddr l_arg = mk_application_getArg(l_app);

/* Retrieve the command-line string of a dynamic application */
T_str8 l_cmdLine;
T_mkCode l_result = mk_application_getCmdLine(l_app, &l_cmdLine);

/* Parse the command-line string token by token */
T_str8 l_token, l_next = l_cmdLine;
while (mk_application_getArgv(l_next, &l_next, l_token, sizeof(l_token),
                               K_MK_FONT_UTF8) == K_MK_OK)
{
    /* process l_token */
}
```

| Function | Description |
| --- | --- |
| `mk_application_getArg(app)` | Returns `descriptor.arg`. For dynamic applications this is the address of the `T_mkApplication` structure itself; for static applications it is the value set by the developer in `T_mkApplicationDescriptor.arg`. |
| `mk_application_getCmdLine(app, chain)` | Writes into `*chain` the address of the command-line argument string passed to `mk_application_installDynamic()`. Returns `K_MK_NULL` in `*chain` for a static application. |
| `mk_application_getArgv(chain, nextChain, arg, argLength, encoding)` | Extracts one whitespace-delimited token from the command-line string. On each call `*nextChain` advances past the current token. Returns `K_MK_ERROR_NOT_AVAILABLE` when the string is exhausted. `argLength` is the size of the caller's buffer in bytes; `encoding` is typically `K_MK_FONT_UTF8`. |

### 4.3 Installing applications

```c
/* Dynamic application — loaded from a .elf file on storage */
T_mkApplication* l_app;
T_mkCode l_result = mk_application_installDynamic(
    &l_app,                   /* out: application handle */
    "/mk/apps/pong/pong.elf", /* path to the .elf; max K_MK_FILE_MAX_NAME_LENGTH bytes */
    "arg1 arg2",              /* command-line string, or K_MK_NULL */
    K_MK_NULL,                /* volume — K_MK_NULL to use the path prefix */
    K_MK_NULL                 /* callback — K_MK_NULL for blocking call */
);

/* Static application — entry point compiled into the firmware */
T_mkCode l_result = mk_application_install(
    &l_app,
    &g_myDescriptor,         /* T_mkApplicationDescriptor */
    &g_myMetadata,           /* T_mkApplicationMetadata   */
    K_MK_NULL
);
```

**`T_mkApplicationDescriptor` fields:**

| Field | Description |
| --- | --- |
| `type` | Application type flags (`K_MK_APPLICATION_TYPE_STATIC` or `K_MK_APPLICATION_TYPE_DYNAMIC`) |
| `taskType` | Entry-point task type (`K_MK_TYPE_DEFAULT` or `K_MK_TYPE_FLOATING`) |
| `gfxPage` | `K_MK_TRUE` to allocate a graphics memory page |
| `memPage` | `K_MK_TRUE` to allocate a standard memory page |
| `stackAddr` | Pointer to the task stack buffer |
| `stackSize` | Stack size in bytes |
| `entryPoint` | Address of the task entry-point function |
| `arg` | Argument passed to the entry point (static applications only) |

**`T_mkApplicationMetadata` fields:**

| Field | Description |
| --- | --- |
| `name` | UTF-8 application name string (may be `K_MK_NULL`) |
| `author` | UTF-8 author name string (may be `K_MK_NULL`) |
| `version` | UTF-8 version string (may be `K_MK_NULL`) |
| `description` | UTF-8 description string (may be `K_MK_NULL`) |
| `iconPath` | UTF-8 path to the application icon (may be `K_MK_NULL`) |
| `iconAddr` | Load address of the icon in memory |

### 4.4 Launching, closing and uninstalling

```c
/* Start an installed application */
T_mkCode l_result = mk_application_launch(l_app, K_MK_NULL);

/* Stop a running application — returns it to INSTALLED state */
l_result = mk_application_close(l_app, K_MK_NULL);

/* Destroy the entry-point task only (no display engine close sequence) */
l_result = mk_application_terminate(l_app, K_MK_NULL);

/* Remove an application from the system entirely */
l_result = mk_application_uninstall(l_app, K_MK_NULL);
```

The difference between `close` and `terminate`:

| Function | What it does |
| --- | --- |
| `mk_application_close()` | Sends `K_MK_EVENT_CLOSE` to the dispatcher. Containers are removed from the factory, the entry-point task is destroyed, and memory pages are freed. Application returns to INSTALLED. |
| `mk_application_terminate()` | Destroys the entry-point task only, without the display engine close sequence. Use this for daemon-style applications that own no containers. |

### 4.5 Updating metadata and input attributes

These two functions allow a running application to update its own metadata or input
device settings at runtime. Both parameters are transmitted **by reference** to the
Display engine and must therefore **not** point to a local (stack-allocated) variable.

```c
/* Update display metadata (name, icon…) */
static T_mkApplicationMetadata l_meta = { "MyApp", "Me", "1.0", K_MK_NULL, K_MK_NULL, K_MK_NULL };
T_mkCode l_result = mk_application_setMetadata(l_app, &l_meta, K_MK_NULL);

/* Update input device attributes (mouse cursor, keyboard repeat…) */
static T_mkDispatcherAttributes l_attrs = {
    .pointerResolution        = 1.0f,
    .stickResolution          = 1.0f,
    .mouseCursorLayer         = K_MK_GRAPHICS_FOREGROUND,
    .mouseCursorVisibility    = K_MK_FIELD_VISIBLE,
    .mouseCursorBitmap        = K_MK_NULL,   /* default cursor */
    .mouseCursorWidth         = 0,
    .mouseCursorHeight        = 0,
    .keyboardInhibitionDuration = 500,       /* ms before first hold event */
    .keyboardHoldRate         = 30           /* ms between hold events */
};
l_result = mk_application_setAttributes(l_app, &l_attrs, K_MK_NULL);
```

**`T_mkDispatcherAttributes` fields:**

| Field | Description |
| --- | --- |
| `pointerResolution` | Mouse/touch pointer speed multiplier. A negative value inverts the axis direction. |
| `stickResolution` | Joystick stick speed multiplier. A negative value inverts the axis direction. |
| `mouseCursorLayer` | Layer on which the cursor is drawn: `K_MK_GRAPHICS_BACKGROUND` or `K_MK_GRAPHICS_FOREGROUND`. |
| `mouseCursorVisibility` | `K_MK_FIELD_VISIBLE` or `K_MK_FIELD_INVISIBLE`. |
| `mouseCursorBitmap` | Address of a custom cursor bitmap in **ARGB8888** format (`uint32_t[]` array, row-major, `width × height` entries). Each `uint32_t` encodes one pixel as `0xAARRGGBB` where `AA` is the alpha channel (`0xFF` = fully opaque, `0x00` = fully transparent). Pass `K_MK_NULL` to use the system default cursor. See `g_mkDefaultCursor` (11 × 17 px) in `mk_cursor_data.c` for a concrete example. The bitmap is drawn by `mk_graphics_drawBitmap()` which expects the data to remain valid for the lifetime of the application. |
| `mouseCursorWidth` | Width of the custom cursor bitmap in pixels. |
| `mouseCursorHeight` | Height of the custom cursor bitmap in pixels. |
| `keyboardInhibitionDuration` | Delay in ms between a key-down event and the first key-hold repeat event. |
| `keyboardHoldRate` | Interval in ms between successive key-hold repeat events. |

### 4.6 Return codes

| Code | Meaning |
| --- | --- |
| `K_MK_OK` | Operation succeeded |
| `K_MK_ERROR_PARAM` | Invalid parameter (null pointer, malformed path…) |
| `K_MK_ERROR_MALLOC` | No free application slot or insufficient SDRAM |
| `K_MK_ERROR_ISR` | Called from an interrupt handler |
| `K_MK_ERROR_RIGHT` | Unprivileged task attempted a privileged operation |
| `K_MK_ERROR_TIMEOUT` | Display engine request timed out |
| `K_MK_ERROR_NOT_FOUND` | `.elf` file not found on storage |
| `K_MK_ERROR_COMM` | Storage communication error during ELF loading |
| `K_MK_ERROR_CORRUPTED` | FAT cluster chain corrupted in the `.elf` file |
| `K_MK_ERROR_UNEXPECTED` | ELF header validation failed (bad magic, missing descriptor…) |
| `K_MK_ERROR_NOT_AVAILABLE` | No more command-line tokens (`mk_application_getArgv` only) |

---

## See also

- [Architecture Overview](Architecture-Overview) — system layers, memory map, privilege model, boot sequence
- [Use or extend the Shell](Shell-and-Commands) — external shell commands, console I/O API
- [Sym2srec](https://github.com/EmbSoft3/Sym2srec/wiki) — symbol table to SREC conversion tool for the Mk kernel API
