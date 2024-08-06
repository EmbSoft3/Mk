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
* @file mk_hcd_deleteUnusedInterfaces.c
* @brief Définition de la fonction mk_hcd_deleteUnusedInterfaces.
* @date 11 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_deleteUnusedInterfaces ( T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de terminaison */
   T_mkHCDEndpointDescriptor *l_endpoint, *l_nextEndpoint;

   /* Déclaration des pointeurs d'interface */
   T_mkHCDInterfaceDescriptor *l_interface, *l_nextInterface;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_interface != K_MK_NULL ) )
   {
      /* Récupération de l'adresse de la première interface */
      l_interface = p_device->interfaceDescriptor;

      /* Tant que toutes les interfaces n'ont pas été désallouées */
      while ( l_interface != K_MK_NULL )
      {
         /* Enregistrement de l'adresse de la prochaine interface */
         l_nextInterface = l_interface->nextInterface;

         /* Si l'interface courante doit être supprimée */
         if ( l_interface != p_interface )
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

               /* Actualisation du pointeur de structure */
               l_endpoint = l_nextEndpoint;
            }

            /* Suppression de la mémoire allouée */
            l_result |= mk_pool_freeSafe ( g_mkHCDPool.interfacePool, ( T_mkAddr ) l_interface );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine interface */
         l_interface = l_nextInterface;
      }

      /* Actualisation du pointeur d'interface */
      p_device->interfaceDescriptor = p_interface;
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


