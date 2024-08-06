/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_mmc_constants.h
* @brief Déclaration des constantes SD/MMC.
* @date 7 févr. 2021
*
*/

#ifndef MK_MMC_CONSTANTS_H
#define MK_MMC_CONSTANTS_H

/**
 * @def K_MK_MMC_STACK_SIZE
 * @brief Définition de la taille de la stack du terminal MMC [en multiple de mots 32bits].
 */

#define K_MK_MMC_STACK_SIZE 350

/**
 *
 */

/**
 * @def K_MK_MMC_CARD_PORT_NUMBER
 * @brief Définition de l'identifiant du registre de configuration GPIO de la broche SDCARD_DETECT.
 * @note La broche est connectée sur le périphérique MFX (0=K_MK_GPIO_EXPANDER).
 *       Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_MMC_CARD_PORT_NUMBER 0

/**
 * @def K_MK_MMC_CARD_PIN_NUMBER
 * @brief Définition de l'offset du bit SDCARD_DETECT dans le registre de configuration GPIO.
 * @note Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_MMC_CARD_PIN_NUMBER 15

/**
 * @def K_MK_MMC_CARD_CONNECTED_STATE
 * @brief Définition de l'état logique indiquant qu'une carte SD/MMC est connectée.
 * @note Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_MMC_CARD_CONNECTED_STATE 0

/**
 *
 */

/**
 * @def K_MK_MMC_REFRESH_TIMEOUT
 * @brief Définition du timeout de rafraichissement du terminal MMC.
 */

#define K_MK_MMC_REFRESH_TIMEOUT 10

/**
 *
 */

#endif

