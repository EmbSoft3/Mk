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
* @file mk_display_events_types.h
* @brief Déclaration des types dédiés au module 'Events'.
* @date 3 mai 2019
*
*/

#ifndef MK_DISPLAY_EVENTS_TYPES_H
#define MK_DISPLAY_EVENTS_TYPES_H

/**
 * @enum T_mkCtrlEvent
 * @brief Déclaration de la structure T_mkCtrlEvent.
 */

typedef enum T_mkCtrlEvent
{
   K_MK_EVENT_NO = 0,                  /*!< Identifiant de l'événement de type 'No'. */
   K_MK_EVENT_ON = 1,                  /*!< Identifiant de l'événement de type 'On'. */
   K_MK_EVENT_PRESS = 1,               /*!< Identifiant de l'événement de type 'Press'. */
   K_MK_EVENT_XPRESS = 2,              /*!< Identifiant de l'événement de type 'XPress'. */
   K_MK_EVENT_OFF = 3,                 /*!< Identifiant de l'événement de type 'Off'. */
   K_MK_EVENT_PUSH = 3,                /*!< Identifiant de l'événement de type 'Push'. */
   K_MK_EVENT_RELEASE = 3,             /*!< Identifiant de l'événement de type 'Release'. */
   K_MK_EVENT_XRELEASE = 4,            /*!< Identifiant de l'événement de type 'XRelease'. */
   K_MK_EVENT_CLICK = 5,               /*!< Identifiant de l'événement de type 'Click'. */
   K_MK_EVENT_XCLICK = 6,              /*!< Identifiant de l'événement de type 'XClick'. */
   K_MK_EVENT_DOUBLE_CLICK = 7,        /*!< Identifiant de l'événement de type 'DoubleClick'. */
   K_MK_EVENT_DOUBLE_XCLICK = 8,       /*!< Identifiant de l'événement de type 'DoubleXClick'. */
   K_MK_EVENT_MOVE = 9,                /*!< Identifiant de l'événement de type 'Move'. */
   K_MK_EVENT_ENTER = 10,              /*!< Identifiant de l'événement de type 'Enter'. */
   K_MK_EVENT_EXIT = 11,               /*!< Identifiant de l'événement de type 'Exit'. */
   K_MK_EVENT_VSCROLL = 12,            /*!< Identifiant de l'événement de type 'VScroll'. */
   K_MK_EVENT_HSCROLL = 13,            /*!< Identifiant de l'événement de type 'HScroll'. */
   K_MK_EVENT_CONNECT = 14,            /*!< Identifiant de l'événement de type 'Connect'. */
   K_MK_EVENT_DISCONNECT = 15,         /*!< Identifiant de l'événement de type 'Disconnect'. */
   K_MK_EVENT_KEY_ROLLOVER = 16,       /*!< Identifiant de l'événement de type 'KeyRollOver'. */
   K_MK_EVENT_KEY_POSTFAIL = 17,       /*!< Identifiant de l'événement de type 'KeyPostFail'. */
   K_MK_EVENT_KEY_DOWN = 18,           /*!< Identifiant de l'événement de type 'KeyDown'. */
   K_MK_EVENT_KEY_HOLD = 19,           /*!< Identifiant de l'événement de type 'KeyHold'. */
   K_MK_EVENT_KEY_UP = 20,             /*!< Identifiant de l'événement de type 'KeyUp'. */
   K_MK_EVENT_CHAR_DOWN = 21,          /*!< Identifiant de l'événement de type 'CharDown'. */
   K_MK_EVENT_CHAR_HOLD = 22,          /*!< Identifiant de l'événement de type 'CharHold'. */
   K_MK_EVENT_CHAR_UP = 23,            /*!< Identifiant de l'événement de type 'CharUp'. */
   K_MK_EVENT_HAT_SWITCH_UP = 24,      /*!< Identifiant de l'événement de type 'HatSwitchUp'. */
   K_MK_EVENT_HAT_SWITCH_DOWN = 25,    /*!< Identifiant de l'événement de type 'HatSwitchDown'. */
   K_MK_EVENT_THROTTLE = 26,           /*!< Identifiant de l'événement de type 'Throttle'. */
   K_MK_EVENT_MOUNT = 27,              /*!< Identifiant de l'événement de type 'Mount'. */
   K_MK_EVENT_UNMOUNT = 28,            /*!< Identifiant de l'événement de type 'Unmount'. */
   K_MK_EVENT_LOCK = 29,               /*!< Identifiant de l'événement de type 'Lock'. */
   K_MK_EVENT_UNLOCK = 30,             /*!< Identifiant de l'événement de type 'Unlock'. */
   K_MK_EVENT_REFRESH = 31,            /*!< Identifiant de l'événement de type 'Refresh'. */
   K_MK_EVENT_CLOSE = 32,              /*!< Identifiant de l'événement de type 'Cose'. */
   K_MK_EVENT_METADATA = 33,           /*!< Identifiant de l'événement de type 'Metadata'. */
   K_MK_EVENT_LAUNCH = 34,             /*!< Identifiant de l'événement de type 'Launch'. */
   K_MK_EVENT_INSTALL = 35,            /*!< Identifiant de l'événement de type 'Install'. */
   K_MK_EVENT_UNINSTALL = 36,          /*!< Identifiant de l'événement de type 'Uninstall'. */
   K_MK_EVENT_SUSPEND = 37,            /*!< Identifiant de l'événement de type 'Suspend'. */
   K_MK_EVENT_RESUME = 38,             /*!< Identifiant de l'événement de type 'Resume'. */
   K_MK_EVENT_DELETE = 39              /*!< Identifiant de l'événement de type 'Delete'. */
} T_mkCtrlEvent;

/**
 * @enum T_mkCtrlId
 * @brief Déclaration de la structure T_mkCtrlId.
 */

typedef enum T_mkCtrlId
{
   K_MK_CONTROL_SYSTEM = 0x0000,       /*!< Identifiant du contrôle de type 'System'. */
   K_MK_CONTROL_MOUSE = 0x0001,        /*!< Identifiant du contrôle de type 'Mouse'. */
   K_MK_CONTROL_KEYBOARD = 0x0002,     /*!< Identifiant du contrôle de type 'Keyboard'. */
   K_MK_CONTROL_CONSUMER = 0x00003,    /*!< Identifiant du contrôle de type 'Consumer'. */
   K_MK_CONTROL_JOYSTICK = 0x0004,     /*!< Identifiant du contrôle de type 'Joystick'. */
   K_MK_CONTROL_DISK = 0x0100,         /*!< Identifiant du contrôle de type 'Disk'. */
   K_MK_CONTROL_VOLUME = 0x0101,       /*!< Identifiant du contrôle de type 'Volume'. */
   K_MK_CONTROL_GPIO = 0x0200,         /*!< Identifiant du contrôle de type 'Gpio'. */
   K_MK_CONTROL_APPLICATION = 0x0300   /*!< Identifiant du contrôle de type 'Application'. */
} T_mkCtrlId;

/**
 *
 */

#endif


