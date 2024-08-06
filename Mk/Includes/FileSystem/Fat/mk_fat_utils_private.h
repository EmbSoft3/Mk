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
* @file mk_fat_utils_private.h
* @brief Déclaration des fonctions utilitaires dédiées au système de fichiers FAT32.
* @date 28 déc. 2020
*
*/

#ifndef MK_FAT_UTILS_PRIVATE_H
#define MK_FAT_UTILS_PRIVATE_H

/**
 * @fn uint32_t mk_fat_utils_getNumberOfEntries ( T_str8 p_fileName );
 * @brief Cette fonction retourne le nombre d'entrées utilisées pour coder un nom de fichier long.
 * @param[in] p_fileName Ce paramètre contient l'adresse d'une chaine de caractères ('\0').
 *
 * @return Cette fonction retourne le nombre d'entrées utlisées pour coder un nom de fichier long ou la valeur 0 si la chaine de caractères est invalide.
 */

uint32_t mk_fat_utils_getNumberOfEntries ( T_str8 p_fileName );

/**
 * @fn T_mkCode mk_fat_utils_checkInvalidName ( T_str8 p_filePath );
 * @brief Cette fonction vérifie la validité d'un nom de fichier.
 * @param[in] p_filePath Ce paramètre contient l'adresse d'une chaine de caractères ('\0').
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la chaine de caractères est valide.
 *         \li \ref K_MK_ERROR_PARAM : la chaine de caractères est invalide.
 */

T_mkCode mk_fat_utils_checkInvalidName ( T_str8 p_filePath );

/**
 * @fn T_mkCode mk_fat_utils_getDate ( uint16_t* p_date, uint16_t* p_time );
 * @brief Cette fonction récupére la valeur du calendrier système puis le converti au format FAT.
 *
 * @param[out] p_date Ce paramètre contient l'adresse du pointeur contenant la date.
 * @param[out] p_time Ce paramètre contient l'adresse du pointeur contenant l'heure.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK               : le calendrier système a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM      : le calendrier système n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_UNEXPECTED : le calendrier système n'a pas été récupéré car le système n'a pas pu fournir une valeur de calendrier cohérente.
 */

T_mkCode mk_fat_utils_getDate ( uint16_t* p_date, uint16_t* p_time );

/**
 * @fn T_mkCode mk_fat_utils_read ( T_mkFile* p_file, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint32_t* p_numberOfBytesRead );
 * @brief Cette fonction lit d'un ou plusieurs bocs de données d'un fichier. La taille du buffer doit être multiple de la taille d'un bloc de données.
 *
 * @param[in]  p_file                Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_blockAddress        Ce paramètre contient l'adresse du premier bloc de données à lire.
 * @param[out] p_buf                 Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]  p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out] p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus suite à l'exécution de cette fonction.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la lecture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la lecture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la lecture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la lecture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_read ( T_mkFile* p_file, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint32_t* p_numberOfBytesRead );

/**
 * @fn T_mkCode mk_fat_utils_write ( T_mkFile* p_file, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint32_t* p_numberOfBytesWrite );
 * @brief Cette fonction écrit un ou plusieurs blocs de données dans un fichier. La taille du buffer doit être multiple de la taille d'un bloc de données.
 *
 * @param[in]  p_file                 Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_blockAddress         Ce paramètre contient l'adresse du premier bloc de données à écrire.
 * @param[in] p_buf                    Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]  p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out] p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrit suite à l'exécution de cette fonction.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_write ( T_mkFile* p_file, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint32_t* p_numberOfBytesWrite );

/**
 * @fn T_mkCode mk_fat_utils_readCache ( T_mkFile* p_file, uint64_t p_blockAddress );
 * @brief Cette fonction charge le cache de données avec plusieurs blocs de données consécutifs. Le chargement est réalisée uniquement si p_blockAddress n'est
 *        pas disponible dans celui-ci.
 *
 * @param[out] p_file         Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_blockAddress Ce paramètre contient l'adresse du premier bloc de données à lire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la lecture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la lecture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la lecture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la lecture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_readCache ( T_mkFile* p_file, uint64_t p_blockAddress );

/**
 * @fn T_mkCode mk_fat_utils_writeCache ( T_mkFile* p_file, uint64_t p_blockAddress );
 * @brief Cette fonction écrit les blocs de données du cache sur le disque. La synchronisation du cache avec le disque est réalisée uniquement si p_blockAddress
 *        n'est pas disponible dans celui-ci.
 *
 * @param[out] p_file         Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_blockAddress Ce paramètre contient l'adresse du premier bloc de données à écrire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_writeCache ( T_mkFile* p_file, uint64_t p_blockAddress );

/**
 * @fn T_mkCode mk_fat_utils_sync ( T_mkFile* p_file );
 * @brief Cette fonction synchronise le cache de données avec le disque.
 * @param[out] p_file Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_sync ( T_mkFile* p_file );

/**
 * @fn T_mkCode mk_fat_utils_appendCluster ( T_mkFile* p_file, uint32_t p_lastCluster, uint32_t* p_nextCluster, uint32_t p_numberOfClusters );
 * @brief Cette fonction ajoute un ou plusieurs clusters à une chaine de clusters ou créée une nouvelle chaine de cluster.
 *
 * @param[in,out] p_file             Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]     p_lastCluster      Ce paramètre contient la valeur du dernier cluster où la valeur \ref K_MK_FAT_CREATE_CLUSTER_CHAIN si une chaine de cluster
 *                                   doit être créée.
 * @param[out]    p_nextCluster      Ce paramètre contient la valeur du premier cluster alloué.
 * @param[in]     p_numberOfClusters Ce paramètre contient le nombre de cluster à allouer.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la création/actualisation de la chaine de cluster a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : la création/actualisation de la chaine de cluster a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la création/actualisation de la chaine de cluster a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la création/actualisation de la chaine de cluster a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la création/actualisation de la chaine de cluster a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la création/actualisation de la chaine de cluster a échoué car le nombre d'entrées disponibles n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT         : la création/actualisation de la chaine de cluster a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_appendCluster ( T_mkFile* p_file, uint32_t p_lastCluster, uint32_t* p_nextCluster, uint32_t p_numberOfClusters );

/**
 * @fn T_mkCode mk_fat_utils_releaseCluster ( T_mkFile* p_file, uint32_t p_cluster );
 * @brief Cette fonction libère une chaine de clusters.
 *
 * @param[in,out] p_file    Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]     p_cluster Ce paramètre contient la valeur du premier cluster de la chaine.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la libération de la chaine de cluster a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la libération de la chaine de cluster a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la libération de la chaine de cluster a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la libération de la chaine de cluster a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la libération de la chaine de cluster a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la libération de la chaine de cluster a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_RIGHT     : la libération de la chaine de cluster a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_releaseCluster ( T_mkFile* p_file, uint32_t p_cluster );

/**
 * @fn T_mkCode mk_fat_utils_setCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_value );
 * @brief Cette fonction modifie la valeur d'un cluster.
 *
 * @param[in,out] p_file        Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]     p_cluster     Ce paramètre contient la valeur du cluster à modifier.
 * @param[out]    p_nextCluster Ce paramètre contient l'ancienne valeur présente dans le cluster.
 * @param[in]     p_value       Ce paramètre contient la valeur à écrire dans le cluster.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la modification du cluster a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la modification du cluster a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la modification du cluster a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la modification du cluster a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la modification du cluster a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la modification du cluster a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_RIGHT     : la modification du cluster a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_setCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_value );

/**
 * @fn T_mkCode mk_fat_utils_getCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_clusterNumber );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs clusters d'une chaine.
 *
 * @param[in,out] p_file          Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]     p_cluster       Ce paramètre contient la valeur d'un cluster de la chaine.
 * @param[out]    p_nextCluster   Ce paramètre contient un pointeur sur une table de clusters de taille p_clusterNumber.
 * @param[in]     p_clusterNumber Ce paramètre contient le nombre de clusters à retourner.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la valeur des clusters a été renvoyées.
 *         \li \ref K_MK_ERROR_PARAM         : la valeur des clusters n'a pas été renvoyées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la valeur des clusters n'a pas été renvoyées car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la valeur des clusters n'a pas été renvoyées car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la valeur des clusters n'a pas été renvoyées car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : la valeur des clusters n'a pas été renvoyées car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_RIGHT         : la valeur des clusters n'a pas été renvoyées car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_getCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_clusterNumber );

/**
 * @fn T_mkCode mk_fat_utils_findCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_searchedCluster, uint32_t p_clusterNumber );
 * @brief Cette fonction retourne la valeur du cluster d'indice p_clusterNumber d'une chaine.
 *
 * @param[in,out] p_file            Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]     p_cluster         Ce paramètre contient la valeur d'un cluster de la chaine.
 * @param[out]    p_searchedCluster Ce paramètre contient la valeur du cluster recherché.
 * @param[in]     p_clusterNumber   Ce paramètre contient l'index du cluster à renvoyer par rapport au cluster de référence (p_cluster).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la valeur du cluster recherché a été renvoyée.
 *         \li \ref K_MK_ERROR_PARAM         : la valeur du cluster recherché n'a pas été renvoyée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la valeur du cluster recherché n'a pas été renvoyée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la valeur du cluster recherché n'a pas été renvoyée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la valeur du cluster recherché n'a pas été renvoyée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : la valeur du cluster recherché n'a pas été renvoyée car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_NOT_FOUND     : la valeur du cluster recherché n'a pas été renvoyée car il n'existe pas.
 *         \li \ref K_MK_ERROR_RIGHT         : la valeur du cluster recherché n'a pas été renvoyée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_findCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_searchedCluster, uint32_t p_clusterNumber );

/**
 * @fn T_mkCode mk_fat_utils_setInfo ( T_mkFile* p_file );
 * @brief Cette fonction actualise le secteur d'information d'une partition FAT.
 * @param[in] p_file Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'actualisation du secteur d'information a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'actualisation du secteur d'information a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'actualisation du secteur d'information a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'actualisation du secteur d'information a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'actualisation du secteur d'information a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'actualisation du secteur d'information a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_setInfo ( T_mkFile* p_file );

/**
 * @fn T_mkCode mk_fat_utils_findName ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_checksum );
 * @brief Cette fonction génére un nom de fichier au format 8.3 à partir d'un nom de fichier long puis vérifie que le nom généré est unique.
 *
 * @param[in]  p_file         Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_handler      Ce paramètre contient l'index d'un gestionnaire de recherche. L'attribut 'currentCluster' doit contenir le cluster du répertoire analysé.
 * @param[in]  p_fileName     Ce paramètre contient l'adresse d'une chaine de caractères ('\0').
 * @param[out] p_fatEntryName Ce paramètre contient l'adresse d'une chaine de caractères stockant le nom généré au format 8.3 ('\0').
 * @param[out] p_checksum     Ce paramètre contient le checksum du nom généré.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la génération du nom de fichier 8.3 a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la génération du nom de fichier 8.3 a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la génération du nom de fichier 8.3 a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la génération du nom de fichier 8.3 a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la génération du nom de fichier 8.3 a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_NOT_FOUND : la génération du nom de fichier 8.3 a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_RIGHT     : la génération du nom de fichier 8.3 a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_findName ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_checksum );

/**
 * @fn T_mkCode mk_fat_utils_setName ( T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_caseType, uint8_t* p_checksum, T_mkFATEntryType p_type, uint16_t p_fileIndex );
 * @brief Cette fonction génére un nom de fichier au format 8.3 à partir d'un nom de fichier court ou long.
 *
 * @param[in]  p_fileName     Ce paramètre contient l'adresse d'une chaine de caractères ('\0').
 * @param[out] p_fatEntryName Ce paramètre contient l'adresse d'une chaine de caractères stockant le nom généré au format 8.3 ('\0').
 * @param[out] p_caseType     Ce paramètre contient la valeur du champ de casse (\ref T_mkFATCaseAttribute) - dédié au nom de fichier court.
 * @param[out] p_checksum     Ce paramètre contient la valeur du checksum correspondant au nom généré.
 * @param[in]  p_type         Ce paramètre contient le type fichier (court: \ref K_MK_FAT_ENTRY_ST, long: \ref K_MK_FAT_ENTRY_EX).
 * @param[in]  p_fileIndex    Ce paramètre contient l'index à écrire dans le nom de fichier 8.3 lors de sa génération - dédié au nom de fichier long et aux collisions.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la génération du nom de fichier 8.3 a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la génération du nom de fichier 8.3 a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_utils_setName ( T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_caseType, uint8_t* p_checksum, T_mkFATEntryType p_type, uint16_t p_fileIndex );

/**
 * @fn T_mkCode mk_fat_utils_getName ( T_mkFATEntryDescriptor* p_entry, T_str8 p_fileName, T_mkFATEntryType p_type );
 * @brief Cette fonction retourne la chaine de caractères contenu dans une entrée d'un répertoire.
 *        Le secteur contenant l'entrée doit préalablement être chargé en mémoire.
 *
 * @param[in] p_entry     Ce paramètre contient l'adresse d'une structure de type \ref T_mkFATEntryDescriptor.
 * @param[out] p_fileName Ce paramètre contient l'adresse de la chaine de caractères ('\0') où les caractères de l'entrée doivent être stockés.
 * @param[in] p_type      Ce paramètre contient le type de l'entrée (\ref K_MK_FAT_ENTRY_ST ou \ref K_MK_FAT_ENTRY_EX)
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les caractères de l'entrée ont été récupérés.
 *         \li \ref K_MK_ERROR_PARAM : les caractères de l'entrée ont été récupérés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_utils_getName ( T_mkFATEntryDescriptor* p_entry, T_str8 p_fileName, T_mkFATEntryType p_type );

/**
 * @fn T_mkCode mk_fat_utils_getNameType ( T_str8 p_fileName, T_mkFATEntryType* p_nameType );
 * @brief Cette fonction permet de récupérer le type d'une chaine de caractères.
 *
 * @param[in]  p_fileName  Ce paramètre contient l'adresse d'une chaine de caractères ('\0').
 * @param[out] p_nameType  Ce paramètre contient le type de la chaine de caractères.
 *                         \li \ref K_MK_FAT_ENTRY_ST : la chaine de caractères est au format 8.3.
 *                         \li \ref K_MK_FAT_ENTRY_EX :la chaine de caractères est au format étendu.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la récupération du type de la chaine de caractères a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la récupération du type de la chaine de caractères a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_utils_getNameType ( T_str8 p_fileName, T_mkFATEntryType* p_nameType );

/**
 * @fn T_mkCode mk_fat_utils_findFile ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, uint16_t p_entry );
 * @brief Cette fonction recherche un fichier à partir de son nom. Si la chaine de caractères présent en paramètre est vide (""), la recherche est effectuée
 *        en fonction de la position du fichier dans le répertoire.
 *
 * @param[out] p_file        Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_filePath    Ce paramètre contient le nom du fichier à rechercher ou "" si la recherche est effectuée en fonction de la position du fichier.
 * @param[in]  p_fileBuf     Ce paramètre contient l'adresse d'un buffer permettant de décomposer le chemin du fichier. Il doit possèder une taille de
 *                           (\ref K_MK_FILE_MAX_NAME_LENGTH + 1) octets.
 * @param[in]  p_baseCluster Ce paramètre contient le cluster du répertoire où la recherche doit être effectuée.
 * @param[in]  p_entry       Ce paramètre contient la position du fichier recherché dans le répertoire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : le fichier a été trouvé.
 *         \li \ref K_MK_ERROR_PARAM     : le fichier n'a pas été trouvé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : le fichier n'a pas été trouvé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : le fichier n'a pas été trouvé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : le fichier n'a pas été trouvé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_NOT_FOUND : le fichier n'a pas été trouvé car il n'existe pas (p_filePath != "") ou car la fin du répertoire a été atteint (p_filePath == "").
 *         \li \ref K_MK_ERROR_RIGHT     : le fichier n'a pas été trouvé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_findFile ( T_mkFile* p_file, T_str8 p_filePath, T_str8 p_fileBuf, uint32_t p_baseCluster, uint16_t p_entry );

/**
 * @fn T_mkCode mk_fat_utils_createFile ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, uint8_t p_fileAttribute );
 * @brief Cette fonction crée un fichier.
 *
 * @param[out] p_file          Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_fileName      Ce paramètre contient le nom du fichier à créer (avec '\0').
 * @param[in]  p_baseCluster   Ce paramètre contient le cluster du répertoire où le fichier doit être créé.
 * @param[in]  p_fileAttribute Ce paramètre contient les attributs du fichier (\ref T_mkFATFileAttribute).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le fichier a été créé.
 *         \li \ref K_MK_ERROR_PARAM         : le fichier n'a pas été créé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : le fichier n'a pas été créé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le fichier n'a pas été créé car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : le fichier n'a pas été créé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : le fichier n'a pas été créé car il existe déjà.
 *         \li \ref K_MK_ERROR_FULL          : le fichier n'a pas été crée car l'espace sur le disque est insuffisant.
 *         \li \ref K_MK_ERROR_CORRUPTED     : le fichier n'a pas été crée car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : le fichier n'a pas été crée car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_COLLISION     : le fichier n'a pas été crée car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_RIGHT         : le fichier n'a pas été créé car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_createFile ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, uint8_t p_fileAttribute );

/**
 * @fn T_mkCode mk_fat_utils_setFile ( T_mkFile* p_file, T_mkFATHandler* p_handler, uint32_t p_size );
 * @brief Cette fonction initialise les attributs d'un fichier.
 *
 * @param[out] p_file    Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkFATHandler. Les attributs "directoryCluster", "entryCluster", "entryVirtualCluster",
 *                       "firstDataCluster", "entryClusterIndex" et "entryVirtualClusterIndex" doivent être initialisés préalablement avec les caractéristiques du fichier.
 * @param[in]  p_size    Ce paramètre contient la taille du fichier.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les attributs du fichier ont été initialisés.
 *         \li \ref K_MK_ERROR_PARAM : les attributs du fichier n'ont pas été initialisés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_fat_utils_setFile ( T_mkFile* p_file, T_mkFATHandler* p_handler, uint32_t p_size );

/**
 * @fn T_mkCode mk_fat_utils_getLastEntry ( T_mkFile* p_file, uint32_t p_baseCluster, T_mkFATEntryAddress* p_address );
 * @brief Cette fonction retourne l'adresse de la dernière entrée non utilisée d'un répertoire.
 *
 * @param[in] p_file         Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_baseCluster Ce paramètre contient le cluster du répertoire où la recherche doit être effectuée.
 * @param[out] p_address     Ce paramètre contient l'adresse de la dernière entrée d'un répertoire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : les coordonnées de l'entrée ont été renvoyée.
 *         \li \ref K_MK_ERROR_PARAM     : les coordonnées de l'entrée n'ont pas été renvoyée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : les coordonnées de l'entrée n'ont pas été renvoyée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : les coordonnées de l'entrée n'ont pas été renvoyée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : les coordonnées de l'entrée n'ont pas été renvoyée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : les coordonnées de l'entrée n'ont pas été renvoyée car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_RIGHT     : les coordonnées de l'entrée n'ont pas été renvoyée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_getLastEntry ( T_mkFile* p_file, uint32_t p_baseCluster, T_mkFATEntryAddress* p_address );

/**
 * @fn T_mkCode mk_fat_utils_writeEntry ( T_mkFile* p_file, T_str8 p_fileName, uint8_t p_fileAttribute, T_mkFATEntryType p_type, T_mkFATHandler* p_handler );
 * @brief Cette fonction écrit une ou plusieurs entrées dans un répertoire.
 *
 * @param[out] p_file          Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]  p_fileName      Ce paramètre contient le nom du fichier à créer ('\0').
 * @param[in]  p_fileAttribute Ce paramètre contient les attributs du fichier (\ref T_mkFATFileAttribute).
 * @param[in]  p_type          Ce paramètre contient le type de l'entrée à créer.
 *                             \li \ref K_MK_FAT_ENTRY_SP : création des entrées '.' et '..'.
 *                             \li \ref K_MK_FAT_ENTRY_ST : création d'une entrée au format 8.3.
 *                             \li \ref K_MK_FAT_ENTRY_EX : création d'une entrée au format étendue.
 * @param[out]  p_handler      Ce paramètre contient l'adresse du gestionnaire stockant la localisation de l'entrée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la création des entrées a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : la création des entrées a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : la création des entrées a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la création des entrées a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : la création des entrées a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_ALREADY_EXIST : la création des entrées a échoué car un fichier avec le même nom existe déjà.
 *         \li \ref K_MK_ERROR_CORRUPTED     : la création des entrées a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : la création des entrées a échoué car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_COLLISION     : la création des entrées a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_RIGHT         : la création des entrées a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_writeEntry ( T_mkFile* p_file, T_str8 p_fileName, uint8_t p_fileAttribute, T_mkFATEntryType p_type, T_mkFATHandler* p_handler );

/**
 * @fn T_mkCode mk_fat_utils_link ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );
 * @brief Cette fonction crée un lien symbolique entre deux fichiers.
 *
 * @param[in] p_file        Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in] p_filePath    Ce paramètre contient la chaine de caractères stockant le nom et le chemin du lien symbolique (avec '\0').
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
 *         \li \ref K_MK_ERROR_CORRUPTED     : la création du lien a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_COLLISION     : la création du lien a échoué car le nombre de collisions max dans la détermination d'un nom de fichier court a été atteint.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : la création du lien a échoué car le système n'a pas pu fournir une valeur de calendrier cohérente.
 *         \li \ref K_MK_ERROR_RIGHT         : la création du lien a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_link ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster );

/**
 * @fn T_mkCode mk_fat_utils_unlink ( T_mkFile* p_file, uint32_t p_mode );
 * @brief Cette fonction supprime un fichier.
 *
 * @param[in, out] p_file Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in]      p_mode Ce paramètre contient le mode de suppression. Une des constantes suivantes peut être utilisée :
 *                        \li \ref K_MK_FAT_RELEASE_CLUSTERS : l'entrée et les clusters de données du fichier sont supprimés.
 *                        \li \ref K_MK_FAT_KEEP_CLUSTERS    : l'entrée du fichier est supprimées, les clusters de données sont conservés.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK              : la suppression du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM     : la suppression du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR       : la suppression du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT   : la suppression du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM      : la suppression du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED : la suppression du fichier a échoué car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_RIGHT     : la suppression du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_unlink ( T_mkFile* p_file, uint32_t p_mode );

/**
 * @fn T_mkCode mk_fat_utils_getFileEntryDescriptor ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entryDescriptor );
 * @brief Cette fonction récupére la valeur de l'entrée 8.3 d'un fichier.
 *
 * @param[in]  p_file            Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[out] p_entryDescriptor Ce paramètre contient l'adresse de la structure stockant la valeur de l'entrée (\ref T_mkFATEntryDescriptor).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la récupération de l'entrée a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la récupération de l'entrée a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la récupération de l'entrée a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la récupération de l'entrée a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la récupération de l'entrée a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la récupération de l'entrée a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_getFileEntryDescriptor ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entryDescriptor );

/**
 * @fn T_mkCode mk_fat_utils_setFileEntryDescriptor ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entryDescriptor );
 * @brief Cette fonction modifie l'entrée 8.3 d'un fichier.
 *
 * @param[in] p_file            Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 * @param[in] p_entryDescriptor Ce paramètre contient l'adresse de la structure stockant la valeur de l'entrée à écrire (\ref T_mkFATEntryDescriptor).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture de l'entrée a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture de l'entrée a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture de l'entrée a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture de l'entrée a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture de l'entrée a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture de l'entrée a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_setFileEntryDescriptor ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entryDescriptor );

/**
 * @fn T_mkCode mk_fat_utils_synchFileEntryDescriptor ( T_mkFile* p_file );
 * @brief Cette fonction synchronise une instance de fichier avec le contenu de son entrée. Cette fonction est utilisée dans le cadre des fichiers partagées (attribut
 *        \ref K_MK_FS_OPEN_SHARED). Dans un premier temps, elle vérifie que le fichier n'a pas été supprimé puis dans un second temps, vérifie si la localisation du
 *        pointeur de fichier est compatible avec la taille du fichier. En cas d'incompatibilité, elle place le pointeur à la fin du fichier.
 * @param[in, out] p_file Ce paramètre contient l'adresse d'une fichier de type \ref T_mkFile.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la synchronisation du fichier a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la synchronisation du fichier a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la synchronisation du fichier a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la synchronisation du fichier a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la synchronisation du fichier a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la synchronisation du fichier a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_fat_utils_synchFileEntryDescriptor ( T_mkFile* p_file );

/**
 *
 */

#endif

