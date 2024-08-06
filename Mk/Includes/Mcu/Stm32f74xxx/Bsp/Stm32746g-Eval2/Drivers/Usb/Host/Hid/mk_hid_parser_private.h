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
* @file mk_hid_parser_private.h
* @brief Déclaration des fonctions dédiées aux parsers HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_PARSER_PRIVATE_H
#define MK_HID_PARSER_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_parseError ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'Report-Descriptor' d'un périphérique HID.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une énumération de type \ref T_mkHIDReportError contenant la première
 *                         erreur rencontrée durant l'analyse. Lorsque aucune erreur n'est détectée, la valeur \ref K_MK_HID_NO_ERROR
 *                         est retournée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse du 'Report-Descriptor' a  été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse du 'Report-Descriptor' n'a pas été réalisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'analyse du 'Report-Descriptor' n'a pas été réalisée en raison d'une erreur d'allocation dynamique.
 *         \li \ref K_MK_ERROR_ISR     : l'analyse du 'Report-Descriptor' n'a pas été réalisée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_parseError ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_parseAlternate ( T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction modifie le 'Report-Descriptor d'un périphérique HID. Elle retire les usages alternatifs de la chaine d'item principale pour les placer
 *        dans une chaine d'item secondaire.
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la modification de la structure du 'Report-Descriptor' a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : la modification de la structure du 'Report-Descriptor' n'a pas été réalisée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_parseAlternate ( T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_parseInput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );
 * @brief Cette fonction transmet la valeur des entrées HID d'un ou de tous les 'Report' d'un périphérique HID au dispatcher.
 *
 * @param[in]      p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe      Ce paramètre contient l'adresse d'un pipe de communication de type \ref T_mkHCDPipe.
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

T_mkCode mk_hid_parseInput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );

/**
 * @fn T_mkCode mk_hid_parseOutput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );
 * @brief Cette fonction transmet la valeur des sorties HID d'un 'Report' à un périphérique HID. Les sorties sont transmises par une requête d'interruption si le périphérique
 *        possède une terminaison de ce type. Dans le cas contraire, une terminaison de contrôle est utilisée.
 *
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in] p_pipe      Ce paramètre contient l'adresse d'un pipe de communication de type \ref T_mkHCDPipe.
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

T_mkCode mk_hid_parseOutput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report );

/**
 *
 */

#endif

