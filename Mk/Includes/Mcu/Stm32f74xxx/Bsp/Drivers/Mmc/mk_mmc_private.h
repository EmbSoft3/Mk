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
* @file mk_mmc_private.h
* @brief Déclaration des fonctions privées dédiées au port SD/MMC.
* @date 1 juin 2020
* @todo Adapter les fonctions pour supporter les périphériques MMC et SDIO.
*
*/

#ifndef MK_MMC_PRIVATE_H
#define MK_MMC_PRIVATE_H

/**
 * @fn void mk_mmc_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal MMC.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_mmc_task ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_mmc_initHandler ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction initialise un gestionnaire MMC de type \ref T_mkMMCHandler.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire MMC de type \ref T_mkMMCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le gestionnaire MMC a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le gestionnaire MMC n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le gestionnaire MMC n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le gestionnaire MMC n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_mmc_initHandler ( T_mkMMCHandler* p_handler );

/**
 * @fn T_mkCode mk_mmc_handle ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction initialise le bus SD/MMC, initialise les périphériques connectés sur le bus et traite les requêtes utilisateurs.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire MMC de type \ref T_mkMMCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction a été exécutée sans recontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la fonction a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué en raison d'une erreur de communication.
 */

T_mkCode mk_mmc_handle ( T_mkMMCHandler* p_handler );

/**
 * @fn T_mkCode mk_mmc_handleReadyState ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction bascule les médias présents sur le bus de l'état IDLE à READY.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire MMC de type \ref T_mkMMCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'initialisation des périphériques a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'initialisation des périphériques a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'initialisation des périphériques a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'initialisation des périphériques a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : l'initialisation des périphériques a échoué en raison d'une erreur de communication.
 */

T_mkCode mk_mmc_handleReadyState ( T_mkMMCHandler* p_handler );

/**
 * @fn T_mkCode mk_mmc_handleReadyState ( T_mkMMCHandler* p_handler, T_mkMMCState* p_state );
 * @brief Cette fonction identifie les médias présents sur le bus. Elle bascule l'état des périphériques de 'READY' à 'IDENTIFICATION' jusqu'à 'STANDBY'.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire MMC de type \ref T_mkMMCHandler.
 * @param[in] p_type    Ce paramètre contient le type des périphériques présents sur le bus. Une des constantes suivantes peut être utilisée : \n
 *                      \ref K_MK_MMC_TYPE_SD, \ref K_MK_MMC_TYPE_MMC et \ref K_MK_MMC_TYPE_SDIO.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'identification des périphériques a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'identification des périphériques a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'identification des périphériques a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'identification des périphériques a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : l'identification des périphériques a échoué en raison d'une erreur de communication.
 */

T_mkCode mk_mmc_handleStandbyState ( T_mkMMCHandler* p_handler, T_mkMMCType p_type );

/**
 * @fn T_mkCode mk_mmc_handleTransferState ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );
 * @brief Cette fonction configure un périphérique présent sur le bus. Elle active le fonctionnement sur 4 fils puis configure la taille
 *        d'un bloc de données. La structure \ref T_mkDisk du périphérique est mise à jour avec les informations contenues dans le CSD.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire MMC de type \ref T_mkMMCHandler.
 * @param[in, out] p_device  Ce paramètre contient l'adresse d'un périphérique MMC de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la configuration des périphériques a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la configuration des périphériques a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la configuration des périphériques a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la configuration des périphériques a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : la configuration des périphériques a échoué en raison d'une erreur de communication.
 */

T_mkCode mk_mmc_handleTransferState ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_handleDeleteState ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction supprime l'ensemble des périphériques alloués par le terminal.
 *        L'événement \ref K_MK_EVENT_DISCONNECT est envoyé au dispatcher pour chaque disque supprimé.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire SD/MMC de type \ref T_mkMMCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les périphériques ont été supprimés.
 *         \li \ref K_MK_ERROR_PARAM   : les périphériques n'ont pas été supprimés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : les périphériques n'ont pas été supprimés car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_mmc_handleDeleteState ( T_mkMMCHandler* p_handler );

/**
 *
 */

#endif

