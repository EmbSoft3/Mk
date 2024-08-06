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
* @file mk_i2c_openPipe.c
* @brief Définition de la fonction mk_i2c_openPipe.
* @date 1 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_setStream ( T_mkDMAPipe* p_pipe, uint32_t p_registerAddr )
{
   /* Désactivation du flux DMA */
   dma_disableStream ( p_pipe->addr, p_pipe->stream );

   /* Configuration de l'adresse de base du registre de données I2C */
   dma_setPeripheralAddr ( p_pipe->addr, p_pipe->stream, p_registerAddr );

   /* Désactivation du mode direct (les transferts sont réalisés en utilisant le FIFO) */
   dma_disableDirectMode ( p_pipe->addr, p_pipe->stream );

   /* Configuration du seuil de déclenchement des transferts */
   dma_setFifoThreshold ( p_pipe->addr, p_pipe->stream, K_DMA_FIFO_THRESHOLD_100_PERCENTS_FULL );

   /* Configuration du mode de fonctionnement */
   dma_enableMemoryPostIncrementation ( p_pipe->addr, p_pipe->stream );
   dma_disablePeripheralPostIncrementation ( p_pipe->addr, p_pipe->stream );

   /* Configuration de la taille des données */
   dma_setMemoryDataSize ( p_pipe->addr, p_pipe->stream, K_DMA_SIZE_8BITS );
   dma_setPeripheralDataSize ( p_pipe->addr, p_pipe->stream, K_DMA_SIZE_8BITS );

   /* Configuration du contrôleur de flux */
   dma_setFlowCtrl ( p_pipe->addr, p_pipe->stream, K_DMA_FLOW_CTRL_DMA );

   /* Configuration du nombre de transaction constituant un burst */
   dma_setPeripheralBurst ( p_pipe->addr, p_pipe->stream, K_DMA_BURST_SINGLE );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_openPipe ( T_mkI2CHandler* p_handler, T_mkDMAPipe** p_pipe, uint32_t p_channel, uint32_t p_stream, T_mkDMACallback p_callback, uint32_t p_registerAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( *p_pipe == K_MK_NULL ) )
   {
      /* Ouverture d'un pipe DMA */
      l_result = mk_dma_openPipe ( p_pipe, p_callback, K_DMA1, p_channel, p_stream, K_DMA_PRIORITY_VERY_HIGH );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Pré-configuration d'un flux DMA */
         mk_i2c_setStream ( *p_pipe, p_registerAddr );
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



