/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_display_refreshFields.c
* @brief Définition de la fonction mk_display_refreshFields.
* @date 1 août 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_refreshContainer ( T_mkContainer* p_container )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkField* l_tmp = p_container->first;

   /* Pour tous les champs présents dans le container */
   while ( ( l_tmp != K_MK_NULL ) && ( l_result == K_MK_OK) )
   {
      /* Recopie du champ visibilité */
      l_tmp->visibility = l_tmp->userVisibility;

      /* Si l'utilisateur souhaite rafraichir le champ */
      if ( l_tmp->userRefresh != 0 )
      {
         /* Actualisation des varibles de rafraichissement */
         l_tmp->refresh = l_tmp->userRefresh;
         l_tmp->userRefresh = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Passage au champ suivant */
      l_tmp = l_tmp->next;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_display_refreshFactory ( T_mkFactory* p_factory )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkContainer* l_tmp = p_factory->first;

   /* Pour tous les containers présents dans la factory */
   while ( ( p_factory != K_MK_NULL ) && ( l_tmp != K_MK_NULL ) && ( l_result == K_MK_OK ) )
   {
      /* Actualisation des attributs des objets du container */
      l_result = mk_display_refreshContainer ( l_tmp );

      /* Passage au prochain container */
      l_tmp = l_tmp->next;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_display_refreshFields ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réservation du sémaphore d'écoute non-privilégié */
   l_result = mk_semaphore_take ( g_mkDisplay.listener.unprivilegedSemaphore, K_MK_TASK_WAIT_FOREVER );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Actualisation des attributs des objets de la factory */
      mk_display_refreshFactory ( &g_mkDisplay.unprivilegedFactory );

      /* Libération du sémaphore */
      l_result = mk_semaphore_release ( g_mkDisplay.listener.unprivilegedSemaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Réservation du sémaphore d'écoute privilégié */
      l_result = mk_semaphore_take ( g_mkDisplay.listener.semaphore, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation des attributs des objets */
         mk_display_refreshFactory   ( &g_mkDisplay.privilegedFactory );
         mk_display_refreshContainer ( g_mkDisplay.criticalContainer );
         mk_display_refreshContainer ( g_mkDisplay.frontendContainer );

         /* Libération du sémaphore */
         l_result |= mk_semaphore_release ( g_mkDisplay.listener.semaphore );
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


