/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_display_handleFaults.c
* @brief Définition de la fonction mk_display_handleFaults.
* @date 31 mars 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_restartUnprivilegedPainter ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Destruction de la tâche de dessin non privilégiée */
   l_result = mk_task_terminate ( g_mkDisplay.painter.unprivilegedTask );

   /* Si aucune erreur ne s'est produite, on essaye de relancer la tâche */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture d'un pattern dans la stack de la tâche */
      _writeWords ( g_mkUnprivilegedPainterStackBuf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE );

      /* Initialisation de la stack non privilégiée appartenant à la tâche de peinture */
      l_result = mk_stack_create ( &g_mkDisplay.painter.unprivilegedStack, K_MK_TYPE_FLOATING, g_mkUnprivilegedPainterStackBuf,
                                    K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE );

      /* Configuration du registre de contrôle de la tâche non privilégiée */
      l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING, K_MK_TASK_ID_ENGINE_UNPRIVILEGED_PAINTER, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_PRIORITY, K_MK_NULL );

      /* Création de la tâche de peinture non privilégiée */
      l_result |= mk_task_create ( &g_mkDisplay.painter.unprivilegedTask, &g_mkDisplay.painter.unprivilegedStack, K_MK_NULL, &l_taskCtrlBlock,
                                   mk_display_userPainter, K_MK_NULL );
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

static T_mkCode mk_display_restartPrivilegedPainter ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Destruction de la tâche de peinture privilégiée */
   l_result = mk_task_terminate ( g_mkDisplay.painter.privilegedTask );

   /* Si aucune erreur ne s'est produite, on essaye de relancer la tâche */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture d'un pattern dans la stack de la tâche */
      _writeWords ( g_mkDisplay.painter.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE );

      /* Initialisation de la stack privilégiée appartenant à la tâche de peinture */
      l_result = mk_stack_create ( &g_mkDisplay.painter.privilegedStack, K_MK_TYPE_FLOATING, g_mkDisplay.painter.buf,
                                    K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE );

      /* Configuration du registre de contrôle de la tâche privilégié */
      l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_PRIVILEGED_PAINTER, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_PRIORITY, K_MK_NULL );

      /* Création de la tâche de peinture privilégiée */
      l_result |= mk_task_create ( &g_mkDisplay.painter.privilegedTask, &g_mkDisplay.painter.privilegedStack, K_MK_NULL, &l_taskCtrlBlock,
                                   mk_display_painter, K_MK_NULL );
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

static T_mkCode mk_display_restartUnprivilegedListener ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Destruction de la tâche d'écoute non privilégiée */
   l_result = mk_task_terminate ( g_mkDisplay.listener.unprivilegedTask );

   /* Si aucune erreur ne s'est produite, on essaye de relancer la tâche */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture d'un pattern dans la stack de la tâche */
      _writeWords ( g_mkUnprivilegedListenerStackBuf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE );

      /* Initialisation de la stack non privilégié de la tâche d'écoute */
      l_result = mk_stack_create ( &g_mkDisplay.listener.unprivilegedStack, K_MK_TYPE_FLOATING, g_mkUnprivilegedListenerStackBuf,
                                    K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE );

      /* Configuration du registre de contrôle de la nouvelle tâche */
      l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING, K_MK_TASK_ID_ENGINE_UNPRIVILEGED_LISTENER, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_PRIORITY, K_MK_NULL );

      /* Création de la tâche d'écoute non privilégiée */
      l_result |= mk_task_create ( &g_mkDisplay.listener.unprivilegedTask, &g_mkDisplay.listener.unprivilegedStack, K_MK_NULL, &l_taskCtrlBlock,
                                   mk_display_userListener, K_MK_NULL );
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

static T_mkCode mk_display_restartPrivilegedListener ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Destruction de la tâche non privilégiée */
   l_result = mk_task_terminate ( g_mkDisplay.listener.privilegedTask );

   /* Si aucune erreur ne s'est produite, on essaye de relancer la tâche */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture d'un pattern dans la stack de la tâche */
      _writeWords ( g_mkDisplay.listener.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE );

      /* Initialisation de la stack privilégiée de la tâche d'écoute */
      l_result = mk_stack_create ( &g_mkDisplay.listener.privilegedStack, K_MK_TYPE_FLOATING, g_mkDisplay.listener.buf,
                                    K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE );

      /* Configuration du registre de contrôle de la nouvelle tâche */
      l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_PRIVILEGED_LISTENER, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_PRIORITY, K_MK_NULL );

      /* Création de la tâche d'écoute privilégiée */
      l_result |= mk_task_create ( &g_mkDisplay.listener.privilegedTask, &g_mkDisplay.listener.privilegedStack, K_MK_NULL, &l_taskCtrlBlock,
                                   mk_display_listener, K_MK_NULL );
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

static T_mkCode mk_display_restartHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Destruction de tâche de gestion des requêtes */
   l_result = mk_task_terminate ( g_mkDisplay.handler.task );

   /* Si aucune erreur ne s'est produite, on essaye de relancer la tâche */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture d'un pattern dans la stack de la tâche */
      _writeWords ( g_mkDisplay.handler.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE );

      /* Initialisation de la stack du gestionnaire de requête */
      l_result = mk_stack_create ( &g_mkDisplay.handler.stack, K_MK_TYPE_FLOATING, g_mkDisplay.handler.buf,
                                    K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE );

      /* Configuration du registre de contrôle de la nouvelle tâche */
      l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_HANDLER, K_MK_DISPLAY_TASK_HANDLER_PRIORITY, K_MK_NULL );

      /* Création de la tâche de gestion des requêtes */
      l_result |= mk_task_create ( &g_mkDisplay.handler.task, &g_mkDisplay.handler.stack, K_MK_NULL, &l_taskCtrlBlock,
                                   mk_display_handler, K_MK_NULL );
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

static T_mkCode mk_display_handleUnprivilegedPainterFault ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réveil de la tâche de peinture privilégiée */
   l_result = mk_event_set ( g_mkDisplay.painter.taskEvent, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Redémarrage de la tâche de peinture non privilégiée */
      l_result = mk_display_restartUnprivilegedPainter ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Libération du sémaphore non privilégié */
      l_result |= mk_semaphore_release ( g_mkDisplay.painter.unprivilegedSemaphore );
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

static T_mkCode mk_display_handleUnprivilegedListenerFault ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Reveille de la tâche d'écoute privilégiée */
   l_result = mk_event_set ( g_mkDisplay.listener.taskEvent, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_EVENT_FLAG );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Redémarrage de la tâche d'écoute non privilégié */
      l_result = mk_display_restartUnprivilegedListener ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Libération du sémaphore non privilégié */
      l_result = mk_semaphore_release ( g_mkDisplay.listener.unprivilegedSemaphore );
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

static T_mkCode mk_display_reinitObjects ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation des objets de synchronisation du moteur graphique */
   l_result  = mk_semaphore_delete ( g_mkDisplay.painter.semaphore );
   l_result |= mk_semaphore_create ( &g_mkDisplay.painter.semaphore, K_MK_AREA_PROTECTED, 1, 0 );
   l_result |= mk_semaphore_delete ( g_mkDisplay.painter.unprivilegedSemaphore );
   l_result |= mk_semaphore_create ( &g_mkDisplay.painter.unprivilegedSemaphore, K_MK_AREA_UNPROTECTED, 1, 0 );
   l_result |= mk_event_delete ( g_mkDisplay.painter.taskEvent );
   l_result |= mk_event_create ( &g_mkDisplay.painter.taskEvent, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_UNPROTECTED, 0 );
   l_result |= mk_semaphore_delete ( g_mkDisplay.listener.semaphore );
   l_result |= mk_semaphore_create ( &g_mkDisplay.listener.semaphore, K_MK_AREA_PROTECTED, 1, 0 );
   l_result |= mk_semaphore_delete ( g_mkDisplay.listener.unprivilegedSemaphore );
   l_result |= mk_semaphore_create ( &g_mkDisplay.listener.unprivilegedSemaphore, K_MK_AREA_UNPROTECTED, 1, 0 );
   l_result |= mk_event_delete ( g_mkDisplay.listener.taskEvent );
   l_result |= mk_event_create ( &g_mkDisplay.listener.taskEvent, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_UNPROTECTED, 0 );
   l_result |= mk_event_delete ( g_mkDisplay.handler.event );
   l_result |= mk_event_create ( &g_mkDisplay.handler.event, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );
   l_result |= mk_pool_initArea ( &g_mkDisplay.handler.area, g_mkUnprivilegedHandlerMessageHeap, K_MK_DISPLAY_REQUEST_AREA_SIZE );
   l_result |= mk_mail_delete ( g_mkDisplay.handler.mail );
   l_result |= mk_mail_create ( &g_mkDisplay.handler.mail, K_MK_AREA_UNPROTECTED, &g_mkDisplay.handler.area, K_MK_DISPLAY_REQUEST_SIZE, K_MK_DISPLAY_REQUEST_NUMBER );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_handlePrivilegedFault ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation des objets du moteur graphique */
   l_result = mk_display_reinitObjects ( );

   /* Redémarrage de l'ensemble des tâches du noyau */
   l_result |= mk_display_restartHandler ( );
   l_result |= mk_display_restartPrivilegedPainter ( );
   l_result |= mk_display_restartPrivilegedListener ( );
   l_result |= mk_display_restartUnprivilegedPainter ( );
   l_result |= mk_display_restartUnprivilegedListener ( );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_display_handleEngineFaults ( T_mkTask* p_task, uint32_t p_fault )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si l'erreur est en relation avec la tâche de dessin non privilégiée */
   if ( p_task == g_mkDisplay.painter.unprivilegedTask )
   {
      /* Redémarrage de la tâche de dessin non privilégiée */
      l_result = mk_display_handleUnprivilegedPainterFault ( );
   }

   /* Sinon si l'erreur est en relation avec la tâche d'écoute non privilégiée */
   else if ( p_task == g_mkDisplay.listener.unprivilegedTask )
   {
      /* Redémarrage de la tâche d'écoute non privilégiée */
      l_result = mk_display_handleUnprivilegedListenerFault ( );
   }

   /* Sinon si l'erreur est en relation avec une tâche privilégiée */
   else
   {
      /* Dans la situation où l'erreur est localisée dans le gestionnaire de requêtes ou */
      /* dans une des tâches privilégiée, on ferme toute les applications en cours d'exécution */
      /* puis on relance le moteur graphique. */
      l_result = mk_display_handlePrivilegedFault ( );
   }

   /* Suppression warning */
   ( void ) p_fault;

   /* Retour */
   return ( l_result );
}

