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
* @file mk_editField_init.c
* @brief Définition de la fonction mk_editField_init.
* @date 1 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_editField_init ( T_mkEditField* p_editField )
{
   /* Si le paramètre est valide */
   if ( p_editField != K_MK_NULL)
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_editField, 0, sizeof ( T_mkEditField ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_editField->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_editField->field, ( T_mkEditField* ) p_editField );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_editField->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_editField->field, K_MK_EDITFIELD_DEFAULT_WIDTH, K_MK_EDITFIELD_DEFAULT_HEIGHT );

      /* Configuration du layer */
      mk_field_setLayer ( &p_editField->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_editField->field, mk_editField_defaultPainter );

      /* Configuration de l'adresse de la fonction d'écoute */
      mk_field_setListener ( &p_editField->field, mk_editField_defaultListener );

      /* Configuration des attributs de la bordure et de l'arrière plan */
      p_editField->borderVisibility = K_MK_GRAPHICS_INVISIBLE;
      p_editField->backgroundVisibility = K_MK_GRAPHICS_INVISIBLE;

      /* Configuration des attributs des curseurs */
      p_editField->primaryCursor.xoffset = K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETX;
      p_editField->primaryCursor.yoffset = K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETY;
      p_editField->primaryCursor.width = K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_WIDTH;
      p_editField->primaryCursor.height = K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_HEIGHT;
      p_editField->primaryCursor.visibility = K_MK_GRAPHICS_INVISIBLE;
      p_editField->primaryCursor.mode = K_MK_GRAPHICS_CURSOR_TYPE_PRIMARY;
      p_editField->secondaryCursor.xoffset = K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETX;
      p_editField->secondaryCursor.yoffset = K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETY;
      p_editField->secondaryCursor.height = K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_HEIGHT;
      p_editField->secondaryCursor.visibility = K_MK_GRAPHICS_INVISIBLE;
      p_editField->secondaryCursor.mode = K_MK_GRAPHICS_CURSOR_TYPE_SECONDARY;
      p_editField->cursor = &p_editField->primaryCursor;

      /* Configuration des styles */
      mk_color_setARGB32 ( &p_editField->style.color, 0 );
      p_editField->style.font = &g_mkDisplay.defaultFont.handle;
      p_editField->style.marginTop = K_MK_GRAPHICS_DEFAULT_MARGIN_TOP;
      p_editField->style.marginBottom = K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM;
      p_editField->style.marginRight = K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT;
      p_editField->style.marginLeft = K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT;
      p_editField->style.verticalAlignment = K_MK_TEXT_CENTER_JUSTIFIED;
      p_editField->style.horizontalAlignment = K_MK_TEXT_CENTER_JUSTIFIED;
      p_editField->style.fontEncoding = K_MK_FONT_ASCII;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


