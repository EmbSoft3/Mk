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
* @file mk_fat_write.c
* @brief Définition de la fonction mk_fat_write.
* @date 6 juin 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_fat_getNewFileSize ( T_mkFile* p_file, uint32_t p_numberOfBytesToWrite )
{
   /* Détermination de la nouvelle taille du fichier */
   uint64_t l_result = ( uint64_t ) p_file->descriptor.fat.currentPointer + ( uint64_t ) p_numberOfBytesToWrite;

   /* Si la taille du fichier est supérieure à la limite */
   if ( l_result > K_MK_FAT_MAX_FILE_SIZE )
   {
      /* Limitation de la taille du fichier */
      l_result = K_MK_FAT_MAX_FILE_SIZE;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si l'écriture n'agrandit pas la taille du fichier */
   if ( l_result < ( uint64_t ) p_file->descriptor.fat.size )
   {
      /* On retourne la taille du fichier */
      l_result = ( uint64_t ) p_file->descriptor.fat.size;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( ( uint32_t ) l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */


static uint32_t mk_fat_getNewClusterNumber ( T_mkFile* p_file, uint32_t p_newFileSize )
{
   /* Déclaration des variables de travail */
   uint32_t l_clusterNumber = 0, l_newClusterNumber = 0;

   /* Détermination du nombre de clusters pour chaque taille de fichier */
   /* L'argument p_newFileSize est forcément supérieur ou égal à la taille du fichier */
   l_clusterNumber = ( uint32_t ) ( p_file->descriptor.fat.size >>
         ( p_file->volume->partition.fat.sBytesPerSector + p_file->volume->partition.fat.sSectorsPerCluster ) );
   l_newClusterNumber = ( uint32_t ) ( p_newFileSize >>
         ( p_file->volume->partition.fat.sBytesPerSector + p_file->volume->partition.fat.sSectorsPerCluster ) );

   /* Retour */
   return ( ( uint32_t ) ( l_newClusterNumber - l_clusterNumber ) );
}

/**
 * @internal
 * @brief
 * @endinternal
 */


static T_mkCode mk_fat_expandFile ( T_mkFile* p_file, uint32_t p_newFileSize, uint32_t p_newClusterNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si l'espace disponible sur le disque est suffisant pour réaliser l'écriture */
   if ( p_file->volume->partition.fat.numberOfFreeCluster >= p_newClusterNumber )
   {
      /* Si la nouvelle taille du fichier est supérieure à l'ancienne */
      if ( p_newFileSize > p_file->descriptor.fat.size )
      {
         /* Augmentation de la taille du fichier */
         /* On alloue les clusters avant l'écriture du fichier pour optimiser la fonction */
         l_result = mk_fat_expand ( p_file, p_newFileSize );
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
      l_result = K_MK_ERROR_FULL;
   }


   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_fat_getBlockAddress ( T_mkFile* p_file, uint32_t p_cluster, uint32_t p_sectorIndex )
{
   /* Détermination de l'adresse du bloc de données */
   uint32_t l_result = p_file->volume->partition.fat.addressOfRootDirectory +
      ( ( p_cluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster ) + p_sectorIndex;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_fat_writeChunk ( T_mkFile* p_file, uint8_t* p_buf, uint32_t p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfBytesWrite = 0;

   /* Récupération de l'adresse du disque stockant le fichier */
   T_mkDisk* l_disk = ( T_mkDisk* ) p_file->volume->disk;

   /* Si le buffer est aligné sur 32 bits ou si le périphérique supporte les accès non alignés */
   if ( ( l_disk->layer.peripheralAccess == K_MK_DISK_ACCESS_TYPE_UNALIGNED ) || ( ( ( uint32_t ) p_buf & 0x3 ) == 0 ) )
   {
      /* Ecriture des blocs de données sur le disque  */
      l_result = mk_fat_utils_write ( p_file, ( uint64_t ) p_blockAddress, p_buf, *p_blockNumber, &l_numberOfBytesWrite );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation du nombre d'octets restant à écrire */
         *p_numberOfBytesToWrite = ( uint32_t ) ( *p_numberOfBytesToWrite - l_numberOfBytesWrite );

         /* Actualisation du nombre d'octets écrits */
         *p_numberOfBytesWrite = ( uint32_t ) ( *p_numberOfBytesWrite + l_numberOfBytesWrite );

         /* Actualisation du pointeur de fichier */
         p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + l_numberOfBytesWrite );

         /* Actualisation du nombre de bloc à écrire */
         *p_blockNumber = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon (buffer non aligné sur 4 octets et accès non aligné non supporté) */
   else
   {
      /* Note : la routine ci-dessous est ajouté car la DMA du périphérique USB ne supporte pas les transferts */
      /* non alignés sur 32 bits. */

      /* Tant que des données doivent être écrite et tant qu'aucune erreur ne s'est produite */
      while ( ( ( *p_blockNumber ) != 0 ) && ( l_result == K_MK_OK ) )
      {
         /* Lecture d'un bloc de donnée */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_blockAddress ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Copie du buffer utilisateur dans le le câche */
            _copy ( p_file->buf, p_buf, p_file->volume->partition.fat.bytesPerSector );

            /* Ecriture d'un bloc de données */
            l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) ( p_blockAddress ) );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Actualisation du nombre de bloc à écrire */
               *p_blockNumber = ( uint32_t ) ( *p_blockNumber - 1 );

               /* Actualisation de l'adresse du prochain bloc de données */
               p_blockAddress = ( uint32_t ) ( p_blockAddress + 1 );

               /* Actualisation de l'adresse du buffer */
               p_buf = ( uint8_t* ) ( p_buf + p_file->volume->partition.fat.bytesPerSector );

               /* Actualisation du nombre d'octets restant à écrire */
               *p_numberOfBytesToWrite = ( uint32_t ) ( *p_numberOfBytesToWrite - p_file->volume->partition.fat.bytesPerSector );

               /* Actualisation du nombre d'octets écrits */
               *p_numberOfBytesWrite = ( uint32_t ) ( *p_numberOfBytesWrite + p_file->volume->partition.fat.bytesPerSector );

               /* Actualisation du pointeur de fichier */
               p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + p_file->volume->partition.fat.bytesPerSector );
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
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_writeFirstBlock ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite, uint32_t* p_blockAddress, uint32_t p_blockIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_bytesNumber = 0, l_blockOffset = 0;

   /* Détermination de l'offset du premier octet à écrire dans le bloc de données */
   l_blockOffset = _math_mod2 ( p_file->descriptor.fat.currentPointer, p_file->volume->partition.fat.sBytesPerSector );

   /* Détermination de l'adresse du premier bloc de données à écrire */
   *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.currentCluster, p_blockIndex );

   /* Lecture du premier bloc de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Détermination du nombre d'octets à écrire dans le premier bloc */
      l_bytesNumber = ( uint32_t ) ( p_file->volume->partition.fat.bytesPerSector - l_blockOffset );

      /* Si le nombre d'octet à écrire dans le premier bloc est supérieur au nombre d'octet demandé par l'utilisateur */
      if ( l_bytesNumber > ( *p_numberOfBytesToWrite ) )
      {
         /* Actualisation du nombre d'octets à écrire dans le premier bloc */
         l_bytesNumber = ( *p_numberOfBytesToWrite );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Copie des premiers octets du buffer utilisateur dans le cache */
      _copy ( &p_file->buf [ l_blockOffset ], p_buf, l_bytesNumber );

      /* Ecriture du bloc de données sur le disque */
      l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation de l'adresse du prochain bloc de données */
         *p_blockAddress = ( uint32_t ) ( ( *p_blockAddress ) + 1 );

         /* Actualisation du nombre d'octets à écrire */
         *p_numberOfBytesToWrite = ( uint32_t ) ( *p_numberOfBytesToWrite - l_bytesNumber );

         /* Actualisation du nombre d'octets écrits */
         *p_numberOfBytesWrite = ( uint32_t ) ( *p_numberOfBytesWrite + l_bytesNumber );

         /* Actualisation du pointeur de fichier */
         p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + l_bytesNumber );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_writeLastBlock ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesWrite, uint32_t* p_blockAddress )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Lecture du dernier bloc de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Copie des derniers octets du buffer utilisateur dans le cache */
      _copy ( p_file->buf, &p_buf [ *p_numberOfBytesWrite ], *p_numberOfBytesToRead );

      /* Ecriture du bloc de données */
      l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation du nombre d'octets écrits */
         *p_numberOfBytesWrite = ( uint32_t ) ( *p_numberOfBytesWrite + *p_numberOfBytesToRead );

         /* Actualisation du pointeur de fichier */
         p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + *p_numberOfBytesToRead );
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


/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_writeFirstCluster ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite  )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_blockIndex = 0, l_clusterOffset = 0, l_numberOfBytesAvailable = 0;

   /* Détermination de l'index du premier bloc de données à écrire dans le cluster */
   l_blockIndex = _math_mod2 ( p_file->descriptor.fat.currentPointer >> p_file->volume->partition.fat.sBytesPerSector, p_file->volume->partition.fat.sSectorsPerCluster );

   /* Ecriture du premier bloc de données */
   /* Le pointeur de fichier est obligatoirement aligné sur la taille d'un bloc */
   l_result = mk_fat_writeFirstBlock ( p_file, p_buf, p_numberOfBytesToWrite, p_numberOfBytesWrite, p_blockAddress, l_blockIndex );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si des nouveaux blocs de données peuvent être écrit dans le premier cluster ET si le nombre de données à écrire est supérieur à la taille d'un secteur. */
      if ( ( ( l_blockIndex + 1 ) < p_file->volume->partition.fat.sectorsPerCluster ) && ( ( *p_numberOfBytesToWrite ) > p_file->volume->partition.fat.bytesPerSector ) )
      {
         /* Dans ce bloc, au moins un secteur du cluster courant peut être écrit. Le nombre d'octets à écrire est supérieur à la taille d'un secteur. */
         /* Détermination du nombre de blocs restant à écrire dans le cluster*/
         *p_blockNumber = ( uint32_t ) ( p_file->volume->partition.fat.sectorsPerCluster - l_blockIndex - 1 );

         /* Détermination du nombre d'octets disponibles dans le cluster */
         l_numberOfBytesAvailable = ( uint32_t ) ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector );

         /* Si le nombre d'octets restant à écrire est inférieur au nombre d'octets disponibles dans le cluster */
         if ( ( *p_numberOfBytesToWrite ) < l_numberOfBytesAvailable )
         {
            /* Détermination du nombre de blocs de données restant à écrire */
            *p_blockNumber = ( *p_numberOfBytesToWrite ) >> p_file->volume->partition.fat.sBytesPerSector;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Le but est de limiter le nombre de requêtes effectuées. */
         /* Si l'adresse du prochain cluster n'est pas consécutive au cluster courant et si le nombre de données restant à écrire est supérieur ou égale au nombre */
         /* d'octets disponibles dans le cluster. */
         if ( ( p_file->descriptor.fat.clusterMap [ 0 ] != ( p_file->descriptor.fat.currentCluster + 1 ) ) && ( ( *p_numberOfBytesToWrite ) >= l_numberOfBytesAvailable ) )
         {
            /* Ecriture des blocs de données sur le disque */
            l_result = mk_fat_writeChunk ( p_file, &p_buf [ *p_numberOfBytesWrite ], *p_blockAddress, p_blockNumber, p_numberOfBytesToWrite, p_numberOfBytesWrite );

            /* Détermination de l'adresse du prochain bloc de données à écrire */
            *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.clusterMap [ 0 ], 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Détermination de l'offset du pointeur de fichier dans le cluster */
         l_clusterOffset = _math_mod2 ( p_file->descriptor.fat.currentPointer + ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector ),
                                       p_file->volume->partition.fat.sClusterSize );

         /* Si l'écriture du cluster est terminée */
         if ( ( l_clusterOffset == 0 ) && ( p_file->descriptor.fat.clusterMap [ 0 ] != K_MK_FAT_LAST_CLUSTER ) )
         {
            /* Actualisation du cluster courant */
            p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.clusterMap [ 0 ];
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
         /* Dans ce bloc, le premier cluster est plein. Les dernières données seront écrites par la fonction mk_fat_readLastBlock. */
         /* Si un nouveau cluster doit être chargé */
         if ( ( ( l_blockIndex + 1 ) == p_file->volume->partition.fat.sectorsPerCluster ) && ( p_file->descriptor.fat.clusterMap [ 0 ] != K_MK_FAT_LAST_CLUSTER ) )
         {
            /* Actualisation du cluster courant */
            p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.clusterMap [ 0 ];

            /* Détermination de l'adresse du prochain bloc de données à écrire */
            *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.clusterMap [ 0 ], 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_writeCurrentClusters ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_clusterIndex = 1, l_numberOfByteToWrite = 0;

   /* Lors de l'arrivée dans cette fonction, l'écriture d'un nombre de bloc 'p_blockNumber' peut avoir été temporisée */
   /* Dans le cas où le nombre d'octets restants à écrire est inférieur à la taille d'un cluster, la boucle n'est pas exécutée. */
   /* De même, lorsque le fichier possède un seul cluster (currentCluster = 0). */

   /* Détermination du nombre de données à écrire */
   l_numberOfByteToWrite = ( uint32_t ) ( ( *p_numberOfBytesToWrite ) - ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector ) );

   /* Tant qu'aucune erreur ne s'est produite et tant qu'un cluster entier peut être écrit */
   while ( ( l_result == K_MK_OK ) && ( l_numberOfByteToWrite >= p_file->volume->partition.fat.clusterSize ) && ( p_file->descriptor.fat.currentCluster != 0 ) )
   {
      /* Actualisation du nombre de bloc à écrire (1 cluster supplémentaire) */
      *p_blockNumber = ( uint32_t ) ( ( *p_blockNumber ) + p_file->volume->partition.fat.sectorsPerCluster );

      /* Si l'adresse du prochain cluster n'est pas consécutive au cluster courant */
      if ( p_file->descriptor.fat.clusterMap [ l_clusterIndex ] != ( p_file->descriptor.fat.currentCluster + 1 ) )
      {
         /* Ecriture des blocs de données sur le disque */
         l_result = mk_fat_writeChunk ( p_file, &p_buf [ *p_numberOfBytesWrite ], *p_blockAddress, p_blockNumber, p_numberOfBytesToWrite, p_numberOfBytesWrite );

         /* Détermination de l'adresse du prochain bloc de données à écrire */
         *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.clusterMap [ l_clusterIndex ], 0 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du nombre de données à écrire */
      l_numberOfByteToWrite = ( uint32_t ) ( l_numberOfByteToWrite - p_file->volume->partition.fat.clusterSize );

      /* Si aucune erreur ne s'est produite et si la chaine de clusters n'est pas terminée */
      if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.clusterMap [ l_clusterIndex ] < K_MK_FAT_VALID_CLUSTER ) )
      {
         /* Actualisation de la valeur du cluster courant */
         p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.clusterMap [ l_clusterIndex ];

         /* Si la chaine de clusters est terminée */
         if ( l_clusterIndex == ( K_MK_FAT_CLUSTER_MAP_LENGTH - 1 ) )
         {
            /* Récupération d'une nouvelle chaine de cluster */
            l_result = mk_fat_utils_getCluster ( p_file, p_file->descriptor.fat.currentCluster, p_file->descriptor.fat.clusterMap, K_MK_FAT_CLUSTER_MAP_LENGTH );

            /* Actualisation de l'index du cluster dans la chaine */
            l_clusterIndex = 0;
         }

         /* Sinon */
         else
         {
            /* Passage au prochain cluster */
            l_clusterIndex = ( uint32_t ) ( l_clusterIndex + 1 );
         }
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

static T_mkCode mk_fat_writeLastCluster ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Détermination du nombre de blocs restant à écrire */
   /* Si le dernier cluster n'était pas consécutif au précédent alors la variable 'p_blockNumber' est nulle */
   uint32_t l_blockNumber = ( uint32_t ) ( ( ( *p_numberOfBytesToWrite ) - ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector ) ) >> p_file->volume->partition.fat.sBytesPerSector );

   /* Détermination du nombre de blocs restant à écrire */
   *p_blockNumber = ( uint32_t ) ( ( *p_blockNumber ) + l_blockNumber );

   /* Si au moins un bloc de données doit être écrit */
   if ( ( *p_blockNumber ) != 0 )
   {
      /* Enregistrement du nombre de bloc à écrire */
      l_blockNumber = ( *p_blockNumber );

      /* Ecriture des blocs de données sur le disque */
      l_result = mk_fat_writeChunk ( p_file, &p_buf [ *p_numberOfBytesWrite ], *p_blockAddress, p_blockNumber, p_numberOfBytesToWrite, p_numberOfBytesWrite );

      /* Actualisation de l'adresse du prochain bloc de données */
      *p_blockAddress = ( uint32_t ) ( ( *p_blockAddress ) + l_blockNumber );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite et si au moins un autre bloc de données supplémentaires doit être écrit */
   if ( ( l_result == K_MK_OK ) && ( ( *p_numberOfBytesToWrite ) != 0 ) )
   {
      /* Ecriture du dernier blocs de données */
      l_result = mk_fat_writeLastBlock ( p_file, p_buf, p_numberOfBytesToWrite, p_numberOfBytesWrite, p_blockAddress );
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

T_mkCode mk_fat_write ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration des variables de travail */
   uint32_t l_blockAddress = 0, l_blockNumber = 0, l_newFileSize = 0, l_newClusterNumber = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_buf != K_MK_NULL ) && ( p_numberOfBytesWrite != K_MK_NULL ) && ( ( ( uint32_t ) p_buf & 0x3 ) == 0 ) )
   {
      /* Réinitialisation du nombre d'octets écrits */
      *p_numberOfBytesWrite = 0;

      /* Si le fichier peut être accédé en écriture */
      if ( p_file->flag.write == 1 )
      {
         /* Détermination de la nouvelle taille du fichier suite à l'écriture */
         l_newFileSize = mk_fat_getNewFileSize ( p_file, p_numberOfBytesToWrite );

         /* Détermination du nombre de nouveau clusters */
         l_newClusterNumber = mk_fat_getNewClusterNumber ( p_file, l_newFileSize );

         /* Si le nombre d'octets à écrire est non nul */
         if ( p_numberOfBytesToWrite != 0 )
         {
            /* Vérification de l'espace disponible sur le disque et augmentation de la taille du fichier */
            /* On alloue l'ensemble des nouveaux clusters */
            l_result = mk_fat_expandFile ( p_file, l_newFileSize, l_newClusterNumber );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Récupération de la chaine de clusters */
               l_result = mk_fat_utils_getCluster ( p_file, p_file->descriptor.fat.currentCluster, p_file->descriptor.fat.clusterMap, K_MK_FAT_CLUSTER_MAP_LENGTH );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Ecriture du premier cluster */
                  l_result = mk_fat_writeFirstCluster ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToWrite, p_numberOfBytesWrite );

                  /* Si aucune erreur ne s'est produite */
                  if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.currentCluster < K_MK_FAT_VALID_CLUSTER ) )
                  {
                     /* Ecriture des clusters intermédiaires */
                     l_result = mk_fat_writeCurrentClusters ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToWrite, p_numberOfBytesWrite );

                     /* Si aucune erreur ne s'est produite */
                     if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.currentCluster < K_MK_FAT_VALID_CLUSTER ) )
                     {
                        /* Ecriture du dernier cluster */
                        l_result = mk_fat_writeLastCluster ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToWrite, p_numberOfBytesWrite );

                        /* Si aucune erreur ne s'est produite */
                        if ( l_result == K_MK_OK )
                        {
                           /* Commutation du drapeau indiquant que le fichier a été modifié */
                           p_file->flag.modified = 1;

                           /* Mise à jour des secteurs présents dans le cache */
                           l_result = mk_fat_utils_sync ( p_file );
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
         l_result = K_MK_ERROR_DENIED;
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




