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
* @file mk_hid_joystick_types.h
* @brief Déclaration des types privés dédiés aux objets 'Joystick'.
* @date 22 avr. 2020
*
*/

#ifndef MK_HID_JOYSTICK_TYPES_H
#define MK_HID_JOYSTICK_TYPES_H

/**
 * @struct T_mkJoystickLayer
 * @brief Déclaration de la structure T_mkJoystickLayer.
 *
 */

typedef struct T_mkJoystickLayer T_mkJoystickLayer;
struct T_mkJoystickLayer
{
   uint16_t type;                               /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_JOYSTICK). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                 /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkJoystick. La position de cet attribut ne doit pas être modifiée. */
};

/**
 * @struct T_mkJoystick
 * @brief Déclaration de la structure T_mkJoystick.
 *
 */

typedef struct T_mkJoystick T_mkJoystick;
struct T_mkJoystick
{
   T_mkJoystickLayer layer;                     /*!< Ce membre contient le registre d'identification du contrôle de type \ref T_mkJoystick. La position de cet attribut ne doit pas être modifiée. */
   T_mkStick3 stick;                            /*!< Ce membre contient le contrôle de type \ref T_mkStick3 dédié au joystick. */
   T_mkThrottle throttle;                       /*!< Ce membre contient le contrôle de type \ref T_mkThrottle dédié au joystick. */
   T_mkHatSwitch hatSwitch;                     /*!< Ce membre contient le contrôle de type \ref T_mkHatSwitch dédié au joystick. */
   T_mkLed* indicator;                          /*!< Ce membre contient une liste de contrôle de type \ref T_mkLed dédié au joystick. */
   T_mkButton* button;                          /*!< Ce membre contient une liste de contrôle de type \ref T_mkButton dédié au joystick. */
};

/**
 * @struct T_mkJoystickPool
 * @brief Déclaration de la structure T_mkJoystickPool.
 *
 */

typedef struct T_mkJoystickPool T_mkJoystickPool;
struct T_mkJoystickPool
{
   T_mkPoolArea area;                           /*!< Ce membre contient un gestionnaire d'allocation dynamique ('Heap'). */
   T_mkPool* pool;                              /*!< Ce membre contient un gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkJoystick. */
   T_mkJoystick heap [ K_MK_JOYSTICK_NUMBER ];  /*!< Ce membre contient un buffer dédiée à la 'Heap'. */
};

/**
 *
 */

#endif

