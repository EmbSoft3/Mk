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
* @file mk_loader_srec_types.h
* @brief Déclaration des types dédiés aux chargements des fichiers de programmation SREC.
* @date 20 déc. 2023
*
*/

#ifndef MK_LOADER_SREC_TYPES_H
#define MK_LOADER_SREC_TYPES_H

/**
 * @enum T_mkSRECState
 * @brief Déclaration de l'énumération T_mkSRECState.
 *
 */

typedef enum T_mkSRECState
{
   K_MK_LOADER_SREC_STATE_START = 0,                        /*!< Définition d'un identifiant permettant de traiter le début du 'Record' (S). */
   K_MK_LOADER_SREC_STATE_TYPE = 1,                         /*!< Définition d'un identifiant permettant de traiter le type de 'Record'. */
   K_MK_LOADER_SREC_STATE_BYTECOUNT = 2,                    /*!< Définition d'un identifiant permettant de traiter le nombre d'octets de données du 'Record'. */
   K_MK_LOADER_SREC_STATE_COPY = 3,                         /*!< Définition d'un identifiant permettant de traiter l'adresse, les données et le checksum du 'Record. */
   K_MK_LOADER_SREC_STATE_BYPASS = 4                        /*!< Définition d'un identifiant permettant d'ignorer la fin d'un ligne. */
} T_mkSRECState;

/**
 * @struct T_mkSRECParser
 * @brief Déclaration de la structure T_mkSRECParser.
 *
 */

typedef struct T_mkSRECParser T_mkSRECParser;
struct T_mkSRECParser
{
   uint32_t numberOfBytesRead;                              /*!< Ce membre contient le nombre d'octets disponibles. */
   uint32_t remainingSize;                                  /*!< Ce membre contient le nombre d'octets restant à analyser dans le fichier. */
   uint32_t bytePointer;                                    /*!< Ce membre contient l'adresse de l'octet en cours d'analyse dans le secteur. */
   uint32_t state;                                          /*!< Ce membre contient le registre d'état du parser (\ref T_mkSRECState). */
   uint32_t recordBytesCount;                               /*!< Ce membre contient le nombre d'octets (adresse + données + checksum) contenues dans le record. */
   uint32_t recordPointer;                                  /*!< Ce membre contient l'adresse du prochain octet à écrire dans le record. */
   uint32_t recordValidity;                                 /*!< Ce membre contient la variable d'état indiquant si le record est exploitable (1) ou non (0). */
   uint8_t  buf [ K_MK_LOADER_SREC_FILEBUFSIZE ];           /*!< Ce membre contient le buffer de travail du parser. */
   uint8_t  record [ K_MK_LOADER_SREC_RECORD_MAX_SIZE ];    /*!< Ce membre contient le buffer où les records sont enregistrés. */
};

/**
 *
 */

#endif


