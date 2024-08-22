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
* @file mk_chromart_drawTriangle.c
* @brief Définition de la fonction mk_chromart_drawTriangle.
* @date 2 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_chromart_sortVectX ( T_mkVect2D** p_v1, T_mkVect2D** p_v2 )
{
   /* Déclaration d'un vecteur temporaire */
   T_mkVect2D* l_tmp = *p_v1;

   /* Si une permutation doit être effectuée */
   if ( ( *p_v2 )->x < ( *p_v1 )->x )
   {
      *p_v1 = *p_v2;
      *p_v2 =  l_tmp;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_chromart_sortVectY ( T_mkVect2D** p_v1, T_mkVect2D** p_v2 )
{
   /* Déclaration d'un vecteur temporaire */
   T_mkVect2D* l_tmp = *p_v1;

   /* Si une permutation doit être effectuée */
   if ( ( *p_v2 )->y < ( *p_v1 )->y )
   {
      *p_v1 = *p_v2;
      *p_v2 =  l_tmp;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_drawPixelTriangle ( T_mkChromartPlane* p_plane, uint32_t p_layer, uint32_t p_offset, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail*/
   uint32_t l_bytesPerPixel, l_addr, *l_pnt;

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_layer ];

   /* Détermination de l'adresse de base */
   l_addr =  ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_layer ]
         + l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) p_plane->y ) + ( uint32_t ) p_plane->x );

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

static T_mkCode mk_chromart_drawFlatTopTriangle ( uint32_t p_layer, T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_mkVect2D* p_v3, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un plan */
   T_mkChromartPlane l_plane;

   /* Déclaration d'un parser de dessin de Triangle */
   T_mkTriangleParser l_parser;

   /* Détermination des coeficients directeurs des droites */
   l_parser.slope1 = ( p_v3->x - p_v1->x ) / ( p_v3->y - p_v1->y );
   l_parser.slope2 = ( p_v3->x - p_v2->x ) / ( p_v3->y - p_v2->y );

   /* Determination des ordonnées de début et de fin */
   l_parser.ystart = _math_ceil ( p_v1->y - 0.5f );
   l_parser.yend   = _math_ceil ( p_v3->y - 0.5f );

   /* Pour chaque ligne à dessiner */
   for ( l_parser.counter = l_parser.ystart ; l_parser.counter < l_parser.yend ; l_parser.counter++ )
   {
      /* Détermination des positions réelles des abscisses */
      /* La valeur 0.5 est ajoutée à la composante y parce que l'origine est située au milieu du pixel */
      l_parser.x1 = l_parser.slope1 * ( ( real32_t ) l_parser.counter + 0.5f - p_v1->y ) + p_v1->x ;
      l_parser.x2 = l_parser.slope2 * ( ( real32_t ) l_parser.counter + 0.5f - p_v2->y ) + p_v2->x ;

      /* Détermination des positions entières */
      l_parser.xstart = _math_ceil ( l_parser.x1 - 0.5f );
      l_parser.xend   = _math_ceil ( l_parser.x2 - 0.5f );

      /* Détermination de la distance entre xstart et xend */
      l_parser.width = ( int32_t ) _math_abs ( l_parser.xend - l_parser.xstart );

      /* Si une ligne doit être dessinée */
      if ( l_parser.width != 0 )
      {
         /* Configuration du plan */
         mk_chromart_setPlane ( &l_plane, ( uint32_t ) l_parser.xstart, ( uint32_t ) l_parser.counter, ( uint32_t ) l_parser.width, 1 );

         /* Dessin de la ligne */
         l_result = mk_chromart_drawPixelTriangle ( &l_plane, p_layer, 0, p_argb );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_drawFlatBottomTriangle ( uint32_t p_layer, T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_mkVect2D* p_v3, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un plan */
   T_mkChromartPlane l_plane;

   /* Déclaration d'un parser de dessin de Triangle */
   T_mkTriangleParser l_parser;

   /* Détermination de la pente des droites (inverse) */
   l_parser.slope1 = ( p_v2->x - p_v1->x ) / ( p_v2->y - p_v1->y );
   l_parser.slope2 = ( p_v3->x - p_v1->x ) / ( p_v3->y - p_v1->y );

   /* Determination des ordonnées de début et de fin */
   l_parser.ystart = _math_ceil ( p_v1->y - 0.5f );
   l_parser.yend   = _math_ceil ( p_v3->y - 0.5f );

   /* Pour chaque ligne à dessiner */
   for ( l_parser.counter = l_parser.ystart ; l_parser.counter < l_parser.yend ; l_parser.counter++ )
   {
      /* Détermination des positions réelles des abscisses */
      /* La valeur 0.5 est ajoutée à la composante y parce que l'origine est située au milieu du pixel */
      l_parser.x1 = l_parser.slope1 * ( ( real32_t ) l_parser.counter + 0.5f - p_v1->y ) + p_v1->x ;
      l_parser.x2 = l_parser.slope2 * ( ( real32_t ) l_parser.counter + 0.5f - p_v1->y ) + p_v1->x ;

      /* Détermination des positions entières */
      l_parser.xstart = _math_ceil ( l_parser.x1 - 0.5f );
      l_parser.xend   = _math_ceil ( l_parser.x2 - 0.5f );

      /* Détermination de la distance entre xstart et xend */
      l_parser.width = ( int32_t ) _math_abs ( l_parser.xend - l_parser.xstart );

      /* Si une ligne doit être dessinée */
      if ( l_parser.width != 0 )
      {
         /* Configuration du plan */
         mk_chromart_setPlane ( &l_plane, ( uint32_t ) l_parser.xstart, ( uint32_t ) l_parser.counter, ( uint32_t ) l_parser.width, 1 );

         /* Dessin de la ligne */
         l_result = mk_chromart_drawPixelTriangle ( &l_plane, p_layer, 0, p_argb );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_drawSolidFlatTriangle ( uint32_t p_layer, T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_mkVect2D* p_v3, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration du rapport alpha */
   real32_t l_alpha;

   /* Déclaration des pointeurs de vecteurs */
   T_mkVect2D* l_v1 = p_v1;
   T_mkVect2D* l_v2 = p_v2;
   T_mkVect2D* l_v3 = p_v3;

   /* Déclaration du vecteur median */
   T_mkVect2D  l_vi;

   /* Tri des vertices en utilisant la composante Y : Y1 => TOP, Y3 => BOTTOM */
   mk_chromart_sortVectY ( &l_v1, &l_v2 );
   mk_chromart_sortVectY ( &l_v2, &l_v3 );
   mk_chromart_sortVectY ( &l_v1, &l_v2 );

   /* Si uniquement le triangle du haut doit être dessiné */
   if ( ( int32_t ) l_v1->y == ( int32_t ) l_v2->y )
   {
      /* Permutation des vertices en utilisant la composante X */
      mk_chromart_sortVectX ( &l_v1, &l_v2 );

      /* Dessin du triangle */
      l_result = mk_chromart_drawFlatTopTriangle ( p_layer, l_v1, l_v2, l_v3, p_argb );
   }

   /* Sinon si uniquement le triangle du bas doit être dessiné */
   else if ( ( int32_t ) l_v2->y == ( int32_t ) l_v3->y )
   {
      /* Permutation des vertices en utilisant la composante X */
      mk_chromart_sortVectX ( &l_v2, &l_v3 );

      /* Dessin du triangle */
      l_result = mk_chromart_drawFlatBottomTriangle ( p_layer, l_v1, l_v2, l_v3, p_argb );
   }

   /* Sinon, triangle quelconque */
   else
   {
      /* Détermination du rapport alpha */
      l_alpha = ( l_v2->y - l_v1->y ) / ( l_v3->y - l_v1->y );

      /* Détermination du vecteur { l_xi, l_yi } */
      l_vi.x = ( l_v1->x + ( l_v3->x - l_v1->x ) * l_alpha );
      l_vi.y = ( l_v1->y + ( l_v3->y - l_v1->y ) * l_alpha );

      /* Si un tiangle doit être dessiné à droite */
      if ( l_v2->x < l_vi.x )
      {
         /* Dessin des triangles */
         l_result  = mk_chromart_drawFlatBottomTriangle ( p_layer, l_v1, l_v2, &l_vi, p_argb );
         l_result |= mk_chromart_drawFlatTopTriangle    ( p_layer, l_v2, &l_vi, l_v3, p_argb );
      }

      /* Sinon */
      else
      {
         /* Dessin des triangles */
         l_result |= mk_chromart_drawFlatBottomTriangle ( p_layer, l_v1, &l_vi, l_v2, p_argb );
         l_result |= mk_chromart_drawFlatTopTriangle    ( p_layer, &l_vi, l_v2, l_v3, p_argb );
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_chromart_drawTriangle ( T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration de trois vecteurs */
   T_mkVect2D l_v1;
   T_mkVect2D l_v2;
   T_mkVect2D l_v3;

   /* Initialisation du premier vecteurs */
   l_v1.x = ( real32_t ) p_request->plane.x;
   l_v1.y = ( real32_t ) p_request->plane.y;

   /* Initialisation du deuxième vecteurs */
   l_v2.x = ( real32_t ) p_request->plane.width;
   l_v2.y = ( real32_t ) p_request->plane.height;

   /* Initialisation du troisième vecteurs */
   l_v3.x = ( real32_t ) p_request->content.triangle.x;
   l_v3.y = ( real32_t ) p_request->content.triangle.y;

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &l_v1, &l_v2, &l_v3, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_request->content.triangle.layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Dessin d'un triangle plein */
      l_result = mk_chromart_drawSolidFlatTriangle ( p_request->content.triangle.layer, &l_v1, &l_v2, &l_v3, p_request->content.triangle.color );
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




