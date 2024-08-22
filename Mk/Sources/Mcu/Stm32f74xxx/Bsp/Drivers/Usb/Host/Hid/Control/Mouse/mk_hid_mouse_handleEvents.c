/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_hid_mouse_handleEvents.c
* @brief Définition de la fonction mk_hid_mouse_handleEvents.
* @date 7 déc. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_mouse_handleEvents ( T_mkMouse* p_mouse, T_mkContainer* p_container, T_mkCtrlEvent p_mkEvtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_mouse != K_MK_NULL ) && ( p_container != K_MK_NULL ) )
   {
      /* Si une événement de type 'Connect' s'est produit */
      if ( p_mkEvtCtrl == K_MK_EVENT_CONNECT )
      {
         /* Configuration de la plage d'évolution et de la résolution du curseur de la souris */
         l_result = mk_hid_mouse_setRectangle ( p_mouse, 0, 0, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

         /* Initialisation du curseur de la souris (graphique) */
         mk_cursor_init ( &p_mouse->cursor );
         mk_cursor_setLayer ( &p_mouse->cursor, K_MK_GRAPHICS_FOREGROUND );
         mk_cursor_setVisibility ( &p_mouse->cursor, K_MK_FIELD_VISIBLE );
         mk_cursor_setPainter ( &p_mouse->cursor, mk_mouse_defaultPainter );

         /* Ajout du curseur dans un container */
         l_result |= mk_container_add ( g_mkDisplay.painter.semaphore, p_container, &p_mouse->cursor.field );
      }

      /* Sinon si un événement de type 'Disconnect' s'est produit */
      else if ( p_mkEvtCtrl == K_MK_EVENT_DISCONNECT )
      {
         /* Retrait du curseur du container */
         mk_container_remove ( g_mkDisplay.painter.semaphore, p_container, &p_mouse->cursor.field );
      }

      /* Sinon si un événement de type 'Move' s'est produit */
      else if ( p_mkEvtCtrl == K_MK_EVENT_MOVE )
      {
         /* Actualisation de la position du curseur */
         mk_cursor_setPosition ( &p_mouse->cursor, p_mouse->axis.x, p_mouse->axis.y );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


