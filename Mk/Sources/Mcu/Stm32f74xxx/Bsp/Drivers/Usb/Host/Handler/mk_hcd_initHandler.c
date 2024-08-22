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
* @file mk_hcd_initHandler.c
* @brief Définition de la fonction mk_hcd_initHandler.
* @date 16 juin 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_initHostHandler ( T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Configuration de la durée initial du reset */
   p_handler->resetTick = K_MK_USB_RESET_TICK;

   /* Initialisation du champ d'événements dédié au port USB */
   l_result = mk_event_create ( &p_handler->portEvent, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du mutex gérant l'allocation des canaux de communication */
      l_result = mk_mutex_create ( &p_handler->channelMutex, K_MK_AREA_PROTECTED );

      /* Initialisation des champs d'événements dédiés aux canaux de communication */
      for ( l_counter = K_USB_CHANNEL0 ; ( l_counter < K_MK_USB_CHANNEL_NUMBER ) && ( l_result == K_MK_OK ) ; l_counter++ )
      {
         l_result = mk_event_create ( &p_handler->channelEvent [ l_counter ], K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_initHandler ( T_mkHCDHandler* p_handler, T_mkAddr p_bus )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( ( p_bus == K_USB_OTGHS ) || ( p_bus == K_USB_OTGFS ) ) )
   {
      /* Initialisation du gestionnaire USB de type host  */
      l_result = mk_hcd_initHostHandler ( p_handler );

      /* Configuration de l'adresse du périphérique matériel (bus) */
      p_handler->bus = p_bus;
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


