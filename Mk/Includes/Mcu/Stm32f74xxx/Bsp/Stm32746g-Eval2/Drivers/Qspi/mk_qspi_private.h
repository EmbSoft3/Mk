/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_qspi_private.h
* @brief Déclaration des fonctions privées dédiées à la mémoire QSPI.
* @date 9 août 2024
*
*/

#ifndef MK_QSPI_PRIVATE_H
#define MK_QSPI_PRIVATE_H

/**
 * @fn T_mkCode mk_qspi_abort ( void );
 * @brief Cette fonction stoppe le transfert en cours sur le bus QSPI.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'arrêt du transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'arrêt du transfert a échoué car un timeout s'est produit.
 */

T_mkCode mk_qspi_abort ( void );

/**
 * @fn T_mkCode mk_qspi_wait ( void );
 * @brief Cette fonction attend la fin d'un transfert QSPI.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert a échoué car un timeout s'est produit.
 */

T_mkCode mk_qspi_wait ( void );

/**
 * @fn T_mkCode mk_qspi_writeInstruction ( uint32_t p_instruction, uint32_t p_mode );
 * @brief Cette fonction transfert une instruction sur le bus QSPI.
 *
 * @param[in] p_instruction Ce paramètre contient la valeur de l'instruction sur 8 bits.
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                          \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le transfert a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le transfert a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_writeInstruction ( uint32_t p_instruction, uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_writeInstructionAddr ( uint32_t p_instruction, uint32_t p_addr, uint32_t p_mode );
 * @brief Cette fonction transfert une instruction et une adresse sur le bus QSPI.
 *
 * @param[in] p_instruction Ce paramètre contient la valeur de l'instruction sur 8 bits.
 * @param[in] p_addr        Ce paramètre contient la valeur de l'adresse sur 32 bits.
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                          \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le transfert a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le transfert a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_writeInstructionAddr ( uint32_t p_instruction, uint32_t p_addr, uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_writeInstructionData ( uint32_t p_instruction, uint32_t p_addr, uint8_t* p_buf, uint32_t p_size, uint32_t p_mode );
 * @brief Cette fonction transfert une instruction, une adresse et un ou plusieurs octets sur le bus QSPI.
 * @param[in] p_instruction Ce paramètre contient la valeur de l'instruction sur 8 bits.
 * @param[in] p_addr        Ce paramètre contient la valeur de l'adresse sur 32 bits.
 * @param[in] p_buf         Ce paramètre contient l'adresse du buffer contenant les octets à envoyer sur le bus QSPI.
 * @param[in] p_size        Ce paramètre contient le nombre de données à envoyer sur le bus QSPI. Il évolue de [1 à \ref K_MK_MICRON_N25Q512A_PAGE_SIZE].
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                          \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le transfert a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : le transfert a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le transfert a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le transfert a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_writeInstructionData ( uint32_t p_instruction, uint32_t p_addr, uint8_t* p_buf, uint32_t p_size, uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_writeRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_size, uint32_t p_mode );
 * @brief Cette fonction écrit une nouvelle valeur dans un registre de la mémoire QSPI.
 *
 * @param[in] p_register    Ce paramètre contient l'adresse d'un buffer contenant la nouvelle valeur du registre (
 *                          \ref T_MicronN25Q512A_StatusRegister, \ref T_MicronN25Q512A_NVConfigurationRegister,
 *                          \ref T_MicronN25Q512A_ConfigurationRegister et T_MicronN25Q512A_EnhancedConfigurationRegister).
 * @param[in] p_instruction Ce paramètre contient la valeur de l'instruction sur 8 bits.
 * @param[in] p_size        Ce paramètre contient la taille du registre (en octets).
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                          \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le transfert a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le transfert a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_writeRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_size, uint32_t p_mode );

/**
 * @fn T_mkCode mk_qspi_readRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_mode, uint32_t p_size );
 * @brief Cette fonction lit la valeur d'un registre de la mémoire QSPI.
 *
 * @param[in] p_register    Ce paramètre contient l'adresse d'un buffer où la valeur du registre doit être stockée (
 *                          \ref T_MicronN25Q512A_StatusRegister, \ref T_MicronN25Q512A_NVConfigurationRegister,
 *                          \ref T_MicronN25Q512A_ConfigurationRegister et T_MicronN25Q512A_EnhancedConfigurationRegister).
 * @param[in] p_instruction Ce paramètre contient la valeur de l'instruction sur 8 bits.
 * @param[in] p_size        Ce paramètre contient la taille du registre (en octets).
 * @param[in] p_mode        Ce paramètre contient le mode de fonctionnement de la mémoire QSPI.
 *                          Une des constante suivante peut être utilisée :
 *                          \ref K_MK_QSPI_MODE_SINGLE, \ref K_MK_QSPI_MODE_DUAL ou \ref K_MK_QSPI_MODE_QUAD
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : le transfert a réussi.
 *         \li \ref K_MK_ERROR_TIMEOUT       : le transfert a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le transfert a échoué car le bus QSPI n'est pas disponible.
 */

T_mkCode mk_qspi_readRegister ( T_mkAddr p_register, uint32_t p_instruction, uint32_t p_size, uint32_t p_mode );

/**
 *
 */

#endif

