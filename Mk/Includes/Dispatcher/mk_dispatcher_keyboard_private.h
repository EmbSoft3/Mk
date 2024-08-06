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
* @file mk_dispatcher_keyboard_private.h
* @brief Déclaration des fonctions privées dédiées aux claviers.
* @date 22 déc. 2019
*
*/

#ifndef MK_DISPATCHER_KEYBOARD_PRIVATE_H
#define MK_DISPATCHER_KEYBOARD_PRIVATE_H

/**
 * @fn T_mkCode mk_dispatcher_translateCode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler, T_mkKey* p_key );
 * @brief Cette fonction convertit un scancode en caractère affichable.
 *
 * @param[in]  p_handler    Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[out] p_message    Ce paramètre contient l'adresse d'un message de type \ref T_mkListenerMessage. Il n'est pas utilisé par la fonction.
 * @param[in]  p_keyboard   Ce paramètre contient l'adresse d'un clavier de type \ref T_mkKeyboard.
 * @param[in]  p_keyHandler Ce paramètre contient l'adresse d'un gestionnaire de touche de type \ref T_mkKeyHandler.
 * @param[out] p_key        Ce paramètre contient l'adresse d'une touche de type \ref T_mkKey.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la conversion du scancode a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la conversion du scancode a échoué.
 */

T_mkCode mk_dispatcher_translateCode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler, T_mkKey* p_key );

/**
 * @fn T_mkCode mk_dispatcher_handleScancode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler );
 * @brief Cette fonction génére un ou plusieurs événements contenant les caractères affichables saisis par l'utilisateur sur un clavier.
 *        Les événements sont \ref K_MK_EVENT_CHAR_UP, \ref K_MK_EVENT_CHAR_HOLD, \ref K_MK_EVENT_CHAR_DOWN, \ref K_MK_EVENT_KEY_POSTFAIL et \ref K_MK_EVENT_KEY_ROLLOVER.
 *
 * @param[in]  p_handler    Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[out] p_message    Ce paramètre contient l'adresse d'un message de type \ref T_mkListenerMessage. Il n'est pas utilisé par la fonction.
 * @param[in]  p_keyboard   Ce paramètre contient l'adresse d'un clavier de type \ref T_mkKeyboard.
 * @param[in]  p_keyHandler Ce paramètre contient l'adresse d'un gestionnaire de touche de type \ref T_mkKeyHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleScancode ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler );

/**
 * @fn T_mkCode mk_dispatcher_handleModifier ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler );
 * @brief Cette fonction génére un ou plusieurs événements contenant les modificateurs saisis par l'utilisateur sur un clavier.
 *        Les événements sont \ref K_MK_EVENT_KEY_UP, \ref K_MK_EVENT_KEY_HOLD et \ref K_MK_EVENT_KEY_DOWN.
 *
 * @param[in]  p_handler    Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[out] p_message    Ce paramètre contient l'adresse d'un message de type \ref T_mkListenerMessage. Il n'est pas utilisé par la fonction.
 * @param[in]  p_keyboard   Ce paramètre contient l'adresse d'un clavier de type \ref T_mkKeyboard.
 * @param[in]  p_keyHandler Ce paramètre contient l'adresse d'un gestionnaire de touche de type \ref T_mkKeyHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la génération de l'événement a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la génération de l'événement a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la génération de l'événement a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la génération de l'événement a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la génération de l'événement a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleModifier ( T_mkDispatcherHandler* p_handler, T_mkListenerMessage* p_message, T_mkKeyboard* p_keyboard, T_mkKeyHandler* p_keyHandler );

/**
 * @fn T_mkCode mk_dispatcher_handleIndicator ( T_mkDispatcherHandler* p_handler, T_mkKeyboard* p_keyboard, T_mkKey* p_key );
 * @brief Cette fonction pilote les indicateurs lumineux d'un clavier en fonction des touches saisies par l'utilisateur.
 *
 * @param[in] p_handler  Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkDispatcherHandler.
 * @param[in] p_keyboard Ce paramètre contient l'adresse d'un clavier de type \ref T_mkKeyboard.
 * @param[in] p_key      Ce paramètre contient l'adresse d'une touche de type \ref T_mkKey.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pilotage des indicateurs lumineux a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le pilotage des indicateurs lumineux a échouécar au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le pilotage des indicateurs lumineux a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : le pilotage des indicateurs lumineux a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le pilotage des indicateurs lumineux a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 */

T_mkCode mk_dispatcher_handleIndicator ( T_mkDispatcherHandler* p_handler, T_mkKeyboard* p_keyboard, T_mkKey* p_key );

/**
 *
 */

#endif

