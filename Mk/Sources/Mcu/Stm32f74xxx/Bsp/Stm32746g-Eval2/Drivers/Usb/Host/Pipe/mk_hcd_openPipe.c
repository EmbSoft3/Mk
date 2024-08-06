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
* @file mk_hcd_openPipe.c
* @brief Définition de la fonction mk_hcd_openPipe.
* @date 21 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_takeChannel ( T_mkHCDHandler* p_handler, uint8_t* p_channel )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une variable de comptage */
   uint8_t l_counter;

   /* Déclaration d'une variable contenant le nombre total de canaux de communication */
   uint8_t l_channelNumber = K_MK_USB_OTGHS_CHANNEL_NUMBER;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_channel != K_MK_NULL ) )
   {
      /* Si le périphérique analysé est le périphérique USB_OTGFS */
      if ( p_handler->bus == K_USB_OTGFS )
      {
         /* Actualisation du nombre total de canaux de communicaton */
         l_channelNumber = K_MK_USB_OTGFS_CHANNEL_NUMBER;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la variable de retour */
      *p_channel = K_MK_USB_CHANNEL_NUMBER;

      /* Entrée en section critique */
      l_result = mk_mutex_take ( p_handler->channelMutex, K_MK_TASK_WAIT_FOREVER );

      /* Si la prise du mutex a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Pour chaque canal de communication */
         for ( l_counter = 0 ; l_counter < l_channelNumber ; l_counter++ )
         {
            /* Si le canal est disponible */
            if ( p_handler->channelTable [ l_counter ] == K_MK_HCD_CHANNEL_NOT_USED )
            {
               /* Actualisation de l'état du canal */
               p_handler->channelTable [ l_counter ] = K_MK_HCD_CHANNEL_USED;

               /* Actualisation de la variable de retour */
               *p_channel = l_counter;

               /* Arrêt de la boucle */
               l_counter = K_MK_USB_CHANNEL_NUMBER;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Sortie de la section critique */
         l_result = mk_mutex_release ( p_handler->channelMutex );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_openPipe ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe, uint8_t p_endpointType, uint8_t p_endpointNumber, uint16_t p_endpointMaxPacketSize, uint32_t p_timeout )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Si les paramètres d'entrées sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Réinitialisation du pipe */
      _writeWords ( p_pipe, 0, sizeof ( T_mkHCDPipe ) >> 2 );

      /* Allocation d'un canal de communication */
      l_result = mk_hcd_takeChannel ( p_handler, &p_pipe->channel );

      /* Si l'éxécution de la fonction a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Si l'allocation du canal a réussi */
         if ( p_pipe->channel != K_MK_USB_CHANNEL_NUMBER )
         {
            /* Configuration des attributs du pipe */
            p_pipe->endpointType = p_endpointType;
            p_pipe->endpointNumber = p_endpointNumber;
            p_pipe->endpointMaxPacketSize = p_endpointMaxPacketSize;
            p_pipe->timeout = p_timeout;

            /* Actualisation de la variable de retour */
            l_result = K_MK_OK;
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_MALLOC;
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


