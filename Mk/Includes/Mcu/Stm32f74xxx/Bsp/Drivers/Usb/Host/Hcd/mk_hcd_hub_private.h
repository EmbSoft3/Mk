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
* @file mk_hcd_hub_private.h
* @brief Déclaration des fonctions privées dédiées aux hubs USB.
* @date 11 oct. 2019
*
*/

#ifndef MK_HCD_HUB_PRIVATE_H
#define MK_HCD_HUB_PRIVATE_H

/**
 * @fn T_mkCode mk_hcd_initHub ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction initialise un hub.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_hub     Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le hub a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le hub n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le hub n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le périphérique n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le hub n'a pas été initialisé car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le hub n'a pas été initialisé en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note Cette fonction alloue dynamiquement un descriteur de hub et désalloue l'intégralité des interfaces non utilisée.
 *
 */

T_mkCode mk_hcd_initHub ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_initPort ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t p_portNumber );
 * @brief Cette fonction initialise un port d'un hub.
 *
 * @param[in, out] p_hub        Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro d'un port du hub.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le port a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le port n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le port n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le port n'a pas été initialisé car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le port n'a pas été initialisé en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_initPort ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t p_portNumber );

/**
 * @fn T_mkCode mk_hcd_initDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_portNumber, T_mkHCDPortStatus* p_portStatus );
 * @brief Cette fonction initialise un périphérique connecté sur un port d'un hub.
 *
 * @param[in]      p_handler    Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_hub        Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro d'un port du hub.
 * @param[in]      p_portStatus Ce paramètre contient les caractéristique du périphérique connecté sur le port.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le périphérique a été initialisé.
 *         \li \ref K_MK_ERROR_PARAM   : le périphérique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le périphérique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le périphérique n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le périphérique n'a pas été initialisé car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le périphérique n'a pas été initialisé en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_initDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_portNumber, T_mkHCDPortStatus* p_portStatus );

/**
 * @fn T_mkCode mk_hcd_getHubDescriptor ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction récupère le descripteur d'un hub.
 *
 * @param[in, out] p_hub  Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le descripteur de hub a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le descripteur de hub n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le descripteur de hub n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le descripteur de hub n'a pas été récupéré car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le descripteur de hub n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le descripteur de hub n'a pas été récupéré en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note Le descripteur de hub est alloué dynamiquement.
 *
 */

T_mkCode mk_hcd_getHubDescriptor ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_getHubStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, T_mkHCDHubStatus* p_status );
 * @brief Cette fonction récupère le registre de statut d'un hub.
 *
 * @param[in, out] p_hub     Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_status  Ce paramètre contient la valeur du registre de statut du hub.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le registre de statut du hub a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le registre de statut du hub n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le registre de statut du hub n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le registre de statut du hub n'a pas été récupéré car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le registre de statut du hub n'a pas été récupéré en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_getHubStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, T_mkHCDHubStatus* p_status );

/**
 * @fn T_mkCode mk_hcd_getHubInterrupt ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t* p_buf, T_mkHCDPipeStatus* p_status );
 * @brief Cette fonction récupère le registre d'interruption d'un hub.
 *
 * @param[in, out] p_hub       Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe      Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[out]     p_buf       Ce paramètre contient la valeur du registre d'interruption du hub.
 * @param[out]     p_status    Ce paramètre contient le statut du pipe.
 * @param[in]      p_bufLength Ce paramètre contient la taille du buffer où les données doivent être stockées.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le registre d'interruption du hub a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le registre d'interruption du hub n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le registre d'interruption du hub n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le registre d'interruption du hub n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le registre d'interruption du hub n'a pas été récupéré en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note La taille du buffer "p_buf" doit être dimensionnée de manière à supporter le nombre maximal de ports qu'un hub peut posséder.
 *
 */

T_mkCode mk_hcd_getHubInterrupt ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t* p_buf, T_mkHCDPipeStatus* p_status, uint16_t p_bufLength );

/**
 * @fn T_mkHCDPortEvent mk_hcd_getPortEvent ( uint8_t* p_buf, uint32_t p_portNumber, T_mkHCDPipeStatus p_pipeStatus );
 * @brief Cette fonction analyse le registre d'interruption d'un hub et indique si un événement est présent ou non.
 *
 * @param[in]      p_buf        Ce paramètre contient l'adresse d'un registre d'interruption.
 * @param[in, out] p_portNumber Ce paramètre contient le numéro du port à analyser.
 * @param[in, out] p_pipeStatus Ce paramètre contient le statut renvoyé par le pipe lors de la récupération du registre d'interruption.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_HCD_PORT_EVENT_DETECTED     : un événement a été détecté sur le port USB interrogé.
 *         \li \ref K_MK_HCD_PORT_EVENT_NOT_DETECTED : aucun événement n'a été détecté sur le port USB interrogé.
 *
 * @note La taille du buffer "p_buf" doit être dimensionnée de manière à supporter le nombre maximal de ports qu'un hub peut possèder.
 *
 */

T_mkHCDPortEvent mk_hcd_getPortEvent ( uint8_t* p_buf, uint32_t p_portNumber, T_mkHCDPipeStatus p_pipeStatus );

/**
 * @fn T_mkCode mk_hcd_setPortEvent ( uint8_t* p_buf, uint32_t p_portNumber );
 * @brief Cette fonction positionne un bit dans le registre d'interruption d'un hub.
 *
 * @param[in]      p_buf        Ce paramètre contient l'adresse d'un registre d'interruption.
 * @param[in, out] p_portNumber Ce paramètre contient le numéro d'un port du hub.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : l'événement a été positionné.
 *         \li \ref K_MK_ERROR_PARAM : l'événement n'a pas été positionné car au moins un paramètre est invalide.
 *
 * @note La taille du buffer "p_buf" doit être dimensionnée de manière à supporter le nombre maximal de ports qu'un hub peut possèder.
 *
 */

T_mkCode mk_hcd_setPortEvent ( uint8_t* p_buf, uint32_t p_portNumber );

/**
 * @fn T_mkCode mk_hcd_getPortStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_port, T_mkHCDPortStatus* p_status );
 * @brief Cette fonction récupère le registre de statut d'un port.
 *
 * @param[in, out] p_hub     Ce paramètre contient l'adresse d'un hub USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_port    Ce paramètre contient le numéro d'un port du hub.
 * @param[out]     p_status  Ce paramètre contient l'adresse d'une structure de type \ref T_mkHCDPortStatus stockant le registre de statut d'un port du hub.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le statut du port a été récupéré.
 *         \li \ref K_MK_ERROR_PARAM   : le statut du port n'a pas été récupéré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le statut du port n'a pas été récupéré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le statut du port n'a pas été récupéré car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le statut du port n'a pas été récupéré en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_getPortStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_port, T_mkHCDPortStatus* p_status );

/**
 * @fn T_mkCode mk_hcd_setPortFeature ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );
 * @brief Cette fonction active une feature d'un port.
 *
 * @param[in]      p_hub     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_value   Ce paramètre contient la valeur de la requête.
 * @param[in]      p_index   Ce paramètre contient l'index de la requête.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la feature a été activée.
 *         \li \ref K_MK_ERROR_PARAM   : la feature n'a pas été activée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la feature n'a pas été activée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la feature n'a pas été activée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la feature n'a pas été activée en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_setPortFeature ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );

/**
 * @fn T_mkCode mk_hcd_clearPortFeature ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );
 * @brief Cette fonction désactive une feature d'un port.
 *
 * @param[in]      p_hub     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_value   Ce paramètre contient la valeur de la requête.
 * @param[in]      p_index   Ce paramètre contient l'index de la requête.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la feature a été désactivée.
 *         \li \ref K_MK_ERROR_PARAM   : la feature n'a pas été désactivée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la feature n'a pas été désactivée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la feature n'a pas été désactivée car le périphérique cible n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la feature n'a pas été désactivée en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_clearPortFeature ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_value, uint16_t p_index );

/**
 * @fn T_mkCode mk_hcd_handleHub ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction gère l'intégralité des hubs présents sur le bus. Elle récupére leurs statuts puis déclenche les actions
 *        appropriées.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la fonction a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la fonction a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleHub ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_handleHubStatus ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction lit le registre d'interruption d'un hub puis déclenche les actions appropriées.
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in]      p_hub     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la fonction a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la fonction a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleHubStatus ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_handlePowerStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );
 * @brief Cette fonction active l'alimentation d'un port USB.
 *
 * @param[in]      p_hub        Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_device     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro du port USB.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'alimentation du port a été activée.
 *         \li \ref K_MK_ERROR_PARAM   : l'alimentation du port n'a pas été activée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'alimentation du port n'a pas été activée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'alimentation du port n'a pas été activée car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'alimentation du port n'a pas été activée en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handlePowerStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );

/**
 * @fn T_mkCode mk_hcd_handleHubOvercurrentStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction désactive tous les ports d'un hub suite à la détection d'une surcharge sur celui-ci.
 *
 * @param[in]      p_hub  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les ports ont été désactivés.
 *         \li \ref K_MK_ERROR_PARAM   : les ports n'ont pas été désactivés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : les ports n'ont pas été désactivés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les ports n'ont pas été désactivés car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les ports n'ont pas été désactivés en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note La désactivation de l'alimentation doit être réalisée par le hub selon la spécification USB2.0.
 *
 */

T_mkCode mk_hcd_handleHubOvercurrentStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_handlePortOvercurrentStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );
 * @brief Cette fonction désactive un port suite à la détection d'une surcharge sur celui-ci.
 *
 * @param[in]      p_hub        Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_device     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro du port USB.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le port a été désactivé.
 *         \li \ref K_MK_ERROR_PARAM   : le port n'a pas été désactivé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le port n'a pas été désactivé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le port n'a pas été désactivé car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le port n'a pas été désactivé en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @note La désactivation de l'alimentation doit être réalisée par le hub selon la spécification USB2.0.
 *
 */

T_mkCode mk_hcd_handlePortOvercurrentStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );

/**
 * @fn T_mkCode mk_hcd_handleConnectStatus ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );
 * @brief Cette fonction énumére le périphérique présent sur un port USB suite à la détection d'une connexion.
 *
 * @param[in]      p_handler    Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in]      p_hub        Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_device     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro du port USB.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'énumération du périphérique a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'énumération du périphérique a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'énumération du périphérique a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : l'énumération du périphérique a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'énumération du périphérique a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : l'énumération du périphérique a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleConnectStatus ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );

/**
 * @fn T_mkCode mk_hcd_handleInvalidStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );
 * @brief Cette fonction réalise les actions adéquates suite à la détection d'un statut invalide.
 *
 * @param[in]      p_hub        Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_device     Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in, out] p_pipe       Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]      p_portNumber Ce paramètre contient le numéro du port USB.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le mécanisme de recouvrement du périphérique a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le mécanisme de recouvrement du périphérique a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le mécanisme de recouvrement du périphérique a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le mécanisme de recouvrement du périphérique a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : le mécanisme de recouvrement du périphérique a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le mécanisme de recouvrement du périphérique a échoué en raison d'une erreur de communication. Le statut
 *                                       de la communication est disponible dans le paramètre "status" de la structure \ref T_mkHCDPipe.
 */

T_mkCode mk_hcd_handleInvalidStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber );

/**
 *
 */

#endif



