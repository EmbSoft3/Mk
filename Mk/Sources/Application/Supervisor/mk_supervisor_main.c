/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_supervisor_main.c
* @brief Définition de la fonction mk_supervisor_main.
* @date 4 nov. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initHome ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un descripteur d'application */
   T_mkApplicationDescriptor l_applicationDescriptor = {
         K_MK_APPLICATION_TYPE_STATIC,       /* Application statique */
         K_MK_TYPE_FLOATING_PRIVILEGED,      /* Tâche flottante privilégiée. */
         K_MK_TRUE,                          /* Allocation d'une page mémoire graphique */
         K_MK_FALSE,                         /* Pas d'allocation de page mémoire standard */
         p_home->stack.buf,                  /* Adresse de la stack */
         K_MK_HOME_STACK_SIZE,               /* Taille de la stack. */
         mk_home_main,                       /* Point d'entrée de l'application */
         ( T_mkAddr ) p_home                 /* Argument de l'application */
   };

   /* Réinitialisation de la structure de l'application */
   _writeWords ( p_home, 0, sizeof ( T_mkHomeApplication ) >> 2 );

   /* Installation de l'application Home */
   l_result = mk_application_install ( &p_home->application, &l_applicationDescriptor, K_MK_NULL, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lancement de l'application */
      l_result = mk_application_launch ( p_home->application, K_MK_NULL );
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

static T_mkCode mk_supervisor_handleSystemFaults ( T_mkSupervisor* p_supervisor, T_mkSupervisorMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_currentApplication = K_MK_NULL;

   /* Si une exception s'est produite */
   if ( ( p_message->fault >= K_MK_SUPERVISOR_NMIFAULT ) && ( p_message->fault <= K_MK_SUPERVISOR_TASKFAULT ) )
   {
      /* Une erreur grave s'est produite */
      /* On cherche à suspendre la tâche qui a provoquée le défaut */

      /* Si la tâche est une tâche en relation avec le moteur graphique */
      if ( ( p_message->task == g_mkDisplay.painter.privilegedTask )  || ( p_message->task == g_mkDisplay.painter.unprivilegedTask )  ||
           ( p_message->task == g_mkDisplay.listener.privilegedTask ) || ( p_message->task == g_mkDisplay.listener.unprivilegedTask ) ||
           ( p_message->task == g_mkDisplay.handler.task ) )
      {
         /* Gestion de l'erreur */
         l_result = mk_display_handleEngineFaults ( p_message->task, p_message->fault );
      }

      /* Sinon */
      else
      {
         /* Si la tâche peut être suspendue */
         if ( ( p_message->task->attribute.state != K_MK_STATE_SUSPENDED ) && ( p_message->task->attribute.state != K_MK_STATE_DELETED ) )
         {
            /* Suspension de la tâche qui a provoqué le défaut */
            /* Action obligatoire pour ne pas provoquer une boucle d'interruption */
            l_result = mk_task_suspend ( p_message->task );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Suite à l'erreur, on ferme l'application courante et on lance l'application principale */
      /* Récupération de l'adresse de l'application courante */
      l_currentApplication = mk_application_getCurrent ( );

      /* Si l'application à fermer est différente de l'application principale */
      if ( l_currentApplication != mk_application_getMain ( ) )
      {
         /* Fermeture de l'application courante */
         l_result = mk_application_close ( l_currentApplication, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Si l'erreur s'est produite sur l'application principale, l'utilisateur va devoir redémarrer le système */
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Création d'un rapport dans le système de fichier */
         l_result = mk_supervisor_report ( p_supervisor, p_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si un blocage du rafraichissement graphique s'est produit */
   else if ( p_message->fault == K_MK_SUPERVISOR_TIMEOUTFAULT )
   {
      /* Création d'un rapport dans le système de fichier */
      l_result = mk_supervisor_report ( p_supervisor, p_message );
   }

   /* Sinon */
   else
   {
      /* On active le mode dégradé */
      /* La décision du redémarrage du système est de la responsabilité de l'utilisateur */
      mk_supervisor_recovery ( p_supervisor, K_MK_SUPERVISOR_ERROR_CODE30, K_MK_NULL, K_MK_NULL );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_supervisor_handleMessage ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task = K_MK_NULL;

   /* Déclaration d'un message */
   T_mkSupervisorMessage l_message;

   /* Boucle pour toujours */
   while ( l_result == K_MK_OK )
   {
      /* Attente tant qu'un message n'a pas été reçu dans la boite */
      l_result = mk_mail_pend ( &l_task, p_supervisor->message.mail, &l_message, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Gestion des erreurs systèmes */
         l_result = mk_supervisor_handleSystemFaults ( p_supervisor, &l_message );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Une erreur critique vient de se produire */
   /* L'intégrité du système n'est plus assurée. On active le mode dégradé */
   /* La décision du redémarrage du système est de la responsabilité de l'utilisateur */
   mk_supervisor_recovery ( p_supervisor, K_MK_SUPERVISOR_ERROR_CODE20, l_task, &l_message );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initAsciiArt ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Effacement de la console */
   l_result = mk_console_clean ( &p_supervisor->console );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      l_result  = mk_console_puts ( &p_supervisor->console, ( T_str8 ) "\nMkSoft for STM32746g-Eval2 board.\n");
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "Copyright (C) 2024 RENARD Mathieu. All rights reserved.\n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "This is free software; see the source for copying conditions.  There is NO\n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n" );

      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) " __  __ _     ____         __ _   \n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "|  \\/  | | __/ ___|  ___  / _| |_\n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "| |\\/| | |/ /\\___ \\ / _ \\| |_| __|\n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "| |  | |   <  ___) | (_) |  _| |_\n" );
      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "|_|  |_|_|\\_\\|____/ \\___/|_|  \\__|\n\n" );

      l_result |= mk_console_puts ( &p_supervisor->console, ( T_str8 ) "\nUse the help command to display the command set.\n" );
      l_result |= mk_console_print ( &p_supervisor->console, ( T_str8 ) "Loading ressources ...\n" );
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

void mk_supervisor_main ( T_mkAddr p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'adresse du superviseur */
   T_mkSupervisor* l_supervisor = ( T_mkSupervisor* ) p_addr;

   /* Initialisation des données du superviseur */
   l_result = mk_supervisor_init ( l_supervisor );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage du nom du système d'exploitation le temps que les */
      /* ressources de l'application home chargent */
      l_result = mk_supervisor_initAsciiArt ( l_supervisor );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Installation et lancement de l'application home */
         /* La désactivation du container critique est réalisé dans l'application home */
         l_result = mk_supervisor_initHome ( &g_mkHome );
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

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Mise en pause du superviseur tant qu'aucune erreur n'est détectée */
      mk_supervisor_handleMessage ( l_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* L'initialisation a échoué. */
   /* Activation du mode dégradé. */
   /* La décision du redémarrage du système est de la responsabilité de l'utilisateur */
   mk_supervisor_recovery ( l_supervisor, K_MK_SUPERVISOR_ERROR_CODE10, K_MK_NULL, K_MK_NULL );

   /* Retour */
   return;
}


