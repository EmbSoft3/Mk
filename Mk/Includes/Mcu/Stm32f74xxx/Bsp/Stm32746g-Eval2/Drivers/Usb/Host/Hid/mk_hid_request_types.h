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
* @file mk_hid_request_types.h
* @brief Déclaration des types dédiés aux requêtes HID.
* @date 21 oct. 2019
*
*/

#ifndef MK_HID_REQUEST_TYPES_H
#define MK_HID_REQUEST_TYPES_H

/**
 * @struct T_mkHIDDescriptorClass
 * @brief Déclaration de la structure T_mkHIDDescriptorClass.
 * @note Enumération dédiée à la requête GET_DESCRIPTOR.
 *
 */

typedef enum T_mkHIDDescriptorClass
{
   K_MK_HID_DESCRIPTOR = 0x2100,                /*!< Définition de l'identifiant du descripteur 'HID_DESCRIPTOR' d'après la spécification HID 1.11. */
   K_MK_HID_REPORT_DESCRIPTOR = 0x2200,         /*!< Définition de l'identifiant du descripteur 'REPORT_DESCRIPTOR' d'après la spécification HID 1.11. */
   K_MK_HID_PHYSICAL_DESCRIPTOR = 0x2300        /*!< Définition de l'identifiant du descripteur 'PHYSICAL_DESCRIPTOR' d'après la spécification HID 1.11. */
} T_mkHIDDescriptorClass;

/**
 * @struct T_mkHIDRequestCode
 * @brief Déclaration de la structure T_mkHIDRequestCode.
 *
 */

typedef enum T_mkHIDRequestCode
{
   K_MK_HID_GET_REPORT = 0x01,                  /*!< Définition de l'identifiant d'une requête de type 'GET_REPORT' d'après la spécification HID 1.11. */
   K_MK_HID_GET_IDLE = 0x2,                     /*!< Définition de l'identifiant d'une requête de type 'GET_IDLE' d'après la spécification HID 1.11. */
   K_MK_HID_GET_PROTOCOL = 0x2,                 /*!< Définition de l'identifiant d'une requête de type 'GET_PROTOCOL' d'après la spécification HID 1.11. */
   K_MK_HID_SET_REPORT = 0x9,                   /*!< Définition de l'identifiant d'une requête de type 'GET_REPORT' d'après la spécification HID 1.11. */
   K_MK_HID_SET_IDLE = 0xA,                     /*!< Définition de l'identifiant d'une requête de type 'SET_IDLE' d'après la spécification HID 1.11. */
   K_MK_HID_SET_PROTOCOL = 0xB                  /*!< Définition de l'identifiant d'une requête de type 'SET_PROTOCOL' d'après la spécification HID 1.11. */
} T_mkHIDRequestCode;

/**
 * @struct T_mkHIDReportCode
 * @brief Déclaration de la structure T_mkHIDReportCode.
 * @note Enumération dédiée aux requêtes GET_REPORT et SET_REPORT.
 *
 */

typedef enum T_mkHIDReportCode
{
   K_MK_HID_REPORT_INPUT = 0x0100,              /*!< Définition de l'identifiant d'un report de type 'INPUT' d'après la spécification HID 1.11. */
   K_MK_HID_REPORT_OUTPUT = 0x0200,             /*!< Définition de l'identifiant d'un report de type 'OUTPUT' d'après la spécification HID 1.11. */
   K_MK_HID_REPORT_FEATURE = 0x0300             /*!< Définition de l'identifiant d'un report de type 'FEATURE' d'après la spécification HID 1.11. */
} T_mkHIDReportCode;

/**
 * @struct T_mkHIDReportProtocol
 * @brief Déclaration de la structure T_mkHIDReportProtocol.
 * @note Enumération dédiée aux requêtes GET_PROTOCOL et SET_PROTOCOL.
 *
 */

typedef enum T_mkHIDReportProtocol
{
   K_MK_HID_BOOT_PROTOCOL = 0x0000,             /*!< Définition de l'identiant 'BOOT_PROTOCOL' d'après la spécification HID 1.11. */
   K_MK_HID_REPORT_PROTOCOL = 0x0001            /*!< Définition de l'identiant 'REPORT_PROTOCOL' d'après la spécification HID 1.11. */
} T_mkHIDReportProtocol;

/**
 *
 */

#endif

