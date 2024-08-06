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
* @file mk_mmc_cmd_constants.h
* @brief Déclaration des constantes dédiées aux commandes SD/MMC.
* @date 4 juil. 2020
*
*/

#ifndef MK_MMC_CMD_CONSTANTS_H
#define MK_MMC_CMD_CONSTANTS_H

/**
 * @def K_MK_MMC_TIMEOUT
 * @brief Définition de la durée [en ms] après laquelle le gestionnaire de communication
 *        MMC considère l'absence de réponse du périphérique.
 */

#define K_MK_MMC_TIMEOUT 64

/**
 * @def K_MK_MMC_TIMEOUT_COUNT
 * @brief Définition du nombre de réémission effectuée suite à la détection d'une erreur.
 */

#define K_MK_MMC_TIMEOUT_COUNT 16

/**
 * @def K_MK_MMC_FREQUENCY_MULTIPLIER
 * @brief Définition d'une constante permettant de calibrer le timeout MMC en [ms].
 */

#define K_MK_MMC_FREQUENCY_MULTIPLIER 4800000

/**
 *
 */

/**
 * @def K_MK_MMC_CRC_BYPASS_ENABLED
 * @brief Définition d'un drapeau empéchant la réémission d'une commande dans le cas d'une
 *        erreur de CRC.
 */

#define K_MK_MMC_CRC_BYPASS_ENABLED 0

/**
 * @def K_MK_MMC_CRC_BYPASS_DISABLED
 * @brief Définition d'un drapeau autorisant de réémission une commande dans le cas d'une
 *        erreur de CRC.
 */

#define K_MK_MMC_CRC_BYPASS_DISABLED 1

/**
 *
 */

/**
 * @def K_MK_MMC_CID_SIZE
 * @brief Définition de la taille du CID [en multiple de mots 32bits].
 */

#define K_MK_MMC_CID_SIZE 4

/**
 * @def K_MK_MMC_ARBITRARY_PATTERN
 * @brief Définition de la valeur du pattern présent dans la commande SEND_INTERFACE_CONDITION (CMD8).
 *        Cette valeur est arbitraire.
 */

#define K_MK_MMC_ARBITRARY_PATTERN 0xAA

/**
 * @def K_MK_MMC_VOLTAGE_RANGE_2V7_TO_3V6
 * @brief Définition de la valeur du champ VHS présent dans la commande SEND_INTERFACE_CONDITION (CMD8).
 */

#define K_MK_MMC_VOLTAGE_RANGE_2V7_TO_3V6 1

/**
 *
 */

/**
 * @def K_MK_MMC_BUSY_BIT
 * @brief Définition de la position du bit 'BUSY' dans le registre OCR du média.
 */

#define K_MK_MMC_BUSY_BIT 0x80000000

/**
 * @def K_MK_MMC_HCS_BIT
 * @brief Définition de la position du bit 'HCS' dans le registre OCR du média.
 */

#define K_MK_MMC_HCS_BIT 0x40000000

/**
 * @def K_MK_MMC_VOLTAGE_RANGE
 * @brief Définition de la valeur du champ 'VOLTAGE_RANGE' dans le registre OCR du média.
 */

#define K_MK_MMC_VOLTAGE_RANGE 0x003C0000

/**
 *
 */

/**
 * @def K_MK_MMC_ERROR_MASK
 * @brief Définition d'un masque permettant d'adresser les erreurs du registre de statut du média.
 */

#define K_MK_MMC_ERROR_MASK 0xFDF90088

/**
 *
 */

/**
 * @def K_MK_MMC_STATUS_BLOCK_SIZE
 * @brief Définition de la taille du bloc de données contenant le registre de statut de la carte.
 *        La formule est la suivante :\n
 *        StatusSize = ( 1 << K_MK_MMC_STATUS_BLOCK_SIZE ) = 64 octets.
 */

#define K_MK_MMC_STATUS_BLOCK_SIZE 6

/**
 * @def K_MK_MMC_DEFAULT_BLOCK_LENGTH
 * @brief Définition de la longueur par défaut d'un bloc de données. La formule est la suivante : \n
 *        LENGTH = ( 1 << K_MK_MMC_DEFAULT_BLOCK_LENGTH )
 */

#define K_MK_MMC_DEFAULT_BLOCK_LENGTH 9

/**
 *
 */

/**
 * @def K_MK_MMC_DEFAULT_SDV1_ADDRESS_MULTIPLIER
 * @brief Définition du facteur de multiplication utilisé pour adresser les média de version 1.
 */

#define K_MK_MMC_DEFAULT_SDV1_ADDRESS_MULTIPLIER 9

/**
 * @def K_MK_MMC_DEFAULT_SDV2_ADDRESS_MULTIPLIER
 * @brief Définition du facteur de multiplication utilisé pour adresser les média de version 2.
 */

#define K_MK_MMC_DEFAULT_SDV2_ADDRESS_MULTIPLIER 0

/**
 * @def K_MK_MMC_DEFAULT_SIZE_MULTIPLIER
 * @brief Définition du facteur de multiplication utilisé pour déterminer la taille d'un média de version 2.
 */

#define K_MK_MMC_DEFAULT_SIZE_MULTIPLIER 512000

/**
 *
 */

/**
 * @def K_MK_MMC_MAX_TRANSFER_SIZE
 * @brief Définition de la taille maximale d'un transfert de données. La formule est la suivante : \n
 *        SIZE = (1 << K_MK_MMC_MAX_TRANSFER_SIZE ) = 131072 octets
 */

#define K_MK_MMC_MAX_TRANSFER_SIZE 17

/**
 *
 */

/**
 * @def K_MK_MMC_IDLE_TO_READY_TIMEOUT
 * @brief Définition de la durée du timeout [en multiple de '5ms'] où la tâche de gestion des périphériques SD/MMC attend
          le passage de l'état 'IDLE' à l'état 'READY'.
 */

#define K_MK_MMC_IDLE_TO_READY_TIMEOUT 200

/**
 *
 */

/**
 * @def K_MK_MMC_PASSWORD_MAX_SIZE
 * @brief Définition de la taille maximale du mot de passe du média [en octets].
 */

#define K_MK_MMC_PASSWORD_MAX_SIZE 16

/**
 *
 */

#endif

