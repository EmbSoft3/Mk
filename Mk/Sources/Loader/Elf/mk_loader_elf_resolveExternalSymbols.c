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
* @file mk_loader_elf_resolveExternalSymbols.c
* @brief Définition de la fonction mk_loader_elf_resolveExternalSymbols.
* @date 1 janv. 2024
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_loader_elf_getHash ( T_str8 p_symbolName )
{
   /* Déclaration des variables de travail */
   uint32_t l_hash = 0, l_g = 0;

   /* Tant que la chaine n'a pas été entièrement parcourue */
   while ( ( *p_symbolName ) != 0 )
   {
      /* Détermination de la valeur du hash */
      l_hash = ( l_hash << 4 ) + ( uint32_t ) *p_symbolName++;
      l_g = l_hash & 0xf0000000;

      if ( l_g > 0 )
      {
         l_hash ^= l_g >> 24;
      }

      else
      {
         /* Ne rien faire */
      }

      l_hash &= ~l_g;
   }

   /* Retour */
   return ( l_hash );
}

/**
 * @internal
 * @brief
 * @endinternal
 */


static uint32_t mk_loader_elf_getGnuHash ( T_str8 p_symbolName )
{
   /* Déclaration des variables de travail */
   uint32_t l_hash = 5381;
   uint8_t l_character = ( uint8_t ) *p_symbolName;

   /* Tant que la chaine n'a pas été parcourue */
   for ( ; l_character != '\0'; l_character = ( uint8_t ) *p_symbolName )
   {
      /* Actualisation de la valeur du hash */
      l_hash = ( l_hash * 33 ) + l_character;

      /* Actualisation du pointeur de chaine */
      p_symbolName++;
   }

   /* Retour */
   return ( l_hash );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_searchLibrary ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem* p_library, T_str8 p_libraryPath, T_str8 p_libraryName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de fichier */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration des variables de travail */
   uint32_t l_pathLength = 0, l_nameLength = 0, l_length = 0;

   /* Récupération de la longueur de la chaine de caractères */
   l_pathLength = mk_utils_utfsize ( p_libraryPath, K_MK_FONT_UTF8 );
   l_nameLength = mk_utils_utfsize ( p_libraryName, K_MK_FONT_UTF8 );
   l_length = ( uint32_t ) ( l_nameLength + l_pathLength );

   /* Si la longueur de la chaine de caractères est valide */
   if ( l_length  < K_MK_FILE_MAX_NAME_LENGTH )
   {
      /* Concaténation des chaines de caractères */
      ( void ) mk_utils_strcat ( ( T_str8 ) p_library->fileBuf, ( T_str8 ) p_libraryPath, ( T_str8 ) "/" );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_library->fileBuf, ( T_str8 ) p_library->fileBuf, ( T_str8 ) p_libraryName );

      /* On vérifie si la bibliothèque externe est présente dans le répertoire de l'application */
      l_result = mk_file_open ( p_elf32Parser->volume, &l_file, ( T_str8 ) p_library->fileBuf, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );

      /* Si la bibliothèque a été trouvé */
      if ( l_result == K_MK_OK )
      {
         /* Configuration des pointeurs 'path' et 'name' */
         p_library->filePath = ( T_str8 ) &p_library->fileBuf [ 0 ];
         p_library->fileName = ( T_str8 ) &p_library->fileBuf [ l_pathLength + 1 ];
         p_library->fileBuf [ l_pathLength ] = '\0';

         /* Allocation d'une nouvelle page mémoire */
         l_result = mk_application_alloc ( ( T_mkAddr* ) &p_library->baseAddr, 0 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Chargement du programme en mémoire */
            l_result = mk_loader_elf_loadRAM ( l_file, ( T_str8 ) p_library->fileName, p_library->baseAddr, p_list, K_MK_NULL );

            /* Si une erreur s'est produite */
            if ( l_result != K_MK_OK )
            {
               /* Désallocation de la page mémoire */
               l_result |= mk_application_free ( p_library->baseAddr );
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

         /* Fermeture du fichier */
         l_result |= mk_file_close ( l_file, K_MK_NULL );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_loadLibrary ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, T_str8 p_libraryName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de bibliothèques */
   T_mkExternalLibraryItem* l_library;

   /* Allocation d'une nouvelle bibliothèque */
   l_result = mk_pool_allocSafe ( g_mkExternalLibraryItemPool.pool, ( T_mkAddr* ) &l_library, K_MK_POOL_CLEAR, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_library != K_MK_NULL) )
   {
      /* Ajout de la bibliothèque externe dans la liste */
      /* La désallocation est réalisée par la fonction mk_application_loadDynamic */
      l_result = mk_loader_addLibrary ( p_list, l_library );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Recherche de la bibliothèque dans le répertoire de l'application */
         l_result = mk_loader_elf_searchLibrary ( p_elf32Parser, p_list, l_library, p_elf32Parser->path, p_libraryName );

         /* Si la bibliothèque n'est pas présente dans le répertoire de l'application */
         if ( l_result == K_MK_ERROR_NOT_FOUND )
         {
            /* Recherche de la bibliothèque dans le répertoire système */
            /* Si la bibliothèque n'est pas trouvée, on retourne une erreur K_MK_ERROR_NOT_FOUND */
            l_result = mk_loader_elf_searchLibrary ( p_elf32Parser, p_list, l_library, (  T_str8 ) "mk/libs", p_libraryName );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_resolveSymbolExternalLibrary ( T_mkExternalLibraryItem* p_library, T_str8 p_symbolName, uint32_t* p_symbolAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_UNRESOLVED;

   /* Déclaration d'un pointeur d'entrée */
   T_mkELF32SymbolTableEntry* l_symbolEntry;

   /* Déclaration des variables de travail */
   uint32_t *l_hashTableAddr = K_MK_NULL, *l_symbolTableAddr = K_MK_NULL, *l_strTableAddr = K_MK_NULL, *l_bucketAddr = K_MK_NULL,  *l_chainAddr = K_MK_NULL;
   uint32_t  l_nbucket = 0, l_hash = 0, l_index, l_strResult = 0;

   /* Récupération de l'adresse de la table de hachage */
   l_hashTableAddr = ( T_mkAddr ) ( ( uint8_t* ) p_library->dynTable.entry [ K_MK_LOADER_ELF32_DT_HASH ].dField.dAddr + ( uint32_t ) p_library->baseAddr );

   /* Récupération de l'adresse de la table des symboles */
   l_symbolTableAddr = ( T_mkAddr ) ( ( uint8_t* ) p_library->dynTable.entry [ K_MK_LOADER_ELF32_DT_SYMTAB ].dField.dAddr + ( uint32_t ) p_library->baseAddr );
   l_strTableAddr = ( T_mkAddr ) ( ( uint8_t* ) p_library->dynTable.entry [ K_MK_LOADER_ELF32_DT_STRTAB ].dField.dAddr + ( uint32_t ) p_library->baseAddr );

   /* Récupération du nombre de buckets dans la table de hachage */
   /* Le nombre de chaines / nombre de symboles n'est pas récupéré */
   l_nbucket = l_hashTableAddr [ 0 ];

   /* Récupération de l'adresse de stockage des buckets et des chaines dans la table de hachage */
   l_bucketAddr = &l_hashTableAddr [ 2 ];
   l_chainAddr = &l_hashTableAddr [ 2 + l_nbucket ];

   /* Récupération de la valeur du hash */
   l_hash = mk_loader_elf_getHash ( p_symbolName );
   l_hash = _math_mod ( l_hash, l_nbucket );

   /* Tant que la chaine n'a pas été trouvée ou tant que la bucket n'a pas été entièrement parcourue */
   for ( l_index = l_bucketAddr [ l_hash ] ; ( l_index != 0 ) && ( l_strResult == 0 ) ; l_index = l_chainAddr [ l_index ] )
   {
      /* Récupération de l'adresse de l'entrée */
      l_symbolEntry = ( T_mkAddr ) ( ( uint8_t* ) l_symbolTableAddr + ( l_index * p_library->dynTable.entry [ K_MK_LOADER_ELF32_DT_SYMENT ].dField.dVal ) );

      /* Comparaison des chaines de caractères */
      l_strResult = mk_utils_strcomp ( ( T_str8 ) ( ( uint8_t* ) l_strTableAddr + l_symbolEntry->stName ) , ( T_str8 ) p_symbolName, 0, 0 );
   }

   /* Si le symbole recherché a été trouvé */
   if ( l_strResult == 1 )
   {
      /* Résolution de l'adresse du symbole */
      *p_symbolAddr = ( uint32_t ) l_symbolEntry->stValue;

      /* Actualisation de la variable de retour */
      l_result = K_MK_OK;
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

static T_mkCode mk_loader_elf_resolveSymbolExternal ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, T_str8 p_symbolName, uint32_t* p_symbolAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_UNRESOLVED;

   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_libraryName = K_MK_NULL;

   /* Déclaration d'un pointeur de bibliothèques */
   T_mkExternalLibraryItem* l_library = K_MK_NULL;

   /* Déclaration d'un pointeur d'entrée */
   T_mkELF32DynamicTableEntry* l_dynEntry = K_MK_NULL;

   /* Détermination du nombre d'entrées dans la table de données dynamiques de la bibliothèque */
   /* Chaque entrée fait 2*4 octets */
   uint32_t l_dEntryNumber = ( uint32_t ) ( p_elf32Parser->dynEntry.pMemSize / K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE );

   /* Détermination de l'adresse de la section .strname */
   uint8_t* l_strtab = ( uint8_t* ) p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_STRTAB ].dField.dAddr + ( uint32_t ) p_elf32Parser->baseAddr;

   /* Pour le nombre d'entrées dans la table dynamique de la bibliothèque */
   for ( l_counter = 0 ; ( l_counter < l_dEntryNumber ) && ( l_result == K_MK_ERROR_UNRESOLVED ); l_counter++ )
   {
      /* Récupération de la valeur de l'entrée. */
      /* La table a été chargée préalablement en mémoire durant l'écriture des segments */
      l_dynEntry = ( T_mkAddr ) ( ( uint8_t* ) p_elf32Parser->dynEntry.pVirtualAddr +
            ( uint32_t ) p_elf32Parser->baseAddr  + ( uint32_t ) ( l_counter * K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE ) );

      /* Si des dépendances avec des bibliothèques sont présentes */
      if ( l_dynEntry->dTag == K_MK_LOADER_ELF32_DT_NEEDED )
      {
         /* Récupération du nom de la bibliothèque */
         l_libraryName = ( T_str8 ) &l_strtab [ p_elf32Parser->dynTable.entry [ l_dynEntry->dTag ].dField.dVal ];

         /* Test si la bibliothèque a déjà été chargée */
         l_result = mk_loader_searchLibrary ( p_list, &l_library, l_libraryName );

         /* Si la bibliothèque n'a pas été chargée */
         if ( l_result == K_MK_ERROR_NOT_AVAILABLE )
         {
            /* Chargement de la bibliothèque externe depuis le système de fichiers */
            /* Fonction récursive */
            l_result = mk_loader_elf_loadLibrary ( p_elf32Parser, p_list, l_libraryName );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Résolution du symbole */
               l_result = mk_loader_elf_resolveSymbolExternalLibrary ( p_list->first, p_symbolName, p_symbolAddr );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Sinon si la bibliothèque a été chargée */
         else if ( l_result == K_MK_OK )
         {
            /* Résolution du symbole */
            l_result = mk_loader_elf_resolveSymbolExternalLibrary ( l_library, p_symbolName, p_symbolAddr );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_resolveSymbolInternal ( T_str8 p_symbolName, uint32_t* p_symbolAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_UNRESOLVED;

   /* Déclaration d'un pointeur d'entrée */
   T_mkELF32SymbolTableEntry* l_symbolEntry = K_MK_NULL;

   /* Déclaration d'un entête de hashage */
   T_mkELF32GNUHashTable l_hashTable = { 0 };

   /* Déclaration des variables de travail */
   uint32_t l_strResult = 0, l_bloomFilterIndex = 0, l_hash = 0, l_mask = 0;
   uint32_t l_symbolIndex = 0, l_symbolHash = 0;

   /* Récupération de l'adresse de base des symboles internes */
   T_mkInternalSymbolsAreaHeader* l_header = ( T_mkInternalSymbolsAreaHeader* ) _mk_loader_elf_getInternalSymbolsBaseAddr ( );

   /* Vérification de la validité de la table */
   if ( ( l_header->magicNumber == K_MK_LOADER_MAGIC_NUMBER ) && ( l_header->version != 0 ) && ( l_header->headerSize >= K_MK_LOADER_MINIMAL_SIZE ) )
   {
      /* Récupération des informations relatives à la table de hashage */
      l_hashTable.nbuckets   =  l_header->gnuhashBaseAddr [ 0 ];
      l_hashTable.symoffset  =  l_header->gnuhashBaseAddr [ 1 ];
      l_hashTable.bloomSize  =  l_header->gnuhashBaseAddr [ 2 ];
      l_hashTable.bloomShift =  l_header->gnuhashBaseAddr [ 3 ];
      l_hashTable.bloom      = &l_header->gnuhashBaseAddr [ 4 ];
      l_hashTable.buckets    = &l_header->gnuhashBaseAddr [ 4 + l_hashTable.bloomSize ];
      l_hashTable.hashValues = &l_header->gnuhashBaseAddr [ 4 + l_hashTable.bloomSize + l_hashTable.nbuckets ];

      /* Détermination de la valeur du hash correspondant au symbole */
      l_hash = mk_loader_elf_getGnuHash ( p_symbolName );

      /* Détermination de la valeur du masque */
      l_mask = ( uint32_t ) ( 1 << _math_mod ( l_hash, K_MK_LOADER_ELF32_BLOOMFILTER_MASKWORDS_SIZE ) ) |
               ( uint32_t ) ( 1 << _math_mod ( l_hash >> l_hashTable.bloomShift, K_MK_LOADER_ELF32_BLOOMFILTER_MASKWORDS_SIZE ) );

      /* Détermination de l'index du filtre de bloom du symbole */
      l_bloomFilterIndex = ( ( l_hash / K_MK_LOADER_ELF32_BLOOMFILTER_MASKWORDS_SIZE ) & ( l_hashTable.bloomSize - 1 ) );

      /* Test si le symbole est présent dans la liste en utilisant le filtre de bloom */
      /* Ce filtre peut produire des faux positif mais pas de faux négatif */
      if ( ( l_hashTable.bloom [ l_bloomFilterIndex ] & l_mask ) == l_mask )
      {
         /* Détermination de l'index du symbole dans la table de hashage */
         l_symbolIndex = l_hashTable.buckets [ _math_mod ( l_hash, l_hashTable.nbuckets ) ];

         /* Si l'index du symbole est valide */
         if ( l_symbolIndex >= l_hashTable.symoffset )
         {
            /* Tant que le symbole recherché n'a pas été trouvé ou tant que toutes les entrées de la bucket n'ont pas été analysées */
            while ( ( ( l_symbolHash & 0x1 ) == 0 ) && ( l_strResult == 0 ) )
            {
               /* Récupération de l'adresse du symbole en cours d'analyse */
               l_symbolEntry = ( T_mkAddr ) ( ( uint8_t* ) l_header->symtabBaseAddr + ( uint32_t ) ( l_symbolIndex * sizeof ( T_mkELF32SymbolTableEntry ) ) );

               /* Récupération de la valeur du hash correspondant au symbole */
               l_symbolHash = l_hashTable.hashValues [ l_symbolIndex - l_hashTable.symoffset ];

               /* Si les valeurs de hachage sont identiques */
               if ( ( l_symbolHash | 0x1 ) == ( l_hash | 0x1 ) )
               {
                  /* Comparaison des chaines de caractères */
                  l_strResult = mk_utils_strcomp ( ( T_str8 ) ( ( uint8_t* ) l_header->strtabBaseAddr + l_symbolEntry->stName ), ( T_str8 ) p_symbolName, 0, 0 );

                  /* Si le symbole recherché a été trouvé */
                  if ( l_strResult == 1 )
                  {
                     /* Résolution de l'adresse du symbole */
                     *p_symbolAddr = ( uint32_t ) l_symbolEntry->stValue;

                     /* Actualisation de la variable de retour */
                     l_result = K_MK_OK;
                  }
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Passage au prochain symbole de la bucket */
               l_symbolIndex = ( uint32_t )l_symbolIndex + 1;
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
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_loader_elf_resolveExternalSymbols ( T_mkELF32FileParser* p_parser, T_mkExternalLibrariesList* p_list, T_str8 p_symbolName, uint32_t* p_symbolAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_symbolName != K_MK_NULL ) && ( p_symbolAddr != K_MK_NULL ) )
   {
      /* Initialisation de la variable de retour */
      *p_symbolAddr = 0;

      /* Recherche du symbole dans l'ensemble des bibliothèques externes en priorité */
      l_result = mk_loader_elf_resolveSymbolExternal ( p_parser, p_list, p_symbolName, p_symbolAddr );

      /* Si le symbole n'a pas été trouvé et qu'aucune erreur ne s'est produite */
      if ( l_result == K_MK_ERROR_UNRESOLVED )
      {
         /* Recherche du symbole dans les symboles internes du système */
         l_result = mk_loader_elf_resolveSymbolInternal ( p_symbolName, p_symbolAddr );
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


