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
* @file mk_graphics_drawRoundRect.c
* @brief Définition de la fonction mk_graphics_drawRoundRect.
* @date 4 avr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graphics_checkRadius ( real32_t p_width, real32_t p_height, real32_t p_radius )
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

static T_mkCode mk_graphics_postRoundRectRequest ( T_mkPlane2Di* p_plane, uint32_t p_layer, real32_t p_radius, uint32_t p_state, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_ROUNDRECT, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Configuration des attributs de la requête */
   mk_chromart_setPlane ( &l_request.content.chromart.plane, p_plane->x, p_plane->y, p_plane->width, p_plane->height );
   mk_chromart_setRoundRect ( &l_request.content.chromart, p_layer, p_state, ( uint32_t ) p_radius, p_argb );

   /* Transmission de la requête */
   l_result = mk_display_postRequest ( &l_request );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graphics_drawRoundRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v1, T_mkVect2D p_v2, real32_t p_radius, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un plan */
   T_mkPlane2Di l_plane;

   /* Déclaration d'un couple largeur hauteur */
   real32_t l_width;
   real32_t l_height;

   /* Conversion des coordonnées du vecteur v1 en entier */
   p_v1.x = mk_vect2d_shift ( p_v1.x );
   p_v1.y = mk_vect2d_shift ( p_v1.y );

   /* Conversion des coordonnées du vecteur v2 en entier */
   p_v2.x = mk_vect2d_shift ( p_v2.x );
   p_v2.y = mk_vect2d_shift ( p_v2.y );

   /* Conversion du rayon en entier */
   p_radius = mk_vect2d_shift ( p_radius );

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &p_v1, &p_v2, &p_v1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Détermination de la valeur du couple largeur - hauteur */
      l_width  = _math_vabs ( p_v1.x - p_v2.x ) + 1;
      l_height = _math_vabs ( p_v1.y - p_v2.y ) + 1;

      /* Détermination de la validité du paramètre rayon */
      l_result = mk_graphics_checkRadius ( l_width, l_height, p_radius );

      /* Si les dimensions sont non nulles */
      if ( l_result == K_MK_OK )
      {
         /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
         /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
         mk_vect2d_sort ( &p_v1, &p_v2 );

         /* Configuration de l'origine du plan */
         l_plane.x = ( uint32_t ) p_v1.x;
         l_plane.y = ( uint32_t ) p_v1.y;

         /* Configuration des dimensions du plan */
         l_plane.width = ( uint32_t ) l_width;
         l_plane.height = ( uint32_t ) l_height;

         /* Transmission de la requête */
         l_result = mk_graphics_postRoundRectRequest ( &l_plane, p_layer, p_radius, p_state, p_argb );
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


