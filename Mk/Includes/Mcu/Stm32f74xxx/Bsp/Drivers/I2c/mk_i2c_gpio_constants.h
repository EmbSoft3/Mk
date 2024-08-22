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
* @file mk_i2c_gpio_constants.h
* @brief Déclaration des constantes dédiées aux broches GPIO des périphériques I2C.
* @date 28 nov. 2020
*
*/

#ifndef MK_I2C_GPIO_CONSTANTS_H
#define MK_I2C_GPIO_CONSTANTS_H

/**
 * @def K_MK_I2C1_GPIO_CLOCK_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SCL.
 */

#define K_MK_I2C1_GPIO_CLOCK_ADDR K_GPIOB

/**
 * @def K_MK_I2C1_GPIO_DATA_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SDA.
 */

#define K_MK_I2C1_GPIO_DATA_ADDR K_GPIOB

/**
 * @def K_MK_I2C1_GPIO_CLOCK_OFFSET
 * @brief Définition de l'offset du bit SCL dans le registre de configuration GPIO.
 */

#define K_MK_I2C1_GPIO_CLOCK_OFFSET 8

/**
 * @def K_MK_I2C1_GPIO_DATA_OFFSET
 * @brief Définition de l'offset du bit SDA dans le registre de configuration GPIO.
 */

#define K_MK_I2C1_GPIO_DATA_OFFSET 9

/**
 * @def K_MK_I2C1_GPIO_CLOCK_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SCL.
 */

#define K_MK_I2C1_GPIO_CLOCK_MULTIPLEXER K_GPIO_AF4

/**
 * @def K_MK_I2C1_GPIO_DATA_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SDA.
 */

#define K_MK_I2C1_GPIO_DATA_MULTIPLEXER K_GPIO_AF4

/**
 *
 */

/**
 * @def K_MK_I2C2_GPIO_CLOCK_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SCL.
 */

#define K_MK_I2C2_GPIO_CLOCK_ADDR K_GPIOB

/**
 * @def K_MK_I2C2_GPIO_DATA_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SDA.
 */

#define K_MK_I2C2_GPIO_DATA_ADDR K_GPIOB

/**
 * @def K_MK_I2C2_GPIO_CLOCK_OFFSET
 * @brief Définition de l'offset du bit SCL dans le registre de configuration GPIO.
 */

#define K_MK_I2C2_GPIO_CLOCK_OFFSET 10

/**
 * @def K_MK_I2C2_GPIO_DATA_OFFSET
 * @brief Définition de l'offset du bit SDA dans le registre de configuration GPIO.
 */

#define K_MK_I2C2_GPIO_DATA_OFFSET 11

/**
 * @def K_MK_I2C2_GPIO_CLOCK_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SCL.
 */

#define K_MK_I2C2_GPIO_CLOCK_MULTIPLEXER K_GPIO_AF4

/**
 * @def K_MK_I2C2_GPIO_DATA_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SDA.
 */

#define K_MK_I2C2_GPIO_DATA_MULTIPLEXER K_GPIO_AF4

/**
 *
 */

/**
 * @def K_MK_I2C3_GPIO_CLOCK_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SCL.
 */

#define K_MK_I2C3_GPIO_CLOCK_ADDR K_GPIOH

/**
 * @def K_MK_I2C3_GPIO_DATA_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SDA.
 */

#define K_MK_I2C3_GPIO_DATA_ADDR K_GPIOH

/**
 * @def K_MK_I2C3_GPIO_CLOCK_OFFSET
 * @brief Définition de l'offset du bit SCL dans le registre de configuration GPIO.
 */

#define K_MK_I2C3_GPIO_CLOCK_OFFSET 7

/**
 * @def K_MK_I2C3_GPIO_DATA_OFFSET
 * @brief Définition de l'offset du bit SDA dans le registre de configuration GPIO.
 */

#define K_MK_I2C3_GPIO_DATA_OFFSET 8

/**
 * @def K_MK_I2C3_GPIO_CLOCK_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SCL.
 */

#define K_MK_I2C3_GPIO_CLOCK_MULTIPLEXER K_GPIO_AF4

/**
 * @def K_MK_I2C3_GPIO_DATA_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SDA.
 */

#define K_MK_I2C3_GPIO_DATA_MULTIPLEXER K_GPIO_AF4

/**
 *
 */

/**
 * @def K_MK_I2C4_GPIO_CLOCK_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SCL.
 */

#define K_MK_I2C4_GPIO_CLOCK_ADDR K_GPIOH

/**
 * @def K_MK_I2C4_GPIO_DATA_ADDR
 * @brief Définition de l'adresse du registre de configuration GPIO de la broche SDA.
 */

#define K_MK_I2C4_GPIO_DATA_ADDR K_GPIOH

/**
 * @def K_MK_I2C4_GPIO_CLOCK_OFFSET
 * @brief Définition de l'offset du bit SCL dans le registre de configuration GPIO.
 */

#define K_MK_I2C4_GPIO_CLOCK_OFFSET 11

/**
 * @def K_MK_I2C4_GPIO_DATA_OFFSET
 * @brief Définition de l'offset du bit SDA dans le registre de configuration GPIO.
 */

#define K_MK_I2C4_GPIO_DATA_OFFSET 12

/**
 * @def K_MK_I2C4_GPIO_CLOCK_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SCL.
 */

#define K_MK_I2C4_GPIO_CLOCK_MULTIPLEXER K_GPIO_AF4

/**
 * @def K_MK_I2C4_GPIO_DATA_MULTIPLEXER
 * @brief Définition du numéro du multiplexeur I2C de la broche SDA.
 */

#define K_MK_I2C4_GPIO_DATA_MULTIPLEXER K_GPIO_AF4

/**
 *
 */

#endif

