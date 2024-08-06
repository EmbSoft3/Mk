/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_dispatcher_handleConsumerCode.c
* @brief Définition de la fonction mk_dispatcher_handleConsumerCode.
* @date 18 avr. 2020
*
*/

#include "mk_dispatcher_api.h"


/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_postConsumerCodeEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkConsumerCode* p_consumerCode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Configuration de l'identifiant du contrôle */
   p_message->ctrlId = ( uint16_t ) p_consumerCode->layer.id;

   /* Si un événement 'Release' doit être généré avant un événement 'Press' */
   if ( ( p_consumerCode->state.lastValue != 0 ) && ( p_consumerCode->state.value != 0 ) )
   {
      /* Si l'objet 'Consumer' est de type 'Selector' */
      if ( p_consumerCode->layer.type == K_MK_BUTTON_SELECTOR_CONTROL )
      {
         /* Configuration de l'identifiant du contrôle */
         p_message->ctrlId = ( uint16_t ) p_consumerCode->state.lastValue;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Configuration de l'événement */
      p_message->ctrlEvt = K_MK_EVENT_RELEASE;

      /* Transmission d'un message */
      l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le sélecteur n'est pas au repos */
      if ( p_consumerCode->state.value != 0 )
      {
         /* Si l'objet 'Consumer' est de type 'Selector' */
         if ( p_consumerCode->layer.type == K_MK_BUTTON_SELECTOR_CONTROL )
         {
            /* Configuration de l'identifiant du contrôle */
            p_message->ctrlId = ( uint16_t ) p_consumerCode->state.value;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_PRESS;
      }

      /* Sinon */
      else
      {
         /* Si l'objet 'Consumer' est de type 'Selector' */
         if ( p_consumerCode->layer.type == K_MK_BUTTON_SELECTOR_CONTROL )
         {
            /* Configuration de l'identifiant du contrôle */
            p_message->ctrlId = ( uint16_t ) p_consumerCode->state.lastValue;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_RELEASE;
      }

      /* Transmission d'un message */
      l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleConsumerCode ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_consumerCode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Déclaration d'un pointeur d'objet Consumer */
   T_mkConsumerCode* l_consumerCode = ( T_mkConsumerCode* ) p_consumerCode;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_consumerCode != K_MK_NULL ) )
   {
      /* Configuration du message de sortie */
      l_message.ctrlEvt   = K_MK_EVENT_NO;                              /* Identifiant de l'événement généré (PRESS ou RELEASE) */
      l_message.appCtrlID = p_appCtrlId;                                /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
      l_message.appCtrl   = p_appCtrl;                                  /* Adresse du contrôle applicatif */
      l_message.tick      = p_message->tick;                            /* Numéro du tick enregistré lors de la détection de l'événement */

      /* Si l'état d'un objet 'Consumer' a été modifié */
      if ( l_consumerCode->state.lastValue != l_consumerCode->state.value )
      {
         /* Génération des événements relatifs aux objets Consumer */
         l_result = mk_dispatcher_postConsumerCodeEvent ( p_handler, &l_message, p_consumerCode );

         /* Actualisation de l'état précédent */
         l_consumerCode->state.lastValue = l_consumerCode->state.value;
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


