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
* @file mk_graphics_drawPixel.c
* @brief Définition de la fonction mk_graphics_drawPixel.
* @date 23 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graphics_drawPixel ( uint32_t p_layer, T_mkVect2D p_v, uint32_t p_argb )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_FILL, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Conversion des coordonnées du vecteur en entier */
   p_v.x = mk_vect2d_shift ( p_v.x );
   p_v.y = mk_vect2d_shift ( p_v.y );

   /* Détermination de la validité des paramètres */
   /* Bypass des paramètres 2 et 3 */
   l_result = mk_graphics_checkVertex ( &p_v, &p_v, &p_v, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Configuration des attributs de la requête */
      mk_chromart_setFill ( &l_request.content.chromart, p_layer, ( uint32_t ) ( g_mkDisplay.screen.width - 1 ), p_argb );
      mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) p_v.x, ( uint32_t ) p_v.y, 1, 1 );

      /* Transmission de la requête */
      l_result = mk_display_postRequest ( &l_request );
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


