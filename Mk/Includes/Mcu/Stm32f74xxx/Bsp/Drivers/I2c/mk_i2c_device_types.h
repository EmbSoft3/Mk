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
* @file mk_i2c_device_types.h
* @brief Déclaration des types dédiés aux périphériques I2C.
* @date 15 nov. 2020
*
*/

#ifndef MK_I2C_DEVICE_TYPES_H
#define MK_I2C_DEVICE_TYPES_H

/**
 * @struct T_mkI2CSetting
 * @brief Déclaration de la structure T_mkI2CSetting.
 *
 */

typedef struct T_mkI2CSetting T_mkI2CSetting;
struct T_mkI2CSetting
{
   uint32_t portNumber;                               /*!< Ce membre contient le numéro du port de connexion du périphérique I2C (\ref K_MK_I2C1, \ref K_MK_I2C2, \ref K_MK_I2C3 et \ref K_MK_I2C4). */
   uint32_t slaveAddr;                                /*!< Ce membre contient l'adresse d'un périphérique esclave connecté sur le bus. Il est dédié au mode maitre. */
   uint32_t deviceAddr1;                              /*!< Ce membre contient la première adresse du périphérique I2C. Il est dédié au mode escalve. */
   uint32_t deviceAddr2;                              /*!< Ce membre contient la seconde adresse du périphérique I2C. Il est dédié au mode escalve. */
   uint32_t addressLength;                            /*!< Ce membre contient le format de l'adresse I2C (\ref K_I2C_10BITS_MODE ou \ref K_I2C_7BITS_MODE). */
   uint32_t enableStretching;                         /*!< Ce champ indique si le mode 'Stretching' doit être activé ou non (0=désactivé, sinon activé). */
   uint32_t mainPrescaler;                            /*!< Ce membre contient la valeur du pré-diviseur principal (entre 0 et 15). */
   uint32_t clockLowPrescaler;                        /*!< Ce membre contient la valeur du pré-diviseur de l'horloge définissant la durée de l'état bas (entre 0 et 255). */
   uint32_t clockHighPrescaler;                       /*!< Ce membre contient la valeur du pré-diviseur de l'horloge définissant la durée de l'état haut (entre 0 et 255). */
   uint32_t dataSetupTime;                            /*!< Ce membre contient la valeur du pré-diviseur définissant la durée de préparation de la donnée (entre 0 et 15). */
   uint32_t dataHoldTime;                             /*!< Ce membre contient la valeur du pré-diviseur définissant la durée de maintien de la donnée (entre 0 et 15). */
};

/**
 * @struct T_mkI2CDevice
 * @brief Déclaration de la structure T_mkI2CDevice.
 *
 */

typedef struct T_mkI2CDevice T_mkI2CDevice;
struct T_mkI2CDevice
{
   uint32_t identifier;                               /*!< Ce membre contient l'identifiant unique du périphérique I2C. */
   T_mkI2CSetting setting;                            /*!< Ce membre contient la structure de configuration du port I2C. */
   T_mkI2CDevice* next;                               /*!< Ce membre contient l'adresse du prochain périphérique I2C ou la valeur \ref K_MK_NULL. */
   T_mkI2CDevice* previous;                           /*!< Ce membre contient l'adresse du précédent périphérique I2C ou la valeur \ref K_MK_NULL. */
};

/**
 *
 */

#endif

