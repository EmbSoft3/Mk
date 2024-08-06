/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_loader_elf_loadRAM.c
* @brief Définition de la fonction mk_loader_elf_loadRAM.
* @date 21 déc. 2023
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_getProgramHeaderEntry ( T_mkFile* p_file, T_mkELF32FileParser* p_elf32Parser, T_mkELF32ProgramHeaderEntry* p_entry, uint32_t p_entryIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Configuration du pointeur de fichier au début d'une entrée */
   l_result = mk_file_seek ( p_file, p_elf32Parser->fileHeader.ePhoff + ( p_entryIndex * p_elf32Parser->fileHeader.ePhentSize ), K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture de l'entrée */
      l_result = mk_file_read ( p_file, p_entry, K_MK_LOADER_ELF32_PROGRAMHEADER_ENTRY_SIZE, &l_numberOfBytesRead, K_MK_NULL );

      /* Si une erreur s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != K_MK_LOADER_ELF32_PROGRAMHEADER_ENTRY_SIZE ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_UNEXPECTED;
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

static T_mkCode mk_loader_elf_writeSegmentToMemory ( T_mkFile* p_file, T_mkELF32ProgramHeaderEntry* p_entry, T_mkAddr p_offsetAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de traval */
   uint32_t l_numberOfBytesRead = 0;

   /* Détermination de l'adresse de destination du segment */
   uint32_t* l_destinationAddr = ( T_mkAddr ) ( ( uint8_t* ) p_offsetAddr + ( uint32_t ) p_entry->pVirtualAddr );

   /* Configuration du pointeur de fichier */
   l_result = mk_file_seek ( p_file, p_entry->pOffset, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture du segment dans la mémoire */
      /* Les données lues sont écrites directement à leur destination. */
      l_result = mk_file_read ( p_file, l_destinationAddr, p_entry->pFileSize, &l_numberOfBytesRead, K_MK_NULL );

      /* Si une erreur s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != p_entry->pFileSize ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_UNEXPECTED;
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

static T_mkCode mk_loader_elf_loadMemorySegments ( T_mkFile* p_file, T_mkELF32FileParser* p_elf32Parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une entrée */
   T_mkELF32ProgramHeaderEntry l_entry;

   /* Déclaration des variables de travail */
   uint32_t* l_destinationAddr, l_counter;

   /* Pour le nombre d'entrées dans la table des segments ('Program Header Table') */
   for ( l_counter = 0 ; ( l_result == K_MK_OK ) && ( l_counter < p_elf32Parser->fileHeader.ePhnum ) ; l_counter++ )
   {
      /* Récupération de la valeur de l'entrée */
      l_result = mk_loader_elf_getProgramHeaderEntry ( p_file, p_elf32Parser, &l_entry, l_counter );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si l'entrée est de type 'PT_DYNAMIC', on la stocke dans le parseur. */
         /* Celle-ci sera utilisée lors de la résolution des symboles. */
         if ( l_entry.pType == K_MK_LOADER_ELF32_PT_DYNAMIC )
         {
            _copy ( &p_elf32Parser->dynEntry, &l_entry, K_MK_LOADER_ELF32_PROGRAMHEADER_ENTRY_SIZE );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Note : Le système ne possède pas de MMU, le mécanisme de pagination ne peut donc pas être mis en oeuvre. */
         /* On se contente de charger les segments de données à l'adresse 'p_offsetAddr'. */
         /* La page de données à une taille de K_MK_LOADER_MEMORY_PAGE_SIZE. */

         /* Si l'entrée est de type 'PT_LOAD' ou 'PT_DYNAMIC' */
         if ( ( l_entry.pType == K_MK_LOADER_ELF32_PT_LOAD ) ||
              ( l_entry.pType == K_MK_LOADER_ELF32_PT_DYNAMIC ) )
         {
            /* Si le segment est valide */
            if ( l_entry.pFileSize <= l_entry.pMemSize )
            {
               /* Si le segment peut être écrit dans la page mémoire allouée */
               if ( ( ( uint32_t ) l_entry.pVirtualAddr < K_MK_LOADER_MEMORY_PAGE_SIZE ) &&
                  ( ( uint32_t ) ( ( uint8_t* ) l_entry.pVirtualAddr + l_entry.pMemSize ) < K_MK_LOADER_MEMORY_PAGE_SIZE ) )
               {
                  /* Si une copie doit être réalisée dans la mémoire */
                  if ( l_entry.pFileSize != 0 )
                  {
                     /* Ecriture du segment en mémoire */
                     mk_loader_elf_writeSegmentToMemory ( p_file, &l_entry, p_elf32Parser->baseAddr );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

                  /* Si des données supplémentaires sont à copier (section .bss ou autres) */
                  if ( l_entry.pMemSize != l_entry.pFileSize )
                  {
                     /* Détermination de l'adresse de destination du segment */
                     l_destinationAddr = ( T_mkAddr ) ( ( uint8_t* ) p_elf32Parser->baseAddr +
                           ( uint32_t ) l_entry.pVirtualAddr + l_entry.pFileSize );

                     /* Remplissage de la mémoire avec des 0 */
                     _writeBytes ( l_destinationAddr, 0, ( uint32_t ) ( l_entry.pMemSize - l_entry.pFileSize ) );
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
                  /* On passe au prochain segment. */
               }
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_CORRUPTED;
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire, on ne charge pas les segments de type PT_PHDR ou PT_INTERP en mémoire. */
            /* Non utile. */
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

static void mk_loader_elf_parseDynamicTable ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Déclaration d'un pointeur d'entrée */
   T_mkELF32DynamicTableEntry* l_dynEntry = K_MK_NULL;

   /* Détermination du nombre d'entrées dans la table de données dynamiques ('DynamicTable') */
   /* Chaque entrée fait 2*4 octets */
   uint32_t l_dEntryNumber = ( uint32_t ) ( p_elf32Parser->dynEntry.pMemSize / K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE );

   /* Pour le nombre d'entrées dans la table */
   for ( l_counter = 0 ; l_counter < l_dEntryNumber ; l_counter++ )
   {
      /* Récupération de la valeur de l'entrée. */
      /* La table a été chargée préalablement en mémoire durant l'écriture des segments */
      l_dynEntry = ( T_mkAddr ) ( ( uint8_t* ) p_elf32Parser->dynEntry.pVirtualAddr +
            ( uint32_t ) p_elf32Parser->baseAddr  + ( uint32_t ) ( l_counter * K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE ) );

      /* Si le tag de l'entrée est supporté */
      if ( l_dynEntry->dTag <= K_MK_LOADER_ELF32_DT_BIND_NOW )
      {
         /* Enregistrent de la valeur de l'entrée dans la structure de données du parser. */
         _copy ( &p_elf32Parser->dynTable.entry [ l_dynEntry->dTag ], l_dynEntry, K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si une bibliothèque externe est en train d'être chargée */
   if ( p_list->first != K_MK_NULL )
   {
      /* Copie de la table de données dynamiques */
      /* La bibliothèque externe est toujours la première entrée de la liste */
      _copy ( &p_list->first->dynTable, &p_elf32Parser->dynTable, sizeof ( T_mkELF32DynamicTable )  );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_relocateSymbols ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si l'entrée contenant la table des symboles est présentes dans le fichier */
   if ( ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_SYMTAB ].dTag != 0 ) && p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_STRTAB ].dTag != 0 )
   {
      /* Si une table de relocalisation de type RELA est disponible */
      if ( ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_RELA ].dTag != 0 ) && ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_RELASZ ].dTag != 0 ) &&
           ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_RELAENT ].dTag != 0 ) && ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_HASH ].dTag != 0 ) )
      {
         /* Réalisation des relocalisations avec addend */
         l_result = mk_loader_elf_relocate ( p_elf32Parser, p_list, K_MK_LOADER_ELF32_DT_RELA );
      }

      /* Sinon si une table de relocalisation de type REL est disponible */
      else if ( ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_REL ].dTag != 0 ) && ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_RELSZ ].dTag != 0 ) &&
           ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_RELENT ].dTag != 0 ) && ( p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_HASH ].dTag != 0 ) )
      {
         /* Réalisation des relocalisations sans addend */
         l_result = mk_loader_elf_relocate ( p_elf32Parser, p_list, K_MK_LOADER_ELF32_DT_REL );
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
      l_result = K_MK_ERROR_CORRUPTED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_readFileHeader ( T_mkFile* p_file, T_mkELF32FileHeader* p_elf32FileHeader )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de traval */
   uint32_t l_numberOfBytesRead = 0;

   /* Lecture de l'entête du fichier */
   l_result = mk_file_read ( p_file, p_elf32FileHeader, K_MK_LOADER_ELF32_FILEHEADER_SIZE, &l_numberOfBytesRead, K_MK_NULL );

   /* Si une erreur s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesRead != K_MK_LOADER_ELF32_FILEHEADER_SIZE ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_UNEXPECTED;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Vérification de la validité de l'entête du fichier elf */
   if ( ( l_result == K_MK_OK ) && (
      ( ( p_elf32FileHeader->eType != K_MK_LOADER_ELF32_ET_EXEC ) && ( p_elf32FileHeader->eType != K_MK_LOADER_ELF32_ET_DYN ) ) ||
        ( p_elf32FileHeader->eIdentMagicNumber != K_MK_LOADER_ELF32_MAGICNUMBER ) || ( p_elf32FileHeader->eIdentClass != K_MK_LOADER_ELF32_32BITS ) ||
        ( p_elf32FileHeader->eIdentData != K_MK_LOADER_ELF32_LITTLE_ENDIAN ) || ( p_elf32FileHeader->eIdentVersion != 1 ) || ( p_elf32FileHeader->eVersion != 1 ) ||
        ( p_elf32FileHeader->eIdentOSABI != K_MK_LOADER_ELF32_SYSTEM_V ) || ( p_elf32FileHeader->eMachine != K_MK_LOADER_ELF32_AARCH32 ) ||
        ( p_elf32FileHeader->eEhSize != K_MK_LOADER_ELF32_FILEHEADER_SIZE ) || ( p_elf32FileHeader->ePhentSize != K_MK_LOADER_ELF32_PROGRAMHEADER_ENTRY_SIZE ) ||
        ( p_elf32FileHeader->eShentSize != K_MK_LOADER_ELF32_SECTIONHEADER_ENTRY_SIZE )
        ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_NOT_SUPPORTED;
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

T_mkCode mk_loader_elf_loadRAM ( T_mkFile* p_file, T_str8 p_path, T_mkAddr p_baseAddr, T_mkExternalLibrariesList* p_list, T_mkAddr* p_startAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un parser */
   T_mkELF32FileParser l_elf32Parser;

   /* Si les paramètres sont valides (les adresses peuvent être nulle) */
   if ( ( p_file != K_MK_NULL ) && ( p_path != K_MK_NULL ) && ( p_list != K_MK_NULL ) )
   {
      /* Réinitialisation du parser */
      _writeWords ( &l_elf32Parser, 0, sizeof ( T_mkELF32FileParser ) >> 2 );

      /* Configuration des caractéristiques de l'application */
      l_elf32Parser.volume = p_file->volume;
      l_elf32Parser.path = p_path;
      l_elf32Parser.baseAddr = p_baseAddr;

      /* Configuration du pointeur de fichier au début de celui-ci */
      l_result = mk_file_seek ( p_file, 0, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Lecture de l'entête du fichier ELF */
         l_result = mk_loader_elf_readFileHeader ( p_file, &l_elf32Parser.fileHeader );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si l'adresse de démarrage du programme doit être récupéré */
            if ( p_startAddr != K_MK_NULL )
            {
               /* Enregistrement de l'adresse de démarrage dans le paramètre de sortie */
               *p_startAddr = ( T_mkAddr ) ( ( uint8_t* ) p_baseAddr + ( uint32_t ) l_elf32Parser.fileHeader.eEntry );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Chargement du programme en mémoire */
            l_result = mk_loader_elf_loadMemorySegments ( p_file, &l_elf32Parser );

            /* Si le fichier est de type ET_DYN alors des résolutions doivent être faites suite au chargement des */
            /* segments dans la mémoire. */
            /* Si le fichier est de type ET_EXEC, aucune résolution n'est nécessaire. */
            if ( ( l_result == K_MK_OK ) && ( l_elf32Parser.fileHeader.eType == K_MK_LOADER_ELF32_ET_DYN ) )
            {
               /* Sources : https://www3.physnet.uni-hamburg.de/physnet/Tru64-Unix/HTML/APS31DTE/DOCU_002.HTM#msym_section */
               /* Les données des segments ci-dessous sont placées dans des segments chargeables (PT_LOAD) par l'éditeur de lien statique */
               /* .dynamic : contient la 'DynamicTable'. */
               /* .got : contient la 'Global Offset Table'. */
               /* .dynsym : contient la 'Dynamic Symbol Table'. */
               /* .rel.dyn : contient la 'Dynamic Relocation Table'. */
               /* .hash : contient la 'Hash Table'. */
               /* .dynstr : contient la 'Dynamic String Table'. */

               /* Récupération des informations contenues dans la table dynamique */
               mk_loader_elf_parseDynamicTable ( &l_elf32Parser, p_list );

               /* Résolution et relocalisation des symboles */
               l_result = mk_loader_elf_relocateSymbols ( &l_elf32Parser, p_list );
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
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}






