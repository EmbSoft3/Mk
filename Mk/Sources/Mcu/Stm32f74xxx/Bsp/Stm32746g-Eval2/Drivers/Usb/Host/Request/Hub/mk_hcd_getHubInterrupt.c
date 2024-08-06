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
* @file mk_hcd_getHubInterrupt.c
* @brief Définition de la fonction mk_hcd_getHubInterrupt.
* @date 12 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint16_t mk_hcd_getHubPacketLength ( T_mkHCDDevice* p_hub )
{
   /* Déclaration de la variable de retour */
   uint16_t l_result = p_hub->hubDescriptor->bNbrPorts >> 3;

   /* Déclaration de travail */
   uint16_t l_modulo = ( uint16_t ) ( p_hub->hubDescriptor->bNbrPorts - ( l_result << 3 ) );

   /* Si un octet supplémentaire doit être ajouté */
   if ( l_result != l_modulo )
   {
      /* Actualisation de la variable de retour */
      l_result = ( uint16_t ) ( l_result + 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_getHubInterrupt ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t* p_buf, T_mkHCDPipeStatus* p_status, uint16_t p_bufLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pipe de sauvegarde */
   T_mkHCDPipe l_tmpPipe;

   /* Déclaration d'une variable stockant la taille d'un paquet */
   uint16_t l_packetLength;

   /* Si les paramètres sont valides */
   if ( ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_buf != K_MK_NULL ) && ( p_status != K_MK_NULL ) )
   {
      /* Réalisation d'une copie temporaire du pipe */
      l_result = mk_hcd_copyPipe ( p_pipe, &l_tmpPipe );

      /* Si la copie a été effectuée */
      if ( l_result == K_MK_OK )
      {
         /* Reconfiguration du pipe */
         l_result = mk_hcd_setPipe ( p_pipe, K_MK_HCD_ENDPOINT_INTERRUPT,
                                     p_hub->interfaceDescriptor->endpoint->bEndpointAddress, p_hub->interfaceDescriptor->endpoint->wMaxPacketSize, p_pipe->timeout );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération de la taille d'un paquet sur le pipe d'interruption */
            l_packetLength = mk_hcd_getHubPacketLength ( p_hub );

            /* Si le nombre d'octets à récupérer est plus petit que la taille du buffer */
            if ( l_packetLength <= p_bufLength )
            {
               /* Transmission d'une requête de statut */
               /* Pour une transaction de type INTERRUPT, le token présent en paramètre est sans importance. Le token utilisé est stocké dans le structure de type T_mkHCDDevice. */
               l_result = mk_hcd_sendPipe ( p_hub, p_hub->interfaceDescriptor->endpoint, p_pipe, ( uint8_t* ) p_buf,
                                          ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA0 ), l_packetLength );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Enregistrement du résultat de la requête */
            *p_status = p_pipe->status;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Reconfiguration du pipe */
         l_result |= mk_hcd_copyPipe ( &l_tmpPipe, p_pipe );
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

