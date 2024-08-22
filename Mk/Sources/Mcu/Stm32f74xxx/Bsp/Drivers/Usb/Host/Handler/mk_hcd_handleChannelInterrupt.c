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
* @file mk_hcd_handleChannelInterrupt.c
* @brief Définition de la fonction mk_hcd_handleChannelInterrupt.
* @date 13 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_handleSplitTransaction ( T_mkHCDHandler* p_handler, uint32_t p_channel, uint32_t p_status )
{
   /* Déclaration des variables de travail */
   uint32_t l_direction, l_type;

   /* Récupération du token de la transaction */
   l_type = usb_getSplitToken ( p_handler->bus, p_channel );

   /* Récupération de la direction de la terminaison */
   l_direction = usb_getEndpointDirection ( p_handler->bus, p_channel );

   /* Si transaction de type SSPLIT */
   if ( l_type == K_USB_TOKEN_SSPLIT )
   {
      /* Récupération du type de la terminaison */
      l_type = usb_getEndpointType ( p_handler->bus, p_channel );

      /* Le comportement du gestionnaire différe en fonction du type de transaction. */
      /* Pour une transaction non périodique (CONTROL, BULK) de type IN, on vérifie la réception d'un ACK. Sinon, on transmet directement le token */
      /* CSPLIT lorsque le canal est désactivé (c'est à dire que le token SSPLIT et IN ont été envoyé sur le bus). */

      /* Si une transaction de type CSPLIT doit être réalisée */
      if ( ( ( p_status & K_USB_ACK_INTERRUPT ) == K_USB_ACK_INTERRUPT ) ||
         ( ( ( l_type == K_USB_INTERRUPT_ENDPOINT ) || ( l_type == K_USB_ISOCHRONOUS_ENDPOINT ) ) && ( l_direction == K_USB_IN_ENDPOINT ) &&
           ( ( p_status & K_USB_CHANNEL_HALTED_INTERRUPT ) == K_USB_CHANNEL_HALTED_INTERRUPT ) ) )
      {
         /* Activation du CSPLIT */
         usb_setCompleteSplit ( p_handler->bus, p_channel );

         /* Réactivation du canal */
         usb_enableChannel ( p_handler->bus, p_channel );
      }

      /* Sinon (NYET ou NAK) */
      else
      {
         /* Configuration du nombre de µTrame avant de rémettre un token NYET ou ACK */
         /* La réactivation du canal est effectué dans le gestionnaire SOF */

         /* Attente d'au moins 3 µTrame (125µs par µTrame) */
         p_handler->sofTable [ p_channel ] = 3;
      }
   }

   /* Sinon (CSPLIT) */
   else
   {
      /* Si le périphérique a répondu avec un NAK */
      if ( ( p_status & K_USB_NAK_INTERRUPT ) == K_USB_NAK_INTERRUPT )
      {
         /* Récupération du type de la terminaison */
         l_type = usb_getEndpointType ( p_handler->bus, p_channel );

         /* Si la terminaison est de type INTERRUPT-IN */
         if ( ( l_type == K_USB_INTERRUPT_ENDPOINT ) && ( l_direction == K_USB_IN_ENDPOINT ) )
         {
            /* Transmission de l'événement TRANSFER_DONE */
            ( void ) mk_event_set ( p_handler->channelEvent [ p_channel ], K_MK_HCD_TRANSFER_DONE | p_status );
         }

         /* Sinon */
         else
         {
            /* Réémission d'un SSPLIT */
            usb_setStartSplit ( p_handler->bus, p_channel );

            /* Transmission d'un événements au terminal */
            ( void ) mk_event_set ( p_handler->channelEvent [ p_channel ], K_MK_HCD_TRANSFER_RESTART_SPLIT );
         }
      }

      /* Sinon (NYET) */
      else
      {
         /* Configuration du nombre de µTrame avant de rémettre un token NYET */
         /* La réactivation du canal est effectué dans le gestionnaire SOF */

         /* Attente d'au moins 1 µTrame (125µs par µTrame) */
         p_handler->sofTable [ p_channel ] = 1;
      }
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_hcd_handleChannelInterrupt ( T_mkHCDHandler* p_handler )
{
   /* Déclaration des variables de travail */
   uint32_t l_channel, l_status, l_type, l_mask, l_split;

   /* Pour le nombre de canal de communication */
   for ( l_channel = K_USB_CHANNEL0 ; l_channel <= K_USB_CHANNEL15 ; l_channel++ )
   {
      /* Lecture du registre d'interruption global */
      l_status = usb_getGlobalChannelInterrupt ( p_handler->bus, ( uint32_t ) ( 1 << l_channel ) );

      /* Si une interruption s'est produite sur le canal analysé */
      if ( l_status == ( uint32_t ) ( 1 << l_channel ) )
      {
         /* Lecture du registre d'interruption dédié au canal */
         l_status = _usb_getClearChannelInterrupt ( p_handler->bus, l_channel, K_USB_CHANNEL_ALL_INTERRUPTS );

         /* Récupération du type de la terminaison */
         l_type = usb_getEndpointType ( p_handler->bus, l_channel );

         /* Récupération du type de transaction */
         l_split = usb_getSplit ( p_handler->bus, l_channel );

         /* Récupération de la valeur du masque d'interruption */
         l_mask = usb_getChannelInterruptMask ( p_handler->bus, l_channel, K_USB_NAK_INTERRUPT );

         /* Si le canal doit être désactivé */
         if ( ( p_handler->channelEvent [ l_channel ]->flag & K_MK_HCD_TRANSFER_DISABLED ) > 0 )
         {
            /* Transmission d'un événements au terminal */
            ( void ) mk_event_set ( p_handler->channelEvent [ l_channel ], K_MK_HCD_TRANSFER_ABORTED );
         }

         /* Sinon si une erreur est survenue durant le transfert */
         else if ( ( l_status & K_MK_HCD_CHANNEL_ABORTED_MASK ) > 0 )
         {
            /* Transmission d'un ou plusieurs événements d'erreur au terminal */
            ( void ) mk_event_set ( p_handler->channelEvent [ l_channel ], K_MK_HCD_TRANSFER_ABORTED | l_status );
         }

         /* Pour un transfert de type OUT, l'interruption est directement déclenchée avec un code $23 (ACK, CHH, TX_COMPLETED) */
         /* Lors de la réception d'un NAK, l'interruption n'est pas déclenchée mais le canal est réactivé et le paquet est émis de nouveau */
         /* sans intervention particulière. */

         /* Pour un transfert de type IN, le TX_COMPLETED puis le CHANNEL_HALTED sont déclenchées dans deux interruptions distinctes. */
         /* En masquant l'interruption TX_COMPLETED, on se ramène au cas de figure ci-dessus. On reçoit alors directement un code $23. */

         /* Lors de la désactivation du canal, l'interruption est déclenchée avec un code 0x02 (CHANNEL_HALTED). Aucun traitement n'est effectué dans */
         /* cette situation. */

         /* Sinon si un paquet a été transmis ou reçu */
         else if ( ( l_status & K_USB_TRANSFER_COMPLETED_INTERRUPT ) == K_USB_TRANSFER_COMPLETED_INTERRUPT )
         {
            /* Si un ACK a été recu */
            if ( ( ( l_status & K_USB_ACK_INTERRUPT ) == K_USB_ACK_INTERRUPT ) )
            {
               /* Transmission de l'événement TRANSFER_DONE */
               ( void ) mk_event_set ( p_handler->channelEvent [ l_channel ], K_MK_HCD_TRANSFER_DONE | l_status );
            }

            /* Sinon si un NYET a été reçu */
            /* Le périphérique USB ne notifie pas directement le NYET, il arrête le canal et notifie le résultat avec le code $03 */
            else if ( ( l_type == K_USB_BULK_ENDPOINT ) && ( ( l_status & K_USB_CHANNEL_HALTED_INTERRUPT ) == K_USB_CHANNEL_HALTED_INTERRUPT ) )
            {
               /* Transmission de l'événement TRANSFER_DONE */
               ( void ) mk_event_set ( p_handler->channelEvent [ l_channel ], K_MK_HCD_TRANSFER_DONE | l_status );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* L'émission d'un token SSPLIT ne provoque pas le déclenchement de l'interruption TRANSFER_COMPLETED contrairement au token CSPLIT. */
         /* L'interruption doit donc vérifier si une transaction de type SSPLIT est en cours et si oui déclencher l'émission du token CSPLIT. */
         /* Contrairement au transaction classique, le hard ne gére pas la réémission automatique du paquet lors de la réception d'un NYET ou d'un NAK */
         /* Il faut donc redéclencher manuellement le transfert; */

         /* Sinon si une transaction de type SPLIT est en cours */
         else if ( l_split == K_USB_SPLIT_TRANSACTION )
         {
            /* Gestion des événements relatifs aux transaction de type SPLIT */
            mk_hcd_handleSplitTransaction ( p_handler, l_channel, l_status );
         }

         /* Pour certain type de périphérique (HUB), la réception d'un NAK indique qu'aucune donnée n'est disponible. Il faut alors mettre fin au transfert. */
         /* Sinon si l'interruption NAK est active */
         else if ( ( l_mask == K_USB_NAK_INTERRUPT ) && ( ( l_status & K_USB_NAK_INTERRUPT ) == K_USB_NAK_INTERRUPT ) )
         {
            /* Transmission de l'événement TRANSFER_DONE */
            ( void ) mk_event_set ( p_handler->channelEvent [ l_channel ], K_MK_HCD_TRANSFER_DONE | K_USB_NAK_INTERRUPT );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désactivation de l'interruption NAK */
         usb_maskChannelInterrupt ( p_handler->bus, l_channel, K_USB_NAK_INTERRUPT );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return;
}



