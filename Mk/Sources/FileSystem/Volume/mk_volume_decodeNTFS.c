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
* @file mk_volume_decodeNTFS.c
* @brief Définition de la fonction mk_volume_decodeNTFS.
* @date 29 mai 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_setNTFSIdentifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
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

static void mk_volume_checkAndRevertFixup ( T_mkVolume* p_volume, T_mkVolumeNTFSFileDescriptor* p_fileDescriptor, uint8_t* p_buf )
{
   /* Déclaration d'une variable stockant le résultat des comparaisons */
   uint32_t l_result = 0;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Actualisation du registre de statut de la partition */
   p_volume->status = K_MK_VOLUME_CORRUPTED;

   /* Vérification de la cohérence des données */
   /* Comparaison du contenu du champ 'Update Sequence' avec les deux derniers octets de chaque secteur */
   for ( l_counter = 0 ; l_counter < ( K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE / p_volume->partition.ntfs.bytesPerSector ) ; l_counter++ )
   {
      /* Réalisation de la comparaison, l'offset de l'update séquence est contenu à la position $4 */
      l_result |= mk_utils_strcomp ( ( T_str8 ) &p_buf [ p_fileDescriptor->updateSequenceOffset ],
                                         ( T_str8 ) &p_buf [ ( p_volume->partition.ntfs.bytesPerSector << l_counter ) - K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE ], 0, K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE );

      /* Si les octets sont identiques */
      if ( l_result != 0 )
      {
         /* Ecriture du contenu stocké dans le champ 'Update Sequence Array' dans les deux derniers octets du secteur */
         _copy ( &p_buf [ ( p_volume->partition.ntfs.bytesPerSector << l_counter ) - K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE ],
                 &p_buf [ p_fileDescriptor->updateSequenceOffset + ( K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE << l_counter ) ], K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE );

         /* Actualisation du registre de statut de la partition */
         p_volume->status &= ( uint32_t ) ( ~K_MK_VOLUME_CORRUPTED );
      }

      /* Sinon */
      else
      {
         /* Actualisation du registre de statut de la partition */
         p_volume->status = K_MK_VOLUME_CORRUPTED;
      }
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_searchName ( T_mkVolume* p_volume, T_mkVolumeNTFSFileDescriptor* p_fileDescriptor, uint8_t* p_buf )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un pointeur d'attribut */
   T_mkVolumeNTFSResidentAttributeHeader l_attributeHeader;

   /* Actualisation du registre de statut de la partition */
   p_volume->status = K_MK_VOLUME_CORRUPTED;

   /* Pour les 'n' attributs contenu dans le 'Record */
   do
   {
      /* Configuration du pointeur d'attribut */
      _copy ( &l_attributeHeader, &p_buf [ p_fileDescriptor->firstAttributeOffset ], sizeof ( T_mkVolumeNTFSResidentAttributeHeader ) );

      /* Si l'attribut $Volume a été trouvé */
      if ( l_attributeHeader.type == K_MK_VOLUME_NTFS_ATTRIBUTE_VOLUME_NAME )
      {
         /* Si la taille du nom est supérieure à la taille supportée */
         if ( l_attributeHeader.contentLength > ( 2 * K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH ) )
         {
            /* Actualisation de la taille du nom de la partition */
            l_attributeHeader.contentLength = ( 2 * K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Copie du nom de la partition dans le volume (code UTF-16) */
         _copy ( p_volume->partition.ntfs.label, &p_buf [ p_fileDescriptor->firstAttributeOffset + l_attributeHeader.nameOffset ], ( uint32_t ) l_attributeHeader.contentLength );

         /* Actualisation du registre de statut de la partition */
         p_volume->status &= ( uint32_t ) ( ~K_MK_VOLUME_CORRUPTED );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de l'offset */
      p_fileDescriptor->firstAttributeOffset = ( uint16_t ) ( p_fileDescriptor->firstAttributeOffset + l_attributeHeader.length );

      /* Actualisation du compteur */
      l_counter++;

   /* Tant que l'intégralité des attributs n'ont pas été analysés */
   } while ( ( l_counter < K_MK_VOLUME_NTFS_NUMBER_OF_MFT_FILE_RECORD  ) && ( l_attributeHeader.type != K_MK_VOLUME_NTFS_END_MARKER_PATTERN ) );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_volume_decodeRecord ( T_mkDisk* p_disk, T_mkVolume* p_volume, uint8_t* p_buf, uint32_t p_firstPartitionSector )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un descripteur de fichier */
   T_mkVolumeNTFSFileDescriptor* l_fileDescriptor;

   /* Déclaration d'une variable stockant le résultat de la comparaison de deux chaines de caractères */
   uint32_t l_compResult = 0;

   /* Déclaration des variables de travail */
   uint64_t l_numberOfBytesRead = 0, l_numberOfBlockToRead = 1;

   /* Détermination de l'adresse du Record '$Volume' */
   /* Ce record est situé à la troisième position du système de fichier */
   /* Chaque record à une taille fixe de 1024 octets */
   uint64_t l_sectorNumber = p_firstPartitionSector +
         ( p_volume->partition.ntfs.lowFirsMFTCluster * p_volume->partition.ntfs.sectorsPerCluster ) + K_MK_VOLUME_NTFS_MFT_VOLUME_RECORD_OFFSET;

   /* Si la taille d'un bloc est inférieur à la taille à lire */
   if ( p_disk->attribute.blockLength < K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE )
   {
      /* Actualisation du nombre de bloc à lire */
      l_numberOfBlockToRead = K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE / p_disk->attribute.blockLength;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Lecture du secteur stockant le record '$Volume'. */
   l_result = mk_disk_readSector ( p_disk, l_sectorNumber, p_buf,
                                 ( uint32_t ) (l_numberOfBlockToRead ), &l_numberOfBytesRead );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead == K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE ) )
   {
      /* Configuration du pointeur de fichier */
      l_fileDescriptor = ( T_mkAddr ) p_buf;

      /* Analyse de la signature */
      l_compResult = mk_utils_strcomp ( ( T_str8 ) &l_fileDescriptor->signature, ( T_str8 ) "FILE", 0, 4 );

      /* Si la partition est valide (présence de la chaine de caractères 'FILE' */
      if ( l_compResult == 1 )
      {
         /* Vérification de la cohérence des données à partir du champ 'UpdateSequence' */
         mk_volume_checkAndRevertFixup ( p_volume, l_fileDescriptor, p_buf );
      }

      /* Sinon */
      else
      {
         /* Actualisation du registre de statut de la partition */
         p_volume->status = K_MK_VOLUME_CORRUPTED;
      }

      /* Si la partition est valide */
      if ( p_volume->status != K_MK_VOLUME_CORRUPTED )
      {
         /* On vérifie que le 'Record' en cours d'analyse est bien de type '$Volume' */
         mk_volume_searchName ( p_volume, l_fileDescriptor, p_buf );

         /* Si le volume n'est pas corrompu */
         if ( p_volume->status != K_MK_VOLUME_CORRUPTED )
         {
            /* Actualisation du registre de statut de la partition */
            p_volume->status = K_MK_VOLUME_READY;
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

static void mk_volume_copyNTFSAttributes ( T_mkVolume* p_volume, uint8_t* p_buf )
{
   /* Récupération du nombre d'octets par secteur */
   _copy ( &p_volume->partition.ntfs.bytesPerSector, &p_buf [ K_MK_VOLUME_NTFS_BYTES_PER_SECTOR_OFFSET ], 2 );

   /* Récupération du nombre de secteurs par cluster */
   _copy ( &p_volume->partition.ntfs.sectorsPerCluster, &p_buf [ K_MK_VOLUME_NTFS_SECTORS_PER_CLUSTER_OFFSET ], 1 );

   /* Récupération du nombre de secteurs dans la partition */
   _copy ( &p_volume->partition.ntfs.lowTotalNumberOfSectors, &p_buf [ K_MK_VOLUME_NTFS_TOTAL_NUMBER_OF_SECTORS_OFFSET ], 4 );
   _copy ( &p_volume->partition.ntfs.highTotalNumberOfSectors, &p_buf [ K_MK_VOLUME_NTFS_TOTAL_NUMBER_OF_SECTORS_OFFSET + 4 ], 4 );

   /* Récupération de l'index du cluster de la MFT */
   _copy ( &p_volume->partition.ntfs.lowFirsMFTCluster, &p_buf [ K_MK_VOLUME_NTFS_FIRST_MFT_CLUSTER_OFFSET ], 4 );
   _copy ( &p_volume->partition.ntfs.highFirsMFTCluster, &p_buf [ K_MK_VOLUME_NTFS_FIRST_MFT_CLUSTER_OFFSET + 4 ], 4 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_volume_decodeNTFSAttributes ( T_mkVolume* p_volume, uint8_t* p_buf )
{
   /* Si l'octet analysé est négatif */
   if ( ( p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_FILE_RECORD_OFFSET ] & 0x80 ) > 0 )
   {
      /* Le champ stocke le nombre d'octets par 'File Record' selon une puissance de 2 */
      p_volume->partition.ntfs.bytesPerFileRecord =
            ( uint32_t ) ( 1 << ( uint32_t ) ( ( ~p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_FILE_RECORD_OFFSET ] ) + 1 ) );
      p_volume->partition.ntfs.clustersPerFileRecord =
            p_volume->partition.ntfs.bytesPerFileRecord /
            ( ( uint32_t ) p_volume->partition.ntfs.sectorsPerCluster * ( uint32_t ) p_volume->partition.ntfs.bytesPerSector );
   }

   /* Sinon */
   else
   {
      /* Récupération du nombre de cluster par 'File Record' */
      p_volume->partition.ntfs.clustersPerFileRecord = p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_FILE_RECORD_OFFSET ];
      p_volume->partition.ntfs.bytesPerFileRecord =
            p_volume->partition.ntfs.clustersPerFileRecord *
            ( uint32_t ) p_volume->partition.ntfs.sectorsPerCluster * ( uint32_t ) p_volume->partition.ntfs.bytesPerSector;
   }

   /* Si l'octet analysé est négatif */
   if ( ( p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_INDEX_BUFFER_OFFSET ] & 0x80 ) > 0 )
   {
      /* Le champ stocke le nombre d'octets par 'IndexBuffer' selon une puissance de 2 */
      p_volume->partition.ntfs.bytesPerIndexBuffer =
            ( uint32_t ) ( 1 << ( uint32_t ) ( ( ~p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_INDEX_BUFFER_OFFSET ] ) + 1 ) );
      p_volume->partition.ntfs.clustersPerIndexBuffer =
            p_volume->partition.ntfs.bytesPerIndexBuffer /
            ( ( uint32_t ) p_volume->partition.ntfs.sectorsPerCluster * ( uint32_t ) p_volume->partition.ntfs.bytesPerSector );
   }

   /* Sinon */
   else
   {
      /* Récupération du nombre de cluster par 'IndexBuffer' */
      p_volume->partition.ntfs.clustersPerIndexBuffer = p_buf [ K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_INDEX_BUFFER_OFFSET ];
      p_volume->partition.ntfs.bytesPerIndexBuffer =
            p_volume->partition.ntfs.clustersPerIndexBuffer *
            ( uint32_t ) p_volume->partition.ntfs.sectorsPerCluster * ( uint32_t ) p_volume->partition.ntfs.bytesPerSector;
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_volume_decodeNTFS ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables stockant la dénomination du disque */
   char8_t l_str [ 4 ] = "vol";
   char8_t l_strIdentifier [ 4 ] = "";

   /* Déclaration d'un pointeur de partition */
   T_mkVolume* l_volume;

   /* Déclaration d'une variable de travail */
   uint32_t l_local = 0;

   /* Si les paramètres sont valides */
   if ( ( p_disk != K_MK_NULL ) && ( p_list != K_MK_NULL ) && ( p_buf != K_MK_NULL ) )
   {
      /* Allocation d'une nouvelle partition */
      l_result = mk_pool_allocSafe ( g_mkVolumePool.pool, ( T_mkAddr ) &l_volume, K_MK_POOL_CLEAR, 0 );

      /* Si l'allocation a réussi */
      if ( ( l_result == K_MK_OK ) && ( l_volume != K_MK_NULL ) )
      {
         /* Configuration du type de la partition */
         l_volume->type = K_MK_VOLUME_TYPE_NTFS;

         /* Configuration du type applicatif */
         l_volume->layer.type = K_MK_CONTROL_VOLUME;

         /* Configuration de l'adresse du disque */
         l_volume->disk = p_disk;

         /* Configuration de l'identifiant de la partition NTFS */
         mk_volume_setNTFSIdentifier ( &l_volume->layer.id, l_volume, g_mkVolumePool.heap, sizeof ( T_mkVolume ) );

         /* Récupération d'un identifiant système unique */
         l_volume->name.id = mk_volume_getSystemIdentifier ( *p_list );

         /* Conversion et stockage de l'identifiant en chaine de caractères */
         mk_utils_itoa ( ( uint32_t ) l_volume->name.id, ( T_str8 ) l_strIdentifier, 10, 1 );
         mk_utils_strcat ( ( T_str8 ) l_volume->name.str, ( T_str8 ) l_str, ( T_str8 ) l_strIdentifier );

         /* Copie des attributs NTFS dans le volume */
         mk_volume_copyNTFSAttributes ( l_volume, p_buf );

         /* Décodage des attributs de la partition */
         mk_volume_decodeNTFSAttributes ( l_volume, p_buf );

         /* Enregistrement de l'adresse de BPB */
         l_volume->partition.ntfs.addressOfBPB = p_firstPartitionSector;

         /* Détermination de la taille d'un cluster */
         l_volume->partition.ntfs.clusterSize = ( uint32_t ) ( ( uint32_t ) l_volume->partition.ntfs.sectorsPerCluster * ( uint32_t ) l_volume->partition.ntfs.bytesPerSector );

         /* Analyse de la taille d'un secteur */
         l_local = mk_utils_check2 ( ( uint32_t ) l_volume->partition.ntfs.bytesPerSector, K_MK_VOLUME_NTFS_MIN_BLOCK_LENGTH, K_MK_VOLUME_NTFS_MAX_BLOCK_LENGTH );

         /* Si la partition n'est pas supportée */
         if ( ( l_local != 0 ) || ( l_volume->partition.ntfs.bytesPerSector != p_disk->attribute.blockLength ) ||
              ( l_volume->partition.ntfs.highFirsMFTCluster != 0 ) || ( l_volume->partition.ntfs.highTotalNumberOfSectors != 0 ) )
         {
            /* Actualisation du registre de statut de la partition */
            l_volume->status = K_MK_VOLUME_NOT_SUPPORTED;
         }

         /* Sinon */
         else
         {
            /* Récupération des informations contenues dans le record '$Volume' */
            l_result = mk_volume_decodeRecord ( p_disk, l_volume, p_buf, p_firstPartitionSector );
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
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


