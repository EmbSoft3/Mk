/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_display_initChromArt.c
* @brief Définition de la fonction mk_display_initChromArt.
* @date 23 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_enableDMA2DRequest ( void )
{
   /* Configuration de la priorité de la requête d'interruption DMA2D */
   nvic_setRequestPriority ( K_NVIC_DMA2D, K_MK_DISPLAY_DMA2D_REQUEST_PRIORITY );

   /* Activation de la requête d'interruption du périphérique DMA2D */
   nvic_enableRequest ( K_NVIC_DMA2D );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_initChromArt ( void )
{
   /* Désactivation des interruptions du périphérique DMA2D */
   dma2d_disableClutAccessErrorInterrupt ( );
   dma2d_disableClutTransferCompleteInterrupt ( );
   dma2d_disableTransferCompleteInterrupt ( );
   dma2d_disableTransferErrorInterrupt ( );
   dma2d_disableConfigurationErrorInterrupt ( );
   dma2d_disableTransferWatermarkInterrupt ( );

   /* Remise à zéro des drapeaux d'interruption du périphérique DMA2D */
   dma2d_clearClutAccessErrorInterruptFlag ( );
   dma2d_clearClutTransferCompleteInterruptFlag ( );
   dma2d_clearTransferCompleteInterruptFlag ( );
   dma2d_clearTransferErrorInterruptFlag ( );
   dma2d_clearConfigurationErrorInterruptFlag ( );
   dma2d_clearTransferWatermarkInterruptFlag ( );

   /* Configuration du limiteur de bande passante */
   dma2d_disableTimer ( );
   dma2d_setTimer ( K_MK_DISPLAY_DMA2D_FILL_BANDWIDTH );
   dma2d_enableTimer ( );

   /* Activation de la requête d'interruption DMA2D */
   mk_display_enableDMA2DRequest ( );

   /* Activation des interruptions du périphérique DMA2D */
   dma2d_enableTransferCompleteInterrupt ( );
   dma2d_enableTransferErrorInterrupt ( );
   dma2d_enableConfigurationErrorInterrupt ( );

   /* Retour */
   return;
}



