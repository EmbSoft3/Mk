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
* @file mk_hid_request_private.h
* @brief Déclaration des fonctions dédiées aux requêtes HID.
* @date 26 oct. 2019
*
*/

#ifndef MK_HID_REQUEST_PRIVATE_H
#define MK_HID_REQUEST_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_getReportDescriptor ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_interfaceNumber );
 * @brief Cette fonction récupére le 'Report-Descriptor d'un périphérique HID.
 *
 * @param[in, out] p_hidDevice       Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe            Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_interfaceNumber Ce paramètre contient le numéro d'une interface HID.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le 'Report-Descriptor' a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le 'Report-Descriptor' n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le 'Report-Descriptor' n'a pas été récupéré car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le 'Report-Descriptor' n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le 'Report-Descriptor' n'a pas été récupéré car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le 'Report-Descriptor' n'a pas été récupéré car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_getReportDescriptor ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_interfaceNumber );

/**
 * @fn T_mkCode mk_hid_setIdle ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t p_duration, uint8_t p_reportID, uint16_t p_interfaceNumber );
 * @brief Cette fonction configure la fréquence de rafraichissement d'un 'Report' d'une interface HID.
 *
 * @param[in, out] p_hidDevice       Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe            Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_duration        Ce paramètre contient la période de rafraichissement [en multiple de 4ms].
 * @param[in]      p_reportID        Ce paramètre contient l'identifiant du 'Report' à configurer.
 * @param[in]      p_interfaceNumber Ce paramètre contient le numéro de l'interface HID à configurer.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la période de rafraichissement a été configurée.
 *         \li \ref K_MK_ERROR_PARAM   : la période de rafraichissement n'a pas été configurée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la période de rafraichissement n'a pas été configurée car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la période de rafraichissement n'a pas été configurée car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_setIdle ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t p_duration, uint8_t p_reportID, uint16_t p_interfaceNumber );

/**
 * @fn T_mkCode mk_hid_setProtocol ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_protocol, uint16_t p_interfaceNumber );
 * @brief Cette fonction configure le protocole de communication d'une interface HID.
 *
 * @param[in, out] p_hidDevice       Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe            Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_protocol        Ce paramètre contient le protocole de communication. Les constantes suivantes peuvent être utilisées : \n
 *                                   \ref K_MK_HID_BOOT_PROTOCOL et \ref K_MK_HID_REPORT_PROTOCOL
 * @param[in]      p_interfaceNumber Ce paramètre contient le numéro de l'interface HID à configurer.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le protocole a été configuré.
 *         \li \ref K_MK_ERROR_PARAM   : le protocole n'a pas été configuré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le protocole n'a pas été configuré car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : le protocole n'a pas été configuré car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_setProtocol ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_protocol, uint16_t p_interfaceNumber );

/**
 * @fn T_mkCode mk_hid_getDeviceReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );
 * @brief Cette fonction récupére la valeur des entrées HID d'un ou de tous les 'Report' contenus dans le 'Report-Descriptor' d'un périphérique HID.
 *
 * @param[in]      p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_report    Ce paramètre contient l'adresse d'un 'Report'. La valeur \ref K_MK_NULL peut être utilisée si l'ensemble des entrées
 *                             doivent être récupérées. Dans ce cas, les 'Report' sont récupérés via une requête d'interruption.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les entrées HID ont été récupérée.
 *         \li \ref K_MK_ERROR_PARAM   : les entrées HID n'ont pas été récupérées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : les entrées HID n'ont pas été récupérées car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : les entrées HID n'ont pas été récupérées car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les entrées HID n'ont pas été récupérées car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : les entrées HID n'ont pas été récupérées car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_getDeviceReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );

/**
 * @fn T_mkCode mk_hid_setDeviceReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );
 * @brief Cette fonction transmet la valeur des sorties HID d'un 'Report' à un périphérique HID. Les sorties sont transmises par une requête d'interruption si le périphérique
 *        possède une terminaison de ce type. Dans le cas contraire, une terminaison de contrôle est utilisée.
 *
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in] p_report    Ce paramètre contient l'adresse d'un 'Report'.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les sorties HID ont été envoyées au périphérique HID.
 *         \li \ref K_MK_ERROR_PARAM   : les sorties HID n'ont pas été envoyées au périphérique HID car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : les sorties HID n'ont pas été envoyées au périphérique HID car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : les sorties HID n'ont pas été envoyées au périphérique HID car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les sorties HID n'ont pas été envoyées au périphérique HID car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : les sorties HID n'ont pas été envoyées au périphérique HID car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_setDeviceReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );

/**
 * @fn T_mkCode mk_hid_getInterrupt ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t* p_buf, uint16_t p_length );
 * @brief Cette fonction receptionne un buffer de données par le biais d'une requête d'interruption de type IN.
 *
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in] p_buf       Ce paramètre contient l'adresse où les données reçues doivent être stockées.
 * @param[in] p_length    Ce paramètre contient la longueur des données à récupérer [en octets].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les données ont été reçues.
 *         \li \ref K_MK_ERROR_PARAM   : les données n'ont pas été reçues car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : les données n'ont pas été reçues car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les données n'ont pas été reçues car une erreur de communication s'est produite.
 *                                       Le statut de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hid_getInterrupt ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t* p_buf, uint16_t p_length );

/**
 * @fn T_mkCode mk_hid_setInterrupt ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t* p_buf, uint16_t p_length );
 * @brief Cette fonction transmet un buffer de données par le biais d'une requête d'interruption de type OUT.
 *
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in] p_buf       Ce paramètre contient l'adresse des données à transmettre.
 * @param[in] p_length    Ce paramètre contient la longueur des données à transmettre [en octets].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les données ont été envoyées.
 *         \li \ref K_MK_ERROR_PARAM   : les données n'ont pas été envoyées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : les données n'ont pas été envoyées car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les données n'ont pas été envoyées car une erreur de communication s'est produite.
 *                                       Le statut de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hid_setInterrupt ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint8_t* p_buf, uint16_t p_length );

/**
 *
 */

#endif

