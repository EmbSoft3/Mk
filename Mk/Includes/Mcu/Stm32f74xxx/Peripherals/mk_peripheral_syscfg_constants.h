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
* @file mk_peripheral_syscfg_constants.h
* @brief Déclaration des constantes dédiées au périphérique SYSCFG.
* @date 26 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_SYSCFG_CONSTANTS_H
#define MK_PERIPHERAL_SYSCFG_CONSTANTS_H

/**
 * @def K_SYSCFG_MEMRMP
 * @brief Adresse du registre SYSCFG_MEMRMP.
 */

#define K_SYSCFG_MEMRMP ( addr_t ) 0x40013800

/**
 * @def K_SYSCFG_EXTICR
 * @brief Adresse du registre SYSCFG_EXTICR.
 */

#define K_SYSCFG_EXTICR ( addr_t ) 0x40013808

/**
 * @def K_SYSCFG_CMPCR
 * @brief Adresse du registre SYSCFG_CMPCR.
 */

#define K_SYSCFG_CMPCR ( addr_t ) 0x40013820

/**
 *
 */

/**
 * @def K_SYSCFG_BANK_SWAP_DISABLE
 * @brief Constante dédiée à la fonction syscfg_swapBank(). \n
 *        Désactivation du mécanisme de permutation des bank 1 et 2
 *        de la mémoire SDRAM. Elles utilisent respectivement les adresses
 *        0xC0000000 et 0xD0000000.
 */

#define K_SYSCFG_BANK_SWAP_DISABLE 0x00000000

/**
 * @def K_SYSCFG_BANK_SWAP_ENABLE
 * @brief Constante dédiée à la fonction syscfg_swapBank(). \n
 *        Activation du mécanisme de permutation des bank 1 et 2
 *        de la mémoire SDRAM. Elles utilisent respectivement les adresses
 *        0x60000000 et 0x70000000.
 */

#define K_SYSCFG_BANK_SWAP_ENABLE 0x00000400

/**
 *
 */

/**
 * @def K_SYSCFG_PORTA
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PA[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTA 0x00000000

/**
 * @def K_SYSCFG_PORTB
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PB[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTB 0x00000001

/**
 * @def K_SYSCFG_PORTC
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PC[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTC 0x00000002

/**
 * @def K_SYSCFG_PORTD
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PD[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTD 0x00000003

/**
 * @def K_SYSCFG_PORTE
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PE[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTE 0x00000004

/**
 * @def K_SYSCFG_PORTF
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PF[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTF 0x00000005

/**
 * @def K_SYSCFG_PORTG
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PG[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTG 0x00000006

/**
 * @def K_SYSCFG_PORTH
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PH[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTH 0x00000007

/**
 * @def K_SYSCFG_PORTI
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PI[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTI 0x00000008

/**
 * @def K_SYSCFG_PORTJ
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PJ[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTJ 0x00000009

/**
 * @def K_SYSCFG_PORTK
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition d'une constante permettant de relier le port PK[x]
 *        sur une ligne d'interruption externe.
 */

#define K_SYSCFG_PORTK 0x0000000A

/**
 *
 */

/**
 * @def K_SYSCFG_EXTI0
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI0.
 */

#define K_SYSCFG_EXTI0 0x00000000

/**
 * @def K_SYSCFG_EXTI1
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI1.
 */

#define K_SYSCFG_EXTI1 0x00000004

/**
 * @def K_SYSCFG_EXTI2
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI2.
 */

#define K_SYSCFG_EXTI2 0x00000008

/**
 * @def K_SYSCFG_EXTI3
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI3.
 */

#define K_SYSCFG_EXTI3 0x0000000C

/**
 * @def K_SYSCFG_EXTI4
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI4.
 */

#define K_SYSCFG_EXTI4 0x00000020

/**
 * @def K_SYSCFG_EXTI5
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI5.
 */

#define K_SYSCFG_EXTI5 0x00000024

/**
 * @def K_SYSCFG_EXTI6
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI6.
 */

#define K_SYSCFG_EXTI6 0x00000028

/**
 * @def K_SYSCFG_EXTI7
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI7.
 */

#define K_SYSCFG_EXTI7 0x0000002C

/**
 * @def K_SYSCFG_EXTI8
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI8.
 */

#define K_SYSCFG_EXTI8 0x00000040

/**
 * @def K_SYSCFG_EXTI9
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI9.
 */

#define K_SYSCFG_EXTI9 0x00000044

/**
 * @def K_SYSCFG_EXTI10
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI10.
 */

#define K_SYSCFG_EXTI10 0x00000048

/**
 * @def K_SYSCFG_EXTI11
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI11.
 */

#define K_SYSCFG_EXTI11 0x0000004C

/**
 * @def K_SYSCFG_EXTI12
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI12.
 */

#define K_SYSCFG_EXTI12 0x00000060

/**
 * @def K_SYSCFG_EXTI13
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI13.
 */

#define K_SYSCFG_EXTI13 0x00000064

/**
 * @def K_SYSCFG_EXTI14
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI14.
 */

#define K_SYSCFG_EXTI14 0x00000068

/**
 * @def K_SYSCFG_EXTI15
 * @brief Constante dédiée à la fonction syscfg_setMultiplexer(). \n
 *        Définition de l'identifiant de la ligne d'interruption EXTI15.
 */

#define K_SYSCFG_EXTI15 0x0000006C

/**
 *
 */

/**
 * @def K_SYSCFG_COMPENSATION_ENABLE
 * @brief Constante dédiée à la fonction syscfg_enableCompensation(). \n
 *        Activation de la compensation de cellule.
 */

#define K_SYSCFG_COMPENSATION_ENABLE 0x00000001

/**
 * @def K_SYSCFG_COMPENSATION_DISABLE
 * @brief Constante dédiée à la fonction syscfg_enableCompensation(). \n
 *        Désactivation de la compensation de cellule.
 */

#define K_SYSCFG_COMPENSATION_DISABLE 0x00000000

/**
 * @def K_SYSCFG_COMPENSATION_ENABLED
 * @brief Constante dédiée à la fonction syscfg_enableCompensation(). \n
 *        Définition de la valeur indiquant que le mécanisme de compensation
 *        de cellule est activée.
 */

#define K_SYSCFG_COMPENSATION_ENABLED 0x00000001

/**
 * @def K_SYSCFG_COMPENSATION_DISABLED
 * @brief Constante dédiée à la fonction syscfg_enableCompensation(). \n
 *        Définition de la valeur indiquant que le mécanisme de compensation
 *        de cellule est désactivée.
 */

#define K_SYSCFG_COMPENSATION_DISABLED 0x00000000

/**
 * @def K_SYSCFG_COMPENSATION_TIMEOUT
 * @brief Définition de la valeur du timeout utilisée lors de l'activation ou
 *        la désactivation du mécanisme de compensation de cellules.
 */

#define K_SYSCFG_COMPENSATION_TIMEOUT 0x00000200

/**
 *
 */

#endif

