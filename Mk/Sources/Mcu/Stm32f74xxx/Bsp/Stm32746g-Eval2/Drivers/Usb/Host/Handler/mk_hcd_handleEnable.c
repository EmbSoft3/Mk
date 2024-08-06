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
* @file mk_hcd_handleEnable.c
* @brief Définition de la fonction mk_hcd_handleEnable.
* @date 26 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_initFirstDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device )
{
   /* Enregistrement de l'adresse du gestionnaire USB */
   p_device->handler = p_handler;

   /* Récupération de la vitesse du périphérique */
   p_device->layer.speed = ( uint8_t ) usb_getPortSpeed ( p_handler->bus );

   /* Configuration des pointeurs de liste */
   p_device->next = p_device;
   p_device->previous = p_device;

   /* Si la vitesse est LS ou FS */
   if ( ( p_device->layer.speed != K_USB_HIGH_SPEED ) && ( p_handler->bus == K_USB_OTGHS ) )
   {
      /* Configuration de la durée entre deux SOF (FS) ou deux Keep-Alive (LS) */
      /* Pour le mode (HS), cette valeur configure la durée entre deux µSOF */
      /* Elle est exprimée en multiple de l'horloge du PHY */
      usb_setFrameInterval ( p_handler->bus, 0xEA60 );
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

static T_mkCode mk_termio_enumerateFirstDevice ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Allocation du premier périphérique sur le bus */
   l_result = mk_pool_allocSafe ( g_mkHCDPool.devicePool, ( T_mkAddr* ) &p_handler->device, K_MK_POOL_CLEAR, 0 );

   /* Si l'allocation a réussi */
   if ( ( l_result == K_MK_OK ) && ( p_handler->device != K_MK_NULL ) )
   {
      /* Initialisation du périphérique */
      mk_hcd_initFirstDevice ( p_handler, p_handler->device );

      /* Initialisation du champ d'événements du périphérique */
      l_result = mk_event_create ( &p_handler->device->flag.event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Lancement de l'enumération du périphérique */
         l_result = mk_hcd_enumerate ( p_handler, p_handler->device, p_pipe );

         /* On ne désalloue pas le périphérique si l'énumération a échoué */
         /* Une nouvelle tentative sera réalisée lors de la réception de l'événement de rafraichissement. */

         /* Si le périphérique n'est plus dans l'état 'ATTACHED' */
         if ( ( l_result == K_MK_OK ) && ( p_handler->device->state != K_MK_HCD_DEVICE_ATTACHED_STATE ) )
         {
            /* Réinitialisation de la durée du reset */
            p_handler->resetTick = K_MK_USB_RESET_TICK;
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
      /* Ne rien faire */
      /* Une erreur critique s'est produite. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleEnable ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enumération du premier périphérique */
   l_result = mk_termio_enumerateFirstDevice ( p_handler, p_pipe );

   /* Si aucune erreur critique ne s'est produite */
   if ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) == K_MK_OK )
   {
      /* Transmission de l'événement de rafraichissement */
      l_result = mk_event_set ( p_handler->portEvent, K_MK_HCD_REFRESH_EVENT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Une erreur critique s'est produite. */
   }

   /* Retour */
   return ( l_result );
}

