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
* @file mk_hid_mouse_defaultPainter.c
* @brief Définition de la fonction mk_hid_mouse_defaultPainter.
* @date 20 nov. 2023
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mouse_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du curseur */
   T_mkCursor* l_cursor = p_field->child;

   /* Déclaration d'un gestionnaire de dispatcher */
   T_mkDispatcherHandler* l_dispatcherHandler = K_MK_NULL;

   /* Suppression warning */
   ( void ) p_container; ( void ) p_frameNumber;

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Récupération de l'adresse du dispatcher */
      l_result = mk_termio_getChild ( g_mkTermioHandler.dispatcher, ( void** ) &l_dispatcherHandler );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && l_dispatcherHandler != K_MK_NULL )
      {
         /* Si le curseur doit être dessiné */
         if ( l_dispatcherHandler->attribute.mouseCursorVisibility == K_MK_FIELD_VISIBLE )
         {
            /* Si le curseur par défaut doit être utilisé */
            if ( l_dispatcherHandler->attribute.mouseCursorBitmap == K_MK_NULL )
            {
               /* Dessin du curseur par défaut */
               l_result = mk_graphics_drawBitmap ( l_dispatcherHandler->attribute.mouseCursorLayer, ( uint32_t* ) l_cursor->bitmap.addr,
                                                   l_cursor->field.position, l_cursor->field.dimension.width, l_cursor->field.dimension.height );
            }

            /* Sinon */
            else
            {
               /* Dessin du curseur utilisateur */
               l_result = mk_graphics_drawBitmap ( l_dispatcherHandler->attribute.mouseCursorLayer, ( uint32_t* ) l_dispatcherHandler->attribute.mouseCursorBitmap,
                                                   l_cursor->field.position, l_dispatcherHandler->attribute.mouseCursorWidth, l_dispatcherHandler->attribute.mouseCursorHeight );
            }
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
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}




