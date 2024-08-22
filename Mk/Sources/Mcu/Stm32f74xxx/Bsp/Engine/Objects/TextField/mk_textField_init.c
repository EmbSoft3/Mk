/**
*
* @copyright Copyright (C) 2022-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_textField_init.c
* @brief Définition de la fonction mk_textField_init.
* @date 22 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_textField_init ( T_mkTextField* p_textField )
{
   /* Si le paramètre est valide */
   if ( p_textField != K_MK_NULL)
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_textField, 0, sizeof ( T_mkTextField ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_textField->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_textField->field, ( T_mkTextField* ) p_textField );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_textField->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_textField->field, K_MK_TEXTFIELD_DEFAULT_WIDTH, K_MK_TEXTFIELD_DEFAULT_HEIGHT );

      /* Configuration du layer */
      mk_field_setLayer ( &p_textField->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de l'index de profondeur */
      mk_field_setZIndex ( &p_textField->field, 1 );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_textField->field, mk_textField_defaultPainter );

      /* Configuration des attributs de la bordure et de l'arrière plan */
      p_textField->borderVisibility = K_MK_GRAPHICS_INVISIBLE;
      p_textField->backgroundVisibility = K_MK_GRAPHICS_INVISIBLE;

      /* Configuration des styles */
      mk_color_setARGB32 ( &p_textField->style.color, 0 );
      p_textField->style.font = &g_mkDisplay.defaultFont.handle;
      p_textField->style.marginTop = K_MK_GRAPHICS_DEFAULT_MARGIN_TOP;
      p_textField->style.marginBottom = K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM;
      p_textField->style.marginRight = K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT;
      p_textField->style.marginLeft = K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT;
      p_textField->style.verticalAlignment = K_MK_TEXT_CENTER_JUSTIFIED;
      p_textField->style.horizontalAlignment = K_MK_TEXT_CENTER_JUSTIFIED;
      p_textField->style.fontEncoding = K_MK_FONT_ASCII;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}



