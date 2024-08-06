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
* @file mk_supervisor_constants.h
* @brief Déclaration des constantes dédiées au superviseur.
* @date 4 janv. 2023
*
*/

#ifndef MK_SUPERVISOR_CONSTANTS_H
#define MK_SUPERVISOR_CONSTANTS_H

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_TASK_PRIORITY
 * @brief Définition de la priorité du superviseur.
 */

#define K_MK_SUPERVISOR_TASK_PRIORITY 9

/**
 * @def K_MK_SUPERVISOR_APPLICATION_STACK_SIZE
 * @brief Définition de la taille de la stack du superviseur [en multiple de mots 32bits].
 */

#define K_MK_SUPERVISOR_APPLICATION_STACK_SIZE 512

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_MESSAGE_NUMBER
 * @brief Définition du nombre maximal de messages dans la messagerie du superviseur.
 */

#define K_MK_SUPERVISOR_MESSAGE_NUMBER 4

/**
 * @def K_MK_SUPERVISOR_MESSAGE_SIZE
 * @brief Définition de la taille d'un message [en multiple de mots 32bits].
 */

#define K_MK_SUPERVISOR_MESSAGE_SIZE 155

/**
 * @def K_MK_SUPERVISOR_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie du superviseur [en multiple de mots 32bits].
 */

#define K_MK_SUPERVISOR_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_SUPERVISOR_MESSAGE_SIZE ) * K_MK_SUPERVISOR_MESSAGE_NUMBER )

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_PATH
 * @brief Définition du chemin où les fichiers du superviseur sont stockés.
 * @warning La taille des buffers doit être actualisée si le chemin est modifié.
 */

#define K_MK_SUPERVISOR_PATH "mk/supervisor/"

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_SIZE
 * @brief Définition de la taille du buffer dédié à la fenêtre d'affichage de la console
 *        du superviseur [en octets].
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_SIZE 16384

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_SIZE
 * @brief Définition de la taille du buffer dédié à la boite de saisie de la console
 *        du superviseur [en octets].
 * @warning La taille de ce buffer doit être en adéquation avec la taille
 *          des buffers utilisés dans le gestionnaire de commandes (shell).
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_SIZE 16384

/**
 * @def K_MK_SUPERVISOR_CONSOLE_REPORT_SIZE
 * @brief Définition de la taille du buffer permettant la création d'un rapport
 *        d'erreur [en octets].
 */

#define K_MK_SUPERVISOR_CONSOLE_REPORT_SIZE 262144

/**
 * @def K_MK_SUPERVISOR_REPORT_NUMBEROFBYTES_TO_WRITE
 * @brief Définition de la taille des requêtes d'enregistrement effectuées
 *        lors de l'édition d'un rapport d'erreur.
 */

#define K_MK_SUPERVISOR_REPORT_NUMBEROFBYTES_TO_WRITE 65536

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_X
 * @brief Définition de la position X de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_Y
 * @brief Définition de la position Y de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_Y 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH
 * @brief Définition de la largeur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH 629

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT
 * @brief Définition de la hauteur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT 436

/**
 * @def K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE
 * @brief Définition de la taille du cache de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE ( 4 * K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH * K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT )

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_X
 * @brief Définition de la position X du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_Y
 * @brief Définition de la position Y du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_Y 447

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH
 * @brief Définition de la largeur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH 629

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT
 * @brief Définition de la hauteur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT 30

/**
 *
 */

#endif

