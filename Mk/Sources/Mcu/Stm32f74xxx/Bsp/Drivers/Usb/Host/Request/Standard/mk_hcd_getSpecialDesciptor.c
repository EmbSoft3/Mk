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
* @file mk_hcd_getSpecialDesciptor.c
* @brief Définition de la fonction mk_hcd_getSpecialDesciptor.
* @date 17 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_setSpecialDescriptorField ( uint8_t* p_source, uint8_t* p_destination, uint8_t* p_offset, uint16_t* p_availableSize )
{
   /* Déclaration d'une variable contenant l'offset courante */
   uint8_t l_offset = *p_offset;

   /* Déclaration d'une variable stockant la taille disponible */
   uint16_t l_availableSize = *p_availableSize;

   /* Enregistrement de la taille du descripteur */
   *p_destination = p_source [ l_offset ];

   /* Actualisation de l'offset courante*/
   *p_offset = ( uint8_t ) ( l_offset + 1 );

   /* Actualisation de la taille disponible */
   *p_availableSize = ( uint8_t ) ( l_availableSize - 1 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_getSpecialDescriptorPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_token, uint16_t* p_packetLength, uint16_t* p_remainingByte )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si la taille du descripteur est inférieure à la taille maximale d'un paquet */
   if ( *p_remainingByte < p_device->deviceDescriptor.bMaxPacketSize0 )
   {
      /* Configuration de la taille du paquet */
      *p_packetLength = *p_remainingByte;

      /* Actualisation du nombre d'octets à récupérer */
      *p_remainingByte = 0;
   }

   /* Sinon */
   else
   {
      /* Actualisation du nombre d'octets à récupérer */
      *p_remainingByte = ( uint16_t ) ( ( *p_remainingByte ) - p_device->deviceDescriptor.bMaxPacketSize0 );
   }

   /* Récupération d'un segment du descripteur */
   l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) p_handler->packetBuf, ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | p_token ), ( *p_packetLength ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_isWantedInterface ( T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDInterfaceDescriptor* p_descriptor, uint8_t* p_interfaceFound )
{
   /* L'interface cible vient d'être trouvée, on actualise donc un verrou pour enregistrer le descripteur recherché */
   if ( ( p_descriptor->bDesciptorType == ( uint8_t ) ( K_MK_HCD_DESC_INTERFACE >> 8 ) ) &&
        ( p_interface->bInterfaceNumber == p_descriptor->bInterfaceNumber ) && ( p_interface->bAlternateSetting == p_descriptor->bAlternateSetting ) )
   {
      *p_interfaceFound = 1;
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

static uint8_t mk_hid_isWantedDescriptor ( T_mkHCDInterfaceDescriptor* p_descriptor, uint8_t* p_interfaceFound, uint8_t p_class, uint8_t p_descriptorLength )
{
   /* Si le descripteur à copier a été trouvé */
   /* La comparaison '<=' est présente pour empécher un débordement si la taille du descripteur est supérieur à l'espace réservé par l'utilisateur */
   /* Une comparaison '==' n'est pas utilisé car il n'est pas obligatoire de récupérer l'intégralité du descripteur */
   if ( ( p_descriptor->bDesciptorType == p_class ) && ( p_descriptor->bLength <= p_descriptorLength ) )
   {
      /* Le descripteur recherché a été trouvé, on réactualise la variable 'p_interfaceFound' pour bloquer le processus */
      /* de copie lorsque le descripteur aura été entièrement copié. */
      *p_interfaceFound = 0;
   }

   /* Sinon */
   else
   {
      /* Actualisation du type du descriptor (ce code ne référence pas de descripteur) */
      p_descriptor->bDesciptorType = 0;
   }

   /* Retour */
   return ( p_descriptor->bDesciptorType );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint8_t mk_hcd_getSpecialDescriptorHead ( T_mkHCDHandler* p_handler, T_mkHCDInterfaceDescriptor* p_descriptor, uint8_t* p_offset, uint16_t* p_availableSize, uint8_t p_step )
{
   /* Si récupération de la taille du descripteur */
   if ( p_step == 0 )
   {
      /* Enregistrement de la taille du descripteur */
      mk_hcd_setSpecialDescriptorField ( p_handler->packetBuf, &p_descriptor->bLength, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 1;
   }

   /* Sinon si récupération du type du descripteur */
   else if ( p_step == 1 )
   {
      /* Enregistrement du type du descripteur */
      mk_hcd_setSpecialDescriptorField ( p_handler->packetBuf, &p_descriptor->bDesciptorType, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 2;
   }

   /* Sinon si récupération d'un numéro d'interface */
   else if ( p_step == 2 )
   {
      /* Enregistrement du numéro de l'interface */
      mk_hcd_setSpecialDescriptorField ( p_handler->packetBuf, &p_descriptor->bInterfaceNumber, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 3;
   }

   /* Sinon si récupération d'une interface alternative */
   else if ( p_step == 3 )
   {
      /* Enregistrement du numéro de l'interface */
      mk_hcd_setSpecialDescriptorField ( p_handler->packetBuf, &p_descriptor->bAlternateSetting, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 4;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( p_step );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_parse ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDInterfaceDescriptor* p_interface, uint8_t* p_buf, uint32_t p_register )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un descripteur d'interface */
   T_mkHCDInterfaceDescriptor l_descriptor;

   /* Déclaration des variables de travail */
   uint8_t l_step = 0, l_offset = 0, l_remainder = 0, l_interfaceFound = 0, l_class = ( p_register >> 8 ) & 0xFF;

   /* Configuration du nombre de données initiales */
   uint16_t l_availableSize, l_packetLength = p_device->deviceDescriptor.bMaxPacketSize0;

   /* Configuration de la taille totale du message */
   uint16_t l_length = p_device->configurationDescriptor.wTotalLength, l_remainingByte = ( uint16_t ) ( p_device->configurationDescriptor.wTotalLength );

   /* Récupération du premier segment du descripteur de configuration */
   l_result = mk_hcd_getSpecialDescriptorPacket ( p_handler, p_device, p_pipe, K_MK_HCD_PID_DATA1, &l_packetLength, &l_remainingByte );

   /* Configuration du nombre d'octets disponibles suite à la transaction */
   l_availableSize = l_packetLength;

   /* Tant que l'intégralité de la structure n'a pas été reçue */
   while ( ( l_length != 0 ) && ( l_result == K_MK_OK ) )
   {
      /* Si l'entête du descripteur doit être récupérée */
      if ( l_step < 4 )
      {
         /* Récupération des 4 premiers octets du descripteur */
         l_step = mk_hcd_getSpecialDescriptorHead ( p_handler, &l_descriptor, &l_offset, &l_availableSize, l_step );
      }

      /* Sinon si il est temps d'identifier l'interface à récupérer */
      else if ( l_step == 4 )
      {
         /* Détermination si l'interface courante est l'interface recherchée */
         mk_hid_isWantedInterface ( p_interface, &l_descriptor, &l_interfaceFound );

         /* Si l'interface a été trouvée */
         if ( l_interfaceFound == 1 )
         {
            /* Détermination si le descripteur courant est le descripteur recherché */
            l_descriptor.bDesciptorType = mk_hid_isWantedDescriptor ( &l_descriptor, &l_interfaceFound, l_class, p_register & 0xFF );

            /* Si le descripteur a été trouvé */
            if ( l_descriptor.bDesciptorType != 0 )
            {
               /* Ecriture de l'entête du descripteur */
               _copy ( p_buf, &l_descriptor, 4 );
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
            /* Actualisation du type du descriptor (ce code ne référence pas de descripteur) */
            l_descriptor.bDesciptorType = 0;
         }

         /* Actualisation de la taille restante dans le paquet */
         l_remainder = ( uint8_t ) ( l_descriptor.bLength - 4 );

         /* Activation de la prochaine étape */
         l_step = 5;
      }

      /* Sinon, le contenu du descripteur doit être récupéré */
      else
      {
         /* Si le descripteur peut être entièrement copié sans demander de paquets supplémentaires */
         if ( l_availableSize >= l_remainder )
         {
            /* Si une copie doit être effectuée */
            if ( l_descriptor.bDesciptorType == l_class )
            {
               /* Copie du descripteur d'interface */
               _copy ( ( uint8_t* ) ( p_buf + ( *p_buf ) - l_remainder ), p_handler->packetBuf + l_packetLength - l_availableSize, ( uint32_t ) l_remainder );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du nombre de données disponibles dans le buffer */
            l_availableSize = ( uint8_t ) ( l_availableSize - l_remainder );

            /* Actualisation de l'offset dans le buffer */
            l_offset = ( uint8_t ) ( l_offset + l_remainder );

            /* Retrait de la taille du descripteur à longueur totale du descripteur */
            l_length = ( uint8_t ) ( l_length - l_descriptor.bLength );

            /* Activation de la prochaine étape */
            /* Le descripteur a été entièrement récupéré */
            /* La variable 'l_remainder' sera réinitialisé dans l'étape 0. */
            l_step = 0;
         }

         /* Sinon */
         else
         {
            /* Si une copie doit être effectuée */
            if ( l_descriptor.bDesciptorType == l_class )
            {
               /* Copie d'un segment du descripteur d'interface */
               _copy ( ( uint8_t* ) ( p_buf + ( *p_buf ) - l_remainder ), p_handler->packetBuf + l_packetLength - l_availableSize, ( uint32_t ) l_availableSize );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du nombre de données restant à récupérer dans le descripteur courant */
            l_remainder = ( uint8_t ) ( l_remainder - l_availableSize );

            /* Actualisation du nombre de données disponibles dans le buffer */
            /* Un nouveau paquet de données doit être demandé */
            l_availableSize = 0;
         }
      }

      /* Si une nouvelle requête doit être effectuée */
      if ( ( l_length != 0 ) && ( l_availableSize == 0 ) && ( l_result == K_MK_OK ) )
      {
         /* Récupération du segment du descripteur de configuration */
         l_result = mk_hcd_getSpecialDescriptorPacket ( p_handler, p_device, p_pipe, K_MK_HCD_PID_TOOGLE, &l_packetLength, &l_remainingByte );

         /* Configuration du nombre d'octets disponibles suite à la transaction */
         l_availableSize = l_packetLength;

         /* Réinitialisation de l'offset du buffer */
         l_offset = 0;
      }

      /* Sinon*/
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_getSpecialDesciptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, T_mkHCDInterfaceDescriptor* p_interface, T_mkAddr p_buf, uint32_t p_register )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_interface != K_MK_NULL ) && ( p_buf != K_MK_NULL ) )
   {
      /* Si le périphérique possède au moins une configuration */
      if ( p_device->deviceDescriptor.bNumConfigurations != 0 )
      {
         /* Création d'une requête permettant de récupérer le descripteur de configuration */
         l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_GET_DESCRIPTOR, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_STANDARD | K_MK_HCD_DEVICE, K_MK_HCD_DESC_CONFIGURATION, 0, p_device->configurationDescriptor.wTotalLength );

         /* Si aucune erreur ne s'est produite */
          if ( l_result == K_MK_OK )
          {
             /* Transmission de la requête */
             l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

             /* Si aucune erreur ne s'est produite */
             if ( l_result == K_MK_OK )
             {
                /* Récupération du contenu du descripteur spécial */
                l_result = mk_hcd_parse ( p_device->handler, p_device, p_pipe, p_interface, ( uint8_t* ) p_buf, p_register );

                /* Si le contenu du descripteur a été récupéré */
                if ( l_result == K_MK_OK )
                {
                   /* Transmission du paquet d'acquittement (ZLP) */
                   l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );
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
         /* Actualisation de l'état du dispositif */
         p_device->state = K_MK_HCD_DEVICE_NOT_VALID;
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


