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
* @file mk_loader_elf.h
* @brief Déclaration des fonctions publiques aux chargements des fichiers de programmation ELF32.
* @date 21 déc. 2023
*
*/

#ifndef MK_LOADER_ELF_H
#define MK_LOADER_ELF_H

/**
 * @fn T_mkCode mk_loader_elf_open ( T_mkVolume* p_volume, T_mkFile** p_file, T_str8 p_filePath, T_mkCallback* p_callback );
 * @brief Cette fonction ouvre un fichier de programmation '.elf'.
 *
 * @param[in]     p_volume      Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume. Il peut prendre la valeur \ref K_MK_NULL.
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_filePath    Ce paramètre contient l'adresse d'une chaine de caractères stockant le chemin et le nom du fichier. La chaine
 *                              de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *                              \n Lorsque le paramètre p_volume est non nul, l'accès est réalisé sur la partition définie par p_volume.
 *                              \n Lorsque le paramètre p_volume est nul, la partition à accéder doit être spécifiée de la manière suivante :
 *                              \n /dsk[n]/vol[k]/path/fileName.elf avec n compris entre [0 et K_MK_DISK_MAX_NUMBER] et k compris entre [0 et K_MK_VOLUME_MAX_NUMBER].
 *                              \n Par exemple la chaine "/dsk0/vol1/fileName.elf" ouvre le fichier "fileName.elf" du disque 0, partition 1.
 *                              La chaine "/disk3/vol0/path/fileName.elf" ouvre le fichier "path/fileName.elf" du disque 3, partition 0.
 *                              \n Les champs /dsk[n]/vol[k]/ peuvent être omis si l'accès est réalisé sur le disque système. Par exemple la chaine "path/cmd.elf"
 *                              ouvre le fichier cmd.elf présent dans le répertoire "path" de la partition système.
 * @param[in]     p_callback    Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le fichier a été ouvert.
 *         \li \ref K_MK_ERROR_PARAM         : le fichier n'a pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : le fichier n'a pas été ouvert car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : le fichier n'a pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le fichier n'a pas été ouvert car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le fichier n'a pas été ouvert car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : le fichier n'a pas été ouvert car il existe déjà.
 *         \li \ref K_MK_ERROR_FULL          : le fichier n'a pas été ouvert car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été ouvert car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été ouvert car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_COLLISION     : le fichier n'a pas été ouvert car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : le fichier n'a pas été ouvert car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été ouvert car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_NOT_FOUND     : le fichier n'a pas été ouvert car il n'existe pas.
 *
 * @note Un fichier ouvert doit être fermé avec la fonction \ref mk_loader_srec_close.
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void f_callback ( T_mkCode p_err, T_mkFile* p_file );
 *
 */

T_mkCode mk_loader_elf_open ( T_mkVolume* p_volume, T_mkFile** p_file, T_str8 p_filePath, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_loader_elf_close ( T_mkFile* p_file, T_mkCallback* p_callback );
 * @brief Cette fonction ferme un fichier de programmation '.elf'.
 *
 * @param[in,out] p_file     Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_callback Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le fichier a été fermé.
 *         \li \ref K_MK_ERROR_PARAM      : le fichier n'a pas été fermé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le fichier n'a pas été fermé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le fichier n'a pas été fermé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le fichier n'a pas été fermé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le fichier n'a pas été fermé car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_RIGHT      : le fichier n'a pas été fermé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void f_callback ( T_mkCode p_err );
 *
 */

T_mkCode mk_loader_elf_close ( T_mkFile* p_file, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_loader_elf_loadRAM ( T_mkFile* p_file, T_str8 p_path, T_mkAddr p_baseAddr, T_mkExternalLibrariesList* p_list, T_mkAddr* p_startAddr );
 * @brief Cette fonction charge un fichier de programmation '.elf' dans la mémoire.
 *
 * @param[in]  p_file      Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]  p_path      Ce paramètre contient l'adresse d'une chaine de caractères stockant le chemin et le nom du fichier de programmation. La chaine
 *                         de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 * @param[in]  p_baseAddr  Ce paramètre contient l'adresse mémoire où le fichier de programmation doit être chargé.
 * @param[out] p_list      Ce paramètre contient la liste de bibliothèques externes permettant de résoudre les symboles du fichier de programmation.
 * @param[out] p_startAddr Ce paramètre contient l'adresse de la fonction de démarrage du programme chargé en mémoire. Il peut prendre la valeur \ref K_MK_NULL si
 *                         l'adresse de démarrage ne doit pas être récupérée. L'offset 'p_baseAddr' est ajoutée à la valeur lue dans le fichier de programmation.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le chargement du fichier de programmation a réussi.
 *         \li \ref K_MK_ERROR_PARAM      : le chargement du fichier de programmation a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le chargement du fichier de programmation a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC     : le chargement du fichier de programmation a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le chargement du fichier de programmation a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le chargement du fichier de programmation a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED  : le chargement du fichier de programmation a échoué car le fichier est corrompu.
 *         \li \ref K_MK_ERROR_RIGHT      : le chargement du fichier de programmation a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNRESOLVED : le chargement du fichier de programmation a échoué car la méthode de résolution n'est pas supportée.
 *
 * @warning Cette fonction est récursive. Elle est exécutée afin de charger chaque bibliothèque externe nécessaire à la résolution des symboles du programme.
 *
 */

T_mkCode mk_loader_elf_loadRAM ( T_mkFile* p_file, T_str8 p_path, T_mkAddr p_baseAddr, T_mkExternalLibrariesList* p_list, T_mkAddr* p_startAddr );

/**
 *
 */

#endif


