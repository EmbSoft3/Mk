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
* @file mk_hid_device_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques HID.
* @date 20 oct. 2019
*
*/

#ifndef MK_HID_DEVICE_PRIVATE_H
#define MK_HID_DEVICE_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_createDevice ( T_mkHIDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );
 * @brief Cette fonction alloue un nouveau périphérique HID. Le nouveau périphérique est ajouté dans la liste des périphériques HID.
 *
 * @param[in, out] p_handler   Ce paramètre contient l'adresse d'un gestionnaire HID de type \ref T_mkHIDHandler.
 * @param[in]      p_device    Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]      p_interface Ce paramètre contient l'adresse d'une interface de description du périphérique HID.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le périphérique HID a été alloué.
 *         \li \ref K_MK_ERROR_PARAM  : le périphérique HID n'a pas été alloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le périphérique HID n'a pas été alloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le périphérique HID n'a pas été alloué car une erreur d'allocation dynamique s'est produite.
 */

T_mkCode mk_hid_createDevice ( T_mkHIDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );

/**
 * @fn T_mkCode mk_hid_initDevice ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction initialise un périphérique HID via le jeu de requêtes HID. L'état du périphérique HID est mis à jour en fonction du statut de l'initialisation.
 *
 * @param[in, out] p_handler   Ce paramètre contient l'adresse d'un gestionnaire HID de type \ref T_mkHIDHandler.
 * @param[in]      p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique HID a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique HID n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique HID n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le périphérique HID n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le périphérique HID n'a pas été initialisé car le périphérique cible n'a pas répondu à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le périphérique HID n'a pas été initialisé car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_initDevice ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_deleteDevice ( T_mkHIDHandler* p_handler, T_mkHCDDevice* p_device );
 * @brief Cette fonction supprime l'intégralité de la mémoire allouée par un périphérique HID. L'intégralité des interfaces HID sont supprimées.
 *        Des événements \ref K_MK_EVENT_DISCONNECT sont envoyés au dispatcher pour chaque périphérique HID supprimé.
 *
 * @param[in, out]  p_handler Ce paramètre contient l'adresse d'un gestionnaire HID de type \ref T_mkHIDHandler.
 * @param[in, out]  p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique HID ont été désalloués.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique HID n'ont pas été désalloués car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le périphérique HID n'ont pas été désalloués car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_deleteDevice ( T_mkHIDHandler* p_handler, T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hid_deleteDeviceByInterface ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction supprime l'intégralité de la mémoire allouée par un périphérique HID. Contrairement à la fonction \ref mk_hid_deleteDevice, seulement la mémoire allouée par
 *        l'interface du périphérique HID est supprimée. Un événement indiquant la déconnexion du périphérique est envoyé au 'Dispatcher'.
 *
 * @param[in, out]  p_handler   Ce paramètre contient l'adresse d'un gestionnaire HID de type \ref T_mkHIDHandler.
 * @param[in, out]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le périphérique HID a été désalloué.
 *         \li \ref K_MK_ERROR_PARAM  : le périphérique HID n'a pas été désalloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le périphérique HID n'a pas été désalloué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_deleteDeviceByInterface ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice );

/**
 *
 */

#endif


