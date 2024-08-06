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
* @file mk_system_memory.h
* @brief Déclaration des fonctions dédiées aux mémoires externes.
* @date 24 févr. 2019
*
*/

#ifndef MK_SYSTEM_MEMORY_H
#define MK_SYSTEM_MEMORY_H

/**
 * @fn void mk_system_memory_initGPIO ( void );
 * @brief Cette fonction initialise les broches GPIO des mémoires externes.
 *
 * @return Sans objet.
 *
 */

void mk_system_memory_initGPIO ( void );

/**
 * @fn void mk_system_memory_initSRAM ( void );
 * @brief Cette fonction initialise la ou les mémoires externes de type SRAM.
 *
 * @return Sans objet.
 *
 */

void mk_system_memory_initSRAM ( void );

/**
 * @fn uint32_t mk_system_memory_initSDRAM ( void );
 * @brief Cette fonction initialise la ou les mémoires externes de type SDRAM.
 * @return Cette fonction retourne la valeur \ref K_SDRAM_OK si l'initialisation a réussi, sinon la valeur \ref K_SDRAM_BUSY.
 *
 */

uint32_t mk_system_memory_initSDRAM ( void );

/**
 * @fn uint32_t mk_system_memory_initQSPI ( void );
 * @brief Cette fonction initialise la ou les mémoires externes de type QSPI.
 *
 * @param[in] p_mode Ce paramètre indique si la mémoire doit être initialisée en mode 1 fil
 *                   (\ref K_QSPI_INSTRUCTION_SINGLE_MODE) ou 4 fils (\ref K_QSPI_INSTRUCTION_QUAD_MODE).
 *
 * @return Cette fonction retourne la valeur \ref K_QSPI_OK si l'initialisation a réussi, sinon la valeur \ref K_QSPI_KO.
 *
 */

uint32_t mk_system_memory_initQSPI ( uint32_t p_mode );

/**
 * @fn void mk_system_memory_init ( void );
 * @brief Cette fonction initialise l'ensemble des mémoires externes.
 * @return Cette fonction retourne la valeur \ref K_SYS_OK si l'initialisation a réussi, sinon les valeur \ref K_SYS_ERROR_SDRAM
 *         ou \ref K_SYS_ERROR_QSPI.
 *
 */

T_sysCode mk_system_memory_init ( void );

/**
 *
 */

#endif


