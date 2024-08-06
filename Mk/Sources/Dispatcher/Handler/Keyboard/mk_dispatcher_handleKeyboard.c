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
* @file mk_dispatcher_handleKeyboard.c
* @brief Définition de la fonction mk_dispatcher_handleKeyboard.
* @date 17 déc. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_handleKeyCode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de gestion */
   T_mkKeyHandler l_keyHandler = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_keyboard != K_MK_NULL ) )
   {
      /* Récupération et transmission des événements en relation avec les modificateurs du clavier */
      l_result = mk_dispatcher_handleModifier ( p_handler, p_message, p_keyboard, &l_keyHandler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération et transmission des événements en relation avec les entrées du clavier */
         l_result = mk_dispatcher_handleScancode ( p_handler, p_message, p_keyboard, &l_keyHandler );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleKeyboard ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Déclaration d'un pointeur de clavier */
   T_mkKeyboard* l_keyboard;

   /* Si les paramètres sont valides */
   if ( ( p_message != K_MK_NULL ) && ( p_message->appCtrl != K_MK_NULL ) )
   {
     /* Récupération de l'adresse du contrôle */
      l_keyboard = p_message->appCtrl;

      /* Si un événement a été configuré */
      if ( p_message->ctrlEvt != K_MK_EVENT_NO )
      {
         /* Si l'événement reçu est de type 'Connect' */
         if ( p_message->ctrlEvt == K_MK_EVENT_CONNECT )
         {
            /* Gestion de l'état initial des indicateurs lumineux */
            l_result = mk_dispatcher_handleIndicator ( p_handler, l_keyboard, K_MK_NULL );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Transmission d'un message à la tâche d'écoute */
            l_result = mk_dispatcher_postEvent ( p_handler, p_message, l_keyboard, K_MK_CONTROL_KEYBOARD, l_keyboard->layer.id );
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
         /* Configuration du message de sortie */
         l_message.ctrlEvt   = K_MK_EVENT_NO;               /* Identifiant de l'événement généré */
         l_message.ctrlId    = 0;                           /* Identifiant du contrôle par défaut */
         l_message.appCtrlID = K_MK_CONTROL_KEYBOARD;       /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
         l_message.appCtrl   = l_keyboard;                  /* Adresse du contrôle applicatif */
         l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

         /* Récupération et transmission des événements en relation avec les entrées du clavier */
         l_result = mk_dispatcher_handleKeyCode ( p_handler, &l_message, l_keyboard );
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


