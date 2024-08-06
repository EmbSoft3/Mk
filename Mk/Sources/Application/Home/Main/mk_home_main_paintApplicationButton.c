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
* @file mk_home_main_paintApplicationButton.c
* @brief Définition de la fonction mk_home_main_paintApplicationButton.
* @date 5 nov. 2023
*
*/

#include "mk_home_api.h"
/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_main_drawString ( T_mkButtonImage* p_buttonImage, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs position */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Si un texte doit être dessiné */
   if ( p_buttonImage->text != K_MK_NULL )
   {
      /* Configuration de la position du texte */
      mk_vect2d_setCoord ( &l_topLeft, p_field->position.x, p_field->position.y + ( real32_t ) K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT );
      mk_vect2d_setCoord ( &l_bottomRight, p_field->position.x + ( real32_t ) p_field->dimension.width, p_field->position.y + ( real32_t ) p_field->dimension.height );

      /* Dessin du texte */
      l_result = mk_graphics_drawString ( p_buttonImage->field.layer, l_topLeft, l_bottomRight, p_buttonImage->text, p_buttonImage->style, K_MK_NULL );
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

T_mkCode mk_home_main_paintApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant une couleur */
   uint32_t l_color;

   /* Déclaration des vecteurs position */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Récupération de l'adresse du bouton image */
   T_mkButtonImage* l_buttonImage = p_field->child;

   /* Si une image a été configurée, on l'affiche */
   if ( ( l_buttonImage->bitmap != K_MK_NULL ) && ( l_buttonImage->bitmap->file != K_MK_NULL ) && ( l_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
   {
      /* Exécution de la fonction de peinture par défaut */
      l_result = mk_buttonImage_defaultTextPainter ( p_container, p_field, p_frameNumber );
   }

   /* Sinon (on affiche un petit rectangle) */
   else
   {
      /* Récupération de la couleur de la bordure */
      l_color = mk_color_getARGB32 ( &l_buttonImage->borderColor );

      /* Configuration de la position du rectangle */
      mk_vect2d_setCoord ( &l_topLeft, p_field->position.x + ( real32_t ) ( ( p_field->dimension.width - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH ) >> 1 ),
                                       p_field->position.y + ( real32_t ) ( ( p_field->dimension.height - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT - l_buttonImage->style->font->height ) >> 1 ) );
      mk_vect2d_setCoord ( &l_bottomRight, l_topLeft.x + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH, l_topLeft.y + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT );

      /* Dessin du rectangle */
      l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Affichage du nom de l'application */
         l_result = mk_home_main_drawString ( l_buttonImage, p_field );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result);
}


