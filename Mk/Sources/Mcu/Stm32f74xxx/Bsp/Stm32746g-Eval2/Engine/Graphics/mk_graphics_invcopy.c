/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_graphics_invcopy.c
* @brief Définition de la fonction mk_graphics_invcopy.
* @date 29 juil. 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graphics_invcopy ( T_mkAddr p_addr, T_mkVect2D p_v, uint32_t p_direction, uint32_t p_layer, uint32_t p_width, uint32_t p_height )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_INVCOPY, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Déclaration d'un vecteur de travail */
   T_mkVect2D l_v = { 0, 0 };

   /* Conversion des coordonnées du vecteur v1 en entier */
   p_v.x = mk_vect2d_shift ( p_v.x );
   p_v.y = mk_vect2d_shift ( p_v.y );

   /* Détermination des coordonnées du vecteur BOTTOM_RIGHT */
   l_v.x = p_v.x + ( real32_t ) p_width - 1.0f;
   l_v.y = p_v.y + ( real32_t ) p_height - 1.0f;

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètres 3 */
   l_result = mk_graphics_checkVertex ( &p_v, &l_v, &p_v, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Si l'image doit être dessinée dans le format ARGB8888 */
      if ( g_mkDisplay.screen.bytesPerPixel [ p_layer ] == K_MK_DISPLAY_ARGB8888 )
      {
         /* Configuration des attributs de la requête */
         mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) ( p_v.x ), ( uint32_t ) ( p_v.y ), p_width, p_height );
         mk_chromart_setCopy ( &l_request.content.chromart, p_addr, 0, p_layer, ( uint32_t ) ( g_mkDisplay.screen.width - p_width ), p_direction | K_MK_GRAPHICS_ARGB8888 );
      }

      /* Sinon */
      else
      {
         /* Configuration des attributs de la requête */
         mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) ( p_v.x ), ( uint32_t ) ( p_v.y ), p_width, p_height );
         mk_chromart_setCopy ( &l_request.content.chromart, p_addr, 0, p_layer, ( uint32_t ) ( g_mkDisplay.screen.width - p_width ), p_direction | K_MK_GRAPHICS_RGB888 );
      }

      /* Transmission de la requête */
      l_result = mk_display_postRequest ( &l_request );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

