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
* @file mk_factory_remove.c
* @brief Définition de la fonction mk_factory_remove.
* @date 4 mai 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_factory_remove ( T_mkSemaphore* p_semaphore, T_mkFactory* p_factory, T_mkContainer* p_container )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Les factory sont des objets partagés. */
   /* Tant que le signal de synchronisation n'a pas été reçu, laisser */
   /* la main à une autre tâche */
   l_result = mk_semaphore_take ( p_semaphore, K_MK_TASK_WAIT_FOREVER );

   /* Si la synchronisation a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Si la liste ne possède qu'un seul élément */
      if ( p_factory->first == p_factory->last )
      {
         /* La liste est vide, les pointeurs de début et de fin doivent pointer sur */
         /* la valeur nulle */
         p_factory->first = K_MK_NULL;
         p_factory->last = K_MK_NULL;
      }

      /* Sinon, la liste possède au moins deux éléments */
      else
      {
         /* Si l'élément est situé en début de liste */
         if ( p_container->previous == K_MK_NULL )
         {
            /* Le deuxième élément passe en tête de liste */
            p_container->next->previous = K_MK_NULL;
            /* Actualisation du pointeur de tête */
            p_factory->first = p_container->next;
         }

         /* Sinon si l'élément est situé en fin de liste */
         else if ( p_container->next == K_MK_NULL )
         {
            /* L'avant dernier élément passe en fin de liste */
            p_container->previous->next = K_MK_NULL;
            /* Actualisation du pointeur de fin */
            p_factory->last = p_container->previous;
         }

         /* Sinon */
         else
         {
            /* L'élément est situé en milieu de liste */
            p_container->previous->next = p_container->next;
            p_container->next->previous = p_container->previous;
         }
      }

      /* L'élément n'appartient à aucune liste, les pointeurs 'next' et 'previous' */
      /* doivent pointer sur la valeur nulle */
      p_container->previous = K_MK_NULL;
      p_container->next = K_MK_NULL;

      /* Libération de la ressource */
      l_result = mk_semaphore_release ( p_semaphore );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


