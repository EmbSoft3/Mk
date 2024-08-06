/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_usart_constants.h
* @brief Déclaration des constantes dédiées au périphérique USART.
* @date 1 avr. 2018
* @todo Implémenter et écrire la documentation du périphérique USART.
*
*/

#ifndef MK_PERIPHERAL_USART_CONSTANTS_H
#define MK_PERIPHERAL_USART_CONSTANTS_H

/**
 * @def K_USART1
 * @brief Adresse de base du périphérique K_USART1.
 */

#define K_USART1 ( addr_t ) 0x40011000

/**
 * @def K_USART2
 * @brief Adresse de base du périphérique K_USART2.
 */

#define K_USART2 ( addr_t ) 0x40004400

/**
 * @def K_USART3
 * @brief Adresse de base du périphérique K_USART3.
 */

#define K_USART3 ( addr_t ) 0x40004800

/**
 * @def K_UART4
 * @brief Adresse de base du périphérique K_UART4.
 */

#define K_UART4 ( addr_t ) 0x40004C00

/**
 * @def K_UART5
 * @brief Adresse de base du périphérique K_UART5.
 */

#define K_UART5 ( addr_t ) 0x40005000

/**
 * @def K_USART6
 * @brief Adresse de base du périphérique K_USART6.
 */

#define K_USART6 ( addr_t ) 0x40011400

/**
 * @def K_UART7
 * @brief Adresse de base du périphérique K_UART7.
 */

#define K_UART7 ( addr_t ) 0x40007800

/**
 * @def K_UART8
 * @brief Adresse de base du périphérique K_UART8.
 */

#define K_UART8 ( addr_t ) 0x40007C00

/**
 *
 */

/**
 * @def K_USART_PARITY_EVEN
 * @brief Constante dédiée à la fonction usart_setParity().\n
 *        Configuration d'une parité paire.
 */

#define K_USART_PARITY_EVEN 0x00000000

/**
 * @def K_USART_PARITY_ODD
 * @brief Constante dédiée à la fonction usart_setParity().\n
 *        Configuration d'une parité impaire.
 */

#define K_USART_PARITY_ODD 0x00000200

/**
 * @def K_USART_FRAME_7BITS
 * @brief Constante dédiée à la fonction usart_setFrame().\n
 *        Configuration de la taille des données sur 7 bits.
 */

#define K_USART_FRAME_7BITS 0x10000000

/**
 * @def K_USART_FRAME_8BITS
 * @brief Constante dédiée à la fonction usart_setFrame().\n
 *        Configuration de la taille des données sur 8 bits.
 */

#define K_USART_FRAME_8BITS 0x00000000

/**
 * @def K_USART_FRAME_9BITS
 * @brief Constante dédiée à la fonction usart_setFrame().\n
 *        Configuration de la taille des données sur 9 bits.
 */

#define K_USART_FRAME_9BITS 0x00001000

/**
 * @def K_USART_FLOW_LSB_FIRST
 * @brief Constante dédiée à la fonction usart_setFlow().\n
 *        Transmission du bit de poids faible (LSB) en premier
 *        sur le bus.
 */

#define K_USART_FLOW_LSB_FIRST 0x00000000

/**
 * @def K_USART_FLOW_MSB_FIRST
 * @brief Constante dédiée à la fonction usart_setFlow().\n
 *        Transmission du bit de poids fort (MSB) en premier
 *        sur le bus.
 */

#define K_USART_FLOW_MSB_FIRST 0x00080000

/**
 *
 */

#endif


