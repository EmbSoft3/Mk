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
* @file mk_peripheral_sdram.h
* @brief Déclaration des fonctions dédiées au contrôleur SDRAM.\n
* @date 23 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_SDRAM_H
#define MK_PERIPHERAL_SDRAM_H

/**
 * @fn sdram_setRefreshRate ( uint32_t p_interrupt, uint32_t p_timer );
 * @brief Cette fonction configure la fréquence de rafraichissement de la mémoire SDRAM. L'équation déterminant la fréquence
 *        de rafraichissement est la suivante : \n
 *
 *        refresh_rate = ( p_timer + 1 ) x SDRAM_FREQUENCY_CLOCK \n
 *        p_timer = ( SDRAM_REFRESH_PERIOD / NUMBER_OF_ROWS ) - 20 \n
 *
 *        La valeur 20 est retranchée pour obtenir une marge de sécurité si une requête de rafraichissement survient quand
 *        une requête de lecture vient d'être acceptée.\n
 *        Suite à l'appel de cette fonction, la valeur de p_timer est chargée dans un timer interne qui commence à compter.
 *        Lorsque la valeur nulle est atteinte, un pulse de rafraichissement est transmis à la mémoire SDRAM.
 *
 * @param[in] p_interrupt Ce paramètre permet d'activer l'interruption indiquant qu'une erreur de rafraichissement est survenue.
 *                        Les constantes suivantes peuvent être utilisées : \n
 *                        \ref K_SDRAM_ENABLE_REFRESH_ERROR_INTERRUPT et \ref K_SDRAM_DISABLE_REFRESH_ERROR_INTERRUPT.
 * @param[in] p_timer     Ce paramètre contient l'image de la fréquence de rafraichissement sur 13 bits.
 *
 * @warning La valeur du paramètre de p_timer doit répondre aux deux conditions suivantes : \n
 *          p_timer >= 41 cycles d'horloge
 *          p_timer != K_SDRAM_RECOVERY + K_SDRAM_ROW_PRECHARGE + K_SDRAM_ROW_CYCLE + K_SDRAM_ROW_TO_COLUMN + 4 cycles d'horloge
 *
 * @return Sans objet.
 *
 */

void sdram_setRefreshRate ( uint32_t p_interrupt, uint32_t p_timer );

/**
 * @fn sdram_setReadLatency ( uint32_t p_latency );
 * @brief Cette fonction configure la durée (en cycle d'horloge) pour effectuer une lecture après la latence CAS ("Column Access Strobe").
 *
 * @param[in] p_latency Ce paramètre configure le nombre de cycles d'horloge entre la fin de la latence CAS et la prochaine lecture.
 *                      Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_SDRAM_CAS_TO_READ_NOCLOCK, \ref K_SDRAM_CAS_TO_READ_1CLOCK, \ref K_SDRAM_CAS_TO_READ_2CLOCK
 *
 * @note Une commande PALL doit être transmise avant l'appel de cette fonction pour s'assurer que l'intégralité des opérations en cours
 *       sont terminées.
 * @return Sans objet.
 *
 */

void sdram_setReadLatency ( uint32_t p_latency );

/**
 * @fn void sdram_setCASLatency ( void_t p_bank, uint32_t p_latency );
 * @brief Cette fonction configure la durée (en cycle d'horloge) de la latence CAS ("Column Access Strobe").
 *
 * @param[in] p_bank    Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 * @param[in] p_latency Ce paramètre configure le nombre de cycles d'horloge de la latence CAS. Les constantes suivantes peuvent être utilisées : \n
 *                      \ref K_SDRAM_CAS_LATENCY_1CLOCK, \ref K_SDRAM_CAS_LATENCY_2CLOCK, \ref K_SDRAM_CAS_LATENCY_3CLOCK
 *
 * @note Une commande PALL doit être transmise avant l'appel de cette fonction pour s'assurer que l'intégralité des opérations en cours
 *       sont terminées.
 * @return Sans objet.
 *
 */

void sdram_setCASLatency ( void_t p_bank, uint32_t p_latency );

/**
 * @fn void sdram_enableBurstMode ( void_t p_bank );
 * @brief Cette fonction active le mode burst. Le contrôleur anticipe les prochaines commandes de lecture durant la latence CAS et
 *        stocke les prochaines données dans le FIFO d'entrée.

 * @return Sans objet.
 *
 */

void sdram_enableBurstMode ( void );

/**
 * @fn void sdram_disableBurstMode ( void_t p_bank );
 * @brief Cette fonction désactive le mode burst. Le contrôleur n'anticipe pas les prochaines commandes de lecture durant la latence
 *        CAS. Les prochaines données ne sont pas stockée dans le FIFO d'entrée.
 *
 * @return Sans objet.
 *
 */

void sdram_disableBurstMode ( void );

/**
 * @fn void sdram_setClockPrescaler ( uint32_t p_prescaler );
 * @brief Cette fonction configure le diviseur de l'horloge (HCLK) qui cadence la mémoire SDRAM. Elle permet aussi de désactiver cette horloge
 *        en utilisant la constante \ref K_SDRAM_PRESCALER_DISABLE :
 *
 * @param[in] p_prescaler Ce paramètre contient la valeur à appliquer au diviseur. Les constantes suivantes peuvent être utilisées : \n
 *                        \ref K_SDRAM_PRESCALER_DIV2, \ref K_SDRAM_PRESCALER_DIV3, \ref K_SDRAM_PRESCALER_DISABLE
 *
 * @warning Suite à une désactivation de l'horloge avec la constante \ref K_SDRAM_PRESCALER_DISABLE, la mémoire SDRAM doit être
 *          réinitialisée. Une commande PALL doit être transmise avant l'appel de cette fonction dans le cas où l'horloge est désactivée.
 * @return Sans objet.
 *
 */

void sdram_setClockPrescaler ( uint32_t p_prescaler );

/**
 * @fn void sdram_enableWriteProtection ( void_t p_bank );
 * @brief Cette fonction active la protection en écriture de la bank spécifiée en paramètre.
 *
 * @param[in] p_bank Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 *
 * @return Sans objet.
 *
 */

void sdram_enableWriteProtection ( void_t p_bank );

/**
 * @fn void sdram_disableWriteProtection ( void_t p_bank );
 * @brief Cette fonction désactive la protection en écriture de la bank spécifiée en paramètre.
 *
 * @param[in] p_bank Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 *
 * @return Sans objet.
 *
 */

void sdram_disableWriteProtection ( void_t p_bank );

/**
 * @fn void sdram_setBankNumber ( void_t p_bank, uint32_t p_count );
 * @brief Cette fonction configure le nombre de bank interne d'une mémoire SDRAM.
 *
 * @param[in] p_bank Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 * @param[in] p_count Ce paramètre contient le nombre de bank. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_TWO_INTERNAL_BANKS et \ref K_SDRAM_FOUR_INTERNAL_BANKS
 *
 * @return Sans objet.
 *
 */

void sdram_setBankNumber ( void_t p_bank, uint32_t p_count );

/**
 * @fn void sdram_setDataBusWidth ( void_t p_bank, uint32_t p_width );
 * @brief Cette fonction configure la largeur du bus de données d'une mémoire SDRAM.
 *
 * @param[in] p_bank Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 * @param[in] p_width Ce paramètre contient la largeur du bus de données. Les constantes suivantes peuvent être utilisées : \n
 *                   \ref K_SDRAM_DATABUS_8BITS, \ref K_SDRAM_DATABUS_16BITS et \ref K_SDRAM_DATABUS_32BITS
 *
 * @return Sans objet.
 *
 */

void sdram_setDataBusWidth ( void_t p_bank, uint32_t p_width );

/**
 * @fn void sdram_setAddressBusWidth ( void_t p_bank, uint32_t p_row, uint32_t p_column );
 * @brief Cette fonction configure le bus d'adresse d'une mémoire SDRAM.
 *
 * @param[in] p_bank   Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées :
 *                     \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 * @param[in] p_row    Ce paramètre contient la largeur d'une rangée. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_SDRAM_ADDRESS_ROW_11BITS, \ref K_SDRAM_ADDRESS_ROW_12BITS et \ref K_SDRAM_ADDRESS_ROW_13BITS
 * @param[in] p_column Ce paramètre contient la largeur d'une colonne. Les constantes suivantes peuvent être utilisées : \n
 *                     \ref K_SDRAM_ADDRESS_COLUMN_8BITS, \ref K_SDRAM_ADDRESS_COLUMN_9BITS, \ref K_SDRAM_ADDRESS_COLUMN_10BITS et
 *                     \ref K_SDRAM_ADDRESS_COLUMN_11BITS
 *
 * @return Sans objet.
 *
 */

void sdram_setAddressBusWidth ( void_t p_bank, uint32_t p_row, uint32_t p_column );

/**
 * @fn void sdram_setMemoryCycle ( void_t p_bank, uint32_t p_type, uint32_t p_value );
 * @brief Cette fonction configure le timing (en cycle d'horloge mémoire) entre deux commandes.
 *
 * @param[in] p_bank  Ce paramètre contient la bank à configurer. Les constantes suivantes peuvent être utilisées :
 *                    \ref K_SDRAM_BANK1 et \ref K_SDRAM_BANK2
 * @param[in] p_type  Ce paramètre contient un identifiant indiquant le timing à configurer. Les constantes suivantes
 *                    peuvent être utilisées : \n
 *                    \ref K_SDRAM_ROW_TO_COLUMN, \ref K_SDRAM_ROW_PRECHARGE, \ref K_SDRAM_RECOVERY, \ref K_SDRAM_ROW_CYCLE,
 *                    \ref K_SDRAM_SELF_REFRESH_TIME, \ref K_SDRAM_EXIT_SELF_REFRESH, \ref K_SDRAM_LOAD_MODE_REGISTER
 * @param[in] p_value Ce paramètre contient le nombre de cycles mémoire à configurer. Il évolue entre [1 et 16] cycles.
 *
 * @note L'appel de cette fonction avec les paramètres \ref K_SDRAM_BANK2 et \ref K_SDRAM_ROW_PRECHARGE ou K_SDRAM_ROW_CYCLE est
 *       sans effet.
 * @return Sans objet.
 *
 */

void sdram_setMemoryCycle ( void_t p_bank, uint32_t p_type, uint32_t p_value );

/**
 * @fn uint32_t sdram_enableClock ( uint32_t p_bank );
 * @brief Cette fonction transmet une commande 'ClockConfiguration' à la mémoire SDRAM. Cette commande fournit l'horloge à la
 *        mémoire SDRAM.
 *
 * @param[in] p_bank Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 *
 * @return Cette fonction retourne les valeurs suivantes :\n
 *         \ref K_SDRAM_OK et \ref K_SDRAM_BUSY
 *
 */

uint32_t sdram_enableClock ( uint32_t p_bank );

/**
 * @fn uint32_t sdram_sendPall ( uint32_t p_bank );
 * @brief Cette fonction transmet une commande 'PALL - All Bank Precharge' à la mémoire SDRAM.
 *
 * @param[in] p_bank Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 *
 * @return Cette fonction retourne les valeurs suivantes :\n
 *         \ref K_SDRAM_OK et \ref K_SDRAM_BUSY
 *
 */

uint32_t sdram_sendPall ( uint32_t p_bank );

/**
 * @fn uint32_t sdram_sendAutoRefresh ( uint32_t p_bank, uint32_t p_cycle );
 * @brief Cette fonction transmet une commande 'AutoRefresh' à la mémoire SDRAM. Une commande 'PALL' doit être transmise à la mémoire
 *        avant l'appel de cette fonction. La fonction \ref sdram_sendPall peut être utilisée.
 *
 * @param[in] p_bank  Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                    suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 * @param[in] p_cycle Ce paramètre contient le nombre de commande 'AutoRefresh' transmise consécutivement après l'appel de cette
 *                    fonction. Il évolue entre [1 et 16] cycles.
 *
 * @return Cette fonction retourne les valeurs suivantes :\n
 *         \ref K_SDRAM_OK et \ref K_SDRAM_BUSY
 *
 */

uint32_t sdram_sendAutoRefresh ( uint32_t p_bank, uint32_t p_cycle );

/**
 * @fn uint32_t sdram_sendLoadModeRegister ( uint32_t p_bank, uint32_t p_value );
 * @brief Cette fonction transmet une commande 'Load Mode Register' à la mémoire SDRAM.
 *
 * @param[in] p_bank  Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                    suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 * @param[in] p_value Ce paramètre contient le contenu du registre 'Load Mode' à transmettre. Il est codé sur 13 bits.
 *
 * @return Cette fonction retourne les valeurs suivantes :\n
 *         \ref K_SDRAM_OK et \ref K_SDRAM_BUSY
 *
 */

uint32_t sdram_sendLoadModeRegister ( uint32_t p_bank, uint32_t p_value );

/**
 * @fn uint32_t sdram_enterSelfRefreshMode ( uint32_t p_bank );
 * @brief Cette fonction transmet une commande 'Self Refresh' à la mémoire SDRAM. Suite à l'appel de cette fonction, l'horloge
 *        n'est plus fourni à la mémoire SDRAM. Les opérations de rafraichissement sont effectuées en interne de celle-ci.
 *
 * @param[in] p_bank Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 *
 * @return Cette fonction retourne les valeurs suivantes :\n
 *         \ref K_SDRAM_OK et \ref K_SDRAM_BUSY
 *
 */

uint32_t sdram_enterSelfRefreshMode ( uint32_t p_bank );

/**
 * @fn void sdram_enterPowerdownMode ( uint32_t p_bank );
 * @brief Cette fonction transmet une commande 'Powerdown' à la mémoire SDRAM. Suite à l'appel de cette fonction, l'horloge n'est
 *        plus fourni continuellement à la mémoire SDRAM. Les opérations de rafraichissement ne sont pas effectuées par la mémoire
 *        mais par le contrôleur SDRAM qui réveil la mémoire puis transmet une commande de rafraichissement périodiquement.
 *
 * @param[in] p_bank Ce paramètre contient la ou les bank où la commande doit être transmise. Une combinaison des constantes
 *                   suivantes peuvent être utilisées : \n \ref K_SDRAM_BANK1_FLAG et \ref K_SDRAM_BANK2_FLAG
 *
 * @return Sans objet.
 *
 */

uint32_t sdram_enterPowerdownMode ( uint32_t p_bank );

/**
 * @fn uint32_t sdram_getBusyStatus ( void );
 * @brief Cette fonction retourne le statut du controleur SDRAM.
 * @return Cette fonction retourne la valeur 0 si le contrôleur SDRAM peut transmettre une nouvelle commande, sinon la valeur 1.
 *
 */

uint32_t sdram_getBusyStatus ( void );

/**
 * @fn uint32_t sdram_getBankStatus1 ( void );
 * @brief Cette fonction retourne le mode courant de la bank 1.
 * @return Cette fonction retourne une des valeurs suivantes : \n
 *         \ref K_SDRAM_BANK_NORMAL_MODE, \ref K_SDRAM_BANK_SELFREFRESH_MODE, \ref K_SDRAM_POWERDOWN_MODE
 *
 */

uint32_t sdram_getBankStatus1 ( void );

/**
 * @fn uint32_t sdram_getBankStatus2 ( void );
 * @brief Cette fonction retourne le mode courant de la bank 2.
 * @return Cette fonction retourne une des valeurs suivantes : \n
 *         \ref K_SDRAM_BANK_NORMAL_MODE, \ref K_SDRAM_BANK_SELFREFRESH_MODE, \ref K_SDRAM_POWERDOWN_MODE
 *
 */

uint32_t sdram_getBankStatus2 ( void );

/**
 * @fn uint32_t sdram_getRefreshErrorFlag ( void );
 * @brief Cette fonction retourne le drapeau d'interruption indiquant qu'une erreur de rafraichissement est survenue.
 * @return Cette fonction retourne la valeur 1 si une erreur s'est produite, sinon la valeur 0.
 *
 */

uint32_t sdram_getRefreshErrorFlag ( void );

/**
 *
 */

#endif
