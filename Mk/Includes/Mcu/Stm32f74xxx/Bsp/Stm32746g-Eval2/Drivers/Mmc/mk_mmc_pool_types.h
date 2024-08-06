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
* @file mk_mmc_pool_types.h
* @brief Déclaration des types dédiés aux pools SD/MMC.
* @date 20 juin 2020
*
*/

#ifndef MK_MMC_POOL_TYPES_H
#define MK_MMC_POOL_TYPES_H

/**
 * @struct T_mkMMCPool
 * @brief Déclaration de la structure T_mkMMCPool.
 *
 */

typedef struct T_mkMMCPool T_mkMMCPool;
struct T_mkMMCPool
{
   T_mkPool* pool;                                          /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les périphériques MMC (\ref T_mkMMCDevice). */
   T_mkPoolArea area;                                       /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   uint32_t heap [ K_MK_MMC_POOL_SIZE ];                    /*!< Ce membre contient la mémoire dédiée aux périphériques MMC. */
};

/**
 * @struct T_mkMMCRequestArea
 * @brief Déclaration de la structure T_mkMMCRequestArea.
 *
 */

typedef struct T_mkMMCRequestArea T_mkMMCRequestArea;
struct T_mkMMCRequestArea
{
   T_mkMail* request;                                       /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination du terminal MMC. */
   T_mkPoolArea area;                                       /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t heap [ K_MK_DISK_REQUEST_AREA_SIZE ];           /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 *
 */

#endif


