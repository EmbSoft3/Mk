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
* @file mk_peripheral_i2c.h
* @brief Déclaration des fonction dédiées au périphérique I2C.
* @date 15 juil. 2020
*
*/

#ifndef MK_PERIPHERAL_I2C_H
#define MK_PERIPHERAL_I2C_H

/**
 * @fn void i2c_enablePacketErrorChecking ( void_t p_addr );
 * @brief Cette fonction active la couche protocolaire PEC (Packet Error Checking) dédiée aux communications SMBus.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_enablePacketErrorChecking ( void_t p_addr );

/**
 * @fn void i2c_disablePacketErrorChecking ( void_t p_addr );
 * @brief Cette fonction désactive la couche protocolaire PEC (Packet Error Checking) dédiée aux communications SMBus.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_disablePacketErrorChecking ( void_t p_addr );

/**
 * @fn void i2c_enableAlert ( void_t p_addr );
 * @brief Le comportement de cette fonction diffère en fonction du mode de fonctionnement. En mode 'Master', cette fonction active
 *        la surveillance de la broche d'alarme dédiée au communications SMBUS. En mode 'Slave', cette fonction configure la broche SMBA
 *        à l'état bas afin de générer une alerte. Elle active ensuite l'adresse dédiée aux réponses du mode alerte.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_enableAlert ( void_t p_addr );

/**
 * @fn void i2c_disableAlert ( void_t p_addr );
 * @brief Le comportement de cette fonction diffère en fonction du mode de fonctionnement. En mode 'Master', cette fonction désactive
 *        la surveillance de la broche d'alarme dédiée au communications SMBUS. En mode 'Slave', cette fonction configure la broche SMBA
 *        à l'état haut afin de stopper la génération de l'alerte.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_disableAlert ( void_t p_addr );

/**
 * @fn void i2c_enableAddress ( void_t p_addr, uint32_t p_type );
 * @brief Cette fonction active une ou plusieurs adresses dédiées aux communication SMBus. Suite à l'activation, le matériel
 *        acquitte (ACK) les messages contenant l'adresse correspondante.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_type Ce paramètre contient le type d'adresse à activer. Une combinaison des constantes suivantes peut être être
 *                   utilisée : \n \ref K_I2C_SMBUS_DEFAULT_ADDRESS, \ref K_I2C_SMBUS_HOST_ADDRESS et \ref K_I2C_BROADCAST_ADDRESS.
 *
 * @return Sans objet.
 * @note Les constantes \ref K_I2C_SMBUS_DEFAULT_ADDRESS et \ref K_I2C_SMBUS_HOST_ADDRESS sont dédiées au communication de type SMBUS.
 *
 */

void i2c_enableAddress ( void_t p_addr, uint32_t p_type );

/**
 * @fn void i2c_disableAddress ( void_t p_addr, uint32_t p_type );
 * @brief Cette fonction désactive une ou plusieurs adresses dédiées aux communication SMBus. Suite à la désactivation, le matériel
 *        acquitte négativement (NACK) les messages contenant l'adresse correspondante.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_type Ce paramètre contient le type d'adresse à désactiver. Une combinaison des constantes suivantes peut être être
 *                   utilisée : \n \ref K_I2C_SMBUS_DEFAULT_ADDRESS, \ref K_I2C_SMBUS_HOST_ADDRESS et \ref K_I2C_BROADCAST_ADDRESS.
 *
 * @return Sans objet.
 * @note Les constantes \ref K_I2C_SMBUS_DEFAULT_ADDRESS et \ref K_I2C_SMBUS_HOST_ADDRESS sont dédiées au communication de type SMBUS.
 *
 */

void i2c_disableAddress ( void_t p_addr, uint32_t p_type );

/**
 * @fn void i2c_enableStretching ( void_t p_addr );
 * @brief Cette fonction autorise la diminution de la vitesse l'horloge I2C en utilisant la technique de stretching qui consiste à
 *        augmenter la durée de l'état bas du signal d'horloge.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'. Elle ne peut être exécutée que lorsque le périphérique I2C est désactivé.
 *
 */

void i2c_enableStretching ( void_t p_addr );

/**
 * @fn void i2c_disableStretching ( void_t p_addr );
 * @brief Cette fonction interdit la diminution de la vitesse l'horloge I2C en utilisant la technique de stretching qui consiste à
 *        augmenter la durée de l'état bas du signal d'horloge.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'. Elle peut être exécutée que lorsque le périphérique I2C est désactivé.
 *
 */

void i2c_disableStretching ( void_t p_addr );

/**
 * @fn void i2c_enableByteCounter ( void_t p_addr );
 * @brief Cette fonction active le compteur d'octets pour le mode 'Slave'. Cette fonction doit être combinée avec les fonctions
 *        \ref i2c_enableReload et \ref i2c_setTransferLength afin de pouvoir acquitter ou non chaque octet entrant.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'.
 * @warning Le compteur d'octets ne doit pas être activé lorsque la fonction i2c_disableStretching a été exécutée.
 *          (cf. datasheet Rev6 page 931).
 *
 */

void i2c_enableByteCounter ( void_t p_addr );

/**
 * @fn void i2c_disableByteCounter ( void_t p_addr );
 * @brief Cette fonction désactive le compteur d'octets pour le mode 'Slave'. La configuration de la taille du transfert à l'aide
 *        de la fonction \ref i2c_setTransferLength n'est alors plus autorisée. De même, la fonction \ref i2c_pec ne peut plus
 *        être utilisée.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'.
 *
 */

void i2c_disableByteCounter ( void_t p_addr );

/**
 * @fn void i2c_enableDMA ( void_t p_addr, uint32_t p_mode );
 * @brief Cette fonction active le transmetteur et/ou le récepteur DMA.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_mode Ce paramètre contient l'identifiant de la DMA à activer. Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_I2C_DMA_TRANSMITTER et \ref K_I2C_DMA_RECEIVER
 *
 * @return Sans objet.
 *
 */

void i2c_enableDMA ( void_t p_addr, uint32_t p_mode );

/**
 * @fn void i2c_disableDMA ( void_t p_addr, uint32_t p_mode );
 * @brief Cette fonction désactive le transmetteur et/ou le récepteur DMA.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_mode Ce paramètre contient l'identifiant de la DMA à désactiver. Une combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_I2C_DMA_TRANSMITTER et \ref K_I2C_DMA_RECEIVER
 *
 * @return Sans objet.
 *
 */

void i2c_disableDMA ( void_t p_addr, uint32_t p_mode );

/**
 * @fn void i2c_enableAnalogNoiseFilter ( void_t p_addr );
 * @brief Cette fonction active le filtre analogique présent sur les broches SDA et SCL du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Les filtres sont positionné en cascade. Ils peuvent être activé simultanémenent.
 *
 */

void i2c_enableAnalogNoiseFilter ( void_t p_addr );

/**
 * @fn void i2c_disableAnalogNoiseFilter ( void_t p_addr );
 * @brief Cette fonction désactive le filtre analogique présent sur les broches SDA et SCL du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Les filtres sont positionné en cascade. Ils peuvent être activé simultanémenent.
 *
 */

void i2c_disableAnalogNoiseFilter ( void_t p_addr );

/**
 * @fn void i2c_enableDigitalNoiseFilter ( void_t p_addr, uint32_t p_bandwidth );
 * @brief Cette fonction active le filtre numérique présent sur les broches SDA et SCL du périphérique I2C.
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                        \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_bandwidth Ce paramètre contient la période de coupure du filtre numérique. Elle est exprimée en multiple de la fréquence du
 *                        périphérique I2C. Elle évolue entre [1 et 15].
 *
 * @return Sans objet.
 * @note Les filtres sont positionné en cascade. Ils peuvent être activé simultanémenent.
 *
 */

void i2c_enableDigitalNoiseFilter ( void_t p_addr, uint32_t p_bandwidth );

/**
 * @fn void i2c_disableDigitalNoiseFilter ( void_t p_addr );
 * @brief Cette fonction désactive le filtre numérique présent sur les broches SDA et SCL du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 *
 */

void i2c_disableDigitalNoiseFilter ( void_t p_addr );

/**
 * @fn void i2c_enableInterrupt ( void_t p_addr, uint32_t p_mask );
 * @brief Cette fonction active une ou plusieurs interruptions du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_mask Ce paramètre contient l'identifiant des interruptions à activer. Une combinaison des constantes suivantes peut
 *                   être utilisée : \n
 *                   \ref K_I2C_ERROR_INTERRUPTS, \ref K_I2C_TRANSFER_COMPLETE_INTERRUPT, \ref K_I2C_STOP_DETECTION_INTERRUPT,
 *                   \ref K_I2C_NACK_INTERRUPT, \ref K_I2C_ADDRESS_MATCHED_INTERRUPT, \ref K_I2C_RX_INTERRUPT et
 *                   \ref K_I2C_TX_INTERRUPT.
 *
 * @return Sans objet.
 *
 */

void i2c_enableInterrupt ( void_t p_addr, uint32_t p_mask );

/**
 * @fn void i2c_disableInterrupt ( void_t p_addr, uint32_t p_mask );
 * @brief Cette fonction désactive une ou plusieurs interruptions du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_mask Ce paramètre contient l'identifiant des interruptions à désactiver. Une combinaison des constantes suivantes peut
 *                   être utilisée : \n
 *                   \ref K_I2C_ERROR_INTERRUPTS, \ref K_I2C_TRANSFER_COMPLETE_INTERRUPT, \ref K_I2C_STOP_DETECTION_INTERRUPT,
 *                   \ref K_I2C_NACK_INTERRUPT, \ref K_I2C_ADDRESS_MATCHED_INTERRUPT, \ref K_I2C_RX_INTERRUPT et
 *                   \ref K_I2C_TX_INTERRUPT.
 *
 * @return Sans objet.
 *
 */

void i2c_disableInterrupt ( void_t p_addr, uint32_t p_mask );

/**
 * @fn void i2c_enable ( void_t p_addr );
 * @brief Cette fonction active le périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 *
 */

void i2c_enable ( void_t p_addr );

/**
 * @fn void i2c_disable ( void_t p_addr );
 * @brief Cette fonction désactive le périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 *
 */

void i2c_disable ( void_t p_addr );

/**
 * @fn void i2c_enableEndMode ( void_t p_addr );
 * @brief Cette fonction configure le périphérique I2C pour qu'il pilote automatiquement le bit de stop après le transfert
 *        des 'n' octets configuré par la fonction \ref i2c_setTransferLength.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'. Elle n'a aucun effet si le périphérique a été configuré par la fonction
 *       \ref i2c_enableReload.
 *
 */

void i2c_enableEndMode ( void_t p_addr );

/**
 * @fn void i2c_disableEndMode ( void_t p_addr );
 * @brief Cette fonction désactive le pilotage automatique du bit de stop. Il est réalisé manuellement à l'aide de la fonction
 *        \ref i2c_stop.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_disableEndMode ( void_t p_addr );

/**
 * @fn void i2c_enableReload ( void_t p_addr );
 * @brief Cette fonction configure le périphérique I2C pour qu'il recharge automatiquement le compteur d'octets avec la valeur
 *        configuré avec la fonction \ref i2c_setTransferLength.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 *
 */

void i2c_enableReload ( void_t p_addr );

/**
 * @fn void i2c_disableReload ( void_t p_addr );
 * @brief Cette fonction désactive le rechargement automatique du compteur d'octets après la fin d'un transfert.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 *
 */

void i2c_disableReload ( void_t p_addr );

/**
 * @fn void i2c_setTransferLength ( void_t p_addr, uint32_t p_count );
 * @brief Cette fonction configure le nombre d'octets à transmettre ou recevoir sur le bus.
 *
 * @param[in] p_addr  Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                    \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_count Ce paramètre contient le nombre de données dans le transfert. Il évolue sur 8 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est sans effet lorsque, en mode 'Slave', le compteur d'octets est désactivé (\ref i2c_disableByteCounter).
 *
 */

void i2c_setTransferLength ( void_t p_addr, uint32_t p_count );

/**
 * @fn void i2c_start ( void_t p_addr );
 * @brief Cette fonction transmet un bit de 'Start' sur le bus. Un bit de 'Restart' est envoyé lorsque la transmission d'un bit de stop
 *        n'est pas automatique (\ref i2c_disableEndMode) et lorsque la réémission automatique est désactivée (\ref i2c_disableReload).
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est sans effet lorsque la fonction \ref i2c_enableReload a été exécutée. Le bit de start est transmis que lorsque
 *       le bus est libre.
 *
 */

void i2c_start ( void_t p_addr );

/**
 * @fn void i2c_stop ( void_t p_addr );
 * @brief Cette fonction transmet un bit de 'Stop' sur le bus.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est sans effet lorsque la fonction \ref i2c_enableReload a été exécutée.
 *
 */

void i2c_stop ( void_t p_addr );

/**
 * @fn void i2c_nack ( void_t p_addr );
 * @brief Cette fonction configure un acquittement négatif (NACK).
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'.
 *
 */

void i2c_nack ( void_t p_addr ); /* Bit 15 */

/**
 * @fn void i2c_setReadWrite ( void_t p_addr, uint32_t p_state );
 * @brief Cette fonction configure le bit RW# en lecture ou écriture.
 *
 * @param[in] p_addr  Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                    \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_state Ce paramètre contient l'état du bit RW#. Une des constantes suivantes peut être utilisée : \n
 *                    \ref K_I2C_READ et \ref K_I2C_WRITE
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_setReadWrite ( void_t p_addr, uint32_t p_state );

/**
 * @fn void i2c_pec ( void_t p_addr );
 * @brief Cette fonction transmet l'octet de vérification de la cohérence des données (PEC) sur le bus.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS. Elle n'a aucun effet si le rechargement automatique est activé.
 *       (\ref i2c_enableReload). De même, la fonction \ref i2c_enableByteCounter doit être appelée avant l'exécution de cette
 *       fonction.
 *
 */

void i2c_pec ( void_t p_addr );

/**
 * @fn void i2c_enableShortHeader ( void_t p_addr );
 * @brief Cette fonction configure le périphérique I2C pour qu'il réalise une séquence de lecture raccourcie. Le préambule est la suivant : \n
 *        START + 1 OCTET ( 7 BITS D'ADRESSE + READ_DIR) + ...
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_enableShortHeader ( void_t p_addr );

/**
 * @fn void i2c_disableShortHeader ( void_t p_addr );
 * @brief Cette fonction configure le périphérique I2C pour qu'il réalise une séquence de lecture complète. Le préambule est la suivant : \n
 *        START + 2 OCTETS (10 BITS D'ADDRESSE + WRITE_DIR) + RESTART + 1 OCTET ( 7 BITS D'ADRESSE + READ_DIR) + ...
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_disableShortHeader ( void_t p_addr );

/**
 * @fn void i2c_enable10BitsAddressingMode ( void_t p_addr );
 * @brief Cette fonction active l'adressage 10 bits.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_enable10BitsAddressingMode ( void_t p_addr );

/**
 * @fn void i2c_enable7BitsAddressingMode ( void_t p_addr );
 * @brief Cette fonction active l'adressage 7 bits.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_enable7BitsAddressingMode ( void_t p_addr );

/**
 * @fn void i2c_setAddress ( void_t p_addr, uint32_t p_addressType, uint32_t p_destinationAddress );
 * @brief Cette fonction configure la valeur de l'adresse de l'esclave.
 *
 * @param[in] p_addr               Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                                 \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_addressType        Ce paramètre contient le type de l'adresse à configurer. Une des constantes suivante peut être utlisée: \n
 *                                 \ref K_I2C_7BITS_MODE, \ref K_I2C_10BITS_MODE
 * @param[in] p_destinationAddress Ce paramètre contient la valeur de l'adresse (7 bits ou 10 bits).
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Master'.
 *
 */

void i2c_setAddress ( void_t p_addr, uint32_t p_addressType, uint32_t p_destinationAddress );

/**
 * @fn void i2c_enableSlaveAddress ( void_t p_addr, uint32_t p_addressNumber );
 * @brief Cette fonction active une des deux adresses du périphérique I2C esclave (adresse propre).
 *
 * @param[in] p_addr          Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                            \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_addressNumber Ce paramètre contient l'identifiant de l'adresse à activer. Un des constantes suivantes peut être utilisée: \n
 *                            \ref K_I2C_SLAVE_ADDR1 ou \ref K_I2C_SLAVE_ADDR2
 *
 * @return Sans objet.
 *
 */

void i2c_enableSlaveAddress ( void_t p_addr, uint32_t p_addressNumber );

/**
 * @fn void i2c_disableSlaveAddress ( void_t p_addr, uint32_t p_addressNumber );
 * @brief Cette fonction désactive une des deux adresses du périphérique I2C (adresse propre).
 *
 * @param[in] p_addr          Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                            \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_addressNumber Ce paramètre contient l'identifiant de l'adresse à désactiver. Un des constantes suivantes peut être utilisée: \n
 *                            \ref K_I2C_SLAVE_ADDR1 ou \ref K_I2C_SLAVE_ADDR2
 *
 * @return Sans objet.
 *
 */

void i2c_disableSlaveAddress ( void_t p_addr, uint32_t p_addressNumber );

/**
 * @fn void i2c_enable10BitsSlaveAddressingMode ( void_t p_addr );
 * @brief Cette fonction active l'adressage 10 bits du péripéhrique I2C esclave (adresse propre).
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave' et ne s'applique que sur l'adresse I2C numéro 1.
 *
 */

void i2c_enable10BitsSlaveAddressingMode ( void_t p_addr );

/**
 * @fn void i2c_enable7BitsSlaveAddressingMode ( void_t p_addr );
 * @brief Cette fonction active l'adressage 7 bits du périphérique I2C esclave  (adresse propre).
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave' et ne s'applique que sur l'adresse I2C numéro 1.
 *
 */

void i2c_enable7BitsSlaveAddressingMode ( void_t p_addr );

/**
 * @fn void i2c_setSlaveAddress ( void_t p_addr, uint32_t p_addressMode, uint32_t p_slaveAddress );
 * @brief Cette fonction configure la valeur de l'adresse du périphérique I2C esclave (adresse propre).
 *
 * @param[in] p_addr        Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                          \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_register    Ce paramètre contient l'identifiant de l'adresse à activer. Un des constantes suivantes peut être utilisée: \n
 *                          \ref K_I2C_SLAVE_ADDR1 ou \ref K_I2C_SLAVE_ADDR2
 * @param[in] p_addressType Ce paramètre contient le type de l'adresse à configurer. Une des constantes suivante peut être utlisée: \n
 *                          \ref K_I2C_7BITS_MODE, \ref K_I2C_10BITS_MODE
 * @param[in] p_ownAddress  Ce paramètre contient la valeur de l'adresse 7 bits ou 10 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'. L'adresse I2C numéro 2 ne peut être que du type 7 bits.
 *
 */

void i2c_setSlaveAddress ( void_t p_addr, uint32_t p_register, uint32_t p_addressType, uint32_t p_ownAddress );

/**
 * @fn void i2c_setSlaveMask ( void_t p_addr, uint32_t p_mask );
 * @brief Cette fonction configure le masque de comparaison de l'adresse I2C numéro 2.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_mask Ce paramètre contient la valeur du masque de comparaison. Une des constantes suivante peut être utlisée: \n
 *                   \ref K_I2C_NO_MASK, \ref K_I2C_MASK_BITS_7TO2_COMPARED, \ref K_I2C_MASK_BITS_7TO3_COMPARED,
 *                   \ref K_I2C_MASK_BITS_7TO4_COMPARED, \ref K_I2C_MASK_BITS_7TO5_COMPARED, \ref K_I2C_MASK_BITS_7TO6_COMPARED et
 *                   \ref K_I2C_MASK_BIT_7_COMPARED et \ref K_I2C_MASK_NO_BIT_COMPARED
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode 'Slave'. L'application du masque est uniquement sur l'adresse I2C numéro 2.
 *
 */

void i2c_setSlaveMask ( void_t p_addr, uint32_t p_mask );

/**
 * @fn void i2c_setPrescaler ( void_t p_addr, uint32_t p_prescaler );
 * @brief Cette fonction configure le pré-diviseur principal selon la formule suivante : \n
 *        T_PRESCALER = ( p_prescaler + 1 ) * T_I2CCLK
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                        \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_prescaler Ce paramètre contient la valeur du pré-diviseur principal sur 4 bits [0 à 15].
 *
 * @return Sans objet.
 *
 */

void i2c_setPrescaler ( void_t p_addr, uint32_t p_prescaler );

/**
 * @fn void i2c_setClock ( void_t p_addr, uint32_t p_lowPrescaler, uint32_t p_highPrescaler );
 * @brief Cette fonction configure les pré-diviseurs permettant de définir la durée des états haut et bas de la broche I2C_SCL. Les formules
 *        de configuration sont les suivantes : \n
 *        T_SCLH = ( p_highPrescaler + 1 ) * T_PRESCALER \n
 *        T_SCLL = ( p_lowPrescaler + 1  ) * T_PRESCALER
 *
 * @param[in] p_addr          Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                            \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_lowPrescaler  Ce paramètre contient la valeur du pré-diviseur de l'horloge basse sur 8 bits [0 à 255].
 * @param[in] p_highPrescaler Ce paramètre contient la valeur du pré-diviseur de l'horloge haute sur 8 bits [0 à 255].
 *
 * @return Sans objet.
 *
 */

void i2c_setClock ( void_t p_addr, uint32_t p_lowPrescaler, uint32_t p_highPrescaler );

/**
 * @fn void i2c_setDataSetupTime ( void_t p_addr, uint32_t p_prescaler );
 * @brief Cette fonction configure le pré-diviseur permettant de définir la durée de préparation de la donnée (c'est à dire la durée
 *        entre le premier front de la broche SDA et le front montant de la broche SCL ).
 *        La formule de configuration est la suivante :\n
 *        T_SCLD = ( p_prescaler + 1 ) * T_PRESCALER
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                        \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_prescaler Ce paramètre contient la valeur du pré-diviseur sur 4 bits [0 à 15].
 *
 * @return Sans objet.
 * @note La broche de donnée SDA est configurée avant que le premier front (montant) ne survienne sur la broche d'horloge.
 *
 */

void i2c_setDataSetupTime ( void_t p_addr, uint32_t p_prescaler );

/**
 * @fn void i2c_setDataHoldTime ( void_t p_addr, uint32_t p_prescaler );
 * @brief Cette fonction configure le pré-diviseur permettant de définir la durée de maintien de la donnée (c'est à dire la durée
 *        entre le front descendant de la broche SCL et le prochain front de de la broche SDA).
 *        front sur la broche SDA.
 *        La formule de configuration est la suivante :\n
 *        T_SDAD = ( p_prescaler + 1 ) * T_PRESCALER
 *
 * @param[in] p_addr      Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                        \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_prescaler Ce paramètre contient la valeur du pré-diviseur sur 4 bits [0 à 15].
 *
 * @return Sans objet.
 *
 */

void i2c_setDataHoldTime ( void_t p_addr, uint32_t p_prescaler );

/**
 * @fn void i2c_enableExtendedClockTimeout ( void_t p_addr, uint32_t p_timeout );
 * @brief Cette fonction active la détection de timeout sur la broche SCL. Lorsque la broche SCL reste à l'état bas pendant une durée
 *        supérieure au seuil fixé alors une erreur de timeout est générée. La valeur du seuil de déclenchement est configurée de la
 *        manière suivante : \n
 *        T_LOWSCL = ( p_timeout + 1 ) * 2048 * T_I2CLK
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                      \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_timeout Ce paramètre contient la valeur du seuil de déclenchement sur 12 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 * @warning La fonction i2c_disableExtendedClockTimeout() doit être exécutée avant l'appel de cette fonction si la valeur du timeout
 *          doit être modifié.
 *
 */

void i2c_enableExtendedClockTimeout ( void_t p_addr, uint32_t p_timeout );

/**
 * @fn void i2c_enableExtendedClockTimeout ( void_t p_addr, uint32_t p_timeout );
 * @brief Cette fonction désactive la détection de timeout sur la broche SCL.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_disableExtendedClockTimeout ( void_t p_addr );

/**
 * @fn void i2c_enableTimeout ( void_t p_addr, uint32_t p_state, uint32_t p_timeout );
 * @brief Cette fonction active la détection de timeout. Lorsque la broche SCL reste à l'état bas ou lorsque les broches
 *        SCL et SDA restent à l'état haut pendant une durée supérieure au seuil fixé alors une erreur de timeout est générée.
 *        La valeur du seuil de déclenchement est configurée de la manière suivante : \n
 *        T_LOWSCL = ( p_timeout + 1 ) * 2048 * T_I2CLK lorsque p_state = \ref K_I2C_SCL_LOW_TIMEOUT \n
 *        T_IDLE   = ( p_timeout + 1 ) * 4 * T_I2CLK lorsque p_state = \ref K_I2C_IDLE_TIMEOUT (SCL = HIGH ET SDA = HIGH)
 *
 * @param[in] p_addr    Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                      \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_state   Ce paramètre contient le type de timeout à configurer. Une des constantes suivantes peut être utilisée :\n
 *                      \ref K_I2C_SCL_LOW_TIMEOUT et \ref K_I2C_IDLE_TIMEOUT
 * @param[in] p_timeout Ce paramètre contient la valeur du seuil de déclenchement sur 12 bits.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_enableTimeout ( void_t p_addr, uint32_t p_state, uint32_t p_timeout );

/**
 * @fn void i2c_disableTimeout ( void_t p_addr );
 * @brief Cette fonction désactive la détection de timeout.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux communications de type SMBUS.
 *
 */

void i2c_disableTimeout ( void_t p_addr );

/**
 * @fn uint32_t i2c_getAddress ( void_t p_addr );
 * @brief Cette fonction retourne la valeur de l'adresse 7 bits reçue.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Cette fonction retourne la valeur de l'adresse sur 7 bits.
 *
 */

uint32_t i2c_getAddress ( void_t p_addr );

/**
 * @fn uint32_t i2c_getStatus ( void_t p_addr, uint32_t p_flags );
 * @brief Cette fonction retourne la valeur d'un ou plusieurs statuts du périphérique I2C.
 *
 * @param[in] p_addr  Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                    \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_flags Ce paramètre contient l'identifiant d'un ou plusieurs statuts du périphérique I2C. Une combinaison des constantes
 *                    suivantes peut être utilisée.
 *                    \ref K_I2C_TRANSFER_DIRECTION_STATUS, \ref K_I2C_BUSY_STATUS, \ref K_I2C_SMBUS_ALERT_INTERRUPT,
 *                    \ref K_I2C_TIMEOUT_INTERRUPT, \ref K_I2C_PEC_ERROR_INTERRUPT, \ref K_I2C_OVERRUN_UNDERRUN_INTERRUPT,
 *                    \ref K_I2C_ARBITRATION_LOST_INTERRUPT, \ref K_I2C_BUS_ERROR_INTERRUPT, \ref K_I2C_TRANSFER_COMPLETE_RELOAD_STATUS,
 *                    \ref K_I2C_TRANSFER_COMPLETE_STATUS, \ref K_I2C_STOP_DETECTION_INTERRUPT, \ref K_I2C_NACK_ERROR_INTERRUPT,
 *                    \ref K_I2C_ADDRESS_MATCHED_INTERRUPT, \ref K_I2C_RX_BUFFER_NOT_EMPTY_INTERRUPT,
 *                    \ref K_I2C_TX_BUFFER_EMPTY_INTERRUPT et \ref K_I2C_TX_BUFFER_EMPTY_STATUS
 *
 * @return Cette fonction retourne la valeur d'un ou plusieurs statuts du périphérique I2C.
 *
 */

uint32_t i2c_getStatus ( void_t p_addr, uint32_t p_flags );

/**
 * @fn uint32_t i2c_clearStatus ( void_t p_addr, uint32_t p_flags );
 * @brief Cette fonction réinitialise la valeur d'un ou plusieurs statuts d'interruption du périphérique I2C.
 *
 * @param[in] p_addr  Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                    \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_flags Ce paramètre contient l'identifiant d'un ou plusieurs statuts du périphérique I2C. Une combinaison des constantes
 *                    suivantes peut être utilisée.
 *                    \ref K_I2C_SMBUS_ALERT_INTERRUPT, \ref K_I2C_TIMEOUT_INTERRUPT, \ref K_I2C_PEC_ERROR_INTERRUPT,
 *                    \ref K_I2C_OVERRUN_UNDERRUN_INTERRUPT, \ref K_I2C_ARBITRATION_LOST_INTERRUPT, \ref K_I2C_BUS_ERROR_INTERRUPT,
 *                    \ref K_I2C_STOP_DETECTION_INTERRUPT, \ref K_I2C_NACK_ERROR_INTERRUPT, \ref K_I2C_ADDRESS_MATCHED_INTERRUPT et
 *                    \ref K_I2C_TX_BUFFER_EMPTY_INTERRUPT
 *
 * @return Sans objet.
 *
 */

void i2c_clearStatus ( void_t p_addr, uint32_t p_flags );

/**
 * @fn uint32_t i2c_getPacketErrorChecking ( void_t p_addr );
 * @brief Cette fonction retourne la valeur de l'octet vérifiant la cohérence des données (PEC).
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Cette fonction retourne la valeur de l'octet vérifiant la cohérence de données (PEC).
 *
 */

uint32_t i2c_getPacketErrorChecking ( void_t p_addr );

/**
 * @fn uint8_t i2c_get ( void_t p_addr );
 * @brief Cette fonction lit le registre de données du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 *
 * @return Cette fonction retourne la valeur du registre de données I2C.
 *
 */

uint8_t i2c_get ( void_t p_addr );

/**
 * @fn uint8_t i2c_set ( void_t p_addr );
 * @brief Cette fonction écrit le registre de données du périphérique I2C.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de base d'un périphérique I2C. Les constantes suivantes peuvent être utilisée: \n
 *                   \ref K_I2C1, \ref K_I2C2, \ref K_I2C3 et \ref K_I2C4
 * @param[in] p_data Ce parmaètre contient l'octet à écrire sur le bus I2C.
 *
 * @return Sans objet.
 *
 */

void i2c_set ( void_t p_addr, uint8_t p_data );

/**
 *
 */

#endif

