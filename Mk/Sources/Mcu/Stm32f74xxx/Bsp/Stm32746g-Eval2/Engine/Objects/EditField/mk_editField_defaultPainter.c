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
* @file mk_editField_defaultPainter.c
* @brief Définition de la fonction mk_editField_defaultPainter.
* @date 1 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_editField_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_color = 0;

   /* Déclaration d'une variable stockant un vecteur de travail */
   T_mkVect2D l_vectDownRight = { 0, 0 };

   /* Récupération de l'adresse de la boite d'édition */
   T_mkEditField* l_editField = ( T_mkEditField* ) p_field->child;

   /* Suppression warning */
   ( void ) p_container;

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Si le curseur doit être dessiné */
      if ( ( l_editField->cursor->visibility == K_MK_GRAPHICS_VISIBLE ) && ( ( p_frameNumber < ( K_MK_DISPLAY_FRAMERATE >> 1 ) ) || ( l_editField->cursorInhibitionCounter != 0 ) ) )
      {
         /* Configuration de la visibilité du curseur */
         l_editField->cursor->blink = K_MK_GRAPHICS_VISIBLE;

         /* Configuration de l'offset du curseur */
         l_editField->cursor->currentOffset = l_editField->cursorBaseOffset;
         l_editField->cursor->baseOffset = l_editField->windowBaseOffset;
      }

      /* Sinon */
      else
      {
         /* Configuration de la visibilité du curseur */
         l_editField->cursor->blink = K_MK_GRAPHICS_INVISIBLE;
      }

      /* Si le cache doit être actualisé */
      if ( ( l_editField->cache == K_MK_NULL ) ||
           ( l_editField->painterBaseAddr != l_editField->windowBaseAddr ) || ( l_editField->cursorPainterOffset != l_editField->cursorBaseOffset ) ||
           ( ( p_frameNumber == ( K_MK_DISPLAY_FRAMERATE >> 1 ) || ( p_frameNumber == 0 ) ) && ( l_editField->cursor->visibility == K_MK_GRAPHICS_VISIBLE ) ) )
      {
         /* Récupération du pointeur de chaine */
         l_editField->painterBaseAddr = l_editField->windowBaseAddr;

         /* Récupération de l'offset du curseur */
         l_editField->cursorPainterOffset = l_editField->cursorBaseOffset;

         /* Configuration du vecteur */
         mk_vect2d_setCoord ( &l_vectDownRight, l_editField->field.position.x + ( real32_t ) l_editField->field.dimension.width, l_editField->field.position.y + ( real32_t ) l_editField->field.dimension.height );

         /* Si l'arrière plan doit être dessiné */
         if ( l_editField->backgroundVisibility == K_MK_GRAPHICS_VISIBLE )
         {
            /* Récupération de la valeur de la couleur */
            l_color = mk_color_getARGB32 ( &l_editField->backgroundColor );

            /* Dessin de l'arrière plan */
            l_result = mk_graphics_drawRect ( l_editField->field.layer, K_MK_GRAPHICS_SOLID, l_editField->field.position, l_vectDownRight, l_color );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si la bordure doit être dessiné */
         if ( l_editField->borderVisibility == K_MK_GRAPHICS_VISIBLE )
         {
            /* Récupération de la valeur de la couleur */
            l_color = mk_color_getARGB32 ( &l_editField->borderColor );

            /* Dessin de la bordure */
            l_result |= mk_graphics_drawRect ( l_editField->field.layer, K_MK_GRAPHICS_EMPTY, l_editField->field.position, l_vectDownRight, l_color );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le défilement automatique est activé */
         if ( l_editField->scrolling == K_MK_EDITFIELD_SCROLLING_ENABLED )
         {
            /* Actualisation de la position du curseur et de la fenêtre courante */
            l_result |= mk_editField_handleScrolling ( l_editField );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Dessin de la chaine de caractères */
         l_result |= mk_graphics_drawString ( l_editField->field.layer, l_editField->field.position, l_vectDownRight, l_editField->painterBaseAddr, &l_editField->style, l_editField->cursor );

         /* Si un cache est configuré */
         if ( l_editField->cache != K_MK_NULL )
         {
            /* Copie du buffer graphique vers le cache */
            l_result |= mk_graphics_copy ( l_editField->cache, l_editField->field.position, K_MK_GRAPHICS_FRAME_TO_ADDR, l_editField->field.layer, l_editField->field.dimension.width, l_editField->field.dimension.height );
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
         l_result |= mk_graphics_copy ( l_editField->cache, l_editField->field.position, K_MK_GRAPHICS_ADDR_TO_FRAME, l_editField->field.layer, l_editField->field.dimension.width, l_editField->field.dimension.height );
      }

      /* Si le compteur d'inhibition doit être actualisé */
      if ( l_editField->cursorInhibitionCounter != 0 )
      {
         /* Décrémentation d'une frame */
         l_editField->cursorInhibitionCounter = ( uint32_t ) ( l_editField->cursorInhibitionCounter - 1 );
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


