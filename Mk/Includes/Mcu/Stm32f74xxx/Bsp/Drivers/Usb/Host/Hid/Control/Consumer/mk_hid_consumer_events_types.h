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
* @file mk_hid_consumer_events_types.h
* @brief Déclaration des types dédiés aux événements des objets 'Consumer'.
* @date 19 avr. 2020
*
*/

#ifndef MK_HID_CONSUMER_EVENTS_TYPES_H
#define MK_HID_CONSUMER_EVENTS_TYPES_H

/**
 * @enum T_mkConsumerEvent
 * @brief Déclaration de la structure T_mkConsumerEvent.
 *
 */

typedef enum T_mkConsumerEvent
{
   K_MK_CONSUMER_NEXT_TRACK = 0xB5,                      /*!< Identifiant du contrôle NEXT_TRACK. */
   K_MK_CONSUMER_PREVIOUS_TRACK = 0xB6,                  /*!< Identifiant du contrôle PREVIOUS_TRACK. */
   K_MK_CONSUMER_STOP = 0xB7,                            /*!< Identifiant du contrôle STOP. */
   K_MK_CONSUMER_PLAY_PAUSE = 0xCD,                      /*!< Identifiant du contrôle PLAY_PAUSE. */
   K_MK_CONSUMER_MUTE = 0xE2,                            /*!< Identifiant du contrôle MUTE. */
   K_MK_CONSUMER_VOLUME_INCREMENT = 0xE9,                /*!< Identifiant du contrôle VOLUME_INCREMENT. */
   K_MK_CONSUMER_VOLUME_DECREMENT = 0xEA,                /*!< Identifiant du contrôle VOLUME_DECREMENT. */
   K_MK_CONSUMER_CTRL_CONFIGURATION_TOOL = 0x183,        /*!< Identifiant du contrôle CONFIGURATION_TOOL. */
   K_MK_CONSUMER_EMAIL_READER = 0x18A,                   /*!< Identifiant du contrôle EMAIL_READER. */
   K_MK_CONSUMER_CALCULATOR = 0x192,                     /*!< Identifiant du contrôle CALCULATOR. */
   K_MK_CONSUMER_HOME = 0x223                            /*!< Identifiant du contrôle HOME. */
} T_mkConsumerEvent;

/**
 *
 */

#endif

