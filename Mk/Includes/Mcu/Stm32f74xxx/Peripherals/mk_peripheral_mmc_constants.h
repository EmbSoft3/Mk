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
* @file mk_peripheral_mmc_constants.h
* @brief Déclaration des constantes dédiées au périphérique SDMMC.
* @date 31 mai 2020
*
*/

#ifndef MK_PERIPHERAL_MMC_CONSTANTS_H
#define MK_PERIPHERAL_MMC_CONSTANTS_H

/**
 * @def K_MMC_POWER
 * @brief Adresse du registre MMC_POWER.
 */

#define K_MMC_POWER ( addr_t ) 0x40012C00

/**
 * @def K_MMC_CLKCR
 * @brief Adresse du registre MMC_CLKCR.
 */

#define K_MMC_CLKCR ( addr_t ) 0x40012C04

/**
 * @def K_MMC_ARG
 * @brief Adresse du registre MMC_ARG.
 */

#define K_MMC_ARG ( addr_t ) 0x40012C08

/**
 * @def K_MMC_CMD
 * @brief Adresse du registre MMC_CMD.
 */

#define K_MMC_CMD ( addr_t ) 0x40012C0C

/**
 * @def K_MMC_RESPCMD
 * @brief Adresse du registre MMC_RESPCMD.
 */

#define K_MMC_RESPCMD ( addr_t ) 0x40012C10

/**
 * @def K_MMC_RESP1
 * @brief Adresse du registre MMC_RESP1.
 */

#define K_MMC_RESP1 ( addr_t ) 0x40012C14

/**
 * @def K_MMC_RESP2
 * @brief Adresse du registre MMC_RESP2.
 */

#define K_MMC_RESP2 ( addr_t ) 0x40012C18

/**
 * @def K_MMC_RESP3
 * @brief Adresse du registre MMC_RESP3.
 */

#define K_MMC_RESP3 ( addr_t ) 0x40012C1C

/**
 * @def K_MMC_RESP4
 * @brief Adresse du registre MMC_RESP4.
 */

#define K_MMC_RESP4 ( addr_t ) 0x40012C20

/**
 * @def K_MMC_DTIMER
 * @brief Adresse du registre MMC_DTIMER.
 */

#define K_MMC_DTIMER ( addr_t ) 0x40012C24

/**
 * @def K_MMC_DLEN
 * @brief Adresse du registre MMC_DLEN.
 */

#define K_MMC_DLEN ( addr_t ) 0x40012C28

/**
 * @def K_MMC_DCTRL
 * @brief Adresse du registre MMC_DCTRL.
 */

#define K_MMC_DCTRL ( addr_t ) 0x40012C2C

/**
 * @def K_MMC_DCOUNT
 * @brief Adresse du registre MMC_DCOUNT.
 */

#define K_MMC_DCOUNT ( addr_t ) 0x40012C30

/**
 * @def K_MMC_STA
 * @brief Adresse du registre MMC_STA.
 */

#define K_MMC_STA ( addr_t ) 0x40012C34

/**
 * @def K_MMC_ICR
 * @brief Adresse du registre MMC_ICR.
 */

#define K_MMC_ICR ( addr_t ) 0x40012C38

/**
 * @def K_MMC_MASK
 * @brief Adresse du registre MMC_MASK.
 */

#define K_MMC_MASK ( addr_t ) 0x40012C3C

/**
 * @def K_MMC_FIFOCNT
 * @brief Adresse du registre MMC_FIFOCNT.
 */

#define K_MMC_FIFOCNT ( addr_t ) 0x40012C48

/**
 * @def K_MMC_FIFO
 * @brief Adresse du registre MMC_FIFO.
 */

#define K_MMC_FIFO ( addr_t ) 0x40012C80

/**
 *
 */

/**
 * @def K_MMC_DATABUS_SIZE_1PIN
 * @brief Constante dédiée à la fonction mmc_setDataBusSize().\n
 *        Configuration du bus de données en mode 1 fil.
 */

#define K_MMC_DATABUS_SIZE_1PIN 0x00000000

/**
 * @def K_MMC_DATABUS_SIZE_4PINS
 * @brief Constante dédiée à la fonction mmc_setDataBusSize().\n
 *        Configuration du bus de données en mode 4 fils.
 */

#define K_MMC_DATABUS_SIZE_4PINS 0x00000001

/**
 * @def K_MMC_DATABUS_SIZE_4PINS
 * @brief Constante dédiée à la fonction mmc_setDataBusSize().\n
 *        Configuration du bus de données en mode 8 fils.
 */

#define K_MMC_DATABUS_SIZE_8PINS 0x00000002

/**
 *
 */

/**
 * @def K_MMC_CLOCK_RISING_EDGE
 * @brief Constante dédiée à la fonction mmc_setSampleEdge().\n
 *        Configuration du point d'échantillonage des signaux sur le front montant de l'horloge.
 */

#define K_MMC_CLOCK_RISING_EDGE 0x00000000

/**
 * @def K_MMC_CLOCK_FALLING_EDGE
 * @brief Constante dédiée à la fonction mmc_setSampleEdge().\n
 *        Configuration du point d'échantillonage des signaux sur le front descendant de l'horloge.
 */

#define K_MMC_CLOCK_FALLING_EDGE 0x00002000

/**
 *
 */

/**
 * @def K_MMC_FLAG_ALL
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition d'un identifiant adressant tous les drapeaux d'interruption.
 */

#define K_MMC_FLAG_ALL 0x007FFFFF

/**
 * @def K_MMC_FLAG_SDIO_INTERRUPT
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption SDIO.
 */

#define K_MMC_FLAG_SDIO_INTERRUPT 0x00400000

/**
 * @def K_MMC_FLAG_RXDATA_AVAILABLE
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption RXDATA_AVAILABLE.
 */

#define K_MMC_FLAG_RXDATA_AVAILABLE 0x00200000

/**
 * @def K_MMC_FLAG_TXDATA_AVAILABLE
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption TXDATA_AVAILABLE.
 */

#define K_MMC_FLAG_TXDATA_AVAILABLE 0x00100000

/**
 * @def K_MMC_FLAG_RXFIFO_EMPTY
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption RXFIFO_EMPTY.
 */

#define K_MMC_FLAG_RXFIFO_EMPTY 0x00080000

/**
 * @def K_MMC_FLAG_TXFIFO_EMPTY
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption TXFIFO_EMPTY.
 */

#define K_MMC_FLAG_TXFIFO_EMPTY 0x00040000

/**
 * @def K_MMC_FLAG_TXFIFO_EMPTY
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption RXFIFO_FULL.
 */

#define K_MMC_FLAG_RXFIFO_FULL 0x00020000

/**
 * @def K_MMC_FLAG_TXFIFO_FULL
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption TXFIFO_FULL.
 */

#define K_MMC_FLAG_TXFIFO_FULL 0x00010000

/**
 * @def K_MMC_FLAG_RXFIFO_HALF_FULL
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption RXFIFO_HALF_FULL.
 */

#define K_MMC_FLAG_RXFIFO_HALF_FULL 0x00008000

/**
 * @def K_MMC_FLAG_TXFIFO_HALF_EMPTY
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption TXFIFO_HALF_EMPTY.
 */

#define K_MMC_FLAG_TXFIFO_HALF_EMPTY 0x00004000

/**
 * @def K_MMC_FLAG_RXDATA_TRANSFER_IN_PROGRESS
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption RXDATA_TRANSFER_IN_PROGRESS.
 */

#define K_MMC_FLAG_RXDATA_TRANSFER_IN_PROGRESS 0x00002000

/**
 * @def K_MMC_FLAG_TXDATA_TRANSFER_IN_PROGRESS
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption TXDATA_TRANSFER_IN_PROGRESS.
 */

#define K_MMC_FLAG_TXDATA_TRANSFER_IN_PROGRESS 0x00001000

/**
 * @def K_MMC_FLAG_CMD_TRANSFER_IN_PROGRESS
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt() et
 *        mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_TRANSFER_IN_PROGRESS.
 */

#define K_MMC_FLAG_CMD_TRANSFER_IN_PROGRESS 0x00000800

/**
 * @def K_MMC_FLAG_DATA_BLOCK_TRANSFERED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption DATA_BLOCK_TRANSFERED.
 * @note  Cette interruption est déclenchée lorsque le contrôle du CRC est OK.
 */

#define K_MMC_FLAG_DATA_BLOCK_TRANSFERED 0x00000400

/**
 * @def K_MMC_FLAG_START_BIT_NOT_DETECTED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption START_BIT_NOT_DETECTED.
 */

#define K_MMC_FLAG_START_BIT_NOT_DETECTED 0x00000200

/**
 * @def K_MMC_FLAG_DATA_COUNTER_REACHED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption DATA_COUNTER_REACHED.
 * @note  Cette interruption est déclenchée lorsque la quantité de données configurée avec la
 *        fonction \ref mmc_getDataCount a été transférée.
 */

#define K_MMC_FLAG_DATA_COUNTER_REACHED 0x00000100

/**
 * @def K_MMC_FLAG_CMD_TRANSMITTED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_TRANSMITTED.
 */

#define K_MMC_FLAG_CMD_TRANSMITTED 0x00000080

/**
 * @def K_MMC_FLAG_CMD_RESPONSE_RECEIVED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_RESPONSE_RECEIVED.
 */

#define K_MMC_FLAG_CMD_RESPONSE_RECEIVED 0x00000040

/**
 * @def K_MMC_FLAG_RXFIFO_OVERRUN
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_RXFIFO_OVERRUN.
 */

#define K_MMC_FLAG_RXFIFO_OVERRUN 0x00000020

/**
 * @def K_MMC_FLAG_TXFIFO_UNDERRUN
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_TXFIFO_UNDERRUN.
 */

#define K_MMC_FLAG_TXFIFO_UNDERRUN 0x00000010

/**
 * @def K_MMC_FLAG_DATA_TIMEOUT
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption DATA_TIMEOUT.
 * @note  Cette interruption est déclenchée lorsque la durée configurée avec la fonction
 *        mmc_setTimeout() est arrivée à échéance.
 */

#define K_MMC_FLAG_DATA_TIMEOUT 0x00000008

/**
 * @def K_MMC_FLAG_DATA_TIMEOUT
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_RESPONSE_TIMEOUT.
 * @note  La durée du timeout pour cette interruption est fixe et vaut 64 cycles de la
 *        broche d'horloge.
 */

#define K_MMC_FLAG_CMD_RESPONSE_TIMEOUT 0x00000004

/**
 * @def K_MMC_FLAG_DATA_BLOCK_FAILED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption DATA_BLOCK_FAILED.
 * @note  Cette interruption indique qu'un bloc de données a été reçu mais que les
 *        CRC calculés et transportés sont différents.
 */

#define K_MMC_FLAG_DATA_BLOCK_FAILED 0x00000002

/**
 * @def K_MMC_FLAG_CMD_RESPONSE_FAILED
 * @brief Constante dédiée aux fonctions mmc_enableInterrupt(), mmc_disableInterrupt(),
 *        mmc_getStatus() et mmc_clearStatus().\n
 *        Définition de l'identifiant de l'interruption CMD_RESPONSE_FAILED.
 * @note  Cette interruption indique qu'une réponse a été reçue mais que les
 *        CRC calculés et transportés sont différents.
 */

#define K_MMC_FLAG_CMD_RESPONSE_FAILED 0x00000001

/**
 *
 */

/**
 * @def K_MMC_READ_WAIT_D2
 * @brief Constante dédiée à la fonction mmc_enableSDIO().\n
 *        Activation du mode 'ReadWait' avec pilotage de la broche de controle D2.
 * @warning Cette constante ne peut être utilisée qu'avec les médias de type SDIO.
 *
 */

#define K_MMC_READ_WAIT_D2 0x00000000

/**
 * @def K_MMC_READ_WAIT_CLK
 * @brief Constante dédiée à la fonction mmc_enableSDIO().\n
 *        Activation du mode 'ReadWait' avec pilotage de la broche de controle CLK.
 * @warning Cette constante ne peut être utilisée qu'avec les médias de type SDIO.
 *
 */

#define K_MMC_READ_WAIT_CLK 0x00000400

/**
 *
 */

/**
 * @def K_MMC_BLOCK_SIZE_1BYTE
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 1 octet.
 */

#define K_MMC_BLOCK_SIZE_1BYTE 0x00000000

/**
 * @def K_MMC_BLOCK_SIZE_2BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 2 octets.
 */

#define K_MMC_BLOCK_SIZE_2BYTES 0x00000001

/**
 * @def K_MMC_BLOCK_SIZE_4BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 4 octets.
 */

#define K_MMC_BLOCK_SIZE_4BYTES 0x00000002

/**
 * @def K_MMC_BLOCK_SIZE_8BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 8 octets.
 */

#define K_MMC_BLOCK_SIZE_8BYTES 0x00000003

/**
 * @def K_MMC_BLOCK_SIZE_16BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 16 octets.
 */

#define K_MMC_BLOCK_SIZE_16BYTES 0x00000004

/**
 * @def K_MMC_BLOCK_SIZE_32BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 32 octets.
 */

#define K_MMC_BLOCK_SIZE_32BYTES 0x00000005

/**
 * @def K_MMC_BLOCK_SIZE_64BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 64 octets.
 */

#define K_MMC_BLOCK_SIZE_64BYTES 0x00000006

/**
 * @def K_MMC_BLOCK_SIZE_128BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 128 octets.
 */

#define K_MMC_BLOCK_SIZE_128BYTES 0x00000007

/**
 * @def K_MMC_BLOCK_SIZE_256BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 256 octets.
 */

#define K_MMC_BLOCK_SIZE_256BYTES 0x00000008

/**
 * @def K_MMC_BLOCK_SIZE_512BYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 512 octets.
 */

#define K_MMC_BLOCK_SIZE_512BYTES 0x00000009

/**
 * @def K_MMC_BLOCK_SIZE_1KBYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 1024 octets.
 */

#define K_MMC_BLOCK_SIZE_1KBYTES 0x0000000A

/**
 * @def K_MMC_BLOCK_SIZE_2KBYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 2048 octets.
 */

#define K_MMC_BLOCK_SIZE_2KBYTES 0x0000000B

/**
 * @def K_MMC_BLOCK_SIZE_4KBYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 4096 octets.
 */

#define K_MMC_BLOCK_SIZE_4KBYTES 0x0000000C

/**
 * @def K_MMC_BLOCK_SIZE_8KBYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 8192 octets.
 */

#define K_MMC_BLOCK_SIZE_8KBYTES 0x0000000D

/**
 * @def K_MMC_BLOCK_SIZE_16KBYTES
 * @brief Constante dédiée à la fonction mmc_setBlockSize().\n
 *        Configuration de la taille d'un bloc de données : 16384 octets.
 */

#define K_MMC_BLOCK_SIZE_16KBYTES 0x0000000E

/**
 *
 */

/**
 * @def K_MMC_DIRECTION_CONTROLLER_TO_CARD
 * @brief Constante dédiée à la fonction mmc_setDirection().\n
 *        Configuration d'un transfert de type sortant.
 */

#define K_MMC_DIRECTION_CONTROLLER_TO_CARD 0x00000000

/**
 * @def K_MMC_DIRECTION_CARD_TO_CONTROLLER
 * @brief Constante dédiée à la fonction mmc_setDirection().\n
 *        Configuration d'un transfert de type entrant.
 */

#define K_MMC_DIRECTION_CARD_TO_CONTROLLER 0x00000002

/**
 *
 */

/**
 * @def K_MMC_SUSPEND_COMMAND
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Configuration d'une commande de type 'Suspend'.
 * @warning Cette constante ne peut être utilisée qu'avec les médias de type SDIO.
 *
 */

#define K_MMC_SUSPEND_COMMAND 0x00000800

/**
 * @def K_MMC_NO_RESPONSE
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Configuration du type de réponse attendue suite à la transmission d'une commande.
 *        Cette constante indique qu'aucune réponse n'est requise.
 */

#define K_MMC_NO_RESPONSE 0x00000000

/**
 * @def K_MMC_SHORT_RESPONSE
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Configuration du type de réponse attendue suite à la transmission d'une commande.
 *        Cette constante indique qu'une réponse de type SHORT est requise.
 */

#define K_MMC_SHORT_RESPONSE 0x00000040

/**
 * @def K_MMC_LONG_RESPONSE
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Configuration du type de réponse attendue suite à la transmission d'une commande.
 *        Cette constante indique qu'une réponse de type LONG est requise.
 */

#define K_MMC_LONG_RESPONSE 0x000000C0

/**
 * @def K_MMC_OPT_STATE_MACHINE
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Activation de la machine à état intégrée au périphérique lors du prochain transfert SD/MMC.
 */

#define K_MMC_OPT_STATE_MACHINE 0x00000400

/**
 * @def K_MMC_OPT_NO_CMD_TIMEOUT
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Désactivation de la fonctionnalité 'Commande-Timeout' utilisée par la machine à état intégrée
 *        au périphérique MMC.
 */

#define K_MMC_OPT_NO_CMD_TIMEOUT 0x00000100

/**
 * @def K_MMC_OPT_STREAM_MODE
 * @brief Constante dédiée à la fonction mmc_setCommand().\n
 *        Cette constante n'est utilisable que lorsque le mode 'Stream' est actif. Elle indique
 *        au périphérique MMC d'attendre la fin du transfert de données en cours avant de transmettre
 *        une nouvelle commande. Le mode 'Stream' est activable par le biais de la fonction
 *        mmc_enableStreamMode().
 */

#define K_MMC_OPT_STREAM_MODE 0x00000200

/**
 *
 */

#endif

