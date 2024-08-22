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
* @file mk_hcd_handleHub.c
* @brief Définition de la fonction mk_hcd_handleHub.
* @date 18 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleHub ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant l'intervalle de rafraichissement et d'une variable de statut */
   uint32_t l_interval, l_status;

   /* Déclaration des pointeurs de périphériques */
   T_mkHCDDevice* l_currentHub, *l_device;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Si au moins un périphérique est présent dans la liste des hubs */
      if ( p_handler->hubList.current != K_MK_NULL )
      {
         /* Effectue */
         do
         {
            /* Récupération de l'adresse du hub courant */
            l_currentHub = p_handler->hubList.current;

            /* Récupération de la valeur de l'intervalle de rafraichissement */
            l_interval = mk_hcd_getTimeRemaining ( l_currentHub, l_currentHub->interfaceDescriptor->endpoint, K_MK_HCD_HUB_REFRESH_TIMEOUT );

            /* S'il est temps de rafraichir le hub */
            if ( l_interval == 0 )
            {
               /* Récupération de l'adresse du premier périphérique dans la liste */
               /* des hubs */
               l_device = l_currentHub->nextHubDevice;

               /* Tant que l'intégralité des périphériques présents sur le hub n'ont pas été analysés */
               /* Le traitement n'est pas stoppé lorsque des erreurs de communication se produisent afin de pouvoir supprimer le périphérique si une */
               /* ou plusieurs déconnexions se sont produites. */
               while ( ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) && ( l_device != K_MK_NULL ) )
               {
                  /* Si le périphérique a été déconnecté */
                  if ( ( l_device->state & K_MK_HCD_DEVICE_DISCONNECTED ) == K_MK_HCD_DEVICE_DISCONNECTED )
                  {
                     /* Récupération de la valeur du registre de statut */
                     l_result = mk_event_wait ( l_device->flag.event, K_MK_EVENT_OR | K_MK_HCD_CLASS_FLAG_ALL, &l_status, 0 );

                     /* Si le registre de statut indique que le périphérique peut être désalloué */
                     if ( ( l_result == K_MK_ERROR_TIMEOUT ) && ( l_device->nextHubDevice == K_MK_NULL ) )
                     {
                        /* Suppression du périphérique de l'arborescence */
                        l_result = mk_hcd_deleteTree ( &p_handler->hubList, l_device, K_MK_HCD_DELETE_ALL );
                     }

                     /* Sinon */
                     else
                     {
                        /* Ne rien faire */
                        /* Certaines tâches utilisant le périphérique n'ont pas encore désallouées la mémoire. */
                     }
                  }

                  /* Si l'énumération du périphérique a échoué */
                  else if ( l_device->state != K_MK_HCD_DEVICE_DISPATCHED_STATE )
                  {
                     /* Lançement du processus d'énumération et ou de dispatch */
                     l_result = mk_hcd_enumerate ( p_handler, l_device, p_pipe );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

                  /* Actualisation du pointeur de périphérique */
                  l_device = l_device->nextDevice;
               }

               /* Lancement du traitement des statuts du hub */
               l_result = mk_hcd_handleHubStatus ( p_handler, l_currentHub, p_pipe );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du pointeur de hub */
            p_handler->hubList.current = l_currentHub->next;

            /* Si le hub a été déconnecté */
            if ( ( l_currentHub->previous->state & K_MK_HCD_DEVICE_DISCONNECTED ) == K_MK_HCD_DEVICE_DISCONNECTED )
            {
               /* Si tous les périphériques connecté sur le hub ont été détruits */
               if ( l_currentHub->previous->nextHubDevice == K_MK_NULL )
               {
                  /* Suppression du périphérique */
                  l_result = mk_hcd_deleteTree ( &p_handler->hubList, l_currentHub->previous, K_MK_HCD_DELETE_ALL );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
                  /* Certaines tâches utilisant le périphérique n'ont pas encore désallouées la mémoire. */
               }
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

         /* Tant que l'intégralité des hubs n'ont pas analysés */
         } while ( ( l_result == K_MK_OK ) && ( l_currentHub != p_handler->device ) );
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


