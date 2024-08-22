/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_mmc_device_types.h
* @brief Déclaration des types dédiés aux périphériques SD/MMC.
* @date 12 juin 2020
*
*/

#ifndef MK_MMC_DEVICE_TYPES_H
#define MK_MMC_DEVICE_TYPES_H

/**
 * @struct T_mkMMCOPCode
 * @brief Déclaration de l'énumération T_mkMMCOPCode.
 *
 */

typedef enum T_mkMMCType
{
   K_MK_MMC_TYPE_NOT_SUPPORTED = 0,                   /* Définition d'une constante indiquant que le média n'est pas supporté. */
   K_MK_MMC_TYPE_SD = 1,                              /* Définition d'une constante indiquant que le média est une carte SD. */
   K_MK_MMC_TYPE_MMC = 2,                             /* Définition d'une constante indiquant que le média est une carte MMC. */
   K_MK_MMC_TYPE_SDIO = 3                             /* Définition d'une constante indiquant que le média est une carte SDIO. */
} T_mkMMCType;

/**
 * @struct T_mkMMCState
 * @brief Déclaration de l'énumération T_mkMMCState.
 *
 */

typedef enum T_mkMMCState
{
   K_MK_MMC_STATE_INACTIVE = 0,                       /* Définition d'une constante indiquant que le bus est dans l'état inactif. */
   K_MK_MMC_STATE_IDLE = 1,                           /* Définition d'une constante indiquant que le bus est dans l'état de repos. */
   K_MK_MMC_STATE_READY = 2,                          /* Définition d'une constante indiquant que le bus est dans l'état prêt. */
   K_MK_MMC_STATE_IDENTIFICATION = 3,                 /* Définition d'une constante indiquant que le bus est dans l'état identification. */
   K_MK_MMC_STATE_STANDBY = 4,                        /* Définition d'une constante indiquant que le bus est dans l'état standby. */
   K_MK_MMC_STATE_TRANSFER = 5,                       /* Définition d'une constante indiquant que le bus est dans l'état en cours de tranfert. */
   K_MK_MMC_STATE_DISCONNECTED = 6                    /* Définition d'une constante indiquant qu'aucun périphérique n'est connecté sur le bus. */
} T_mkMMCState;

/**
 * @struct T_mkMMCDeviceLayer
 * @brief Déclaration de la structure T_mkMMCDeviceLayer.
 *
 */

typedef struct T_mkMMCDeviceLayer T_mkMMCDeviceLayer;
struct T_mkMMCDeviceLayer
{
   uint32_t type;                                     /*!< Ce membre contient le type du périphérique de stockage (MMC ou MSC). La position de cet attribut ne doit pas être modifiée. */
   uint32_t addr;                                     /*!< Ce membre contient l'adresse du périphérique (RCA). Elle est décalée de 16 bits pour s'adapter au format des commandes. */
   uint32_t busWidth;                                 /*!< Ce membre contient la largeur du bus de données (\ref T_mkMMCBusWidth). */
   uint32_t blockLength;                              /*!< Ce membre contient la longueur d'un bloc de données. */
   uint32_t multiplier;                               /*!< Ce membre contient la valeur du multiplicateur d'adresse (par décalage). */
};

/**
 * @struct T_mkMMCDevice
 * @brief Déclaration de la structure T_mkMMCDevice.
 *
 */

typedef struct T_mkMMCDevice T_mkMMCDevice;
struct T_mkMMCDevice
{
   T_mkMMCDeviceLayer layer;                          /*!< Ce membre contient les caractéristiques de base du périphérique. La position de cet attribut ne doit pas être modifiée. */
   T_mkMMCType type;                                  /*!< Ce membre contient le type du périphérique (\ref T_mkMMCType). */
   T_mkMMCState state;                                /*!< Ce membre contient l'état du périphérique (\ref T_mkMMCState). */
   T_mkMMCPortStatus portStatus;                      /*!< Ce membre contient le registre de statut matériel. */
   T_mkMMCCStatusRegister status;                     /*!< Ce membre contient le registre de statut du périphérique. */
   T_mkAddr handler;                                  /*!< Ce membre contient l'adresse du gestionnnaire de communication MMC. */
   T_mkMMCDevice* next;                               /*!< Ce membre contient l'adresse du prochain périphérique dans la liste ou la valeur \ref K_MK_NULL. */
   T_mkMMCDevice* previous;                           /*!< Ce membre contient l'adresse du précédent périphérique dans la liste ou la valeur \ref K_MK_NULL. */
   T_mkDisk* disk;                                    /*!< Ce membre contient l'adresse d'un disque de type \ref T_mkDisk. */
};

/**
 *
 */

#endif

