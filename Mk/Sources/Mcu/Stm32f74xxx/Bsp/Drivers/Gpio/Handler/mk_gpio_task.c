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
* @file mk_gpio_task.c
* @brief Définition de la fonction mk_gpio_task.
* @date 20 déc. 2020
* @todo Libérer la mémoire allouée par le terminal à la destruction de celui-ci.
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_gpio_init ( void )
{
   /* Initialisation de la broche MMC_DETECT (K_MK_GPIO_SDCARD_DETECT) */
   gpio_setMode  ( K_GPIOC, K_GPIO_INPUT, 13 );
   gpio_speed    ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 13 );
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_UP, 13 );

   /* Initialisation de la broche B_USER (K_MK_GPIO_USER_PUSHBUTTON) */
   gpio_setMode  ( K_GPIOI, K_GPIO_INPUT, 11 );
   gpio_speed    ( K_GPIOI, K_GPIO_MEDIUM_SPEED, 11 );
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_OFF, 11 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_dispatchGpioMessage ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   T_mkDispatcherHandler* l_dispatcherHandler = K_MK_NULL;
   T_mkDispatcherMessage  l_message;

   /* Récupération de l'adresse du dispatcher */
   l_result = mk_termio_getChild ( g_mkTermioHandler.dispatcher, ( void** ) &l_dispatcherHandler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration du message */
      l_message.appCtrl = ( T_mkAddr ) &p_handler->ctrl;
      l_message.ctrlEvt = K_MK_EVENT_NO;
      l_message.tick = mk_getTick ( );

      /* Etant donné que la priorité du dispatcher est supérieure à la priorité de la tâche GPIO, les informations */
      /* du contrôle peuvent être transmise par référence. Il n'est pas nécessaire de transmettre une copie. */

      /* Transmission d'un message au dispatcher */
      l_result = mk_mail_post ( l_dispatcherHandler->mailArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
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

static T_mkCode mk_gpio_initGPIOHandler ( T_mkTermio* p_termio, T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Réinitialisation du gestionnaire GPIO */
   _writeWords ( p_handler, 0, sizeof ( T_mkGPIOHandler ) >> 2 );

   /* Configuration de la structure de données du terminal */
   l_result = mk_termio_setChild ( p_termio, ( T_mkGPIOHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire GPIO */
      l_result = mk_gpio_initHandler ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission d'un événement pour signaler la fin de l'initialisation du terminal GPIO */
         l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_GPIO );
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

static T_mkCode mk_gpio_handleCallback ( T_mkTask* p_task, T_mkGPIOMessage* p_message, T_mkCode p_code )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Si une fonction de rappel a été configurée */
   if ( p_message->callback != K_MK_NULL )
   {
      /* Configuration des arguments de la fonction de rappel */
      l_callbackParams.param1 = ( T_mkAddr ) p_code;

      /* Déclenchement de la fonction de rappel */
      l_result = mk_callback_trig ( p_message->callback->handler, p_message->callback, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Récupération du niveau de privilège de la zone mémoire */
      l_area = _mk_memory_isPrivilegedArea ( ( T_mkAddr ) p_message->result );

      /* Si la tâche émettrice de la requête possède un niveau de droits suffisants  */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         *p_message->result = p_code;
      }

      /* Si la tâche est suspendue */
      if ( p_task->attribute.state == K_MK_STATE_SUSPENDED )
      {
         /* Réactivation de la tâche */
         l_result = mk_task_resume ( p_task );
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

static T_mkCode mk_gpio_handleEvent ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task;

   /* Déclaration d'un message */
   T_mkGPIOMessage l_message;

   /* Tant qu'aucune erreur non critique ne s'est produite */
   while ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_TIMEOUT ) || ( l_result == K_MK_ERROR_COMM ) )
   {
      /* Lecture des broches GPIO qui doivent générer un événement */
      p_handler->ctrl.currentEvent  = ( gpio_get ( K_GPIOC, 13 ) << K_MK_GPIO_SDCARD_DETECT ) ;
      p_handler->ctrl.currentEvent |= ( gpio_get ( K_GPIOI, 11 ) << K_MK_GPIO_USER_PUSHBUTTON ) ;

      /* Si un changement d'état s'est produit */
      if ( p_handler->ctrl.currentEvent != p_handler->ctrl.lastEvent )
      {
         /* Transmission d'un événement au dispatcher */
         l_result = mk_gpio_dispatchGpioMessage ( p_handler );

         /* Actualisation de la valeur du registre */
         p_handler->ctrl.lastEvent = p_handler->ctrl.currentEvent;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Analyse de la messagerie afin de récupérer les requêtes envoyées par l'utilisateur */
      l_result = mk_mail_pend ( &l_task, p_handler->requestArea->request, ( T_mkAddr ) &l_message, K_MK_GPIO_REQUEST_TIMEOUT );

      /* Si une requête est disponible */
      if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
      {
         /* Traitement de la requête */
         l_result = mk_gpio_handleRequest ( l_task, p_handler, &l_message, l_message.requestIdentifier );

         /* Gestion et déclenchement de la fonction de rappel si nécessaire */
         l_result |= mk_gpio_handleCallback ( l_task, &l_message, l_result );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Attente 10 ms (modulo la durée passée à attendre la requête) */
      l_result |= mk_task_delay ( K_MK_GPIO_REQUEST_TIMEOUT );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_gpio_task ( T_mkAddr p_param )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = ( T_mkTermio* ) p_param;

   /* Déclaration d'un gestionnaire de périphérique GPIO */
   T_mkGPIOHandler l_handler;

   /* Initialisation des broches GPIO */
   mk_gpio_init ( );

   /* Initialisation du gestionnaire GPIO */
   l_result = mk_gpio_initGPIOHandler ( l_termio, &l_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Gestion des événements du terminal */
      l_result = mk_gpio_handleEvent ( &l_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Le résultat de la fonction n'est pas vérifié car l'intégrité du système n'est plus garantie. */
   /* Une erreur grave vient de se produire */
   /* La destruction du terminal est de la responsabilité du superviseur. */
   ( void ) mk_termio_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Retour */
   return;
}
