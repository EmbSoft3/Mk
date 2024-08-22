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
* @file mk_editField_setAttribute.c
* @brief Définition de la fonction mk_editField_setAttribute.
* @date 7 févr. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_editField_setAttribute ( T_mkEditField* p_editField, T_mkVect2D p_v1, T_mkVect2D p_v2, T_mkVect2Di* p_topLeft, T_mkVect2Di* p_downRight, T_str8 p_windowBaseAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration de deux couples de coordonnées */
   T_mkVect2Di l_v1, l_v2;

   /* Conversion des coordonnées du vecteur en entier */
   p_v1.x = mk_vect2d_shift ( p_v1.x );
   p_v1.y = mk_vect2d_shift ( p_v1.y );
   p_v2.x = mk_vect2d_shift ( p_v2.x );
   p_v2.y = mk_vect2d_shift ( p_v2.y );

   /* Détermination de la validité des paramètres */
   /* Bypass du paramètre 3 */
   l_result = mk_graphics_checkVertex ( &p_v1, &p_v2, &p_v1, ( real32_t ) ( g_mkDisplay.screen.width + 1 ), ( real32_t ) ( g_mkDisplay.screen.height + 1 ) );

   /* Si les coordonnées sont valides */
   if ( l_result == K_MK_OK )
   {
      /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
      /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
      mk_vect2d_sort ( &p_v1, &p_v2 );

      /* Configuration des couples de coordonnées */
      l_v1.x = ( uint32_t ) p_v1.x;
      l_v1.y = ( uint32_t ) p_v1.y;
      l_v2.x = ( uint32_t ) p_v2.x;
      l_v2.y = ( uint32_t ) p_v2.y;

      /* Modification des vecteurs de coordonnées selon les valeurs de marge */
      l_result = mk_display_utils_setMargin ( &l_v1, &l_v2, &p_editField->style );

      /* Si les paramètres sont valides */
      if ( l_result == K_MK_OK )
      {
         /* Récupération de la taille de la fenêtre de dessin */
         p_editField->windowNumberOfRow = mk_display_utils_getWindowMaxNumberOfLines ( &p_editField->style, ( uint32_t ) ( l_v2.y - l_v1.y ) );

         /* Récupération du nombre de lignes à dessiner en fonction de la taille de la fenêtre */
         p_editField->windowCurrentNumberOfRow =
               mk_display_utils_getWindowCurrentNumberOfLines ( p_editField->style.font, p_windowBaseAddr, p_editField->windowNumberOfRow, ( uint32_t ) p_editField->style.fontEncoding, ( uint32_t ) ( l_v2.x - l_v1.x ) );

         /* Détermination des coordonnées des vecteurs position TOP_LEFT et BOTTOM_RIGHT */
         mk_vect2d_setCoord2Di ( p_topLeft, l_v1.x, l_v1.y );
         mk_vect2d_setCoord2Di ( p_downRight, l_v2.x, l_v2.y );
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


