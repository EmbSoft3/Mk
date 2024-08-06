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
* @file mk_buttonImage_init.c
* @brief Définition de la fonction mk_buttonImage_init.
* @date 10 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_buttonImage_init ( T_mkButtonImage* p_buttonImage )
{
   /* Si le paramètre est valide */
   if ( p_buttonImage != K_MK_NULL)
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_buttonImage, 0, sizeof ( T_mkButtonImage ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_buttonImage->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_buttonImage->field, ( T_mkButtonImage* ) p_buttonImage );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_buttonImage->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_buttonImage->field, K_MK_BUTTON_IMAGE_DEFAULT_WIDTH, K_MK_BUTTON_IMAGE_DEFAULT_HEIGHT );

      /* Configuration du layer */
      mk_field_setLayer ( &p_buttonImage->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_buttonImage->field, mk_buttonImage_defaultPainter );

      /* Configuration de l'adresse de la fonction d'écoute */
      mk_field_setListener (&p_buttonImage->field, K_MK_NULL );

      /* Configuration de la couleur de la bordure */
      mk_color_setARGB32 ( &p_buttonImage->borderColor, 0 );

      /* Configuration de l'état de la bordure */
      p_buttonImage->borderVisibility = K_MK_GRAPHICS_INVISIBLE;

      /* Configuration du pointeur d'image */
      p_buttonImage->bitmap = K_MK_NULL;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}



