/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_volume_delete.c
* @brief Définition de la fonction mk_volume_delete.
* @date 29 mai 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_volume_delete ( T_mkVolume* p_list, uint32_t p_enableEvent )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de partition */
   T_mkVolume* l_nextVolume = K_MK_NULL;

   /* Tant que la liste de partition n'a pas été parcourue */
   while ( p_list != K_MK_NULL )
   {
      /* Récupération de l'adresse de la prochaine partition */
      l_nextVolume = p_list->nextVolume;

      /* Si un événement doit être transmis au dispatcher */
      if ( p_enableEvent == 1 )
      {
         /* On signale au dispatcher que le volume a été supprimé */
         l_result |= mk_volume_dispatch ( p_list, K_MK_EVENT_UNMOUNT );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la structure de la partition */
      _writeWords ( p_list, 0, sizeof ( T_mkVolume ) >> 2 );

      /* Désallocation de la partition */
      l_result |= mk_pool_freeSafe ( g_mkVolumePool.pool, p_list );

      /* Actualisation du pointeur de liste */
      p_list = l_nextVolume;
   }

   /* Retour */
   return ( l_result );
}


