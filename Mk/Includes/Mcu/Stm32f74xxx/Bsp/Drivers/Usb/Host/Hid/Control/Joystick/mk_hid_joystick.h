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
* @file mk_hid_joystick.h
* @brief Déclaration des fonctions publiques dédiées aux objets 'Joystick'.
* @date 25 avr. 2020
*
*/

#ifndef MK_HID_JOYSTICK_H
#define MK_HID_JOYSTICK_H

/**
 * @fn T_mkCode mk_hid_joystick_getID ( T_mkJoystick* p_joystick, uint16_t* p_id );
 * @brief Cette fonction retourne l'identifiant d'un joystick de type \ref T_mkJoystick.
 *
 * @param[in]  p_joystick Ce paramètre contient l'adresse d'un objet de type \ref T_mkJoystick.
 * @param[out] p_id       Ce paramètre contient l'adresse d'une variable où est stocké l'identifiant d'un joystick.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas correctement exécutée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_joystick_getID ( T_mkJoystick* p_joystick, uint16_t* p_id );

/**
 * @fn T_mkCode mk_hid_joystick_getStick ( T_mkJoystick* p_joystick, T_mkStick3* p_stick );
 * @brief Cette fonction retourne la valeur de chaque attribut du stick d'un joystick de type \ref T_mkJoystick.
 *
 * @param[in]  p_joystick Ce paramètre contient l'adresse d'un objet de type \ref T_mkJoystick.
 * @param[out] p_stick    Ce paramètre contient l'adresse d'une variable où sont copiés les attributs du stick.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas correctement exécutée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_joystick_getStick ( T_mkJoystick* p_joystick, T_mkStick3* p_stick );

/**
 * @fn T_mkCode mk_hid_joystick_getThrottle ( T_mkJoystick* p_joystick, T_mkThrottle* p_throttle );
 * @brief Cette fonction retourne la valeur de chaque attribut du throttle d'un joystick de type \ref T_mkJoystick.
 *
 * @param[in]  p_joystick Ce paramètre contient l'adresse d'un objet de type \ref T_mkJoystick.
 * @param[out] p_throttle Ce paramètre contient l'adresse d'une variable où sont copiés les attributs du throttle.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas correctement exécutée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_joystick_getThrottle ( T_mkJoystick* p_joystick, T_mkThrottle* p_throttle );

/**
 *
 */

#endif

