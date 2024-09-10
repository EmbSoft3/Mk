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
* @file mk_system_memory_initSDRAM.c
* @brief Définition de la fonction mk_system_memory_initSDRAM.
* @date 24 févr. 2019
*
*/

#include "mk_system_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_system_memory_initSDRAMFMC ( void )
{
   /* Configuration de la fréquence de la broche SDCLK à 108Mhz - 166MHz max */
   /* pour la mémoire IS42S32800G-6)  */
   /* Freq ( SDCLK ) = Freq ( HCLK ) / DIVn */
   sdram_setClockPrescaler ( K_SDRAM_PRESCALER_DIV2 );

   /* Activation du mode burst et configuration du nombre de 'Waitstate' */
   /* après la latence CAS */
   sdram_enableBurstMode ( );
   sdram_setReadLatency ( K_SDRAM_CAS_TO_READ_NOCLOCK );

   /* Désactivation de la protection en écriture */
   sdram_disableWriteProtection ( K_SDRAM_BANK1 );

   /* Configuration des WaitState entre commandes. Les données internes du */
   /* datasheet de la mémoire IS42S32800G-6 sont utilisées. */
   /* Activate to Read/Write - TRCD */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_ROW_TO_COLUMN, 2 ); /* 2 min */
   /* Precharge to Another - TRP */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_ROW_PRECHARGE, 1 );
   /* Write to Precharge - TWR */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_RECOVERY, 2 ); /* 2 min */
   /* Refresh to Activate and Refresh to Refresh - TRC */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_ROW_CYCLE, 6 ); /* 6 cyles min */
   /* Self-Refresh Minimum Period - TRAS */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_SELF_REFRESH_TIME, 1 );
   /* Self-Refresh Exit To Activate - TXSR */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_EXIT_SELF_REFRESH, 1 );
   /* LoadMode To Activate - TMRD */
   sdram_setMemoryCycle ( K_SDRAM_BANK1, K_SDRAM_LOAD_MODE_REGISTER, 1 );

   /* Configuration du nombre de 'bank' internes et de la latence CAS */
   sdram_setCASLatency ( K_SDRAM_BANK1, K_SDRAM_CAS_LATENCY_2CLOCK ); /* 2 CLOCK min */
   sdram_setBankNumber ( K_SDRAM_BANK1, K_SDRAM_FOUR_INTERNAL_BANKS );

   /* Configuration du bus de données et du bus d'adresse */
   sdram_setDataBusWidth ( K_SDRAM_BANK1, K_SDRAM_DATABUS_16BITS );
   sdram_setAddressBusWidth ( K_SDRAM_BANK1, K_SDRAM_ADDRESS_ROW_12BITS, K_SDRAM_ADDRESS_COLUMN_8BITS );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_system_memory_initializationSequence ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Activation de l'horloge */
   l_result = sdram_enableClock ( K_SDRAM_BANK1_FLAG );

   /* Attente 1ms (100 µs min) */
   mk_utils_waitus ( 1000 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_SDRAM_OK )
   {
      /* Transmission des commandes 'Precharge All' et 'Auto Refresh' */
      l_result = sdram_sendPall ( K_SDRAM_BANK1_FLAG );

      /* Transmission de la commande de rafraichissement */
      l_result |= sdram_sendAutoRefresh ( K_SDRAM_BANK1_FLAG, 8 ); /* 2 cycles min */

      /* Configuration du "Load Mode Register" de la SDRAM */
      l_result |= sdram_sendLoadModeRegister ( K_SDRAM_BANK1_FLAG, K_MK_SDRAM_LOADMODE_REGISTER_VALUE );

      /* Configuration de la fréquence de rafraichissement (64ms ou 16ms quand Ta > 85°C) */
      /* Refresh_rate = ( 64ms / (4096) ) = 15.625 µs */
      /* p_timer = Refresh_rate . freq (SDCLK) - 20 = 15.625 µs* 100 MHz - 20 = 1542 */
      sdram_setRefreshRate ( K_SDRAM_DISABLE_REFRESH_ERROR_INTERRUPT, 1542 ); /* 1292 dans l'exemple ST.*/

      /* Attente 1ms (optionnelle) */
      mk_utils_waitus ( 1000 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_system_memory_initSDRAM ( void )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Initialisation du FMC (module SDRAM) */
   mk_system_memory_initSDRAMFMC ( );

   /* Initialisation de la mémoire */
   l_result = mk_system_memory_initializationSequence ( );

   /* Retour */
   return ( l_result );
}



