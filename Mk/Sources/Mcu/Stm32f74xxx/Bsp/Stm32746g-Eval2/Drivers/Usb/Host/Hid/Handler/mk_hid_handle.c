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
* @file mk_hid_handle.c
* @brief Définition de la fonction mk_hid_handle.
* @date 19 oct. 2019
*
*/

#include "mk_hid_api.h"
/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_handle ( T_mkHIDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphérique HID */
   T_mkHIDDevice* l_currentDevice;

   /* Déclaration d'une variable stockant la valeur de l'intervalle de rafraichissement */
   uint32_t l_interval;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Enregistrement de l'adresse du premier périphérique HID */
      l_currentDevice = p_handler->list.first;

      /* Si au moins un périphérique est présent dans la liste HID */
      if ( l_currentDevice != K_MK_NULL )
      {
         /* Effectue */
         do
         {
            /* Si le périphérique a été déconnecté du bus */
            if ( ( l_currentDevice->device->state & K_MK_HCD_DEVICE_DISCONNECTED ) == K_MK_HCD_DEVICE_DISCONNECTED )
            {
               /* Suppression du périphérique HID */
               l_result |= mk_hid_deleteDevice ( p_handler, l_currentDevice->device );
            }

            /* Sinon si le périphérique n'est pas initialisé */
            else if ( ( l_currentDevice->state & K_MK_HID_DEVICE_CONFIGURED_STATE ) != K_MK_HID_DEVICE_CONFIGURED_STATE )
            {
               /* Initialisation du périphérique HID */
               l_result |= mk_hid_initDevice ( p_handler, l_currentDevice );
            }

            /* Sinon */
            else
            {
               /* Récupération de la valeur de l'intervalle de rafraichissement */
               l_interval = mk_hcd_getTimeRemaining ( l_currentDevice->device, l_currentDevice->interface->endpoint, K_MK_HID_REFRESH_TIMEOUT );

               /* Si il est temps de rafraichir le périphérique HID */
               if ( l_interval == 0 )
               {
                  /* Récupération et dispatch des entrées HID. */
                  l_result |= mk_hid_dispatchInput ( p_handler, l_currentDevice );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Actualisation du pointeur courant */
            l_currentDevice = l_currentDevice->next;

         /* Tant que l'intégralité des périphériques HID n'ont pas analysés */
         } while ( l_currentDevice != K_MK_NULL );

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( p_handler->list.first != K_MK_NULL ) )
         {
            /* Récupération et dispatch des sorties HID */
            l_result = mk_hid_dispatchOutput ( p_handler->list.first );
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

      /* Attente 11 ms */
      l_result |= mk_task_sleep ( K_MK_HID_REFRESH_TIMEOUT + 1 );
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


