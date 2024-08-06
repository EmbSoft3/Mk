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
* @file mk_fat_utils_releaseCluster.c
* @brief Définition de la fonction mk_fat_utils_releaseCluster.
* @date 9 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_updateAllocationTable ( T_mkFile* p_file, uint32_t p_clusterBlock, uint32_t* p_numberOfClustersReleased )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_counter = 0, l_numberOfBytesWrite = 0;

   /* Ecriture de la première FAT */
   l_result = mk_fat_utils_writeCache ( p_file,  ( uint64_t ) ( p_clusterBlock ) );

   /* Pour le nombre de FAT à mettre à jour */
   for ( l_counter = 1 ; ( l_result == K_MK_OK ) && ( l_counter < p_file->volume->partition.fat.numberOfFAT ) && ( l_counter < K_MK_FAT_NUMBER_OF_FAT_TO_UPDATE ); l_counter++ )
   {
      /* Ecriture du secteur de données */
      /* La cache d'écriture n'est pas utilisé car deux appels consécutifs de la fonction d'écriture provoque une corruption */
      l_result = mk_fat_utils_write ( p_file,  ( uint64_t ) ( p_clusterBlock + ( l_counter * p_file->volume->partition.fat.sectorsPerFAT ) ), p_file->buf, 1, &l_numberOfBytesWrite );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Actualisation du nombre de clusters libres */
      p_file->volume->partition.fat.numberOfFreeCluster = ( uint32_t ) ( p_file->volume->partition.fat.numberOfFreeCluster + ( *p_numberOfClustersReleased ) );
   }

   /* Sinon */
   else
   {

   }

   /* Réinitialisation de la variable comptant le nombre de clusters libérés */
   *p_numberOfClustersReleased = 0;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getNextBlock ( T_mkFile* p_file, uint32_t p_clusterBlock, uint32_t p_nextBlock, uint32_t* p_numberOfClustersReleased )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Mise à jour de la table d'allocation (FAT) */
   l_result = mk_fat_utils_updateAllocationTable ( p_file, p_clusterBlock, p_numberOfClustersReleased );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture du prochain secteur de données */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_nextBlock ) );
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

T_mkCode mk_fat_utils_releaseCluster ( T_mkFile* p_file, uint32_t p_cluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = K_MK_NULL;

   /* Déclaration des variables de travail */
   uint32_t l_currentClusterBlock = 0, l_nextClusterBlock = 0, l_nextCluster = p_cluster, l_clusterIndex = 0, l_numberOfClustersReleased = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) &&
      ( ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_cluster < K_MK_FAT_VALID_CLUSTER ) ) )
   {
      /* Détermination de l'adresse du cluster dans la FAT */
      l_currentClusterBlock = p_file->volume->partition.fat.addressOfFAT +
            ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector );

      /* Initialisation de l'algorithme */
      l_nextClusterBlock = l_currentClusterBlock;

      /* Lecture d'un secteur de données */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_currentClusterBlock ) );

      /* Tant que la chaine de clusters n'a pas été entièrement désallouées et tant qu'aucune */
      /* erreur ne s'est produite */
      while ( ( l_result == K_MK_OK ) && ( l_nextCluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) &&
              ( l_nextCluster < K_MK_FAT_VALID_CLUSTER ) )
      {
         /* Si la lecture d'un nouveau bloc de données est nécessaire */
         if ( l_currentClusterBlock != l_nextClusterBlock )
         {
            /* Mise à jour des tables d'allocation (FAT) puis lecture du prochain secteur de données */
            l_result = mk_fat_utils_getNextBlock ( p_file, l_currentClusterBlock, l_nextClusterBlock, &l_numberOfClustersReleased );

            /* Actualisation de l'adresse du prochain secteur */
            l_currentClusterBlock = l_nextClusterBlock;
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
            /* Actualisation de la valeur du cluster courant */
            p_cluster = l_nextCluster;

            /* Détermination de l'offset du cluster dans le secteur de la FAT */
            l_clusterIndex = ( uint32_t ) ( _math_mod2 ( p_cluster, p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

            /* Détermination de la valeur du prochain cluster */
            l_nextCluster = l_buf [ l_clusterIndex ];

            /* Désallocation du cluster courant (on conserve la valeur des 4 bits de poids fort) */
            l_buf [ l_clusterIndex ] = ( uint32_t ) ( l_buf [ l_clusterIndex ] & ( uint32_t ) ( ~ K_MK_FAT_CLUSTER_MASK ) );

            /* Actualisation du nombre de clusters libérés */
            l_numberOfClustersReleased = ( uint32_t ) ( l_numberOfClustersReleased + 1 );

            /* Détermination de l'adresse du prochain bloc de données */
            l_nextClusterBlock = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( l_nextCluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Mise à jour des tables d'allocation (FAT) */
         l_result = mk_fat_utils_updateAllocationTable ( p_file, l_currentClusterBlock, &l_numberOfClustersReleased );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ecriture du secteur d'information */
            l_result = mk_fat_utils_setInfo ( p_file );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si la chaine de cluster est corrompue */
      else if ( l_nextCluster < p_file->volume->partition.fat.firstRootDirectoryCluster )
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



