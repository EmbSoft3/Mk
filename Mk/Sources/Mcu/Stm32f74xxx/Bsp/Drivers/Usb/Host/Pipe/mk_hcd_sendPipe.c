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
* @file mk_hcd_sendPipe.c
* @brief Définition de la fonction mk_hcd_sendPipe.
* @date 21 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_swapToken ( T_mkHCDEndpointDescriptor* p_endpoint, T_mkHCDPipe* p_pipe, uint8_t p_token )
{
   /* Si la terminaison est de type CONTROL */
   if ( p_pipe->endpointType == K_USB_CONTROL_ENDPOINT )
   {
      /* Si une permutation de PID est nécessaire */
      if ( p_token == K_USB_PID_TOOGLE )
      {
         /* Permutation des PIDs */
         if ( p_pipe->token == K_USB_PID_DATA1 )
         {
            p_pipe->token = K_USB_PID_DATA0;
         }

         /* Sinon */
         else
         {
            p_pipe->token = K_USB_PID_DATA1;
         }
      }

      /* Sinon */
      else
      {
         /* Enregistrement de la valeur du PID */
         p_pipe->token = p_token;
      }
   }

   /* Sinon si la terminaison est de type INTERRUPT ou BULK */
   else if ( ( p_pipe->endpointType == K_USB_INTERRUPT_ENDPOINT ) || ( p_pipe->endpointType == K_USB_BULK_ENDPOINT ) )
   {
      /* Si la transaction n'est pas sur la terminaison 0 */
      if ( p_endpoint != K_MK_NULL )
      {
         /* Actualisation du token */
         p_pipe->token = p_endpoint->bToken;
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
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_updateToken ( T_mkHCDEndpointDescriptor* p_endpoint, T_mkHCDPipe* p_pipe )
{
   /* Si la terminaison est de type INTERRUPT ou BULK et si la transaction a réussi */
   if ( ( ( p_pipe->endpointType == K_USB_INTERRUPT_ENDPOINT ) || ( p_pipe->endpointType == K_USB_BULK_ENDPOINT ) ) &&
        ( ( ( p_pipe->status & K_MK_HCD_FLAG_ACK ) == K_MK_HCD_FLAG_ACK ) || ( ( p_pipe->status & K_MK_HCD_FLAG_CHH ) == K_MK_HCD_FLAG_CHH ) ) )
   {
      /* Si le transfert n'est pas sur la terminaison 0 et si le token doit être actualisé (1 = nombre de paquets impaires) */
      if ( ( p_endpoint != K_MK_NULL ) && ( ( p_pipe->numberOfPackets & 0x01 ) > 0 ) )
      {
         /* Permutation des PID */
         if ( p_endpoint->bToken == K_USB_PID_DATA1 )
         {
            p_endpoint->bToken = K_USB_PID_DATA0;
         }

         /* Sinon */
         else
         {
            p_endpoint->bToken = K_USB_PID_DATA1;
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
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_sendPipe ( T_mkHCDDevice* p_device, T_mkHCDEndpointDescriptor* p_endpoint, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_register, uint32_t p_length )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'un pointeur de gestionnaire USB */
   T_mkHCDHandler* l_handler = K_MK_NULL;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_buf != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du gestionnaire USB */
      l_handler = ( T_mkHCDHandler* ) p_device->handler;

      /* Réinitialisation de la variable stockant le nombre de paquets transmis */
      p_pipe->numberOfPackets = 0;

      /* Configuration des attributs de la terminaison */
      p_pipe->endpointDirection = ( uint8_t ) ( ( p_register >> 24 ) & 0xF );

      /* Détermination du PID à transmettre */
      mk_hcd_swapToken ( p_endpoint, p_pipe, ( uint8_t ) ( ( p_register >> 28 ) & 0xF ) );

      /* Effectue */
      do
      {
         /* Réinitialisation du statut de la communication */
         p_pipe->status = K_MK_HCD_NO_FLAG;

         /* Si une transaction de type SPLIT doit être effectuée */
         if ( ( l_handler->bus == K_USB_OTGHS ) && ( l_handler->device->layer.speed == K_USB_HIGH_SPEED ) && ( p_device->layer.speed != K_USB_HIGH_SPEED ) && ( p_device->layer.hubAddr != 0 ) )
         {
            /* Déclenchement d'une transaction de type split */
            l_result = mk_hcd_sendSplitPacket ( l_handler, p_device, p_pipe, p_buf, p_length );
         }

         /* Sinon */
         else
         {
            /* Déclenchement d'une transaction normale */
            l_result = mk_hcd_sendPacket ( l_handler, p_device, p_pipe, p_buf, p_length );
         }

         /* Actualisation des tokens pour les transactions périodiques */
         mk_hcd_updateToken ( p_endpoint, p_pipe );

         /* Actualisation de la variable de comptage */
         l_counter++;

      /* Tant qu'une erreur de communication est présente ou tant que le nombre maximal de tentatives n'a pas été atteint */
      } while ( ( l_result == K_MK_ERROR_COMM ) && ( ( p_pipe->status & K_MK_HCD_ERROR_STALL ) != K_MK_HCD_ERROR_STALL ) && ( l_counter < K_MK_HCD_TIMEOUT_COUNT ) );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

