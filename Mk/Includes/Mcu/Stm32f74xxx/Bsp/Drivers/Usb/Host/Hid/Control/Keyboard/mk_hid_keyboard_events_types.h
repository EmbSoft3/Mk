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
* @file mk_hid_keyboard_events_types.h
* @brief Déclaration des types dédiés aux événements des objets 'Keyboard'.
* @date 16 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_EVENTS_TYPES_H
#define MK_HID_KEYBOARD_EVENTS_TYPES_H

/**
 * @enum T_mkKeyboardEvent
 * @brief Déclaration de la structure T_mkKeyboardEvent.
 *
 */

typedef enum T_mkKeyboardEvent
{
   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           0         0        0          0          0               xx             */

   K_MK_KEYBOARD_ENTER = 0x0028,
   K_MK_KEYBOARD_ESCAPE = 0x0029,
   K_MK_KEYBOARD_BACKSPACE = 0x002A,
   K_MK_KEYBOARD_TABULATION = 0x002B,
   K_MK_KEYBOARD_CAPSLOCK = 0x0039,
   K_MK_KEYBOARD_F1 = 0x003A,
   K_MK_KEYBOARD_F2 = 0x003B,
   K_MK_KEYBOARD_F3 = 0x003C,
   K_MK_KEYBOARD_F4 = 0x003D,
   K_MK_KEYBOARD_F5 = 0x003E,
   K_MK_KEYBOARD_F6 = 0x003F,
   K_MK_KEYBOARD_F7 = 0x0040,
   K_MK_KEYBOARD_F8 = 0x0041,
   K_MK_KEYBOARD_F9 = 0x0042,
   K_MK_KEYBOARD_F10 = 0x0043,
   K_MK_KEYBOARD_F11 = 0x0044,
   K_MK_KEYBOARD_F12 = 0x0045,
   K_MK_KEYBOARD_PRINTSCREEN = 0x0046,
   K_MK_KEYBOARD_SCROLLLOCK = 0x0047,
   K_MK_KEYBOARD_PAUSE = 0x0048,
   K_MK_KEYBOARD_INSERT = 0x0049,
   K_MK_KEYBOARD_START = 0x004A,
   K_MK_KEYBOARD_PAGEUP = 0x004B,
   K_MK_KEYBOARD_DELETE = 0x004C,
   K_MK_KEYBOARD_END = 0x004D,
   K_MK_KEYBOARD_PAGEDOWN = 0x004E,
   K_MK_KEYBOARD_RIGHTARROW = 0x004F,
   K_MK_KEYBOARD_LEFTARROW = 0x0050,
   K_MK_KEYBOARD_DOWNARROW = 0x0051,
   K_MK_KEYBOARD_UPARROW = 0x0052,
   K_MK_KEYPAD_NUMLOCK = 0x0053,
   K_MK_KEYPAD_ENTER = 0x0058,
   K_MK_KEYBOARD_APPLICATION = 0x0065,
   K_MK_KEYBOARD_F13 = 0x0068,
   K_MK_KEYBOARD_F14 = 0x0069,
   K_MK_KEYBOARD_F15 = 0x006A,
   K_MK_KEYBOARD_F16 = 0x006B,
   K_MK_KEYBOARD_F17 = 0x006C,
   K_MK_KEYBOARD_F18 = 0x006D,
   K_MK_KEYBOARD_F19 = 0x006E,
   K_MK_KEYBOARD_F20 = 0x006F,
   K_MK_KEYBOARD_F21 = 0x0070,
   K_MK_KEYBOARD_F22 = 0x0071,
   K_MK_KEYBOARD_F23 = 0x0072,
   K_MK_KEYBOARD_F24 = 0x0073,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           0         0        0          0          1               xx             */

   K_MK_KEYBOARD_LEFTCTRL = 0x0100,
   K_MK_KEYBOARD_FR_LCOPY = 0x0106,
   K_MK_KEYBOARD_FR_LPAST = 0x0119,
   K_MK_KEYBOARD_FR_LCUT  = 0x011B,
   K_MK_KEYBOARD_FR_LUNDO = 0x011A,
   K_MK_KEYBOARD_FR_LREDO = 0x011C,
   K_MK_KEYBOARD_FR_LREFRESH = 0x0115,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           0         0        0          1          0               xx             */

   K_MK_KEYBOARD_LEFTSHIFT = 0x0200,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           0         0        1          0          0               xx             */

   K_MK_KEYBOARD_LEFTALT = 0x0400,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           0         1        0          0          0               xx             */

   K_MK_KEYBOARD_LEFTGUI = 0x0800,
   K_MK_KEYBOARD_STOP_MEDIA = 0x0804,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          0           1         0        0          0          0               xx             */

   K_MK_KEYBOARD_RIGHTCTRL = 0x0100,
   K_MK_KEYBOARD_FR_RCOPY = 0x1006,
   K_MK_KEYBOARD_FR_RPAST = 0x1019,
   K_MK_KEYBOARD_FR_RCUT  = 0x101B,
   K_MK_KEYBOARD_FR_RUNDO = 0x101A,
   K_MK_KEYBOARD_FR_RREDO = 0x101C,
   K_MK_KEYBOARD_FR_RREFRESH = 0x1015,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         0          1           0         0        0          0          0               xx             */

   K_MK_KEYBOARD_RIGHTSHIFT = 0x2000,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     0         1          0           0         0        0          0          0               xx             */

   K_MK_KEYBOARD_RIGHTALT = 0x4000,

   /* Modificateur */
   /*    D15       D14        D13         D12       D11      D10        D9         D8      D7      ...      D0     */
   /*  RightGUI  RightAlt  RightShift  RightCtrl  LeftGUI  LeftAlt   LeftShift   LeftCtrl        Scancode          */
   /*     1         0          0           0         0        0          0          0               xx             */

   K_MK_KEYBOARD_RIGHTGUI = 0x8000
} T_mkKeyboardEvent;

/**
 *
 */

#endif

