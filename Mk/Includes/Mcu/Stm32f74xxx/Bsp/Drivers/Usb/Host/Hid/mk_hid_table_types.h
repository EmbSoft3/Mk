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
* @file mk_hid_table_types.h
* @brief Déclaration des types dédiés aux tables HID.
* @date 20 nov. 2019
*
*/

#ifndef MK_HID_TABLE_TYPES_H
#define MK_HID_TABLE_TYPES_H

/**
 * @struct T_mkHIDGlobalTable
 * @brief Déclaration de la structure T_mkHIDGlobalTable.
 *
 */

typedef struct T_mkHIDGlobalTable T_mkHIDGlobalTable;
struct T_mkHIDGlobalTable
{
   uint32_t usagePage;              /*!< Ce membre contient la valeur de l'attribut 'UsagePage'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */
   int32_t  logicalMinimum;         /*!< Ce membre contient la valeur de l'attribut 'LogicalMinimum'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */
   int32_t  logicalMaximum;         /*!< Ce membre contient la valeur de l'attribut 'LogicalMaximum'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */
   uint32_t reportSize;             /*!< Ce membre contient la valeur de l'attribut 'ReportSize'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */
   uint32_t reportCount;            /*!< Ce membre contient la valeur de l'attribut 'ReportCount'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */

   uint32_t reportID;               /*!< Ce membre contient la valeur de l'attribut 'ReportID'. */
   int32_t  physicalMinimum;        /*!< Ce membre contient la valeur de l'attribut 'PhysicalMinimum'. */
   int32_t  physicalMaximum;        /*!< Ce membre contient la valeur de l'attribut 'PhysicalMaximum'. */
   uint32_t physical;               /*!< Ce membre contient la valeur de l'attribut 'Physical'. */
   uint32_t unitExponent;           /*!< Ce membre contient la valeur de l'attribut 'UnitExponent'. */
   uint32_t unit;                   /*!< Ce membre contient la valeur de l'attribut 'Unit'. */
};

/**
 * @struct T_mkHIDLocalTable
 * @brief Déclaration de la structure T_mkHIDLocalTable.
 *
 */

typedef struct T_mkHIDLocalTable T_mkHIDLocalTable;
struct T_mkHIDLocalTable
{
   uint32_t usage;                  /*!< Ce membre contient la valeur de l'attribut 'Usage'. La spécification HID 1.11 spécifie ce champ comme obligatoire. */
   uint32_t usageMinimum;           /*!< Ce membre contient la valeur de l'attribut 'UsageMinimum'. */
   uint32_t usageMaximum;           /*!< Ce membre contient la valeur de l'attribut 'UsageMaximum'. */
   uint32_t designatorIndex;        /*!< Ce membre contient la valeur de l'attribut 'DesignatorIndex'. */
   uint32_t designatorMinimum;      /*!< Ce membre contient la valeur de l'attribut 'DesignatorMinimum'. */
   uint32_t designatorMaximum;      /*!< Ce membre contient la valeur de l'attribut 'DesignatorMaximum'. */
   uint32_t stringIndex;            /*!< Ce membre contient la valeur de l'attribut 'StringIndex'. */
   uint32_t stringMinimum;          /*!< Ce membre contient la valeur de l'attribut 'StringMinimum'. */
   uint32_t stringMaximum;          /*!< Ce membre contient la valeur de l'attribut 'StringMaximum'. */
   uint32_t delimiter;              /*!< Ce membre contient la valeur de l'attribut 'Delimiter'. */
   T_mkHIDLocalTable* previous;     /*!< Ce membre contient l'adresse d'une structure \ref T_mkHIDLocalTable. Il est utilisé lorsqu'une table doit être stockée dans une 'Stack' */
};

/**
 * @struct T_mkHIDReportTable
 * @brief Déclaration de la structure T_mkHIDReportTable.
 *
 */

typedef struct T_mkHIDReportTable T_mkHIDReportTable;
struct T_mkHIDReportTable
{
   T_mkHIDGlobalTable global;       /*!< Ce membre contient la valeur des items de type global. */
   T_mkHIDLocalTable* local;        /*!< Ce membre contient la valeur des items de type local. */
};

/**
 * @struct T_mkHIDReportStack
 * @brief Déclaration de la structure T_mkHIDReportStack.
 *
 */

typedef struct T_mkHIDReportStack T_mkHIDReportStack;
struct T_mkHIDReportStack
{
   T_mkHIDLocalTable* top;          /*!< Ce membre contient l'adresse d'une stack HID local. */
};

/**
 *
 */

#endif


