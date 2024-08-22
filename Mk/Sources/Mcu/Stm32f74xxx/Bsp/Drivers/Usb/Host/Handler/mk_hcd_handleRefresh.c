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
* @file mk_hcd_handleRefresh.c
* @brief Définition de la fonction mk_hcd_handleRefresh.
* @date 24 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleRefresh ( T_mkHCDHandler* p_handler, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si au moins un périphérique est présent sur le bus */
   if ( p_handler->device != K_MK_NULL )
   {
      /* Si le premier périphérique n'a pas été configuré */
      if ( ( p_handler->device->state & K_MK_HCD_DEVICE_DISPATCHED_STATE ) != K_MK_HCD_DEVICE_DISPATCHED_STATE )
      {
         /* Lançement du processus d'énumération */
         l_result = mk_hcd_enumerate ( p_handler, p_handler->device, p_pipe );
      }

      /* Sinon */
      else
      {
         /* Lançement du processus d'analyse des hubs */
         l_result = mk_hcd_handleHub ( p_handler, p_pipe );
      }

      /* Si aucune erreur critique ne s'est produite */
      if ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) == K_MK_OK )
      {
         /* Transmission de l'événement de rafraichissement */
         l_result = mk_event_set ( p_handler->portEvent, K_MK_HCD_REFRESH_EVENT );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Attente de 5 ms entre chaque intervalle de rafraichissement */
            l_result = mk_task_sleep ( K_MK_HCD_HUB_REFRESH_TIMEOUT + 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Une erreur critique s'est produite. */
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* Une erreur critique s'est produite. */
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


