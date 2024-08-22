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
* @file mk_hid_keyboard.h
* @brief Déclaration des fonctions publiques dédiées aux objets 'Keyboard'.
* @date 18 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_H
#define MK_HID_KEYBOARD_H

/**
 * @fn T_mkCode mk_hid_keyboard_getID ( T_mkKeyboard* p_keyboard, uint16_t* p_id );
 * @brief Cette fonction retourne l'identifiant d'un clavier de type \ref T_mkKeyboard.
 *
 * @param[in]  p_keyboard Ce paramètre contient l'adresse d'un objet de type \ref T_mkKeyboard.
 * @param[out] p_id       Ce paramètre contient l'identifiant du clavier.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_keyboard_getID ( T_mkKeyboard* p_keyboard, uint16_t* p_id );

/**
 * @fn void mk_hid_keyboard_setCountryCode ( T_mkKeyboard* p_keyboard, uint16_t p_countryCode );
 * @brief Cette fonction assigne une table de correspondance à un clavier en fonction d'un code pays.
 *
 * @param[in]  p_keyboard    Ce paramètre contient l'adresse d'un objet de type \ref T_mkKeyboard.
 * @param[out] p_countryCode Ce paramètre contient le code pays d'un clavier. Les constantes définie dans l'énumération
 *                           \ref T_mkHIDCountryCode peuvent être utilisées.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_keyboard_setCountryCode ( T_mkKeyboard* p_keyboard, uint16_t p_countryCode );

/**
 *
 */

#endif


