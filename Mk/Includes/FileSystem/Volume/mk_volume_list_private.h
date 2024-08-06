/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_volume_list_private.h
* @brief Déclaration des fonctions privées dédiées aux listes chainées des partitions.
* @date 11 sept. 2021
*
*/

#ifndef MK_VOLUME_LIST_PRIVATE_H
#define MK_VOLUME_LIST_PRIVATE_H

/**
 * @fn uint32_t mk_volume_getSystemIdentifier ( T_mkVolume* p_list );
 * @brief Cette fonction retourne la valeur d'identifiant système unique.
 * @param[in,out] p_list Ce paramètre contient l'adresse de la première partition d'une liste.
 *
 * @return Cette fonction retourne la valeur d'un identifiant unique. Il évolue entre [0 et K_MK_VOLUME_MAX_NUMBER-1].
 *
 */

uint32_t mk_volume_getSystemIdentifier ( T_mkVolume* p_list );

/**
 * @fn T_mkCode mk_volume_add ( T_mkVolume** p_list, T_mkVolume* p_volume );
 * @brief Cette fonction ajoute une partition de type \ref T_mkVolume dans une liste de partitions.
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse d'une liste de type \ref T_mkVolume.
 * @param[in]      p_volume Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la partition a été ajoutée dans la liste.
 *         \li \ref K_MK_ERROR_PARAM : la partition n'a pas été ajoutée dans la liste car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_volume_add ( T_mkVolume** p_list, T_mkVolume* p_volume );

/**
 * @fn T_mkCode mk_volume_delete ( T_mkVolume* p_list, uint32_t p_enableEvent );
 * @brief Cette fonction supprime toutes les partitions d'une liste de partitions. En fonction de la valeur de p_enableEvent,
 *        un événement de type \ref K_MK_EVENT_UNMOUNT peut être envoyé au dispatcher.
 *
 * @param[in,out] p_list        Ce paramètre contient l'adresse de la première partition de la liste.
 * @param[in]     p_enableEvent Ce paramètre contient un drapeau permettant de transmettre (valeur 1) ou non (valeur 0) l'événement
 *                              \ref K_MK_EVENT_UNMOUNT au dispatcher pour chaque partition.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les partitions de la liste ont été désallouées.
 *         \li \ref K_MK_ERROR_PARAM : les partitions de la liste n'ont pas été désallouées car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_volume_delete ( T_mkVolume* p_list, uint32_t p_enableEvent );

/**
 *
 */

#endif

