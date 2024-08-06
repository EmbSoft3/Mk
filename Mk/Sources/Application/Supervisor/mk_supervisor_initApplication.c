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
* @file mk_supervisor_initApplication.c
* @brief Définition de la fonction mk_supervisor_initApplication.
* @date 4 janv. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_initApplication ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un registre de contrôle */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Déclaration d'un descripteur d'application */
   T_mkApplicationDescriptor l_applicationDescriptor = {
         K_MK_APPLICATION_TYPE_STATIC,             /* Application statique */
         K_MK_TYPE_FLOATING_PRIVILEGED,            /* Tâche flottante privilégiée. */
         K_MK_FALSE,                               /* Allocation d'une page mémoire graphique */
         K_MK_FALSE,                               /* Pas d'allocation de page mémoire standard */
         g_mkSupervisor.stack.buf,                 /* Adresse de la stack */
         K_MK_SUPERVISOR_APPLICATION_STACK_SIZE,   /* Taille de la stack. */
         mk_supervisor_main,                       /* Point d'entrée de l'application */
         ( T_mkAddr ) &g_mkSupervisor              /* Argument de l'application */
   };

   /* Réinitialisation des données du superviseur */
   _writeWords ( &g_mkSupervisor, 0, sizeof ( T_mkSupervisor ) >> 2 );

   /* Ecriture d'un pattern dans la stack du superviseur */
   _writeWords ( g_mkSupervisor.stack.buf, K_MK_TASK_STACK_PATTERN, K_MK_SUPERVISOR_APPLICATION_STACK_SIZE );

   /* Initialisation de l'application */
   l_result = mk_application_init ( &g_mkSupervisor.application, &l_applicationDescriptor, K_MK_TASK_ID_SUPERVISOR, K_MK_SUPERVISOR_TASK_PRIORITY );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la stack de l'application principale */
      l_result = mk_stack_create ( &g_mkSupervisor.application.task.stack, g_mkSupervisor.application.descriptor.taskType,
                                   g_mkSupervisor.application.descriptor.stackAddr, g_mkSupervisor.application.descriptor.stackSize );

      /* Si la stack a correctement été initialisée */
      if ( l_result == K_MK_OK )
      {
         /* Configuration du registre de contrôle de la nouvelle tâche */
         /* L'attribut 'owner' de l'application 'supervisor' doit être nul afin que l'attribut 'owner' des ces tâches enfants soit nul. */
         /* Lorsque le gestionnaire du moteur graphique (handler) créé une nouvelle application, la propriété de celle-ci est alors correctement */
         /* attribuée. C'est le paramètre 'owner' présent dans le TCB qui est utilisé et non pas le paramètre owner de la tâche. */
         l_result = mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, g_mkSupervisor.application.descriptor.taskType,
                                               g_mkSupervisor.application.task.identifier, g_mkSupervisor.application.task.priority, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Création de la tâche principale dédiée à l'application */
         l_result = mk_task_create ( &g_mkSupervisor.application.task.addr, &g_mkSupervisor.application.task.stack, K_MK_NULL, &l_taskCtrlBlock,
                                     g_mkSupervisor.application.descriptor.entryPoint, g_mkSupervisor.application.descriptor.arg );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Modification de l'état de la tâche */
         g_mkSupervisor.application.state = K_MK_APPLICATION_STATE_RUNNING;
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


