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
* @file mk_hcd_handlePortInterrupt.c
* @brief Définition de la fonction mk_hcd_handlePortInterrupt.
* @date 13 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_hcd_handlePortInterrupt ( T_mkHCDHandler* p_handler )
{
   /* Récupération du statut du port USB */
   uint32_t l_status = usb_getPortStatus ( p_handler->bus, K_USB_PORT_DEVICE_CONNECTED_FLAG | K_USB_PORT_DEVICE_ATTACHED_FLAG |
                                           K_USB_OVERCURRENT_CHANGE_FLAG | K_USB_PORT_ENABLED_CHANGE_FLAG | K_USB_PORT_ENABLED_FLAG );

   /* Si le périphérique USB a détecté une connexion sur le bus */
   if ( l_status == ( K_USB_DEVICE_CONNECTED | K_USB_DEVICE_ATTACHED ) )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_HCD_DEVICE_CONNECTED_EVENT );

      /* Réinitialisation du drapeau d'interruption */
      usb_clearStatus ( p_handler->bus, K_USB_PORT_DEVICE_CONNECTED_FLAG );
   }

   /* Sinon si le port USB a été activé */
   else if ( l_status == ( K_USB_DEVICE_ATTACHED | K_USB_PORT_ENABLED | K_USB_PORT_ENABLED_STATUS_CHANGED ) )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_HCD_DEVICE_ENABLED_EVENT );

      /* Réinitialisation du drapeau d'interruption (cf. warning dans la déclaration de la fonction) */
      usb_clearStatus ( p_handler->bus, K_USB_PORT_ENABLED_FLAG );
   }

   /* Sinon si le périphérique USB a détecté une déconnexion sur le bus */
   else if ( ( l_status & K_USB_PORT_ENABLED_STATUS_CHANGED ) == K_USB_PORT_ENABLED_STATUS_CHANGED )
   {
      /* Désactivation de l'alimentation */
      usb_disablePower ( p_handler->bus );

      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_HCD_DEVICE_DISCONNECTED_EVENT );

      /* Réinitialisation du drapeau d'interruption (cf. warning dans le déclaration de la fonction) */
      usb_clearStatus ( p_handler->bus, K_USB_PORT_ENABLED_STATUS_CHANGED );
   }

   /* Sinon si le périphérique USB a détecté une surcharge sur le bus */
   else if ( ( l_status & K_USB_OVERCURRENT_CHANGED ) == K_USB_OVERCURRENT_CHANGED )
   {
      /* Désactivation de l'alimentation */
      usb_disablePower ( p_handler->bus );

      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_HCD_OVERCURRENT_EVENT );

      /* Réinitialisation du drapeau d'interruption (cf. warning dans le déclaration de la fonction) */
      usb_clearStatus ( p_handler->bus, K_USB_OVERCURRENT_CHANGED );
   }

   /* Sinon */
   else
   {
      /* Ce cas ne doit jamais être atteint. Dans le cas contraire, une déconnexion du bus est */
      /* simulée */

      /* Désactivation de l'alimentation */
      usb_disablePower ( p_handler->bus );

      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_HCD_DEVICE_DISCONNECTED_EVENT );

      /* Réinitialisation du drapeau d'interruption */
      usb_clearStatus ( p_handler->bus, K_USB_PORT_DEVICE_CONNECTED_FLAG );
   }

   /* Retour */
   return;
}


