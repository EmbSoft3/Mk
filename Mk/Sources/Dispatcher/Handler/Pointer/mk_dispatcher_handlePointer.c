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
* @file mk_dispatcher_handlePointer.c
* @brief Définition de la fonction mk_dispatcher_handlePointer.
* @date 24 nov. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handlePointer ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Déclaration d'un pointeur de bouton */
   T_mkAxis2* l_pointer = ( T_mkAxis2* ) p_axis;

   /* Déclaration des variables de travail */
   real32_t l_x, l_y;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_axis != K_MK_NULL ) )
   {
      /* Configuration du message de sortie */
      l_message.ctrlEvt   = K_MK_EVENT_MOVE;             /* Identifiant de l'événement généré */
      l_message.ctrlId    = 0;                           /* Identifiant du contrôle */
      l_message.appCtrlID = p_appCtrlId;                 /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
      l_message.appCtrl   = p_appCtrl;                   /* Adresse du contrôle applicatif */
      l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

      /* Si un déplacement du curseur s'est produit */
      if ( ( l_pointer->dx != 0 ) || ( l_pointer->dy != 0 ) )
      {
         /* Détermination de la valeur des coordonnées */
         l_x = l_pointer->x + ( ( real32_t ) l_pointer->dx * p_handler->attribute.pointerResolution );
         l_y = l_pointer->y + ( ( real32_t ) l_pointer->dy * p_handler->attribute.pointerResolution );

         /* Si la coordonnée x est négative */
         if ( l_x < 0 )
         {
            /* Réinitialisation de la valeur de la coordonnée x */
            l_x = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si la coordonnée y est négative */
         if ( l_y < 0 )
         {
            /* Réinitialisation de la valeur de la coordonnée y */
            l_y = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Mise à jour de la coordonnée x en fonction de la valeur minimale du layer */
         if ( l_x < l_pointer->rectangle.x )
         {
            /* Actualisation de la coordonnée x */
            l_x = l_pointer->rectangle.x;
         }

         /* Mise à jour de la coordonnée x en fonction de la valeur maximale du layer */
         else if ( l_x > ( l_pointer->rectangle.x + l_pointer->rectangle.width ) )
         {
            /* Actualisation de la coordonnée x */
            l_x = l_pointer->rectangle.x + l_pointer->rectangle.width - 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Mise à jour de la coordonnée y en fonction de la valeur minimale du layer */
         if ( l_y < l_pointer->rectangle.y )
         {
            /* Actualisation de la coordonnée y */
            l_y = l_pointer->rectangle.y;
         }

         /* Mise à jour de la coordonnée y en fonction de la valeur maximale du layer */
         else if ( l_y > ( l_pointer->rectangle.y + l_pointer->rectangle.height ) )
         {
            /* Actualisation de la coordonnée y */
            l_y = l_pointer->rectangle.y + l_pointer->rectangle.height - 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation des coordonnées du pointeur */
         l_pointer->x = l_x;
         l_pointer->y = l_y;

         /* Transmission d'un message */
         l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
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
