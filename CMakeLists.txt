################################################################################
# CMakeLists.txt — OS Mk, ARM Cortex-M7 bare-metal project
#
# The kernel (mk-kernel) is integrated as a git submodule in Mk/Kernel/:
#
#   git submodule add <url-mk-kernel> Mk/Kernel
#   git clone --recurse-submodules <url-os>
#   git submodule update --init --recursive      (after a plain clone)
#
# Requirements:
#   - arm-none-eabi-gcc in PATH (Linux/macOS)
#     or TOOLCHAIN_PATH defined below (Windows)
#   - CMake >= 3.25
#   - Ninja (recommended for cross-compilation with Visual Studio)
#
# Usage from command line:
#
#   cmake -B build -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=CMake/arm-none-eabi-toolchain.cmake \
#         -DBOARD=EVAL2 \
#         -DCMAKE_BUILD_TYPE=Release
#   cmake --build build
#
# Usage from Visual Studio (CMakeSettings.json or CMakePresets.json):
#   See cmake/CMakePresets.json provided alongside.
################################################################################

cmake_minimum_required(VERSION 3.25)

# The toolchain must be defined BEFORE project()
# It is passed as an argument (-DCMAKE_TOOLCHAIN_FILE=...) or via a preset.

project(Mk
    LANGUAGES C ASM
    VERSION   1.0.0
    DESCRIPTION "ARM Cortex-M7 bare-metal firmware"
)

################################################################################
# Board
################################################################################

set(BOARD "EVAL2" CACHE STRING "Target board (EVAL2 | DISCO_REV_C)")
set_property(CACHE BOARD PROPERTY STRINGS EVAL2 DISCO_REV_C)

if(BOARD STREQUAL "EVAL2")
    set(BOARD_DEFINE MK_BOARD_EVAL2)
elseif(BOARD STREQUAL "DISCO_REV_C")
    set(BOARD_DEFINE MK_BOARD_DISCO_REV_C)
else()
    message(FATAL_ERROR "Unknown BOARD=${BOARD}. Use EVAL2 or DISCO_REV_C.")
endif()

message(STATUS "Board : ${BOARD}  (${BOARD_DEFINE})")

################################################################################
# Kernel (git submodule)
################################################################################

set(KERNEL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Kernel")

if(NOT EXISTS "${KERNEL_PATH}/CMakeLists.txt")
    message(FATAL_ERROR
        "Kernel submodule missing or empty: '${KERNEL_PATH}'.\n"
        "Run: git submodule update --init --recursive")
endif()

add_subdirectory(Mk/Kernel)

################################################################################
# Paths
################################################################################

set(SOURCES_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Sources")
set(INCLUDES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Includes")
set(LD_SCRIPT     "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Make/linker.ld")
set(SYMBOL_BASE_ADDR "0x002C0000")

# Sanity checks
if(NOT EXISTS "${SOURCES_PATH}")
    message(FATAL_ERROR "SOURCES_PATH '${SOURCES_PATH}' not found.")
endif()
if(NOT EXISTS "${INCLUDES_PATH}")
    message(FATAL_ERROR "INCLUDES_PATH '${INCLUDES_PATH}' not found.")
endif()
if(NOT EXISTS "${LD_SCRIPT}")
    message(FATAL_ERROR "Linker script '${LD_SCRIPT}' not found.")
endif()

################################################################################
# Sources (OS-specific: the kernel is built by mk_kernel)
################################################################################

# Recursively collect .c and .asm files
file(GLOB_RECURSE C_SOURCES   CONFIGURE_DEPENDS "${SOURCES_PATH}/*.c")
file(GLOB_RECURSE ASM_SOURCES CONFIGURE_DEPENDS "${SOURCES_PATH}/*.asm")

# Recursively collect include directories
file(GLOB_RECURSE ALL_HEADERS CONFIGURE_DEPENDS
    "${INCLUDES_PATH}/*.h"
    "${INCLUDES_PATH}/*.asm"
)

# Extract unique directories from header list
set(INCLUDE_DIRS "${INCLUDES_PATH}")
foreach(_hdr IN LISTS ALL_HEADERS)
    get_filename_component(_dir "${_hdr}" DIRECTORY)
    list(APPEND INCLUDE_DIRS "${_dir}")
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

################################################################################
# Assembler file properties
#
# .asm files require -x assembler-with-cpp to be treated
# as assembly with C preprocessor.
################################################################################

set_source_files_properties(${ASM_SOURCES} PROPERTIES
    LANGUAGE ASM
    COMPILE_OPTIONS "-x;assembler-with-cpp"
)

################################################################################
# Executable
################################################################################

add_executable(${PROJECT_NAME}
    ${C_SOURCES}
    ${ASM_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME          "${PROJECT_NAME}"
    SUFFIX               ".elf"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${BOARD_DEFINE})

# Link ALL kernel objects (OBJECT library, not a .a archive):
# required so every function exported to ELF applications is present
# in the image and therefore in the symbol table (sym2srec),
# even if neither the kernel nor the OS calls it. Also inherits kernel
# headers (mk_api.h) and the board definition as PUBLIC.
target_link_libraries(${PROJECT_NAME} PRIVATE mk_kernel)

################################################################################
# C dialect compilation options
################################################################################

set(CDIAL_OPTIONS
    -std=c18
    -fno-asm
    -fno-builtin
    -fno-cond-mismatch
    -ffreestanding
    -fsigned-bitfields
    -fsigned-char
    -fsso-struct=little-endian
)

################################################################################
# ARM options
#
# Must be kept strictly identical to those of the kernel (same ABI, same FPU).
################################################################################

set(ARM_OPTIONS
    -mcpu=cortex-m7
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -mno-unaligned-access
    -mlittle-endian
)

################################################################################
# Warnings
################################################################################

set(WARN_OPTIONS
    -Wpedantic -pedantic-errors -Werror -Wall -Wextra
    -Wdouble-promotion -Wnull-dereference -Wshift-negative-value
    -Wswitch-default -Wswitch-enum -Wswitch-bool -Wswitch-unreachable
    -Wstrict-overflow=5 -Wduplicated-branches -Wduplicated-cond
    -Wdiscarded-qualifiers -Wdiscarded-array-qualifiers
    -Wincompatible-pointer-types -Wint-conversion -Wint-to-pointer-cast
    -Wpointer-to-int-cast -Wdiv-by-zero -Wsystem-headers -Wtrampolines
    -Wfloat-equal -Wno-traditional -Wdeclaration-after-statement
    -Wshadow -Wshadow=local -Wunsafe-loop-optimizations -Wpointer-compare
    -Wno-undef -Wunused-macros -Wbad-function-cast
    -Wno-cast-qual -Wcast-align -Wcast-align=strict -Wwrite-strings -Wconversion
    -Wjump-misses-init -Waddress-of-packed-member -Wlogical-op
    -Waggregate-return -Waggressive-loop-optimizations -Wpointer-arith
    -Wattributes -Wstrict-prototypes -Wold-style-definition
    --warn-missing-parameter-type -Wmissing-prototypes -Wmissing-declarations
    -Wmultichar -Wnormalized=none -Wattribute-warning
    -Wdeprecated -Wdeprecated-declarations -Woverflow
    -Woverride-init-side-effects -Wpacked -Wno-packed-bitfield-compat
    -Wpadded -Wredundant-decls -Wnested-externs -Winline
    -Wno-long-long -Wvla -Woverlength-strings
)

################################################################################
# Common options (C + ASM)
################################################################################

set(COMMON_OPTIONS
    ${ARM_OPTIONS}
    -fanalyzer          # static analyzer
    -fmessage-length=0
    -nostdinc
    -fstack-usage
)

################################################################################
# Debug / Release options
#
# CMake automatically injects CMAKE_BUILD_TYPE into flags;
# we disable its default flags (CACHE "") and manage our own.
################################################################################

# Clear default CMake flags to avoid interference
set(CMAKE_C_FLAGS_DEBUG          "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE        "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_MINSIZEREL     "" CACHE STRING "" FORCE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_OPT_OPTIONS
        -g3 -ggdb -fno-eliminate-unused-debug-symbols
        -O0 -fno-inline-functions -fno-short-enums -fno-move-loop-invariants
    )
else()  # Release (default)
    set(BUILD_OPT_OPTIONS
        -Ofast -fno-inline-functions -fno-short-enums -fno-move-loop-invariants
    )
endif()

################################################################################
# Apply flags to target
################################################################################

target_compile_options(${PROJECT_NAME} PRIVATE
    # C-only options (applied to .c files)
    $<$<COMPILE_LANGUAGE:C>:
        ${CDIAL_OPTIONS}
        ${COMMON_OPTIONS}
        ${BUILD_OPT_OPTIONS}
        ${WARN_OPTIONS}
        -x c
    >
    # ASM options (-x assembler-with-cpp is set in set_source_files_properties)
    $<$<COMPILE_LANGUAGE:ASM>:
        ${COMMON_OPTIONS}
        ${BUILD_OPT_OPTIONS}
        ${WARN_OPTIONS}
    >
)

################################################################################
# Linker
################################################################################

target_link_options(${PROJECT_NAME} PRIVATE
    # Linker options
    -nostartfiles
    -nodefaultlibs
    -nolibc
    -nostdlib
    -no-pie
    -export-dynamic
    # Linker script
    -T "${LD_SCRIPT}"
    # Map file
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
)

################################################################################
# Post-build: copy, strip, sym2srec
################################################################################

# Artifact paths
set(ELF_FILE    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf")
set(STRIP_FILE  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-Strip.elf")
set(SREC_FILE   "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.srec")

if(CMAKE_HOST_WIN32)
    set(SYM2SREC "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Make/sym2srec.exe")
else()
    set(SYM2SREC "${CMAKE_CURRENT_SOURCE_DIR}/Mk/Make/sym2srec")
endif()

# Ensure binary exists
if(NOT EXISTS "${SYM2SREC}")
    message(FATAL_ERROR "sym2srec not found: ${SYM2SREC}")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${ELF_FILE}" "${STRIP_FILE}"
    COMMAND "${CMAKE_OBJCOPY_TOOL}"
            --discard-all --strip-debug "${STRIP_FILE}"
    COMMAND "${SYM2SREC}"
            "${STRIP_FILE}" "${SREC_FILE}" "${SYMBOL_BASE_ADDR}"
    COMMAND "${CMAKE_SIZE_TOOL}"
            --format=berkeley --totals "${ELF_FILE}"
    COMMENT "Post-build: copy -> strip -> srec -> size"
    VERBATIM
)

################################################################################
# Utility target 'print' (size only, no rebuild)
################################################################################

add_custom_target(print
    COMMAND ${CMAKE_SIZE_TOOL} --format=berkeley --totals "${ELF_FILE}"
    COMMENT "  SIZE  ${PROJECT_NAME}.elf"
)

################################################################################
# Configuration summary
################################################################################

message(STATUS "Build type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Kernel       : ${KERNEL_PATH} (submodule)")
message(STATUS "Sources      : ${SOURCES_PATH}")
message(STATUS "Includes     : ${INCLUDES_PATH}")
message(STATUS "Linker script: ${LD_SCRIPT}")
message(STATUS "sym2srec     : ${SYM2SREC}")