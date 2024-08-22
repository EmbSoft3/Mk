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
* @file mk_hid_setUsageValue.c
* @brief Définition de la fonction mk_hid_setUsageValue.
* @date 6 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_sendUsageRequest ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Le buffer USB vient d'être écrit avec la valeur du 'Report'. Il est temps d'envoyer la dernière transaction du transfert */
   /* Si la transaction doit s'effectuer via une interruption */
   if ( p_hidDevice->outEndpoint != K_MK_NULL )
   {
      /* Réalisation d'une transaction USB via la requête d'interruption */
      /* Le nombre d'octets écrits dans le buffer de données HID est stocké dans la variable 'byteOffset' */
      /* On ne compare pas cette valeur avec la taille maximale d'un paquet car la variable ByteRemaining est forcément inférieure ou égale */
      /* à la taille maximale d'un paquet. */
      l_result = mk_hid_setInterrupt ( p_hidDevice, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf, ( uint16_t ) ( p_parser->byteOffset ) );

      /* Actualisation du nombre maximal de bits disponibles avant de déclencher un nouveau transfert */
      p_parser->bitNumber = ( uint32_t ) p_hidDevice->outEndpoint->wMaxPacketSize << 3;
   }

   /* Sinon */
   else
   {
      /* Réalisation d'une transaction USB via une requête de contrôle */
      /* Le nombre d'octets écrits dans le buffer de données HID est stocké dans la variable 'byteOffset' */
      /* On ne compare pas cette valeur avec la taille maximale d'un paquet car la variable ByteRemaining est forcément inférieure ou égale */
      /* à la taille maximale d'un paquet. */
      l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf,
                                   ( uint32_t ) ( K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1 ), p_parser->byteOffset );

      /* Actualisation du nombre maximal de bits disponibles avant de déclencher un nouveau transfert */
      p_parser->bitNumber = ( uint32_t ) p_hidDevice->device->deviceDescriptor.bMaxPacketSize0 << 3;
   }

   /* Si le paquet n'est pas acquitté, une erreur s'est produite */
   if ( ( p_pipe->status & K_MK_HCD_FLAG_ACK ) != K_MK_HCD_FLAG_ACK )
   {
      /* Actualisation de l'état du périphérique */
      p_hidDevice->state |= K_MK_HID_DEVICE_ERROR_STATE;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le nombre de données restantes à récupérer est supérieure à la taille maximale d'un paquet */
   if ( p_parser->byteRemaining > p_hidDevice->outEndpoint->wMaxPacketSize )
   {
      /* Actualisation du nombre de données restantes */
      p_parser->byteRemaining = ( uint32_t ) ( p_parser->byteRemaining - p_hidDevice->outEndpoint->wMaxPacketSize );
   }

   /* Sinon */
   else
   {
      /* Le nombre de données restantes à transférer est nul */
      p_parser->byteRemaining = 0;
   }

   /* Actualisation de l'offset du buffer et du nombre de bits disponibles */
   p_parser->byteOffset = 0;
   p_parser->bitAvailable = 8;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setOutputBuffer ( T_mkHIDUsageParser* p_parser, uint32_t p_remainingSize )
{
   /* Déclaration des variables de travail */
   uint32_t l_chunk, l_shift;

   /* Si une adresse a été configurée */
   if ( p_parser->usageBuf != K_MK_NULL )
   {
      /* Détermination de la valeur de décalage */
      l_shift = ( uint32_t ) ( ( ( ~p_remainingSize ) + 1 ) & 0x7 );

      /* Récupération du morceau de données dans l'octet courant */
      l_chunk = ( uint32_t ) p_parser->usageBuf [ 0 ] & ( uint32_t ) ( 0xFF >> l_shift );

      /* Actualisation du buffer USB */
      g_mkHIDPacketBuf [ p_parser->byteOffset ] = ( uint8_t ) ( g_mkHIDPacketBuf [ p_parser->byteOffset ] | ( l_chunk << ( 8 - p_parser->bitAvailable ) ) );
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

T_mkCode mk_hid_setUsageValue ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportTable* p_table )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_parser != K_MK_NULL ) && ( p_table != K_MK_NULL ) )
   {
      /* Tant que l'intégralité de l'usage n'a pas été récupéré */
      while ( ( p_parser->usageSize != 0 ) && ( l_result == K_MK_OK ) && ( ( p_hidDevice->state & K_MK_HID_DEVICE_ERROR_STATE ) != K_MK_HID_DEVICE_ERROR_STATE ) )
      {
         /* Le report de certain périphérique est constitué de plusieurs transactions. Ce cas est géré ci-dessous en vérifiant que des */
         /* octets restent à transmettre et que l'intégralité des bits de la transaction courante ont été traités. */

         /* Si une nouvelle transaction doit être déclenchée */
         if ( ( p_parser->bitNumber == 0 ) && ( p_parser->byteRemaining != 0 ) )
         {
            /* Déclenchement d'une nouvelle transaction sur le bus */
            l_result = mk_hid_sendUsageRequest ( p_hidDevice, p_pipe, p_parser );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si l'usage peut être partiellement ou entièrement récupéré */
            if ( p_parser->usageSize >= p_parser->bitAvailable )
            {
               /* Actualisation du buffer de sortie HID */
               mk_hid_setOutputBuffer ( p_parser, p_parser->bitAvailable );

               /* Actualisation des variables */
               p_parser->bitNumber -= p_parser->bitAvailable;
               p_parser->usageSize -= p_parser->bitAvailable;
               p_parser->bitAvailable = 8;
               p_parser->byteOffset++;
            }

            /* Sinon */
            else
            {
               /* Actualisation du buffer de sortie HID */
               mk_hid_setOutputBuffer ( p_parser, p_parser->usageSize );

               /* Actualisation des variables */
               p_parser->bitAvailable -= p_parser->usageSize;
               p_parser->bitNumber -= p_parser->usageSize;
               p_parser->usageSize = 0;
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
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


