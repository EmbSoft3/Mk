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
* @file mk_peripheral_mmc.h
* @brief Déclaration des fonctions dédiées au périphérique SDMMC.
* @date 31 mai 2020
*
*/

#ifndef MK_PERIPHERAL_MMC_H
#define MK_PERIPHERAL_MMC_H

/**
 * @fn void mmc_enable ( void );
 * @brief Cette fonction active le périphérique MMC. Suite à l'exécution de cette
 *        fonction l'horloge est transmise au périphérique.
 * @return Sans objet.
 *
 */

void mmc_enable ( void );

/**
 * @fn void mmc_disable ( void );
 * @brief Cette fonction désactive le périphérique MMC. Suite à l'exécution de cette
 *        fonction l'horloge n'est plus transmise au périphérique.
 * @return Sans objet.
 *
 */

void mmc_disable ( void );

/**
 * @fn void mmc_enableDma ( void );
 * @brief Cette fonction active le mode DMA.
 * @return Sans objet.
 *
 */

void mmc_enableDma ( void );

/**
 * @fn void mmc_disableDma ( void );
 * @brief Cette fonction désactive le mode DMA.
 * @return Sans objet.
 *
 */

void mmc_disableDma ( void );

/**
 * @fn void mmc_enablePowerSavingMode ( void );
 * @brief Cette fonction active le mode économie d'énergie. Dans ce mode l'horloge
 *        est active quand le bus est actif.
 * @return Sans objet.
 *
 */

void mmc_enablePowerSavingMode ( void );

/**
 * @fn void mmc_disablePowerSavingMode ( void );
 * @brief Cette fonction désactive le mode économie d'énergie. Dans ce mode l'horloge
 *        est continuellement active.
 * @return Sans objet.
 *
 */

void mmc_disablePowerSavingMode ( void );

/**
 * @fn void mmc_enableFlowControl ( void );
 * @brief Cette fonction active les broches de contrôle du périphérique MMC.
 * @return Sans objet.
 *
 */

void mmc_enableFlowControl ( void );

/**
 * @fn void mmc_disableFlowControl ( void );
 * @brief Cette fonction désactive les broches de contrôle du périphérique MMC.
 * @return Sans objet.
 *
 */

void mmc_disableFlowControl ( void );

/**
 * @fn void mmc_enableClockPin ( void );
 * @brief Cette fonction active la broche d'horloge.
 * @return Sans objet.
 *
 */

void mmc_enableClockPin ( void );

/**
 * @fn void mmc_disableClockPin ( void );
 * @brief Cette fonction désactive la broche d'horloge.
 * @return Sans objet.
 *
 */

void mmc_disableClockPin ( void );

/**
 * @fn void mmc_setDataBusSize ( uint32_t p_size );
 * @brief Cette fonction configure la taille du bus de données.
 * @param[in] p_size Ce paramètre contient la taille du bus de données. Une des
 *                   constantes suivantes peut être utilisée : \n
 *                   \ref K_MMC_DATABUS_SIZE_1PIN, \ref K_MMC_DATABUS_SIZE_4PINS ou \ref K_MMC_DATABUS_SIZE_8PINS
 * @return Sans objet.
 *
 */

void mmc_setDataBusSize ( uint32_t p_size );

/**
 * @fn void mmc_enableBypass ( void );
 * @brief Cette fonction désactive le pré-diviseur d'horloge intégré dans le
 *        périphérique MMC.
 * @return Sans objet.
 *
 */

void mmc_enableBypass ( void );

/**
 * @fn void mmc_disableBypass ( void );
 * @brief Cette fonction active le pré-diviseur d'horloge intégré dans le
 *        périphérique MMC. Le pré-diviseur est configuré avec la fonction
 *        \ref mmc_setPrescaler.
 * @return Sans objet.
 *
 */

void mmc_disableBypass ( void );

/**
 * @fn void mmc_setPrescaler ( uint32_t p_prescaler );
 * @brief Cette fonction configure le pré-diviseur interne du périphérique MMC. Le pré-diviseur
 *        doit préalablement être activé avec la fonction \ref mmc_disableBypass.
 *        La valeur de l'horloge en sortie du pré-diviseur est égale à : \n
 *        MMC_CLOCK_PIN [Hz] = MMC_INPUT_CLOCK / ( p_prescaler + 2 )
 * @param[in] p_prescaler Ce paramètre contient la valeur du prédiviseur. Il évolue de [0 à 255].
 * @return Sans objet.
 *
 */

void mmc_setPrescaler ( uint32_t p_prescaler );

/**
 * @fn void mmc_setSampleEdge ( uint32_t p_edge );
 * @brief Cette fonction configure le point d'échantillonnage où les données prennent un
 *        nouvelle état.
 * @param[in] p_edge Ce paramètre définie l'instant de transition des données. Une des
 *                   constantes suivantes peut être utilisée : \n
 *                   \ref K_MMC_CLOCK_RISING_EDGE ou \ref K_MMC_CLOCK_FALLING_EDGE
 * @return Sans objet.
 *
 */

void mmc_setSampleEdge ( uint32_t p_edge );

/**
 * @fn uint32_t mmc_enableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction active une ou plusieurs interruptions.
 *
 * @param[in] p_mask Ce paramètre contient l'identifiant d'une ou plusieurs interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_MMC_FLAG_SDIO_INTERRUPT, \ref K_MMC_FLAG_RXDATA_AVAILABLE, \ref K_MMC_FLAG_TXDATA_AVAILABLE,
 *                   \ref K_MMC_FLAG_RXFIFO_EMPTY, \ref K_MMC_FLAG_TXFIFO_EMPTY, \ref K_MMC_FLAG_RXFIFO_FULL,
 *                   \ref K_MMC_FLAG_TXFIFO_FULL, \ref K_MMC_FLAG_RXFIFO_HALF_FULL, \ref K_MMC_FLAG_TXFIFO_HALF_EMPTY,
 *                   \ref K_MMC_FLAG_RXDATA_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_TXDATA_TRANSFER_IN_PROGRESS,
 *                   \ref K_MMC_FLAG_CMD_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_DATA_BLOCK_TRANSFERED,
 *                   \ref K_MMC_FLAG_DATA_COUNTER_REACHED, \ref K_MMC_FLAG_CMD_TRANSMITTED, \ref K_MMC_FLAG_CMD_RESPONSE_RECEIVED,
 *                   \ref K_MMC_FLAG_RXFIFO_OVERRUN, \ref K_MMC_FLAG_TXFIFO_UNDERRUN,
 *                   \ref K_MMC_FLAG_DATA_TIMEOUT, \ref K_MMC_FLAG_CMD_RESPONSE_TIMEOUT, \ref K_MMC_FLAG_DATA_BLOCK_FAILED et
 *                   \ref K_MMC_FLAG_CMD_RESPONSE_FAILED et \ref K_MMC_FLAG_START_BIT_NOT_DETECTED.
 *
 * @return Sans objet.
 *
 */

void mmc_enableInterrupt ( uint32_t p_mask );

/**
 * @fn uint32_t mmc_disableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction désactive une ou plusieurs interruptions.
 *
 * @param[in] p_mask Ce paramètre contient l'identifiant d'une ou plusieurs interruptions. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_MMC_FLAG_SDIO_INTERRUPT, \ref K_MMC_FLAG_RXDATA_AVAILABLE, \ref K_MMC_FLAG_TXDATA_AVAILABLE,
 *                   \ref K_MMC_FLAG_RXFIFO_EMPTY, \ref K_MMC_FLAG_TXFIFO_EMPTY, \ref K_MMC_FLAG_RXFIFO_FULL,
 *                   \ref K_MMC_FLAG_TXFIFO_FULL, \ref K_MMC_FLAG_RXFIFO_HALF_FULL, \ref K_MMC_FLAG_TXFIFO_HALF_EMPTY,
 *                   \ref K_MMC_FLAG_RXDATA_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_TXDATA_TRANSFER_IN_PROGRESS,
 *                   \ref K_MMC_FLAG_CMD_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_DATA_BLOCK_TRANSFERED,
 *                   \ref K_MMC_FLAG_DATA_COUNTER_REACHED, \ref K_MMC_FLAG_CMD_TRANSMITTED, \ref K_MMC_FLAG_CMD_RESPONSE_RECEIVED,
 *                   \ref K_MMC_FLAG_RXFIFO_OVERRUN, \ref K_MMC_FLAG_TXFIFO_UNDERRUN,
 *                   \ref K_MMC_FLAG_DATA_TIMEOUT, \ref K_MMC_FLAG_CMD_RESPONSE_TIMEOUT, \ref K_MMC_FLAG_DATA_BLOCK_FAILED et
 *                   \ref K_MMC_FLAG_CMD_RESPONSE_FAILED et \ref K_MMC_FLAG_START_BIT_NOT_DETECTED.
 *
 * @return Sans objet.
 *
 */

void mmc_disableInterrupt ( uint32_t p_mask );

/**
 * @fn uint32_t mmc_getStatus ( uint32_t p_mask );
 * @brief Cette fonction retourne un ou plusieurs statuts du périphérique MMC.
 *
 * @param[in] p_mask Ce paramètre contient l'identifiant d'un ou plusieurs statuts du périphérique MMC. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_MMC_FLAG_SDIO_INTERRUPT, \ref K_MMC_FLAG_RXDATA_AVAILABLE, \ref K_MMC_FLAG_TXDATA_AVAILABLE,
 *                   \ref K_MMC_FLAG_RXFIFO_EMPTY, \ref K_MMC_FLAG_TXFIFO_EMPTY, \ref K_MMC_FLAG_RXFIFO_FULL,
 *                   \ref K_MMC_FLAG_TXFIFO_FULL, \ref K_MMC_FLAG_RXFIFO_HALF_FULL, \ref K_MMC_FLAG_TXFIFO_HALF_EMPTY,
 *                   \ref K_MMC_FLAG_RXDATA_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_TXDATA_TRANSFER_IN_PROGRESS,
 *                   \ref K_MMC_FLAG_CMD_TRANSFER_IN_PROGRESS, \ref K_MMC_FLAG_DATA_BLOCK_TRANSFERED,
 *                   \ref K_MMC_FLAG_DATA_COUNTER_REACHED, \ref K_MMC_FLAG_CMD_TRANSMITTED, \ref K_MMC_FLAG_CMD_RESPONSE_RECEIVED,
 *                   \ref K_MMC_FLAG_RXFIFO_OVERRUN, \ref K_MMC_FLAG_TXFIFO_UNDERRUN,
 *                   \ref K_MMC_FLAG_DATA_TIMEOUT, \ref K_MMC_FLAG_CMD_RESPONSE_TIMEOUT, \ref K_MMC_FLAG_DATA_BLOCK_FAILED et
 *                   \ref K_MMC_FLAG_CMD_RESPONSE_FAILED et \ref K_MMC_FLAG_START_BIT_NOT_DETECTED.
 *
 * @return Un ou plusieurs statuts du périphérique MMC.
 *
 */

uint32_t mmc_getStatus ( uint32_t p_mask );

/**
 * @fn void mmc_clearStatus ( uint32_t p_mask );
 * @brief Cette fonction réinitialise un ou plusieurs statuts du périphérique MMC.
 *
 * @param[in] p_mask Ce paramètre contient l'identifiant d'un ou plusieurs statuts du périphérique MMC. Une combinaison des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_MMC_FLAG_SDIO_INTERRUPT, \ref K_MMC_FLAG_DATA_BLOCK_TRANSFERED, \ref K_MMC_FLAG_DATA_COUNTER_REACHED,
 *                   \ref K_MMC_FLAG_CMD_TRANSMITTED, \ref K_MMC_FLAG_CMD_RESPONSE_RECEIVED,
 *                   \ref K_MMC_FLAG_RXFIFO_OVERRUN, \ref K_MMC_FLAG_TXFIFO_UNDERRUN,
 *                   \ref K_MMC_FLAG_DATA_TIMEOUT, \ref K_MMC_FLAG_CMD_RESPONSE_TIMEOUT, \ref K_MMC_FLAG_DATA_BLOCK_FAILED et
 *                   \ref K_MMC_FLAG_CMD_RESPONSE_FAILED et \ref K_MMC_FLAG_START_BIT_NOT_DETECTED.
 *
 * @return Sans objet.
 *
 */

void mmc_clearStatus ( uint32_t p_mask );

/**
 * @fn void mmc_enableSDIO ( uint32_t p_waitMode );
 * @brief Cette fonction active les fonctions spécifiques SDIO.
 * @param[in] p_waitMode Ce paramètre contient le type de la séquence 'ReadWait' à utiliser. Un des paramètres suivants peut être
 *                       utilisé : \n \ref K_MMC_READ_WAIT_D2 ou \ref K_MMC_READ_WAIT_CLK
 * @return Sans objet.
 *
 */

void mmc_enableSDIO ( uint32_t p_waitMode );

/**
 * @fn void mmc_disableSDIO ( void );
 * @brief Cette fonction désactive les fonctions spécifiques SDIO.
 * @return Sans objet.
 *
 */

void mmc_disableSDIO ( void );

/**
 * @fn void mmc_disableSDIO ( void );
 * @brief Cette fonction déclenche une séquence de type 'ReadWait'.
 * @return Sans objet.
 *
 */

void mmc_startReadWait ( void );

/**
 * @fn void mmc_stopReadWait ( void );
 * @brief Cette fonction stoppe une séquence de type 'ReadWait'.
 * @return Sans objet.
 *
 */

void mmc_stopReadWait ( void );

/**
 * @fn void mmc_enableStreamMode ( void );
 * @brief Cette fonction active le mode de transfert par 'Stream' ou 'MultiBytes' (SDIO).
 * @return Sans objet.
 *
 */

void mmc_enableStreamMode ( void );

/**
 * @fn void mmc_enableBlockMode ( void );
 * @brief Cette fonction active le mode de transfert par bloc de données.
 * @return Sans objet.
 *
 */

void mmc_enableBlockMode ( void );

/**
 * @fn void mmc_setBlockSize ( uint32_t p_blockSize );
 * @brief Cette fonction configure la taille d'un bloc de données.
 * @param[in] p_blockSize Ce paramètre contient la taille d'un bloc de données. Une des constantes suivantes peut
 *                        être utilisé :\n \ref K_MMC_BLOCK_SIZE_1BYTE, \ref K_MMC_BLOCK_SIZE_2BYTES,
 *                        \ref K_MMC_BLOCK_SIZE_4BYTES, ... , \ref K_MMC_BLOCK_SIZE_16KBYTES
 * @return Sans objet.
 *
 */

void mmc_setBlockSize ( uint32_t p_blockSize );

/**
 * @fn void mmc_setTransferSize ( uint32_t p_size );
 * @brief Cette fonction configure la taille d'un transfert en octets.
 * @param[in] p_size Ce paramètre contient la taille d'un transfert sur 24 bits.
 * @return Sans objet.
 *
 */

void mmc_setTransferSize ( uint32_t p_size );

/**
 * @fn void mmc_setDirection ( uint32_t p_direction );
 * @brief Cette fonction configure la direction du transfert.
 * @param[in] p_direction Ce paramètre contient la direction du transfert. Une des constantes suivantes
 *                        peut être utilisée : \n
 *                        \ref K_MMC_DIRECTION_CONTROLLER_TO_CARD ou \ref K_MMC_DIRECTION_CARD_TO_CONTROLLER
 * @return Sans objet.
 *
 */

void mmc_setDirection ( uint32_t p_direction );

/**
 * @fn void mmc_setTimeout ( uint32_t p_timeout );
 * @brief Cette fonction configure la durée du timeout. Elle prend effet lorsque l'état 'Wait_R' ou 'Busy' est détecté. Sur échéance,
 *        une interruption est déclenchée.
 * @param[in] p_timeout Ce paramètre contient la durée du timeout (sur 32 bits) en multiple de la période de la broche d'horloge.
 * @return Sans objet.
 *
 */

void mmc_setTimeout ( uint32_t p_timeout );

/**
 * @fn void mmc_setCommand ( uint32_t p_opCode, uint32_t p_argument, uint32_t p_responseType, uint32_t p_optionCode );
 * @brief Cette fonction configure la commande à transmettre au périphérique MMC.
 *
 * @param[in] p_opCode       Ce paramètre contient le code 8 bits de la commande. La constante \ref K_MMC_SUSPEND_COMMAND
 *                           peut être utilisée pour transmettre une commande d'arrêt si un média de type \a SDIO est connecté.
 * @param[in] p_argument     Ce paramètre contient l'argument 32 bits de la commande.
 * @param[in] p_responseType Ce paramètre contient le type de réponse à recevoir. Une des constantes suivantes peut
 *                           être utilisée : \n
 *                           \ref K_MMC_NO_RESPONSE, \ref K_MMC_SHORT_RESPONSE ou \ref K_MMC_LONG_RESPONSE
 * @param[in] p_optionCode   Ce paramètre contient des configurations additionnelles nécessaires à la machine à état. Une combinaison
 *                           des constantes suivantes peut être utilisée : \n
 *                           \ref K_MMC_OPT_STATE_MACHINE, \ref K_MMC_OPT_STREAM_MODE, \ref K_MMC_OPT_NO_CMD_TIMEOUT
 *
 * @note La valeur du timeout est configurée à partir de la fonction \ref mmc_setTimeout.
 * @return Sans objet.
 *
 */

void mmc_setCommand ( uint32_t p_opCode, uint32_t p_argument, uint32_t p_responseType, uint32_t p_optionCode );

/**
 * @fn void mmc_getResponse ( T_MMCResponse* p_register );
 * @brief Cette fonction retourne la valeur de la réponse renvoyée par le média. Dans le cas ou la réponse ne contient pas
 *        l'index de la commande, alors le champ 'index' prend la valeur $FF.
 * @param[in] p_register Ce paramètre contient la valeur de la réponse retournée par le média.
 * @return Sans objet.
 *
 */

void mmc_getResponse ( T_MMCResponse* p_register );

/**
 * @fn void mmc_getResponseByType ( void_t p_buf, uint32_t p_type );
 * @brief Cette fonction retourne la valeur d'une réponse en fonction de son type.
 *
 * @param[in] p_buf  Ce paramètre contient l'adresse du buffer où la réponse doit être stockée.
 * @param[in] p_type Ce paramètre contient le type de la réponse désirée. Une des constantes suivantes peut être utilisée :\n
 *                   \ref K_MMC_NO_RESPONSE, \ref K_MMC_SHORT_RESPONSE ou \ref K_MMC_LONG_RESPONSE
 * @return Sans objet.
 *
 */

void mmc_getResponseByType ( void_t p_buf, uint32_t p_type );

/**
 * @fn void mmc_enableTransfer ( void );
 * @brief Cette fonction active un transfert de données suite à la transmission d'une commande.
 * @return Sans objet.
 *
 */

void mmc_enableTransfer ( void );

/**
 * @fn void mmc_disableTransfer ( void );
 * @brief Cette fonction désactive un transfert de données.
 * @return Sans objet.
 *
 */

void mmc_disableTransfer ( void );

/**
 * @fn void mmc_writeWord ( uint32_t p_word );
 * @brief Cette fonction écrit un mot 32 bits dans le FIFO du périphérique MMC.
 *
 * @param[in] p_word Ce paramètre contient la valeur du mot 32bits à écrire dans le FIFO.
 * @return Sans objet.
 *
 */

void mmc_writeWord ( uint32_t p_word );

/**
 * @fn uint32_t mmc_readWord ( void );
 * @brief Cette fonction lit un mot 32 bits dans le FIFO du périphérique MMC.
 * @return La valeur du mot 32 bits lu.
 *
 */

uint32_t mmc_readWord ( void );

/**
 * @fn void mmc_setTransferSize ( uint32_t p_size );
 * @brief Cette fonction retourne le nombre de données restant à transférer.
 * @return Cette fonction retourne le nombre de données restant à transférer. Ce nombre est codé sur 24 bits.
 *
 */

uint32_t mmc_getDataCount ( void );

/**
 * @fn uint32_t mmc_getFifoCount ( void );
 * @brief Cette fonction retourne la taille disponible (en mots 32bits) dans le FIFO du périphérique MMC.
 * @return Le nombre de mots 32bits disponibles dans le FIFO du périphérique MMC.
 *
 */

uint32_t mmc_getFifoCount ( void );

/**
 *
 */

#endif


