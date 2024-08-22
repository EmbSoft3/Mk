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
* @file mk_hid_error_private.h
* @brief Déclaration des fonctions dédiées à la vérification des erreurs HID.
* @date 20 oct. 2019
*
*/

#ifndef MK_HID_ERROR_PRIVATE_H
#define MK_HID_ERROR_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_checkOutOfRange ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que la plage de variation de chaque usage est correcte.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'analyse de la structure n'a pas été réalisée en raison d'une erreur d'allocation dynamique.
 *         \li \ref K_MK_ERROR_ISR     : l'analyse de la structure n'a pas été réalisée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_checkOutOfRange ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkApplicationDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que chaque 'Report' commence par une collection applicative.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'analyse de la structure n'a pas été réalisée en raison d'une erreur d'allocation dynamique.
 *         \li \ref K_MK_ERROR_ISR     : l'analyse de la structure n'a pas été réalisée car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_checkApplicationDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkCouplingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que les balises fonctionnant par paires sont correctement déclarées.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 *
 * @warning L'analyse des balises de type 'Collection' et 'EndCollection' n'est pas réalisé.
 */

T_mkCode mk_hid_checkCouplingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkInvalidDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que la déclaration d'une balise n'est pas effectuée à une position invalide.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_checkInvalidDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkInvalidValue ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie l'absence de valeurs invalides.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_checkInvalidValue ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkMissingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie la présence des balises obligatoires.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_checkMissingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkNestingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que les balises sont correctement imbriquées.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_hid_checkNestingDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 * @fn T_mkCode mk_hid_checkUnkwnownDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );
 * @brief Cette fonction vérifie la conformité du 'ReportDescriptor'. La structure de type \ref T_mkHIDReportError est actualisée en fonction du
 *        résultat de l'analyse. Cette fonction vérifie que des déclarations invalides ne sont pas présentes dans le 'ReportDescriptor'.
 *
 * @param[in]  p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 * @param[out] p_error     Ce paramètre contient l'adresse d'une structure de type \ref T_mkHIDReportError.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'analyse de la structure a été réalisée.
 *         \li \ref K_MK_ERROR_PARAM   : l'analyse de la structure n'a pas été réalisée car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_checkUnkwnownDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error );

/**
 *
 */

#endif


