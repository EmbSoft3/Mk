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
* @file mk_hcd_deleteTree.c
* @brief Définition de la fonction mk_hcd_deleteTree.
* @date 27 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_deleteAllInterfaces ( T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de terminaison */
   T_mkHCDEndpointDescriptor *l_endpoint, *l_nextEndpoint;

   /* Déclaration des pointeurs d'interface */
   T_mkHCDInterfaceDescriptor *l_interface = p_device->interfaceDescriptor, *l_nextInterface;

   /* Tant que toutes les interfaces n'ont pas été désallouées */
   while ( l_interface != K_MK_NULL )
   {
      /* Récupération du pointeur de terminaison */
      l_endpoint = l_interface->endpoint;

      /* Enregistrement de l'adresse de la prochaine interface */
      l_nextInterface = l_interface->nextInterface;

      /* Tant que toutes les terminaisons de l'interface n'ont pas été désallouées */
      while ( l_endpoint != K_MK_NULL )
      {
         /* Enregistrement de l'adresse de la prochaine terminaison */
         l_nextEndpoint = l_endpoint->nextEndpoint;

         /* Suppression de la mémoire allouée */
         l_result |= mk_pool_freeSafe ( g_mkHCDPool.endpointPool, ( T_mkAddr ) l_endpoint );

         /* Passage à la prochaine terminaison */
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

static T_mkCode mk_hcd_deleteHub ( T_mkHCDList* p_list, T_mkHCDDevice* p_hub, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Tant que l'intégralité des périphériques sur le hub n'ont pas été supprimé */
   while ( p_hub->nextHubDevice != K_MK_NULL )
   {
      /* Suppression du périphérique courant */
      l_result |= mk_hcd_deleteTree ( p_list, p_hub->nextHubDevice, p_mode );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_deleteTree ( T_mkHCDList* p_list, T_mkHCDDevice* p_device, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_device != K_MK_NULL )
   {
      /* Si le périphérique à supprimer est un hub */
      if ( p_device->hubDescriptor != K_MK_NULL )
      {
         /* Si le périphérique USB doit être retiré de la liste secondaire */
         if ( p_list != K_MK_NULL )
         {
            /* Suppression du périphérique de la liste secondaire */
            l_result = mk_hcd_remove ( p_list, p_device );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Suppression des périphériques connectés sur le hub */
         l_result |= mk_hcd_deleteHub ( p_list, p_device, p_mode );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le dispositif possède un descripteur de hub */
      if ( p_device->hubDescriptor != K_MK_NULL )
      {
         /* Suppression du descripteur de hub */
         l_result |= mk_pool_freeSafe ( g_mkHCDPool.hubPool, ( T_mkAddr ) p_device->hubDescriptor );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Sinon si le périphérique possède au moins une interface */
      if ( p_device->interfaceDescriptor != K_MK_NULL )
      {
         /* Suppresssion des descripteurs d'interface */
         l_result |= mk_hcd_deleteAllInterfaces ( p_device );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique doit être supprimé */
      if ( p_mode == K_MK_HCD_DELETE_ALL )
      {
         /* Si le périphérique n'est pas en tête de liste */
         if ( p_device->previousDevice != K_MK_NULL )
         {
            /* Actualisation de la chaine */
            p_device->previousDevice->nextDevice = p_device->nextDevice;
         }

         /* Sinon */
         else
         {
            /* Gestion du dispositif principal */
            if ( p_device->previousHubDevice != K_MK_NULL )
            {
               /* Actualisation du pointeur de hub */
               p_device->previousHubDevice->nextHubDevice = p_device->nextDevice;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Si le périphérique n'est pas en fin de liste */
         if ( p_device->nextDevice != K_MK_NULL )
         {
            /* Actualisation de la chaine */
            p_device->nextDevice->previousDevice = p_device->previousDevice;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désallocation du périphérique */
         l_result |= mk_pool_freeSafe ( g_mkHCDPool.devicePool, ( T_mkAddr ) p_device );
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
      /* La transmission d'un code K_MK_NULL en paramètre est valide. */
   }

   /* Retour */
   return ( l_result );
}
