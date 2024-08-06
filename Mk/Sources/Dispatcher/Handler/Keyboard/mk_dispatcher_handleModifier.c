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
* @file mk_dispatcher_handleModifier.c
* @brief Définition de la fonction mk_dispatcher_handleModifier.
* @date 30 déc. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCtrlEvent mk_dispatcher_setKeyEvent ( T_mkDispatcherHandler* p_dispatcher, T_mkListenerMessage* p_message, T_mkKeyCode* p_key )
{
   /* Déclaration de la variable de retour */
   T_mkCtrlEvent l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_timeout;

   /* Si un modificateur est positionné */
   if ( p_key->state.value != 0 )
   {
      /* Si un événement de type 'DOWN' doit être généré */
      if ( ( p_key->state.lastEvent == 0 ) || ( p_key->state.lastEvent == K_MK_EVENT_KEY_UP ) )
      {
         /* Initialisation de la variable permettant la temporisation du premier événement 'HOLD' */
         /* Lorsqu'un événement 'DOWN' survient, un événement 'HOLD' peut survenir au bout de K_MK_KEYBOARD_HOLD_EVENT_RATE ms */
         p_key->tick.clickCount = p_dispatcher->attribute.keyboardInhibitionDuration;

         /* Mémorisation du type d'événement généré */
         l_result = K_MK_EVENT_KEY_DOWN;
      }

      /* Sinon */
      else
      {
         /* Les 'Reports' sont retournés par le clavier à intervalle régulier ou lorsqu'une touche change d'état. */
         /* Afin d'éviter le spam de ces événements, on temporise leurs transmissions. */
         l_timeout = mk_utils_tick ( p_key->tick.pressTick, p_message->tick );

         /* Si un événement de type 'Hold' doit être généré */
         if ( l_timeout >= p_key->tick.clickCount )
         {
            /* Désactivation de l'inhibition des événements 'HOLD' */
            p_key->tick.clickCount = p_dispatcher->attribute.keyboardHoldRate;

            /* Mémorisation du type d'événement généré */
            l_result = K_MK_EVENT_KEY_HOLD;
         }

         /* Sinon */
         else
         {
            /* Le timeout d'inhibition des événements 'Hold' n'est pas dépassé, aucun événement ne doit être */
            /* généré. */
            l_result = K_MK_EVENT_NO;
         }
      }
   }

   /* Sinon */
   else
   {
      /* Configuration du type d'événement généré */
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

T_mkCode mk_dispatcher_handleModifier ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de touche */
   T_mkKeyCode* l_key = p_keyboard->modifier;

   /* Pour le nombre de modificateur du clavier */
   for ( ; ( l_key != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_key = l_key->nextButton )
   {
      /* Si un changement d'état s'est produit */
      if ( l_key->state.value != l_key->state.lastValue )
      {
         /* Actualisation de l'état précédent */
         l_key->state.lastValue = l_key->state.value;

         /* Configuration du type de message à générer */
         l_key->state.lastEvent = mk_dispatcher_setKeyEvent ( p_handler, p_message, l_key );

         /* Dans le cas d'un modificateur, aucune information n'est fournie à l'utilisateur. */
         /* Enregistrement de l'adresse de la structure de sortie */
         p_keyboard->output = K_MK_NULL;

         /* Configuration du message envoyé aux fonction d'écoute */
         p_message->ctrlEvt = l_key->state.lastEvent;

         /* Configuration de l'identifiant du modificateur */
         p_message->ctrlId  = ( uint16_t ) ( ( 256 << ( l_key->layer.id & 0x7 ) ) );

         /* Transmission d'un message */
         l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) p_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si un modificateur est positionné et si aucune erreur critique ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_key->state.value != 0 ) )
      {
         /* Création d'un champ de bits à partir de l'état des modificateurs. Ce champ de bit est utilisé pour déterminer */
         /* si l'utilisateur a entré une commande ou un caractère affichable */
         p_keyHandler->modifier = ( uint16_t ) ( p_keyHandler->modifier | ( 1 << ( l_key->layer.id & 0x7 ) ) );

         /* Si au moins un modificateur désignant une commande est actif */
         if ( ( p_keyHandler->modifier & K_MK_KEYBOARD_USER_COMMAND ) != 0 )
         {
            /* Actualisation de la variable indiquant qu'une commande a été entrée par l'utilisateur */
            /* Si plus d'un modificateur est validé alors l'algorithme considère qu'une commande est entrée. */
            p_keyHandler->cmd = 1;
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

   /* Retour */
   return ( l_result );
}



