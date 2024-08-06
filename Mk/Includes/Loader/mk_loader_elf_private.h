/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_loader_elf_private.h
* @brief Déclaration des fonctions privées dédiées aux chargements des fichiers de programmation ELF32.
* @date 7 juil. 2024
*
*/

#ifndef MK_LOADER_ELF_PRIVATE
#define MK_LOADER_ELF_PRIVATE

/**
 * @fn T_mkAddr _mk_loader_elf_getInternalSymbolsBaseAddr ( void );
 * @brief Cette fonction retourne l'adresse mémoire où les symboles du système (K_MK_INTERNAL_SYMBOLS_BASE_ADDR) ont été chargés
 *        lors de la programmation de la cible.
 *
 * @return Cette fonction retourne la valeur du symbole K_MK_INTERNAL_SYMBOLS_BASE_ADDR).
 *
 */

T_mkAddr _mk_loader_elf_getInternalSymbolsBaseAddr ( void );

/**
 * @fn T_mkCode mk_loader_elf_relocate ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, uint32_t p_relIndex );
 * @brief Cette fonction relocalise les symboles d'un fichier de programmation .elf.
 *
 * @param[in]  p_elf32Parser Ce paramètre contient l'adresse d'un parser de fichier elf de type \ref T_mkELF32FileParser.
 * @param[out] p_list        Ce paramètre contient la liste de bibliothèques externes allouées pour résoudre et relocaliser les symboles du fichier de programmation.
 * @param[in]  p_relIndex    Ce paramètre contient l'index de la table de relocalisation.
 *                           Il peut prendre les valeurs \ref K_MK_LOADER_ELF32_DT_RELA ou \ref K_MK_LOADER_ELF32_DT_REL.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : la relocalisation des symboles a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : la relocalisation des symboles a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : la relocalisation des symboles a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC     : la relocalisation des symboles a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT    : la relocalisation des symboles a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : la relocalisation des symboles a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : la relocalisation des symboles a échoué car le fichier est corrompu.
 *         \li \ref K_MK_ERROR_UNRESOLVED : la relocalisation des symboles a échoué car un symbole n'a pas été résolu.
 *         \li \ref K_MK_ERROR_NOT_FOUND  : la relocalisation des symboles a échoué car une bibliothèque externe n'a pas été trouvée.
 *         \li \ref K_MK_ERROR_UNEXPECTED : la relocalisation des symboles a échoué car les symboles internes sont corrompus.
 *         \li \ref K_MK_ERROR_RIGHT      : la relocalisation des symboles a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @warning Cette fonction est récursive. Elle est exécutée afin de charger chaque bibliothèque externe nécessaire à la résolution des symboles du programme.
 *
 */

T_mkCode mk_loader_elf_relocate ( T_mkELF32FileParser* p_elf32Parser, T_mkExternalLibrariesList* p_list, uint32_t p_relIndex );

/**
 * @fn T_mkCode mk_loader_elf_resolveExternalSymbols ( T_mkELF32FileParser* p_parser, T_mkExternalLibrariesList* p_list, T_str8 p_symbolName, uint32_t* p_symbolAddr );
 * @brief Cette fonction détermine l'adresse du symbole présent en paramètre.
 *
 * @param[in]  p_parser      Ce paramètre contient l'adresse d'un parser de fichier elf de type \ref T_mkELF32FileParser.
 * @param[out] p_list        Ce paramètre contient la liste de bibliothèques externes allouées pour résoudre le symbole.
 * @param[in]  p_symbolName  Ce paramètre contient l'adresse de la chain de caractères contenant la dénominition du symbole. La chaine doit se terminée par le
 *                           caractère de fin de chaine ('\0').
 * @param[out] p_symbolAddr  Ce paramètre contient l'adresse du symbole.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : la résolution du symbole a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : la résolution du symbole a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : la résolution du symbole a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC     : la résolution du symbole a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT    : la résolution du symbole a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : la résolution du symbole a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNRESOLVED : la résolution du symbole a échoué car le symbole n'a pas été trouvé.
 *         \li \ref K_MK_ERROR_NOT_FOUND  : la résolution du symbole a échoué car une bibliothèque externe n'a pas été trouvée.
 *         \li \ref K_MK_ERROR_UNEXPECTED : la résolution du symbole a échoué car les symboles internes sont corrompus.
 *         \li \ref K_MK_ERROR_RIGHT      : la résolution du symbole a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @warning Cette fonction est récursive. Elle est exécutée afin de charger chaque bibliothèque externe nécessaire à la résolution du symbole.
 *
 */

T_mkCode mk_loader_elf_resolveExternalSymbols ( T_mkELF32FileParser* p_parser, T_mkExternalLibrariesList* p_list, T_str8 p_symbolName, uint32_t* p_symbolAddr );

/**
 *
 */

#endif
