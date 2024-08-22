/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_hcd_searchEndpoint.c
* @brief Définition de la fonction mk_hcd_searchEndpoint.
* @date 5 janv. 2020
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_searchEndpoint ( T_mkHCDInterfaceDescriptor* p_interface, T_mkHCDEndpointDescriptor** p_endpoint, uint32_t p_type, uint32_t p_direction )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de terminaison */
   T_mkHCDEndpointDescriptor* l_endpoint;

   /* Si les paramètres sont valides */
   if ( ( p_interface != K_MK_NULL ) && ( p_endpoint != K_MK_NULL ) )
   {
      /* Réinitialisation du résultat */
      ( *p_endpoint ) = K_MK_NULL;

      /* Initialisation du pointeur de terminaison */
      l_endpoint = p_interface->endpoint;

      /* Pour toutes les terminaisons de l'interface */
      while ( l_endpoint != K_MK_NULL )
      {
         /* Si la terminaison est du type recherchée et possède la direction recherchée */
         if ( ( ( l_endpoint->bmAttributes & 0x3 ) == p_type ) && ( ( ( l_endpoint->bEndpointAddress & 0x80 ) >> 7 ) == p_direction ) )
         {
            /* Actualisation de la valeur de retour */
            ( *p_endpoint ) = l_endpoint;

            /* Arrêt de la boucle */
            l_endpoint = K_MK_NULL;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le processus ne doit pas s'arrêté */
         if ( l_endpoint != K_MK_NULL )
         {
            /* Actualisation du pointeur d'interface */
            l_endpoint = l_endpoint->nextEndpoint;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
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



