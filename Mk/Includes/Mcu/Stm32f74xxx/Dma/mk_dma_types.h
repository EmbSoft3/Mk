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
* @file mk_dma_types.h
* @brief Déclaration des types dédiés à la DMA.
* @date 26 juin 2020
*
*/

#ifndef MK_DMA_TYPES_H
#define MK_DMA_TYPES_H

/**
 * @typedef T_mkDMACallback;
 * @brief Déclaration de la fonction de rappel DMA.
 *
 */

typedef void (*T_mkDMACallback ) ( void );

/**
 * @struct T_mkDMAPeripheral
 * @brief Déclaration de l'énumération T_mkDMAPeripheral.
 *
 */

typedef enum T_mkDMAPeripheral
{
   K_MK_DMA1 = 0,                                           /*!< Code indiquant que le périphérique DMA1 doit être utilisé. */
   K_MK_DMA2 = 1                                            /*!< Code indiquant que le périphérique DMA2 doit être utilisé. */
} T_mkDMAPeripheral;


/**
 * @struct T_mkDMAStreamStatus
 * @brief Déclaration de l'énumération T_mkDMAStreamStatus.
 *
 */

typedef enum T_mkDMAStreamStatus
{
   K_MK_DMA_CHANNEL_NOT_USED = 0,                           /*!< Code indiquant que le canal DMA n'est pas utilisé. */
   K_MK_DMA_CHANNEL_USED = 1                                /*!< Code indiquant que le canal DMA est utilisé. */
} T_mkDMAStreamStatus;

/**
 * @struct T_mkDMAStatus
 * @brief Déclaration de l'énumération T_mkDMAStatus.
 *
 */

typedef enum T_mkDMAStatus
{
   K_MK_DMA_STATUS_NO_FLAG = 0,                             /*!< Code indiquant que le transfert DMA n'a pas débuté. */
   K_MK_DMA_STATUS_TRANSFER_COMPLETED = 1,                  /*!< Code indiquant que le transfert DMA s'est correctement déroulé. */
   K_MK_DMA_STATUS_TRANSFER_ERROR = 2,                      /*!< Code indiquant qu'une erreur s'est produite durant le transfert DMA. */
   K_MK_DMA_STATUS_DIRECT_MODE_ERROR = 4                    /*!< Code indiquant qu'une erreur s'est produite durant le transfert DMA (dédié au mode 'Direct'). */
} T_mkDMAStatus;

/**
 * @struct T_mkDMAPipe
 * @brief Déclaration de la structure T_mkDMAPipe.
 *
 */

typedef struct T_mkDMAPipe T_mkDMAPipe;
struct T_mkDMAPipe
{
   T_mkAddr  addr;                                          /*!< Ce membre contient l'adresse du périphérique DMA. */
   uint32_t  index;                                         /*!< Ce membre contient l'index du périphérique DMA. */
   uint32_t  channel;                                       /*!< Ce membre contient le numéro du canal DMA associé au pipe. */
   uint32_t  stream;                                        /*!< Ce membre contient le numéro du flux DMA associé au pipe. */
   T_mkEvent* event;                                        /*!< Ce membre contient le registre d'événements associé au pipe. */
   T_mkDMAStatus status;                                    /*!< Ce membre contient le registre de statuts associé au pipe. */
   T_mkDMACallback volatile callback;                       /*!< Ce membre contient le pointeur de callback. */
};

/**
 * @struct T_mkDMAHandler
 * @brief Déclaration de la structure T_mkDMAHandler.
 *
 */

typedef struct T_mkDMAHandler T_mkDMAHandler;
struct T_mkDMAHandler
{
   T_mkEvent* event;                                        /*!< Ce membre contient un champ d'événement permettant d'allouer les canaux DMA de manière sécurisée. */
};

/**
 *
 */

#endif


