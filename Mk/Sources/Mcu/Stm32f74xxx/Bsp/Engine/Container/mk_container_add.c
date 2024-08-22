/**
*
* @copyright Copyright (C) 2019-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_container_add.c
* @brief Définition de la fonction mk_container_add.
* @date 4 mai 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_container_add ( T_mkSemaphore* p_semaphore, T_mkContainer* p_container, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des pointeurs de champs */
   T_mkField* l_currentField = K_MK_NULL, *l_previousField = K_MK_NULL;

   /* Les containers sont des objets partagés. */
   /* Tant que le signal de synchronisation n'a pas été reçu, laisser */
   /* la main à une autre tâche */
   l_result = mk_semaphore_take ( p_semaphore, K_MK_TASK_WAIT_FOREVER );

   /* Si la synchronisation a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Si la liste est vide */
      if ( p_container->first == K_MK_NULL )
      {
         /* La liste contient un seul élement, les pointeurs 'next' et */
         /* 'previous' doivent pointer sur la valeur nulle. */
         p_field->previous = K_MK_NULL;
         p_field->next = K_MK_NULL;

         /* Configuration des pointeurs de début et de fin de liste */
         p_container->first = p_field;
         p_container->last = p_field;
      }

      /* Sinon */
      else
      {
         /* Récupération de l'adresse du premier champ dans le container */
         l_currentField = p_container->first;

         /* On place le champ dans la liste en fonction de son indice de profondeur. */
         /* Si deux champs possèdent le même indice, on place le nouveau champ en tête. */
         /* Il sera alors dessiné en premier. */
         while ( ( l_currentField != K_MK_NULL ) && ( p_field->zIndex > l_currentField->zIndex ) )
         {
            /* Passage au prochain champ */
            l_previousField = l_currentField;
            l_currentField = l_currentField->next;
         }

         /* Actualisation des pointeurs du nouvel élément */
         p_field->previous = l_previousField;
         p_field->next = l_currentField;

         /* Si le pointeur de liste doit être actualisé */
         /* Le champ a été inséré en tête de liste */
         if ( l_previousField == K_MK_NULL )
         {
            /* Configuration du pointeur de début de liste */
            p_container->first = p_field;
         }

         /* Sinon */
         else
         {
            /* Le précédent champ pointe sur le nouveau champ */
            l_previousField->next = p_field;
         }

         /* Si le pointeur de fin de liste doit être actualisé */
         /* Le champ a été inséré en fin de liste */
         if ( l_currentField == K_MK_NULL )
         {
            /* Configuration du pointeur de fin de liste */
            p_container->last = p_field;
         }

         /* Sinon */
         else
         {
            /* Le prochain champ doit pointer sur le nouveau champ */
            l_currentField->previous = p_field;
         }
      }

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

