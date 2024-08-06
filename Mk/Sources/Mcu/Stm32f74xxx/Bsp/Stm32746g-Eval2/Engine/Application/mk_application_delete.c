/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_application_delete.c
* @brief Définition de la fonction mk_application_delete.
* @date 5 août 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_delete ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Lorsqu'une application est détruite, les événements K_MK_EVENT_CLOSE ou K_MK_EVENT_UNINSTALL sont générés */
   /* pour prévenir l'utilisateur que les ressources allouées par l'application doivent êtree libérées (fichiers, sémaphore, ...). */
   /* La désallocation des pages mémoires est donc temporisée afin que le traitement des événements K_MK_EVENT_CLOSE ou K_MK_EVENT_UNINSTALL */
   /* se produise dans un contexte mémoire persistant. */
   /* La désallocation des pages mémoire est réalisée dans la tâche de peinture car celle-ci est moins prioritaire que la tâche d'écoute. */
   /* On s'assure donc le traitement des événéments K_MK_EVENT_CLOSE ou K_MK_EVENT_UNINSTALL. */
   /* La constante K_MK_DISPLAY_GARBAGE_ELAPSE_TIMEOUT permet de configurer le nombre de frames avant que la désallocation se produise. */

   /* Déclaration d'un pointeur d'élément */
   T_mkApplicationGarbageItem* l_currentGarbageItem = g_mkDisplay.application.list.deleted;

   /* Parcours de liste chainée */
   while ( ( l_result == K_MK_OK ) && ( l_currentGarbageItem != K_MK_NULL ) )
   {
      /* Si le compteur de frame est nul, il est temps de désallouer les pages mémoire */
      if ( l_currentGarbageItem->elapseCounter == 0 )
      {
         /* Libération des ressources de l'application */
         l_result = mk_application_release ( l_currentGarbageItem->application );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Retrait de l'élément de la liste puis désallocation */
            l_result = mk_application_removeDeletedList ( l_currentGarbageItem );
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
         /* On décrémente le compteur d'une unité */
         l_currentGarbageItem->elapseCounter = ( uint32_t ) l_currentGarbageItem->elapseCounter - 1u;
      }

      /* Passage à la prochaine application */
      l_currentGarbageItem = l_currentGarbageItem->next;
   }

   /* Retour */
   return ( l_result );
}


