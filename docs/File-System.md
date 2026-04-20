# Work with files and storage

This page describes the storage subsystem of Mk and the public API it exposes
to applications: the **volume API** for enumerating disks and partitions, and the
**file API** for reading and writing files on a FAT32 volume.

---

## Table of contents

1. [Architecture overview](#1-architecture-overview)
2. [How the file system works](#2-how-the-file-system-works)
   - 2.1 [File system tasks](#21-file-system-tasks)
   - 2.2 [Synchronous vs asynchronous mode](#22-synchronous-vs-asynchronous-mode)
   - 2.3 [Sector cache](#23-sector-cache)
   - 2.4 [Concurrent access](#24-concurrent-access)
3. [Path addressing](#3-path-addressing)
   - 3.1 [Absolute paths](#31-absolute-paths)
   - 3.2 [Relative paths (system volume)](#32-relative-paths-system-volume)
   - 3.3 [Volume pointer shortcut](#33-volume-pointer-shortcut)
   - 3.4 [Maximum path length](#34-maximum-path-length)
4. [Volume API](#4-volume-api)
   - 4.1 [System volume](#41-system-volume)
   - 4.2 [Enumerating MMC devices, disks, and volumes](#42-enumerating-mmc-devices-disks-and-volumes)
   - 4.3 [Enumerating USB MSC devices, disks, and volumes](#43-enumerating-usb-msc-devices-disks-and-volumes)
   - 4.4 [Volume navigation functions](#44-volume-navigation-functions)
   - 4.5 [T_mkVolume key fields](#45-t_mkvolume-key-fields)
5. [File API](#5-file-api)
   - 5.1 [Opening files](#51-opening-files)
   - 5.2 [Closing files](#52-closing-files)
   - 5.3 [Reading and writing](#53-reading-and-writing)
   - 5.4 [File pointer](#54-file-pointer)
   - 5.5 [Size management](#55-size-management)
   - 5.6 [File metadata](#56-file-metadata)
   - 5.7 [File operations](#57-file-operations)
6. [Disk API (raw block access)](#6-disk-api-raw-block-access)
7. [Common patterns](#7-common-patterns)
8. [Return codes](#8-return-codes)

---

## 1. Architecture overview

The storage stack is organized in four layers.

```
┌──────────────────────────────────────────────────┐
│                  Application                     │
│                (mk_file_*.h)                     │
├──────────────────────────────────────────────────┤
│               File System tasks                  │
│   (4 independent tasks — 2 shared, 2 exclusive)  │
├──────────────────────────────────────────────────┤
│          FAT32 layer  /  Volume layer            │
│    (cluster chain traversal, sector cache)       │
├──────────────────────────────────────────────────┤
│                 Disk drivers                     │
│    MMC (mk_mmc_*.h)     MSC / USB (mk_msc_*.h)   │
└──────────────────────────────────────────────────┘
```

Each **device** (SD card reader or USB MSC device) exposes one or more **disks**.
Each disk contains one or more **volumes** (partitions). A **file** belongs to
exactly one volume.

Objects and their relationships:

```
T_mkMMCDevice  ──── T_mkDisk ──┐
T_mkMSCDevice  ──── T_mkDisk ──┴── T_mkVolume ── T_mkFile
```

---

## 2. How the file system works

### 2.1 File system tasks

All file and disk I/O goes through a dedicated pool of four kernel tasks:

- **Two shared tasks** — serve requests from any caller with the `K_MK_FS_OPEN_SHARED`
  flag set. Multiple callers may access the same file concurrently using these tasks.
- **Two exclusive tasks** — serve one caller at a time, used when `K_MK_FS_OPEN_SHARED`
  is not set.

An application sends a request to one of these tasks via a mailbox
(`T_mkFileMessage`). The task executes the I/O and either unblocks the caller
(synchronous mode) or invokes the callback (asynchronous mode).

### 2.2 Synchronous vs asynchronous mode

Every file API function accepts a `T_mkCallback* p_callback` parameter.

When `p_callback` is `K_MK_NULL` the call **blocks** until the I/O is complete.
The return value of the function carries the result.

When `p_callback` is non-null the call returns immediately and the file system
task invokes the callback with the result when finished. The callback signature
varies by function and is documented in each section below. Any output buffer
passed to an asynchronous call must remain valid for the entire duration of the
operation — do not pass stack-allocated buffers.

### 2.3 Sector cache

#### Physical layout

The system allocates one static DMA-capable buffer per FS task:

```c
uint8_t g_mkFileBuf[K_MK_FILE_NUMBER_OF_TASKS][K_MK_FILE_CACHE_SIZE];
//                  4 tasks                     2 048 bytes each
```

A `T_mkFile` object does not embed the cache buffer — it only holds three
metadata fields that point into the task's buffer:

| Field | Role |
| --- | --- |
| `cacheBaseAddress` | Pointer to the start of the task buffer (fixed for a given request). |
| `cacheCurrentAddress` | LBA address of the first sector currently held in the buffer. |
| `cacheFlushFlag` | Dirty bit: set to 1 when the buffer contains unwritten data. |

The effective cache window covers `numberOfBlocksPerWindow` consecutive sectors,
where `numberOfBlocksPerWindow = K_MK_FILE_MAX_BLOCK_LENGTH / bytesPerSector`
(e.g. `1 024 / 512 = 2` sectors for a 512-byte/sector volume, consuming 1 024 of
the 2 048 bytes allocated).

#### Reset at each request

`mk_file_handle()` calls `mk_file_handleFileInstance()` **at the start of every
request** (except OPEN and STAT), which unconditionally executes:

```c
p_file->cacheBaseAddress    = p_buf;   /* rebind to the current task's buffer */
p_file->cacheCurrentAddress = 0;       /* invalidate the window               */
p_file->cacheFlushFlag      = 0;       /* clear the dirty bit                 */
```

The cache is therefore **not persistent across requests**: it provides no
benefit for two consecutive `mk_file_read` calls on the same file. Its role is
limited to caching within a single request.

#### When the cache is used

The cache (`readCache` / `writeCache`) is used in the following situations:

**Partial sector access** — the first and last blocks of a read or write that
are not aligned to a sector boundary are always handled through the cache.
`readCache` loads the full sector, the relevant bytes are copied to or from the
user buffer in memory, and `writeCache` marks the window dirty. The dirty sector
is not written to disk immediately; it is flushed when the window must be evicted.

**Unaligned user buffer** — when the user buffer address is not 32-bit aligned
and the hardware DMA does not support unaligned transfers (e.g. USB MSC), every
block of the transfer is routed through the cache sector by sector instead of
going directly to disk.

**FAT metadata operations** — directory entries, FAT cluster chain updates,
rename, chmod, link, and unlink all read-modify-write FAT sectors through the
cache.

Whole-sector, aligned transfers (the common case for large reads and writes)
bypass the cache entirely and go straight to disk via `mk_fat_utils_read` /
`mk_fat_utils_write`. These functions do call `mk_fat_utils_sync()` first if
the target address overlaps the current cache window, to avoid stale data.

### 2.4 Concurrent access

A per-volume semaphore serializes all FAT cluster-chain modifications on a
given volume. Multiple tasks may read different files on the same volume
simultaneously, but write operations (cluster allocation, rename, unlink) are
serialized.

An individual `T_mkFile` instance must not be shared between tasks without
additional application-level locking.

---

## 3. Path addressing

### 3.1 Absolute paths

When the `p_volume` parameter of a file function is `K_MK_NULL`, the volume is
encoded in the path string using the following syntax:

```
/dsk<n>/vol<k>/<path>/<filename>
```

where `n` is the disk index in `[0, K_MK_DISK_MAX_NUMBER-1]` and `k` is the
partition index in `[0, K_MK_VOLUME_MAX_NUMBER-1]`.

Examples:

```
/dsk0/vol0/config.ini          → disk 0, partition 0, file config.ini
/dsk0/vol1/logs/app.log        → disk 0, partition 1, file logs/app.log
/dsk3/vol0/data/records.bin    → disk 3, partition 0, file data/records.bin
```

### 3.2 Relative paths (system volume)

The `/dsk[n]/vol[k]/` prefix may be omitted when accessing the **system volume**
(`g_mkSystemVolume`). The path then starts directly with the file or directory
name:

```
config.ini                     → system volume, root, config.ini
mk/apps/pong/pong.elf          → system volume, mk/apps/pong/pong.elf
```

### 3.3 Volume pointer shortcut

When a `T_mkVolume*` pointer is passed directly as the `p_volume` argument,
the `/dsk[n]/vol[k]/` prefix is ignored and the path is resolved on that
specific volume. This is the recommended approach for applications that already
hold a volume pointer.

```c
T_mkFile* l_file;
mk_file_open(l_myVolume, &l_file, "data/log.bin",
             K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL);
```

### 3.4 Maximum path length

A path string must not exceed `K_MK_FILE_MAX_NAME_LENGTH` bytes (255 bytes),
including the `/dsk[n]/vol[k]/` prefix if present.

---

## 4. Volume API

Volumes are discovered automatically when a storage device is connected.
The application navigates the device → disk → volume hierarchy using the
functions described below.

### 4.1 System volume

The global variable `g_mkSystemVolume` always points to the partition used to
boot the system. It is the volume from which `.elf` files and configuration are
loaded by default.

```c
#include "mk_volume_data.h"

T_mkVolume* l_sysVol = g_mkSystemVolume;
```

### 4.2 Enumerating MMC devices, disks, and volumes

```c
#include "mk_mmc.h"

T_mkMMCDevice* l_dev;
T_mkDisk*      l_disk;
T_mkVolume*    l_vol;

/* Iterate over all SD/MMC devices */
for (mk_mmc_getFirstDevice(&l_dev);
     l_dev != K_MK_NULL;
     mk_mmc_getNextDevice(&l_dev, l_dev))
{
    /* Iterate over disks on this device */
    for (mk_mmc_getFirstDisk(l_dev, &l_disk);
         l_disk != K_MK_NULL;
         mk_mmc_getNextDisk(&l_disk, l_disk))
    {
        /* Iterate over volumes (partitions) on this disk */
        for (mk_disk_getFirstVolume(l_disk, &l_vol);
             l_vol != K_MK_NULL;
             mk_disk_getNextVolume(&l_vol, l_vol))
        {
            /* l_vol->type   → K_MK_VOLUME_TYPE_FAT32 / FAT16 / NTFS / UNKNOWN */
            /* l_vol->status → K_MK_VOLUME_READY / NOT_SUPPORTED / CORRUPTED   */
            /* l_vol->name.str → system identifier, e.g. "dsk0vol0"            */
        }
    }
}
```

### 4.3 Enumerating USB MSC devices, disks, and volumes

```c
#include "mk_msc.h"

T_mkMSCDevice* l_dev;
T_mkDisk*      l_disk;
T_mkVolume*    l_vol;

for (mk_msc_getFirstDevice(&l_dev);
     l_dev != K_MK_NULL;
     mk_msc_getNextDevice(&l_dev, l_dev))
{
    for (mk_msc_getFirstDisk(l_dev, &l_disk);
         l_disk != K_MK_NULL;
         mk_msc_getNextDisk(&l_disk, l_disk))
    {
        for (mk_disk_getFirstVolume(l_disk, &l_vol);
             l_vol != K_MK_NULL;
             mk_disk_getNextVolume(&l_vol, l_vol))
        {
            /* process l_vol */
        }
    }
}
```

### 4.4 Volume navigation functions

| Function | Description |
| --- | --- |
| `mk_mmc_getFirstDevice(device)` | Returns the first SD/MMC device, or `K_MK_NULL` if none is connected. |
| `mk_mmc_getNextDevice(device, current)` | Advances to the next SD/MMC device. |
| `mk_mmc_getFirstDisk(device, disk)` | Returns the first disk of an MMC device. |
| `mk_mmc_getNextDisk(disk, current)` | Advances to the next disk on the same MMC device. |
| `mk_msc_getFirstDevice(device)` | Returns the first USB MSC device. |
| `mk_msc_getNextDevice(device, current)` | Advances to the next USB MSC device. |
| `mk_msc_getFirstDisk(device, disk)` | Returns the first disk of a USB MSC device. |
| `mk_msc_getNextDisk(disk, current)` | Advances to the next disk on the same MSC device. |
| `mk_disk_getFirstVolume(disk, volume)` | Returns the first volume (partition) of a disk. |
| `mk_disk_getNextVolume(volume, current)` | Advances to the next volume on the same disk. |

All navigation functions return `K_MK_OK` on success and write `K_MK_NULL`
into the output pointer when the end of the list is reached. They only return
`K_MK_ERROR_PARAM` if a null pointer argument is passed.

### 4.5 `T_mkVolume` key fields

| Field | Type | Description |
| --- | --- | --- |
| `type` | `T_mkVolumeType` | `K_MK_VOLUME_TYPE_FAT16`, `K_MK_VOLUME_TYPE_FAT32`, `K_MK_VOLUME_TYPE_NTFS`, or `K_MK_VOLUME_TYPE_UNKNOWN`. |
| `status` | `T_mkVolumeStatus` | `K_MK_VOLUME_READY`, `K_MK_VOLUME_NOT_ENUMERATED`, `K_MK_VOLUME_NOT_SUPPORTED`, or `K_MK_VOLUME_CORRUPTED`. |
| `name.str` | `char8_t[12]` | System-assigned identifier, e.g. `"dsk0vol0"`. |
| `partition.fat.label` | `uint8_t[11]` | Volume label read from the BPB (FAT32 only). |
| `partition.fat.totalNumberOfSectors` | `uint32_t` | Total partition capacity in sectors. |
| `partition.fat.bytesPerSector` | `uint16_t` | Bytes per sector (typically 512). |
| `partition.fat.numberOfFreeCluster` | `uint32_t` | Number of free clusters remaining. |
| `partition.fat.clusterSize` | `uint32_t` | Cluster size in bytes. |

---

## 5. File API

The file API is declared in `mk_file.h`. All functions route through the file
system tasks and accept a callback pointer for asynchronous operation.

### 5.1 Opening files

#### `mk_file_open` — open by absolute or relative path

```c
T_mkCode mk_file_open(
    T_mkVolume*   p_volume,    /* target volume, or K_MK_NULL for path-embedded volume */
    T_mkFile**    p_file,      /* out: file handle */
    T_str8        p_filePath,  /* path string, max K_MK_FILE_MAX_NAME_LENGTH bytes */
    T_mkFileMode  p_mode,      /* open mode flags (see below) */
    T_mkCallback* p_callback
);
```

The open mode is a combination of a **create/open policy** and **access flags**:

**Create/open policies (mutually exclusive):**

| Constant | Behaviour |
| --- | --- |
| `K_MK_FS_OPEN_EXISTING` | Open if the file exists; fail if it does not. Pointer placed at start. |
| `K_MK_FS_OPEN_ALWAYS` | Open if it exists, create otherwise. Pointer placed at start. |
| `K_MK_FS_OPEN_APPEND` | Open if it exists, create otherwise. Pointer placed at end. |
| `K_MK_FS_OPEN_CREATE` | Create a new file; fail if it already exists. |
| `K_MK_FS_OPEN_CREATE_DIRECTORY` | Create a new directory; fail if it already exists. |
| `K_MK_FS_OPEN_TRUNCATE` | Truncate to zero if it exists, create if it does not. |

**Access flags (combinable with `|`):**

| Constant | Meaning |
| --- | --- |
| `K_MK_FS_OPEN_READ` | Open for reading. Required to call `mk_file_read`. |
| `K_MK_FS_OPEN_WRITE` | Open for writing. Required to call `mk_file_write`, `mk_file_unlink`, `mk_file_rename`, `mk_file_truncate`, `mk_file_expand`. |
| `K_MK_FS_OPEN_SHARED` | Route the request through a shared file system task, allowing concurrent access from multiple tasks. |

Example:

```c
T_mkFile* l_file;

/* Open existing file for reading on the system volume */
T_mkCode l_result = mk_file_open(
    K_MK_NULL, &l_file, "config/settings.ini",
    K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL);

/* Create or overwrite a file for writing on a specific volume */
l_result = mk_file_open(
    l_myVolume, &l_file, "logs/app.log",
    K_MK_FS_OPEN_TRUNCATE | K_MK_FS_OPEN_WRITE, K_MK_NULL);
```

Asynchronous callback: `void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_openDirectory` — open a file by index within a directory

```c
T_mkCode mk_file_openDirectory(
    T_mkFile**    p_file,       /* out: file handle */
    T_mkFile*     p_directory,  /* open directory handle */
    uint16_t      p_entry,      /* zero-based entry index */
    uint8_t       p_mode,       /* access flags: READ / WRITE / SHARED */
    T_mkCallback* p_callback
);
```

Opens the `p_entry`-th file inside an already-open directory. This is the
primary function for iterating directory contents: call it in a loop with
increasing `p_entry` values until `K_MK_ERROR_NOT_FOUND` is returned.

See the [List a directory](#7-common-patterns) example in §7.

Asynchronous callback: `void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_openRelative` — open a file relative to a directory

```c
T_mkCode mk_file_openRelative(
    T_mkFile**    p_file,       /* out: file handle */
    T_mkFile*     p_directory,  /* open directory handle */
    T_str8        p_filePath,   /* path relative to p_directory */
    uint8_t       p_mode,       /* access flags: READ / WRITE / SHARED */
    T_mkCallback* p_callback
);
```

Resolves `p_filePath` starting from the directory represented by `p_directory`.
This avoids constructing absolute paths when already positioned inside a subdirectory.

Asynchronous callback: `void f_callback(T_mkCode p_err, T_mkFile* p_file)`

### 5.2 Closing files

```c
T_mkCode mk_file_close(T_mkFile* p_file, T_mkCallback* p_callback);
```

Flushes any pending cache write-back and frees the file handle. A file opened with
`K_MK_FS_OPEN_WRITE` that has been modified writes the updated directory entry
(size, modification timestamp) back to disk at this point.

A file deleted with `mk_file_unlink` must still be closed with `mk_file_close`.

Asynchronous callback: `void f_callback(T_mkCode p_err)`

### 5.3 Reading and writing

#### `mk_file_read`

```c
T_mkCode mk_file_read(
    T_mkFile*     p_file,
    T_mkAddr      p_buf,                  /* output buffer */
    uint32_t      p_numberOfBytesToRead,
    uint32_t*     p_numberOfBytesRead,    /* out: actual bytes read */
    T_mkCallback* p_callback
);
```

Reads up to `p_numberOfBytesToRead` bytes starting at the current file pointer
position. The file pointer advances by the number of bytes actually read.

If the function returns `K_MK_OK` but `*p_numberOfBytesRead < p_numberOfBytesToRead`,
the end of file has been reached. The file does not need to be closed or
repositioned in this case.

If the function returns an error the file pointer is in an indeterminate state;
call `mk_file_seek` before the next operation.

Requires `K_MK_FS_OPEN_READ`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_requested, uint32_t* p_bytesRead)`

#### `mk_file_write`

```c
T_mkCode mk_file_write(
    T_mkFile*     p_file,
    T_mkAddr      p_buf,                   /* data to write */
    uint32_t      p_numberOfBytesToWrite,
    uint32_t*     p_numberOfBytesWrite,    /* out: actual bytes written */
    T_mkCallback* p_callback
);
```

Writes `p_numberOfBytesToWrite` bytes at the current file pointer position.
New clusters are allocated automatically as the file grows.

Requires `K_MK_FS_OPEN_WRITE`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, uint32_t p_requested, uint32_t* p_bytesWritten)`

### 5.4 File pointer

#### `mk_file_seek` — set the file pointer

```c
T_mkCode mk_file_seek(
    T_mkFile*     p_file,
    uint32_t      p_filePointer,   /* byte offset from start, or special constant */
    T_mkCallback* p_callback
);
```

Sets the file pointer to a byte offset from the beginning of the file. Two
special constants are available:

| Constant | Value | Effect |
| --- | --- | --- |
| `K_MK_FS_POINTER_TO_SOF` | `0` | Positions the pointer at the beginning of the file. |
| `K_MK_FS_POINTER_TO_EOF` | `0xFFFFFFFF` | Positions the pointer at the end of the file. |

If the requested offset exceeds the file size the pointer is placed at the end.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_tell` — get the current file pointer

```c
T_mkCode mk_file_tell(
    T_mkFile*     p_file,
    uint32_t*     p_filePointer,   /* out: current byte offset */
    T_mkCallback* p_callback
);
```

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, uint32_t* p_filePointer)`

#### `mk_file_eof` — test end-of-file

```c
T_mkCode mk_file_eof(
    T_mkFile*     p_file,
    uint32_t*     p_eof,    /* out: K_MK_FS_EOF_TRUE or K_MK_FS_EOF_FALSE */
    T_mkCallback* p_callback
);
```

Returns `K_MK_FS_EOF_TRUE` if the file pointer is at or past the last byte of
the file, `K_MK_FS_EOF_FALSE` otherwise.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, uint32_t* p_eof)`

### 5.5 Size management

#### `mk_file_truncate` — shorten a file

```c
T_mkCode mk_file_truncate(T_mkFile* p_file, T_mkCallback* p_callback);
```

Truncates the file at the current file pointer position, freeing all clusters
beyond that point. If the pointer is at the start (`K_MK_FS_POINTER_TO_SOF`)
the entire file content is discarded (size becomes zero). If the pointer equals
the file size, the function has no effect.

Requires `K_MK_FS_OPEN_WRITE`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_expand` — grow a file

```c
T_mkCode mk_file_expand(
    T_mkFile*     p_file,
    uint32_t      p_newFileSize,   /* new size in bytes */
    T_mkCallback* p_callback
);
```

Pre-allocates clusters to bring the file to `p_newFileSize` bytes. The content
of the newly allocated region is undefined. The file pointer is not moved.
If `p_newFileSize` is smaller than the current file size the function has no effect.

Requires `K_MK_FS_OPEN_WRITE`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

### 5.6 File metadata

#### `mk_file_stat` — test file existence

```c
T_mkCode mk_file_stat(
    T_mkVolume*   p_volume,
    T_str8        p_filePath,
    T_mkCallback* p_callback
);
```

Returns `K_MK_OK` if the file exists, `K_MK_ERROR_NOT_FOUND` otherwise. Does
not open the file or allocate a `T_mkFile` handle.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_statRelative` — test existence relative to a directory

```c
T_mkCode mk_file_statRelative(
    T_mkVolume*   p_volume,
    T_str8        p_directoryPath,   /* path to the parent directory */
    T_str8        p_filePath,        /* file name or relative sub-path */
    T_mkCallback* p_callback
);
```

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_getName` — retrieve the UTF-8 file name

```c
T_mkCode mk_file_getName(
    T_mkFile*     p_file,
    T_str8        p_fileName,   /* output buffer, min K_MK_FILE_MAX_NAME_LENGTH bytes */
    T_mkCallback* p_callback
);
```

Writes the long file name of the open file into `p_fileName` as a UTF-8 string.
The caller's buffer must be at least `K_MK_FILE_MAX_NAME_LENGTH` (255) bytes.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, T_str8 p_fileName)`

#### `mk_file_getInfo` — retrieve the FAT directory entry

```c
T_mkCode mk_file_getInfo(
    T_mkFile*     p_file,
    T_mkFileInfo* p_fileInfo,   /* out: union wrapping T_mkFATEntryDescriptor */
    T_mkCallback* p_callback
);
```

Fills `*p_fileInfo` with the raw FAT32 directory entry for the file. The
`T_mkFileInfo` union exposes the FAT32 fields through its `.fat` member
(`T_mkFATEntryDescriptor`):

| Field | Type | Description |
| --- | --- | --- |
| `fat.name[8]` | `uint8_t[]` | Short name (8.3, space-padded). |
| `fat.extension[3]` | `uint8_t[]` | Short extension (space-padded). |
| `fat.attribute` | `uint8_t` | FAT attribute byte (`T_mkFATFileAttribute`). |
| `fat.creationDate` | `uint16_t` | Creation date (bits 15–9 = year−1980, 8–5 = month, 4–0 = day). |
| `fat.creationTime` | `uint16_t` | Creation time (bits 15–11 = hour, 10–5 = minutes, 4–0 = seconds÷2). |
| `fat.modificationDate` | `uint16_t` | Last modification date (same packed format). |
| `fat.modificationTime` | `uint16_t` | Last modification time (same packed format). |
| `fat.fileSize` | `uint32_t` | File size in bytes. |

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, T_mkFileInfo* p_info)`

#### `mk_file_getSize` — retrieve the file size

```c
T_mkCode mk_file_getSize(
    T_mkFile*     p_file,
    uint32_t*     p_lowFileSize,    /* out: low 32 bits of size in bytes */
    uint32_t*     p_highFileSize,   /* out: high 32 bits (always 0 on FAT32) */
    T_mkCallback* p_callback
);
```

Returns the file size split across two 32-bit words to accommodate large files.
On FAT32 volumes `*p_highFileSize` is always 0 (FAT32 limits files to 4 GiB − 1).

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, uint32_t p_low, uint32_t p_high)`

#### `mk_file_getType` — query file type

```c
T_mkCode mk_file_getType(
    T_mkFile*     p_file,
    uint32_t*     p_type,    /* out: T_mkFileType */
    T_mkCallback* p_callback
);
```

| Constant | Meaning |
| --- | --- |
| `K_MK_FS_TYPE_FILE` | Regular file. |
| `K_MK_FS_TYPE_DIRECTORY` | Subdirectory. |
| `K_MK_FS_TYPE_ROOTDIRECTORY` | Root directory of the volume. |

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file, uint32_t p_fileType)`

### 5.7 File operations

#### `mk_file_rename` — rename or move a file

```c
T_mkCode mk_file_rename(
    T_mkFile*     p_file,       /* file to rename (must be open with WRITE) */
    T_str8        p_filePath,   /* new name/path on the same volume */
    T_mkCallback* p_callback
);
```

Renames or moves `p_file` to `p_filePath`. The destination must be on the same
volume; cross-volume moves are not supported. Fails with `K_MK_ERROR_ALREADY_EXIST`
if the destination name already exists.

Requires `K_MK_FS_OPEN_WRITE`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_unlink` — delete a file

```c
T_mkCode mk_file_unlink(T_mkFile* p_file, T_mkCallback* p_callback);
```

Marks the file as deleted and frees its cluster chain. The `T_mkFile` handle
remains valid until `mk_file_close` is called; no further reads or writes
should be performed on it after `mk_file_unlink` returns successfully.

Requires `K_MK_FS_OPEN_WRITE`.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_link` — create a symbolic link

```c
T_mkCode mk_file_link(
    T_mkFile*     p_file,       /* source file */
    T_str8        p_filePath,   /* path for the new link */
    T_mkCallback* p_callback
);
```

Creates a new directory entry at `p_filePath` pointing to the same cluster
chain as `p_file`. The handle of the new link is not returned; open the link
path separately if needed.

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

#### `mk_file_chmod` — change file attributes

```c
T_mkCode mk_file_chmod(
    T_mkFile*         p_file,
    T_mkFileAttribute p_attribute,   /* new attribute mask — replaces existing */
    T_mkCallback*     p_callback
);
```

Replaces the file's attribute byte entirely with `p_attribute`. Combinable constants:

| Constant | Meaning |
| --- | --- |
| `K_MK_FS_ATTRIBUTE_NO` | No attributes. |
| `K_MK_FS_ATTRIBUTE_READ_ONLY` | File is read-only. |
| `K_MK_FS_ATTRIBUTE_HIDDEN` | File is hidden. |
| `K_MK_FS_ATTRIBUTE_SYSTEM` | File is a system file. |
| `K_MK_FS_ATTRIBUTE_ARCHIVE` | File has been modified since last backup. |

Asynchronous callback:
`void f_callback(T_mkCode p_err, T_mkFile* p_file)`

---

## 6. Disk API (raw block access)

The disk API provides direct block-level access, bypassing the FAT layer.
It is intended for low-level tools such as partition formatters or integrity
checkers, not for routine application I/O. These functions are synchronous only.

### `mk_disk_read`

```c
T_mkCode mk_disk_read(
    T_mkDisk*  p_disk,
    uint64_t   p_blockAddress,         /* first LBA block to read */
    T_mkAddr   p_buf,                  /* output buffer */
    uint32_t   p_numberOfBlockToRead,
    uint64_t*  p_numberOfBytesRead     /* out: bytes transferred */
);
```

Reads one or more contiguous sectors from the disk starting at LBA address
`p_blockAddress`. The buffer size must be a multiple of the sector size
(typically 512 bytes).

### `mk_disk_write`

```c
T_mkCode mk_disk_write(
    T_mkDisk*  p_disk,
    uint64_t   p_blockAddress,
    T_mkAddr   p_buf,
    uint32_t   p_numberOfBlockToWrite,
    uint64_t*  p_numberOfBytesWrite
);
```

Writes one or more contiguous sectors starting at `p_blockAddress`.

---

## 7. Common patterns

### Read an entire file into a buffer

```c
T_mkFile* l_file;
uint32_t  l_low, l_high, l_bytesRead;

mk_file_open(K_MK_NULL, &l_file, "data.bin",
             K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL);

mk_file_getSize(l_file, &l_low, &l_high, K_MK_NULL);

uint8_t* l_buf = /* allocate l_low bytes */;
mk_file_read(l_file, l_buf, l_low, &l_bytesRead, K_MK_NULL);

mk_file_close(l_file, K_MK_NULL);
```

### Append to a log file

```c
T_mkFile* l_file;
uint32_t  l_written;
const char* l_msg = "Event occurred\n";

mk_file_open(K_MK_NULL, &l_file, "logs/events.log",
             K_MK_FS_OPEN_APPEND | K_MK_FS_OPEN_WRITE, K_MK_NULL);

mk_file_write(l_file, (T_mkAddr) l_msg,
              mk_utils_strlen((T_str8) l_msg), &l_written, K_MK_NULL);

mk_file_close(l_file, K_MK_NULL);
```

### Read-modify-write

```c
uint8_t  l_buf[512];
uint32_t l_read, l_written;
T_mkFile* l_file;

mk_file_open(l_vol, &l_file, "data.bin",
             K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE,
             K_MK_NULL);

mk_file_read(l_file, l_buf, sizeof(l_buf), &l_read, K_MK_NULL);

/* modify l_buf */

mk_file_seek(l_file, K_MK_FS_POINTER_TO_SOF, K_MK_NULL);
mk_file_write(l_file, l_buf, l_read, &l_written, K_MK_NULL);

mk_file_close(l_file, K_MK_NULL);
```

### List a directory

```c
T_mkFile* l_dir;
T_mkFile* l_entry;
uint16_t  l_idx = 0;
char      l_name[K_MK_FILE_MAX_NAME_LENGTH];
uint32_t  l_type;

/* Open the root directory by passing only the volume prefix path */
mk_file_open(K_MK_NULL, &l_dir, "/dsk0/vol0",
             K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL);

while (mk_file_openDirectory(&l_entry, l_dir, l_idx++,
                              K_MK_FS_OPEN_READ, K_MK_NULL) == K_MK_OK)
{
    mk_file_getName(l_entry, (T_str8) l_name, K_MK_NULL);
    mk_file_getType(l_entry, &l_type, K_MK_NULL);
    /* display l_name, l_type */
    mk_file_close(l_entry, K_MK_NULL);
}

mk_file_close(l_dir, K_MK_NULL);
```

---

## 8. Return codes

| Code | Meaning |
| --- | --- |
| `K_MK_OK` | Operation succeeded. |
| `K_MK_ERROR_PARAM` | Invalid parameter (null pointer, empty path, unsupported flag combination). |
| `K_MK_ERROR_MALLOC` | No free file handle slot available in the pool. |
| `K_MK_ERROR_ISR` | Called from an interrupt handler. |
| `K_MK_ERROR_RIGHT` | Unprivileged task attempted a privileged operation. |
| `K_MK_ERROR_TIMEOUT` | File system task did not respond in time. |
| `K_MK_ERROR_COMM` | Physical read/write error on the storage device. |
| `K_MK_ERROR_CORRUPTED` | FAT cluster chain is corrupted. |
| `K_MK_ERROR_NOT_FOUND` | File or directory does not exist (`mk_file_stat`, `mk_file_openDirectory` exhausted). |
| `K_MK_ERROR_ALREADY_EXIST` | Create operation failed because an entry with that name already exists. |
| `K_MK_ERROR_FULL` | No free sectors or clusters on the volume. |
| `K_MK_ERROR_DENIED` | Operation not permitted: read-only file opened for write, or required access flag was not set at open time. |
| `K_MK_ERROR_WRITE_PROTECT` | Storage device is hardware write-protected. |
| `K_MK_ERROR_COLLISION` | Short name (8.3) generation exceeded the maximum allowed collision count. |
| `K_MK_ERROR_UNEXPECTED` | RTC could not provide a valid timestamp for the directory entry. |

---

## See also

- [Kernel internals](Kernel-API) — tasks, memory pools, synchronisation objects
- [Build a graphical application](Graphical-Engine) — containers, widgets, painters, listeners
- [Handle input events](Event-System) — listeners, keyboard, mouse, joystick and HID events
