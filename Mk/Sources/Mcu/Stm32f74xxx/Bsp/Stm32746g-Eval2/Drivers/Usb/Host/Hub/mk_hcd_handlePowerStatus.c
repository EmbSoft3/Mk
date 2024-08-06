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
* @file mk_hcd_handlePowerStatus.c
* @brief Définition de la fonction mk_hcd_handlePowerStatus.
* @date 15 sept. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handlePowerStatus ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_portNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Si un périphérique est connecté sur le bus */
      if ( p_device != K_MK_NULL )
      {
         /* Réinitialisation de l'état de celui-ci */
         p_device->state &= ( T_mkHCDDeviceState ) ( ~K_MK_HCD_DEVICE_OVERCURRENT );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Activation de l'alimentation du port */
      l_result = mk_hcd_setPortFeature ( p_hub, p_pipe, ( uint16_t ) K_MK_HCD_PORT_POWER, ( uint16_t ) ( p_portNumber ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Attente de la stabilisation de l'alimentation */
         l_result = mk_task_sleep ( ( uint32_t ) ( ( uint32_t ) ( p_hub->hubDescriptor->bPwrOn2PwrGood ) * 2 ) + 200 );
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


