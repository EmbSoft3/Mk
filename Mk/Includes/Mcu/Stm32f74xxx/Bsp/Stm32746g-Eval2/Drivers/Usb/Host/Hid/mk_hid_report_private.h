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
* @file mk_hid_report_private.h
* @brief Déclaration des fonctions dédiées aux reports HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_REPORT_PRIVATE_H
#define MK_HID_REPORT_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_getReportNumber ( T_mkHIDDevice* p_hidDevice, uint32_t* p_reportNumber );
 * @brief Cette fonction retourne le nombre de 'Report' contenu dans le 'Report-Descriptor'.
 *
 * @param[in]  p_hidDevice    Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_reportNumber Ce paramètre contient le nombre de 'Report'.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la détermination du nombre de 'Report' a échoué car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_getReportNumber ( T_mkHIDDevice* p_hidDevice, uint32_t* p_reportNumber );

/**
 * @fn T_mkCode mk_hid_getReport ( T_mkHIDDevice* p_hidDevice, T_mkHIDReport* p_report, uint32_t p_index );
 * @brief Cette fonction retourne l'adresse du 'Report' identifié par p_index.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_report    Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport.
 * @param[in]  p_index     Ce paramètre contient la position du 'Report' dans le 'Report-Descriptor'.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la récupération du 'Report' a échoué car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_getReport ( T_mkHIDDevice* p_hidDevice, T_mkHIDReport* p_report, uint32_t p_index );

/**
 * @fn T_mkCode mk_hid_deleteReport ( T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction supprime les 'Report' d'un périphérique HID. Un événement \ref K_MK_EVENT_DISCONNECT est envoyé au dispatcher pour chaque 'Report' supprimé.
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : la mémoire allouée a été désalloués.
 *         \li \ref K_MK_ERROR_PARAM  : la mémoire allouée n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : la mémoire allouée n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_deleteReport ( T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_deleteReportDescriptor ( T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction supprime le 'ReportDescriptor' d'un périphérique HID.
 * @param[in, out] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : la mémoire allouée a été désalloués.
 *         \li \ref K_MK_ERROR_PARAM  : la mémoire allouée n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : la mémoire allouée n'a pas été désallouée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_deleteReportDescriptor ( T_mkHIDDevice* p_hidDevice );

/**
 *
 */

#endif

