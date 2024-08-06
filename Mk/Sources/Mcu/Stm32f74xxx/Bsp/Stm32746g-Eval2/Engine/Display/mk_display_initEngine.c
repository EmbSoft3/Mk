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
* @file mk_display_initEngine.c
* @brief Définition de la fonction mk_display_initEngine.
* @date 17 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_initRegisters ( void )
{
   /* Initialisation du registre de statut du moteur graphique */
   g_mkDisplay.status.reserved = 0;
   g_mkDisplay.status.wakeup = 0;
   g_mkDisplay.status.painterLock = 0;
   g_mkDisplay.status.listenerLock = 0;
   g_mkDisplay.status.criticalLock = 0;

   /* Initialisation des variables de calcul du frameRate */
   g_mkDisplay.framerate.value = K_MK_DISPLAY_FRAMERATE;
   g_mkDisplay.framerate.period = 0;
   g_mkDisplay.framerate.counter = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_initFrameBuffers ( void )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Pour le nombre de buffers graphiques */
   for ( l_counter = 0 ; l_counter < K_MK_DISPLAY_FRAME_BUFFER_NUMBER ; l_counter++ )
   {
      /* Initialisation des attributs d'un buffer graphique */
      g_mkDisplay.frame [ l_counter ].validity = 0;
      g_mkDisplay.frame [ l_counter ].status.backgroundLayer = 0;
      g_mkDisplay.frame [ l_counter ].status.foregroundLayer = 0;
      g_mkDisplay.frame [ l_counter ].next = &g_mkDisplay.frame [ l_counter + 1 ];
      g_mkDisplay.frame [ l_counter ].addr [ K_MK_GRAPHICS_FOREGROUND ] = K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR + ( l_counter * K_MK_DISPLAY_FRAME_BUFFER_SIZE );
      g_mkDisplay.frame [ l_counter ].addr [ K_MK_GRAPHICS_BACKGROUND ] = K_MK_DISPLAY_FRAME_BUFFER_BANK2_BASE_ADDR + ( l_counter * K_MK_DISPLAY_FRAME_BUFFER_SIZE );
   }

   /* Rebouclage des buffers graphiques */
   g_mkDisplay.frame [ K_MK_DISPLAY_FRAME_BUFFER_NUMBER - 1 ].next = &g_mkDisplay.frame [ 0 ];

   /* Initialisation des pointeurs (cf. type \ref T_mkDisplayFramePointer) */
   g_mkDisplay.pnt.currentBufferPrinted = &g_mkDisplay.frame [ 0 ];
   g_mkDisplay.pnt.currentBufferUpdated = &g_mkDisplay.frame [ 1 ];
   g_mkDisplay.pnt.currentBufferUsed    = &g_mkDisplay.frame [ 1 ];

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_initScreen ( void )
{
   /* Configuration de la largeur et de la hauteur de l'écran */
   mk_display_setWidth ( K_MK_DISPLAY_WIDTH );
   mk_display_setHeight ( K_MK_DISPLAY_HEIGHT );

   /* Configuration de la taille des pixels des layers de premier et d'arrière plan. */
   /* L'arrière plan est au format ARGB888 pour réduire le flux de données nécessaires au périphérique LTDC. */
   g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_FOREGROUND ] = K_MK_DISPLAY_ARGB8888;
   g_mkDisplay.screen.bytesPerPixel [ K_MK_GRAPHICS_BACKGROUND ] = K_MK_DISPLAY_RGB888;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_initFactory ( void )
{
   /* Initialisation des factory */
   mk_factory_init ( &g_mkDisplay.privilegedFactory );
   mk_factory_init ( &g_mkDisplay.unprivilegedFactory );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_initContainer ( void )
{
   /* Allocation du container critique et du container de premier plan */
   g_mkDisplay.frontendContainer = mk_pool_alloc ( g_mkDisplay.handler.containerPool, K_MK_POOL_CLEAR );
   g_mkDisplay.criticalContainer = mk_pool_alloc ( g_mkDisplay.handler.containerPool, K_MK_POOL_CLEAR );

   /* Initialisation des containers alloués */
   mk_container_init ( g_mkDisplay.frontendContainer, K_MK_TYPE_PRIVILEGED );
   mk_container_init ( g_mkDisplay.criticalContainer, K_MK_TYPE_PRIVILEGED );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_initApplication ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des pointeurs du gestionnaire d'application */
   g_mkDisplay.application.current = K_MK_NULL;
   g_mkDisplay.application.main = K_MK_NULL;
   g_mkDisplay.application.list.first = K_MK_NULL;
   g_mkDisplay.application.list.last = K_MK_NULL;
   g_mkDisplay.application.list.deleted = K_MK_NULL;
   g_mkDisplay.application.numberOfInstalledApps = 0;
   g_mkDisplay.application.numberOfRunningApps = 0;

   /* Initialisation de la zone mémoire dédiée au gestionnaire d'allocation dynamique */
   l_result = mk_pool_initArea ( &g_mkDisplay.application.area, ( uint32_t* ) K_MK_DISPLAY_APPLICATION_START_ADDR, K_MK_DISPLAY_APPLICATION_MEMORY_SIZE >> 2 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique */
      l_result = mk_pool_create ( &g_mkDisplay.application.area, &g_mkDisplay.application.pool, K_MK_AREA_PROTECTED, K_MK_DISPLAY_APPLICATION_PAGE_SIZE >> 2,
                                  K_MK_DISPLAY_APPLICATION_MEMORY_SIZE / K_MK_DISPLAY_APPLICATION_PAGE_SIZE );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la zone mémoire dédiée au gestionnaire d'allocation dynamique */
      l_result = mk_pool_initArea ( &g_mkDisplay.application.deletedArea, ( T_mkApplicationGarbageItem* ) g_mkPrivilegedGarbageBuf, K_MK_DISPLAY_GARBAGE_APPLICATION_AREA_SIZE >> 2 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire d'allocation dynamique */
         l_result = mk_pool_create ( &g_mkDisplay.application.deletedArea, &g_mkDisplay.application.deletedPool, K_MK_AREA_PROTECTED, sizeof ( T_mkApplicationGarbageItem ) >> 2,
                                     K_MK_DISPLAY_APPLICATION_NUMBER );
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

static T_mkCode mk_display_initPainter ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Initialisation des objets synchronisant le gestionnaire de requêtes et les tâches de peinture */
   l_result = mk_semaphore_create ( &g_mkDisplay.painter.semaphore, K_MK_AREA_PROTECTED, 1, 0 );
   l_result |= mk_semaphore_create ( &g_mkDisplay.painter.unprivilegedSemaphore, K_MK_AREA_UNPROTECTED, 1, 0 );
   /* Initialisation de l'objet synchronisant la tâche de peinture privilégiée et l'interruption LTDC (Frame) */
   l_result |= mk_event_create ( &g_mkDisplay.painter.frameEvent, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );
   /* Initialisation de l'objet synchronisant les deux tâches de peinture (privilégiée et non privilégiée) */
   l_result |= mk_event_create ( &g_mkDisplay.painter.taskEvent, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_UNPROTECTED, 0 );

   /* Initialisation de la tâche de peinture privilégiée */
   /* Ecriture d'un pattern dans la stack de la tâche */
   _writeWords ( g_mkDisplay.painter.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE );
   /* Initialisation de la stack de peinture privilégiée */
   l_result |= mk_stack_create ( &g_mkDisplay.painter.privilegedStack, K_MK_TYPE_FLOATING, g_mkDisplay.painter.buf, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE );
   /* Initialisation du registre de contrôle de la tâche privilégiée */
   l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_PRIVILEGED_PAINTER, K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_PRIORITY, K_MK_NULL );
   /* Création de la tâche de peinture privilégiée */
   l_result |= mk_task_create ( &g_mkDisplay.painter.privilegedTask, &g_mkDisplay.painter.privilegedStack, K_MK_NULL, &l_taskCtrlBlock, mk_display_painter, K_MK_NULL );

   /* Initialisation de la tâche de peinture non privilégiée */
   /* Ecriture d'un pattern dans la stack de la tâche */
   _writeWords ( g_mkUnprivilegedPainterStackBuf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE );
   /* Initialisation de la stack de peinture non privilégiée */
   l_result |= mk_stack_create ( &g_mkDisplay.painter.unprivilegedStack, K_MK_TYPE_FLOATING, g_mkUnprivilegedPainterStackBuf, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE );
   /* Initialisation du registre de contrôle de la tâche non privilégiée */
   l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING, K_MK_TASK_ID_ENGINE_UNPRIVILEGED_PAINTER, K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_PRIORITY, K_MK_NULL );
   /* Création de la tâche de peinture non privilégiée */
   l_result |= mk_task_create ( &g_mkDisplay.painter.unprivilegedTask, &g_mkDisplay.painter.unprivilegedStack, K_MK_NULL, &l_taskCtrlBlock,
                                mk_display_userPainter, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_initListener ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre de contrôle */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Initialisation des objets synchronisant le gestionnaire de requêtes et les tâches d'écoute */
   l_result = mk_semaphore_create ( &g_mkDisplay.listener.semaphore, K_MK_AREA_PROTECTED, 1, 0 );
   l_result |= mk_semaphore_create ( &g_mkDisplay.listener.unprivilegedSemaphore, K_MK_AREA_UNPROTECTED, 1, 0 );
   /* Initialisation de l'objet synchronisant  les tâches d'écoute (privilégiée et non privilégiée) */
   l_result |= mk_event_create ( &g_mkDisplay.listener.taskEvent, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_UNPROTECTED, 0 );

   /* Initialisation de la tâche d'écoute privilégiée */
   /* Ecriture d'un pattern dans la stack de la tâche */
   _writeWords ( g_mkDisplay.listener.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE );
   /* Initialisation de la stack privilégiée de la tâche d'écoute */
   l_result |= mk_stack_create ( &g_mkDisplay.listener.privilegedStack, K_MK_TYPE_FLOATING, g_mkDisplay.listener.buf, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE );
   /* Initialisation du registre de contrôle de la nouvelle tâche */
   l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_PRIVILEGED_LISTENER, K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_PRIORITY, K_MK_NULL );
   /* Création de la tâche d'écoute privilégiée */
   l_result |= mk_task_create ( &g_mkDisplay.listener.privilegedTask, &g_mkDisplay.listener.privilegedStack, K_MK_NULL, &l_taskCtrlBlock, mk_display_listener, K_MK_NULL );

   /* Initialisation de la tâche d'écoute non privilégiée */
   /* Ecriture d'un pattern dans la stack de la tâche */
   _writeWords ( g_mkUnprivilegedListenerStackBuf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE );
   /* Initialisation de la stack non privilégié de la tâche d'écoute */
   l_result |= mk_stack_create ( &g_mkDisplay.listener.unprivilegedStack, K_MK_TYPE_FLOATING, g_mkUnprivilegedListenerStackBuf, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE );
   /* Initialisation du registre de contrôle de la nouvelle tâche */
   l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING, K_MK_TASK_ID_ENGINE_UNPRIVILEGED_LISTENER, K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_PRIORITY, K_MK_NULL );
   /* Création de la tâche d'écoute non privilégiée */
   l_result |= mk_task_create ( &g_mkDisplay.listener.unprivilegedTask, &g_mkDisplay.listener.unprivilegedStack, K_MK_NULL, &l_taskCtrlBlock, mk_display_userListener, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_initHandler ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Initialisation de l'objet de synchronisation entre le gestionnaire de requêtes et l'accélérateur graphique (chromart) */
   l_result = mk_event_create ( &g_mkDisplay.handler.event, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );
   /* Initialisation de la zone mémoire dédiées à la messagerie du gestionnaire de requêtes */
   l_result |= mk_pool_initArea ( &g_mkDisplay.handler.area, g_mkUnprivilegedHandlerMessageHeap, K_MK_DISPLAY_REQUEST_AREA_SIZE );
   /* Initialisation de la boite de messages du gestionnaire de requêtes. */
   l_result |= mk_mail_create ( &g_mkDisplay.handler.mail, K_MK_AREA_UNPROTECTED, &g_mkDisplay.handler.area, K_MK_DISPLAY_REQUEST_SIZE, K_MK_DISPLAY_REQUEST_NUMBER );

   /* Initialisation de la zone mémoire dédiées à l'allocation des containers */
   l_result |= mk_pool_initArea ( &g_mkDisplay.handler.containerArea, g_mkPrivilegedContainerBuf, K_MK_DISPLAY_CONTAINER_AREA_SIZE );
   /* Initialisation du gestionnaire d'allocation dynamique des containers */
   l_result |= mk_pool_create ( &g_mkDisplay.handler.containerArea, &g_mkDisplay.handler.containerPool, K_MK_AREA_PROTECTED, ( uint32_t ) ( sizeof ( T_mkContainer ) >> 2 ), K_MK_DISPLAY_CONTAINER_NUMBER );

   /* Initialisation de la zone mémoire dédiées à l'allocation des applications */
   l_result |= mk_pool_initArea ( &g_mkDisplay.handler.applicationArea, g_mkPrivilegedApplicationBuf, K_MK_DISPLAY_APPLICATION_AREA_SIZE );
   /* Initialisation du gestionnaire d'allocation dynamique des applications */
   l_result |= mk_pool_create ( &g_mkDisplay.handler.applicationArea, &g_mkDisplay.handler.applicationPool, K_MK_AREA_PROTECTED, ( uint32_t ) ( sizeof ( T_mkApplication ) >> 2 ), K_MK_DISPLAY_APPLICATION_NUMBER );

   /* Initialisation de la tâche du gestionnaire de requêtes */
   /* Ecriture d'un pattern dans la stack de la tâche */
   _writeWords ( g_mkDisplay.handler.buf, K_MK_TASK_STACK_PATTERN, K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE );
   /* Initialisation de la stack du gestionnaire de requêtes */
   l_result |= mk_stack_create ( &g_mkDisplay.handler.stack, K_MK_TYPE_FLOATING, g_mkDisplay.handler.buf, K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE );
   /* Initialisation du registre de contrôle de la nouvelle tâche */
   l_result |= mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, K_MK_TYPE_FLOATING_PRIVILEGED, K_MK_TASK_ID_ENGINE_HANDLER, K_MK_DISPLAY_TASK_HANDLER_PRIORITY, K_MK_NULL );
   /* Création de la tâche des gestion des requêtes */
   l_result |= mk_task_create ( &g_mkDisplay.handler.task, &g_mkDisplay.handler.stack, K_MK_NULL, &l_taskCtrlBlock, mk_display_handler, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_display_initEngine ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des objets et des tâches de peinture */
   l_result = mk_display_initPainter ( );

   /* Initialisation des objets et des tâches d'écoute */
   l_result |= mk_display_initListener ( );

   /* Initialisation du gestionnaire de requêtes */
   l_result |= mk_display_initHandler ( );

   /* Initialisation des registres du moteur graphique */
   mk_display_initRegisters ( );

   /* Initialisation des buffers graphiques */
   mk_display_initFrameBuffers ( );

   /* Configuration des dimensions de l'écran */
   mk_display_initScreen ( );

   /* Initialisation des factory */
   mk_display_initFactory ( );

   /* Initialisation des containers */
   mk_display_initContainer ( );

   /* Initialisation des registres des applications */
   mk_display_initApplication ( );

   /* Initialisation des polices de caractères par défaut */
   mk_font_initDefault ( );

   /* Initialisation du matériel du moteur */
   mk_display_init ( );

   /* Initialisation de l'accélérateur graphique */
   mk_display_initChromArt ( );

   /* Retour */
   return ( l_result );
}


