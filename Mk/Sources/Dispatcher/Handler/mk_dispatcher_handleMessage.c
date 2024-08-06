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
* @file mk_dispatcher_handleMessage.c
* @brief Définition de la fonction mk_dispatcher_handleMessage.
* @date 18 nov. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleMessage ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération du type du contrôle */
   uint16_t* l_type = ( uint16_t* ) ( p_message->appCtrl );

   /* Si le paramètre est valide */
   if ( p_message != K_MK_NULL )
   {
      /* Si une structure de contrôle est rattachée à l'événement */
      if ( l_type != K_MK_NULL )
      {
         /* Si le contrôle est de type 'Mouse' */
         if ( ( *l_type ) == K_MK_CONTROL_MOUSE )
         {
            /* Traitement du contrôle de type 'Mouse' */
            l_result = mk_dispatcher_handleMouse ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Joystick' */
         else if ( ( *l_type ) == K_MK_CONTROL_JOYSTICK )
         {
            /* Gestion des événements en relation avec le contrôle de type 'Joystick' */
            l_result = mk_dispatcher_handleJoystick ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Keyboard' ou 'Keypad' */
         else if ( ( *l_type ) == K_MK_CONTROL_KEYBOARD )
         {
            /* Gestion des événements en relation avec le contrôle de type 'Keyboard' ou 'Keypad' */
            l_result = mk_dispatcher_handleKeyboard ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Consumer' */
         else if ( ( *l_type ) == K_MK_CONTROL_CONSUMER )
         {
            /* Gestion des événements en relation avec le contrôle de type 'Consumer' */
            l_result = mk_dispatcher_handleConsumer ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Disk' */
         else if ( ( *l_type ) == K_MK_CONTROL_DISK )
         {
            /* Gestion des événements en relation avec les disques */
            l_result = mk_dispatcher_handleDisk ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Volume' */
         else if ( ( *l_type ) == K_MK_CONTROL_VOLUME )
         {
            /* Gestion des événements en relation avec les partitions */
            l_result = mk_dispatcher_handleVolume ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'GPIO' */
         else if ( ( *l_type ) == K_MK_CONTROL_GPIO )
         {
            /* Gestion des événements en relation avec les broches d'entrée/sortie */
            l_result = mk_dispatcher_handleGpio ( p_handler, p_message );
         }

         /* Sinon si le contrôle est de type 'Application' */
         else if ( ( *l_type ) == K_MK_CONTROL_APPLICATION )
         {
            /* Gestion des événements en relation avec les applications */
            l_result = mk_dispatcher_handleApplication ( p_handler, p_message );
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
         /* Transmission d'un message à la tâche d'écoute */
         l_result = mk_dispatcher_postEvent ( p_handler, p_message, K_MK_NULL, K_MK_CONTROL_SYSTEM, 0 );
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


