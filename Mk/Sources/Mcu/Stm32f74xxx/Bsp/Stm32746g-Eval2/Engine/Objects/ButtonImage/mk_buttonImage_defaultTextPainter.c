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
* @file mk_buttonImage_defaultTextPainter.c
* @brief Définition de la fonction mk_buttonImage_defaultTextPainter.
* @date 21 sept. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_buttonImage_drawImage ( T_mkButtonImage* p_buttonImage, T_mkField* p_field, T_mkFont* p_font )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un vecteur de travail */
   T_mkVect2D l_topLeft;

   /* Si la taille du bitmap est inférieure ou égale à la taille du champ */
   if ( ( p_buttonImage->bitmap->width <= p_field->dimension.width ) &&
        ( p_buttonImage->bitmap->height <= ( p_field->dimension.height - p_font->height ) ) )
   {
      /* Configuration du vecteur TopLeft */
      mk_vect2d_setCoord ( &l_topLeft, p_field->position.x + ( real32_t ) ( ( p_field->dimension.width - p_buttonImage->bitmap->width ) >> 1 ),
                                       p_field->position.y + ( real32_t ) ( ( p_field->dimension.height - p_buttonImage->bitmap->height - p_font->height ) >> 1 ) );

      /* Dessin du bitmap */
      l_result = mk_bmp_draw ( p_buttonImage->bitmap, p_buttonImage->field.layer, l_topLeft );
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

static T_mkCode mk_buttonImage_drawDefaultRect ( T_mkButtonImage* p_buttonImage, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant une couleur */
   uint32_t l_color;

   /* Déclaration des vecteurs TopLeft et BottomRight */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Récupération de la valeur de la couleur */
   l_color = mk_color_getARGB32 ( &p_buttonImage->borderColor );

   /* Configuration du vecteur TopLeft */
   mk_vect2d_setCoord ( &l_topLeft, p_field->position.x + ( real32_t ) ( p_field->dimension.width / 10 ),
                                    p_field->position.y + ( real32_t ) ( p_field->dimension.height / 10 ) );

   /* Configuration du vecteur BottomLeft */
   mk_vect2d_setCoord ( &l_bottomRight, p_field->position.x + ( real32_t ) ( 9 * p_field->dimension.width / 10 ),
                                        p_field->position.y + ( real32_t ) ( 9 * p_field->dimension.height / 10 ) );

   /* Dessin d'un rectangle */
   l_result = mk_graphics_drawRect ( p_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_buttonImage_drawString ( T_mkButtonImage* p_buttonImage, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs TopLeft et BottomRight */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Si un texte doit être dessiné */
   if ( p_buttonImage->text != K_MK_NULL )
   {
      /* Si une image a été configurée (on affiche le texte dessous) */
      if ( ( p_buttonImage->bitmap != K_MK_NULL ) && ( p_buttonImage->bitmap->file != K_MK_NULL ) && ( p_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
      {
         /* Configuration du vecteur TopLeft */
         mk_vect2d_setCoord ( &l_topLeft, p_field->position.x,
                                          p_field->position.y + ( real32_t ) p_buttonImage->bitmap->height );
      }

      /* Sinon (on affiche le texte au milieu du champ) */
      else
      {
         /* Configuration du vecteur TopLeft */
         mk_vect2d_setCoord ( &l_topLeft, p_field->position.x, p_field->position.y );
      }

      /* Configuration du vecteur BottomRight */
      mk_vect2d_setCoord ( &l_bottomRight, p_field->position.x + ( real32_t ) p_field->dimension.width,
                                           p_field->position.y + ( real32_t ) p_field->dimension.height );

      /* Dessin de la bordure */
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

T_mkCode mk_buttonImage_defaultTextPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du bouton */
   T_mkButtonImage* l_buttonImage = p_field->child;

   /* Suppression warning */
   ( void ) p_container, ( void ) p_frameNumber;

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Récupération de la police de caractères par défaut */
      T_mkFont* l_font = mk_font_getDefault ();

      /* Si un style a été spécifié */
      if ( ( l_buttonImage->style != K_MK_NULL ) && ( l_buttonImage->style->font != K_MK_NULL ) )
      {
         /* Actualisation du pointeur de police de caractères */
         l_font = l_buttonImage->style->font;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une image a été configurée */
      if ( ( l_buttonImage->bitmap != K_MK_NULL ) && ( l_buttonImage->bitmap->file != K_MK_NULL ) && ( l_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
      {
         /* Dessin de l'image */
         l_result = mk_buttonImage_drawImage ( l_buttonImage, p_field, l_font );
      }

      /* Sinon */
      else
      {
         /* Dessin du rectangle par défaut */
         l_result = mk_buttonImage_drawDefaultRect ( l_buttonImage, p_field );
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Dessin de la chaine de caractères du bouton */
         l_result = mk_buttonImage_drawString ( l_buttonImage, p_field );
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




