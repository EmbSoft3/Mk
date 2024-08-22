/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_msc_pool_types.h
* @brief Déclaration des types dédiés aux pools des périphériques de stockage.
* @date 17 mai 2020
*
*/

#ifndef MK_MSC_POOL_TYPES_H
#define MK_MSC_POOL_TYPES_H

/**
 * @struct T_mkMSCMessageArea
 * @brief Déclaration de la structure T_mkMSCMessageArea.
 *
 */

typedef struct T_mkMSCMessageArea T_mkMSCMessageArea;
struct T_mkMSCMessageArea
{
   T_mkMail* mail;                                          /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du terminal MSC (depuis HCD). */
   T_mkPoolArea area;                                       /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t heap [ K_MK_MSC_MESSAGE_AREA_SIZE ];            /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkMSCRequestArea
 * @brief Déclaration de la structure T_mkMSCRequestArea.
 *
 */

typedef struct T_mkMSCRequestArea T_mkMSCRequestArea;
struct T_mkMSCRequestArea
{
   T_mkMail* request;                                       /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du terminal MSC (depuis le système de fichiers). */
   T_mkPoolArea area;                                       /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t heap [ K_MK_DISK_REQUEST_AREA_SIZE ];           /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkMSCPool
 * @brief Déclaration de la structure T_mkMSCPool.
 *
 */

typedef struct T_mkMSCPool T_mkMSCPool;
struct T_mkMSCPool
{
   T_mkPool* pool;                                          /*!< Ce membre contient un gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkMSCDevice. */
   T_mkPoolArea area;                                       /*!< Ce membre contient un gestionnaire d'allocation dynamique ('Heap'). */
   uint32_t heap [ K_MK_MSC_POOL_SIZE ];                    /*!< Ce membre contient un buffer dédiée à la 'Heap'. */
};

/**
 *
 */

#endif

