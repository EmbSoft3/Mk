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
* @file mk_peripheral_usb.h
* @brief Déclaration des fonctions dédiées au périphérique USB.
* @todo Déterminer l'utilité des registres OTG_DEACHINT et OTG_DEACHINTMSK.
* @todo Déterminer si le bit ARPEN du registre DTHRCTL doit être implémenté.
* @date 18 mai 2019
*
*/

#ifndef MK_PERIPHERAL_USB_H
#define MK_PERIPHERAL_USB_H

/**
 * @fn void usb_enableDmaMode ( void_t p_usb );
 * @brief Cette fonction active le mode DMA du périphérique USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableDmaMode ( void );

/**
 * @fn void usb_disableDmaMode ( void_t p_usb );
 * @brief Cette fonction désactive le mode DMA du périphérique USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableDmaMode ( void );

/**
 * @fn uint32_t usb_getDMARequestStatus ( void );
 * @brief Cette fonction indique si une requête DMA est en cours d'exécution ou non.
 *        Cette fonction est réservé au périphérique USB_OTG_HS. Elle ne doit être utilisée
 *        que pour le debug.
 *
 * @return Cette fonction retourne une valeur 1 si une requête est en cours, sinon la valeur 0.
 *
 */

uint32_t usb_getDMARequestStatus ( void );

/**
 * @fn void usb_gate ( void_t p_usb, uint32_t p_mode );
 * @brief Cette fonction permet de stopper la transmission de l'horloge à un ou plusieurs modules du périphérique
 *        USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mode Ce paramètre contient un ou plusieurs masques de configuration. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n \ref K_USB_GATE_HCLK, \ref K_USB_GATE_PHY, \ref K_USB_GATE_CORE
 *                   ou \ref K_USB_GATE_NONE.
 *
 * @return Sans objet.
 *
 */

void usb_gate ( void_t p_usb, uint32_t p_mode );

/**
 * @fn void usb_setOTGRevision ( void_t p_usb, uint32_t p_revision );
 * @brief Cette fonction configure la version du protocole OTG à utiliser (1.3 ou 2.0). La version 1.3 réalise une impulsion
 *        sur les lignes de données et la ligne VBUS durant une séquence SRP. La version 2.0 réalise une impulsion uniquement
 *        sur les lignes de données.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_revision Ce paramètre contient l'indice de la spécification USB à utiliser. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_SPECIFICATION_1DOT3 et \ref K_USB_SPECIFICATION_2DOT0.
 *
 * @return Sans objet.
 *
 */

void usb_setOTGRevision ( void_t p_usb, uint32_t p_revision );

/**
 * @fn void usb_selectPHY ( uint32_t p_phy );
 * @brief Cette fonction selectionne le PHY du périphérique USB_OTGHS.
 *
 * @param[in] p_phy Ce paramètre contient le PHY à utiliser. Les constantes suivantes peuvent être utilisées : \n
 *                  \ref K_USB_PHY_FULLSPEED, \ref K_USB_PHY_HIGHSPEED_UTMI et \ref K_USB_PHY_HIGHSPEED_ULPI.
 *
 * @return Sans objet.
 *
 */

void usb_selectPHY ( uint32_t p_phy );

/**
 * @fn uint32_t usb_getPHYState ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction retourne l'état du PHY USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques. Une des constantes
 *                   suivantes peut être utilisée : \n \ref K_USB_PHY_DEEP_SLEEP_STATUS, \ref K_USB_PHY_SLEEP_STATUS
 *                   et \ref K_USB_PHY_SUSPENDED_STATUS.
 *
 * @return Cette fonction retourne une valeur non nulle si le PHY est en mode sommeil ou suspendu, sinon la valeur
 *         nulle.
 *
 */

uint32_t usb_getPHYState ( void_t p_usb, uint32_t p_flag );

/**
 * @fn uint32_t usb_reset ( void );
 * @brief Cette fonction reset le coeur USB, le positionne dans l'état de repos et nettoie l'intégralité des
 *        FIFOs de transmission et de récepion.
 *        Un delai de 3 cycles de l'horloge PHY doit être effectué après l'appel de cette fonction.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_reset ( void_t p_usb );

/**
 * @fn uint32_t usb_reset ( void );
 * @brief Cette fonction retourne le statut indiquant si l'opération de reset du coeur est en cours ou non.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction indique si une reset est en cours ou non. Elle renvoie les valeurs \ref K_USB_RESET_KO
 *         ou \ref K_USB_RESET_OK.
 *
 */

uint32_t usb_getResetStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_resetFrameCounter ( void );
 * @brief Cette fonction reset le coeur USB en conservant les informations d'énumération.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout permettant de s'assurer que l'opération
 *                      de réinitialisation a été effectuée. Il ne doit pas être nul.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_RESET_OK si l'opération a réussi, sinon la valeur
 *         \ref K_USB_RESET_KO.
 *
 */

uint32_t usb_resetPartial ( void_t p_usb, uint32_t p_timeout );

/**
 * @fn void usb_enableTransceiver ( void_t p_usb );
 * @brief Cette fonction active le transcodeur USBOTG en émission et en réception.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableTransceiver ( void_t p_usb );

/**
 * @fn void usb_disableTransceiver ( void_t p_usb );
 * @brief Cette fonction désactive le transcodeur USBOTG en émission et réception.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableTransceiver ( void_t p_usb );

/**
 * @fn void usb_enableOverride ( void_t p_usb );
 * @brief Cette fonction permet d'activer le bypass des signaux A_VALID, B_VALID et VBUS_VALID renvoyé par le layer
 *        physique (PHY).
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant les signaux à activer. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_OVERRIDE_AVALID_SIGNAL, \ref K_USB_OVERRIDE_BVALID_SIGNAL et
 *                   \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL.
 *
 * @note Les constantes \ref K_USB_OVERRIDE_AVALID_SIGNAL et \ref K_USB_OVERRIDE_BVALID_SIGNAL ne peuvent pas être
 *       utilisées en mode device. La constante \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL ne peut pas être utilisée
 *       en mode host.
 *
 * @return Sans objet.
 *
 */

void usb_enableOverride ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_disableOverride ( void_t p_usb );
 * @brief Cette fonction permet de désactiver le bypass des signaux A_VALID, B_VALID et VBUS_VALID renvoyé par le layer
 *        physique (PHY).
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant les signaux à désactiver. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_OVERRIDE_AVALID_SIGNAL, \ref K_USB_OVERRIDE_BVALID_SIGNAL et
 *                   \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL.
 *
 * @note Les constantes \ref K_USB_OVERRIDE_AVALID_SIGNAL et \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL ne peuvent pas être
 *       utilisées en mode host. La constante \ref K_USB_OVERRIDE_BVALID_SIGNAL ne peut pas être utilisée
 *       en mode device.
 *
 * @return Sans objet.
 *
 */

void usb_disableOverride ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_setOverride ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction permet d'attribuer la valeur 'Valide' aux signaux A_VALID, B_VALID et VBUS_VALID lorsque l'override
 *        est activé.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS
 *
 * @param[in] p_mask Ce paramètre est un masque contenant les signaux à configurer. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_OVERRIDE_AVALID_SIGNAL, \ref K_USB_OVERRIDE_BVALID_SIGNAL et
 *                   \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL.
 *
 * @note Les constantes \ref K_USB_OVERRIDE_AVALID_SIGNAL et \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL ne peuvent pas être
 *       utilisées en mode host. La constante \ref K_USB_OVERRIDE_BVALID_SIGNAL ne peut pas être utilisée
 *       en mode device.
 *
 * @return Sans objet.
 *
 */

void usb_setOverride ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_clearOverride ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction permet d'attribuer la valeur 'Invalide' aux signaux A_VALID, B_VALID et VBUS_VALID lorsque l'override
 *        est activé.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant les signaux à configurer. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_OVERRIDE_AVALID_SIGNAL, \ref K_USB_OVERRIDE_BVALID_SIGNAL et
 *                   \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL.
 *
 * @note Les constantes \ref K_USB_OVERRIDE_AVALID_SIGNAL et \ref K_USB_OVERRIDE_VBUSVALID_SIGNAL ne peuvent pas être
 *       utilisées en mode host. La constante \ref K_USB_OVERRIDE_BVALID_SIGNAL ne peut pas être utilisée
 *       en mode device.
 *
 * @return Sans objet.
 *
 */

void usb_clearOverride ( void_t p_usb, uint32_t p_mask );

/**
 * @fn uint32_t usb_getConnectorID ( void_t p_usb );
 * @brief Cette fonction indique si le dispositif est configuré en classe A (host) ou en classe B (device)
 *        en utilisant la ligne ID.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS
 *
 * @return Cette fonction retourne la valeur \ref K_USB_ID_CLASS_A ou la valeur \ref K_USB_ID_CLASS_B.
 *
 */

uint32_t usb_getConnectorID ( void_t p_usb );

/**
 * @fn void usb_enableVBUSComparators ( void_t p_usb );
 * @brief Cette fonction active les comparateurs du signal VBUS servant à fournir le signal VBUS_VALID. Si les protocoles
 *        HNP ou SRP sont activés, les comparateurs sont automatiquement activés.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableVBUSComparators ( void_t p_usb );

/**
 * @fn void usb_disableVBUSComparators ( void_t p_usb );
 * @brief Cette fonction désactive les comparateurs du signal VBUS servant à fournir le signal VBUS_VALID. Si les protocoles
 *        HNP ou SRP sont activés, les comparateurs doivent être activés.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableVBUSComparators ( void_t p_usb );

/**
 * @fn void usb_flushTxFifo ( void_t p_usb, uint32_t p_fifoNumber );
 * @brief Cette fonction permet de réinitialiser un ou tous les buffers de transmission.
 *        L'utilisateur doit s'assurer que le coeur USB n'est pas en en train d'accèder le ou les buffers
 *        en lecture ET écriture avant d'exécuter cette fonction. L'opération nécessite 8 cycles d'horloge
 *        AHB ou PHY pour se terminer. L'horloge de référence à prendre en compte est la plus petite des
 *        deux. Le timeout ne doit  pas être nul.
 *
 * @param[in] p_usb        Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                         peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_fifoNumber Ce paramètre contient le numéro du FIFO de transmission à réinitialiser. Les constantes
 *                         suivantes peuvent être utilisées : \n \ref K_USB_TXFIFO_0 à \ref K_USB_TXFIFO_15.
 *                         La constante K_USB_TXFIFO_ALL peut être utilisée pour réinitialiser tous les buffers
 *                         de transmission.
 *
 * @return Sans objet.
 *
 */

void usb_flushTxFifo ( void_t p_usb, uint32_t p_fifoNumber );

/**
 * @fn uint32_t usb_getFlushTxStatus ( void_t p_usb );
 * @brief Cette fonction retourne le statut du FIFO de type TX après le lancement d'une réinitialisation.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_FLUSH_OK si l'opération a réussi, sinon la valeur
 *         \ref K_USB_FLUSH_KO.
 *
 */

uint32_t usb_getFlushTxStatus ( void_t p_usb );

/**
 * @fn void usb_flushRxFifo ( void_t p_usb );
 * @brief Cette fonction permet de réinitialiser le buffer de réception.
 *        L'utilisateur doit s'assurer que le coeur USB n'est pas en en train d'accèder le buffer en lecture
 *        ET écriture avant d'exécuter cette fonction. Le flush nécessite 8 cycles d'horloge AHB ou PHY
 *        pour se terminer. L'horloge de référence à prendre en compte est la plus petite des deux.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_flushRxFifo ( void_t p_usb );

/**
 * @fn uint32_t usb_getFlushRxStatus ( void_t p_usb );
 * @brief Cette fonction retourne le statut du FIFO de type RX après le lancement d'une réinitialisation.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_FLUSH_OK si l'opération a réussi, sinon la valeur
 *         \ref K_USB_FLUSH_KO.
 *
 */

uint32_t usb_getFlushRxStatus ( void_t p_usb );

/**
 * @fn void usb_setRxFifoSize ( void_t p_usb, uint32_t p_size );
 * @brief Cette fonction permet de configurer la taille du FIFO de réception [en multiple de mots 32 bits].
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS
 * @param[in] p_size Ce paramètre contient la taille du FIFO de réception. La taille évolue de [16 à 1024]
 *                   pour le périphérique USBOTG_HS et évolue de [16 à 512] pour le périphérique USBOTG_FS.
 *
 * @return Sans objet.
 *
 */

void usb_setRxFifoSize ( void_t p_usb, uint32_t p_size );

/**
 * @fn void usb_getRxStatus ( void_t p_usb, uint32_t p_operation, T_USBOTGRxStatus* p_status )
 * @brief Cette fonction retourne le statut du prochain paquet à lire présent dans le FIFO de réception.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_operation Ce paramètre contient le type d'opération à effectuer. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_DEBUG_READ et \ref K_USB_POP.
 * @param[out] p_status   Ce paramètre contient l'adresse d'un registre de status de type \ref T_USBOTGRxStatus.
 *
 * @return Sans objet.
 *
 */

void usb_getRxStatus ( void_t p_usb, uint32_t p_operation, T_USBOTGRxStatus* p_status );

/**
 * @fn uint32_t usb_getIdleStatus ( void_t p_usb );
 * @brief Cette fonction indique si la machine à état est au repos ou non.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_IDLE si la machine est au repos, sinon la valeur
 *         \ref K_USB_BUSY.
 *
 */

uint32_t usb_getIdleStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getMode ( void_t p_usb );
 * @brief Cette fonction retourne le mode de fonctionnement du périphérique USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_HOST_MODE ou \ref K_USB_DEVICE_MODE.
 *
 */

uint32_t usb_getMode ( void_t p_usb );

/**
 * @fn void usb_setBurstLength ( uint32_t p_length );
 * @brief Cette fonction configure la taille des accès du périphérique USB_OTGHS.
 *
 * @param[in] p_length Ce paramètre contient la taille des accès. Les constantes suivantes peuvent être
 *                     utilisées :\n \ref K_USB_BURST_4WORDS, \ref K_USB_BURST_8WORDS, \ref K_USB_BURST_16WORDS.
 *
 * @note Cette fonction supporte les constantes \ref K_USB_BURST_1WORD_DO_NOT_USED et
 *       \ref K_USB_BURST_1WORD_DO_NOT_USED dont l'utilisation n'est pas conseillée.
 *
 * @return Sans objet.
 *
 */

void usb_setBurstLength ( uint32_t p_length );

/**
 * @fn void usb_setCoreId ( void_t p_usb, uint32_t p_id );
 * @brief Cette fonction configure l'identifiant du coeur USB sur 32 bits.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_id  Ce paramètre contient l'identifiant du coeur USB sur 32 bits.
 *
 * @return Sans objet.
 *
 */

void usb_setCoreId ( void_t p_usb, uint32_t p_id );

/**
 * @fn uint32_t usb_getCoreId ( void_t p_usb );
 * @brief Cette fonction retourne l'identifiant du coeur USB sur 32 bits.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur de l'identifiant du coeur USB.
 *
 */

uint32_t usb_getCoreId ( void_t p_usb );

/**
 * @fn void usb_setTurnaroundTime ( void_t p_usb, uint32_t p_time );
 * @brief Cette fonction permet de compenser la latence de lecture des accès AHB en augmentant le temps de réponse
 *        du périphérique USB_OTGHS.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_time Ce paramètre contient la latence. La constante suivante peut être utilisée en mode USB_HS :\n
 *                   \ref K_USB_HS_TRDT_AHB_30_MHZ_MIN.
 *                   Les constantes suivantes peuvent être utilisées en mode USBFS :\n
 *                   \ref K_USB_FS_TRDT_AHB_14DOT2_TO_15DOT0_MHZ, \ref K_USB_FS_TRDT_AHB_15DOT0_TO_16DOT0_MHZ,
 *                   \ref K_USB_FS_TRDT_AHB_16DOT0_TO_17DOT2_MHZ, \ref K_USB_FS_TRDT_AHB_17DOT2_TO_18DOT5_MHZ,
 *                   \ref K_USB_FS_TRDT_AHB_18DOT5_TO_20DOT0_MHZ, \ref K_USB_FS_TRDT_AHB_20DOT0_TO_21DOT8_MHZ,
 *                   \ref K_USB_FS_TRDT_AHB_21DOT8_TO_24DOT0_MHZ, \ref K_USB_FS_TRDT_AHB_24DOT0_TO_27DOT5_MHZ,
 *                   \ref K_USB_FS_TRDT_AHB_27DOT5_TO_32DOT0_MHZ et \ref K_USB_FS_TRDT_AHB_32_MHZ_MIN.\n
 *
 * @return Sans objet.
 *
 */

void usb_setTurnaroundTime ( void_t p_usb, uint32_t p_time );

/**
 * @fn void usb_setTimeoutCalibration ( void_t p_usb, uint32_t p_clock );
 * @brief Cette fonction permet de compenser les variations de PHY en ajoutant un timeout entre deux paquets.
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_clock Ce paramètre contient la valeur de calibration en multiple de PHY_CLOCK. La valeur
 *                    évolue entre [0 et 7].

 * @return Sans objet.
 *
 */

void usb_setTimeoutCalibration ( void_t p_usb, uint32_t p_clock );

/**
 * @fn void usb_maskInterrupts ( void_t p_usb );
 * @brief Cette fonction masque la totalité des interruptions USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS
 *
 * @note Suite à l'appel de cette fonction, les registres d'interruption sont mis à jour mais les exceptions ne sont pas
 *       déclenchées.
 *
 * @return Sans objet.
 *
 */

void usb_maskInterrupts ( void_t p_usb );

/**
 * @fn void usb_maskInterrupts ( void_t p_usb );
 * @brief Cette fonction démasque la totalité des interruptions USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_unmaskInterrupts ( void_t p_usb );

/**
 * @fn void usb_maskCoreInterrupts ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction masque un ou plusieurs drapeaux d'interruption du coeur d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position de l'interruption à masquer. Les constantes suivantes peuvent
 *                   être utilisées : \n
 *
 *                   \ref K_USB_WAKEUP_INTERRUPT, \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_VBUS_VALID_RANGE_INTERRUPT,
 *                   \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_ID_PIN_CHANGE_INTERRUPT, \ref K_USB_LPM_INTERRUPT,
 *                   \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT, \ref K_USB_PORT_INTERRUPT,
 *                   \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT, \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,\ref K_USB_OUT_ENDPOINT_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *                   \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT,
 *                   \ref K_USB_RESET_INTERRUPT, \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT,
 *                   \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT, \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT,
 *                   \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_RX_FIFO_NOT_EMPTY_INTERRUPT,
 *                   \ref K_USB_START_OF_FRAME_INTERRUPT, \ref K_USB_OTG_EVENT_INTERRUPT, \ref K_USB_MODE_MISMATCH_INTERRUPT et
 *                   \ref K_USB_CORE_ALL_INTERRUPTS.
 *
 * @note Les constantes \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT,
 *       \ref K_USB_PORT_INTERRUPT, \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT et \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT
 *       peuvent être utilisée en mode host.\n
 *
 *       Les constantes \ref K_USB_VBUS_VALID_RANGE_INTERRUPT, \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT,
 *       \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_INTERRUPT, \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *       \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT, \ref K_USB_RESET_INTERRUPT,
 *       \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT, \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT et
 *       \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT peuvent être utilisée en mode device. \n
 *
 * @return Sans objet.
 *
 */

void usb_maskCoreInterrupts ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_unmaskCoreInterrupts ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction démasque un ou plusieurs drapeaux d'interruption du coeur d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position de l'interruption à démasquer. Les constantes suivantes peuvent
 *                   être utilisées : \n
 *
 *                   \ref K_USB_WAKEUP_INTERRUPT, \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_VBUS_VALID_RANGE_INTERRUPT,
 *                   \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_ID_PIN_CHANGE_INTERRUPT, \ref K_USB_LPM_INTERRUPT,
 *                   \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT, \ref K_USB_PORT_INTERRUPT,
 *                   \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT, \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,\ref K_USB_OUT_ENDPOINT_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *                   \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT,
 *                   \ref K_USB_RESET_INTERRUPT, \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT,
 *                   \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT, \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT,
 *                   \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_RX_FIFO_NOT_EMPTY_INTERRUPT,
 *                   \ref K_USB_START_OF_FRAME_INTERRUPT, \ref K_USB_OTG_EVENT_INTERRUPT, \ref K_USB_MODE_MISMATCH_INTERRUPT et
 *                   \ref K_USB_CORE_ALL_INTERRUPTS.
 *
 * @note Les constantes \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT,
 *       \ref K_USB_PORT_INTERRUPT, \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT et \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT
 *       peuvent être utilisée en mode host.\n
 *
 *       Les constantes \ref K_USB_VBUS_VALID_RANGE_INTERRUPT, \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT,
 *       \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_INTERRUPT, \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *       \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT, \ref K_USB_RESET_INTERRUPT,
 *       \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT, \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT et
 *       \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT peuvent être utilisée en mode device. \n
 *
 *
 * @return Sans objet.
 *
 */

void usb_unmaskCoreInterrupts ( void_t p_usb, uint32_t p_mask );

/**
 * @fn uint32_t usb_getOTGInterruptFlag ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction retourne la valeur d'un drapeau d'interruption d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position de l'interruption à renvoyer. Une des constantes
 *                   suivantes peut être utilisée : \n
 *
 *                   \ref K_USB_ID_PIN_INTERRUPT, \ref K_USB_DEBOUNCE_DONE_INTERRUPT, \ref K_USB_HOST_TIMEOUT_INTERRUPT,
 *                   \ref K_USB_HNP_DETECTED_INTERRUPT, \ref K_USB_HNP_STATUS_INTERRUPT, \ref K_USB_SRP_STATUS_INTERRUPT,
 *                   \ref K_USB_END_OF_SESSION_INTERRUPT et \ref K_USB_OTG_ALL_INTERRUPTS.
 *
 * @note La constante \ref K_USB_DEBOUNCE_DONE_INTERRUPT peut être utilisée en mode host. Les autres peuvent être
 *       utilisées dans les deux modes.
 *
 * @return Cette fonction retourne une valeur non nulle si le drapeau d'interruption est positionné sinon la valeur 0.
 *
 */

uint32_t usb_getOTGInterruptFlag ( void_t p_usb, uint32_t p_mask );

/**
 * @fn uint32_t usb_getCoreInterruptFlag ( void_t p_usb );
 * @brief Cette fonction retourne la valeur d'un drapeau d'interruption du coeur d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position de l'interruption à renvoyer. Une des constantes
 *                   suivantes peut être utilisée : \n
 *
 *                   \ref K_USB_WAKEUP_INTERRUPT, \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_VBUS_VALID_RANGE_INTERRUPT,
 *                   \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_ID_PIN_CHANGE_INTERRUPT, \ref K_USB_LPM_INTERRUPT,
 *                   \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT, \ref K_USB_PORT_INTERRUPT,
 *                   \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT, \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,\ref K_USB_OUT_ENDPOINT_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *                   \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT,
 *                   \ref K_USB_RESET_INTERRUPT, \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT,
 *                   \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT, \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT,
 *                   \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_RX_FIFO_NOT_EMPTY_INTERRUPT,
 *                   \ref K_USB_START_OF_FRAME_INTERRUPT, \ref K_USB_OTG_EVENT_INTERRUPT, \ref K_USB_MODE_MISMATCH_INTERRUPT et
 *                   \ref K_USB_CORE_ALL_INTERRUPTS.
 *
 * @note Les constantes \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_PERIODIC_TXFIFO_EMPTY_INTERRUPT, \ref K_USB_CHANNELS_INTERRUPT,
 *       \ref K_USB_PORT_INTERRUPT, \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT et \ref K_USB_NON_PERIODIC_TXFIFO_EMPTY_INTERRUPT
 *       peuvent être utilisée en mode host.\n
 *
 *       Les constantes \ref K_USB_VBUS_VALID_RANGE_INTERRUPT, \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT,
 *       \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_INTERRUPT, \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *       \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT, \ref K_USB_RESET_INTERRUPT,
 *       \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT, \ref K_USB_GLOBAL_OUT_NACK_INTERRUPT et
 *       \ref K_USB_GLOBAL_NON_PERIODIC_IN_NACK_INTERRUPT peuvent être utilisée en mode device. \n
 *
 *       Les constantes \ref K_USB_LPM_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT sont dédiées au périphérique USB_OTGFS.
 *       La constante \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT est dédiée au périphérique USB_OTG_HS
 *
 * @return Cette fonction retourne une valeur non nulle si le drapeau d'interruption est positionné sinon la valeur 0.
 *
 */

uint32_t usb_getCoreInterruptFlag ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_clearOTGInterruptFlag ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction remet à zéro les drapeaux d'interruption d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position des interruptions à réinitialiser. Une combinaison
 *                   des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_ID_PIN_INTERRUPT, \ref K_USB_DEBOUNCE_DONE_INTERRUPT, \ref K_USB_HOST_TIMEOUT_INTERRUPT,
 *                   \ref K_USB_HNP_DETECTED_INTERRUPT, \ref K_USB_HNP_STATUS_INTERRUPT, \ref K_USB_SRP_STATUS_INTERRUPT,
 *                   \ref K_USB_END_OF_SESSION_INTERRUPT et \ref K_USB_OTG_ALL_INTERRUPTS.
 *
 * @note La constante \ref K_USB_DEBOUNCE_DONE_INTERRUPT ne peut être utilisée en mode host. Les autres peuvent être
 *       utilisées dans les deux modes.
 *
 * @return Sans objet.
 *
 */

void usb_clearOTGInterruptFlag ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_clearCoreInterruptFlag ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction remet à zéro les drapeaux d'interruption du coeur d'un périphérique USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre est un masque contenant la position de l'interruption à renvoyer. Les constantes suivantes peuvent
 *                   être utilisées : \n
 *
 *                   \ref K_USB_WAKEUP_INTERRUPT, \ref K_USB_SESSION_REQUEST_INTERRUPT, \ref K_USB_VBUS_VALID_RANGE_INTERRUPT,
 *                   \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_ID_PIN_CHANGE_INTERRUPT, \ref K_USB_LPM_INTERRUPT,
 *                   \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT, \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT,
 *                   \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *                   \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT,
 *                   \ref K_USB_RESET_INTERRUPT, \ref K_USB_SUSPENDED_STATE_INTERRUPT, \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT,
 *                   \ref K_USB_START_OF_FRAME_INTERRUPT, \ref K_USB_MODE_MISMATCH_INTERRUPT et \ref K_USB_CORE_ALL_INTERRUPTS.
 *
 * @note Les constantes \ref K_USB_SESSION_REQUEST_INTERRUPT et \ref K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT peuvent être utilisée
 *       en mode host.\n
 *
 *       Les constantes \ref K_USB_VBUS_VALID_RANGE_INTERRUPT, \ref K_USB_DISCONNECT_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT,
 *       \ref K_USB_INCOMPLETE_ISOCHRONOUS_OUT_TRANSFERT_INTERRUPT, \ref K_USB_INCOMPLETE_ISOCHRONOUS_IN_TRANSFERT_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_INTERRUPT, \ref K_USB_IN_ENDPOINT_INTERRUPT, \ref K_USB_END_OF_PERIODIC_FRAME_INTERRUPT,
 *       \ref K_USB_ISOCHRONOUS_OUT_PACKET_DROPPED_INTERRUPT, \ref K_USB_ENUMERATION_DONE_INTERRUPT, \ref K_USB_RESET_INTERRUPT,
 *       \ref K_USB_SUSPENDED_STATE_INTERRUPT et \ref K_USB_EARLY_SUSPENDED_STATE_INTERRUPT peuvent être utilisée en mode device. \n
 *
 *       Les constantes \ref K_USB_LPM_INTERRUPT, \ref K_USB_RESET_SUSPENDED_STATE_INTERRUPT sont dédiées au périphérique USB_OTGFS.
 *       La constante \ref K_USB_DATA_FETCH_SUSPENDED_INTERRUPT est dédiée au périphérique USB_OTG_HS.
 *
 * @return Sans objet.
 *
 */

void usb_clearCoreInterruptFlag ( void_t p_usb, uint32_t p_mask );

/**
 *
 */

/**
 * @fn void usb_disablePort ( void_t p_usb );
 * @brief Cette fonction désactive le port USB. L'activation du port est effectuée via une séquence de
 *        réinitialisation. Il est désactivé automatiquement par le coeur lors de la détection d'une surcharge
 *        ou d'une déconnexion. La fonction \ref usb_getPortStatus permet de récupérer l'état du port USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disablePort ( void_t p_usb );

/**
 * @fn void usb_enableHostMode ( void_t p_usb );
 * @brief Cette fonction force le périphérique USB en mode host indépendamment de l'état de la broche ID.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableHostMode ( void_t p_usb );

/**
 * @fn void usb_disableHostMode ( void_t p_usb );
 * @brief Cette fonction désactive le mécanisme d'activation forcée du mode host. L'état du périphérique USB est
 *        fonction de l'état de la broche ID.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableHostMode ( void_t p_usb );

/**
 * @fn void usb_resetPort ( void_t p_usb, uint32_t p_value );
 * @brief Cette fonction réinitialise le port USB. Le périphérique nécessite 10 ms pour la prise en compte
 *        du reset et 10 (LS et FS) ou 50 ms (HS) supplémentaires pour effectuer le reset.
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_value Ce paramètre contient la l'état de la réinitialisation. Les constantes suivantes peuvent
 *                    être utilisées : \n \ref K_USB_RESET_ENABLE et \ref K_USB_RESET_DISABLE.
 *
 * @return Sans objet.
 *
 */

void usb_resetPort ( void_t p_usb, uint32_t p_value );

/**
 * @fn void usb_setClass ( void_t p_usb, uint32_t p_mode );
 * @brief Cette fonction sélectionne la classe d'un dispositif host.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mode Ce paramètre contient la révision du protocole USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTG_HOST et \ref K_USB_EMBEDDED_HOST.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setClass ( void_t p_usb, uint32_t p_mode );

/**
 * @fn void usb_setPHYClock ( void_t p_usb, uint32_t p_speed );
 * @brief Cette fonction configure la vitesse des PHY LS et FS de la liaison USB.
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_speed Ce paramètre contient la vitesse de l'horloge. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_PHY_CLOCK_48MHZ et \ref K_USB_PHY_CLOCK_6MHZ.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. La constante \ref K_USB_PHY_CLOCK_6MHZ est réservée à un
 *       PHY de type LS.\n
 *       La fréquence d'horloge du PHY doit être configurée lors de la détection d'une connection sur le bus
 *       en fonction de la fréquence du périphérique connecté.
 *
 */

void usb_setPHYClock ( void_t p_usb, uint32_t p_speed );

/**
 * @fn void usb_setHostTestMode ( void_t p_usb, uint32_t p_mode );
 * @brief Cette fonction active le mode test et déclenche l'émission d'un pattern sur le bus. La constante
 *        \ref K_USB_TEST_MODE_DISABLE permet la désactivation du mode test.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mode Ce paramètre contient le type de la pattern à émettre sur le bus. Les constantes suivantes peuvent
 *                   être utilisées : \ref K_USB_TEST_MODE_DISABLE, \ref K_USB_TEST_MODE_J, \ref K_USB_TEST_MODE_K,
 *                   \ref K_USB_TEST_MODE_SE0_NAK, \ref K_USB_TEST_MODE_PACKET et \ref K_USB_TEST_FORCE_ENABLE.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setHostTestMode ( void_t p_usb, uint32_t p_mode );

/**
 * @fn void usb_enablePower ( void_t p_usb );
 * @brief Cette fonction active l'alimentation du bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_enablePower ( void_t p_usb );

/**
 * @fn void usb_disablePower ( void_t p_usb );
 * @brief Cette fonction désactive l'alimentation du bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_disablePower ( void_t p_usb );

/**
 * @fn void usb_enableResume ( void_t p_usb );
 * @brief Cette fonction positionne le port en mode fonctionnel. Le coeur USB active le processus de
 *        recouvrement indépendamment de l'application lorsqu'un paquet 'Remote Wakeup' est détecté.
 *        L'application a la charge de désactiver le processus de réveil à l'aide de la fonction
 *        \ref usb_disableResume lors du déclenchement de l'interruption correspondante (\ref K_USB_WAKEUP_INTERRUPT).
 *        Si le mode LPM est actif et que le coeur est en mode sommeil (L1), l'activation et la désactivation
 *        du recouvrement est effectué de manière automatique. Le signal est piloté pendant un durée définie
 *        par la fonction \ref usb_setBESLBehavior puis désactiver par le coeur.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_enableResume ( void_t p_usb );

/**
 * @fn void usb_disableResume ( void_t p_usb );
 * @brief Cette fonction doit être exécutée lorsque le processus de reveil du port et terminé (cf. fonction
 *        \ref usb_enableResume).
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_disableResume ( void_t p_usb );

/**
 * @fn void usb_suspendPort ( void_t p_usb );
 * @brief Cette fonction positionne le port en mode suspendu. Les paquets 'SOF' ne sont plus envoyés mais
 *        l'horloge du PHY reste cadencée par défaut. La fonction \ref usb_gate doit être appelée
 *        pour suspendre l'horloge du PHY dans ce mode.\n
 *        Ce mode est automatiquement désactivé lorsqu'un 'Remote Wakeup' est détecté, lorsqu'un périphérique
 *        est déconnecté du bus ou lors de l'appel des fonctions \ref usb_enableResume ou \ref usb_resetPort.\n
 *        La fonction \ref usb_getPortStatus permet de savoir si le bus est dans l'état suspendu.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_suspendPort ( void_t p_usb );

/**
 * @fn void usb_enableChannel ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction active un canal de communication du coeur USB.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

void usb_enableChannel ( void_t p_usb, uint32_t p_channel );

/**
 * @fn void usb_disableChannel ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction désactive un canal de communication du coeur USB.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

void usb_disableChannel ( void_t p_usb, uint32_t p_channel );

/**
 * @fn void usb_setChannel ( void_t p_usb, uint32_t p_channel, T_USBOTGChannel* p_addr );
 * @brief Cette fonction configure un canal de communication du coeur USB.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_addr    Ce paramètre contient l'adresse d'une structure de type \ref T_USBOTGChannel initialisée.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

void usb_setChannel ( void_t p_usb, uint32_t p_channel, T_USBOTGChannel* p_addr );

/**
 * @fn uint32_t usb_getPacketRemainder ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction retourne le nombre de paquets restant à transmettre dans un transfert.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Le nombre de paquets à transmettre dans le transfert USB courant.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

uint32_t usb_getPacketRemainder ( void_t p_usb, uint32_t p_channel );

/**
 * @fn uint32_t usb_getEndpointType ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction retourne le type d'une terminaison.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_CONTROL_ENDPOINT, \ref K_USB_ISOCHRONOUS_ENDPOINT,
 *         \ref K_USB_BULK_ENDPOINT ou \ref K_USB_INTERRUPT_ENDPOINT
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

uint32_t usb_getEndpointType ( void_t p_usb, uint32_t p_channel );

/**
 * @fn uint32_t usb_getEndpointDirection ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction retourne la direction d'une terminaison.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_IN_ENDPOINT ou \ref K_USB_OUT_ENDPOINT.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

uint32_t usb_getEndpointDirection ( void_t p_usb, uint32_t p_channel );

/**
 * @fn void usb_setStartSplit ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction active une transaction de type startSplit.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

void usb_setStartSplit ( void_t p_usb, uint32_t p_channel );

/**
 * @fn void usb_setCompleteSplit ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction active une transaction de type completeSplit.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

void usb_setCompleteSplit ( void_t p_usb, uint32_t p_channel );

/**
 * @fn uint32_t usb_getSplit ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction indique si la transaction en cours est de type split.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_SPLIT_TRANSACTION ou la valeur \ref K_USB_DEFAULT_TRANSACTION.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

uint32_t usb_getSplit ( void_t p_usb, uint32_t p_channel );

/**
 * @fn uint32_t usb_getSplitToken ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction indique le token courant d'une transaction de type split.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_TOKEN_SSPLIT ou la valeur \ref K_USB_TOKEN_CSPLIT.
 * @note Cette fonction est dédiée au mode host. \n Les constantes \ref K_USB_CHANNEL12 à \ref K_USB_CHANNEL15
 *       sont réservées pour le périphérique USB_OTGHS.
 *
 */

uint32_t usb_getSplitToken ( void_t p_usb, uint32_t p_channel );

/**
 * @fn uint32_t usb_getPortStatus ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction retourne un statut du port USB.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes
 *                   suivantes peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient l'identifiant du statut à retourner. Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_OTGDP_PIN_FLAG, \ref K_USB_OTGDM_PIN_FLAG, \ref K_USB_SUSPENDED_FLAG,
 *                   \ref K_USB_OVERCURRENT_CHANGE_FLAG, \ref K_USB_OVERCURRENT_FLAG,
 *                   \ref K_USB_PORT_ENABLED_CHANGE_FLAG, \ref K_USB_PORT_ENABLED_FLAG,
 *                   \ref K_USB_PORT_DEVICE_CONNECTED_FLAG, \ref K_USB_PORT_DEVICE_ATTACHED_FLAG.
 *
 * @return Cette fonction retourne une valeur fonction de l'identifiant présent en paramètre :
 *
 *         \li K_USB_OTGDP_PIN_FLAG : l'état logique de la broche OTG_DP,
 *         \li K_USB_OTGDM_PIN_FLAG : l'état logique de la broche OTG_DM,
 *         \li K_USB_SUSPENDED_FLAG : les valeurs \ref K_USB_SUSPEND_MODE_ENABLED ou \ref K_USB_SUSPEND_MODE_DISABLED,
 *         \li K_USB_OVERCURRENT_CHANGE_FLAG : les valeurs \ref K_USB_OVERCURRENT_CHANGED ou \ref K_USB_OVERCURRENT_NOT_CHANGED,
 *         \li K_USB_OVERCURRENT_FLAG : les valeurs \ref K_USB_OVERCURRENT_DETECTED ou \ref K_USB_OVERCURRENT_NOT_DETECTED,
 *         \li K_USB_PORT_ENABLED_CHANGE_FLAG : \ref K_USB_PORT_ENABLED_STATUS_CHANGED ou \ref K_USB_PORT_ENABLED_STATUS_NOT_CHANGED,
 *         \li K_USB_PORT_ENABLED_FLAG : les valeurs \ref K_USB_PORT_ENABLED ou \ref K_USB_PORT_DISABLED,
 *         \li K_USB_PORT_DEVICE_CONNECTED_FLAG : les valeurs \ref K_USB_DEVICE_CONNECTED ou \ref K_USB_DEVICE_NOT_CONNECTED,
 *         \li K_USB_PORT_DEVICE_ATTACHED_FLAG : les valeurs \ref K_USB_DEVICE_ATTACHED ou \ref K_USB_DEVICE_NOT_ATTACHED
 *
 * @note Cette fonction est dédiée au mode host. \n Les status \ref K_USB_OVERCURRENT_CHANGE_FLAG, \ref K_USB_PORT_ENABLED_CHANGE_FLAG
 *       et \ref K_USB_PORT_DEVICE_CONNECTED_FLAG nécessite une réinitialisation. La fonction \ref usb_clearStatus peut être utilisée à
 *       cet effet.
 *
 */

uint32_t usb_getPortStatus ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_clearStatus ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction réinitialise un statut du port USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient l'identifiant du statut à réinitialiser. Un des constantes suivantes peut être
 *                   utilisée : \n \ref K_USB_OVERCURRENT_CHANGE_FLAG, \ref K_USB_PORT_ENABLED_CHANGE_FLAG et
 *                   \ref K_USB_PORT_DEVICE_CONNECTED_FLAG et \ref K_USB_PORT_ENABLED_FLAG.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 * @warning La réinitialisation du drapeau \ref K_USB_PORT_ENABLED_CHANGE_FLAG s'effectue en écrivant la valeur 1 sur
 *          le drapeau \ref K_USB_PORT_ENABLED_FLAG. Cette action n'est pas spécifiée dans le datasheet.
 *
 */

void usb_clearStatus ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_enableFrameReload ( void_t p_usb );
 * @brief Cette fonction autorise l'exécution de la routine \ref usb_setFrameInterval lorsque le périphérique
 *        USB est en fonctionnement.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_enableFrameReload ( void_t p_usb );

/**
 * @fn void usb_disableFrameReload ( void_t p_usb );
 * @brief Cette fonction interdit la l'exécution de la routine \ref usb_setFrameInterval lorsque le périphérique
 *        USB est en fonctionnement.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_disableFrameReload ( void_t p_usb );

/**
 * @fn void usb_setFrameInterval ( void_t p_usb, uint32_t p_interval );
 * @brief Cette fonction configure la période inter-trames. Elle est exprimée en multiple de l'horloge du PHY.
 *        Cette période correspond à la durée entre deux 'Start Of Frame' (FS), deux 'Keep Alive' (LS) ou deux
 *        'micro Start Of Frame' (HS).
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_interval Ce paramètre contient la période entre deux trames en multiple de l'horloge du PHY.
 *                       Elle est exprimée sur 16 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.\n La période doit être configurée lorsque le port est
 *       activé (\ref usb_getPortStatus).\n Cette fonction peut être exécutée en runtime si la routine
 *       \ref usb_enableFrameReload a été appelée durant l'initialisation.
 *
 */

void usb_setFrameInterval ( void_t p_usb, uint32_t p_interval );

/**
 * @fn uint32_t usb_getFrameCounter ( void_t p_usb );
 * @brief Cette fonction retourne le numéro de la trame courante.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne le numéro de la trame courante. La valeur évolue entre [0 et 0x3FFF].
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getFrameCounter ( void_t p_usb );

/**
 * @fn uint32_t usb_getFrameTimeRemaining ( void_t p_usb );
 * @brief Cette fonction retourne la durée restante dans la période courante [en multiple de l'horloge du PHY].
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la durée restante dans la période courante.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getFrameTimeRemaining ( void_t p_usb );

/**
 * @fn uint32_t usb_resetFrameCounter ( void );
 * @brief Cette fonction permet de réinialiser le compteur de trames du coeur USB_OTGFS.
 *
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout permettant de s'assurer que l'opération
 *                      de réinitialisation a été effectuée. Il ne doit pas être nul.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_RESET_OK si l'opération a réussi, sinon la valeur
 *         \ref K_USB_RESET_KO.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_resetFrameCounter ( uint32_t p_timeout );

/**
 * @fn uint32_t usb_getHostStatus ( void_t p_usb );
 * @brief Cette fonction indique si le dispositif configuré en classe A (maitre) est connecté sur le bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur 1 si le dispositif est connecté sur le bus, sinon la valeur 0.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getHostStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getDebounceTime ( void_t p_usb );
 * @brief Cette fonction indique le type de la connection survenue sur le bus USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_PHYSICAL_CONNECTION ou la valeur \ref K_USB_SOFT_CONNECTION.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getDebounceTime ( void_t p_usb );

/**
 * @fn uint32_t usb_getPortSpeed ( void_t p_usb );
 * @brief Cette fonction retourne la vitesse du dispositif connecté sur le bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne une des valeurs suivantes : \n
 *         \ref K_USB_HIGH_SPEED, \ref K_USB_FULL_SPEED et \ref K_USB_LOW_SPEED.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getPortSpeed ( void_t p_usb );

/**
 * @fn void usb_setHostTxFifoEmptyLevel ( void_t p_usb, uint32_t p_type, uint32_t p_level );
 * @brief Cette fonction permet de configurer l'instant de déclenchement de l'interruption relative au FIFO de
 *        transmission (périodique et non périodique).
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_type  Ce paramètre contient le type du FIFO de transmission. Les constantes suivantes peuvent
 *                    être utilisées : \n \ref K_USB_PERIODIC_TXFIFO et \ref K_USB_NONPERIODIC_TXFIFO
 * @param[in] p_level Ce paramètre contient le niveau de déclenchement de l'interruption relative au FIFO de
 *                    transmission. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_USB_TXFIFO_HALF_EMPTY et \ref K_USB_TXFIFO_EMPTY.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setHostTxFifoEmptyLevel ( void_t p_usb, uint32_t p_type, uint32_t p_level );

/**
 * @fn void usb_setNonPeriodicTxFifoSize ( void_t p_usb, uint32_t p_size );
 * @brief Cette fonction permet de configurer la taille du FIFO de transmission non périodique [en multiple de
 *        mots 32 bits].
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_size Ce paramètre contient la taille du FIFO de transmission de type non périodique. La taille
 *                   évolue de [16 à 512].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setNonPeriodicTxFifoSize ( void_t p_usb, uint32_t p_size );

/**
 * @fn void usb_setNonPeriodicTxFifoAddr ( void_t p_usb, uint32_t p_addr );
 * @brief Cette fonction permet de configurer l'adresse de base du FIFO de transmission non périodique.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_addr Ce paramètre contient l'adresse de base du FIFO de transmission de type non périodique sur
 *                   16 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setNonPeriodicTxFifoAddr ( void_t p_usb, uint32_t p_addr );

/**
 * @fn void usb_setPeriodicTxFifoSize ( void_t p_usb, uint32_t p_size );
 * @brief Cette fonction permet de configurer la taille du FIFO de transmission périodique [en multiple de
 *        mots 32 bits].
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_size Ce paramètre contient la taille du FIFO de transmission de type périodique. La taille
 *                   évolue de [16 à 512].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setPeriodicTxFifoSize ( void_t p_usb, uint32_t p_size );

/**
 * @fn void usb_setPeriodicTxFifoAddr ( void_t p_usb, uint32_t p_addr );
 * @brief Cette fonction permet de configurer l'adresse de base du FIFO de transmission périodique.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_addr Ce paramètre contient l'adresse de base du FIFO de transmission de type périodique sur
 *                   16 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_setPeriodicTxFifoAddr ( void_t p_usb, uint32_t p_addr );

/**
 * @fn void usb_getNonPeriodicTxStatus ( void_t p_usb, T_USBOTGNonPeriodicTxStatus* p_status );
 * @brief Cette fonction retourne le statut du buffer de transmission non périodique et le statut de la file de requête.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[out] p_status Ce paramètre contient l'adresse d'un registre de status de type \ref T_USBOTGNonPeriodicTxStatus.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_getNonPeriodicTxStatus ( void_t p_usb, T_USBOTGNonPeriodicTxStatus* p_status );

/**
 * @fn void usb_getPeriodicTxStatus ( void_t p_usb, T_USBOTGPeriodicTxStatus* p_status );
 * @brief Cette fonction retourne le statut du buffer de transmission périodique et le statut de la file de requête.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[out] p_status Ce paramètre contient l'adresse d'un registre de status de type \ref T_USBOTGPeriodicTxStatus.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_getPeriodicTxStatus ( void_t p_usb, T_USBOTGPeriodicTxStatus* p_status );

/**
 * @fn uint32_t usb_getChannelStatus ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction retourne l'état d'un canal de communication.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_CHANNEL_IDLE, \ref K_USB_CHANNEL_DISABLED et \ref K_USB_CHANNEL_ENABLED.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getChannelStatus ( void_t p_usb, uint32_t p_channel );

/**
 * @fn void usb_maskGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction masque une ou plusieurs interruptions globales dédiées aux canaux de communication.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mask Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n
 *                   \ref K_USB_MASK_CHANNEL0 à \ref K_USB_MASK_CHANNEL15 et \ref K_USB_MASK_CHANNEL_ALL
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_maskGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_unmaskGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction démasque une ou plusieurs interruptions globales dédiées aux canaux de communication.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mask Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n
 *                   \ref K_USB_MASK_CHANNEL0 à \ref K_USB_MASK_CHANNEL15 et \ref K_USB_MASK_CHANNEL_ALL
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_unmaskGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );

/**
 * @fn uint32_t usb_getGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs drapeaux d'interruption global d'un canal.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mask Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n
 *                   \ref K_USB_MASK_CHANNEL0 à \ref K_USB_MASK_CHANNEL15 et \ref K_USB_MASK_CHANNEL_ALL
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 * @note Cette fonction est dédiée au mode host.
 *
 */

uint32_t usb_getGlobalChannelInterrupt ( void_t p_usb, uint32_t p_mask );

/**
 * @fn void usb_maskChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction masque une ou plusieurs interruptions dédiées aux canaux de communication.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

void usb_maskChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 * @fn void usb_unmaskChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction démasque une ou plusieurs interruptions dédiées aux canaux de communication.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

void usb_unmaskChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 * @fn void usb_clearChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction réinitialise une ou plusieurs interruptions dédiées aux canaux de communication.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

void usb_clearChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 * @fn uint32_t usb_getChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs drapeaux d'interruption d'un canal.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 *
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

uint32_t usb_getChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 * @fn uint32_t usb_getChannelInterruptMask ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs masque d'interruption d'un canal.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un masque d'interruption est positionné sinon
 *         la valeur 0.
 *
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

uint32_t usb_getChannelInterruptMask ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 * @fn uint32_t _usb_getClearChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );
 * @brief Cette fonction retourne et réinitialise la valeur d'un ou plusieurs drapeaux d'interruption d'un canal.
 *
 * @param[in] p_usb     Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                      peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel Ce paramètre contient le numéro du canal. Les constantes suivantes peuvent être
 *                      utilisées : \n \ref K_USB_CHANNEL0 à \ref K_USB_CHANNEL15.
 * @param[in] p_mask    Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                      suivantes peuvent être utilisées : \n
 *                      \ref K_USB_DATA_TOGGLE_INTERRUPT, \ref K_USB_FRAME_OVERRUN_INTERRUPT, \ref K_USB_BABBLE_ERROR_INTERRUPT,
 *                      \ref K_USB_TRANSACTION_ERROR_INTERRUPT, \ref K_USB_NYET_INTERRUPT, \ref K_USB_ACK_INTERRUPT,
 *                      \ref K_USB_NAK_INTERRUPT, \ref K_USB_STALL_INTERRUPT, \ref K_USB_AHB_ERROR_INTERRUPT,
 *                      \ref K_USB_CHANNEL_HALTED_INTERRUPT, \ref K_USB_TRANSFER_COMPLETED_INTERRUPT et
 *                      \ref K_USB_CHANNEL_ALL_INTERRUPTS.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 *
 * @note Cette fonction est dédiée au mode host.\n Les constantes \ref K_USB_NYET_INTERRUPT et \ref K_USB_AHB_ERROR_INTERRUPT
 *       sont réservées aux périphériques USB_OTGHS.
 *
 */

uint32_t _usb_getClearChannelInterrupt ( void_t p_usb, uint32_t p_channel, uint32_t p_mask );

/**
 *
 */

/**
 * @fn void usb_enableDeviceMode ( void_t p_usb );
 * @brief Cette fonction force le périphérique USB en mode device indépendamment de l'état de la broche ID.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableDeviceMode ( void_t p_usb );

/**
 * @fn void usb_enableDeviceMode ( void_t p_usb );
 * @brief Cette fonction désactive le mécanisme d'activation forcé du mode device. L'état du périphérique USB est
 *        fonction de l'état de la broche ID.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableDeviceMode ( void_t p_usb );

/**
 * @fn void usb_setDeviceSpeed ( void_t p_usb, uint32_t p_speed );
 * @brief Cette fonction configure la vitesse du périphérique USB (énumération et vitesse max).
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_speed Ce paramètre contient la vitesse du périphérique USB. Les constantes suivantes peuvent être
 *                    utilisées : \n
 *                    \ref K_USB_HIGH_SPEED et \ref K_USB_FULL_SPEED et \ref K_USB_FULL_SPEED_INTERNAL
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_HIGH_SPEED et \ref K_USB_FULL_SPEED
 *       sont réservée au périphérique USB_OTGHS.
 *
 */

void usb_setDeviceSpeed ( void_t p_usb, uint32_t p_speed );

/**
 * @fn void usb_setDeviceTestMode ( void_t p_usb, uint32_t p_mode );
 * @brief Cette fonction active le mode test et déclenche l'émission d'un pattern sur le bus. La constante
 *        \ref K_USB_TEST_MODE_DISABLE permet la désactivation du mode test.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_mode Ce paramètre contient le type de la pattern à émettre sur le bus. Les constantes suivantes peuvent
 *                   être utilisées : \ref K_USB_TEST_MODE_DISABLE, \ref K_USB_TEST_MODE_J, \ref K_USB_TEST_MODE_K,
 *                   \ref K_USB_TEST_MODE_SE0_NAK, \ref K_USB_TEST_MODE_PACKET et \ref K_USB_TEST_FORCE_ENABLE.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setDeviceTestMode ( void_t p_usb, uint32_t p_mode );

/**
 * @fn void usb_enableSoftDisconnect ( void_t p_usb );
 * @brief Cette fonction déconnecte de manière logiciel le périphérique du bus. L'application ne pas exécuter
 *        la fonction \ref usb_disableSoftDisconnect avant les durées suivantes pour que l'hôte prenne en compte
 *        la déconnexion :
 *        \li Full Speed - Suspended : 1ms + 2.5µs
 *        \li Full Speed - Idle : 2.5µs
 *        \li Full Speed - Not Idle, Not Suspended : 2.5µs
 *        \li High Speed - Not Idle, Not Suspended : 125µs
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_enableSoftDisconnect ( void_t p_usb );

/**
 * @fn void usb_enableSoftDisconnect ( void_t p_usb );
 * @brief Cette fonction reconnecte le périphérique sur le bus. L'hote déclenche alors un nouveau processus
 *        d'énumération.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_disableSoftDisconnect ( void_t p_usb );

/**
 * @fn void usb_enableRemoteWakeup ( void_t p_usb );
 * @brief Cette fonction génére une séquence de réveil de l'hôte. L'application doit appelée la fonction
 *        \ref usb_disableRemoteWakeup entre 1 et 15 ms après l'exécution de cette fonction, conformément
 *        à la spécification USB 2.0.
 *        Si le mode LPM est actif et que le coeur est en mode sommeil (L1), la requête est automatiquement
 *        désactivée 50µs après l'exécution de cette fonction (T_L1DevDrvResume). La fonction
 *        \ref usb_disableRemoteWakeup n'a pas besoin d'être appelée.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 * @warning Cette fonction ne doit pas être appelée si la fonction \ref usb_getRemoteWakeupValue retourne
 *          une valeur nulle.
 *
 */

void usb_enableRemoteWakeup ( void_t p_usb );

/**
 * @fn void usb_disableRemoteWakeup ( void_t p_usb );
 * @brief Cette fonction désactive la séquence de réveil de l'hôte.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_disableRemoteWakeup ( void_t p_usb );

/**
 * @fn void usb_disableRemoteWakeup ( void_t p_usb );
 * @brief Cette fonction indique au coeur que la configuration des registres du périphérique USB est terminée.
 *        Elle doit être appelée après un réveil du mode 'Power Down'.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setConfigurationDone ( void_t p_usb );

/**
 * @fn void usb_setDMAPeriodicFetchingTime ( uint32_t p_percent );
 * @brief Cette fonction configure la durée allouée au moteur DMA pour récupérer les données présente dans
 *        les terminaisons périodique de types IN. Après l'échéance de cette durée, le moteur DMA commence à traiter
 *        les terminaisons non périodique.
 *
 * @param[in] p_percent Ce paramètre contient un pourcentage de la période d'une trame. Les constantes suivantes
 *                      peuvent être utilisées : \n
 *                      \n K_USB_DMA_ALLOCATE_25_PERCENT_TO_FETCH_PERIODIC_ENDPOINT,
 *                      \n K_USB_DMA_ALLOCATE_50_PERCENT_TO_FETCH_PERIODIC_ENDPOINT et
 *                      \n K_USB_DMA_ALLOCATE_75_PERCENT_TO_FETCH_PERIODIC_ENDPOINT
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setDMAPeriodicFetchingTime ( uint32_t p_percent );

/**
 * @fn void usb_setEOFInterruptThreshold ( void_t p_usb, uint32_t p_threshold );
 * @brief Cette fonction configure la seuil de déclenchement de l'interruption 'End Of Frame Interrupt'.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_threshold Ce paramètre contient le seuil de déclenchement de l'interruption. Les constantes
 *                        suivantes peuvent être utilisées : \n
 *                        \ref K_USB_80_PERCENTS_OF_FRAME_INTERVAL, \ref K_USB_85_PERCENTS_OF_FRAME_INTERVAL,
 *                        \ref K_USB_90_PERCENTS_OF_FRAME_INTERVAL et \ref K_USB_95_PERCENTS_OF_FRAME_INTERVAL
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setEOFInterruptThreshold ( void_t p_usb, uint32_t p_threshold );

/**
 * @fn void usb_setDeviceAddress ( void_t p_usb, uint32_t p_addr );
 * @brief Cette fonction configure l'adresse USB du périphérique. Cette adresse est définie par le maitre.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_addr Ce paramètre contient l'adresse USB du dispositif sur 7 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setDeviceAddress ( void_t p_usb, uint32_t p_addr );

/**
 * @fn void usb_overwriteNZLPacketHandshake ( void_t p_usb, uint32_t p_handshake );
 * @brief Cette fonction définit le comportement du coeur lors de la réception d'un paquet de type
 *        'NonZeroLength'. Elle permet d'envoyer un statut STALL indépendamment du statut de la terminaison.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_handshake Ce paramètre contient le comportement du coeur. Les constantes suivantes peuvent être
 *                        utilisées : \n
 *                        \ref K_USB_NZL_RESPONSE_IS_STALL et \ref K_USB_NZL_RESPONSE_IS_DEFAULT
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_overwriteNZLPacketHandshake ( void_t p_usb, uint32_t p_handshake );

/**
 * @fn uint32_t usb_getDeviceStatus ( void_t p_usb );
 * @brief Cette fonction indique si le périphérique est connecté sur le bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur 1 si le dispositif est connecté sur le bus, sinon la valeur 0.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getDeviceStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getFrameNumber ( void_t p_usb );
 * @brief Cette fonction retourne le numéro de trame contenu dans le 'SOF' courant.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne le numéro de trame.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getFrameNumber ( void_t p_usb );

/**
 * @fn void usb_enableThreshold ( uint32_t p_type );
 * @brief Cette fonction active le déclenchement des transferts sur le bus AHB à partir d'un seuil de données.
 *
 * @param[in] p_type Ce paramètre contient le type de transfert. Une combinaison des constantes suivantes
 *                   peut être utilisées : \n \ref K_USB_THRESHOLD_RECEIVE_DIRECTION, \ref K_USB_THRESHOLD_NON_ISOCHRONOUS_IN_ENDPOINT et
 *                   \ref K_USB_THRESHOLD_ISOCHRONOUS_IN_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device et au périphérique USB_OTGHS.
 *
 */

void usb_enableThreshold ( uint32_t p_type );

/**
 * @fn void usb_disableThreshold ( uint32_t p_type );
 * @brief Cette fonction désactive le déclenchement des transferts sur le bus AHB à partir d'un seuil de données.
 *
 * @param[in] p_type Ce paramètre contient le type de transfert. Une combinaison des constantes suivantes
 *                   peut être utilisées : \n \ref K_USB_THRESHOLD_RECEIVE_DIRECTION, \ref K_USB_THRESHOLD_NON_ISOCHRONOUS_IN_ENDPOINT et
 *                   \ref K_USB_THRESHOLD_ISOCHRONOUS_IN_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device et au périphérique USB_OTGHS.
 *
 */

void usb_disableThreshold ( uint32_t p_type );

/**
 * @fn void usb_setThreshold ( uint32_t p_direction, uint32_t p_threshold );
 * @brief Cette fonction configure le seuil de déclenchement des transferts sur le bus AHB lors d'une transmission
 *        et d'une réception.
 *
 * @param[in] p_direction Ce paramètre contient la direction du transfert. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_RECEIVE_DIRECTION et \ref K_USB_TRANSMIT_DIRECTION.
 * @param[in] p_threshold Ce paramètre contient le seuil de déclenchement du transfert exprimé en DWORD sur 9 bits.
 *                        La valeur minimale est 8 DWORD, la valeur recommandée est celle configurée avec la fonction
 *                        \ref usb_setBurstLength.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device et au périphérique USB_OTGHS.
 *
 */

void usb_setThreshold ( uint32_t p_direction, uint32_t p_threshold );

/**
 * @fn uint32_t usb_getErraticErrorStatus ( void_t p_usb );
 * @brief Cette fonction indique si une erreur erratique à été détectée. Si une erreur est détectée, le
 *        controleur USB bascule en mode suspendu et une interruption est générée. L'application doit
 *        alors effectuer une déconnexion logiciel du bus.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_ERRATIC_ERROR_DETECTED ou \ref K_USB_ERRATIC_ERROR_NOT_DETECTED.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getErraticErrorStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getSignalStatus ( void_t p_usb );
 * @brief Cette fonction retourne l'état des broches DP et DM.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_usb Ce paramètre contient l'identifiant d'un signal USB. Les constantes suivantes peuvent être
 *                  utilisées : \n \ref K_USB_OTGDP_PIN_FLAG et \ref K_USB_OTGDM_PIN_FLAG.
 *
 * @return Cette fonction retourne le niveau logique du signal présent dans en paramètre.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getSignalStatus ( void_t p_usb, uint32_t p_signal );

/**
 * @fn uint32_t usb_getSuspendStatus ( void_t p_usb );
 * @brief Cette fonction indique si le bus USB est dans l'état suspendu.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_SUSPENDED_STATE ou \ref K_USB_NOT_SUSPENDED_STATE.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getSuspendStatus ( void_t p_usb );

/**
 * @fn void usb_enableGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction active le bypass de type NAK des terminaisons de type IN ou OUT.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le type de terminaison. Les constantes suivantes peuvent être
 *                   utilisées. \n
 *                   \ref K_USB_GLOBAL_OUT_NAK et \ref K_USB_GLOBAL_IN_NAK.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. La fonction \ref usb_getCoreInterruptFlag permet de
 *       savoir si le mécanisme de bypass est effectif ou non. Cette fonction ne doit être exécutée que
 *       si la fonction \ref usb_getCoreInterruptFlag retourne un status nulle.
 *
 */

void usb_enableGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_disableGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction désactive le bypass de type NAK des terminaisons de type IN ou OUT.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le type de terminaison. Les constantes suivantes peuvent être
 *                   utilisées. \n
 *                   \ref K_USB_GLOBAL_OUT_NAK et \ref K_USB_GLOBAL_IN_NAK.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_disableGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );

/**
 * @fn uint32_t usb_getGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction retourne la valeur du bypass de type NAK des terminaisons de type IN ou OUT.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le type de terminaison. Les constantes suivantes peuvent être
 *                   utilisées. \n
 *                   \ref K_USB_GLOBAL_OUT_NAK et \ref K_USB_GLOBAL_IN_NAK.
 *
 * @return Cette fonction retourne les valeurs K_HANDSHAKE_OVERWRITE ou K_HANDSHAKE_DEFAULT : \n
 *
 *         \li K_HANDSHAKE_OVERWRITE :
 *             Pour une terminaison de type OUT, aucune donnée n'est écrite dans le FIFO de réception,
 *             le statut NAK est envoyé pour tous les paquets à l'exception des paquets de type SETUP.
 *             Les paquets ISOCHRONES font exception à la régles précédente.
 *             Pour une terminaison de type IN, le statut NAK est envoyé pour chaque entrée non périodique.
 *
 *         \li K_HANDSHAKE_DEFAULT :
 *             Les statuts envoyés répondent à un fonctionnement normal.
 *
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getGlobalOverwriteStatus ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_enableINEndpoint ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction active un terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_enableINEndpoint ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn void usb_enableOUTEndpoint ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction active un terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT6 à
 *       \ref K_USB_OUT_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_enableOUTEndpoint ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn void usb_disableINEndpoint ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction désactive un terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_disableINEndpoint ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn void usb_disableOUTEndpoint ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction désactive un terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT6 à
 *       \ref K_USB_OUT_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.\n La terminaison 0 ne peut pas être
 *       désactivée.
 *
 */

void usb_disableOUTEndpoint ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn void usb_setINEndpoint ( void_t p_usb, uint32_t p_endpoint, T_USBOTGINEndpoint* p_addr );
 * @brief Cette fonction configure un terminaison de type IN du coeur USB.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_addr     Ce paramètre contient l'adresse d'une structure de type \ref T_USBOTGINEndpoint initialisée.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_setINEndpoint ( void_t p_usb, uint32_t p_endpoint, T_USBOTGINEndpoint* p_addr );

/**
 * @fn void usb_setOUTEndpoint ( void_t p_usb, uint32_t p_endpoint, T_USBOTGOUTEndpoint* p_addr );
 * @brief Cette fonction configure un terminaison de type OUT du coeur USB.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_addr     Ce paramètre contient l'adresse d'une structure de type \ref T_USBOTGOUTEndpoint initialisée.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT6 à
 *       \ref K_USB_OUT_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_setOUTEndpoint ( void_t p_usb, uint32_t p_endpoint, T_USBOTGOUTEndpoint* p_addr );

/**
 * @fn void usb_setINEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction positionne un ou plusieurs drapeaux de contrôle d'une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux à positionner. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_FLAG_EVEN_FRAME ou \ref K_USB_FLAG_PID_DATA0,
 *                       \ref K_USB_FLAG_ODD_FRAME, \ref K_USB_FLAG_NAK et \ref K_USB_FLAG_STALL.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_setINEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn void usb_setOUTEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction positionne un ou plusieurs drapeaux de contrôle d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux à positionner. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_FLAG_EVEN_FRAME ou \ref K_USB_FLAG_PID_DATA0,
 *                       \ref K_USB_FLAG_ODD_FRAME, K_USB_FLAG_PID_DATA1, \ref K_USB_FLAG_NAK et
 *                       \ref K_USB_FLAG_STALL.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_setOUTEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn void usb_clearINEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction réinitialise un ou plusieurs drapeaux de contrôle d'une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux à positionner. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_FLAG_CLEAR_NAK et \ref K_USB_FLAG_CLEAR_STALL.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_clearINEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn void usb_clearOUTEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction réinitialise un ou plusieurs drapeaux de contrôle d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux à positionner. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_FLAG_CLEAR_NAK et \ref K_USB_FLAG_CLEAR_STALL.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_clearOUTEndpointFlag ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn uint32_t usb_getINEndpointStatus ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne les statuts d'une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le statut à renvoyer. Une des constantes suivantes
 *                       peut être utilisées : \n \ref K_USB_STATUS_NAK, \ref K_USB_STATUS_EVEN_ODD_FRAME ou
 *                       \ref K_USB_STATUS_DATA_PID  et \ref K_USB_STATUS_ACTIVE.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li Pour un statut de type \ref K_USB_STATUS_NAK, la valeur 1 (NAK) ou 0 (NON-NAK),
 *         \li Pour un statut de type \ref K_USB_STATUS_EVEN_ODD_FRAME, la valeur 1 (ODD) ou 0 (EVEN),
 *         \li Pour un statut de type \ref K_USB_STATUS_DATA_PID, la valeur 1 (DATA1) ou 0 (DATA0),
 *         \li Pour un statut de type \ref K_USB_STATUS_ACTIVE, la valeur 1 (ACTIF) ou 0 (INACTIF).
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getINEndpointStatus ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn uint32_t usb_getOUTEndpointStatus ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne les statuts d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le statut à renvoyer. Une des constantes suivantes
 *                       peut être utilisées : \n \ref K_USB_STATUS_NAK, \ref K_USB_STATUS_EVEN_ODD_FRAME ou
 *                       \ref K_USB_STATUS_DATA_PID  et \ref K_USB_STATUS_ACTIVE.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li Pour un statut de type \ref K_USB_STATUS_NAK, la valeur 1 (NAK) ou 0 (NON-NAK),
 *         \li Pour un statut de type \ref K_USB_STATUS_EVEN_ODD_FRAME, la valeur 1 (ODD) ou 0 (EVEN),
 *         \li Pour un statut de type \ref K_USB_STATUS_DATA_PID, la valeur 1 (DATA1) ou 0 (DATA0),
 *         \li Pour un statut de type \ref K_USB_STATUS_ACTIVE, la valeur 1 (ACTIF) ou 0 (INACTIF).
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getOUTEndpointStatus ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn uint32_t usb_getINEndpointPacketCount ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne le nombre de paquets restant à envoyer sur le bus USB pour terminer le
 *        transfert sur une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 *
 * @return Cette fonction retourne le nombre de paquets restant à envoyer sur le bus USB.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getINEndpointPacketCount ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn uint32_t usb_getOUTEndpointPacketCount ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne le nombre de paquets restant à envoyer sur le bus USB pour terminer le
 *        transfert sur une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 *
 * @return Cette fonction retourne le nombre de paquets restant à envoyer sur le bus USB.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getOUTEndpointPacketCount ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn uint32_t usb_getINEndpointTransfertSize ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne le nombre d'octets restant à envoyer sur le bus USB pour terminer le
 *        transfert sur une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 *
 * @return Cette fonction retourne le nombre d'octets restant à envoyer sur le bus USB.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getINEndpointTransfertSize ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn uint32_t usb_getINEndpointTransfertSize ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne le nombre d'octets restant à envoyer sur le bus USB pour terminer le
 *        transfert d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 *
 * @return Cette fonction retourne le nombre d'octets restant à envoyer sur le bus USB.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getOUTEndpointTransfertSize ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn uint32_t usb_getTxFifoSpaceAvailable ( void_t p_usb, uint32_t p_endpoint );
 * @brief Cette fonction retourne le nombre de mots 32 bits disponibles dans le FIFO de transmission d'une
 *        terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 *
 * @return Cette fonction retourne le nombre de mots 32 bits disponibles dans le FIFO de transmission d'une
 *        terminaison de type IN.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT6 à
 *       \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getTxFifoSpaceAvailable ( void_t p_usb, uint32_t p_endpoint );

/**
 * @fn void usb_maskEarlySuspendInterrupt ( void_t p_usb );
 * @brief Cette fonction masque l'interruption de type 'EarlySuspendInterrupt'. Cette interruption est
 *        rattaché à l'interruption 'Erractic Error'.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_maskEarlySuspendInterrupt ( void_t p_usb );

/**
 * @fn void usb_unmaskEarlySuspendInterrupt ( void_t p_usb );
 * @brief Cette fonction démasque l'interruption de type 'EarlySuspendInterrupt'. Cette interruption est
 *        rattaché à l'interruption 'Erractic Error'.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_unmaskEarlySuspendInterrupt ( void_t p_usb );

/**
 * @fn void usb_maskINEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction masque une ou plusieurs interruptions d'une terminaison de type IN.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le ou les drapeaux d'interruptions à masquer.
 *                   Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT, \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT, \ref K_USB_IN_ENDPOINT_NAK_EFFECTIVE_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_MISMATCH_INTERRUPT, \ref K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT, \ref K_USB_IN_ENDPOINT_DISABLED_INTERRUPT et
 *                   \ref K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT et
 *       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_maskINEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_unmaskINEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction démasque une ou plusieurs interruptions d'une terminaison de type IN.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le ou les drapeaux d'interruptions à démasquer.
 *                   Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT, \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT, \ref K_USB_IN_ENDPOINT_NAK_EFFECTIVE_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_MISMATCH_INTERRUPT, \ref K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT,
 *                   \ref K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT, \ref K_USB_IN_ENDPOINT_DISABLED_INTERRUPT et
 *                   \ref K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT et
 *       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_unmaskINEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_clearINEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction réinitialise une ou plusieurs interruptions d'une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux d'interruptions à réinitialiser.
 *                       Une combinaison des constantes suivantes peut être utilisée : \n
 *                       \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT, \ref K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS, \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT, \ref K_USB_IN_ENDPOINT_DISABLED_INTERRUPT et
 *                       \ref K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT, \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT,
 *       \ref K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT et \ref K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS sont dédiées
 *       au périphérique USB_OTGHS.\n
 *       Les constantes \ref K_USB_IN_ENDPOINT6 à \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_clearINEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn uint32_t usb_getINEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs drapeaux d'interruption d'une terminaison de type IN.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_IN_ENDPOINT0 à \ref K_USB_IN_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux d'interruptions devant être renvoyés.
 *                       Une combinaison des constantes suivantes peut être utilisée : \n
 *                       \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT, \ref K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS, \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT, \ref K_USB_IN_ENDPOINT_TXFIFO_EMPTY_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_NAK_EFFECTIVE_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TOKEN_RECEIVED_WHEN_TXFIFO_EMPTY_INTERRUPT,
 *                       \ref K_USB_IN_ENDPOINT_TIMEOUT_INTERRUPT, \ref K_USB_IN_ENDPOINT_DISABLED_INTERRUPT et
 *                       \ref K_USB_IN_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_IN_ENDPOINT_BNA_INTERRUPT,
 *       \ref K_USB_IN_ENDPOINT_TXFIFO_UNDERRUN_INTERRUPT, \ref K_USB_IN_ENDPOINT_NAK_INTERRUPT,
 *       \ref K_USB_IN_ENDPOINT_BABBLE_ERROR_INTERRUPT et \ref K_USB_IN_ENDPOINT_PACKET_DROPPED_STATUS sont dédiées
 *       au périphérique USB_OTGHS.\n
 *       Les constantes \ref K_USB_IN_ENDPOINT6 à \ref K_USB_IN_ENDPOINT8 sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getINEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn void usb_maskOUTEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction masque une ou plusieurs interruptions d'une terminaison de type OUT.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le ou les drapeaux d'interruptions à masquer.
 *                   Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_OUT_ENDPOINT_NYET_INTERRUPT, \ref K_USB_OUT_ENDPOINT_BNA_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT, \ref K_USB_OUT_ENDPOINT_MISMATCH_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT, \ref K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT et
 *                   \ref K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT_NYET_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_BNA_INTERRUPT, \ref K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT
 *       et \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_maskOUTEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_unmaskOUTEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction démasque une ou plusieurs interruptions d'une terminaison de type OUT.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient le ou les drapeaux d'interruptions à démasquer.
 *                   Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_USB_OUT_ENDPOINT_NYET_INTERRUPT, \ref K_USB_OUT_ENDPOINT_BNA_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT, \ref K_USB_OUT_ENDPOINT_MISMATCH_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT,
 *                   \ref K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT, \ref K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT et
 *                   \ref K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT_NYET_INTERRUPT,
 *       \ref K_USB_OUT_ENDPOINT_BNA_INTERRUPT, \ref K_USB_OUT_ENDPOINT_FIFO_UNDERRUN_INTERRUPT
 *       et \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_unmaskOUTEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_clearOUTEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );
 * @brief Cette fonction réinitialise une ou plusieurs interruptions d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux d'interruptions à réinitialiser.
 *                       Une combinaison des constantes suivantes peut être utilisée : \n
 *                       \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT,
 *                       \ref K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT, \ref K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT et
 *                       \ref K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT6 à \ref K_USB_OUT_ENDPOINT8
 *       sont dédiées au périphérique USB_OTGHS.
 *
 */

void usb_clearOUTEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn uint32_t usb_getOUTEndpointInterrupt ( void_t p_usb, uint32_t p_channel );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs drapeaux d'interruption d'une terminaison de type OUT.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_endpoint Ce paramètre contient l'identifiant de la terminaison. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OUT_ENDPOINT0 à \ref K_USB_OUT_ENDPOINT8.
 * @param[in] p_flag     Ce paramètre contient le ou les drapeaux d'interruptions à renvoyer.
 *                       Une combinaison des constantes suivantes peut être utilisée : \n
 *                       \ref K_USB_OUT_ENDPOINT_B2B_SETUP_PACKETS_RECEIVED_INTERRUPT, \ref ,
 *                       \ref K_USB_OUT_ENDPOINT_SETUP_PHASE_DONE_INTERRUPT, \ref K_USB_OUT_ENDPOINT_DISABLED_INTERRUPT et
 *                       \ref K_USB_OUT_ENDPOINT_TRANSFER_COMPLETED_INTERRUPT.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 *
 * @note Cette fonction est dédiée au mode device. Les constantes \ref K_USB_OUT_ENDPOINT6 à \ref K_USB_OUT_ENDPOINT8
 *       sont dédiées au périphérique USB_OTGHS.
 *
 */

uint32_t usb_getOUTEndpointInterrupt ( void_t p_usb, uint32_t p_endpoint, uint32_t p_flag );

/**
 * @fn void usb_maskGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction masque une ou plusieurs interruptions globales dédiées aux terminaisons.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_MASK_IN_ENDPOINT0 à \ref K_USB_MASK_IN_ENDPOINT8, \ref K_USB_MASK_OUT_ENDPOINT0
 *                   à \ref K_USB_MASK_OUT_ENDPOINT7, \ref K_USB_MASK_ALL_IN_ENDPOINT et \ref K_USB_MASK_ALL_OUT_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_maskGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_unmaskGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction démasque une ou plusieurs interruptions globales dédiées aux terminaisons.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_MASK_IN_ENDPOINT0 à \ref K_USB_MASK_IN_ENDPOINT8, \ref K_USB_MASK_OUT_ENDPOINT0
 *                   à \ref K_USB_MASK_OUT_ENDPOINT7, \ref K_USB_MASK_ALL_IN_ENDPOINT et \ref K_USB_MASK_ALL_OUT_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode host.
 *
 */

void usb_unmaskGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn uint32_t usb_getGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs drapeaux d'interruption d'une terminaison.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_MASK_IN_ENDPOINT0 à \ref K_USB_MASK_IN_ENDPOINT8, \ref K_USB_MASK_OUT_ENDPOINT0
 *                   à \ref K_USB_MASK_OUT_ENDPOINT7, \ref K_USB_MASK_ALL_IN_ENDPOINT et \ref K_USB_MASK_ALL_OUT_ENDPOINT.
 *
 * @return Cette fonction retourne une valeur non nulle si au moins un drapeau d'interruption est positionné sinon
 *         la valeur 0.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getGlobalEndpointInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_maskINEndpointEmptyInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction masque une ou plusieurs interruptions de type 'Empty' d'une terminaison de type IN.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_MASK_IN_ENDPOINT0 à \ref K_USB_MASK_IN_ENDPOINT8 et \ref K_USB_MASK_ALL_IN_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_maskINEndpointEmptyInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_unmaskINEndpointEmptyInterrupt ( void_t p_usb, uint32_t p_flag );
 * @brief Cette fonction démasque une ou plusieurs interruptions de type 'Empty' d'une terminaison de type IN.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_flag Ce paramètre contient un ou plusieurs masques d'interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_USB_MASK_IN_ENDPOINT0 à \ref K_USB_MASK_IN_ENDPOINT8 et \ref K_USB_MASK_ALL_IN_ENDPOINT.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_unmaskINEndpointEmptyInterrupt ( void_t p_usb, uint32_t p_flag );

/**
 * @fn void usb_setEndpoint0TxFifoSize ( void_t p_usb, uint32_t p_size );
 * @brief Cette fonction permet de configurer la taille du FIFO de transmission de la terminaison 0 [en multiple de
 *        mots 32 bits].
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_size Ce paramètre contient la taille du FIFO de la terminaison EP0. La taille évolue de [16 à 512].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setEndpoint0TxFifoSize ( void_t p_usb, uint32_t p_size );

/**
 * @fn void usb_setEndpoint0TxFifoAddr ( void_t p_usb, uint32_t p_addr );
 * @brief Cette fonction permet de configurer l'adresse de base du FIFO de la terminaison 0.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_addr Ce paramètre contient l'adresse de base du FIFO de la terminaison 0 sur 11 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setEndpoint0TxFifoAddr ( void_t p_usb, uint32_t p_addr );

/**
 * @fn void usb_setEndpointTxFifoSize ( void_t p_usb, uint32_t p_fifo, uint32_t p_size );
 * @brief Cette fonction permet de configurer la taille du FIFO de transmission d'une terminaison en multiple de
 *        mots 32 bits.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_fifo Ce paramètre contient le numéro de la terminaison à configurer. Les constantes suivantes peuvent
 *                   être utilisées : \n
 *                   \li \ref K_USB_ENDPOINT1 à \ref K_USB_ENDPOINT5 pour le périphérique USBOTG_FS.
 *                   \li \ref K_USB_ENDPOINT1 à \ref K_USB_ENDPOINT8 pour le périphérique USBOTG_HS.
 * @param[in] p_size Ce paramètre contient la taille du FIFO de la terminaison. La taille évolue de [16 à 512].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setEndpointTxFifoSize ( void_t p_usb, uint32_t p_fifo, uint32_t p_size );

/**
 * @fn void usb_setEndpointTxFifoAddr ( void_t p_usb, uint32_t p_fifo, uint32_t p_addr );
 * @brief Cette fonction permet de configurer l'adresse de base du FIFO de transmission d'une terminaison.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_fifo Ce paramètre contient le numéro de la terminaison à configurer. Les constantes suivantes peuvent
 *                   être utilisées : \n
 *                   \li \ref K_USB_ENDPOINT1 à \ref K_USB_ENDPOINT5 pour le périphérique USBOTG_FS.
 *                   \li \ref K_USB_ENDPOINT1 à \ref K_USB_ENDPOINT8 pour le périphérique USBOTG_HS.
 * @param[in] p_addr Ce paramètre contient l'adresse de base du FIFO [sur 16 bits].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setEndpointTxFifoAddr ( void_t p_usb, uint32_t p_fifo, uint32_t p_addr );

/**
 * @fn void usb_setDeviceTxFifoEmptyLevel ( void_t p_usb, uint32_t p_level );
 * @brief Cette fonction permet de configurer l'instant de déclenchement de l'interruption relative au FIFO de
 *        transmission.
 *
 * @param[in] p_usb   Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                    peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_level Ce paramètre contient le niveau de déclenchement de l'interruption relative au FIFO de
 *                    transmission. Les constantes suivantes peuvent être utilisées : \n
 *                    \ref K_USB_TXFIFO_HALF_EMPTY et \ref K_USB_TXFIFO_EMPTY.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setDeviceTxFifoEmptyLevel ( void_t p_usb, uint32_t p_level );

/**
 *
 */

/**
 * @fn void usb_setULPI ( uint32_t p_mask );
 * @brief Cette fonction configure le PHY ULPI du périphérique USB_OTGHS.
 *
 * @param[in] p_mask Ce paramètre contient les masques de configuration. Une combinaison des constantes suivantes
 *                   peuvent être utilisées : \n
 *
 *                   \li \ref K_USB_ULPI_PROTECTION_ENABLED ou \ref K_USB_ULPI_PROTECTION_DISABLED, \n
 *                   \li \ref K_USB_ULPI_COMPLEMENT_OUTPUT_QUALIFIED ou \ref K_USB_ULPI_COMPLEMENT_OUTPUT_NOT_QUALIFIED, \n
 *                   \li \ref K_USB_ULPI_VBUS_INVERT_DISABLED ou \ref K_USB_ULPI_VBUS_INVERT_ENABLED, \n
 *                   \li \ref K_USB_ULPI_TX_VALID ou \ref K_USB_ULPI_TERMSEL, \n
 *                   \li \ref K_USB_ULPI_INTERNAL_VBUS_COMPARATOR ou \ref K_USB_ULPI_EXTERNAL_VBUS_COMPARATOR, \n
 *                   \li \ref K_USB_ULPI_CHARGE_PUMP ou \ref K_USB_ULPI_EXTERNAL_SUPPLY, \n
 *                   \li \ref K_USB_ULPI_CLOCK_POWERDOWN_ENABLED ou \ref K_USB_ULPI_CLOCK_POWERDOWN_DISABLED, \n
 *                   \li \ref K_USB_ULPI_AUTORESUME_ENABLED ou \ref K_USB_ULPI_AUTORESUME_DISABLED, \n
 *                   \li \ref K_USB_ULPI_INTERFACE_DEFAULT ou \ref K_USB_ULPI_INTERFACE_FULLSPEED, \n
 *                   \li \ref K_USB_ULPI_INTERNAL_PLL et \ref K_USB_ULPI_EXTERNAL_CLOCK. \n
 *
 * @return Sans objet.
 *
 */

void usb_setULPI ( uint32_t p_mask );

/**
 * @fn void usb_enableULPITiming ( void );
 * @brief Cette fonction ajoute une latence lors de la phase de configuration du PHY ULPI USB_OTGHS.
 *        Cette durée est nécessaire à la configuration de certain PHY ULPI.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_enableULPITiming ( void );

/**
 * @fn void usb_disableULPITiming ( void );
 * @brief Cette fonction supprimer la latence ajoutée lors de la phase de configuration du PHY ULPI USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_disableULPITiming ( void );

/**
 *
 */

/**
 * @fn void usb_enableHNPCapability ( void_t p_usb );
 * @brief Cette fonction active le support HNP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableHNPCapability ( void_t p_usb );

/**
 * @fn void usb_disableHNPCapability ( void_t p_usb );
 * @brief Cette fonction désactive le support HNP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableHNPCapability ( void_t p_usb );

/**
 * @fn void usb_sendHNPRequest ( void_t p_usb );
 * @brief Cette fonction déclenche une requête HNP sur le bus USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode device.
 * @return Sans objet.
 *
 */

void usb_sendHNPRequest ( void_t p_usb );

/**
 * @fn void usb_setHNPDeviceEnabled ( void_t p_usb );
 * @brief Cette fonction doit être appelée lorsque l'application a correctement reçue une commande de type
 *        SetFeature.SetHNPEnable en provenance du dispositif host.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode device.
 * @return Sans objet.
 *
 */

void usb_setHNPDeviceEnabled ( void_t p_usb );

/**
 * @fn void usb_setHNPDeviceEnabled ( void_t p_usb );
 * @brief Cette fonction doit être appelée lorsque l'application a correctement envoyée une commande de type
 *        SetFeature.SetHNPEnable au dispositif device.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode host.
 * @return Sans objet.
 *
 */

void usb_setHNPHostEnabled ( void_t p_usb );

/**
 * @fn void usb_sendHNPRequest ( void_t p_usb );
 * @brief Cette fonction retourne le résultat de la requête HNP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_HNP_SUCCESS ou \ref K_USB_HNP_FAILURE.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getHNPStatus ( void_t p_usb );

/**
 *
 */

/**
 * @fn void usb_enableSRPCapability ( void_t p_usb );
 * @brief Cette fonction active le support SRP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableSRPCapability ( void_t p_usb );

/**
 * @fn void usb_disableSRPCapability ( void_t p_usb );
 * @brief Cette fonction désactive le support SRP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableSRPCapability ( void_t p_usb );

/**
 * @fn void usb_sendSRPRequest ( void_t p_usb );
 * @brief Cette fonction déclenche une requête SRP sur le bus USB.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_sendSRPRequest ( void_t p_usb );

/**
 * @fn void usb_setSRPDischargeTime ( void_t p_usb, uint32_t p_time );
 * @brief Cette fonction configure la durée de la décharge du signal VBUS après une requête SRP.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_time Ce paramètre contient la durée de la décharge en multiple de l'horloge du PHY [sur 26 bits].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setSRPDischargeTime ( void_t p_usb, uint32_t p_time );

/**
 * @fn void usb_setSRPPulsingTime ( void_t p_usb, uint32_t p_time );
 * @brief Cette fonction configure la durée de l'impulsion du signal VBUS durant une requête SRP.
 *
 * @param[in] p_usb  Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                   peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_time Ce paramètre contient la durée de l'impulsion en multiple de l'horloge du PHY [sur 26 bits].
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode device.
 *
 */

void usb_setSRPPulsingTime ( void_t p_usb, uint32_t p_time );

/**
 * @fn uint32_t usb_getSRPStatus ( void_t p_usb );
 * @brief Cette fonction retourne le résultat de la requête SRP.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_SRP_SUCCESS ou \ref K_USB_SRP_FAILURE.
 * @note Cette fonction est dédiée au mode device.
 *
 */

uint32_t usb_getSRPStatus ( void_t p_usb );

/**
 *
 */

/**
 * @fn void usb_enableLPMCapability ( void_t p_usb );
 * @brief Cette fonction active le support LPM.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS
 *
 * @return Sans objet.
 *
 */

void usb_enableLPMCapability ( void_t p_usb );

/**
 * @fn void usb_disableLPMCapability ( void_t p_usb );
 * @brief Cette fonction désactive le support LPM.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableLPMCapability ( void_t p_usb );

/**
 * @fn void usb_enableBESLReject ( void_t p_usb );
 * @brief Cette fonction permet de rejeter les requêtes LPM dont la valeur du BESL est supérieur à la valeur configurée
 *        avec la routine \ref usb_setBESLBehavior. Le périphérique transmet alors un NYET à l'hôte.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode device.
 * @return Sans objet.
 *
 */

void usb_enableBESLReject ( void_t p_usb );

/**
 * @fn void usb_disableBESLReject ( void_t p_usb );
 * @brief Cette fonction désactive le mécanisme de rejection des requêtes LPM.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode device.
 * @return Sans objet.
 *
 */

void usb_disableBESLReject ( void_t p_usb );

/**
 * @fn void usb_setBESLBehavior ( void_t p_usb );
 * @brief Cette fonction active le support 'Best Effort Service Latency' conformément au document 'USB 2.0 Link Power
 *        Management Addendum Engineering Change Notice to the USB 2.0 specification, July 16, 2007'.
 *
 * @param[in] p_usb       Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                        peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_threshold En mode device, le coeur passe en état de sommeil (L1) si la latence BESL contenue dans la
 *                        trame LPM est supérieure ou égale à la latence définie par ce paramètre.\n
 *                        En mode host, ce paramètre définit la latence pour laquel le coeur engage la procédure de réveil
 *                        quand une condition de réveil est détectée.\n
 *                        Les constantes suivantes peuvent être utilisées :
 *                        \ref K_USB_BESL_THRESHOLD_75_US à \ref K_USB_BESL_THRESHOLD_950_US.
 *
 * @return Sans objet.
 *
 */

void usb_setBESLBehavior ( void_t p_usb, uint32_t p_threshold );

/**
 * @fn void usb_sendLPMRequest ( void_t p_usb, uint32_t p_channel, uint32_t p_besl, uint32_t p_remoteWakeup, uint32_t p_timeout );
 * @brief Cette fonction transmet une requête LPM.
 *
 * @param[in] p_usb          Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                           peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_channel      Ce paramètre contient le numéro de canal USB. Les constantes suivantes peuvent être
 *                           utilisées : \n \ref K_USB_LPM_CHANNEL0 à \ref K_USB_LPM_CHANNEL15.
 * @param[in] p_besl         Ce paramètre contient la valeur du 'BESL' contenu dans la transaction LPM. Les constantes
 *                           suivantes peuvent être utilisées : \n
 *                           \ref K_USB_BESL_125_US à \ref K_USB_BESL_10000_US
 * @param[in] p_remoteWakeup Ce paramètre contient la valeur du champ 'RemoteWakeup' de la requête LPM. Les constantes
 *                           suivantes peuvent être utilisées : \n
 *                           \ref K_USB_REMOTE_WAKEUP_ENABLED et \ref K_USB_REMOTE_WAKEUP_DISABLED
 * @param[in] p_timeout      Ce paramètre contient le nombre de fois où la commande est répéter tant qu'une réponse
 *                           non valide n'est pas reçue. Ce paramètre évolue entre 0 et 7.
 *
 * @note Les constante K_USB_CHANNEL12 à K_USB_CHANNEL15 sont dédiées au périphériques USBOTG_HS.\n
 *       Cette fonction est dédiée au mode host.
 * @return Sans objet.
 *
 */

void usb_sendLPMRequest ( void_t p_usb, uint32_t p_channel, uint32_t p_besl, uint32_t p_remoteWakeup, uint32_t p_timeout );

/**
 * @fn void usb_setLPMRequestResponse ( void_t p_usb, uint32_t p_response );
 * @brief Cette fonction configure la réponse à une requête LPM. Les réponses configurable sont 'ACK' et 'NYET'.
 *        En fonction de la validité du message LPM, le coeur retourne automatiquement les réponses 'STALL' ou
 *        'ERROR'.
 *
 * @param[in] p_usb      Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                       peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 * @param[in] p_response Ce paramètre contient la valeur de la réponse. Les constantes suivantes peuvent être
 *                       utilisées : \n \ref K_USB_LPM_ACK à \ref K_USB_LPM_NYET.
 *
 * @note Cette fonction est dédiée au mode host.
 * @return Sans objet.
 *
 */

void usb_setLPMRequestResponse ( void_t p_usb, uint32_t p_response );

/**
 * @fn void usb_enableLPMDeepSleep ( void_t p_usb );
 * @brief Cette fonction active le sommeil profond en mode L1.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableLPMDeepSleep ( void_t p_usb );

/**
 * @fn void usb_disableLPMDeepSleep ( void_t p_usb );
 * @brief Cette fonction désactive le sommeil profond en mode L1.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableLPMDeepSleep ( void_t p_usb );

/**
 * @fn void usb_enableLPMShallowSleep ( void_t p_usb );
 * @brief Cette fonction active le sommeil peu profond en mode L1.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_enableLPMShallowSleep ( void_t p_usb );

/**
 * @fn void usb_disableLPMShallowSleep ( void_t p_usb );
 * @brief Cette fonction désactive le sommeil peu profond en mode L1.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Sans objet.
 *
 */

void usb_disableLPMShallowSleep ( void_t p_usb );

/**
 * @fn uint32_t usb_getLPMRetryCount ( void_t p_usb );
 * @brief Cette fonction retourne le nombre d'essais restants dans la séquence courante d'une transaction LPM.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne le nombre d'essais restants dans la séquence courante.
 *
 */

uint32_t usb_getLPMRetryCount ( void_t p_usb );

/**
 * @fn uint32_t usb_getLPMRetryCount ( void_t p_usb );
 * @brief Cette fonction retourne la valeur de la réponse d'une transaction LPM. Cette fonction est valide
 *        lorsque le résultat de la fonction \ref usb_getLPMRetryCount est nul.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonction est dédiée au mode host.
 * @return Cette fonction retourne une des valeurs suivantes : \n
 *         \ref K_USB_LPM_ACK, \ref K_USB_LPM_NYET, \ref K_USB_LPM_STALL et \ref K_USB_LPM_ERROR.
 *
 */

uint32_t usb_getLPMResponse ( void_t p_usb );

/**
 * @fn uint32_t usb_getLPMSleepStatus ( void_t p_usb );
 * @brief Cette fonction indique si le coeur est en état de sommeil (L1).
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_L1_MODE_ENABLED et \ref K_USB_L1_MODE_DISABLED.
 *
 */

uint32_t usb_getLPMSleepStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getLPMReadyToWakeStatus ( void_t p_usb );
 * @brief Cette fonction indique si le coeur peut sortir de son état de sommeil (L1).
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @return Cette fonction retourne les valeurs \ref K_USB_READY_TO_WAKE ou \ref K_USB_NOT_READY_TO_WAKE.
 *
 */

uint32_t usb_getLPMReadyToWakeStatus ( void_t p_usb );

/**
 * @fn uint32_t usb_getRemoteWakeupValue ( void_t p_usb );
 * @brief Cette fonction retourne la valeur du champ 'bRemoteWake' contenu dans une requête LPM quand une
 *        réponse ACK, NYET ou STALL est transmise à l'hôte suite à la requête.
 *
 * @param[in] p_usb Ce paramètre contient l'adresse de base du périphérique USB. Les constantes suivantes
 *                  peuvent être utilisées : \n \ref K_USB_OTGFS et \ref K_USB_OTGHS.
 *
 * @note Cette fonctione est dédiée au mode device.
 * @return Cette fonction retourne la valeur du champ 'bRemoteWake'.
 *
 */

uint32_t usb_getRemoteWakeupValue ( void_t p_usb );

/**
 *
 */

/**
 * @fn void usb_enableI2C ( void );
 * @brief Cette fonction active la liaison I2C permetant la configuration d'un PHY externe de type USBOTG_FS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_enableI2C ( void );

/**
 * @fn void usb_disableI2C ( void );
 * @brief Cette fonction désactive la liaison I2C permetant la configuration d'un PHY externe de type USBOTG_FS.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_disableI2C ( void );

/**
 * @fn void usb_setI2CDeviceAddr ( uint32_t p_addr );
 * @brief Cette fonction configure la valeur des bits de poids faible de l'adresse I2C du PHY USBOTG_FS.
 *        En fonction du circuit sélectionné, l'adresse peut être configurée matériellement. Cette fonction
 *        est alors sans effet.
 *
 * @param[in] p_addr Ce paramètre contient la valeur des deux bits de poids faible de l'adresse I2C.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_setI2CDeviceAddr ( uint32_t p_addr );

/**
 * @fn void usb_setI2CInterface ( uint32_t p_interface );
 * @brief Cette fonction configure l'interface de pilotage du PHY USB.
 *
 * @param[in] p_interface Ce paramètre contient le type d'interface à utiliser. L'interface doit être sélectionnée
 *                        en fonction du modèle du PHY-USB. Les constantes suivantes peuvent être utilisées : \n
 *                        \ref K_USB_I2C_VP_VM_MODE et \ref K_USB_I2C_DAT_SE0_MODE.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_setI2CInterface ( uint32_t p_interface );

/**
 * @fn void usb_readI2C ( uint32_t p_addr, uint32_t p_register );
 * @brief Cette fonction transmet une commande de lecture à un périphérique sur le bus I2C. L'utilisateur doit
 *        s'assurer qu'une commande peut être transmise à l'aide de la fonction \ref usb_getI2CStatus. Le résultat
 *        de la commande peut être récupéré avec la fonction \ref usb_getI2CData.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse du périphérique I2C sur 7 bits.
 * @param[in] p_register Ce paramètre contient l'adresse du registre à lire sur 8 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_readI2C ( uint32_t p_addr, uint32_t p_register );

/**
 * @fn void usb_writeI2C ( void_t p_usb, uint32_t p_addr, uint32_t p_register, uint32_t p_data );
 * @brief Cette fonction transmet une commande d'écriture à un périphérique sur le bus I2C. L'utilisateur doit
 *        s'assurer qu'une commande peut être transmise à l'aide de la fonction \ref usb_getI2CStatus. Le résultat
 *        de la commande peut être récupéré avec la fonction \ref usb_getI2CData.
 *
 * @param[in] p_addr     Ce paramètre contient l'adresse du périphérique I2C sur 7 bits.
 * @param[in] p_register Ce paramètre contient l'adresse du registre à écrire sur 8 bits.
 * @param[in] p_data     Ce paramètre contient la valeur à écrire dans le registre sur 8 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

void usb_writeI2C ( uint32_t p_addr, uint32_t p_register, uint32_t p_data );

/**
 * @fn uint32_t usb_getI2CStatus ( void );
 * @brief Cette fonction retourne le statut du bus I2C.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_I2C_BUSY ou \ref K_USB_I2C_IDLE.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

uint32_t usb_getI2CStatus ( void );

/**
 * @fn uint32_t usb_getI2CData ( uint32_t* p_data );
 * @brief Cette fonction retourne le statut d'une commande. Dans le cas d'une lecture, elle retourne
 *        la valeur du registre lu.
 * @param[out] p_data Ce paramètre contient la valeur du registre lu.
 *
 * @return Cette fonction retourne la valeur \ref K_USB_I2C_ACK ou \ref K_USB_I2C_NACK.
 * @note Cette fonction est dédiée au périphérique USBOTG_FS.
 *
 */

uint32_t usb_getI2CData ( uint32_t* p_data );

/**
 *
 */

#endif
