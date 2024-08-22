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
* @file mk_mmc_cmd_private.h
* @brief Déclaration des fonctions privées dédiées aux commandes SD/MMC.
* @date 4 juil. 2020
*
*/

#ifndef MK_MMC_CMD_PRIVATE_H
#define MK_MMC_CMD_PRIVATE_H

/**
 * @fn T_mkCode mk_mmc_setIdleState ( T_mkMMCHandler* p_handler );
 * @brief Cette fonction positionne le bus SD/MMC dans l'état de repos.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire SD/MMC de type \ref T_mkMMCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_setIdleState ( T_mkMMCHandler* p_handler );

/**
 * @fn T_mkCode mk_mmc_select ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );
 * @brief Cette fonction sélectionne un périphérique SD/MMC. Le périphérique est sélectionné en fonction de son adresse relative (RCA).
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_select ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_publishNewRCA ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );
 * @brief Cette fonction récupére l'adresse relative (RCA) d'un périphérique SD/MMC. L'adresse est stockée dans les attributs de la structure
 *        \ref T_mkMMCDevice.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_publishNewRCA ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_setApplicationMode ( T_mkMMCHandler* p_handler, T_mkMMCCStatusRegister* p_status, uint32_t p_addr );
 * @brief Cette fonction active le mode applicatif d'un périphérique SD/MMC afin d'exécuter des commandes de type ACDM.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[out] p_status  Ce paramètre contient l'adresse du registre de statut du périphérique SD/MMC.
 * @param[in]  p_addr    Ce paramètre contient l'adresse RCA du périphérique SD/MMC.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_setApplicationMode ( T_mkMMCHandler* p_handler, T_mkMMCCStatusRegister* p_status, uint32_t p_addr );

/**
 * @fn T_mkCode mk_mmc_getStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );
 * @brief Cette fonction récupére la valeur du registre de statut d'un périphérique SD/MMC.
 *
 * @param[in]     p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in,out] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_getStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_sendStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCExtendedStatus* p_status );
 * @brief Cette fonction récupére la valeur du registre de statut étendu d'un périphérique SD/MMC.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in]  p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[out] p_status  Ce paramètre contient l'adresse du registre de statut étendu.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Le périphérique SD/MMC doit être sélectionné avant d'exécuter cette fonction (cf. fonction \ref mk_mmc_select).
 *
 */

T_mkCode mk_mmc_sendStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCExtendedStatus* p_status );

/**
 * @fn T_mkCode mk_mmc_setBusWidth ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );
 * @brief Cette fonction configure la largeur du bus de communication d'un périphérique SD/MMC.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[in] p_arg     Ce paramètre contient la taille du bus SD/MMC. Une des constantes suivantes peut être utilisée :\n
 *                      \ref K_MK_MMC_BUS_WIDTH_1BIT et \ref K_MK_MMC_BUS_WIDTH_4BITS
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Le périphérique SD/MMC doit être sélectionné avant d'exécuter cette fonction (cf. fonction \ref mk_mmc_select).
 *
 */

T_mkCode mk_mmc_setBusWidth ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );

/**
 * @fn T_mkCode mk_mmc_setBlockLength ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );
 * @brief Cette fonction configure la taille des blocs de données d'un périphérique SD/MMC.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[in] p_arg     Ce paramètre contient la taille d'un bloc de données.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Le périphérique SD/MMC doit être sélectionné avant d'exécuter cette fonction (cf. fonction \ref mk_mmc_select).
 * @note La taille maximale d'un bloc de données est sotckée dans le CID (\ref T_mkMMCCIDRegister).
 *
 */

T_mkCode mk_mmc_setBlockLength ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );

/**
 * @fn T_mkCode mk_mmc_setBlockCount ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );
 * @brief Cette fonction configure le nombre de blocs de données à transférer ou récupérer suite à une commande d'écriture ou lecture multiples.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[in] p_arg     Ce paramètre contient le nombre de blocs de données à transférer ou à récupérer. Il est codé sur 16 bits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Le périphérique SD/MMC doit être sélectionné avant d'exécuter cette fonction (cf. fonction \ref mk_mmc_select).
 *
 */

T_mkCode mk_mmc_setBlockCount ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, uint32_t p_arg );

/**
 * @fn T_mkCode mk_mmc_stopTransmission ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );
 * @brief Cette fonction arrête un flux de lecture ou d'écriture multiples.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Le périphérique SD/MMC doit être sélectionné avant d'exécuter cette fonction (cf. fonction \ref mk_mmc_select).
 *
 */

T_mkCode mk_mmc_stopTransmission ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_setSecurity ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_str8 p_password, uint32_t p_length, uint32_t p_type );
 * @brief Cette fonction configure les paramètres de sécurité d'un média de type SD.
 *
 * @param[in] p_handler  Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in] p_device   Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[in] p_password Ce paramètre contient le mot de passe utilisateur.
 * @param[in] p_length   Ce paramètre contient la taille du mot de passe en octets [0 à 16].
 *                       Une valeur de 0 signifie que la carte n'est pas protégée par mot de passe.
 * @param[in] p_type     Ce paramètre contient le type de la requête. Une des constantes suivantes peut être utilisée :
 *                       \li \ref K_MK_DISK_SD_LOCK            : cette requête vérrouille la carte.
 *                       \li \ref K_MK_DISK_SD_UNLOCK          : cette requête dévérrouille la carte en utilisant le mot de passe fourni en paramètre.
 *                       \li \ref K_MK_DISK_SD_REMOVE_PASSWORD : cette requête supprime la protection par mot de passe en utilisant le mot de passe fourni en paramètre.
 *                       \li \ref K_MK_DISK_SD_SET_PASSWORD    : cette requête active la protection par mot de passe. Lorsqu'un mot de passe est défini (paramètre p_length
 *                                                               différent de 0), la carte est automatiquement vérrouillée au prochain "Power-on".
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication.
 *
 * @note Les flags \ref K_MK_DISK_SD_SET_PASSWORD et \ref K_MK_DISK_SD_LOCK peuvent être combinés pour définir un mot de passe et vérrouillé la carte dans la même séquence.
 *
 */

T_mkCode mk_mmc_setSecurity ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_str8 p_password, uint32_t p_length, uint32_t p_type );

/**
 * @fn T_mkCode mk_mmc_sendCmd ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCCommand* p_command, T_mkAddr p_response, T_mkAddr p_buf, uint32_t* p_portStatus );
 * @brief Cette fonction transmet une commande à un périphérique MMC.
 *
 * @param[in]  p_handler    Ce paramètre contient l'adresse d'un gestionnaire de type \ref T_mkMMCHandler.
 * @param[in]  p_device     Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 * @param[in]  p_command    Ce paramètre contient l'adresse d'une commande de type \ref T_mkMMCCommand. Les attributs de la commande doivent être configurés avant l'appel de cette
 *                          fonction.
 * @param[out] p_response   Ce paramètre contient la valeur de la réponse obtenue suite à la transmission de la commande.
 *                          La valeur \ref K_MK_NULL peut être spécifiée si aucune réponse n'est attendue.
 * @param[in,out] p_buf     Ce paramètre contient l'adresse du buffer de données de la commande.
 *                          La valeur \ref K_MK_NULL peut être spécifiée si aucun buffer n'est nécessaire.
 * @param[out] p_portStatus Ce paramètre contient la valeur du registre de statut du port de communication.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la commande SD/MMC a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la commande SD/MMC a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la commande SD/MMC a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la commande SD/MMC a échoué en raison d'un timeout. La validité des paramètres p_response et p_buf est fonction du registre de statut du port.
 *         \li \ref K_MK_ERROR_COMM    : la commande SD/MMC a échoué en raison d'une erreur de communication. La validité des paramètres p_response et p_buf est fonction du registre
 *                                       de statut du port.
 *
 */

T_mkCode mk_mmc_sendCmd ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCCommand* p_command, T_mkAddr p_response, T_mkAddr p_buf, T_mkMMCPortStatus* p_portStatus );

/**
 *
 */

#endif

