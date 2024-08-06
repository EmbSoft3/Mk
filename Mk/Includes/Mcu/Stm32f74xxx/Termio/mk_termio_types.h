/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_termio_types.h
* @brief Déclaration des types dédiés aux terminaux d'entrées-sorties.
* @date 9 juin 2019
*
*/

#ifndef MK_TERMIO_TYPES_H
#define MK_TERMIO_TYPES_H

/**
 * @struct T_mkTermio
 * @brief Déclaration de la structure T_mkTermio.
 *
 */

typedef struct T_mkTermio T_mkTermio;
struct T_mkTermio
{
   T_mkTask* task;                                                               /*!< Ce membre contient la tâche du terminal. */
   T_mkStack stack;                                                              /*!< Ce membre contient la stack du terminal. */
   T_mkAddr child;                                                               /*!< Ce membre pointe sur une structure de données d'un périphérique. */
};

/**
 * @struct T_mkTermioArea
 * @brief Déclaration de la structure T_mkTermioArea.
 *
 */

typedef struct T_mkTermioArea T_mkTermioArea;
struct T_mkTermioArea
{
   T_mkPool* pool;                                                               /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les terminaux. */
   T_mkPoolArea area;                                                            /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   uint32_t heap [ K_MK_TERMIO_NUMBER * ( sizeof ( T_mkTermio ) >> 2 ) ];        /*!< Ce membre contient le buffer d'allocation dynamique. */
};

/**
 * @struct T_mkTermioHandler
 * @brief Déclaration de la structure T_mkTermioHandler.
 *
 */

typedef struct T_mkTermioHandler T_mkTermioHandler;
struct T_mkTermioHandler
{
   T_mkTermio* dispatcher;                                                       /*!< Ce membre pointe sur le terminal DISPATCHER. */
   T_mkTermio* usbhs;                                                            /*!< Ce membre pointe sur le terminal USB_OTGHS. */
   T_mkTermio* usbfs;                                                            /*!< Ce membre pointe sur le terminal USB_OTGFS. */
   T_mkTermio* usbhid;                                                           /*!< Ce membre pointe sur le terminal USB_HID. */
   T_mkTermio* msc;                                                              /*!< Ce membre pointe sur le terminal USB_MSC. */
   T_mkTermio* mmc;                                                              /*!< Ce membre pointe sur le terminal MMC. */
   T_mkTermio* gpio;                                                             /*!< Ce membre pointe sur le terminal GPIO. */
   T_mkTermio* i2c1;                                                             /*!< Ce membre pointe sur le terminal I2C1. */
   T_mkTermio* i2c2;                                                             /*!< Ce membre pointe sur le terminal I2C2. */
   T_mkTermio* i2c3;                                                             /*!< Ce membre pointe sur le terminal I2C3. */
   T_mkTermio* i2c4;                                                             /*!< Ce membre pointe sur le terminal I2C4. */
   T_mkTermio* fileManager [ K_MK_FILE_NUMBER_OF_TASKS ];                        /*!< Ces membres pointent sur les terminaux FILE_SYSTEM. */
};

/**
 * @struct T_mkTermioSync
 * @brief Déclaration de la structure T_mkTermioSync.
 *
 */

typedef struct T_mkTermioSync T_mkTermioSync;
struct T_mkTermioSync
{
   T_mkEvent* event;                                                             /*!< Ce membre contient un champ d'événement qui permet de synchroniser l'initialisation des terminaux. */
};

/**
 * @enum T_mkTermioFlag
 * @brief Déclaration de l'énumération T_mkTermioFlag.
 *
 */

typedef enum T_mkTermioFlag
{
   K_MK_TERMIO_FLAG_I2C1 = 0x0001,                                               /*!< Flag signifiant la fin de l'initialisation de la tâche I2C1. */
   K_MK_TERMIO_FLAG_I2C2 = 0x0002,                                               /*!< Flag signifiant la fin de l'initialisation de la tâche I2C2. */
   K_MK_TERMIO_FLAG_I2C3 = 0x0004,                                               /*!< Flag signifiant la fin de l'initialisation de la tâche I2C3. */
   K_MK_TERMIO_FLAG_I2C4 = 0x0008,                                               /*!< Flag signifiant la fin de l'initialisation de la tâche I2C4. */
   K_MK_TERMIO_FLAG_GPIO = 0x0010,                                               /*!< Flag signifiant la fin de l'initialisation de la tâche GPIO. */
   K_MK_TERMIO_FLAG_MMC = 0x0020,                                                /*!< Flag signifiant la fin de l'initialisation de la tâche MMC. */
   K_MK_TERMIO_FLAG_MSC = 0x0040,                                                /*!< Flag signifiant la fin de l'initialisation de la tâche MSC. */
   K_MK_TERMIO_FLAG_HID = 0x0080,                                                /*!< Flag signifiant la fin de l'initialisation de la tâche HID. */
   K_MK_TERMIO_FLAG_USBHS = 0x0100,                                              /*!< Flag signifiant la fin de l'initialisation de la tâche USBHS. */
   K_MK_TERMIO_FLAG_USBFS = 0x0200,                                              /*!< Flag signifiant la fin de l'initialisation de la tâche USBFS. */
   K_MK_TERMIO_FLAG_DISPATCHER = 0x0400,                                         /*!< Flag signifiant la fin de l'initialisation de la tâche DISPATCHER. */
   K_MK_TERMIO_FLAG_FILESYSTEM = 0x0800                                          /*!< Flag signifiant la fin de l'initialisation de la tâche FILE_SYSTEM. */
} T_mkTermioFlag;

/**
 * @enum T_mkTermioIdentifier
 * @brief Déclaration de l'énumération T_mkTermioIdentifier.
 *
 */

typedef enum T_mkTermioIdentifier
{
   K_MK_TERMIO_DISPATCHER_ID = 0x0100,                                           /*!< Identifiant de la tâche du terminal DISPATCHER. */
   K_MK_TERMIO_HCD_OTGHS_ID  = 0x0200,                                           /*!< Identifiant de la tâche du terminal USB_OTGHS. */
   K_MK_TERMIO_HCD_OTGFS_ID  = 0x0201,                                           /*!< Identifiant de la tâche du terminal USB_OTGFS. */
   K_MK_TERMIO_HID_ID        = 0x0202,                                           /*!< Identifiant de la tâche du terminal USB_HID. */
   K_MK_TERMIO_MSC_ID        = 0x0203,                                           /*!< Identifiant de la tâche du terminal MSC. */
   K_MK_TERMIO_MMC_ID        = 0x0300,                                           /*!< Identifiant de la tâche du terminal MMC. */
   K_MK_TERMIO_GPIO_ID       = 0x0301,                                           /*!< Identifiant de la tâche du terminal GPIO. */
   K_MK_TERMIO_I2C1_ID       = 0x0310,                                           /*!< Identifiant de la tâche du terminal I2C1. */
   K_MK_TERMIO_I2C2_ID       = 0x0311,                                           /*!< Identifiant de la tâche du terminal I2C2. */
   K_MK_TERMIO_I2C3_ID       = 0x0312,                                           /*!< Identifiant de la tâche du terminal I2C3. */
   K_MK_TERMIO_I2C4_ID       = 0x0313,                                           /*!< Identifiant de la tâche du terminal I2C4. */
   K_MK_TERMIO_FILESYSTEM_ID = 0x03FF                                            /*!< Identifiant de la tâche des terminaux FILESYSTEM. */
} T_mkTermioIdentifier;

/**
 *
 */

#endif
