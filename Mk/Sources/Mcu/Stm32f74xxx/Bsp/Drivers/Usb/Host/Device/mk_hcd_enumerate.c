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
* @file mk_hcd_enumerate.c
* @brief Définition de la fonction mk_hcd_enumerate.
* @date 15 juin 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_checkControlEnpointMaxPacketSize ( T_mkHCDDevice* p_device, uint16_t p_maxPacketSize )
{
   /* Si le MPS est nul */
   if ( p_maxPacketSize == 0 )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type LS avec un MPS différent de 8 octets */
   else if ( ( p_device->layer.speed == K_USB_LOW_SPEED ) && ( p_maxPacketSize != 8 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type FS avec un MPS différent de 8, 16, 32 ou 64 octets */
   else if ( ( p_device->layer.speed == K_USB_LOW_SPEED ) && ( ! ( ( p_maxPacketSize == 8 ) ||
           ( p_maxPacketSize == 16 ) || ( p_maxPacketSize == 32 ) || ( p_maxPacketSize == 64 ) ) ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Si le périphérique est de type HS avec un MPS différent de 64 octets */
   else if ( ( p_device->layer.speed == K_USB_HIGH_SPEED ) && ( p_maxPacketSize != 64 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
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

static void mk_hcd_checkIsochronousMaxPacketSize ( T_mkHCDDevice* p_device, uint16_t p_maxPacketSize )
{
   /* Si le MPS est nul */
   if ( p_maxPacketSize == 0 )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type LS */
   else if ( p_device->layer.speed == K_USB_LOW_SPEED )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type FS avec un MPS supérieur à 1023 octets */
   else if ( ( p_device->layer.speed == K_USB_FULL_SPEED ) && ( p_maxPacketSize > 1023 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type HS avec un MPS supérieur à 1024 octets */
   else if ( ( p_device->layer.speed == K_USB_HIGH_SPEED ) && ( p_maxPacketSize > 1024 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
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

static void mk_hcd_checkInterruptMaxPacketSize ( T_mkHCDDevice* p_device, uint16_t p_maxPacketSize )
{
   /* Si le MPS est nul */
   if ( p_maxPacketSize == 0 )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type LS avec un MPS supérieur à 8 octets */
   else if ( ( p_device->layer.speed == K_USB_LOW_SPEED ) && ( p_maxPacketSize > 8 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type LS avec un MPS supérieur à 64 octets */
   else if ( ( p_device->layer.speed == K_USB_FULL_SPEED ) && ( p_maxPacketSize > 64 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type HS avec un MPS supérieur à 1024 octets */
   else if ( ( p_device->layer.speed == K_USB_HIGH_SPEED ) && ( p_maxPacketSize > 1024 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
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

static void mk_hcd_checkBulkMaxPacketSize ( T_mkHCDDevice* p_device, uint16_t p_maxPacketSize )
{
   /* Si le MPS est nul */
   if ( p_maxPacketSize == 0 )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type LS */
   else if ( p_device->layer.speed == K_USB_LOW_SPEED )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type FS avec un MPS différent de 8, 16, 32 ou 64 octets */
   else if ( ( p_device->layer.speed == K_USB_FULL_SPEED ) && ( ! ( ( p_maxPacketSize == 8 ) ||
           ( p_maxPacketSize == 16 ) || ( p_maxPacketSize == 32 ) || ( p_maxPacketSize == 64 ) ) ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon si le périphérique est de type HS avec un MPS différent de 512 octets */
   else if ( ( p_device->layer.speed == K_USB_HIGH_SPEED ) && ( p_maxPacketSize != 512 ) )
   {
      /* Actualisation de l'état du périphérique */
      p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
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

static void mk_hcd_checkEnpointMaxPacketSize ( T_mkHCDDevice* p_device )
{
   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface;

   /* Déclaration d'un pointeur de terminaison */
   T_mkHCDEndpointDescriptor* l_endpoint;

   /* Pour chaque interface du périphérique */
   for ( l_interface = p_device->interfaceDescriptor ; ( l_interface != K_MK_NULL ) ; l_interface = l_interface->nextInterface )
   {
      /* Pour chaque terminaison de l'interface */
      for ( l_endpoint = l_interface->endpoint ; l_endpoint != K_MK_NULL ; l_endpoint = l_endpoint->nextEndpoint )
      {
         /* Test du type de la terminaison */
         switch ( ( l_endpoint->bmAttributes & 0x3 ) )
         {
            case K_MK_HCD_ENDPOINT_CONTROL :
               /* Vérification du maxPacketSize d'une terminaison de type 'Control' */
               mk_hcd_checkControlEnpointMaxPacketSize ( p_device, l_endpoint->wMaxPacketSize & 0x7FF );
               break;

            case K_MK_HCD_ENDPOINT_ISOCHRONOUS :
               /* Vérification du maxPacketSize d'une terminaison de type 'Isochronous' */
               mk_hcd_checkIsochronousMaxPacketSize ( p_device, l_endpoint->wMaxPacketSize & 0x7FF );
               break;

            case K_MK_HCD_ENDPOINT_BULK :
               /* Vérification du maxPacketSize d'une terminaison de type 'Bulk' */
               mk_hcd_checkBulkMaxPacketSize ( p_device, l_endpoint->wMaxPacketSize & 0x7FF );
               break;

            case K_MK_HCD_ENDPOINT_INTERRUPT :
               /* Vérification du maxPacketSize d'une terminaison de type 'Interrupt' */
               mk_hcd_checkInterruptMaxPacketSize ( p_device, l_endpoint->wMaxPacketSize & 0x7FF );
               break;

            default:
               /* Actualisation de l'état du périphérique */
               p_device->state |= K_MK_HCD_DEVICE_NOT_VALID;
               break;
         }
      }
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_setAddressedState ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Actualisation de l'état du périphérique */
   p_device->state = K_MK_HCD_DEVICE_ATTACHED_STATE;

   /* Réinitialisation du MPS du pipe */
   p_pipe->endpointMaxPacketSize = K_MK_HCD_DEFAULT_MAX_PACKET_SIZE;

   /* Récupération du descripteur de périphérique */
   l_result = mk_hcd_getDeviceDescriptor ( p_device, p_pipe );

   /* Si le descripteur de périphérique a été récupéré */
   if ( l_result == K_MK_OK )
   {
      /* Configuration de l'adresse du dispositif */
      l_result = mk_hcd_setDeviceAddress ( p_device, p_pipe );

      /* Si l'adresse a correctement été configurée */
      if ( l_result == K_MK_OK )
      {
         /* Ecriture de l'adresse dans la structure */
         l_result = mk_hcd_setAddress ( p_device );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de l'état du périphérique */
            p_device->state = K_MK_HCD_DEVICE_ADDRESSED_STATE;

            /* Vérification de la validité du champ 'MaxPacketSize' de la terminaison 0 */
            /* Cette action est réalisée après l'allocation d'une adresse pour éviter de laisser un périphérique */
            /* avec une adresse nulle sur le bus. */
            mk_hcd_checkControlEnpointMaxPacketSize ( p_device, ( uint16_t ) p_device->deviceDescriptor.bMaxPacketSize0 );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_setConfiguredState ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Récupération du descripteur de périphérique au complet */
   l_result = mk_hcd_getDeviceDescriptor ( p_device, p_pipe );

   /* Lorsque le descripteur de périphérique vient d'être récupéré, on peut commencer à récupérer le qualificateur de périphérique. */
   /* Le qualificateur est disponible seulement si le périphérique est de type de type HS (bcdUSB >= 2.0). */
   /* Ce bloc spécifie les nouvelles caractéristiques du périphérique si la vitesse nominale de celui-ci vient à changer. Dans l'application, */
   /* On récupére le descripteur pour information uniquement car le changement de vitesse n'est pas implémenté. En conséquence, les descripteurs */
   /* OtherSpeedConfiguration, ne sont jamais récupérés. */
   if ( l_result == K_MK_OK )
   {
      /* Si un périphérique HS est branché sur un hub qui n'a pas la même vitesse que le périphérique venant d'être connecté */
      if ( ( p_device->previousHubDevice != K_MK_NULL ) && ( p_device->layer.speed != p_device->previousHubDevice->layer.speed ) &&
           ( p_device->previousHubDevice->layer.speed != K_USB_HIGH_SPEED) && ( p_device->deviceDescriptor.bcdUSB [ 1 ] >= 2 ) )
      {
         /* Récupération du qualificateur de périphérique */
         l_result = mk_hcd_getDeviceQualifier ( p_device, p_pipe );

         /* Contrairement au autre bloc durant l'énumération, la réception d'un STALL n'est pas défini comme un comportement anormal */
         if ( ( p_pipe->status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL )
         {
            /* On bascule le résultat à OK, ce n'est pas une erreur de communication car */
            /* l'intégralité des périphériques USB ne supporte pas cette requête. */
            l_result = K_MK_OK;
         }

         /* Sinon */
         else
         {
            /* Vérification de la validité du champ MaxPacketSize de la terminaison 0 */
            mk_hcd_checkControlEnpointMaxPacketSize ( p_device, p_device->deviceQualifier.bMaxPacketSize0 );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le qualificateur de périphérique a été récupéré */
      if ( ( l_result == K_MK_OK ) && ( ( ( p_device->state & K_MK_HCD_DEVICE_NOT_VALID ) != K_MK_HCD_DEVICE_NOT_VALID ) ) )
      {
         /* Récupération du descripteur de configuration */
         l_result = mk_hcd_getConfigurationDescriptor ( p_device, p_pipe, K_MK_HCD_CONFIGURATION_DESCRIPTOR_SIZE );

         /* Si le descripteur de configuration a été récupéré */
         if ( ( l_result == K_MK_OK ) && ( ( p_device->state & K_MK_HCD_DEVICE_NOT_VALID ) != K_MK_HCD_DEVICE_NOT_VALID ) )
         {
            /* Activation de la configuration principale */
            l_result = mk_hcd_setDeviceConfiguration ( p_device, p_pipe );

            /* Si la configuration a été activée */
            if ( l_result == K_MK_OK )
            {
               /* Actualisation de l'état du périphérique */
               p_device->state = K_MK_HCD_DEVICE_CONFIGURED_STATE;

               /* Le périphérique est configuré, on lance la vérification du 'MaxPacketSize' de chaque terminaison avant de réaliser */
               /* le dispatch. */
               mk_hcd_checkEnpointMaxPacketSize ( p_device );
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
      /* Voir commentaire dans la fonction mk_hcd_setDeviceAddress */
      /* Il arrive que la requête d'adresse soit acquitée alors que le changement n'a pas */
      /* été pris en compte. Pour corriger ce défaut, on recommence l'énumération. */

      /* Réinitialisation de l'adresse du périphérique */
      p_device->layer.deviceAddr = 0;

      /* Modification de l'état du périphérique. */
      p_device->state = K_MK_HCD_DEVICE_ATTACHED_STATE;
   }

   /* Retour */
   return ( l_result );
}


/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_enumerate ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Si le périphérique est dans l'état HCD_ATTACHED */
      /* On empêche les périphériques ayant un état différent de HCD_ATTACHED d'éxécuter ce code */
      if ( p_device->state == K_MK_HCD_DEVICE_ATTACHED_STATE )
      {
         /* Configuration de l'adresse du périphérique */
         l_result = mk_hcd_setAddressedState ( p_device, p_pipe );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique est dans l'état HCD_ADDRESSED */
      /* On empêche les périphériques ayant un état différent de HCD_ADDRESSED d'éxécuter ce code */
      if ( ( l_result == K_MK_OK ) && ( p_device->state == K_MK_HCD_DEVICE_ADDRESSED_STATE ) )
      {
         /* Configuration du périphérique */
         l_result = mk_hcd_setConfiguredState ( p_device, p_pipe );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique est dans l'état HCD_CONFIGURED */
      /* On empêche les périphériques ayant un état différent de HCD_CONFIGURED d'éxécuter ce code */
      if ( ( l_result == K_MK_OK ) && ( p_device->state == K_MK_HCD_DEVICE_CONFIGURED_STATE ) )
      {
         /* On transmet l'adresse du périphérique au terminal de gestion */
         l_result = mk_hcd_dispatchDevice ( p_handler, p_device, p_pipe );
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

