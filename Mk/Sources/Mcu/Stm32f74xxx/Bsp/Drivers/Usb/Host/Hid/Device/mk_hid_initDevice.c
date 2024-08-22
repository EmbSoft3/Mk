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
* @file mk_hid_initDevice.c
* @brief Définition de la fonction mk_hid_initDevice.
* @date 21 oct. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_initEndpoint ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* La spécification HID définie l'ordre des terminaisons. La terminaison de type IN est présente en première position tandis que la */
   /* terminaison de type OUT (qui peut être optionnelle) est située en deuxième position. */

   /* Recherche de la terminaison HID de type IN */
   l_result = mk_hcd_searchEndpoint ( p_hidDevice->interface, &p_hidDevice->inEndpoint, K_USB_INTERRUPT_ENDPOINT, K_USB_IN_ENDPOINT );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Recherche de la terminaison HID de type OUT */
      /* Une valeur nulle est autorisée */
      l_result = mk_hcd_searchEndpoint ( p_hidDevice->interface, &p_hidDevice->outEndpoint, K_USB_INTERRUPT_ENDPOINT, K_USB_OUT_ENDPOINT );

      /* Vérification de l'ordre des terminaisons */
      if ( p_hidDevice->outEndpoint != K_MK_NULL )
      {
         /* Si la terminaison de type OUT n'est pas située juste après la terminaison de type IN */
         if ( p_hidDevice->inEndpoint->nextEndpoint != p_hidDevice->outEndpoint )
         {
            /* Basculement de l'état du périphérique */
            p_hidDevice->state |= K_MK_HID_DEVICE_NOT_SUPPORTED;
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

static T_mkCode mk_hid_configureDevice ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération du descripteur HID */
   l_result = mk_hcd_getSpecialDesciptor ( p_hidDevice->device, p_pipe, p_hidDevice->interface, &p_hidDevice->hidDescriptor,
                                           ( uint32_t ) ( K_MK_HID_DESCRIPTOR | ( uint8_t ) sizeof ( T_mkHIDDescriptor ) ) );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_hidDevice->hidDescriptor.bNumDescriptors >= 1 ) &&
      ( ( p_hidDevice->device->state & K_MK_HCD_DEVICE_NOT_VALID ) != K_MK_HCD_DEVICE_NOT_VALID ) && ( p_hidDevice->state == K_MK_HID_DEVICE_NOT_INIT_STATE ) )
   {
      /* Si le périphérique est une souris ou un clavier et qu'il supporte le 'Boot Protocol' */
      if ( ( ( p_hidDevice->interface->bInterfaceProtocol == 1 ) || ( p_hidDevice->interface->bInterfaceProtocol == 2 ) ) &&
             ( p_hidDevice->interface->bInterfaceSubClass == 1 ) )
      {
         /* Activation du protocol 'REPORT_PROTOCOL <1>' */
         /* Le tableau de la spécification HID page 78 indique que cette requête est obligatoirement supportée par les périphériques en mode BOOT. */
         l_result = mk_hid_setProtocol ( p_hidDevice, p_pipe, K_MK_HID_REPORT_PROTOCOL, p_hidDevice->interface->bInterfaceNumber );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* L'état du périphérique (state) n'a pas pu évoluer depuis la dernière requête, il est inutile de le tester de nouveau. */
      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de la fréquence de rafraichissement du périphérique */
         /* Etant donné que la gestion de l'événement 'HOLD' n'est pas uniforme pour tous les claviers, on configure une fréquence de type nulle par défaut. */
         /* Pour certain périphérique, la requête 'setIdle' n'est pas supportée. Ce n'est pas un comportement anormal car cette requête peut être */
         /* optionnelle en fonction du type du périphérique HID (souris, clavier, ...). */
         l_result = mk_hid_setIdle ( p_hidDevice, p_pipe, 0, 0, p_hidDevice->interface->bInterfaceNumber );
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

static T_mkCode mk_hid_routeReportDescriptor ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre de statut */
   T_mkHIDReportError l_error = K_MK_HID_NO_ERROR;

   /* Récupération du 'Report Descriptor' */
   /* La fonction peut positionner le périphérique HID dans l'état NOT_SUPPORTED si un item de type 'Long' est rencontré */
   l_result = mk_hid_getReportDescriptor ( p_hidDevice, p_pipe, p_hidDevice->interface->bInterfaceNumber );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_hidDevice->state == K_MK_HID_DEVICE_NOT_INIT_STATE ) )
   {
      /* Analyse de la conformité du 'ReportDescriptor' */
      l_result = mk_hid_parseError ( p_hidDevice, &l_error );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_error == K_MK_HID_NO_ERROR ) )
      {
         /* Modification de la structure du 'Report Descriptor' afin d'enlever les usages alternatifs */
         /* de la chaine principale. */
         l_result = mk_hid_parseAlternate ( p_hidDevice );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Lancement du processus de routage des 'Reports' */
            l_result = mk_hid_route ( p_hidDevice );

            /* Actualisation de l'état du périphérique HID */
            p_hidDevice->state |= K_MK_HID_DEVICE_CONFIGURED_STATE;
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
         /* Basculement de l'état du périphérique */
         p_hidDevice->state |= K_MK_HID_DEVICE_NOT_SUPPORTED;
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

T_mkCode mk_hid_initDevice ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pipe */
   T_mkHCDPipe l_pipe;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_hidDevice != K_MK_NULL ) )
   {
      /* Ouverture d'un pipe */
      l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe, K_MK_HCD_ENDPOINT_CONTROL, K_MK_HCD_ENDPOINT0, p_hidDevice->device->deviceDescriptor.bMaxPacketSize0, K_MK_HCD_TIMEOUT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Recherche de l'adresse des terminaisons d'interruption IN/OUT du périphérique HID */
         l_result = mk_hid_initEndpoint ( p_hidDevice );

         /* Si aucune erreur ne s'est produite */
         /* Le périphérique HID doit obligatoirement avoir une terminaison de type INTERRUPT_IN. */
         if ( ( l_result == K_MK_OK ) && ( p_hidDevice->state == K_MK_HID_DEVICE_NOT_INIT_STATE ) && ( p_hidDevice->inEndpoint != K_MK_NULL ) )
         {
            /* Récupération du descripteur HID et configuration du périphérique */
            l_result = mk_hid_configureDevice ( p_hidDevice, &l_pipe );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) || ( ( l_pipe.status & K_MK_HCD_ERROR_STALL ) == K_MK_HCD_ERROR_STALL ) )
            {
               /* Récupération du 'Report-Descriptor', analyse puis lancement du processus de routage */
               l_result = mk_hid_routeReportDescriptor ( p_hidDevice, &l_pipe );
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

         /* Fermeture du pipe (cette fonction ne modifie pas le statut du pipe) */
         l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique HID doit être supprimé */
      if ( p_hidDevice->state != K_MK_HID_DEVICE_CONFIGURED_STATE )
      {
         /* Suppression du périphérique HID et suppression de son interface */
         l_result |= mk_hid_deleteDeviceByInterface ( p_handler, p_hidDevice );
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


