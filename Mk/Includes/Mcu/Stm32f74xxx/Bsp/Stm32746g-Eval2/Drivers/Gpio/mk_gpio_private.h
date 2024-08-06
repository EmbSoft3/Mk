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
* @file mk_gpio_private.h
* @brief Déclaration des fonctions privées dédiées au terminal GPIO.
* @date 21 déc. 2020
*
*/

#ifndef MK_GPIO_PRIVATE_H
#define MK_GPIO_PRIVATE_H

/**
 * @fn void mk_gpio_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal GPIO.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_gpio_task ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_i2c_initHandler ( T_mkI2CHandler* p_handler );
 * @brief Cette fonction initialise un gestionnaire GPIO de type \ref T_mkGPIOHandler.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire GPIO de type \ref T_mkGPIOHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le gestionnaire GPIO a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire GPIO n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire GPIO n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire GPIO n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_gpio_initHandler ( T_mkGPIOHandler* p_handler );

/**
 * @fn T_mkCode mk_gpio_handleRequest ( T_mkTask* p_task, T_mkGPIOHandler* p_handler, T_mkGPIOMessage* p_message, uint32_t p_request );
 * @brief Cette fonction traite les requêtes reçues par le terminal GPIO.
 *
 * @param[in] p_task    Ce paramètre contient l'adresse de la tâche qui a posté la requête.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire GPIO de type \ref T_mkGPIOHandler.
 * @param[in] p_message Ce paramètre contient l'adresse d'une requête de type \ref T_mkGPIOMessage.
 * @param[in] p_request Ce paramètre contient l'identifiant de la requête
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK          : la requête utilisateur a été traitée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la requête utilisateur n'a pas été traitée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la requête utilisateur n'a pas été traitée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : la requête utilisateur n'a pas été traitée car une tâche de type non privilégié ne peut pas utiliser une broche GPIO protégée.
 *
 */

T_mkCode mk_gpio_handleRequest ( T_mkTask* p_task, T_mkGPIOHandler* p_handler, T_mkGPIOMessage* p_message, uint32_t p_request );

/**
 *
 */

#endif


