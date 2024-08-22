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
* @file mk_buttonImage_defaultPainter.c
* @brief Définition de la fonction mk_buttonImage_defaultPainter.
* @date 10 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_buttonImage_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant un vecteur */
   T_mkVect2D l_vect;

   /* Déclaration d'une variable stockant une couleur */
   uint32_t l_color;

   /* Récupération de l'adresse du bouton */
   T_mkButtonImage* l_buttonImage = p_field->child;

   /* Suppression warning */
   ( void ) p_container, ( void ) p_frameNumber;

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Si les paramètres sont valides */
      if ( ( l_buttonImage->bitmap != K_MK_NULL ) && ( l_buttonImage->bitmap->file != K_MK_NULL ) && ( l_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
      {
         /* Dessin du bitmap */
         l_result = mk_bmp_draw ( l_buttonImage->bitmap, l_buttonImage->field.layer, p_field->position );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une bordure doit être dessinée */
      if ( l_buttonImage->borderVisibility == K_MK_GRAPHICS_VISIBLE )
      {
         /* Configuration du vecteur */
         mk_vect2d_setCoord ( &l_vect, p_field->position.x + ( real32_t ) p_field->dimension.width, p_field->position.y + ( real32_t ) p_field->dimension.height );

         /* Récupération de la valeur de la couleur */
         l_color = mk_color_getARGB32 ( &l_buttonImage->borderColor );

         /* Dessin de la bordure */
         l_result = mk_graphics_drawRoundRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, p_field->position, l_vect, 5, l_color );
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




