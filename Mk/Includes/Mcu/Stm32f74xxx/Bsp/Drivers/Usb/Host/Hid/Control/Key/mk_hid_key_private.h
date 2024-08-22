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
* @file mk_hid_key_private.h
* @brief Déclaration des fonctions privées dédiées aux objets 'Key'
* @date 25 déc. 2019
*
*/

#ifndef MK_HID_KEY_PRIVATE_H
#define MK_HID_KEY_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_key_initPool ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux objets de type \ref T_mkKey.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire d'allocation dynamique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_key_initPool ( void );

/**
 * @fn T_mkCode mk_hid_key_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_keyNumber );
 * @brief Cette fonction alloue une liste chainée composée de p_keyNumber touches puis l'assigne à un usage.
 *
 * @param[in] p_table     Ce paramètre contient l'adresse de la table des items globaux et locaux.
 * @param[in] p_usage     Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 * @param[in] p_keyNumber Ce paramètre contient le nombre d'objet de type \ref T_mkKey à allouer.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les touches ont été allouées.
 *         \li \ref K_MK_ERROR_PARAM  : les touches n'ont pas été allouées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les touches n'ont pas été allouées car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les touches n'ont pas été allouées car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_key_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_keyNumber );

/**
 * @fn T_mkKey** mk_hid_key_getLast ( T_mkKey** p_key );
 * @brief Cette fonction retourne l'adresse du dernier pointeur de type \ref T_mkKey d'une liste.
 * @param[in] p_key Ce paramètre contient l'adresse d'un élément de la liste.
 *
 * @return Cette fonction retourne la valeur \ref K_MK_NULL si la liste est vide sinon l'adresse de la dernière touche de la liste.
 */

T_mkKey** mk_hid_key_getLast ( T_mkKey** p_key );

/**
 * @fn T_mkCode mk_hid_key_delete ( T_mkKey* p_key );
 * @brief Cette fonction désalloue les éléments d'une liste chainée de type \ref T_mkKey.
 * @param[in] p_key Ce paramètre contient l'adresse du premier élément de la liste.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les touches ont été désalloués.
 *         \li \ref K_MK_ERROR_PARAM  : les touches n'ont pas été désalloués car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : les touches n'ont pas été désalloués car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les touches n'ont pas été désalloués car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_key_delete ( T_mkKey* p_key );

/**
 *
 */

#endif
