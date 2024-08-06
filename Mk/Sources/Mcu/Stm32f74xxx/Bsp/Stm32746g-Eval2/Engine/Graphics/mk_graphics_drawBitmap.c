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
* @file mk_graphics_drawBitmap.c
* @brief Définition de la fonction mk_graphics_drawBitmap.
* @date 4 déc. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graphics_drawBitmap ( uint32_t p_layer, uint32_t* p_bitmap, T_mkVect2D p_v1, uint32_t p_column, uint32_t p_row )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables stockant la largeur et la hauteur du bitmap */
   uint32_t l_width, l_height;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_BLEND, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Détermination de l'adresse de base du buffer utilisé pour le blending */
   uint32_t* l_addr = ( uint32_t* ) g_mkDisplay.pnt.currentBufferUsed->addr [ p_layer ];

   /* Conversion des coordonnées du vecteur v1 en entier */
   p_v1.x = mk_vect2d_shift ( p_v1.x );
   p_v1.y = mk_vect2d_shift ( p_v1.y );

   /* Détermination de la validité des paramètres */
   /* Bypass des paramètres 2 et 3 */
   l_result = mk_graphics_checkVertex ( &p_v1, &p_v1, &p_v1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

   /* Si les paramètres sont conformes */
   if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
   {
      /* Si les dimensions sont non nulles */
      if ( ( p_column > 0 ) && ( p_row > 0 ) )
      {
         /* Détermination des différentiels */
         l_width = g_mkDisplay.screen.width - ( uint32_t ) p_v1.x;
         l_height = g_mkDisplay.screen.height - ( uint32_t ) p_v1.y;

         /* Si la largeur du bitmap ne doit pas être modulée */
         if ( l_width > p_column )
         {
            /* Actualisation de la largeur du bitmap */
            l_width = p_column;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si la hauteur du bitmap ne doit pas être modulée */
         if ( l_height > p_row )
         {
            /* Actualisation de la largeur du bitmap */
            l_height = p_row;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de l'adresse */
         l_addr = l_addr + ( ( uint32_t ) ( ( uint32_t ) p_v1.y * g_mkDisplay.screen.width ) + ( uint32_t ) p_v1.x );

         /* Configuration de la requête */
         mk_chromart_setBlend ( &l_request.content.chromart, p_bitmap, l_addr, p_layer );
         mk_chromart_setBlendOffset ( &l_request.content.chromart, p_column - l_width, g_mkDisplay.screen.width - l_width, g_mkDisplay.screen.width - l_width );
         mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) p_v1.x, ( uint32_t ) p_v1.y, l_width, l_height );

         /* Dessin du bitmap à partir de l'adresse source */
         /* Un blending est utilisé afin d'éviter le phénoméne de recouvrement sur le plan */
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
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



