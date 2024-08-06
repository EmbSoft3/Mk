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
* @file mk_fat_types.h
* @brief Déclaration des types dédiés au système de fichiers FAT32.
* @date 26 déc. 2020
*
*/

#ifndef MK_FAT_TYPES_H
#define MK_FAT_TYPES_H

/**
 * @struct T_mkFATFile
 * @brief Déclaration de la structure T_mkFATFile.
 *
 */

typedef struct T_mkFATFile T_mkFATFile;
struct T_mkFATFile
{
   uint32_t  directoryCluster;                                          /*!< Ce membre contient le cluster du répertoire où l'entrée du fichier est stockée. */
   uint32_t  firstCluster;                                              /*!< Ce membre contient l'adresse du premier cluster de données du fichier. */
   uint32_t  entryCluster;                                              /*!< Ce membre contient l'adresse du cluster où l'entrée du fichier est stockée. */
   uint32_t  virtualEntryCluster;                                       /*!< Ce membre contient l'adresse du cluster virtuel où l'entrée du fichier est stockée (ou valeur \ref K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT si le fichier est au format 8.3). */
   uint16_t  entryIndex;                                                /*!< Ce membre contient l'index de l'entrée par rapport au cluster où le fichier est stockée. */
   uint16_t  virtualEntryIndex;                                         /*!< Ce membre contient l'index de l'entrée virtuelle par rapport au cluster où le fichier est stockée (ou valeur \ref K_MK_FAT_VIRTUAL_ENTRY_DEFAULT si le fichier est au format 8.3). */
   uint32_t  currentCluster;                                            /*!< Ce membre contient la valeur du cluster où est localisé le pointeur de fichier. */
   uint32_t  currentPointer;                                            /*!< Ce membre contient la valeur du pointeur de fichier. Il évolue entre [0 et size]. */
   uint32_t  size;                                                      /*!< Ce membre contient la taille du fichier [en octets]. */
   uint32_t* clusterMap;                                                /*!< Ce membre contient l'adresse du cache utilisé pour précharger l'adresse de \ref K_MK_FAT_CLUSTER_MAP_LENGTH avant une opération de lecture/écriture. */
};

/**
 * @enum T_mkFATEntryType
 * @brief Déclaration de l'énumération T_mkFATEntryType.
 *
 */

typedef enum T_mkFATEntryType
{
   K_MK_FAT_ENTRY_SP = 0,                                               /*!< Ce code est l'identifiant des deux entrées spéciales '.' et '..' . */
   K_MK_FAT_ENTRY_ST = 1,                                               /*!< Ce code est l'identifiant d'une entrée standard au format 8.3 . */
   K_MK_FAT_ENTRY_EX = 2                                                /*!< Ce code est l'identifiant d'une entrée étendue. */
} T_mkFATEntryType;

/**
 * @enum T_mkFATUnlinkMode
 * @brief Déclaration de l'énumération T_mkFATUnlinkMode.
 *
 */

typedef enum T_mkFATUnlinkMode
{
   K_MK_FAT_RELEASE_CLUSTERS = 0,                                       /*!< Ce code indique que la chaine de clusters doit être désallouée lors de la suppression d'une entrée. */
   K_MK_FAT_KEEP_CLUSTERS = 1                                           /*!< Ce code indique que la chaine de clusters ne doit pas être désallouée lors de la suppression d'une entrée. */
} T_mkFATUnlinkMode;

/**
 * @struct T_mkFATEntryDescriptor
 * @brief Déclaration de l'énumération T_mkFATEntryDescriptor.
 *
 */

typedef struct T_mkFATEntryDescriptor T_mkFATEntryDescriptor;
struct T_mkFATEntryDescriptor
{
   uint8_t  name [8];                                                   /*!< Ce membre contient les 8 caractères (nom) codant un nom de fichier court. */
   uint8_t  extension [3];                                              /*!< Ce membre contient les 3 caractères (extension) codant l'extension d'un fichier court. */
   uint8_t  attribute;                                                  /*!< Ce membre contient les attributs d'un fichier (\ref T_mkFATFileAttribute). */
   uint8_t  caseType;                                                   /*!< Ce membre contient le registre indiquant si le nom 8.3 du fichier est entièrement en minuscule ou en majuscule. */
   uint8_t  checksum;                                                   /*!< Ce membre contient le checksum de l'entrée. */
   uint16_t creationTime;                                               /*!< Ce membre contient l'heure de création du fichier. */
   uint16_t creationDate;                                               /*!< Ce membre contient la date de création du fichier. */
   uint16_t accessDate;                                                 /*!< Ce membre contient la date du dernier accès au fichier. */
   uint16_t firstClusterHigh;                                           /*!< Ce membre contient l'adresse du premier cluster de données (poids fort). */
   uint16_t modificationTime;                                           /*!< Ce membre contient l'heure de modification du fichier. */
   uint16_t modificationDate;                                           /*!< Ce membre contient la date de modification du fichier. */
   uint16_t firstClusterLow;                                            /*!< Ce membre contient l'adresse du premier cluster de données (poids faible). */
   uint32_t fileSize;                                                   /*!< Ce membre contient la taille du fichier (en octets). */
};

/**
 * @struct T_mkFATEntryAddress
 * @brief Déclaration de la structure T_mkFATEntryAddress.
 *
 */

typedef struct T_mkFATEntryAddress T_mkFATEntryAddress;
struct T_mkFATEntryAddress
{
   uint16_t entryIndex;                                                 /*!< Ce membre contient l'index de l'entrée par rapport au début du secteur. */
   uint16_t blockIndex;                                                 /*!< Ce membre contient l'index du secteur par rapport au début du cluster. */
   uint32_t currentBlock;                                               /*!< Ce membre contient l'adresse du secteur courant. */
   uint32_t currentCluster;                                             /*!< Ce membre contient l'adresse du cluster courant. */
};

/**
 * @struct T_mkFATEntryHandler
 * @brief Déclaration de la structure T_mkFATEntryHandler.
 *
 */

typedef struct T_mkFATHandler T_mkFATHandler;
struct T_mkFATHandler
{
   uint16_t entrySearched;                                              /*!< Ce membre contient l'index de l'entrée recherchée. */
   uint8_t  entryChecksum;                                              /*!< Ce membre contient le checksum contenu dans l'entrée. */
   uint8_t  padding;                                                    /*!< Ce membre contient un octet de padding. */
   uint16_t entryBlockIndex;                                            /*!< Ce membre contient l'index de l'entrée par rapport au secteur. */
   uint16_t entryClusterIndex;                                          /*!< Ce membre contient l'index de l'entrée par rapport au début du cluster. */
   uint16_t entryVirtualClusterIndex;                                   /*!< Ce membre contient l'index de l'entrée virtuelle par rapport au début du cluster. */
   uint16_t entryVirtualNumber;                                         /*!< Ce membre contient le nombre d'entrées étendues. */
   uint32_t entryBlock;                                                 /*!< Ce membre contient l'adresse du bloc de données où est localisé l'entrée. */
   uint32_t entryCluster;                                               /*!< Ce membre contient le cluster où est localisé l'entrée. */
   uint32_t entryVirtualCluster;                                        /*!< Ce membre contient le cluster où est localisé l'entrée virtuelle. */
   uint32_t firstDataCluster;                                           /*!< Ce membre contient l'adresse du premier cluster de données du fichier. */
   uint32_t blockIndex;                                                 /*!< Ce membre contient l'index du secteur dans le cluster. */
   uint32_t directoryIndex;                                             /*!< Ce membre contient l'index du répertoire analysé. */
   uint32_t directoryCluster;                                           /*!< Ce membre contient le numéro du cluster où est localisée la première entrée d'un répertoire. */
   uint32_t currentBlock;                                               /*!< Ce membre contient l'adresse du secteur courant. */
   uint32_t currentCluster;                                             /*!< Ce membre contient l'adresse du cluster courant. */
   uint32_t fileNameLength;                                             /*!< Ce membre contient la longueur courante du nom de fichier en cours d'analyse. */
   uint32_t flag;                                                       /*!< Ce membre contient une variable d'état générale. */
};

/**
 * @enum T_mkFATFileAttribute
 * @brief Déclaration de l'énumération T_mkFATFileAttribute.
 *
 */

typedef enum T_mkFATFileAttribute
{
   K_MK_FAT_NO_ATTRIBUTE = 0,
   K_MK_FAT_READ_ONLY = 0x01,                                           /*!< Ce code indique que le fichier est en lecture seule. */
   K_MK_FAT_HIDDEN = 0x02,                                              /*!< Ce code indique que le fichier est cachée. */
   K_MK_FAT_SYSTEM_FILE = 0x04,                                         /*!< Ce code indique que le fichier est un fichier système. */
   K_MK_FAT_VOLUME_LABEL = 0x08,                                        /*!< Ce code indique que le fichier est une partition. */
   K_MK_FAT_EXTENDED = 0x0F,                                            /*!< Ce code indique que l'entrée est étendue. */
   K_MK_FAT_SUBDIRECTORY = 0x10,                                        /*!< Ce code indique que le fichier est un répertoire. */
   K_MK_FS_FAT_ARCHIVE = 0x20                                           /*!< Ce code indique que le fichier est une archive. */
} T_mkFATFileAttribute;

/**
 * @enum T_mkFATEntryAttribute
 * @brief Déclaration de l'énumération T_mkFATEntryAttribute.
 *
 */

typedef enum T_mkFATEntryAttribute
{
   K_MK_FAT_NO_ENTRY = 0,                                               /*!< Ce code indique que l'entrée d'un répertoire n'est pas utilisée. */
   K_MK_FAT_E5_ENTRY = 0x05,                                            /*!< Ce code indique que le premier caractère du nom d'une entrée est le caractère '0xE5'. */
   K_MK_FAT_DELETED_ENTRY = 0xE5                                        /*!< Ce code indique que l'entrée d'un répertoire a été supprimée. */
} T_mkFATEntryAttribute;

/**
 * @enum T_mkFATCaseAttribute
 * @brief Déclaration de l'énumération T_mkFATCaseAttribute.
 *
 */

typedef enum T_mkFATCaseAttribute
{
   K_MK_FAT_NAME_LOWER_CASE_FLAG = 0x08,                                /*!< Ce code indique que le nom d'un fichier est intégralement en minuscule. */
   K_MK_FAT_EXTENSION_LOWER_CASE_FLAG = 0x10                            /*!< Ce code indique que l'extension d'un fichier est intégralement en minuscule. */
} T_mkFATCaseAttribute;


/**
 *
 */

#endif

