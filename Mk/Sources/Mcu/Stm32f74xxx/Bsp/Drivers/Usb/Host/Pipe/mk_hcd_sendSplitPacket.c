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
* @file mk_hcd_sendSplitPacket.c
* @brief Définition de la fonction mk_hcd_sendSplitPacket.
* @date 8 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hcd_getPacketCount ( T_mkHCDPipe* p_pipe, uint16_t p_maxPacketSize, uint32_t p_length )
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

   /* Enregistrement du nombre de paquets à transmettre */
   p_pipe->numberOfPackets = l_result;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_initSplitTransaction ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length, uint16_t p_splitToken, uint8_t p_splitPosition )
{
   /* Déclaration d'un canal USB */
   T_USBOTGChannel l_channel;

   /* Déclaration d'un pointeur de gestionnaire */
   /* Le gestionnaire n'est pas transmis en paramètre pour limiter la quantité à 6 */
   T_mkHCDHandler* l_handler = ( T_mkHCDHandler* ) p_device->handler;

   /* Détermination du nombre de paquets à transmettre */
   uint32_t l_tmp =  ( uint32_t ) mk_hcd_getPacketCount ( p_pipe, p_pipe->endpointMaxPacketSize, p_length );

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
   l_channel.transferRegister.field.pid = ( uint8_t ) ( p_pipe->token & 0x3 );                                                      /* PID de la transaction */
   l_channel.transferRegister.field.packetCount = ( uint16_t ) ( l_tmp & 0x3FF );                                                   /* Nombre de paquets dans la transaction */
   l_channel.transferRegister.field.transferSize = ( uint32_t ) ( p_length & 0x7FFFF);                                              /* Taille du transfert en octets (multiple de la taille maximal d'un paquet) */
   l_channel.dmaAddr = ( uint32_t ) p_buf;                                                                                          /* Adresse de base des données à transmettre */

   /* Configuration de la transaction de type SPLIT */
   l_channel.splitRegister.field.split = K_USB_SPLIT_MODE_ENABLE;                                                                   /* Activation du mode Split */
   l_channel.splitRegister.field.hubAddr = ( uint8_t ) ( p_device->layer.hubSplitAddr & 0x7F );                                     /* Adresse du hub */
   l_channel.splitRegister.field.portAddr = ( uint8_t ) ( p_device->layer.portSplitNumber & 0x7F );                                 /* Numéro du port */
   l_channel.splitRegister.field.transaction = ( uint8_t ) ( p_splitToken & 0x1 );                                                  /* Start or Complete Split Transaction */
   l_channel.splitRegister.field.position = ( uint8_t ) ( p_splitPosition & 0x3 );                                                  /* All, first, middle or end Payload (Isochrone uniquement) */

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
      l_tmp = ( uint32_t ) ( ~ usb_getFrameNumber ( l_handler->bus ) );

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
   usb_setChannel ( l_handler->bus, p_pipe->channel, &l_channel );                                                                  /* Configuration du canal */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_enableTransfer ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Activation d'une transaction de type SSPLIT */
   usb_setStartSplit ( p_handler->bus, p_pipe->channel );

   /* Transmission des paquets sur le bus */
   l_result = mk_hcd_startTransfer ( p_handler, p_device, p_pipe );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_sendSplit ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Configuration d'une transaction de type Start_Split */
   mk_hcd_initSplitTransaction ( p_device, p_pipe, p_buf, p_length, K_USB_START_SPLIT, K_USB_ALL_PAYLOADS );

   /* Effectue */
   do
   {
      /* Si le dernier paquet doit être envoyé sur le bus */
      if ( p_length <= p_pipe->endpointMaxPacketSize )
      {
         /* Transfert d'un nouveau paquet */
         l_result = mk_hcd_enableTransfer ( p_handler, p_device, p_pipe );

         /* Actualisation du nombre d'octets à transmettre */
         p_length = 0;
      }

      /* Sinon */
      else
      {
         /* Transfert du paquet courant */
         l_result = mk_hcd_enableTransfer ( p_handler, p_device, p_pipe );

         /* Actualisation du nombre d'octets à transmettre */
         p_length = ( uint32_t ) ( p_length - p_pipe->endpointMaxPacketSize );
      }

   /* Tant que le transfert n'est pas terminé */
   } while ( ( p_length != 0 ) && ( l_result == K_MK_OK ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_sendSplitPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkAddr p_buf, uint32_t p_length )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Transmission d'un ou plusieurs paquets en mode SPLIT */
      l_result = mk_hcd_sendSplit ( p_handler, p_device, p_pipe, p_buf, p_length );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


