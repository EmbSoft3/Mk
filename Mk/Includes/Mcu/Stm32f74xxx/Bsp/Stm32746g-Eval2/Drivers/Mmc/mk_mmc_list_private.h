/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_mmc_list_private.h
* @brief Déclaration des fonctions privées dédiées aux listes SD/MMC.
* @date 20 juin 2020
*
*/

#ifndef MK_MMC_LIST_PRIVATE_H
#define MK_MMC_LIST_PRIVATE_H

/**
 * @fn T_mkCode mk_mmc_add ( T_mkMMCList* p_list, T_mkMMCDevice* p_device );
 * @brief Cette fonction ajoute un périphérique de type \ref T_mkMMCDevice dans une liste de périphériques.
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse d'une liste de type \ref T_mkMMCList.
 * @param[in]      p_device Ce paramètre contient l'adresse d'un périphérique MMC de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le périphérique a été ajouté au début de la liste chainée.
 *         \li \ref K_MK_ERROR_PARAM : la périphérique n'a pas ajouté dans la liste chainée car au moins un paramètre est invalide.
 *
 * @note Le pointeur de la liste doit être initialisé à la valeur \ref K_MK_NULL avant d'exécuter cette fonction.
 *
 */

T_mkCode mk_mmc_add ( T_mkMMCList* p_list, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_remove ( T_mkMMCList* p_list, T_mkMMCDevice* p_device );
 * @brief Cette fonction supprime un périphérique de type \ref T_mkMMCDevice d'une liste de périphériques.
 *
 * @param[in, out] p_list   Ce paramètre contient l'adresse d'une liste de type \ref T_mkMMCList.
 * @param[in]      p_device Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *                          Le périphérique doit être dans la liste.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique a été supprimé de la liste chainée.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique n'a pas été supprimé de la liste chainée car au moins un paramètre est invalide.
 */

T_mkCode mk_mmc_remove ( T_mkMMCList* p_list, T_mkMMCDevice* p_device );

/**
 *
 */

#endif


