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
* @file mk_mmc_openPipe.c
* @brief Définition de la fonction mk_mmc_openPipe.
* @date 6 juil. 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_mmc_setStream ( T_mkMMCHandler* p_handler )
{
   /* Désactivation du flux */
   dma_disableStream ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Configuration de l'adresse de base du registre de données MMC */
   dma_setPeripheralAddr ( p_handler->pipe->addr, p_handler->pipe->stream, ( uint32_t ) K_MMC_FIFO );

   /* Désactivation du mode direct (les transferts sont réalisés en utilisant le FIFO) */
   dma_disableDirectMode ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Configuration du seuil de déclenchement des transferts */
   dma_setFifoThreshold ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_FIFO_THRESHOLD_100_PERCENTS_FULL );

   /* Configuration du mode de fonctionnement */
   dma_enableMemoryPostIncrementation ( p_handler->pipe->addr, p_handler->pipe->stream );
   dma_disablePeripheralPostIncrementation ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Configuration de la taille de l'incrémentation automatique */
   /* Basculer la constante à 8BITS pour réaliser des accès non alignés sur 32 bits. */
   dma_setMemoryDataSize ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_SIZE_8BITS );

   /* Configuration de la taille de l'incrémentation automatique */
   dma_setPeripheralDataSize ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_SIZE_32BITS );

   /* Configuration du controleur de flux */
   dma_setFlowCtrl ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_FLOW_CTRL_PERIPHERAL );

   /* Configuration du nombre de transaction constituant un burst */
   dma_setPeripheralBurst ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_BURST_4BEATS );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_openPipe ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_handler->pipe == K_MK_NULL ) )
   {
      /* Ouverture d'un pipe DMA */
      l_result = mk_dma_openPipe ( &p_handler->pipe, mk_mmc_callback, K_DMA2, K_DMA_CHANNEL4, K_DMA_STREAM3, K_DMA_PRIORITY_VERY_HIGH );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Pré-configuration d'un flux DMA */
         mk_mmc_setStream ( p_handler );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


