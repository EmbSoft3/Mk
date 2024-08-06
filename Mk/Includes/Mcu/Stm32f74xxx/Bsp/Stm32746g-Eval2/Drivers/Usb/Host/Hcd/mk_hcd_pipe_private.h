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
* @file mk_hcd_pipe_private.h
* @brief Déclaration des fonctions privées dédiées aux pipes USB.
* @date 8 oct. 2019
*
*/

#ifndef MK_HCD_PIPE_PRIVATE
#define MK_HCD_PIPE_PRIVATE

/**
 * @fn T_mkCode mk_hcd_openPipe ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe, uint8_t p_endpointType, uint8_t p_endpointNumber, uint16_t p_endpointMaxPacketSize );
 * @brief Cette fonction ouvre un pipe de communication. Le pipe est défini par un numéro et un type de terminaison ainsi que par la taille maximale d'un
 *        paquet.
 *
 * @param[in]  p_handler               Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[out] p_pipe                  Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]  p_endpointType          Ce paramètre contient le type de la terminaison. Les constantes suivantes peuvent être utilisées : \n
 *                                     \ref K_MK_HCD_ENDPOINT_CONTROL, \ref K_MK_HCD_ENDPOINT_INTERRUPT, \ref K_MK_HCD_ENDPOINT_BULK et \ref K_MK_HCD_ENDPOINT_ISOCHRONOUS.
 * @param[in]  p_endpointNumber        Ce paramètre contient le numéro de la terminaison USB. Les constantes \ref K_MK_HCD_ENDPOINT0 à \ref K_MK_HCD_ENDPOINT8 peuvent être
 *                                     utilisées.
 * @param[in]  p_endpointMaxPacketSize Ce paramètre contient la taille maximale des paquets de la terminaison.
 * @param[in]  p_timeout               Ce paramètre contient la valeur du timeout de transmission [en ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pipe a été ouvert.
 *         \li \ref K_MK_ERROR_PARAM   : le pipe n'a pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : le pipe n'a pas été ouvert car aucun canal de communication n'est disponible.
 *         \li \ref K_MK_ERROR_ISR     : le pipe n'a pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NESTED  : le pipe n'a pas été ouvert car la tâche appelante est déjà propriétaire d'un autre objet de synchronisation de type \ref T_mkMutex.
 */

T_mkCode mk_hcd_openPipe ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe, uint8_t p_endpointType, uint8_t p_endpointNumber, uint16_t p_endpointMaxPacketSize, uint32_t p_timeout );

/**
 * @fn T_mkCode mk_hcd_closePipe ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction ferme un pipe de communication.
 *
 * @param[in]  p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[out] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le pipe a été fermé.
 *         \li \ref K_MK_ERROR_PARAM : le pipe n'a pas été fermé car au moins un paramètre est invalide.
 */

T_mkCode mk_hcd_closePipe ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_setPipe ( T_mkHCDPipe* p_pipe, uint8_t p_endpointType, uint8_t p_endpointNumber, uint16_t p_endpointMaxPacketSize, uint32_t p_timeout );
 * @brief Cette fonction reconfigure un pipe de communication ouvert avec la fonction \ref mk_hcd_openPipe. L'identifiant du canal de communication
 *        utilisé n'est pas modifié.
 *
 * @param[out] p_pipe                  Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in]  p_endpointType          Ce paramètre contient le type de la terminaison. Les constantes suivantes peuvent être utilisées : \n
 *                                     \ref K_MK_HCD_ENDPOINT_CONTROL, \ref K_MK_HCD_ENDPOINT_INTERRUPT, \ref K_MK_HCD_ENDPOINT_BULK et \ref K_MK_HCD_ENDPOINT_ISOCHRONOUS.
 * @param[in]  p_endpointNumber        Ce paramètre contient le numéro de la terminaison USB. Les constantes \ref K_MK_HCD_ENDPOINT0 à \ref K_MK_HCD_ENDPOINT8 peuvent être
 *                                     utilisées.
 * @param[in]  p_endpointMaxPacketSize Ce paramètre contient la taille maximale des paquets de la terminaison.
 * @param[in]  p_timeout               Ce paramètre contient le timeout de transmission [en ms].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pipe a été reconfiguré.
 *         \li \ref K_MK_ERROR_PARAM   : le pipe n'a pas été reconfiguré car au moins un paramètre est invalide.
 */

T_mkCode mk_hcd_setPipe ( T_mkHCDPipe* p_pipe, uint8_t p_endpointType, uint8_t p_endpointNumber, uint16_t p_endpointMaxPacketSize, uint32_t p_timeout );

/**
 * @fn T_mkCode mk_hcd_copyPipe ( T_mkHCDPipe* p_inPipe, T_mkHCDPipe* p_outPipe );
 * @brief Cette fonction copie l'intégralité des attributs d'un pipe dans un second pipe.
 *
 * @param[out] p_inPipe  Ce paramètre contient l'adresse du pipe à copier.
 * @param[in]  p_outPipe Ce paramètre contient l'adresse du pipe acceuillant la copie.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : le pipe a été correctement copié.
 *         \li \ref K_MK_ERROR_PARAM : le pipe n'a pas été copié car au moins un paramètre est invalide.
 */

T_mkCode mk_hcd_copyPipe ( T_mkHCDPipe* p_inPipe, T_mkHCDPipe* p_outPipe );

/**
 * @fn T_mkCode mk_hcd_sendPipe ( T_mkHCDDevice* p_device, T_mkHCDEndpointDescriptor* p_endpoint, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_register, uint32_t p_length );
 * @brief Cette fonction déclenche l'envoi ou la réception d'un ou plusieurs paquets sur le bus USB.
 *
 * @param[in]      p_device   Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]      p_endpoint Ce paramètre contient l'adresse d'une terminaison USB de type \ref T_mkHCDEndpointDescriptor.
 * @param[in]      p_pipe     Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_buf      Ce paramètre contient l'adresse d'un buffer de données (utilisé en transmission ou en réception).
 * @param[in]      p_register Ce paramètre contient les caractéristiques du paquet. Il est constitué d'une combinaison des champs 'pid' et 'direction' organisé de
 *                            la manière suivante : p_register = pid <D31:D28> | direction <D27:D24>\n
 *                            Les constantes suivantes peuvent être utilisées :\n
 *                            \li pid : \ref K_MK_HCD_PID_DATA0, \ref K_MK_HCD_PID_DATA1, \ref K_MK_HCD_PID_DATA2, \ref K_MK_HCD_PID_SETUP, \ref K_MK_HCD_PID_MDATA et \ref K_MK_HCD_PID_TOOGLE
 *                            \li direction : \ref K_MK_HCD_ENDPOINT_OUT et \ref K_MK_HCD_ENDPOINT_IN
 * @param[in]      p_length   Ce paramètre contient le nombre d'octets à transférer ou recevoir.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert des paquets a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert des paquets a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert des paquets a échoué car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le transfert des paquets a échoué en raison d'une erreur de communication. Le statut de la communication est disponible dans le  paramètre "status"
 *                                       de la structure \ref T_mkHCDPipe.
 *
 * @note Le token \ref K_USB_PID_TOOGLE autorise le pipe à permuter le token automatiquement.
 * @note Le nombre de paquets envoyés ou reçus sur la terminaison est fonction du nombre d'octets p_length et de la taille maximal d'un paquet.
 * @warning Dans le cas d'une requête de type CONTROL_IN, si le nombre de données à recevoir est supérieur au nombre de données reçues, une corruption du buffer de réception peut se produire. Il est donc
 *          important de correctement configurer le paramètre 'p_length'. \n
 *
 */

T_mkCode mk_hcd_sendPipe ( T_mkHCDDevice* p_device, T_mkHCDEndpointDescriptor* p_endpoint, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_register, uint32_t p_length );

/**
 * @fn T_mkCode mk_hcd_startTransfer ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction déclenche l'envoi ou la réception d'un paquet sur le bus USB.
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in] p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert ou la réception du paquet a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert ou la réception du paquet a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le transfert ou la réception du paqueta échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert ou la réception du paquet car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : le transfert ou la réception du paquet en raison d'une erreur de communication. Le statut de la communication est disponible dans le
 *                                       paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @warning Cette fonction est privée. La fonction \ref mk_hcd_sendPipe doit être utilisée.
 *
 */

T_mkCode mk_hcd_startTransfer ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_haltTransfer ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );
 * @brief Cette fonction arrête l'envoi ou la réception d'un paquet sur le bus USB
 *
 * @param[in] p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in] p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le transfert ou la réception du paquet a été suspendu.
 *         \li \ref K_MK_ERROR_PARAM   : le transfert ou la réception du paquet n'a pas été suspendu car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le transfert ou la réception du paquet n'a pas été suspendu  car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le transfert ou la réception du paquet n'a pas été suspendu en raison d'une erreur du périphérique matériel.
 *
 * @warning Cette fonction est privée. La fonction \ref mk_hcd_sendPipe doit être utilisée.
 *
 */

T_mkCode mk_hcd_haltTransfer ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe );

/**
 * @fn T_mkCode mk_hcd_sendPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length );
 * @brief Cette fonction déclenche l'envoi ou la réception d'un ou plusieurs paquets sur le bus USB (mode normal).
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in]      p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]      p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_buf     Ce paramètre contient l'adresse d'un buffer de données (utilisé en transmission ou en réception).
 * @param[in]      p_length  Ce paramètre contient le nombre d'octets à transférer ou recevoir.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les paquets a été transmis ou reçus.
 *         \li \ref K_MK_ERROR_PARAM   : les paquets a été transmis ou reçus car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : les paquets a été transmis ou reçus car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les paquets a été transmis ou reçus car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les paquets a été transmis ou reçus en raison d'une erreur de communication. Le statut de la communication est disponible dans le
 *                                       paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @warning Cette fonction est privée. La fonction \ref mk_hcd_sendPipe doit être utilisée.
 *
 */

T_mkCode mk_hcd_sendPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length );

/**
 * @fn T_mkCode mk_hcd_sendSplitPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length );
 * @brief Cette fonction déclenche l'envoi ou la réception d'un ou plusieurs paquets sur le bus USB (mode split).
 *
 * @param[in]      p_handler Ce paramètre contient l'adresse d'un gestionnaire USB de type \ref T_mkHCDHandler.
 * @param[in]      p_device  Ce paramètre contient l'adresse d'un périphérique USB de type \ref T_mkHCDDevice.
 * @param[in]      p_pipe    Ce paramètre contient l'adresse d'un pipe de type \ref T_mkHCDPipe.
 * @param[in, out] p_buf     Ce paramètre contient l'adresse d'un buffer de données (utilisé en transmission ou en réception).
 * @param[in]      p_length  Ce paramètre contient le nombre d'octets à transférer ou recevoir.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les paquets a été transmis ou reçus.
 *         \li \ref K_MK_ERROR_PARAM   : les paquets a été transmis ou reçus car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : les paquets a été transmis ou reçus car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : les paquets a été transmis ou reçus car le périphérique n'a pas répondu.
 *         \li \ref K_MK_ERROR_COMM    : les paquets a été transmis ou reçus en raison d'une erreur de communication. Le statut de la communication est disponible dans le
 *                                       paramètre "status" de la structure \ref T_mkHCDPipe.
 *
 * @warning Cette fonction est privée. La fonction \ref mk_hcd_sendPipe doit être utilisée.
 *
 */

T_mkCode mk_hcd_sendSplitPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length );

/**
 *
 */

#endif

