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
* @file mk_progressBar_defaultPainter.c
* @brief Définition de la fonction mk_progressBar_defaultPainter.
* @date 14 oct. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_progressBar_drawString ( T_mkProgressBar* p_progressBar, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration du style par défaut de la barre de progression */
   /* Il peut être statique car il est commun à toutes les fonctions de peinture par défaut */
   static T_mkTextStyle l_defaultStyle = { K_MK_NULL, K_MK_FONT_ASCII, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
         0, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */

   /* Déclaration d'un buffer stockant la chaine de caractères par défaut (pourcentage) */
   char8_t l_strNumber [ 4 ] = { 0 };

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = ( T_str8 ) p_progressBar->defaultText;

   /* Déclaration d'un pointeur de police de caractères */
   T_mkFont* l_font = mk_font_getDefault ( );

   /* Déclaration d'un pointeur de style */
   T_mkTextStyle* l_style = &l_defaultStyle;

   /* Déclaration d'un vecteur de travail */
   T_mkVect2D l_bottomRight = { 0, 0 };

   /* Détermination des coordonnées de la barre de progression */
   mk_vect2d_setCoord ( &l_bottomRight, ( real32_t ) ( p_field->position.x + ( real32_t ) p_field->dimension.width - 1.0f ),
                                        ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - 1.0f ) );

   /* Si un style a été spécifié */
   if ( p_progressBar->style != K_MK_NULL )
   {
      /* Récupération de l'adresse du style */
      l_style = p_progressBar->style;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une chaine de caractères a été spécifiée */
   if ( p_progressBar->text != K_MK_NULL )
   {
      /* Récupération de l'adresse de la chaine de caractères */
      l_str = p_progressBar->text;
   }

   /* Si le texte peut être dessiné dans la barre de progression */
   if ( l_font->height < p_field->dimension.height )
   {
      /* Conversion de la valeur en chaine de caractères */
      ( void ) mk_utils_itoa ( p_progressBar->value, ( T_str8 ) l_strNumber, 10, 0 );

      /* Ajout du caractère % */
      ( void ) mk_utils_strcat ( ( T_str8 ) p_progressBar->defaultText, ( T_str8 ) l_strNumber, ( T_str8 ) "% ");

      /* Dessin de la chaine de caractères */
      l_result = mk_graphics_drawString ( p_field->layer, p_field->position, l_bottomRight, l_str, l_style, K_MK_NULL );
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

T_mkCode mk_progressBar_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant une couleur au format ARGB8888 */
   uint32_t l_color = 0;

   /* Déclaration des vecteurs de travail */
   T_mkVect2D l_topLeft = { 0, 0 }, l_bottomRight = { 0, 0 }, l_foregroundValue = { 0, 0 };

   /* Récupération de l'adresse de la barre de progression */
   T_mkProgressBar* l_progressBar = ( T_mkProgressBar* ) p_field->child;

   /* Déclaration d'une variable stockant le rayon de la barre de progression */
   real32_t l_radius = ( real32_t ) l_progressBar->borderWidth;

   /* Suppression warning */
   ( void ) p_container; ( void ) p_frameNumber;

   /* Si le champ doit être rafraichi */
   if ( ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED ) &&
        ( p_field->dimension.width >= ( 2*l_radius ) ) && ( p_field->dimension.height >= ( 2*l_radius ) ) )
   {
      /* Détermination des coordonnées de la barre de progression */
      mk_vect2d_setCoord ( &l_bottomRight, ( real32_t ) ( p_field->position.x + ( real32_t ) p_field->dimension.width - 1.0f ),
                                           ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - 1.0f ) );
      /* Si une bordure doit être dessinée */
      if ( ( l_result == K_MK_OK ) && ( l_progressBar->borderVisibility == K_MK_FIELD_VISIBLE ) )
      {
         /* Récupération de la valeur de la couleur */
         l_color = mk_color_getARGB32 ( &l_progressBar->borderColor );

         /* Dessin du rectangle de la bordure */
         l_result = mk_graphics_drawRoundRect ( p_field->layer, K_MK_GRAPHICS_SOLID, p_field->position, l_bottomRight, l_radius, l_color );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la valeur du rayon */
         l_radius = 0.0f;
      }

      /* Détermination des coordonnées de la barre de progression pour l'arrière plan et le premier plan */
      mk_vect2d_setCoord ( &l_topLeft, ( real32_t ) ( p_field->position.x + l_radius ), ( real32_t ) ( p_field->position.y + l_radius ) );
      mk_vect2d_setCoord ( &l_bottomRight, ( real32_t ) ( p_field->position.x + ( real32_t ) p_field->dimension.width  - ( l_radius ) - 1.0f ),
                                           ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - ( l_radius ) - 1.0f ) );

      /* Si l'arrière plan doit être dessiné */
      if ( ( l_result == K_MK_OK ) && ( l_progressBar->backgroundVisibility == K_MK_FIELD_VISIBLE ) )
      {
         /* Récupération de la valeur de la couleur */
         l_color = mk_color_getARGB32 ( &l_progressBar->backgroundColor );

         /* Dessin du rectangle de l'arrière plan */
         l_result = mk_graphics_drawRect ( p_field->layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le premier plan doit être dessiné */
      if ( ( l_result == K_MK_OK ) && ( l_progressBar->foregroundVisibility == K_MK_FIELD_VISIBLE ) && ( l_progressBar->value != 0 ) )
      {
         /* Détermination des coordonnées de la barre de progression */
         mk_vect2d_setCoord ( &l_foregroundValue, ( real32_t ) ( p_field->position.x + ( real32_t ) ( ( l_progressBar->value * ( p_field->dimension.width - ( uint32_t ) l_radius ) / 100 ) - 1 ) ),
                                                  ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - l_radius - 1.0f ) );

         /* Récupération de la valeur de la couleur */
         l_color = mk_color_getARGB32 ( &l_progressBar->foregroundColor );

         /* Dessin du rectangle de premier plan */
         l_result = mk_graphics_drawRect ( p_field->layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_foregroundValue, l_color );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une chaine de caractères doit être dessinée */
      if ( ( l_result == K_MK_OK ) && ( l_progressBar->textVisibility == K_MK_FIELD_VISIBLE ) )
      {
         /* Dessin de la chaine de caractères */
         l_result = mk_progressBar_drawString ( l_progressBar, p_field );
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


