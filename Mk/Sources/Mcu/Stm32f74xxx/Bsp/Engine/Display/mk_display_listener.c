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
* @file mk_display_listener.c
* @brief Définition de la fonction mk_display_listener.
* @date 18 nov. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_getDispatcherChild ( T_mkDispatcherHandler** p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un champ d'événements */
   uint32_t l_event = 0;

   /* Attente de la fin de l'initialisation du dispatcher. */
   l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_DISPATCHER, &l_event, K_MK_TASK_WAIT_FOREVER );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération de l'adresse du dispatcher */
      l_result = mk_termio_getChild ( g_mkTermioHandler.dispatcher, ( void** ) p_handler );
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

static void mk_display_handleFocus ( T_mkMouse* p_mouse, T_mkField* p_field, T_mkCtrlEvent p_mainEvtCtrl )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_currentState;

   /* Analyse de la position du curseur par rapport au champ */
   l_currentState = mk_field_inside ( p_field, p_mouse->axis.x, p_mouse->axis.y );

   /* Si un clic s'est produit  */
   if ( p_mainEvtCtrl == K_MK_EVENT_CLICK )
   {
      /* Si le clic s'est produite dans le champ et si le champ n'est pas déjà sélectionné */
      if ( ( p_field->focus == K_MK_FIELD_STATE_IDLE ) && ( l_currentState == 1 ) )
      {
         /* Le champ gagne le focus */
         mk_field_setFocus ( p_field, K_MK_FIELD_STATE_FOCUS );
      }

      /* Sinon si le clic s'est produit à l'extérieur du champ et si le champ en cours d'analyse a le focus */
      else if ( ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) && ( l_currentState == 0 ) )
      {
         /* Le champ perd le focus */
         mk_field_setFocus ( p_field, K_MK_FIELD_STATE_IDLE );
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

   /* Si le champ en cours d'analyse a le focus et si ce champ est devenu invisible */
   if ( ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) && ( p_field->visibility == K_MK_FIELD_INVISIBLE ) )
   {
      /* Le champ perd le focus */
      mk_field_setFocus ( p_field, K_MK_FIELD_STATE_IDLE );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_handleSystemMessage ( T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si un événement en relation avec une souris s'est produit */
   if ( p_message->appCtrlID == K_MK_CONTROL_MOUSE )
   {
      /* Gestion des événements primaires de type 'Mouse' */
      l_result = mk_hid_mouse_handleEvents ( ( T_mkMouse* ) p_message->appCtrl, g_mkDisplay.frontendContainer, p_message->ctrlEvt );
   }

   /* Sino si un événement en relation avec un joystick s'est produit */
   else if ( p_message->appCtrlID == K_MK_CONTROL_JOYSTICK )
   {
      /* Gestion des événements primaires de type 'Joystick' */
      l_result = mk_hid_joystick_handleEvents ( ( T_mkJoystick* ) p_message->appCtrl, p_message->ctrlEvt );
   }

   /* Sinon si un événement en relation avec un clavier s'est produit */
   else if ( p_message->appCtrlID == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion des événements primaires de type 'Keyboard' */
      l_result = mk_hid_keyboard_handleEvents ( ( T_mkKeyboard* ) p_message->appCtrl, p_message->ctrlEvt );
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

static T_mkCode mk_display_handleSubEvents ( T_mkContainer* p_container, T_mkField* p_field, T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un événement */
   T_mkCtrlEvent l_subEvent;

   /* Si un événement en relation avec une souris s'est produit */
   if ( p_message->appCtrlID == K_MK_CONTROL_MOUSE )
   {
      /* Configuration de l'événement à analyser */
      l_subEvent = K_MK_EVENT_ENTER;

      /* Gestion des événements secondaires de la souris */
      l_result = mk_hid_mouse_handleSubEvents ( ( T_mkMouse* ) p_message->appCtrl, p_field, ( T_mkCtrlEvent ) p_message->ctrlEvt, &l_subEvent );

      /* Si un événement de type 'ENTER' a été détecté */
      if ( ( l_result == K_MK_OK ) && ( l_subEvent == K_MK_EVENT_ENTER ) )
      {
         /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
         l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_ENTER, ( uint32_t ) p_message->ctrlId );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de l'événement à analyser */
         l_subEvent = K_MK_EVENT_EXIT;

         /* Gestion des événements secondaires de la souris */
         l_result = mk_hid_mouse_handleSubEvents ( ( T_mkMouse* ) p_message->appCtrl, p_field, ( T_mkCtrlEvent ) p_message->ctrlEvt, &l_subEvent );

         /* Si un événement de type 'EXIT' a été détecté */
         if ( ( l_result == K_MK_OK ) && ( l_subEvent == K_MK_EVENT_EXIT ) )
         {
            /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
            l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_EXIT, ( uint32_t ) p_message->ctrlId );
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

      /* Si pas d'erreur, événement de type 'Press' et champ sélectionné */
      if ( ( l_result == K_MK_OK ) && ( p_message->ctrlEvt == K_MK_EVENT_PRESS ) && ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) )
      {
         /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
         l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_XPRESS, ( uint32_t ) p_message->ctrlId );
      }

      /* Sinon si pas d'erreur, événement de type 'Release' et champ sélectionné */
      else if ( ( l_result == K_MK_OK ) && ( p_message->ctrlEvt == K_MK_EVENT_RELEASE ) && ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) )
      {
         /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
         l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_XRELEASE, ( uint32_t ) p_message->ctrlId );
      }

      /* Sinon si pas d'erreur, événement de type 'Click' et champ sélectionné */
      else if ( ( l_result == K_MK_OK ) && ( p_message->ctrlEvt == K_MK_EVENT_CLICK ) && ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) )
      {
         /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
         l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_XCLICK, ( uint32_t ) p_message->ctrlId );
      }

      /* Sinon si pas d'erreur, événement de type 'DoubleClick' et champ sélectionné */
      else if ( ( l_result == K_MK_OK ) && ( p_message->ctrlEvt == K_MK_EVENT_DOUBLE_CLICK ) && ( p_field->focus == K_MK_FIELD_STATE_FOCUS ) )
      {
         /* Exécution de la fonction d'écoute du champ pour signaler l'événement */
         l_result = p_field->listener ( p_container, p_field, p_message->appCtrlID, p_message->appCtrl, K_MK_EVENT_DOUBLE_XCLICK, ( uint32_t ) p_message->ctrlId );
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

static T_mkCode mk_display_listenContainer ( T_mkContainer* p_container, T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkField* l_tmp = p_container->first;

   /* Pour tous les champs présents dans le container */
   while ( ( l_tmp != K_MK_NULL ) && ( l_result == K_MK_OK) )
   {
      /* Si un évènment en relation avec une souris s'est produit */
      if ( p_message->appCtrlID == K_MK_CONTROL_MOUSE )
      {
         /* Gestion du focus des champs */
         mk_display_handleFocus ( ( T_mkMouse* ) p_message->appCtrl, l_tmp, ( T_mkCtrlEvent ) p_message->ctrlEvt );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le champ possède une fonction d'écoute  */
      if ( ( l_tmp->listener != K_MK_NULL ) && ( l_tmp->activity == K_MK_FIELD_ACTIF ) )
      {
         /* Génération, analyse puis traitement des sous-événements spécifiques aux champs */
         l_result = mk_display_handleSubEvents ( p_container, l_tmp, p_message );

         /* Traitement de l'événement principal */
         l_result |= l_tmp->listener ( p_container, l_tmp, p_message->appCtrlID, p_message->appCtrl, p_message->ctrlEvt, ( uint32_t ) p_message->ctrlId );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Passage au prochain champ */
      l_tmp = l_tmp->next;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_listenCritical ( T_mkContainer* p_container, T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si un listener est associé au container */
   if ( p_container->listener != K_MK_NULL )
   {
      /* Exécution du listener dédié au container */
      l_result = p_container->listener ( p_container, K_MK_NULL, p_message->appCtrlID, p_message->appCtrl, p_message->ctrlEvt, ( uint32_t ) p_message->ctrlId );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Exécution des fonctions d'écoute de l'ensemble des champs présent dans le container */
      l_result = mk_display_listenContainer ( g_mkDisplay.criticalContainer, p_message );
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

static T_mkCode mk_display_listenFactory ( T_mkFactory* p_factory, T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkContainer* l_tmp = p_factory->first;

   /* Si les fonctions d'écoutes doivent être exécutées */
   if ( g_mkDisplay.status.criticalLock == 0 )
   {
      /* Pour tous les containers présents dans la factory */
      while ( ( l_result == K_MK_OK )  && ( l_tmp != K_MK_NULL )  )
      {
         /* Si un listener est associé au container */
         if ( l_tmp->listener != K_MK_NULL )
         {
            /* Exécution du listener du container */
            l_result = l_tmp->listener ( l_tmp, K_MK_NULL, p_message->appCtrlID, p_message->appCtrl, p_message->ctrlEvt, ( uint32_t ) p_message->ctrlId );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage au prochain container */
         l_tmp = l_tmp->next;
      }

      /* Réinitialisation de la variable de travail */
      l_tmp = p_factory->first;

      /* Pour tous les containers présents dans la factory */
      while ( ( l_result == K_MK_OK )  && ( l_tmp != K_MK_NULL )  )
      {
         /* Dessin de l'ensemble des container présent dans la factory */
         l_result = mk_display_listenContainer ( l_tmp, p_message );

         /* Passage au prochain container */
         l_tmp = l_tmp->next;
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

static T_mkCode mk_display_listenPrivilegedFactory ( T_mkListenerMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField;

   /* Les applications (getter/setter des objets) doivent être synchronisées avec les fonctions d'écoutes car */
   /* elles accédent la même ressource partagée. La tâche non privilégiée ne peut pas piloter */
   /* le sémaphore privilégié car elle ne possède pas les droits. */
   l_result = mk_semaphore_take ( g_mkDisplay.listener.semaphore, K_MK_TASK_WAIT_FOREVER );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Dessin de l'ensemble des containers présents dans la liste critique */
      l_result = mk_display_listenCritical ( g_mkDisplay.criticalContainer, p_message );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Dessin de la factory privilégiées */
         l_result = mk_display_listenFactory ( &g_mkDisplay.privilegedFactory, p_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Libération du sémaphore */
      l_result |= mk_semaphore_release ( g_mkDisplay.listener.semaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la tâche de traitement des fonctions d'écoute non privilégiés doit s'exécutée */
      if ( g_mkDisplay.status.listenerLock == 0 )
      {
         /* Réveil de la tâche d'écoute non privilégiée */
         l_result = mk_event_set ( g_mkDisplay.listener.taskEvent, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_EVENT_FLAG );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* On attend tant que les champs non privilégiés n'ont pas été dessiné */
            /* On ajoute un timeout de 10 secondes dans la situation d'un blocage sans fin */
            l_result = mk_event_wait ( g_mkDisplay.listener.taskEvent, K_MK_EVENT_AND | K_MK_EVENT_CLEAR | K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_EVENT_FLAG,
                  &l_eventField, K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT
            );

            /* Si un timeout s'est produit */
            if ( l_result == K_MK_ERROR_TIMEOUT )
            {
               /* Le boucle des painter non privilégiés est bloquée */
               /* On bascule les flags de statut à 1 pour désactiver l'éxécution des painters et des listeners non privilégiés */
               /* La liste doit être purgée pour réactiver l'exécution de ceux-ci. */
               g_mkDisplay.status.painterLock = 1 ;
               g_mkDisplay.status.listenerLock = 1 ;

               /* Suspension des tâches de dessin et d'écoute non privilégiées */
               l_result = mk_task_suspend ( g_mkDisplay.painter.unprivilegedTask );
               l_result |= mk_task_suspend ( g_mkDisplay.listener.unprivilegedTask );

               /* On avertie l'utilisateur qu'une erreur s'est produite */
               l_result |= mk_display_reportTimeout ( );
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

void mk_display_userListener ( T_mkAddr p_unused )
{
   /* Cette fonction est la fonction d'écoute non privilégiée. */
   /* Elle est déclenchée sur requête par la fonction d'écoute privilégiée. */

   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField;

   /* Boucle tant qu'aucune erreur ne s'est produite */
   while ( l_result == K_MK_OK )
   {
      /* Attente du signal de réveil envoyé par la tâche d'écoute privilégiée */
      l_result = mk_event_wait ( g_mkDisplay.listener.taskEvent, K_MK_EVENT_AND | K_MK_EVENT_CLEAR | K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_EVENT_FLAG,
            &l_eventField, K_MK_TASK_WAIT_FOREVER
      );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Les applications (getter/setter des objets) doivent être synchronisées avec les fonctions d'écoutes car */
         /* elles accédent la même ressource partagée. La tâche non privilégiée ne peut pas piloter */
         /* le sémaphore privilégié car elle ne possède pas les droits. */
         l_result = mk_semaphore_take ( g_mkDisplay.listener.unprivilegedSemaphore, K_MK_TASK_WAIT_FOREVER );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Dessin de la factory non privilégiée */
            l_result = mk_display_listenFactory ( &g_mkDisplay.unprivilegedFactory, &g_mkDisplay.listenerMessage );

            /* Libération du sémaphore */
            l_result |= mk_semaphore_release ( g_mkDisplay.listener.unprivilegedSemaphore );

            /* Peu importe le statut d'erreur, il faut réveillée la tâche privilégiée */
            l_result |= mk_event_set ( g_mkDisplay.listener.taskEvent, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_EVENT_FLAG );
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

   /* Une erreur grave vient de se produire */
   /* La gestion de l'erreur est de la responsabilité du superviseur. */
   ( void ) mk_display_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Suppression warning */
   ( void ) ( p_unused );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_listener ( T_mkAddr p_unused )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un gestionnaire de message */
   T_mkDispatcherHandler* l_dispatcherHandler = K_MK_NULL;

   /* On attend tant que le dispatcher n'est pas initialisé */
   l_result = mk_display_getDispatcherChild ( &l_dispatcherHandler );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_dispatcherHandler != K_MK_NULL ) )
   {
      /* Boucle pour toujours */
      while ( 1 )
      {
         /* Analyse de la boite de message pour savoir si un message est disponible */
         l_result = mk_mail_pend ( K_MK_NULL, l_dispatcherHandler->listenerArea->mail, ( T_mkAddr ) &g_mkDisplay.listenerMessage, K_MK_TASK_WAIT_FOREVER );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Gestion des événements du système */
            l_result = mk_display_handleSystemMessage ( &g_mkDisplay.listenerMessage );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Transmission de l'événement à toutes les fonctions d'écoute de la factory privilégiée */
               l_result = mk_display_listenPrivilegedFactory ( &g_mkDisplay.listenerMessage );
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

         /* Si une erreur s'est produite */
         if ( l_result != K_MK_OK )
         {
            /* Une erreur grave vient de se produire */
            /* La gestion de l'erreur est de la responsabilité du superviseur. */
            ( void ) mk_display_report ( l_result );
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
      /* Ne rien faire */
   }

   /* Une erreur grave vient de se produire */
   /* La gestion de l'erreur est de la responsabilité du superviseur. */
   ( void ) mk_display_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Suppression warning */
   ( void ) p_unused;

   /* Retour */
   return;
}

