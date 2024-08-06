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
* @file mk_peripheral_sdram_constants.h
* @brief Déclaration des constantes dédiées au contrôleur SDRAM.\n
* @date 23 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_SDRAM_CONSTANTS_H
#define MK_PERIPHERAL_SDRAM_CONSTANTS_H

/**
 * @def K_SDRAM_BANK1
 * @brief Adresse de base des registres de la banque 1.
 */

#define K_SDRAM_BANK1 ( addr_t ) 0xA0000140

/**
 * @def K_SDRAM_BANK2
 * @brief Adresse de base des registres de la banque 1.
 */

#define K_SDRAM_BANK2 ( addr_t ) 0xA0000144

/**
 * @def K_SDRAM_SDCMR
 * @brief Adresse du registre SDRAM_SDCMR.
 */

#define K_SDRAM_SDCMR ( addr_t ) 0xA0000150

/**
 * @def K_SDRAM_SDRTR
 * @brief Adresse du registre SDRAM_SDRTR.
 */

#define K_SDRAM_SDRTR ( addr_t ) 0xA0000154

/**
 * @def K_SDRAM_SDSR
 * @brief Adresse du registre SDRAM_SDSR.
 */

#define K_SDRAM_SDSR ( addr_t ) 0xA0000158

/**
 * @def K_SDRAM_CAS_TO_READ_NOCLOCK
 * @brief Constante dédiée à la fonction sdram_setReadLatency(). \n
 *        Définition du nombre de cycle d'horloge entre la fin de la latence
 *        CAS et la prochaine lecture.
 */

#define K_SDRAM_CAS_TO_READ_NOCLOCK 0x00000000

/**
 * @def K_SDRAM_CAS_TO_READ_1CLOCK
 * @brief Constante dédiée à la fonction sdram_setReadLatency(). \n
 *        Définition du nombre de cycle d'horloge entre la fin de la latence
 *        CAS et la prochaine lecture.
 */

#define K_SDRAM_CAS_TO_READ_1CLOCK 0x00002000

/**
 * @def K_SDRAM_CAS_TO_READ_2CLOCK
 * @brief Constante dédiée à la fonction sdram_setReadLatency(). \n
 *        Définition du nombre de cycle d'horloge entre la fin de la latence
 *        CAS et la prochaine lecture.
 */

#define K_SDRAM_CAS_TO_READ_2CLOCK 0x00004000

/**
 * @def K_SDRAM_CAS_LATENCY_1CLOCK
 * @brief Constante dédiée à la fonction sdram_setCASLatency(). \n
 *        Définition du nombre de cycle d'horloge de la latence CAS.
 */

#define K_SDRAM_CAS_LATENCY_1CLOCK 0x00000080

/**
 * @def K_SDRAM_CAS_LATENCY_2CLOCK
 * @brief Constante dédiée à la fonction sdram_setCASLatency(). \n
 *        Définition du nombre de cycle d'horloge de la latence CAS.
 */

#define K_SDRAM_CAS_LATENCY_2CLOCK 0x00000100

/**
 * @def K_SDRAM_CAS_LATENCY_3CLOCK
 * @brief Constante dédiée à la fonction sdram_setCASLatency(). \n
 *        Définition du nombre de cycle d'horloge de la latence CAS.
 */

#define K_SDRAM_CAS_LATENCY_3CLOCK 0x00000180

/**
 * @def K_SDRAM_PRESCALER_DIV2
 * @brief Constante dédiée à la fonction sdram_setClockPrescaler(). \n
 *        Configuration du prédiviseur à la valeur 2.
 */

#define K_SDRAM_PRESCALER_DIV2 0x00000800

/**
 * @def K_SDRAM_PRESCALER_DIV3
 * @brief Constante dédiée à la fonction sdram_setClockPrescaler(). \n
 *        Configuration du prédiviseur à la valeur 3.
 */

#define K_SDRAM_PRESCALER_DIV3 0x00000C00

/**
 * @def K_SDRAM_PRESCALER_DISABLE
 * @brief Constante dédiée à la fonction sdram_setClockPrescaler(). \n
 *        Désactivation de l'horloge qui cadence la mémoire SDRAM.
 */

#define K_SDRAM_PRESCALER_DISABLE 0x00000000

/**
 * @def K_SDRAM_TWO_INTERNAL_BANKS
 * @brief Constante dédiée à la fonction sdram_setBankNumber(). \n
 *        Configuration du nombre de "bank" internes du contrôleur SDRAM.
 */

#define K_SDRAM_TWO_INTERNAL_BANKS 0x00000000

/**
 * @def K_SDRAM_FOUR_INTERNAL_BANKS
 * @brief Constante dédiée à la fonction sdram_setBankNumber(). \n
 *        Configuration du nombre de "bank" internes du contrôleur SDRAM.
 */

#define K_SDRAM_FOUR_INTERNAL_BANKS 0x00000040

/**
 * @def K_SDRAM_DATABUS_8BITS
 * @brief Constante dédiée à la fonction sdram_setDataBusWidth(). \n
 *        Configuration de la largeur du bus de données.
 */

#define K_SDRAM_DATABUS_8BITS 0x00000000

/**
 * @def K_SDRAM_DATABUS_16BITS
 * @brief Constante dédiée à la fonction sdram_setDataBusWidth(). \n
 *        Configuration de la largeur du bus de données.
 */

#define K_SDRAM_DATABUS_16BITS 0x00000010

/**
 * @def K_SDRAM_DATABUS_32BITS
 * @brief Constante dédiée à la fonction sdram_setDataBusWidth(). \n
 *        Configuration de la largeur du bus de données.
 */

#define K_SDRAM_DATABUS_32BITS 0x00000020

/**
 * @def K_SDRAM_ADDRESS_ROW_11BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_ROW_11BITS 0x00000000

/**
 * @def K_SDRAM_ADDRESS_ROW_12BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_ROW_12BITS 0x00000004

/**
 * @def K_SDRAM_ADDRESS_ROW_13BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_ROW_13BITS 0x00000008

/**
 * @def K_SDRAM_ADDRESS_COLUMN_8BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_COLUMN_8BITS 0x00000000

/**
 * @def K_SDRAM_ADDRESS_COLUMN_9BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_COLUMN_9BITS 0x00000001

/**
 * @def K_SDRAM_ADDRESS_COLUMN_10BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_COLUMN_10BITS 0x00000002

/**
 * @def K_SDRAM_ADDRESS_COLUMN_11BITS
 * @brief Constante dédiée à la fonction sdram_setAddressBusWidth(). \n
 *        Configuration du bus d'adresse.
 */

#define K_SDRAM_ADDRESS_COLUMN_11BITS 0x00000003

/**
 * @def K_SDRAM_ROW_TO_COLUMN
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre une
 *        commande 'Activate' et une commande 'Read' ou 'Write'.
 */

#define K_SDRAM_ROW_TO_COLUMN 0x00000018

/**
 * @def K_SDRAM_ROW_PRECHARGE
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre une
 *        commande 'Precharge' et une autre commande.
 */

#define K_SDRAM_ROW_PRECHARGE 0x00000014

/**
 * @def K_SDRAM_RECOVERY
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre une
 *        commande 'Write'et une commande 'Precharge'.
 */

#define K_SDRAM_RECOVERY 0x00000010

/**
 * @def K_SDRAM_ROW_CYCLE
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre une
 *        commande 'Refresh' et une commande 'Activate' et entre deux
 *        commande 'Refresh'.
 */

#define K_SDRAM_ROW_CYCLE 0x0000000C

/**
 * @def K_SDRAM_SELF_REFRESH_TIME
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration de la durée minimum d'auto-rafraichissemnet.
 */

#define K_SDRAM_SELF_REFRESH_TIME 0x00000008

/**
 * @def K_SDRAM_EXIT_SELF_REFRESH
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre la
 *        fin d'une commande 'Self Refresh' et une commande 'Activate'.
 */

#define K_SDRAM_EXIT_SELF_REFRESH 0x00000004

/**
 * @def K_SDRAM_LOAD_MODE_REGISTER
 * @brief Constante dédiée à la fonction sdram_setMemoryCycle(). \n
 *        Configuration du nombre de cycle d'horloge mémoire entre une
 *        commande 'Load Mode Register' et une commande 'Activate' ou 'Refresh'.
 */

#define K_SDRAM_LOAD_MODE_REGISTER 0x00000000

/**
 * @def K_SDRAM_BANK1_FLAG
 * @brief Constante dédiée aux fonctions sdram_sendClock(), sdram_sendPall(),
 *        sdram_sendAutoRefresh(), sdram_sendLoadModeRegister(),
 *        sdram_sendSelfRefresh() et sdram_sendPowerdown(). \n
 *        Définition de la bank où la commande doit être transmise.
 */

#define K_SDRAM_BANK1_FLAG 0x00000010

/**
 * @def K_SDRAM_BANK2_FLAG
 * @brief Constante dédiée aux fonctions sdram_sendClock(), sdram_sendPall(),
 *        sdram_sendAutoRefresh(), sdram_sendLoadModeRegister(),
 *        sdram_sendSelfRefresh() et sdram_sendPowerdown(). \n
 *        Définition de la bank où la commande doit être transmise.
 */

#define K_SDRAM_BANK2_FLAG 0x00000008

/**
 * @def K_SDRAM_ENABLE_REFRESH_ERROR_INTERRUPT
 * @brief Constante dédiée à la fonction sdram_setRefreshRate(). \n
 *        Activation de l'interruption indiquant qu'une erreur de rafraichissement
 *        s'est produite.
 */

#define K_SDRAM_ENABLE_REFRESH_ERROR_INTERRUPT 0x00004000

/**
 * @def K_SDRAM_DISABLE_REFRESH_ERROR_INTERRUPT
 * @brief Constante dédiée à la fonction sdram_setRefreshRate(). \n
 *        Désactivation de l'interruption indiquant qu'une erreur de rafraichissement
 *        s'est produite.
 */

#define K_SDRAM_DISABLE_REFRESH_ERROR_INTERRUPT 0x00000000

/**
 * @def K_SDRAM_BANK_NORMAL_MODE
 * @brief Constante dédiée aux fonctions sdram_getBankStatus1() et sdram_getBankStatus2(). \n
 *        Définition du mode de fonctionnement courant des bank 1 et 2.
 */

#define K_SDRAM_BANK_NORMAL_MODE 0x00000000

/**
 * @def K_SDRAM_BANK_SELFREFRESH_MODE
 * @brief Constante dédiée aux fonctions sdram_getBankStatus1() et sdram_getBankStatus2(). \n
 *        Définition du mode de fonctionnement courant des bank 1 et 2.
 */

#define K_SDRAM_BANK_SELFREFRESH_MODE 0x00000001

/**
 * @def K_SDRAM_POWERDOWN_MODE
 * @brief Constante dédiée aux fonctions sdram_getBankStatus1() et sdram_getBankStatus2(). \n
 *        Définition du mode de fonctionnement courant des bank 1 et 2.
 */

#define K_SDRAM_POWERDOWN_MODE 0x00000002

/**
 * @def K_SDRAM_OK
 * @brief Constante dédiée aux fonctions sdram_enableClock(), sdram_enterSelfRefreshMode(),
 *        sdram_enterPowerdownMode(), sdram_sendAutoRefresh(), sdram_sendLoadModeRegister()
 *        et sdram_sendPall() \n
 *        Résultat d'une fonction indiquant que le transfert de la commande a réussi.
 */

#define K_SDRAM_OK 0x00000000

/**
 * @def K_SDRAM_BUSY
 * @brief Constante dédiée aux fonctions sdram_enableClock(), sdram_enterSelfRefreshMode(),
 *        sdram_enterPowerdownMode(), sdram_sendAutoRefresh(), sdram_sendLoadModeRegister()
 *        et sdram_sendPall() \n
 *        Résultat d'une fonction indiquant que la commande n'a pas été transmise au bout
 *        du timeout spécifié.
 */

#define K_SDRAM_BUSY 0x00000001

/**
 * @def K_SDRAM_BUSY
 * @brief Définition du timeout de transmission d'une commande.
 */

#define K_SDRAM_TIMEOUT 0x00000100

/**
 *
 */

#endif


