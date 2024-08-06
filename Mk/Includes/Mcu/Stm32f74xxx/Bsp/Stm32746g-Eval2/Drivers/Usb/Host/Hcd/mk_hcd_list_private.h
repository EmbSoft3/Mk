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
* @file mk_hcd_list_private.h
* @brief Déclaration des fonctions privées dédiées aux listes USB.
* @date 27 juil. 2019
*
*/

#ifndef MK_HCD_LIST_PRIVATE_H
#define MK_HCD_LIST_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_add ( T_mkHCDList* p_list, T_mkHCDDevice* p_device );
 * @brief Cette fonction ajoute un périphérique USB dans une liste rebouclée sur elle même.
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse de la liste
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique USB a été ajouté dans la liste
 *         \li \ref K_MK_ERROR_PARAM : le périphérique USB n'a pas été ajouté dans la liste car au moins un paramètre est invalide
 *
 * @note Lorsque la liste est vide, les pointeurs "next" et "previous" du périphérique doivent pointer sur lu même.
 *       Cette fonction n'alloue pas de périphérique dynamiquement.
 *
 */

T_mkCode mk_hcd_add ( T_mkHCDList* p_list, T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hcd_remove ( T_mkHCDList* p_list, T_mkHCDDevice* p_device );
 * @brief Cette fonction supprime un périphérique USB présent dans une liste rebouclée sur elle même.
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse de la liste
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique USB a été supprimé de la liste.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique USB n'a pas été supprimé de la liste car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_hcd_remove ( T_mkHCDList* p_list, T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hcd_addTree ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device );
 * @brief Cette fonction ajoute un nouveau périphérique dans l'arborescence des périphériques USB (liste simplement chainée).
 *
 * @param[in, out] p_hub    Ce paramètre contient l'adresse du hub où le périphérique est connecté.
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique USB a été ajouté dans l'arborescence des périphériques.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique USB n'a pas été ajouté dans l'arborescence car au moins un paramètre est invalide.
 *
 * @note Lors de l'ajout du premier périphérique, les paramètres p_hub et p_device doivent pointer sur la même adresse.
 *       Cette fonction n'alloue pas de périphérique dynamiquement.
 *
 */

T_mkCode mk_hcd_addTree ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hcd_deleteTree ( T_mkHCDList* p_list, T_mkHCDDevice* p_device, uint32_t p_mode );
 * @brief Cette fonction retire un périphérique présent dans l'arborescence des périphériques USB. L'intégralité de la mémoire
 *        additionnelle allouée par le périphérique est supprimée (interface, terminaison, ...). En fonction de la valeur du paramètre
 *        p_mode, le périphérique p_device peut être désalloué (\ref K_MK_HCD_DELETE_ALL) ou non (\ref K_MK_HCD_DELETE_PARTIAL).
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse d'une liste rebouclée sur elle même. Si le périphérique n'est présent
 *                          dans aucune liste, ce paramètre doit prendre la valeur \ref K_MK_NULL.
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB.
 * @param[in]      p_mode   Ce paramètre précise si le dispositif doit être désalloué partiellement ou totalement. Il peut prendre
 *                          les valeurs suivantes : \ref K_MK_HCD_DELETE_PARTIAL et \ref K_MK_HCD_DELETE_ALL.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique USB a été retiré de l'arborescence des périphériques.
 *         \li \ref K_MK_ERROR_PARAM : le périphérique USB n'a pas été retiré de l'arborescence car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le périphérique USB n'a pas été retiré de l'arborescence car la fonction a été exécutée depuis
 *                                     un vecteur d'interruption.
 *
 * @note Si le périphérique est un hub, cette fonction supprime tous les périphériques présent en aval.
 * @warning Attention, la suppression des périphériques est réalisée de manière \a récursive.
 *
 */

T_mkCode mk_hcd_deleteTree ( T_mkHCDList* p_list, T_mkHCDDevice* p_device, uint32_t p_mode );

/**
 * @fn T_mkCode mk_hcd_deleteInterface ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );
 * @brief Cette fonction désalloue une interface présente dans une liste de type \ref T_mkHCDInterfaceDescriptor.
 *
 * @param[in, out] p_device    Ce paramètre contient l'adresse d'un périphérique USB contenant une liste d'interface.
 * @param[in, out] p_interface Ce paramètre contient l'adresse d'une interface de type \ref T_mkHCDInterfaceDescriptor.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'interface a été désallouée.
 *         \li \ref K_MK_ERROR_PARAM : l'interface n'a pas été désallouée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'interface n'a pas été désallouée car la fonction a été exécutée depuis
 *                                     un vecteur d'interruption.
 *
 * @note Si l'interface n'est pas présente dans la liste, aucune interface n'est supprimée.
 *
 */

T_mkCode mk_hcd_deleteInterface ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );

/**
 * @fn T_mkCode mk_hcd_deleteUnusedInterfaces ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );
 * @brief Cette fonction désalloue toutes les interfaces d'une liste de type \ref T_mkHCDInterfaceDescriptor à l'exception
 *        de l'interface p_interface.
 *
 * @param[in, out] p_device    Ce paramètre contient l'adresse d'un périphérique USB contenant une liste d'interface.
 * @param[in, out] p_interface Ce paramètre contient l'adresse d'une interface de type \ref T_mkHCDInterfaceDescriptor.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les interfaces non utilisées ont été désallouées.
 *         \li \ref K_MK_ERROR_PARAM : les interfaces non utilisées n'ont pas été désallouées car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : les interfaces non utilisées n'ont pas été désallouées car la fonction a été exécutée depuis
 *                                     un vecteur d'interruption.
 *
 * @note Si l'interface n'est pas présente dans la liste, l'intégralité de la liste est désallouée.
 *
 */

T_mkCode mk_hcd_deleteUnusedInterfaces ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface );

/**
 *
 */

#endif

