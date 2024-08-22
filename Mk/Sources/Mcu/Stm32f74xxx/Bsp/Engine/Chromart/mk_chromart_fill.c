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
* @file mk_chromart_fill.c
* @brief Définition de la fonction mk_chromart_fill.
* @date 1 avr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_fill ( T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_bytesPerPixel, l_firstWindowAddr, l_lastWindowAddr, l_lastFrameAddr, *l_pnt;

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_request->content.fill.layer ];

   /* Détermination de l'adresse de départ de la zone à dessiner */
   l_firstWindowAddr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.fill.layer ]
         + l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) p_request->plane.y ) + ( uint32_t ) p_request->plane.x );

   /* Détermination de l'adresse de fin de la zone à dessiner */
   l_lastWindowAddr = l_firstWindowAddr + K_MK_DISPLAY_BYTE_PER_PIXEL * ( p_request->plane.width * p_request->plane.height );

   /* Détermination de l'adresse de fin du buffer graphique */
   l_lastFrameAddr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.fill.layer ] +
         K_MK_DISPLAY_BYTE_PER_PIXEL * ( g_mkDisplay.screen.width * g_mkDisplay.screen.height ) ;

   /* Si la requête est contenue dans un seul buffer graphique */
   if ( ( l_lastWindowAddr <= l_lastFrameAddr ) &&
        ( p_request->content.fill.offset < g_mkDisplay.screen.width ) && ( p_request->content.fill.layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Si un seul pixel doit être dessiné */
      if ( ( p_request->plane.width == 1 ) && ( p_request->plane.height == 1 ) )
      {
         /* Récupération de l'adresse du pixel */
         l_pnt = ( uint32_t* ) l_firstWindowAddr;

         /* Ecriture du pixel directement dans la mémoire graphique */
         if ( l_bytesPerPixel == K_MK_DISPLAY_RGB888 )
         {
            _copy ( l_pnt, &p_request->content.fill.color, 3 );
         }

         /* Sinon */
         else
         {
            *l_pnt = p_request->content.fill.color;
         }
      }

      /* Sinon */
      else
      {
         /* Configuration du canal DMA2D */
         dma2d_setMode ( K_DMA2D_REGISTER_TO_MEMORY );
         dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, l_firstWindowAddr );
         dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, p_request->content.fill.offset );

         /* Configuration des caractéristique de la figure */
         dma2d_setColor ( K_DMA2D_PFC_OUTPUT, p_request->content.fill.color );
         dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_ARGB8888 );
         dma2d_setRectangle ( ( uint32_t ) p_request->plane.width, ( uint32_t ) p_request->plane.height );

         /* Si le layer est au format RGB888 */
         if ( l_bytesPerPixel == K_MK_DISPLAY_RGB888 )
         {
            dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_RGB888 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de la bande passante du transfert */
         dma2d_setTimer ( K_MK_DISPLAY_DMA2D_FILL_BANDWIDTH );

         /* Déclenchement du transfert DMA2D */
         dma2d_start ( );

         /* Attendre jusqu'à la fin du transfert */
         l_result = mk_chromart_wait ( );
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


