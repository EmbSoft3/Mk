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
* @file mk_loader_elf_relocate.c
* @brief Définition de la fonction mk_loader_elf_relocate.
* @date 10 janv. 2024
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_loader_elf_relocateRelative ( T_mkELF32RelAEntry* p_relEntry, T_mkAddr p_offsetAddr )
{
   /* Résolution puis relocalisation de l'adresse du symbole */
   uint32_t* l_relocationAddr = ( T_mkAddr ) ( ( uint8_t* ) p_relEntry->rOffset + ( uint32_t ) p_offsetAddr  );
   *l_relocationAddr = ( uint32_t ) ( ( int32_t ) ( ( uint8_t* ) *l_relocationAddr + ( uint32_t ) p_offsetAddr ) + ( int32_t ) p_relEntry->rAddend );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_loader_elf_relocateAbs32 ( T_mkELF32SymbolTableEntry* p_symbolEntry, T_mkELF32RelAEntry* p_relEntry, T_mkAddr p_offsetAddr )
{
   /* Résolution puis relocalisation de l'adresse du symbole */
   uint32_t* l_relocationAddr = ( T_mkAddr ) ( ( uint8_t* ) p_relEntry->rOffset + ( uint32_t ) p_offsetAddr  );
   *l_relocationAddr += ( uint32_t ) ( ( uint8_t* ) p_symbolEntry->stValue + ( uint32_t ) p_offsetAddr + p_relEntry->rAddend );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_loader_elf_relocateGlobal ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, T_mkELF32SymbolTableEntry* p_symbolEntry, T_mkELF32RelAEntry* p_relEntry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint8_t* l_strtab;
   uint32_t l_bindType = 0;

   /* Récupération de l'adresse de relocalisation */
   uint32_t* l_relocationAddr = ( T_mkAddr ) ( ( uint8_t* ) p_relEntry->rOffset + ( uint32_t ) p_elf32Parser->baseAddr  );

   /* Si le symbole peut être résolue sans ressource complémentaire */
   if ( p_symbolEntry->stShndx != K_MK_LOADER_ELF32_SHN_UNDEF )
   {
      /* Résolution puis relocalisation de l'adresse du symbole */
      *l_relocationAddr = ( uint32_t ) ( ( uint8_t* ) p_symbolEntry->stValue + ( uint32_t ) p_elf32Parser->baseAddr + p_relEntry->rAddend );
   }

   /* Sinon */
   else
   {
      /* Récupération de la valeur de l'attribut de binding */
      l_bindType = ( ( p_symbolEntry->stInfo >> 4 ) & 0xF );

      /* Si le symbole est de type GLOBAL ou WEAK */
      if ( ( l_bindType == K_MK_LOADER_ELF32_STB_GLOBAL ) || ( l_bindType == K_MK_LOADER_ELF32_STB_WEAK ) )
      {
         /* Détermination de l'adresse de la section .strname */
         l_strtab = ( uint8_t* ) p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_STRTAB ].dField.dAddr + ( uint32_t ) p_elf32Parser->baseAddr;

         /* Résolution de l'adresse du symbole en utilisant la table des symboles du système ou une bibliothèque externe. */
         l_result = mk_loader_elf_resolveExternalSymbols ( p_elf32Parser, p_list, ( T_str8 ) &l_strtab [ p_symbolEntry->stName ], l_relocationAddr );

         /* Relocalisation de l'adresse du symbole */
         *l_relocationAddr = ( uint32_t ) ( ( int32_t ) *l_relocationAddr + p_relEntry->rAddend );
      }

      /* Sinon */
      else
      {
         /* L'opération n'est pas supportée pas le système */
         l_result = K_MK_ERROR_UNRESOLVED;
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

static T_mkCode mk_loader_elf_relocateByType ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, T_mkELF32RelAEntry* p_relEntry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_relType, l_relSymbTableIndex;

   /* Déclaration d'un pointeur d'entrée */
   T_mkELF32SymbolTableEntry* l_symbolEntry = K_MK_NULL;

   /* Récupération du type de la résolution à effectuer et de l'index du symbole associé */
   l_relType = ( uint32_t ) ( p_relEntry->rInfo & 0xFF );
   l_relSymbTableIndex = ( uint32_t ) ( ( p_relEntry->rInfo >> 8 ) & 0xFFFFFF );

   /* Récupération des informations relatives au symbole */
   l_symbolEntry = ( T_mkAddr ) ( ( uint8_t* ) p_elf32Parser->dynTable.entry[ K_MK_LOADER_ELF32_DT_SYMTAB ].dField.dAddr +
         ( uint32_t ) p_elf32Parser->baseAddr + ( uint32_t ) ( l_relSymbTableIndex * K_MK_LOADER_ELF32_SYMBOLTABLE_ENTRY_SIZE ) );

   /* Si l'entrée est de type R_ARM_RELATIVE */
   if ( l_relType == K_MK_LOADER_ELF32_R_ARM_RELATIVE )
   {
      /* Relocalisation du symbole */
      mk_loader_elf_relocateRelative ( p_relEntry, p_elf32Parser->baseAddr );
   }

   /* Sinon si l'entrée est de type R_ARM_ABS32 */
   else if ( l_relType == K_MK_LOADER_ELF32_R_ARM_ABS32 )
   {
      /* Relocalisation du symbole */
      mk_loader_elf_relocateAbs32 ( l_symbolEntry, p_relEntry, p_elf32Parser->baseAddr );
   }

   /* Sinon si l'entrée est de type R_ARM_GLOB_DAT */
   else if ( l_relType == K_MK_LOADER_ELF32_R_ARM_GLOB_DAT )
   {
      /* Relocalisation du symbole */
      l_result = mk_loader_elf_relocateGlobal ( p_elf32Parser, p_list, l_symbolEntry, p_relEntry );
   }

   /* Sinon (K_MK_LOADER_ELF32_R_ARM_JUMP_SLOT, K_MK_LOADER_ELF32_R_ARM_COPY ou autres ...)  */
   else
   {
      /* L'opération K_MK_LOADER_ELF32_R_ARM_JUMP_SLOT n'est pas supportée par le système car celui-ci n'est pas équipé d'une MMU */
      /* avec un espace d'adressage virtuel. */

      /* L'opération n'est pas supportée pas le système. */
      l_result = K_MK_ERROR_UNRESOLVED;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_loader_elf_relocate ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, uint32_t p_relIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t  l_counter = 0, l_relTableSize = 0, l_entryNumber = 0, l_relTableEntrySize = 0;
   uint32_t* l_relTableAddr = K_MK_NULL;

   /* Déclaration d'une entrée de relocalisation */
   T_mkELF32RelAEntry l_relEntry;

   /* Si les paramètres sont valides (les adresses peuvent être nulle) */
   if ( ( p_elf32Parser != K_MK_NULL ) && ( p_elf32Parser->path != K_MK_NULL ) )
   {
      /* Récupération de l'adresse de la table de relocalisation */
      l_relTableAddr = p_elf32Parser->dynTable.entry[ p_relIndex ].dField.dAddr;

      /* Récupération de la taille de la table de relocalisation */
      l_relTableSize = p_elf32Parser->dynTable.entry[ p_relIndex + 1 ].dField.dVal;

      /* Récupération de la taille d'une entrée de la table de relocalisation */
      l_relTableEntrySize = p_elf32Parser->dynTable.entry[ p_relIndex + 2 ].dField.dVal;

      /* Détermination du nombre d'entrées dans la table de relocalisation */
      l_entryNumber = l_relTableSize / l_relTableEntrySize;

      /* Vérification de la validité des données récupérées */
      l_counter = _math_mod ( l_relTableSize, l_relTableEntrySize );

      /* Si les données sont valides */
      if ( l_counter == 0 )
      {
         /* Pour le nombre d'entrées dans la table de relocalisation */
         for ( l_counter = 0 ; ( l_counter < l_entryNumber ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Récupération du contenu d'une entrée */
            _copy ( &l_relEntry, ( T_mkAddr ) ( ( uint8_t* ) l_relTableAddr +
                  ( uint32_t ) p_elf32Parser->baseAddr + ( uint32_t ) ( l_counter * l_relTableEntrySize ) ), l_relTableEntrySize );

            /* Si l'entrée est de type DT_REL */
            if ( l_relTableEntrySize == K_MK_LOADER_ELF32_RELOCATION_ENTRY_SIZE )
            {
               /* L'entrée ne possède pas d'addend */
               l_relEntry.rAddend = 0;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Réalisation de la relocalisation du symbole */
            l_result = mk_loader_elf_relocateByType ( p_elf32Parser, p_list, &l_relEntry );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


