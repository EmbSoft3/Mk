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
* @file mk_mmc_Interrupt.c
* @brief Définition de la fonction mk_mmc_Interrupt.
* @date 5 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_mmc_handleInterrupt ( T_mkMMCHandler* p_handler )
{
   /* Récupération de la valeur du registre de statuts */
   uint32_t l_status = mmc_getStatus (
         K_MMC_FLAG_CMD_TRANSMITTED | K_MMC_FLAG_CMD_RESPONSE_RECEIVED | K_MMC_FLAG_DATA_BLOCK_TRANSFERED |
         K_MMC_FLAG_RXFIFO_OVERRUN | K_MMC_FLAG_TXFIFO_UNDERRUN | K_MMC_FLAG_CMD_RESPONSE_TIMEOUT | K_MMC_FLAG_DATA_TIMEOUT |
         K_MMC_FLAG_DATA_BLOCK_FAILED | K_MMC_FLAG_CMD_RESPONSE_FAILED | K_MMC_FLAG_START_BIT_NOT_DETECTED );

   /* Si une erreur s'est produite */
   if ( ( l_status & ( K_MMC_FLAG_RXFIFO_OVERRUN | K_MMC_FLAG_TXFIFO_UNDERRUN | K_MMC_FLAG_START_BIT_NOT_DETECTED ) ) > 0 )
   {
      /* La détection des drapeaux 'Underrun' et 'Overrun' ne doit pas se produite si le contrôle de flux est actif. */
      /* Transmission des événements au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_MMC_TRANSFER_ABORTED | l_status );
   }

   /* Sinon si une erreur ponctuelle s'est produite */
   else if ( ( l_status & ( K_MMC_FLAG_DATA_BLOCK_FAILED | K_MMC_FLAG_CMD_RESPONSE_FAILED ) ) > 0 )
   {
      /* Transmission des événements au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_MMC_TRANSFER_ERROR | l_status );
   }

   /* Sinon si une erreur de timeout s'est produite */
   else if ( ( l_status & ( K_MMC_FLAG_CMD_RESPONSE_TIMEOUT | K_MMC_FLAG_DATA_TIMEOUT ) ) > 0 )
   {
      /* Transmission des événements au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_MMC_TRANSFER_TIMEOUT | l_status );
   }

   /* Sinon si une commande a été reçue ou envoyée */
   else if ( ( l_status & ( K_MMC_FLAG_CMD_TRANSMITTED | K_MMC_FLAG_DATA_BLOCK_TRANSFERED | K_MMC_FLAG_CMD_RESPONSE_RECEIVED ) ) > 0 )
   {
      /* Transmission de l'événement TRANSFER_DONE */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_MMC_TRANSFER_DONE | l_status );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Réinitialisation des drapeaux d'interruption */
   mmc_clearStatus ( K_MMC_FLAG_ALL );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_mmc_interrupt ( void )
{
   /* Si le gestionnaire MMC est valide */
   if ( g_mkTermioHandler.mmc->child != K_MK_NULL )
   {
      /* Gestion des interruptions du périphérique MMC */
      mk_mmc_handleInterrupt ( g_mkTermioHandler.mmc->child );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


