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
* @file mk_i2c_port_private.h
* @brief Déclaration des fonctions privées dédiées aux ports I2C.
* @date 10 oct. 2020
*
*/

#ifndef MK_I2C_PORT_PRIVATE_H
#define MK_I2C_PORT_PRIVATE_H

/**
 * @fn void mk_i2c_initGPIO ( T_mkAddr p_bus );
 * @brief Cette fonction initialise les broches matérielles d'un bus I2C.
 * @param p_bus Ce paramètre contient l'adresse d'un bus I2C. Une des constantes suivantes peut être utlisées :
 *              \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4.
 *
 * @return Sans objet.
 *
 */

void mk_i2c_initGPIO ( T_mkAddr p_bus );

/**
 * @fn void mk_i2c_init ( T_mkI2CHandler* p_handler, T_mkI2CSetting* p_setting );
 * @brief Cette fonction initialise un périphérique I2C.
 *
 * @param p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param p_setting Ce paramètre contient l'adresse de la structure de configuration du périphérique I2C.
 *
 * @return Sans objet.
 *
 */

void mk_i2c_init ( T_mkI2CHandler* p_handler, T_mkI2CSetting* p_setting );

/**
 * @fn T_mkCode mk_i2c_send ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_transfer );
 * @brief Cette fonction déclenche un transfert I2C.
 *
 * @param[in]  p_handler  Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[in]  p_device   Ce paramètre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice.
 * @param[in]  p_frame    Ce paramètre contient l'adresse d'une trame I2C de type \ref T_mkI2CFrame.
 * @param[out] p_transfer Ce paramètre contient le statut du transfert.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert de la trame I2C a réussi. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_COMM    : le transfert de la trame I2C a échoué en raison d'une erreur de communication. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert de la trame I2C a échoué en raison d'une erreur de timeout. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert de la trame I2C a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_i2c_send ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_transfer );

/**
 *
 */

#endif

