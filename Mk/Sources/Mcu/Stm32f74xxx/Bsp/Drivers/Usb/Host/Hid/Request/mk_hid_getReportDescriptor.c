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
* @file mk_hid_getReportDescriptor.c
* @brief Définition de la fonction mk_hid_getReportDescriptor.
* @date 26 oct. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_getReportDescriptorPacket ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint32_t p_token, uint16_t* p_remainingByte )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant le nombre d'octets dans un paquet */
   uint16_t l_packetLength = p_hidDevice->device->deviceDescriptor.bMaxPacketSize0;

   /* Si la taille du descripteur est inférieure à la taille maximale d'un paquet */
   if ( *p_remainingByte < p_hidDevice->device->deviceDescriptor.bMaxPacketSize0 )
   {
      /* Configuration de la taille du paquet */
      l_packetLength = ( *p_remainingByte );

      /* Le nombre d'octets restant à récupérer est nul */
      *p_remainingByte = 0;
   }

   /* Sinon */
   else
   {
      /* Actualisation du nombre d'octet restant à récupérer */
      *p_remainingByte = ( uint16_t ) ( ( *p_remainingByte ) - l_packetLength );
   }

   /* Récupération d'un segment du descripteur */
   l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf, ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | p_token ), l_packetLength );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint8_t mk_hid_getItemLength ( uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   uint8_t l_length;

   /* Récupération de la longueur de l'item */
   l_length = ( uint8_t ) ( ( 1 << ( ( *p_buf ) & 0x3 ) ) >> 1 );

   /* Retour */
   return ( l_length );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setItemType ( T_mkHIDDevice* p_hidDevice, uint8_t* p_buf )
{
   /* Déclaration de la variable de retour */
   uint8_t l_type;

   /* Récupération du type l'item */
   l_type = ( uint8_t ) ( ( *p_buf ) & 0x0C );

   /* Si l'item est un item de type 'Long' */
   if ( l_type == K_MK_HID_ITEM_TYPE_LONG_ITEM )
   {
      /* Actualisation de l'état du périphérique HID */
      /* Le périphérique HID n'est pas suporté */
      p_hidDevice->state |= K_MK_HID_DEVICE_NOT_SUPPORTED;
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

static T_mkCode mk_hid_parseReportDescriptor ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable d'état */
   uint8_t l_step = 0;

   /* Déclaration des variables de travail */
   uint8_t l_length = 0, l_offset = 0;

   /* Déclaration d'un pointeur contenant l'adresse du buffer de données */
   uint8_t* l_pnt = g_mkHIDPacketBuf;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem** l_currentItem;

   /* Déclaration d'une variable stockant le nombre d'octets restant à récupérer */
   uint16_t l_remainingByte = p_length;

   /* Configuration du pointeur d'item */
   l_currentItem = &p_hidDevice->reportDescriptor.item;

   /* Récupération du premier paquet de données du 'Report-Descriptor' */
   l_result = mk_hid_getReportDescriptorPacket ( p_hidDevice, p_pipe, K_MK_HCD_PID_DATA1, &l_remainingByte );

   /* Tant que l'intégralité de la structure n'a pas été analysée et qu'aucune erreur ne s'est produite */
   while ( ( l_result == K_MK_OK ) && ( ( p_hidDevice->state & K_MK_HID_DEVICE_NOT_SUPPORTED ) != K_MK_HID_DEVICE_NOT_SUPPORTED ) &&
           ( p_length != 0 ) )
   {
      /* S'il est temps de récupérer l'identifiant d'un item */
      if ( l_step == 0 )
      {
         /* Allocation d'un nouvel item */
         l_result = mk_pool_allocSafe ( g_mkHIDPool.itemPool, ( T_mkAddr* ) l_currentItem, K_MK_POOL_CLEAR, 0 );

         /* Si l'allocation a réussi */
         if ( ( l_result == K_MK_OK ) && ( ( *l_currentItem ) != K_MK_NULL ) )
         {
            /* Récupération de l'identifiant de l'item */
            ( *l_currentItem )->head.value = ( uint8_t ) ( *l_pnt );

            /* Récupération de la longueur de l'item */
            l_length = mk_hid_getItemLength ( l_pnt );

            /* Récupération du type de l'item */
            mk_hid_setItemType ( p_hidDevice, l_pnt );

            /* Réinitialisation de l'offset */
            l_offset = 0;

            /* Actualisation des variables de travail */
            l_pnt++; p_length--;

            /* Actualisation de l'étape */
            l_step = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Un erreur d'allocation s'est produite */
            /* Le parser va s'arrêter */
         }
      }

      /* Sinon si il est temps de récupérer le contenu de l'item */
      else if ( l_step == 1 )
      {
         /* Si l'intégralité des données de l'item n'ont pas été récupérées */
         if ( l_length != 0 )
         {
            /* Enregistrement de la valeur de l'item */
            ( *l_currentItem )->value = ( uint32_t ) ( ( *l_currentItem )->value | ( uint32_t ) ( ( *l_pnt ) << ( 8 * l_offset ) ) );

            /* Actualisation des variables de travail */
            l_pnt++; l_offset++;
            p_length--; l_length--;
         }

         /* Sinon */
         else
         {
            /* Actualisation de la valeur du pointeur d'item */
            l_currentItem = &( *l_currentItem )->nextItem;

            /* Les données ont été récupérées, l'identifiant du prochain 'Item' doit être récupéré */
            l_step = 0;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* S'il est temps de récupérer un nouveau segment du descripteur */
      if ( ( l_result == K_MK_OK ) && ( l_pnt == &g_mkHIDPacketBuf [ p_hidDevice->device->deviceDescriptor.bMaxPacketSize0 ] ) && ( p_length != 0 ) )
      {
         /* Récupération d'un nouveau paquet de données du 'Report-Descriptor' */
         l_result = mk_hid_getReportDescriptorPacket ( p_hidDevice, p_pipe, K_MK_HCD_PID_TOOGLE, &l_remainingByte );

         /* Actualisation du pointeur de données */
         l_pnt = g_mkHIDPacketBuf;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si une erreur s'est produite ou si le périphérique n'est pas supporté */
   if ( ( l_result != K_MK_OK ) || ( ( p_hidDevice->state & K_MK_HID_DEVICE_NOT_SUPPORTED ) == K_MK_HID_DEVICE_NOT_SUPPORTED ) )
   {
      /* Destruction du 'ReportDescriptor' */
      l_result |= mk_hid_deleteReportDescriptor ( p_hidDevice );
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

T_mkCode mk_hid_getReportDescriptor ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, uint16_t p_interfaceNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant la longueur du descripteur */
   uint16_t l_length;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Détermination de la longueur du descripteur */
      l_length = ( uint16_t ) ( ( uint16_t ) ( p_hidDevice->hidDescriptor.wDescriptorLength [ 0 ] ) | ( ( uint16_t ) ( p_hidDevice->hidDescriptor.wDescriptorLength [ 1 ] ) << 8 ) );

      /* Création d'une requête permettant de récupérer le 'Report Descriptor' */
      l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_GET_DESCRIPTOR, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_STANDARD | K_MK_HCD_INTERFACE, K_MK_HID_REPORT_DESCRIPTOR, p_interfaceNumber, l_length );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de la requête */
         l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération des reports contenus dans le descripteur */
            l_result = mk_hid_parseReportDescriptor ( p_hidDevice, p_pipe, l_length );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Transmission du paquet d'acquittement (ZLP) */
               l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );
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



