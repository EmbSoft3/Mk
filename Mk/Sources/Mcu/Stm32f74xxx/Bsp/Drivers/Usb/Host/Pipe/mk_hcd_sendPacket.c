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
* @file mk_hcd_sendPacket.c
* @brief Définition de la fonction mk_hcd_sendPacket.
* @date 15 juin 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hcd_getPacketCount ( uint16_t p_maxPacketSize, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Si la taille des données est supérieure à la taille maximale d'un paquet */
   if ( p_length > p_maxPacketSize )
   {
      /* Détermination du nombre de paquets */
      l_result = ( ( uint32_t ) p_length + ( uint32_t ) p_maxPacketSize - 1 ) / p_maxPacketSize;
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

static void mk_hcd_initTransaction ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length, uint32_t p_packetNumber )
{
   /* Déclaration d'un canal USB */
   T_USBOTGChannel l_channel;

   /* Déclaration d'une variable de travail */
   uint32_t l_tmp = 0;

   /* Réinitialisation de la structure de configuration */
   _writeWords ( &l_channel, 0, K_USB_CHANNEL_SIZE );

   /* Configuration du canal de communication */
   l_channel.cfgRegister.field.endPointType = ( uint8_t ) ( p_pipe->endpointType & 0x3 );                                           /* Type de la terminaison */
   l_channel.cfgRegister.field.endPointDirection = ( uint8_t ) ( p_pipe->endpointDirection & 0x1 );                                 /* Direction du transfert */
   l_channel.cfgRegister.field.deviceAddr = ( uint8_t ) ( p_device->layer.deviceAddr & 0x7F );                                      /* Adresse du dispositif */
   l_channel.cfgRegister.field.speed = ( uint8_t ) ( ( p_device->layer.speed >> 1 ) & 0x1 );                                        /* Vitesse du dispositif (LS ou FS/HS) */
   l_channel.cfgRegister.field.endPointNumber = ( uint8_t ) ( p_pipe->endpointNumber & 0xF );                                       /* Numéro de la terminaison */
   l_channel.cfgRegister.field.transactionPerFrame = 1;                                                                             /* Une transaction par trame obligatoirement */
   l_channel.cfgRegister.field.maxPacketSize = ( uint16_t ) ( p_pipe->endpointMaxPacketSize & 0x7FF );                              /* Nombre d'octets maximal par paquets */
   l_channel.transferRegister.field.ping = 0;                                                                                       /* Pas d'émission d'un token PING */
   l_channel.transferRegister.field.pid = ( uint8_t ) ( p_pipe->token & 0x3 );                                                      /* PID initial de la transaction */
   l_channel.transferRegister.field.packetCount = ( uint16_t ) ( p_packetNumber & 0x3FF );                                          /* Nombre de paquets dans la transaction */
   l_channel.transferRegister.field.transferSize = ( uint32_t ) ( p_length & 0x7FFFF);                                              /* Taille du transfert en octets (multiple de la taille maximal d'un paquet) */
   l_channel.dmaAddr = ( uint32_t ) p_buf;                                                                                          /* Adresse de base des données à transmettre */

   /* Si la transaction est de type périodique */
   if ( ( p_pipe->endpointType == K_USB_INTERRUPT_ENDPOINT ) || ( p_pipe->endpointType == K_USB_ISOCHRONOUS_ENDPOINT ) )
   {
      /* La transaction doit se déclencher sur une trame impaire */
      l_channel.cfgRegister.field.oddFrame = 1;                                                                                     /* Odd Frame */
   }

   /* Sinon */
   else
   {
      /* Détermination du prochain numéro de trame */
      l_tmp = ( uint32_t ) ( ~ usb_getFrameNumber ( p_handler->bus ) );

      /* La transaction peut se produire sur une trame paire ou impaire */
      l_channel.cfgRegister.field.oddFrame = ( uint32_t ) ( l_tmp ) & 0x1;                                                          /* Odd/Even Frame */
   }

   /* Si la transaction est de type 'BULK-OUT-HS' */
   if ( ( p_device->layer.speed == K_USB_HIGH_SPEED ) && ( p_pipe->endpointType == K_USB_BULK_ENDPOINT ) &&
        ( p_pipe->endpointDirection == K_USB_OUT_ENDPOINT ) )
   {
      /* La transaction doit se déclencher sur une trame impaire */
      l_channel.transferRegister.field.ping = 1;                                                                                    /* Emission préalable d'un tocken PING */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Configuration et activation du canal */
   usb_setChannel ( p_handler->bus, p_pipe->channel, &l_channel );                                                                  /* Configuration du canal */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_sendPackets ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint8_t* l_buf = p_buf;
   uint32_t l_currentPacketsNumber = 0, l_numberOfPacketsTransmitted = 0, l_length = 0, l_offset = 0;

   /* Déclaration d'une variable stockant le nombre de paquets de la transaction */
   uint32_t l_totalNumberOfPackets = mk_hcd_getPacketCount ( p_pipe->endpointMaxPacketSize, p_length );

   /* Tant qu'aucune erreur ne s'est produite ou tant que l'intégralité des paquets n'ont pas été transmis */
   while ( ( l_result == K_MK_OK ) && ( ( p_pipe->status & K_MK_HCD_ERROR_STALL ) != K_MK_HCD_ERROR_STALL ) && ( l_totalNumberOfPackets != 0 ) )
   {
      /* Actualisation du nombre de paquets à transmettre */
      p_pipe->numberOfPackets = l_totalNumberOfPackets;

      /* Limitation du nombre de paquet à transmettre */
      l_currentPacketsNumber = l_totalNumberOfPackets;

      /* Si la boucle a été exécutée au moins une fois (transfert de 1023 paquets), les PIDs doivent être actualisé */
      if ( l_offset != 0 )
      {
         /* Permutation des PIDs */
         if ( p_pipe->token == K_USB_PID_DATA1 )
         {
            /* Actualisation du PID */
            p_pipe->token = K_USB_PID_DATA0;
         }

         /* Sinon */
         else
         {
            /* Actualisation du PID */
            p_pipe->token = K_USB_PID_DATA1;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le nombre de paquets est supérieurs à la limite fixées par le périphérique USB */
      if ( l_totalNumberOfPackets > K_MK_HCD_MAX_NUMBER_OF_PACKETS )
      {
         /* Actualisation du nombre de paquets à transmettre */
         p_pipe->numberOfPackets = K_MK_HCD_MAX_NUMBER_OF_PACKETS;

         /* Limitation du nombre de paquets */
         l_currentPacketsNumber = K_MK_HCD_MAX_NUMBER_OF_PACKETS;

         /* Actualisation de la taille du transfert */
         l_length = ( l_currentPacketsNumber * p_pipe->endpointMaxPacketSize );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la taille du transfert */
         l_length = p_length;
      }

      /* Initialisation de la transaction */
      mk_hcd_initTransaction ( p_handler, p_device, p_pipe, &l_buf [ l_offset ], l_length, l_currentPacketsNumber );

      /* Transmission des paquets sur le bus */
      l_result = mk_hcd_startTransfer ( p_handler, p_device, p_pipe );

      /* Actualisation de l'offset du buffer */
      l_offset = ( uint32_t ) ( l_offset + l_length );

      /* Actualisation de la longueur de la transaction */
      p_length = ( uint32_t ) ( p_length - l_length );

      /* Actualisation du nombre de paquet à transmettre */
      l_totalNumberOfPackets = ( uint32_t ) ( l_totalNumberOfPackets - l_currentPacketsNumber );

      /* Actualisation du nombre de paquets transmis */
      l_numberOfPacketsTransmitted = ( uint32_t ) ( l_numberOfPacketsTransmitted + p_pipe->numberOfPackets );
   }

   /* Actualisation du nombre de paquet transmis */
   p_pipe->numberOfPackets = l_numberOfPacketsTransmitted;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_sendPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length )
{
   /* Déclaration d'une variable de retour  */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_buf != K_MK_NULL ) )
   {
      /* Transmission des paquets sur le bus */
      l_result = mk_hcd_sendPackets ( p_handler, p_device, p_pipe, p_buf, p_length );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



