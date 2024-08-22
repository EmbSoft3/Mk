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
* @file mk_mmc_device_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques SD/MMC.
* @date 12 juin 2020
*
*/

#ifndef MK_MMC_DEVICE_PRIVATE_H
#define MK_MMC_DEVICE_PRIVATE_H

/**
 * @fn T_mkCode mk_mmc_createDevice ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction alloue un nouveau périphérique de type \ref T_mkMMCDevice puis l'ajoute dans la liste d'un gestionnaire.
 *        Un disque est automatiquement alloué pour chaque périphérique.
 *
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[out]     p_device  Ce paramètre contient l'adresse du périphérique MMC alloué.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le périphérique MMC a été alloué puis ajouté dans la liste du gestionnaire.
 *         \li \ref K_MK_ERROR_PARAM  : le périphérique MMC n'a pas été alloué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le périphérique MMC n'a pas été alloué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le périphérique MMC n'a pas été alloué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT  : le périphérique MMC n'a pas été alloué car une tâche de type non privilégié ne peut pas allouer un périphérique MMC protégé.

 */

T_mkCode mk_mmc_createDevice ( T_mkMMCHandler* p_handler, T_mkMMCDevice** p_device );

/**
 * @fn T_mkCode mk_mmc_deleteDevice ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_enableEvent );
 * @brief Cette fonction désalloue un périphérique MMC présent dans une liste d'un gestionnaire. Le disque assigné au périphérique est aussi
 *        désalloué.
 *
 * @param[in, out] p_handler     Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in]      p_device      Ce paramètre contient l'adresse du périphérique à supprimer.
 * @param[in]      p_enableEvent Ce paramètre contient un drapeau permettant de transmettre (valeur 1) ou non l'événement \ref K_MK_EVENT_DISCONNECT
 *                               au dispatcher.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : le périphérique a été supprimé.
 *         \li \ref K_MK_ERROR_PARAM  : le périphérique n'a pas été supprimé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le périphérique n'a pas été supprimé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : le périphérique n'a pas été supprimé car une tâche de type non privilégié ne peut pas désallouer un périphérique MMC protégé.

 */

T_mkCode mk_mmc_deleteDevice ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_enableEvent );

/**
 *
 */

#endif

