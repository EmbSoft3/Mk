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
* @file mk_hcd_private.h
* @brief Déclaration des fonctions privées dédiées à l'USB.
* @date 12 juin 2019
*
*/

#ifndef MK_HCD_PRIVATE_H
#define MK_HCD_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_initArea ( void );
 * @brief Cette fonction initialise les gestionnaires d'allocation dynamique USB.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK           : les gestionnaires d'allocation dynamique ont été initialisés.
 *         \li \ref K_MK_ERROR_MALLOC : les gestionnaires d'allocation dynamique n'ont pas été initialisés car la taille du buffer primaire est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les gestionnaires d'allocation dynamique n'ont pas été initialisés car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hcd_initArea ( void );

/**
 * @fn T_mkCode mk_hcd_initHandler ( T_mkHCDHandler* p_handler, T_mkAddr p_bus );
 * @brief Cette fonction initialise un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in]  p_bus         Ce paramètre contient l'adresse de base d'un périphérique matériel. Les constantes suivantes peuvent être utilisées : \n
 *                           \ref K_USB_OTGHS et \ref K_USB_OTGFS
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le gestionnaire USB a été été initialisé.
 *         \li \ref K_MK_ERROR_PARAM : le gestionnaire USB n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : le gestionnaire USB n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_hcd_initHandler ( T_mkHCDHandler* p_handler, T_mkAddr p_bus );

/**
 * @fn T_mkCode mk_hcd_resetTree ( T_mkHCDList* p_list, T_mkHCDDevice* p_device, uint32_t p_mode );
 * @brief Cette fonction supprime l'intégralité de l'arborescence des périphériques USB.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'ensemble des périphériques USB ont été supprimé de l'arborescence des périphériques.
 *         \li \ref K_MK_ERROR_PARAM : l'ensemble des périphériques USB n'ont pas été supprimé de l'arborescence car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'ensemble des périphériques USB n'ont pas été supprimé de l'arborescence car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 * @note Si le périphérique est un hub, cette fonction supprime tous les périphériques présent en aval.
 * @warning Attention, la suppression des dispositifs est réalisée de manière \a récursive.
 *
 */

T_mkCode mk_hcd_resetTree ( T_mkHCDHandler* p_handler );

/**
 * @fn T_mkCode mk_hcd_signalDisconnectEvent ( T_mkHCDDevice* p_device );
 * @brief Cette fonction actualise le registre d'état d'un ou plusieurs périphériques USB afin de signaler leur déconnexion du bus.
 * @param[in, out] p_device Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'actualisation des périphériques a été réalisé.
 *         \li \ref K_MK_ERROR_PARAM : l'actualisation des périphériques n'a pas été réalisé car au moins un paramètre est invalide.
 *
 * @warning Attention, la signalisation est réalisée de manière \a récursive.
 *
 */

T_mkCode mk_hcd_signalDisconnectEvent ( T_mkHCDDevice* p_device );

/**
 * @fn T_mkCode mk_hcd_handleHostEvent ( T_mkAddr p_termio, T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction traite les événements envoyés par le périphérique matériel USB. En addition, elle transmet à intervalle régulier un
 *        événement permettant le rafraichissement des hubs connectés sur le bus.
 *
 * @param[in, out] p_termio  Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le ou les événements ont été traités.
 *         \li \ref K_MK_ERROR_PARAM   : le ou les événements n'ont pas été traités car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_INIT    : le ou les événements n'ont pas été traités en raison d'une erreur d'initialisation.
 *         \li \ref K_MK_ERROR_ISR     : le ou les événements n'ont pas été traités car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le ou les événements n'ont pas été traités car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le ou les événements n'ont pas été traités car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le ou les événements n'ont pas été traités en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleHostEvent ( T_mkAddr p_termio, T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_handleHostMode ( T_mkAddr p_termio, T_mkHCDHandler* p_handler );
 * @brief Cette fonction supprime le terminal de type host lorsqu'un événement ID_PIN_CHANGE est détecté. Elle active ensuite
 *        le terminal de type device.
 *
 * @param[in, out] p_termio  Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_ERROR_PARAM   : les traitements de la fonction ont échoués car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_INIT    : les traitements de la fonction ont échoués en raison d'une erreur d'initialisation.
 *         \li \ref K_MK_ERROR_ISR     : les traitements de la fonction ont échoués car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : les traitements de la fonction ont échoués car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : les traitements de la fonction ont échoués car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les traitements de la fonction ont échoués en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note En cas de réussite de la fonction, cette fonction ne retourne aucun résultat (destruction de la tâche).
 *
 */

T_mkCode mk_hcd_handleHostMode ( T_mkAddr p_termio, T_mkHCDHandler* p_handler );

/**
 * @fn T_mkCode mk_hcd_handleConnect ( T_mkHCDHandler* p_handler );
 * @brief Cette fonction initialise le port USB suite à la connexion du premier périphérique USB sur le bus.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'initialisation du port USB a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'initialisation du port USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'initialisation du port USB a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_INIT    : l'initialisation du port USB a échoué en raison d'une erreur d'initialisation (timeout matériel).
 *         \li \ref K_MK_ERROR_MALLOC  : l'initialisation du port USB a échoué en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_hcd_handleConnect ( T_mkHCDHandler* p_handler );

/**
 * @fn T_mkCode mk_hcd_handleDisconnect ( T_mkHCDHandler* p_handler );
 * @brief Cette fonction supprime l'arborescence des périphériques USB suite à la déconnexion du premier périphérique USB du bus.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la suppression de l'arborescence a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la suppression de l'arborescence a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la suppression de l'arborescence a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la suppression de l'arborescence a échoué en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_hcd_handleDisconnect ( T_mkHCDHandler* p_handler );

/**
 * @fn T_mkCode mk_hcd_handleEnable ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction initialise le premier périphérique USB connecté sur le bus.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'initialisation du périphérique USB a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'initialisation du périphérique USB a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'initialisation du périphérique USB a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : l'initialisation du périphérique USB a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'initialisation du périphérique USB a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'initialisation du périphérique USB a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note Cette fonction alloue dynamiquement le premier périphérique du bus.
 *
 */

T_mkCode mk_hcd_handleEnable ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_handleOvercurrent ( T_mkHCDHandler* p_handler );
 * @brief Cette fonction désactive l'alimentation du bus USB lorsqu'une surchage est détectée. L'arborescence des périphériques USB est totalement supprimée.
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la gestion de la surchage a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la gestion de la surchage a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la gestion de la surchage a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la gestion de la surchage a échoué car une erreur d'allocation dynamique s'est produite.
 */

T_mkCode mk_hcd_handleOvercurrent ( T_mkHCDHandler* p_handler );

/**
 * @fn T_mkCode mk_hcd_handleRefresh ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction rafraichis les hubs connectés sur le bus USB. Si l'initialisation du premier périphérique USB avait échouée, elle relance
 *        le processus d'énumération.
 *        Cette fonction est déclenchée à intervalle régulier par le biais d'un événement.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la séquence de rafraichissement des hubs a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la séquence de rafraichissement des hubs a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la séquence de rafraichissement des hubs a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la séquence de rafraichissement des hubs a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la séquence de rafraichissement des hubs a échoué car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la séquence de rafraichissement des hubs a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleRefresh ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 *
 */

#endif
