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
* @file mk_hcd_setDeviceAddress.c
* @brief Définition de la fonction mk_hcd_setDeviceAddress.
* @date 28 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_setDeviceAddress ( T_mkHCDDevice* p_device, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Déclaration d'une variable contenant l'adresse du périphérique */
   uint8_t l_address = 0;

   /* Si les paramètres sont valides */
   if ( ( p_device != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Calcul d'une adresse pour le périphérique */
      l_result = mk_hcd_getAddress ( p_device, &l_address );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Création d'une requête de configuration de l'adresse */
         l_result = mk_hcd_createRequest ( &l_request, K_MK_HCD_SET_ADDRESS, K_MK_HCD_HOST_TO_DEVICE | K_MK_HCD_STANDARD | K_MK_HCD_DEVICE, ( uint16_t ) l_address, 0, 0 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Transmission de la requête */
            l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* La norme USB2.0 spécifie une attente maximale de 50ms pour traiter la requête de configuration de l'adresse. */
               /* En fonction du périphérique connecté, il peut être nécessaire d'attendre plus longtemps. Il peut arriver que le */
               /* périphérique acquitte la transaction (ZLP) alors que l'adresse n'est pas prise en compte. */

               /* Ce cas particulier est corrigé lors de la configuration du périphérique. Si un timeout est reçu lors de la demande */
               /* du descripteur du périphérique alors on retourne dans l'état ATTACHED_STATE avec l'adresse de défaut. */

               /* Attente de 55 ms */
               l_result = mk_task_sleep ( 55 );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Réception du paquet d'acquittement (ZLP) */
                  l_result = mk_hcd_sendPipe ( p_device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1, 0 );
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


