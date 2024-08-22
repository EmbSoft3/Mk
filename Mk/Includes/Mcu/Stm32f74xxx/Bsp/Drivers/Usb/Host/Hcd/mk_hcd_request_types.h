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
* @file mk_hcd_request_types.h
* @brief Déclaration des types dédiés aux requêtes USB.
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_REQUEST_TYPES_H
#define MK_HCD_REQUEST_TYPES_H

/**
 * @enum T_mkHCDEnumRequestRecipient
 * @brief Déclaration du type T_mkHCDEnumRequestRecipient.
 */

typedef enum T_mkHCDEnumRequestRecipient
{
   K_MK_HCD_DEVICE = 0,                                              /*!< Valeur définie par la spécification USB2.0 => DEVICE */
   K_MK_HCD_INTERFACE = 1,                                           /*!< Valeur définie par la spécification USB2.0 => INTERFACE */
   K_MK_HCD_ENDPOINT = 2,                                            /*!< Valeur définie par la spécification USB2.0 => ENDPOINT */
   K_MK_HCD_OTHER = 3                                                /*!< Valeur définie par la spécification USB2.0 => OTHER */
} T_mkHCDEnumRequestRecipient;

/**
 * @enum T_mkHCDEnumRequestType
 * @brief Déclaration du type T_mkHCDEnumRequestType.
 */

typedef enum T_mkHCDEnumRequestType
{
   K_MK_HCD_STANDARD = 0,                                            /*!< Valeur définie par la spécification USB2.0 => STANDARD */
   K_MK_HCD_CLASS = 32,                                              /*!< Valeur définie par la spécification USB2.0 => CLASS */
   K_MK_HCD_VENDOR = 64                                              /*!< Valeur définie par la spécification USB2.0 => VENDOR_SPECIFIC */
} T_mkHCDEnumRequestType;

/**
 * @enum T_mkHCDEnumRequestDirection
 * @brief Déclaration du type T_mkHCDEnumRequestDirection.
 */

typedef enum T_mkHCDEnumRequestDirection
{
   K_MK_HCD_HOST_TO_DEVICE = 0,                                      /*!< Valeur définie par la spécification USB2.0 => HOST_TO_DEVICE */
   K_MK_HCD_DEVICE_TO_HOST = 128                                     /*!< Valeur définie par la spécification USB2.0 => DEVICE_TO_HOST */
} T_mkHCDEnumRequestDirection;

/**
 * @enum T_mkHCDEnumEndpointDirection
 * @brief Déclaration du type T_mkHCDEnumEndpointDirection.
 */

typedef enum T_mkHCDEnumEndpointDirection
{
   K_MK_HCD_OUT_ENPOINT = 0,                                         /*!< Valeur définie par la spécification USB2.0 => OUT_ENDPOINT */
   K_MK_HCD_IN_ENDPOINT = 128                                        /*!< Valeur définie par la spécification USB2.0 => IN_ENDPOINT */
} T_mkHCDEnumEndpointDirection;

/**
 * @enum T_mkHCDRequestCode
 * @brief Déclaration du type T_mkHCDRequestCode.
 */

typedef enum T_mkHCDRequestCode
{
   K_MK_HCD_GET_STATUS = 0,                                          /*!< Valeur définie par la spécification USB2.0 => GET_STATUS */
   K_MK_HCD_CLEAR_FEATURE = 1,                                       /*!< Valeur définie par la spécification USB2.0 => CLEAR_FEATURE */
   K_MK_HCD_RSV1 = 2,                                                /*!< Valeur définie par la spécification USB2.0 => RESERVED */
   K_MK_HCD_SET_FEATURE = 3,                                         /*!< Valeur définie par la spécification USB2.0 => SET_FEATURE */
   K_MK_HCD_RSV2 = 4,                                                /*!< Valeur définie par la spécification USB2.0 => RESERVED */
   K_MK_HCD_SET_ADDRESS = 5,                                         /*!< Valeur définie par la spécification USB2.0 => SET_ADDRESS */
   K_MK_HCD_GET_DESCRIPTOR = 6,                                      /*!< Valeur définie par la spécification USB2.0 => GET_DESCRIPTOR */
   K_MK_HCD_SET_DESCRIPTOR = 7,                                      /*!< Valeur définie par la spécification USB2.0 => SET_DESCRIPTOR */
   K_MK_HCD_GET_CONFIGURATION = 8,                                   /*!< Valeur définie par la spécification USB2.0 => GET_CONFIGURATION */
   K_MK_HCD_SET_CONFIGURATION = 9,                                   /*!< Valeur définie par la spécification USB2.0 => SET_CONFIGURATION */
   K_MK_HCD_GET_INTERFACE = 10,                                      /*!< Valeur définie par la spécification USB2.0 => GET_INTERFACE */
   K_MK_HCD_SET_INTERFACE = 11,                                      /*!< Valeur définie par la spécification USB2.0 => SET_INTERFACE */
   K_MK_HCD_SYNCH_FRAME = 12                                         /*!< Valeur définie par la spécification USB2.0 => SYNC_FRAME */
} T_mkHCDRequestCode;

/**
 * @enum T_mkHCDRequestDescriptor
 * @brief Déclaration du type T_mkHCDRequestDescriptor.
 */

typedef enum T_mkHCDRequestDescriptor
{
   K_MK_HCD_DESC_DEVICE = 0x0100,                                    /*!< Valeur définie par la spécification USB2.0 => DEVICE_DESCRIPTOR */
   K_MK_HCD_DESC_CONFIGURATION = 0x0200,                             /*!< Valeur définie par la spécification USB2.0 => CONFIGURATION_DESCRIPTOR */
   K_MK_HCD_DESC_STRING = 0x0300,                                    /*!< Valeur définie par la spécification USB2.0 => STRING_DESCRIPTOR */
   K_MK_HCD_DESC_INTERFACE = 0x0400,                                 /*!< Valeur définie par la spécification USB2.0 => INTERFACE_DESCRIPTOR */
   K_MK_HCD_DESC_ENDPOINT = 0x0500,                                  /*!< Valeur définie par la spécification USB2.0 => ENDPOINT_DESCRIPTOR */
   K_MK_HCD_DESC_DEVICE_QUALIFIER = 0x0600,                          /*!< Valeur définie par la spécification USB2.0 => DEVICE_QUALIFIER */
   K_MK_HCD_DESC_OTHER_SPEED_CONFIGURATION = 0x0700,                 /*!< Valeur définie par la spécification USB2.0 => OTHER_SPEED_CONFIGURATION */
   K_MK_HCD_DESC_INTERFACE_POWER1 = 0x0800,                          /*!< Valeur définie par la spécification USB2.0 => INTERFACE_POWER1 */
   K_MK_HCD_DESC_HUB = 0x2900                                        /*!< Valeur définie par la spécification USB2.0 => HUB_DESCRIPTOR */
} T_mkHCDRequestDescriptor;

/**
 * @enum T_mkHCDRequestFeature
 * @brief Déclaration du type T_mkHCDRequestFeature.
 */

typedef enum T_mkHCDRequestFeature
{
   K_MK_HCD_ENDPOINT_HALT = 0,                                       /*!< Valeur définie par la spécification USB2.0 => HALT_ENDPOINT */
   K_MK_HCD_DEVICE_REMOTE_WAKEUP = 1,                                /*!< Valeur définie par la spécification USB2.0 => REMOTE_WAKEUP */
   K_MK_HCD_TEST_MODE = 2                                            /*!< Valeur définie par la spécification USB2.0 => TEST_MODE */
} T_mkHCDRequestFeature;

/**
 * @struct T_mkHCDRequest
 * @brief Déclaration de la structure T_mkHCDRequest.
 *
 */

typedef struct T_mkHCDRequest T_mkHCDRequest;
struct T_mkHCDRequest
{
   uint8_t  bmRequestType;                                           /*!< Champ défini par la spécification USB2.0 => BITMAP_REQUEST_TYPE */
   uint8_t  bRequest;                                                /*!< Champ défini par la spécification USB2.0 => BITMAP_REQUEST */
   uint16_t wValue;                                                  /*!< Champ défini par la spécification USB2.0 => BITMAP_REQUEST_VALUE */
   uint16_t wIndex;                                                  /*!< Champ défini par la spécification USB2.0 => BITMAP_REQUEST_INDEX */
   uint16_t wLength;                                                 /*!< Champ défini par la spécification USB2.0 => BITMAP_REQUEST_LENGTH */
};


/**
 *
 */

#endif


