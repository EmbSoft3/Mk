/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_msc_openPipe.c
* @brief Définition de la fonction mk_msc_openPipe.
* @date 21 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_openPipe ( T_mkMSCDevice* p_mscDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_mscDevice != K_MK_NULL )
   {
      /* Si le protocole de transport est de type 'Bulk-Only' */
      if ( p_mscDevice->interface->bInterfaceProtocol == K_MK_MSC_PROTOCOL_BBB )
      {
         /* Ouverture du pipe de contrôle */
         /* Etant donné que l'instance du 'pipe' est conservée dans le périphérique, on peut ouvrir et fermer le pipe sans perdre les données de permutation des tokens. */
         l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler, &p_mscDevice->ctrlPipe, K_MK_HCD_ENDPOINT_CONTROL, K_MK_HCD_ENDPOINT0, p_mscDevice->device->deviceDescriptor.bMaxPacketSize0, K_MK_HCD_TIMEOUT );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ouverture du pipe de type 'Bulk-In' */
            l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler, &p_mscDevice->inPipe, K_MK_HCD_ENDPOINT_BULK, p_mscDevice->inEndpoint->bEndpointAddress & 0xF, p_mscDevice->inEndpoint->wMaxPacketSize, 1500 );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Ouverture d'un pipe de type 'BulkOut' */
               l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler, &p_mscDevice->outPipe, K_MK_HCD_ENDPOINT_BULK, p_mscDevice->outEndpoint->bEndpointAddress & 0xF, p_mscDevice->outEndpoint->wMaxPacketSize, 1500 );

               /* Si une erreur s'est produite */
               if ( l_result != K_MK_OK )
               {
                  /* Fermeture des pipes */
                  l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler,  &p_mscDevice->ctrlPipe );
                  l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler,  &p_mscDevice->inPipe );
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
               /* Fermeture du pipe de contrôle */
               l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler,  &p_mscDevice->ctrlPipe );
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

