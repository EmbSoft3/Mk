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
* @file mk_hid_led_private.h
* @brief Déclaration des fonctions privées dédiées aux objets 'Led'.
* @date 3 janv. 2020
*
*/

#ifndef MK_HID_LED_PRIVATE_H
#define MK_HID_LED_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_led_initPool ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux objets de type \ref T_mkLed.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire d'allocation dynamique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_led_initPool ( void );

/**
 * @fn T_mkCode mk_hid_led_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_ledNumber );
 * @brief Cette fonction alloue une liste chainée composée de p_ledNumber led puis l'assigne à un usage.
 *
 * @param[in] p_table     Ce paramètre contient l'adresse de la table des items globaux et locaux.
 * @param[in] p_usage     Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 * @param[in] p_ledNumber Ce paramètre contient le nombre de led de type \ref T_mkLed à allouer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les led ont été allouées .
 *         \li \ref K_MK_ERROR_PARAM  : les led n'ont pas été allouées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les led n'ont pas été allouées car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les led n'ont pas été allouées car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_led_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_ledNumber );

/**
 * @fn T_mkLed** mk_hid_led_getLast ( T_mkLed** p_led );
 * @brief Cette fonction retourne l'adresse du dernier pointeur de type \ref T_mkLed d'une liste.
 * @param[in] p_led Ce paramètre contient l'adresse d'un élément de la liste.
 *
 * @return Cette fonction retourne la valeur \ref K_MK_NULL si la liste est vide sinon l'adresse de la dernière led de la liste.
 */

T_mkLed** mk_hid_led_getLast ( T_mkLed** p_led );

/**
 * @fn T_mkCode mk_hid_led_setType ( T_mkLed* p_led, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction configure le type d'une LED selon le standard HID. Le type peut évolué parmis une des valeurs suivantes : \n
 *        \ref K_MK_LED_UNKNOWN_CONTROL, \ref K_MK_LED_SELECTOR_CONTROL et \ref K_MK_LED_ON_OFF_CONTROL
 *
 * @param[in] p_led   Ce paramètre contient l'adresse d'un objet de type \ref T_mkLed.
 * @param[in] p_table Ce paramètre contient l'adresse de la table des items globaux et locaux.
 * @param[in] p_usage Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le type de la led a été configuré.
 *         \li \ref K_MK_ERROR_PARAM  : le type de la led n'a pas été configuré car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_led_setType ( T_mkLed* p_led, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 * @fn T_mkCode mk_hid_led_delete ( T_mkLed* p_led );
 * @brief Cette fonction désalloue les éléments d'une liste chainée de type \ref T_mkLed.
 * @param[in] p_led Ce paramètre contient l'adresse du premier élément de la liste.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les led ont été désallouées.
 *         \li \ref K_MK_ERROR_PARAM  : les led n'ont pas été désallouées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les led n'ont pas été désallouées car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les led n'ont pas été désallouées car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_led_delete ( T_mkLed* p_led );

/**
 *
 */

#endif

