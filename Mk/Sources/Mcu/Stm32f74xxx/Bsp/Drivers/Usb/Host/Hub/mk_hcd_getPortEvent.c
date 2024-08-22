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
* @file mk_hcd_getPortEvent.c
* @brief Définition de la fonction mk_hcd_getPortEvent.
* @date 18 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkHCDPortEvent mk_hcd_getPortEvent ( uint8_t* p_buf, uint32_t p_portNumber, T_mkHCDPipeStatus p_pipeStatus )
{
   /* Déclaration d'une variable de retour */
   T_mkHCDPortEvent l_result = K_MK_HCD_PORT_EVENT_NOT_DETECTED;

   /* Déclaration d'une variable de travail */
   uint32_t l_offset = 0;

   /* Si le paramètre est valide et si un ACK a été reçu */
   if ( ( p_buf != K_MK_NULL ) && ( ( p_pipeStatus & K_MK_HCD_FLAG_ACK ) == K_MK_HCD_FLAG_ACK ) )
   {
      /* Détermination de l'offset du port */
      l_offset = ( p_portNumber >> 3 );

      /* Détermination de l'indice du bit */
      p_portNumber = ( uint32_t ) ( 1 << ( p_portNumber - ( l_offset << 3 ) ) ) ;

      /* Si un événement s'est produit sur le port */
      if ( ( p_buf [ l_offset ] & p_portNumber ) == p_portNumber )
      {
         /* Réinitialisation de l'événement */
         p_buf [ l_offset ] &= ( uint8_t ) ( ~ p_portNumber );

         /* Actualisation de la variable de retour */
         l_result = K_MK_HCD_PORT_EVENT_DETECTED;
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

   /* Retour */
   return ( l_result );
}


