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
* @file mk_gpio_types.h
* @brief Déclaration des types GPIO.
* @date 20 déc. 2020
*
*/

#ifndef MK_GPIO_TYPES_H
#define MK_GPIO_TYPES_H

/**
 * @enum T_mkGPIOPort
 * @brief Déclaration de l'énumération T_mkGPIOPort.
 *
 */

typedef enum T_mkGPIOPort
{
   K_MK_GPIO_EXPANDER = 0,                                           /*!< Définition de l'identifiant du port externe relié au périphérique MFX. */
   K_MK_GPIO_PORTA = 1,                                              /*!< Définition de l'identifiant du port A. */
   K_MK_GPIO_PORTB = 2,                                              /*!< Définition de l'identifiant du port B. */
   K_MK_GPIO_PORTC = 3,                                              /*!< Définition de l'identifiant du port C. */
   K_MK_GPIO_PORTD = 4,                                              /*!< Définition de l'identifiant du port D. */
   K_MK_GPIO_PORTE = 5,                                              /*!< Définition de l'identifiant du port E. */
   K_MK_GPIO_PORTF = 6,                                              /*!< Définition de l'identifiant du port F. */
   K_MK_GPIO_PORTG = 7,                                              /*!< Définition de l'identifiant du port G. */
   K_MK_GPIO_PORTH = 8,                                              /*!< Définition de l'identifiant du port H. */
   K_MK_GPIO_PORTI = 9,                                              /*!< Définition de l'identifiant du port I. */
   K_MK_GPIO_PORTJ = 10,                                             /*!< Définition de l'identifiant du port J. */
   K_MK_GPIO_PORTK = 11                                              /*!< Définition de l'identifiant du port K. */
} T_mkGPIOPort;

/**
 * @enum T_mkGPIODirection
 * @brief Déclaration de l'énumération T_mkGPIODirection.
 *
 */

typedef enum T_mkGPIODirection
{
   K_MK_GPIO_INPUT = 0,                                              /*!< Définition d'une constante permettant la configuration d'une GPIO en entrée. */
   K_MK_GPIO_OUTPUT = 1                                              /*!< Définition d'une constante permettant la configuration d'une GPIO en sortie. */
} T_mkGPIODirection;

/**
 * @enum T_mkGPIOOutputType
 * @brief Déclaration de l'énumération T_mkGPIOOutputType.
 *
 */

typedef enum T_mkGPIOOutputType
{
   K_MK_GPIO_PUSHPULL = 0,                                           /*!< Définition d'une constante permettant la configuration d'une sortie push-pull. */
   K_MK_GPIO_OPENDRAIN = 1                                           /*!< Définition d'une constante permettant la configuration d'une sortie open-drain. */
} T_mkGPIOOutputType;

/**
 * @enum T_mkGPIOInputType
 * @brief Déclaration de l'énumération T_mkGPIOInputType.
 *
 */

typedef enum T_mkGPIOInputType
{
   K_MK_GPIO_DISABLE_PULL = 0,                                       /*!< Définition d'une constante permettant de désactiver la résistance de tirage d'une entrée. */
   K_MK_GPIO_ENABLE_PULL = 1                                         /*!< Définition d'une constante permettant d'activer la résistance de tirage d'une entrée. */
} T_mkGPIOInputType;

/**
 * @enum T_mkGPIOResistor
 * @brief Déclaration de l'énumération T_mkGPIOResistor.
 *
 */

typedef enum T_mkGPIOResistor
{
   K_MK_GPIO_PULLDOWN = 0,                                           /*!< Définition d'une constante permettant de configurer la résistance de tirage en pull-Down. */
   K_MK_GPIO_PULLUP = 1                                              /*!< Définition d'une constante permettant de configurer la résistance de tirage en pull-up. */
} T_mkGPIOResistor;

/**
 * @enum T_mkGPIOLevel
 * @brief Déclaration de l'énumération T_mkGPIOLevel.
 *
 */

typedef enum T_mkGPIOLevel
{
   K_MK_GPIO_LOW = 0,                                                /*!< Définition d'une constante permettant de positionner une broche au niveau logique HIGH. */
   K_MK_GPIO_HIGH = 1                                                /*!< Définition d'une constante permettant de positionner une broche au niveau logique LOW. */
} T_mkGPIOLevel;


/**
 * @enum T_mkGPIORequest
 * @brief Déclaration de la structure T_mkGPIORequest.
 *
 */

typedef enum T_mkGPIORequest
{
   K_MK_GPIO_SETUP = 1,                                              /*!< Définition de l'identifiant de la requête de configuration d'une broche GPIO. */
   K_MK_GPIO_SET = 2                                                 /*!< Définition de l'identifiant de la requête de positionnement de l'état d'une broche GPIO. */
} T_mkGPIORequest;

/**
 * @struct T_mkGPIOSetting
 * @brief Déclaration de la structure T_mkGPIOSetting.
 *
 */

typedef struct T_mkGPIOSetting T_mkGPIOSetting;
struct T_mkGPIOSetting
{
   uint32_t direction;                                               /*!< Ce membre contient la direction de la broche GPIO (\ref K_MK_GPIO_INPUT et \ref K_MK_GPIO_OUTPUT). */
   uint32_t type;                                                    /*!< Ce membre contient le type de la broche GPIO (Input - \ref K_MK_GPIO_ENABLE_PULL et \ref K_MK_GPIO_DISABLE_PULL, Output - \ref K_MK_GPIO_PUSHPULL et \ref K_MK_GPIO_OPENDRAIN). */
   uint32_t resistor;                                                /*!< Ce membre contient la type de la résistance de tirage de la broche GPIO (\ref K_MK_GPIO_PULLUP et \ref K_MK_GPIO_PULLDOWN). */
};

/**
 * @struct T_mkGPIOMessage
 * @brief Déclaration de la structure T_mkGPIOMessage.
 *
 */

typedef struct T_mkGPIOMessage T_mkGPIOMessage;
struct T_mkGPIOMessage
{
   uint32_t requestIdentifier;                                       /*!< Ce membre contient l'identifiant de la requête de type \ref T_mkGPIORequest. */
   uint32_t port;                                                    /*!< Ce membre contient l'identifiant d'un port GPIO (\ref T_mkGPIOPort). */
   uint32_t pinNumber;                                               /*!< Ce membre contient le numéro d'une broche GPIO. */
   T_mkAddr setting;                                                 /*!< Ce membre contient le contenu de la requête. */
   T_mkCode* result;                                                 /*!< Ce membre contient le résultat de la requête. */
   T_mkCallback* callback;                                           /*!< Ce membre contient l'adresse d'une fonction de rappel. */
};

/**
 * @struct T_mkGPIORegister
 * @brief Déclaration de la structure T_mkGPIORegister.
 *
 */

typedef struct T_mkGPIORegister T_mkGPIORegister;
struct T_mkGPIORegister
{
   uint32_t last;                                                    /*!< Ce membre contient la dernière valeur mémorisée sur le port GPIO du périphérique MFX (broches externes uniquement). */
   uint32_t current;                                                 /*!< Ce membre contient la valeur lue sur le port GPIO du périphérique MFX (broches externes uniquement). */
};

/**
 * @struct T_mkGPIOLayer
 * @brief Déclaration de la structure T_mkGPIOLayer.
 *
 */

typedef struct T_mkGPIOLayer T_mkGPIOLayer;
struct T_mkGPIOLayer
{
   uint16_t type;                                                    /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_GPIO). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                                      /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkGPIOCtrl. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkGPIOCtrl
 * @brief Déclaration de la structure T_mkGPIOCtrl.
 *
 */

typedef struct T_mkGPIOCtrl T_mkGPIOCtrl;
struct T_mkGPIOCtrl
{
   T_mkGPIOLayer layer;                                              /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkGPIOCtrl. La position de cet attribut ne doit pas être modifiée. */
   T_mkGPIORegister expander;                                        /*!< Ce membre contient les valeurs présentes et passées lues sur le port GPIO du périphérique MFX (broches externes uniquement). */
};

/**
 * @struct T_mkGPIOHandler
 * @brief Déclaration de la structure T_mkGPIOHandler.
 *
 */

typedef struct T_mkGPIOHandler T_mkGPIOHandler;
struct T_mkGPIOHandler
{
   T_mkI2CDevice* device;                                            /*!< Ce membre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice. */
   T_mkGPIOCtrl ctrl;                                                /*!< Ce membre contient le registre de contrôle du terminal GPIO. */
   T_mkGPIORequestArea* requestArea;                                 /*!< Ce membre contient l'adresse de la structure contenant les données relatives à la messagerie du terminal GPIO. */
};


/**
 *
 */

#endif

