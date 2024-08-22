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
* @file mk_hcd_getConfigurationDescriptor.c
* @brief Définition de la fonction mk_hcd_getConfigurationDescriptor.
* @date 28 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_getConfigurationDescriptorPacket ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint32_t p_token, uint16_t* p_packetLength, uint16_t* p_remainingByte )
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
   l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) p_handler->packetBuf, K_MK_HCD_ENDPOINT_IN | p_token, ( *p_packetLength ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_setConfigurationDescriptorField ( uint8_t* p_source, uint8_t* p_destination, uint8_t* p_offset, uint16_t* p_availableSize )
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

static uint8_t mk_hcd_setConfigurationDescriptorHead ( T_mkHCDHandler* p_handler, T_mkHCDInterfaceDescriptor* p_descriptor, uint8_t* p_offset, uint16_t* p_availableSize, uint8_t p_step )
{
   /* Si la taille du descripteur doit être récupérée */
   if ( p_step == 0 )
   {
      /* Enregistrement de la taille du descripteur */
      mk_hcd_setConfigurationDescriptorField ( p_handler->packetBuf, &p_descriptor->bLength, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 1;
   }

   /* Sinon si le type du descripteur doit être récupéré */
   else if ( p_step == 1 )
   {
      /* Enregistrement du type du descripteur */
      mk_hcd_setConfigurationDescriptorField ( p_handler->packetBuf, &p_descriptor->bDesciptorType, p_offset, p_availableSize );

      /* Activation de la prochaine étape */
      p_step = 2;
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

static T_mkCode mk_hcd_newInterface ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor** p_interface )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface = *p_interface;

   /* Si la première interface va être récupérée */
   if ( l_interface == K_MK_NULL )
   {
      /* Allocation dynamique du premier descripteur d'interface */
      l_result = mk_pool_allocSafe ( g_mkHCDPool.interfacePool, ( T_mkAddr* ) &p_device->interfaceDescriptor, K_MK_POOL_CLEAR, 0 );

      /* Actualisation du pointeur d'interface */
      l_interface = p_device->interfaceDescriptor;
   }

   /* Sinon */
   else
   {
      /* Allocation dynamique d'un descripteur d'interface */
      l_result = mk_pool_allocSafe ( g_mkHCDPool.interfacePool, ( T_mkAddr* ) &l_interface->nextInterface, K_MK_POOL_CLEAR, 0 );

      /* Actualisation du pointeur d'interface */
      l_interface = l_interface->nextInterface;
   }

   /* Actualisation de la variable de retour */
   *p_interface = l_interface;

   /* Si l'allocation a réussi */
   if ( ( l_result != K_MK_OK ) || ( l_interface == K_MK_NULL ) )
   {
      /* Actualisation de la variable de retour */
      l_result |= K_MK_ERROR_MALLOC;
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

static T_mkCode mk_hcd_newEndpoint ( T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDEndpointDescriptor** p_endpoint )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de terminaison */
   T_mkHCDEndpointDescriptor* l_endpoint = *p_endpoint;

   /* Si la première terminaison va être récupérée */
   if ( p_interface->endpoint == K_MK_NULL )
   {
      /* Allocation dynamique du premier descripteur de terminaison */
      l_result = mk_pool_allocSafe ( g_mkHCDPool.endpointPool, ( T_mkAddr* ) &p_interface->endpoint, K_MK_POOL_CLEAR, 0 );

      /* Actualisation du pointeur de terminaison */
      l_endpoint = p_interface->endpoint;
   }

   /* Sinon */
   else
   {
      /* Allocation dynamique d'un descripteur de terminaison */
      l_result = mk_pool_allocSafe ( g_mkHCDPool.endpointPool, ( T_mkAddr* ) &l_endpoint->nextEndpoint, K_MK_POOL_CLEAR, 0 );

      /* Actualisation du pointeur de terminaison */
      l_endpoint = l_endpoint->nextEndpoint;
   }

   /* Actualisation de la variable de retour */
   *p_endpoint = l_endpoint;

   /* Si l'allocation a réussi */
   if ( ( l_result != K_MK_OK ) || ( l_endpoint == K_MK_NULL ) )
   {
      /* Actualisation de la variable de retour */
      l_result |= K_MK_ERROR_MALLOC;
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

static T_mkCode mk_hcd_newDescriptor ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor** p_interface, T_mkHCDEndpointDescriptor** p_endpoint, T_mkHCDInterfaceDescriptor* p_descriptor, uint8_t** p_buf )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une interface doit être allouée */
   if ( p_descriptor->bDesciptorType == ( uint8_t ) ( K_MK_HCD_DESC_INTERFACE >> 8 ) )
   {
      /* Si la taille de l'interface est valide */
      if ( p_descriptor->bLength == K_MK_HCD_INTEFACE_DESCRIPTOR_SIZE )
      {
         /* Allocation d'une nouvelle interface */
         l_result = mk_hcd_newInterface ( p_device, p_interface );

         /* Configuration du pointeur de descripteur */
         *p_buf = ( uint8_t* ) *p_interface;

         /* Si l'allocation a réussi */
         if ( l_result == K_MK_OK )
         {
            /* La structure est automatiquement réinitialisée lors d'une allocation */
            /* Il n'est donc pas nécessaire de réinitialiser les pointeurs */
            /* Cependant, Il faut copier les champs déjà récupérés (bLength et bDescriptorType) dans la nouvelle structure */
            _copy ( *p_interface, p_descriptor, 2 );
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
         /* Actualisation de l'état du périphérique */
         p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
      }
   }

   /* Sinon si une terminaison doit être allouée */
   else if ( p_descriptor->bDesciptorType == ( uint8_t ) ( K_MK_HCD_DESC_ENDPOINT >> 8 ) )
   {
      /* Si la taille de la terminaison est valide */
      if ( ( p_descriptor->bLength == K_MK_HCD_ENDPOINT_DESCRIPTOR_SIZE ) || ( p_descriptor->bLength == K_MK_HCD_AUDIO_ENDPOINT_DESCRIPTOR_SIZE ) )
      {
         /* Allocation d'une nouvelle terminaison */
         l_result = mk_hcd_newEndpoint ( *p_interface, p_endpoint );

         /* Configuration du pointeur de descripteur */
         *p_buf = ( uint8_t* ) *p_endpoint;

         /* Si l'allocation a réussi */
         if ( l_result == K_MK_OK )
         {
            /* La structure est automatiquement réinitialisée lors d'une allocation */
            /* Il n'est donc pas nécessaire de réinitialiser les pointeurs */
            /* Cependant, Il faut copier les champs déjà récupérés (bLength et bDescriptorType) dans la nouvelle structure */
            _copy ( *p_endpoint, p_descriptor, 2 );
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
         /* Actualisation de l'état du périphérique */
         p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation du type du descripteur (ce code ne référence pas de descripteur) */
      p_descriptor->bDesciptorType = 0;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_deleteMemory ( T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs d'interface */
   T_mkHCDInterfaceDescriptor *l_interface, *l_nextInterface;

   /* Déclaration des pointeurs de terminaison */
   T_mkHCDEndpointDescriptor *l_endpoint, *l_nextEndpoint;

   /* Récupération du pointeur d'interface */
   l_interface = p_device->interfaceDescriptor;

   /* Tant que toutes les interfaces n'ont pas été désallouées */
   while ( l_interface != K_MK_NULL )
   {
      /* Enregistrement de l'adresse de la prochaine interface */
      l_nextInterface = l_interface->nextInterface;

      /* Récupération du pointeur de terminaison */
      l_endpoint = l_interface->endpoint;

      /* Tant que toutes les terminaisons de l'interface n'ont pas été désallouées */
      while ( l_endpoint != K_MK_NULL )
      {
         /* Enregistrement de l'adresse de la prochaine terminaison */
         l_nextEndpoint = l_endpoint->nextEndpoint;

         /* Suppression de la mémoire allouée */
         l_result |= mk_pool_freeSafe ( g_mkHCDPool.endpointPool, ( T_mkAddr ) l_endpoint );

         /* Actualisation du pointeur de structure */
         l_endpoint = l_nextEndpoint;
      }

      /* Suppression de la mémoire allouée */
      l_result |= mk_pool_freeSafe ( g_mkHCDPool.interfacePool, ( T_mkAddr ) l_interface );

      /* Actualisation du pointeur de structure */
      l_interface = l_nextInterface;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_parse ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un descripteur d'interface */
   T_mkHCDInterfaceDescriptor l_descriptor;

   /* Déclaration d'un pointeur de descripteur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface = K_MK_NULL;

   /* Déclaration d'un pointeur de terminaison */
   T_mkHCDEndpointDescriptor* l_endpoint = K_MK_NULL;

   /* Déclaration des variables de travail */
   uint8_t  l_step = 0, l_offset = 0, l_remainder = 0, *l_buf = K_MK_NULL;

   /* Déclaration d'une variable stockant le nombre d'octets dans un paquet */
   uint16_t l_packetLength = p_device->deviceDescriptor.bMaxPacketSize0;

   /* Configuration de la taille totale du message */
   uint16_t l_availableSize, l_length = p_device->configurationDescriptor.wTotalLength, l_remainingByte = p_device->configurationDescriptor.wTotalLength;

   /* Récupération du premier segment du descripteur de configuration */
   l_result = mk_hcd_getConfigurationDescriptorPacket ( p_handler, p_device, p_pipe, K_MK_HCD_PID_DATA1, &l_packetLength, &l_remainingByte );

   /* Configuration du nombre d'octets disponibles suite à la transaction */
   l_availableSize = l_packetLength;

   /* Tant que l'intégralité de la structure n'a pas été reçue */
   while ( ( l_length != 0 ) && ( l_result == K_MK_OK ) )
   {
      /* Si l'entête du descripteur du descripteur doit être récupérée */
      if ( l_step < 2 )
      {
         /* Récupération des 4 premiers octets du descripteur */
         l_step = mk_hcd_setConfigurationDescriptorHead ( p_handler, &l_descriptor, &l_offset, &l_availableSize, l_step );
      }

      /* Sinon si le descripteur doit être alloué */
      else if ( l_step == 2 )
      {
         /* Allocation et configuration de l'entête d'un nouveau descripteur (interface ou terminaison) */
         l_result = mk_hcd_newDescriptor ( p_device, &l_interface, &l_endpoint, &l_descriptor, &l_buf );

         /* Actualisation des variables */
         l_remainder = ( uint8_t ) ( l_descriptor.bLength - 2 );

         /* Activation de la prochaine étape */
         l_step = 3;
      }

      /* Sinon, le contenu du descripteur doit être récupéré */
      else
      {
         /* Si le descripteur peut être entièrement copié sans demander de paquets supplémentaires */
         if ( l_availableSize >= l_remainder )
         {
            /* Si une copie doit être effectuée */
            if ( l_descriptor.bDesciptorType != 0 )
            {
               /* Copie du descripteur d'interface ou de terminaison */
               _copy ( ( uint8_t* ) ( l_buf + ( *l_buf ) - l_remainder ), p_handler->packetBuf + l_packetLength - l_availableSize, ( uint32_t ) l_remainder );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du nombre de données disponibles dans le buffer */
            l_availableSize = ( uint8_t ) ( l_availableSize - l_remainder );

            /* Actualisation de l'offset dans le buffer */
            l_offset = ( uint8_t ) ( l_remainder + l_offset );

            /* Retrait de la taille du descripteur à longueur totale du descripteur de configuration */
            l_length = ( uint8_t ) ( l_length - l_descriptor.bLength );

            /* Activation de la prochaine étape */
            /* Le descripteur a été entièrement récupéré */
            /* La variable 'l_remainder' sera réinitialisé dans l'étape 2. */
            l_step = 0;
         }

         /* Sinon */
         else
         {
            /* Si une copie doit être effectuée */
            if ( l_descriptor.bDesciptorType != 0 )
            {
               /* Copie du descripteur d'interface ou de terminaison */
               _copy ( ( uint8_t* ) ( l_buf + ( *l_buf ) - l_remainder ), p_handler->packetBuf + l_packetLength - l_availableSize, ( uint32_t ) l_availableSize );
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
         /* Récupération d'un segment du descripteur de configuration */
         l_result = mk_hcd_getConfigurationDescriptorPacket ( p_handler, p_device, p_pipe, K_MK_HCD_PID_TOOGLE, &l_packetLength, &l_remainingByte );

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

   /* Si une erreur s'est produite */
   if ( l_result != K_MK_OK )
   {
      /* Désallocation de la mémoire allouée */
      l_result |= mk_hcd_deleteMemory ( p_device );
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

T_mkCode mk_hcd_getConfigurationDescriptor ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe, uint16_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_length != 0 ) )
   {
      /* Si le périphérique possède au moins une configuration */
      if ( p_device->deviceDescriptor.bNumConfigurations != 0 )
      {
         /* Création d'une requête permettant de récupérer le descripteur de configuration */
         l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_GET_DESCRIPTOR, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_STANDARD | K_MK_HCD_DEVICE, K_MK_HCD_DESC_CONFIGURATION, 0, p_length );

         /* Si aucune erreur ne s'est produite */
          if ( l_result == K_MK_OK )
          {
             /* Transmission de la requête */
             l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

             /* Si aucune erreur ne s'est produite */
             if ( l_result == K_MK_OK )
             {
                /* Si l'intégralité du descripteur doit être récupéré */
                if ( p_length == p_device->configurationDescriptor.wTotalLength )
                {
                   /* Si le descripteur de configuration est valide */
                   if ( ( p_device->configurationDescriptor.bDesciptorType == ( uint8_t ) ( K_MK_HCD_DESC_CONFIGURATION >> 8 ) ) && ( p_device->configurationDescriptor.bLength == K_MK_HCD_CONFIGURATION_DESCRIPTOR_SIZE ) )
                   {
                      /* Récupération du contenu des interfaces et des terminaisons */
                      l_result = mk_hcd_parse ( p_device->handler, p_device, p_pipe );
                   }

                   /* Sinon */
                   else
                   {
                      /* Actualisation de l'état du périphérique */
                      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
                   }
                }

                /* Sinon */
                else
                {
                   /* Récupération du contenu du descripteur de configuration uniquement */
                   l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) ( T_mkHCDConfigurationDescriptor* ) &p_device->configurationDescriptor, ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1 ), p_length );
                }

                /* Si le contenu du descripteur a été récupéré */
                if ( l_result == K_MK_OK )
                {
                   /* Transmission du paquet d'acquittement (ZLP) */
                   l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );

                   /* Si aucune erreur ne s'est produite */
                   if ( l_result == K_MK_OK )
                   {
                      /* S'il est temps de récupérer les descripteurs d'interface et de terminaison */
                      if ( ( p_length != p_device->configurationDescriptor.wTotalLength ) && ( p_length == K_MK_HCD_CONFIGURATION_DESCRIPTOR_SIZE ) )
                      {
                         /* Récupération des descripteurs d'interface et de terminaison */
                         l_result = mk_hcd_getConfigurationDescriptor ( p_device, p_pipe, p_device->configurationDescriptor.wTotalLength );
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



