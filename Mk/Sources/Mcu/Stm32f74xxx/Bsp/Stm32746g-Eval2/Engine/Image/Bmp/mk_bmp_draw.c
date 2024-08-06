/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_bmp_draw.c
* @brief Définition de la fonction mk_bmp_draw.
* @date 26 mai 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_bmp_draw ( T_mkBMPFile* p_bitmap, uint32_t p_layer, T_mkVect2D p_v )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de traveil */
   T_mkVect2D l_pixel;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_COPY, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Si les paramètres sont valides */
   if ( ( p_bitmap != K_MK_NULL ) && ( p_bitmap->file != K_MK_NULL ) && ( p_bitmap->baseAddr != K_MK_NULL ) )
   {
      /* Conversion des coordonnées du vecteur en entier */
      p_v.x = mk_vect2d_shift ( p_v.x );
      p_v.y = mk_vect2d_shift ( p_v.y );

      /* Détermination des coordonnées de fin de l'image */
      l_pixel.x = p_v.x + ( real32_t ) p_bitmap->width;
      l_pixel.y = p_v.y + ( real32_t ) p_bitmap->height;

      /* Vérification de la compatibilité des dimensions de l'image avec l'écran */
      l_result = mk_graphics_checkVertex ( &p_v, &l_pixel, &p_v, ( real32_t ) ( g_mkDisplay.screen.width + 1 ), ( real32_t ) ( g_mkDisplay.screen.height + 1 ) );

      /* Si l'image peut être affichée */
      if ( l_result == K_MK_OK )
      {
         /* Si l'image doit être dessinée dans le format ARGB8888 */
         if ( g_mkDisplay.screen.bytesPerPixel [ p_layer ] == K_MK_DISPLAY_ARGB8888 )
         {
            /* Configuration des attributs de la requête */
            mk_chromart_setCopy ( &l_request.content.chromart, p_bitmap->baseAddr, 0, p_layer, ( g_mkDisplay.screen.width - p_bitmap->width ), K_MK_GRAPHICS_ADDR_TO_FRAME | K_MK_GRAPHICS_ARGB8888 );
            mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) ( p_v.x ), ( uint32_t ) ( p_v.y ), p_bitmap->width, p_bitmap->height );
         }

         /* Sinon */
         else
         {
            /* Configuration des attributs de la requête */
            mk_chromart_setCopy ( &l_request.content.chromart, p_bitmap->baseAddr, 0, p_layer, ( g_mkDisplay.screen.width - p_bitmap->width ), K_MK_GRAPHICS_ADDR_TO_FRAME | K_MK_GRAPHICS_RGB888 );
            mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) ( p_v.x ), ( uint32_t ) ( p_v.y ), p_bitmap->width, p_bitmap->height );
         }

         /* Dessin du bitmap */
         l_result = mk_display_postRequest ( &l_request );
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


