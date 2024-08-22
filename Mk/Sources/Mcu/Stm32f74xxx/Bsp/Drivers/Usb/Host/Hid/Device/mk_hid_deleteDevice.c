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
* @file mk_hid_deleteDevice.c
* @brief Définition de la fonction mk_hid_deleteDevice.
* @date 20 oct. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_deleteDevice ( T_mkHIDHandler* p_handler, T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Récupération de l'adresse de la première interface */
      l_interface = p_device->interfaceDescriptor;

      /* Pour chaque interface du périphérique */
      /* Il est possible qu'un dispositif soit détruit alors qu'il ne possède aucune interface. */
      /* Ce cas peut se produire lorsqu'une interface invalide a été détectée puis désallouer avant la déconnection */
      /* du périphérique. */
      while ( l_interface != K_MK_NULL )
      {
         /* Si l'interface est une interface HID */
         if ( p_device->interfaceDescriptor->bInterfaceClass == K_MK_HCD_CLASS_HID )
         {
            /* Ne pas modifier l'ordre de suppression, la fonction mk_hid_deleteReport transmet un événement */
            /* indiquant la déconnexion du périphérique aux Dispatcher. */

            /* Suppression des collections et de la mémoire allouée pour le périphérique HID */
            l_result |= mk_hid_deleteReport ( ( T_mkHIDDevice* ) l_interface->child );

            /* Suppression du 'ReportDescriptor' */
            l_result |= mk_hid_deleteReportDescriptor ( ( T_mkHIDDevice* ) l_interface->child );

            /* Suppression du périphérique HID de la liste */
            l_result |= mk_hid_remove ( &p_handler->list, ( T_mkHIDDevice* ) l_interface->child );

            /* Désallocation du périphérique HID */
            l_result |= mk_pool_freeSafe ( g_mkHIDPool.devicePool, ( T_mkAddr* ) l_interface->child );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de la valeur du pointeur d'interface */
         l_interface = l_interface->nextInterface;
      }

      /* Réinitialisation du drapeau de déconnexion */
      /* On signale au terminal USB que le périphérique HCD peut être détruit. */
      l_result |= mk_event_clear ( p_device->flag.event, K_MK_HCD_CLASS_FLAG_HID );
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




