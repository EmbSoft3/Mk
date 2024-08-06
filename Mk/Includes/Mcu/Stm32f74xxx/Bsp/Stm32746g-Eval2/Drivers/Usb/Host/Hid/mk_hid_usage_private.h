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
* @file mk_hid_usage_private.h
* @brief Déclaration des fonctions privées dédiées aux usages HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_USAGE_PRIVATE_H
#define MK_HID_USAGE_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_getUsageNumber ( T_mkHIDReport* p_report, uint32_t* p_usageNumber );
 * @brief Cette fonction retourne le nombre d'usage contenu dans un 'Report'.
 *
 * @param[in]  p_report      Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport.
 * @param[out] p_usageNumber Ce paramètre contient le le nombre d'usage d'un report.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la détermination du nombre d'Usage a échoué car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_getUsageNumber ( T_mkHIDReport* p_report, uint32_t* p_usageNumber );

/**
 * @fn T_mkCode mk_hid_getUsage ( T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_index );
 * @brief Cette fonction retourne l'adresse de l'usage identifié par p_index.
 *
 * @param[in]  p_report Ce paramètre contient l'adresse d'un report de type \ref T_mkHIDReport.
 * @param[out] p_usage  Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 * @param[in]  p_index  Ce paramètre contient la position de l'usage dans le report.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la récupération de l'Usage a échoué car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_getUsage ( T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_index );

/**
 * @fn T_mkCode mk_hid_setUsageAddr ( T_mkHIDUsage* p_usage, T_mkAddr p_destAddr, uint16_t p_destinationSize );
 * @brief Cette fonction écrit une adresse de routage dans le premier item d'un usage.
 *
 * @param[in, out] p_usage           Ce paramètre contient l'adresse d'un usage de type \ref T_mkHIDUsage.
 * @param[in]      p_destAddr        Ce paramètre contient la valeur de l'adresse de routage. La valeur \ref K_MK_NULL est autorisée.
 * @param[in]      p_destinationSize Ce paramètre contient la taille [en bits] de l'espace mémoire attribué à l'Usage (typiquement 8, 16 ou 32).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_setUsageAddr ( T_mkHIDUsage* p_usage, T_mkAddr p_destAddr, uint16_t p_destinationSize );

/**
 * @fn T_mkCode mk_hid_getUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, uint16_t p_destinationSize );
 * @brief Cette fonction parse le buffer de données HID puis écrit la valeur d'un usage dans son adresse de routage.
 *        Cette fonction demande la suite du buffer de données au périphérique HID s'il est nécessaire de réaliser plusieurs transactions pour en récupérer l'intégralité.
 *        Dans le cas où le périphérique répond à la requête avec une NAK, l'état du périphérique HID évolue à \ref K_MK_HID_DEVICE_ERROR_STATE.
 *
 * @param[in]      p_hidDevice       Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe            Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser          Ce paramètre contient l'adresse d'un parser HID de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table           Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 * @param[in]      p_destinationSize Ce paramètre contient la taille de la variable [en bits] où est stocké la valeur de l'usage récupéré
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car le périphérique cible n'a pas répondu suite à la requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_getUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, uint16_t p_destinationSize );

/**
 * @fn T_mkCode mk_hid_setUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table );
 * @brief Cette fonction parse la valeur d'un usage dans un buffer de données puis le transmet à un périphérique HID.
 *        Dans le cas où le périphérique répond à la requête avec une NAK, l'état du périphérique HID évolue à \ref K_MK_HID_DEVICE_ERROR_STATE.
 *
 * @param[in]      p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in]      p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser    Ce paramètre contient l'adresse d'un parser HID de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table     Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car le périphérique cible n'a pas répondu suite à la requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_setUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table );

/**
 * @fn T_mkCode mk_hid_readUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction stocke la valeur d'un usage HID de type 'Input' à l'adresse de destination déterminée durant le processus de routage.
 *        Cette routine doit être exécutée lorsqu'une balise usage est rencontrée.
 *
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser    Ce paramètre contient l'adresse d'un parser de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table     Ce paramètre contient l'adresse de la table d'item de type \ref T_mkHIDReportTable.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'une structure \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la valeur a été écrite.
 *         \li \ref K_MK_ERROR_PARAM   : la valeur n'a pas été écrite car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la valeur n'a pas été écrite car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la valeur n'a pas été écrite car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_readUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 * @fn T_mkCode mk_hid_readMultipleUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction stocke la valeur de plusieurs usage HID de type 'Input' aux adressex de destination déterminées durant le processus de routage.
 *        Cette routine doit être exécutée lorsqu'une balise de type 'UsageMinimum' est rencontrée.
 *
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser    Ce paramètre contient l'adresse d'un parser de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table     Ce paramètre contient l'adresse de la table d'item de type \ref T_mkHIDReportTable.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'une structure \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les valeurs ont été écrites.
 *         \li \ref K_MK_ERROR_PARAM   : les valeurs n'ont pas été écrites car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : les valeurs n'ont pas été écrites car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : les valeurs n'ont pas été écrites car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_readMultipleUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 * @fn T_mkCode mk_hid_writeUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction copie la valeur d'un usage HID de type 'Output' depuis son adresse de routage vers le 'Report' d'un périphérique HID.
 *        Cette routine doit être exécutée lorsqu'une balise usage est rencontrée.
 *
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser    Ce paramètre contient l'adresse d'un parser de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table     Ce paramètre contient l'adresse de la table d'item de type \ref T_mkHIDReportTable.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'une structure \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la valeur a été copiée.
 *         \li \ref K_MK_ERROR_PARAM   : la valeur n'a pas été copiée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la valeur n'a pas été copiée car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la valeur n'a pas été copiée car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_writeUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 * @fn T_mkCode mk_hid_writeMultipleUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction copie la valeur de plusieurs usage HID de type 'Output' depuis leur adresse de routage vers le 'Report' d'un périphérique HID.
 *        Cette routine doit être exécutée lorsqu'une balise 'UsageMinimum' est rencontrée.
 *
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_parser    Ce paramètre contient l'adresse d'un parser de type \ref T_mkHIDUsageParser.
 * @param[in]      p_table     Ce paramètre contient l'adresse de la table d'item de type \ref T_mkHIDReportTable.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'une structure \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les valeurs ont été copiée.
 *         \li \ref K_MK_ERROR_PARAM   : les valeurs n'ont pas été copiées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : les valeurs n'ont pas été copiées car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : les valeurs n'ont pas été copiées car une erreur de communication s'est produite.
 */

T_mkCode mk_hid_writeMultipleUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 *
 */

#endif


