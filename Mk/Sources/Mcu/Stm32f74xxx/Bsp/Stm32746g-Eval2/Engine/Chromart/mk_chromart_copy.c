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
* @file mk_chromart_copy.c
* @brief Définition de la fonction mk_chromart_copy.
* @date 31 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_startCopyRequest ( T_mkChromartRequest* p_request, uint32_t p_bytesPerPixel, uint32_t p_resolution )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Configuration du canal DMA2D */
   dma2d_setMode ( K_DMA2D_MEMORY_TO_MEMORY );

   /* Configuration du format des pixels */
   dma2d_setFormat ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FORMAT_ARGB8888 );
   dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, p_resolution );

   /* Si le layer est au format RGB888 */
   if ( p_bytesPerPixel == K_MK_DISPLAY_RGB888 )
   {
      dma2d_setFormat ( K_DMA2D_PFC_FOREGROUND, K_DMA2D_FORMAT_RGB888 );
      dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, p_resolution );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration de la fenêtre */
   dma2d_setRectangle ( ( uint32_t ) p_request->plane.width, ( uint32_t ) p_request->plane.height );

   /* Configuration de la bande passante du transfert */
   dma2d_setTimer ( K_MK_DISPLAY_DMA2D_COPY_BANDWIDTH );

   /* Déclenchement du transfert DMA2D */
   dma2d_start ( );

   /* Attendre jusqu'à la fin du transfert */
   l_result = mk_chromart_wait ( );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_copy ( T_mkTask* p_task, T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_area, l_bytesPerPixel;
   uint32_t l_firstWindowAddr, l_lastWindowAddr, l_lastFrameAddr, l_sourceWindowAddr;
   uint32_t l_direction, l_resolution;

   /* Récupération de la direction du transfert */
   l_direction = p_request->content.copy.dirOrResolution & 0xFFFF0000;

   /* Récupération de la résolution du buffer de sortie */
   l_resolution = p_request->content.copy.dirOrResolution & 0x0000FFFF;

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_request->content.copy.destinationLayer ];

   /* Détermination de l'adresse source */
   l_sourceWindowAddr = ( uint32_t ) ( p_request->content.copy.sourceAddr );

   /* Vérification de la validité de l'instance de retour */
   l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( l_sourceWindowAddr ) );
   l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( ( uint8_t* ) l_sourceWindowAddr +
         K_MK_DISPLAY_BYTE_PER_PIXEL * ( p_request->plane.width * p_request->plane.height ) - 1 ) );

   /* Si le transfert s'effectue du buffer graphique vers un buffer utilisateur, si ce buffer est située en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( l_direction == K_MK_GRAPHICS_FRAME_TO_ADDR ) &&
        ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Ne rien faire */
   }

   /* Sinon */
   else
   {
      /* Si les paramètres de la requête sont valides */
      if ( ( p_request->content.copy.destinationOffset < g_mkDisplay.screen.width ) &&
           ( p_request->content.copy.sourceOffset  < g_mkDisplay.screen.width ) &&
           ( p_request->content.copy.destinationLayer <= K_MK_GRAPHICS_BACKGROUND ) )
      {
         /* Détermination de la première adresse de la zone à dessiner */
         l_firstWindowAddr = ( uint32_t ) ( g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.copy.destinationLayer ] ) +
               l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) p_request->plane.y ) + ( uint32_t ) p_request->plane.x );

         /* Si la direction du transfert s'effectue d'un buffer utilisateur vers un buffer graphique */
         if ( l_direction == K_MK_GRAPHICS_ADDR_TO_FRAME )
         {
            /* Détermination de la dernière adresse de la zone à dessiner */
            l_lastWindowAddr = l_firstWindowAddr + K_MK_DISPLAY_BYTE_PER_PIXEL * ( p_request->plane.width * p_request->plane.height );

            /* Détermination de l'adresse de fin du buffer graphique */
            l_lastFrameAddr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.copy.destinationLayer ] +
                  K_MK_DISPLAY_BYTE_PER_PIXEL * ( g_mkDisplay.screen.width * g_mkDisplay.screen.height ) ;

            /* Configuration des adresses de base et de destination */
            dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, l_firstWindowAddr );
            dma2d_setAddr ( K_DMA2D_MEM_FOREGROUND, l_sourceWindowAddr );

            /* Configuration des offsets */
            dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, ( uint32_t ) p_request->content.copy.destinationOffset );
            dma2d_setOffset ( K_DMA2D_MEM_FOREGROUND, ( uint32_t ) p_request->content.copy.sourceOffset );

            /* Si la requête de type COPY peut être réalisée */
            if ( l_lastWindowAddr <= l_lastFrameAddr )
            {
               /* Déclenchement de la requête */
               l_result = mk_chromart_startCopyRequest ( p_request, l_bytesPerPixel, l_resolution );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Sinon (buffer graphique vers buffer utilisateur ) */
         else
         {
            /* Configuration des adresses de base et de destination */
            dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, l_sourceWindowAddr );
            dma2d_setAddr ( K_DMA2D_MEM_FOREGROUND, l_firstWindowAddr );

            dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, ( uint32_t ) p_request->content.copy.sourceOffset );
            dma2d_setOffset ( K_DMA2D_MEM_FOREGROUND, ( uint32_t ) p_request->content.copy.destinationOffset );

            /* Déclenchement de la requête */
            l_result = mk_chromart_startCopyRequest ( p_request, l_bytesPerPixel, l_resolution );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}



