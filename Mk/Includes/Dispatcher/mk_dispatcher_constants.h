/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_dispatcher_constants.h
* @brief Déclaration des constantes dédiées au dispatcher.
* @date 17 nov. 2019
*
*/

#ifndef MK_DISPATCHER_CONSTANTS_H
#define MK_DISPATCHER_CONSTANTS_H

/**
 * @def K_MK_DISPATCHER_STACK_SIZE
 * @brief Définition de la taille de la stack du dispatcher [en multiple de mots 32bits].
 */

#define K_MK_DISPATCHER_STACK_SIZE 256

/**
 * @def K_MK_TERMIO_DISPATCHER_PRIORITY
 * @brief Définition de la priorité du dispatcher.
 */

#define K_MK_TERMIO_DISPATCHER_PRIORITY 3

/**
 *
 */

/**
 * @def K_MK_DISPATCHER_MESSAGE_NUMBER
 * @brief Définition du nombre maximal de messages dans la messagerie du dispatcher.
 */

#define K_MK_DISPATCHER_MESSAGE_NUMBER 8

/**
 * @def K_MK_DISPATCHER_INCOMING_MESSAGE_SIZE
 * @brief Définition de la taille (en multiple de mots 32bits) d'un message entrant (terminal vers dispatcher).
 */

#define K_MK_DISPATCHER_INCOMING_MESSAGE_SIZE 4

/**
 * @def K_MK_DISPATCHER_LISTENER_MESSAGE_SIZE
 * @brief Définition de la taille (en multiple de mots 32bits) d'un message sortant (dispatcher vers tâche d'écoute).
 */

#define K_MK_DISPATCHER_LISTENER_MESSAGE_SIZE 4

/**
 * @def K_MK_DISPATCHER_INCOMING_MESSAGE_SIZE
 * @brief Définition de la taille (en multiple de mots 32bits) d'un message HID (dispatcher vers terminal HID).
 */

#define K_MK_DISPATCHER_HID_MESSAGE_SIZE 4

/**
 *
 */

/**
 * @def K_MK_DISPATCHER_INCOMING_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie entrante [en multiple de mots 32bits].
 */

#define K_MK_DISPATCHER_INCOMING_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_DISPATCHER_INCOMING_MESSAGE_SIZE ) * K_MK_DISPATCHER_MESSAGE_NUMBER )

/**
 * @def K_MK_DISPATCHER_LISTENER_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie sortante [en multiple de mots 32bits].
 */

#define K_MK_DISPATCHER_LISTENER_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_DISPATCHER_LISTENER_MESSAGE_SIZE ) * K_MK_DISPATCHER_MESSAGE_NUMBER )

/**
 * @def K_MK_DISPATCHER_INCOMING_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie HID [en multiple de mots 32bits].
 */

#define K_MK_DISPATCHER_HID_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_DISPATCHER_HID_MESSAGE_SIZE ) * K_MK_DISPATCHER_MESSAGE_NUMBER )

/**
 *
 */

#endif

