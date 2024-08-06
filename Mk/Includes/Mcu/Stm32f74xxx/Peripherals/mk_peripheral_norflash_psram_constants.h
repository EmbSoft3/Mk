/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_norflash_psram_constants.h
* @brief Déclaration des constantes dédiées aux contrôleurs NORFLASH, PSRAM, SRAM et ROM.
* @date 16 oct. 2022
*
*/

#ifndef MK_PERIPHERAL_NORFLASH_PSRAM_CONSTANTS_H
#define MK_PERIPHERAL_NORFLASH_PSRAM_CONSTANTS_H

/**
 * @def K_NORFLASH_PSRAM_BANK1
 * @brief Adresse de base du registre FMC_BCR1.
 */

#define K_NORFLASH_PSRAM_BANK1 ( addr_t ) 0xA0000000

/**
 * @def K_NORFLASH_PSRAM_BANK2
 * @brief Adresse de base du registre FMC_BCR2.
 */

#define K_NORFLASH_PSRAM_BANK2 ( addr_t ) 0xA0000008

/**
 * @def K_NORFLASH_PSRAM_BANK3
 * @brief Adresse de base du registre FMC_BCR3.
 */

#define K_NORFLASH_PSRAM_BANK3 ( addr_t ) 0xA0000010

/**
 * @def K_NORFLASH_PSRAM_BANK4
 * @brief Adresse de base du registre FMC_BCR4.
 */

#define K_NORFLASH_PSRAM_BANK4 ( addr_t ) 0xA0000018

/**
 * @def K_NORFLASH_PSRAM_TYPE_READ
 * @brief Constante dédiée aux fonctions norflash_psram_setAccessMode()
 *        norflash_psram_setAddressPhases(), norflash_psram_setTurnaroundPhase() et
 *        norflash_psram_setDataPhase() \n
 *        Définition de l'identifiant du registre permettant de configurer
 *        les timings de lecture asynchrone.
 */

#define K_NORFLASH_PSRAM_TYPE_READ 0x00000001

/**
 * @def K_NORFLASH_PSRAM_TYPE_WRITE
 * @brief Constante dédiée aux fonctions norflash_psram_setAccessMode()
 *        norflash_psram_setAddressPhases(), norflash_psram_setTurnaroundPhase() et
 *        norflash_psram_setDataPhase() \n
 *        Définition de l'identifiant du registre permettant de configurer
 *        les timings d'écriture asynchrone.
 */

#define K_NORFLASH_PSRAM_TYPE_WRITE 0x00000041

/**
 * @def K_NORFLASH_PSRAM_MODE_A
 * @brief Constante dédiée à la fonction norflash_psram_setAccessMode(). \n
 *        Définition de l'identifiant du mode A.
 */

#define K_NORFLASH_PSRAM_MODE_A 0x00000000

/**
 * @def K_NORFLASH_PSRAM_MODE_B
 * @brief Constante dédiée à la fonction norflash_psram_setAccessMode(). \n
 *        Définition de l'identifiant du mode B.
 */

#define K_NORFLASH_PSRAM_MODE_B 0x10000000

/**
 * @def K_NORFLASH_PSRAM_MODE_C
 * @brief Constante dédiée à la fonction norflash_psram_setAccessMode(). \n
 *        Définition de l'identifiant du mode C.
 */

#define K_NORFLASH_PSRAM_MODE_C 0x20000000

/**
 * @def K_NORFLASH_PSRAM_MODE_D
 * @brief Constante dédiée à la fonction norflash_psram_setAccessMode(). \n
 *        Définition de l'identifiant du mode D.
 */

#define K_NORFLASH_PSRAM_MODE_D 0x30000000

/**
 * @def K_NORFLASH_PSRAM_SRAM
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryType(). \n
 *        Définition de l'identifiant du type de mémoire SRAM.
 */

#define K_NORFLASH_PSRAM_SRAM 0x00000000

/**
 * @def K_NORFLASH_PSRAM_PSRAM
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryType(). \n
 *        Définition de l'identifiant du type de mémoire PSRAM.
 */

#define K_NORFLASH_PSRAM_PSRAM 0x00000004

/**
 * @def K_NORFLASH_PSRAM_NORFLASH
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryType(). \n
 *        Définition de l'identifiant du type de mémoire NOR_FLASH.
 */

#define K_NORFLASH_PSRAM_NORFLASH 0x00000048

/**
 * @def K_NORFLASH_PSRAM_ONENANDFLASH
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryType(). \n
 *        Définition de l'identifiant du type de mémoire OneNAND_FLASH.
 */

#define K_NORFLASH_PSRAM_ONENANDFLASH 0x00000008

/**
 * @def K_NORFLASH_PSRAM_8BITS
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryBus(). \n
 *        Définition d'un identifiant permettant de configurer un bus de données de 8 bits.
 */

#define K_NORFLASH_PSRAM_8BITS 0x00000000

/**
 * @def K_NORFLASH_PSRAM_16BITS
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryBus(). \n
 *        Définition d'un identifiant permettant de configurer un bus de données de 16 bits.
 */

#define K_NORFLASH_PSRAM_16BITS 0x00000010

/**
 * @def K_NORFLASH_PSRAM_32BITS
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryBus(). \n
 *        Définition d'un identifiant permettant de configurer un bus de données de 32 bits.
 */

#define K_NORFLASH_PSRAM_32BITS 0x00000020

/**
 * @def K_NORFLASH_PSRAM_ENABLE_MULTIPLEXED_MODE
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryBus(). \n
 *        Définition d'un identifiant permettant d'activer le multiplexage du bus de
 *        données avec le bus d'adresse.
 */

#define K_NORFLASH_PSRAM_ENABLE_MULTIPLEXED_MODE 0x00000002

/**
 * @def K_NORFLASH_PSRAM_DISABLE_MULTIPLEXED_MODE
 * @brief Constante dédiée à la fonction norflash_psram_setMemoryBus(). \n
 *        Définition d'un identifiant permettant de désactiver le multiplexage du bus de
 *        données avec le bus d'adresse.
 */

#define K_NORFLASH_PSRAM_DISABLE_MULTIPLEXED_MODE 0x00000000

/**
 * @def K_NORFLASH_PSRAM_PAGE_SIZE_DISABLED
 * @brief Constante dédiée à la fonction norflash_psram_setPageSize(). \n
 *        Définition d'un identifiant permettant de désactiver la fonction de pagination des
 *        mémoires CRAM.
 */

#define K_NORFLASH_PSRAM_PAGE_SIZE_DISABLED 0x00000000

/**
 * @def K_NORFLASH_PSRAM_PAGE_SIZE_128_BYTES
 * @brief Constante dédiée à la fonction norflash_psram_setPageSize(). \n
 *        Définition d'un identifiant permettant de configurer une taille de page de 128 octets.
 *        Cette constante est dédiée aux mémoires CRAM.
 */

#define K_NORFLASH_PSRAM_PAGE_SIZE_128_BYTES 0x00010000

/**
 * @def K_NORFLASH_PSRAM_PAGE_SIZE_256_BYTES
 * @brief Constante dédiée à la fonction norflash_psram_setPageSize(). \n
 *        Définition d'un identifiant permettant de configurer une taille de page de 256 octets.
 *        Cette constante est dédiée aux mémoires CRAM.
 */

#define K_NORFLASH_PSRAM_PAGE_SIZE_256_BYTES 0x00020000

/**
 * @def K_NORFLASH_PSRAM_PAGE_SIZE_512_BYTES
 * @brief Constante dédiée à la fonction norflash_psram_setPageSize(). \n
 *        Définition d'un identifiant permettant de configurer une taille de page de 512 octets.
 *        Cette constante est dédiée aux mémoires CRAM.
 */

#define K_NORFLASH_PSRAM_PAGE_SIZE_512_BYTES 0x00030000

/**
 * @def K_NORFLASH_PSRAM_PAGE_SIZE_1024_BYTES
 * @brief Constante dédiée à la fonction norflash_psram_setPageSize(). \n
 *        Définition d'un identifiant permettant de configurer une taille de page de 1024 octets.
 *        Cette constante est dédiée aux mémoires CRAM.
 */

#define K_NORFLASH_PSRAM_PAGE_SIZE_1024_BYTES 0x00040000

/**
 * @def K_NORFLASH_PSRAM_NWAIT_ASSERTED_BEFORE_WAITSTATE
 * @brief Constante dédiée à la fonction norflash_psram_setSynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant de configurer quand le signal NWAIT est inséré sur le bus.
 *        Cette constante est dédiée au mode synchrone.
 */

#define K_NORFLASH_PSRAM_NWAIT_ASSERTED_BEFORE_WAITSTATE 0x00000000

/**
 * @def K_NORFLASH_PSRAM_NWAIT_ASSERTED_DURING_WAITSTATE
 * @brief Constante dédiée à la fonction norflash_psram_setSynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant de configurer quand le signal NWAIT est inséré sur le bus.
 *        Cette constante est dédiée au mode synchrone.
 */

#define K_NORFLASH_PSRAM_NWAIT_ASSERTED_DURING_WAITSTATE 0x00000800

/**
 * @def K_NORFLASH_PSRAM_ENABLE_WAITSTATE
 * @brief Constante dédiée à la fonction norflash_psram_setSynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant d'activer l'insertion d'un ou plusieurs WaitState
 *        après la période de latence.
 */

#define K_NORFLASH_PSRAM_ENABLE_WAITSTATE 0x00002000

/**
 * @def K_NORFLASH_PSRAM_DISABLE_WAITSTATE
 * @brief Constante dédiée à la fonction norflash_psram_setSynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant de désactiver l'insertion d'un ou plusieurs WaitState
 *        après la période de latence.
 */

#define K_NORFLASH_PSRAM_DISABLE_WAITSTATE 0x00000000

/**
 * @def K_NORFLASH_PSRAM_NWAIT_ACTIVE_LOW
 * @brief Constante dédiée à la fonction norflash_psram_setNWaitPolarity(). \n
 *        Définition d'un identifiant permettant de configurer la polarité du signal NWAIT.
 */

#define K_NORFLASH_PSRAM_NWAIT_ACTIVE_LOW 0x00000000

/**
 * @def K_NORFLASH_PSRAM_NWAIT_ACTIVE_HIGH
 * @brief Constante dédiée à la fonction norflash_psram_setNWaitPolarity(). \n
 *        Définition d'un identifiant permettant de configurer la polarité du signal NWAIT.
 */

#define K_NORFLASH_PSRAM_NWAIT_ACTIVE_HIGH 0x00000200

/**
 * @def K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS
 * @brief Constante dédiée aux fonctions norflash_psram_setReadOperation() et norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant de configurer les lecture/écriture en mode asynchrone.
 */

#define K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS 0x00000000

/**
 * @def K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS
 * @brief Constante dédiée aux fonctions norflash_psram_setReadOperation() et norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant de configurer les lecture/écriture en mode synchrone.
 */

#define K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS 0x00000001

/**
 * @def K_NORFLASH_PSRAM_ENABLE_WRITE_OPERATION
 * @brief Constante dédiée à la fonction norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant d'activer les transferts en écriture.
 */

#define K_NORFLASH_PSRAM_ENABLE_WRITE_OPERATION 0x00001000

/**
 * @def K_NORFLASH_PSRAM_DISABLE_WRITE_OPERATION
 * @brief Constante dédiée à la fonction norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant de désactiver les transferts en écriture.
 */

#define K_NORFLASH_PSRAM_DISABLE_WRITE_OPERATION 0x00000000

/**
 * @def K_NORFLASH_PSRAM_ENABLE_WRITE_FIFO
 * @brief Constante dédiée à la fonction norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant d'activer le FIFO d'écriture.
 */

#define K_NORFLASH_PSRAM_ENABLE_WRITE_FIFO 0x00000000

/**
 * @def K_NORFLASH_PSRAM_DISABLE_WRITE_FIFO
 * @brief Constante dédiée à la fonction norflash_psram_setWriteOperation(). \n
 *        Définition d'un identifiant permettant de désactiver le FIFO d'écriture.
 */

#define K_NORFLASH_PSRAM_DISABLE_WRITE_FIFO 0x00200000

/**
 * @def K_NORFLASH_PSRAM_ENABLE_NWAIT
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant d'activer le signal NWAIT durant les transferts asynchrones.
 */

#define K_NORFLASH_PSRAM_ENABLE_NWAIT 0x00008000

/**
 * @def K_NORFLASH_PSRAM_DISABLE_NWAIT
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant d'activer le signal NWAIT durant les transferts asynchrones.
 */

#define K_NORFLASH_PSRAM_DISABLE_NWAIT 0x00000000

/**
 * @def K_NORFLASH_PSRAM_ENABLE_CLOCK
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant d'activer le signal FMC_CLK durant les transferts asynchrones.
 */

#define K_NORFLASH_PSRAM_ENABLE_CLOCK 0x00100000

/**
 * @def K_NORFLASH_PSRAM_DISABLE_CLOCK
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant d'activer le signal FMC_CLK durant les transferts asynchrones.
 *        L'horloge est activée uniquement durant les transferts synchrones.
 */

#define K_NORFLASH_PSRAM_DISABLE_CLOCK 0x00000000

/**
 * @def K_NORFLASH_PSRAM_ENABLE_EXTENDED_TIMING
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant de réaliser une programmation indépendante des timings de lecture
 *        et d'écriture (cf. \ref K_NORFLASH_PSRAM_TYPE_READ et \ref K_NORFLASH_PSRAM_TYPE_WRITE).
 */

#define K_NORFLASH_PSRAM_ENABLE_EXTENDED_TIMING 0x00004000

/**
 * @def K_NORFLASH_PSRAM_ENABLE_EXTENDED_TIMING
 * @brief Constante dédiée à la fonction norflash_psram_setAsynchronousConfiguration(). \n
 *        Définition d'un identifiant permettant de réaliser une programmation commune des timings de lecture
 *        et d'écriture (cf. \ref K_NORFLASH_PSRAM_TYPE_READ).
 */

#define K_NORFLASH_PSRAM_DISABLE_EXTENDED_TIMING 0x00000000

/**
 *
 */

#endif


