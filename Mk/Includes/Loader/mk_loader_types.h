/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_loader_types.h
* @brief Déclaration des types dédiés aux chargements des fichiers de programmation et des bibliothèques externes.
* @date 13 janv. 2024
*
*/

#ifndef MK_LOADER_TYPES_H
#define MK_LOADER_TYPES_H

/**
 * @struct T_mkInternalSymbolsAreaHeader
 * @brief Déclaration de la structure T_mkInternalSymbolsAreaHeader.
 *
 */

typedef struct T_mkInternalSymbolsAreaHeader T_mkInternalSymbolsAreaHeader;
struct T_mkInternalSymbolsAreaHeader
{
   uint32_t  magicNumber;                                               /*!< Ce membre contient la signature de l'entête. */
   uint32_t  headerSize;                                                /*!< Ce membre contient la taille de l'entête [en octets]. */
   uint32_t  reserved;                                                  /*!< Ce membre est reservé. */
   uint32_t  version;                                                   /*!< Ce membre contient la version de l'entête */
   uint32_t* symtabBaseAddr;                                            /*!< Ce membre contient l'adresse de base de la section .symtab. */
   uint32_t  symtabSize;                                                /*!< Ce membre contient la taille de la section .symtab [en octets]. */
   uint8_t*  strtabBaseAddr;                                            /*!< Ce membre contient l'adresse de base de la section .strtab. */
   uint32_t  strtabSize;                                                /*!< Ce membre contient la taille de la section .strtab [en octets]. */
   uint32_t* gnuhashBaseAddr;                                           /*!< Ce membre contient l'adresse de base de la section .gnuhash. */
   uint32_t  gnuhashSize;                                               /*!< Ce membre contient la taille de la section .gnuhash [en octets]. */
};

/**
 * @struct T_mkExternalLibraryItem
 * @brief Déclaration de la structure T_mkExternalLibraryItem.
 *
 */

typedef struct T_mkExternalLibraryItem T_mkExternalLibraryItem;
struct T_mkExternalLibraryItem
{
   int8_t fileBuf [ K_MK_FILE_MAX_NAME_LENGTH + 1 ];                    /*!< Ce membre contient une chaine de caractères stockant le chemin et le nom d'une bibliothèque externe. */
   T_str8 fileName;                                                     /*!< Ce membre contient l'adresse de la chaine de caractère contenant le nom de la bibliothèque externe. */
   T_str8 filePath;                                                     /*!< Ce membre contient l'adresse de la chaine de caractère contenant le chemin de la bibliothèque externe. */
   T_mkAddr baseAddr;                                                   /*!< Ce membre contient l'adresse de base de la bibliothèque externe. */
   T_mkELF32DynamicTable dynTable;                                      /*!< Ce membre contient la table dynamique de la bibliothèque externe. */
   T_mkExternalLibraryItem* next;                                       /*!< Ce membre contient l'adresse de la prochaine bibliothèque externe. */
};

/**
 * @struct T_mkExternalLibraryItem
 * @brief Déclaration de la structure T_mkExternalLibraryItem.
 *
 */

typedef struct T_mkExternalLibrariesList T_mkExternalLibrariesList;
struct T_mkExternalLibrariesList
{
   T_mkExternalLibraryItem* first;                                      /*!< Ce membre contient l'adresse de la première bibliothèque d'une liste. */
};

/**
 * @struct T_mkExternalLibraryItem
 * @brief Déclaration de la structure T_mkExternalLibraryItem.
 *
 */

typedef struct T_mkExternalLibraryItemPool T_mkExternalLibraryItemPool;
struct T_mkExternalLibraryItemPool
{
   T_mkPool* pool;                                                      /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les bibliothèques externes (\ref T_mkExternalLibraryItem). */
   T_mkPoolArea area;                                                   /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkExternalLibraryItem buf [ K_MK_LOADER_LIBRARY_ITEM_NUMBER ];     /*!< Ce membre contient la mémoire dédiée aux bibliothèques externes. */
};

/**
 *
 */

#endif


