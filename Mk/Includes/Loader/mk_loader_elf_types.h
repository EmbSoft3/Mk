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
* @file mk_loader_elf_types.h
* @brief Déclaration des types dédiés aux chargements des fichiers de programmation ELF32.
* @date 21 déc. 2023
*
*/

#ifndef MK_LOADER_ELF_TYPES_H
#define MK_LOADER_ELF_TYPES_H

/**
 * @enum T_mkELF32FileType
 * @brief Déclaration de l'énumération T_mkELF32FileType.
 *
 */

typedef enum T_mkELF32FileType
{
   K_MK_LOADER_ELF32_ET_NONE = 0,         /*!< Définition du type ET_NONE d'un fichier ELF32. */
   K_MK_LOADER_ELF32_ET_REL = 1,          /*!< Définition du type ET_REL d'un fichier ELF32. */
   K_MK_LOADER_ELF32_ET_EXEC = 2,         /*!< Définition du type ET_EXEC d'un fichier ELF32. */
   K_MK_LOADER_ELF32_ET_DYN = 3,          /*!< Définition du type ET_DYN d'un fichier ELF32. */
   K_MK_LOADER_ELF32_ET_CORE = 4          /*!< Définition du type ET_CORE d'un fichier ELF32. */
} T_mkELF32FileType;


/**
 * @struct T_mkELF32FileHeader
 * @brief Déclaration de la structure T_mkELF32FileHeader.
 *
 */

typedef struct T_mkELF32FileHeader T_mkELF32FileHeader;
struct T_mkELF32FileHeader
{
   uint32_t  eIdentMagicNumber;           /*!< Magic Number :  0x7F, 0x45, 0x4C, 0x46). */
   uint8_t   eIdentClass;                 /*!< Format du fichier : 32bits <1> ou 64 bits <2>. */
   uint8_t   eIdentData;                  /*!< Endianness : little <1>, big <2>. */
   uint8_t   eIdentVersion;               /*!< Version. */
   uint8_t   eIdentOSABI;                 /*!< OS Cible. */
   uint8_t   eIdentABIVersion;            /*!< Version de l'ABI. */
   uint8_t   eIdentPadding [7];           /*!< Padding. */
   uint16_t  eType;                       /*!< Type : No_File_Type <0>, Relocatable_File <1>, Execution_File <2>, Shared_Object_File <3>, Core_File <4>, Processor-specific <0xFF00 ou 0xFFFF>. */
   uint16_t  eMachine;                    /*!< Instruction Set : ARM <0x28>. */
   uint32_t  eVersion;                    /*!< Version : Invalide <0>, Valide <1>. */
   uint32_t* eEntry;                      /*!< Adresse de démarrage du programme. */
   uint32_t  ePhoff;                      /*!< Offset de la 'Programm header table'. */
   uint32_t  eShoff;                      /*!< Offset de la 'Section header table'. */
   uint32_t  eFlags;                      /*!< Flags : fonction de l'architecture. */
   uint16_t  eEhSize;                     /*!< Taille de cette entête (52 bytes for 32bits). */
   uint16_t  ePhentSize;                  /*!< Taille d'une entrée de la 'Programm header table'. */
   uint16_t  ePhnum;                      /*!< Nombre d'entrées dans la 'Programm header table'. */
   uint16_t  eShentSize;                  /*!< Taille d'une entrée de la 'Section header table'. */
   uint16_t  eShnum;                      /*!< Nombre d'entrées dans la 'Section header table'. */
   uint16_t  eShStrndx;                   /*!< Index de l'entrée de la 'Section header table' qui contient le nom des sections. */
};

/**
 *
 */

/**
 * @enum T_mkELF32SpecialSectionIndex
 * @brief Déclaration de l'énumération T_mkELF32SpecialSectionIndex.
 *
 */

typedef enum T_mkELF32SpecialSectionIndex
{
   K_MK_LOADER_ELF32_SHN_UNDEF = 0,       /*!< Identifiant d'une section stockant des symboles non définies */
   K_MK_LOADER_ELF32_SHN_ABS = 0xFFF1,    /*!< Identifiant d'une section stockant des symboles de types 'Abs'. */
   K_MK_LOADER_ELF32_SHDN_COMMON = 0xFFF2 /*!< Identifiant d'une section stockant des symboles de types 'Common'. */
} T_mkELF32SpecialSectionIndex;

/**
 * @struct T_mkELF32SectionHeaderEntry
 * @brief Déclaration de la structure T_mkELF32SectionHeaderEntry.
 * @note Il y a un descripteur de section (\ref T_mkELF32SectionHeaderEntry ) pour chaque section qui est présente dans le fichier. Attention,
 *       il peut exister des descripteurs de sections qui ne possèdent pas de section associée.
 *
 */

typedef struct T_mkELF32SectionHeaderEntry T_mkELF32SectionHeaderEntry;
struct T_mkELF32SectionHeaderEntry
{
   uint32_t  sName;                       /*!< Offset vers la chaine de caractères contenant le nom de la section. */
   uint32_t  sType;                       /*!< Type de l'entrée (PROGRAM_DATA <1>, SYMBOL_TABLE <2>, .... */
   uint32_t  sFlags;                      /*!< Attributs de la section (Writable <1>, Alloc <2>, ExecInstr <4> ...). */
   uint32_t* sAddr;                       /*!< Adresse de la section si celle-ci est chargée sinon 0. */
   uint32_t  sOffset;                     /*!< Offset de la section dans le fichier. */
   uint32_t  sSize;                       /*!< Taille de la section dans le fichier [en octets]. Peut être 0. */
   uint32_t  sLink;                       /*!< Index d'une section associée. La signification dépend du type de section. */
   uint32_t  sInfo;                       /*!< Information complémentaire liée à la section. La signification dépend du type de section. */
   uint32_t  sAddrAlign;                  /*!< Alignement de la section en mémoire : No_alignement <0> ou <1>, sinon 2^p_Align. */
   uint32_t  sEntrySize;                  /*!< Taille des entrées d'une table de taille fixe (table des symboles par exemple) en octets. Valeur 0 si non applicable. */
};

/**
 * @enum T_mkELF32SymbolBinding
 * @brief Déclaration de l'énumération T_mkELF32SymbolBinding.
 *
 */

typedef enum T_mkELF32SymbolBinding
{
   K_MK_LOADER_ELF32_STB_LOCAL = 0,       /*!< Identifiant d'un symbole avec résolution de type 'local'. */
   K_MK_LOADER_ELF32_STB_GLOBAL = 1,      /*!< Identifiant d'un symbole avec résolution de type 'global'. */
   K_MK_LOADER_ELF32_STB_WEAK = 2         /*!< Identifiant d'un symbole avec résolution de type 'weak'. */
} T_mkELF32SymbolBinding;

/**
 * @enum T_mkELF32SymbolType
 * @brief Déclaration de l'énumération T_mkELF32SymbolType.
 *
 */

typedef enum T_mkELF32SymbolType
{
   K_MK_LOADER_ELF32_STT_NOTYPE = 0,      /*!< Identifiant d'un symbole de type 'NoType'. */
   K_MK_LOADER_ELF32_STT_OBJECT = 1,      /*!< Identifiant d'un symbole de type 'Object'. */
   K_MK_LOADER_ELF32_STT_FUNC = 2,        /*!< Identifiant d'un symbole de type 'Func'. */
   K_MK_LOADER_ELF32_STT_SECTION = 3,     /*!< Identifiant d'un symbole de type 'Section'. */
   K_MK_LOADER_ELF32_STT_FILE = 4         /*!< Identifiant d'un symbole de type 'File'. */
} T_mkELF32SymbolType;

/**
 * @struct T_mkELF32SymbolTableEntry
 * @brief Déclaration de la structure T_mkELF32SymbolTableEntry.
 * @note Structure pointée par une section de type SHT_SYMTAB ou SHT_DYNSYM.
 *
 */

typedef struct T_mkELF32SymbolTableEntry T_mkELF32SymbolTableEntry;
struct T_mkELF32SymbolTableEntry
{
   uint32_t  stName;                      /*!< Offset vers la chaine de caractères contenant le nom du symbole. */
   uint32_t* stValue;                     /*!< Valeur du symbole (valeur, adresse, ...) . */
   uint32_t  stSize;                      /*!< Taille du symbole [en octets]. Peut être 0. */
   uint8_t   stInfo;                      /*!< Type <3:0> (OBJECT, FUNC, SECTION, FILE, ...) et attributs de 'Binding' <7:4> du symbole (STB_LOCAL, STB_GLOBAL, STB_WEAK, ...). */
   uint8_t   stOther;                     /*!< Non implémenté (valeur 0). */
   uint16_t  stShndx;                     /*!< Index de l'entrée de la 'Section Header Table' auquel appartient le symbole. */
};

/**
 *
 */

/**
 * @enum T_mkELF32RelocationType
 * @brief Déclaration de l'énumération T_mkELF32RelocationType.
 * @note Définition des codes dédié au 'Dynamic Linker' :
 *       \li S    : adresse du symbole S (présent dans l'entrée de relocation).
 *       \li A    : addend de la relocation
 *       \li P    : adresse du lieu où la relocalisation doit avoir lieu (dérivé de r_offset).
 *       \li Pa   : adresse ajoutée P & 0xFFFFFFFC
 *       \li T    : valeur 1 si S est de type STT_FUNC et son symbole adresse une instruction Thumb. Sinon 0.
 *       \li B(S) : adresse du segment où est présent le symbole S. Doit être alignée sur 32bits.
 *
 * @note Code \ref K_MK_LOADER_ELF32_R_ARM_GLOB_DAT : \n
 *       Configuration d'une entrée de la GOT avec l'adresse du symbole à relocaliser.
 *
 * @note Code \ref K_MK_LOADER_ELF32_R_ARM_JUMP_SLOT : \n
 *       Configuration d'une entrée de la PLT avec l'adresse du symbole à relocaliser.
 *
 * @note Code \ref K_MK_LOADER_ELF32_R_ARM_RELATIVE : \n
 *       Configuration de l'adresse d'un symbole S avec la différence entre l'adresse où le segment définisant S a été chargé et l'adresse où le segment a été linké.
 *
 * @note Code \ref K_MK_LOADER_ELF32_R_ARM_COPY : \n
 *       Il est dédié au fichier ELF de type 'ET_EXEC'. Il indique au 'Dynamic Linker' de chercher le symbole dans une 'Shared Library' puis de copier le nombre
 *       d'octets spécifiés par st_size à l'adresse pointée par le symbole.
 *
 */

typedef enum T_mkELF32RelocationType
{
   K_MK_LOADER_ELF32_R_ARM_ABS32 = 2,       /*!< Résoudre l'adresse du symbole spécifié. Opération : (S + A) | T. */
   K_MK_LOADER_ELF32_R_ARM_COPY = 20,       /*!< Voir note */
   K_MK_LOADER_ELF32_R_ARM_GLOB_DAT = 21,   /*!< Résoudre l'adresse du symbole spécifié. Opération : (S + A) | T. */
   K_MK_LOADER_ELF32_R_ARM_JUMP_SLOT = 22,  /*!< Résoudre l'adresse du symbole spécifié. Opération : (S + A) | T. */
   K_MK_LOADER_ELF32_R_ARM_RELATIVE = 23    /*!< Voir note. Opération : B(S) + A. */
} T_mkELF32RelocationType;

/**
 * @struct T_mkELF32RelEntry
 * @brief Déclaration de la structure T_mkELF32RelEntry.
 * @note Structure pointée par une section de type SHT_REL.
 *
 */

typedef struct T_mkELF32RelEntry T_mkELF32RelEntry;
struct T_mkELF32RelEntry
{
   uint32_t* rOffset;                        /*!< Offset ('Relocatable file') ou adresse virtuelle ('Executable File' et 'Shared Object') où doit être appliquée l'opération de relocalisation. L'offset [en octets] est calculé depuis le début de la section. */
   uint32_t  rInfo;                          /*!< Type <7:0> de la relocalisation et index dans la "Symbol Table" <31:8> contenant le paramètre de l'opération (par exemple, le symbole de la fonction appelée dans une opération de type CALL).  */
};

/**
 * @struct T_mkELF32RelAEntry
 * @brief Déclaration de la structure T_mkELF32RelAEntry.
 * @note Structure pointée par une section de type SHT_RELA.
 *
 */

typedef struct T_mkELF32RelAEntry T_mkELF32RelAEntry;
struct T_mkELF32RelAEntry
{
   uint32_t* rOffset;                        /*!< Offset ('Relocatable file') ou adresse virtuelle ('Executable File' et 'Shared Object') où doit être appliquer l'opération de relocalisation. L'offset [en octets] est calculé depuis le début de la section. */
   uint32_t  rInfo;                          /*!< Type <7:0> de la relocalisation et index dans la "Symbol Table" <31:8> contenant le paramètre de l'opération (par exemple, le symbole de la fonction appelée dans une opération de type CALL).  */
   int32_t  rAddend;                         /*!< Valeur constante utilisée pour calculer la valeur de la relocalisation. */
};

/**
 *
 */

/**
 * @enum T_mkELF32DynamicTableTag
 * @brief Déclaration de l'énumération T_mkELF32DynamicTableTag.
 *
 */

typedef enum T_mkELF32DynamicTableTag
{
   K_MK_LOADER_ELF32_DT_NULL = 0,            /*!< Définition du tag DT_NULL d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_NEEDED = 1,          /*!< Définition du tag DT_NEEDED d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_PLTRELSZ = 2,        /*!< Définition du tag DT_PLTRELSZ d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_PLTGOT = 3,          /*!< Définition du tag DT_PLTGOT d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_HASH = 4,            /*!< Définition du tag DT_HASH d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_STRTAB = 5,          /*!< Définition du tag DT_STRTAB d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_SYMTAB = 6,          /*!< Définition du tag DT_SYMTAB d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RELA = 7,            /*!< Définition du tag DT_RELA d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RELASZ = 8,          /*!< Définition du tag DT_RELASZ d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RELAENT = 9,         /*!< Définition du tag DT_RELAENT d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_STRSZ = 10,          /*!< Définition du tag DT_STRSZ d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_SYMENT = 11,         /*!< Définition du tag DT_SYMENT d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_INIT = 12,           /*!< Définition du tag DT_INIT d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_FINI = 13,           /*!< Définition du tag DT_FINI d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_SONAME = 14,         /*!< Définition du tag DT_SONAME d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RPATH = 15,          /*!< Définition du tag DT_RPATH d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_SYMBOLIC = 16,       /*!< Définition du tag DT_SYMBOLIC d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_REL = 17,            /*!< Définition du tag DT_REL d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RELSZ = 18,          /*!< Définition du tag DT_RELSZ d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_RELENT = 19,         /*!< Définition du tag DT_RELENT d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_PLTREL = 20,         /*!< Définition du tag DT_PLTREL d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_DEBUG = 21,          /*!< Définition du tag DT_DEBUG d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_TESTREL = 22,        /*!< Définition du tag DT_TESTREL d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_JMPREL = 23,         /*!< Définition du tag DT_JMPREL d'une entrée la 'Dynamic Table'. */
   K_MK_LOADER_ELF32_DT_BIND_NOW = 24        /*!< Définition du tag DT_BIND_NOW d'une entrée la 'Dynamic Table'. */
} T_mkELF32DynamicTableTag;

/**
 * @union T_mkELF32DynamicTableEntryField
 * @brief Déclaration de la structure T_mkELF32DynamicTableEntry.
 *
 */

typedef union T_mkELF32DynamicTableEntryField T_mkELF32DynamicTableEntryField;
union T_mkELF32DynamicTableEntryField
{
   uint32_t  dVal;                           /*!< Valeur entière de l'entrée. */
   uint32_t* dAddr;                          /*!< Adresse virtuelle du programme. */
};

/**
 * @struct T_mkELF32DynamicTableEntry
 * @brief Déclaration de la structure T_mkELF32DynamicTableEntry.
 *
 */

typedef struct T_mkELF32DynamicTableEntry T_mkELF32DynamicTableEntry;
struct T_mkELF32DynamicTableEntry
{
   uint32_t dTag;                            /*!< Tag de l'entrée de la table dynamique : DT_NULL <0>, DT_NEED <1>, ... */
   T_mkELF32DynamicTableEntryField dField;   /*!< Contenu de l'entrée de table dynamique. */
};

/**
 * @struct T_mkELF32DynamicTable
 * @brief Déclaration de la structure T_mkELF32DynamicTable.
 *
 */

typedef struct T_mkELF32DynamicTable T_mkELF32DynamicTable;
struct T_mkELF32DynamicTable
{
   T_mkELF32DynamicTableEntry entry [ K_MK_LOADER_ELF32_DT_BIND_NOW + 1 ];    /*!< Ce membre contient l'adresse de la table de relocalisation (type \ref T_mkELF32RelEntry). */
};

/**
 *
 */

/**
 * @enum T_mkELF32SegmentType
 * @brief Déclaration de l'énumération T_mkELF32SegmentType.
 *
 */

typedef enum T_mkELF32SegmentType
{
   K_MK_LOADER_ELF32_PT_NULL = 0,            /*!< Définition du type PT_NULL d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_LOAD = 1,            /*!< Définition du type PT_LOAD d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_DYNAMIC = 2,         /*!< Définition du type PT_DYNAMIC d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_INTERP = 3,          /*!< Définition du type PT_INTERP d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_NOTE = 4,            /*!< Définition du type PT_NOTE d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_SHLIB = 5,           /*!< Définition du type PT_SHLIB d'un segment de la 'Program Header Table'. */
   K_MK_LOADER_ELF32_PT_PHDR = 6             /*!< Définition du type PT_PHDR d'un segment de la 'Program Header Table'. */
} T_mkELF32SegmentType;

/**
 * @struct T_mkELF32ProgramHeaderEntry
 * @brief Déclaration de la structure T_mkELF32ProgramHeaderEntry.
 * @note La table 'Program Header' est consituée de plusieurs entrées. Elles indiquent au système
 *       comment créer l'image à télécharger à partir de segments. Chaque entrée décrit les caractéristiques d'un segment.
 *       Cette table n'a de signification que pour les types de fichiers 'Executable File' et "Shared Object File'.
 *
 */

typedef struct T_mkELF32ProgramHeaderEntry T_mkELF32ProgramHeaderEntry;
struct T_mkELF32ProgramHeaderEntry
{
   uint32_t  pType;                          /*!< Type de l'entrée : PT_NULL <0>, PT_LOAD <1>, PT_DYNAMIC <2>, PT_PHDR <6>, ... */
   uint32_t  pOffset;                        /*!< Offset du segment de données dans le fichier. */
   uint32_t* pVirtualAddr;                   /*!< Adresse virtuelle du segment. */
   uint32_t* pPhysicalAddr;                  /*!< Adresse physique du segment. */
   uint32_t  pFileSize;                      /*!< Taille du segment dans le fichier [en octets]. Peut être 0. */
   uint32_t  pMemSize;                       /*!< Taille du segment dans la mémoire [en octets]. Peut être 0. */
   uint32_t  pFlags;                         /*!< Attributs du segment : Executable <1>, Writeable <2>, Readeable <4>. */
   uint32_t  pAlign;                         /*!< Alignement du segment en mémoire : No_alignement <0> ou <1>, sinon 2^p_Align. */
};

/**
 *
 */

/**
 * @struct T_mkELF32GNUHashTable
 * @brief Déclaration de la structure T_mkELF32GNUHashTable.
 *
 */

typedef struct T_mkELF32GNUHashTable T_mkELF32GNUHashTable;
struct T_mkELF32GNUHashTable
{
    uint32_t  nbuckets;                      /*!< Ce membre contient le nombre de bucket de la table de hashage. */
    uint32_t  symoffset;                     /*!< Ce membre contient l'offset des symboles de la table de hashage. */
    uint32_t  bloomSize;                     /*!< Ce membre contient la taille du filtre de bloom (en multiple de mots 32bits) . */
    uint32_t  bloomShift;                    /*!< Ce membre contient la valeur de décalage utilisée pour calculer le filtre de bloom. */
    uint32_t* bloom;                         /*!< Ce membre contient un pointeur sur le premier éléments du filtre de bloom. */
    uint32_t* buckets;                       /*!< Ce membre contient un pointeur sur la première bucket de la table de hashage. */
    uint32_t* hashValues;                    /*!< Ce membre contient un pointeur sur la premiere valeur de la table de hashage. */
};

/**
 *
 */

/**
 * @struct T_mkELF32FileParser
 * @brief Déclaration de la structure T_mkELF32FileParser.
 *
 */

typedef struct T_mkELF32FileParser T_mkELF32FileParser;
struct T_mkELF32FileParser
{
   T_str8 path;                              /*!< Ce membre contient l'adresse d'une chaine de caractères stockant le chemin et le nom du fichier de programmation. */
   T_mkVolume* volume;                       /*!< Ce membre contient l'adresse de la partition où est stocké le fichier de programmation. Il peut prendre la valeur \ref K_MK_NULL. */
   T_mkAddr baseAddr;                        /*!< Ce membre contient l'adresse de base où l'application est déployée. */
   T_mkELF32FileHeader fileHeader;           /*!< Ce membre contient l'entête d'un fichier ELF32. */
   T_mkELF32ProgramHeaderEntry dynEntry;     /*!< Ce membre contient la valeur de l'entrée dynamique de la 'Program Header Table'. */
   T_mkELF32DynamicTable dynTable;           /*!< Ce membre contient les champs de la 'Dynamic Table' exploités par le parser. */
};

/**
 *
 */

#endif


