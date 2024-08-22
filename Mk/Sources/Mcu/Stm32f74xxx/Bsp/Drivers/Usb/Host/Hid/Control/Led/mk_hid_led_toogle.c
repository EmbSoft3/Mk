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
* @file mk_hid_led_toogle.c
* @brief Définition de la fonction mk_hid_led_toogle.
* @date 4 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_hid_led_toogle ( T_mkLed* p_led, uint16_t p_id )
{
   /* Si le paramètre est valide */
   if ( p_led != K_MK_NULL )
   {
      /* Tant que l'intégralité des indicateurs n'ont pas parcourus */
      while ( p_led != K_MK_NULL )
      {
         /* Si l'indicateur recherché a été trouvé */
         if ( p_led->layer.id == ( uint16_t ) p_id )
         {
            /* Actualisation des attributs */
            p_led->state.lastValue = p_led->state.value;
            p_led->state.value = ( int16_t ) ( ~ p_led->state.value );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du pointeur de led */
         p_led = p_led->nextLed;
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Il se peut que le contrôle (clavier par exemple) ne possède pas d'indicateur */
   }

   /* Retour */
   return;
}

