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
* @file mk_hid_usage_types.h
* @brief Déclaration des types dédiés aux usages HID.
* @date 20 nov. 2019
*
*/

#ifndef MK_HID_USAGE_TYPES_H
#define MK_HID_USAGE_TYPES_H

/**
 * @struct T_mkHIDUsage
 * @brief Déclaration de la structure T_mkHIDUsage.
 * @note Un 'Usage' est délimité par des 'Items' de types 'Input', 'Ouput' ou 'Feature'.
 *
 */

typedef struct T_mkHIDUsage T_mkHIDUsage;
struct T_mkHIDUsage
{
   T_mkHIDItem* first;                             /*!< Ce membre contient l'adresse du premier item de l'usage. */
   T_mkHIDItem* last;                              /*!< Ce membre contient l'adresse du dernier item de l'usage. */
};

/**
 * @struct T_mkHIDUsageParser
 * @brief Déclaration de la structure T_mkHIDUsageParser.
 *
 */

typedef struct T_mkHIDUsageParser T_mkHIDUsageParser;
struct T_mkHIDUsageParser
{
   uint32_t* usageBuf;                             /*!< Ce membre contient l'adresse d'un buffer de données 'HID'. */
   uint32_t  usageSize;                            /*!< Ce membre contient la taille en bits de l'usage à récupérer. */
   uint32_t  byteOffset;                           /*!< Ce membre contient la position courante de l'octet en cours de traitement (entre 0 et 1023). */
   uint32_t  bitAvailable;                         /*!< Ce membre contient le nombre de bits restant à analyser dans l'octet en cours de traitement (entre 1 et 8). */
   uint32_t  bitNumber;                            /*!< Ce membre contient le nombre totale de bits disponibles dans le buffer de données HID. */
   uint32_t  byteRemaining;                        /*!< Ce membre contient le nombre total d'octets qui doivent être récupéré. */
   uint32_t  reportID;                             /*!< Ce membre contient l'identifiant du 'Report'. */
   uint32_t  endpointType;                         /*!< Ce membre contient le type de la terminaison à utiliser. */
};

/**
 *
 */

#endif

