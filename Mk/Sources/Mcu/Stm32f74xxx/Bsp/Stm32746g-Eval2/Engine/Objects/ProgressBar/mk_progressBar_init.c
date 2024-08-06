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
* @file mk_progressBar_init.c
* @brief Définition de la fonction mk_progressBar_init.
* @date 14 oct. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_progressBar_init ( T_mkProgressBar* p_progressBar )
{
   /* Si le paramètre est valide */
   if ( p_progressBar != K_MK_NULL )
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_progressBar, 0, sizeof ( T_mkProgressBar ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_progressBar->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_progressBar->field, ( T_mkProgressBar* ) p_progressBar );

      /* Configuration du layer */
      mk_field_setLayer ( &p_progressBar->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_progressBar->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_progressBar->field, K_MK_PROGRESSBAR_DEFAULT_WIDTH, K_MK_PROGRESSBAR_DEFAULT_HEIGHT );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_progressBar->field, mk_progressBar_defaultPainter );

      /* Configuration de l'adresse de la fonction d'écoute */
      mk_field_setListener (&p_progressBar->field, K_MK_NULL );

      /* Configuration de la couleur d'arrière-plan */
      mk_progressBar_setBackgroundColor ( p_progressBar, K_MK_COLOR_ARGB_BLACK );
      mk_progressBar_setBackgroundVisibility ( p_progressBar, K_MK_FIELD_VISIBLE );

      /* Configuration de la couleur de premier-plan */
      mk_progressBar_setForegroundColor ( p_progressBar, K_MK_COLOR_ARGB_YELLOW );
      mk_progressBar_setForegroundVisibility ( p_progressBar, K_MK_FIELD_VISIBLE );

      /* Configuration de la bordure */
      mk_progressBar_setBorderColor ( p_progressBar, K_MK_COLOR_ARGB_BLACK );
      mk_progressBar_setBorderVisibility ( p_progressBar, K_MK_FIELD_VISIBLE );
      mk_progressBar_setBorderWidth ( p_progressBar, 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}



