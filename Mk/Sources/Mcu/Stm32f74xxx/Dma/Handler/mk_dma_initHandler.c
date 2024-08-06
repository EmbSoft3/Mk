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
* @file mk_dma_initHandler.c
* @brief Définition de la fonction mk_dma_initHandler.
* @date 27 juin 2020
*
*/

#include "mk_dma_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_dma_initRequest ( void )
{
   /* Activation des interruptions du périphérique DMA1 */
   nvic_enableRequest ( K_NVIC_DMA1_STREAM0 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM1 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM2 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM3 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM4 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM5 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM6 );
   nvic_enableRequest ( K_NVIC_DMA1_STREAM7 );

   /* Activation des interruptions du périphérique DMA2 */
   nvic_enableRequest ( K_NVIC_DMA2_STREAM0 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM1 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM2 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM3 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM4 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM5 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM6 );
   nvic_enableRequest ( K_NVIC_DMA2_STREAM7 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dma_initHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des compteurs */
   uint32_t l_dmaCounter, l_streamCounter;

   /* Réinitialisation du gestionnaire DMA */
   _writeWords ( &g_mkDMAHandler, 0, sizeof ( T_mkDMAHandler ) >> 2 );

   /* Activation des requêtes d'interruptions */
   mk_dma_initRequest ( );

   /* Initialisation du registre d'événement */
   l_result = mk_event_create ( &g_mkDMAHandler.event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, K_MK_DMA_EVENT_INIT_VALUE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Pour le nombre de périphériques DMA supportés par le système */
      for ( l_dmaCounter = 0 ; l_dmaCounter < K_MK_DMA_NUMBER ; l_dmaCounter++ )
      {
         /* Pour le nombre de flux DMA supportés par chaque périphérique */
         for ( l_streamCounter = 0 ; l_streamCounter < K_MK_DMA_STREAM_NUMBER ; l_streamCounter++ )
         {
            /* Réinitialisation du pipe */
            _writeWords ( &g_mkDMAPipe [ l_dmaCounter ] [ l_streamCounter ], 0, sizeof ( T_mkDMAPipe ) >> 2 );

            /* Initialisation du registre d'événement */
            l_result |= mk_event_create ( &g_mkDMAPipe [ l_dmaCounter ] [ l_streamCounter ].event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, 0 );
         }
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
