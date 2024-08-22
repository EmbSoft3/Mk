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
* @file mk_hid_keyboard_data.h
* @brief Déclaration des données dédiées aux objets 'Keyboard'.
* @date 15 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_DATA_H
#define MK_HID_KEYBOARD_DATA_H

/**
 * @fn T_mkKeyboardPool g_mkKeyboardPool;
 * @brief Déclaration de la zone mémoire permettant l'allocation dynamique des objets de type \ref T_mkKeyboard.
 *
 */

extern T_mkKeyboardPool g_mkKeyboardPool;

/**
 * @fn int8_t g_mkHidLookupTable;
 * @brief Déclaration de la table de correspondance des caractères AZERTY.
 *
 */

extern const int8_t g_mkHidLookupTable [ ];

/**
 * @fn int32_t g_mkHidFrExtendedAzertyLookupTable;
 * @brief Déclaration de la table de correspondance des caractères AZERTY(FR) étendue.
 *
 */

extern const uint32_t g_mkHidFrExtendedAzertyLookupTable [ ];

/**
 *
 */

#endif

