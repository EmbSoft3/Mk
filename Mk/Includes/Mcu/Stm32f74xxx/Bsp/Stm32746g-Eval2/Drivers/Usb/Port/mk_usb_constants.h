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
* @file mk_usb_constants.h
* @brief Déclarations des constantes du module USB.
* @date 18 juil. 2019
*
*/

#ifndef MK_USB_CONSTANTS_H
#define MK_USB_CONSTANTS_H

/**
 * @def K_MK_USBHS_DEVICE_STACK_SIZE
 * @brief Définition de la taille de stack du terminal USBHS_DEVICE [en multiple de mots 32bits].
 */

#define K_MK_USBHS_DEVICE_STACK_SIZE 256

/**
 * @def K_MK_USBFS_DEVICE_STACK_SIZE
 * @brief Définition de la taille de stack du terminal USBFS_DEVICE [en multiple de mots 32bits].
 */

#define K_MK_USBFS_DEVICE_STACK_SIZE 256

/**
 * @def K_MK_USBHS_HOST_STACK_SIZE
 * @brief Définition de la taille de stack du terminal USBHS_HOST [en multiple de mots 32bits].
 */

#define K_MK_USBHS_HOST_STACK_SIZE 512

/**
 * @def K_MK_USBFS_HOST_STACK_SIZE
 * @brief Définition de la taille de stack du terminal USBFS_HOST [en multiple de mots 32bits].
 */

#define K_MK_USBFS_HOST_STACK_SIZE 512

/**
 *
 */

/**
 * @def K_MK_USB_RESET_TIMEOUT
 * @brief Définition du nombre de tentatives réalisées par le logiciel lorsqu'il
 *        vérifie que le coeur USB a été réinitialisé. Chaque tentative est espacée de
 *        2 ms.
 */

#define K_MK_USB_RESET_TIMEOUT 250

/**
 * @def K_MK_USB_BUSY_TIMEOUT
 * @brief Définition du nombre de tentatives réalisées par le logiciel lorsqu'il
 *        vérifie que le coeur USB est au repos. Chaque tentative est espacée de
 *        2 ms.
 */

#define K_MK_USB_BUSY_TIMEOUT 50

/**
 * @def K_MK_USB_FIFO_TIMEOUT
 * @brief Définition du nombre de tentatives réalisées par le logiciel lorsqu'il
 *        vérifie que les FIFOs ont été réinitialisés. Chaque tentative est espacée de
 *        2 ms.
 */

#define K_MK_USB_FIFO_TIMEOUT 50

/**
 * @def K_MK_USB_RXFIFO_SIZE
 * @brief Définition de la taille du FIFO de réception USB [en multiple de mots 32 bits].
 */

#define K_MK_USB_RXFIFO_SIZE 512

/**
 * @def K_MK_USB_TXFIFO_SIZE
 * @brief Définition de la taille des FIFO de transmission USB [en multiple de mots 32 bits].
 */

#define K_MK_USB_TXFIFO_SIZE 256

/**
 * @def K_MK_USB_OTGHS_CHANNEL_NUMBER
 * @brief Définition du nombre de canal de communication dédié au périphériphérique
 *        USB_OTGHS.
 */

#define K_MK_USB_OTGHS_CHANNEL_NUMBER 16

/**
 * @def K_MK_USB_OTGFS_CHANNEL_NUMBER
 * @brief Définition du nombre de canal de communication dédié au périphériphérique
 *        USB_OTGFS.
 */

#define K_MK_USB_OTGFS_CHANNEL_NUMBER 12

/**
 * @def K_MK_USB_CHANNEL_NUMBER
 * @brief Définition du nombre maximal de canal de communication.
 */

#define K_MK_USB_CHANNEL_NUMBER K_MK_USB_OTGHS_CHANNEL_NUMBER

/**
 * @def K_MK_HCD_MAX_NUMBER_OF_PACKETS
 * @brief Définition du nombre maximal de paquets supportés par le périphérique USB.
 */

#define K_MK_HCD_MAX_NUMBER_OF_PACKETS 1023

/**
 * @def K_MK_USB_DEFAULT_MAX_PACKET_SIZE
 * @brief Définition de la taille maximal d'un paquet [en octets].
 */

#define K_MK_USB_DEFAULT_MAX_PACKET_SIZE 64

/**
 * @def K_MK_USB_RESET_TICK
 * @brief Définition de la durée d'un reset sur un port USB [en multiple de tick].
 */

#define K_MK_USB_RESET_TICK 55

/**
 * @def K_MK_USB_MAX_RESET_TICK
 * @brief Définition de la durée maximal d'un reset sur un port USB [en multiple de tick].
 *        La durée modulée du reset ne peut pas dépasser la valeur \ref K_MK_USB_MAX_RESET_TICK.
 */

#define K_MK_USB_MAX_RESET_TICK 5000

/**
 *
 */

#endif


