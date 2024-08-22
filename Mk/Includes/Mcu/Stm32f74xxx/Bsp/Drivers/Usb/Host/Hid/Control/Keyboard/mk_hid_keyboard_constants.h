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
* @file mk_hid_keyboard_constants.h
* @brief Déclaration des constantes dédiées aux objets 'Keyboard'.
* @date 15 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_CONSTANTS_H
#define MK_HID_KEYBOARD_CONSTANTS_H

/**
 * @def K_MK_KEYBOARD_NUMBER
 * @brief Définition du nombre d'objets de type \ref T_mkKeyboard pouvant être alloués.
 */

#define K_MK_KEYBOARD_NUMBER 10

/**
 * @def K_MK_KEYBOARD_SUBTABLE_SIZE
 * @brief Définition de la taille [en octets] des segments de données présents dans la
 *        table de correspondance du clavier (\ref g_mkHidLookupTable).
 */

#define K_MK_KEYBOARD_SUBTABLE_SIZE 232

/**
 * @def K_MK_KEYBOARD_HOLD_INHIBITION_DURATION
 * @brief Définition de la durée minimale [en ms] entre la génération de l'événement 'DOWN'
 *        et le premier événement 'HOLD'.
 */

#define K_MK_KEYBOARD_HOLD_INHIBITION_DURATION 500

/**
 * @def K_MK_KEYBOARD_HOLD_RATE
 * @brief Définition de la durée minimale [en ms] entre la génération de deux événements 'HOLD'.
 */

#define K_MK_KEYBOARD_HOLD_RATE 100

/**
 *
 */

#endif


