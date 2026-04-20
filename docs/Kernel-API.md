# Kernel internals

This page describes the internal mechanisms of the Mk kernel: the three hardware
interrupts that drive it, the task list structures, the preemption mechanism, the
callback manager, and the public API exposed to applications and ISRs.

---

## Table of contents

1. [Overview](#1-overview)
2. [Interrupt priorities](#2-interrupt-priorities)
3. [Scheduler structure — g_mkScheduler](#3-scheduler-structure--g_mkscheduler)
   - 3.1 [Task lists](#31-task-lists)
4. [The four scheduler lists](#4-the-four-scheduler-lists)
   - 4.1 [Ready lists — readyList\[\]](#41-ready-lists--readylist)
   - 4.2 [Delay list — delayList](#42-delay-list--delaylist)
   - 4.3 [Suspend list — suspendList](#43-suspend-list--suspendlist)
   - 4.4 [Blocked lists — embedded in synchronisation objects](#44-blocked-lists--embedded-in-synchronisation-objects)
5. [System tick](#5-system-tick)
   - 5.1 [Frequency](#51-frequency)
   - 5.2 [What SysTick does on each tick](#52-what-systick-does-on-each-tick)
   - 5.3 [What PendSV does (context switch)](#53-what-pendsv-does-context-switch)
6. [Preemption and context switch](#6-preemption-and-context-switch)
   - 6.1 [How a context switch is triggered](#61-how-a-context-switch-is-triggered)
   - 6.2 [Cortex-M7 dual execution modes](#62-cortex-m7-dual-execution-modes)
7. [Priority inheritance (mutex)](#7-priority-inheritance-mutex)
8. [System call mechanics (SVC)](#8-system-call-mechanics-svc)
9. [Public API](#9-public-api)
   - 9.1 [Kernel lifecycle](#91-kernel-lifecycle)
   - 9.2 [Tasks](#92-tasks)
   - 9.3 [Memory pools](#93-memory-pools)
   - 9.4 [Mutexes](#94-mutexes)
   - 9.5 [Semaphores](#95-semaphores)
   - 9.6 [Event fields](#96-event-fields)
   - 9.7 [Mailboxes](#97-mailboxes)
   - 9.8 [Callback manager](#98-callback-manager)
10. [CPU load measurement](#10-cpu-load-measurement)
11. [Configurable constants](#11-configurable-constants)

---

## 1. Overview

The Mk kernel is a fixed-priority preemptive RTOS. It is driven entirely by three ARM
Cortex-M7 exceptions:

| Exception | Role |
| --- | --- |
| **SysTick** | System clock — advances the tick counter and triggers PendSV |
| **PendSV** | Performs the actual context switch: wakes timed-out tasks, advances the round-robin pointer, saves and restores registers |
| **SVC** | System call gate — every task interaction with the kernel goes through this exception |

---

## 2. Interrupt priorities

The Cortex-M7 represents exception priorities on 4 bits (0 = highest, 15 = lowest).
Priorities are configured at startup inside `mk_init()`:

```c
/* mk_scheduler_constants.h */
#define K_MK_SCHEDULER_BASE_PRIORITY  15   /* SysTick and PendSV */
#define K_MK_SCHEDULER_SVC_PRIORITY    7   /* SVC = MASK_PRIORITY - 1 */
#define K_MK_SCHEDULER_MASK_PRIORITY   8   /* BASEPRI threshold used in critical sections */
```

**Why is SVC higher priority than SysTick and PendSV?**

A system call issued from an ISR must execute immediately, without waiting for an
ongoing SysTick to complete. SVC at priority 7 can therefore preempt SysTick (15) and
PendSV (15). Conversely, neither SysTick nor PendSV can preempt an active SVC handler.

**Why do SysTick and PendSV share the same priority?**

PendSV is designed to run last, after all application ISRs have completed. By assigning
it the same (lowest) priority as SysTick, the context switch is always deferred until
every higher-priority interrupt has finished. SysTick and PendSV do not preempt each
other — if SysTick pends PendSV, PendSV runs on return from SysTick.

**Critical section — BASEPRI register**

The Cortex-M7 BASEPRI register blocks all interrupts whose numeric priority is greater
than or equal to the value written. The Mk kernel uses BASEPRI instead of PRIMASK
(which would block everything, including SVC) to implement fine-grained critical
sections.

`_mk_scheduler_mask()` and `_mk_scheduler_unmask()` are **dedicated to interrupt
context**. Their purpose is to prevent a higher-priority ISR from preempting another
ISR that is already executing a system call, which would corrupt the shared
`g_mkSVCObject` structure. When executed from an unprivileged Thread mode task, the
`MSR BASEPRI` instruction is **ignored** per the ARM v7-M architecture specification —
these functions have no effect in that context.

The consequence of this design on ISR system calls:

- **ISRs at priority 8–15** (≥ `K_MK_SCHEDULER_MASK_PRIORITY`) can safely issue
  system calls. When such an ISR calls `_mk_scheduler_mask(K_MK_SCHEDULER_SVC_PRIORITY)`,
  BASEPRI is raised to mask any ISR of equal or lower priority (8–15), preventing
  concurrent access to `g_mkSVCObject`.
- **ISRs at priority 0–7** (< `K_MK_SCHEDULER_MASK_PRIORITY`) **cannot issue system
  calls safely**. Because BASEPRI cannot be raised above the current execution level,
  another ISR at priority 0–7 could preempt mid-call and overwrite the shared
  `g_mkSVCObject`, causing corruption.

The effect of `BASEPRI = 7` on each exception class during a critical section:

| Exception | Priority | Masked by BASEPRI = 7? |
| --- | --- | --- |
| SVC | 7 | **No** — equal value is not masked; only strictly greater values are blocked |
| User ISRs (priority < 8) | 0–7 | **No** — not blocked |
| User ISRs (priority ≥ 8) | 8–15 | **Yes** — blocked |
| SysTick | 15 | **Yes** — blocked |
| PendSV | 15 | **Yes** — blocked |

The previous BASEPRI value is saved before each `_mk_scheduler_mask()` call and
restored by `_mk_scheduler_unmask()`. Critical sections are therefore safely nestable.

---

## 3. Scheduler structure — `g_mkScheduler`

The scheduler is a single global structure residing in privileged memory:

```c
/* mk_scheduler_types.h */
struct T_mkScheduler
{
    T_mkTask*  currentTask;                               /* currently running task */
    T_mkList   readyList[K_MK_SCHEDULER_PRIORITY_NUMBER + 1]; /* per-priority ready lists */
    T_mkList   delayList;                                 /* sleeping tasks, sorted by expiry */
    T_mkList   suspendList;                               /* explicitly suspended tasks */
    T_mkStatus statusRegister;                            /* kernel state flags */
    uint32_t   priorityRegister;                          /* bitmap of non-empty ready lists */
    uint32_t   tickRegister;                              /* system tick counter */
    uint32_t   taskCounter;                               /* number of allocated tasks */
    T_mkLoad   load;                                      /* CPU load computation data */
    T_mkTask   idle;                                      /* idle task descriptor */
    T_mkTask   main;                                      /* main task descriptor */
};
```

### 3.1 Task lists

Each `T_mkList` contains a single `current` pointer to the head of a doubly-linked
circular list. Tasks embed their chain pointers directly in their control block
(`T_mkTask`) — no separate node allocation is needed.

```
Doubly-linked circular list (example: readyList[3])

  current
     │
     ▼
  ┌──────┐  next  ┌──────┐  next  ┌──────┐
  │  A   │───────▶│  B   │───────▶│  C   │──┐
  │      │◀───────│      │◀───────│      │  │ (→ wraps back to A)
  └──────┘ prev   └──────┘ prev   └──────┘◀─┘
```

Each task has **two independent sets** of chain pointers, indexed by
`K_MK_LIST_TASK` (0) and `K_MK_LIST_SYNC` (1). The same task can therefore appear
simultaneously in the delay list (via `K_MK_LIST_TASK`) and in the blocked list of a
synchronisation object (via `K_MK_LIST_SYNC`) without any pointer conflicts.

---

## 4. The four scheduler lists

### 4.1 Ready lists — `readyList[]`

There are `K_MK_SCHEDULER_PRIORITY_NUMBER + 1 = 11` ready lists. Index 0 is reserved
for the idle task. Indices 1 to 10 correspond to user priority levels, where **10 is
the highest priority** and **1 is the lowest**. This convention is the inverse of the
ARM hardware priority numbering: a higher numeric value means a higher scheduling
priority in Mk.

Tasks at the same priority level are scheduled in **round-robin**: `mk_list_add`
always inserts at the tail of the circular list. At the next context switch, if the
task is not locked, the `current` pointer advances by one position.

```
readyList[3] — priority level 3 (three tasks, round-robin)

  current
     │
     ▼
  ┌──────┐       ┌──────┐       ┌──────┐
  │  T1  │──────▶│  T2  │──────▶│  T3  │──┐
  │(run) │       │(next)│       │      │  │
  └──────┘◀──────└──────┘◀──────└──────┘◀─┘
  Next context switch (if unlocked): current = T2
```

**Priority register (`priorityRegister`)**

To avoid scanning all lists at every context switch, the kernel maintains a 32-bit
bitmap where bit N−1 is set whenever at least one task is present in `readyList[N]`.
PendSV uses the `CLZ` (Count Leading Zeros) instruction on this register to instantly
find the index of the highest-priority non-empty list: the highest set bit corresponds
to the highest active priority level.

```
priorityRegister = 0b...00000101
                           ││
                           │└── bit 0: readyList[1] non-empty (priority level 1, lowest)
                           └─── bit 2: readyList[3] non-empty (priority level 3)
```

### 4.2 Delay list — `delayList`

Used by `mk_task_sleep()` and `mk_task_delay()`, and internally by synchronisation
objects that support a timeout.

**Sorted by ascending timeout**: `mk_list_addTimeout` inserts each task at the correct
position according to `tick.timeout`, so the list head is always the next task to
expire. PendSV only needs to compare `delayList.current->tick.timeout` against
`tickRegister` — no full traversal is required.

```
delayList (head = nearest expiry)

 current
    │
    ▼  timeout=102    timeout=105    timeout=110
  ┌────┐ ──────────▶ ┌────┐ ──────▶ ┌────┐
  │ T5 │             │ T2 │          │ T7 │ ...
  └────┘             └────┘          └────┘
```

### 4.3 Suspend list — `suspendList`

Contains tasks explicitly suspended by `mk_task_suspend()`. They do not participate
in scheduling and their timeouts do not expire. They leave this list only via
`mk_task_resume()`.

### 4.4 Blocked lists — embedded in synchronisation objects

Each mutex, semaphore, mailbox or event field owns its own blocked list, chained
through the `K_MK_LIST_SYNC` pointers of `T_mkTask`. It is **sorted by descending
priority** (`mk_list_addPriority`): the `current` pointer always points to the
highest-priority task waiting for the object, which guarantees it will be unblocked
first. Tasks with equal priority are ordered by insertion time within the same
priority level.

---

## 5. System tick

### 5.1 Frequency

The SysTick period is configurable at `mk_start()` call time. In practice, Mk runs
at **1 tick = 1 ms**.

### 5.2 What SysTick does on each tick

SysTick is intentionally minimal:

1. Increments `g_mkScheduler.tickRegister`.
2. Pends PendSV (`nvic_setPendingException(K_NVIC_PENDING_PENDSV)`).

All other scheduling work — waking timed-out tasks and advancing the round-robin
pointer — is performed inside PendSV when it executes after SysTick returns.

### 5.3 What PendSV does (context switch)

PendSV is the true workhorse of the scheduler. In addition to saving and restoring
task registers, it:

1. Calls `mk_scheduler_wake()`: removes from `delayList` all tasks whose
   `tick.timeout == tickRegister`, moves them back to their respective `readyList`,
   and updates `priorityRegister`.
2. Reads `priorityRegister` (via `CLZ`) to find the highest-priority non-empty
   `readyList`.
3. Loads `readyList[best].current` as the new task and writes it to `currentTask`.
4. If the `locked` flag in `statusRegister` is **clear**, advances the `current`
   pointer in that same list by one position (round-robin step **within the selected
   priority level only**).
5. Clears the `locked` flag.
6. Loads the task pointed to by the updated `current`, saves the outgoing context
   and restores the incoming context.

**The `locked` flag** is set to 1 whenever a context switch is triggered explicitly
(yield, sleep, block, or by SVC at the end of a system call). It prevents PendSV from
advancing the `current` pointer within the elected priority level — guaranteeing that
the task at the head of that list runs for at least one full tick before the round-robin
moves to the next task at the same priority. Tasks at a different (higher) priority are
unaffected: they are selected by the `priorityRegister` / CLZ path before the lock is
even consulted.

---

## 6. Preemption and context switch

### 6.1 How a context switch is triggered

A context switch is always triggered by pending PendSV:

```c
void mk_scheduler_pend(uint32_t p_mkStatus)
{
    if (p_mkStatus == K_MK_ISR_NO)
        _mk_scheduler_unmask(K_MK_SCHEDULER_IDLE_PRIORITY); /* unmask everything */

    g_mkScheduler.statusRegister.locked = 1;
    nvic_setPendingException(K_NVIC_PENDING_PENDSV);
}
```

It is triggered from two paths:
- **SysTick**: automatically every tick (periodic preemption).
- **SVC**: at the end of a system call that modifies the lists (sleep, block, creation
  of a higher-priority task, release of an object that unblocks a higher-priority
  task…).

### 6.2 Cortex-M7 dual execution modes

The kernel exploits the ARM distinction between **Handler mode** (interrupts) and
**Thread mode** (tasks):

- Tasks run in **Thread mode** using the Process Stack Pointer (PSP).
- Handlers (SysTick, PendSV, SVC) run in **Handler mode** using the Main Stack
  Pointer (MSP).

Each task owns its own PSP pointing to the top of its dedicated stack. A context
switch reduces to exchanging PSP values.

---

## 7. Priority inheritance (mutex)

Priority inheritance applies to mutexes only. It resolves priority inversion: if a
high-priority task T_H is blocked on a mutex held by a low-priority task T_L, T_L
temporarily receives the priority of T_H.

**Inheritance (`mk_call_inherit`)**: triggered when T_H fails to take the mutex. The
kernel raises T_L's `currentPriority` and moves it to the appropriate `readyList` (or
to the blocked list if T_L is itself blocked).

**Disinheritance (`mk_call_disinherit`)**: triggered when T_L releases the mutex or
when T_H's timeout expires. T_L's `currentPriority` is lowered back to its base
priority (or to the priority of the next task waiting on the mutex, if any remain).

Each task maintains two separate priority fields:

| Field | Meaning |
| --- | --- |
| `attribute.priority` | Base priority, set at creation, never changed by the kernel |
| `attribute.currentPriority` | Effective priority, may be raised by inheritance |

The scheduler always uses `currentPriority` for all list operations.

---

## 8. System call mechanics (SVC)

Every public kernel function that modifies task or synchronisation object state goes
through the same mechanism.

### Step 1 — Build the SVC object

```c
/* Simplified excerpt from mk_task_sleep() */
T_mkSVCObject l_svc;
l_svc.type                       = K_MK_SYSCALL_SLEEP_FUNCTION;
l_svc.data[K_MK_OFFSET_TICK]    = (T_mkAddr) p_tick;
l_svc.data[K_MK_OFFSET_TIMEOUT] = (T_mkAddr)(g_mkScheduler.tickRegister + p_tick);
```

### Step 2 — Route via `mk_svc_set()`

`mk_svc_set()` detects whether the call originates from an ISR or a task:

- **From a task**: copies the SVC object into the `svc` field of the current task,
  then triggers the `SVC #0` instruction.
- **From an ISR**: copies into the global `g_mkSVCObject` (dedicated ISR object) and
  sets the `statusRegister.isr` flag.

### Step 3 — Dispatch in the SVC handler

`mk_scheduler_handle()` is called from the assembly SVC handler and dispatches on the
call identifier:

| Identifier range | Handler |
| --- | --- |
| 1000–1007 | Object creation (`mk_call_create`) |
| 2000–2006 | Object deletion (`mk_call_delete`) |
| 3000–3008 | Task management (`mk_call_handleTask`) |
| 4000–4006 | Block on synchronisation object (`mk_call_synchronise`) |
| 5000–5003 | Unblock from synchronisation object (`mk_call_unblock`) |

When the lists change, `mk_scheduler_pend()` pends PendSV at the end of the handler.

---

## 9. Public API

All kernel public functions are accessible from task context and, where explicitly
noted, from interrupt handlers. Every function returns a `T_mkCode`; always check the
return value.

### 9.1 Kernel lifecycle

| Function | Description |
| --- | --- |
| `mk_init(type, stack, size)` | Initialises the kernel. `type` is `K_MK_MODE_DEFAULT` or `K_MK_MODE_FLOATING` (enables the FPU and reserves floating-point register save space in every task stack). Must be called before any other kernel function. Requires privileged execution mode. |
| `mk_createIdle(stack, size, fn, arg)` | Configures the idle task entry point and stack. Must be called after `mk_init()` and before `mk_start()`. |
| `mk_start(tick)` | Starts the scheduler. `tick` is the SysTick reload value in hardware timer counts; if `tick` is 0, the SysTick timer is not initialised and no periodic preemption occurs. Requires privileged execution mode (handler or privileged thread). Does not return until `mk_stop()` is called from another task. |
| `mk_stop()` | Stops the scheduler and returns execution to the main task context. Requires privileged execution mode. |
| `mk_restart(tick)` | Restarts the scheduler after `mk_stop()`. Requires privileged execution mode. |
| `mk_getTick()` | Returns the current value of `tickRegister`. Due to preemption, the returned value may already be stale by the time it is consumed. |

### 9.2 Tasks

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_task_setTaskCtrlBlock(attr, type, id, prio, owner)` | Yes | Fills a `T_mkTaskCtrlBlock` before passing it to `mk_task_create()`. Priority ranges from 1 (lowest) to `K_MK_SCHEDULER_PRIORITY_NUMBER` (highest, default 10). |
| `mk_task_create(handle, stack, pool, attr, fn, arg)` | Yes | Creates a task and places it in the ready state. Provide either a static `T_mkStack` or a `T_mkPool` for dynamic stack allocation, not both. When called from an ISR, `handle` must be `K_MK_NULL`. |
| `mk_task_terminate(task)` | Yes | Destroys a task. Pass `K_MK_NULL` to terminate the calling task. Does **not** free objects (pools, semaphores…) that the task had allocated. |
| `mk_task_yield()` | No | Triggers a voluntary context switch. If no other task exists at any priority, the calling task immediately resumes. |
| `mk_task_sleep(ticks)` | No | Suspends the calling task for at least `ticks` system ticks (absolute delay from the current tick). |
| `mk_task_delay(ticks)` | No | Like `mk_task_sleep()`, but the delay is measured relative to the last reference tick — useful for periodic tasks requiring jitter compensation. |
| `mk_task_suspend(task)` | Yes | Moves a task to the suspend list. Pass `K_MK_NULL` to suspend the calling task. |
| `mk_task_resume(task)` | Yes | Moves a suspended task back to the ready list. |
| `mk_task_priority(task, prio)` | Yes | Changes a task's base priority. Not allowed while the task holds a mutex. |
| `mk_task_get(task, attr, offset)` | No | Reads one attribute of a task. `offset` is one of `K_MK_ID`, `K_MK_TYPE`, `K_MK_STATE`, `K_MK_PRIORITY`, `K_MK_CURRENT_PRIORITY`. |
| `mk_task_getHandle(handle, id)` | No | Finds a task by its numeric identifier. If multiple tasks share the same identifier, the first match is returned. |
| `mk_task_getLoad(task, load)` | No | Returns the CPU load percentage of a task, updated every `K_MK_SCHEDULER_CPU_LOAD_RATE` ticks. Requires privileged access. |

### 9.3 Memory pools

Fixed-size block allocator. Two allocation variants are provided: a non-thread-safe
fast path (`mk_pool_alloc` / `mk_pool_free`) and a blocking thread-safe path
(`mk_pool_allocSafe` / `mk_pool_freeSafe`).

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_pool_initArea(area, buf, size)` | — | Initialises a raw memory region (`T_mkPoolArea`) from which pools are carved. `size` is in 32-bit words. |
| `mk_pool_create(area, pool, areaType, blockSize, count)` | No | Creates a fixed-size allocator inside `area`. Memory carved from `area` cannot be reclaimed. |
| `mk_pool_alloc(pool, clear)` | — | Allocates one block (non-thread-safe). Returns `K_MK_NULL` if no block is available. |
| `mk_pool_free(pool, addr)` | — | Frees one block (non-thread-safe). The block must be returned to the pool it came from. |
| `mk_pool_allocSafe(pool, addr, clear, timeout)` | No | Thread-safe allocation; blocks until a block is available or timeout expires. |
| `mk_pool_freeSafe(pool, addr)` | No | Thread-safe free; may unblock a task waiting in `mk_pool_allocSafe`. |
| `mk_pool_available(pool)` | — | Returns the address of the next available block, or `K_MK_NULL`. |
| `mk_pool_count(pool, count)` | No | Writes the number of free blocks into `count`. |
| `mk_pool_delete(pool)` | Yes | Destroys the pool descriptor. |

### 9.4 Mutexes

Mutexes implement **priority inheritance** and are strictly non-nestable: a task may
hold at most one mutex at a time.

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_mutex_create(mutex, areaType)` | No | Allocates and initialises a mutex. `areaType` is `K_MK_AREA_PROTECTED` (unprivileged tasks cannot use the mutex) or `K_MK_AREA_UNPROTECTED`. |
| `mk_mutex_take(mutex, timeout)` | No | Takes the mutex token. Blocks until available or timeout expires. Use `K_MK_TASK_WAIT_FOREVER` to block indefinitely. Returns `K_MK_ERROR_NESTED` if the calling task already holds a mutex. |
| `mk_mutex_release(mutex)` | No | Releases the mutex token. Returns `K_MK_ERROR_TIMEOUT` if the calling task does not own it. |
| `mk_mutex_delete(mutex)` | No | Destroys the mutex. |

### 9.5 Semaphores

Counting semaphore. Unlike mutexes, semaphores carry no ownership and no priority
inheritance, and can be released from ISRs.

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_semaphore_create(sem, areaType, total, initial)` | No | Allocates a semaphore with `total` tokens, of which `initial` are initially unavailable. |
| `mk_semaphore_take(sem, timeout)` | No | Takes one token. Blocks until a token is available or timeout expires. |
| `mk_semaphore_release(sem)` | **Yes** | Releases one token. Returns `K_MK_ERROR_TIMEOUT` if all tokens are already available (semaphore full). |
| `mk_semaphore_delete(sem)` | No | Destroys the semaphore. |

### 9.6 Event fields

A `T_mkEvent` is a 30-bit flag register. Two variants are available:

- **`K_MK_ID_EVENT_FLAG`** — at most one task can wait on the field at a time.
- **`K_MK_ID_EVENT_SIGNAL`** — any number of tasks can wait simultaneously.

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_event_create(event, type, areaType, initialFlags)` | No | Allocates an event field of the given type. |
| `mk_event_set(event, flags)` | **Yes** | Sets one or more bits (bitwise OR); does not clear existing bits. Up to 30 bits (bits 0–29) are available. |
| `mk_event_clear(event, flags)` | **Yes** | Clears one or more bits. |
| `mk_event_wait(event, inFlags, outFlags, timeout)` | No | Waits until one or more events are set. `inFlags` encodes both the bits to watch and the match mode (`K_MK_EVENT_OR` / `K_MK_EVENT_AND`) combined with the auto-clear policy (`K_MK_EVENT_CLEAR` / `K_MK_EVENT_NOT_CLEAR`). |
| `mk_event_delete(event)` | **Yes** | Destroys the event field. |

### 9.7 Mailboxes

A `T_mkMail` is a fixed-capacity FIFO message queue. Messages are **copied by value**
into the mailbox's internal memory. To transfer a large object without copying it, a
task can post a pointer to the object as the message payload — in this case the sender
must ensure the pointed-to data remains valid until the receiver has consumed it (e.g.
statically or heap-allocated data, not a local variable).

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_mail_create(mail, areaType, area, msgSize, count)` | No | Allocates a mailbox holding `count` messages of `msgSize` bytes each, inside `area`. |
| `mk_mail_post(mail, msg, nextState, timeout)` | **Yes** (timeout=0 only) | Posts a message. `nextState` is `K_MK_STATE_READY` or `K_MK_STATE_SUSPENDED` — the latter suspends the poster after a successful post. When called from an ISR, `timeout` must be 0, `nextState` must be `K_MK_STATE_READY` and the message buffer must reside in persistent memory (global, static or dynamically allocated). |
| `mk_mail_pend(senderTask, mail, msg, timeout)` | No | Reads and removes the oldest message. `senderTask` may be `K_MK_NULL` if the sender identity is not needed. |
| `mk_mail_delete(mail)` | **Yes** | Destroys the mailbox. |

### 9.8 Callback manager

The callback subsystem lets any task or ISR request execution of a function in a
dedicated privileged or unprivileged runner task, and optionally wait for completion.

| Function | ISR-safe | Description |
| --- | --- | --- |
| `mk_callback_init(stackType)` | No | Initialises the two permanent callback runner tasks (one privileged, one unprivileged). `stackType` is `K_MK_TYPE_FLOATING` or `K_MK_TYPE_DEFAULT`. Must be called once after `mk_init()`. |
| `mk_callback_createHandler(handler, areaType)` | No | Creates a `T_mkCallbackHandler`, which owns the mailbox and event field used to dispatch and signal callbacks. |
| `mk_callback_create(handler, areaType, callback, fn)` | No | Creates a `T_mkCallback` registered to `handler`, pointing to function `fn`. Each callback gets a unique bit in the handler's event field, usable with `mk_callback_wait()`. |
| `mk_callback_trig(handler, callback, params)` | — | Posts a callback execution request. Returns immediately; the callback runs asynchronously in the runner task. |
| `mk_callback_wait(handler, ids, outIds, timeout)` | No | Waits until one or more callbacks have completed. Thin wrapper around `mk_event_wait()` on the handler's event field. |
| `mk_callback_deleteHandler(handler)` | No | Destroys a callback handler. |
| `mk_callback_delete(callback)` | No | Destroys a callback function descriptor. |

---

## 10. CPU load measurement

The kernel measures the CPU time consumed by each task using the **hardware SysTick
counter** (`SYST_CVR`), which counts down from `timerRegister` to 0 at every tick.
The measurement is performed inside `_mk_scheduler_load()`, called at the very
beginning of every PendSV invocation, before the context switch takes place — so the
elapsed time is always credited to the task that was actually running.

**Per-context-switch accumulation**

Each task owns two load fields:

| Field | Role |
| --- | --- |
| `load.value` | Running accumulator, incremented at every PendSV |
| `load.lastValue` | Snapshot published to the user at the end of each measurement window |

At each PendSV entry, the elapsed hardware ticks since the last PendSV are computed as:

```
elapsed = load.usTickRegister - SYST_CVR
```

where `load.usTickRegister` holds the SysTick counter value captured at the **end** of
the previous PendSV. This value is added to the current task's `load.value` and to the
global sum `load.usTickRegisterSum`.

**SysTick overflow handling**

Because SysTick reloads asynchronously with respect to PendSV, a reload may occur
between two consecutive PendSV invocations. The `COUNTFLAG` bit of `SYST_CSR` is
checked at each entry: if set, the counter has wrapped. In that case the remaining
time from the previous cycle (`load.usTickRegister`) and the elapsed time in the new
cycle (`timerRegister − SYST_CVR`) are accumulated separately before being summed,
preventing any measurement gap.

**Window and publication**

The scheduler counts elapsed ticks in `load.cycleRegister`. When
`cycleRegister` reaches `K_MK_SCHEDULER_CPU_LOAD_RATE` (default: 1000 ticks = 1 s at
1 ms/tick), the window closes:

1. `load.usTickRegisterLastSum` ← `load.usTickRegisterSum` (total hardware ticks in
   the window, used as the denominator when computing percentages).
2. `load.usTickRegisterSum` is reset to 0.
3. For every task slot (idle task + all `K_MK_SCHEDULER_MAX_NUMBER_OF_TASKS` pool
   slots): `load.lastValue` ← `load.value`, then `load.value` is reset to 0.
4. `load.cycleRegister` is reset to 0.

`mk_task_getLoad()` computes the percentage as:

```
load% = (task.load.lastValue × 100) / load.usTickRegisterLastSum
```

The result is therefore expressed in **hardware timer counts**, not in ticks — the
granularity is sub-tick, bounded by the SysTick clock frequency.

---

## 11. Configurable constants

These constants in `mk_scheduler_constants.h` can be adjusted before compilation:

| Constant | Default | Description |
| --- | --- | --- |
| `K_MK_SCHEDULER_PRIORITY_NUMBER` | 10 | Number of user priority levels (10 = highest, 1 = lowest) |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_TASKS` | 32 | Maximum number of allocatable tasks |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_POOLS` | 48 | Maximum number of pools |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_MAILS` | 48 | Maximum number of mailboxes |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_EVENTS` | 128 | Maximum number of event fields |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_MUTEX` | 48 | Maximum number of mutexes |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_SEMAPHORES` | 32 | Maximum number of semaphores |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_CALLBACK_HANDLER` | 48 | Maximum number of callback handlers |
| `K_MK_SCHEDULER_MAX_NUMBER_OF_CALLBACK_FUNCTION` | 48 | Maximum number of callback function descriptors |
| `K_MK_SCHEDULER_CPU_LOAD_RATE` | 1000 | CPU load computation window (in ticks) |
| `K_MK_SCHEDULER_MASK_PRIORITY` | 8 | BASEPRI threshold — must not equal `SVC_PRIORITY` |
| `K_MK_SCHEDULER_BASE_PRIORITY` | 15 | SysTick and PendSV priority |

---

## See also

- [Architecture Overview](Architecture-Overview) — system layers, memory map, privilege model, boot sequence
- [Work with files and storage](File-System) — disk, volume and file API
- [Load and run external programs](ELF-Loader) — dynamic loading, SDRAM page allocation, symbol resolution
- [Use or extend the Shell](Shell-and-Commands) — external shell commands, console I/O API

