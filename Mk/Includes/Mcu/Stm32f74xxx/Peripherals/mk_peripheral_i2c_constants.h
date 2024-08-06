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
* @file mk_peripheral_i2c_constants.h
* @brief Déclaration des constantes dédiées au périphérique I2C.
* @date 15 juil. 2020
*
*/

#ifndef MK_PERIPHERAL_I2C_CONSTANTS_H
#define MK_PERIPHERAL_I2C_CONSTANTS_H

/**
 * @def K_I2C1
 * @brief Adresse de base du périphérique I2C1.
 */

#define K_I2C1 ( addr_t ) 0x40005400

/**
 * @def K_I2C2
 * @brief Adresse de base du périphérique I2C2.
 */

#define K_I2C2 ( addr_t ) 0x40005800

/**
 * @def K_I2C3
 * @brief Adresse de base du périphérique I2C3.
 */

#define K_I2C3 ( addr_t ) 0x40005C00

/**
 * @def K_I2C4
 * @brief Adresse de base du périphérique I2C4.
 */

#define K_I2C4 ( addr_t ) 0x40006000

/**
 *
 */

/**
 * @def K_I2C_SMBUS_DEFAULT_ADDRESS
 * @brief Constante dédiée aux fonctions i2c_enableAddress() et i2c_disableAddress(). \n
 *        Activation ou désactivation de l'adresse de défaut (0b1100001x).
 * @note  Cette constante est dédiée au communication SMBUS.
 *
 */

#define K_I2C_SMBUS_DEFAULT_ADDRESS 0x00200000

/**
 * @def K_I2C_SMBUS_HOST_ADDRESS
 * @brief Constante dédiée aux fonctions i2c_enableAddress() et i2c_disableAddress(). \n
 *        Activation ou désactivation de l'adresse du maitre (0xb0001000x).
 * @note  Cette constante est dédiée au communication SMBUS.
 *
 */

#define K_I2C_SMBUS_HOST_ADDRESS 0x00100000

/**
 * @def K_I2C_BROADCAST_ADDRESS
 * @brief Constante dédiée aux fonctions i2c_enableAddress() et i2c_disableAddress(). \n
 *        Activation ou désactivation de l'adresse de broadcast (0xb00000000).
 *
 */

#define K_I2C_BROADCAST_ADDRESS 0x00080000

/**
 *
 */

/**
 * @def K_I2C_DMA_TRANSMITTER
 * @brief Constante dédiée aux fonctions i2c_enableDMA() et i2c_disableDMA(). \n
 *        Activation ou désactivation du transmetteur DMA.
 *
 */

#define K_I2C_DMA_TRANSMITTER 0x00004000

/**
 * @def K_I2C_DMA_RECEIVER
 * @brief Constante dédiée aux fonctions i2c_enableDMA() et i2c_disableDMA(). \n
 *        Activation ou désactivation du récepteur DMA.
 *
 */

#define K_I2C_DMA_RECEIVER 0x00008000

/**
 *
 */

/**
 * @def K_I2C_ERROR_INTERRUPTS
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation des interruptions d'erreurs (Arbitration Lost,
 *        Bus Error Detection, Overrun/Underrun, Timeout Detection, PEC Error Detection et
 *        Alert Pin Event Detection)
 *
 */

#define K_I2C_ERROR_INTERRUPTS 0x00000080

/**
 * @def K_I2C_TRANSFER_COMPLETE_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation des interruptions de fin de transfert (Transfer Complete,
 *        Transfer Complete Reload).
 *
 */

#define K_I2C_TRANSFER_COMPLETE_INTERRUPT 0x00000040

/**
 * @def K_I2C_STOP_DETECTION_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation de l'interruption indiquant la détection d'un bit de
 *        STOP.
 *
 */

#define K_I2C_STOP_DETECTION_INTERRUPT 0x00000020

/**
 * @def K_I2C_NACK_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation de l'interruption indiquant la détection d'un
 *        NACK.
 *
 */

#define K_I2C_NACK_INTERRUPT 0x00000010

/**
 * @def K_I2C_ADDRESS_MATCHED_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation de l'interruption indiquant la réception d'une
 *        addresse valide.
 *
 */

#define K_I2C_ADDRESS_MATCHED_INTERRUPT 0x00000008

/**
 * @def K_I2C_RX_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation de l'interruption indiquant la présence d'un octet
 *        dans le buffer de réception.
 *
 */

#define K_I2C_RX_INTERRUPT 0x00000004

/**
 * @def K_I2C_TX_INTERRUPT
 * @brief Constante dédiée aux fonctions i2c_enableInterrupt() et i2c_disableInterrupt(). \n
 *        Activation ou désactivation de l'interruption indiquant la présence d'un octet
 *        dans le buffer de transmission.
 *
 */

#define K_I2C_TX_INTERRUPT 0x00000002

/**
 *
 */

/**
 * @def K_I2C_READ
 * @brief Constante dédiée à la fonction i2c_setReadWrite(). \n
 *        Configuration d'un transfert en lecture.
 *
 */

#define K_I2C_READ 0x00000400

/**
 * @def K_I2C_WRITE
 * @brief Constante dédiée à la fonction i2c_setReadWrite(). \n
 *        Configuration d'un transfert en écriture.
 *
 */

#define K_I2C_WRITE 0x00000000

/**
 *
 */

/**
 * @def K_I2C_7BITS_MODE
 * @brief Constante dédiée aux fonctions i2c_setAddress() et i2c_setSlaveAddress(). \n
 *        Configuration de l'adresse en mode 7 bits.
 *
 */

#define K_I2C_7BITS_MODE 0x00000001

/**
 * @def K_I2C_10BITS_MODE
 * @brief Constante dédiée aux fonctions i2c_setAddress() et i2c_setSlaveAddress(). \n
 *        Configuration de l'adresse en mode 10 bits.
 *
 */

#define K_I2C_10BITS_MODE 0x00000000

/**
 *
 */

/**
 * @def K_I2C_SLAVE_ADDR1
 * @brief Constante dédiée aux fonctions i2c_enableSlaveAddress() et i2c_disableSlaveAddress(). \n
 *        Activation ou désactivation de l'adresse esclave numéro 1.
 *
 */

#define K_I2C_SLAVE_ADDR1 0x00000000

/**
 * @def K_I2C_SLAVE_ADDR2
 * @brief Constante dédiée aux fonctions i2c_enableSlaveAddress() et i2c_disableSlaveAddress(). \n
 *        Activation ou désactivation de l'adresse esclave numéro 2.
 *
 */

#define K_I2C_SLAVE_ADDR2 0x00000001

/**
 *
 */

/**
 * @def K_I2C_NO_MASK
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:1].
 *
 */

#define K_I2C_NO_MASK 0x00000000

/**
 * @def K_I2C_MASK_BITS_7TO2_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:2].
 *
 */

#define K_I2C_MASK_BITS_7TO2_COMPARED 0x00000100

/**
 * @def K_I2C_MASK_BITS_7TO3_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:3].
 *
 */

#define K_I2C_MASK_BITS_7TO3_COMPARED 0x00000200

/**
 * @def K_I2C_MASK_BITS_7TO4_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:4].
 *
 */

#define K_I2C_MASK_BITS_7TO4_COMPARED 0x00000300

/**
 * @def K_I2C_MASK_BITS_7TO5_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:5].
 *
 */

#define K_I2C_MASK_BITS_7TO5_COMPARED 0x00000400

/**
 * @def K_I2C_MASK_BITS_7TO6_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur les bits [7:6].
 *
 */

#define K_I2C_MASK_BITS_7TO6_COMPARED 0x00000500

/**
 * @def K_I2C_MASK_BITS_7TO6_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante configure la comparaison sur le bit 7 uniquement.
 *
 */

#define K_I2C_MASK_BIT_7_COMPARED 0x00000600

/**
 * @def K_I2C_MASK_NO_BIT_COMPARED
 * @brief Constante dédiée à la fonction i2c_setSlaveMask(). \n
 *        Configuration du masque de comparaison dédié à l'adresse esclave numéro 2.
 *        Cette constante désactive la comparaison d'adresse.
 *
 */

#define K_I2C_MASK_NO_BIT_COMPARED 0x00000700

/**
 *
 */

/**
 * @def K_I2C_SCL_LOW_TIMEOUT
 * @brief Constante dédiée à la fonction i2c_enableTimeout(). \n
 *        Configuration de la durée du timeout T_LOWSCL.
 *
 */

#define K_I2C_SCL_LOW_TIMEOUT 0x00000000

/**
 * @def K_I2C_IDLE_TIMEOUT
 * @brief Constante dédiée à la fonction i2c_enableTimeout(). \n
 *        Configuration de la durée du timeout T_IDLE.
 *
 */

#define K_I2C_IDLE_TIMEOUT 0x00001000

/**
 *
 */

/**
 * @def K_I2C_FLAG_ALL
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Adressage de l'intégralité des bits de statut du périphérique I2C.
 *
 */

#define K_I2C_FLAG_ALL 0x00FFBFFF

/**
 * @def K_I2C_TRANSFER_DIRECTION_STATUS
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant la direction
 *        du transfert.
 *
 */

#define K_I2C_TRANSFER_DIRECTION_STATUS 0x00010000

/**
 * @def K_I2C_BUSY_STATUS
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant qu'une communication
 *        est en cours.
 *
 */

#define K_I2C_BUSY_STATUS 0x00008000

/**
 * @def K_I2C_BUSY_STATUS
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant la fin d'un transfert
 *        lorsque le rechargement automatique est activé.
 *
 */

#define K_I2C_TRANSFER_COMPLETE_RELOAD_STATUS 0x00000080

/**
 * @def K_I2C_TRANSFER_COMPLETE_STATUS
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant la fin d'un transfert
 *        lorsque le rechargement automatique est désactivé.
 *
 */

#define K_I2C_TRANSFER_COMPLETE_STATUS 0x00000040

/**
 * @def K_I2C_TX_BUFFER_EMPTY_STATUS
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant que le registre de
 *        transmission est vide.
 *
 */

#define K_I2C_TX_BUFFER_EMPTY_STATUS 0x00000001

/**
 * @def K_I2C_RX_BUFFER_NOT_EMPTY_INTERRUPT
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant qu'une donnée est
 *        disponible dans le registre de réception.
 *
 */

#define K_I2C_RX_BUFFER_NOT_EMPTY_INTERRUPT 0x00000004

/**
 * @def K_I2C_TX_BUFFER_EMPTY_INTERRUPT
 * @brief Constante dédiée à la fonction i2c_getStatus(). \n
 *        Définition de la position du bit indiquant que le registre de
 *        transmission est vide.
 *
 */

#define K_I2C_TX_BUFFER_EMPTY_INTERRUPT 0x00000002

/**
 * @def K_I2C_SMBUS_ALERT_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'une
 *        alerte SMBus.
 *
 */

#define K_I2C_SMBUS_ALERT_INTERRUPT 0x00002000

/**
 * @def K_I2C_TIMEOUT_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'un
 *        timeout.
 *
 */

#define K_I2C_TIMEOUT_INTERRUPT 0x00001000

/**
 * @def K_I2C_PEC_ERROR_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'une
 *        d'erreur sur la cohérence des données (PEC).
 *
 */

#define K_I2C_PEC_ERROR_INTERRUPT 0x00000800

/**
 * @def K_I2C_OVERRUN_UNDERRUN_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'une
 *        d'erreur de communication de type 'Overrun' ou 'Underrun'.
 *
 */

#define K_I2C_OVERRUN_UNDERRUN_INTERRUPT 0x00000400

/**
 * @def K_I2C_ARBITRATION_LOST_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'une
 *        d'erreur d'arbitration (bus multi-maitre).
 *
 */

#define K_I2C_ARBITRATION_LOST_INTERRUPT 0x00000200

/**
 * @def K_I2C_BUS_ERROR_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la présence d'une
 *        d'erreur de communication (bit de start ou stop cadencé incorrectement).
 *
 */

#define K_I2C_BUS_ERROR_INTERRUPT 0x00000100

/**
 * @def K_I2C_STOP_DETECTION_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la détection d'un bit de
 *        STOP sur le bus.
 *
 */

#define K_I2C_STOP_DETECTION_INTERRUPT 0x00000020

/**
 * @def K_I2C_NACK_ERROR_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la détection d'un NACK après
 *        la transmission d'un octet sur le bus.
 *
 */

#define K_I2C_NACK_ERROR_INTERRUPT 0x00000010

/**
 * @def K_I2C_ADDRESS_MATCHED_INTERRUPT
 * @brief Constante dédiée au fonctions i2c_getStatus() et i2c_clearStatus(). \n
 *        Définition de la position du bit indiquant la réception d'une adresse
 *        valide.
 *
 */

#define K_I2C_ADDRESS_MATCHED_INTERRUPT 0x00000008


/**
 *
 */

/**
 *
 */

#endif

