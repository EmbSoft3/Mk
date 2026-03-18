/**
*
* @copyright Copyright (C) 2020-2026 RENARD Mathieu. All rights reserved.
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
 *
 */

typedef struct T_mkGPIOHandler T_mkGPIOHandler;

/**
 * @struct T_mkGPIOExpanderGetFunction
 * @brief Création du type T_mkGPIOExpanderGetFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderGetFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t* p_value );

/**
 * @struct T_mkGPIOExpanderDirectionFunction
 * @brief Création du type T_mkGPIOExpanderDirectionFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderDirectionFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_direction );

/**
 * @struct T_mkGPIOExpanderTypeFunction
 * @brief Création du type T_mkGPIOExpanderTypeFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderTypeFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_type );

/**
 * @struct T_mkGPIOExpanderResistorFunction
 * @brief Création du type T_mkGPIOExpanderResistorFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderResistorFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber, uint32_t p_resistor );

/**
 * @struct T_mkGPIOExpanderSetFunction
 * @brief Création du type T_mkGPIOExpanderSetFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderSetFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );

/**
 * @struct T_mkGPIOExpanderClearFunction
 * @brief Création du type T_mkGPIOExpanderClearFunction.
 */

typedef T_mkCode ( *T_mkGPIOExpanderClearFunction ) ( T_mkGPIOHandler* p_handler, uint32_t p_pinNumber );

/**
 *
 */

/**
 * @struct T_mkGPIOPinHandlerCallback
 * @brief Déclaration de la structure T_mkGPIOPinHandlerCallback.
 *
 */

typedef struct T_mkGPIOPinHandlerCallback T_mkGPIOPinHandlerCallback;
struct T_mkGPIOPinHandlerCallback
{
   T_mkGPIOExpanderGetFunction expanderGet;                          /*!< Ce membre contient l'adresse de la fonction permettant de récupérer l'état d'une broche GPIO */
   T_mkGPIOExpanderDirectionFunction expanderDirection;              /*!< Ce membre contient l'adresse de la fonction permettant de configurer la direction d'une broche GPIO */
   T_mkGPIOExpanderTypeFunction expanderType;                        /*!< Ce membre contient l'adresse de la fonction permettant de configurer le type d'une broche GPIO */
   T_mkGPIOExpanderResistorFunction expanderResistor;                /*!< Ce membre contient l'adresse de la fonction permettant de configurer la résistance d'une broche GPIO */
   T_mkGPIOExpanderSetFunction expanderSet;                          /*!< Ce membre contient l'adresse de la fonction permettant positionner une broche GPIO au niveau logique HIGH */
   T_mkGPIOExpanderClearFunction expanderClear;                      /*!< Ce membre contient l'adresse de la fonction permettant positionner une broche GPIO au niveau logique LOW */
};

/**
 * @struct T_mkGPIOMessage
 * @brief Déclaration de la structure T_mkGPIOMessage.
 *
 */

typedef struct T_mkGPIOPinHandler T_mkGPIOPinHandler;
struct T_mkGPIOPinHandler
{
   uint32_t port;                                                    /*!< Ce membre contient le numéro du port (\ref T_mkGPIOPort) assigné à l'identifiant \ref T_mkGPIOPinID */
   uint32_t pinNumber;                                               /*!< Ce membre contient le numéro de la broche assigné à l'identifant \ref T_mkGPIOPinID. */
   uint32_t type;                                                    /*!< Ce membre contient le type de la broche (\ref T_mkGPIODirection). */
   uint32_t initialValue;                                            /*!< Ce membre contient la valeur initiale de la broche \ref T_mkGPIOPinID. */
   uint32_t lastValue;                                               /*!< Ce membre contient la dernière valeur mémorisée de la broche \ref T_mkGPIOPinID. */
   uint32_t currentValue;                                            /*!< Ce membre contient la valeur mémorisée de la broche \ref T_mkGPIOPinID. */
   uint16_t idleState;                                               /*!< Ce membre contient l'événement à assigner à la broche lorsque celle-ci revient à l'état de repos (\ref K_MK_EVENT_NO si non applicable). */
   uint16_t activeState;                                             /*!< Ce membre contient l'événement à assigner à la broche lorsque celle-ci passe à l'état actif (\ref K_MK_EVENT_NO si non applicable). */
   uint32_t isProtect;                                               /*!< Ce membre indique si la broche T_mkGPIOPinID est protégée ou non. */
   T_mkGPIOPinHandlerCallback callback;                              /*!< Ce membre contient l'ensemble des fonctions permettant l'accès à la broche GPIO. */
};

/**
 *
 */

/**
 * @enum T_mkGPIOPort
 * @brief Déclaration de l'énumération T_mkGPIOPort.
 *
 */

typedef enum T_mkGPIOPort
{
   K_MK_GPIO_SYSID = 0,                                              /*!< Définition de l'identifiant indiquant que la broche est adressée de manière générique. */
   K_MK_GPIO_EXTERNAL = 1,                                           /*!< Définition de l'identifiant du/des ports externes. */
   K_MK_GPIO_PORTA = 2,                                              /*!< Définition de l'identifiant du port A. */
   K_MK_GPIO_PORTB = 3,                                              /*!< Définition de l'identifiant du port B. */
   K_MK_GPIO_PORTC = 4,                                              /*!< Définition de l'identifiant du port C. */
   K_MK_GPIO_PORTD = 5,                                              /*!< Définition de l'identifiant du port D. */
   K_MK_GPIO_PORTE = 6,                                              /*!< Définition de l'identifiant du port E. */
   K_MK_GPIO_PORTF = 7,                                              /*!< Définition de l'identifiant du port F. */
   K_MK_GPIO_PORTG = 8,                                              /*!< Définition de l'identifiant du port G. */
   K_MK_GPIO_PORTH = 9,                                              /*!< Définition de l'identifiant du port H. */
   K_MK_GPIO_PORTI = 10,                                             /*!< Définition de l'identifiant du port I. */
   K_MK_GPIO_PORTJ = 11,                                             /*!< Définition de l'identifiant du port J. */
   K_MK_GPIO_PORTK = 12,                                             /*!< Définition de l'identifiant du port K. */
   K_MK_GPIO_NUMBER_OF_PORTS = 13                                    /*!< Définition du nombre d'identifiants. */
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
 * @enum T_mkGPIOProtect
 * @brief Déclaration de l'énumération T_mkGPIOProtect.
 *
 */

typedef enum T_mkGPIOProtect
{
   K_MK_GPIO_UNPROTECTED = 0,                                        /*!< Définition d'une constante permettant de positionner une broche au niveau logique HIGH. */
   K_MK_GPIO_PROTECTED = 1                                           /*!< Définition d'une constante permettant de positionner une broche au niveau logique LOW. */
} T_mkGPIOProtect;

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
   T_mkGPIOPinHandler* pin;                                          /*!< Ce membre contient les valeurs présentes et passées lues sur le port GPIO du périphérique MFX (broches externes uniquement). */
};

/**
 * @struct T_mkGPIOHandler
 * @brief Déclaration de la structure T_mkGPIOHandler.
 *
 */

struct T_mkGPIOHandler
{
   T_mkI2CDevice* device;                                            /*!< Ce membre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice. */
   T_mkGPIOCtrl ctrl;                                              /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkGPIOCtrl. La position de cet attribut ne doit pas être modifiée. */
   T_mkGPIORequestArea* requestArea;                                 /*!< Ce membre contient l'adresse de la structure contenant les données relatives à la messagerie du terminal GPIO. */
};





















/**
 *
 */

#endif

