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
* @file mk_hid_keyboard_private.h
* @brief Déclaration des fonctions privées dédiées aux objets 'Keyboard'.
* @date 15 déc. 2019
*
*/

#ifndef MK_HID_KEYBOARD_PRIVATE_H
#define MK_HID_KEYBOARD_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_keyboard_initPool ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux claviers de type \ref T_mkKeyboard.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire d'allocation dynamique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_keyboard_initPool ( void );

/**
 * @fn T_mkCode mk_hid_keyboard_delete ( T_mkKeyboard* p_keyboard );
 * @brief Cette fonction désalloue la mémoire allouée par un clavier de type \ref T_mkKeyboard.
 * @param[in] p_keyboard Ce paramètre contient l'adresse d'un contrôle de type \ref T_mkKeyboard.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : la mémoire a été désallouée.
 *         \li \ref K_MK_ERROR_PARAM  : la mémoire n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : la mémoire n'a pas été désallouée car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : la mémoire n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_keyboard_delete ( T_mkKeyboard* p_keyboard );

/**
 * @fn T_mkCode mk_hid_keyboard_handleEvents ( T_mkKeyboard* p_keyboard, T_mkCtrlEvent p_mkEvtCtrl );
 * @brief Cette fonction est réservée, elle ne réalise aucun traitement.
 *
 * @param[in] p_keyboard  Ce paramètre contient l'adresse d'un objet de type \ref T_mkKeyboard.
 * @param[in] p_mkEvtCtrl Ce paramètre contient l'identifiant d'un événement de type \ref T_mkCtrlEvent.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le traitement des événements s'est déroulé sans rencontrer d'erreur.
*          \li \ref K_MK_ERROR_PARAM : le traitement des événements a échoué car au moins un paramètre est invalide.
*/

T_mkCode mk_hid_keyboard_handleEvents ( T_mkKeyboard* p_keyboard, T_mkCtrlEvent p_mkEvtCtrl );

/**
 *
 */

#endif

