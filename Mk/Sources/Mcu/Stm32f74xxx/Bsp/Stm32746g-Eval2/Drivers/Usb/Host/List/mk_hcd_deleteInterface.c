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
* @file mk_hcd_deleteInterface.c
* @brief Définition de la fonction mk_hcd_deleteInterface.
* @date 4 nov. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_deleteInterface ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable d'état */
   uint32_t l_lock = 0;

   /* Déclaration d'un pointeur de terminaison */
   T_mkHCDEndpointDescriptor *l_endpoint, *l_nextEndpoint;

   /* Déclaration des pointeurs d'interfaces */
   T_mkHCDInterfaceDescriptor *l_interface, *l_previousInterface = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_interface != K_MK_NULL ) )
   {
      /* Récupération de l'adresse de la première interface */
      l_interface = p_device->interfaceDescriptor;

      /* Tant que toutes les interfaces n'ont pas été analysée */
      while ( ( l_interface != K_MK_NULL ) && ( l_lock == 0 ) )
      {
         /* Si l'interface courante doit être supprimée */
         if ( l_interface == p_interface )
         {
            /* Récupération du pointeur de terminaison */
            l_endpoint = l_interface->endpoint;

            /* Tant que toutes les terminaisons de l'interface n'ont pas été désallouées */
            while ( l_endpoint != K_MK_NULL )
            {
               /* Enregistrement de l'adresse de la prochaine terminaison */
               l_nextEndpoint = l_endpoint->nextEndpoint;

               /* Suppression de la mémoire allouée */
               l_result |= mk_pool_freeSafe ( g_mkHCDPool.endpointPool, ( T_mkAddr ) l_endpoint );

               /* Actualisation du pointeur de terminaison */
               l_endpoint = l_nextEndpoint;
            }

            /* Si l'interface n'est pas en tête de liste */
            if ( l_previousInterface != K_MK_NULL )
            {
               /* Actualisation du pointeur d'interface */
               l_previousInterface->nextInterface = l_interface->nextInterface;
            }

            /* Sinon */
            else
            {
               /* Actualisation du pointeur d'interface */
               p_device->interfaceDescriptor = l_interface->nextInterface;
            }

            /* Suppression de la mémoire allouée */
            l_result |= mk_pool_freeSafe ( g_mkHCDPool.interfacePool, ( T_mkAddr ) l_interface );

            /* L'interface et ses terminaisons ont été supprimées, on arrête la boucle */
            l_lock = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de la valeur de l'interface précédente */
         l_previousInterface = l_interface;

         /* Actualisation du pointeur d'interface */
         l_interface = l_interface->nextInterface;
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



