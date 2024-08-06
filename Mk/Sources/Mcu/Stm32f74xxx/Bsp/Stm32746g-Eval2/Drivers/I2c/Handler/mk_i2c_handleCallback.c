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
* @file mk_i2c_handleCallback.c
* @brief Définition de la fonction mk_i2c_handleCallback.
* @date 28 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_i2c_handleCallback ( T_mkI2CDMAHandler* p_handler )
{
   /* Déclaration d'un registre de statut */
   uint32_t l_status;

   /* Lecture du registre de statut du périphérique I2C */
   l_status = dma_getTransferCompleteInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Si le transfert est terminé */
   if ( l_status > 0 )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->pipe->event, K_MK_DMA_STATUS_TRANSFER_COMPLETED );

      /* Réinitialisation du drapeau d'interruption */
      dma_clearTransferCompleteInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Lecture du registre d'erreurs */
   l_status = dma_getTransferErrorInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Si une erreur s'est produite */
   if ( l_status > 0 )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->pipe->event, K_MK_DMA_STATUS_TRANSFER_ERROR );

      /* Réinitialisation du drapeau d'interruption */
      dma_clearTransferErrorInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

