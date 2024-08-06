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
* @file mk_supervisor_mount.c
* @brief Définition de la fonction mk_supervisor_mount.
* @date 6 janv. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_waitFileSystemEvent ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de tâches */
   T_mkTask* l_task = K_MK_NULL;

   /* Déclaration d'un message */
   T_mkSupervisorMessage l_message;

   /* Déclaration des variables de travail */
   uint32_t l_event = 0, l_counter = 0, l_break = 0;

   /* Effectue */
   do
   {
      /* On regarde la boite de messages du superviseur pour savoir si une erreur s'est produite */
      l_result = mk_mail_pend ( &l_task, p_supervisor->message.mail, &l_message, 0 );

      /* Si aucun message n'a été reçu */
      if ( l_result == K_MK_ERROR_TIMEOUT )
      {
         /* Attente de l'intialisation du système de fichiers */
         l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_FILESYSTEM, &l_event, 0 );
      }

      /* Sinon */
      else
      {
         /* Une erreur vient de se produire */
         /* Arrêt de la boucle */
         l_break = 1;
      }

      /* Si aucune erreur ne s'est produite */
      if ( ( l_break == 0 ) && ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) )
      {
         /* Réalisation d'une pause de 500ms */
         l_result = mk_task_sleep ( 500 );
      }

      /* Sinon */
      else
      {
         /* Une erreur vient de se produire */
         /* Arrêt de la boucle */
         l_break = 1;
      }

      /* Actualisation d'un compteur */
      l_counter+=500;

   /* Tant qu'aucune erreur ne s'est produite et tant que l'initialisation des terminaux de gestion du système de fichiers n'est pas terminée */
   } while ( ( l_result == K_MK_OK ) && ( l_break == 0 ) &&
           ( ( l_event & K_MK_TERMIO_FLAG_FILESYSTEM ) != K_MK_TERMIO_FLAG_FILESYSTEM ) && ( l_counter < K_MK_TERMIO_INIT_TIMEOUT ) );

   /* Si aucune erreur ne s'est produite et si le système de fichiers n'a pas été initialisé */
   if (  ( l_result == K_MK_OK ) && ( l_break == 0 ) && ( ( l_event & K_MK_TERMIO_FLAG_FILESYSTEM ) != K_MK_TERMIO_FLAG_FILESYSTEM ) )
   {
      /* On active le mode dégradé */
      /* La décision du redémarrage du système est de la responsabilité de l'utilisateur */
      mk_supervisor_recovery ( p_supervisor, K_MK_SUPERVISOR_ERROR_CODE100, K_MK_NULL, K_MK_NULL );
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

T_mkCode mk_supervisor_mount ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task = K_MK_NULL;

   /* Déclaration d'un message */
   T_mkSupervisorMessage l_message;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Attente tant qu'aucun terminal de gestion du système de fichiers n'est initialisé */
   l_result = mk_supervisor_waitFileSystemEvent ( p_supervisor );

   /* Tant qu'aucune erreur ne s'est produite et tant que le système de fichiers n'a pas été initialisé */
   while ( ( l_result == K_MK_OK ) && ( p_supervisor->volume == K_MK_NULL ) )
   {
      /* Réalisation d'une pause */
      l_result = mk_task_sleep ( 500 );

      /* Récupération de l'adresse du volume système */
      p_supervisor->volume = g_mkSystemVolume;

      /* Si aucune ne erreur s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* On regarde la boite de messages du superviseur pour savoir si une erreur s'est produite */
         l_result = mk_mail_pend ( &l_task, p_supervisor->message.mail, &l_message, 0 );

         /* Si aucun message n'a été reçu */
         if ( l_result == K_MK_ERROR_TIMEOUT )
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

      /* Si aucune ne erreur s'est produite et si au bout de 5 secondes, le système de fichiers n'a pas été trouvé */
      if ( ( l_result == K_MK_OK ) && ( l_counter == 10 ) )
      {
         /* On active le mode dégradé */
         /* La décision du redémarrage du système est de la responsabilité de l'utilisateur */
         mk_supervisor_recovery ( p_supervisor, K_MK_SUPERVISOR_ERROR_CODE110, K_MK_NULL, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du compteur */
      l_counter++;
   };

   /* Retour */
   return ( l_result );
}


