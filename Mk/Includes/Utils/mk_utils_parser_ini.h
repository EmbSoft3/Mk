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
* @file mk_utils_parser_ini.h
* @brief Déclaration des fonctions publiques dédiées au parser des fichiers ".ini".
* @date 8 janv. 2023
*
*/

#ifndef MK_UTILS_PARSER_INI_H
#define MK_UTILS_PARSER_INI_H

/**
 * @fn T_mkCode mk_utils_ini_open ( T_mkVolume* p_volume, T_mkFile** p_file, T_str8 p_filePath, T_mkCallback* p_callback );
 * @brief Cette fonction ouvre un fichier d'initialisation '.ini'.
 *
 * @param[in]     p_volume   Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume. Il peut prendre la valeur \ref K_MK_NULL.
 * @param[in,out] p_file     Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_filePath Ce paramètre contient l'adresse de la chaine de caractères stockant le chemin et le nom du fichier. La chaine
 *                           de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *                           \n Lorsque le paramètre p_volume est non nul, l'accès est réalisé sur la partition définie par p_volume.
 *                           \n Lorsque le paramètre p_volume est nul, la partition à accéder doit être spécifiée de la manière suivante :
 *                           \n /dsk[n]/vol[k]/path/fileName.ini avec n compris entre [0 et K_MK_DISK_MAX_NUMBER] et k compris entre [0 et K_MK_VOLUME_MAX_NUMBER].
 *                           \n Par exemple la chaine "/dsk0/vol1/fileName.ini" ouvre le fichier "fileName.ini" du disque 0, partition 1.
 *                           La chaine "/disk3/vol0/path/fileName.ini" ouvre le fichier "path/fileName.ini" du disque 3, partition 0.
 *                           \n Les champs /dsk[n]/vol[k]/ peuvent être omis si l'accès est réalisé sur le disque système. Par exemple la chaine "path/sys.ini"
 *                           ouvre le fichier sys.ini présent dans le répertoire "path" de la partition système.
 * @param[in]     p_callback Ce paramètre contient l'adresse d'une fonction de rappel de type \ref T_mkCallback ou la valeur \ref K_MK_NULL si la fonction doit être
 *                           exécutée de manière synchrone.\n
 *                           Le prototype de la fonction de rappel est le suivant : void f_callback ( T_mkCode p_err, T_mkFile* p_file );
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
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été ouvert car le fichier est corrompu (la table des clusters FAT).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été ouvert car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_COLLISION     : le fichier n'a pas été ouvert car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : le fichier n'a pas été ouvert car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été ouvert car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @note Un fichier ouvert doit être fermé avec la fonction \ref mk_utils_ini_close.
 *
 */

T_mkCode mk_utils_ini_open ( T_mkVolume* p_volume, T_mkFile** p_file, T_str8 p_filePath, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_utils_ini_close ( T_mkFile* p_file, T_mkCallback* p_callback );
 * @brief Cette fonction ferme un fichier d'initialisation '.ini'.
 *
 * @param[in,out] p_file     Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_callback Ce paramètre contient l'adresse d'une fonction de rappel de type \ref T_mkCallback ou la valeur \ref K_MK_NULL si la fonction doit être
 *                           exécutée de manière synchrone.\n
 *                           Le prototype de la fonction de rappel est le suivant : void f_callback ( T_mkCode p_err );
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le fichier a été fermé.
 *         \li \ref K_MK_ERROR_PARAM      : le fichier n'a pas été fermé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR        : le fichier n'a pas été fermé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT    : le fichier n'a pas été fermé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM       : le fichier n'a pas été fermé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le fichier n'a pas été fermé car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_RIGHT      : le fichier n'a pas été fermé car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_utils_ini_close ( T_mkFile* p_file, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_utils_ini_getValue ( T_mkFile* p_file, T_str8 p_section, T_str8 p_property, T_str8 p_value, uint32_t p_valueLength );
 * @brief Cette fonction retourne la valeur d'une propriété d'un fichier d'initialisation '.ini'.
 *
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_section     Ce paramètre contient le nom de la section délimité par une paire de crochet ([sectionName]). Ce paramètre peut être vide ("").
 * @param[in]     p_property    Ce paramètre contient le nom de la propriété.
 * @param[out]    p_value       Ce paramètre contient l'adresse du buffer stockant la valeur de la propriété. Un octet supplémentaire doit être fourni pour le
 *                              caractère de fin de chaine.
 * @param[out]    p_valueLength Ce paramètre contient la taille du buffer stockant la valeur de la propriété (caractère de fin de chaine compris).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la valeur de la propriété a été récupérée.
 *         \li \ref K_MK_ERROR_PARAM     : la valeur de la propriété n'a pas été récupérée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la valeur de la propriété n'a pas été récupérée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la valeur de la propriété n'a pas été récupérée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la valeur de la propriété n'a pas été récupérée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la valeur de la propriété n'a pas été récupérée car le fichier est corrompu (la table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED    : la valeur de la propriété n'a pas été récupérée car il n'a pas été ouvert avec les droits en lecture.
 *         \li \ref K_MK_ERROR_RIGHT     : la valeur de la propriété n'a pas été récupérée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_NOT_FOUND : la valeur de la propriété n'a pas été récupérée car la propriété n'a pas été trouvée dans le fichier d'initialisation.
 *
 * @warning L'encodage du fichier doit être de type ASCII.
 *
 */

T_mkCode mk_utils_ini_getValue ( T_mkFile* p_file, T_str8 p_section, T_str8 p_property, T_str8 p_value, uint32_t p_valueLength );

/**
 *
 */

#endif

