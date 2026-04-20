# Build an application

This section walks through building and running Mk applications, using two reference
examples:

- **[BlinkLed](https://github.com/EmbSoft3/BlinkLed)** — a minimal background daemon with no UI that toggles a GPIO at a
  configurable rate.
- **[Pong](https://github.com/EmbSoft3/Pong)** — a complete graphical application demonstrating layers, widgets, painters
  and event listeners.

---

## Table of contents

1. [How Mk applications work](#1-how-mk-applications-work)
2. [Choosing your application pattern](#2-choosing-your-application-pattern)
   - 2.1 [Pattern A — Background daemon (BlinkLed)](#21-pattern-a--background-daemon-blinkled)
   - 2.2 [Pattern B — Graphical application (Pong)](#22-pattern-b--graphical-application-pong)
3. [Step 1 — Declare the application descriptor](#3-step-1--declare-the-application-descriptor)
   - 3.1 [Application type](#31-application-type)
   - 3.2 [Task type](#32-task-type)
   - 3.3 [Graphical memory page (gfxPage)](#33-graphical-memory-page-gfxpage)
   - 3.4 [Standard memory page (memPage)](#34-standard-memory-page-mempage)
   - 3.5 [Static argument (arg)](#35-static-argument-arg)
4. [Step 2 — Define the application state structure](#4-step-2--define-the-application-state-structure)
5. [Step 3 — Write the entry point](#5-step-3--write-the-entry-point)
   - 5.1 [Pattern A — Daemon (BlinkLed)](#51-pattern-a--daemon-blinkled)
   - 5.2 [Pattern B — Graphical application (Pong)](#52-pattern-b--graphical-application-pong)
6. [Step 4 — Initialise the graphical application](#6-step-4--initialise-the-graphical-application)
   - 6.1 [Retrieve the application handle](#61-retrieve-the-application-handle)
   - 6.2 [Initialise the layer](#62-initialise-the-layer)
   - 6.3 [Initialise the screen widget](#63-initialise-the-screen-widget)
   - 6.4 [Initialise text fields and fonts](#64-initialise-text-fields-and-fonts)
   - 6.5 [Configure dispatcher attributes (keyboard / mouse)](#65-configure-dispatcher-attributes-keyboard--mouse)
   - 6.6 [Create the container and register with the factory](#66-create-the-container-and-register-with-the-factory)
7. [Step 5 — Handle events: listeners](#7-step-5--handle-events-listeners)
   - 7.1 [Application listener (suspend / resume / close)](#71-application-listener-suspend--resume--close)
   - 7.2 [Widget listener (keyboard input)](#72-widget-listener-keyboard-input)
8. [Step 6 — Draw the scene: painters](#8-step-6--draw-the-scene-painters)
9. [Step 7 — Build, install and run](#9-step-7--build-install-and-run)
10. [Error codes](#10-error-codes)

---

## 1. How Mk applications work

An Mk application is a position-independent `.elf` file loaded at runtime by the dynamic
loader into a dedicated 64 KB SDRAM page. It is fully self-contained and references the
Mk kernel API directly — no copy of the kernel is needed in the binary.

Every application revolves around two mandatory components and one optional one:

| Component | Required | Description |
| --- | --- | --- |
| **Application descriptor** | Yes | Declares the entry point, stack, task type, and metadata. Placed in the `.descriptor` section so the loader finds it at the base of the loaded page. |
| **Entry point** | Yes | The function called once by the loader when the application is launched. |
| **Event callbacks** | No | Painter and listener functions invoked by the graphical engine each frame. Only needed for graphical applications (Pattern B) that delegate execution to the Display engine after the entry point exits. Background daemons (Pattern A) run entirely inside the entry point loop and do not register any callbacks. An application may also keep its entry-point task alive and perform all work there, without ever registering a painter or listener. |

---

## 2. Choosing your application pattern

Before writing any code, decide which pattern fits your use case.

### 2.1 Pattern A — Background daemon (BlinkLed)

The entry point runs a simple infinite loop. There is no UI, no container, no listener.
Use this for background services (hardware polling, GPIO toggling, communication tasks).

```
Loader calls main()
  └─ parse command-line arguments
  └─ while (1) { do_work(); mk_task_sleep(rate); }
```

### 2.2 Pattern B — Graphical application (Pong)

The entry point initialises all widgets and the container, registers the container with
the graphical engine, then **optionally terminates itself**. Once `mk_task_terminate()`
is called, the application lives entirely inside the painter and listener callbacks
invoked by the Display engine at each frame.

Terminating the entry-point task is not mandatory. You can keep it alive and use it for
background work (game loop logic, networking, polling…) while the Display engine drives
the graphical side concurrently through painters and listeners. Both approaches can
coexist. If the entry-point task is still running when the application is closed by the
user or the system, the kernel destroys it automatically — you do not need to terminate
it explicitly before closing.

```
Loader calls mk_pong_main()
  └─ mk_pong_init()          ← set up widgets, container, register with factory
  └─ mk_task_terminate()     ← optional: main task exits; engine takes over

Display engine (every frame):
  ├─ mk_pong_paintPlayground()   ← draw scene, advance game logic
  ├─ mk_pong_paintButton()       ← draw menu buttons
  └─ mk_pong_listenApplication() ← handle suspend / resume
  └─ mk_pong_listenPlayground()  ← handle keyboard input
```

---

## 3. Step 1 — Declare the application descriptor

Every application must declare a `T_mkApplicationDynamicHeader` structure in the
`.descriptor` linker section. This is how the loader identifies and launches your
application.

```c
#define K_MK_SECTION_STACK      __attribute__((section(".stack"),      used))
#define K_MK_SECTION_DESCRIPTOR __attribute__((section(".descriptor"), used))

/* Application stack */
K_MK_SECTION_STACK uint32_t g_mkStack[K_MK_PONG_STACK_SIZE];

/* Application descriptor */
K_MK_SECTION_DESCRIPTOR T_mkApplicationDynamicHeader g_mkApplicationDynamicHeader =
{
    /* Header — fixed boilerplate, do not change field order */
    {
        K_MK_DISPLAY_APPLICATION_DYNAMICHEADER_MAGICNUMBER,
        sizeof(T_mkApplicationDynamicHeader),
        0xFFFFFFFF,
        1,
        &g_mkApplicationDynamicHeader.descriptor,
        sizeof(T_mkApplicationDescriptor),
        &g_mkApplicationDynamicHeader.metadata,
        sizeof(T_mkApplicationMetadata),
        &g_mkApplicationDynamicHeader.args,
        sizeof(T_mkApplicationCmdLineArguments)
    },

    /* Descriptor */
    {
        K_MK_APPLICATION_TYPE_DYNAMIC,   /* Application type  — see §3.1 */
        K_MK_TYPE_FLOATING,              /* Task type         — see §3.2 */
        K_MK_FALSE,                      /* gfxPage           — see §3.3 */
        K_MK_FALSE,                      /* memPage           — see §3.4 */
        g_mkStack,                       /* Stack address */
        K_MK_PONG_STACK_SIZE,            /* Stack size (words) */
        mk_pong_main,                    /* Entry point */
        K_MK_NULL                        /* arg (static apps only) */
    },

    /* Metadata */
    {
        (T_str8) "Pong",
        (T_str8) "Mac Lewis",
        (T_str8) "V1.1",
        (T_str8) "Just a Pong Game",
        (T_str8) "mk_pong.bmp",         /* Icon BMP file — must be placed at the root of the application directory on storage */
        K_MK_NULL
    },

    /* Command-line arguments (zeroed by default) */
    { { 0 } }
};
```

### 3.1 Application type

The first descriptor field controls how Mk manages the application lifecycle.

| Constant | Value | Description |
| --- | --- | --- |
| `K_MK_APPLICATION_TYPE_STATIC` | 0 | Linked directly into the firmware. Registered at boot via `mk_application_install()`. Used by native system applications (Supervisor, Home). |
| `K_MK_APPLICATION_TYPE_DYNAMIC` | 1 | Loaded at runtime from a `.elf` file on storage. The loader deploys the binary into a dedicated 64 KB SDRAM page, resolves symbols against the kernel API table, and registers the application. **Use this for all external applications.** |
| `K_MK_APPLICATION_TYPE_DAEMON` | 2 | The application runs in the background and does not become the foreground application when launched. **Must be combined with `K_MK_APPLICATION_TYPE_DYNAMIC`** for a dynamically loaded daemon: `K_MK_APPLICATION_TYPE_DYNAMIC \| K_MK_APPLICATION_TYPE_DAEMON`. The two flags occupy independent bits (bit 0 and bit 1) and the kernel tests them separately with bitwise AND, so combining them is safe and correct. |

### 3.2 Task type

The second field controls privilege level and floating-point context of the entry-point
task.

| Constant | Privilege | Floating-point context saved at every context switch |
| --- | --- | --- |
| `K_MK_TYPE_FLOATING_PRIVILEGED` | Privileged | Yes (S0–S31, FPSCR) |
| `K_MK_TYPE_FLOATING` | Unprivileged | Yes (S0–S31, FPSCR) |
| `K_MK_TYPE_PRIVILEGED` | Privileged | No — FPU must not be used |
| `K_MK_TYPE_DEFAULT` | Unprivileged | No — FPU must not be used |

Choose `K_MK_TYPE_FLOATING` for graphical applications that perform floating-point
calculations (ball physics, animations…) but do not need to access privileged memory
regions. Choose `K_MK_TYPE_FLOATING_PRIVILEGED` only when direct access to kernel
structures is required.

> Unprivileged tasks cannot access privileged memory regions. Any violation triggers a
> MemFault and terminates the offending application cleanly — the kernel and all other
> applications are unaffected.

### 3.3 Graphical memory page (`gfxPage`)

When set to `K_MK_TRUE`, Mk allocates a **graphical memory page** from external SDRAM
at launch time. The base address is stored in `p_application->page.gfxAddr`.

| Property | Value |
| --- | --- |
| Location | External SDRAM (`0xC0000000` region) |
| Size | **1 228 800 bytes** (640 × 480 × 4 — four full-screen ARGB8888 frame buffers) |
| Lifetime | Allocated on launch, freed automatically on close or terminate |

Use `gfxPage = K_MK_TRUE` when your application needs a large off-screen buffer (e.g.
a console rendering cache). **The Pong application does not use a graphical page** —
all drawing goes directly through the widget API which uses the engine's own frame
buffers. Set `gfxPage = K_MK_FALSE` whenever your application relies solely on the
widget API.

### 3.4 Standard memory page (`memPage`)

When set to `K_MK_TRUE`, Mk allocates a **standard memory page** from external SRAM at
launch time. The base address is stored in `p_application->page.memAddr`.

| Property | Value |
| --- | --- |
| Location | External SRAM (`0x68000000` region) |
| Size | **65 536 bytes** (64 KB) |
| Lifetime | Allocated on launch, freed automatically on close or terminate |

> **Note:** for dynamic applications, the loader deploys the `.elf` binary into a
> separate 64 KB SDRAM page (`deploymentAddr`). The `memPage` SRAM page is a completely
> independent allocation available for general-purpose use.

### 3.5 Static argument (`arg`)

Behaviour depends on application type:

- **Static** (`K_MK_APPLICATION_TYPE_STATIC`): the value is forwarded verbatim to the
  entry point as `p_param`. Use it to pass a pointer to a pre-allocated state structure.
- **Dynamic / Daemon**: the loader **overwrites** this field with the `T_mkApplication*`
  handle before launching the task. The value you write in the descriptor is ignored.
  The entry point always receives the application handle:

```c
void mk_pong_main(T_mkAddr p_param)
{
    /* p_param is T_mkApplication* for dynamic applications */
    /* Pong ignores it and uses mk_application_getCurrent() instead */
    (void) p_param;
    ...
}
```

---

## 4. Step 2 — Define the application state structure

Declare a single global structure that owns all runtime objects of the application.
This avoids dynamic allocation and keeps everything in one place.

```c
/* mk_pong_types.h */

typedef struct T_mkPongApplication T_mkPongApplication;
struct T_mkPongApplication
{
    T_mkApplication*        application;  /* Handle returned by mk_application_getCurrent() */
    T_mkPongBackgroundFields background;  /* All graphical widgets */
    T_mkPongPlayground      playground;   /* Game state */
    T_mkContainer*          container;    /* Root graphical container */
};

typedef struct T_mkPongBackgroundFields T_mkPongBackgroundFields;
struct T_mkPongBackgroundFields
{
    T_mkFont       font;          /* Custom font */
    T_mkFontPage   page;          /* Font page descriptor */
    T_mkLayer      layers;        /* Layer controller */
    T_mkScreen     playground;    /* Full-screen drawing surface */
    T_mkTextField  scoreJ1;       /* Player 1 score label */
    T_mkTextField  scoreJ2;       /* Player 2 score label */
    T_mkTextField  buttonStart;   /* "Play" menu button */
    T_mkTextField  buttonQuit;    /* "Quit" menu button */
    T_mkTextStyle  buttonStyle;   /* Shared text style for buttons */
};
```

```c
/* mk_pong_data.c */
T_mkPongApplication g_mkPongApplication;
```

The global instance is declared without `static` so that all source files can reach it
via `extern` when needed inside painters and listeners.

---

## 5. Step 3 — Write the entry point

### 5.1 Pattern A — Daemon (BlinkLed)

The entry point runs for the entire application lifetime. It reads command-line
arguments then loops forever.

```c
void main(T_mkAddr p_param)
{
    uint32_t l_rate;
    uint8_t  l_argv[16] = { 0 };
    T_str8   l_arguments = K_MK_NULL;

    /* Retrieve the application handle */
    T_mkApplication* l_application = (T_mkApplication*) p_param;

    /* Read command-line arguments */
    (void) mk_application_getCmdLine(l_application, &l_arguments);
    (void) mk_application_getArgv(l_arguments, &l_arguments,
                                  (T_str8) l_argv, 16, K_MK_FONT_ASCII);

    /* Convert first argument to an integer (blink period in ms) */
    l_rate = (uint32_t) mk_utils_atoi((T_str8) l_argv, 10);

    /* Run forever */
    while (1)
    {
        gpio_toggle();
        mk_task_sleep(l_rate);
    }
}
```

From the Shell, launch with: `launch blinkLedRelease.elf 500`

### 5.2 Pattern B — Graphical application (Pong)

The entry point initialises the application then **optionally terminates itself**.
Calling `mk_task_terminate()` hands over all subsequent execution to the Display engine
via the registered painter and listener callbacks. This is the approach used by Pong
for simplicity, but it is not required — the entry-point task may remain alive to handle
background work in parallel with the Display engine.

```c
void mk_pong_main(T_mkAddr p_param)
{
    /* Initialise the application: widgets, container, factory registration */
    T_mkCode l_result = mk_pong_init(&g_mkPongApplication);

    /* Terminate the main task — the Display engine takes over */
    /* This call is optional. The task can remain alive for background work. */
    if (l_result == K_MK_OK)
    {
        (void) mk_task_terminate(K_MK_NULL);
    }

    /* Should never be reached */
    while (1) {}

    (void) p_param;
}
```

> **Note:** if `mk_task_terminate()` is not called and the entry-point task remains
> running, it is still destroyed **automatically by the kernel** when the application is
> closed via `mk_application_close()`. You do not need to terminate it explicitly before
> closing.

> There is no mailbox, no message loop in the entry point. The application closes when
> the user presses **Q** from inside the listener, which calls `mk_application_close()`
> directly.

---

## 6. Step 4 — Initialise the graphical application

All widget setup, layer configuration, and container registration happen in a dedicated
`init` function called from the entry point.

### 6.1 Retrieve the application handle

For dynamic applications, use `mk_application_getCurrent()` rather than casting
`p_param`. This is the recommended approach when the entry point terminates early,
because `p_param` ceases to be valid once the task exits.

```c
p_pong->application = mk_application_getCurrent();
```

### 6.2 Initialise the layer

A `T_mkLayer` controls which hardware compositing plane the application draws onto.
Mk provides two planes: **background** and **foreground**. They are blended by the
LTDC controller in hardware, with the foreground drawn on top of the background.

```c
mk_layer_init(&p_pong->background.layers);
mk_layer_set(&p_pong->background.layers, K_MK_LAYER_BACKGROUND_VISIBLE);
```

| Constant | Plane | Typical use |
| --- | --- | --- |
| `K_MK_LAYER_BACKGROUND_VISIBLE` | Background | Game scenes, full-screen content |
| `K_MK_LAYER_FOREGROUND_VISIBLE` | Foreground | Overlays, HUD, cursor |

Both planes can be activated simultaneously when the application uses both layers:

```c
mk_layer_set(&p_pong->background.layers,
             K_MK_LAYER_BACKGROUND_VISIBLE | K_MK_LAYER_FOREGROUND_VISIBLE);
```

The layer object must be added to the container as a field (see §6.6). Every widget
you later create must also be assigned to the correct plane via its own `setLayer` call.

### 6.3 Initialise the screen widget

A `T_mkScreen` is a full-screen drawing surface. It is a standard widget like any other
— it has a painter and a listener, and it can be reused across different graphical
contexts. In Pong, the same `T_mkScreen` instance is used for both the menu and the
game scene: its default painter is replaced by a custom one (`mk_pong_paintPlayground`)
and its default listener by `mk_pong_listenPlayground`. Setting both painter and
listener on the same screen object is the usual pattern for applications that draw their
own content using the graphics API rather than relying on pre-built widgets.

```c
mk_screen_init(&p_pong->background.playground);
mk_screen_setColor(&p_pong->background.playground, K_MK_COLOR_ARGB_BLACK);
mk_screen_setLayer(&p_pong->background.playground, K_MK_GRAPHICS_BACKGROUND);
mk_screen_setVisibility(&p_pong->background.playground, K_MK_FIELD_VISIBLE);
mk_screen_setActivity(&p_pong->background.playground, K_MK_FIELD_ACTIF);
mk_screen_setPainter(&p_pong->background.playground, mk_pong_paintPlayground);
mk_screen_setListener(&p_pong->background.playground, mk_pong_listenPlayground);
```

> Set visibility to `K_MK_FIELD_VISIBLE` **and** activity to `K_MK_FIELD_ACTIF` for
> the widget to be both drawn and able to receive events. Invisible widgets are not
> drawn; inactive widgets do not receive events.

### 6.4 Initialise text fields and fonts

`T_mkTextField` is the standard widget for displaying text. It can be configured with
a custom font, colours, margins and alignment.

```c
/* Custom font loaded from the kernel's built-in font table */
mk_font_init(&p_pong->background.font);
mk_font_setHeight(&p_pong->background.font, K_MK_PONG_FIELD_FONT_HEIGHT);
mk_font_setPage(&p_pong->background.page,
                K_MK_FONT_PAGE_BASIC_LATIN,
                (uint32_t)(K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1),
                &g_mkFontDejaVuMathTeXGyre36ptBasicLatinPageDescriptor[0][0],
                g_mkFontDejaVuMathTeXGyre36ptBasicLatinPage);
mk_font_addPage(&p_pong->background.font, &p_pong->background.page);

/* Score label for player 1 */
mk_textField_init(&p_pong->background.scoreJ1);
mk_textField_setPosition(&p_pong->background.scoreJ1,
                         K_MK_PONG_FIELD_SCORE_J1_POSITION_X,
                         K_MK_PONG_FIELD_SCORE_J1_POSITION_Y);
mk_textField_setDimension(&p_pong->background.scoreJ1,
                          K_MK_PONG_FIELD_SCORE_J1_WIDTH,
                          K_MK_PONG_FIELD_SCORE_J1_HEIGHT);
mk_textField_setLayer(&p_pong->background.scoreJ1, K_MK_GRAPHICS_BACKGROUND);
mk_textField_setTextColor(&p_pong->background.scoreJ1, K_MK_COLOR_ARGB_WHITE);
mk_textField_setTextAlignment(&p_pong->background.scoreJ1,
                              K_MK_TEXT_CENTER_JUSTIFIED,
                              K_MK_TEXT_CENTER_JUSTIFIED);
mk_textField_setText(&p_pong->background.scoreJ1, p_pong->playground.j1.strScore);
mk_textField_setTextEncoding(&p_pong->background.scoreJ1, K_MK_FONT_UTF8);
mk_textField_setVisibility(&p_pong->background.scoreJ1, K_MK_FIELD_VISIBLE);
mk_textField_setActivity(&p_pong->background.scoreJ1, K_MK_FIELD_ACTIF);
mk_textField_setCache(&p_pong->background.scoreJ1, K_MK_NULL);
mk_textField_setFont(&p_pong->background.scoreJ1, &p_pong->background.font);
```

> `mk_textField_setCache()` accepts a buffer address to enable glyph caching: once a
> character has been rendered pixel by pixel, its bitmap is stored in the cache so
> subsequent frames can blit it directly instead of redrawing it from scratch. Pass
> `K_MK_NULL` to disable caching entirely, which is required when the text content
> changes every frame (score display, live counters), since a stale cache would show
> outdated glyphs.

### 6.5 Configure dispatcher attributes (keyboard / mouse)

`mk_application_setAttributes()` configures how Mk routes input events to the
application. Use it to set the key repeat delay, repeat rate, mouse cursor visibility
and cursor layer.

```c
T_mkDispatcherAttributes l_attributes = {
    K_MK_POINTER_DEFAULT_RESOLUTION,  /* Mouse cursor resolution */
    K_MK_STICK_DEFAULT_RESOLUTION,    /* Joystick resolution */
    K_MK_GRAPHICS_FOREGROUND,         /* Layer on which the cursor is drawn */
    K_MK_FIELD_INVISIBLE,             /* Cursor visibility (hidden for Pong) */
    K_MK_NULL,                        /* Custom cursor bitmap (NULL = default) */
    0, 0,                             /* Cursor width / height (unused if default) */
    50,                               /* Delay before first key-repeat event (ms) */
    10,                               /* Interval between subsequent key-repeat events (ms) */
};

T_mkCode l_result = mk_application_setAttributes(p_pong->application,
                                                  &l_attributes, K_MK_NULL);
```

### 6.6 Create the container and register with the factory

A `T_mkContainer` groups all widgets that belong to the application. Widgets are added
to the container via `mk_container_addField()`, but **adding a widget to a container
does not make it visible or active on its own**. Each widget's visibility and activity
are controlled independently through their respective `setVisibility()` and
`setActivity()` setters. The container becomes known to the Display engine only after
it is registered with the factory via `mk_factory_addContainer()`. That registration
step is what makes the engine start calling the painters and dispatching events to the
listeners of all fields in the container.

All containers that the application has registered with the factory are automatically
removed from the factory by the system when the application is closed — you do not need
to call `mk_factory_removeContainer()` explicitly.

The container's listener (`mk_pong_listenApplication`) handles application-level
events such as suspend and resume.

```c
/* Create the container with its application-level listener */
l_result = mk_container_create(&p_pong->container, 0,
                               mk_pong_listenApplication, K_MK_NULL);

/* Add every widget field to the container */
if (l_result == K_MK_OK)
{
    l_result  = mk_container_addField(p_pong->container,
                    &p_pong->background.playground.field, K_MK_NULL);
    l_result |= mk_container_addField(p_pong->container,
                    &p_pong->background.layers.field,     K_MK_NULL);
    l_result |= mk_container_addField(p_pong->container,
                    &p_pong->background.buttonQuit.field, K_MK_NULL);
    l_result |= mk_container_addField(p_pong->container,
                    &p_pong->background.buttonStart.field,K_MK_NULL);
    l_result |= mk_container_addField(p_pong->container,
                    &p_pong->background.scoreJ1.field,    K_MK_NULL);
    l_result |= mk_container_addField(p_pong->container,
                    &p_pong->background.scoreJ2.field,    K_MK_NULL);
}

/* Register the container with the Display engine */
if (l_result == K_MK_OK)
{
    l_result = mk_factory_addContainer(p_pong->container, K_MK_NULL);
}
```

> Add the **layer field** (`layers.field`) to the container **after** the screen field
> but **before** any widgets that must appear above the screen. Field order in the
> container determines the compositing order within the same plane.

---

## 7. Step 5 — Handle events: listeners

Listeners are callbacks invoked by the Display engine whenever an event occurs on a
widget or at the application level. Every listener has the same signature:

```c
T_mkCode myListener(
    T_mkContainer* p_container,  /* Container that owns the widget */
    T_mkField*     p_field,      /* Field that received the event */
    T_mkCtrlId     p_appCtrlId,  /* Type of the event source */
    T_mkAddr       p_appCtrl,    /* Pointer to the event source object */
    T_mkCtrlEvent  p_evtCtrl,    /* Event type */
    uint32_t       p_ctrlId      /* Event detail (key code, button id...) */
);
```

### 7.1 Application listener (suspend / resume / close)

The container listener receives application-level lifecycle events. Always check that
`p_appCtrl == l_application` before acting, because the same listener receives events
for every application running concurrently.

```c
T_mkCode mk_pong_listenApplication(
    T_mkContainer* p_container, T_mkField* p_field,
    T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl,
    T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId)
{
    T_mkApplication*     l_application = mk_container_getOwner(p_container);
    T_mkPongApplication* l_pong        = &g_mkPongApplication;

    if ((p_appCtrl == l_application) && (p_appCtrlId == K_MK_CONTROL_APPLICATION))
    {
        if (p_evtCtrl == K_MK_EVENT_RESUME)
        {
            /* Application brought to foreground -- restore visibility */
            mk_container_setVisibility(l_pong->container, K_MK_FIELD_VISIBLE);
            mk_container_setActivity(l_pong->container, K_MK_FIELD_ACTIF);
        }
        else if (p_evtCtrl == K_MK_EVENT_SUSPEND)
        {
            /* Application sent to background -- hide everything */
            mk_container_setVisibility(l_pong->container, K_MK_FIELD_INVISIBLE);
            mk_container_setActivity(l_pong->container, K_MK_FIELD_INACTIF);
        }
    }

    (void) p_field; (void) p_appCtrlId; (void) p_ctrlId;
    return K_MK_OK;
}
```

### 7.2 Widget listener (keyboard input)

Widget listeners are attached to individual widgets (here, the `T_mkScreen`). Filter
by `p_appCtrlId` to select the input source, then by `p_evtCtrl` to select the event
type.

```c
T_mkCode mk_pong_listenPlayground(
    T_mkContainer* p_container, T_mkField* p_field,
    T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl,
    T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId)
{
    T_mkPongApplication* l_pong = &g_mkPongApplication;

    if (p_appCtrlId == K_MK_CONTROL_KEYBOARD)
    {
        if (l_pong->playground.startGame == K_MK_PONG_GAME_START)
        {
            if ((p_evtCtrl == K_MK_EVENT_KEY_DOWN) || (p_evtCtrl == K_MK_EVENT_KEY_HOLD))
            {
                if      (p_ctrlId == K_MK_KEYBOARD_UPARROW)   mk_pong_handleRacketUP(l_pong);
                else if (p_ctrlId == K_MK_KEYBOARD_DOWNARROW) mk_pong_handleRacketDOWN(l_pong);
            }
            if ((p_evtCtrl == K_MK_EVENT_KEY_DOWN) && (p_ctrlId == K_MK_KEYBOARD_ESCAPE))
            {
                l_pong->playground.startGame = K_MK_PONG_GAME_STOP;
            }
        }
        else
        {
            if (p_evtCtrl == K_MK_EVENT_CHAR_DOWN)
            {
                T_mkKeyboard* l_keyboard = (T_mkKeyboard*) p_appCtrl;
                if ((l_keyboard->input->key.ascii == 'r') || (l_keyboard->input->key.ascii == 'R'))
                {
                    mk_pong_initGames(l_pong);
                    l_pong->playground.startGame = K_MK_PONG_GAME_START;
                }
                else if ((l_keyboard->input->key.ascii == 'q') || (l_keyboard->input->key.ascii == 'Q'))
                {
                    (void) mk_application_close(l_pong->application, K_MK_NULL);
                }
            }
        }
    }

    (void) p_field; (void) p_container;
    return K_MK_OK;
}
```

**Event source identifiers (`p_appCtrlId`)**

| Constant | Source |
| --- | --- |
| `K_MK_CONTROL_APPLICATION` | Application lifecycle (suspend, resume, close, uninstall) |
| `K_MK_CONTROL_KEYBOARD` | USB HID keyboard |
| `K_MK_CONTROL_MOUSE` | USB HID mouse |
| `K_MK_CONTROL_JOYSTICK` | USB HID joystick |
| `K_MK_CONTROL_SYSTEM` | System-level events |

**Keyboard event types (`p_evtCtrl` when `p_appCtrlId == K_MK_CONTROL_KEYBOARD`)**

| Constant | Description |
| --- | --- |
| `K_MK_EVENT_KEY_DOWN` | Key pressed (fires once on initial press) |
| `K_MK_EVENT_KEY_HOLD` | Key held (fires repeatedly after the repeat delay) |
| `K_MK_EVENT_KEY_UP` | Key released |
| `K_MK_EVENT_CHAR_DOWN` | Character decoded from the key press (use for text input) |

Use `K_MK_EVENT_KEY_DOWN` for discrete actions (pause, fire). Use
`K_MK_EVENT_KEY_HOLD` for continuous movement (racket up/down). Use
`K_MK_EVENT_CHAR_DOWN` when you need the decoded character (menu input, text fields).

---

## 8. Step 6 — Draw the scene: painters

Painters are callbacks invoked every frame by the Display engine, once per registered
widget that has a painter function. They handle both drawing and, when convenient,
game logic updates.

```c
T_mkCode mk_pong_paintPlayground(
    T_mkContainer* p_container,
    T_mkField*     p_field,
    uint32_t       p_frameNumber)
{
    T_mkCode             l_result    = K_MK_OK;
    T_mkScreen*          l_screen    = (T_mkScreen*) p_field->child;
    T_mkPongApplication* l_pong      = &g_mkPongApplication;
    T_mkVect2D           l_v1, l_v2;

    if (p_field->refresh != K_MK_FIELD_REFRESH_DISABLED)
    {
        /* Clear the screen */
        l_result = mk_graphics_fill(l_screen->field.layer,
                                    mk_color_getARGB32(&l_screen->color));

        /* Draw borders, rackets, ball */
        mk_vect2d_setCoord(&l_v1, l_pong->playground.j1.racket.x,
                                  l_pong->playground.j1.racket.y);
        mk_vect2d_setCoord(&l_v2, l_v1.x + K_MK_PONG_RACKET_WIDTH,
                                  l_v1.y + K_MK_PONG_RACKET_HEIGHT);
        l_result = mk_graphics_drawRect(l_screen->field.layer,
                                        K_MK_GRAPHICS_SOLID, l_v1, l_v2,
                                        K_MK_COLOR_ARGB_WHITE);

        /* Advance game logic */
        if (l_pong->playground.startGame == K_MK_PONG_GAME_START)
        {
            mk_textField_setVisibility(&l_pong->background.buttonStart, K_MK_FIELD_INVISIBLE);
            mk_textField_setVisibility(&l_pong->background.buttonQuit,  K_MK_FIELD_INVISIBLE);
            mk_pong_setBallPosition(l_pong, p_frameNumber);
            mk_pong_setRacketPosition(l_pong, &l_pong->playground.j2, p_frameNumber);
        }
        else
        {
            mk_textField_setVisibility(&l_pong->background.buttonStart, K_MK_FIELD_VISIBLE);
            mk_textField_setVisibility(&l_pong->background.buttonQuit,  K_MK_FIELD_VISIBLE);
        }
    }

    (void) p_container;
    return l_result;
}
```

**Painter signature**

| Parameter | Description |
| --- | --- |
| `p_container` | Container that owns the widget (rarely needed, cast to `(void)`) |
| `p_field` | The field being painted. Cast `p_field->child` to the concrete widget type. |
| `p_frameNumber` | Index of the current frame within the current second. Cycles from `0` to `K_MK_DISPLAY_FRAMERATE - 1` (i.e. **0 to 59** at 60 Hz), then resets to 0. Use it for time-based animations, blinking effects, or to throttle costly operations to run only every N frames. |

**Key drawing functions**

| Function | Description |
| --- | --- |
| `mk_graphics_fill(layer, color)` | Fill the entire plane with a solid colour |
| `mk_graphics_drawRect(layer, mode, v1, v2, color)` | Draw a filled or outline rectangle |
| `mk_graphics_drawRoundRect(layer, mode, v1, v2, radius, color)` | Draw a rounded rectangle |
| `mk_graphics_drawString(layer, v1, v2, str, style, NULL)` | Draw a UTF-8 string |

Always check `p_field->refresh != K_MK_FIELD_REFRESH_DISABLED` before drawing. The
refresh field is a throttling mechanism: once all graphical buffers have been rendered,
the Display engine sets it to `K_MK_FIELD_REFRESH_DISABLED` to prevent unnecessary
redraws on subsequent frames. When the widget content changes (score update, ball
position, visibility toggle...), request an explicit repaint by calling the widget's
setter:

```c
mk_screen_setRefresh(&p_pong->background.playground, K_MK_FIELD_REFRESH_ENABLED);
/* or for a text field: */
mk_textField_setRefresh(&p_pong->background.scoreJ1, K_MK_FIELD_REFRESH_ENABLED);
```

The engine will then call the painter again on the next frame and reset the flag
automatically once the redraw is complete.

---

## 9. Step 7 — Build, install and run

The application Makefile mirrors the Mk kernel Makefile structure.

1. Set `TOOLCHAIN_PATH` in `make/makefile` to your ARM toolchain directory.
2. Set `INCLUDES_API_PATH` to point to the Mk `Includes/` directory.
3. Build:

```
make clean
make all
```

This produces the `.elf` file — the file to deploy on target.

> The linker script (`make/linker.ld`) places the `.descriptor` section first so that
> the loader can read the application header at the base address of the loaded SDRAM
> page. Do not reorder sections.

Copy the `.elf` to the root of a FAT-formatted SD card or USB drive, then open the
Supervisor shell. To open it, press **Alt + S** from anywhere in the UI (this shortcut
toggles the shell console on and off). Then use the shell commands:

```
install pongGameRelease.elf
```

The application will appear in the Home screen list. To launch it directly:

```
launch pongGameRelease.elf
```

Daemons accept command-line arguments after the filename:

```
launch blinkLedRelease.elf 500
```

To stop a running application:

```
terminate pongGameRelease.elf
```

To remove an installed application:

```
uninstall pongGameRelease.elf
```

---

## 10. Error codes

All Mk API functions return a `T_mkCode`. Always check the return value.

| Code | Meaning |
| --- | --- |
| `K_MK_OK` | Success |
| `K_MK_ERROR_PARAM` | Invalid parameter |
| `K_MK_ERROR_ISR` | Called from an interrupt handler (not allowed) |
| `K_MK_ERROR_RIGHT` | Insufficient privilege level |
| `K_MK_ERROR_TIMEOUT` | Operation timed out |
| `K_MK_ERROR_MALLOC` | Memory allocation failed |
| `K_MK_ERROR_COMM` | Communication error |
| `K_MK_ERROR_CORRUPTED` | Corrupted resource (e.g. FAT cluster table) |
| `K_MK_ERROR_FULL` | Disk full |
| `K_MK_ERROR_NOT_FOUND` | File or resource not found |
| `K_MK_ERROR_WRITE_PROTECT` | Disk is write-protected |
| `K_MK_ERROR_UNEXPECTED` | Unexpected internal error |

---

## See also

- [Build a graphical application](Graphical-Engine) — containers, widgets, painters, listeners
- [Handle input events](Event-System) — full reference for keyboard, mouse, joystick and HID events
- [ELF Loader](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
