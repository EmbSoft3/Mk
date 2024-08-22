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
* @file mk_hid_dispatcher_private.h
* @brief Déclaration des fonctions privées dédiées au dispatcher HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_DISPATCHER_PRIVATE_H
#define MK_HID_DISPATCHER_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_dispatchInput ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction récupère la valeur de chaque usage d'entrée d'un périphérique HID. Elle transmet ensuite la valeur
 *        des entrées aux dispatcher pour qu'il puisse générer les événements adéquates.
 *
 * @param[in]      p_handler   Ce paramètre contient l'adresse d'un gestionnaire HID de type \ref T_mkHIDHandler.
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le dispatch des entrées a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le dispatch des entrées a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le dispatch des entrées a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le dispatch des entrées a échoué car le périphérique cible n'a pas répondu à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le dispatch des entrées a échoué car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_dispatchInput ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_dispatchOutput ( T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction récupère la valeur de chaque usage de sortie d'un périphérique HID. Elle transmet ensuite la valeur
 *        des sorties aux périphérique HID.
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le dispatch des sorties a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le dispatch des sorties a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le dispatch des sorties a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le dispatch des sorties a échoué car le périphérique cible n'a pas répondu à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le dispatch des sorties a échoué car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_dispatchOutput ( T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_dispatchMessage ( T_mkHIDReport* p_report, uint16_t p_ctrlEvt );
 * @brief Cette fonction transmet un événement au dispatcher.
 *
 * @param[in] p_report  Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport.
 * @param[in] p_ctrlEvt Ce paramètre contient l'identifiant d'un contrôle. Les champs de la structure \ref T_mkCtrlEvent peuvent être utilisés.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'événement a été envoyé au dispatcher.
 *         \li \ref K_MK_ERROR_PARAM   : l'événement n'a pas été envoyé au dispatcher car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_dispatchMessage ( T_mkHIDReport* p_report, uint16_t p_ctrlEvt );

/**
 *
 */

#endif


