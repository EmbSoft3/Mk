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
* @file mk_display_initLTDC.c
* @brief Définition de la fonction mk_display_initLTDC.
* @date 22 févr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_initLTDC ( void )
{
   /* Désactivation du périphérique LTDC */
   ltdc_disable ( );

   /* Désactivation des interruptions LTDC */
   ltdc_disableReloadInterrupt ( );
   ltdc_enableTransferErrorInterrupt ( );
   ltdc_disableFifoUnderrunInterrupt ( );
   ltdc_disableLineInterrupt ( );

   /* Remise à zéro des drapeaux d'interruption */
   ltdc_clearReloadInterrupt ( );
   ltdc_clearTransferErrorInterruptFlag ( );
   ltdc_clearFifoUnderrunInterrupt ( );
   ltdc_clearLineInterrupt ( );

   /* Configuration de la polarité des signaux de contrôle (actif à l'état bas) */
   ltdc_clearPolarity ( K_LTDC_HSYNC | K_LTDC_VSYNC | K_LTDC_PIXEL_CLOCK | K_LTDC_DATA_ENABLE );

   /* Configuration de la ligne déclenchant une interruption */
   ltdc_setLineInterrupt (
         K_MK_DISPLAY_LTDC_VSYNC_PULSE_WITDH + K_MK_DISPLAY_LTDC_VBP_WIDTH + K_MK_DISPLAY_LTDC_VACTIVE_WIDTH + 1
         );

   /* Configuration de la largeur de l'écran */
   ltdc_setWidth (
         K_MK_DISPLAY_LTDC_HSYNC_PULSE_WITDH,
         K_MK_DISPLAY_LTDC_HBP_WIDTH,
         K_MK_DISPLAY_LTDC_HACTIVE_WIDTH,
         K_MK_DISPLAY_LTDC_HFP_WIDTH
         );

   /* Configuration de la hauteur de l'écran */
   ltdc_setHeight (
         K_MK_DISPLAY_LTDC_VSYNC_PULSE_WITDH,
         K_MK_DISPLAY_LTDC_VBP_WIDTH,
         K_MK_DISPLAY_LTDC_VACTIVE_WIDTH,
         K_MK_DISPLAY_LTDC_VFP_WIDTH
         );

   /* Activation du dithering (écran 18bits) */
   /* Le dithering a été désactivé car l'alternance des pixels provoque un scintillement de l'écran */
   /* lorsque l'écran est regardé de près. */
   /*ltdc_enableDithering ( );*/

   /* Configuration de la couleur d'arrière plan */
   ltdc_setBackground ( K_MK_DISPLAY_LTDC_DEFAULT_BACKGROUND );

   /* Activation des interruptions */
   ltdc_enableTransferErrorInterrupt ( );
   ltdc_enableFifoUnderrunInterrupt ( );
   ltdc_enableLineInterrupt ( );

   /* Configuration des layers */
   mk_display_initLayer1 ( );
   mk_display_initLayer2 ( );

   /* Chargement de la configuration des layers */
   ltdc_loadLayers ( K_LTDC_IMMEDIATE );

   /* Activation du périphérique LTDC */
   ltdc_enable ( );

   /* Retour */
   return;
}




