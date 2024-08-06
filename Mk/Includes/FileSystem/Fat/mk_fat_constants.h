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
* @file mk_fat_constants.h
* @brief Définition des constantes dédiées au système de fichiers FAT32.
* @date 26 déc. 2020
*
*/

#ifndef MK_FAT_CONSTANTS_H
#define MK_FAT_CONSTANTS_H

/**
 * @def K_MK_FAT_NUMBER_OF_FAT_TO_UPDATE
 * @brief Définition du nombre minimal de FAT à actualiser lors de la modification
 *        de la table des clusters.
 *        La valeur minimale de cette constante est 1. Elle est bornée par la
 *        valeur de l'attribut numberOfFat contenu dans la structure
 *        \ref T_mkVolumeFAT.
 * @note Cette constante peut être modifiée par l'utilisateur.
 *
 */

#define K_MK_FAT_NUMBER_OF_FAT_TO_UPDATE 2

/**
 * @def K_MK_FAT_COLLISION_NUMBER
 * @brief Définition du nombre maximal de collision pouvant survenir lors
 *        de la détermination d'un nom de fichier court (format étendu).
 * @note Cette constante peut être modifiée par l'utilisateur.
 *
 */

#define K_MK_FAT_COLLISION_NUMBER 32

/**
 * @def K_MK_FAT_CALENDAR_NUMBER
 * @brief Définition du nombre maximal d'occurences pouvant survenir lors
 *        de la récupération du temps système avant de lever une erreur.
 * @note Cette constante peut être modifiée par l'utilisateur.
 *
 */

#define K_MK_FAT_CALENDAR_NUMBER 32

/**
 * @def K_MK_FAT_CLUSTER_MAP_LENGTH
 * @brief Définition de la taille du cache utilisé pour précharger la valeur
 *        de 'n' clusters d'un fichier.
 * @note Cette constante peut être modifiée par l'utilisateur.
 *
 */

#define K_MK_FAT_CLUSTER_MAP_LENGTH 16

/**
 *
 */

/**
 * @def K_MK_FAT_CLUSTER_ENTRY_SIZE
 * @brief Définition de la taille d'un cluster FAT32 [en octets].
 */

#define K_MK_FAT_CLUSTER_ENTRY_SIZE 4

/**
 * @def K_MK_FAT_ENTRY_SIZE
 * @brief Définition de la taille d'une entrée de répertoire [en octets].
 */

#define K_MK_FAT_ENTRY_SIZE 32

/**
 * @def K_MK_FAT_ENTRY_NAME_SIZE
 * @brief Définition de la taille d'un nom de fichier court [en octets].
 */

#define K_MK_FAT_ENTRY_NAME_SIZE 8

/**
 * @def K_MK_FAT_ENTRY_EXTENSION_SIZE
 * @brief Définition de la taille d'une extension de fichier court [en octets].
 */

#define K_MK_FAT_ENTRY_EXTENSION_SIZE 3

/**
 *
 */

/**
 * @def K_MK_FAT_MIN_NUMBER_OF_CLUSTERS
 * @brief Définition du nombre minimal de clusters dans une partition FAT32.
 */

#define K_MK_FAT_MIN_NUMBER_OF_CLUSTERS 65525

/**
 * @def K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS
 * @brief Définition du nombre de clusters réservés dans une partition FAT32.
 */

#define K_MK_FAT_NUMBER_OF_RESERVED_CLUSTERS 2

/**
 *
 */

/**
 * @def K_MK_FAT_EXTENDED_ENTRY_MASK
 * @brief Définition de la valeur du masque permettant d'identifier une entrée
 *        de répertoire comme étendue.
 */

#define K_MK_FAT_EXTENDED_ENTRY_MASK 0x40

/**
 * @def K_MK_FAT_EXTENDED_ENTRY_COUNT_MASK
 * @brief Définition de la valeur du masque permettant de déterminer le nombre
 *        d'entrées étendues implémentant un nom de fichier long.
 */

#define K_MK_FAT_EXTENDED_ENTRY_COUNT_MASK 0x3F

/**
 * @def K_MK_FAT_EXTENDED_PADDING
 * @brief Définition de la valeur de la signature utilisée pour indiquer la
 *        fin du nom d'un fichier long dans une entrée étendue.
 */

#define K_MK_FAT_EXTENDED_PADDING 0xFF

/**
 * @def K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY
 * @brief Définition du nombre de caractères contenus dans une entrée étendue.
 */

#define K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY 13

/**
 *
 */

/**
 * @def K_MK_FAT_FIRST_ENTRY_OFFSET
 * @brief Définition de l'offset de la première entrée dans un répertoire.
 */

#define K_MK_FAT_FIRST_ENTRY_OFFSET 0

/**
 * @def K_MK_FAT_FIRST_DIRECTORY_ENTRY
 * @brief Définition de l'offset de la première entrée de données dans un
 *        répertoire ('.', '..').
 */

#define K_MK_FAT_FIRST_DIRECTORY_ENTRY 2

/**
 *
 */

/**
 * @def K_MK_FAT_VIRTUAL_ENTRY_DEFAULT
 * @brief Définition d'une valeur précisant que le fichier n'est pas de type
 *        étendu.
 */

#define K_MK_FAT_VIRTUAL_ENTRY_DEFAULT 0xFFFF

/**
 * @def K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT
 * @brief Définition d'une valeur précisant que le fichier n'est pas de type
 *        étendu.
 */

#define K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT 0xFFFFFFFF

/**
 * @def K_MK_FAT_LONG_NAME_FOUND
 * @brief Définition d'une signature indiquant que le nom du fichier long
 *        n'a pas été trouvé durant une opération de recherche par nom.
 */

#define K_MK_FAT_LONG_NAME_FOUND 0xFFFFFFFF

/**
 * @def K_MK_FAT_ENTRY_FOUND
 * @brief Définition d'une signature indiquant que le nom du fichier long
 *        a été trouvé durant une opération de recherche par nom.
 */

#define K_MK_FAT_ENTRY_FOUND 0

/**
 * @def K_MK_FAT_CREATE_CLUSTER_CHAIN
 * @brief Définition d'un identifiant permettant d'ajouter une nouvelle
 *        chaine de clusters à un répertoire.
 */

#define K_MK_FAT_CREATE_CLUSTER_CHAIN 0

/**
 *
 */

/**
 * @def K_MK_FAT_VALID_CLUSTER
 * @brief Définition de la plage de validité haute d'un cluster alloué.
 */

#define K_MK_FAT_VALID_CLUSTER 0x0FFFFFF7

/**
 * @def K_MK_FAT_LAST_CLUSTER
 * @brief Définition de la signature indiquant que le cluster est le
 *        dernier cluster du fichier.
 */

#define K_MK_FAT_LAST_CLUSTER 0x0FFFFFF8

/**
 * @def K_MK_FAT_FREE_CLUSTER
 * @brief Définition de la signature indiquant que le cluster est
 *        disponible.
 */

#define K_MK_FAT_FREE_CLUSTER 0x00000000

/**
 * @def K_MK_FAT_CLUSTER_MASK
 * @brief Définition de la valeur du masque utilisé pour récupérer
 *        la valeur d'un cluster.
 */

#define K_MK_FAT_CLUSTER_MASK 0x0FFFFFFF

/**
 *
 */

/**
 * @def K_MK_FAT_MAX_FILE_SIZE
 * @brief Définition de la taille maximale d'un fichier [en octets].
 */

#define K_MK_FAT_MAX_FILE_SIZE 0xFFFFFFFF

/**
 *
 */

#endif
