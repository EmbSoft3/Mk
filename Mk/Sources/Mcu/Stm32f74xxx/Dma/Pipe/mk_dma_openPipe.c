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
* @file mk_dma_openPipe.c
* @brief Définition de la fonction mk_dma_openPipe.
* @date 26 juin 2020
*
*/

#include "mk_dma_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_dma_initStream ( T_mkDMAPipe* p_pipe, uint32_t p_priority )
{
   /* Désactivation du flux */
   dma_disableStream ( p_pipe->addr, p_pipe->stream );

   /* Configuration du canal */
   dma_setChannel ( p_pipe->addr, p_pipe->stream, p_pipe->channel );

   /* Configuration de la priorité du flux DMA */
   dma_setPriority ( p_pipe->addr, p_pipe->stream, p_priority );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dma_openPipe ( T_mkDMAPipe** p_pipe, T_mkDMACallback p_callback, T_mkAddr p_dma, uint32_t p_channel, uint32_t p_stream, uint32_t p_priority )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une variable contenant l'index du périphérique DMA */
   uint8_t l_dma = K_MK_DMA1;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField = 0;

   /* Si les paramètres sont valides */
   if ( ( p_pipe != K_MK_NULL ) && ( *p_pipe == K_MK_NULL ) && ( ( p_channel >> 25 ) < K_MK_DMA_CHANNEL_NUMBER ) && ( p_stream < K_MK_DMA_STREAM_NUMBER ) )
   {
      /* Si le périphérique matériel est le périphérique DMA2 */
      if ( p_dma == K_DMA2 )
      {
         /* Actualisation de l'index du périphérique DMA */
         l_dma = K_MK_DMA2;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Attente et allocation d'un canal DMA */
      l_result = mk_event_wait ( g_mkDMAHandler.event, ( K_MK_EVENT_AND | K_MK_EVENT_CLEAR | ( uint32_t ) ( 1 << ( ( uint32_t ) ( l_dma * K_MK_DMA_STREAM_NUMBER ) + p_stream ) ) ), &l_eventField, K_MK_TASK_WAIT_FOREVER );

      /* Si la prise du mutex a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Configuration du pointeur de pipe */
         *p_pipe = &g_mkDMAPipe [ l_dma ] [ p_stream ];

         /* Configuration du pipe */
         ( *p_pipe )->index    = l_dma;
         ( *p_pipe )->addr     = p_dma;
         ( *p_pipe )->channel  = p_channel;
         ( *p_pipe )->stream   = p_stream;
         ( *p_pipe )->callback = p_callback;

         /* Initialisation du flux DMA */
         mk_dma_initStream ( *p_pipe, p_priority );
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
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


