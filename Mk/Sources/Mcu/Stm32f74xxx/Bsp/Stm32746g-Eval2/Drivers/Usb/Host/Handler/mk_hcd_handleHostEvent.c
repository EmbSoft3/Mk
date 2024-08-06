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
* @file mk_hcd_handleHostEvent.c
* @brief Définition de la fonction mk_hcd_handleHostEvent.
* @date 24 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleHostEvent ( T_mkAddr p_termio, T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de statut */
   uint32_t l_usbEvent;

   /* Tant qu'un signal n'a pas été reçu, laisser la main à une autre tâche */
   l_result = mk_event_wait ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR |
                              K_MK_HCD_DEVICE_CONNECTED_EVENT | K_MK_HCD_DEVICE_DISCONNECTED_EVENT | K_MK_HCD_ID_PIN_EVENT |
                              K_MK_HCD_OVERCURRENT_EVENT | K_MK_HCD_REFRESH_EVENT |
                              K_MK_HCD_DEVICE_ENABLED_EVENT,
                              &l_usbEvent, K_MK_TASK_WAIT_FOREVER );

   /* Si au moins un événement est disponible et si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le mode de fonctionnement du coeur USB doit être modifié */
      if ( ( l_usbEvent & K_MK_HCD_ID_PIN_EVENT ) == K_MK_HCD_ID_PIN_EVENT )
      {
         /* Réinitialisation de l'arborescence des périphériques USB au complet */
         l_result = mk_hcd_handleDisconnect ( p_handler );

         /* On relance le terminal afin de réinitialiser le coeur USB et basculer vers le nouveau mode (host, device) */
         l_result = mk_hcd_handleHostMode ( p_termio, p_handler );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une surchage est détectée sur le bus */
      if ( ( l_usbEvent & K_MK_HCD_OVERCURRENT_EVENT ) == K_MK_HCD_OVERCURRENT_EVENT )
      {
         /* L'alimentation est automatiquemnet désactivée par l'interruption OTG */
         /* La tâche doit cependant mettre à jour le statut du périphérique principal */
         l_result = mk_hcd_handleOvercurrent ( p_handler );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique principal vient d'être déconnecté du bus */
      if ( ( l_usbEvent & K_MK_HCD_DEVICE_DISCONNECTED_EVENT ) == K_MK_HCD_DEVICE_DISCONNECTED_EVENT )
      {
         /* Il est nécessaire de positionner le traitement de l'événement DISCONNECTED en amont de l'événement CONNECTED */
         /* afin de gérer le cas d'une connexion / déconnexion rapide. */
         /* En outre, lorsqu'une connexion est détectée, on s'assure que le dispositif n'a pas été déconnecté. */

         /* Réinitialisation de l'arborescence des périphériques USB au complet */
         l_result = mk_hcd_handleDisconnect ( p_handler );

         /* Mise à jour du champ d'événements */
         l_usbEvent &= ( uint32_t ) ( ~ ( K_MK_HCD_DEVICE_CONNECTED_EVENT | K_MK_HCD_REFRESH_EVENT ) );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique principal vient d'être connecté sur le bus */
      if ( ( l_usbEvent & K_MK_HCD_DEVICE_CONNECTED_EVENT ) == K_MK_HCD_DEVICE_CONNECTED_EVENT )
      {
         /* Initialisation du port USB */
         l_result = mk_hcd_handleConnect ( p_handler );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le port USB est prêt à être utilisé (reset OK) */
      if ( ( l_usbEvent & K_MK_HCD_DEVICE_ENABLED_EVENT ) == K_MK_HCD_DEVICE_ENABLED_EVENT )
      {
         /* Enumération du périphérique */
         l_result = mk_hcd_handleEnable ( p_handler, p_pipe );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* S'il est temps de rafraichir les hubs où d'énumérer un dispositif */
      if ( ( l_usbEvent & K_MK_HCD_REFRESH_EVENT ) == K_MK_HCD_REFRESH_EVENT )
      {
         /* Réalisation du processus de rafraichissement */
         l_result = mk_hcd_handleRefresh ( p_handler, p_pipe );
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
      /* Une erreur système vient de se produire */
      /* On conserve le résultat puis on rajoute un nouveau statut. */
      l_result |= K_MK_ERROR_UNEXPECTED;
   }

   /* Retour */
   return ( l_result );
}


