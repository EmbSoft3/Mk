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
* @file mk_i2c_isr_private.h
* @brief Déclaration des fonctions privées dédiées aux interruptions I2C.
* @date 1 nov. 2020
*
*/

#ifndef MK_I2C_ISR_PRIVATE_H
#define MK_I2C_ISR_PRIVATE_H

/**
 * @fn void mk_i2c1_interrupt ( void );
 * @brief Cette fonction est le gestionnaire d'interruption I2C1.
 * @return Sans objet.
 *
 */

void mk_i2c1_interrupt ( void );

/**
 * @fn void mk_i2c2_interrupt ( void );
 * @brief Cette fonction est le gestionnaire d'interruption I2C2.
 * @return Sans objet.
 *
 */

void mk_i2c2_interrupt ( void );

/**
 * @fn void mk_i2c3_interrupt ( void );
 * @brief Cette fonction est le gestionnaire d'interruption I2C3.
 * @return Sans objet.
 *
 */

void mk_i2c3_interrupt ( void );

/**
 * @fn void mk_i2c4_interrupt ( void );
 * @brief Cette fonction est le gestionnaire d'interruption I2C4.
 * @return Sans objet.
 *
 */

void mk_i2c4_interrupt ( void );

/**
 *
 */

/**
 * @fn void mk_i2c1_errorInterrupt ( void );
 * @brief Cette fonction est le gestionnaire d'erreur I2C1.
 * @return Sans objet.
 *
 */

void mk_i2c1_errorInterrupt ( void );

/**
 * @fn void mk_i2c2_errorInterrupt ( void );
 * @brief Cette fonction est le gestionnaire d'erreur I2C2.
 * @return Sans objet.
 *
 */

void mk_i2c2_errorInterrupt ( void );

/**
 * @fn void mk_i2c3_errorInterrupt ( void );
 * @brief Cette fonction est le gestionnaire d'erreur I2C3.
 * @return Sans objet.
 *
 */

void mk_i2c3_errorInterrupt ( void );

/**
 * @fn void mk_i2c4_errorInterrupt ( void );
 * @brief Cette fonction est le gestionnaire d'erreur I2C4.
 * @return Sans objet.
 *
 */

void mk_i2c4_errorInterrupt ( void );

/**
 *
 */

/**
 * @fn void mk_i2c1_transmitCallback ( void );
 * @brief Cette fonction est le gestionnaire de transmission DMA dédié au périphérique I2C1.
 * @return Sans objet.
 *
 */

void mk_i2c1_transmitCallback ( void );

/**
 * @fn void mk_i2c2_transmitCallback ( void );
 * @brief Cette fonction est le gestionnaire de transmission DMA dédié au périphérique I2C2.
 * @return Sans objet.
 *
 */

void mk_i2c2_transmitCallback ( void );

/**
 * @fn void mk_i2c3_transmitCallback ( void );
 * @brief Cette fonction est le gestionnaire de transmission DMA dédié au périphérique I2C3.
 * @return Sans objet.
 *
 */

void mk_i2c3_transmitCallback ( void );

/**
 * @fn void mk_i2c4_transmitCallback ( void );
 * @brief Cette fonction est le gestionnaire de transmission DMA dédié au périphérique I2C4.
 * @return Sans objet.
 *
 */

void mk_i2c4_transmitCallback ( void );

/**
 *
 */

/**
 * @fn void mk_i2c1_receiveCallback ( void );
 * @brief Cette fonction est le gestionnaire de réception DMA dédié au périphérique I2C1.
 * @return Sans objet.
 *
 */

void mk_i2c1_receiveCallback ( void );

/**
 * @fn void mk_i2c2_receiveCallback ( void );
 * @brief Cette fonction est le gestionnaire de réception DMA dédié au périphérique I2C2.
 * @return Sans objet.
 *
 */

void mk_i2c2_receiveCallback ( void );

/**
 * @fn void mk_i2c3_receiveCallback ( void );
 * @brief Cette fonction est le gestionnaire de réception DMA dédié au périphérique I2C3.
 * @return Sans objet.
 *
 */

void mk_i2c3_receiveCallback ( void );

/**
 * @fn void mk_i2c4_receiveCallback ( void );
 * @brief Cette fonction est le gestionnaire de réception DMA dédié au périphérique I2C4.
 * @return Sans objet.
 *
 */

void mk_i2c4_receiveCallback ( void );

/**
 *
 */

#endif


