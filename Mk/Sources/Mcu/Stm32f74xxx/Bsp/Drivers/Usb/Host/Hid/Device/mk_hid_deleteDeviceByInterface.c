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
* @file mk_hid_deleteDeviceByInterface.c
* @brief Définition de la fonction mk_hid_deleteDeviceByInterface.
* @date 4 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_deleteDeviceMemory ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Suppression des collections et de la mémoire allouée pour le périphérique HID */
   l_result |= mk_hid_deleteReport ( p_hidDevice );

   /* Suppression du 'ReportDescriptor' */
   l_result |= mk_hid_deleteReportDescriptor ( p_hidDevice );

   /* Suppression du périphérique HID de la liste */
   l_result |= mk_hid_remove ( &p_handler->list, p_hidDevice );

   /* Désallocation du périphérique HID */
   l_result |= mk_pool_freeSafe ( g_mkHIDPool.devicePool, p_hidDevice);

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_deleteDeviceByInterface ( T_mkHIDHandler* p_handler, T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface;

   /* Déclaration d'un pointeur de périphérique */
   T_mkHCDDevice* l_device;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_hidDevice != K_MK_NULL ) )
   {
      /* Enregistrement de l'adresse du périphérique */
      l_device = p_hidDevice->device;

      /* Enregistrement de l'adresse de l'interface du périphérique HID */
      l_interface = p_hidDevice->interface;

      /* Suppression du périphérique HID et des objets internes */
      l_result |= mk_hid_deleteDeviceMemory ( p_handler, p_hidDevice );

      /* Suppression de l'interface du périphérique HID */
      /* Il n'est pas nécessaire de protéger la destruction de l'interface par une section */
      /* critique. La tâche HCD ne peut intéragir dessus que durant la destruction d'un périphérique */
      /* ou durant le processus de dispatch. La destruction du périphérique ne s'effectue qu'avec le consentement */
      /* de la tâche HID. Le dispatch a été réalisé lorsque ce code s'exécute (au pire, le dispatcher est en */
      /* train de traiter la prochaine interface ce qui est sans conséquence). */
      l_result |= mk_hcd_deleteInterface ( l_device, l_interface );

      /* Si le périphérique ne possède plus d'interface */
      if ( l_device->interfaceDescriptor == K_MK_NULL )
      {
         /* Réinitialisation du drapeau de déconnexion */
         /* On signale au terminal USB que le périphérique HCD peut être détruit. */
         l_result |= mk_event_clear ( l_device->flag.event, K_MK_HCD_CLASS_FLAG_HID );
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





