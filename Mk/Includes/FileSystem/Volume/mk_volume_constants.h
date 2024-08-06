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
* @file mk_volume_constants.h
* @brief Déclaration des constantes dédiées aux partitions.
* @date 15 juin 2020
*
*/

#ifndef MK_VOLUME_CONSTANTS_H
#define MK_VOLUME_CONSTANTS_H

/**
 * @def K_MK_VOLUME_MAX_NUMBER
 * @brief Définition du nombre maximal de volumes (\ref T_mkVolume) pouvant être alloués.
 */

#define K_MK_VOLUME_MAX_NUMBER 16

/**
 * @def K_MK_VOLUME_RECURSIVITY_LEVEL
 * @brief Définition du nombre d'itérations maximales de la fonction récursive
 *        \ref mk_volume_init.
 */

#define K_MK_VOLUME_RECURSIVITY_LEVEL 3

/**
 * @def K_MK_VOLUME_MBR_SECTOR
 * @brief Définition de l'adresse du secteur de boot.
 */

#define K_MK_VOLUME_MBR_SECTOR 0

/**
 * @def K_MK_VOLUME_MBR_SIZE
 * @brief Définition de la taille du secteur de boot [en octets].
 */

#define K_MK_VOLUME_MBR_SIZE 0x200

/**
 * @def K_MK_VOLUME_MBR_NUMBER_OF_ENTRIES
 * @brief Définition du nombre d'entrées dans le MBR.
 */

#define K_MK_VOLUME_MBR_NUMBER_OF_ENTRIES 0x04

/**
 * @def K_MK_VOLUME_MBR_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée du MBR [en octets].
 */

#define K_MK_VOLUME_MBR_ENTRY_SIZE 0x10

/**
 * @def K_MK_VOLUME_MBR_FIRST_ENTRY_OFFSET
 * @brief Définition de l'offset de la première entrée du MBR.
 */

#define K_MK_VOLUME_MBR_FIRST_ENTRY_OFFSET 0x01BE

/**
 * @def K_MK_VOLUME_MBR_SIGNATURE
 * @brief Définition de la valeur de la signature du secteur de boot.
 */

#define K_MK_VOLUME_MBR_SIGNATURE 0xAA55

/**
 *
 */

/**
 * @def K_MK_VOLUME_NTFS_MIN_BLOCK_LENGTH
 * @brief Définition de la taille minimale d'un bloc de données.
 */

#define K_MK_VOLUME_NTFS_MIN_BLOCK_LENGTH 512

/**
 * @def K_MK_VOLUME_NTFS_MAX_BLOCK_LENGTH
 * @brief Définition de la taille maximale d'un bloc de données.
 */

#define K_MK_VOLUME_NTFS_MAX_BLOCK_LENGTH 4096

/**
 * @def K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH
 * @brief Définition du nombre maximal de caractères UTF-16 contenu dans
 *        le nom d'une partition NTFS.
 */

#define K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH 0x10

/**
 * @def K_MK_VOLUME_NTFS_PARTITION_LABEL_OFFSET
 * @brief Définition de l'offset du label 'NTFS' dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_PARTITION_LABEL_OFFSET 0x03

/**
 * @def K_MK_VOLUME_NTFS_BYTES_PER_SECTOR_OFFSET
 * @brief Définition de l'offset du champ 'BytePerSector' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_BYTES_PER_SECTOR_OFFSET 0x0B

/**
 * @def K_MK_VOLUME_NTFS_SECTORS_PER_CLUSTER_OFFSET
 * @brief Définition de l'offset du champ 'SectorsPerCluster' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_SECTORS_PER_CLUSTER_OFFSET 0x0D

/**
 * @def K_MK_VOLUME_NTFS_TOTAL_NUMBER_OF_SECTORS_OFFSET
 * @brief Définition de l'offset du champ 'TotalNumberOfSector' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_TOTAL_NUMBER_OF_SECTORS_OFFSET 0x28

/**
 * @def K_MK_VOLUME_NTFS_FIRST_MFT_CLUSTER_OFFSET
 * @brief Définition de l'offset du champ 'FirstMFTCluster' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_FIRST_MFT_CLUSTER_OFFSET 0x30

/**
 * @def K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_FILE_RECORD_OFFSET
 * @brief Définition de l'offset du champ 'BytesClusterPerFileRecord' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_FILE_RECORD_OFFSET 0x40

/**
 * @def K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_INDEX_BUFFER_OFFSET
 * @brief Définition de l'offset du champ 'BytesClusterPerIndexBuffer' situé dans le premier secteur de la
 *        partition NTFS.
 */

#define K_MK_VOLUME_NTFS_BYTES_CLUSTERS_PER_INDEX_BUFFER_OFFSET 0x40

/**
 * @def K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE
 * @brief Définition de la taille de la séquence de contrôle de chaque secteur [en octets].
 */

#define K_MK_VOLUME_NTFS_UPDATE_SEQUENCE_SIZE 0x02

/**
 * @def K_MK_VOLUME_NTFS_NUMBER_OF_MFT_FILE_RECORD
 * @brief Définition du nombre maximal de record pouvant être contenu dans un fichier de la MFT.
 */

#define K_MK_VOLUME_NTFS_NUMBER_OF_MFT_FILE_RECORD 0x10

/**
 * @def K_MK_VOLUME_NTFS_END_MARKER_PATTERN
 * @brief Définition de l'identifiant de fin de record.
 */

#define K_MK_VOLUME_NTFS_END_MARKER_PATTERN 0xFFFFFFFF

/**
 * @def K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE
 * @brief Définition de la taille minimale d'un fichier [en octets].
 */

#define K_MK_VOLUME_NTFS_MINIMUM_FILE_SIZE 0x400

/**
 * @def K_MK_VOLUME_NTFS_MFT_VOLUME_RECORD_OFFSET
 * @brief Définition de l'offset du 'Record' $Volume [en secteurs].
 *        L'offset est définie par rapport à la localisation de la MFT.
 */

#define K_MK_VOLUME_NTFS_MFT_VOLUME_RECORD_OFFSET 0x06

/**
 *
 */

/**
 * @def K_MK_VOLUME_FAT32_MIN_SECTOR_PER_CLUSTER
 * @brief Définition de la taille minimale d'un cluster [en secteurs].
 */

#define K_MK_VOLUME_FAT32_MIN_SECTOR_PER_CLUSTER 1

/**
 * @def K_MK_VOLUME_FAT32_MAX_SECTOR_PER_CLUSTER
 * @brief Définition de la taille maximale d'un cluster [en secteurs].
 */

#define K_MK_VOLUME_FAT32_MAX_SECTOR_PER_CLUSTER 128

/**
 * @def K_MK_VOLUME_FAT32_MAX_CLUSTER_SIZE
 * @brief Définition de la taille maximale d'un cluster [en octets].
 */

#define K_MK_VOLUME_FAT32_MAX_CLUSTER_SIZE 65536

/**
 * @def K_MK_VOLUME_FAT32_MIN_BLOCK_LENGTH
 * @brief Définition de la taille minimale d'un bloc de données [en octets].
 */

#define K_MK_VOLUME_FAT32_MIN_BLOCK_LENGTH 512

/**
 * @def K_MK_VOLUME_FAT32_MAX_BLOCK_LENGTH
 * @brief Définition de la taille maximale d'un bloc de données [en octets].
 */

#define K_MK_VOLUME_FAT32_MAX_BLOCK_LENGTH 4096

/**
 * @def K_MK_VOLUME_FAT32_FIRST_CLUSTER
 * @brief Définition de l'offset du premier cluster de la partition.
 */

#define K_MK_VOLUME_FAT32_FIRST_CLUSTER 0x00000002

/**
 * @def K_MK_VOLUME_FAT32_MAX_VOLUME_NAME_LENGTH
 * @brief Définition du nombre maximal de caractères ASCII contenu dans
 *        le nom d'un volume FAT32.
 */

#define K_MK_VOLUME_FAT32_MAX_VOLUME_NAME_LENGTH 11

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_FIRST_LABEL_OFFSET
 * @brief Définition de l'offset du premier label 'RRaA' situé dans le secteur d'information de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_FIRST_LABEL_OFFSET 0x00

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_SECOND_LABEL_OFFSET
 * @brief Définition de l'offset du second label 'RRaA' situé dans le secteur d'information de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_SECOND_LABEL_OFFSET 0x1E4

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_NUMBER_OF_FREE_CLUSTERS_OFFSET
 * @brief Définition de l'offset où est situé le nombre de clusters disponibles.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_NUMBER_OF_FREE_CLUSTERS_OFFSET 0x1E8

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_NEXT_FREE_CLUSTER_OFFSET
 * @brief Définition de l'offset où est situé l'index du prochain cluster disponible.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_NEXT_FREE_CLUSTER_OFFSET 0x1EC

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE_OFFSET
 * @brief Définition de l'offset de la signature du secteur d'information.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE_OFFSET 0x1FC

/**
 * @def K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE
 * @brief Définition de la valeur de la signature du secteur d'information.
 */

#define K_MK_VOLUME_FAT32_FSINFORMATION_SIGNATURE 0xAA550000

/**
 * @def K_MK_VOLUME_FAT32_PARTITION_LABEL_OFFSET
 * @brief Définition de l'offset du label 'FAT32' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_PARTITION_LABEL_OFFSET 0x52

/**
 * @def K_MK_VOLUME_FAT32_BYTES_PER_SECTOR_OFFSET
 * @brief Définition de l'offset du champ 'BytePerSector' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_BYTES_PER_SECTOR_OFFSET 0x0B

/**
 * @def K_MK_VOLUME_FAT32_SECTORS_PER_CLUSTER_OFFSET
 * @brief Définition de l'offset du champ 'SectorsPerCluster' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_SECTORS_PER_CLUSTER_OFFSET 0x0D

/**
 * @def K_MK_VOLUME_FAT32_NUMBER_OF_RESERVED_SECTORS_OFFSET
 * @brief Définition de l'offset du champ 'NumberOfReservedSectors' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_NUMBER_OF_RESERVED_SECTORS_OFFSET 0x0E

/**
 * @def K_MK_VOLUME_FAT32_NUMBER_OF_FAT_OFFSET
 * @brief Définition de l'offset du champ 'NumberOfFAT' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_NUMBER_OF_FAT_OFFSET 0x10

/**
 * @def K_MK_VOLUME_FAT32_TOTAL_NUMBER_OF_SECTORS_OFFSET
 * @brief Définition de l'offset du champ 'TotatNumberOfSector' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_TOTAL_NUMBER_OF_SECTORS_OFFSET 0x20

/**
 * @def K_MK_VOLUME_FAT32_SECTORS_PER_FAT_OFFSET
 * @brief Définition de l'offset du champ 'SectorsPerFAT' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_SECTORS_PER_FAT_OFFSET 0x24

/**
 * @def K_MK_VOLUME_FAT32_FIRST_ROOT_DIRECTORY_CLUSTER_OFFSET
 * @brief Définition de l'offset du champ 'FirstRootDirectoryCluster' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_FIRST_ROOT_DIRECTORY_CLUSTER_OFFSET 0x2C

/**
 * @def K_MK_VOLUME_FAT32_ADDRESS_OF_INFORMATION_SECTOR_OFFSET
 * @brief Définition de l'offset du champ 'AddressOfInformationSector' situé dans le premier secteur de la
 *        partition.
 */

#define K_MK_VOLUME_FAT32_ADDRESS_OF_INFORMATION_SECTOR_OFFSET 0x30

/**
 * @def K_MK_VOLUME_FAT32_VOLUME_NAME_OFFSET
 * @brief Définition de l'offset du nom de la partition dans le premier secteur de la partition.
 */

#define K_MK_VOLUME_FAT32_VOLUME_NAME_OFFSET 0x47

/**
 *
 */

#endif

