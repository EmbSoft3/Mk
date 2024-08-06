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
* @file mk_loader_elf_constants.h
* @brief Déclaration des constantes dédiées aux chargements des fichiers de programmation ELF32.
* @date 21 déc. 2023
*
*/

#ifndef MK_LOADER_ELF_CONSTANTS_H
#define MK_LOADER_ELF_CONSTANTS_H

/**
 * @def K_MK_LOADER_ELF32_FILEHEADER_SIZE
 * @brief Définition de la taille de l'entête d'un fichier ELF 32 bits [en octets].
 */

#define K_MK_LOADER_ELF32_FILEHEADER_SIZE 52

/**
 * @def K_MK_LOADER_ELF32_FILEHEADER_SIZE
 * @brief Définition de la taille d'une entrée de la Program Header Table [en octets].
 */

#define K_MK_LOADER_ELF32_PROGRAMHEADER_ENTRY_SIZE 32

/**
 * @def K_MK_LOADER_ELF32_SECTIONHEADER_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée de la Section Header Table [en octets].
 */

#define K_MK_LOADER_ELF32_SECTIONHEADER_ENTRY_SIZE 40

/**
 * @def K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée de la Dynamic Table [en octets].
 */

#define K_MK_LOADER_ELF32_DYNAMICTABLE_ENTRY_SIZE 8

/**
 * @def K_MK_LOADER_ELF32_SYMBOLTABLE_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée de la Symbole Table [en octets].
 */

#define K_MK_LOADER_ELF32_SYMBOLTABLE_ENTRY_SIZE 16

/**
 * @def K_MK_LOADER_ELF32_RELOCATION_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée de relocalisation [en octets].
 */

#define K_MK_LOADER_ELF32_RELOCATION_ENTRY_SIZE 8

/**
 *
 */

/**
 * @def K_MK_LOADER_ELF32_MAGICNUMBER
 * @brief Définition de l'identifiant d'un fichier ELF.
 */

#define K_MK_LOADER_ELF32_MAGICNUMBER 0x464C457F

/**
 * @def K_MK_LOADER_ELF32_32BITS
 * @brief Définition du format 32bits d'un fichier ELF.
 */

#define K_MK_LOADER_ELF32_32BITS 0x1

/**
 * @def K_MK_LOADER_ELF32_LITTLE_ENDIAN
 * @brief Définition du format Little Endian d'un fichier ELF.
 */

#define K_MK_LOADER_ELF32_LITTLE_ENDIAN 0x1

/**
 * @def K_MK_LOADER_ELF32_SYSTEM_V
 * @brief Définition de l'OS cible UNIX- SYSTEM V d'un fichier ELF.
 */

#define K_MK_LOADER_ELF32_SYSTEM_V 0x0

/**
 * @def K_MK_LOADER_ELF32_AARCH32
 * @brief Définition du set d'instruction ARM 32bits d'un fichier ELF.
 */

#define K_MK_LOADER_ELF32_AARCH32 0x28

/**
 *
 */

/**
 * @def K_MK_LOADER_ELF32_BLOOMFILTER_MASKWORDS_SIZE
 * @brief Définition de la taille des mots constituant le filtre de BLOOM [en bits].
 */

#define K_MK_LOADER_ELF32_BLOOMFILTER_MASKWORDS_SIZE 32

/**
 *
 */

#endif


