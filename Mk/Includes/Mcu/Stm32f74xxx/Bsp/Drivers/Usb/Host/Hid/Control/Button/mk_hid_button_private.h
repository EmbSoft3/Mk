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
* @file mk_hid_button_private.h
* @brief Déclaration des fonctions dédiées aux objets 'Button'.
* @date 31 oct. 2019
*
*/

#ifndef MK_HID_BUTTON_PRIVATE_H
#define MK_HID_BUTTON_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_button_initPool ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux objets de type \ref T_mkButton.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire d'allocation dynamique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_button_initPool ( void );

/**
 * @fn T_mkCode mk_hid_button_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_buttonNumber );
 * @brief Cette fonction alloue une liste chainée composée de p_buttonNumber boutons puis l'assigne à un usage.
 *
 * @param[in] p_table        Ce paramètre contient l'adresse de la table des items globaux et locaux.
 * @param[in] p_usage        Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 * @param[in] p_buttonNumber Ce paramètre contient le nombre de boutons à allouer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les boutons ont été alloué.
 *         \li \ref K_MK_ERROR_PARAM  : les boutons n'ont pas été alloués car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les boutons n'ont pas été alloués car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les boutons n'ont pas été alloués car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_button_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_buttonNumber );

/**
 * @fn T_mkButton** mk_hid_button_getLast ( T_mkButton** p_button );
 * @brief Cette fonction retourne l'adresse du dernier pointeur de boutons d'une liste.
 * @param[in] p_button Ce paramètre contient l'adresse d'un élément de la liste.
 *
 * @return Cette fonction retourne la valeur \ref K_MK_NULL si la liste est vide sinon l'adresse du dernier bouton de la liste.
 */

T_mkButton** mk_hid_button_getLast ( T_mkButton** p_button );

/**
 * @fn T_mkCode mk_hid_button_setType ( T_mkButton* p_button, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction configure le type d'un bouton selon le standard HID. Le type peut évolué parmis une des valeurs suivantes : \n
 *        \ref K_MK_BUTTON_UNKNOWN_CONTROL, \ref K_MK_BUTTON_SELECTOR_CONTROL, \ref K_MK_BUTTON_MOMENTARY_CONTROL, \ref K_MK_BUTTON_ONE_SHOT_CONTROL,
 *        \ref K_MK_BUTTON_ON_OFF_CONTROL et \ref K_MK_BUTTON_TOOGLE_ON_OFF_CONTROL
 *
 * @param[in] p_button Ce paramètre contient l'adresse d'un objet de type \ref T_mkButton.
 * @param[in] p_table  Ce paramètre contient l'adresse de la table des items globaux et locaux.
 * @param[in] p_usage  Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le type du bouton a été configuré.
 *         \li \ref K_MK_ERROR_PARAM  : le type du bouton n'a pas été configuré car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_button_setType ( T_mkButton* p_button, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 * @fn T_mkCode mk_hid_button_delete ( T_mkButton* p_button );
 * @brief Cette fonction désalloue les éléments d'une liste chainée de type \ref T_mkButton.
 * @param[in] p_button Ce paramètre contient l'adresse du premier élément de la liste.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les boutons ont été désalloués.
 *         \li \ref K_MK_ERROR_PARAM  : les boutons n'ont pas été désalloués car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les boutons n'ont pas été désalloués car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les boutons n'ont pas été désalloués car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_button_delete ( T_mkButton* p_button );

/**
 *
 */

#endif

