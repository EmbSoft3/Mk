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
* @file mk_hid_dispatchInput.c
* @brief Définition de la fonction mk_hid_dispatchInput.
* @date 4 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_dispatchInput ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pipe */
   T_mkHCDPipe l_pipe;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_hidDevice != K_MK_NULL ) )
   {
      /* Ouverture d'un pipe en mode INTERRUPT_IN */
      l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe, K_MK_HCD_ENDPOINT_INTERRUPT, p_hidDevice->inEndpoint->bEndpointAddress & 0xF,
                                   p_hidDevice->inEndpoint->wMaxPacketSize, K_MK_HCD_TIMEOUT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération et décodage des reports */
         l_result = mk_hid_getDeviceReport ( p_hidDevice, &l_pipe, K_MK_NULL );

         /* Fermeture du pipe */
         l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe );
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


