/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_utils_parser_ini_types.h
* @brief Déclaration des types dédiés au parser de fichier ".ini".
* @date 8 janv. 2023
*
*/

#ifndef MK_UTILS_PARSER_INI_TYPES_H
#define MK_UTILS_PARSER_INI_TYPES_H

/**
 * @enum T_mkINIState
 * @brief Déclaration de l'énumération T_mkINIState.
 *
 */

typedef enum T_mkINIState
{
   K_MK_UTILS_PARSER_INI_STATE_START = 0,                   /*!< Identifiant de l'état permettant de traiter les caractères de début de ligne. */
   K_MK_UTILS_PARSER_INI_STATE_COMPARE = 1,                 /*!< Identifiant de l'état permettant de rechercher une chaine de caractères. */
   K_MK_UTILS_PARSER_INI_STATE_BYPASS = 2,                  /*!< Identifiant de l'état permettant d'ignorer les caractères jusqu'à la prochaine ligne. */
   K_MK_UTILS_PARSER_INI_STATE_COPY = 3                     /*!< Identifiant de l'état permettant de copier la valeur de la propriété. */
} T_mkINIState;

/**
 * @struct T_mkINIParser
 * @brief Déclaration de la structure T_mkINIParser.
 *
 */

typedef struct T_mkINIParser T_mkINIParser;
struct T_mkINIParser
{
   uint32_t numberOfBytesRead;                              /*!< Ce membre contient le nombre d'octets disponibles. */
   uint32_t remainingSize;                                  /*!< Ce membre contient le nombre d'octets restant à analyser dans le fichier. */
   uint32_t bytePointer;                                    /*!< Ce membre contient l'adresse de l'octet en cours d'analyse dans le secteur. */
   uint32_t strPointer;                                     /*!< Ce membre contient l'adresse de l'octet en cours d'analyse dans la chaine de caractères. */
   uint32_t state;                                          /*!< Ce membre contient le registre d'état du parser (\ref T_mkINIState). */
   uint8_t  buf [ K_MK_UTILS_PARSER_INI_FILEBUFSIZE ];      /*!< Ce membre contient le buffer de travail du parser. */
};

/**
 *
 */

#endif

