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
* @file mk_hid_led_types.h
* @brief Déclaration des types dédiés aux objets 'Led'.
* @date 3 janv. 2020
*
*/

#ifndef MK_HID_LED_TYPES_H
#define MK_HID_LED_TYPES_H

/**
 * @enum T_mkLedType
 * @brief Déclaration de l'énumération T_mkLedType.
 *
 */

typedef enum T_mkLedType
{
   K_MK_LED_UNKNOWN_CONTROL = 0,                /*!< Définition du type 'Unknown' (le type de la led n'est pas reconnu). */
   K_MK_LED_SELECTOR_CONTROL = 1,               /*!< Définition du type 'Selector' selon la norme HID. */
   K_MK_LED_ON_OFF_CONTROL = 4                  /*!< Définition du type 'ON/OFF' selon la norme HID. */
} T_mkLedType;

/**
 * @struct T_mkLedLayer
 * @brief Déclaration de la structure T_mkLedLayer.
 *
 */

typedef struct T_mkLedLayer T_mkLedLayer;
struct T_mkLedLayer
{
   uint16_t id;                                 /*!< Ce membre contient l'identifiant d'un objet de type \ref T_mkLed. */
   uint16_t type;                               /*!< Ce membre contient le type d'un objet \ref T_mkLed (\ref T_mkLedType). */
   int32_t min;                                 /*!< Ce membre contient la valeur minimale de la Led. */
   int32_t max;                                 /*!< Ce membre contient la valeur maximale de la Led. */
};

/**
 * @struct T_mkLedState
 * @brief Déclaration de la structure T_mkLedState.
 *
 */

typedef struct T_mkLedState T_mkLedState;
struct T_mkLedState
{
   int16_t value;                               /*!< Ce membre contient l'état d'un objet de type \ref T_mkLed. La position de cet attribut ne doit pas être modifiée. */
   int16_t lastValue;                           /*!< Ce membre contient le dernier état d'un objet de type \ref T_mkLed. */
};

/**
 * @struct T_mkLed
 * @brief Déclaration de la structure T_mkLed.
 *
 */

typedef struct T_mkLed T_mkLed;
struct T_mkLed
{
   T_mkLed* nextLed;                            /*!< Ce membre contient l'adresse du prochain objet de type \ref T_mkLed. La position de cet attribut ne doit pas être modifiée. */
   T_mkLedState state;                          /*!< Ce membre contient le registre d'état d'un objet de type \ref T_mkLed. La position de cet attribut ne doit pas être modifiée. */
   T_mkLedLayer layer;                          /*!< Ce membre contient le registre d'identification d'un objet de type \ref T_mkLed. */
};

/**
 * @struct T_mkLedPool
 * @brief Déclaration de la structure T_mkLedPool.
 *
 */

typedef struct T_mkLedPool T_mkLedPool;
struct T_mkLedPool
{
   T_mkPoolArea area;                           /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                              /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkLed. */
   T_mkLed heap [ K_MK_LED_NUMBER ];            /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkLed. */
};

/**
 *
 */

#endif


