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
* @file mk_micron_n25q512a_constants.h
* @brief Déclaration des constantes dédiées à la mémoire MICRON N25Q512A.
* @date 5 mai 2020
*+
*/

#ifndef MK_MICRON_N25Q512A_CONSTANTS_H
#define MK_MICRON_N25Q512A_CONSTANTS_H

/**
 * @def K_MK_MICRON_N25Q512A_SIZE
 * @brief Définition de la taille de la mémoire QSPI (en octets).
 */

#define K_MK_MICRON_N25Q512A_SIZE 0x04000000

/**
 * @def K_MK_MICRON_N25Q512A_SECTOR_NUMBER
 * @brief Définition du nombre de secteurs de la mémoire QSPI.
 */

#define K_MK_MICRON_N25Q512A_SECTOR_NUMBER 1024

/**
 * @def K_MK_MICRON_N25Q512A_SECTOR_SIZE
 * @brief Définition de la taille d'un secteur de la mémoire QSPI.
 */

#define K_MK_MICRON_N25Q512A_SECTOR_SIZE 0x10000

/**
 * @def K_MK_MICRON_N25Q512A_PAGE_SIZE
 * @brief Définition de la taille d'une page de la mémoire QSPI.
 */

#define K_MK_MICRON_N25Q512A_PAGE_SIZE 0x100

/**
 *
 */

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_ID
 * @brief Définition de l'instruction READ_ID.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ_ID 0x9E

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_STATUS
 * @brief Définition de l'instruction READ_STATUS.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ_STATUS 0x05

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_WRITE_STATUS
 * @brief Définition de l'instruction WRITE_STATUS.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_WRITE_STATUS 0x01

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION
 * @brief Définition de l'instruction READ_NON_VOLATILE_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION 0xB5

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION
 * @brief Définition de l'instruction WRITE_NON_VOLATILE_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION 0xB1

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION
 * @brief Définition de l'instruction READ_VOLATILE_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION 0x85

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION
 * @brief Définition de l'instruction WRITE_VOLATILE_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION 0x81

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION
 * @brief Définition de l'instruction READ_VOLATILE_ENHANCED_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION 0x65

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION
 * @brief Définition de l'instruction WRITE_VOLATILE_ENHANCED_CONFIGURATION.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION 0x61

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ
 * @brief Définition de l'instruction READ.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_READ 0x03

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_FAST_READ
 * @brief Définition de l'instruction FAST_READ.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_FAST_READ 0x0B

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_4BYTE_FAST_READ
 * @brief Définition de l'instruction 4BYTE_FAST_READ.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_4BYTE_FAST_READ 0x0C

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE
 * @brief Définition de l'instruction WRITE_ENABLE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE 0x06

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_ENTER_4BYTE_ADDRESS_MODE
 * @brief Définition de l'instruction ENTER_4BYTE_ADDRESS_MODE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_ENTER_4BYTE_ADDRESS_MODE 0xB7

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_EXIT_4BYTE_ADDRESS_MODE
 * @brief Définition de l'instruction EXIT_4BYTE_ADDRESS_MODE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_EXIT_4BYTE_ADDRESS_MODE 0xE9

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_ENABLE_RESET
 * @brief Définition de l'instruction RESET ENABLE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_ENABLE_RESET 0x66

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_RESET_MEMORY
 * @brief Définition de l'instruction RESET MEMORY.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_RESET_MEMORY 0x99

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_SECTOR_ERASE
 * @brief Définition de l'instruction SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_SECTOR_ERASE 0xD8

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_DIE_ERASE
 * @brief Définition de l'instruction SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_DIE_ERASE 0xC4

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_4BYTES_SECTOR_ERASE
 * @brief Définition de l'instruction 4BYTES SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_4BYTES_SECTOR_ERASE 0xDC

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_PAGE_PROGRAM
 * @brief Définition de l'instruction SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_PAGE_PROGRAM 0x02

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_PAGE_PROGRAM
 * @brief Définition de l'instruction SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_PAGE_PROGRAM 0x02

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_QUAD_INPUT_FAST_PROGRAM
 * @brief Définition de l'instruction SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_QUAD_INPUT_FAST_PROGRAM 0x32

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_4BYTES_PAGE_PROGRAM
 * @brief Définition de l'instruction 4BYTES SECTOR ERASE.
 */

#define K_MK_MICRON_N25Q512A_OPCODE_4BYTES_PAGE_PROGRAM 0x12

/**
 *
 */

/**
 * @def K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE
 * @brief Définition du nombre de dummy cycle durant la lecture d'un registre.
 */

#define K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE 0x00

/**
 * @def K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE
 * @brief Définition du nombre de dummy cycle durant les opérations de lecture et d'écriture (memory map).
 */

#define K_MK_MICRON_N25Q512A_DUMMY_CYCLE 0x01

/**
 * @def K_MK_MICRON_N25Q512A_TIMEOUT
 * @brief Définition du nombre de scrutation du registre de statut du périphérique QSPI
 *        suite à l'émission d'un mot sur le bus ou l'arrêt d'un transfert.
 */

#define K_MK_MICRON_N25Q512A_TIMEOUT 1024

/**
 * @def K_MK_MICRON_N25Q512A_MEMORY_TIMEOUT
 * @brief Définition du nombre de scrutation du registre de statut de la mémoire QSPI
 *         suite à la transmission d'une commande d'écriture ou d'effacement.
 */

#define K_MK_MICRON_N25Q512A_MEMORY_TIMEOUT 16384

/**
 * @def K_MK_MICRON_N25Q512A_OPCODE_READ_ID
 * @brief Définition de l'identifiant fabriquant de la mémoire.
 */

#define K_MK_MICRON_N25Q512A_MANUFACTURER_ID 0x20

/**
 *
 */

#endif

