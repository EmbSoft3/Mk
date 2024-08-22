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
* @file mk_gpio.h
* @brief Déclaration des fonctions publiques dédiées aux broches GPIO.
* @date 22 déc. 2020
*
*/

#ifndef MK_GPIO_H
#define MK_GPIO_H

/**
 * @fn T_mkCode mk_gpio_setup ( uint32_t p_port, uint32_t p_pinNumber, T_mkGPIOSetting* p_setting, T_mkCallback* p_callback );
 * @brief Cette fonction configure une broche GPIO.
 *
 * @param[in] p_port      Ce paramètre contient l'identifiant d'un port GPIO. Une des constantes suivantes peut être utilisée :
 *                        \ref K_MK_GPIO_EXPANDER ou \ref K_MK_GPIO_PORTA jusqu'à \ref K_MK_GPIO_PORTK
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue de [0 à \ref MK_GPIO_EXPANDER_NUMBER_OF_PINS[
 *                        pour le périphérique MFX et de [0 à \ref K_GPIO_NUMBER_OF_PINS_PER_PORT[ pour les ports internes.
 * @param[in] p_setting   Ce paramètre contient les attributs de la broche à configurer :
 *                        \li direction : \ref K_MK_GPIO_INPUT et \ref K_MK_GPIO_OUTPUT
 *                        \li type (\ref K_MK_GPIO_OUTPUT) : \ref K_MK_GPIO_PUSHPULL ou \ref K_MK_GPIO_OPENDRAIN
 *                        \li type (\ref K_MK_GPIO_INPUT) : \ref K_MK_GPIO_ENABLE_PULL ou \ref K_MK_GPIO_DISABLE_PULL
 *                        \li resistor : \ref K_MK_GPIO_PULLUP ou \ref K_MK_GPIO_PULLDOWN
 * @param[in] p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la requête n'a pas été postée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête n'a pas été postée car la messagerie est pleine.
 *         \li \ref K_MK_ERROR_ISR     : la requête n'a pas été postée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM    : la requête n'a pas été exécutée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête n'a pas été exécutée car un timeout de communication s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : la requête n'a pas été exécutée car une tâche non privilégiée ne peut pas modifier une broche protégée.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_gpio_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_gpio_setup ( uint32_t p_port, uint32_t p_pinNumber, T_mkGPIOSetting* p_setting, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_gpio_set ( uint32_t p_port, uint32_t p_pinNumber, uint32_t p_value, T_mkCallback* p_callback );
 * @brief Cette fonction configure le niveau logique d'une broche GPIO.
 *
 * @param[in] p_port      Ce paramètre contient l'identifiant d'un port GPIO. Une des constantes suivantes peut être utilisée :
 *                        \ref K_MK_GPIO_EXPANDER ou \ref K_MK_GPIO_PORTA jusqu'à \ref K_MK_GPIO_PORTK
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue de [0 à \ref MK_GPIO_EXPANDER_NUMBER_OF_PINS[
 *                        pour le périphérique externe et de [0 à \ref K_GPIO_NUMBER_OF_PINS_PER_PORT[ pour les ports internes.
 * @param[in] p_value     Ce paramètre contient le niveau logique à positionner sur la broche. Une des constantes suivantes peut être utilisée : \n
 *                        \ref K_MK_GPIO_HIGH ou \ref K_MK_GPIO_LOW
 * @param[in] p_callback  Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a été exécutée sans renconter d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la requête n'a pas été exécutée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête n'a pas été exécutée car la messagerie est pleine.
 *         \li \ref K_MK_ERROR_ISR     : la requête n'a pas été exécutée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM    : la requête n'a pas été exécutée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête n'a pas été exécutée car un timeout de communication s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : la requête n'a pas été exécutée car une tâche non privilégiée ne peut pas modifier une broche protégée.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_gpio_callback ( T_mkCode p_result );
 *
 */

T_mkCode mk_gpio_set ( uint32_t p_port, uint32_t p_pinNumber, uint32_t p_value, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_gpio_get ( uint32_t p_port, uint32_t p_pinNumber, uint32_t* p_value );
 * @brief Cette fonction retourne le niveau logique d'une broche GPIO.
 *
 * @param[in] p_port      Ce paramètre contient l'identifiant d'un port GPIO. Une des constantes suivantes peut être utilisée :
 *                        \ref K_MK_GPIO_EXPANDER ou \ref K_MK_GPIO_PORTA jusqu'à \ref K_MK_GPIO_PORTK
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue de [0 à \ref MK_GPIO_EXPANDER_NUMBER_OF_PINS[
 *                        pour le périphérique externe et de [0 à \ref K_GPIO_NUMBER_OF_PINS_PER_PORT[ pour les ports internes.
 * @param[out] p_value    Ce paramètre contient le niveau logique lu sur la broche. Il évolue entre [0 et 1].
 *                        Les constantes \ref K_MK_GPIO_HIGH et \ref K_MK_GPIO_LOW peuvent être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture de la broche a été réalisée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture de la broche n'a pas été réalisée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_gpio_get ( uint32_t p_port, uint32_t p_pinNumber, uint32_t* p_value );

/**
 *
 */

#endif
