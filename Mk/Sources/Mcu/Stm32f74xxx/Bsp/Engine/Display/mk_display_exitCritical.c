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
* @file mk_display_exitCritical.c
* @brief Définition de la fonction mk_display_exitCritical.
* @date 4 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_releaseUnPrivilegedRessources ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la tâche courante n'est pas la tâche de peinture */
   if ( g_mkScheduler.currentTask != g_mkDisplay.painter.unprivilegedTask )
   {
      /* Réservation du sémaphore de peinture non privilégié */
      l_result = mk_semaphore_release ( g_mkDisplay.painter.unprivilegedSemaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le sémaphore ne doit pas être libéré si cette fonction est exécutées par la tâche de peinture */
   }

   /* Si la tâche courante n'est pas la tâche listener */
   if ( ( l_result == K_MK_OK ) && ( g_mkScheduler.currentTask != g_mkDisplay.listener.unprivilegedTask ) )
   {
      /* Réservation du sémaphore d'écoute non privilégié */
      l_result = mk_semaphore_release ( g_mkDisplay.listener.unprivilegedSemaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le sémaphore ne doit pas être libéré si cette fonction est exécutées par la tâche d'écoute */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_releasePrivilegedRessources ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la tâche courante n'est pas la tâche de peinture */
   if ( g_mkScheduler.currentTask != g_mkDisplay.painter.privilegedTask )
   {
      /* Réservation du sémaphore de peinture privilégié */
      l_result = mk_semaphore_release ( g_mkDisplay.painter.semaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le sémaphore ne doit pas être libéré si cette fonction est exécutées par la tâche de peinture */
   }

   /* Si la tâche courante n'est pas la tâche listener */
   if ( ( l_result == K_MK_OK ) && ( g_mkScheduler.currentTask != g_mkDisplay.listener.privilegedTask ) )
   {
      /* Réservation du sémaphore d'écoute privilégié */
      l_result = mk_semaphore_release ( g_mkDisplay.listener.semaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le sémaphore ne doit pas être libéré si cette fonction est exécutées par la tâche d'écoute */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_display_exitCritical ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération des droits d'exécution */
   uint32_t l_right = _mk_scheduler_privileged ( );

   /* Si cette fonction est exécutée en mode privilégié */
   if ( l_right == K_MK_MODE_HANDLER )
   {
      /* Lancement du processus de gestion des ressources privilégiées */
      l_result = mk_display_releasePrivilegedRessources ( );
   }

   /* Sinon */
   else
   {
      /* Lancement du processus de gestion des ressources non privilégiées */
      l_result = mk_display_releaseUnPrivilegedRessources ( );
   }

   /* Retour */
   return ( l_result );
}


