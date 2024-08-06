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
* @brief Déclaration des types dédiés aux reports HID.
* @date 20 nov. 2019
*
*/

#ifndef MK_HID_REPORT_TYPES_H
#define MK_HID_REPORT_TYPES_H

/**
 * @enum T_mkHIDReportError
 * @brief Déclaration de l'énumération T_mkHIDReportError.
 *
 */

typedef enum T_mkHIDReportError
{
   K_MK_HID_NO_ERROR = 0,                                                  /*!< Définition d'un code indiquant qu'aucune erreur n'a été détectée durant la vérification du 'Report-Descriptor'. */

   K_MK_HID_ERROR_INVALID_DECLARATION_ITEM = 0x10,                         /*!< Définition d'un code indiquant la déclaration d'un 'Item' inconnu dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_INVALID_DECLARATION_COLLECTION = 0x13,                   /*!< Définition d'un code indiquant que les collections de tête d'un 'Report-Descriptor ne sont pas toutes de type applicatives. */
   K_MK_HID_ERROR_INVALID_DECLARATION_DELIMITER = 0x11,                    /*!< Définition d'un code indiquant la déclaration d'un 'Item' de type 'Delimiter' invalide dans le 'Report-Descriptor' (déclaration en dehors d'une collection applicative ou présence d'usages non uniformes ou d'item invalides entre les balises 'Open' et 'Close'. */
   K_MK_HID_ERROR_NESTING_DELIMITER= 0x01,                                 /*!< Définition d'un code indiquant la déclaration d'un 'Item' de type 'Delimiter' invalide dans le 'Report-Descriptor' (au moins deux balises de type 'Open' ou 'Close' sont imbriquées). */

   K_MK_HID_ERROR_INVALID_VALUE_PUSH = 0x20,                               /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'Push' est invalide. */
   K_MK_HID_ERROR_INVALID_VALUE_POP = 0x21,                                /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'Pop' est invalide. */
   K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MIN_MAX = 0x22,                    /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'LogicalMinimum' est supérieure ou égale à la valeur d'un 'Item' de type 'LogicalMaximum'. */
   K_MK_HID_ERROR_INVALID_VALUE_USAGE_MIN_MAX = 0x23,                      /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'UsageMinimum' est supérieure à la valeur d'un 'Item' de type 'UsageMaximum'. */
   K_MK_HID_ERROR_INVALID_VALUE_USAGE_PAGE_MIN_MAX = 0x24,                 /*!< Définition d'un code indiquant que la valeur de la page d'un 'Item' de type 'UsageMinimum' est différente de la valeur de la page d'un 'Item' de type 'UsageMaximum'. */
   K_MK_HID_ERROR_INVALID_VALUE_DESIGNATOR_MIN_MAX = 0x25,                 /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'DesignatorMinimum' est supérieure à la valeur d'un 'Item' de type 'DesignatorMaximum'. */
   K_MK_HID_ERROR_INVALID_VALUE_STRING_MIN_MAX = 0x26,                     /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'StringMinimum' est supérieure à la valeur d'un 'Item' de type 'StringMaximum'. */
   K_MK_HID_ERROR_INVALID_VALUE_PHYSICAL_MIN_MAX = 0x27,                   /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'PhysicalMinimum' est supérieure ou égale à la valeur d'un 'Item' de type 'PhysicalMaximum' (sous condition qu'une balise de type 'Physical' soit présente. */
   K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MINIMUM = 0x28,                    /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'LogicalMinimum' est négative alors qu'un 'Usage' de type 'Array' a été déclaré. */
   K_MK_HID_ERROR_INVALID_VALUE_LOGICAL_MAXIMUM = 0x29,                    /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'LogicalMaximum' est négative alors qu'un 'Usage' de type 'Array' a été déclaré ou que la valeur de l'item 'LogicalMaximum' est supérieur au nombre d'usage définis. */
   K_MK_HID_ERROR_INVALID_VALUE_USAGE_PAGE = 0x2A,                         /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'UsagePage' est invalide (la valeur est nulle ou supérieur à 0xFFFF). */
   K_MK_HID_ERROR_INVALID_VALUE_REPORT_ID = 0x2B,                          /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'ReportID' est invalide (la valeur est nulle ou supérieur à 0xFF). */
   K_MK_HID_ERROR_INVALID_VALUE_REPORT_COUNT = 0x2C,                       /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'ReportCount' est invalide (la valeur est nulle). */
   K_MK_HID_ERROR_INVALID_VALUE_DELIMITER = 0x2D,                          /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'Delimiter' est invalide (la valeur est différente de 0 ou 1). */

   K_MK_HID_ERROR_INVALID_RANGE_NULL = 0x30,                               /*!< Définition d'un code indiquant que la valeur 'NULL' d'une entrée n'est pas située en dehors de la plage 'LogicalMinimum' à 'LogicalMaximum'. */
   K_MK_HID_ERROR_INVALID_RANGE_LOGICAL_MAXIMUM = 0x31,                    /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'LogicalMaximum' est en dehors de la plage de variation définie par un 'Item' de type 'ReportSize'. */
   K_MK_HID_ERROR_INVALID_RANGE_LOGICAL_MINIMUM = 0x32,                    /*!< Définition d'un code indiquant que la valeur d'un 'Item' de type 'LogicalMinimum' est en dehors de la plage de variation définie par un 'Item' de type 'ReportSize'. */

   K_MK_HID_ERROR_MISSING_DECLARATION_ITEM = 0x40,                         /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'Input', 'Output' ou 'Feature' n'est présent dansle 'Report-Descriptor. */
   K_MK_HID_ERROR_MISSING_DECLARATION_USAGE_PAGE = 0x41,                   /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'UsagePage' n'est présent dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_MISSING_DECLARATION_LOGICAL_MINIMUM = 0x42,              /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'LogicalMinimum' n'est présent dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_MISSING_DECLARATION_LOGICAL_MAXIMUM = 0x43,              /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'LogicalMaximum' n'est présent dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_MISSING_DECLARATION_REPORT_SIZE = 0x44,                  /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'ReportSize' n'est présent dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_MISSING_DECLARATION_REPORT_COUNT = 0x45,                 /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'ReportCount' n'est présent dans le 'Report-Descriptor'. */
   K_MK_HID_ERROR_MISSING_DECLARATION_USAGE = 0x46,                        /*!< Définition d'un code indiquant qu'aucun 'Item' de type 'Usage' n'est présent dans au moins un 'Report' du 'Report-Descriptor'. */

   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_PUSH_POP = 0x50,               /*!< Définition d'un code indiquant que le nombre d'Item de type 'Pop' est différent du nombre d'item de type 'Push'. */
   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_USAGE_MIN_MAX = 0x51,          /*!< Définition d'un code indiquant que le nombre d'Item de type 'UsageMinimal' est différent du nombre d'item de type 'UsageMaximal'. */
   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_DESIGNATOR_MIN_MAX = 0x52,     /*!< Définition d'un code indiquant que le nombre d'Item de type 'DesignatorMinimal' est différent du nombre d'item de type 'DesignatorMaximal'. */
   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_STRING_MIN_MAX = 0x53,         /*!< Définition d'un code indiquant que le nombre d'Item de type 'StringMinimal' est différent du nombre d'item de type 'StringMaximal'. */
   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_DELIMITER = 0x54,              /*!< Définition d'un code indiquant que le nombre d'Item de type 'OpenDelimter' est différent du nombre d'item de type 'CloseDelimiter'. */
   K_MK_HID_ERROR_CORRESPONDING_DECLARATION_COLLECTION = 0x55              /*!< Définition d'un code indiquant que le nombre d'Item de type 'EndCollection' est supérieur au nombre d'item de type 'Collection'. */
} T_mkHIDReportError;

/**
 * @struct T_mkHIDReportDescriptor
 * @brief Déclaration de la structure T_mkHIDReportDescriptor.
 *
 */

typedef struct T_mkHIDReportDescriptor T_mkHIDReportDescriptor;
struct T_mkHIDReportDescriptor
{
   T_mkHIDItem* item;                                                      /*!< Ce membre contient l'adresse du premier 'Item' du 'Report-Descriptor'. */
};

/**
 * @struct T_mkHIDReport
 * @brief Déclaration de la structure T_mkHIDReport.
 *
 */

typedef struct T_mkHIDReport T_mkHIDReport;
struct T_mkHIDReport
{
   T_mkHIDItem* first;                                                     /*!< Ce membre contient l'adresse du premier 'Item' du 'Report'. La position de ce champ ne doit pas être modifiée. */
   T_mkHIDItem* last;                                                      /*!< Ce membre contient l'adresse du dernier 'Item' du 'Report'. La position de ce champ ne doit pas être modifiée. */

   uint32_t id;                                                            /*!< Ce membre contient l'identifiant du 'Report'. */
   uint32_t inputSize;                                                     /*!< Ce membre contient la taille de toutes les entrées du 'Report' [en octets]. */
   uint32_t outputSize;                                                    /*!< Ce membre contient la taille de toutes les sorties du 'Report' [en octets]. */

   T_mkAddr addr;                                                          /*!< Ce membre contient l'adresse d'un contrôle applicatif. */
   T_mkPool* pool;                                                         /*!< Ce membre contient l'adresse de la 'Pool' utilisée pour allouer dynamiquement le contrôle applicatif. */

   T_mkHIDReport* next;                                                    /*!< Ce membre contient l'adresse du prochain 'Report'. */
};

/**
 *
 */

#endif


