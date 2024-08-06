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
* @file mk_dispatcher_handleButton.c
* @brief Définition de la fonction mk_dispatcher_handleButton.
* @date 21 nov. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_postTimedButtonEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkButton* p_button )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_time;

   /* Si un événement 'Press' a été généré */
   if ( p_button->state.lastEvent == K_MK_EVENT_PRESS )
   {
      /* Enregistrement de la valeur du tick où l'événement 'Press' s'est déclenché */
      p_button->tick.pressTick = p_message->tick;

      /* Détermination de la durée du clic */
      l_time = mk_utils_tick ( p_button->tick.clickTick, p_message->tick );

      /* Si la durée d'un double clic est dépassée */
      if ( l_time > K_MK_EVENT_DOUBLE_CLICK_TIMEOUT )
      {
         /* Réinitialisation du compteur de clic */
         p_button->tick.clickCount = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le compteur de click est nul */
      if ( p_button->tick.clickCount == 0 )
      {
         /* Enregistrement de la valeur du tick où l'événement 'Press' s'est déclenché */
         p_button->tick.clickTick = p_button->tick.pressTick;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du compteur de clic */
      p_button->tick.clickCount++;
   }

   /* Sinon si un événement 'Release' a été généré */
   else if ( p_button->state.lastEvent == K_MK_EVENT_RELEASE )
   {
      /* Détermination de la durée du clic */
      l_time = mk_utils_tick ( p_button->tick.pressTick, p_message->tick );

      /* Si la durée du clic est inférieure au timeout */
      if ( l_time <= K_MK_EVENT_CLICK_TIMEOUT )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_CLICK;

         /* Transmission d'un message */
         l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Une séquence 'double clic' est constitué des événements 'Press', 'Release', 'Press', 'Release'. */
      /* La durée maximale entre un 'Press' et un 'Release' est égale à K_MK_EVENT_CLICK_TIMEOUT. */
      /* La durée maximale entre le premier 'Press' et le dernier 'Release' est égale à K_MK_EVENT_DOUBLE_CLICK_TIMEOUT. */
      /* L'événement est généré si ces deux conditions sont respectées. */

      /* Si un clic a été détecté */
      if ( p_button->tick.clickCount == 2 )
      {
         /* Détermination de la durée du double clic */
         l_time = mk_utils_tick ( p_button->tick.clickTick, p_message->tick );

         /* Si la durée du double clic est inférieure au timeout */
         if ( l_time <= K_MK_EVENT_DOUBLE_CLICK_TIMEOUT )
         {
            /* Configuration de l'événement */
            p_message->ctrlEvt = K_MK_EVENT_DOUBLE_CLICK;

            /* Transmission d'un message */
            l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Réinitialisation du compteur de clic */
         p_button->tick.clickCount = 0;
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_postButtonEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkButton* p_button )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le bouton est dans l'état '1' */
   if ( p_button->state.value == 1 )
   {
      /* Si le type du bouton est 'Momentary Control' (MC) */
      if ( p_button->layer.type == K_MK_BUTTON_MOMENTARY_CONTROL )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_PRESS;
      }

      /* Sinon si le bouton est de type 'Toogle ON/OFF Control' (OOC) ou 'Selector' (Sel) */
      else if ( ( p_button->layer.type == K_MK_BUTTON_TOOGLE_ON_OFF_CONTROL ) ||
                ( p_button->layer.type == K_MK_BUTTON_SELECTOR_CONTROL ) )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_PRESS;
      }

      /* Sinon si le bouton est de type 'ON/OFF Control' (OOC) */
      else if ( p_button->layer.type == K_MK_BUTTON_ON_OFF_CONTROL )
      {
         /* Si l'état précédent est nul */
         if ( p_button->state.lastValue == 0 )
         {
            /* Configuration de l'événement */
            p_message->ctrlEvt = K_MK_EVENT_PRESS;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le bouton est de type 'OneShot' (OSC) */
      else if ( p_button->layer.type == K_MK_BUTTON_ONE_SHOT_CONTROL )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_PRESS;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si le bouton est dans l'état '-1' */
   else if ( p_button->state.value == ( -1 ) )
   {
      /* Si le bouton est de type 'ON/OFF Control' (OOC) */
      if ( p_button->layer.type == K_MK_BUTTON_ON_OFF_CONTROL )
      {
         /* Si l'état précédent est nul */
         if ( p_button->state.value == 0 )
         {
            /* Configuration de l'événement */
            p_message->ctrlEvt = K_MK_EVENT_RELEASE;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }
   }

   /* Sinon */
   else
   {
      /* Si le type du bouton est MC */
      if ( p_button->layer.type == K_MK_BUTTON_MOMENTARY_CONTROL )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_RELEASE;
      }

      /* Sinon si le bouton est de type 'Toogle ON/OFF Control' (OOC) ou 'Selector' (Sel) */
      else if ( ( p_button->layer.type == K_MK_BUTTON_TOOGLE_ON_OFF_CONTROL ) ||
                ( p_button->layer.type == K_MK_BUTTON_SELECTOR_CONTROL ) )
      {
         /* Configuration de l'événement */
         p_message->ctrlEvt = K_MK_EVENT_RELEASE;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si un événement doit être généré */
   if ( p_message->ctrlEvt != K_MK_EVENT_NO )
   {
      /* Transmission d'un message */
      l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );

      /* Memorisation de l'événement */
      p_button->state.lastEvent = p_message->ctrlEvt;
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

T_mkCode mk_dispatcher_handleButton ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_button )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Déclaration d'un pointeur de bouton */
   T_mkButton* l_button = ( T_mkButton* ) p_button;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_button != K_MK_NULL ) )
   {
      /* Configuration du message de sortie */
      l_message.ctrlEvt   = K_MK_EVENT_NO;               /* Identifiant de l'événement généré (PRESS ou RELEASE) */
      l_message.ctrlId    = l_button->layer.id;          /* Identifiant du contrôle */
      l_message.appCtrlID = p_appCtrlId;                 /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
      l_message.appCtrl   = p_appCtrl;                   /* Adresse du contrôle applicatif */
      l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

      /* Si l'état du bouton a été modifié */
      if ( l_button->state.lastValue != l_button->state.value )
      {
         /* Génération des événements relatifs aux boutons */
         l_result = mk_dispatcher_postButtonEvent ( p_handler, &l_message, l_button );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Génération des événements relatifs aux temporisations */
            l_result = mk_dispatcher_postTimedButtonEvent ( p_handler, &l_message, l_button );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Mémorisation de l'état du bouton */
         l_button->state.lastValue = l_button->state.value;
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
