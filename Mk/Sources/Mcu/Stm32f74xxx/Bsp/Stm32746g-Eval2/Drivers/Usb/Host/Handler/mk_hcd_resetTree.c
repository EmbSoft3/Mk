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
* @file mk_hcd_resetTree.c
* @brief Définition de la fonction mk_hcd_resetTree.
* @date 20 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_removeDevice ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de statut */
   uint32_t l_status;

   /* Récupération de la valeur du registre de statut */
   l_result = mk_event_wait ( p_device->flag.event, K_MK_EVENT_OR | K_MK_HCD_CLASS_FLAG_ALL, &l_status, 0 );

   /* Si le registre de statut indique que le périphérique peut être désalloué */
   /* et si aucune périphérique n'est connecté sur le hub */
   if ( ( l_result == K_MK_ERROR_TIMEOUT ) && ( p_device->nextHubDevice == K_MK_NULL ) )
   {
      /* Suppression du périphérique */
      l_result = mk_hcd_deleteTree ( &p_handler->hubList, p_device, K_MK_HCD_DELETE_ALL );

      /* Si le périphérique est le périphérique principal */
      if ( p_device == p_handler->device )
      {
         /* Réinitialisation de l'adresse du périphérique principal */
         p_handler->device = K_MK_NULL;
      }
   }

   /* Sinon */
   else
   {
      /* Certaines tâches (HID, MSC, ...) utilisant le périphérique n'ont pas encore désallouée la mémoire supplémentaire. */
      /* On laisse la main à une autre tâche */
      l_result = mk_task_sleep ( 5 );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_resetTree ( T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de hub */
   T_mkHCDDevice* l_currentHub;

   /* Déclaration d'un pointeur de périphérique */
   T_mkHCDDevice* l_device;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Initialisation du pointeur de périphérique */
      /* On pointe sur le périphérique principal */
      l_device = p_handler->device;

      /* Récupération de l'adresse du hub courant */
      l_currentHub = p_handler->hubList.current;

      /* Si au moins un hub est connecté sur le bus */
      if ( l_currentHub != K_MK_NULL )
      {
         /* Effectue */
         do
         {
            /* Récupération de l'adresse du périphérique courant */
            l_device = l_currentHub->nextHubDevice;

            /* Tant que l'intégralité des périphériques sur le hub n'ont pas été analysé */
            while ( l_device != K_MK_NULL )
            {
               /* Analyse puis suppression du périphérique */
               l_result |= mk_hcd_removeDevice ( p_handler, l_device );

               /* Actualisation de l'adresse du périphérique courant */
               l_device = l_device->nextDevice;
            }

            /* Récupération de l'adresse du hub courant */
            l_currentHub = l_currentHub->next;

            /* Analyse puis suppression du périphérique */
            l_result |= mk_hcd_removeDevice ( p_handler, l_currentHub->previous );

         /* Tant que tous les périphériques connectés sur les hubs n'ont pas été supprimés */
         } while ( p_handler->hubList.current != K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Tant que le périphérique principal n'a pas été supprimé */
      while ( p_handler->device != K_MK_NULL )
      {
         /* Analyse puis suppression du périphérique */
         l_result |= mk_hcd_removeDevice ( p_handler, l_device );
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


