# Use or extend the Shell

This page describes how the Shell works internally, how to use its built-in commands, and how to write an external command that can be invoked by name from the console.

---

## Table of contents

1. [Architecture overview](#1-architecture-overview)
2. [Built-in commands](#2-built-in-commands)
3. [Console I/O API](#3-console-io-api)
4. [Writing an external command](#4-writing-an-external-command)
   - 4.1 [Principle](#41-principle)
   - 4.2 [Deployment](#42-deployment)
   - 4.3 [Argument parsing](#43-argument-parsing)
   - 4.4 [Minimal example](#44-minimal-example)
5. [Multi-phase built-in commands](#5-multi-phase-built-in-commands)

---

## 1. Architecture overview

The Shell is split into two independent components:

- **Shell application** (`shellRelease.elf`) — a dynamic graphical application that provides the console UI. It owns a `T_mkConsole` widget and its keyboard listener. When the user presses **Enter**, the listener writes the command string to a temporary file in `mk/tmp/` (name randomly generated) and posts a `T_mkShellMessage` to the handler mailbox `g_mkShellMessageArea.mail`. Multiple instances of the Shell application can run simultaneously (e.g. one per connected terminal or display context), each with its own `T_mkConsole`. 

- **Shell handler** (`mk_shell` task) — a privileged kernel task (`K_MK_TASK_ID_SHELL`, priority 2) created at boot by `mk_shell_create`. It blocks on the mailbox, reads the temporary file, deletes it, then dispatches the command string to the appropriate function.

```
 User (keyboard)
      │  Enter pressed
      ▼
 mk_supervisor_listenConsole
   1. write command string to mk/tmp/<random>.input
   2. mk_mail_post(g_mkShellMessageArea.mail, {fileName, console})
      │
      ▼
 mk_shell task (priority 2)
   mk_shell_handle:
     1. mk_file_read(fileName) → command string in page memory
     2. mk_file_unlink(fileName)
     3. mk_shell_execute → dispatch to built-in function
                        → or mk_shell_run (external command)
```

The mailbox depth is `K_MK_SHELL_MESSAGE_NUMBER = 8`. If the mailbox is full when the user presses Enter, the command is dropped and a message is printed in the console.

The shell handler allocates one SRAM page (`K_MK_PAGE_ID_SRAM`, size `K_MK_PAGE_SRAM_BLOCK_SIZE` = 64 KB) at initialisation. The command string is stored in this page and remains valid for the entire duration of command execution since the handler runs at higher priority than the Shell application.

The initial working directory is set to `/<disk>/<volume>/mk/shell` at startup, where `<disk>` and `<volume>` are the identifiers of the system volume.

---

## 2. Built-in commands

All built-in commands are dispatched directly inside the shell handler task. Type `help` in the console to list them, or `help <command>` for usage of a specific command.

| Command | Syntax | Description |
|---|---|---|
| `help` | `help [cmd]` | List all commands or show usage for one |
| `cls` | `cls` | Clear the console output |
| `reset` | `reset` | Immediately restart the system |
| `restart` | `restart` | Restart with confirmation prompt |
| `abort` | `abort` | Abort the current multi-phase command |
| `install` | `install <path.elf> [-s "args"] [-l]` | Install a dynamic application; `-l` launches it immediately; `-s` passes arguments |
| `uninstall` | `uninstall <pid>` | Uninstall an installed dynamic application |
| `launch` | `launch <pid>` | Launch an already-installed application |
| `terminate` | `terminate <pid>` | Stop a running application |
| `get-apps` | `get-apps [pid]` | List all installed applications or details of one |
| `ls` | `ls` | List contents of the current directory |
| `cd` | `cd <path>` | Change the current directory |
| `pwd` | `pwd` | Print the current directory |
| `lsdsk` | `lsdsk` | List all mounted disks and partitions |

Paths passed to `install`, `cd`, and `run` can be absolute (starting with `/`) or relative to the current working directory.

---

## 3. Console I/O API

The following functions write to or read from a `T_mkConsole`. They operate on the console's standard output **file** (not directly on the graphical widget). 

| Function | Description |
|---|---|
| `mk_console_print(p_console, str)` | Write a UTF-8 string to the console's standard output file. A graphical refresh is triggered after this call. |
| `mk_console_log(p_console, str)` | Write a UTF-8 string to the console's standard output file, prepending a header of the form `TID({tid}h) > {yy-mm-ddThh:mm:ss,000} >` (task ID and RTC timestamp). A graphical refresh is triggered after this call. |
| `mk_console_puts(p_console, str)` | Write a UTF-8 string to the console's standard output file. No graphical refresh is triggered. |
| `mk_console_gets(p_console, buf, len)` | Retrieve the current content of the console's prompt (input field) into `buf`. `len` is the buffer size in bytes, null terminator included. |
| `mk_console_clear(p_console)` | Clear (erase) the console's standard output file. |

`mk_console_print` is the standard output function for command feedback: it writes and immediately refreshes the display. `mk_console_log` adds a timestamp prefix suitable for diagnostics. `mk_console_puts` is useful when assembling multiple lines before triggering a single refresh manually. `mk_console_gets` reads the prompt content, typically used in a multi-phase command to collect the user's response.

---

## 4. Writing an external command

### 4.1 Principle

When the shell handler does not recognise a typed word as a built-in command, it calls `mk_shell_run`. This function treats the word as a filename: it looks for `<command>.elf` in the current working directory (or at the absolute path if the command starts with `/`), installs it as a dynamic application via `mk_application_installDynamic`, and immediately launches it with `mk_application_launch`.

An external command is therefore a **standard Mk dynamic application** (see [ELF Loader](ELF-Loader) and [Build a graphical application](Graphical-Engine)). It runs independently in its own task, completely detached from the shell handler once launched. It can use the full Mk API including graphical widgets, file I/O, and USB devices.

The command-line arguments typed after the command name are passed to the application as its command-line string, retrievable with `mk_application_getCmdLine` or `mk_application_getArgv`.

### 4.2 Deployment

The `mk/shell` path is resolved at shell initialisation time inside `mk_shell_init()` (source: `Mk/Sources/Shell/Handler/mk_shell_init.c`). The function calls `mk_supervisor_getVolume()` to retrieve the system volume, then builds the initial working directory string as:

```
/<disk.name.id>/<volume.name.str>/<K_MK_SHELL_EXTERNAL_COMMAND_PATH>
```

where `K_MK_SHELL_EXTERNAL_COMMAND_PATH = "mk/shell"`. The result is stored in `p_shell->currentDirectory` and is used as the base for all relative-path command lookups.

Place the compiled `.elf` file in the `mk/shell/` directory on the system volume. Since the shell's initial working directory points there, typing the base name of the file (without `.elf`) is enough to invoke it:

```
mk/
└── shell/
    └── mycommand.elf    ← invoked by typing: mycommand [args]
```

Alternatively, a command can be invoked from any directory using an absolute path:

```
/DISK0/MK_SYSTEM/mk/shell/mycommand.elf [args]
```

Or using a relative path from the current directory after a `cd`.

### 4.3 Argument parsing

The entire text typed after the command name is passed as the application's command-line string. Use `mk_application_getArgv` to iterate over whitespace-separated tokens:

```c
T_mkCode mk_application_getArgv(
    T_str8         p_chain,        /* current position in the command string */
    T_str8*        p_nextChain,    /* output: position of the next token */
    T_str8         p_arg,          /* output buffer for the current token */
    uint32_t       p_argLength,    /* size of p_arg buffer in bytes */
    T_mkFontUnicode p_fontEncoding /* encoding of the command string */
);
```

Returns `K_MK_OK` when a token was extracted, `K_MK_ERROR_NOT_AVAILABLE` when the end of the string is reached.

```c
void myCommand_main(T_mkAddr p_arg)
{
    T_str8 l_cmdLine = (T_str8) p_arg;   /* full argument string */
    T_str8 l_next    = K_MK_NULL;
    uint8_t l_token[64] = { 0 };
    T_mkCode l_result;

    /* Iterate over whitespace-separated tokens */
    l_result = mk_application_getArgv(l_cmdLine, &l_next,
                                      (T_str8) l_token, sizeof(l_token),
                                      K_MK_FONT_UTF8);
    while (l_result == K_MK_OK)
    {
        /* process l_token */
        l_cmdLine = l_next;
        l_result = mk_application_getArgv(l_cmdLine, &l_next,
                                          (T_str8) l_token, sizeof(l_token),
                                          K_MK_FONT_UTF8);
    }

    mk_task_terminate(K_MK_NULL);
}
```

Tokens that contain spaces can be enclosed in double quotes: `mycommand "hello world" arg2`. The shell strips the quotes before passing the string to the application.

### 4.4 Minimal example

The skeleton below is a non-graphical command that reads one argument, prints a message to the system console, and exits.

Every dynamic application must expose a `T_mkApplicationDynamicHeader` as the **first object in its first loaded ELF segment** (offset 0 of the SDRAM page). The dynamic loader reads it immediately after mapping the ELF into memory to validate the application and retrieve its entry point and stack configuration.

`mk_application_data.c`:

```c
#include "mk_api.h"

/* Entry point — forward declaration */
void myCommand_main(T_mkAddr p_arg);

/* Stack */
uint32_t g_mkStack[256];

/*
 * Dynamic application header.
 * This structure must be the first symbol placed in the ELF (linker script
 * ensures it lands at offset 0 of the first PT_LOAD segment).
 * The loader reads it at l_page + 0 after deploying the ELF into SDRAM.
 */
T_mkApplicationDynamicHeader g_mkApplicationHeader =
{
   .header =
   {
      .magicNumber    = K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER,
      .headerSize     = sizeof ( T_mkApplicationHeader ),
      .version        = 1,
      .descriptorAddr = ( T_mkAddr ) &g_mkApplicationHeader.descriptor,
      .descriptorSize = sizeof ( T_mkApplicationDescriptor ),
      .metadataAddr   = ( T_mkAddr ) &g_mkApplicationHeader.metadata,
      .metadataSize   = sizeof ( T_mkApplicationMetadata ),
      .argAddr        = ( T_mkAddr ) &g_mkApplicationHeader.args,
      .argSize        = sizeof ( T_mkApplicationCmdLineArguments ),
   },
   .descriptor =
   {
      .type       = K_MK_APPLICATION_TYPE_DYNAMIC,
      .taskType   = K_MK_TYPE_DEFAULT,   /* unprivileged task */
      .gfxPage    = K_MK_FALSE,          /* no graphical memory page */
      .memPage    = K_MK_FALSE,          /* no standard memory page */
      .stackAddr  = ( T_mkAddr ) g_mkStack,
      .stackSize  = sizeof ( g_mkStack ),
      .entryPoint = ( T_mkAddress ) myCommand_main,
   },
   .metadata =
   {
      .name        = ( T_str8 ) "MyCommand",
      .author      = K_MK_NULL,
      .version     = K_MK_NULL,
      .description = K_MK_NULL,
      .iconPath    = K_MK_NULL,
      .iconAddr    = K_MK_NULL,
   }
};
```

`mk_main.c`:

```c
#include "mk_api.h"

void myCommand_main(T_mkAddr p_arg)
{
   /* Déclaration des variables de travail */
   T_mkApplication* l_application = ( T_mkApplication* ) p_arg;
   T_str8  l_cmdLine = K_MK_NULL;
   T_str8  l_next    = K_MK_NULL;
   uint8_t l_token [ 64 ] = { 0 };
   T_mkCode l_result;

   /* Récupération de la ligne de commande */
   l_cmdLine = mk_application_getCmdLine ( l_application );

   /* Extraction du premier argument */
   l_result = mk_application_getArgv ( l_cmdLine, &l_next,
                                       ( T_str8 ) l_token, sizeof ( l_token ),
                                       K_MK_FONT_UTF8 );
   if ( l_result == K_MK_OK )
   {
      /* Traitement de l_token */
   }
   else
   {
      /* Aucun argument fourni */
   }

   /* Terminaison de la tâche */
   mk_task_terminate ( K_MK_NULL );
}
```

> **Note:** `p_arg` received by the entry point is the address of the `T_mkApplication` structure, not the raw command-line string. Use `mk_application_getCmdLine(p_application)` to retrieve the argument string.

---

## 5. Multi-phase built-in commands

Some built-in commands require user interaction across multiple Enter presses (e.g. a confirmation prompt). This is implemented through the `reg` register of `T_mkShell`:

```c
struct T_mkShellMemoryRegister {
    uint32_t                 cmdInProgress; /* K_MK_SHELL_CMD_IN_PROGRESS or _END */
    T_mkAddr                 addr;          /* arbitrary state pointer */
    T_mkShellCallbackFunction callback;     /* function to call on next input */
};

typedef T_mkCode (*T_mkShellCallbackFunction)(
    T_mkShell*   p_shell,
    T_mkConsole* p_console,
    T_mkAddr     p_addr,     /* == p_shell->reg.addr */
    T_str8       p_str,      /* the new input line */
    uint32_t     p_length    /* length of p_str in bytes */
);
```

When a command sets `cmdInProgress = K_MK_SHELL_CMD_IN_PROGRESS`, the next input from the user is routed directly to `reg.callback` instead of the normal dispatch table. The only exception is `abort`, which always clears the multi-phase state regardless.

The `restart` command illustrates the pattern:

```c
T_mkCode mk_shell_restart(T_mkShell* p_shell, T_mkConsole* p_console,
                           T_mkAddr p_addr, T_str8 p_str, uint32_t p_length)
{
    if (p_addr == K_MK_NULL)
    {
        /* Phase 1: arm the callback and prompt for confirmation */
        p_shell->reg.cmdInProgress = K_MK_SHELL_CMD_IN_PROGRESS;
        p_shell->reg.callback      = mk_shell_restart;
        p_shell->reg.addr          = K_MK_NOT_NULL;   /* non-NULL flags phase 2 */
        return mk_console_print(p_console, (T_str8) "Confirm restart (y/n) ?\r\n\r\n");
    }
    else
    {
        /* Phase 2: process the user's answer */
        p_shell->reg.cmdInProgress = K_MK_SHELL_CMD_END;
        if (p_str[0] == 'y')
            cortex_resetSystem();
        return K_MK_OK;
    }
    (void) p_length;
}
```

Key rules for a multi-phase command:
- Set `reg.cmdInProgress = K_MK_SHELL_CMD_IN_PROGRESS` and `reg.callback` in phase 1.
- The callback receives the same `T_mkShell*`, `T_mkConsole*`, and `reg.addr` on every subsequent call.
- Always set `reg.cmdInProgress = K_MK_SHELL_CMD_END` when the sequence is complete.
- The user can type `abort` at any time to cancel: the handler clears `cmdInProgress` and `callback` before returning.

This mechanism is built into the shell handler and is directly available to any **built-in** command (i.e. a command compiled into the `mk_shell` task).

An **external command** can also use the multi-phase mechanism, but it must instantiate its own `T_mkShell` and `T_mkConsole` — exactly as the [Shell](https://github.com/EmbSoft3/Shell/tree/main) application does. 

---

## See also

- [Writing your first application](Writing-Your-First-Application) — step-by-step guide from descriptor to running application
- [Load and run external programs](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
- [Sym2srec](https://github.com/EmbSoft3/Sym2srec/wiki) — symbol table to SREC conversion tool for the Mk kernel API
