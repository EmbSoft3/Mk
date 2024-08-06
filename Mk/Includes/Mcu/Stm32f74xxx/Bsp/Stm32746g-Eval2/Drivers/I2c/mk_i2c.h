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
* @file mk_i2c.h
* @brief Déclaration des fonctions publiques dédiées aux périphériques I2C.
* @date 14 nov. 2020
*
*/

#ifndef MK_I2C_H
#define MK_I2C_H

/**
 * @fn T_mkCode mk_i2c_open ( T_mkI2CDevice** p_device, T_mkI2CSetting* p_setting, T_mkCallback* p_callback );
 * @brief Cette fonction ouvre un port de communication I2C.
 *
 * @param[out] p_device   Ce paramètre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice.
 * @param[in]  p_setting  Ce paramètre contient l'adresse de la structure de configuration du périphérique I2C.
 * @param[in]  p_callback Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la requête a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM         : la requête n'a pas été exécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la requête n'a pas été exécutée car la messagerie est pleine.
 *         \li \ref K_MK_ERROR_ISR           : la requête n'a pas été exécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : la requête n'a pas été exécutée car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : la requête n'a pas été exécutée car la requête n'est pas suportée.
 *         \li \ref K_MK_ERROR_MALLOC        : la requête n'a pas été exécutée en raison d'une erreur d'allocation dynamique.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_i2c_callback ( T_mkCode p_result, T_mkI2CDevice* p_device );
 *
 */

T_mkCode mk_i2c_open ( T_mkI2CDevice** p_device, T_mkI2CSetting* p_setting, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_i2c_close ( T_mkI2CDevice* p_device, T_mkCallback* p_callback );
 * @brief Cette fonction ferme un port de communication I2C.
 *
 * @param[in] p_device   Ce paramètre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice.
 * @param[in] p_callback Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la requête a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM         : la requête n'a pas été exécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la requête n'a pas été exécutée car la messagerie est pleine.
 *         \li \ref K_MK_ERROR_ISR           : la requête n'a pas été exécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la requête n'a pas été exécutée car le port de communication n'a pas été ouvert.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_i2c_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_i2c_close ( T_mkI2CDevice* p_device, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_i2c_postMessage ( T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_status, T_mkCallback* p_callback );
 * @brief Cette fonction déclenche un transfert I2C.
 *
 * @param[in]  p_device   Ce paramètre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice.
 * @param[in]  p_frame    Ce paramètre contient l'adresse d'une trame I2C de type \ref T_mkI2CFrame.
 * @param[out] p_status   Ce paramètre contient le statut du transfert.
 * @param[in]  p_callback Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                  : la requête a été exécutée.
 *         \li \ref K_MK_ERROR_PARAM         : la requête n'a pas été exécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la requête n'a pas été exécutée car la messagerie est pleine.
 *         \li \ref K_MK_ERROR_ISR           : la requête n'a pas été exécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM          : la requête n'a pas été exécutée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT       : la requête n'a pas été exécutée car un timeout de communication s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : la requête n'a pas été exécutée car le port de communication n'a pas été ouvert.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante :
 *       void mk_i2c_callback ( T_mkCode p_result, T_mkI2CDevice* p_device, T_mkI2CTransferStatus* p_status );
 *
 */

T_mkCode mk_i2c_postMessage ( T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_status, T_mkCallback* p_callback );

/**
 *
 */

#endif

