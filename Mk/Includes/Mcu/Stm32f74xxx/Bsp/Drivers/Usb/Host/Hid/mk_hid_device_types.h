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
* @file mk_hid_device_types.h
* @brief Déclaration des types dédiés aux périphériques HID.
* @date 20 oct. 2019
*
*/

#ifndef MK_HID_DEVICE_TYPES_H
#define MK_HID_DEVICE_TYPES_H

/**
 * @struct T_mkHIDDeviceState
 * @brief Déclaration de la structure T_mkHIDDeviceState.
 *
 */

typedef enum T_mkHIDDeviceState
{
   K_MK_HID_DEVICE_NOT_INIT_STATE = 0,                /*!< Définition d'un état indiquant que le périphérique HID n'est pas initialisé. */
   K_MK_HID_DEVICE_CONFIGURED_STATE = 1,              /*!< Définition d'un état indiquant que le périphérique HID est initialisé. */
   K_MK_HID_DEVICE_NOT_SUPPORTED = 2,                 /*!< Définition d'un état indiquant que le périphérique HID n'est pas supporté par le système. */
   K_MK_HID_DEVICE_ERROR_STATE = 4                    /*!< Définition d'un état indiquant que le périphérique HID est en erreur (erreur de communication n'ont récupérable). */
} T_mkHIDDeviceState;

/**
 * @struct T_mkHIDDescriptor
 * @brief Déclaration de la structure T_mkHIDDescriptor.
 *
 */

typedef struct T_mkHIDDescriptor T_mkHIDDescriptor;
struct T_mkHIDDescriptor
{
   uint8_t  bLength;                                  /*!< Champ défini par la spécification HID 1.11 => DESCRIPTOR_LENGTH */
   uint8_t  bDescriptorType;                          /*!< Champ défini par la spécification HID 1.11 => DESCRIPTOR_TYPE */
   uint8_t  bcdHID [ 2 ];                             /*!< Champ défini par la spécification HID 1.11 => HID_REVISON */
   uint8_t  bCountryCode;                             /*!< Champ défini par la spécification HID 1.11 => COUNTRY_CODE */
   uint8_t  bNumDescriptors;                          /*!< Champ défini par la spécification HID 1.11 => DESCRIPTOR_NUMBER */
   uint8_t  bDescriptorTypes;                         /*!< Champ défini par la spécification HID 1.11 => DESCRIPTOR_TYPE [REPORT] */
   uint8_t  wDescriptorLength [ 2 ];                  /*!< Champ défini par la spécification HID 1.11 => DESCRIPTOR_LENGTH [REPORT] */
   uint8_t  bOptionalDescriptorType;                  /*!< Champ défini par la spécification HID 1.11 => OPTIONNAL_DESCRIPTOR_TYPE */
   uint8_t  bOptionalDescriptorLength [ 2 ];          /*!< Champ défini par la spécification HID 1.11 => OPTIONNAL_DESCRIPTOR_LENGTH */
};

/**
 * @struct T_mkHIDDevice
 * @brief Déclaration de la structure T_mkHIDDevice.
 *
 */

typedef struct T_mkHIDDevice T_mkHIDDevice;
struct T_mkHIDDevice
{
   T_mkHCDDevice* device;                             /*!< Ce membre contient l'adresse du périphérique HCD propriétaire du périphérique HID. */
   T_mkHIDDevice* next;                               /*!< Ce membre contient l'adresse du prochain périphérique HID ou la valeur \ref K_MK_NULL. */
   T_mkHIDDevice* previous;                           /*!< Ce membre contient l'adresse du précédent périphérique HID ou la valeur \ref K_MK_NULL. */

   T_mkHIDDeviceState state;                          /*!< Ce membre contient l'état opérationnel du périphérique HID. */
   T_mkHCDInterfaceDescriptor* interface;             /*!< Ce membre contient l'adresse de l'interface HID dédiée au périphérique. */
   T_mkHCDEndpointDescriptor* inEndpoint;             /*!< Ce membre contient l'adresse de la terminaison d'interruption de type IN du périphérique HID. */
   T_mkHCDEndpointDescriptor* outEndpoint;            /*!< Ce membre contient l'adresse de la terminaison d'interruption de type OUT du périphérique HID ou la valeur \ref K_MK_NULL. */
   T_mkHIDDescriptor hidDescriptor;                   /*!< Ce membre contient le contenu du descripteur HID. */
   T_mkHIDReportDescriptor reportDescriptor;          /*!< Ce membre contient le contenu du descripteur de 'Report' HID. */
   T_mkHIDReport* report;                             /*!< Ce membre contient l'adresse du premier 'Report' du périphérique HID. */
};

/**
 *
 */

#endif


