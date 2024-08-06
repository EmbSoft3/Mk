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
* @file mk_hcd_startTransfer.c
* @brief Définition de la fonction mk_hcd_startTransfer.
* @date 8 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_unmaskInterrupt ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Si le transfert est de type INTERRUPT */
   if ( p_pipe->endpointType == K_USB_INTERRUPT_ENDPOINT )
   {
      /* Activation de l'interruption NAK */
      usb_unmaskChannelInterrupt ( p_handler->bus, p_pipe->channel, K_USB_NAK_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_startTransfer ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Effectue */
      do
      {
         /* Configuration du masque d'interruption en fonction du type de transaction */
         mk_hcd_unmaskInterrupt ( p_handler, p_pipe );

         /* Déclenchement d'une transaction */
         usb_enableChannel ( p_handler->bus, p_pipe->channel );

         /* Attendre tant que la transaction n'est pas terminé */
         /* La constante K_USB_CHANNEL_ALL_INTERRUPT est présente afin de réinitialiser automatiquement tous les drapeaux */
         l_result =  mk_event_wait ( p_handler->channelEvent [ p_pipe->channel ], K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_USB_CHANNEL_ALL_INTERRUPTS |
                                     K_MK_HCD_TRANSFER_ABORTED | K_MK_HCD_TRANSFER_DONE | K_MK_HCD_TRANSFER_RESTART_SPLIT, ( uint32_t* ) ( &p_pipe->status ), p_pipe->timeout );

         /* Actualisation du compteur de tentatives */
         l_counter++;

      /* Tant que l'événement de fin n'est pas déclenché */
      } while ( ( p_pipe->status == K_MK_HCD_TRANSFER_RESTART_SPLIT ) && ( ( p_pipe->status & K_MK_HCD_ERROR_STALL ) != K_MK_HCD_ERROR_STALL ) && ( l_counter < K_MK_HCD_TIMEOUT_SPLIT_COUNT ) );

      /* Si le résultat de la transaction est disponible */
      if ( l_result == K_MK_OK )
      {
         /* Si une erreur s'est produite */
         if ( ( p_pipe->status & ( K_MK_HCD_TRANSFER_ABORTED | K_MK_HCD_TRANSFER_RESTART_SPLIT ) ) > 0 )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_COMM;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Mise à jour du statut du pipe */
         p_pipe->status &= K_MK_HCD_CHANNEL_MASK;

      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Récupération du nombre de paquets transmis */
      l_counter = usb_getPacketRemainder ( p_handler->bus, p_pipe->channel );

      /* Actualisation du nombre de paquets transmis */
      p_pipe->numberOfPackets = ( uint32_t ) ( p_pipe->numberOfPackets - l_counter );

      /* Désactivation du canal */
      l_result |= mk_hcd_haltTransfer ( p_handler, p_pipe );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



