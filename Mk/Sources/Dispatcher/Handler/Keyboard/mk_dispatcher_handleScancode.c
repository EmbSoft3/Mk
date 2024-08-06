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
* @file mk_dispatcher_handleScancode.c
* @brief Définition de la fonction mk_dispatcher_handleScancode.
* @date 30 déc. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCtrlEvent mk_dispatcher_setCharEvent ( T_mkKeyHandler* p_handler, T_mkCtrlEvent p_event, T_mkCtrlEvent p_state )
{
   /* Configuration de type de message envoyé au listener */
   /* Si un événement de type 'HOLD' doit être positionné */
   if ( p_state == K_MK_EVENT_CHAR_HOLD )
   {
      p_event = K_MK_EVENT_CHAR_HOLD;
   }

   /* Sinon */
   else
   {
      p_event = K_MK_EVENT_CHAR_DOWN;
   }

   /* Si une commande a été détectée */
   if ( p_handler->cmd != 0 )
   {
      /* Configuration de type de message envoyé au listener */
      /* Si l'état de base est de type 'DOWN' */
      if ( p_event == K_MK_EVENT_CHAR_DOWN )
      {
         p_event = K_MK_EVENT_KEY_DOWN;
      }

      /* Sinon si l'événement de base est de type 'HOLD' */
      else if ( p_event == K_MK_EVENT_CHAR_HOLD )
      {
         p_event = K_MK_EVENT_KEY_HOLD;
      }

      /* Sinon ('UP') */
      else
      {
         p_event = K_MK_EVENT_KEY_UP;
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( p_event );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCtrlEvent mk_dispatcher_setIdleCharEvent ( T_mkKey* p_key )
{
   /* Déclaration de la variable de retour */
   T_mkCtrlEvent l_result;

   /* Si un caractère affichable a déjà été transmis */
   /* Configuration du type du message envoyé au listener */
   if ( ( p_key->button.state.lastEvent == K_MK_EVENT_CHAR_DOWN ) || ( p_key->button.state.lastEvent == K_MK_EVENT_CHAR_HOLD ) )
   {
      l_result = K_MK_EVENT_CHAR_UP;
   }

   /* Sinon */
   else
   {
      l_result = K_MK_EVENT_KEY_UP;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_postKeyEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler, T_mkKey* p_key, T_mkCtrlEvent p_state )
{
   /* Transcodage du code clavier en code commande ou en code affichable */
   T_mkCode l_result = mk_dispatcher_translateCode ( p_handler, p_message, p_keyboard, p_keyHandler, p_key );

   /* Si aucune erreur ne s'est produite et si le code clavier est valide */
   if ( ( l_result == K_MK_OK ) && ( p_keyHandler->scancode != 0 ) )
   {
      /* Enregistrement de l'adresse de la structure de sortie */
      p_keyboard->output = &p_key->key;

      /* Si un événement de type 'DOWN' ou 'HOLD' doit être généré */
      if ( p_state != K_MK_EVENT_CHAR_UP )
      {
         /* Configuration de type de message envoyé à la tâche d'écoute */
         p_message->ctrlEvt = mk_dispatcher_setCharEvent ( p_keyHandler, K_MK_EVENT_CHAR_DOWN, p_state );

         /* Enregistrement de la combinaison de touches dans le message à destination de la tâche d'écoute */
         p_message->ctrlId = ( uint16_t ) p_keyHandler->scancode;

         /* Memorisation de l'événement envoyé afin de savoir quel événement transmettre lorsque la touche */
         /* est relachée. */
         p_key->button.state.lastEvent = p_message->ctrlEvt;

         /* Memorisation de la combinaison de touches actionnées afin de savoir quel code transmettre */
         /* lorsque la touche est relachée. */
         p_key->button.state.lastMemo = ( uint16_t ) p_keyHandler->scancode;

         /* Mémorisation de l'instant ou l'événement a été généré */
         p_key->button.tick.pressTick = p_message->tick;
      }

      /* Sinon ( événement UP ) */
      else
      {
         /* Sélection du type de message envoyé à la tâche d'écoute en fonction de l'état précédent */
         p_message->ctrlEvt = mk_dispatcher_setIdleCharEvent ( p_key );

         /* Enregistrement de la combinaison de touches dans le message à destination de la tâche d'écoute */
         /* On transmet la combinaison de touches enregistrées lorsque la touche a été actionnée pour la dernière fois. */
         p_message->ctrlId = p_key->button.state.lastMemo;
      }

      /* Transmission d'un message */
      l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Réinitialisation de la variable d'état indiquant la présence d'une commande */
   p_keyHandler->cmd = 0;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_generateKeyUpHoldEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de touches */
   T_mkKey *l_lastKey = p_keyboard->input, *l_currentKey;

   /* Déclaration d'une variable d'état */
   uint32_t l_state = 0, l_timeout = 0;

   /* Pour le nombre d'entrées du clavier */
   for ( ; ( ( l_lastKey != K_MK_NULL ) && ( l_result == K_MK_OK ) ) ; l_lastKey = ( T_mkKey* ) l_lastKey->button.nextButton )
   {
      /* Note : la valeur initiale des attributs 'lastValue' est nulle, la variable 'l_currentKey' contient l'entrée courante */
      /* Il ne peut se produire qu'un type d'événement par entrée. */
      /* Dans cette boucle, on compare les valeurs passées avec les valeurs présentes pour générer les événements 'UP' et 'HOLD'. */

      /* Si l'entrée courante contient une valeur */
      if ( l_lastKey->button.state.lastValue != 0 )
      {
         /* Pour le nombre d'entrées du clavier */
         for ( l_currentKey = p_keyboard->input ; ( ( l_currentKey != K_MK_NULL ) && ( l_result == K_MK_OK ) ) ; l_currentKey = ( T_mkKey* ) l_currentKey->button.nextButton )
         {
            /* Si la touche est dans l'état 'Hold' */
            if ( l_lastKey->button.state.lastValue == l_currentKey->button.state.value )
            {
               /* Actualisation de la variable d'état */
               l_state = 1;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Récupération du code clavier courant */
         p_keyHandler->scancode = ( uint16_t ) l_lastKey->button.state.lastValue;

         /* Si un événement de type 'UP' doit être généré */
         if ( l_state == 0 )
         {
            /* Transmission d'un message de type 'UP' à la tâche d'écoute */
            l_result = mk_dispatcher_postKeyEvent ( p_handler, p_message, p_keyboard, p_keyHandler, l_lastKey, K_MK_EVENT_CHAR_UP );
         }

         /* Sinon si un événement de type 'HOLD' doit être généré */
         else if ( l_state == 1 )
         {
            /* Les 'Reports' sont retournés par le clavier à intervalle régulier ou lorsqu'une touche change d'état. */
            /* Afin d'éviter le spam de ces événements, on temporise leurs transmissions. */
            l_timeout = mk_utils_tick ( l_lastKey->button.tick.pressTick, p_message->tick );

            /* Si un événement de type 'Hold' doit être envoyé */
            if ( l_timeout >= l_lastKey->button.tick.clickCount )
            {
               /* Transmission d'un message de type 'HOLD' à la tâche d'écoute */
               l_result = mk_dispatcher_postKeyEvent ( p_handler, p_message, p_keyboard, p_keyHandler, l_lastKey, K_MK_EVENT_CHAR_HOLD );

               /* Désactivation de l'inhibition des événements 'HOLD' et configuration de la durée minimal entre deux événements HOLD */
               l_lastKey->button.tick.clickCount = p_handler->attribute.keyboardHoldRate;
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

         /* Actualisation de la variable d'état */
         l_state = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_generateKeyDownEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de touches */
   T_mkKey *l_lastKey, *l_currentKey;

   /* Déclaration d'une variable d'état */
   uint32_t l_state = 0;

   /* Pour le nombre d'entrées du clavier */
   for ( l_currentKey = p_keyboard->input ; ( ( l_currentKey != K_MK_NULL ) && ( l_result == K_MK_OK ) ) ; l_currentKey = ( T_mkKey* ) l_currentKey->button.nextButton )
   {
      /* Note : la valeur initiale des attributs 'lastValue' est nulle, la variable 'l_currentKey' contient l'entrée courante */
      /* Il ne peut se produire qu'un type d'événement par entrée. */
      /* Dans cette boucle, on compare les valeurs présentes avec les valeurs passées pour générer les événements 'DOWN'. */

      /* Si l'entrée courante contient une valeur */
      if ( l_currentKey->button.state.value != 0 )
      {
         /* Pour le nombre d'entrées du clavier */
         for ( l_lastKey = p_keyboard->input; ( ( l_lastKey != K_MK_NULL ) && ( l_result == K_MK_OK ) ) ; l_lastKey = ( T_mkKey* ) l_lastKey->button.nextButton )
         {
            /* Si la touche est dans l'état 'Hold' */
            if ( l_currentKey->button.state.value == l_lastKey->button.state.lastValue )
            {
               /* Actualisation de la variable d'état */
               l_state = 1;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Si un événement de type 'DOWN' doit être généré */
         if ( l_state == 0 )
         {
            /* Gestion des indicateur lumineux du clavier */
            l_result = mk_dispatcher_handleIndicator ( p_handler, p_keyboard, l_currentKey );

            /* Récupération du code clavier courant */
            p_keyHandler->scancode = ( uint16_t ) l_currentKey->button.state.value;

            /* Initialisation de la variable permettant la temporisation du premier événement 'HOLD' */
            /* Lorsqu'un événement 'DOWN' survient, un événement 'HOLD' peut survenir au bout de K_MK_KEYBOARD_HOLD_EVENT_RATE ms */
            l_currentKey->button.tick.clickCount = p_handler->attribute.keyboardInhibitionDuration;

            /* Transmission d'un message de type 'DOWN' à la tâche d'écoute */
            l_result |= mk_dispatcher_postKeyEvent ( p_handler, p_message, p_keyboard, p_keyHandler, l_currentKey, K_MK_EVENT_CHAR_DOWN );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de la variable d'état */
         l_state = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_dispatcher_setKeyState ( T_mkKeyboard* p_keyboard )
{
   /* Déclaration des pointeurs de touches */
   T_mkKey *l_currentKey = p_keyboard->input;

   /* Pour le nombre d'entrées du clavier */
   for ( ; ( l_currentKey != K_MK_NULL ) ; l_currentKey = ( T_mkKey* ) l_currentKey->button.nextButton )
   {
      /* Actualisation des 'n' valeurs passées */
      l_currentKey->button.state.lastValue = l_currentKey->button.state.value;
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_translateKeyToEvent ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Le but de cette fonction est de comparer l'ancien et le nouveau 'Report'. */
   /* L'ancien 'Report' est stocké dans l'attribut 'lastValue' tandis que le nouveau est stocké dans l'attribut 'value'. */

   /* Lors de la comparaison, plusieurs situations peuvent se présenter : */

   /* - La valeur présente n'est égale à aucune des valeurs passées, un événement de type 'DOWN' doit être généré. */
   /* - La valeur passée est égale à une des valeurs présentes, un événement de type 'HOLD' doit être généré. */
   /* - La valeur passée n'est égale à aucune des valeurs présentes, un événement de type 'UP' doit être généré. */

   /* Génération des événements 'UP' ou 'DOWN' */
   l_result = mk_dispatcher_generateKeyUpHoldEvent ( p_handler, p_message, p_keyboard, p_keyHandler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Génération des événements 'DOWN' */
      l_result = mk_dispatcher_generateKeyDownEvent ( p_handler, p_message, p_keyboard, p_keyHandler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Le traitement est terminé, on actualise les valeurs passées avec les valeurs présentes. */
   mk_dispatcher_setKeyState ( p_keyboard );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleScancode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de touche */
   T_mkKey* l_key = p_keyboard->input;

   /* Réinitialisation de la variable stockant l'événement à générer */
   p_message->ctrlEvt = K_MK_EVENT_NO;

   /* Pour le nombre d'entrées du clavier et tant qu'aucune erreur ne s'est produite */
   for ( ; ( l_key != K_MK_NULL ) && ( p_message->ctrlEvt == K_MK_EVENT_NO ) ; l_key = ( T_mkKey* ) l_key->button.nextButton )
   {
      /* Dans la section ci-dessous, un événement d'erreur est envoyé à la tâche d'écoute si le clavier indique la présence */
      /* d'une anomalie interne. */

      /* Si une erreur de type POST_FAIL s'est produite */
      if ( l_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_POST_FAIL )
      {
         /* Configuration du type de message envoyé à la tâche d'écoute */
         p_message->ctrlEvt = K_MK_EVENT_KEY_POSTFAIL;
      }

      /* Sinon si une overflow s'est produite (le nombre de touche appuyé est supérieur au nombre d'entrées) */
      else if ( l_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_ERROR_ROLL_OVER )
      {
         /* Configuration du type de message envoyé à la tâche d'écoute */
         p_message->ctrlEvt = K_MK_EVENT_KEY_ROLLOVER;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si un message doit être envoyé à la tâche d'écoute */
      if ( p_message->ctrlEvt != K_MK_EVENT_NO )
      {
         /* Transmission d'un message */
         l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si aucune erreur ne s'est produite */
   if ( ( ( l_result == K_MK_OK ) && ( p_message->ctrlEvt == K_MK_EVENT_NO ) ) )
   {
      /* Gestion des événements de types 'UP', 'HOLD' et 'DOWN' */
      l_result = mk_dispatcher_translateKeyToEvent ( p_handler, p_message, p_keyboard, p_keyHandler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



