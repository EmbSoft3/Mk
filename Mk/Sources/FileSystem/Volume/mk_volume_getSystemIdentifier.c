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
* @file mk_volume_getSystemIdentifier.c
* @brief Définition de la fonction mk_volume_getSystemIdentifier.
* @date 9 mars 2024
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_volume_getSystemIdentifier ( T_mkVolume* p_list )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_VOLUME_MAX_NUMBER;

   /* Déclaration des variables de travail */
   uint32_t l_identifier = 0, l_find = 0;

   /* Déclaration d'un pointeur de partition */
   T_mkVolume* l_volume = p_list;

   /* Pour le nombre d'identifiant pouvant être alloué */
   for ( l_identifier = 0 ; l_identifier < K_MK_VOLUME_MAX_NUMBER ; l_identifier++ )
   {
      /* Initialisation du pointeur de volume */
      l_volume = p_list;

      /* Parcours de l'ensemble des partitions allouées sur le disque */
      while ( ( l_volume != K_MK_NULL ) && ( l_find == 0 ) )
      {
         /* Si l'identifiant est déjà utilisé */
         if ( l_identifier == l_volume->name.id )
         {
            /* Actualisation de la variable d'état */
            l_find = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine partition */
         l_volume = l_volume->nextVolume;
      }

      /* Si un identifiant unique a été trouvé */
      if ( l_find == 0 )
      {
         /* Actualisation de la variable de retour */
         l_result = l_identifier;

         /* Arrêt de la boucle */
         l_identifier = K_MK_VOLUME_MAX_NUMBER;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Réinitialisation de la variable d'état */
      l_find = 0;
   }

   /* Retour */
   return ( l_result );
}


