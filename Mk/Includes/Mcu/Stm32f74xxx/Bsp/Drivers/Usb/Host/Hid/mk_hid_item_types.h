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
* @file mk_hid_report_types.h
* @brief Déclaration des types dédiés aux items HID.
* @date 25 oct. 2019
*
*/

#ifndef MK_HID_ITEM_TYPES_H
#define MK_HID_ITEM_TYPES_H

/**
 * @enum T_mkHIDShortItemType
 * @brief Déclaration de l'énumération T_mkHIDShortItemType.
 *
 */

typedef enum T_mkHIDShortItemType
{
   K_MK_HID_ITEM_TYPE_MAIN = 0x00,                       /*!< Définition de l'identifiant d'un 'Item' de type 'Main' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TYPE_GLOBAL = 0x04,                     /*!< Définition de l'identifiant d'un 'Item' de type 'Global' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TYPE_LOCAL = 0x08,                      /*!< Définition de l'identifiant d'un 'Item' de type 'Local' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TYPE_LONG_ITEM = 0x0C                   /*!< Définition de l'identifiant d'un 'Item' de type 'Long' d'après la spécification HID 1.11. */
} T_mkHIDShortItemType;

/**
 * @enum T_mkHIDShortItemTag
 * @brief Déclaration de l'énumération T_mkHIDShortItemTag.
 *
 */

typedef enum T_mkHIDShortItemTag
{
   /* Global Item */
   K_MK_HID_ITEM_TAG_USAGE_PAGE = 1,                     /*!< Définition de l'identifiant 'UsagePage' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_LOGICAL_MINIMUM = 5,                /*!< Définition de l'identifiant 'LogicalMinimum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_LOGICAL_MAXIMUM = 9,                /*!< Définition de l'identifiant 'LogicalMaximum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_PHYSICAL_MINIMUM = 13,              /*!< Définition de l'identifiant 'PhysicalMinimum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_PHYSICAL_MAXIMUM = 17,              /*!< Définition de l'identifiant 'PhysicalMaximum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_UNIT_EXPONENT = 21,                 /*!< Définition de l'identifiant 'UnitExponent' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_UNIT = 25,                          /*!< Définition de l'identifiant 'Unit' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_REPORT_SIZE = 29,                   /*!< Définition de l'identifiant 'ReportSize' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_REPORT_ID = 33,                     /*!< Définition de l'identifiant 'ReportID' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_REPORT_COUNT = 37,                  /*!< Définition de l'identifiant 'ReportCount' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_PUSH = 41,                          /*!< Définition de l'identifiant 'Push' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_POP = 45,                           /*!< Définition de l'identifiant 'Pop' d'après la spécification HID 1.11. */

   /* Main Item */
   K_MK_HID_ITEM_TAG_INPUT = 32,                         /*!< Définition de l'identifiant 'Input' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_OUTPUT = 36,                        /*!< Définition de l'identifiant 'Output' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_FEATURE = 44,                       /*!< Définition de l'identifiant 'Feature' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_COLLECTION = 40,                    /*!< Définition de l'identifiant 'Collection' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_END_COLLECTION = 48,                /*!< Définition de l'identifiant 'EndCollection' d'après la spécification HID 1.11. */

   /* Local Item */
   K_MK_HID_ITEM_TAG_USAGE = 2,                          /*!< Définition de l'identifiant 'Usage' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_USAGE_MINIMUM = 6,                  /*!< Définition de l'identifiant 'UsageMinimum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_USAGE_MAXIMUM = 10,                 /*!< Définition de l'identifiant 'UsageMaximum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_DESIGNATOR_INDEX = 14,              /*!< Définition de l'identifiant 'DesignatorIndex' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_DESIGNATOR_MINIMUM = 18,            /*!< Définition de l'identifiant 'DesignatorMinimum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_DESIGNATOR_MAXIMUM = 22,            /*!< Définition de l'identifiant 'DesignatorMaximum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_STRING_INDEX = 30,                  /*!< Définition de l'identifiant 'StringIndex' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_STRING_MINIMUM = 34,                /*!< Définition de l'identifiant 'StringMinimum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_STRING_MAXIMUM = 38,                /*!< Définition de l'identifiant 'StringMaximum' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_TAG_DELIMITER = 42                      /*!< Définition de l'identifiant 'Delimiter' d'après la spécification HID 1.11. */
} T_mkHIDShortItemTag;

/**
 * @enum T_mkHIDMainItemTag
 * @brief Déclaration de l'énumération T_mkHIDMainItemTag.
 *
 */

typedef enum T_mkHIDMainItemTag
{
   K_MK_HID_ITEM_CONSTANT = 0x01,                        /*!< Définition de l'identifiant 'Constant' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_VARIABLE = 0x02,                        /*!< Définition de l'identifiant 'Variable' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_RELATIVE = 0x04,                        /*!< Définition de l'identifiant 'Relative' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_WRAP = 0x08,                            /*!< Définition de l'identifiant 'Wrap' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_NON_LINEAR = 0x10,                      /*!< Définition de l'identifiant 'NonLinear' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_NO_PREFERRED = 0x20,                    /*!< Définition de l'identifiant 'NoPreferred' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_NULL_STATE = 0x40,                      /*!< Définition de l'identifiant 'NullState' d'après la spécification HID 1.11. */
   K_MK_HID_ITEM_BUFFERED_BYTES = 0x100                  /*!< Définition de l'identifiant 'BufferedBypes' d'après la spécification HID 1.11. */
} T_mkHIDMainItemTag;

/**
 * @struct T_mkHIDItemBitfield
 * @brief Déclaration de la structure T_mkHIDItemBitfield.
 *
 */

typedef struct T_mkHIDItemBitfield T_mkHIDItemBitfield;
struct T_mkHIDItemBitfield
{
   unsigned_t size:2;                                      /*!< Ce champ stocke la taille d'un item. */
   unsigned_t tag:6;                                       /*!< Ce champ stocke l'identifiant d'un item. */
   unsigned_t reserved:8;                                  /*!< Ce champ est réservé. */
   unsigned_t destinationSize:16;                          /*!< Ce membre contient la taille [en bits] de la valeur de l'item. */
};

/**
 * @struct T_mkHIDItemHead
 * @brief Déclaration de l'union T_mkHIDItemHead.
 *
 */

typedef union T_mkHIDItemHead T_mkHIDItemHead;
union T_mkHIDItemHead
{
   T_mkHIDItemBitfield field;                            /*!< Ce membre contient la valeur d'un item sous forme d'un champ de bits. */
   uint32_t value;                                       /*!< Ce membre contient la valeur brute d'un item. */
};

/**
 * @struct T_mkHIDItem
 * @brief Déclaration de la structure T_mkHIDItem.
 *
 */

typedef struct T_mkHIDItem T_mkHIDItem;
struct T_mkHIDItem
{
   T_mkHIDItemHead head;                                 /*!< Ce membre contient les caractèristiques de l'item (entête). */
   T_mkHIDItem* nextItem;                                /*!< Ce membre contient l'adresse du prochain item contenu dans le report. */
   T_mkHIDItem* nextAlternate;                           /*!< Ce champ est valide lorsque l'item est un usage. Il contient l'adresse d'un usage équivalent. */

   T_mkAddr addr;                                        /*!< Ce membre contient l'adresse de routage de l'item. Les valeurs \ref K_MK_NULL, \ref K_MK_INVALID_HANDLE ont une signification particulière pour le parser. */
   uint32_t value;                                       /*!< Ce membre contient la valeur de l'item issue du 'ReportDescriptor' (Ne pas confondre avec la valeur de l'Usage). */
};

/**
 *
 */

#endif


