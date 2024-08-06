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
 * @def MK_MICRON_N25Q512A_OPCODE_READ_ID
 * @brief Définition de l'instruction READ_ID.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ_ID 0x9E

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ_STATUS
 * @brief Définition de l'instruction READ_STATUS.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ_STATUS 0x05

/**
 * @def MK_MICRON_N25Q512A_OPCODE_WRITE_STATUS
 * @brief Définition de l'instruction WRITE_STATUS.
 */

#define MK_MICRON_N25Q512A_OPCODE_WRITE_STATUS 0x01

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION
 * @brief Définition de l'instruction READ_NON_VOLATILE_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ_NV_CONFIGURATION 0xB5

/**
 * @def MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION
 * @brief Définition de l'instruction WRITE_NON_VOLATILE_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_WRITE_NV_CONFIGURATION 0xB1

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION
 * @brief Définition de l'instruction READ_VOLATILE_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ_CONFIGURATION 0x85

/**
 * @def MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION
 * @brief Définition de l'instruction WRITE_VOLATILE_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_WRITE_CONFIGURATION 0x81

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION
 * @brief Définition de l'instruction READ_VOLATILE_ENHANCED_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ_ENHANCED_CONFIGURATION 0x65

/**
 * @def MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION
 * @brief Définition de l'instruction WRITE_VOLATILE_ENHANCED_CONFIGURATION.
 */

#define MK_MICRON_N25Q512A_OPCODE_WRITE_ENHANCED_CONFIGURATION 0x61

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ
 * @brief Définition de l'instruction READ.
 */

#define MK_MICRON_N25Q512A_OPCODE_READ 0x03

/**
 * @def MK_MICRON_N25Q512A_OPCODE_FAST_READ
 * @brief Définition de l'instruction FAST_READ.
 */

#define MK_MICRON_N25Q512A_OPCODE_FAST_READ 0x0B

/**
 * @def MK_MICRON_N25Q512A_OPCODE_4BYTE_FAST_READ
 * @brief Définition de l'instruction 4BYTE_FAST_READ.
 */

#define MK_MICRON_N25Q512A_OPCODE_4BYTE_FAST_READ 0x0C

/**
 * @def MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE
 * @brief Définition de l'instruction WRITE_ENABLE.
 */

#define MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE 0x06

/**
 * @def MK_MICRON_N25Q512A_OPCODE_ENTER_4BYTE_ADDRESS_MODE
 * @brief Définition de l'instruction ENTER_4BYTE_ADDRESS_MODE.
 */

#define MK_MICRON_N25Q512A_OPCODE_ENTER_4BYTE_ADDRESS_MODE 0xB7

/**
 * @def MK_MICRON_N25Q512A_OPCODE_EXIT_4BYTE_ADDRESS_MODE
 * @brief Définition de l'instruction EXIT_4BYTE_ADDRESS_MODE.
 */

#define MK_MICRON_N25Q512A_OPCODE_EXIT_4BYTE_ADDRESS_MODE 0xE9

/**
 * @def MK_MICRON_N25Q512A_OPCODE_ENABLE_RESET
 * @brief Définition de l'instruction RESET ENABLE.
 */

#define MK_MICRON_N25Q512A_OPCODE_ENABLE_RESET 0x66

/**
 * @def MK_MICRON_N25Q512A_OPCODE_RESET_MEMORY
 * @brief Définition de l'instruction RESET MEMORY.
 */

#define MK_MICRON_N25Q512A_OPCODE_RESET_MEMORY 0x99

/**
 *
 */

/**
 * @def MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE
 * @brief Définition du nombre de dummy cycle durant la lecture d'un registre.
 */

#define MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE 0x00

/**
 * @def MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE
 * @brief Définition du nombre de dummy cycle durant les opérations de lecture et d'écriture (memory map).
 */

#define MK_MICRON_N25Q512A_DUMMY_CYCLE 0x01

/**
 * @def K_MICRON_N25Q512A_TIMEOUT
 * @brief Définition du nombre de scrutation du registre de statuts QSPI suite à l'émission d'un mot
 *        sur le bus QSPI ou l'arrêt d'un transfert.
 */

#define K_MICRON_N25Q512A_TIMEOUT 1024

/**
 * @def MK_MICRON_N25Q512A_OPCODE_READ_ID
 * @brief Définition de l'identifiant fabriquant de la mémoire.
 */

#define MK_MICRON_N25Q512A_MANUFACTURER_ID 0x20

/**
 *
 */

#endif

