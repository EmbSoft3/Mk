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
* @file mk_hcd_getDeviceDescriptor.c
* @brief Définition de la fonction mk_hcd_getDeviceDescriptor.
* @date 28 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_getDeviceDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Création de la requête de récupération du descripteur de périphérique */
      l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_GET_DESCRIPTOR, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_STANDARD | K_MK_HCD_DEVICE, K_MK_HCD_DESC_DEVICE, 0, K_MK_HCD_DEVICE_DESCRIPTOR_SIZE );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de la requête */
         l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du descripteur */
            l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) ( T_mkHCDDeviceDescriptor* ) &p_device->deviceDescriptor, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1, K_MK_HCD_DEVICE_DESCRIPTOR_SIZE );

            /* Si la transaction est terminée */
            if ( l_result == K_MK_OK )
            {
               /* Configuration du maxpacketSize de la terminaison 0 */
               p_pipe->endpointMaxPacketSize = p_device->deviceDescriptor.bMaxPacketSize0;

               /* Transmission du paquet d'acquittement (ZLP) */
               l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );
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



