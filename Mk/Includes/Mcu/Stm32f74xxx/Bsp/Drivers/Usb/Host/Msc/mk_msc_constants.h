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
* @file mk_msc_constants.h
* @brief Déclaration des constantes dédiées aux périphériques de stockage.
* @date 16 mai 2020
*
*/

#ifndef MK_MSC_CONSTANTS_H
#define MK_MSC_CONSTANTS_H

/**
 * @def K_MK_MSC_STACK_SIZE
 * @brief Définition de la taille de la stack du terminal MSC [en multiple de mots 32bits].
 */

#define K_MK_MSC_STACK_SIZE 500

/**
 * @def K_MK_MSC_MAX_PACKET_SIZE
 * @brief Définition de taille du buffer de données du terminal MSC.
 */

#define K_MK_MSC_MAX_PACKET_SIZE 1024

/**
 * @def K_MK_MSC_MAX_LUN
 * @brief Définition du nombre maximal d'unité logique (Logical Unit Number).
 */

#define K_MK_MSC_MAX_LUN 0x10

/**
 *
 */

/**
 * @def K_MK_MSC_REFRESH_TIMEOUT
 * @brief Définition du timeout de rafraichissement des périphériques MSC [en multiple de tick].
 */

#define K_MK_MSC_REFRESH_TIMEOUT 100

/**
 * @def K_MK_MSC_MAX_DEVICE_NUMBER
 * @brief Définition du nombre maximal de périphériques MSC (\ref T_mkMSCDevice) pouvant être alloués.
 * @note Cette constante peut être modifée par l'utilisateur.
 */

#define K_MK_MSC_MAX_DEVICE_NUMBER ( K_MK_HCD_MAX_DEVICE_NUMBER >> 1 )

/**
 *
 */

/**
 * @def K_MK_MSC_MESSAGE_SIZE
 * @brief Définition de la taille d'un message MSC [en multiple de mots 32 bits].
 */

#define K_MK_MSC_MESSAGE_SIZE 2

/**
 * @def K_MK_MSC_MESSAGE_AREA_SIZE
 * @brief Définition de la taille de la messagerie MSC [en multiple de mots 32bits].
 */

#define K_MK_MSC_MESSAGE_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_MSC_MESSAGE_SIZE ) * K_MK_HCD_MAX_DEVICE_NUMBER )

/**
 *
 */

#endif

