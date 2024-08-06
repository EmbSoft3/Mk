/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_task.c
* @brief Définition de la fonction mk_file_task.
* @date 30 mai 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_initMessageArea ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à la messagerie non partagée */
   l_result = mk_pool_initArea ( &g_mkFileMessageArea.requestArea, g_mkFileMessageArea.requestHeap, K_MK_FILE_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &g_mkFileMessageArea.request, K_MK_AREA_UNPROTECTED, &g_mkFileMessageArea.requestArea, K_MK_FILE_MESSAGE_SIZE, K_MK_FILE_MESSAGE_NUMBER );
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

static T_mkCode mk_file_initMessageSharedArea ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à la messagerie partagée */
   l_result = mk_pool_initArea ( &g_mkFileMessageSharedArea.requestArea, g_mkFileMessageSharedArea.requestHeap, K_MK_FILE_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &g_mkFileMessageSharedArea.request, K_MK_AREA_UNPROTECTED, &g_mkFileMessageSharedArea.requestArea, K_MK_FILE_MESSAGE_SIZE, K_MK_FILE_MESSAGE_NUMBER );
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

static T_mkCode mk_file_initFileArea ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des fichiers */
   l_result = mk_pool_initArea ( &g_mkFileArea.area, g_mkFileArea.heap, K_MK_FILE_NUMBER * ( sizeof ( T_mkFile ) >> 2 ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des fichiers */
      l_result = mk_pool_create ( &g_mkFileArea.area, &g_mkFileArea.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkFile ) >> 2, K_MK_FILE_NUMBER );
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

static T_mkCode mk_file_handleInitEvent ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Positionnement de l'événement FILESYSTEM */
   l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_FILESYSTEM );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Attente de la fin de l'initialisation des terminaux MMC et MSC */
      l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_MMC | K_MK_TERMIO_FLAG_MSC, &l_event, K_MK_TERMIO_INIT_TIMEOUT );
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

static T_mkCode mk_file_initFSHandler ( T_mkTermio* p_termio )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Si identifiant du premier terminal */
   if ( p_termio->task->attribute.identifier == K_MK_TERMIO_FILESYSTEM_ID )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_file_initMessageArea ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire de fichier */
         l_result = mk_file_initMessageSharedArea ( );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation de la pool de fichiers */
            l_result = mk_file_initFileArea ( );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Attente de l'intialisation des gestionnaires MMC et MSC */
               l_result = mk_file_handleInitEvent ( );
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
      /* Attente de la fin de l'initialisation des données du système de fichiers */
      l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_FILESYSTEM, &l_event, K_MK_TERMIO_INIT_TIMEOUT );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a réussi. */
      l_result = mk_termio_log ( ( T_str8 ) "[FileSystem] ready;\n" );
   }

   /* Sinon */
   else
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a échoué. */
      l_result = mk_termio_log ( ( T_str8 ) "[FileSystem] failed;\n" );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_file_handleEvents ( T_mkTermio* p_termio )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task = K_MK_NULL;

   /* Déclaration d'un message */
   T_mkFileMessage l_message;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams;

   /* Boucle tant qu'aucune erreur critique ne s'est produite */
   while ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_TIMEOUT ) || ( l_result == K_MK_ERROR_COMM ) )
   {
      /* Attendre tant qu'un message n'a pas été reçu */
      l_result = mk_mail_pend ( &l_task, g_mkFileMessageArea.request, ( T_mkAddr ) &l_message, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
      {
         /* Exécution de la requête utilisateur */
         l_result = mk_file_handle ( &l_message, &l_callbackParams, l_task, &g_mkFileBuf [ p_termio->task->attribute.identifier - K_MK_TERMIO_FILESYSTEM_ID ] [ 0 ], 0 );

         /* Si une fonction de rappel a été configurée */
         if ( l_message.callback != K_MK_NULL )
         {
            /* Ecriture du résultat de la requête dans la structure de rappel */
            /* Les autres arguments sont configurés dans les fonctions propres à chaque requête */
            l_callbackParams.param1 = ( T_mkAddr ) l_result;

            /* Déclenchement de la fonction de rappel */
            l_result = mk_callback_trig ( l_message.callback->handler, l_message.callback, &l_callbackParams );
         }

         /* Sinon */
         else
         {
            /* Vérification de la validité de l'instance de retour */
            l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( l_message.result ) );

            /* Si l'instance de la variable de retour est située en dehors de la zone non protégée et si la tâche */
            /* qui a transmis le message est de type non privilégié */
            if ( ( ( l_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
            {
               /* Ne rien faire */
            }

            /* Sinon */
            else
            {
               /* Enregistrement de la valeur du résultat */
               *l_message.result = l_result;
            }

            /* Réactivation de la tâche qui a réalisé la requête */
            l_result = mk_task_resume ( l_task );
         }
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

void mk_file_task ( T_mkAddr p_param )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = ( T_mkTermio* ) p_param;

   /* Initialisation du gestionnaire de fichier */
   l_result = mk_file_initFSHandler ( l_termio );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Exécution de la boucle de traitement des requêtes utilisateur */
      l_result = mk_file_handleEvents ( l_termio );
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


