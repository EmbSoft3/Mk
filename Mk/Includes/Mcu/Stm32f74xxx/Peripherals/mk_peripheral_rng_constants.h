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
* @file mk_peripheral_rng_constants.h
* @brief Déclaration des constantes dédiées au périphérique RNG.
* @date 30 mai 2020
*
*/

#ifndef MK_PERIPHERAL_RNG_CONSTANTS_H
#define MK_PERIPHERAL_RNG_CONSTANTS_H

/**
 * @def K_RNG_CR
 * @brief Adresse du registre RNG_CR.
 */

#define K_RNG_CR ( addr_t ) 0x50060800

/**
 * @def K_RNG_SR
 * @brief Adresse du registre RNG_SR.
 */

#define K_RNG_SR ( addr_t ) 0x50060804

/**
 * @def K_RNG_DR
 * @brief Adresse du registre RNG_DCR.
 */

#define K_RNG_DR ( addr_t ) 0x50060808

/**
 *
 */

/**
 * @def K_RNG_SEED_ERROR_INTERRUPT_STATUS
 * @brief Constante dédiée aux fonctions rng_getStatus() et rng_clearStatus(). \n
 *        Définition de la position du drapeau SEED_ERROR_INTERRUPT_STATUS.
 */

#define K_RNG_SEED_ERROR_INTERRUPT_STATUS 0x00000040

/**
 * @def K_RNG_CLOCK_ERROR_INTERRUPT_STATUS
 * @brief Constante dédiée aux fonctions rng_getStatus() et rng_clearStatus(). \n
 *        Définition de la position du drapeau CLOCK_ERROR_INTERRUPT_STATUS.
 */

#define K_RNG_CLOCK_ERROR_INTERRUPT_STATUS 0x00000020

/**
 * @def K_RNG_SEED_ERROR_CURRENT_STATUS
 * @brief Constante dédiée à la fonction rng_getStatus(). \n
 *        Définition de la position du drapeau SEED_ERROR_CURRENT_STATUS.
 */

#define K_RNG_SEED_ERROR_CURRENT_STATUS 0x00000004

/**
 * @def K_RNG_CLOCK_ERROR_CURRENT_STATUS
 * @brief Constante dédiée à la fonction rng_getStatus(). \n
 *        Définition de la position du drapeau CLOCK_ERROR_CURRENT_STATUS.
 */

#define K_RNG_CLOCK_ERROR_CURRENT_STATUS 0x00000002

/**
 * @def K_RNG_READY_STATUS
 * @brief Constante dédiée à la fonction rng_getStatus(). \n
 *        Définition de la position du drapeau K_RNG_READY_STATUS.
 */

#define K_RNG_READY_STATUS 0x00000001

/**
 *
 */

#endif

