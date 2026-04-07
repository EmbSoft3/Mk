/**
*
* @copyright Copyright (C) 2026 RENARD Mathieu. All rights reserved.
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
* @file mk_termio_bsp_data.c
* @brief Déclaration des données dédiées aux BSP des terminaux d'entrées-sorties.
* @date 19 mars 2026
*
*/

#include "mk_termio_api.h"


/**
 *
 */

/* Si compilation pour la carte EVAL2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @fn T_mkTermioCtrlBlock g_mkTermioCtrlBlock;
 * @brief Déclaration du gestionnaire contenant les caractéristiques des terminaux à initialiser.
 *
 */

const T_mkTermioCtrlBlock g_mkTermioCtrlBlock [ K_MK_TERMIO_NUMBER ] =
{
   /* Attention, adapter le nombre de terminaux K_MK_TERMIO_FILESYSTEM_ID en fonction du nombre de système de fichiers K_MK_FILE_NUMBER_OF_TASKS */
   { K_MK_TERMIO_DISPATCHER_ID,     K_MK_TERMIO_DISPATCHER_PRIORITY, mk_dispatcher_task,      g_mkDispatcherStack,           K_MK_DISPATCHER_STACK_SIZE },
   { K_MK_TERMIO_MMC_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_mmc_task,             g_mkMMCStackAddr,              K_MK_MMC_STACK_SIZE },
   { K_MK_TERMIO_I2C1_ID,           K_MK_TERMIO_TASK_PRIORITY,       mk_i2c_task,             g_mkI2CStackAddr,              K_MK_I2C_STACK_SIZE },
   { K_MK_TERMIO_GPIO_ID,           K_MK_TERMIO_TASK_PRIORITY,       mk_gpio_task,            g_mkGPIOStackAddr,             K_MK_GPIO_STACK_SIZE },
   { K_MK_TERMIO_HCD_OTGHS_ID,      K_MK_TERMIO_TASK_PRIORITY,       mk_usbhs_taskDeviceMode, g_mkUSBHSDeviceStackAddr,      K_MK_USBHS_DEVICE_STACK_SIZE },
   { K_MK_TERMIO_HCD_OTGFS_ID,      K_MK_TERMIO_TASK_PRIORITY,       mk_usbfs_taskDeviceMode, g_mkUSBFSDeviceStackAddr,      K_MK_USBFS_DEVICE_STACK_SIZE },
   { K_MK_TERMIO_HID_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_hid_task,             g_mkHIDStackAddr,              K_MK_HID_STACK_SIZE },
   { K_MK_TERMIO_MSC_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_msc_task,             g_mkMSCStackAddr,              K_MK_MSC_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID,     K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 0 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 1, K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 1 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 2, K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 2 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 3, K_MK_TERMIO_TASK_PRIORITY,       mk_file_taskShared,      &g_mkFileStackAddr [ 3 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 }
};

/* Sinon si compilation pour la carte DISCO_REV_C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @fn T_mkTermioCtrlBlock g_mkTermioCtrlBlock;
 * @brief Déclaration du gestionnaire contenant les caractéristiques des terminaux à initialiser.
 *
 */

const T_mkTermioCtrlBlock g_mkTermioCtrlBlock [ K_MK_TERMIO_NUMBER ] =
{
   /* Attention, adapter le nombre de terminaux K_MK_TERMIO_FILESYSTEM_ID en fonction du nombre de système de fichiers K_MK_FILE_NUMBER_OF_TASKS */
   { K_MK_TERMIO_DISPATCHER_ID,     K_MK_TERMIO_DISPATCHER_PRIORITY, mk_dispatcher_task,      g_mkDispatcherStack,           K_MK_DISPATCHER_STACK_SIZE },
   { K_MK_TERMIO_MMC_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_mmc_task,             g_mkMMCStackAddr,              K_MK_MMC_STACK_SIZE },
   { K_MK_TERMIO_I2C3_ID,           K_MK_TERMIO_TASK_PRIORITY,       mk_i2c_task,             g_mkI2CStackAddr,              K_MK_I2C_STACK_SIZE },
   { K_MK_TERMIO_GPIO_ID,           K_MK_TERMIO_TASK_PRIORITY,       mk_gpio_task,            g_mkGPIOStackAddr,             K_MK_GPIO_STACK_SIZE },
   { K_MK_TERMIO_HCD_OTGHS_ID,      K_MK_TERMIO_TASK_PRIORITY,       mk_usbhs_taskDeviceMode, g_mkUSBHSDeviceStackAddr,      K_MK_USBHS_DEVICE_STACK_SIZE },
   { K_MK_TERMIO_HCD_OTGFS_ID,      K_MK_TERMIO_TASK_PRIORITY,       mk_usbfs_taskDeviceMode, g_mkUSBFSDeviceStackAddr,      K_MK_USBFS_DEVICE_STACK_SIZE },
   { K_MK_TERMIO_HID_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_hid_task,             g_mkHIDStackAddr,              K_MK_HID_STACK_SIZE },
   { K_MK_TERMIO_MSC_ID,            K_MK_TERMIO_TASK_PRIORITY,       mk_msc_task,             g_mkMSCStackAddr,              K_MK_MSC_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID,     K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 0 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 1, K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 1 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 2, K_MK_TERMIO_TASK_PRIORITY,       mk_file_task,            &g_mkFileStackAddr [ 2 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_FILESYSTEM_ID + 3, K_MK_TERMIO_TASK_PRIORITY,       mk_file_taskShared,      &g_mkFileStackAddr [ 3 ][ 0 ], K_MK_FILE_STACK_SIZE },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 },
   { K_MK_TERMIO_NO,                K_MK_TERMIO_TASK_PRIORITY,       K_MK_NULL,               K_MK_NULL,                     0 }
};

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif
