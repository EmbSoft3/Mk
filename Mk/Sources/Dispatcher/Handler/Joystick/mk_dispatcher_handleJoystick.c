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
* @file mk_dispatcher_handleJoystick.c
* @brief Définition de la fonction mk_dispatcher_handleJoystick.
* @date 25 avr. 2020
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_handleJoystickButton ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkJoystick* p_joystick )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du premier bouton du joystick */
   T_mkButton* l_button = p_joystick->button;

   /* Traitement des boutons du joystick */
   while ( ( l_result == K_MK_OK ) && ( l_button != K_MK_NULL ) )
   {
      /* Génération des événements en relation avec le bouton  */
      l_result = mk_dispatcher_handleButton ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_JOYSTICK, ( T_mkAddr ) p_joystick, ( T_mkAddr ) l_button );

      /* Passage au prochain contrôle */
      l_button = l_button->nextButton;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleJoystick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de joystick */
   T_mkJoystick* l_joystick = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_message != K_MK_NULL ) && ( p_message->appCtrl != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du controle */
      l_joystick = p_message->appCtrl;

      /* Si un événement a été configuré */
      if ( p_message->ctrlEvt != K_MK_EVENT_NO )
      {
         /* Transmission d'un message à la tâche d'écoute */
         l_result = mk_dispatcher_postEvent ( p_handler, p_message, l_joystick, K_MK_CONTROL_JOYSTICK, l_joystick->layer.id );
      }

      /* Sinon */
      else
      {
         /* Génération des événements relatifs au contrôle */
         l_result = mk_dispatcher_handleJoystickButton ( p_handler, p_message, l_joystick );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Génération des événements relatifs aux sticks du joystick */
            l_result = mk_dispatcher_handleStick ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_JOYSTICK, ( T_mkAddr ) l_joystick, ( T_mkAddr ) &l_joystick->stick );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Génération des événements relatifs aux interrupteurs du joystick. */
               l_result = mk_dispatcher_handleHatSwitch ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_JOYSTICK, ( T_mkAddr ) l_joystick, ( T_mkAddr ) &l_joystick->hatSwitch );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Génération des événements relatifs aux manettes du joystick */
                  l_result = mk_dispatcher_handleThrottle ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_JOYSTICK, ( T_mkAddr ) l_joystick, ( T_mkAddr ) &l_joystick->throttle );
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


