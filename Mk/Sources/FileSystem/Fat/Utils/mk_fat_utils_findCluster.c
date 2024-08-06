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
* @file mk_fat_utils_findCluster.c
* @brief Définition de la fonction mk_fat_utils_findCluster.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_findCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_searchedCluster, uint32_t p_clusterNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf;

   /* Déclaration des variables de travail */
   uint32_t l_offset = 0, l_block = 0, l_nextBlock = 0, l_clusterNumber = 0;

   /* Dans la situation où l'index du cluster recherché est supérieur à la taille de la chaine alors */
   /* la fonction retourne la valeur du dernier cluster */

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_searchedCluster != K_MK_NULL ) &&
      ( ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_cluster < K_MK_FAT_VALID_CLUSTER ) ) )
   {
      /* Actualisation de la variable de retour */
      *p_searchedCluster = p_cluster;

      /* Enregistrement de l'index du cluster à rechercher */
      l_clusterNumber = p_clusterNumber;

      /* Détermination de l'adresse du premier bloc de recherche */
      l_block = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

      /* Lecture du secteur de données */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_block ) );

      /* Initialisation de l'algorithme */
      l_nextBlock = l_block;

      /* Tant que la chaine de cluster n'a pas été entièrement analysée et tant qu'aucune */
      /* erreur ne s'est produite */
      while ( ( l_result == K_MK_OK ) && ( l_clusterNumber != 0 ) &&
              ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_cluster < K_MK_FAT_VALID_CLUSTER ) )
      {
         /* Si la lecture d'un nouveau bloc de données est nécessaire */
         if ( l_block != l_nextBlock )
         {
            /* Lecture du secteur de données */
            l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_nextBlock ) );

            /* Actualisation de l'adresse du prochain secteur */
            l_block = l_nextBlock;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Conversion du buffer du fichier en 32 bits (cast) */
         l_buf = ( T_mkAddr ) p_file->buf;

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement de la valeur du cluster courant */
            *p_searchedCluster = p_cluster;

            /* Détermination de l'offset du prochain cluster dans la buffer */
            l_offset = ( uint32_t ) ( _math_mod2 ( p_cluster, p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

            /* Détermination de la valeur du prochain cluster */
            p_cluster = ( uint32_t ) ( l_buf [ l_offset ] & K_MK_FAT_CLUSTER_MASK );

            /* Détermination de l'adresse du prochain bloc de données */
            l_nextBlock = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

            /* Actualisation de l'index du cluster recherché */
            l_clusterNumber = ( uint32_t ) ( l_clusterNumber - 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si la recherche du cluster a échoué */
      if ( ( p_clusterNumber != K_MK_FAT_LAST_CLUSTER ) && ( l_clusterNumber != 0 ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_FOUND;
      }

      /* Sinon si la chaine de cluster est corrompue */
      else if ( p_cluster < p_file->volume->partition.fat.firstRootDirectoryCluster )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_CORRUPTED;
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


