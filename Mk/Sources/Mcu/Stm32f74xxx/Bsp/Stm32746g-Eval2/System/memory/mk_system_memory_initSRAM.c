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
* @file mk_system_memory_initSRAM.c
* @brief Définition de la fonction mk_system_memory_initSRAM.
* @date 18 oct. 2022
*
*/

#include "mk_system_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_system_memory_initSRAM ( void )
{
   /* Désactivation de la bank dédiée à la mémoire SRAM */
   norflash_psram_disableBank ( K_NORFLASH_PSRAM_BANK3 );

   /* Configuration du type de mémoire connectée à la bank */
   norflash_psram_setMemoryType ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_SRAM );

   /* Configuration du format du bus mémoire */
   norflash_psram_setMemoryBus ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_16BITS, K_NORFLASH_PSRAM_DISABLE_MULTIPLEXED_MODE );

   /* Configuration de la polarité du signal NWAIT (non utilisé) */
   norflash_psram_setNWaitPolarity ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_NWAIT_ACTIVE_LOW );

   /* Désactivation de la fonction de pagination des mémoires CRAM */
   norflash_psram_setPageSize ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_PAGE_SIZE_DISABLED );

   /* Configuration du type des opérations de lecture */
   norflash_psram_setReadOperation ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS );

   /* Configuration du type des opérations d'écriture */
   norflash_psram_setWriteOperation ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_ENABLE_WRITE_OPERATION,
                                      K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS, K_NORFLASH_PSRAM_ENABLE_WRITE_FIFO  );

   /* Configuration du mode asynchrone */
   /* Pas de signal NWAIT et CLK */
   /* Mode étendu désactivé (fonctionnement en mode 1) */
   norflash_psram_setAsynchronousConfiguration ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_DISABLE_NWAIT,
                                                 K_NORFLASH_PSRAM_DISABLE_CLOCK, K_NORFLASH_PSRAM_DISABLE_EXTENDED_TIMING );

   /* Configuration des attributs du mode synchrone (non utilisé) */
   norflash_psram_setSynchronousConfiguration ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_NWAIT_ASSERTED_BEFORE_WAITSTATE,
                                                K_NORFLASH_PSRAM_DISABLE_WAITSTATE );

   /* Configuration du mode d'accès A */
   norflash_psram_setAccessMode ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_TYPE_READ, K_NORFLASH_PSRAM_MODE_A );

   /* Configuration des timings des transferts */
   /* Freq ( HCLK ) = 216 MHz */

   /* Configuration de la fréquence Freq (FMC_CLK) à 108MHz - 2 Cycles (valeur 1) */
   /* Timing non utilisé pour ce type de mémoire */
   norflash_psram_setClockSpeed ( K_NORFLASH_PSRAM_BANK3, 1 );

   /* Configuration du nombre de cycles de latence avant de lire ou écire les données. */
   /* 2 cycles à Freq (FMC_CLK) - (valeur 0). */
   /* Timing non utilisé pour ce type de mémoire */
   norflash_psram_setDataLatency ( K_NORFLASH_PSRAM_BANK3, 0 );

   /* Configuration du délai entre deux transactions */
   /* 0 cycles HCLK */
   norflash_psram_setTurnaroundPhase ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_TYPE_READ, 0 );

   /* Configuration de la durée de la phase de données */
   /* 2 cycles à Freq (HCLK) */
   norflash_psram_setDataPhase ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_TYPE_READ, 2 );

   /* Configuration de la durée de la phase de données */
   /* 2 cycles à Freq (HCLK) pour la phase Setup, 0 cycle pour la phase Hold (timing non utilisé). */
   norflash_psram_setAddressPhases ( K_NORFLASH_PSRAM_BANK3, K_NORFLASH_PSRAM_TYPE_READ, 2, 0 );

   /* Activation de la bank dédiée à la mémoire SRAM */
   norflash_psram_enableBank ( K_NORFLASH_PSRAM_BANK3 );

   /* Retour */
   return;
}

