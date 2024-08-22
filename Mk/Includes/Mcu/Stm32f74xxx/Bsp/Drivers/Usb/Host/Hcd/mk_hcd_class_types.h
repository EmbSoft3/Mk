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
* @file mk_hcd_class_types.h
* @brief Définition des classes de périphériques USB 2.0.
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_CLASS_TYPES_H
#define MK_HCD_CLASS_TYPES_H

/**
 * @enum T_mkHCDDeviceClass
 * @brief Déclaration du type T_mkHCDDeviceClass.
 */

typedef enum T_mkHCDDeviceClass
{
   K_MK_HCD_CLASS_BASE = 0x00,                                                   /*!< Définition de la classe USB_IF_CLASS_BASE. */
   K_MK_HCD_CLASS_AUDIO = 0x01,                                                  /*!< Définition de la classe USB_IF_CLASS_AUDIO. */
   K_MK_HCD_CLASS_CDC_CONTROL = 0x02,                                            /*!< Définition de la classe USB_IF_CLASS_CDC_CONTROL. */
   K_MK_HCD_CLASS_HID = 0x03,                                                    /*!< Définition de la classe USB_IF_CLASS_HID. */
   K_MK_HCD_CLASS_PHYSICAL = 0x05,                                               /*!< Définition de la classe USB_IF_CLASS_PHYSICAL. */
   K_MK_HCD_CLASS_IMAGE = 0x06,                                                  /*!< Définition de la classe USB_IF_CLASS_IMAGE. */
   K_MK_HCD_CLASS_PRINTER = 0x07,                                                /*!< Définition de la classe USB_IF_CLASS_PRINTER. */
   K_MK_HCD_CLASS_MASS_STORAGE = 0x08,                                           /*!< Définition de la classe USB_IF_CLASS_MASS_STORAGE. */
   K_MK_HCD_CLASS_HUB = 0x09,                                                    /*!< Définition de la classe USB_IF_CLASS_HUB. */
   K_MK_HCD_CLASS_CDC_DATA = 0x0A,                                               /*!< Définition de la classe USB_IF_CLASS_CDC_DATA. */
   K_MK_HCD_CLASS_SMART_CARD = 0x0B,                                             /*!< Définition de la classe USB_IF_CLASS_SMART_CARD. */
   K_MK_HCD_CLASS_CONTENT_SECURITY = 0x0D,                                       /*!< Définition de la classe USB_IF_CLASS_CONTENT_SECURITY. */
   K_MK_HCD_CLASS_VIDEO = 0x0E,                                                  /*!< Définition de la classe USB_IF_CLASS_VIDEO. */
   K_MK_HCD_CLASS_PERSONAL_HEALTHCARE = 0x0F,                                    /*!< Définition de la classe USB_IF_CLASS_PERSONAL_HEALTHCARE. */
   K_MK_HCD_CLASS_AUDIO_VIDEO_DEVICES = 0x10,                                    /*!< Définition de la classe USB_IF_CLASS_AUDIO_VIDEO_DEVICES. */
   K_MK_HCD_CLASS_BILLBOARD_DEVICE = 0x11,                                       /*!< Définition de la classe USB_IF_CLASS_BILLBOARD_DEVICE. */
   K_MK_HCD_CLASS_USB_TYPE_C_BRIDGE = 0x12,                                      /*!< Définition de la classe USB_IF_CLASS_TYPE_C_BRIDGE. */
   K_MK_HCD_CLASS_DIAGNOSTIC_DEVICE = 0xDC,                                      /*!< Définition de la classe USB_IF_CLASS_DIAGNOSTIC_DEVICE. */
   K_MK_HCD_CLASS_WIRELESS_CONTROLLER = 0xE0,                                    /*!< Définition de la classe USB_IF_CLASS_WIRELESS_CONTROLLER. */
   K_MK_HCD_CLASS_MISCELLANEOUS = 0xEF,                                          /*!< Définition de la classe USB_IF_CLASS_MISCELLANEAOUS. */
   K_MK_HCD_CLASS_APPLICATION_SPECIFIC = 0xFE,                                   /*!< Définition de la classe USB_IF_CLASS_APPLICATION_SPECIFIC. */
   K_MK_HCD_CLASS_VENDOR_SPECIFIC = 0xFF                                         /*!< Définition de la classe USB_IF_CLASS_VENDOR_SPECIFIC. */
} T_mkHCDDeviceClass;

/**
 * @enum T_mkHCDDeviceClassFlag
 * @brief Déclaration du type T_mkHCDDeviceClassFlag.
 */

typedef enum T_mkHCDDeviceClassFlag
{
   K_MK_HCD_CLASS_FLAG_BASE = 0x01,                                              /*!< Identifiant de la classe USB_IF_CLASS_BASE. */
   K_MK_HCD_CLASS_FLAG_AUDIO = 0x02,                                             /*!< Identifiant de la classe USB_IF_CLASS_AUDIO. */
   K_MK_HCD_CLASS_FLAG_CDC_CONTROL = 0x04,                                       /*!< Identifiant de la classe USB_IF_CLASS_CDC_CONTROL. */
   K_MK_HCD_CLASS_FLAG_HID = 0x08,                                               /*!< Identifiant de la classe USB_IF_CLASS_HID. */
   K_MK_HCD_CLASS_FLAG_PHYSICAL = 0x10,                                          /*!< Identifiant de la classe USB_IF_CLASS_PHYSICAL. */
   K_MK_HCD_CLASS_FLAG_IMAGE = 0x20,                                             /*!< Identifiant de la classe USB_IF_CLASS_IMAGE. */
   K_MK_HCD_CLASS_FLAG_PRINTER = 0x40,                                           /*!< Identifiant de la classe USB_IF_CLASS_PRINTER. */
   K_MK_HCD_CLASS_FLAG_MASS_STORAGE = 0x80,                                      /*!< Identifiant de la classe USB_IF_CLASS_MASS_STORAGE. */
   K_MK_HCD_CLASS_FLAG_HUB = 0x100,                                              /*!< Identifiant de la classe USB_IF_CLASS_HUB. */
   K_MK_HCD_CLASS_FLAG_CDC_DATA = 0x200,                                         /*!< Identifiant de la classe USB_IF_CLASS_CDC_DATA. */
   K_MK_HCD_CLASS_FLAG_SMART_CARD = 0x400,                                       /*!< Identifiant de la classe USB_IF_CLASS_SMART_CARD. */
   K_MK_HCD_CLASS_FLAG_CONTENT_SECURITY = 0x800,                                 /*!< Identifiant de la classe USB_IF_CLASS_CONTENT_SECURITY. */
   K_MK_HCD_CLASS_FLAG_VIDEO = 0x1000,                                           /*!< Identifiant de la classe USB_IF_CLASS_VIDEO. */
   K_MK_HCD_CLASS_FLAG_PERSONAL_HEALTHCARE = 0x2000,                             /*!< Identifiant de la classe USB_IF_CLASS_PERSONAL_HEALTHCARE. */
   K_MK_HCD_CLASS_FLAG_AUDIO_VIDEO_DEVICES = 0x4000,                             /*!< Identifiant de la classe USB_IF_CLASS_AUDIO_VIDEO_DEVICES. */
   K_MK_HCD_CLASS_FLAG_BILLBOARD_DEVICE = 0x8000,                                /*!< Identifiant de la classe USB_IF_CLASS_BILLBOARD_DEVICE. */
   K_MK_HCD_CLASS_FLAG_USB_TYPE_C_BRIDGE = 0x10000,                              /*!< Identifiant de la classe USB_IF_CLASS_TYPE_C_BRIDGE. */
   K_MK_HCD_CLASS_FLAG_DIAGNOSTIC_DEVICE = 0x20000,                              /*!< Identifiant de la classe USB_IF_CLASS_DIAGNOSTIC_DEVICE. */
   K_MK_HCD_CLASS_FLAG_WIRELESS_CONTROLLER = 0x40000,                            /*!< Identifiant de la classe USB_IF_CLASS_WIRELESS_CONTROLLER. */
   K_MK_HCD_CLASS_FLAG_MISCELLANEOUS = 0x80000,                                  /*!< Identifiant de la classe USB_IF_CLASS_MISCELLANEAOUS. */
   K_MK_HCD_CLASS_FLAG_APPLICATION_SPECIFIC = 0x100000,                          /*!< Identifiant de la classe USB_IF_CLASS_APPLICATION_SPECIFIC. */
   K_MK_HCD_CLASS_FLAG_VENDOR_SPECIFIC = 0x200000,                               /*!< Identifiant de la classe USB_IF_CLASS_VENDOR_SPECIFIC. */
   K_MK_HCD_CLASS_FLAG_ALL = 0x3FFFFFFF                                          /*!< Identifiant permettant d'adresser toutes les classes supportées */
} T_mkHCDDeviceClassFlag;


/**
 *
 */

#endif


