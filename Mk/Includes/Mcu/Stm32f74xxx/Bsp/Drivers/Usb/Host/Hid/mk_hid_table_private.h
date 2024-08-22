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
* @file mk_hid_table_private.h
* @brief Déclaration des fonctions dédiées aux tables HID.
* @date 18 nov. 2019
*
*/

#ifndef MK_HID_TABLE_PRIVATE_H
#define MK_HID_TABLE_PRIVATE_H

/**
 * @fn T_mkCode mk_hid_setItemStateTable ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDItem* p_item );
 * @brief Cette fonction actualise la table ou la pile d'item en fonction des caractéristiques de l'item HID présent en paramètre.
 *
 * @param[in, out] p_stack Ce paramètre contient l'adresse d'une pile de type \ref T_mkHIDReportStack.
 *                         La pile permet de stocker ou restituer l'état des 'Items' de type 'Local' lors des opérations de type 'Push' ou 'Pop'.
 * @param[out]     p_table Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 *                         La table permet d'enregistrer l'état courant de chaque 'Item' contenu dans le 'Report-Descriptor'.
 * @param[in]      p_item  Ce paramètre contient l'adresse d'un 'Item' de type \ref T_mkHIDItem.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'actualisation de la table ou de la pile s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : l'actualisation de la table ou de la pile car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'actualisation de la table ou de la pile car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : l'actualisation de la table ou de la pile car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_setItemStateTable ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDItem* p_item );

/**
 * @fn T_mkCode mk_hid_setItemStateTableByReport ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report );
 * @brief Cette fonction actualise la table ou la pile d'item en fonction des caractéristiques de tous les items du 'Report' présent en paramètre.
 *
 * @param[in, out] p_stack  Ce paramètre contient l'adresse d'une pile de type \ref T_mkHIDReportStack.
 *                          La pile permet de stocker ou restituer l'état des 'Items' de type 'Local' lors des opérations de type 'Push' ou 'Pop'.
 * @param[out]     p_table  Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 *                          La table permet d'enregistrer l'état courant de chaque 'Item' contenu dans le 'Report-Descriptor'.
 * @param[in]      p_report Ce paramètre contient l'adresse d'un 'Report' de type \ref T_mkHIDReport.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'actualisation de la table ou de la pile s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : l'actualisation de la table ou de la pile car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'actualisation de la table ou de la pile car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : l'actualisation de la table ou de la pile car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_setItemStateTableByReport ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report );

/**
 * @fn T_mkCode mk_hid_setItemStateTableByUsage ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );
 * @brief Cette fonction actualise la table ou la pile d'item en fonction des caractéristiques de tous les items de l'usage présent en paramètre.
 *        Un usage de type \ref T_mkHIDUsage comprend l'intégralité des 'Item' délimité par les balises de type 'Input', 'Output' ou 'Feature'.
 *
 * @param[in, out] p_stack  Ce paramètre contient l'adresse d'une pile de type \ref T_mkHIDReportStack.
 *                          La pile permet de stocker ou restituer l'état des 'Items' de type 'Local' lors des opérations de type 'Push' ou 'Pop'.
 * @param[out]     p_table  Ce paramètre contient l'adresse d'une table de type \ref T_mkHIDReportTable.
 *                          La table permet d'enregistrer l'état courant de chaque 'Item' contenu dans le 'Report-Descriptor'.
 * @param[in]      p_usage  Ce paramètre contient l'adresse d'un 'Usage' de type \ref T_mkHIDUsage.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'actualisation de la table ou de la pile s'est déroulé sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : l'actualisation de la table ou de la pile car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : l'actualisation de la table ou de la pile car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : l'actualisation de la table ou de la pile car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hid_setItemStateTableByUsage ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage );

/**
 *
 */

#endif


