/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_hid_keyboard_types.h
* @brief Déclaration des types dédiés aux objets 'Keyboard'.
* @date 14 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_TYPES_H
#define MK_HID_KEYBOARD_TYPES_H

/**
 * @enum T_mkKeyboardIdentifier
 * @brief Déclaration de la structure T_mkKeyboardLayer.
 *
 */

typedef enum T_mkKeyboardIdentifier
{
   K_MK_KEYBOARD_LEFT_CTRL = 1,                                   /*!< Définition de la position du bit LEFT_CTRL dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_LEFT_SHIFT = 2,                                  /*!< Définition de la position du bit LEFT_SHIFT dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_LEFT_ALT = 4,                                    /*!< Définition de la position du bit LEFT_ALT dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_LEFT_GUI = 8,                                    /*!< Définition de la position du bit LEFT_GUI dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_RIGHT_CTRL = 16,                                 /*!< Définition de la position du bit RIGHT_CTRL dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_RIGHT_SHIFT = 32,                                /*!< Définition de la position du bit RIGHT_SHIFT dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_RIGHT_ALT = 64,                                  /*!< Définition de la position du bit RIGHT_ALT dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_RIGHT_GUI = 128,                                 /*!< Définition de la position du bit RIGHT_GUI dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_SHIFT = 34,                                      /*!< Définition de la position des bits LEFT_SHIFT et RIGHT_SHIFT dans l'énumération \ref T_mkKeyboardEvent dans l'énumération \ref T_mkKeyboardEvent. */
   K_MK_KEYBOARD_USER_COMMAND = 157                               /*!< Définition de la position des bits RIGHT_GUI, RIGHT_CTRL, LEFT_GUI, LEFT_ALT et LEFT_CTRL dans l'énumération \ref T_mkKeyboardEvent dans l'énumération \ref T_mkKeyboardEvent. */
} T_mkKeyboardIdentifier;

/**
 * @enum T_mkKeyboardIdentifier
 * @brief Déclaration de la structure T_mkKeyboardLayer.
 *
 */

typedef enum T_mkKeyboardType
{
   K_MK_KEYBOARD_QWERTY_US = 0,                                   /*!< Définition de l'identiant du clavier US QWERTY. */
   K_MK_KEYBOARD_AZERTY_FR = 1                                    /*!< Définition de l'identiant du clavier FR_AZERTY. */
} T_mkKeyboardType;

/**
 * @struct T_mkKeyCode
 * @brief Surcharge de la structure T_mkButton en T_mkKeyCode.
 *
 */

typedef struct T_mkButton T_mkKeyCode;

/**
 * @struct T_mkKeyboardLookup
 * @brief Surcharge de la structure uint32_t* en T_mkKeyboardLookup.
 *
 */

typedef uint32_t* T_mkKeyboardLookup;

/**
 * @struct T_mkKeyHandler
 * @brief Déclaration de la structure T_mkKeyHandler.
 *
 */

typedef struct T_mkKeyHandler T_mkKeyHandler;
struct T_mkKeyHandler
{
   uint16_t cmd;                                                  /*!< Ce membre contient la valeur 1 lorsque au moins une des touches RIGHT_GUI, RIGHT_CTRL, LEFT_GUI, LEFT_ALT et LEFT_CTRL on été saisie sur le clavier. */
   uint16_t scancode;                                             /*!< Ce membre contient le scancode de la touche saisie sur le clavier (cf. document HID Usage Tables Version 1.12 §10). */
   uint16_t modifier;                                             /*!< Ce membre contient l'identifiant du ou des modificateurs saisies sur le clavier (\ref T_mkKeyboardIdentifier). */
   uint16_t padding16;                                            /*!< Padding. */
};

/**
 * @struct T_mkSpKey
 * @brief Déclaration de la structure T_mkSpKey.
 *
 */

typedef struct T_mkSpKey T_mkSpKey;
struct T_mkSpKey
{
   unsigned_t capslock:1;                                         /*!< Ce membre contient l'état de la touche CAPS_LOCK. */
   unsigned_t numlock:1;                                          /*!< Ce membre contient l'état de la touche NUM_LOCK. */
   unsigned_t scrolllock:1;                                       /*!< Ce membre contient l'état de la touche SCROLL_LOCK. */
   unsigned_t reserved:29;                                        /*!< Ce champ est reservé pour un usage ultérieur. */
};

/**
 * @struct T_mkKeyboardLayer
 * @brief Déclaration de la structure T_mkKeyboardLayer.
 *
 */

typedef struct T_mkKeyboardLayer T_mkKeyboardLayer;
struct T_mkKeyboardLayer
{
   uint16_t type;                                                 /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_KEYBOARD). Il est utilisé pour identifier les contrôles applicatif. La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                                   /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkKeyboard. La position de cet attribut ne doit pas être modifiée. */
   uint16_t lang;                                                 /*!< Ce membre contient la topologie du clavier (AZERTY, QWERTY, ... ). */
   uint16_t countryCode;                                          /*!< Ce membre contient le code pays du clavier. */
};

/**
 * @struct T_mkKeyboard
 * @brief Déclaration de la structure T_mkKeyboard.
 *
 */

typedef struct T_mkKeyboard T_mkKeyboard;
struct T_mkKeyboard
{
   T_mkKeyboardLayer  layer;                                      /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkKeyboard. La position de cet attribut ne doit pas être modifiée. */
   T_mkKeyCode* modifier;                                         /*!< Ce membre contient l'état des touches CTRL, ALT, GUI, ... du clavier. */
   T_mkKey* input;                                                /*!< Ce membre contient une liste de contrôle de type \ref T_mkKey. Ils stockent les informations relatives à la touche pressée (Scancode) */
   T_mkUTFKey* output;                                            /*!< Ce membre contient les informations à transmettre à la tâche de gestion des événements (listener) suite au traitement de la combinaison de touches saisies. */
   T_mkLed* indicator;                                            /*!< Ce membre contient l'état des voyants du clavier. */
   T_mkSpKey specialKey;                                          /*!< Ce membre contient l'état des touches spéciales du clavier. */
   T_mkKeyboardLookup lookup;                                     /*!< Ce membre contient l'adresse de la table de correspondance du clavier. */
};

/**
 * @struct T_mkKeyboardPool
 * @brief Déclaration de la structure T_mkKeyboardPool.
 *
 */

typedef struct T_mkKeyboardPool T_mkKeyboardPool;
struct T_mkKeyboardPool
{
   T_mkPoolArea area;                                             /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                                                /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkKeyboard. */
   T_mkKeyboard heap [ K_MK_KEYBOARD_NUMBER ];                    /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkKeyboard. */
};


/**
 *
 */

#endif

