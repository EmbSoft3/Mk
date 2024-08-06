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
* @file mk_hcd_getTimeRemaining.c
* @brief Définition de la fonction mk_hcd_getTimeRemaining.
* @date 19 oct. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_hcd_getTimeRemaining ( T_mkHCDDevice* p_device, T_mkHCDEndpointDescriptor* p_endpoint, uint32_t p_timeout )
{
   /* Déclaration d'une variable de retour */
   uint32_t l_result;

   /* Si l'intervalle de rafraichissement n'est pas terminé */
   if ( p_endpoint->tick.period > p_timeout )
   {
      /* Actualisation de l'intervalle */
      p_endpoint->tick.period -= p_timeout;

      /* Actualisation de la variable de retour */
      l_result = p_endpoint->tick.period;
   }

   /* Sinon */
   else
   {
      /* Si le périphérique est de type LS ou FS */
      if ( p_device->layer.speed != K_USB_HIGH_SPEED )
      {
         /* Configuration de l'interval de polling */
         /* Il est exprimé en multiple de 1ms, la valeur peut varier entre 1 et 255 */
         p_endpoint->tick.period = ( uint32_t ) p_endpoint->bInterval;
      }

      /* Sinon */
      else
      {
         /* Configuration de l'interval de polling */
         /* Il est exprimé en multiple de 125µs, la valeur peut varier entre 1 et 16 */
         p_endpoint->tick.period = ( uint32_t ) ( 1 << ( p_endpoint->bInterval - 1 ) ) >> 3;
      }

      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Retour */
   return ( l_result );
}



