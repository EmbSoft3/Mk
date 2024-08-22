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
* @file mk_display_initLayer2.c
* @brief Définition de la fonction mk_display_initLayer2.
* @date 22 févr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_clearBuffer ( uint32_t p_argb )
{
   /* Remise à zéro du buffer graphique 1 */
   _writeWords ( K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR, p_argb,
                 K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_initLayer2 ( void )
{
   /* Désactivation des mécanismes non utilisés */
   ltdc_disableLookUpTable ( K_LTDC_LAYER2 );
   ltdc_disableColorKeying ( K_LTDC_LAYER2 );

   /* Configuration de la clé du mécanisme ColorKeying */
   ltdc_setColorKeying ( K_LTDC_LAYER2, 0 );

   /* Configuration du format des pixels */
   /* Ne pas oublier de modifier la valeur de la donnée foregroundBytesPerPixel (T_mkDisplayScreen) si la configuration */
   /* est modifiée. */
   ltdc_setPixelFormat ( K_LTDC_LAYER2, K_LTDC_ARGB8888 );

   /* Configuration de la composante alpha par défaut */
   ltdc_setConstantAlpha ( K_LTDC_LAYER2, 255 );

   /* Configuration de l'arrière plan par défaut */
   ltdc_setDefaultColor ( K_LTDC_LAYER2, K_MK_DISPLAY_LTDC_DEFAULT_LAYER_BACKGROUND );

   /* Configuration de la fenêtre du layer */
   ltdc_setLayer (
         K_LTDC_LAYER2,
         0, g_mkDisplay.screen.width - 1,
         0, g_mkDisplay.screen.height - 1
         );

   /* Configuration des facteurs alpha */
   ltdc_setBlendingFactors (
         K_LTDC_LAYER2,
         K_LTDC_BLENDING_FACTOR1_PXL_ALPHA_x_CONSTANT_ALPHA,
         K_LTDC_BLENDING_FACTOR2_1_DIFF_PXL_ALPHA_x_CONSTANT_ALPHA
         );

   /* Configuration du buffer graphique */
   /* Peu importe le format des pixels, on alloue 4 octets pour chaque pixels du buffer */
   ltdc_setFrameBuffer (
         K_LTDC_LAYER2,
         ( uint32_t ) K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR,
         K_MK_DISPLAY_BYTE_PER_PIXEL * g_mkDisplay.screen.width,
         K_MK_DISPLAY_BYTE_PER_PIXEL * g_mkDisplay.screen.width, g_mkDisplay.screen.height );

   /* Réinitialisation du buffer graphique */
   mk_display_clearBuffer ( K_MK_DISPLAY_LTDC_DEFAULT_LAYER_BACKGROUND );

   /* Activation du layer */
   ltdc_enableLayer ( K_LTDC_LAYER2 );

   /* Retour */
   return;
}




