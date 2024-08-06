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
* @file mk_display_handler.c
* @brief Définition de la fonction mk_display_handler.
* @date 10 mai 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_handleEngineRequest ( T_mkDisplayEngineRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si touts les dessins de la frame courante ont été traitées */
   if ( p_request->id == K_MK_DISPLAY_REQUEST_TYPE_NEXT_FRAME )
   {
      /* Actualisation du drapeau de validité du buffer */
      g_mkDisplay.pnt.currentBufferUpdated->validity = 1;

      /* Configuration de l'adresse du prochain buffer */
      g_mkDisplay.pnt.currentBufferUpdated = g_mkDisplay.pnt.currentBufferUpdated->next;
   }

   /* Sinon le layer de premier plan doit être activé */
   else if (p_request->id == K_MK_DISPLAY_REQUEST_TYPE_ENABLE_FOREGROUND )
   {
      /* Passage du drapeau à 1 pour que le layer soit activé à la fin de la trame courante */
      g_mkDisplay.pnt.currentBufferUpdated->status.foregroundLayer = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si les requêtes d'activation des layers peuvent être exécutées */
   if ( g_mkDisplay.status.criticalLock == 0 )
   {
      /* Si le layer d'arrière plan doit être activé */
      /* Cette requête ne peut pas être exécutée si le mode critique est actif */
      if ( p_request->id == K_MK_DISPLAY_REQUEST_TYPE_ENABLE_BACKGROUND )
      {
         /* Passage du drapeau à 1 pour que le layer soit activé à la fin de la trame courante */
         g_mkDisplay.pnt.currentBufferUpdated->status.backgroundLayer = 1;
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

void mk_display_handler ( T_mkAddr p_unused )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task;

   /* Déclaration d'une requête */
   T_mkDisplayRequest l_request;

   /* Boucle pour toujours */
   while ( 1 )
   {
      /* Analyse de la boite de messages */
      l_result = mk_mail_pend ( &l_task, g_mkDisplay.handler.mail, ( T_mkAddr ) &l_request, K_MK_TASK_WAIT_FOREVER );

      /* Si une message est disponible et si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
      {
         /* Si le requête est de type 'Engine' */
         if ( l_request.type == K_MK_DISPLAY_REQUEST_TYPE_ENGINE )
         {
            /* Exécution d'une requête de contrôle du moteur graphique */
            l_result = mk_display_handleEngineRequest ( &l_request.content.engine );
         }

         /* Sinon si la requête est de type 'Chromart' */
         else if ( l_request.type == K_MK_DISPLAY_REQUEST_TYPE_CHROMART )
         {
            /* Exécution d'une requête de dessin */
            l_result = mk_chromart_handleRequest ( l_task, &l_request.content.chromart );
         }

         /* Sinon si la requête est de type 'Application' */
         else if ( l_request.type == K_MK_DISPLAY_REQUEST_TYPE_APPLICATION )
         {
            /* Exécution d'une requête applicative */
            l_result = mk_application_handleRequest ( l_task, &l_request.content.application );
         }

         /* Sinon si la requête est de type 'Container' */
         else if ( l_request.type == K_MK_DISPLAY_REQUEST_TYPE_CONTAINER )
         {
            /* Si la variable de retour est valide */
            if ( l_request.content.container.result != K_MK_NULL )
            {
               /* Exécution d'une requête relative aux containers et factory */
               l_result = mk_container_handleRequest ( l_task, &l_request.content.container );
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

      /* Si une erreur grave s'est produite */
      if ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) != K_MK_OK )
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

   /* Suppression du warning */
   ( void ) ( p_unused );

   /* Retour */
   return;
}


