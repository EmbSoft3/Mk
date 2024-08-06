/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_pool_types.h
* @brief Déclaration des types dédiés aux pools du système de fichiers.
* @date 13 juin 2021
*
*/

#ifndef MK_FILE_POOL_TYPES_H
#define MK_FILE_POOL_TYPES_H

/**
 * @struct T_mkFileArea
 * @brief Déclaration de la structure T_mkFileArea.
 *
 */

typedef struct T_mkFileArea T_mkFileArea;
struct T_mkFileArea
{
   T_mkPool* pool;                                             /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les fichiers (\ref T_mkFile). */
   T_mkPoolArea area;                                          /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkFile heap [ K_MK_FILE_NUMBER ];                         /*!< Ce membre contient la mémoire dédiée aux fichiers. */
};

/**
 * @struct T_mkFileMessageArea
 * @brief Déclaration de la structure T_mkFileMessageArea.
 *
 */

typedef struct T_mkFileMessageArea T_mkFileMessageArea;
struct T_mkFileMessageArea
{
   T_mkMail* request;                                          /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination des tâches de gestion du système de fichiers. */
   T_mkPoolArea requestArea;                                   /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t requestHeap [ K_MK_FILE_MESSAGE_AREA_SIZE ];       /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 *
 */

#endif
