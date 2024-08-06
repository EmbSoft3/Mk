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
* @file mk_hid_mouse_handleSubEvents.c
* @brief Définition de la fonction mk_hid_mouse_handleSubEvents.
* @date 13 déc. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_mouse_handleSubEvents ( T_mkMouse* p_mouse, T_mkField* p_field, T_mkCtrlEvent p_mainEvtCtrl, T_mkCtrlEvent* p_subEvtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un événement */
   T_mkCtrlEvent l_subEvent;

   /* Déclaration des variables d'état */
   uint32_t l_currentState;

   /* Si les paramètres sont valides */
   if ( ( p_mouse != K_MK_NULL ) && ( p_field != K_MK_NULL ) )
   {
      /* Récupération de la valeur de l'événement à analyser */
      l_subEvent = ( * p_subEvtCtrl );

      /* Actualisation de la valeur du résultat */
      ( *p_subEvtCtrl ) = K_MK_EVENT_NO;

      /* Si une événement de type 'Move' s'est produit */
      if ( p_mainEvtCtrl == K_MK_EVENT_MOVE )
      {
         /* Analyse de la position du curseur par rapport au champ */
         l_currentState = mk_field_inside ( p_field, p_mouse->axis.x, p_mouse->axis.y );

         /* Si l'analyse porte sur l'événement 'K_MK_EVENT_ENTER' */
         if ( l_subEvent == K_MK_EVENT_ENTER )
         {
            /* Si le curseur n'est pas déjà dans le champ */
            if ( ( p_field->cursor == K_MK_FIELD_CURSOR_OUTSIDE ) && ( l_currentState == 1 ) )
            {
               /* Actualisation de l'attribut curseur du champ */
               mk_field_setCursor ( p_field, K_MK_FIELD_CURSOR_INSIDE );

               /* Actualisation de la valeur du résultat */
               ( *p_subEvtCtrl ) = K_MK_EVENT_ENTER;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Sinon si l'analyse porte sur l'événement 'K_MK_EVENT_EXIT' */
         else if ( l_subEvent == K_MK_EVENT_EXIT )
         {
            /* Si le curseur est sorti du champ */
            /* L'attribut cursor est utilisé car en fonction de la résolution de la souris, il peut arriver que  */
            /* l'événement EXIT soit manqué.*/
            if ( ( p_field->cursor == K_MK_FIELD_CURSOR_INSIDE ) && ( l_currentState == 0 ) )
            {
               /* Actualisation de l'attribut curseur du champ */
               mk_field_setCursor ( p_field, K_MK_FIELD_CURSOR_OUTSIDE );

               /* Actualisation de la valeur du résultat */
               ( *p_subEvtCtrl ) = K_MK_EVENT_EXIT;
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



