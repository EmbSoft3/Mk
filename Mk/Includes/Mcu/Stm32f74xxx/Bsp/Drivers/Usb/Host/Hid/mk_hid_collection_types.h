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
* @file mk_hid_collection_types.h
* @brief Déclaration des types dédiés aux collections du module 'HID'.
* @date 20 nov. 2019
*
*/

#ifndef MK_HID_COLLECTION_TYPES_H
#define MK_HID_COLLECTION_TYPES_H

/**
 * @enum T_mkHIDCollectionType
 * @brief Déclaration de l'énumération T_mkHIDCollectionType.
 *
 */

typedef enum T_mkHIDCollectionType
{
   K_MK_HID_COLLECTION_TYPE_PHYSICAL = 0x00,          /*!< Définition de l'identifiant d'une collection de type 'Physical' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_APPLICATION = 0x01,       /*!< Définition de l'identifiant d'une collection de type 'Application' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_LOGICAL = 0x02,           /*!< Définition de l'identifiant d'une collection de type 'Logical' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_REPORT = 0x03,            /*!< Définition de l'identifiant d'une collection de type 'Report' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_NAMED_ARRAY = 0x04,       /*!< Définition de l'identifiant d'une collection de type 'NamedArray' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_USAGE_SWITCH = 0x05,      /*!< Définition de l'identifiant d'une collection de type 'UsageSwitch' selon la spécification HID 1.11. */
   K_MK_HID_COLLECTION_TYPE_USAGE_MODIFIER = 0x06     /*!< Définition de l'identifiant d'une collection de type 'UsageModifier' selon la spécification HID 1.11. */
} T_mkHIDCollectionType;

/**
 *
 */

#endif


