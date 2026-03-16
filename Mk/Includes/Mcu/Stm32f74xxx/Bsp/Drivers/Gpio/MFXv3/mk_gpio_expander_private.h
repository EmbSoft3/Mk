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
* @file mk_gpio_expander_private.h
* @brief Déclaration des fonctions privées dédiées au périphérique MFX.
* @date 20 déc. 2020
*
*/

#ifndef MK_GPIO_EXPANDER_PRIVATE_H
#define MK_GPIO_EXPANDER_PRIVATE_H

/**
 * @fn T_mkCode mk_gpio_expander_init ( T_mkGPIOHandler* p_handler );
 * @brief Cette fonction ouvre un port de communication I2C puis initialise le périphérique MFX.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : le périphérique MFX a été intialisé.
 *         \li \ref K_MK_ERROR_PARAM          : le périphérique MFX n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : le périphérique MFX n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : le périphérique MFX n'a pas été initialisé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : le périphérique MFX n'a pas été initialisé car un timeout de communication s'est produit.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE  : le périphérique MFX n'a pas été initialisé car aucun port de communication n'est disponible.
 *         \li \ref K_MK_ERROR_RIGHT          : le périphérique MFX n'a pas été initialisé car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_MALLOC         : le périphérique MFX n'a pas été initialisé car aucun bloc mémoire n'est disponible pour ouvrir un nouveau port de communication.
 *
 */

T_mkCode mk_gpio_expander_init ( T_mkGPIOHandler* p_handler );

/**
 * @fn T_mkCode mk_gpio_expander_deinit ( T_mkGPIOHandler* p_handler );
 * @brief Cette fonction ferme un port de communication I2C puis réinitialise (reset) le périphérique MFX.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique MFX a été fermé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique MFX n'a pas été fermé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique MFX n'a pas été fermé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM    : le périphérique MFX n'a pas été fermé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le périphérique MFX n'a pas été fermé car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_deinit ( T_mkGPIOHandler* p_handler );

/**
 * @fn T_mkCode mk_gpio_expander_reset ( T_mkGPIOHandler* p_handler );
 * @brief Cette fonction réinitialise le périphérique MFX (reset).
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : le périphérique MFX a été réinitialisé.
 *         \li \ref K_MK_ERROR_PARAM          : le périphérique MFX n'a pas été réinitialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : le périphérique MFX n'a pas été réinitialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : le périphérique MFX n'a pas été réinitialisé car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : le périphérique MFX n'a pas été réinitialisé car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_reset ( T_mkGPIOHandler* p_handler );

/**
 * @fn T_mkCode mk_gpio_expander_type ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_type );
 * @brief Cette fonction configure le type d'une broche GPIO du périphérique MFX.
 *
 * @param[in] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue entre [0 et\ref MK_GPIO_EXPANDER_NUMBER_OF_PINS]. Les
 *                        constantes définies dans la structure \ref T_mkGPIOExpanderPin peuvent être utilisées.
 * @param[in] p_type      Ce paramètre contient le type de la broche à configurer. Les constantes \ref K_MK_GPIO_PUSHPULL et \ref K_MK_GPIO_OPENDRAIN peuvent
 *                        être utilisées pour une broche configurée en sortie. Les constantes \ref K_MK_GPIO_ENABLE_PULL et \ref K_MK_GPIO_DISABLE_PULL peuvent
 *                        être utilisées pour une broche configurée en entrée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la broche a été configurée.
 *         \li \ref K_MK_ERROR_PARAM          : la broche n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la broche n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la broche n'a pas été configurée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la broche n'a pas été configurée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_type ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_type );

/**
 * @fn T_mkCode mk_gpio_expander_direction ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_direction );
 * @brief Cette fonction configure la direction d'une broche GPIO du périphérique MFX.
 *
 * @param[in] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue entre [0 et\ref MK_GPIO_EXPANDER_NUMBER_OF_PINS]. Les
 *                        constantes définies dans la structure \ref T_mkGPIOExpanderPin peuvent être utilisées.
 * @param[in] p_direction Ce paramètre contient la direction de la broche à configurer. Les constantes \ref K_MK_GPIO_INPUT et \ref K_MK_GPIO_OUTPUT peuvent
 *                        être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la broche a été configurée.
 *         \li \ref K_MK_ERROR_PARAM          : la broche n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la broche n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la broche n'a pas été configurée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la broche n'a pas été configurée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_direction ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_direction );

/**
 * @fn T_mkCode mk_gpio_expander_resistor ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_resistor );
 * @brief Cette fonction configure le type de la résistance de tirage d'une broche GPIO du périphérique MFX.
 *
 * @param[in] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue entre [0 et\ref MK_GPIO_EXPANDER_NUMBER_OF_PINS]. Les
 *                        constantes définies dans la structure \ref T_mkGPIOExpanderPin peuvent être utilisées.
 * @param[in] p_resistor  Ce paramètre contient la type de la résitance de tirage. Les constantes \ref K_MK_GPIO_PULLUP et \ref K_MK_GPIO_PULLDOWN p
 *                        euvent être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la broche a été configurée.
 *         \li \ref K_MK_ERROR_PARAM          : la broche n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la broche n'a pas été configurée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la broche n'a pas été configurée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la broche n'a pas été configurée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_resistor ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_resistor );

/**
 * @fn T_mkCode mk_gpio_expander_set ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );
 * @brief Cette fonction positionne une broche GPIO du périphérique MFX au niveau logique HIGH.
 *
 * @param[in] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue entre [0 et\ref MK_GPIO_EXPANDER_NUMBER_OF_PINS]. Les
 *                        constantes définies dans la structure \ref T_mkGPIOExpanderPin peuvent être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la broche a été positionnée au niveau logique HIGH.
 *         \li \ref K_MK_ERROR_PARAM          : la broche n'a pas été positionnée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la broche n'a pas été positionnée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la broche n'a pas été positionnée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la broche n'a pas été positionnée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_set ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );

/**
 * @fn T_mkCode mk_gpio_expander_clear ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );
 * @brief Cette fonction positionne une broche GPIO du périphérique MFX au niveau logique LOW.
 *
 * @param[in] p_handler   Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_pinNumber Ce paramètre contient le numéro de la broche GPIO à configurer. Il évolue entre [0 et\ref MK_GPIO_EXPANDER_NUMBER_OF_PINS]. Les
 *                        constantes définies dans la structure \ref T_mkGPIOExpanderPin peuvent être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la broche a été positionnée au niveau logique LOW.
 *         \li \ref K_MK_ERROR_PARAM          : la broche n'a pas été positionnée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la broche n'a pas été positionnée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la broche n'a pas été positionnée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la broche n'a pas été positionnée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_clear ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );

/**
 * @fn T_mkCode mk_gpio_expander_get ( T_mkGPIOHandler* p_handler, uint32_t* p_value );
 * @brief Cette fonction lit l'état d'une broche GPIO du périphérique MFX.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[out] p_value   Ce paramètre contient la valeur du port GPIO du périphérique MFX sur \ref MK_GPIO_EXPANDER_NUMBER_OF_PINS bits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : le port GPIO a été lu.
 *         \li \ref K_MK_ERROR_PARAM          : le port GPIO n'a pas été lu car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : le port GPIO n'a pas été lu car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : le port GPIO n'a pas été lu car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : le port GPIO n'a pas été lu car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_get ( T_mkGPIOHandler* p_handler, uint32_t* p_value );

/**
 * @fn T_mkCode mk_gpio_expander_read ( T_mkGPIOHandler* p_handler, uint8_t* p_register, uint8_t p_length );
 * @brief Cette fonction lit un registre I2C du périphérique MFX.
 *
 * @param[in]  p_handler  Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[out] p_register Ce paramètre contient la valeur du registre lu.
 * @param[in]  p_length   Ce paramètre contient la taille du registre à lire [en octets].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : la lecture du registre a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM          : la lecture du registre n'a pas été réalisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : la lecture du registre n'a pas été réalisée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : la lecture du registre n'a pas été réalisée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : la lecture du registre n'a pas été réalisée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_read ( T_mkGPIOHandler* p_handler, uint8_t* p_register, uint8_t p_length );

/**
 * @fn T_mkCode mk_gpio_expander_write ( T_mkGPIOHandler* p_handler, uint8_t p_register, uint8_t p_value );
 * @brief Cette fonction écrit un registre I2C du périphérique MFX.
 *
 * @param[in] p_handler  Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkGPIOHandler.
 * @param[in] p_register Ce paramètre contient l'adresse du registre à écrire.
 * @param[in] p_value    Ce paramètre contient la valeur à écrire dans le registre.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK                   : l'écriture du registre a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM          : l'écriture du registre n'a pas été réalisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR            : l'écriture du registre n'a pas été réalisée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_COMM           : l'écriture du registre n'a pas été réalisée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT        : l'écriture du registre n'a pas été réalisée car un timeout de communication s'est produit.
 *
 */

T_mkCode mk_gpio_expander_write ( T_mkGPIOHandler* p_handler, uint8_t p_register, uint8_t p_value );

/**
 *
 */

#endif

