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
* @file mk_hcd_device_types.h
* @brief Déclaration des types dédiées aux périphériques USB.
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_DEVICE_TYPES_H
#define MK_HCD_DEVICE_TYPES_H

/**
 * @struct T_mkHCDDeviceQualifier
 * @brief Déclaration de la structure T_mkHCDDeviceQualifier.
 *
 */

typedef struct T_mkHCDDeviceQualifier T_mkHCDDeviceQualifier;
struct T_mkHCDDeviceQualifier
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint8_t  bcdUSB [ 2 ];                                                        /*!< Ce champ est défini par la spécification USB2.0 => USB_REVISON */
   uint8_t  bDeviceClass;                                                        /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_CLASS */
   uint8_t  bDeviceSubClass;                                                     /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_SUBCLASS */
   uint8_t  bDeviceProtocol;                                                     /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_PROTOCOL */
   uint8_t  bMaxPacketSize0;                                                     /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT0_MPS */
   uint8_t  bNumConfigurations;                                                  /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_NUMBER */
   uint8_t  bReserved;                                                           /*!< Ce champ est défini par la spécification USB2.0 => RESERVED */
   uint16_t wPadding;                                                            /*!< PADDING */
};

/**
 * @struct T_mkHCDDeviceDescriptor
 * @brief Déclaration de la structure T_mkHCDDeviceDescriptor.
 *
 */

typedef struct T_mkHCDDeviceDescriptor T_mkHCDDeviceDescriptor;
struct T_mkHCDDeviceDescriptor
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint8_t  bcdUSB [ 2 ];                                                        /*!< Ce champ est défini par la spécification USB2.0 => USB_REVISON */
   uint8_t  bDeviceClass;                                                        /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_CLASS */
   uint8_t  bDeviceSubClass;                                                     /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_SUBCLASS */
   uint8_t  bDeviceProtocol;                                                     /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_PROTOCOL */
   uint8_t  bMaxPacketSize0;                                                     /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT0_MPS */
   uint16_t idVendor;                                                            /*!< Ce champ est défini par la spécification USB2.0 => VENDOR_ID */
   uint16_t idProduct;                                                           /*!< Ce champ est défini par la spécification USB2.0 => PRODUCT_ID */
   uint8_t  bcdDevice [ 2 ];                                                     /*!< Ce champ est défini par la spécification USB2.0 => DEVICE_RELEASE_NUMBER */
   uint8_t  iManufacturer;                                                       /*!< Ce champ est défini par la spécification USB2.0 => MANUFACTURER_INDEX */
   uint8_t  iProduct;                                                            /*!< Ce champ est défini par la spécification USB2.0 => PRODUCT_INDEX */
   uint8_t  iSerialNumber;                                                       /*!< Ce champ est défini par la spécification USB2.0 => PRODUCT_SERIAL_NUMBER */
   uint8_t  bNumConfigurations;                                                  /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_NUMBER */
   uint16_t wPadding;                                                            /*!< PADDING */
};

/**
 * @struct T_mkHCDEndpointTick
 * @brief Déclaration de la structure T_mkHCDEndpointTick.
 *
 */

typedef struct T_mkHCDEndpointTick T_mkHCDEndpointTick;
struct T_mkHCDEndpointTick
{
   uint32_t period;                                                              /*!< Ce membre contient la période de rafraichissement d'une terminaison en milliseconde. */
};

/**
 * @struct T_mkHCDEndpointDescriptor
 * @brief Déclaration de la structure T_mkHCDEndpointDescriptor.
 *
 */

typedef struct T_mkHCDEndpointDescriptor T_mkHCDEndpointDescriptor;
struct T_mkHCDEndpointDescriptor
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint8_t  bEndpointAddress;                                                    /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_NUMBER_DIRECTION */
   uint8_t  bmAttributes;                                                        /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_ATTRIBUTE */
   uint16_t wMaxPacketSize;                                                      /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_MAX_PACKET_SIZE */
   uint8_t  bInterval;                                                           /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_INTERVAL */
   uint8_t  bRefresh;                                                            /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_REFRESH (AUDIO DEVICE ONLY) */
   uint8_t  bSynchAddress;                                                       /*!< Ce champ est défini par la spécification USB2.0 => SYNC_ADDRESS (AUDIO DEVICE ONLY) */
   uint8_t  bToken;                                                              /*!< Ce membre contient la valeur du token utilisé pour les transaction USB. */
   uint16_t wPadding;                                                            /*!< PADDING. */
   T_mkHCDEndpointTick tick;                                                     /*!< Ce membre contient la période de rafraichissement de la terminaison [en ms]. */
   T_mkHCDEndpointDescriptor* nextEndpoint;                                      /*!< Ce membre contient l'adresse de la prochaine terminaison de l'interface. */
};

/**
 * @struct T_mkHCDInterfaceDescriptor
 * @brief Déclaration de la structure T_mkHCDInterfaceDescriptor.
 *
 */

typedef struct T_mkHCDInterfaceDescriptor T_mkHCDInterfaceDescriptor;
struct T_mkHCDInterfaceDescriptor
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint8_t  bInterfaceNumber;                                                    /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_NUMBER */
   uint8_t  bAlternateSetting;                                                   /*!< Ce champ est défini par la spécification USB2.0 => ALTERNATE_INTERFACE */
   uint8_t  bNumEndpoints;                                                       /*!< Ce champ est défini par la spécification USB2.0 => ENDPOINT_NUMBER */
   uint8_t  bInterfaceClass;                                                     /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_CLASS */
   uint8_t  bInterfaceSubClass;                                                  /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_SUBCLASS */
   uint8_t  bInterfaceProtocol;                                                  /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_PROTOCOL */
   uint8_t  iInteface;                                                           /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_INDEX */

   uint8_t  bPadding;                                                            /*!< PADDING */
   uint16_t wPadding;                                                            /*!< PADDING */

   T_mkHCDInterfaceDescriptor* nextInterface;                                    /*!< Ce membre contient l'adresse de la prochaine interface de la configuration. */
   T_mkHCDEndpointDescriptor*  endpoint;                                         /*!< Ce membre contient l'adresse de la première terminaison de l'interface. */
   T_mkAddr child;                                                               /*!< Ce membre contient l'adresse d'un périphérique enfant (\ref T_mkHIDDevice, \ref T_mkMSCDevice, ...). */
};

/**
 * @struct T_mkHCDConfigurationDescriptor
 * @brief Déclaration de la structure T_mkHCDConfigurationDescriptor.
 *
 */

typedef struct T_mkHCDConfigurationDescriptor T_mkHCDConfigurationDescriptor;
struct T_mkHCDConfigurationDescriptor
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint16_t wTotalLength;                                                        /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TOTAL_LENGTH */
   uint8_t  bNumInterfaces;                                                      /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_NUMBER */
   uint8_t  bConfigurationValue;                                                 /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_VALUE */
   uint8_t  iConfiguration;                                                      /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_INDEX */
   uint8_t  bmAttributes;                                                        /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_ATTRIBUTE */
   uint8_t  bMaxPower;                                                           /*!< Ce champ est défini par la spécification USB2.0 => MAX_CURRENT_CONSUMPTION */

   uint8_t  bPadding;                                                            /*!< PADDING */
   uint16_t wPadding;                                                            /*!< PADDING */
};

/**
 * @struct T_mkHCDOtherSpeedConfiguration
 * @brief Déclaration de la structure T_mkHCDOtherSpeedConfiguration.
 *
 */

typedef struct T_mkHCDOtherSpeedConfiguration T_mkHCDOtherSpeedConfiguration;
struct T_mkHCDOtherSpeedConfiguration
{
   uint8_t  bLength;                                                             /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_LENGTH */
   uint8_t  bDesciptorType;                                                      /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TYPE */
   uint16_t wTotalLength;                                                        /*!< Ce champ est défini par la spécification USB2.0 => DESCRIPTOR_TOTAL_LENGTH */
   uint8_t  bNumInterfaces;                                                      /*!< Ce champ est défini par la spécification USB2.0 => INTERFACE_NUMBER */
   uint8_t  bConfigurationValue;                                                 /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_VALUE */
   uint8_t  iConfiguration;                                                      /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_INDEX */
   uint8_t  bmAttributes;                                                        /*!< Ce champ est défini par la spécification USB2.0 => CONFIGURATION_ATTRIBUTE */
   uint8_t  bMaxPower;                                                           /*!< Ce champ est défini par la spécification USB2.0 => MAX_CURRENT_CONSUMPTION */

   uint8_t  bPadding;                                                            /*!< PADDING */
   uint16_t wPadding;                                                            /*!< PADDING */
};

/**
 * @struct T_mkHCDDeviceStatus
 * @brief Déclaration de la structure T_mkHCDDeviceStatus.
 *
 */

typedef struct T_mkHCDDeviceStatus T_mkHCDDeviceStatus;
struct T_mkHCDDeviceStatus
{
   unsigned_t selfPowered:1;                                                       /*!< Ce champ est défini par la spécification USB2.0 => SELF_POWER_STATUS */
   unsigned_t remoteWakeup:1;                                                      /*!< Ce champ est défini par la spécification USB2.0 => REMOTE_WAKEUP_STATUS */
   unsigned_t reserved:30;                                                         /*!< Ce champ est défini par la spécification USB2.0 => RESERVED */
};

/**
 * @struct T_mkHCDDeviceLayer
 * @brief Déclaration de la structure T_mkHCDDeviceLayer.
 *
 */

typedef struct T_mkHCDDeviceLayer T_mkHCDDeviceLayer;
struct T_mkHCDDeviceLayer
{
   uint8_t deviceAddr;                                                           /*!< Ce membre contient l'adresse unique du périphérique (entre 1 et 127). */
   uint8_t speed;                                                                /*!< Ce membre contient la vitesse du périphérique (LS, FS et HS). */
   uint8_t hubAddr;                                                              /*!< Ce membre contient l'adresse unique du hub où est connecté le périphérique. */
   uint8_t portNumber;                                                           /*!< Ce membre contient le numéro du port où est connecté le périphérique. */
   uint8_t hubSplitAddr;                                                         /*!< Ce membre contient l'adresse unique du hub devant effectuer les transactions de type SPLIT. */
   uint8_t portSplitNumber;                                                      /*!< Ce membre contient le numéro du port effectuant les transactions de type SPLIT. */
   uint8_t token;                                                                /*!< Ce membre contient la valeur du token utilisé pour les transaction USB. */
   uint8_t padding;                                                              /*!< Ce champ est reservé pour un usage ultérieur. */
};

/**
 * @struct T_mkHCDDeviceState
 * @brief Déclaration de la structure T_mkHCDDeviceState.
 *
 */

typedef enum T_mkHCDDeviceState
{
   K_MK_HCD_DEVICE_ATTACHED_STATE = 0,                                           /*!< Code indiquant que le périphérique est connecté sur le bus USB. */
   K_MK_HCD_DEVICE_ADDRESSED_STATE = 1,                                          /*!< Code indiquant que le périphérique possède une adresse. */
   K_MK_HCD_DEVICE_CONFIGURED_STATE = 2,                                         /*!< Code indiquant que le périphérique est configuré. */
   K_MK_HCD_DEVICE_DISPATCHED_STATE = 4,                                         /*!< Code indiquant que le périphérique est configuré et qu'il a été pris en charge par le terminal de traitement adéquate. */
   K_MK_HCD_DEVICE_NOT_VALID = 8,                                                /*!< Code indiquant que le périphérique est invalide. */
   K_MK_HCD_DEVICE_OVERCURRENT = 16,                                             /*!< Code indiquant que le périphérique a provoqué une surcharge. */
   K_MK_HCD_DEVICE_DISCONNECTED = 32                                             /*!< Code indiquant que le périphérique a été déconnecté. */
} T_mkHCDDeviceState;

/**
 * @struct T_mkHCDDeviceFlag
 * @brief Déclaration de la structure T_mkHCDDeviceFlag.
 *
 */

typedef struct T_mkHCDDeviceFlag T_mkHCDDeviceFlag;
struct T_mkHCDDeviceFlag
{
   T_mkEvent* event;                                                             /*!< Ce membre contient le registre de statut pemettant de déterminer si un périphérique USB peut être désalloué. */
};

/**
 * @struct T_mkHCDDevice
 * @brief Déclaration de la structure T_mkHCDDevice.
 *
 */

typedef struct T_mkHCDDevice  T_mkHCDDevice;
struct T_mkHCDDevice
{
   T_mkAddr handler;                                                             /*!< Ce champ pointe sur un gestionnaire USB de type \ref T_mkHCDHandler. */

   T_mkHCDDeviceLayer layer;                                                     /*!< Ce membre contient les caractéristiques de base du périphérique USB. */
   T_mkHCDDeviceState state;                                                     /*!< Ce membre contient le registre d'état du périphérique USB. */
   T_mkHCDDeviceFlag  flag;                                                      /*!< Ce membre contient le registre de statut permettant de déterminer si un périphérique USB peut être désalloué. */
   T_mkHCDDeviceStatus status;                                                   /*!< Ce membre contient le registre de statut du périphérique USB. */

   T_mkHCDDevice* next;                                                          /*!< Ce membre contient l'adresse du prochain périphérique de la liste (rebouclée sur elle-même). */
   T_mkHCDDevice* previous;                                                      /*!< Ce membre contient l'adresse du précédent périphérique de la liste (rebouclée sur elle-même). */

   T_mkHCDDevice* nextDevice;                                                    /*!< Ce membre contient l'adresse du prochain périphérique connecté sur le hub. */
   T_mkHCDDevice* previousDevice;                                                /*!< Ce membre contient l'adresse du précédent périphérique connecté sur le hub. */
   T_mkHCDDevice* nextHubDevice;                                                 /*!< Ce membre contient l'adresse du premier périphérique connecté sur un hub. Il est non nul pour un hub et nul pour un périphérique. */
   T_mkHCDDevice* previousHubDevice;                                             /*!< Ce membre contient l'adresse du hub où est connecté le périphérique. Il est nul pour le premier périphérique de l'arborescence. */

   T_mkHCDDeviceDescriptor deviceDescriptor;                                     /*!< Ce membre contient le descripteur de périphérique. */
   T_mkHCDDeviceQualifier deviceQualifier;                                       /*!< Ce membre contient le qualificateur de périphérique. */
   T_mkHCDConfigurationDescriptor configurationDescriptor;                       /*!< Ce membre contient le descripteur de configuration. */
   T_mkHCDInterfaceDescriptor* interfaceDescriptor;                              /*!< Ce membre contient les descripteurs d'interface. */
   T_mkHCDHubDescriptor* hubDescriptor;                                          /*!< Ce membre contient le descripteur de hub. */
};

/**
 * @struct T_mkHCDMessage
 * @brief Déclaration de la structure T_mkHCDMessage.
 *
 */

typedef struct T_mkHCDMessage T_mkHCDMessage;
struct T_mkHCDMessage
{
   T_mkHCDDevice* device;                                                        /*!< Ce membre contient l'adresse d'un périphérique de type \ref T_mkHCDDevice. */
   T_mkHCDInterfaceDescriptor* interface;                                        /*!< Ce membre contient l'adresse d'une interface de type \ref T_mkHCDInterfaceDescriptor. */
};

/**
 *
 */

#endif

