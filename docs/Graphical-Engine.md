# Build a graphical application

This page describes how to build a graphical application on top of the Mk engine. It covers the rendering pipeline, the object hierarchy, the application lifecycle, and the low-level drawing API.

---

## Table of contents

1. [Architecture overview](#1-architecture-overview)
2. [Rendering pipeline](#2-rendering-pipeline)
   - 2.1 [Frame buffers and LTDC layers](#21-frame-buffers-and-ltdc-layers)
   - 2.2 [Task model](#22-task-model)
   - 2.3 [Frame loop](#23-frame-loop)
   - 2.4 [Refresh mechanism](#24-refresh-mechanism)
3. [Object hierarchy](#3-object-hierarchy)
   - 3.1 [Factory and containers](#31-factory-and-containers)
   - 3.2 [Fields](#32-fields)
   - 3.3 [Built-in widgets](#33-built-in-widgets)
4. [Application lifecycle](#4-application-lifecycle)
   - 4.1 [Descriptor and metadata](#41-descriptor-and-metadata)
   - 4.2 [Install, launch, close](#42-install-launch-close)
   - 4.3 [Static vs dynamic applications](#43-static-vs-dynamic-applications)
5. [Painter callbacks](#5-painter-callbacks)
   - 5.1 [Signature and context](#51-signature-and-context)
   - 5.2 [Controlling refresh](#52-controlling-refresh)
   - 5.3 [Default painters](#53-default-painters)
6. [Low-level drawing API](#6-low-level-drawing-api)
   - 6.1 [Layers and color format](#61-layers-and-color-format)
   - 6.2 [Primitives](#62-primitives)
   - 6.3 [Text rendering](#63-text-rendering)
   - 6.4 [Bitmap and copy operations](#64-bitmap-and-copy-operations)
7. [Working example](#7-working-example)

---

## 1. Architecture overview

The Mk graphical engine is organized around five permanent system tasks that drive the display independently of application code. Applications do not drive the screen directly: they register objects (fields) into containers, provide painter callbacks, and let the engine call those callbacks at the right moment in the frame cycle.

```
 ┌──────────────────────────────────────────────┐
 │         Application task (user code)         │
 │  install → launch → set attributes → close   │
 └────────────┬────────────────────────┬─────────┘
              │ mk_application_*       │ mk_factory_* / mk_container_*
              ▼                        ▼
 ┌────────────────────────────────────────────────────┐
 │               Handler task (priority 8)            │
 │    processes T_mkDisplayRequest from the mailbox   │
 └──────────────────────────┬─────────────────────────┘
                            │
          ┌─────────────────┴──────────────────┐
          ▼                                    ▼
 ┌─────────────────┐                  ┌─────────────────────┐
 │  Painter tasks  │                  │  Listener tasks     │
 │  priv  (pri 5)  │                  │  priv  (pri 7)      │
 │  unpriv (pri 4) │                  │  unpriv (pri 6)     │
 └────────┬────────┘                  └─────────────────────┘
          │ painter callbacks
          ▼
 ┌──────────────────────────┐
 │  LTDC + DMA2D (ChroMart) │
 │  640×480, ~60 FPS        │
 └──────────────────────────┘
```

All requests sent from application code to the engine transit through the handler's mailbox (`g_mkDisplay.handler.mail`). The public API functions (`mk_application_*`, `mk_container_*`, `mk_factory_*`) simply post `T_mkDisplayRequest` messages to that mailbox and either block (synchronous call, `p_callback == NULL`) or return immediately (asynchronous call with callback).

---

## 2. Rendering pipeline

### 2.1 Frame buffers and LTDC layers

The display hardware is a 640×480 TFT driven by the STM32F74xxx LTDC peripheral. Pixel format is ARGB8888 (4 bytes per pixel). Eight frame buffers are allocated in SDRAM (FMC Bank5), each consisting of two planes:

| Plane | LTDC layer | Constant |
|---|---|---|
| Background | Layer 1 | `K_MK_GRAPHICS_BACKGROUND` = 1 |
| Foreground | Layer 2 | `K_MK_GRAPHICS_FOREGROUND` = 0 |

Each frame buffer pair is represented by `T_mkDisplayFrameBuffer`:

```c
struct T_mkDisplayFrameBuffer {
    uint32_t* addr[2];     /* [FOREGROUND], [BACKGROUND] */
    vuint32_t validity;    /* 1 = ready to display */
    T_mkDisplayFrameBufferStatus status; /* layer enable flags */
    T_mkDisplayFrameBuffer* next;
};
```

The eight buffers form a ring list. Three pointers track the state at any moment:

| Pointer | Owner | Role |
|---|---|---|
| `currentBufferPrinted` | LTDC / VSync ISR | Buffer currently scanned out to the panel |
| `currentBufferUsed` | Painter tasks | Buffer currently being drawn into |
| `currentBufferUpdated` | Handler task | Buffer whose `validity` flag and LTDC addresses are being prepared for display |

The three pointers move through the ring independently and normally point to three different buffers:

- **`currentBufferPrinted`** is the buffer the LTDC hardware is reading right now. Only the VSync ISR advances this pointer (after switching the LTDC layer registers to the next ready buffer).
- **`currentBufferUsed`** is the buffer the painter tasks are actively writing into. The privileged painter advances this pointer at the end of each frame, immediately after posting the `NEXT_FRAME` request to the handler.
- **`currentBufferUpdated`** is the buffer the handler is currently finalizing: it sets `validity = 1` on it (marking it ready to display) and advances this pointer. It therefore always lags one slot behind `currentBufferUsed`.

A buffer is available for painting only when `currentBufferUsed != currentBufferPrinted`. This guarantees that the painter never writes into the buffer currently being displayed. If the painter runs faster than the VSync rate and catches up with `currentBufferPrinted`, it sleeps on `painter.frameEvent` until the ISR wakes it.

The nominal frame rate is derived from the LTDC clock configuration:

```
K_MK_DISPLAY_LTDC_FREQUENCY = 22 750 000 Hz
scanline = HSYNC + HBP + 640 + HFP = 20 + 114 + 640 + 4 = 778 pixels
frame    = (VSYNC + VBP + 480 + VFP) × scanline = (3+2+480+2) × 778 = 378 818 clocks
K_MK_DISPLAY_FRAMERATE = 22 750 000 / 378 818 ≈ 60
```

So the LTDC interrupt fires at approximately 60 Hz. The measured frame rate may be lower when painting takes longer than one VSync interval.

### 2.2 Task model

| Task entry point | Priority | Role |
|---|---|---|
| `mk_display_handler` | 8 | Request processor, ChroMart sequencer |
| `mk_display_listener` | 7 | Privileged listener — routes input events to fields |
| `mk_display_userListener` | 6 | Unprivileged listener — same, for unprivileged containers |
| `mk_display_painter` | 5 | Privileged painter — drives the frame loop |
| `mk_display_userPainter` | 4 | Unprivileged painter — paints unprivileged containers |

The painter at priority 5 is therefore preempted by the handler (priority 8) and both listener tasks (priorities 7 and 6).

### 2.3 Frame loop

The privileged painter executes the following sequence every frame:

```
while (1) {
    if (currentBufferUsed != currentBufferPrinted) {

        mk_display_refreshFields();       // sync object attribute snapshots

        if (factories or criticalContainer not empty) {

            /* 1. Signal unprivileged painter and wait for it to complete */
            mk_event_set(painter.taskEvent, UNPRIVILEGED_PAINTER_FLAG);
            mk_event_wait(painter.taskEvent, PRIVILEGED_PAINTER_FLAG, ...);
            //   └─ unprivileged painter runs mk_factory_paint(&unprivilegedFactory)
            //      and signals back when done

            /* 2. Execute privileged factory painter callbacks */
            mk_semaphore_take(painter.semaphore);
            mk_factory_paint(&privilegedFactory);

            /* 3. Paint the critical container (system overlays) */
            mk_container_paint(criticalContainer);

            /* 4. Paint the frontend container last (mouse cursor — must always be on top) */
            mk_container_paint(frontendContainer);
            mk_semaphore_release(painter.semaphore);

        } else {
            mk_graphics_clear(K_MK_GRAPHICS_FOREGROUND);
        }

        /* 5. Advance buffer pointer and notify handler */
        currentBufferUsed = currentBufferUsed->next;
        mk_display_postRequest(NEXT_FRAME);

    } else {
        /* No free buffer: painter is faster than VSync */
        status.wakeup = 1;
        mk_event_wait(painter.frameEvent, ...);  // sleep until VSync wakes us
    }
}
```

The unprivileged painter runs **first**, concurrently with the privileged painter's semaphore acquisition. Once it finishes and signals back, the privileged painter takes the semaphore, runs its own factory, then the critical container, and finally the frontend container (which holds the mouse cursor and must always be drawn last).

The VSync ISR (`mk_display_frameInterrupt`) fires at each LTDC vertical blank:

1. Checks if the next buffer in the ring has `validity == 1`.
2. If so, writes its address pair to the LTDC layer registers and calls `ltdc_loadLayers(K_LTDC_IMMEDIATE)`.
3. Clears `validity` on the newly displayed buffer (making it available for painting again).
4. If `status.wakeup == 1`, wakes the painter via `mk_event_set(painter.frameEvent, ...)`.

The handler task receives the `NEXT_FRAME` request posted by the painter, sets `validity = 1` on `currentBufferUpdated`, and advances that pointer.

### 2.4 Refresh mechanism

Each `T_mkField` carries a `refresh` counter and a `userRefresh` counter. The engine counter is initialized to `K_MK_FIELD_REFRESH_ENABLED = K_MK_DISPLAY_FRAME_BUFFER_NUMBER = 8`. On every frame, the painter decrements it. When it reaches zero, the painter stops calling that field's painter callback.

The rationale: with 8 frame buffers in the ring, a field must be painted at least 8 consecutive frames to ensure that every buffer in the ring contains the updated image. After that, re-painting every frame is wasteful for static content.

To force a repaint (e.g. after updating an object's data), call:

```c
mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_ENABLED);
```

This resets the counter to 8 and restarts painting for that field. To permanently disable painting:

```c
mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_DISABLED);  /* = 0 */
```

The `userRefresh` counter follows the same logic but is controlled exclusively by application code, independently of the engine counter.

---

## 3. Object hierarchy

### 3.1 Factory and containers

The top of the display hierarchy consists of two **factory** lists:

```c
struct T_mkFactory {
    T_mkContainer* first;
    T_mkContainer* last;
};
```

`g_mkDisplay.privilegedFactory` and `g_mkDisplay.unprivilegedFactory` each hold an ordered list of containers sorted by `zIndex`. A container at a higher `zIndex` is painted after containers with lower values, appearing on top.

A **container** (`T_mkContainer`) is the direct owner of a list of fields. It also holds the listener callback invoked by the engine when an input event targets any field it owns, and a reference to the `T_mkApplication` that created it.

```c
struct T_mkContainer {
    uint32_t type;          /* K_MK_TYPE_PRIVILEGED or K_MK_TYPE_DEFAULT */
    uint32_t zIndex;
    T_mkAddr factory;
    T_mkAddr owner;         /* T_mkApplication* */
    T_mkField* first;
    T_mkField* last;
    T_mkListener listener;  /* container-level event callback */
    T_mkContainer* next;
    T_mkContainer* previous;
};
```

Creating and registering a container is done through the engine's request mailbox:

```c
T_mkContainer* myContainer;

/* Synchronous create — blocks until the handler completes */
mk_container_create(&myContainer, zIndex, myListener, K_MK_NULL);

/* Register in the factory */
mk_factory_addContainer(myContainer, K_MK_NULL);
```

To remove a container from display without destroying it:

```c
mk_factory_removeContainer(myContainer, K_MK_NULL);
```

To destroy it entirely, the container **must first be removed from the factory** before being deleted. Deleting a container that is still registered in the factory results in undefined behavior since the painter tasks may still hold a reference to it:

```c
/* Step 1: remove from factory */
mk_factory_removeContainer(myContainer, K_MK_NULL);
/* Step 2: then destroy */
mk_container_delete(myContainer, K_MK_NULL);
```

### 3.2 Fields

`T_mkField` is the base type for every graphical object. It is always the **first member** of all widget structs, enabling safe upcasting between any widget pointer and `T_mkField*`.

```c
struct T_mkField {
    uint32_t focus;         /* K_MK_FIELD_STATE_IDLE / K_MK_FIELD_STATE_FOCUS */
    uint32_t cursor;        /* K_MK_FIELD_CURSOR_OUTSIDE / K_MK_FIELD_CURSOR_INSIDE */
    uint32_t refresh;       /* engine-managed refresh counter */
    uint32_t userRefresh;   /* user-managed refresh counter */
    uint32_t visibility;    /* K_MK_FIELD_VISIBLE / K_MK_FIELD_INVISIBLE */
    uint32_t userVisibility;
    uint32_t activity;      /* K_MK_FIELD_ACTIF / K_MK_FIELD_INACTIF */
    uint32_t layer;         /* K_MK_GRAPHICS_FOREGROUND / K_MK_GRAPHICS_BACKGROUND */
    uint32_t zIndex;
    uint32_t frameNumber;   /* index of the frame currently being painted */
    T_mkVect2D position;    /* {real32_t x, real32_t y} in pixels */
    T_mkFieldDimension dimension; /* {uint32_t width, uint32_t height} */
    T_mkListener listener;  /* field-level event callback */
    T_mkPainter painter;    /* paint callback */
    T_mkAddr child;         /* pointer back to the owning widget (upcast handle) */
    T_mkField* next;
    T_mkField* previous;
};
```

Key field attributes:

| Attribute | Values | Effect |
|---|---|---|
| `visibility` | `K_MK_FIELD_VISIBLE` / `INVISIBLE` | Enables or disables the painter callback |
| `activity` | `K_MK_FIELD_ACTIF` / `INACTIF` | Enables or disables the listener callback |
| `layer` | `K_MK_GRAPHICS_FOREGROUND` / `BACKGROUND` | Which LTDC layer to draw on |
| `zIndex` | 0 – 0xFFFFFFFF | Paint order within the container |
| `focus` | `STATE_IDLE` / `STATE_FOCUS` | Set automatically by the listener on mouse click |
| `cursor` | `CURSOR_OUTSIDE` / `CURSOR_INSIDE` | Set automatically when the mouse enters or leaves the field |

Adding a field to a container:

```c
mk_container_addField(myContainer, &myWidget.field, K_MK_NULL);
```

### 3.3 Built-in widgets

All built-in widgets follow the same pattern: a `T_mkField field` as first member, a `T_mkAddr child` pointing back to the widget, and type-specific data.

| Type | Description |
|---|---|
| `T_mkScreen` | Full-screen solid color background; `mk_screen_defaultPainter` fills the target layer |
| `T_mkLayer` | Controls the alpha transparency of the foreground and background LTDC layers |
| `T_mkTextField` | Displays a UTF-8/UTF-16/UTF-32 string with a configurable `T_mkTextStyle`; optional background and border |
| `T_mkEditField` | `T_mkTextField` with keyboard editing: blinking cursor, insert/overwrite modes, `mk_editField_defaultListener` handles all keystrokes |
| `T_mkButtonImage` | Clickable button that displays a BMP bitmap and an optional text label; `mk_buttonImage_defaultPainter` renders both |
| `T_mkFigure` | Generic field with only a custom painter; used for arbitrary drawing |
| `T_mkProgressBar` | Horizontal progress bar with configurable foreground/background colors, border, and percentage text |
| `T_mkGraph2D` | 2D line graph over a configurable data array |
| `T_mkConsole` | Two-field composite (prompt + output window), local echo, keyboard focus management |

Initialization follows the same pattern for every widget:

```c
T_mkTextField myLabel;

mk_textField_init(&myLabel);
mk_textField_setPosition(&myLabel, 10.0f, 20.0f);
mk_textField_setDimension(&myLabel, 200, 30);
mk_textField_setLayer(&myLabel, K_MK_GRAPHICS_FOREGROUND);
mk_textField_setZIndex(&myLabel, 1);
mk_textField_setVisibility(&myLabel, K_MK_FIELD_VISIBLE);
mk_textField_setActivity(&myLabel, K_MK_FIELD_INACTIF);
mk_textField_setPainter(&myLabel, mk_textField_defaultPainter);
mk_textField_setString(&myLabel, (T_str8) "Hello, world!");
mk_textField_setStyle(&myLabel, &myTextStyle);

mk_container_addField(myContainer, &myLabel.field, K_MK_NULL);
```

---

## 4. Application lifecycle

### 4.1 Descriptor and metadata

Every application is described by a `T_mkApplicationDescriptor` and an optional `T_mkApplicationMetadata`:

```c
typedef struct T_mkApplicationDescriptor {
    uint8_t type;      /* K_MK_APPLICATION_TYPE_STATIC, _DYNAMIC, or _DAEMON */
    uint8_t taskType;  /* task privilege level */
    uint8_t gfxPage;   /* K_MK_TRUE: allocate a 640×480×4 byte SDRAM page */
    /* ... stack size, priority, entry point ... */
} T_mkApplicationDescriptor;

typedef struct T_mkApplicationMetadata {
    T_str8 name;
    T_str8 author;
    T_str8 version;
    T_str8 description;
    T_str8 iconPath;   /* path to a BMP icon file */
    T_mkAddr iconAddr; /* load address of the icon in memory */
} T_mkApplicationMetadata;
```

The `gfxPage` field is significant: when set to `K_MK_TRUE`, the engine reserves one 640×480×4 byte block (one full frame buffer worth of SDRAM) for the application's private use. This block can hold a pre-rendered background, a sprite sheet, or any large pixel buffer.

Up to 16 applications can be installed simultaneously (`K_MK_DISPLAY_APPLICATION_NUMBER = 16`).

### 4.2 Install, launch, close

The application API works entirely through the handler mailbox. Every function takes a `T_mkCallback* p_callback` parameter:

- If `p_callback == K_MK_NULL` the call **blocks** until the handler completes the request.
- If `p_callback != K_MK_NULL` the call returns immediately and the callback is invoked on completion with the result code and the application pointer.

```c
/* Install: registers the application with the engine */
T_mkApplication* myApp = K_MK_NULL;
mk_application_install(&myApp, &myDescriptor, &myMetadata, K_MK_NULL);

/* Launch: creates the application task and starts execution */
mk_application_launch(myApp, K_MK_NULL);

/* Close: requests graceful shutdown; the application task is given
   a chance to clean up before being destroyed */
mk_application_close(myApp, K_MK_NULL);

/* Terminate: forceful shutdown without cleanup */
mk_application_terminate(myApp, K_MK_NULL);

/* Uninstall: removes the application from the registry and frees
   its memory (after a 1-frame garbage-collection delay) */
mk_application_uninstall(myApp, K_MK_NULL);
```

The **garbage collector** (`mk_application_delete`) runs once per frame inside the painter loop. It waits one full frame cycle (`K_MK_DISPLAY_APPLICATION_ELAPSE_TIMEOUT = 1`) before freeing an application's SDRAM page, ensuring that no painter callback is still executing against that memory when it is released.

### 4.3 Static vs dynamic applications

**Static applications** (`K_MK_APPLICATION_TYPE_STATIC`) are linked into the firmware at build time. Their descriptor and entry point are known at link time.

**Dynamic applications** (`K_MK_APPLICATION_TYPE_DYNAMIC`) are loaded from a file stored on a mass storage device. The engine reads the file, verifies the magic number `0x44594E41`, and relocates the application to the SDRAM application pool:

```c
mk_application_installDynamic(&myApp, "/apps/myapp.bin",
                               K_MK_NULL, myVolume, K_MK_NULL);
```

Command-line arguments can be passed to a dynamic application via the file path parameter and retrieved at runtime with `mk_application_getCmdLine` / `mk_application_getArgv`.

For a detailed description of the ELF loading and relocation process, refer to the [ELF Loader](ELF-Loader) wiki page.

**Daemon applications** (`K_MK_APPLICATION_TYPE_DAEMON`) run in the background and are not visible in the application launcher.

---

## 5. Painter callbacks

### 5.1 Signature and context

A painter callback has the following signature:

```c
T_mkCode myPainter(T_mkContainer* p_container,
                   T_mkField*     p_field,
                   uint32_t       p_frameNumber);
```

- `p_container`: the container that owns the field being painted.
- `p_field`: the field being painted. The widget pointer is obtained by `p_field->child`.
- `p_frameNumber`: index of the current frame in the ring buffer, ranging from 0 to `K_MK_DISPLAY_FRAMERATE - 1`.

The callback is invoked by the painter task (either privileged or unprivileged, depending on the container type). It must not block and must not take semaphores that could deadlock with the engine. All `mk_graphics_*` calls are legal inside a painter callback.

The owning application is retrieved via the container:

```c
T_mkApplication* app = mk_container_getOwner(p_container);
MyAppState* state = (MyAppState*) mk_application_getArg(app);
```

### 5.2 Controlling refresh

A painter should disable its own refresh counter once it has rendered static content that will not change:

```c
T_mkCode myStaticPainter(T_mkContainer* p_container,
                         T_mkField* p_field, uint32_t p_frameNumber)
{
    T_mkCode result;
    T_mkMyWidget* widget = (T_mkMyWidget*) p_field->child;

    /* Draw the widget */
    result = mk_graphics_drawRect(p_field->layer, K_MK_GRAPHICS_SOLID,
                                  p_field->position,
                                  /* bottom-right corner */ ...,
                                  widget->color);

    /* Stop repainting once all frame buffers are up to date */
    mk_field_setRefresh(p_field, K_MK_FIELD_REFRESH_DISABLED);

    return result;
}
```

When the widget's data changes (e.g. a new color is set), the setter must re-enable refresh:

```c
void myWidget_setColor(T_mkMyWidget* widget, uint32_t color)
{
    widget->color = color;
    mk_field_setRefresh(&widget->field, K_MK_FIELD_REFRESH_ENABLED);
}
```

### 5.3 Default painters

Every built-in widget ships a ready-to-use default painter that handles the common rendering cases. These can be used directly or called from a custom painter to add decorations:

| Widget | Default painter |
|---|---|
| `T_mkScreen` | `mk_screen_defaultPainter` |
| `T_mkLayer` | `mk_layer_defaultPainter` |
| `T_mkTextField` | `mk_textField_defaultPainter` |
| `T_mkEditField` | `mk_editField_defaultPainter` |
| `T_mkButtonImage` | `mk_buttonImage_defaultPainter` (image) / `mk_buttonImage_defaultTextPainter` (image + label) |
| `T_mkProgressBar` | `mk_progressBar_defaultPainter` |

---

## 6. Low-level drawing API

All `mk_graphics_*` functions write directly into the frame buffer currently allocated for painting (`currentBufferUsed`). They are valid inside a painter callback regardless of whether the callback runs in a privileged or unprivileged context. Colors are specified as a packed `uint32_t` ARGB8888 value or as a `T_mkARGB` struct.

### 6.1 Layers and color format

```c
/* Layers */
#define K_MK_GRAPHICS_FOREGROUND  0   /* LTDC Layer 2 */
#define K_MK_GRAPHICS_BACKGROUND  1   /* LTDC Layer 1 */

/* Pixel formats */
#define K_MK_GRAPHICS_ARGB8888    0x00000000
#define K_MK_GRAPHICS_RGB888      0x00000001
#define K_MK_GRAPHICS_RGB565      0x00000002
#define K_MK_GRAPHICS_ARGB1555    0x00000003
#define K_MK_GRAPHICS_ARGB4444    0x00000004

/* Color as struct */
typedef struct T_mkARGB { uint8_t b, g, r, a; } T_mkARGB;

/* Color as packed uint32: 0xAARRGGBB */
```

### 6.2 Primitives

All coordinates are passed as `T_mkVect2D { real32_t x, y }`.

```c
/* Fill entire layer with a solid color */
T_mkCode mk_graphics_fill(uint32_t layer, uint32_t argb);

/* Clear layer to transparent black */
T_mkCode mk_graphics_clear(uint32_t layer);

/* Set LTDC global alpha for a layer (0–255) */
T_mkCode mk_graphics_setAlpha(uint32_t layer, uint8_t alpha);

/* Single pixel */
T_mkCode mk_graphics_drawPixel(uint32_t layer, T_mkVect2D v, uint32_t argb);

/* Axis-aligned rectangle — state: K_MK_GRAPHICS_SOLID or K_MK_GRAPHICS_EMPTY */
T_mkCode mk_graphics_drawRect(uint32_t layer, uint32_t state,
                               T_mkVect2D v1, T_mkVect2D v2, uint32_t argb);

/* Rectangle with rounded corners */
T_mkCode mk_graphics_drawRoundRect(uint32_t layer, uint32_t state,
                                    T_mkVect2D v1, T_mkVect2D v2,
                                    real32_t radius, uint32_t argb);

/* Line segment between v1 and v2 */
T_mkCode mk_graphics_drawLine(uint32_t layer,
                               T_mkVect2D v1, T_mkVect2D v2, uint32_t argb);

/* Circle — state: K_MK_GRAPHICS_SOLID or K_MK_GRAPHICS_EMPTY */
T_mkCode mk_graphics_drawCircle(uint32_t layer, uint32_t state,
                                 T_mkVect2D center, real32_t radius, uint32_t argb);

/* Filled triangle */
T_mkCode mk_graphics_drawTriangle(uint32_t layer,
                                   T_mkVect2D v1, T_mkVect2D v2, T_mkVect2D v3,
                                   uint32_t argb);
```

### 6.3 Text rendering

Text is rendered into a bounding box defined by two corners. The `T_mkTextStyle` structure controls font, encoding, alignment, margins, and color.

```c
typedef struct T_mkTextStyle {
    T_mkFont*         font;
    T_mkFontUnicode   fontEncoding;        /* K_MK_FONT_ASCII, UTF8, UTF16, UTF32 */
    T_mkTextAlignment verticalAlignment;   /* TOP, CENTER, DOWN */
    T_mkTextAlignment horizontalAlignment; /* LEFT, CENTER, RIGHT */
    uint32_t marginTop, marginBottom, marginRight, marginLeft;
    T_mkARGB color;
} T_mkTextStyle;

T_mkCode mk_graphics_drawString(uint32_t layer,
                                 T_mkVect2D v1, T_mkVect2D v2,
                                 T_str8 string,
                                 T_mkTextStyle* style,
                                 T_mkTextCursor* cursor); /* NULL for static text */
```

Two system fonts are available at all times:

- `g_mkDisplay.defaultFont` — proportional font.
- `g_mkDisplay.defaultFixedFont` — monospaced font.

Both cover Basic Latin, Latin-1 Supplement, Latin Extended A/B, General Punctuation, Mathematical Operators, Currency Symbols, and Arrows.

### 6.4 Bitmap and copy operations

```c
/* Draw a raw ARGB8888 bitmap array of p_column × p_row pixels at position v1 */
T_mkCode mk_graphics_drawBitmap(uint32_t layer, uint32_t* bitmap,
                                 T_mkVect2D v1,
                                 uint32_t columns, uint32_t rows);

/* Copy a rectangular region with identical pixel formats */
T_mkCode mk_graphics_copy(T_mkAddr src, T_mkVect2D dst, uint32_t direction,
                           uint32_t layer, uint32_t width, uint32_t height);

/* Copy a rectangular region with automatic pixel format conversion */
T_mkCode mk_graphics_invcopy(T_mkAddr src, T_mkVect2D dst, uint32_t direction,
                              uint32_t layer, uint32_t width, uint32_t height);

/* Plot a data graph between v1 and v2 from an address holding sample data */
T_mkCode mk_graphics_plot(uint32_t layer, T_mkVect2D v1, T_mkVect2D v2,
                           uint32_t type, T_mkAddr data);
```

The `direction` parameter for both copy functions controls DMA2D transfer direction: `K_MK_GRAPHICS_ADDR_TO_FRAME` copies from a memory address into the frame buffer; `K_MK_GRAPHICS_FRAME_TO_ADDR` copies from the frame buffer back to memory (useful for screen capture).

`mk_graphics_copy` performs a direct memory-to-memory transfer and assumes that the source pixel format already matches the frame buffer format.

`mk_graphics_invcopy` performs the same transfer but **with automatic pixel format conversion** via DMA2D's Pixel Format Converter (PFC).

---

## 7. Working example

The sketch below shows a minimal application that draws a single `T_mkTextField` rendered by the built-in default painter, with no custom painter or listener.

```c
/* Application state */
typedef struct {
    T_mkContainer* container;
    T_mkScreen background;
    T_mkTextField label;
} T_mkMyApp;

static T_mkMyApp g_myApp;

/* ------------------------------------------------------------------ */
/* Application entry point                                             */
/* ------------------------------------------------------------------ */

void myApp_main(T_mkAddr arg)
{
    T_mkMyApp* app = &g_myApp;
    (void) arg;

    /* font=NULL uses the engine default font, marginLeft=20, color=opaque red */
    T_mkTextStyle l_style = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED,
                               0, 0, 0, 20, { 0x00, 0x00, 0xFF, 0xFF } };

    /* --- Container (no listener) --- */
    mk_container_create(&app->container, 0, K_MK_NULL, K_MK_NULL);

    /* --- Background screen --- */
    mk_screen_init(&app->background);
    mk_screen_setPosition(&app->background, 0.0f, 0.0f);
    mk_screen_setDimension(&app->background, 640, 480);
    mk_screen_setLayer(&app->background, K_MK_GRAPHICS_FOREGROUND);
    mk_screen_setZIndex(&app->background, 0);
    mk_screen_setVisibility(&app->background, K_MK_FIELD_VISIBLE);
    mk_screen_setActivity(&app->background, K_MK_FIELD_INACTIF);
    mk_screen_setPainter(&app->background, K_MK_NULL);
    mk_container_addField(app->container, &app->background.field, K_MK_NULL);

    /* --- Label --- */
    mk_textField_init(&app->label);
    mk_textField_setPosition(&app->label, 200.0f, 220.0f);
    mk_textField_setDimension(&app->label, 240, 40);
    mk_textField_setLayer(&app->label, K_MK_GRAPHICS_FOREGROUND);
    mk_textField_setZIndex(&app->label, 0);
    mk_textField_setVisibility(&app->label, K_MK_FIELD_VISIBLE);
    mk_textField_setActivity(&app->label, K_MK_FIELD_INACTIF);
    mk_textField_setPainter(&app->label, mk_textField_defaultPainter);
    mk_textField_setStyle(&app->label, &l_style);
    mk_textField_setString(&app->label, (T_str8) "Hello, world!");
    mk_container_addField(app->container, &app->label.field, K_MK_NULL);

    /* --- Register container in the factory --- */
    mk_factory_addContainer(app->container, K_MK_NULL);

    /* Application event loop */
    while (1) {
        mk_task_sleep(100);
    }
}
```

`T_mkTextStyle` fields in order: `font`, `fontEncoding`, `verticalAlignment`, `horizontalAlignment`, `marginTop`, `marginBottom`, `marginRight`, `marginLeft`, `color` (`T_mkARGB` as `{ b, g, r, a }`). Passing `K_MK_NULL` for `font` instructs the default painter to fall back to the engine's built-in font (`g_mkDisplay.defaultFont`).

---

## See also

- [Writing your first application](Writing-Your-First-Application) — step-by-step guide from descriptor to running application
- [Handle input events](Event-System) — full reference for keyboard, mouse, joystick and HID events
- [ELF Loader](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
