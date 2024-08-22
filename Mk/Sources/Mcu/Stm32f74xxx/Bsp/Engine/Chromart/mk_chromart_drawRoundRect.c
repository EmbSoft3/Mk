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
* @file mk_chromart_drawRoundRect.c
* @brief Définition de la fonction mk_chromart_drawRoundRect.
* @date 2 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_checkRadius ( real32_t p_width, real32_t p_height, real32_t p_radius )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = K_MK_OK;

   /* Détermination du diamètre du cercle */
   real32_t l_diameter = 2.0f * p_radius;

   /* Si le cercle ne peut pas être compris dans le rectangle */
   if ( ( p_width < l_diameter ) || ( p_height < l_diameter ) || ( p_width <= 0.0f ) || ( p_height <= 0.0f) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
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

static T_mkCode mk_chromart_drawPixelRoundRect ( T_mkChromartPlane* p_plane, uint32_t p_layer, uint32_t p_offset, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail*/
   uint32_t l_bytesPerPixel, l_addr, *l_pnt;

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_layer ];

   /* Détermination de l'adresse de base */
   l_addr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_layer ] +
         l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) p_plane->y ) + ( uint32_t ) p_plane->x );

   /* Si un seul pixel doit être dessiné */
   if ( ( p_plane->width == 1 ) && ( p_plane->height == 1 ) )
   {
      /* Récupération de l'adresse du pixel */
      l_pnt = ( uint32_t* ) l_addr;

      /* Ecriture du pixel directement dans la mémoire graphique */
      if ( l_bytesPerPixel == K_MK_DISPLAY_RGB888 )
      {
         _copy ( l_pnt, &p_argb, 3 );
      }

      /* Sinon */
      else
      {
         *l_pnt = p_argb;
      }
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

static T_mkCode mk_chromart_drawSolidRoundRect ( uint32_t p_layer, T_mkPlane2Di* p_plane, uint32_t p_radius, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un parser permettant de réaliser l'algorithme de tracer de cercle d'Andres */
   T_mkAndresParser l_parser;

   /* Déclaration des plans */
   T_mkChromartPlane l_plane1, l_plane2, l_plane3, l_plane4;

   /* Déclaration d'une variable de travail */
   uint32_t l_height;

   /* Configuration des conditions initiales de l'algorithme */
   mk_parser_initSolidRoundRectAndres ( &l_parser, p_radius, p_plane->width );
   mk_parser_initRoundRectCircleAndres ( &l_parser, p_radius, p_plane->x, p_plane->y, p_plane->height );

   /* Tant que le cercle n'est pas entièrement dessiné */
   while ( ( l_parser.y >= l_parser.x ) && ( l_result == K_MK_OK ) )
   {
      /* Configuration des plans */
      mk_chromart_setPlane ( &l_plane1, l_parser.cx - l_parser.x, l_parser.cy - l_parser.y, l_parser.dx, 1 );
      mk_chromart_setPlane ( &l_plane2, l_parser.cx - l_parser.x, l_parser.by + l_parser.y, l_parser.dx, 1 );
      mk_chromart_setPlane ( &l_plane3, l_parser.cx - l_parser.y, l_parser.cy - l_parser.x, l_parser.dy, 1 );
      mk_chromart_setPlane ( &l_plane4, l_parser.cx - l_parser.y, l_parser.by + l_parser.x, l_parser.dy, 1 );

      /* Dessin des segments supérieurs et inférieurs de la figure */
      l_result  = mk_chromart_drawPixelRoundRect ( &l_plane1, p_layer, 1, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane2, p_layer, 1, p_argb );

      /* Dessin des segments centraux de la figure */
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane3, p_layer, 1, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane4, p_layer, 1, p_argb );

      /* Actualisation des données de l'algorithme */
      mk_parser_refreshSolidRoundRectAndres ( &l_parser, p_radius, p_plane->width );
   }

   /* Actualisation de la nouvelle hauteur */
   /* Il est nécessaire de retrancher deux rayons. */
   l_height = p_plane->height - ( p_radius << 1 );

   /* Si la hauteur du rectangle est non nulle */
   if ( l_height != 0 )
   {
      /* Configuration du plan */
       mk_chromart_setPlane ( &l_plane1, p_plane->x, l_parser.cy, p_plane->width, l_height );

      /* Dessin du rectangle central */
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane1, p_layer, g_mkDisplay.screen.width - p_plane->width, p_argb );
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

static T_mkCode mk_chromart_drawEmptyRoundRect ( uint32_t p_layer, T_mkPlane2Di* p_plane, uint32_t p_radius, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un parser permettant de réaliser l'algorithme de tracer de cercle d'Andres */
   T_mkAndresParser l_parser;

   /* Déclaration des plans */
   T_mkChromartPlane l_plane1, l_plane2, l_plane3, l_plane4;

   /* Déclaration des variables de travail */
   uint32_t l_width, l_height;

   /* Configuration des conditions initiales de l'algorithme */
   mk_parser_initEmptyRoundRectAndres ( &l_parser, p_radius, p_plane->width );
   mk_parser_initRoundRectCircleAndres ( &l_parser, p_radius, p_plane->x, p_plane->y, p_plane->height );

   /* Tant que le cercle n'est pas entièrement dessiné */
   while ( ( l_parser.y >= l_parser.x ) && ( l_result == K_MK_OK ) )
   {
      /* Configuration des plans */
      mk_chromart_setPlane ( &l_plane1, l_parser.cx - l_parser.x, l_parser.cy - l_parser.y, 1, 2 );
      mk_chromart_setPlane ( &l_plane2, l_parser.cx - l_parser.x, l_parser.by + l_parser.y, 1, 2 );
      mk_chromart_setPlane ( &l_plane3, l_parser.cx - l_parser.y, l_parser.cy - l_parser.x, 1, 2 );
      mk_chromart_setPlane ( &l_plane4, l_parser.cx - l_parser.y, l_parser.by + l_parser.x, 1, 2 );

      /* Dessin des segments supérieurs et inférieurs de la figure */
      l_result  = mk_chromart_drawPixelRoundRect ( &l_plane1, p_layer, l_parser.dx, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane2, p_layer, l_parser.dx, p_argb );

      /* Dessin des segments centraux de la figure */
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane3, p_layer, l_parser.dy, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane4, p_layer, l_parser.dy, p_argb );

      /* Actualisation des données de l'algorithme */
      mk_parser_refreshEmptyRoundRectAndres ( &l_parser, p_radius, p_plane->width );
   }

   /* Actualisation de la nouvelle hauteur et de la nouvelle largeur */
   /* Il est nécessaire de retrancher deux rayons. */
   l_width =  p_plane->width  - ( p_radius << 1 );
   l_height = p_plane->height - ( p_radius << 1 );

   /* Si la hauteur du rectangle est non nulle */
   if ( l_height != 0 )
   {
      /* Configuration des plans */
      mk_chromart_setPlane ( &l_plane3, p_plane->x, l_parser.cy, 1, l_height );
      mk_chromart_setPlane ( &l_plane4, p_plane->x + p_plane->width - 1, l_parser.cy, 1, l_height );

      /* Dessin des lignes verticales droite et gauche */
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane3, p_layer, g_mkDisplay.screen.width - 1, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane4, p_layer, g_mkDisplay.screen.width - 1, p_argb );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si la hauteur du rectangle est non nulle */
   if ( l_width != 0 )
   {
      /* Configuration des plans */
      mk_chromart_setPlane ( &l_plane1, l_parser.cx, p_plane->y, l_width, 1 );
      mk_chromart_setPlane ( &l_plane2, l_parser.cx, p_plane->y + p_plane->height - 1, l_width, 1 );

      /* Dessin des lignes horizontales supérieure et inférieure */
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane1, p_layer, 0, p_argb );
      l_result |= mk_chromart_drawPixelRoundRect ( &l_plane2, p_layer, 0, p_argb );
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

T_mkCode mk_chromart_drawRoundRect ( T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des vecteurs de travail */
   T_mkVect2D l_v1, l_v2;

   /* Déclaration d'un plan */
   T_mkPlane2Di l_plane;

   /* Configuration des couples de coordonnées */
   mk_vect2d_setCoord ( &l_v1, ( real32_t ) p_request->plane.x, ( real32_t ) p_request->plane.y );
   mk_vect2d_setCoord ( &l_v2, ( real32_t ) ( p_request->plane.x + p_request->plane.width - 1 ), ( real32_t ) ( p_request->plane.y + p_request->plane.height - 1 ) );

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &l_v1, &l_v2, &l_v1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_request->content.roundRect.layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Détermination de la validité du paramètre rayon */
      l_result = mk_chromart_checkRadius ( ( real32_t ) p_request->plane.width, ( real32_t ) p_request->plane.height, ( real32_t ) p_request->content.roundRect.radius );

      /* Si le paramètre est valide */
      if ( l_result == K_MK_OK )
      {
         /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
         /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
         mk_vect2d_sort ( &l_v1, &l_v2 );

         /* Configuration de l'origine du plan */
         l_plane.x = ( uint32_t ) l_v1.x;
         l_plane.y = ( uint32_t ) l_v1.y;

         /* Configuration des dimensions du plan */
         l_plane.width = ( uint32_t ) p_request->plane.width;
         l_plane.height = ( uint32_t ) p_request->plane.height;

         /* Si figure pleine */
         if ( p_request->content.roundRect.state == K_MK_GRAPHICS_SOLID )
         {
            /* Dessin d'une figure pleine */
            l_result = mk_chromart_drawSolidRoundRect ( p_request->content.roundRect.layer, &l_plane, ( uint32_t ) p_request->content.roundRect.radius, p_request->content.roundRect.color );
         }

         /* Sinon */
         else
         {
            /* Dessin d'une figure vide */
            l_result = mk_chromart_drawEmptyRoundRect ( p_request->content.roundRect.layer, &l_plane, ( uint32_t ) p_request->content.roundRect.radius, p_request->content.roundRect.color );
         }
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



