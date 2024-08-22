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
* @file mk_i2c_private.h
* @brief Déclaration des fonctions privées I2C.
* @date 7 nov. 2020
*
*/

#ifndef MK_I2C_PRIVATE_H
#define MK_I2C_PRIVATE_H

/**
 * @fn void mk_i2c_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal I2C.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_i2c_task ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_i2c_initHandler ( T_mkI2CHandler* p_handler );
 * @brief Cette fonction initialise un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le gestionnaire I2C a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le gestionnaire I2C n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le gestionnaire I2C n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le gestionnaire I2C n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_i2c_initHandler ( T_mkI2CHandler* p_handler );

/**
 * @fn T_mkCode mk_i2c_handleCreate ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device, T_mkI2CSetting* p_setting );
 * @brief Cette fonction alloue un nouveau périphérique de type \ref T_mkI2CDevice puis l'ajoute dans une liste de périphériques.
 *
 * @param[in]  p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out] p_device  Ce paramètre contient l'adresse du périphérique I2C alloué.
 * @param[in]  p_setting Ce paramètre contient l'adresse de la structure de configuration du périphérique I2C.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK                  : le périphérique I2C a été alloué et ajouté dans la liste de périphérique.
 *         \li \ref K_MK_ERROR_PARAM         : le périphérique I2C n'a pas été alloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR           : le périphérique I2C n'a pas été alloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT         : le périphérique I2C n'a pas été alloué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_NOT_SUPPORTED : le périphérique I2C n'a pas été alloué car le gestionnaire I2C ne supporte pas 2 périphériques de type différent (Maitre/Esclave).
 *         \li \ref K_MK_ERROR_MALLOC        : le périphérique I2C n'a pas été alloué en raison d'une erreur d'allocation dynamique.
 *
 */

T_mkCode mk_i2c_handleCreate ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device, T_mkI2CSetting* p_setting );

/**
 * @fn T_mkCode mk_i2c_handleDelete ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );
 * @brief Cette fonction supprime un périphérique de type \ref T_mkI2CDevice. Il est retiré de la liste du gestionnaire.
 *
 * @param[in]  p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out] p_device  Ce paramètre contient l'adresse du périphérique à supprimer.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le périphérique I2C a été supprimé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique I2C n'a pas été supprimé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique I2C n'a pas été supprimé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le périphérique I2C n'a pas été supprimé car une tâche de type non privilégié ne possède pas les droits.
 *
 */

T_mkCode mk_i2c_handleDelete ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );

/**
 * @fn T_mkCode mk_i2c_handleMessage ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_status );
 * @brief Cette fonction déclenche un transfert I2C.
 *
 * @param[in]  p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[in]  p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkI2CDevice.
 * @param[in]  p_frame   Ce paramètre contient l'adresse d'une trame I2C de type \ref T_mkI2CFrame.
 * @param[out] p_status  Ce paramètre contient le statut du transfert.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert de la trame I2C a réussi. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_COMM    : le transfert de la trame I2C a échoué en raison d'une erreur de communication. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert de la trame I2C a échoué en raison d'une erreur de timeout. Le statut de la communication est disponible dans la structure \ref T_mkI2CTransferStatus.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert de la trame I2C a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_i2c_handleMessage ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_status );

/**
 * @fn void mk_i2c_handleMasterInterrupt ( T_mkI2CHandler* p_handler );
 * @brief Cette fonction contient le code exécuté lors du déclenchement d'une interruption I2C.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 *
 * @return Sans objet.
 *
 */

void mk_i2c_handleMasterInterrupt ( T_mkI2CHandler* p_handler );

/**
 *
 */

#endif

