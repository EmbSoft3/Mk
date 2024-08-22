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
* @file mk_application_release.c
* @brief Définition de la fonction mk_application_release.
* @date 16 août 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_removeContainers ( T_mkApplication* p_application, T_mkSemaphore* p_semaphore, T_mkFactory* p_factory )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkContainer* l_container = p_factory->first;

   /* Pour tous les containers présents dans la factory */
   while ( ( p_factory != K_MK_NULL ) && ( l_container != K_MK_NULL ) && ( l_result == K_MK_OK ) )
   {
      /* Si l'application est propriétaire du container */
      if ( l_container->owner == p_application )
      {
         /* Suppression des containers de la factory */
         l_result = mk_factory_remove ( p_semaphore, p_factory, l_container );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Passage au prochain container */
      l_container = l_container->next;
   }

   /* Retour */
   return ( l_result );
}


/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_release ( T_mkApplication* p_application )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_application != K_MK_NULL )
   {
      /* Libération des containers de la factory privilégiée */
      l_result = mk_application_removeContainers ( p_application, g_mkDisplay.painter.unprivilegedSemaphore, &g_mkDisplay.unprivilegedFactory );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Libération des containers de la factory non privilégiée */
         l_result = mk_application_removeContainers ( p_application, g_mkDisplay.painter.semaphore, &g_mkDisplay.privilegedFactory );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une page de mémoire graphique a été allouée */
      if ( ( l_result == K_MK_OK ) && ( p_application->page.gfxAddr != K_MK_NULL ) )
      {
         /* Libération de la mémoire */
         l_result |= mk_page_free ( K_MK_PAGE_ID_SDRAM, p_application->page.gfxAddr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une page de mémoire statique a été allouée */
      if ( ( l_result == K_MK_OK ) && ( p_application->page.memAddr != K_MK_NULL ) )
      {
         /* Libération de la mémoire */
         l_result |= mk_page_free ( K_MK_PAGE_ID_SRAM, p_application->page.memAddr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une page de mémoire de déploiement a été allouée */
      if ( ( l_result == K_MK_OK ) && ( p_application->page.deploymentAddr != K_MK_NULL ) )
      {
         /* Libération de la mémoire */
         l_result |= mk_application_free ( p_application->page.deploymentAddr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la tâche de l'application peut être détruite */
      if ( ( l_result == K_MK_OK ) && ( p_application->task.addr != K_MK_NULL ) && ( p_application == p_application->task.addr->owner ) &&
           ( p_application->task.addr->attribute.state != K_MK_STATE_DELETED ) )
      {
         /* Arrêt de la tâche dédiée à l'application */
         /* La désallocation des objets alloués par l'application est de la responsabilité de l'utilisateur. */
         l_result |= mk_task_terminate ( p_application->task.addr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( p_application->state == K_MK_APPLICATION_STATE_UNINSTALLED ) )
      {
         /* Réinitialisation du pointeur de tâche de l'application */
         p_application->task.addr = K_MK_NULL;

         /* Retrait de l'application de la liste des applications */
         mk_application_remove ( &g_mkDisplay.application.list, p_application );

         /* Si l'application est dynamique, on libère les bibliothèques externes déployées */
         l_result = mk_loader_flushLibraries ( &p_application->dynamic.libraries );

         /* Libération de l'application */
         l_result |= mk_pool_freeSafe ( g_mkDisplay.handler.applicationPool, p_application );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Emission d'un événement à destination du dispatcher. */
         /* On utilise l'application principale car le mécanisme d'identification est interne à la tâche. */
         l_result = mk_application_post ( g_mkDisplay.application.main, K_MK_EVENT_DELETE );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}





