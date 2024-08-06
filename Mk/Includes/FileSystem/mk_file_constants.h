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
* @file mk_file_constants.h
* @brief Déclaration des constantes dédiées au système de fichiers.
* @date 26 déc. 2020
*
*/

#ifndef MK_FILE_CONSTANTS_H
#define MK_FILE_CONSTANTS_H

/**
 *
 */

/**
 * @def K_MK_FILE_STACK_SIZE
 * @brief Définition de la taille des stacks du système de fichiers [en multiple de mots 32bits].
 */

#define K_MK_FILE_STACK_SIZE 512

/**
 * @def K_MK_FILE_NUMBER_OF_TASKS
 * @brief Définition du nombre de tâches du systèmes de fichiers.
 * @note Au minimum 2 tâches (1 partagé et 1 non partagé)
 */

#define K_MK_FILE_NUMBER_OF_TASKS 4

/**
 *
 */

/**
 * @def K_MK_FILE_MIN_BLOCK_LENGTH
 * @brief Définition de la taille minimale d'un bloc de données.
 */

#define K_MK_FILE_MIN_BLOCK_LENGTH 512

/**
 * @def K_MK_FILE_MAX_BLOCK_LENGTH
 * @brief Définition de la taille maximale d'un bloc de données.
 */

#define K_MK_FILE_MAX_BLOCK_LENGTH 1024

/**
 * @def K_MK_FILE_MAX_BLOCK_LENGTH_SHIFT
 * @brief Définition de la taille maximale d'un bloc de données selon
 *        la formule suivante : \n
 *        K_MK_DISK_MAX_BLOCK_LENGTH = ( 1 << K_MK_FILE_MAX_BLOCK_LENGTH )
 */

#define K_MK_FILE_MAX_BLOCK_LENGTH_SHIFT 10

/**
 *
 */

/**
 * @def K_MK_FILE_CACHE_SIZE
 * @brief Définition de la taille des buffers constituant le cache [en octets].
 */

#define K_MK_FILE_CACHE_SIZE 2048

/**
 * @def K_MK_FILE_MAX_NAME_LENGTH
 * @brief Définition de la taille maximale de la chaine de caractères
 *        stockant le nom et le chemin d'un fichier.
 */

#define K_MK_FILE_MAX_NAME_LENGTH 255

/**
 *
 */

/**
 * @def K_MK_FILE_MESSAGE_SIZE
 * @brief Définition de la taille d'un message du système de fichiers [en multiple de mots 32 bits].
 */

#define K_MK_FILE_MESSAGE_SIZE 8

/**
 * @def K_MK_FILE_MESSAGE_NUMBER
 * @brief Définition du nombre maximal de messages dans la messagerie du système de fichiers.
 */

#define K_MK_FILE_MESSAGE_NUMBER 15

/**
 * @def K_MK_FILE_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie du système de fichiers.
 */

#define K_MK_FILE_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_FILE_MESSAGE_SIZE ) * K_MK_FILE_MESSAGE_NUMBER )

/**
 *
 */

#endif

