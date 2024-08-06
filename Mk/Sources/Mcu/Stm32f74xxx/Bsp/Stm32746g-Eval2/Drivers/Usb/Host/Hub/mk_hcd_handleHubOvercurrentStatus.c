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
* @file mk_hcd_handleHubOvercurrentStatus.c
* @brief Définition de la fonction mk_hcd_handleHubOvercurrentStatus.
* @date 16 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleHubOvercurrentStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_portNumber;

   /* Si les paramètres sont valides */
   if ( ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Si une surcharge a été détectée */
      if ( p_hub->hubDescriptor->hHubStatus.overCurrent == 1 )
      {
         /* Pour chaque port du hub */
         for ( l_portNumber = 0 ; l_portNumber < p_hub->hubDescriptor->bNbrPorts ; l_portNumber++ )
         {
            /* Réinitialisation du drapeau de surcharge */
            l_result = mk_hcd_clearPortFeature ( p_hub, p_pipe, ( uint16_t ) K_MK_HCD_CHANGE_PORT_OVERCURRENT, ( uint16_t ) ( l_portNumber ) );

            /* Désactivation de l'alimentation du port */
            /* On ne teste pas le résultat de la fonction précédente car toutes les actions sont réalisées sans condition. */
            l_result |= mk_hcd_clearPortFeature ( p_hub, p_pipe, ( uint16_t ) K_MK_HCD_PORT_POWER, ( uint16_t ) ( l_portNumber ) );
         }

         /* Signalisation de la déconnexion du périphérique */
         l_result |= mk_hcd_signalDisconnectEvent ( p_hub->nextHubDevice );

         /* Actualisation de l'état du périphérique */
         p_hub->state |= K_MK_HCD_DEVICE_OVERCURRENT;

         /* Modification du timeout de rafraichissement du pipe */
         p_hub->interfaceDescriptor->endpoint->tick.period = K_MK_HCD_OVERCURRENT_TIMEOUT;

         /* Simulation d'un événement afin de réactiver l'alimentation à la prochaine séquence */
         l_result |= mk_hcd_setPortEvent ( p_hub->hubDescriptor->bStatusBuf, l_portNumber );
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



