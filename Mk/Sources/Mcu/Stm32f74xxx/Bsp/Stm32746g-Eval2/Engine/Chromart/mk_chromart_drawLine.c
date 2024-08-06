/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_chromart_drawLine.c
* @brief Définition de la fonction mk_chromart_drawLine.
* @date 2 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_drawPixelLine ( T_mkChromartPlane* p_plane, uint32_t p_layer, uint32_t p_offset, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_bytesPerPixel, l_addr, *l_pnt;

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_layer ];

   /* Détermination de l'adresse de base */
   l_addr =  ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_layer ] +
         l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) p_plane->y ) + ( uint32_t ) p_plane->x );

   /* Si un seul pixel doit être dessiné */
   if ( ( p_plane->width == 1 ) && ( p_plane->height == 1 ) )
   {
      /* Récupération de l'adresse du pixel */
      l_pnt = ( uint32_t* ) l_addr;

      /* Ecriture du pixel directement dans la mémoire graphique */
      *l_pnt = p_argb;
   }

   /* Sinon */
   else
   {
      /* Configuration du canal DMA2D */
      dma2d_setMode ( K_DMA2D_REGISTER_TO_MEMORY );
      dma2d_setAddr ( K_DMA2D_MEM_OUTPUT, l_addr );
      dma2d_setOffset ( K_DMA2D_MEM_OUTPUT, p_offset );

      /* Configuration des caractéristique de la figure */
      dma2d_setColor ( K_DMA2D_PFC_OUTPUT, p_argb );
      dma2d_setFormat ( K_DMA2D_PFC_OUTPUT, K_DMA2D_FORMAT_ARGB8888 );
      dma2d_setRectangle ( ( uint32_t ) p_plane->width, ( uint32_t ) p_plane->height );

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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_plotHorizontal ( uint32_t p_layer, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2, uint32_t p_argb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration du parser de dessin de ligne */
   T_mkBresenhamParser l_parser;

   /* Déclaration d'un plan */
   T_mkChromartPlane l_plane;

   /* Déclaration d'un compteur sur l'axe des abscisses et d'un compteur de pixel */
   uint32_t l_counter = p_x1, l_pixelCounter = 0;

   /* Initialisation du parser */
   mk_parser_initBresenhamHorizontal ( &l_parser, p_x1, p_y1, p_x2, p_y2 );

   /* Pour les n pixels de la ligne */
   for ( ; ( l_counter < p_x2 ) && ( l_result == K_MK_OK ) ; l_counter++ )
   {
      /* Si l'ordonnée doit être actualisée */
      if ( l_parser.d > 0 )
      {
         /* Configuration du plan */
         mk_chromart_setPlane ( &l_plane, ( l_counter - l_pixelCounter ), ( uint32_t ) l_parser.y, l_pixelCounter + 1, 1 );

         /* Dessin des 'n' pixels précédents (pas d'offset) */
         l_result = mk_chromart_drawPixelLine ( &l_plane, p_layer, 0, p_argb );

         /* Actualisation de l'ordonnée et de l'erreur */
         l_parser.y += ( l_parser.yi );
         l_parser.d -= ( l_parser.dx << 1 );

         /* Réinitialisation du compteur de pixels */
         l_pixelCounter = 0;
      }

      /* Sinon */
      else
      {
         /* Actualisation du nombre de pixels à dessiner */
         l_pixelCounter++;
      }

      /* Actualisation de l'erreur */
      l_parser.d += ( l_parser.dy << 1 );
   }

   /* Si les pixels précédents doivent être dessinés */
   if ( ( l_pixelCounter != 0 ) && ( l_result == K_MK_OK ) )
   {
      /* Configuration du plan */
      mk_chromart_setPlane ( &l_plane, ( l_counter - l_pixelCounter ), ( uint32_t ) l_parser.y, l_pixelCounter + 1, 1 );

      /* Dessin des 'n' pixels (pas d'offset) */
      l_result = mk_chromart_drawPixelLine ( &l_plane, p_layer, 0, p_argb );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_plotVertical ( uint32_t p_layer, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2, uint32_t p_argb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un plan */
   T_mkChromartPlane l_plane;

   /* Déclaration du parser de dessin de ligne */
   T_mkBresenhamParser l_parser;

   /* Déclaration d'un compteur sur l'axe des abscisses et d'un compteur de pixel */
   uint32_t l_counter = p_y1, l_pixelCounter = 0;

   /* Initialisation du parser */
   mk_parser_initBresenhamVertical ( &l_parser, p_x1, p_y1, p_x2, p_y2 );

   /* Pour les n pixels de la ligne */
   for ( ; ( l_counter < p_y2 ) && ( l_result == K_MK_OK ) ; l_counter++ )
   {
      /* Si l'abscisse doit être actualisé */
      if ( l_parser.d > 0 )
      {
         /* Configuration du plan */
         mk_chromart_setPlane ( &l_plane, ( uint32_t ) l_parser.x, ( l_counter - l_pixelCounter ), 1, l_pixelCounter + 1 );

         /* Dessin des 'n' pixels précédents (avec offset) */
         l_result = mk_chromart_drawPixelLine ( &l_plane, p_layer, g_mkDisplay.screen.width - 1, p_argb );

         /* Actualisation de l'abscisse et de l'erreur */
         l_parser.x += ( l_parser.xi );
         l_parser.d -= ( l_parser.dy << 1 );

         /* Réinitialisation du compteur de pixels */
         l_pixelCounter = 0;
      }

      /* Sinon */
      else
      {
         /* Actualisation du nombre de pixels à dessiner */
         l_pixelCounter++;
      }

      /* Actualisation de l'erreur */
      l_parser.d += ( l_parser.dx << 1 );
   }

   /* Si les pixels précédents doivent être dessinés */
   if ( ( l_pixelCounter != 0 ) && ( l_result == K_MK_OK ) )
   {
      /* Configuration du plan */
      mk_chromart_setPlane ( &l_plane, ( uint32_t ) l_parser.x, ( l_counter - l_pixelCounter ), 1, l_pixelCounter + 1 );

      /* Dessin des 'n' pixels (avec offset) */
      l_result = mk_chromart_drawPixelLine ( &l_plane, p_layer, g_mkDisplay.screen.width - 1, p_argb );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_drawLine ( T_mkChromartRequest* p_request )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration des vecteurs de travail */
   T_mkVect2D l_v1, l_v2;

   /* Déclaration des composantes du coeficient directeur */
   real32_t l_dx;
   real32_t l_dy;

   /* Configuration des couples de coordonnées */
   mk_vect2d_setCoord ( &l_v1, ( real32_t ) p_request->plane.x, ( real32_t ) p_request->plane.y );
   mk_vect2d_setCoord ( &l_v2, ( real32_t ) p_request->content.line.x, ( real32_t ) p_request->content.line.y );

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &l_v1, &l_v2, &l_v1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_request->content.line.layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Détermination des valeurs absolues du coeficient directeur */
      l_dx = _math_vabs ( l_v2.x - l_v1.x );
      l_dy = _math_vabs ( l_v2.y - l_v1.y );

      /* Si dessin d'une ligne sur l'axe horizontal */
      if ( l_dy < l_dx )
      {
         /* Permutation des abscisses pour dessin de gauche à droite */
         if ( l_v1.x > l_v2.x )
         {
            /* Dessin de la ligne */
            l_result = mk_chromart_plotHorizontal ( p_request->content.line.layer, ( uint32_t ) l_v2.x, ( uint32_t ) l_v2.y, ( uint32_t ) l_v1.x, ( uint32_t ) l_v1.y, p_request->content.line.color );
         }

         /* Sinon */
         else
         {
            /* Dessin de la ligne */
            l_result = mk_chromart_plotHorizontal ( p_request->content.line.layer, ( uint32_t ) l_v1.x, ( uint32_t ) l_v1.y, ( uint32_t ) l_v2.x, ( uint32_t ) l_v2.y, p_request->content.line.color );
         }
      }

      /* Sinon, dessin d'une ligne sur l'axe vertical */
      else
      {
         /* Permutation des ordonnées pour dessin de haut en bas */
         if ( l_v1.y > l_v2.y )
         {
            /* Dessin de la ligne */
            l_result = mk_chromart_plotVertical ( p_request->content.line.layer, ( uint32_t ) l_v2.x, ( uint32_t ) l_v2.y, ( uint32_t ) l_v1.x, ( uint32_t ) l_v1.y, p_request->content.line.color );
         }

         /* Sinon */
         else
         {
            /* Dessin de la ligne */
            l_result = mk_chromart_plotVertical ( p_request->content.line.layer, ( uint32_t ) l_v1.x, ( uint32_t ) l_v1.y, ( uint32_t ) l_v2.x, ( uint32_t ) l_v2.y, p_request->content.line.color );
         }
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

