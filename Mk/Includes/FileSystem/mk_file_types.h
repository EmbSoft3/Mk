/**
*
* @copyright Copyright (C) 2020-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_file_types.h
* @brief Déclaration des types dédiés au système de fichiers.
* @date 26 déc. 2020
*
*/

#ifndef MK_FILE_TYPES_H
#define MK_FILE_TYPES_H

/**
 * @enum T_mkFileMode
 * @brief Déclaration de l'énumération T_mkFileMode.
 *
 */

typedef enum T_mkFileMode
{
   K_MK_FS_OPEN_EXISTING = 1,                                  /*!< Définition du code d'ouverture d'un fichier. Ouvre un fichier s'il existe, sinon échec de la fonction. Positionne le pointeur de fichier au début du fichier. */
   K_MK_FS_OPEN_ALWAYS = 2,                                    /*!< Définition du code d'ouverture d'un fichier. Ouvre un fichier s'il existe, sinon création. Positionne le pointeur de fichier au début du fichier. */
   K_MK_FS_OPEN_APPEND = 4,                                    /*!< Définition du code d'ouverture d'un fichier. Ouvre un fichier s'il existe, sinon création. Positionne le pointeur de fichier à la fin du fichier. */
   K_MK_FS_OPEN_CREATE = 8,                                    /*!< Définition du code d'ouverture d'un fichier. Création d'un nouveau fichier, échec de la fonction s'il existe. */
   K_MK_FS_OPEN_CREATE_DIRECTORY = 16,                         /*!< Définition du code d'ouverture d'un fichier. Création d'un nouveau répertoire, échec de la fonction s'il existe. */
   K_MK_FS_OPEN_TRUNCATE = 32,                                 /*!< Définition du code d'ouverture d'un fichier. Création d'un nouveau fichier, le fichier est tronqué s'il existe. */
   K_MK_FS_OPEN_READ = 64,                                     /*!< Définition du code d'ouverture d'un fichier. Le fichier possède les accès en lecture. */
   K_MK_FS_OPEN_WRITE = 128,                                   /*!< Définition du code d'ouverture d'un fichier. Le fichier possède les accès en écriture. */
   K_MK_FS_OPEN_SHARED = 256                                   /*!< Définition du code d'ouverture d'un fichier. Le fichier est partagé entre plusieurs processus. */
} T_mkFileMode;

/**
 * @enum T_mkFileAttribute
 * @brief Déclaration de l'énumération T_mkFileAttribute.
 *
 */

typedef enum T_mkFileAttribute
{
   K_MK_FS_ATTRIBUTE_NO = 0x0,                                 /*!< Définition d'un code indiquant que le fichier n'a pas d'attribut. */
   K_MK_FS_ATTRIBUTE_READ_ONLY = 0x1,                          /*!< Définition d'un code indiquant que le fichier est en lecture seule. */
   K_MK_FS_ATTRIBUTE_HIDDEN = 0x2,                             /*!< Définition d'un code indiquant que le fichier est cachée. */
   K_MK_FS_ATTRIBUTE_SYSTEM = 0x4,                             /*!< Définition d'un code indiquant que le fichier est un fichier système. */
   K_MK_FS_ATTRIBUTE_VOLUME = 0x8,                             /*!< Définition d'un code indiquant que le fichier est une partition. */
   K_MK_FS_ATTRIBUTE_EXTENTED = 0xF,                           /*!< Définition d'un code indiquant que l'entrée est étendue. */
   K_MK_FS_ATTRIBUTE_DIRECTORY = 0x10,                         /*!< Définition d'un code indiquant que le fichier est un répertoire. */
   K_MK_FS_ATTRIBUTE_ARCHIVE = 0x20                            /*!< Définition d'un code indiquant que le fichier est une archive. */
} T_mkFileAttribute;

/**
 * @enum T_mkFileEof
 * @brief Déclaration de l'énumération T_mkFileEof.
 *
 */

typedef enum T_mkFileEof
{
   K_MK_FS_EOF_FALSE = 0,                                      /*!< Définition d'un code indiquant que la fin du fichier a été atteinte. */
   K_MK_FS_EOF_TRUE = 1                                        /*!< Définition d'un code indiquant que la fin du fichier n'a pas été atteinte. */
} T_mkFileEof;

/**
 * @enum T_mkFileType
 * @brief Déclaration de l'énumération T_mkFileType.
 *
 */

typedef enum T_mkFileType
{
   K_MK_FS_TYPE_DIRECTORY = 0,                                 /*!< Définition d'un code indiquant que l'instance d'un fichier de type \ref T_mkFile est un répertoire. */
   K_MK_FS_TYPE_FILE = 1,                                      /*!< Définition d'un code indiquant que l'instance d'un fichier de type \ref T_mkFile est un fichier. */
   K_MK_FS_TYPE_ROOTDIRECTORY = 2                              /*!< Définition d'un code indiquant que l'instance d'un fichier de type \ref T_mkFile est un répertoire racine. */
} T_mkFileType;

/**
 * @enum T_mkFilePointer
 * @brief Déclaration de l'énumération T_mkFilePointer.
 *
 */

typedef enum T_mkFilePointer
{
   K_MK_FS_POINTER_TO_SOF = 0,                                 /*!< Définition d'un code positionnant le pointeur de fichier au début du fichier. */
   K_MK_FS_POINTER_TO_EOF = ( int32_t ) 0xFFFFFFFF             /*!< Définition d'un code positionnant le pointeur de fichier à la fin du fichier. */
} T_mkFilePointer;

/**
 * @enum T_mkFileRequest
 * @brief Déclaration de la structure T_mkFileRequest.
 *
 */

typedef enum T_mkFileRequest
{
   K_MK_FS_CHMOD = 1,                                          /*!< Définition de l'identifiant de la requête CHMOD. */
   K_MK_FS_CLOSE = 2,                                          /*!< Définition de l'identifiant de la requête CLOSE. */
   K_MK_FS_EOF = 3,                                            /*!< Définition de l'identifiant de la requête EOF. */
   K_MK_FS_EXPAND = 4,                                         /*!< Définition de l'identifiant de la requête EXPAND. */
   K_MK_FS_GETNAME = 5,                                        /*!< Définition de l'identifiant de la requête GETNAME. */
   K_MK_FS_LINK = 6,                                           /*!< Définition de l'identifiant de la requête LINK. */
   K_MK_FS_OPEN = 7,                                           /*!< Définition de l'identifiant de la requête OPEN. */
   K_MK_FS_OPEN_DIRECTORY = 8,                                 /*!< Définition de l'identifiant de la requête OPEN_DIRECTORY. */
   K_MK_FS_OPEN_RELATIVE = 9,                                  /*!< Définition de l'identifiant de la requête OPEN_RELATIVE. */
   K_MK_FS_READ = 10,                                          /*!< Définition de l'identifiant de la requête READ. */
   K_MK_FS_RENAME = 11,                                        /*!< Définition de l'identifiant de la requête RENAME. */
   K_MK_FS_SEEK = 12,                                          /*!< Définition de l'identifiant de la requête SEEK. */
   K_MK_FS_STAT = 13,                                          /*!< Définition de l'identifiant de la requête STAT. */
   K_MK_FS_TELL = 14,                                          /*!< Définition de l'identifiant de la requête TELL. */
   K_MK_FS_TRUNCATE = 15,                                      /*!< Définition de l'identifiant de la requête TRUNCATE. */
   K_MK_FS_UNLINK = 16,                                        /*!< Définition de l'identifiant de la requête UNLINK. */
   K_MK_FS_WRITE = 17,                                         /*!< Définition de l'identifiant de la requête WRITE. */
   K_MK_FS_FILEINFO = 18,                                      /*!< Définition de l'identifiant de la requête FILE_INFO. */
   K_MK_FS_SIZE = 19,                                          /*!< Définition de l'identifiant de la requête SIZE. */
   K_MK_FS_TYPE = 20                                           /*!< Définition de l'identifiant de la requête TYPE. */
} T_mkFileRequest;

/**
 * @union T_mkFileDescriptor
 * @brief Déclaration de l'union T_mkFileDescriptor.
 *
 */

typedef union T_mkFileDescriptor T_mkFileDescriptor;
union T_mkFileDescriptor
{
   T_mkFATFile fat;                                            /*!< Ce membre contient le descripteur d'un fichier FAT32. */
};

/**
 * @union T_mkFileInfo
 * @brief Déclaration de l'union T_mkFileInfo.
 *
 */

typedef union T_mkFileInfo T_mkFileInfo;
union T_mkFileInfo
{
   T_mkFATEntryDescriptor fat;                                 /*!< Ce membre contient les données relatives à un fichier FAT32. */
};

/**
 * @struct T_mkFileFlag
 * @brief Déclaration de l'union T_mkFileFlag.
 *
 */

typedef struct T_mkFileFlag T_mkFileFlag;
struct T_mkFileFlag
{
   unsigned_t read:1;                                          /*!< Ce membre contient un drapeau indiquant que le fichier peut être accédé en lecture. */
   unsigned_t write:1;                                         /*!< Ce membre contient un drapeau indiquant que le fichier peut être accédé en écriture. */
   unsigned_t shared:1;                                        /*!< Ce membre contient un drapeau indiquant que le fichier est partagé. */
   unsigned_t deleted:1;                                       /*!< Ce membre contient un drapeau indiquant que le fichier a été supprimé. */
   unsigned_t modified:1;                                      /*!< Ce membre contient un drapeau indiquant que le fichier a été modifié. */
   unsigned_t rootDirectory:1;                                 /*!< Ce membre contient un drapeau indiquant que le fichier est le répertoire racine. */
   unsigned_t writeProtect:1;                                  /*!< Ce membre contient un drapeau indiquant que le disque stockant le fichier est protégé en écriture. */
   unsigned_t reserved:25;                                     /*!< Ce champ est reservé. */
};

/**
 * @struct T_mkFileMessage
 * @brief Déclaration de la structure T_mkFileMessage.
 *
 */

typedef struct T_mkFileMessage T_mkFileMessage;
struct T_mkFileMessage
{
   uint32_t requestIdentifier;                                 /*!< Ce membre contient l'identifiant d'une requête de type \ref T_mkFileRequest. */
   T_mkAddr argument1;                                         /*!< Ce membre contient le premier arguments de la requête. */
   T_mkAddr argument2;                                         /*!< Ce membre contient le deuxième arguments de la requête. */
   T_mkAddr argument3;                                         /*!< Ce membre contient le troisième arguments de la requête. */
   T_mkAddr argument4;                                         /*!< Ce membre contient le quatrième argument de la requête. */
   T_mkAddr argument5;                                         /*!< Ce membre contient le cinquième argument de la requête. */
   T_mkCode* result;                                           /*!< Ce membre contient le résultat de la requête. */
   T_mkCallback* callback;                                     /*!< Ce membre contient l'adresse d'une fonction de rappel. */
};

/**
 * @struct T_mkFile
 * @brief Déclaration de l'union T_mkFile.
 *
 */

typedef struct T_mkFile T_mkFile;
struct T_mkFile
{
   T_mkVolume* volume;                                         /*!< Ce membre contient l'adresse de la partition du fichier. */
   T_mkFileDescriptor descriptor;                              /*!< Ce membre contient le descripteur du fichier. */
   T_mkFileFlag flag;                                          /*!< Ce membre contient le registre de statut du fichier. */
   uint8_t* buf;                                               /*!< Ce membre contient le dernier bloc de données chargé dans le cache. Il doit être aligné sur 4 octets */
   uint32_t cacheCurrentAddress;                               /*!< Ce membre contient l'adresse de la dernière fenêtre chargée dans le cache. */
   T_mkAddr cacheBaseAddress;                                  /*!< Ce membre contient l'adresse du cache dans la mémoire. */
   uint32_t cacheFlushFlag;                                    /*!< Ce membre contient le drapeau de synchronisation du cache et du disque. */
};

/**
 *
 */

#endif

