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
* @file mk_mmc_init.c
* @brief Définition de la fonction mk_mmc_init.
* @date 1 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_mmc_init ( void )
{
   /* Désactivation du périphérique MMC */
   mmc_disable ( );

   /* Désactivation du mode économie d'énergie */
   mmc_disablePowerSavingMode ( );

   /* Activation du contrôle du flux */
   mmc_enableFlowControl ( );

   /* Désactivation de la broche d'horloge */
   mmc_disableClockPin ( );

   /* Configuration de la taille du bus */
   mmc_setDataBusSize ( K_MMC_DATABUS_SIZE_1PIN );

   /* Désactivation du bypass de l'horloge */
   mmc_disableBypass ( );

   /* Configuration de la vitesse de l'horloge MMC */
   /* FREQ_PERIPH = 48MHz */
   /* FREQ_MMC = FREQ_PERIPH / ( 118 + 2 ) = 400 kHz */
   mmc_setPrescaler ( 118 );

   /* Configuration du point d'échantillonage sur front descendant */
   mmc_setSampleEdge ( K_MMC_CLOCK_FALLING_EDGE );

   /* Réinitialisation des drapeaux d'interruption */
   mmc_clearStatus ( K_MMC_FLAG_ALL );

   /* Activation des interruptions MMC */
   mmc_enableInterrupt ( K_MMC_FLAG_DATA_BLOCK_TRANSFERED | K_MMC_FLAG_CMD_TRANSMITTED | K_MMC_FLAG_CMD_RESPONSE_RECEIVED |
                         K_MMC_FLAG_RXFIFO_OVERRUN | K_MMC_FLAG_TXFIFO_UNDERRUN | K_MMC_FLAG_CMD_RESPONSE_TIMEOUT |
                         K_MMC_FLAG_DATA_BLOCK_FAILED | K_MMC_FLAG_CMD_RESPONSE_FAILED | K_MMC_FLAG_START_BIT_NOT_DETECTED );

   /* Activation de la DMA */
   mmc_enableDma ( );

   /* Activation du périphérique MMC */
   mmc_enable ( );

   /* Activation de l'horloge */
   mmc_enableClockPin ( );

   /* Retour */
   return;
}
