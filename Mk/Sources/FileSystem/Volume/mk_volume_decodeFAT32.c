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
* @file mk_volume_decodeFAT32.c
* @brief Définition de la fonction mk_volume_decodeFAT32.
* @date 29 mai 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_setFAT32Identifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de l'identifiant unique de la partition */
   *p_identifier = ( uint16_t ) ( ( K_MK_VOLUME_MAX_NUMBER - 1 ) - ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_copyFAT32Attributes ( T_mkVolume* p_volume, uint8_t* p_buf )
{
   /* Le champ maximumNumberOfRootDirectoryEntries n'est pas dédié à une partition FAT32 */
   /* Il conserve une valeur nulle. */

   /* Récupération du nom de la partition */
   _copy ( p_volume->partition.fat.label, &p_buf [ K_MK_VOLUME_FAT32_VOLUME_NAME_OFFSET ], K_MK_VOLUME_FAT32_MAX_VOLUME_NAME_LENGTH );

   /* Récupération du nombre d'octets par secteur */
   _copy ( &p_volume->partition.fat.bytesPerSector, &p_buf [ K_MK_VOLUME_FAT32_BYTES_PER_SECTOR_OFFSET ], 2 );

   /* Récupération du nombre de secteurs par cluster */
   _copy ( &p_volume->partition.fat.sectorsPerCluster, &p_buf [ K_MK_VOLUME_FAT32_SECTORS_PER_CLUSTER_OFFSET ], 1 );

   /* Récupération du nombre de secteurs réservés */
   _copy ( &p_volume->partition.fat.numberOfReservedSectors, &p_buf [ K_MK_VOLUME_FAT32_NUMBER_OF_RESERVED_SECTORS_OFFSET ], 2 );

   /* Récupération du nombre de FAT */
   _copy ( &p_volume->partition.fat.numberOfFAT, &p_buf [ K_MK_VOLUME_FAT32_NUMBER_OF_FAT_OFFSET ], 1 );

   /* Récupération du nombre de secteurs dans la partition */
   _copy ( &p_volume->partition.fat.totalNumberOfSectors, &p_buf [ K_MK_VOLUME_FAT32_TOTAL_NUMBER_OF_SECTORS_OFFSET ], 4 );

   /* Récupération du nombre de secteurs par FAT */
   _copy ( &p_volume->partition.fat.sectorsPerFAT, &p_buf [ K_MK_VOLUME_FAT32_SECTORS_PER_FAT_OFFSET ], 4 );

   /* Récupération de l'index du premier cluster du répertoire racine */
   _copy ( &p_volume->partition.fat.firstRootDirectoryCluster, &p_buf [ K_MK_VOLUME_FAT32_FIRST_ROOT_DIRECTORY_CLUSTER_OFFSET ], 4 );

   /* Récupération de l'adresse du secteur d'information de la partition */
   _copy ( &p_volume->partition.fat.addressOfInformationSector, &p_buf [ K_MK_VOLUME_FAT32_ADDRESS_OF_INFORMATION_SECTOR_OFFSET ], 2 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_decodeFAT32Attributes ( T_mkVolume* p_volume, uint32_t p_firstPartitionSector )
{
   /* Détermination de la taille d'un cluster */
   p_volume->partition.fat.clusterSize = ( uint32_t ) ( ( uint32_t ) p_volume->partition.fat.bytesPerSector * ( uint32_t ) p_volume->partition.fat.sectorsPerCluster );

   /* Enregistrement de l'adresse de BPB */
   p_volume->partition.fat.addressOfBPB = p_firstPartitionSector;

   /* Enregistrement de l'adresse de la première FAT */
   p_volume->partition.fat.addressOfFAT = p_volume->partition.fat.addressOfBPB + p_volume->partition.fat.numberOfReservedSectors;

   /* Détermination de l'adresse du premier secteur d'information */
   p_volume->partition.fat.addressOfInformationSector = p_volume->partition.fat.addressOfBPB + p_volume->partition.fat.addressOfInformationSector;

   /* Enregistrement de l'adresse du répertoire racine */
   p_volume->partition.fat.addressOfRootDirectory = p_volume->partition.fat.addressOfFAT + ( p_volume->partition.fat.numberOfFAT * p_volume->partition.fat.sectorsPerFAT );

   /* Détermination du nombre d'entrées par secteur */
   p_volume->partition.fat.numberOfEntriesPerSector = p_volume->partition.fat.bytesPerSector / K_MK_FAT_ENTRY_SIZE;

   /* Détermination du nombre d'entrées de cluster par secteur */
   p_volume->partition.fat.numberOfClusterEntriesPerSector = p_volume->partition.fat.bytesPerSector / K_MK_FAT_CLUSTER_ENTRY_SIZE;

   /* Détermination du nombre de blocs de données par fenêtre */
   p_volume->partition.fat.numberOfBlocksPerWindow = ( uint32_t ) ( K_MK_FILE_MAX_BLOCK_LENGTH / p_volume->partition.fat.bytesPerSector );

   /* Détermination de la valeur du décalage du nombre d'octets par secteur */
   p_volume->partition.fat.sBytesPerSector = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.bytesPerSector );

   /* Détermination de la valeur du décalage du nombre de secteurs par cluster */
   p_volume->partition.fat.sSectorsPerCluster = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.sectorsPerCluster );

   /* Détermination de la valeur du décalage de la taille d'un cluster */
   p_volume->partition.fat.sClusterSize = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.clusterSize );

   /* Détermination de la valeur du décalage du nombre d'entrées par secteur */
   p_volume->partition.fat.sNumberOfEntriesPerSector = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.numberOfEntriesPerSector );

   /* Détermination de la valeur du décalage du nombre de cluster par secteur */
   p_volume->partition.fat.sNumberOfClusterEntriesPerSector = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.numberOfClusterEntriesPerSector );

   /* Détermination du nombre de secteurs disponibles dans la partition */
   p_volume->partition.fat.numberOfAvailableSectors = ( uint32_t ) ( p_volume->partition.fat.totalNumberOfSectors - ( uint32_t ) p_volume->partition.fat.numberOfReservedSectors -
        ( uint32_t ) ( ( uint32_t ) p_volume->partition.fat.numberOfFAT * ( uint32_t ) p_volume->partition.fat.sectorsPerFAT ) );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_getNumberOfFreeClusters ( T_mkVolume* p_volume, uint8_t* p_buf, uint32_t* p_freeCluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_numberOfClusters = 0, l_numberOfClustersPerWindow = 0, l_currentClusterIndex = 0, l_block = 0, l_counter = 0;
   uint64_t l_numberOfBytesRead = 0;

   /* Configuration du pointeur de buffer */
   uint32_t* l_buf = ( T_mkAddr ) p_buf;

   /* Détermination de l'adresse du premier bloc à lire */
   l_block = p_volume->partition.fat.addressOfFAT;

   /* Détermination du nombre maximal de clusters */
   /* On ajoute les deux clusters réservés dans le compte */
   l_numberOfClusters = ( ( p_volume->partition.fat.numberOfAvailableSectors >> ( uint32_t ) p_volume->partition.fat.sSectorsPerCluster ) + K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS );

   /* Détermination du nombre de clusters par fenêtre */
   l_numberOfClustersPerWindow = ( uint8_t ) _math_div2shift ( ( uint32_t ) p_volume->partition.fat.numberOfClusterEntriesPerSector * p_volume->partition.fat.numberOfBlocksPerWindow );

   /* Initialisation de la variable de retour */
   *p_freeCluster = 0;

   /* Tant que l'analyse n'est pas terminée */
   while ( ( l_result == K_MK_OK ) && ( l_counter < l_numberOfClusters ) )
   {
      /* Détermination de l'index du prochain cluster à analyser */
      l_currentClusterIndex = ( uint32_t ) ( _math_mod2 ( l_counter, l_numberOfClustersPerWindow ) );

      /* Si un nouveau secteur doit être lu */
      if ( l_currentClusterIndex == 0 )
      {
         /* Lecture d'un groupe de secteur sur le disque */
         l_result = mk_disk_readSector ( ( T_mkDisk* ) p_volume->disk, ( uint64_t ) l_block, l_buf, p_volume->partition.fat.numberOfBlocksPerWindow, &l_numberOfBytesRead );

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result != K_MK_OK ) || ( l_numberOfBytesRead != ( p_volume->partition.fat.numberOfBlocksPerWindow * p_volume->partition.fat.bytesPerSector ) ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_COMM;
         }

         /* Sinon */
         else
         {
            /* Actualisation de l'adresse du prochain blocs de données */
            l_block = ( uint32_t ) ( l_block + p_volume->partition.fat.numberOfBlocksPerWindow );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le cluster est disponible */
      if ( l_buf [ l_currentClusterIndex ] == K_MK_FAT_FREE_CLUSTER )
      {
         /* Actualisation du nombre de clusters libre */
         *p_freeCluster = ( uint32_t ) ( ( *p_freeCluster ) + 1 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du nombre de clusters analysés */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_getVolumeInformation ( T_mkDisk* p_disk, T_mkVolume* p_volume, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = ( T_mkAddr ) p_buf;

   /* Déclaration des variables de travail */
   uint32_t l_local = 0, l_numberOfClusters = 0;
   uint64_t l_numberOfBytesRead = 0;

   /* Enregistrement de l'adresse du premier cluster disponible */
   /* La recherche du prochain cluster disponible commence à partir de cet index. */
   p_volume->partition.fat.nextFreeCluster = K_MK_VOLUME_FAT32_FIRST_CLUSTER;
   p_volume->partition.fat.numberOfFreeCluster = ( uint32_t ) ( p_volume->partition.fat.numberOfAvailableSectors / ( uint32_t ) p_volume->partition.fat.sectorsPerCluster );

   /* Lecture du premier secteur de la partition. */
   l_result = mk_disk_readSector ( p_disk, ( uint64_t ) p_volume->partition.fat.addressOfInformationSector, p_buf, 1, &l_numberOfBytesRead );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead == p_disk->attribute.blockLength )  )
   {
      /* Si le secteur d'information n'est pas corrompu */
      if ( l_buf [ ( K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE_OFFSET >> 2 ) ] == K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE )
      {
         /* Analyse de la validité du secteur d'information (1ere signature) */
         l_local  = mk_utils_strcomp ( ( T_str8 ) &p_buf [ K_MK_VOLUME_FAT32_FSINFORMATION_FIRST_LABEL_OFFSET ], ( T_str8 ) "RRaA", 0, 4 );

         /* Si le secteur d'information est valide */
         if ( l_local == 1 )
         {
            /* Analyse de la validité du secteur d'information (2eme signature) */
            l_local = mk_utils_strcomp ( ( T_str8 ) &p_buf [ K_MK_VOLUME_FAT32_FSINFORMATION_SECOND_LABEL_OFFSET ], ( T_str8 ) "rrAa", 0, 4 );

            /* Si le secteur d'information est valide */
            if ( l_local == 1 )
            {
               /* Détermination du nombre maximal de clusters */
               l_numberOfClusters = ( p_volume->partition.fat.numberOfAvailableSectors / ( uint32_t ) p_volume->partition.fat.sectorsPerCluster );

               /* Récupération du nombre de clusters disponibles */
               _copy ( &p_volume->partition.fat.numberOfFreeCluster, &p_buf [ K_MK_VOLUME_FAT32_FSINFORMATION_NUMBER_OF_FREE_CLUSTERS_OFFSET ], 4 );

               /* Récupération de l'adresse du prochain cluster disponible */
               _copy ( &p_volume->partition.fat.nextFreeCluster, &p_buf [ K_MK_VOLUME_FAT32_FSINFORMATION_NEXT_FREE_CLUSTER_OFFSET ], 4 );

               /* Si l'adresse du prochain cluster disponible est invalide */
               if ( p_volume->partition.fat.numberOfFreeCluster == 0xFFFFFFFF )
               {
                  /* La recherche du prochain cluster disponible commence à la valeur par défaut */
                  p_volume->partition.fat.nextFreeCluster = K_MK_VOLUME_FAT32_FIRST_CLUSTER;
               }

               /* Sinon */
               else
               {
                  /* Suppression de la valeur des 4 bits de poids fort du cluster (28bits) */
                  p_volume->partition.fat.nextFreeCluster = ( uint32_t ) ( p_volume->partition.fat.nextFreeCluster & K_MK_FAT_CLUSTER_MASK );
               }

               /* Si le nombre de cluster disponible est invalide */
               if ( ( p_volume->partition.fat.numberOfFreeCluster > l_numberOfClusters ) || ( p_volume->partition.fat.numberOfFreeCluster == 0xFFFFFFFF ) )
               {
                  /* Récupération du nombre de clusters disponibles par analyse de la FAT */
                  l_result = mk_volume_getNumberOfFreeClusters ( p_volume, p_buf, &p_volume->partition.fat.numberOfFreeCluster );
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
               /* Actualisation du registre de statut de la partition */
               p_volume->status = K_MK_VOLUME_NOT_SUPPORTED;
            }
         }

         /* Sinon */
         else
         {
            /* Actualisation du registre de statut de la partition */
            p_volume->status = K_MK_VOLUME_NOT_SUPPORTED;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation du registre de statut de la partition */
         p_volume->status = K_MK_VOLUME_CORRUPTED;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COMM;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_volume_decodeFAT32 ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables stockant la dénomination système du disque */
   char8_t l_str [ 4 ] = "vol";
   char8_t l_strIdentifier [ 4 ] = "";

   /* Déclaration des variables de travail */
   uint32_t l_local = 0, l_numberOfClusters = 0;

   /* Déclaration d'un pointeur de partition */
   T_mkVolume* l_volume;

   /* Si le paramètre est valide */
   if ( p_list != K_MK_NULL )
   {
      /* Allocation d'une nouvelle partition */
      l_result = mk_pool_allocSafe ( g_mkVolumePool.pool, ( T_mkAddr ) &l_volume, K_MK_POOL_CLEAR, 0 );

      /* Si l'allocation a réussi */
      if ( ( l_result == K_MK_OK ) && ( l_volume != K_MK_NULL ) )
      {
         /* Configuration du type de la partition */
         l_volume->type = K_MK_VOLUME_TYPE_FAT32;

         /* Configuration du type applicatif */
         l_volume->layer.type = K_MK_CONTROL_VOLUME;

         /* Configuration de l'adresse du disque */
         l_volume->disk = p_disk;

         /* Configuration de l'identifiant de la partition FAT32 */
         mk_volume_setFAT32Identifier ( &l_volume->layer.id, l_volume, g_mkVolumePool.heap, sizeof ( T_mkVolume ) );

         /* Récupération d'un identifiant système unique */
         l_volume->name.id = mk_volume_getSystemIdentifier ( *p_list );

         /* Conversion et stockage de l'identifiant en chaine de caractères */
         mk_utils_itoa ( ( uint32_t ) l_volume->name.id, ( T_str8 ) l_strIdentifier, 10, 1 );
         mk_utils_strcat ( ( T_str8 ) l_volume->name.str, ( T_str8 ) l_str, ( T_str8 ) l_strIdentifier );

         /* Copie des attributs FAT32 dans le volume */
         mk_volume_copyFAT32Attributes ( l_volume, p_buf );

         /* Décodage des attributs de la partition */
         mk_volume_decodeFAT32Attributes ( l_volume, p_firstPartitionSector );

         /* Analyse de la taille d'un secteur */
         l_local = mk_utils_check2 ( ( uint32_t ) l_volume->partition.fat.bytesPerSector, K_MK_VOLUME_FAT32_MIN_BLOCK_LENGTH, K_MK_VOLUME_FAT32_MAX_BLOCK_LENGTH );

         /* Analyse de la taille d'un cluster */
         l_local |= mk_utils_check2 ( ( uint32_t ) l_volume->partition.fat.sectorsPerCluster, K_MK_VOLUME_FAT32_MIN_SECTOR_PER_CLUSTER, K_MK_VOLUME_FAT32_MAX_SECTOR_PER_CLUSTER );

         /* Détermination du nombre maximal de clusters */
         l_numberOfClusters = ( l_volume->partition.fat.numberOfAvailableSectors / ( uint32_t ) l_volume->partition.fat.sectorsPerCluster );

         /* Si le volume n'est pas supporté */
         if ( ( l_local != 0 ) || ( l_volume->partition.fat.bytesPerSector != p_disk->attribute.blockLength ) || ( l_volume->partition.fat.clusterSize > K_MK_VOLUME_FAT32_MAX_CLUSTER_SIZE ) ||
              ( l_volume->partition.fat.firstRootDirectoryCluster < K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS ) || ( l_numberOfClusters < K_MK_FAT_MIN_NUMBER_OF_CLUSTERS ) )
         {
            /* Actualisation du registre de statut de la partition */
            l_volume->status = K_MK_VOLUME_NOT_SUPPORTED;
         }

         /* Sinon */
         else
         {
            /* Récupération des informations relatives au secteur d'information (prochain cluster disponible et au nombre de clusters disponibles dans la partition) */
            l_result = mk_volume_getVolumeInformation ( p_disk, l_volume, p_buf );
         }

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( l_volume->status != K_MK_VOLUME_NOT_SUPPORTED ) )
         {
            /* Comparaison du nom de la partition */
            l_local = mk_utils_strcomp ( ( T_str8 ) l_volume->partition.fat.label, ( T_str8 ) "MK_SYSTEM", 0, 9 );

            /* Si le partition est la partition système */
            if ( l_local == 1 )
            {
               /* Enregistrement de l'adresse de la partition système */
               g_mkSystemVolume = l_volume;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du registre de statut de la partition */
            l_volume->status = K_MK_VOLUME_READY;

            /* Ajout de la nouvelle partition dans la liste des partitions du disque */
            l_result = mk_volume_add ( p_list, l_volume );
         }

         /* Sinon */
         else
         {
            /* Désallocation de la partition */
            l_result |= mk_pool_freeSafe ( g_mkVolumePool.pool, l_volume );
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
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


