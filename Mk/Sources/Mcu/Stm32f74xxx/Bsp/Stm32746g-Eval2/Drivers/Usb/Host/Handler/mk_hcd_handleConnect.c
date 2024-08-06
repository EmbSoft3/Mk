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
* @file mk_hcd_handleConnect.c
* @brief Définition de la fonction mk_hcd_handleConnect.
* @date 24 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_modulateReset ( T_mkHCDHandler* p_handler )
{
   /* Modulation de la durée du reset */
   /* On double la valeur à chaque tentative (on conserve une durée max de 2 sec) */
   p_handler->resetTick = p_handler->resetTick << 1;

   /* Si la durée du reset devient trop importante */
   if ( p_handler->resetTick > K_MK_USB_MAX_RESET_TICK )
   {
      /* Limitation de la durée de reset */
      p_handler->resetTick = K_MK_USB_MAX_RESET_TICK;
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

T_mkCode mk_hcd_handleConnect ( T_mkHCDHandler* p_handler )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_status;

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* On attends afin d'être certain que la stabilisation de l'alimentation entre l'hote et le périphérique */
      /* est OK */
      l_result = mk_task_sleep ( 500 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si un dispositif a déjà été alloué */
         /* Ce cas se produit si l'événement 'Disconnect' a été manqué ou ne s'est pas produit */
         /* En fonction de la durée du reset, l'événement 'Connect' peut se produire en boucle. Il conserve alors */
         /* le périphérique connecté dans l'état 'ATTACHED'. */
         if ( p_handler->device != K_MK_NULL )
         {
            /* Transmission du signal de déconnection */
            l_result = mk_hcd_signalDisconnectEvent ( p_handler->device );

            /* Suppresssion de l'arbre USB au complet */
            l_result |= mk_hcd_resetTree ( p_handler );

            /* Modulation de la durée de reset */
            mk_hcd_modulateReset ( p_handler );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Récupération du statut du port USB */
         l_status = usb_getPortStatus ( p_handler->bus, K_USB_PORT_DEVICE_ATTACHED_FLAG | K_USB_PORT_ENABLED_FLAG );

         /* Si le dispositif est toujours connecté sur le port */
         if ( ( ( l_status & K_USB_DEVICE_ATTACHED ) == K_USB_DEVICE_ATTACHED ) &&
              ( ( l_status & K_USB_PORT_ENABLED ) != K_USB_PORT_ENABLED ) )
         {
            /* Initialisation du port USB */
            l_result = mk_usb_initPort ( p_handler->bus, p_handler->resetTick );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
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


