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
* @file mk_peripheral_qspi_constants.h
* @brief Déclaration des constantes dédiées au périphérique QSPI.
* @date 2 mai 2020
*
*/

#ifndef MK_PERIPHERAL_QSPI_CONSTANTS_H
#define MK_PERIPHERAL_QSPI_CONSTANTS_H

/**
 * @def K_QSPI_CR
 * @brief Adresse du registre QSPI_CR.
 */

#define K_QSPI_CR ( addr_t ) 0xA0001000

/**
 * @def K_QSPI_DCR
 * @brief Adresse du registre QSPI_DCR.
 */

#define K_QSPI_DCR ( addr_t ) 0xA0001004

/**
 * @def K_QSPI_SR
 * @brief Adresse du registre QSPI_SR.
 */

#define K_QSPI_SR ( addr_t ) 0xA0001008

/**
 * @def K_QSPI_FCR
 * @brief Adresse du registre QSPI_FCR.
 */

#define K_QSPI_FCR ( addr_t ) 0xA000100C

/**
 * @def K_QSPI_DLR
 * @brief Adresse du registre QSPI_DLR.
 */

#define K_QSPI_DLR ( addr_t ) 0xA0001010

/**
 * @def K_QSPI_CCR
 * @brief Adresse du registre QSPI_CCR.
 */

#define K_QSPI_CCR ( addr_t ) 0xA0001014

/**
 * @def K_QSPI_AR
 * @brief Adresse du registre QSPI_AR.
 */

#define K_QSPI_AR ( addr_t ) 0xA0001018

/**
 * @def K_QSPI_ABR
 * @brief Adresse du registre QSPI_ABR.
 */

#define K_QSPI_ABR ( addr_t ) 0xA000101C

/**
 * @def K_QSPI_DR
 * @brief Adresse du registre QSPI_DR.
 */

#define K_QSPI_DR ( addr_t ) 0xA0001020

/**
 * @def K_QSPI_PSMKR
 * @brief Adresse du registre QSPI_PSMKR.
 */

#define K_QSPI_PSMKR ( addr_t ) 0xA0001024

/**
 * @def K_QSPI_PSMAR
 * @brief Adresse du registre QSPI_PSMAR.
 */

#define K_QSPI_PSMAR ( addr_t ) 0xA0001028

/**
 * @def K_QSPI_PIR
 * @brief Adresse du registre QSPI_PIR.
 */

#define K_QSPI_PIR ( addr_t ) 0xA000102C

/**
 * @def K_QSPI_LPTR
 * @brief Adresse du registre QSPI_LPTR.
 */

#define K_QSPI_LPTR ( addr_t ) 0xA0001030

/**
 *
 */

/**
 * @def K_QSPI_OK
 * @brief Constante générique.\n
 *        Définition d'un code indiquant que l'opération courante a réussi.
 */

#define K_QSPI_OK 0x00000000

/**
 * @def K_QSPI_KO
 * @brief Constante générique.\n
 *        Définition d'un code indiquant que l'opération courante a échoué.
 */


#define K_QSPI_KO 0x00000001

/**
 *
 */

/**
 * @def K_QSPI_FLASH1
 * @brief Constante dédiée à la fonction qspi_enableSingleFlashMode().\n
 *        Définition de l'identifiant de la FLASH numéro 1.
 */

#define K_QSPI_FLASH1 0x00000000

/**
 * @def K_QSPI_FLASH2
 * @brief Constante dédiée à la fonction qspi_enableSingleFlashMode().\n
 *        Définition de l'identifiant de la FLASH numéro 2.
 */

#define K_QSPI_FLASH2 0x00000080

/**
 *
 */

/**
 * @def K_QSPI_TIMEOUT_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition de l'interruption TIMEOUT.
 */

#define K_QSPI_TIMEOUT_INTERRUPT 0x00100000

/**
 * @def K_QSPI_STATUS_MATCH_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition de l'interruption STATUS_MATCH.
 */

#define K_QSPI_STATUS_MATCH_INTERRUPT 0x00080000

/**
 * @def K_QSPI_FIFO_THRESHOLD_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition de l'interruption FIFO_THRESHOLD.
 */

#define K_QSPI_FIFO_THRESHOLD_INTERRUPT 0x00040000

/**
 * @def K_QSPI_TRANSFER_COMPLETE_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition de l'interruption TRANSFER_COMPLETE.
 */

#define K_QSPI_TRANSFER_COMPLETE_INTERRUPT 0x00020000

/**
 * @def K_QSPI_TRANSFER_ERROR_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition de l'interruption TRANSFER_ERROR.
 */

#define K_QSPI_TRANSFER_ERROR_INTERRUPT 0x00010000

/**
 * @def K_QSPI_ALL_INTERRUPT
 * @brief Constante dédiée aux fonctions qspi_enableInterrupt() et qspi_disableInterrupt().\n
 *        Définition d'une constante adressant toutes les interruptions.
 */

#define K_QSPI_ALL_INTERRUPT 0x001F0000

/**
 *
 */

/**
 * @def K_QSPI_DEFAULT_EDGE
 * @brief Constante dédiée à la fonction qspi_setSampleEdge().\n
 *        Définition du point d'échantillonnage des données fournis par la mémorie FLASH.
 */

#define K_QSPI_DEFAULT_EDGE 0x00000000

/**
 * @def K_QSPI_NEXT_EDGE
 * @brief Constante dédiée à la fonction qspi_setSampleEdge().\n
 *        Définition du point d'échantillonnage des données fournis par la mémorie FLASH.
 */

#define K_QSPI_NEXT_EDGE 0x00000010

/**
 *
 */

/**
 * @def K_QSPI_MATCH_AND
 * @brief Constante dédiée à la fonction qspi_setPollingMatchMode().\n
 *        Définition du type de comparaison réalisée par le périphérique QSPI lors de la génération
 *        d'un événement 'Match'.
 */

#define K_QSPI_MATCH_AND 0x00000000

/**
 * @def K_QSPI_MATCH_OR
 * @brief Constante dédiée à la fonction qspi_setPollingMatchMode().\n
 *        Définition du type de comparaison réalisée par le périphérique QSPI lors de la génération
 *        d'un événement 'Match'.
 */

#define K_QSPI_MATCH_OR 0x00800000

/**
 *
 */

/**
 * @def K_QSPI_AUTOMATIC_POLLING_MODE_CONTINUE_AFTER_MATCH
 * @brief Constante dédiée à la fonction qspi_setPollingMatchMode().\n
 *        Définition du comportement adopté par le périphérique QSPI lorsqu'un événement 'Match' est
 *        survenu.
 */

#define K_QSPI_AUTOMATIC_POLLING_MODE_CONTINUE_AFTER_MATCH 0x00000000

/**
 * @def K_QSPI_AUTOMATIC_POLLING_MODE_STOP_AFTER_MATCH
 * @brief Constante dédiée à la fonction qspi_setPollingMatchMode().\n
 *        Définition du comportement adopté par le périphérique QSPI lorsqu'un événement 'Match' est
 *        survenu.
 */

#define K_QSPI_AUTOMATIC_POLLING_MODE_STOP_AFTER_MATCH 0x00400000

/**
 *
 */

/**
 * @def K_QSPI_ABORT_OK
 * @brief Constante dédiée à la fonction qspi_getAbortStatus().\n
 *        Valeur de retour indiquant l'arrêt du transfert.
 */

#define K_QSPI_ABORT_OK 0x00000000

/**
 * @def K_QSPI_ABORT_IN_PROGRESS
 * @brief Constante dédiée à la fonction qspi_getAbortStatus().\n
 *        Valeur de retour indiquant que le transfert est toujours en cours d'exécution.
 */

#define K_QSPI_ABORT_IN_PROGRESS 0x00000001

/**
 *
 */

/**
 * @def K_QSPI_IDLE_CLOCK_LOW
 * @brief Constante dédiée à la fonction qspi_setIdleClockState().\n
 *        Définition de l'état de repos de l'horloge entre deux commandes.
 */

#define K_QSPI_IDLE_CLOCK_LOW 0x00000000

/**
 * @def K_QSPI_IDLE_CLOCK_HIGH
 * @brief Constante dédiée à la fonction qspi_setIdleClockState().\n
 *        Définition de l'état de repos de l'horloge entre deux commandes.
 */

#define K_QSPI_IDLE_CLOCK_HIGH 0x00000001

/**
 *
 */

/**
 * @def K_QSPI_BUSY_STATUS
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition de la position du drapeau BUSY_STATUS.
 */

#define K_QSPI_BUSY_STATUS 0x00000005

/**
 * @def K_QSPI_TIMEOUT_STATUS
 * @brief Constante dédiée aux fonctions qspi_getStatus() et qspi_clearStatus().\n
 *        Définition de la position du drapeau TIMEOUT_STATUS.
 */

#define K_QSPI_TIMEOUT_STATUS 0x00000004

/**
 * @def K_QSPI_MATCH_STATUS
 * @brief Constante dédiée aux fonctions qspi_getStatus() et qspi_clearStatus().\n
 *        Définition de la position du drapeau MATCH_STATUS.
 */

#define K_QSPI_MATCH_STATUS 0x00000003

/**
 * @def K_QSPI_FIFO_THRESHOLD_STATUS
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition de la position du drapeau FIFO_THRESHOLD.
 */

#define K_QSPI_FIFO_THRESHOLD_STATUS 0x00000002

/**
 * @def K_QSPI_TRANSFER_COMPLETE_STATUS
 * @brief Constante dédiée aux fonctions qspi_getStatus() et qspi_clearStatus().\n
 *        Définition de la position du drapeau TRANSFER_COMPLETE_STATUS.
 */

#define K_QSPI_TRANSFER_COMPLETE_STATUS 0x00000001

/**
 * @def K_QSPI_TRANSFER_ERROR_STATUS
 * @brief Constante dédiée aux fonctions qspi_getStatus() et qspi_clearStatus().\n
 *        Définition de la position du drapeau TRANSFER_ERROR_STATUS.
 */

#define K_QSPI_TRANSFER_ERROR_STATUS 0x00000000

/**
 *
 */

/**
 * @def K_QSPI_BUSY
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut BUSY.
 */

#define K_QSPI_BUSY 0x00000001


/**
 * @def K_QSPI_TIMEOUT
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut TIMEOUT.
 */

#define K_QSPI_TIMEOUT 0x00000001

/**
 * @def K_QSPI_MATCH
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut MATCH.
 */

#define K_QSPI_MATCH 0x00000001

/**
 * @def K_QSPI_FIFO_THRESHOLD
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut FIFO_THRESHOLD.
 */

#define K_QSPI_FIFO_THRESHOLD 0x00000001

/**
 * @def K_QSPI_TRANSFER_COMPLETE
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut TRANSFER_COMPLETE.
 */

#define K_QSPI_TRANSFER_COMPLETE 0x00000001

/**
 * @def K_QSPI_TRANSFER_ERROR
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif au statut TRANSFER_ERROR.
 */

#define K_QSPI_TRANSFER_ERROR 0x00000001

/**
 * @def K_QSPI_BUSY
 * @brief Constante dédiée à la fonction qspi_getStatus().\n
 *        Définition du code de retour relatif aux statuts BUSY, TIMEOUT, MATCH, FIFO_THRESHOLD,
 *        TRANSFER_COMPLETE et TRANSFER_ERROR.
 */

#define K_QSPI_IDLE 0x00000000

/**
 *
 */

/**
 * @def K_QSPI_SDR_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de l'identifiant du mode SDR (SingleDataRate).
 */

#define K_QSPI_SDR_MODE 0x00000000

/**
 * @def K_QSPI_DDR_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de l'identifiant du mode DDR (DoubleDataRate).
 */

#define K_QSPI_DDR_MODE 0x80000000

/**
 *
 */

/**
 * @def K_QSPI_ANALOG_DELAY
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de l'instant de pilotage des données QSPI en mode DDR.
 */

#define K_QSPI_ANALOG_DELAY 0x00000000

/**
 * @def K_QSPI_QUARTER_DELAY
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de l'instant de pilotage des données QSPI en mode DDR.
 */

#define K_QSPI_QUARTER_DELAY 0x40000000

/**
 *
 */

/**
 * @def K_QSPI_INSTRUCTION_NO_LINE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'instruction.
 */

#define K_QSPI_INSTRUCTION_NO_LINE_MODE 0x00000000

/**
 * @def K_QSPI_INSTRUCTION_SINGLE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'instruction.
 */

#define K_QSPI_INSTRUCTION_SINGLE_MODE 0x00000100

/**
 * @def K_QSPI_INSTRUCTION_DUAL_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'instruction.
 */

#define K_QSPI_INSTRUCTION_DUAL_MODE 0x00000200

/**
 * @def K_QSPI_INSTRUCTION_QUAD_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'instruction.
 */

#define K_QSPI_INSTRUCTION_QUAD_MODE 0x00000300

/**
 *
 */

/**
 * @def K_QSPI_ADDRESS_NO_LINE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'adressse.
 */

#define K_QSPI_ADDRESS_NO_LINE_MODE 0x00000000

/**
 * @def K_QSPI_ADDRESS_SINGLE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'adressse.
 */

#define K_QSPI_ADDRESS_SINGLE_MODE 0x00000400

/**
 * @def K_QSPI_ADDRESS_DUAL_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'adressse.
 */

#define K_QSPI_ADDRESS_DUAL_MODE 0x00000800

/**
 * @def K_QSPI_ADDRESS_QUAD_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert de l'adressse.
 */

#define K_QSPI_ADDRESS_QUAD_MODE 0x00000C00

/**
 *
 */

/**
 * @def K_QSPI_ADDRESS_SIZE_8BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des adresses.
 */

#define K_QSPI_ADDRESS_SIZE_8BITS 0x00000000

/**
 * @def K_QSPI_ADDRESS_SIZE_16BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des adresses.
 */

#define K_QSPI_ADDRESS_SIZE_16BITS 0x00001000

/**
 * @def K_QSPI_ADDRESS_SIZE_24BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des adresses.
 */

#define K_QSPI_ADDRESS_SIZE_24BITS 0x00002000

/**
 * @def K_QSPI_ADDRESS_SIZE_32BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des adresses.
 */

#define K_QSPI_ADDRESS_SIZE_32BITS 0x00003000

/**
 *
 */

/**
 * @def K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des paramètres.
 */

#define K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE 0x00000000

/**
 * @def K_QSPI_ALTERNATE_BYTES_SINGLE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des paramètres.
 */

#define K_QSPI_ALTERNATE_BYTES_SINGLE_MODE 0x00004000

/**
 * @def K_QSPI_ALTERNATE_BYTES_DUAL_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des paramètres.
 */

#define K_QSPI_ALTERNATE_BYTES_DUAL_MODE 0x00008000

/**
 * @def K_QSPI_ALTERNATE_BYTES_QUAD_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des paramètres.
 */

#define K_QSPI_ALTERNATE_BYTES_QUAD_MODE 0x0000C000

/**
 *
 */

/**
 * @def K_QSPI_ALTERNATE_BYTES_SIZE_8BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des paramètres d'une commande.
 */

#define K_QSPI_ALTERNATE_BYTES_SIZE_8BITS 0x00000000

/**
 * @def K_QSPI_ALTERNATE_BYTES_SIZE_16BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des paramètres d'une commande.
 */

#define K_QSPI_ALTERNATE_BYTES_SIZE_16BITS 0x00010000

/**
 * @def K_QSPI_ALTERNATE_BYTES_SIZE_24BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des paramètres d'une commande.
 */

#define K_QSPI_ALTERNATE_BYTES_SIZE_24BITS 0x00020000

/**
 * @def K_QSPI_ALTERNATE_BYTES_SIZE_32BITS
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition de la taille des paramètres d'une commande.
 */

#define K_QSPI_ALTERNATE_BYTES_SIZE_32BITS 0x00030000

/**
 *
 */

/**
 * @def K_QSPI_DATA_NO_LINE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des données.
 */

#define K_QSPI_DATA_NO_LINE_MODE 0x00000000

/**
 * @def K_QSPI_DATA_SINGLE_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des données.
 */

#define K_QSPI_DATA_SINGLE_MODE 0x01000000

/**
 * @def K_QSPI_DATA_DUAL_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des données.
 */

#define K_QSPI_DATA_DUAL_MODE 0x02000000

/**
 * @def K_QSPI_DATA_QUAD_MODE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition du nombre de broches QSPI utilisés lors du transfert des données.
 */

#define K_QSPI_DATA_QUAD_MODE 0x03000000

/**
 *
 */

/**
 * @def K_QSPI_SEND_INSTRUCTION_ONLY_ONCE
 * @brief Constante dédiée aux fonctions qspi_enableMemoryMappedMode(), qspi_enableStatusPollingMode(),
 *        qspi_enableIndirectReadMode() et qspi_enableIndirectWriteMode().\n
 *        Définition d'une constante permettant permettant de ne pas réperter l'instruction
 *        à chaque commande.
 */

#define K_QSPI_SEND_INSTRUCTION_ONLY_ONCE 0x10000000

/**
 *
 */

/**
 * @def K_QSPI_INDIRECT_WRITE_MODE
 * @brief Constante dédiée à la fonction qspi_setMode().\n
 *        Définition de l'identifiant du mode 'INDIRECT_WRITE'.
 */

#define K_QSPI_INDIRECT_WRITE_MODE 0x00000000

/**
 * @def K_QSPI_INDIRECT_READ_MODE
 * @brief Constante dédiée à la fonction qspi_setMode().\n
 *        Définition de l'identifiant du mode 'INDIRECT_READ'.
 */

#define K_QSPI_INDIRECT_READ_MODE 0x01000000

/**
 * @def K_QSPI_AUTOMATIC_POLLING_MODE
 * @brief Constante dédiée à la fonction qspi_setMode().\n
 *        Définition de l'identifiant du mode 'AUTOMATIC_POLLING_MODE'.
 */

#define K_QSPI_AUTOMATIC_POLLING_MODE 0x02000000

/**
 * @def K_QSPI_MEMORY_MAPPED_MODE
 * @brief Constante dédiée à la fonction qspi_setMode().\n
 *        Définition de l'identifiant du mode 'MEMORY_MAPPED_MODE'.
 */

#define K_QSPI_MEMORY_MAPPED_MODE 0x03000000

/**
 *
 */

#endif
