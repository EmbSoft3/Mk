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
* @file mk_hid_router_private.h
* @brief Déclaration des fonctions dédiées au routeur HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_ROUTER_PRIVATE_H
#define MK_HID_ROUTER_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_route ( T_mkHIDDevice* p_hidDevice );
 * @brief Cette fonction déclenche le processus de routage de tous les 'Report' d'un périphérique HID.
 *        En fonction du contenu de chaque 'Report', cette fonction alloue puis attribut contrôle applicatif (Mouse, Keyboard, ...) à chaque 'Report'.
 *        Si le 'Report' n'est pas supporté par le système, aucun contrôle applicatif n'est attribué.
 * @param[in] p_hidDevice Ce paramètre contient l'adresse d'un périphérique HID de type \ref T_mkHIDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_route ( T_mkHIDDevice* p_hidDevice );

/**
 * @fn T_mkCode mk_hid_routeControl ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t* p_bypass, uint32_t p_type );
 * @brief Cette fonction associe une adresse mémoire à chaque entrée/sortie HID d'un 'Report'. Une adresse différente de \ref K_MK_NULL ou \ref K_MK_INVALID_HANDLE
 *        signifie qu'une entrée/sortie HID a été routée. Une valeur \ref K_MK_INVALID_HANDLE signifie que l'entrée/sortie HID doit être ignorée.
 *        La valeur \ref K_MK_NULL signifie que l'item n'est pas une entrée/sortie HID ou que l'entrée/sortie est bypassé.
 *
 * @param[in, out] p_stack  Ce paramètre contient l'adresse d'une pile de type \ref T_mkHIDReportStack.
 *                          La pile permet de stocker ou resituer l'état des 'Items' de type 'Local' lors des opérations de type 'Push' ou 'Pop'.
 * @param[in, out] p_table  Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 *                          La table permet d'enregistrer l'état courant de chaque 'Item' contenu dans le 'Report-Descriptor'.
 * @param[in]      p_report Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport. L'adresse pointe sur le 'Report' courant qui doit être analysé.
 * @param[in, out] p_usage  Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage. L'adresse pointe sur l'usage courant qui doit être analysé.
 * @param[in, out] p_bypass Ce paramètre contient l'adresse d'une variable dont la valeur permet d'inhiber le processus de routage tant que l'identifiant du 'Report' n'est pas rencontré.
 *                          Une valeur non nulle signifie que le filtrage est actif. Cette fonction réinitialise ce paramètre lorsqu'un 'ReportID' est rencontré.
 * @param[in]      p_type   Ce paramètre contient le type du contrôle applicatif. Les valeurs définies dans les énumérations du fichier mk_hid_page_types.h peuvent être utilisées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_routeControl ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t* p_bypass, uint32_t p_type );

/**
 * @fn T_mkCode mk_hid_routeMouse ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );
 * @brief Cette fonction attribut une adresse aux usages contenus dans un contrôle de type 'Mouse'.
 *
 * @param[in]      p_table     Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 * @param[in]      p_report    Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport. L'adresse pointe sur le 'Report' courant qui doit être analysé.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage. L'adresse pointe sur l'usage courant qui doit être analysé.
 * @param[in]      p_page      Ce paramètre contient la valeur de la page courante.
 * @param[out]     p_usageUsed Ce paramètre content l'adresse d'une variable permettant la gestion des usages alternatifs. La fonction bascule la variable à la valeur
 *                             nulle lorsque l'identifiant de l'usage analysé n'est pas supporté par le contrôle applicatif.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_routeMouse ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );

/**
 * @fn T_mkCode mk_hid_routeJoystick ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );
 * @brief Cette fonction attribut une adresse aux usages contenus dans un contrôle de type 'Joystick'.
 *
 * @param[in]      p_table     Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 * @param[in]      p_report    Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport. L'adresse pointe sur le 'Report' courant qui doit être analysé.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage. L'adresse pointe sur l'usage courant qui doit être analysé.
 * @param[in]      p_page      Ce paramètre contient la valeur de la page courante.
 * @param[out]     p_usageUsed Ce paramètre content l'adresse d'une variable permettant la gestion des usages alternatifs. La fonction bascule la variable à la valeur
 *                             nulle lorsque l'identifiant de l'usage analysé n'est pas supporté par le contrôle applicatif.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_routeJoystick ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );

/**
 * @fn T_mkCode mk_hid_routeKeyboard ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );
 * @brief Cette fonction attribut une adresse aux usages contenus dans un contrôle de type 'Keyboard' ou 'Keypad'.
 *
 * @param[in]      p_table     Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 * @param[in]      p_report    Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport. L'adresse pointe sur le 'Report' courant qui doit être analysé.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage. L'adresse pointe sur l'usage courant qui doit être analysé.
 * @param[in]      p_page      Ce paramètre contient la valeur de la page courante.
 * @param[out]     p_usageUsed Ce paramètre content l'adresse d'une variable permettant la gestion des usages alternatifs. La fonction bascule la variable à la valeur
 *                             nulle lorsque l'identifiant de l'usage analysé n'est pas supporté par le contrôle applicatif.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_routeKeyboard ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );

/**
 * @fn T_mkCode mk_hid_routeConsumer ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );
 * @brief Cette fonction attribut une adresse aux usages contenus dans un contrôle de type 'Consumer'.
 *
 * @param[in]      p_table     Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 * @param[in]      p_report    Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport. L'adresse pointe sur le 'Report' courant qui doit être analysé.
 * @param[in, out] p_usage     Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage. L'adresse pointe sur l'usage courant qui doit être analysé.
 * @param[in]      p_page      Ce paramètre contient la valeur de la page courante.
 * @param[out]     p_usageUsed Ce paramètre content l'adresse d'une variable permettant la gestion des usages alternatifs. La fonction bascule la variable à la valeur
 *                             nulle lorsque l'identifiant de l'usage analysé n'est pas supporté par le contrôle applicatif.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le processus de routage s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : le processus de routage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le processus de routage a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le processus de routage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_routeConsumer ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed );

/**
 *
 */

#endif

