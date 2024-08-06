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
* @file mk_fat_read.c
* @brief Définition de la fonction mk_fat_read.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_fat_getNumberOfBytesToRead ( T_mkFile* p_file, uint32_t p_numberOfBytesToRead )
{
   /* Détermination de la taille disponible dans le fichier */
   uint32_t l_result = p_file->descriptor.fat.size - p_file->descriptor.fat.currentPointer;

   /* Si la taille disponible est inférieure au nombre d'octets demandés */
   if ( l_result > p_numberOfBytesToRead )
   {
      /* On borne le nombre d'octets à lire */
      l_result = p_numberOfBytesToRead;
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

static uint32_t mk_fat_readChunk ( T_mkFile* p_file, uint8_t* p_buf, uint32_t p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Récupération de l'adresse du disque stockant le fichier */
   T_mkDisk* l_disk = ( T_mkDisk* ) p_file->volume->disk;

   /* Si le buffer est aligné sur 32 bits ou si le périphérique supporte les accès non alignés */
   if ( ( l_disk->layer.peripheralAccess == K_MK_DISK_ACCESS_TYPE_UNALIGNED ) || ( ( ( uint32_t ) p_buf & 0x3 ) == 0 ) )
   {
      /* Lecture des blocs de données sur le disque  */
      l_result = mk_fat_utils_read ( p_file, ( uint64_t ) p_blockAddress, p_buf, *p_blockNumber, &l_numberOfBytesRead );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation du nombre d'octets restant à lire */
         *p_numberOfBytesToRead = ( uint32_t ) ( *p_numberOfBytesToRead - l_numberOfBytesRead );

         /* Actualisation du nombre d'octets lus */
         *p_numberOfBytesRead = ( uint32_t ) ( *p_numberOfBytesRead + l_numberOfBytesRead );

         /* Actualisation du pointeur de fichier */
         p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + l_numberOfBytesRead );

         /* Actualisation du nombre de bloc à lire */
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

      /* Tant que des données doivent être lue et tant qu'aucune erreur ne s'est produite */
      while ( ( ( *p_blockNumber ) != 0 ) && ( l_result == K_MK_OK ) )
      {
         /* Lecture d'un bloc de donnée */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_blockAddress ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Copie des octets dans le buffer utilisateur */
            _copy ( p_buf, p_file->buf, p_file->volume->partition.fat.bytesPerSector );

            /* Actualisation du nombre de bloc à lire */
            *p_blockNumber = ( uint32_t ) ( *p_blockNumber - 1 );

            /* Actualisation de l'adresse du prochain bloc de données */
            p_blockAddress = ( uint32_t ) ( p_blockAddress + 1 );

            /* Actualisation de l'adresse du buffer */
            p_buf = ( uint8_t* ) ( p_buf + p_file->volume->partition.fat.bytesPerSector );

            /* Actualisation du nombre d'octets restant à lire */
            *p_numberOfBytesToRead = ( uint32_t ) ( *p_numberOfBytesToRead - p_file->volume->partition.fat.bytesPerSector );

            /* Actualisation du nombre d'octets lus */
            *p_numberOfBytesRead = ( uint32_t ) ( *p_numberOfBytesRead + p_file->volume->partition.fat.bytesPerSector );

            /* Actualisation du pointeur de fichier */
            p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + p_file->volume->partition.fat.bytesPerSector );
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

static T_mkCode mk_fat_readFirstBlock ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead, uint32_t* p_blockAddress, uint32_t p_blockIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_bytesNumber = 0, l_blockOffset = 0;

   /* Détermination de l'offset du premier octet à lire dans le bloc de données */
   l_blockOffset = _math_mod2 ( p_file->descriptor.fat.currentPointer, p_file->volume->partition.fat.sBytesPerSector );

   /* Détermination de l'adresse du premier bloc de données à lire */
   *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.currentCluster, p_blockIndex );

   /* Lecture du premier bloc de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Détermination du nombre d'octets à lire dans le premier bloc */
      l_bytesNumber = ( uint32_t ) ( p_file->volume->partition.fat.bytesPerSector - l_blockOffset );

      /* Si le nombre d'octet à lire dans le premier bloc est supérieur au nombre d'octets demandés par l'utilisateur */
      if ( l_bytesNumber > ( *p_numberOfBytesToRead ) )
      {
         /* Actualisation du nombre d'octets à lire dans le premier bloc */
         l_bytesNumber = ( *p_numberOfBytesToRead );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Copie des premiers octets dans le buffer utilisateur */
      _copy ( p_buf, &p_file->buf [ l_blockOffset ], l_bytesNumber );

      /* Actualisation de l'adresse du prochain bloc de données */
      *p_blockAddress = ( uint32_t ) ( ( *p_blockAddress ) + 1 );

      /* Actualisation du nombre d'octets à lire */
      *p_numberOfBytesToRead = ( uint32_t ) ( *p_numberOfBytesToRead - l_bytesNumber );

      /* Actualisation du nombre d'octets lus */
      *p_numberOfBytesRead = ( uint32_t ) ( *p_numberOfBytesRead + l_bytesNumber );

      /* Actualisation du pointeur de fichier */
      p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + l_bytesNumber );
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

static T_mkCode mk_fat_readLastBlock ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead, uint32_t* p_blockAddress )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Lecture du dernier bloc de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_blockAddress ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Copie des derniers octets dans le buffer utilisateur */
      _copy ( &p_buf [ *p_numberOfBytesRead ], p_file->buf, *p_numberOfBytesToRead );

      /* Actualisation du nombre d'octets lus */
      *p_numberOfBytesRead = ( uint32_t ) ( *p_numberOfBytesRead + *p_numberOfBytesToRead );

      /* Actualisation du pointeur de fichier */
      p_file->descriptor.fat.currentPointer = ( uint32_t ) ( p_file->descriptor.fat.currentPointer + *p_numberOfBytesToRead );
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

static T_mkCode mk_fat_readFirstCluster ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead  )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_blockIndex = 0, l_clusterOffset = 0, l_numberOfBytesAvailable = 0;

   /* Détermination de l'index du premier bloc de données à lire dans le cluster */
   l_blockIndex = _math_mod2 ( p_file->descriptor.fat.currentPointer >> p_file->volume->partition.fat.sBytesPerSector, p_file->volume->partition.fat.sSectorsPerCluster );

   /* Lecture du premier bloc de données */
   /* Le pointeur de fichier est obligatoirement aligné sur la taille d'un bloc */
   l_result = mk_fat_readFirstBlock ( p_file, p_buf, p_numberOfBytesToRead, p_numberOfBytesRead, p_blockAddress, l_blockIndex );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si des nouveaux blocs de données peuvent être lus dans le premier cluster ET si le nombre de données à lire est supérieur à la taille d'un secteur. */
      if ( ( ( l_blockIndex + 1 ) < p_file->volume->partition.fat.sectorsPerCluster ) && ( ( *p_numberOfBytesToRead ) > p_file->volume->partition.fat.bytesPerSector ) )
      {
         /* Détermination du nombre de blocs restant à lire dans le cluster */
         *p_blockNumber = ( uint32_t ) ( p_file->volume->partition.fat.sectorsPerCluster - l_blockIndex - 1 );

         /* Détermination du nombre d'octets disponibles dans le cluster */
         l_numberOfBytesAvailable = ( uint32_t ) ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector );

         /* Si le nombre d'octets restant à lire est inférieur à la taille de la prochaine lecture */
         if ( ( *p_numberOfBytesToRead ) < l_numberOfBytesAvailable )
         {
            /* Détermination du nombre de blocs à lire */
            *p_blockNumber = ( *p_numberOfBytesToRead ) >> p_file->volume->partition.fat.sBytesPerSector;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si l'adresse du prochain cluster n'est pas consécutive au cluster courant et si le nombre de données restante à lire et supérieur au nombre */
         /* de données disponible dans le cluster. */
         if ( ( p_file->descriptor.fat.clusterMap [ 0 ] != ( p_file->descriptor.fat.currentCluster + 1 ) ) && ( ( *p_numberOfBytesToRead ) > l_numberOfBytesAvailable ) )
         {
            /* Lecture des blocs de données sur le disque */
            /* Les clusters ne sont pas alignés, on ne peut donc pas différer la lecture */
            l_result = mk_fat_readChunk ( p_file, &p_buf [ *p_numberOfBytesRead ], *p_blockAddress, p_blockNumber, p_numberOfBytesToRead, p_numberOfBytesRead );

            /* Détermination de l'adresse du prochain bloc de données à lire */
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

         /* Si la lecture du cluster est terminée */
         if ( l_clusterOffset == 0 )
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
         /* Dans ce bloc, le premier cluster est plein ou le nombre de données restant à lire est inférieur à la taille d'un secteur. */
         /* Les dernières données seront lue par la fonction mk_fat_readLastBlock. */

         /* Si un nouveau cluster doit être chargé */
         if ( ( ( l_blockIndex + 1 ) == p_file->volume->partition.fat.sectorsPerCluster ) && ( p_file->descriptor.fat.clusterMap [ 0 ] != K_MK_FAT_LAST_CLUSTER ) )
         {
            /* Actualisation du cluster courant */
            p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.clusterMap [ 0 ];

            /* Détermination de l'adresse du prochain bloc de données à lire */
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

static T_mkCode mk_fat_readCurrentClusters ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_clusterIndex = 1, l_numberOfByteToRead = 0;

   /* Lors de l'arrivée dans cette fonction, la lecture d'un nombre de bloc 'p_blockNumber' peut avoir été temporisée. */
   /* Dans le cas où le nombre d'octets restants à lire est inférieur à la taille d'un cluster, la boucle n'est pas exécutée. */
   /* De même, lorsque le fichier possède un seul cluster (currentCluster = 0). */

   /* Initialisation du nombre de données à lire */
   l_numberOfByteToRead = ( uint32_t ) ( ( *p_numberOfBytesToRead ) - ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector ) );

   /* Tant qu'aucune erreur ne s'est produite et tant qu'un cluster entier peut être lu */
   while ( ( l_result == K_MK_OK ) && ( l_numberOfByteToRead >= p_file->volume->partition.fat.clusterSize ) && ( p_file->descriptor.fat.currentCluster != 0 ) )
   {
      /* Actualisation du nombre de blocs à lire */
      *p_blockNumber = ( uint32_t ) ( ( *p_blockNumber ) + p_file->volume->partition.fat.sectorsPerCluster );

      /* Si l'adresse du prochain cluster n'est pas consécutive au cluster courant */
      if ( p_file->descriptor.fat.clusterMap [ l_clusterIndex ] != ( p_file->descriptor.fat.currentCluster + 1 ) )
      {
         /* Lecture des blocs de données sur le disque */
         l_result = mk_fat_readChunk ( p_file, &p_buf [ *p_numberOfBytesRead ], *p_blockAddress, p_blockNumber, p_numberOfBytesToRead, p_numberOfBytesRead );

         /* Détermination de l'adresse du prochain bloc de données à lire */
         *p_blockAddress = mk_fat_getBlockAddress ( p_file, p_file->descriptor.fat.clusterMap [ l_clusterIndex ], 0 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du nombre de données à lire */
      l_numberOfByteToRead = ( uint32_t ) ( l_numberOfByteToRead - p_file->volume->partition.fat.clusterSize );

      /* Si aucune erreur ne s'est produite et si la chaine de cluster n'est pas terminée */
      if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.clusterMap [ l_clusterIndex ] < K_MK_FAT_VALID_CLUSTER ) )
      {
         /* Actualisation de la valeur du cluster courant */
         p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.clusterMap [ l_clusterIndex ];

         /* Si la chaine de cluster est terminée */
         if ( l_clusterIndex == ( K_MK_FAT_CLUSTER_MAP_LENGTH - 1 ) )
         {
            /* Récupération d'une nouvelle chaine de clusters */
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

static T_mkCode mk_fat_readLastCluster ( T_mkFile* p_file, uint8_t* p_buf, uint32_t* p_blockAddress, uint32_t* p_blockNumber, uint32_t* p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Détermination du nombre de blocs restant à lire */
   /* Si le dernier cluster n'est pas consécutif au précédent alors la variable 'p_blockNumber' est nulle */
   uint32_t l_blockNumber = ( uint32_t ) ( ( ( *p_numberOfBytesToRead ) - ( ( *p_blockNumber ) * p_file->volume->partition.fat.bytesPerSector ) ) >> p_file->volume->partition.fat.sBytesPerSector );

   /* Détermination du nombre de blocs restant à lire */
   *p_blockNumber = ( uint32_t ) ( ( *p_blockNumber ) + l_blockNumber );

   /* Si au moins un bloc de données doit être lu */
   if ( ( *p_blockNumber ) != 0 )
   {
      /* Enregistrement du nombre de blocs à lire */
      l_blockNumber = ( *p_blockNumber );

      /* Lecture des blocs de données sur le disque */
      l_result = mk_fat_readChunk ( p_file, &p_buf [ *p_numberOfBytesRead ], *p_blockAddress, p_blockNumber, p_numberOfBytesToRead, p_numberOfBytesRead );

      /* Actualisation de l'adresse du prochain bloc de données */
      *p_blockAddress = ( uint32_t ) ( ( *p_blockAddress ) + l_blockNumber );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite et si au moins un autre bloc de données supplémentaires doit être lu */
   if ( ( l_result == K_MK_OK ) && ( ( *p_numberOfBytesToRead ) != 0 ) )
   {
      /* Lecture du dernier blocs de données */
      l_result = mk_fat_readLastBlock ( p_file, p_buf, p_numberOfBytesToRead, p_numberOfBytesRead, p_blockAddress );
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

T_mkCode mk_fat_read ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_blockAddress = 0, l_blockNumber = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_buf != K_MK_NULL ) && ( p_numberOfBytesRead != K_MK_NULL ) && ( ( ( uint32_t ) p_buf & 0x3 ) == 0 ) )
   {
      /* Réinitialisation du nombre d'octets lus */
      *p_numberOfBytesRead = 0;

      /* Si le fichier peut être accédé en lecture */
      if ( p_file->flag.read == 1 )
      {
         /* Détermination du nombre d'octets à lire */
         p_numberOfBytesToRead = mk_fat_getNumberOfBytesToRead ( p_file, p_numberOfBytesToRead );

         /* Si le nombre d'octets à lire est non nul */
         if ( p_numberOfBytesToRead != 0 )
         {
            /* Récupération de la chaine de cluster */
            l_result = mk_fat_utils_getCluster ( p_file, p_file->descriptor.fat.currentCluster, p_file->descriptor.fat.clusterMap, K_MK_FAT_CLUSTER_MAP_LENGTH );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Lecture du premier cluster */
               l_result = mk_fat_readFirstCluster ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToRead, p_numberOfBytesRead );

               /* Si aucune erreur ne s'est produite */
               if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.currentCluster < K_MK_FAT_VALID_CLUSTER ) )
               {
                  /* Lecture des clusters intermédiaires */
                  l_result = mk_fat_readCurrentClusters ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToRead, p_numberOfBytesRead );

                  /* Si aucune erreur ne s'est produite */
                  if ( ( l_result == K_MK_OK ) && ( p_file->descriptor.fat.currentCluster < K_MK_FAT_VALID_CLUSTER ) )
                  {
                     /* Lecture du dernier cluster */
                     l_result = mk_fat_readLastCluster ( p_file, p_buf, &l_blockAddress, &l_blockNumber, &p_numberOfBytesToRead, p_numberOfBytesRead );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



