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
* @file mk_peripheral_syscfg.h
* @brief Déclaration des fonctions dédiées au périphérique SYSCFG.
* @date 26 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_SYSCFG_H
#define MK_PERIPHERAL_SYSCFG_H

/**
 * @fn void syscfg_swapBank ( uint32_t p_mode );
 * @brief Cette fonction permet de permuter l'adresse des bank 1 et 2 des mémoires SDRAM avec les
 *        l'adresse des bank 1 et 2 des mémoire NOR/PSRAM.
 * @param[in] p_mode Ce paramètre indique si la permutation doit être effectuée ou non. Les constantes suivantes peuvent
 *                   être utilisées :
 *                   \ref K_SYSCFG_BANK_SWAP_DISABLE et \ref K_SYSCFG_BANK_SWAP_ENABLE
 *
 * @return Sans objet.
 *
 */

void syscfg_swapBank ( uint32_t p_mode );

/**
 * @fn void syscfg_setMultiplexer ( uint32_t p_line, uint32_t p_port );
 * @brief Cette fonction relie une ligne d'interruption à une broche GPIO.
 *
 * @param[in] p_line Ce paramètre contient l'identifiant de la ligne d'interruption à configurer. Une des constantes
 *                   suivantes peut être utilisée :
 *                   \ref K_SYSCFG_EXTI0 à \ref K_SYSCFG_EXTI15
 * @param[in] p_port Ce paramètre contient l'identifiant de la broche GPIO. Une des constantes suivantes peut être
 *                   utilisée :
 *                   \ref K_SYSCFG_PORTA à \ref K_SYSCFG_PORTK
 *
 * @note Le multiplexage est réalisé de la manière suivante : \n
 *       EXTI0 -> PORTA<0> à PORTK<0> ; EXTI1 -> PORTA<1> à PORTK<1>, ... , EXTI15 -> PORTA<15> à PORTK<15>.
 * @return Sans objet.
 *
 */

void syscfg_setMultiplexer ( uint32_t p_line, uint32_t p_port );

/**
 * @fn uint32_t syscfg_cellCompensation ( uint32_t p_mode, uint32_t p_timeout );
 * @brief Cette fonction active ou désactive la compensation de cellules nécessaire aux broches hautes vitesse.
 *        Une broche est considérée en haute vitesse si elle travaille entre 50 et 100MHz.
 *
 * @param[in] p_mode Ce paramètre reprèsente l'état du module de compensation de cellules. Les constantes suivantes
 *                   peuvent être utilisées : \n
 *                   \ref K_SYSCFG_COMPENSATION_ENABLE et \ref K_SYSCFG_COMPENSATION_DISABLE
 * @param[in] p_timeout Ce paramètre contient le timeout maximal. Il est exprimé en multiple de 100µs.
 *
 * @warning Cette fonction doit être utilisée uniquement si le microcontroleur est alimenté entre 2,4V et 3,6V.
 * @return Cette fonction retourne la valeur \ref K_SYSCFG_COMPENSATION_ENABLED si l'activation a réussi,
 *         sinon la valeur \ref K_SYSCFG_COMPENSATION_DISABLED.
 *
 */

uint32_t syscfg_cellCompensation ( uint32_t p_mode, uint32_t p_timeout );

/**
 *
 */

#endif

