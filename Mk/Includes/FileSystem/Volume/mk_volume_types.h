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
* @file mk_volume_types.h
* @brief Déclaration des types dédiés aux partitions.
* @date 15 juin 2020
* @todo Retravailler la description des structures NTFS.
*
*/

#ifndef MK_VOLUME_TYPES_H
#define MK_VOLUME_TYPES_H

/**
 * @enum T_mkVolumeType
 * @brief Déclaration de la structure T_mkVolumeType.
 *
 */

typedef enum T_mkVolumeType
{
   K_MK_VOLUME_TYPE_UNKNOWN = 0x00,                                                    /*!< Définition de l'identifiant d'une partition inconnue. */
   K_MK_VOLUME_TYPE_FAT16 = 0x01,                                                      /*!< Définition de l'identifiant d'une partition FAT16. */
   K_MK_VOLUME_TYPE_FAT32 = 0x02,                                                      /*!< Définition de l'identifiant d'une partition FAT32. */
   K_MK_VOLUME_TYPE_NTFS = 0x03                                                        /*!< Définition de l'identifiant d'une partition NTFS. */
} T_mkVolumeType;

/**
 * @enum T_mkVolumeEntryIdentifier
 * @brief Déclaration de la structure T_mkVolumeEntryIdentifier.
 *
 */

typedef enum T_mkVolumeEntryIdentifier
{
   K_MK_VOLUME_ENTRY_EMPTY = 0x00,                                                     /*!< Définition de la valeur de l'entrée indiquant l'absence de partition. */
   K_MK_VOLUME_ENTRY_IBM_CHS_CONTAINER = 0x05,                                         /*!< Définition de la valeur de l'entrée indiquant une liste de partitions étendues au format CHS. */
   K_MK_VOLUME_ENTRY_MICROSOFT_CHS_LBA_NTFS = 0x07,                                    /*!< Définition de la valeur de l'entrée indiquant une partition NTFS au format CHS ou LBA. */
   K_MK_VOLUME_ENTRY_MICROSOFT_CHS_FAT32 = 0x0B,                                       /*!< Définition de la valeur de l'entrée indiquant une partition FAT32 au format CHS. */
   K_MK_VOLUME_ENTRY_MICROSOFT_LBA_FAT32 = 0x0C,                                       /*!< Définition de la valeur de l'entrée indiquant une partition FAT32 au format LBA. */
   K_MK_VOLUME_ENTRY_MICROSOFT_LBA_CONTAINER = 0x0F                                    /*!< Définition de la valeur de l'entrée indiquant une liste de partitions étendues au format LBA. */
} T_mkVolumeEntryIdentifier;

/**
 * @enum T_mkVolumeStatus
 * @brief Déclaration de la structure T_mkVolumeStatus.
 *
 */

typedef enum T_mkVolumeStatus
{
   K_MK_VOLUME_NOT_ENUMERATED = 0x0,                                                   /*!< Définition d'un code indiquant que la partition n'a pas été énumérée. */
   K_MK_VOLUME_READY = 0x1,                                                            /*!< Définition d'un code indiquant que la partition est prête à être utilisée. */
   K_MK_VOLUME_NOT_SUPPORTED = 0x2,                                                    /*!< Définition d'un code indiquant que la partition n'est pas supportée. */
   K_MK_VOLUME_CORRUPTED = 0x4                                                         /*!< Définition d'un code indiquant que la partition est corrompue. */
} T_mkVolumeStatus;

/**
 * @struct T_mkVolumeEntry
 * @brief Déclaration de la structure T_mkVolumeEntry.
 *
 */

typedef struct T_mkVolumeEntry T_mkVolumeEntry;
struct T_mkVolumeEntry
{
   unsigned_t bootable:8;                                                                /*!< Ce membre contient le code indiquant si la partition est bootable ou non. */
   unsigned_t firstHead:8;                                                               /*!< Ce membre contient l'adresse de la première tête de la partition (CHS). */
   unsigned_t firstSector:6;                                                             /*!< Ce membre contient l'adresse du permier secteur de la partition (CHS). */
   unsigned_t firstCylinder:10;                                                          /*!< Ce membre contient l'adresse du permier cyclindre de la partition (CHS). */
   unsigned_t type:8;                                                                    /*!< Ce membre contient l'identifiant de la partition (\ref T_mkVolumeEntryIdentifier). */
   unsigned_t lastHead:8;                                                                /*!< Ce membre contient l'adresse de la dernière tête de la partition (CHS). */
   unsigned_t lastSector:6;                                                              /*!< Ce membre contient l'adresse du dernier secteur de la partition (CHS). */
   unsigned_t lastCylinder:10;                                                           /*!< Ce membre contient l'adresse du dernier cyclindre de la partition (CHS). */
   unsigned_t firstLBA:32;                                                               /*!< Ce membre contient l'adresse du premier secteur de la partition (LBA). */
   unsigned_t numberOfSectors:32;                                                        /*!< Ce membre contient la taille de la partition en secteur. */
};

/**
 *
 */

/**
 * @struct T_mkVolumeFAT
 * @brief Déclaration de la structure T_mkVolumeFAT.
 *
 */

typedef struct T_mkVolumeFAT T_mkVolumeFAT;
struct T_mkVolumeFAT
{
   uint8_t label[ K_MK_VOLUME_FAT32_MAX_VOLUME_NAME_LENGTH ];                          /*!< Ce membre contient le nom du volume. */
   uint8_t sectorsPerCluster;                                                          /*!< Ce membre contient le nombre de secteurs par cluster. */
   uint8_t numberOfFAT;                                                                /*!< Ce membre contient le nombre de FAT dans la partition. */

   uint8_t sBytesPerSector;                                                            /*!< Ce membre contient le nombre d'octets par secteur (format bytePerSector = (1 << sBytesPerSector) ). */
   uint8_t sSectorsPerCluster;                                                         /*!< Ce membre contient le nombre de secteurs par cluster (format sectorPerCluster = (1 << sSectorsPerCluster) ). */
   uint8_t sClusterSize;                                                               /*!< Ce membre contient la taille d'un cluster en octets (format clusterSize = (1 << sClusterSize) ). */
   uint8_t sNumberOfEntriesPerSector;                                                  /*!< Ce membre contient le nombre d'entrées de répertoires (32 octets) par secteur (format numberOfEntriesPerSector = (1 << sNumberOfEntriesPerSector) ). */
   uint8_t sNumberOfClusterEntriesPerSector;                                           /*!< Ce membre contient le nombre d'entrées de cluster (4 octets) par secteur (format numberOfClusterEntriesPerSector = (1 << sNumberOfClusterEntriesPerSector) ). */

   uint16_t bytesPerSector;                                                            /*!< Ce membre contient le nombre d'octets par secteur. */
   uint16_t numberOfReservedSectors;                                                   /*!< Ce membre contient le nombre de secteurs réservés. */
   uint16_t maximumNumberOfRootDirectoryEntries;                                       /*!< Ce membre contient le nombre maximum d'entrées dans le répertoire racine. */
   uint32_t clusterSize;                                                               /*!< Ce membre contient la taille d'un cluster en octets. */
   uint32_t sectorsPerFAT;                                                             /*!< Ce membre contient le nombre de secteurs par FAT. */
   uint32_t totalNumberOfSectors;                                                      /*!< Ce membre contient le nombre total de secteurs dans la partition. */
   uint32_t numberOfAvailableSectors;                                                  /*!< Ce membre contient le nombre de secteurs disponibles dans la partition. */
   uint32_t firstRootDirectoryCluster;                                                 /*!< Ce membre contient l'adresse du répertoire racine (en cluster). */
   uint32_t addressOfBPB;                                                              /*!< Ce membre contient l'adresse du BPB (en secteur). */
   uint32_t addressOfFAT;                                                              /*!< Ce membre contient l'adresse de la première FAT (en secteur). */
   uint32_t addressOfRootDirectory;                                                    /*!< Ce membre contient l'adresse du répertoire racine (en secteur). */
   uint32_t addressOfInformationSector;                                                /*!< Ce membre contient l'adresse du secteur d'information (en secteur). */
   uint32_t nextFreeCluster;                                                           /*!< Ce membre contient le numéro du prochain cluster disponible. */
   uint32_t numberOfFreeCluster;                                                       /*!< Ce membre contient le nombre de clusters disponibles. */

   uint32_t numberOfEntriesPerSector;                                                  /*!< Ce membre contient le nombre d'entrées de répertoire (32 octets) par secteur. */
   uint32_t numberOfClusterEntriesPerSector;                                           /*!< Ce membre contient le nombre d'entrées de cluster (4 octets) par secteur. */
   uint32_t numberOfBlocksPerWindow;                                                   /*!< Ce membre contient le nombre de secteurs dans le cache. */
};

/**
 *
 */

/**
 * @struct T_mkVolumeNTFSNonResidentAttributeHeader
 * @brief Déclaration de la structure T_mkVolumeNTFSNonResidentAttributeHeader.
 *
 */

typedef struct T_mkVolumeNTFSNonResidentAttributeHeader T_mkVolumeNTFSNonResidentAttributeHeader;
struct T_mkVolumeNTFSNonResidentAttributeHeader
{
   uint32_t type;                                                                      /*!< Ce membre contient le type de l'attribut (\ref T_mkVolumeNTFSAttribute). */
   uint32_t length;                                                                    /*!< Ce membre contient la taille de l'attribut en octets (avec l'entête). */
   uint8_t  formCode;                                                                  /*!< Ce membre contient un code indiquant si l'attribut est de type resident (0) ou non (1). */
   uint8_t  nameLength;                                                                /*!< Ce membre contient la taille du nom de l'attribut en octet. */
   uint16_t nameOffset;                                                                /*!< Ce membre contient l'offset où est présent le nom de l'attribut. */
   uint16_t flags;                                                                     /*!< Ce membre contient les flags de l'attribut (Compressed, Encrypted, ...). */
   uint16_t attributeID;                                                               /*!< Ce membre contient l'identifiant de l'attribut. */
   uint32_t lowStartVirtualClusterNumber;                                              /*!< Ce membre contient l'adresse de début du VCN (poids faible). */
   uint32_t highStartVirtualClusterNumber;                                             /*!< Ce membre contient l'adresse de début du VCN (poids fort). */
   uint32_t lowEndingVirtualClusterNumber;                                             /*!< Ce membre contient l'adresse de fin du VCN (poids faible). */
   uint32_t highEndingVirtualClusterNumber;                                            /*!< Ce membre contient l'adresse de fin du VCN (poids fort). */
   uint16_t runListOffset;                                                             /*!< Ce membre contient l'offset des données. */
   uint16_t compressionUnitSize;                                                       /*!< Ce membre contient la taille de l'unité de compression (au format 2^x). */
   uint32_t reserved;                                                                  /*!< Ce membre contient un mot de padding. */
   uint32_t lowSizeOnDiskOfAttributeContent;                                           /*!< Ce membre contient la taille de l'attribut allouée sur le disque (poids faible). */
   uint32_t highSizeOnDiskOfAttributeContent;                                          /*!< Ce membre contient la taille de l'attribut allouée sur le disque (poids fort). */
   uint32_t lowSizeAttributeContent;                                                   /*!< Ce membre contient la taille de l'attribut (poids faible). */
   uint32_t highSizeAttributeContent;                                                  /*!< Ce membre contient la taille de l'attribut (poids fort). */
   uint32_t lowInitializedSizeOfAttributeContent;                                      /*!< Ce membre contient la taille de l'attribut compressé (poids faible). */
   uint32_t highInitializedSizeOfAttributeContent;                                     /*!< Ce membre contient la taille de l'attribut compressé (poids fort). */
};

/**
 * @struct T_mkVolumeNTFSResidentAttributeHeader
 * @brief Déclaration de la structure T_mkVolumeNTFSResidentAttributeHeader.
 *
 */

typedef struct T_mkVolumeNTFSResidentAttributeHeader T_mkVolumeNTFSResidentAttributeHeader;
struct T_mkVolumeNTFSResidentAttributeHeader
{
   uint32_t type;                                                                      /*!< Ce membre contient le type de l'attribut (\ref T_mkVolumeNTFSAttribute). */
   uint32_t length;                                                                    /*!< Ce membre contient la taille de l'attribut en octets (avec l'entête). */
   uint8_t  formCode;                                                                  /*!< Ce membre contient un code indiquant si l'attribut est de type resident (0) ou non (1). */
   uint8_t  nameLength;                                                                /*!< Ce membre contient la taille du nom de l'attribut en octet. */
   uint16_t nameOffset;                                                                /*!< Ce membre contient l'offset où est présent le nom de l'attribut. */
   uint16_t flags;                                                                     /*!< Ce membre contient les flags de l'attribut (Compressed, Encrypted, ...). */
   uint16_t attributeID;                                                               /*!< Ce membre contient l'identifiant de l'attribut. */
   uint32_t contentLength;                                                             /*!< Ce membre contient la taille des données en octets. */
   uint16_t contentOffset;                                                             /*!< Ce membre contient l'offset des données (aligné sur 4 octets). */
   uint16_t unused;                                                                    /*!< Ce champ n'est pas utilisée. */
};

/**
 * @enum T_mkVolumeStatus
 * @brief Déclaration de la structure T_mkVolumeStatus.
 *
 */

typedef enum T_mkVolumeNTFSAttribute
{
   K_MK_VOLUME_NTFS_ATTRIBUTE_STANDARD_INFORMATION = 0x10,                             /*!< Définition de l'identifiant indiquant que l'attribut est de type STANDARD_INFORMATION. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_LIST = 0x20,                                             /*!< Définition de l'identifiant indiquant que l'attribut est de type LIST. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_FILE_NAME = 0x30,                                        /*!< Définition de l'identifiant indiquant que l'attribut est de type FILE_NAME. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_VOLUME_VERSION_OBJECT_ID = 0x40,                         /*!< Définition de l'identifiant indiquant que l'attribut est de type VOLUME_VERSION_OBJECT_ID. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_SECURITY_DESCRIPTOR = 0x50,                              /*!< Définition de l'identifiant indiquant que l'attribut est de type SECURITY_DESCRIPTOR. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_VOLUME_NAME = 0x60,                                      /*!< Définition de l'identifiant indiquant que l'attribut est de type VOLUME_NAME. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_VOLUME_INFORMATION = 0x70,                               /*!< Définition de l'identifiant indiquant que l'attribut est de type VOLUME_INFORMATION. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_DATA = 0x80,                                             /*!< Définition de l'identifiant indiquant que l'attribut est de type DATA. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_INDEX_ROOT = 0x90,                                       /*!< Définition de l'identifiant indiquant que l'attribut est de type INDEX_ROOT. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_INDEX_ALLOCATION = 0xA0,                                 /*!< Définition de l'identifiant indiquant que l'attribut est de type INDEX_ALLOCATION. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_BITMAP = 0xB0,                                           /*!< Définition de l'identifiant indiquant que l'attribut est de type BITMAP. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_SYMBOLIC_LINK_REPARSE_POINT = 0xC0,                      /*!< Définition de l'identifiant indiquant que l'attribut est de type SYMBOLIC_LINK_REPARSE_POINT. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_EA_INFORMATION = 0xD0,                                   /*!< Définition de l'identifiant indiquant que l'attribut est de type EA_INFORMATION. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_EA = 0xE0,                                               /*!< Définition de l'identifiant indiquant que l'attribut est de type EA. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_PROPERTY_SET = 0xF0,                                     /*!< Définition de l'identifiant indiquant que l'attribut est de type PROPERTY_SET. */
   K_MK_VOLUME_NTFS_ATTRIBUTE_LOGGUED_UTILITY_STREAM = 0x100                           /*!< Définition de l'identifiant indiquant que l'attribut est de type LOGGUED_UTILITY_STREAM. */
} T_mkVolumeNTFSAttribute;

/**
 * @struct T_mkVolumeNTFSFileDescriptor
 * @brief Déclaration de la structure T_mkVolumeNTFSFileDescriptor.
 *
 */

typedef struct T_mkVolumeNTFSFileDescriptor T_mkVolumeNTFSFileDescriptor;
struct T_mkVolumeNTFSFileDescriptor
{
   uint32_t signature;                                                                 /*!< Ce membre contient la valeur de la signature de l'entête. */
   uint16_t updateSequenceOffset;                                                      /*!< Ce membre contient l'offset de l'updateSequence. */
   uint16_t updateSequenceSize;                                                        /*!< Ce membre contient la taille de l'updateSequence. */
   uint32_t lowLogFileSequenceNumber;                                                  /*!< Ce membre contient un identifiant actualisé chaque fois que le record est actualisé (poids faible). */
   uint32_t highLogFileSequenceNumber;                                                 /*!< Ce membre contient un identifiant actualisé chaque fois que le record est actualisé (poids fort). */
   uint16_t useDeletionCount;                                                          /*!< Ce membre contient un compteur indiquant le nombre de modification du record. */
   uint16_t hardLinkCount;                                                             /*!< Ce membre contient le nombre d'entrées qui référence ce record. */
   uint16_t firstAttributeOffset;                                                      /*!< Ce membre contient l'offset du premier attribut. */
   uint16_t flags;                                                                     /*!< Ce membre contient les flags du record (directory, in_used, ...). */
   uint32_t fileSize;                                                                  /*!< Ce membre contient la taille réélle du record (en octets). */
   uint32_t allocatedFileSize;                                                         /*!< Ce membre contient la taille du record sur le disque (en octets). */
   uint32_t lowFileReference;                                                          /*!< Ce membre contient une référence sur le record de base (poids faible). */
   uint32_t highFileReference;                                                         /*!< Ce membre contient une référence sur le record de base (poids fort). */
   uint16_t nextAttributeID;                                                           /*!< Ce membre contient l'identifiant du prochain attribut. */
   uint16_t updateSequenceNumber;                                                      /*!< Ce membre contient la valeur de l'updateSequence. */
};

/**
 * @struct T_mkVolumeNTFS
 * @brief Déclaration de la structure T_mkVolumeNTFS.
 *
 */

typedef struct T_mkVolumeNTFS T_mkVolumeNTFS;
struct T_mkVolumeNTFS
{
   uint16_t label[ K_MK_VOLUME_NTFS_MAX_VOLUME_NAME_LENGTH ];                          /*!< Ce membre contient le nom du volume au format UTF-16. */
   uint16_t bytesPerSector;                                                            /*!< Ce membre contient le nombre d'octets par secteur. */
   uint8_t  sectorsPerCluster;                                                         /*!< Ce membre contient le nombre de secteurs par cluster. */
   uint8_t  padding8;                                                                  /*!< Ce membre contient un octet de padding. */
   uint32_t clusterSize;                                                               /*!< Ce membre contient la taille d'un cluster en octets. */
   uint32_t bytesPerFileRecord;                                                        /*!< Ce membre contient le nombre d'octets par FileRecord. */
   uint32_t clustersPerFileRecord;                                                     /*!< Ce membre contient le nombre de clusters par FileRecord. */
   uint32_t bytesPerIndexBuffer;                                                       /*!< Ce membre contient le nombre d'octets par IndexBuffer. */
   uint32_t clustersPerIndexBuffer;                                                    /*!< Ce membre contient le nombre de clusters par IndexBuffer. */
   uint32_t lowTotalNumberOfSectors;                                                   /*!< Ce membre contient le nombre total de secteurs (poids faible). */
   uint32_t highTotalNumberOfSectors;                                                  /*!< Ce membre contient le nombre total de secteurs (poids fort). */
   uint32_t lowFirsMFTCluster;                                                         /*!< Ce membre contient l'adresse du premier cluster de la MFT (poids faible). */
   uint32_t highFirsMFTCluster;                                                        /*!< Ce membre contient l'adresse du premier cluster de la MFT (poids fort). */
   uint32_t addressOfBPB;                                                              /*!< Ce membre contient l'adresse du BPB. */
};

/**
 *
 */

/**
 * @struct T_mkVolumeName
 * @brief Déclaration de la structure T_mkVolumeName.
 *
 */

typedef struct T_mkVolumeName T_mkVolumeName;
struct T_mkVolumeName
{
   uint32_t id;                                                                        /*!< Ce membre contient la valeur de l'identifiant système de la partition. */
   char8_t str [12];                                                                   /*!< Ce membre contient la chaine de caractères qui stocke l'identifiant système de la partition. */
};

/**
 * @struct T_mkVolumeLayer
 * @brief Déclaration de la structure T_mkVolumeLayer.
 *
 */

typedef struct T_mkVolumeLayer T_mkVolumeLayer;
struct T_mkVolumeLayer
{
   uint16_t type;                                                                      /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_VOLUME). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                                                        /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkVolume. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkVolumeDescriptor
 * @brief Déclaration de la structure T_mkVolumeDescriptor.
 *
 */

typedef union T_mkVolumeDescriptor T_mkVolumeDescriptor;
union T_mkVolumeDescriptor
{
   T_mkVolumeFAT fat;                                                                  /*!< Ce membre contient les données relatives à une partition FAT. */
   T_mkVolumeNTFS ntfs;                                                                /*!< Ce membre contient les données relatives à une partition NTFS. */
};

/**
 * @struct T_mkVolume
 * @brief Déclaration de la structure T_mkVolume.
 *
 */

typedef struct T_mkVolume T_mkVolume;
struct T_mkVolume
{
   T_mkVolumeLayer layer;                                                              /*!< Ce membre contient le registre d'identification du volume de type \ref T_mkVolume. La position de cet attribut ne doit pas être modifiée. */
   uint32_t type;                                                                      /*!< Ce membre contient le type de la partition (\ref T_mkVolumeType). */
   uint32_t status;                                                                    /*!< Ce membre contient le statut de la partition (\ref T_mkVolumeStatus). */
   T_mkVolumeDescriptor partition;                                                     /*!< Ce membre contient les données de la partition. */
   T_mkVolumeName name;                                                                /*!< Ce membre contient la dénomination système de la partition. */
   T_mkVolume* nextVolume;                                                             /*!< Ce membre contient l'adresse de la prochaine partition sur le disque (ou \ref K_MK_NULL si aucune partition n'est présente). */
   T_mkAddr disk;                                                                      /*!< Ce membre contient l'adresse du disque propriétaire de la partition. */
};

/**
 *
 */

#endif

