/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_container_handleRequest.c
* @brief Définition de la fonction mk_container_handleRequest.
* @date 1 nov. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_container_checkInstance ( T_mkContainerRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Déclaration d'une variable de travail */
   uint32_t l_modulo = 0;

   /* Si l'instance du container est valide */
   if ( ( l_container != K_MK_NULL ) &&
      ( ( l_container >=  ( T_mkContainer* ) &g_mkPrivilegedContainerBuf [0] ) &&
        ( l_container < ( ( T_mkContainer* ) &g_mkPrivilegedContainerBuf [0] + K_MK_DISPLAY_CONTAINER_NUMBER ) ) ) )
   {
      /* Vérification de l'alignement de l'adresse */
      l_modulo = _math_mod ( ( uint32_t ) l_container - ( uint32_t ) &g_mkPrivilegedContainerBuf[0], sizeof ( T_mkContainer ) );

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

static T_mkCode mk_container_checkFieldInstance ( T_mkTask* p_task, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Si l'instance du container est valide */
   if ( ( p_field != K_MK_NULL ) )
   {
      /* Vérification de la validité de l'instance de retour */
      l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_field ) );
      l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( ( uint8_t* ) p_field + sizeof ( T_mkField ) - 1 ) );

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
         /* Actualisation de la variable de retour */
         l_result = K_MK_OK;
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

static T_mkCode mk_container_handleCreateRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = K_MK_NULL;

   /* Vérification de la validité de l'instance de retour */
   uint32_t l_area = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( p_request->container ) );

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
      /* Si le paramètre "container" est valide */
      if ( p_request->container != K_MK_NULL )
      {
         /* Allocation d'un nouveau container */
         /* L'adresse d'un pointeur est envoyée dans la requête */
         l_result = mk_pool_allocSafe ( g_mkDisplay.handler.containerPool, p_request->container, K_MK_POOL_CLEAR, 0 );

         /* Récupération de l'adresse du container alloué */
         l_container = * ( T_mkContainer** ) p_request->container;

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_container != K_MK_NULL ) )
         {
            /* Initialisation du container */
            mk_container_init ( l_container, K_MK_TYPE_DEFAULT );

            /* Configuration de la tâche propriétaire du container */
            l_container->owner = p_task->owner;

            /* Configuration de la fonction d'écoute du container */
            l_container->listener = p_request->listener;

            /* Si la tâche qui a exécutée la requête est de type privilégiée */
            if ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
            {
               /* Configuration du type de container */
               l_container->type = K_MK_TYPE_PRIVILEGED;
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
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Configuration de l'argument de la fonction de rappel */
      p_callbackParam->param2 = l_container;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_container_handleDeleteRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration de l'argument de la fonction de rappel */
   p_callbackParam->param2 = l_container;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Libération du container */
      l_result = mk_pool_freeSafe ( g_mkDisplay.handler.containerPool, l_container );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de l'argument de la fonction de rappel */
         p_callbackParam->param2 = K_MK_NULL;
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

static T_mkCode mk_container_handleListenerRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration des arguments de la fonction de rappel */
   p_callbackParam->param2 = l_container;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Configuration du listener */
      l_container->listener = p_request->listener;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_container_handleAddRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration des arguments de la fonction de rappel */
   p_callbackParam->param2 = p_request->container;
   p_callbackParam->param3 = p_request->field;

   /* Vérification de l'instance du champ */
   l_result = mk_container_checkFieldInstance ( p_task, p_request->field );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
      /* est de type privilégié */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
           ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }

      /* Sinon */
      else
      {
         /* Si la tâche est de type privilégiée */
         if ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
         {
            /* Ajout du champ dans le container */
            l_result = mk_container_add ( g_mkDisplay.painter.semaphore, l_container, p_request->field );
         }

         /* Sinon */
         else
         {
            /* Ajout du champ dans le container */
            l_result = mk_container_add ( g_mkDisplay.painter.unprivilegedSemaphore, l_container, p_request->field );
         }
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

static T_mkCode mk_container_handleRemoveRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration des arguments de la fonction de rappel */
   p_callbackParam->param2 = p_request->container;
   p_callbackParam->param3 = p_request->field;

   /* Vérification de l'instance du champ */
   l_result = mk_container_checkFieldInstance ( p_task, p_request->field );

   /* Si le paramètre est valide */
   if ( l_result == K_MK_OK )
   {
      /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
      /* est de type privilégié */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
           ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }

      /* Sinon */
      else
      {
         /* Si la tâche est de type privilégiée */
         if ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
         {
            /* Ajout du champ dans le container */
            l_result = mk_container_remove ( g_mkDisplay.painter.semaphore, p_request->container, p_request->field );
         }

         /* Sinon */
         else
         {
            /* Ajout du champ dans le container */
            l_result = mk_container_remove ( g_mkDisplay.painter.unprivilegedSemaphore, p_request->container, p_request->field );
         }
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

static T_mkCode mk_container_handleAddFactoryRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration de l'argument de la fonction de rappel */
   p_callbackParam->param2 = p_request->container;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le container est de type privilégiée */
      if ( l_container->type == K_MK_TYPE_PRIVILEGED )
      {
         /* Enregistrement de l'adresse de la factory propriétaire du container */
         l_container->factory = &g_mkDisplay.privilegedFactory;

         /* Ajout du container dans la factory privilégiée */
         l_result = mk_factory_add ( g_mkDisplay.painter.semaphore, &g_mkDisplay.privilegedFactory, l_container );
      }

      /* Sinon */
      else
      {
         /* Enregistrement de l'adresse de la factory propriétaire du container */
         l_container->factory = &g_mkDisplay.unprivilegedFactory;

         /* Ajout du container dans la factory non privilégiée */
         l_result = mk_factory_add ( g_mkDisplay.painter.unprivilegedSemaphore, &g_mkDisplay.unprivilegedFactory, l_container );
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

static T_mkCode mk_container_handleRemoveFactoryRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request, T_mkCallbackParam* p_callbackParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de container */
   T_mkContainer* l_container = p_request->container;

   /* Configuration de l'argument de la fonction de rappel */
   p_callbackParam->param2 = p_request->container;

   /* Si la tâche ayant exécutée la requête est de type non privilégiée et si le container */
   /* est de type privilégié */
   if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
        ( l_container->type == K_MK_TYPE_PRIVILEGED ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_RIGHT;
   }

   /* Sinon */
   else
   {
      /* Si le container est de type privilégiée */
      if ( l_container->type == K_MK_TYPE_PRIVILEGED )
      {
         /* Ajout du container dans la factory non privilégiée */
         l_result = mk_factory_remove ( g_mkDisplay.painter.semaphore, l_container->factory, l_container );
      }

      /* Sinon */
      else
      {
         /* Ajout du container dans la factory non privilégiée */
         l_result = mk_factory_remove ( g_mkDisplay.painter.unprivilegedSemaphore, l_container->factory, l_container );
      }

      /* Actualisation de l'adresse de la factory propriétaire du container */
      l_container->factory = K_MK_NULL;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_container_handleRequest ( T_mkTask* p_task, T_mkContainerRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Déclaration des paramètres de retour */
   T_mkCallbackParam l_callbackParams;

   /* Si la requête est de type CONTAINER_CREATE */
   if ( p_request->id == K_MK_DISPLAY_REQUEST_CONTAINER_CREATE )
   {
      /* Gestion de la requête de création d'un container */
      l_result = mk_container_handleCreateRequest ( p_task, p_request, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Vérification de l'instance du container */
      l_result = mk_container_checkInstance ( p_request );

      /* Si les paramètres sont valides */
      if ( l_result == K_MK_OK )
      {
         /* Si la requête est de type CONTAINER_DELETE */
         if ( p_request->id == K_MK_DISPLAY_REQUEST_CONTAINER_DELETE )
         {
            /* Gestion de la requête de destruction d'un container */
            l_result = mk_container_handleDeleteRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type CONTAINER_LISTENER */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_CONTAINER_LISTENER )
         {
            /* Gestion de la requête permettant de configurer la fonction d'écoute d'un container */
            l_result = mk_container_handleListenerRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type CONTAINER_ADD */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_CONTAINER_ADD )
         {
            /* Gestion de la requête permettant d'ajouter un champ dans un container */
            l_result = mk_container_handleAddRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type CONTAINER_REMOVE */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_CONTAINER_REMOVE )
         {
            /* Gestion de la requête permettant de retirer un champ dans un container */
            l_result = mk_container_handleRemoveRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type FACTORY_ADD */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_FACTORY_ADD )
         {
            /* Gestion de la requête permettant d'ajouter un container dans une factory */
            l_result = mk_container_handleAddFactoryRequest ( p_task, p_request, &l_callbackParams );
         }

         /* Sinon si la requête est de type FACTORY_REMOVE */
         else if ( p_request->id == K_MK_DISPLAY_REQUEST_FACTORY_REMOVE )
         {
            /* Gestion de la requête permettant de retirer un container d'une factory */
            l_result = mk_container_handleRemoveFactoryRequest ( p_task, p_request, &l_callbackParams );
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



