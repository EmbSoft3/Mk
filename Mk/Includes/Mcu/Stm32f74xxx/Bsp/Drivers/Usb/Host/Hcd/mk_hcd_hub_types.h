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
* @file mk_hcd_hub_types.h
* @brief Déclaration des types dédiés aux hubs du module "HCD".
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_HUB_TYPES_H
#define MK_HCD_HUB_TYPES_H

/**
 * @enum T_mkHCDHubFeature
 * @brief Déclaration du type T_mkHCDHubFeature.
 */

typedef enum T_mkHCDHubFeature
{
   K_MK_HCD_CHANGE_HUB_LOCALPOWER = 0,                         /*!< Valeur définie par la spécification USB2.0 => HUB_LOCALPOWER_FEATURE */
   K_MK_HCD_CHANGE_HUB_OVERCURRENT = 1                         /*!< Valeur définie par la spécification USB2.0 => HUB_OVERCURRENT_FEATURE */
} T_mkHCDHubFeature;

/**
 * @enum T_mkHCDHubFeature
 * @brief Déclaration du type T_mkHCDHubFeature.
 */

typedef enum T_mkHCDPortFeature
{
   K_MK_HCD_PORT_CONNECTION = 0x00,                            /*!< Valeur définie par la spécification USB2.0 => PORT_CONNECTION_FEATURE */
   K_MK_HCD_PORT_ENABLE = 0x01,                                /*!< Valeur définie par la spécification USB2.0 => PORT_ENABLE_FEATURE */
   K_MK_HCD_PORT_SUSPEND = 0x02,                               /*!< Valeur définie par la spécification USB2.0 => PORT_SUSPEND_FEATURE */
   K_MK_HCD_PORT_OVERCURRENT = 0x03,                           /*!< Valeur définie par la spécification USB2.0 => PORT_OVERCURRENT_FEATURE */
   K_MK_HCD_PORT_RESET = 0x04,                                 /*!< Valeur définie par la spécification USB2.0 => PORT_RESET_FEATURE */
   K_MK_HCD_PORT_POWER = 0x08,                                 /*!< Valeur définie par la spécification USB2.0 => PORT_POWER_FEATURE */
   K_MK_HCD_PORT_LOW_SPEED = 0x09,                             /*!< Valeur définie par la spécification USB2.0 => PORT_LS_SPEED_FEATURE */
   K_MK_HCD_CHANGE_PORT_CONNECTION = 0x10,                     /*!< Valeur définie par la spécification USB2.0 => PORT_CONNECTION_CHANGED_FEATURE */
   K_MK_HCD_CHANGE_PORT_ENABLE = 0x11,                         /*!< Valeur définie par la spécification USB2.0 => PORT_ENABLE_CHANGED_FEATURE */
   K_MK_HCD_CHANGE_PORT_SUSPEND = 0x12,                        /*!< Valeur définie par la spécification USB2.0 => PORT_SUSPEND_CHANGED_FEATURE */
   K_MK_HCD_CHANGE_PORT_OVERCURRENT = 0x13,                    /*!< Valeur définie par la spécification USB2.0 => PORT_OVERCURRENT_CHANGED_FEATURE */
   K_MK_HCD_CHANGE_PORT_RESET = 0x14,                          /*!< Valeur définie par la spécification USB2.0 => PORT_RESET_CHANGED_FEATURE */
   K_MK_HCD_PORT_TEST = 0x15,                                  /*!< Valeur définie par la spécification USB2.0 => PORT_TEST_FEATURE */
   K_MK_HCD_PORT_INDICATOR = 0x16                              /*!< Valeur définie par la spécification USB2.0 => PORT_INDICATOR_FEATURE */
} T_mkHCDPortFeature;

/**
 * @enum T_mkHCDHubFeature
 * @brief Déclaration du type T_mkHCDHubFeature.
 */

typedef enum T_mkHCDPortEvent
{
   K_MK_HCD_PORT_EVENT_NOT_DETECTED = 0,                       /*!< Valeur indiquant qu'aucun événement n'a été détecté sur le port USB. */
   K_MK_HCD_PORT_EVENT_DETECTED = 1                            /*!< Valeur indiquant qu'au moins un événement a été détecté sur le port USB. */
} T_mkHCDPortEvent;

/**
 * @struct T_mkHCDPortStatus
 * @brief Déclaration de la structure T_mkHCDPortStatus.
 *
 */

typedef struct T_mkHCDPortStatus T_mkHCDPortStatus;
struct T_mkHCDPortStatus
{
   unsigned_t currentConnectStatus:1;                            /*!< Champ défini par la spécification USB2.0 => CURRENT_CONNECT_STATUS */
   unsigned_t portEnabledDisabled:1;                             /*!< Champ défini par la spécification USB2.0 => PORT_ENABLED_DISABLED_STATUS */
   unsigned_t suspend:1;                                         /*!< Champ défini par la spécification USB2.0 => SUSPEND_STATUS */
   unsigned_t overCurrent:1;                                     /*!< Champ défini par la spécification USB2.0 => OVERCURRENT_STATUS */
   unsigned_t reset:1;                                           /*!< Champ défini par la spécification USB2.0 => RESET_STATUS */
   unsigned_t reserved1:3;                                       /*!< Champ défini par la spécification USB2.0 => RESERVED */
   unsigned_t portPower:1;                                       /*!< Champ défini par la spécification USB2.0 => PORT_POWER_STATUS */
   unsigned_t lowSpeedDeviceAttached:1;                          /*!< Champ défini par la spécification USB2.0 => LS_DEVICE_STATUS */
   unsigned_t highSpeedDeviceAttached:1;                         /*!< Champ défini par la spécification USB2.0 => HS_DEVICE_STATUS */
   unsigned_t portTestMode:1;                                    /*!< Champ défini par la spécification USB2.0 => TEST_MODE_STATUS */
   unsigned_t portIndicatorControl:1;                            /*!< Champ défini par la spécification USB2.0 => PORT_INDICATOR_STATUS */
   unsigned_t reserved2:3;                                       /*!< Champ défini par la spécification USB2.0 => RESERVED */

   unsigned_t connectStatusChange:1;                             /*!< Champ défini par la spécification USB2.0 => CURRENT_CONNECT_STATUS_CHANGED */
   unsigned_t portEnableDisableChange:1;                         /*!< Champ défini par la spécification USB2.0 => PORT_ENABLED_DISABLED_STATUS_CHANGED */
   unsigned_t suspendChange:1;                                   /*!< Champ défini par la spécification USB2.0 => SUSPEND_STATUS_CHANGED */
   unsigned_t overCurrentIndicatorChange:1;                      /*!< Champ défini par la spécification USB2.0 => OVERCURRENT_STATUS_CHANGED */
   unsigned_t resetChange:1;                                     /*!< Champ défini par la spécification USB2.0 => RESET_STATUS_CHANGED */
   unsigned_t reserved3:11;                                      /*!< Champ défini par la spécification USB2.0 => RESERVED */
};

/**
 * @struct T_mkHCDHubStatus
 * @brief Déclaration de la structure T_mkHCDHubStatus.
 *
 */

typedef struct T_mkHCDHubStatus T_mkHCDHubStatus;
struct T_mkHCDHubStatus
{
   unsigned_t localPowerSource:1;                                /*!< Champ défini par la spécification USB2.0 => POWER_SUPPLY_STATUS */
   unsigned_t overCurrent:1;                                     /*!< Champ défini par la spécification USB2.0 => OVERCURRENT_STATUS */
   unsigned_t reserved1:14;                                      /*!< Champ défini par la spécification USB2.0 => RESERVED */

   unsigned_t localPowerStatusChange:1;                          /*!< Champ défini par la spécification USB2.0 => POWER_SUPPLY_STATUS_CHANGED */
   unsigned_t overCurrentChange:1;                               /*!< Champ défini par la spécification USB2.0 => OVERCURRENT_STATUS_CHANGED */
   unsigned_t reserved2:14;                                      /*!< Champ défini par la spécification USB2.0 => RESERVED */
};

/**
 * @struct T_mkHCDStringDescriptor
 * @brief Déclaration de la structure T_mkHCDStringDescriptor.
 *
 */

typedef struct T_mkHCDHubDescriptor T_mkHCDHubDescriptor;
struct T_mkHCDHubDescriptor
{
   /**
    * @note L'intégralité du descripteur n'est pas récupéré car il possède des champs dont la longueur est fonction du nombre de port.
    *       Un buffer de 32 octets (255 ports + hub) est ajouté afin de récupérer le statut des ports d'un hub lors d'une requête d'interruption.
    */

   uint8_t bLength;                                            /*!< Champ défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t bDesciptorType;                                     /*!< Champ défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint8_t bNbrPorts;                                          /*!< Champ défini par la spécification USB2.0 => PORT_NUMBER */
   uint8_t bHubCharacteristics;                                /*!< Champ défini par la spécification USB2.0 => HUB_CHARACTERISTICS */
   uint8_t bReserved;                                          /*!< Champ défini par la spécification USB2.0 => RESERVED */
   uint8_t bPwrOn2PwrGood;                                     /*!< Champ défini par la spécification USB2.0 => POWER_ON_TIMEOUT */
   uint8_t bHubContrCurrent;                                   /*!< Champ défini par la spécification USB2.0 => MAX_CURRENT_CONSUMPTION */
   uint8_t bDeviceRemovable;                                   /*!< Champ défini par la spécification USB2.0 => POWER_SUPPLY_MODE */

   uint8_t bStatusBuf [ 32 ];                                  /*!< Ce champ est utilisé pour récupérer les informations d'un hub possèdant 255 ports (max). */
   T_mkHCDHubStatus hHubStatus;                                /*!< Ce champ est utilisé pour récupérer le statut du hub. */
   T_mkHCDPortStatus hPortStatus;                              /*!< Ce champ est utilisé pour récupérer le statut d'un port USB du hub. */
};

/**
 *
 */

#endif

