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
* @file mk_i2c_device_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques I2C.
* @date 15 nov. 2020
*
*/

#ifndef MK_I2C_DEVICE_PRIVATE_H
#define MK_I2C_DEVICE_PRIVATE_H

/**
 * @fn T_mkCode mk_i2c_getHandler ( T_mkI2CHandler** p_handler, uint32_t p_peripheralIdentifier );
 * @brief Cette fonction retourne l'adresse du gestionnaire I2C identifié par 'p_peripheralIdentifier'.
 *
 * @param[out] p_handler              Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[in]  p_peripheralIdentifier Ce paramètre contient l'identifiant du périphérique I2C. Une des constantes suivante peut être utlisée :
 *                                    \ref K_MK_I2C1 à \ref K_MK_I2C4.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'adresse du gestionnaire I2C a été écrite dans le paramètre 'p_peripheralIdentifier'.
 *         \li \ref K_MK_ERROR_PARAM   : l'adresse du gestionnaire I2C n'a pas été écrite dans 'p_peripheralIdentifier' car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_i2c_getHandler ( T_mkI2CHandler** p_handler, uint32_t p_peripheralIdentifier );

/**
 * @fn T_mkCode mk_i2c_createDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device );
 * @brief Cette fonction alloue un nouveau périphérique I2C puis l'ajoute dans la liste d'un gestionnaire.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out] p_device  Ce paramètre contient l'adresse du périphérique I2C alloué.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le périphérique I2C a été alloué puis ajouté dans la liste du gestionnaire.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique I2C n'a pas été alloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le périphérique I2C n'a pas été alloué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique I2C n'a pas été alloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le périphérique I2C n'a pas été alloué car une tâche de type non privilégié ne peut pas allouer un périphérique I2C protégé.
 *
 */

T_mkCode mk_i2c_createDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device );

/**
 * @fn T_mkCode mk_i2c_deleteDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );
 * @brief Cette fonction désalloue un périphérique I2C présent dans une liste d'un gestionnaire.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out] p_device  Ce paramètre contient l'adresse du périphérique I2C à supprimer.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le périphérique I2C a été supprimé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique I2C n'a pas été supprimé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique I2C n'a pas été supprimé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le périphérique I2C n'a pas été supprimé car une tâche de type non privilégié ne peut pas désallouer un périphérique I2C protégé.
 *
 */

T_mkCode mk_i2c_deleteDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );

/**
 * @fn T_mkCode mk_i2c_checkDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );
 * @brief Cette fonction vérifie si un périphérique I2C est présent dans la liste des périphériques d'un gestionnaire I2C.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire I2C de type \ref T_mkI2CHandler.
 * @param[out] p_device  Ce paramètre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK                  : le périphérique I2C est présent dans la liste des périphériques du gestionnaire.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : le périphérique I2C n'est pas présent dans la liste des périphériques du gestionnaire.
 *         \li \ref K_MK_ERROR_PARAM         : la recherche du périphérique I2C n'a pas été réalisée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_i2c_checkDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device );

/**
 *
 */

#endif

