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
* @file mk_graphics_drawString.c
* @brief Définition de la fonction mk_drawString.
* @date 20 avr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graphics_postStringRequest ( uint32_t p_layer, T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_str8 p_string, T_mkTextStyle* p_style, T_mkTextCursor* p_cursor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_CHROMART, { { K_MK_DISPLAY_REQUEST_CHROMART_STRING, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Configuration des attributs de la requête */
   mk_chromart_setString ( &l_request.content.chromart, p_string, p_style, p_cursor, p_layer );
   mk_chromart_setPlane ( &l_request.content.chromart.plane, ( uint32_t ) p_v1->x, ( uint32_t ) p_v1->y, ( uint32_t ) ( p_v2->x - p_v1->x ), ( uint32_t ) ( p_v2->y - p_v1->y ) );

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

T_mkCode mk_graphics_drawString ( uint32_t p_layer, T_mkVect2D p_v1, T_mkVect2D p_v2, T_str8 p_string, T_mkTextStyle* p_style, T_mkTextCursor* p_cursor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des vecteurs de travail */
   T_mkVect2Di l_v1, l_v2;
   T_mkVect2D  l_r1, l_r2;

   /* Déclaration d'une structure contenant le style par défaut de la chaine de caractères */
   T_mkTextStyle l_defaultStyle = {
        K_MK_NULL,
        K_MK_FONT_ASCII, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
        K_MK_GRAPHICS_DEFAULT_MARGIN_TOP, K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM,
        K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT, K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT,
        K_MK_GRAPHICS_DEFAULT_TEXT_COLOR
   };

   /* Déclaration d'un pointeur de style */
   T_mkTextStyle* l_style = p_style;

   /* Conversion des coordonnées du vecteur en entier */
   p_v1.x = mk_vect2d_shift ( p_v1.x );
   p_v1.y = mk_vect2d_shift ( p_v1.y );
   p_v2.x = mk_vect2d_shift ( p_v2.x );
   p_v2.y = mk_vect2d_shift ( p_v2.y );

   /* Conversion des vecteur v1 et v2 en flottant pour la vérification des paramètres */
   mk_vect2d_setCoord2Di ( &l_v1, ( uint32_t ) p_v1.x, ( uint32_t ) p_v1.y );
   mk_vect2d_setCoord2Di ( &l_v2, ( uint32_t ) p_v2.x, ( uint32_t ) p_v2.y );

   /* Si l'utilisateur a spécifié un style */
   if ( p_style == K_MK_NULL )
   {
      /* Configuration du style */
      l_style = ( T_mkTextStyle* ) &l_defaultStyle;
   }

   /* Sinon */
   else
   {
     /* Ne rien faire */
   }

   /* Modification des vecteurs en fonction des valeurs des marges */
   l_result = mk_display_utils_setMargin ( &l_v1, &l_v2, l_style );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Conversion des vecteur v1 et v2 en flottant pour la vérification des paramètres */
      mk_vect2d_setCoord ( &l_r1, ( real32_t ) l_v1.x, ( real32_t ) l_v1.y );
      mk_vect2d_setCoord ( &l_r2, ( real32_t ) l_v2.x, ( real32_t ) l_v2.y );

      /* Détermination de la validité des paramètres */
      /* Bypass du paramètre 3 */
      l_result = mk_graphics_checkVertex ( &l_r1, &l_r2, &l_r1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

      /* Si les paramètres sont conformes */
      if ( ( l_result == K_MK_OK ) && ( p_layer <= K_MK_GRAPHICS_BACKGROUND ) )
      {
         /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
         /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
         mk_vect2d_sort ( &p_v1, &p_v2 );

         /* Transmission de la requête */
         l_result = mk_graphics_postStringRequest ( p_layer, &p_v1, &p_v2, p_string, p_style, p_cursor );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
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


