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
* @file mk_dispatcher_task.c
* @brief Définition de la fonction mk_dispatcher_task.
* @date 17 nov. 2019
*
* @todo Désallouer la mémoire lors de la destruction du terminal.
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_init ( T_mkTermio* p_termio, T_mkDispatcherHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire */
   _writeWords ( p_handler, 0, sizeof ( T_mkDispatcherHandler ) >> 2 );

   /* Configuration de la structure de données du dispatcher */
   l_result = mk_termio_setChild ( p_termio, ( T_mkDispatcherHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du dispatcher */
      l_result = mk_dispatcher_initHandler ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Affichage d'un message dans la console du superviseur pour indiquer */
         /* que l'initialisation a réussi. */
         l_result = mk_termio_log ( ( T_str8 ) "[Dispatcher] ready;\n" );
      }

      /* Sinon */
      else
      {
         /* Affichage d'un message dans la console du superviseur pour indiquer */
         /* que l'initialisation a échoué. */
         l_result = mk_termio_log ( ( T_str8 ) "[Dispatcher] failed;\n" );
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

void mk_dispatcher_task ( T_mkAddr p_param )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire */
   T_mkDispatcherHandler l_handler;

   /* Déclaration d'un message */
   T_mkDispatcherMessage l_message;

   /* Initialisation du dispatcher */
   l_result = mk_dispatcher_init ( ( T_mkTermio* ) p_param, &l_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Tant qu'aucune erreur ne s'est produite */
      while ( l_result == K_MK_OK )
      {
         /* Analyse de la boite de messages pour savoir si un nouvel événement est disponible */
         l_result = mk_mail_pend ( K_MK_NULL, l_handler.mailArea->mail, ( T_mkAddr ) &l_message, K_MK_TASK_WAIT_FOREVER );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Traitement du message entrant */
            l_result = mk_dispatcher_handleMessage ( &l_handler, &l_message );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le dispatcher n'a pas été initialisé. */
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
