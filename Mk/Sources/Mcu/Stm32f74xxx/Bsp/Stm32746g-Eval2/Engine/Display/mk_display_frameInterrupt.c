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
* @file mk_display_frameInterrupt.c
* @brief Définition de la fonction mk_display_frameInterrupt.
* @date 17 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_frameInterrupt ( void )
{
   /* Remise à zéro du drapeau d'interruption */
   ltdc_clearLineInterrupt ( );

   /* Désactivation du limiteur de bande passante de l'accélérateur chromart */
   dma2d_disableTimer ( );

   /* Si le prochain buffer peut être affiché */
   if ( g_mkDisplay.pnt.currentBufferPrinted->next->validity == 1 )
   {
      /* Configuration de l'adresse de base des layers */
      ltdc_setFrameAddr ( K_LTDC_LAYER1, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->next->addr [ K_MK_GRAPHICS_BACKGROUND ] );
      ltdc_setFrameAddr ( K_LTDC_LAYER2, ( uint32_t ) g_mkDisplay.pnt.currentBufferPrinted->next->addr [ K_MK_GRAPHICS_FOREGROUND ] );

      /* Réinitialisation des drapeaux des buffers */
      g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer = 0;
      g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer = 0;

      /* Actualisation de l'adresse du buffer affiché */
      g_mkDisplay.pnt.currentBufferPrinted = g_mkDisplay.pnt.currentBufferPrinted->next;

      /* Activation des layers */
      /* Si le layer de premier plan doit être activé */
      if ( g_mkDisplay.pnt.currentBufferPrinted->status.foregroundLayer == 1 )
      {
         /* Activation du layer */
         ltdc_enableLayer ( K_LTDC_LAYER2 );
      }

      /* Sinon */
      else
      {
         /* Désactivation du layer */
         ltdc_disableLayer ( K_LTDC_LAYER2 );
      }

      /* Si le layer d'arrière plan doit être activé */
      if ( g_mkDisplay.pnt.currentBufferPrinted->status.backgroundLayer == 1 )
      {
         /* Activation du layer */
         ltdc_enableLayer ( K_LTDC_LAYER1 );
      }

      /* Sinon */
      else
      {
         /* Désactivation du layer */
         ltdc_disableLayer ( K_LTDC_LAYER1 );
      }

      /* Réinitialisation du drapeau de validité */
      g_mkDisplay.pnt.currentBufferPrinted->validity = 0;

      /* Actualisation du layer */
      ltdc_loadLayers ( K_LTDC_IMMEDIATE );

      /* Si le painter doit être redémarré */
      if ( g_mkDisplay.status.wakeup == 1 )
      {
         /* Réveil de la tâche de peinture privilégiée */
         ( void ) mk_event_set ( g_mkDisplay.painter.frameEvent, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG );

         /* Réinitialisation du drapeau */
         g_mkDisplay.status.wakeup = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du compteur de trame */
      g_mkDisplay.framerate.counter++;
   }

   /* Sinon, l'intégralité des objets n'ont pas été traités durant la frame */
   /* courante */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation de la valeur du frameRate */
   g_mkDisplay.framerate.period++;

   /* Si la valeur du frameRate doit être actualisé */
   if ( g_mkDisplay.framerate.counter == K_MK_DISPLAY_FRAMERATE )
   {
      /* Détermination de la valeur du framerate */
      /* framerate.value   -> K_MK_DISPLAY_FRAMERATE */
      /* framerate.counter -> framerate.period avec framerate.counter = K_MK_DISPLAY_FRAMERATE */
      /* framerate.value = K_MK_DISPLAY_FRAMERATE² / framerate.period. */
      g_mkDisplay.framerate.value = ( uint32_t ) ( ( K_MK_DISPLAY_FRAMERATE * K_MK_DISPLAY_FRAMERATE ) / g_mkDisplay.framerate.period ) ;

      /* Acutalisation des données de calcul du frameRate */
      g_mkDisplay.framerate.period = 0;
      g_mkDisplay.framerate.counter = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Reset de la pipeline */
   _cortex_resetPipeline ( );

   /* Retour */
   return;
}



