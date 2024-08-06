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
* @file mk_application_handleRequest.c
* @brief Définition de la fonction mk_application_handleRequest.
* @date 17 août 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_checkInstance ( T_mkApplicationRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Déclaration d'une variable de travail */
   uint32_t l_modulo = 0;

   /* Si l'instance de l'application est valide */
   if ( ( l_application != K_MK_NULL ) &&
      ( ( l_application >=  ( T_mkApplication* ) &g_mkPrivilegedApplicationBuf [0] ) &&
        ( l_application < ( ( T_mkApplication* ) &g_mkPrivilegedApplicationBuf [0] + K_MK_DISPLAY_APPLICATION_NUMBER ) ) ) )
   {
      /* Vérification de l'alignement de l'adresse */
      l_modulo = _math_mod ( ( uint32_t ) l_application - ( uint32_t ) &g_mkPrivilegedApplicationBuf[0], sizeof ( T_mkApplication ) );

      /* Si l'adresse est alignée */
      if ( l_modulo == 0 )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_OK;
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

static T_mkCode mk_application_handleInstallRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_id = 0;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = K_MK_NULL;

   /* Vérification de la validité de l'instance de retour */
   uint32_t l_area = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_request->application ) );

   /* Si l'instance de la variable de retour est située en dehors de la zone non protégée et si la tâche */
   /* qui a transmis le message est de type non privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le paramètre "application" est valide */
      if ( ( l_result == K_MK_OK ) && ( p_request->application != K_MK_NULL ) )
      {
         /* Allocation d'une nouvelle application */
         /* L'adresse d'un pointeur est envoyée dans la requête */
         l_result = mk_pool_allocSafe ( g_mkDisplay.handler.applicationPool, ( T_mkAddr* ) p_request->application, K_MK_POOL_CLEAR, 0 );

         /* Récupération de l'adresse de l'application allouée */
         l_application = * ( T_mkApplication** ) p_request->application;

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_application != K_MK_NULL ) )
         {
            /* Détermination de la valeur de l'identifiant unique de l'application */
            l_id = K_MK_DISPLAY_APPLICATION_BASE_ID + ( uint32_t ) ( l_application - ( T_mkApplication* ) &g_mkPrivilegedApplicationBuf [ 0 ] );

            /* Si la tâche qui a exécutée la requête n'est pas privilégiée */
            if ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == 0 )
            {
               /* Configuration du type de l'application (le type privilégié est supprimé) */
               p_request->content.descriptor.taskType &= ( uint8_t ) ( ~K_MK_TYPE_PRIVILEGED );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Réinitialisation de l'application allouée */
            _writeWords ( l_application, 0, sizeof ( T_mkApplication ) >> 2 );

            /* Si l'application est de type dynamique */
            if ( p_request->content.path != K_MK_NULL )
            {
               /* Déploiement de l'application en mémoire */
               l_result = mk_application_loadDynamic ( l_application, p_request, l_id );
            }

            /* Sinon */
            else
            {
               /* Initialisation d'une application de type statique */
               l_result = mk_application_init ( l_application, &p_request->content.descriptor, l_id, K_MK_DISPLAY_APPLICATION_DEFAULT_PRIORITY );

               /* Si des métadonnées sont présentes */
               if ( p_request->content.addr != K_MK_NULL )
               {
                  /* Configuration des métadonnées */
                  _copy ( &l_application->metadata, p_request->content.addr, sizeof ( T_mkApplicationMetadata ) );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ajout de la nouvelle application dans la liste */
               mk_application_add ( &g_mkDisplay.application.list, l_application );

               /* Actualisation du compteur d'applications */
               g_mkDisplay.application.numberOfInstalledApps = ( uint32_t ) ( g_mkDisplay.application.numberOfInstalledApps + 1 );
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
            /* Emission d'un événement à destination du dispatcher. */
            l_result = mk_application_post ( l_application, K_MK_EVENT_INSTALL );
         }

         /* Sinon */
         else
         {
            /* Une erreur s'est produite, on libère la mémoire de l'application */
            l_result |= mk_pool_freeSafe ( g_mkDisplay.handler.applicationPool, l_application );
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Configuration de l'argument de la fonction de rappel */
      p_callbackParam->param2 = l_application;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_handleLaunchRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un TCB de tâche */
   T_mkTaskCtrlBlock l_taskCtrlBlock;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si les paramètres sont valides */
      if ( ( p_request->application->state == K_MK_APPLICATION_STATE_INSTALLED ) &&
         ( ( ( uint32_t ) p_request->application->descriptor.stackAddr & 0x3 ) == 0 ) )
      {
         /* Ecriture d'un pattern dans la stack de l'application */
         _writeWords ( p_request->application->descriptor.stackAddr, K_MK_TASK_STACK_PATTERN, p_request->application->descriptor.stackSize );

         /* Initialisation de la stack de l'application principale */
         l_result = mk_stack_create ( &p_request->application->task.stack, p_request->application->descriptor.taskType,
                                      p_request->application->descriptor.stackAddr, p_request->application->descriptor.stackSize );

         /* Si la stack a correctement été initialisée */
         if ( l_result == K_MK_OK )
         {
            /* Configuration du registre de contrôle de la nouvelle tâche */
            l_result = mk_task_setTaskCtrlBlock ( &l_taskCtrlBlock, p_request->application->descriptor.taskType,
                                                  p_request->application->task.identifier, p_request->application->task.priority, p_request->application );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite et si une page mémoire graphique doit être allouée */
         if ( ( l_result == K_MK_OK ) && ( p_request->application->descriptor.gfxPage == K_MK_TRUE ) )
         {
            /* Allocation d'une page mémoire graphique */
            l_result = mk_page_alloc ( K_MK_PAGE_ID_SDRAM, &p_request->application->page.gfxAddr, 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite et si une page mémoire standard doit être allouée */
         if ( ( l_result == K_MK_OK ) && ( p_request->application->descriptor.memPage == K_MK_TRUE ) )
         {
            /* Allocation d'une page mémoire standard */
            l_result = mk_page_alloc ( K_MK_PAGE_ID_SRAM, &p_request->application->page.memAddr, 0 );
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
            l_result = mk_task_create ( &p_request->application->task.addr, &p_request->application->task.stack, K_MK_NULL, &l_taskCtrlBlock,
                                        p_request->application->descriptor.entryPoint, p_request->application->descriptor.arg );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation du compteur d'application */
            g_mkDisplay.application.numberOfRunningApps = ( uint32_t ) ( g_mkDisplay.application.numberOfRunningApps + 1 );

            /* Modification de l'état de l'application */
            p_request->application->state = K_MK_APPLICATION_STATE_RUNNING;

            /* Si aucune application n'a été lancée */
            if ( g_mkDisplay.application.main == K_MK_NULL )
            {
               /* La nouvelle application devient l'application principale */
               g_mkDisplay.application.main = p_request->application;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si l'application n'est pas une application d'arrière plan */
            if ( ( p_request->application->descriptor.type & K_MK_APPLICATION_TYPE_DAEMON ) != K_MK_APPLICATION_TYPE_DAEMON )
            {
               /* La nouvelle application devient l'application courante */
               g_mkDisplay.application.current = p_request->application;
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

         /* Si une erreur s'est produite et si une page de mémoire graphique a été allouée */
         if ( ( l_result != K_MK_OK ) && ( p_request->application->page.gfxAddr != K_MK_NULL ) )
         {
            /* Libération de la mémoire allouée */
            l_result = mk_page_free ( K_MK_PAGE_ID_SDRAM, p_request->application->page.gfxAddr );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si une erreur s'est produite et si une page de mémoire standard a été allouée */
         if ( ( l_result != K_MK_OK ) && ( p_request->application->page.memAddr != K_MK_NULL ) )
         {
            /* Libération de la mémoire allouée */
            l_result = mk_page_free ( K_MK_PAGE_ID_SRAM, p_request->application->page.memAddr );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Configuration de l'argument de la fonction de rappel */
         p_callbackParam->param2 = p_request->application;

         /* Si aucune erreur s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Emission d'un événement à destination du dispatcher. */
            l_result = mk_application_post ( p_request->application, K_MK_EVENT_LAUNCH );
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
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_handleUninstallRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Ajout de l'application dans la liste des applications à supprimer */
      l_result = mk_application_addDeletedList ( l_application, K_MK_DISPLAY_APPLICATION_ELAPSE_TIMEOUT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si le compteur des applications lancées n'est pas nul et si l'application était en cours de fonctionnement */
         if ( ( g_mkDisplay.application.numberOfRunningApps != 0 ) && ( l_application->state == K_MK_APPLICATION_STATE_RUNNING ) )
         {
            /* Actualisation du compteur d'application */
            g_mkDisplay.application.numberOfRunningApps = ( uint32_t ) ( g_mkDisplay.application.numberOfRunningApps - 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le compteur des applications créées n'est pas nul */
         if ( g_mkDisplay.application.numberOfInstalledApps != 0 )
         {
            /* Actualisation du compteur d'application */
            g_mkDisplay.application.numberOfInstalledApps = ( uint32_t ) ( g_mkDisplay.application.numberOfInstalledApps - 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si l'application était l'application courante */
         if ( g_mkDisplay.application.current == l_application )
         {
            /* L'application principale devient l'application courante */
            g_mkDisplay.application.current = g_mkDisplay.application.main;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Modification de l'état de la tâche */
         l_application->state = K_MK_APPLICATION_STATE_UNINSTALLED;

         /* Emission d'un événement à destination du dispatcher. */
         l_result = mk_application_post ( l_application, K_MK_EVENT_UNINSTALL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Configuration de l'argument de la fonction de rappel */
      p_callbackParam->param2 = K_MK_NULL;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_handleTerminateRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      if ( ( l_result == K_MK_OK ) && ( l_application->task.addr != K_MK_NULL ) && ( l_application == l_application->task.addr->owner ) &&
           ( l_application->task.addr->attribute.state != K_MK_STATE_DELETED ) )
      {
         /* Arrêt de la tâche dédiée à l'application */
         /* La désallocation des objets alloués par l'application est de la responsabilité de l'utilisateur. */
         l_result = mk_task_terminate ( l_application->task.addr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Réinitialisation du pointeur de tâche de l'application */
         l_application->task.addr = K_MK_NULL;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Configuration de l'argument de la fonction de rappel */
      p_callbackParam->param2 = K_MK_NULL;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_application_handleCloseRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si l'application était l'application courante */
      if ( g_mkDisplay.application.current == l_application )
      {
         /* L'application principale devient l'application courante */
         g_mkDisplay.application.current = g_mkDisplay.application.main;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Ajout de l'application dans la liste des applications à supprimer */
      l_result = mk_application_addDeletedList ( l_application, K_MK_DISPLAY_APPLICATION_ELAPSE_TIMEOUT );

      /* Configuration de l'argument de la fonction de rappel */
      p_callbackParam->param2 = K_MK_NULL;

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Modification de l'état de la tâche */
         l_application->state = K_MK_APPLICATION_STATE_INSTALLED;

         /* Si le compteur des applications lancées n'est pas nul */
         if ( g_mkDisplay.application.numberOfRunningApps != 0 )
         {
            /* Actualisation du compteur d'application */
            g_mkDisplay.application.numberOfRunningApps = ( uint32_t ) ( g_mkDisplay.application.numberOfRunningApps - 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Emission d'un événement à destination du dispatcher. */
         l_result = mk_application_post ( l_application, K_MK_EVENT_CLOSE );
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

static T_mkCode mk_application_handleMetadataRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le paramètre est valide */
      if ( p_request->content.addr != K_MK_NULL )
      {
         /* Copie des métadonnées */
         _copy ( &l_application->metadata, p_request->content.addr, sizeof ( T_mkApplicationMetadata ) );

         /* Configuration de l'argument de la fonction de rappel */
         p_callbackParam->param2 = l_application;

         /* Emission d'un événement à destination du dispatcher. */
         l_result = mk_application_post ( l_application, K_MK_EVENT_METADATA );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
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

static T_mkCode mk_application_handleAttributeRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = p_request->application;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si l'application */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( ( l_application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le paramètre est valide */
      if ( p_request->content.addr != K_MK_NULL )
      {
         /* Copie des attributs dans l'application */
         _copy ( &l_application->attribute, p_request->content.addr, sizeof ( T_mkDispatcherAttributes ) );

         /* Chargement des attributs dans le dispatcher */
         l_result = mk_application_loadDispatcherInputs ( l_application );

         /* Configuration de l'argument de la fonction de rappel */
         p_callbackParam->param2 = l_application;
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
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

T_mkCode mk_application_handleRequest ( T_mkTask* p_task, T_mkApplicationRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams = { 0 };

   /* Si la requête est de type APPLICATION_INSTALL */
   if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_INSTALL )
   {
      /* Gestion de la requête de création d'une application  */
      l_result = mk_application_handleInstallRequest ( p_task, p_request, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Vérification de l'instance de l'application */
      l_result = mk_application_checkInstance ( p_request );

      /* Si les paramètres sont valides */
      if ( l_result == K_MK_OK )
      {
         /* Si la requête est de type APPLICATION_UNINSTALL */
         if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_UNINSTALL )
         {
            /* Gestion de la requête de desinstallation d'une application */
            l_result = mk_application_handleUninstallRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type APPLICATION_LAUNCH */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_LAUNCH )
         {
            /* Gestion de la requête de lancement d'une application */
            l_result = mk_application_handleLaunchRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type K_MK_DISPLAY_REQUEST_APPLICATION_CLOSE */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_CLOSE )
         {
            /* Gestion de la requête de fermeture d'une application */
            l_result = mk_application_handleCloseRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type K_MK_DISPLAY_REQUEST_APPLICATION_TERMINATE */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_TERMINATE )
         {
            /* Gestion de la requête de destruction de la tâche d'une application */
            l_result = mk_application_handleTerminateRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type APPLICATION_ATTRIBUTE */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_ATTRIBUTE )
         {
            /* Gestion de la requête de configuration des attributs d'une application (dispatcher) */
            l_result = mk_application_handleAttributeRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type APPLICATION_METADATA */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_APPLICATION_METADATA )
         {
            /* Gestion de la requête de configuration des métadonnées d'une application */
            l_result = mk_application_handleMetadataRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si une fonction de rappel a été configurée */
   if ( p_request->callback != K_MK_NULL )
   {
      /* Configuration du résultat */
      /* Les autres arguments sont configurés dans les fonctions propres à chaque requête */
      l_callbackParams.param1 = ( T_mkAddr ) l_result;

      /* Déclenchement de la fonction de rappel */
      l_result = mk_callback_trig ( p_request->callback->handler, p_request->callback, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Vérification de la validité de l'instance de retour */
      l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_request->result ) );

      /* Si l'instance de la variable de retour est située en dehors de la zone non protégée et si la tâche */
      /* qui a transmis le message est de type non privilégié */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Enregistrement de la valeur du résultat */
         *p_request->result = l_result;
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


