/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_fat_private.h
* @brief Définition des fonctions privées dédiées au système de fichiers FAT32.
* @date 28 déc. 2020
*
*/

#ifndef MK_FAT_PRIVATE_H
#define MK_FAT_PRIVATE_H

/**
 * @fn T_mkCode mk_fat_open ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, T_mkFileMode p_mode );
 * @brief Cette fonction ouvre un fichier présent sur une partition.
 *
 * @param[in]     p_volume      Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_filePath    Ce paramètre contient l'adresse d'une chaine de caractères UTF8 stockant le chemin et le nom du fichier. La chaine
 *                              de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *                              Lorsque la chaine prend la valeur "", l'instance du répertoire racine est renvoyée.
 * @param[in]     p_baseCluster Ce paramètre contient le cluster d'un répertoire.
 * @param[in]     p_mode        Ce paramètre contient le mode d'ouverture du fichier. Les constantes suivantes peuvent être utilisées :
 *                              \li \ref K_MK_FS_OPEN_EXISTING         : la fonction ouvre le fichier s'il existe, sinon elle retourne une erreur. Le pointeur de fichier est placé au début du fichier.
 *                              \li \ref K_MK_FS_OPEN_ALWAYS           : la fonction ouvre le fichier s'il existe, sinon elle le crée. Le pointeur de fichier est placé au début du fichier.
 *                              \li \ref K_MK_FS_OPEN_APPEND           : la fonction ouvre le fichier s'il existe, sinon elle le crée. Le pointeur de fichier est placé à la fin du fichier.
 *                              \li \ref K_MK_FS_OPEN_CREATE           : la fonction retourne une erreur si le fichier existe, sinon elle le crée.
 *                              \li \ref K_MK_FS_OPEN_CREATE_DIRECTORY : la fonction retourne une erreur si le répertoire existe, sinon elle le crée.
 *                              \li \ref K_MK_FS_OPEN_TRUNCATE         : la fonction tronque le fichier s'il existe, sinon elle le crée.\n
 *
 *                              Une combinaison des 3 flags suivants peut être utilisée pour spécifier les modes d'accès :
 *                              \li \ref K_MK_FS_OPEN_READ   : le fichier est ouvert avec l'accès en lecture.
 *                              \li \ref K_MK_FS_OPEN_WRITE  : le fichier est ouvert avec l'accès en écriture.
 *                              \li \ref K_MK_FS_OPEN_SHARED : le fichier est ouvert en mode partagé.
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
 *         \li \ref K_MK_ERROR_DENIED        : le fichier n'a pas été ouvert car un fichier en lecture seul ne peut pas être ouvert en écriture.
 *
 * @warning Un fichier ne peut pas être ouvert avec le flag \ref K_MK_FS_OPEN_WRITE si le disque est protégé en écriture.
 * @note Un fichier ouvert doit être fermé avec la fonction \ref mk_fat_close.
 *
 */

T_mkCode mk_fat_open ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, T_mkFileMode p_mode );

/**
 * @fn T_mkCode mk_fat_openDirectory ( T_mkVolume* p_volume, T_mkFile* p_file, uint32_t p_baseCluster, uint16_t p_entry, T_mkFileMode p_mode );
 * @brief Cette fonction ouvre le fichier d'index p_entry d'un répertoire.
 *
 * @param[in]     p_volume      Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in,out] p_file        Ce paramètre contient l'instance d'un répertoire.
 * @param[in]     p_baseCluster Ce paramètre contient le cluster d'un répertoire.
 * @param[in]     p_entry       Ce paramètre contient l'index du fichier à ouvrir dans le répertoire.
 * @param[in]     p_mode        Ce paramètre contient les modes d'accès du fichier :
 *                              \li \ref K_MK_FS_OPEN_READ   : le fichier est ouvert avec l'accès en lecture.
 *                              \li \ref K_MK_FS_OPEN_WRITE  : le fichier est ouvert avec l'accès en écriture.
 *                              \li \ref K_MK_FS_OPEN_SHARED : le fichier est ouvert en mode partagé. *
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le fichier a été ouvert.
 *         \li \ref K_MK_ERROR_PARAM         : le fichier n'a pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC        : le fichier n'a pas été ouvert car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : le fichier n'a pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le fichier n'a pas été ouvert car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le fichier n'a pas été ouvert car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : le fichier n'a pas été ouvert car il existe déjà.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été ouvert car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été ouvert car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_COLLISION     : le fichier n'a pas été ouvert car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été ouvert car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_NOT_FOUND     : le fichier n'a pas été ouvert car il n'existe pas.
 *         \li \ref K_MK_ERROR_DENIED        : le fichier n'a pas été ouvert car un fichier en lecture seul ne peut pas être ouvert en écriture.
 *
 * @warning Un fichier ne peut pas être ouvert avec le flag \ref K_MK_FS_OPEN_WRITE si le disque est protégé en écriture.
 * @note Un fichier ouvert doit être fermé avec la fonction \ref mk_fat_close.
 *
 */

T_mkCode mk_fat_openDirectory ( T_mkVolume* p_volume, T_mkFile* p_file, uint32_t p_baseCluster, uint16_t p_entry, T_mkFileMode p_mode );

/**
 * @fn T_mkCode mk_fat_close ( T_mkFile* p_file );
 * @brief Cette fonction ferme un fichier.
 * @param[in,out] p_file Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
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
 */

T_mkCode mk_fat_close ( T_mkFile* p_file );

/**
 * @fn T_mkCode mk_fat_search ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, uint16_t p_entry );
 * @brief Cette fonction recherche un fichier à partir de son nom (UTF8). Si la chaine de caractères présent en paramètre est vide ('\0'), la recherche est effectuée
 *        en fonction de la position du fichier dans le répertoire.
 *
 * @param[in]  p_volume      Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]  p_filePath    Ce paramètre contient le nom du fichier à rechercher ou "" si la recherche est effectuée en fonction de la position du fichier dans un répertoire.
 * @param[in]  p_baseCluster Ce paramètre contient le cluster du répertoire où la recherche doit être effectuée.
 * @param[in]  p_entry       Ce paramètre contient la position du fichier recherché dans le répertoire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : le fichier recherché a été trouvé.
 *         \li \ref K_MK_ERROR_PARAM     : le fichier recherché n'a pas été trouvé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : le fichier recherché n'a pas été trouvé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : le fichier recherché n'a pas été trouvé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : le fichier recherché n'a pas été trouvé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_NOT_FOUND : le fichier recherché n'a pas été trouvé car il n'existe pas (p_filePath != "") ou car la fin du répertoire a été atteint (p_filePath == "").
 *         \li \ref K_MK_ERROR_RIGHT     : le fichier recherché n'a pas été trouvé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_search ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, uint16_t p_entry );

/**
 * @fn T_mkCode mk_fat_link ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );
 * @brief Cette fonction crée un lien symbolique entre deux fichiers.
 *
 * @param[in] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in] p_filePath    Ce paramètre contient l'adresse d'une chaine de caractères UTF8 stockant le chemin et le nom du lien à créer. La chaine
 *                          de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 * @param[in] p_baseCluster Ce paramètre contient le cluster du répertoire où le lien doit être créé.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la création du lien a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : la création du lien a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la création du lien a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la création du lien a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la création du lien a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_FULL          : la création du lien a échoué car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : la création du lien a échoué car un fichier avec le même nom existe déjà.
 *         \li \ref K_MK_ERROR_CORRUPTED     : la création du lien a échoué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_COLLISION     : la création du lien a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : la création du lien a échoué car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : la création du lien a échoué car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : la création du lien n'a pas été réalisé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note L'instance du lien créé n'est pas renvoyée.
 *
 */

T_mkCode mk_fat_link ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );

/**
 * @fn T_mkCode mk_fat_unlink ( T_mkFile* p_file );
 * @brief Cette fonction supprime un fichier.
 * @param[in,out] p_file Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la suppression du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la suppression du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la suppression du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la suppression du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la suppression du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_FULL      : la suppression du fichier a échoué car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_CORRUPTED : la suppression du fichier a échoué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_RIGHT     : la suppression du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED    : la suppression du fichier a échoué car le fichier n'a pas été ouvert avec les droits en écriture.
 *
 * @note L'accès en écriture doit être activé pour utiliser cette fonction.
 * @note Un fichier supprimé doit être fermé à l'aide de la fonction \ref mk_fat_close.
 *
 */

T_mkCode mk_fat_unlink ( T_mkFile* p_file );

/**
 * @fn T_mkCode mk_fat_rename ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );
 * @brief Cette fonction renomme / déplace un fichier. L'opération ne peut pas être réalisée entre 2 partitions.
 *
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_filePath    Ce paramètre contient l'adresse d'une chaine de caractères UTF8 stockant le chemin et le nom du fichier. La chaine
 *                              de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 * @param[in]     p_baseCluster Ce paramètre contient le cluster du répertoire de début de l'opération.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le fichier a été renommé.
 *         \li \ref K_MK_ERROR_PARAM         : le fichier n'a pas été renommé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : le fichier n'a pas été renommé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le fichier n'a pas été renommé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le fichier n'a pas été renommé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_FULL          : le fichier n'a pas été renommé car l'espace sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : le fichier n'a pas été renommé car un fichier avec le même nom existe déjà.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été renommé car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_COLLISION     : le fichier n'a pas été renommé car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été renommé car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : le fichier n'a pas été renommé car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été renommé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : le fichier n'a pas été renommé car il n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_fat_rename ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );

/**
 * @fn T_mkCode mk_fat_getName ( T_mkFile* p_file, T_str8 p_fileName );
 * @brief Cette fonction retourne le nom d'un fichier au format UTF8.
 *
 * @param[in]  p_file     Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[out] p_fileName Ce paramètre contient l'adresse de la chaine de caractères où le nom du fichier doit être stocké.
 *                        L'utilisateur doit fournir une chaine de taille minimale \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le nom du fichier a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le nom du fichier n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le nom du fichier n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le nom du fichier n'a pas été récupéré car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : le nom du fichier n'a pas été récupéré car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : le nom du fichier n'a pas été récupéré car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_getName ( T_mkFile* p_file, T_str8 p_fileName );

/**
 * @fn T_mkCode mk_fat_chmod ( T_mkFile* p_file, uint8_t p_attribute );
 * @brief Cette fonction modifie les attributs d'un fichier.
 *
 * @param[in] p_file      Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in] p_attribute Ce paramètre contient les nouveaux attributs du fichier. Les anciens attributs sont supprimés.
 *                        Une combinaison des constantes suivantes peut être utilisée :
 *                        \li \ref K_MK_FS_ATTRIBUTE_NO        : le fichier ne possède pas d'attribut.
 *                        \li \ref K_MK_FS_ATTRIBUTE_READ_ONLY : le fichier est en lecture seul.
 *                        \li \ref K_MK_FS_ATTRIBUTE_HIDDEN    : le fichier est caché.
 *                        \li \ref K_MK_FS_ATTRIBUTE_SYSTEM    : le fichier est un fichier système.
 *                        \li \ref K_MK_FS_ATTRIBUTE_VOLUME    : le fichier est un nom de volume.
 *                        \li \ref K_MK_FS_ATTRIBUTE_ARCHIVE   : le fichier est une archive.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : les attributs du fichier ont été modifiés.
 *         \li \ref K_MK_ERROR_PARAM         : les attributs du fichier n'ont pas été modifiés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : les attributs du fichier n'ont pas été modifiés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : les attributs du fichier n'ont pas été modifiés car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : les attributs du fichier n'ont pas été modifiés car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_WRITE_PROTECT : les attributs du fichier n'ont pas été modifiés car le disque est protégé en écriture.
 *         \li \ref K_MK_ERROR_RIGHT         : les attributs du fichier n'ont pas été modifiés car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_chmod ( T_mkFile* p_file, uint8_t p_attribute );

/**
 * @fn T_mkCode mk_fat_seek ( T_mkFile* p_file, uint32_t p_filePointer );
 * @brief Cette fonction configure la valeur du pointeur de fichier.
 *
 * @param[in]  p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[out] p_filePointer Ce paramètre contient la nouvelle valeur du pointeur de fichier. Les constantes \ref K_MK_FS_POINTER_TO_SOF ou
 *                           \ref K_MK_FS_POINTER_TO_EOF peuvent être utilisées pour pointer respectivement au début et à la fin du fichier.\n
 *                           Si la valeur du pointeur de fichier est supérieur à la taille du fichier, le pointeur de fichier est alors placé à la fin
 *                           du fichier.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la valeur du pointeur de fichier a été configurée.
 *         \li \ref K_MK_ERROR_PARAM     : la valeur du pointeur de fichier n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la valeur du pointeur de fichier n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la valeur du pointeur de fichier n'a pas été configurée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la valeur du pointeur de fichier n'a pas été configurée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la valeur du pointeur de fichier n'a pas été configurée car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_RIGHT     : la valeur du pointeur de fichier n'a pas été configurée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_seek ( T_mkFile* p_file, uint32_t p_filePointer );

/**
 * @fn T_mkCode mk_fat_tell ( T_mkFile* p_file, uint32_t* p_filePointer );
 * @brief Cette fonction retourne la valeur du pointeur de fichier.
 *
 * @param[in] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in] p_filePointer Ce paramètre contient l'adresse où doit être stocké la valeur du pointeur de fichier.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la valeur du pointeur de fichier est disponible dans la paramètre de retour.
 *         \li \ref K_MK_ERROR_PARAM : la valeur du pointeur de fichier n'est pas disponible dans le paramètre de retour car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_tell ( T_mkFile* p_file, uint32_t* p_filePointer );

/**
 * @fn T_mkCode mk_fat_stat ( T_mkVolume* p_volume, T_str8 p_filePath, uint32_t p_baseCluster, uint8_t* p_buf );
 * @brief Cette fonction teste l'existence d'un fichier.
 *
 * @param[in] p_volume      Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in] p_filePath    Ce paramètre contient l'adresse d'une chaine de caractères UTF8 stockant le chemin et le nom du fichier à tester. La chaine
 *                          de caractères ne doit pas dépasser \ref K_MK_FILE_MAX_NAME_LENGTH octets.
 * @param[in] p_baseCluster Ce paramètre contient le cluster du répertoire où la recherche doit être effectuée.
 * @param[in] p_buf         Ce paramètre contient l'adresse d'un cache de données.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : le fichier existe.
 *         \li \ref K_MK_ERROR_NOT_FOUND : le fichier n'existe pas.
 *         \li \ref K_MK_ERROR_PARAM     : l'existence du fichier n'a pas été testée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : l'existence du fichier n'a pas été testée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : l'existence du fichier n'a pas été testée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : l'existence du fichier n'a pas été testée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT     : l'existence du fichier n'a pas été testée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_stat ( T_mkVolume* p_volume, T_str8 p_filePath, uint32_t p_baseCluster, uint8_t* p_buf );

/**
 * @fn T_mkCode mk_fat_eof ( T_mkFile* p_file, uint32_t* p_eof );
 * @brief Cette fonction teste si la fin d'un fichier a été atteinte.
 *
 * @param[in]  p_file Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[out] p_eof  Ce paramètre contient l'adresse où doit être stocké le résultat de la fonction :
 *                    \li \ref K_MK_FS_EOF_TRUE  : le pointeur de fichier est à la fin du fichier.
 *                    \li \ref K_MK_FS_EOF_FALSE : le pointeur de fichier n'est pas à la fin du fichier.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_eof ( T_mkFile* p_file, uint32_t* p_eof );

/**
 * @fn T_mkCode mk_fat_truncate ( T_mkFile* p_file );
 * @brief Cette fonction tronque un fichier à partir de la valeur du pointeur du fichier :
 *        \li Si le pointeur de fichier est nul, l'intégralité du fichier est tronqué (taille nulle).
 *        \li Si le pointeur de fichier est égal à la taille du fichier, le fichier n'est pas tronqué.
 * @param[in,out] p_file Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : le fichier a été tronqué.
 *         \li \ref K_MK_ERROR_PARAM     : le fichier n'a pas été tronqué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : le fichier n'a pas été tronqué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : le fichier n'a pas été tronqué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : le fichier n'a pas été tronqué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : le fichier n'a pas été tronqué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED    : le fichier n'a pas été tronqué car il n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_RIGHT     : le fichier n'a pas été tronqué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note L'accès en écriture doit être activé pour utiliser cette fonction.
 *
 */

T_mkCode mk_fat_truncate ( T_mkFile* p_file );

/**
 * @fn T_mkCode mk_fat_expand ( T_mkFile* p_file, uint32_t p_newFileSize );
 * @brief Cette fonction augmente la taille d'un fichier. Aucune opération n'est réalisée si le paramètre p_newFileSize est inférieur à la taille du fichier.
 *        La position du pointeur de fichier n'est pas modifiée.
 *
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_newFileSize Ce paramètre contient la nouvelle taille du fichier [en octets].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la taille du fichier a été augmentée.
 *         \li \ref K_MK_ERROR_PARAM     : la taille du fichier n'a pas été augmentée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la taille du fichier n'a pas été augmentée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la taille du fichier n'a pas été augmentée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la taille du fichier n'a pas été augmentée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la taille du fichier n'a pas été augmentée car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED    : la taille du fichier n'a pas été augmentée car il n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL      : la taille du fichier n'a pas été augmentée car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT     : la taille du fichier n'a pas été augmentée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note L'accès en écriture doit être activé pour utiliser cette fonction.
 *
 */

T_mkCode mk_fat_expand ( T_mkFile* p_file, uint32_t p_newFileSize );

/**
 * @fn T_mkCode mk_fat_read ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead );
 * @brief Cette fonction lit un ou plusieurs octets d'un fichier. L'offset du premier octet lu est définie par le pointeur de fichier.
 *
 * @param[in,out] p_file                Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[out]    p_buf                 Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]     p_numberOfBytesToRead Ce paramètre contient le nombre d'octets à lire.
 * @param[out]    p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus. Si la fonction s'est exécutée sans erreur et que p_numberOfBytesRead est
 *                                      différent de p_numberOfBytesToRead, alors la fin du fichier a été atteinte.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la lecture du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la lecture du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la lecture du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la lecture du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la lecture du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la lecture du fichier a échoué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED    : la lecture du fichier a échoué car il n'a pas été ouvert avec les droits en lecture.
 *         \li \ref K_MK_ERROR_RIGHT     : la lecture du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note L'accès en lecture doit être activé pour utiliser cette fonction.
 * @note Le pointeur de fichier doit être reconfiguré si l'exécution de cette fonction a échoué.
 *
 */

T_mkCode mk_fat_read ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToRead, uint32_t* p_numberOfBytesRead );

/**
 * @fn T_mkCode mk_fat_write ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite );
 * @brief Cette fonction écrit un ou plusieurs octets dans un fichier. L'offset du premier octet écrit est définie par le pointeur de fichier.
 *
 * @param[in,out] p_file                 Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[in]     p_buf                  Ce paramètre contient l'adresse du buffer de données à écrire.
 * @param[in]     p_numberOfBytesToWrite Ce paramètre contient le nombre d'octets à écrire.
 * @param[out]    p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : l'écriture du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : l'écriture du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : l'écriture du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : l'écriture du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : l'écriture du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : l'écriture du fichier a échoué car le fichier est corrompu (table des clusters FAT).
 *         \li \ref K_MK_ERROR_DENIED    : l'écriture du fichier a échoué car il n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL      : l'écriture du fichier a échoué car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT     : l'écriture du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 * @note L'accès en écriture doit être activé pour utiliser cette fonction.
 * @note Le pointeur de fichier doit être reconfiguré si l'exécution de cette fonction a échoué.
 *
 */

T_mkCode mk_fat_write ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite );

/**
 * @fn T_mkCode mk_fat_getInfo ( T_mkFile* p_file, T_mkFileInfo* p_fileInfo );
 * @brief Cette fonction retourne les informations relatives à un fichier.
 *
 * @param[in]  p_file     Ce paramètre contient l'adresse d'un fichier de type \ref T_mkFile.
 * @param[out] p_fileInfo Ce paramètre contient l'adresse d'une structure de type \ref T_mkFileInfo où les informations doivent être stockées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la récupération des informations du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la récupération des informations du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la récupération des informations du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la récupération des informations du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la récupération des informations du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la récupération des informations du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_getInfo ( T_mkFile* p_file, T_mkFileInfo* p_fileInfo );

/**
 *
 */

#endif

