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
* @file mk_textField_defaultPainter.c
* @brief Définition de la fonction mk_textField_defaultPainter.
* @date 22 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_textField_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_color = 0;

   /* Déclaration d'une variable stockant un vecteurs de travail */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Récupération de l'adresse de la zone de texte */
   T_mkTextField* l_textField = p_field->child;

   /* Suppression warning */
   ( void ) p_frameNumber; ( void ) p_container;

   /* Si la zone de texte doit être rafraichie */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Si le cache doit être actualisé */
      if ( ( l_textField->cache == K_MK_NULL ) || ( l_textField->strAddr != l_textField->painterAddr ) )
      {
         /* Récupération de l'adresse de la chaine de caractères */
         l_textField->painterAddr = l_textField->strAddr;

         /* Configuration du vecteur */
         mk_vect2d_setCoord ( &l_vectDownRight, p_field->position.x + ( real32_t ) p_field->dimension.width, p_field->position.y + ( real32_t ) p_field->dimension.height );

         /* Si l'arrière plan doit être dessiné */
         if ( l_textField->backgroundVisibility == K_MK_GRAPHICS_VISIBLE )
         {
            /* Récupération de la valeur de la couleur */
            l_color = mk_color_getARGB32 ( &l_textField->backgroundColor );

            /* Dessin de l'arrière plan */
            l_result = mk_graphics_drawRect ( p_field->layer, K_MK_GRAPHICS_SOLID, p_field->position, l_vectDownRight, l_color );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si la bordure doit être dessinée */
         if ( l_textField->borderVisibility == K_MK_GRAPHICS_VISIBLE )
         {
            /* Récupération de la valeur de la couleur */
            l_color = mk_color_getARGB32 ( &l_textField->borderColor );

            /* Dessin de la bordure */
            l_result |= mk_graphics_drawRect ( p_field->layer, K_MK_GRAPHICS_EMPTY, p_field->position, l_vectDownRight, l_color );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Dessin de la chaine de caractères */
         l_result |= mk_graphics_drawString ( p_field->layer, p_field->position, l_vectDownRight, l_textField->painterAddr, &l_textField->style, K_MK_NULL );

         /* Si un cache est configuré */
         if ( l_textField->cache != K_MK_NULL )
         {
            /* Copie du buffer graphique vers le cache */
            l_result |= mk_graphics_copy ( l_textField->cache, l_textField->field.position, K_MK_GRAPHICS_FRAME_TO_ADDR, l_textField->field.layer, l_textField->field.dimension.width, l_textField->field.dimension.height );
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
         /* Copie du cache vers le buffer graphique */
         l_result |= mk_graphics_copy ( l_textField->cache, l_textField->field.position, K_MK_GRAPHICS_ADDR_TO_FRAME, l_textField->field.layer, l_textField->field.dimension.width, l_textField->field.dimension.height );
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



