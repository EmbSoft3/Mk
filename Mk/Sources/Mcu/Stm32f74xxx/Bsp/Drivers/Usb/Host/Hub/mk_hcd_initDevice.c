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
* @file mk_hcd_initDevice.c
* @brief Définition de la fonction mk_hcd_initDevice.
* @date 20 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_setAttributes ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDDevice* p_newDevice, T_mkHCDPortStatus* p_status, uint16_t p_port )
{
   /* Enregistrement de l'adresse du gestionnaire USB */
   p_newDevice->handler = ( T_mkHCDHandler* ) p_handler;

   /* Enregistrement et configuration des paramètres du périphérique */
   p_newDevice->layer.portNumber = ( uint8_t ) p_port;
   p_newDevice->layer.hubAddr = p_hub->layer.deviceAddr;

   /* Configuration des pointeurs de liste */
   p_newDevice->next = p_newDevice;
   p_newDevice->previous = p_newDevice;

   /* Si le périphérique est de type HS */
   if ( p_status->highSpeedDeviceAttached == 1 )
   {
      /* Configuration de la vitesse du périphérique */
      p_newDevice->layer.speed = K_USB_HIGH_SPEED;
   }

   /* Sinon si le dispositif est de type LS */
   else if ( p_status->lowSpeedDeviceAttached == 1 )
   {
      /* Configuration de la vitesse du périphérique */
      p_newDevice->layer.speed = K_USB_LOW_SPEED;
   }

   /* Sinon */
   else
   {
      /* Configuration de la vitesse du périphérique */
      p_newDevice->layer.speed = K_USB_FULL_SPEED;
   }

   /* Si le hub est de type HS */
   if ( p_hub->layer.speed == K_USB_HIGH_SPEED )
   {
      /* Configuration de l'adresse utilisée en mode SPLIT */
      p_newDevice->layer.hubSplitAddr = p_hub->layer.deviceAddr;
      p_newDevice->layer.portSplitNumber = ( uint8_t ) p_port;
   }

   /* Sinon */
   else
   {
      /* L'adresse et le port utilisé pour le SPLIT sont ceux du dernier hub de type */
      /* HS ou 0 si aucun HUB est de type HS (mode désactivé) */
      p_newDevice->layer.hubSplitAddr = p_hub->layer.hubSplitAddr;
      p_newDevice->layer.portSplitNumber = p_hub->layer.portSplitNumber;
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_initDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint16_t p_portNumber, T_mkHCDPortStatus* p_portStatus )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un périphérique */
   T_mkHCDDevice* l_newDevice;

   /* Allocation dynamique d'un nouveau périphérique */
   l_result = mk_pool_allocSafe ( g_mkHCDPool.devicePool, ( T_mkAddr* ) &l_newDevice, K_MK_POOL_CLEAR, 0 );

   /* Si l'allocation a réussi */
   if ( ( l_result == K_MK_OK ) && ( l_newDevice != K_MK_NULL ) )
   {
      /* Configuration des attributs du nouveau périphérique */
      mk_hcd_setAttributes ( p_handler, p_hub, l_newDevice, p_portStatus, p_portNumber );

      /* Initialisation du champ d'événements */
      l_result = mk_event_create ( &l_newDevice->flag.event, K_MK_ID_EVENT_SIGNAL, K_MK_AREA_PROTECTED, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Ajout du périphérique dans la liste */
         l_result = mk_hcd_addTree ( p_hub, l_newDevice );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Lançement de l'énumération */
            l_result = mk_hcd_enumerate ( p_handler, l_newDevice, p_pipe );
         }

         /* Sinon */
         else
         {
            /* Désallocation mémoire */
            l_result |= mk_pool_freeSafe ( g_mkHCDPool.devicePool, ( T_mkAddr ) l_newDevice );
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
   }

   /* Retour */
   return ( l_result );
}


