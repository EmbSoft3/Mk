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
* @file mk_graphics_drawRect.c
* @brief Définition de la fonction mk_graphics_drawRect.
* @date 25 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graphics_drawSolidRect ( uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_width, uint32_t p_height, uint32_t p_argb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_FILL, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Configuration des attributs de la requête */
   mk_chromart_setFill ( &l_request.content.chromart, p_layer, ( uint32_t ) ( g_mkDisplay.screen.width - p_width ), p_argb );
   mk_chromart_setPlane ( &l_request.content.chromart.plane, p_x, p_y, p_width, p_height );

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

static T_mkCode mk_graphics_drawEmptyRect ( uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_width, uint32_t p_height, uint32_t p_argb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Dessin des segments du rectangle */
   l_result  = mk_graphics_drawSolidRect ( p_layer, p_x, p_y, p_width, 1, p_argb );
   l_result |= mk_graphics_drawSolidRect ( p_layer, p_x, p_y, 1, p_height, p_argb );
   l_result |= mk_graphics_drawSolidRect ( p_layer, p_x, p_y + p_height - 1, p_width, 1, p_argb );
   l_result |= mk_graphics_drawSolidRect ( p_layer, p_x + p_width - 1, p_y, 1, p_height, p_argb );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graphics_drawRect ( uint32_t p_layer, uint32_t p_state, T_mkVect2D p_v1, T_mkVect2D p_v2, uint32_t p_argb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un couple largeur hauteur */
   real32_t l_width;
   real32_t l_height;

   /* Conversion des coordonnées du vecteur v1 en entier */
   p_v1.x = mk_vect2d_shift ( p_v1.x );
   p_v1.y = mk_vect2d_shift ( p_v1.y );

   /* Conversion des coordonnées du vecteur v2 en entier */
   p_v2.x = mk_vect2d_shift ( p_v2.x );
   p_v2.y = mk_vect2d_shift ( p_v2.y );

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &p_v1, &p_v2, &p_v1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Détermination de la valeur du couple largeur - hauteur */
      l_width  = _math_vabs ( p_v1.x - p_v2.x ) + 1.0f;
      l_height = _math_vabs ( p_v1.y - p_v2.y ) + 1.0f;

      /* Si les dimensions sont non nulles */
      if ( ( l_width > 0.0f ) && ( l_height > 0.0f ) )
      {
         /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
         /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
         mk_vect2d_sort ( &p_v1, &p_v2 );

         /* Si un rectangle plein doit être dessiné */
         if ( p_state == K_MK_GRAPHICS_SOLID )
         {
            /* Dessin d'un rectangle rempli */
            l_result = mk_graphics_drawSolidRect ( p_layer, ( uint32_t ) p_v1.x, ( uint32_t ) p_v1.y, ( uint32_t ) ( l_width ), ( uint32_t ) ( l_height ), p_argb );
         }

         /* Sinon */
         else
         {
            /* Dessin d'un rectangle vide */
            l_result = mk_graphics_drawEmptyRect ( p_layer, ( uint32_t ) p_v1.x, ( uint32_t ) p_v1.y, ( uint32_t ) ( l_width ), ( uint32_t ) ( l_height ), p_argb );
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



