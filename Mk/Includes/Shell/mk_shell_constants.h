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
* @file mk_shell_constants.h
* @brief Déclaration des constantes dédiées au shell.
* @date 11 nov. 2023
*
*/

#ifndef MK_SHELL_CONSTANTS_H
#define MK_SHELL_CONSTANTS_H


/**
 * @def K_MK_SHELL_NUMBER
 * @brief Définition du nombre de gestionnaires de commandes.
 *        Conserver cette constante à la valeur 1 pour supporter les commandes à phase multiples.
 */

#define K_MK_SHELL_NUMBER 1

/**
 * @def K_MK_SHELL_TASK_PRIORITY
 * @brief Définition de la priorité des gestionnaires de commandes.
 */

#define K_MK_SHELL_TASK_PRIORITY 2

/**
 * @def K_MK_SHELL_STACK_SIZE
 * @brief Définition de la taille de la stack des gestionnaires de commandes [en multiple de mots 32bits].
 */

#define K_MK_SHELL_STACK_SIZE 500

/**
 *
 */

/**
 * @def K_MK_SHELL_MESSAGE_NUMBER
 * @brief Définition du nombre maximal de messages dans la messagerie des gestionnaires de commandes.
 */

#define K_MK_SHELL_MESSAGE_NUMBER 8

/**
 * @def K_MK_SHELL_INCOMING_MESSAGE_SIZE
 * @brief Définition de la taille d'un message [en multiple de mots 32bits].
 */

#define K_MK_SHELL_INCOMING_MESSAGE_SIZE ( sizeof ( T_mkShellMessage ) >> 2 )

/**
 * @def K_MK_SHELL_INCOMING_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie des gestionnaires de commandes [en multiple de mots 32bits].
 */

#define K_MK_SHELL_INCOMING_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_SHELL_INCOMING_MESSAGE_SIZE ) * K_MK_SHELL_MESSAGE_NUMBER )

/**
 *
 */

/**
 * @def K_MK_SHELL_PATH
 * @brief Définition du chemin où les fichiers des gestionnaires de commandes sont stockés.
 * @warning La taille des buffers doit être actualisée si le chemin est modifié.
 */

#define K_MK_SHELL_PATH ( T_str8 ) "mk/tmp/"

/**
 * @def K_MK_SHELL_EXTERNAL_COMMAND_PATH
 * @brief Définition du chemin où les commandes externes du système sont stockées.
 * @warning La taille des buffers doit être actualisée si le chemin est modifié.
 */

#define K_MK_SHELL_EXTERNAL_COMMAND_PATH ( T_str8 ) "mk/shell"

/**
 * @def K_MK_SHELL_FILE_NAME_LENGTH
 * @brief Définition de la longueur des noms de fichiers des gestionnaire de commandes.
 * @warning La taille des buffers doit être actualisée si la longueur est modifiée.
 */

#define K_MK_SHELL_FILE_NAME_LENGTH 32

/**
 *
 */

#endif

