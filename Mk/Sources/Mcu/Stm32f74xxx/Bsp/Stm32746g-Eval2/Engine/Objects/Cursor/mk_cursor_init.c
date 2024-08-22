/**
*
* @copyright Copyright (C) 2019-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_cursor_init.c
* @brief Définition de la fonction mk_cursor_init.
* @date 2 déc. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_cursor_init ( T_mkCursor* p_cursor )
{
   /* Si le paramètre est valide */
   if ( p_cursor != K_MK_NULL)
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_cursor, 0, sizeof ( T_mkCursor ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_cursor->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_cursor->field, ( T_mkCursor* ) p_cursor );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_cursor->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_cursor->field, K_MK_CURSOR_DEFAULT_WIDTH, K_MK_CURSOR_DEFAULT_HEIGHT );

      /* Configuration du layer */
      mk_field_setLayer ( &p_cursor->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de l'index de profondeur */
      mk_field_setZIndex ( &p_cursor->field, 1 );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_cursor->field, mk_cursor_defaultPainter );

      /* Configuration de l'adresse du bitmap du curseur */
      p_cursor->bitmap.addr = ( T_mkAddr ) g_mkDefaultCursor;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}




