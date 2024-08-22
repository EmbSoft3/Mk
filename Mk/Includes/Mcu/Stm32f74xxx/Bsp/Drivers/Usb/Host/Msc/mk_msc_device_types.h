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
* @file mk_msc_device_types.h
* @brief Déclaration des types dédiés aux périphériques de stockage.
* @date 17 mai 2020
*
*/

#ifndef MK_MSC_DEVICE_TYPES_H
#define MK_MSC_DEVICE_TYPES_H

/**
 * @struct T_mkStorageDeviceState
 * @brief Déclaration de la structure T_mkStorageDeviceState.
 *
 */

typedef enum T_mkStorageDeviceState
{
   K_MK_MSC_DEVICE_NOT_INIT_STATE = 0,                /*!< Définition d'un état indiquant que le périphérique MSC n'est pas initialisé. */
   K_MK_MSC_DEVICE_CONFIGURED_STATE = 1,              /*!< Définition d'un état indiquant que le périphérique MSC est configuré. */
   K_MK_MSC_DEVICE_NOT_SUPPORTED = 2,                 /*!< Définition d'un état indiquant que le périphérique MSC n'est pas supporté. */
   K_MK_MSC_DEVICE_ERROR_STATE = 4                    /*!< Définition d'un état indiquant que le périphérique MSC est en erreur (erreur de communication n'ont récupérable). */
} T_mkStorageDeviceState;

/**
 * @struct T_mkStorageDeviceState
 * @brief Déclaration de la structure T_mkStorageDeviceState.
 *
 */

typedef enum T_mkStorageDeviceStatus
{
   K_MK_MSC_DEVICE_STATUS_CMD_PASSED = 0,             /*!< Définition du statut "CMD_PASSED" du protocole "BulkOnly". */
   K_MK_MSC_DEVICE_STATUS_CMD_FAILED = 1,             /*!< Définition du statut "CMD_FAILED" du protocole "BulkOnly". */
   K_MK_MSC_DEVICE_STATUS_PHASE_ERROR = 2,            /*!< Définition du statut "PHASE_ERRROR" du protocole "BulkOnly". */
   K_MK_MSC_DEVICE_STATUS_REQUEST_NOT_COMPLETED = 3,  /*!< Définition du statut "REQUEST_NOT_COMPLETED" du protocole "BulkOnly". */
   K_MK_MSC_DEVICE_STATUS_CMD_STALLED = 4             /*!< Définition du statut "CMD_STALLED" du protocole "BulkOnly". */
} T_mkStorageDeviceStatus;

/**
 * @struct T_mkMSCDeviceLayer
 * @brief Déclaration de la structure T_mkMSCDeviceLayer.
 *
 */

typedef struct T_mkMSCDeviceLayer T_mkMSCDeviceLayer;
struct T_mkMSCDeviceLayer
{
   uint32_t type;                                     /*!< Ce membre contient le type du périphérique de stockage. La position de cet attribut ne doit pas être modifiée. */
   uint8_t numberOfLUN;                               /*!< Ce membre contient le nombre d'unités logiques du périphérique MSC. */
   uint8_t padding24 [3];                             /*!< Padding. */
};

/**
 * @struct T_mkMSCDevice
 * @brief Déclaration de la structure T_mkMSCDevice.
 *
 */

typedef struct T_mkMSCDevice T_mkMSCDevice;
struct T_mkMSCDevice
{
   T_mkMSCDeviceLayer layer;                          /*!< Ce membre contient les caractéristiques du périphérique MSC. La position de cet attribut ne doit pas être modifiée. */
   T_mkHCDDevice* device;                             /*!< Ce membre contient l'adresse du périphérique HCD propriétaire du périphérique MSC. */
   T_mkMSCDevice* next;                               /*!< Ce membre contient l'adresse du prochain périphérique MSC ou la valeur \ref K_MK_NULL. */
   T_mkMSCDevice* previous;                           /*!< Ce membre contient l'adresse du précédent périphérique MSC ou la valeur \ref K_MK_NULL. */

   T_mkStorageDeviceState state;                      /*!< Ce membre contient l'état opérationnel du périphérique MSC. */
   T_mkStorageDeviceStatus status;                    /*!< Ce membre contient le registre de statut "BulkOnly" du périphérique MSC. */

   T_mkHCDInterfaceDescriptor* interface;             /*!< Ce membre contient l'adresse de l'interface MSC dédiée au périphérique. */
   T_mkHCDEndpointDescriptor* inEndpoint;             /*!< Ce membre contient l'adresse de la terminaison de type BULK-IN du périphérique MSC. */
   T_mkHCDEndpointDescriptor* outEndpoint;            /*!< Ce membre contient l'adresse de la terminaison de type BULK-OUT du périphérique MSC. */
   T_mkHCDPipe ctrlPipe;                              /*!< Ce membre contient l'adresse du pipe de contrôle dédié aux protocoles de communication (BBB, CBI, ...). */
   T_mkHCDPipe inPipe;                                /*!< Ce membre contient l'adresse du pipe de données (IN) dédié aux protocoles de communication (BBB, CBI, ...). */
   T_mkHCDPipe outPipe;                               /*!< Ce membre contient l'adresse du pipe de données (OUT) dédié aux protocoles de communication (BBB, CBI, ...). */

   T_mkDisk* disk;                                    /*!< Ce membre contient l'adresse d'un ou plusieurs disques ou la valeur \ref K_MK_NULL. */
};


/**
 *
 */

#endif

