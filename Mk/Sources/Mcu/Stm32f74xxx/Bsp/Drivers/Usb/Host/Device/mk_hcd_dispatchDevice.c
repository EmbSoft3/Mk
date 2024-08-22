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
* @file mk_hcd_dispatchDevice.c
* @brief Définition de la fonction mk_hcd_dispatchDevice.
* @date 4 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_dispatch ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDDeviceClass p_class, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le périphérique (ou l'interface) appartient à la classe Hub */
   if ( p_class == K_MK_HCD_CLASS_HUB )
   {
      /* Initialisation du hub */
      l_result = mk_hcd_initHub ( p_handler, p_device, p_pipe );

      /* Si aucune erreur ne s'est produite et si l'état du périphérique est correct */
      /* Il est important de tester l'état du périphérique car en analysant les attributs du hub, */
      /* la fonction mk_hcd_initHub peut renvoyer un statut K_MK_HCD_DEVICE_NOT_VALID. */
      if ( ( l_result == K_MK_OK ) && ( p_device->state == K_MK_HCD_DEVICE_CONFIGURED_STATE ) )
      {
         /* Ajout du périphérique dans la liste des hubs */
         l_result = mk_hcd_add ( &p_handler->hubList, p_device );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si le périphérique (ou l'interface) appartient à la classe HID */
   else if ( p_class == K_MK_HCD_CLASS_HID )
   {
      /* Déclaration d'un pointeur de gestionnaire HID */
      T_mkHIDHandler* l_hidHandler = K_MK_NULL;

      /* Déclaration d'un message */
      T_mkHCDMessage l_message = { p_device, p_interface };

      /* Récupération de l'adresse du gestionnaire HID */
      l_result = mk_termio_getChild ( g_mkTermioHandler.usbhid, ( void** ) &l_hidHandler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de l'adresse du nouveau périphérique au gestionnaire HID */
         l_result = mk_mail_post ( l_hidHandler->mailArea->mail, &l_message, K_MK_STATE_READY, 0 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation du registre de statut du périphérique */
            /* Le périphérique est de type HID */
            l_result = mk_event_set ( p_device->flag.event, K_MK_HCD_CLASS_FLAG_HID );
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

   /* Sinon si le périphérique (ou l'interface) appartient à la classe MSC */
   else if ( p_class == K_MK_HCD_CLASS_MASS_STORAGE )
   {
      /* Déclaration d'un pointeur de gestionnaire MSC */
      T_mkMSCHandler* l_storageHandler = K_MK_NULL;

      /* Déclaration d'un message */
      T_mkHCDMessage l_message = { p_device, p_interface };

      /* Récupération de l'adresse du gestionnaire MSC */
      l_result = mk_termio_getChild ( g_mkTermioHandler.msc, ( void** ) &l_storageHandler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de l'adresse du nouveau périphérique au gestionnaire MSC */
         l_result = mk_mail_post ( l_storageHandler->messageArea->mail, &l_message, K_MK_STATE_READY, 0 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation du registre de statut du périphérique */
            /* Le périphérique est de type MSC */
            l_result = mk_event_set ( p_device->flag.event, K_MK_HCD_CLASS_FLAG_MASS_STORAGE );
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

   /* Suppression warning */
   ( void ) p_interface;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_dispatchDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) &&
        ( p_device->interfaceDescriptor != K_MK_NULL ) && ( p_device->state == K_MK_HCD_DEVICE_CONFIGURED_STATE ) )
   {
      /* Si la classe doit être récupérée dans les descripteurs d'interfaces */
      if ( p_device->deviceDescriptor.bDeviceClass == K_MK_HCD_CLASS_BASE )
      {
         /* Initialisation du pointeur */
         l_interface = p_device->interfaceDescriptor;

         /* Il est nécessaire d'analyser toutes les interfaces du périphérique */
         while ( ( l_interface != K_MK_NULL ) && ( l_result == K_MK_OK ) )
         {
            /* Si l'interface analysée est une interface nominale */
            if ( l_interface->bAlternateSetting == 0 )
            {
               /* Transmission de l'adresse du périphérique au terminal de traitement */
               l_result = mk_hcd_dispatch ( p_handler, p_device, l_interface, l_interface->bInterfaceClass, p_pipe );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du pointeur d'interface */
            l_interface = l_interface->nextInterface;
         }
      }

      /* Sinon */
      else
      {
         /* Transmission de l'adresse du périphérique au terminal de traitement */
         /* La classe est marquée dans le descripteur de périphérique. Il est inutile de parcourir toutes les interfaces */
         l_result = mk_hcd_dispatch ( p_handler, p_device, K_MK_NULL, p_device->deviceDescriptor.bDeviceClass, p_pipe );
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation de l'état du périphérique */
         p_device->state = K_MK_HCD_DEVICE_DISPATCHED_STATE;
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



