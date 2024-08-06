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
* @file mk_hcd_handleHostInterrupt.c
* @brief Définition de la fonction mk_hcd_handleHostInterrupt.
* @date 13 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_hcd_handleHostInterrupt ( T_mkHCDHandler* p_handler )
{
   /* Déclaration d'une variable de statut */
   uint32_t l_flags;

   /* Récupération des statuts d'interruption du coeur */
   l_flags = usb_getCoreInterruptFlag ( p_handler->bus, K_USB_PORT_INTERRUPT | K_USB_ID_PIN_CHANGE_INTERRUPT |
                                        K_USB_DISCONNECT_INTERRUPT | K_USB_OTG_EVENT_INTERRUPT | K_USB_CHANNELS_INTERRUPT |
                                        K_USB_MODE_MISMATCH_INTERRUPT | K_USB_SESSION_REQUEST_INTERRUPT | K_USB_START_OF_FRAME_INTERRUPT |
                                        K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT );

   /* Si les transactions périodique n'ont pas été intégralement transmise à la fin de la 'Frame' courante */
   if ( ( l_flags & K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT ) == K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT )
   {
      /* Réinitialisation du drapeau d'interruption */
      usb_clearCoreInterruptFlag ( p_handler->bus, K_USB_INCOMPLETE_PERIODIC_TRANSFERT_INTERRUPT );
   }

   else
   {
      /* Ne rien faire */
   }

   /* Si un événement sur un canal s'est produit */
   if ( ( l_flags & K_USB_CHANNELS_INTERRUPT ) == K_USB_CHANNELS_INTERRUPT )
   {
      /* Gestion des interruptions relatives aux canaux de commnication */
      mk_hcd_handleChannelInterrupt ( p_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une permutation de mode s'est produite (Host2Device et Device2Host) */
   if ( ( l_flags & K_USB_ID_PIN_CHANGE_INTERRUPT ) == K_USB_ID_PIN_CHANGE_INTERRUPT )
   {
      /* Gestion de l'interruption relative au mode de fonctionnement */
      mk_hcd_handleIdPinInterrupt ( p_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si un événement OTG s'est produit */
   if ( ( l_flags & K_USB_OTG_EVENT_INTERRUPT ) == K_USB_OTG_EVENT_INTERRUPT )
   {
      /* Réinitialisation du drapeau d'interruption */
      usb_clearOTGInterruptFlag ( p_handler->bus, K_USB_OTG_ALL_INTERRUPTS );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une requête de session s'est produite */
   if ( ( l_flags & K_USB_SESSION_REQUEST_INTERRUPT ) == K_USB_SESSION_REQUEST_INTERRUPT )
   {
      /* Réinitialisation du drapeau d'interruption */
      usb_clearCoreInterruptFlag ( p_handler->bus, K_USB_SESSION_REQUEST_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une erreur de mode s'est produite */
   if ( ( l_flags & K_USB_MODE_MISMATCH_INTERRUPT ) == K_USB_MODE_MISMATCH_INTERRUPT )
   {
      /* Réinitialisation du drapeau d'interruption */
      usb_clearCoreInterruptFlag ( p_handler->bus, K_USB_MODE_MISMATCH_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si un nouveau SOF a commencé */
   if ( ( l_flags & K_USB_START_OF_FRAME_INTERRUPT ) == K_USB_START_OF_FRAME_INTERRUPT )
   {
      /* Gestion de l'interruption SOF */
      mk_hcd_handleStartOfFrameInterrupt ( p_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si un événement sur le port s'est produit */
   if ( ( l_flags & K_USB_PORT_INTERRUPT ) == K_USB_PORT_INTERRUPT )
   {
      /* Gestion de l'interruption relative au port */
      mk_hcd_handlePortInterrupt ( p_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si un périphérique a été déconnecté */
   if ( ( l_flags & K_USB_DISCONNECT_INTERRUPT ) == K_USB_DISCONNECT_INTERRUPT )
   {
      /* Réinitialisation du drapeau d'interruption */
      usb_clearCoreInterruptFlag ( p_handler->bus, K_USB_DISCONNECT_INTERRUPT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

