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
* @file mk_display_painter.c
* @brief Définition de la fonction mk_display_painter.
* @date 17 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_paint ( T_mkFactory* p_factory )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclararion d'un pointeur de champ */
   T_mkField* l_field;

   /* Si les fonctions de peinture doivent être exécutées */
   if ( g_mkDisplay.status.criticalLock == 0 )
   {
      /* Exécution des fonctions de peinture */
      l_result = mk_factory_paint ( p_factory, &l_field );
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

void mk_display_userPainter ( T_mkAddr p_unused )
{
   /* Cette fonction est la fonction de peinture non privilégiée. */
   /* Elle est déclenchée sur requête par la fonction de peinture privilégiée. */

   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField;

   /* Boucle tant qu'aucune erreur ne s'est produite */
   while ( l_result == K_MK_OK )
   {
      /* Attente du signal de réveil envoyé par la tâche de peinture privilégiée */
      l_result = mk_event_wait ( g_mkDisplay.painter.taskEvent, K_MK_EVENT_AND | K_MK_EVENT_CLEAR | K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_EVENT_FLAG,
            &l_eventField, K_MK_TASK_WAIT_FOREVER
      );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Les applications (getter/setter des objets) doivent être synchronisées avec les fonctions de peintures car */
         /* elles accédent la même ressource partagée. La tâche de peinture non privilégiée ne peut pas piloter */
         /* le sémaphore privilégié car elle ne possède pas les droits. */
         l_result = mk_semaphore_take ( g_mkDisplay.painter.unprivilegedSemaphore, K_MK_TASK_WAIT_FOREVER );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Exécution des fonctions de peinture non privilégiées */
            l_result = mk_display_paint ( &g_mkDisplay.unprivilegedFactory );

            /* Peu importe le statut d'erreur, il faut réveillée la tâche privilégiée */
            l_result |= mk_event_set ( g_mkDisplay.painter.taskEvent, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG );

            /* Libération du sémaphore de peinture non privilégié */
            l_result |= mk_semaphore_release ( g_mkDisplay.painter.unprivilegedSemaphore );
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

static void mk_display_handlePainter ( void )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField;

   /* Si la tâche de traitement des fonctions de peinture non privilégiées doit s'exécutée */
   if ( g_mkDisplay.status.painterLock == 0 )
   {
      /* Réveil de la tâche de peinture non privilégiée */
      l_result = mk_event_set ( g_mkDisplay.painter.taskEvent, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_EVENT_FLAG );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* On attend tant que les champs non privilégiés n'ont pas été dessiné */
         /* On ajoute un timeout de 10 secondes dans la situation d'un blocage sans fin. */
         l_result = mk_event_wait ( g_mkDisplay.painter.taskEvent, K_MK_EVENT_AND | K_MK_EVENT_CLEAR | K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG,
               &l_eventField, K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT
         );

         /* Si un timeout s'est produit */
         if ( l_result == K_MK_ERROR_TIMEOUT )
         {
            /* Le boucle des painters non privilégiés est bloquée */
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

   /* A ce stade, il est nécessaire d'exécuter les fonctions de peinture privilégiées */
   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Les applications (getter/setter des objets) et la tâche de gestion doivent être synchronisées avec les fonctions de peintures car */
      /* elles accédent la même ressource partagée. */
      l_result = mk_semaphore_take ( g_mkDisplay.painter.semaphore, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Exécution des fonctions de peinture privilégiées */
         l_result = mk_display_paint ( &g_mkDisplay.privilegedFactory );

         /* Dessin du container contenant les objets critiques */
         l_result |= mk_container_paint ( g_mkDisplay.criticalContainer, K_MK_NULL );

         /* Dessin du container contenant les objets de premier plan */
         /* Ce container contient le curseur de souris, il doit obligatoirement être dessiné en dernier */
         l_result |= mk_container_paint ( g_mkDisplay.frontendContainer, K_MK_NULL );

         /* Libération du sémaphore de peinture privilégié */
         l_result |= mk_semaphore_release ( g_mkDisplay.painter.semaphore );
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
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_painter ( T_mkAddr p_unused )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un champ d'événements */
   uint32_t l_eventField;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_ENGINE, { { K_MK_DISPLAY_REQUEST_TYPE_NEXT_FRAME, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Boucle pour toujours */
   while ( 1 )
   {
      /* Si un buffer graphique peut être rempli */
      if ( g_mkDisplay.pnt.currentBufferUsed != g_mkDisplay.pnt.currentBufferPrinted )
      {
         /* Rafraichissement des attributs de l'ensemble des objets présents dans les containers */
         mk_display_refreshFields ( );

         /* Désallocation des applications présente dans la liste des applications à supprimer */
         l_result = mk_application_delete ( );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si au moins un container est présent dans les factory */
            if ( ( g_mkDisplay.privilegedFactory.first != K_MK_NULL ) || ( g_mkDisplay.unprivilegedFactory.first != K_MK_NULL ) ||
                 ( g_mkDisplay.criticalContainer != K_MK_NULL ) )
            {
               /* Lancement des fonctions de peinture privilégiée et non privilégiée */
               mk_display_handlePainter ( );
            }

            /* Sinon */
            else
            {
               /* Réinitialisation du buffer de premier plan */
               l_result = mk_graphics_clear ( K_MK_GRAPHICS_FOREGROUND );
            }

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Actualisation du pointeur, on passe au prochain buffer graphique */
               g_mkDisplay.pnt.currentBufferUsed = g_mkDisplay.pnt.currentBufferUsed->next;

               /* On signale au gestionnaire d'événement que la frame courante a été dessinée. */
               l_result = mk_display_postRequest ( &l_request );
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
         /* La tâche de peinture s'exécute plus rapidement que la tâche de gestion des requêtes */
         /* On temporise son exécution le temps qu'un nouveau buffer se libère. */

         /* Signalisation de l'arrêt de la tâche */
         g_mkDisplay.status.wakeup = 1;

         /* Temporisation et attente du signal de réveil */
         l_result = mk_event_wait ( g_mkDisplay.painter.frameEvent, K_MK_EVENT_AND | K_MK_EVENT_CLEAR | K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG,
               &l_eventField, K_MK_TASK_WAIT_FOREVER
               );
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

   /* Suppression warning */
   ( void ) p_unused;

   /* Retour */
   return;
}



