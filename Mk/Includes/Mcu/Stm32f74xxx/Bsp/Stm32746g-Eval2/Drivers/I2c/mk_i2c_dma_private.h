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
* @file mk_i2c_dma_private.h
* @brief Déclaration des fonctions privées dédiées aux pipes I2C.
* @date 1 nov. 2020
*
*/

#ifndef MK_I2C_DMA_PRIVATE_H
#define MK_I2C_DMA_PRIVATE_H

/**
 * @fn T_mkCode mk_i2c_openPipe ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction ouvre et initialise un pipe de communication I2C.
 *
 * @param[in, out] p_handler      Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out]     p_pipe         Ce paramètre contient l'adresse d'un pipe de communication de type \ref T_mkDMAPipe.
 * @param[in]      p_channel      Ce paramètre contient le numéro d'un canal DMA (\ref K_DMA_CHANNEL0 à \ref K_DMA_CHANNEL7).
 * @param[in]      p_stream       Ce paramètre contient le numéro d'un flux DMA (\ref K_DMA_STREAM0 à \ref K_DMA_STREAM7).
 * @param[in]      p_callback     Ce paramètre contient l'adresse de la fonction de rappel DMA.
 * @param[in]      p_registerAddr Ce paramètre contient l'adresse de base du buffer de données du périphérique I2C (transmission ou réception).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pipe de communication I2C a été ouvert.
 *         \li \ref K_MK_ERROR_PARAM   : le pipe de communication I2C n'a pas été ouvert car au moins un paramètre est invalide.
 */

T_mkCode mk_i2c_openPipe ( T_mkI2CHandler* p_handler, T_mkDMAPipe** p_pipe, uint32_t p_channel, uint32_t p_stream, T_mkDMACallback p_callback, uint32_t p_registerAddr );

/**
 * @fn T_mkCode mk_i2c_closePipe ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction ferme un pipe de communication I2C.
 *
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de communication de type \ref T_mkDMAPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le pipe de communication I2C a été fermé.
 *         \li \ref K_MK_ERROR_PARAM : le pipe de communication I2C n'a pas été fermé car au moins un paramètre est invalide.
 */

T_mkCode mk_i2c_closePipe ( T_mkI2CHandler* p_handler, T_mkDMAPipe** p_pipe );

/**
 * @fn void mk_i2c_handleCallback ( T_mkI2CDMAHandler* p_handler );
 * @brief Cette fonction est la fonction de rappel des interruptions DMA dédiées aux périphériques I2C.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de communication DMA.
 *
 * @return Sans objet.
 *
 */

void mk_i2c_handleCallback ( T_mkI2CDMAHandler* p_handler );

/**
 *
 */

#endif

