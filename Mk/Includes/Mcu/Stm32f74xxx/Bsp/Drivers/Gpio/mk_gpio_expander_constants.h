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
* @file mk_gpio_expander_constants.h
* @brief Déclaration des constantes dédiées au périphérique MFX.
* @date 20 déc. 2020
*
*/

#ifndef MK_GPIO_EXPANDER_CONSTANTS_H
#define MK_GPIO_EXPANDER_CONSTANTS_H

/**
 * @def MK_GPIO_EXPANDER_ADDR
 * @brief Définition de l'adresse I2C du périphérique MFX.
 */

#define MK_GPIO_EXPANDER_ADDR 0x42

/**
 * @def MK_GPIO_EXPANDER_TIMEOUT
 * @brief Définition de la durée [en ms] du timeout de communication avec le périphérique MFX.
 */

#define MK_GPIO_EXPANDER_TIMEOUT 0x08

/**
 * @def MK_GPIO_EXPANDER_NUMBER_OF_PINS
 * @brief Définition du nombre de broches d'entrées-sorties du périphérique MFX.
 */

#define MK_GPIO_EXPANDER_NUMBER_OF_PINS 24

/**
 *
 */

/**
 * @def MK_GPIO_EXPANDER_SYSCTRL_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de contrôle du périphérique MFX.
 */

#define MK_GPIO_EXPANDER_SYSCTRL_REGISTER_ADDR 0x40

/**
 * @def MK_GPIO_EXPANDER_SYSCTRL_SOFTWARE_RESET
 * @brief Définition de l'offset du bit RESET dans le registre de contrôle.
 */

#define MK_GPIO_EXPANDER_SYSCTRL_SOFTWARE_RESET 0x80

/**
 * @def MK_GPIO_EXPANDER_SYSCTRL_ENABLE_ALTERNATE_GPIO
 * @brief Définition de l'offset du bit ALT_GPIO dans le registre de contrôle.
 */

#define MK_GPIO_EXPANDER_SYSCTRL_ENABLE_ALTERNATE_GPIO 0x08

/**
 * @def MK_GPIO_EXPANDER_SYSCTRL_ENABLE_GPIO
 * @brief Définition de l'offset du bit EN_GPIO dans le registre de contrôle.
 */

#define MK_GPIO_EXPANDER_SYSCTRL_ENABLE_GPIO 0x01

/**
 *
 */

/**
 * @def MK_GPIO_EXPANDER_DIRECTION_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de direction du périphérique MFX.
 *        \li '0' = Input.
 *        \li '1' = Output.
 */

#define MK_GPIO_EXPANDER_DIRECTION_REGISTER_ADDR 0x60

/**
 * @def MK_GPIO_EXPANDER_TYPE_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de configuration du périphérique MFX.
 *        \li output : '0' = sortie push-pull,            '1' = sortie open-drain.
 *        \li input  : '0' = pas de résistance de tirage, '1' = résistance de tirage.
 */

#define MK_GPIO_EXPANDER_TYPE_REGISTER_ADDR 0x64

/**
 * @def MK_GPIO_EXPANDER_PULL_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de configuration des résistances de
 *        tirage du périphérique MFX.
 *        \li '0' = Pulldown.
 *        \li '1' = Pullup.
 */

#define MK_GPIO_EXPANDER_PULL_REGISTER_ADDR 0x68

/**
 * @def MK_GPIO_EXPANDER_SET_REGISTER_ADDR
 * @brief Définition de l'adresse du registre d'activation des broches de sorties
 *        du périphérique MFX.
 *        \li '0' = Pas d'effet.
 *        \li '1' = Niveau haut.
 */

#define MK_GPIO_EXPANDER_SET_REGISTER_ADDR 0x6C

/**
 * @def MK_GPIO_EXPANDER_CLEAR_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de désactivation des broches de sorties
 *        du périphérique MFX.
 *        \li '0' = Pas d'effet.
 *        \li '1' = Niveau bas.
 */

#define MK_GPIO_EXPANDER_CLEAR_REGISTER_ADDR 0x70

/**
 * @def MK_GPIO_EXPANDER_GET_REGISTER_ADDR
 * @brief Définition de l'adresse du registre de lecture des broches d'entrées du
 *        périphérique MFX.
 *        \li '0' = L'entrée est au niveau bas.
 *        \li '1' = L'entrée est au haut.
 */

#define MK_GPIO_EXPANDER_GET_REGISTER_ADDR 0x10

/**
 *
 */

#endif

