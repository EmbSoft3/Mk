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
* @file mk_dispatcher_handleGpio.c
* @brief Définition de la fonction mk_dispatcher_handleGpio.
* @date 22 déc. 2020
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_handleGpioEvent ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkGPIOCtrl* p_gpio )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_counter, l_lastValue = 0, l_currentValue = 0;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Configuration du message de sortie */
   l_message.appCtrlID = K_MK_CONTROL_GPIO;           /* Identifiant du contrôle applicatif */
   l_message.appCtrl   = p_gpio;                      /* Adresse du contrôle applicatif */
   l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

   /* Pour le nombre d'entrées à analyser */
   for ( l_counter = 0 ; l_counter < MK_GPIO_EXPANDER_NUMBER_OF_PINS ; l_counter++ )
   {
      /* Configuration de l'identifiant du contrôle */
      l_message.ctrlId = ( uint16_t ) l_counter;

      /* Récupération de la valeur des entrées courante et passé */
      l_lastValue = ( uint32_t ) ( ( p_gpio->expander.last >> l_counter ) & 0x1 );
      l_currentValue = ( uint32_t ) ( ( p_gpio->expander.current >> l_counter ) & 0x1 );

      /* Si l'entrée concerne le joystick */
      if ( l_counter <= K_MK_EXPANDER_JOYSTICK_UP )
      {
         /* Si l'entrée a changée d'état */
         if ( l_lastValue != l_currentValue )
         {
            /* Si l'état de la broche est différent de l'état de repos */
            if ( l_currentValue != g_expanderSettingTable [ l_counter ] [ 3 ] )
            {
               /* Configuration de l'identifiant de l'événement à générer (PRESS ou RELEASE) */
               l_message.ctrlEvt = K_MK_EVENT_PRESS;
            }

            /* Sinon */
            else
            {
               /* Configuration de l'identifiant de l'événement à générer (PRESS ou RELEASE) */
               l_message.ctrlEvt = K_MK_EVENT_RELEASE;
            }

            /* Transmission d'un message à la tâche d'écoute */
            l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si l'entrée concerne la carte SD */
      else if ( l_counter == K_MK_EXPANDER_SDCARD_DETECT )
      {
         /* Si l'entrée a changée d'état */
         if ( l_lastValue != l_currentValue )
         {
            /* Si l'état de la broche est différent de l'état de repos */
            if ( l_currentValue != g_expanderSettingTable [ l_counter ] [ 3 ] )
            {
               /* Configuration de l'identifiant de l'événement à générer (K_MK_EVENT_CONNECT) */
               l_message.ctrlEvt = K_MK_EVENT_CONNECT;
            }

            /* Sinon */
            else
            {
               /* Configuration de l'identifiant de l'événement à générer (K_MK_EVENT_DISCONNECT) */
               l_message.ctrlEvt = K_MK_EVENT_DISCONNECT;
            }

            /* Transmission d'un message à la tâche d'écoute */
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

T_mkCode mk_dispatcher_handleGpio ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de contrôle */
   T_mkGPIOCtrl* l_gpio = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_message != K_MK_NULL ) && ( p_message->appCtrl != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du contrôle */
      l_gpio = p_message->appCtrl;

      /* Si un événement a été configuré */
      if ( p_message->ctrlEvt != K_MK_EVENT_NO )
      {
         /* Transmission d'un message à la tâche d'écoute */
         l_result = mk_dispatcher_postEvent ( p_handler, p_message, l_gpio, K_MK_CONTROL_GPIO, l_gpio->layer.id );
      }

      /* Sinon */
      else
      {
         /* Gestion des événements en relation avec les GPIO */
         l_result = mk_dispatcher_handleGpioEvent ( p_handler, p_message, l_gpio );
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



