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
* @file mk_hid_mouse_private.h
* @brief Déclaration des fonctions privées dédiées aux objets 'Mouse'.
* @date 31 oct. 2019
*
*/

#ifndef MK_HID_MOUSE_PRIVATE_H
#define MK_HID_MOUSE_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_mouse_initPool ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux objets de type \ref T_mkMouse.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le gestionnaire d'allocation dynamique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_mouse_initPool ( void );

/**
 * @fn T_mkCode mk_hid_mouse_delete ( T_mkMouse* p_mouse );
 * @brief Cette fonction désalloue la mémoire allouée par une souris de type \ref T_mkMouse.
 * @param[in] p_mouse Ce paramètre contient l'adresse d'un contrôle de type \ref T_mkMouse.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : la mémoire a été désallouée.
 *         \li \ref K_MK_ERROR_PARAM  : la mémoire n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : la mémoire n'a pas été désallouée car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : la mémoire n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_mouse_delete ( T_mkMouse* p_mouse );

/**
 * @fn T_mkCode mk_hid_mouse_handleEvents ( T_mkMouse* p_mouse, T_mkContainer* p_container, T_mkCtrlEvent p_mkEvtCtrl );
 * @brief Cette fonction est exécutée par le système, elle réalise les traitements adéquates lorsque les événements \ref K_MK_EVENT_CONNECT, \ref K_MK_EVENT_DISCONNECT et \ref K_MK_EVENT_MOVE
 *        sont reçus.
 *
 * @param[in] p_mouse     Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[in] p_container Ce paramètre contient l'adresse d'un objet de type \ref T_mkContainer.
 * @param[in] p_mkEvtCtrl Ce paramètre contient l'identifiant d'un événement de type \ref T_mkCtrlEvent.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le traitement des événements s'est déroulé sans rencontrer d'erreur.
*          \li \ref K_MK_ERROR_PARAM   : le traitement des événements a échoué car au moins un paramètre est invalide.
*          \li \ref K_MK_ERROR_ISR     : le traitement des événements a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
*/

T_mkCode mk_hid_mouse_handleEvents ( T_mkMouse* p_mouse, T_mkContainer* p_container, T_mkCtrlEvent p_mkEvtCtrl );

/**
 * @fn T_mkCode mk_hid_mouse_handleSubEvents ( T_mkField* p_field, T_mkMouse* p_mouse, T_mkCtrlEvent p_mainEvtCtrl, T_mkCtrlEvent* p_subEvtCtrl );
 * @brief Cette fonction est exécutée par le système. Elle permet de générer des événements secondaires à partir des événements primaire généré par le dispatcher.
 *
 * @param[in] p_mouse       Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[in] p_field       Ce paramètre contient l'adresse d'un objet de type \ref T_mkField.
 * @param[in] p_mainEvtCtrl Ce paramètre contient l'identifiant de l'événement primaire.
 * @param[out] p_usbEvtCtrl Ce paramètre contient l'identifiant de l'événement secondaire. La valeur \ref K_MK_EVENT_NO est écrite si aucun événement secondaire n'est généré.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le traitement des événements s'est déroulé sans rencontrer d'erreur.
*          \li \ref K_MK_ERROR_PARAM   : le traitement des événements a échoué car au moins un paramètre est invalide.
*          \li \ref K_MK_ERROR_ISR     : le traitement des événements a échoué car cette fonction a été exécutée depuis un vecteur d'interruption.
*/

T_mkCode mk_hid_mouse_handleSubEvents ( T_mkMouse* p_mouse, T_mkField* p_field, T_mkCtrlEvent p_mainEvtCtrl, T_mkCtrlEvent* p_subEvtCtrl );

/**
 * @fn T_mkCode mk_mouse_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut du curseur d'une souris de type \ref T_mkMouse. Elle est exécutée
 *        à intervalle régulier par le moteur graphique.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkCursor.
 *                          L'adresse du curseur peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le traitement de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le traitement de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le traitement de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le traitement de la fonction de peinture a échoué car aucun emplaçement mémoire ne s'est libéré dans le timeout imparti.
 *         \li \ref K_MK_ERROR_RIGHT   : le traitement de la fonction de peinture a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_mouse_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif

