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
* @file mk_fat_utils_appendCluster.c
* @brief Définition de la fonction mk_fat_utils_appendCluster.
* @date 3 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_writeCluster ( T_mkFile* p_file, uint32_t p_lastClusterBlock, uint32_t p_lastClusterIndex, uint32_t p_freeClusterBlock, uint32_t p_freeCluster, uint32_t p_numberOfClusters )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_numberOfBytesWrite = 0;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = K_MK_NULL;

   /* Lecture d'un secteur de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_lastClusterBlock ) );

   /* Configuration du pointeur de buffer */
   l_buf = ( T_mkAddr ) p_file->buf;

   /* Ajout du nouveau cluster dans la chaine */
   l_buf [ p_lastClusterIndex ] = ( uint32_t ) p_freeCluster ;

   /* Si le secteur doit être actualisé */
   if ( ( l_result == K_MK_OK ) && ( ( p_numberOfClusters == 0 ) || ( p_lastClusterBlock != p_freeClusterBlock ) ) )
   {
      /* Ecriture de la première FAT */
      l_result = mk_fat_utils_writeCache ( p_file,  ( uint64_t ) ( p_lastClusterBlock ) );

      /* Pour le nombre de FAT à mettre à jour */
      for ( l_counter = 1 ; ( l_result == K_MK_OK ) && ( l_counter < p_file->volume->partition.fat.numberOfFAT ) && ( l_counter < K_MK_FAT_NUMBER_OF_FAT_TO_UPDATE ); l_counter++ )
      {
         /* Mise à jour des FATs auxiliaires  */
         /* La cache d'écriture n'est pas utilisé car deux appels consécutifs de la fonction d'écriture provoque une corruption */
         l_result = mk_fat_utils_write ( p_file, ( uint64_t ) ( p_lastClusterBlock + ( l_counter * p_file->volume->partition.fat.sectorsPerFAT ) ), p_file->buf, 1, &l_numberOfBytesWrite );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture d'un secteur de données */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_freeClusterBlock ) );
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

static T_mkCode mk_fat_utils_writeLastCluster ( T_mkFile* p_file, uint32_t p_lastClusterBlock, uint32_t p_lastClusterIndex, uint32_t p_freeClusterBlock, uint32_t p_numberOfClusters )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Ecriture de la valeur de fin de chaine dans le dernier cluster */
   l_result = mk_fat_utils_writeCluster ( p_file, p_lastClusterBlock, p_lastClusterIndex, p_freeClusterBlock, K_MK_FAT_LAST_CLUSTER, 0 );

   /* Si l'intégralité des clusters ont été ajoutés */
   if ( p_numberOfClusters != 0 )
   {
      /* Actualisation de la variable de retour */
      l_result |= K_MK_ERROR_NOT_AVAILABLE;
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

static T_mkCode mk_fat_utils_getNextFreeClusterBlock ( T_mkFile* p_file, uint32_t* p_freeClusterBlock, uint32_t p_freeClusterIndex, uint32_t p_endClusterIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la FAT a été entièrement analysée */
   if ( ( ( *p_freeClusterBlock ) >= ( p_file->volume->partition.fat.addressOfFAT + ( p_file->volume->partition.fat.sectorsPerFAT - 1 ) ) ) &&
        ( p_freeClusterIndex == p_endClusterIndex ) )
   {
      /* Réinitialisation de l'index du prochain cluster à analyser */
      p_file->volume->partition.fat.nextFreeCluster = K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS;

      /* Détermination de l'adresse du prochain bloc de recherche */
      ( *p_freeClusterBlock ) = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_file->volume->partition.fat.nextFreeCluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

      /* Lecture d'un nouveau bloc de données */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_freeClusterBlock ) );
   }

   /* Sinon */
   else
   {
      /* Si un nouveau secteur doit être chargé */
      if ( p_freeClusterIndex == ( p_file->volume->partition.fat.numberOfClusterEntriesPerSector - 1 ) )
      {
         /* Actualisation de l'adresse du nouveau secteur de recherche */
         ( *p_freeClusterBlock ) = ( uint32_t ) ( ( *p_freeClusterBlock ) + 1 );

         /* Lecture d'un secteur de données */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_freeClusterBlock ) );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getFreeCluster ( T_mkFile* p_file, uint32_t p_lastCluster, uint32_t* p_nextCluster, uint32_t p_numberOfClusters )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = K_MK_NULL;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_numberOfClusters = 0, l_endClusterIndex = 0, l_numberOfClustersToWrite = 0;
   uint32_t l_freeClusterBlock = 0, l_freeClusterIndex = 0, l_lastClusterBlock = 0, l_lastClusterIndex = 0;

   /* Détermination du nombre maximal de clusters */
   /* On ajoute les deux clusters réservés dans le compte */
   l_numberOfClusters = ( ( p_file->volume->partition.fat.numberOfAvailableSectors >> ( uint32_t ) p_file->volume->partition.fat.sSectorsPerCluster ) + K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS );
   l_numberOfClustersToWrite = p_numberOfClusters;

   /* Détermination de l'adresse et de l'index du cluster précédent */
   l_freeClusterBlock = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_file->volume->partition.fat.nextFreeCluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );
   l_lastClusterBlock = ( uint32_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_lastCluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );
   l_lastClusterIndex = ( uint32_t ) ( _math_mod2 ( p_lastCluster, p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

   /* Détermination de l'index du dernier cluster dans la FAT */
   /* La FAT comprend 3 clusters réservés non inclus dans le compte des clusters disponibles (l_numberOfClusters) */
   l_endClusterIndex = ( uint32_t ) ( _math_mod2 ( ( l_numberOfClusters - 1 ), p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

   /* Lecture d'un secteur de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) l_freeClusterBlock );

   /* Tant que l'analyse n'est pas terminée */
   while ( ( l_result == K_MK_OK ) && ( l_counter < l_numberOfClusters ) && ( l_numberOfClustersToWrite != 0 ) )
   {
      /* Actualisation de la valeur du pointeur */
      l_buf = ( T_mkAddr ) p_file->buf;

      /* Détermination de l'index du prochain cluster à analyser */
      /* Les 4 bits de poids fort de la variable 'nextFreeCluster' ont été remis à zéro à l'initialisation de la partition. */
      l_freeClusterIndex = ( uint32_t ) ( _math_mod2 ( p_file->volume->partition.fat.nextFreeCluster, p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

      /* Si le cluster est disponible */
      if ( ( l_buf [ l_freeClusterIndex ] & K_MK_FAT_CLUSTER_MASK ) == K_MK_FAT_FREE_CLUSTER )
      {
         /* Actualisation de la variable de retour */
         *p_nextCluster = ( p_file->volume->partition.fat.nextFreeCluster & K_MK_FAT_CLUSTER_MASK );

         /* Si le cluster n'est pas le premier cluster du fichier */
         if ( p_lastCluster != 0 )
         {
            /* Ecriture de la valeur du cluster disponible dans le dernier cluster */
            l_result = mk_fat_utils_writeCluster ( p_file, l_lastClusterBlock, l_lastClusterIndex, l_freeClusterBlock, p_file->volume->partition.fat.nextFreeCluster, l_numberOfClustersToWrite );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du nombre de clusters trouvés */
         l_numberOfClustersToWrite = ( uint32_t ) ( l_numberOfClustersToWrite - 1 );

         /* Actualisation de l'adresse du dernier cluster */
         l_lastClusterBlock = l_freeClusterBlock;

         /* Actualisation de l'index du dernier cluster */
         l_lastClusterIndex = l_freeClusterIndex;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de l'index du prochain cluster à analyser */
      p_file->volume->partition.fat.nextFreeCluster = ( uint32_t ) ( p_file->volume->partition.fat.nextFreeCluster + 1 );

      /* Détermination de l'adresse du prochain bloc de recherche */
      l_result = mk_fat_utils_getNextFreeClusterBlock ( p_file, &l_freeClusterBlock, l_freeClusterIndex, l_endClusterIndex );

      /* Actualisation du nombre de clusters analysés */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture de la valeur de fin de chaine dans le dernier cluster */
      l_result = mk_fat_utils_writeLastCluster ( p_file, l_lastClusterBlock, l_lastClusterIndex, l_freeClusterBlock, l_numberOfClustersToWrite );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Décrémentation du nombre de clusters libres */
   p_file->volume->partition.fat.numberOfFreeCluster = ( uint32_t ) ( p_file->volume->partition.fat.numberOfFreeCluster - ( p_numberOfClusters - l_numberOfClustersToWrite ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_appendCluster ( T_mkFile* p_file, uint32_t p_lastCluster, uint32_t* p_nextCluster, uint32_t p_numberOfClusters )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_nextCluster != K_MK_NULL ) &&
      ( ( ( p_lastCluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_lastCluster < K_MK_FAT_VALID_CLUSTER ) ) || ( p_lastCluster == 0 ) ) )
   {
      /* Si le nombre de clusters disponibles est suffisant pour traiter la requête de l'utilisateur */
      if ( p_file->volume->partition.fat.numberOfFreeCluster >= p_numberOfClusters )
      {
         /* Si au moins un cluster doit être ajouté */
         if ( p_numberOfClusters != 0 )
         {
            /* Récupération de la chaine de clusters */
            l_result = mk_fat_utils_getFreeCluster ( p_file, p_lastCluster, p_nextCluster, p_numberOfClusters );

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
         l_result = K_MK_ERROR_NOT_AVAILABLE;
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


