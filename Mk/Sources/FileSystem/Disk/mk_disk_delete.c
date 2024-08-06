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
* @file mk_disk_delete.c
* @brief Définition de la fonction mk_disk_delete.
* @date 17 sept. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_disk_delete ( T_mkDisk** p_list, T_mkDisk* p_disk, uint32_t p_enableEvent )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   T_mkDisk *l_currentDisk = K_MK_NULL, *l_nextDisk = K_MK_NULL, *l_previousDisk = K_MK_NULL;

   /* Si le paramètre est valide */
   if ( p_list != K_MK_NULL )
   {
      /* Récupération de l'adresse du premier disque */
      l_currentDisk = *p_list;
      l_previousDisk = K_MK_NULL;

      /* Tant que la liste n'a pas été entièrement parcourue */
      while ( l_currentDisk != K_MK_NULL )
      {
         /* Récupération de l'adresse du prochain disque */
         l_nextDisk = l_currentDisk->nextDisk;

         /* Si disque analysé est le disque recherché et si celui-ci n'est pas en utilisation */
         if ( ( ( l_currentDisk == p_disk ) || ( p_disk == K_MK_NULL ) ) && ( l_currentDisk->status.main & K_MK_DISK_USED ) != K_MK_DISK_USED )
         {
            /* Si le disque à supprimer est le premier de la liste */
            if ( l_currentDisk == ( *p_list ) )
            {
               /* Actualisation du pointeur de liste */
               *p_list = l_nextDisk;
            }

            /* Sinon */
            else
            {
               /* Suppression d'un élément de la liste */
               l_previousDisk->nextDisk = l_nextDisk;
            }

            /* Reconfiguration de l'adresse du précédent disque */
            l_previousDisk = l_nextDisk;

            /* On supprime les partitions présentes dans le disque et on signale */
            /* au dispatcher que les volumes ont été supprimé. */
            l_result |= mk_volume_delete ( l_currentDisk->volume, 1 );

            /* Si un événement doit être transmis au dispatcher */
            if ( p_enableEvent == 1 )
            {
               /* On signale au dispatcher que le disque vient d'être supprimé */
               l_result |= mk_disk_dispatch ( l_currentDisk, K_MK_EVENT_DISCONNECT );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Suppression du sémpahore */
            l_result |= mk_semaphore_delete ( l_currentDisk->semaphore );

            /* Réinitialisation de la structure disque */
            _writeWords ( l_currentDisk, 0, sizeof ( T_mkDisk ) >> 2 );

            /* Suppression du disque */
            l_result |= mk_pool_freeSafe ( g_mkDiskPool.pool, l_currentDisk );
         }

         /* Sinon */
         else
         {
            /* Reconfiguration de l'adresse du précédent disque */
            l_previousDisk = l_currentDisk;
         }

         /* Passage au prochain disque */
         l_currentDisk = l_nextDisk;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_OK;
   }

   /* Retour */
   return ( l_result );
}

