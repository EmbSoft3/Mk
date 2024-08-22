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
* @file mk_hid_button_types.h
* @brief Déclaration des types dédiés aux objets 'Button'.
* @date 31 oct. 2019
*
*/

#ifndef MK_HID_BUTTON_TYPES_H
#define MK_HID_BUTTON_TYPES_H

/**
 * @enum T_mkButtonType
 * @brief Déclaration de l'énumération T_mkButtonType.
 *
 */

typedef enum T_mkButtonType
{
   K_MK_BUTTON_UNKNOWN_CONTROL = 0,             /*!< Définition du type 'Unknown' qui indique que le type du bouton n'est pas reconnu */
   K_MK_BUTTON_SELECTOR_CONTROL = 1,            /*!< Définition du type 'Selector' selon la norme HID. */
   K_MK_BUTTON_MOMENTARY_CONTROL = 2,           /*!< Définition du type 'Momentary' selon la norme HID. */
   K_MK_BUTTON_ONE_SHOT_CONTROL = 3,            /*!< Définition du type 'One shot' selon la norme HID. */
   K_MK_BUTTON_ON_OFF_CONTROL = 4,              /*!< Définition du type 'ON/OFF' selon la norme HID. */
   K_MK_BUTTON_TOOGLE_ON_OFF_CONTROL = 5        /*!< Définition du type 'Toogle ON/OFF' selon la norme HID. */
} T_mkButtonType;

/**
 * @struct T_mkButton
 * @brief Déclaration de la structure T_mkButton.
 *
 */

typedef struct T_mkButtonState T_mkButtonState;
struct T_mkButtonState
{
   int16_t value;                               /*!< Ce membre contient l'état du bouton. La position de cet attribut ne doit pas être modifiée. */
   int16_t lastValue;                           /*!< Ce membre contient le dernier état du bouton enregistré. */
   uint16_t lastEvent;                          /*!< Ce membre contient le dernier événement du bouton enregistré. */
   uint16_t lastMemo;                           /*!< Ce membre contient le dernier mémo enregistré. */
};

/**
 * @struct T_mkButtonLayer
 * @brief Déclaration de la structure T_mkButtonLayer.
 *
 */

typedef struct T_mkButtonLayer T_mkButtonLayer;
struct T_mkButtonLayer
{
   uint16_t id;                                 /*!< Ce membre contient l'identifiant du bouton. */
   uint16_t type;                               /*!< Ce membre contient le type du bouton (\ref T_mkButtonType). */
};

/**
 * @struct T_mkButtonTick
 * @brief Déclaration de la structure T_mkButtonTick.
 *
 */

typedef struct T_mkButtonTick T_mkButtonTick;
struct T_mkButtonTick
{
   uint32_t pressTick;                          /*!< Ce membre contient la valeur du tick où un événement de type 'Press' s'est produit. */
   uint32_t clickTick;                          /*!< Ce membre contient la valeur du tick où un événement de type 'Click' s'est produit. */
   uint32_t clickCount;                         /*!< Ce membre contient le compteur d'événements 'Click'. */
};

/**
 * @struct T_mkButton
 * @brief Déclaration de la structure T_mkButton.
 *
 */

typedef struct T_mkButton T_mkButton;
struct T_mkButton
{
   T_mkButton* nextButton;                      /*!< Ce membre contient l'adresse du prochain bouton de la liste. La position de cet attribut ne doit pas être modifiée. */
   T_mkButtonState state;                       /*!< Ce membre contient le registre d'état du bouton. La position de cet attribut ne doit pas être modifiée. */
   T_mkButtonLayer layer;                       /*!< Ce membre contient le registre d'identification du bouton. */
   T_mkButtonTick tick;                         /*!< Ce membre contient les registres temporelles permettant la génération d'événements avancés. */
};

/**
 * @struct T_mkButtonPool
 * @brief Déclaration de la structure T_mkButtonPool.
 *
 */

typedef struct T_mkButtonPool T_mkButtonPool;
struct T_mkButtonPool
{
   T_mkPoolArea area;                           /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                              /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkButton. */
   T_mkButton heap [ K_MK_BUTTON_NUMBER ];      /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkButton. */
};

/**
 *
 */

#endif

