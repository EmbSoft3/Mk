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
* @file mk_hid_led_setType.c
* @brief Définition de la fonction mk_hid_led_setType.
* @date 4 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_led_setType ( T_mkLed* p_led, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_led != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Une LED peut être caractérisé par les types 'Selector' (Sel) ou 'ON/OFF Controls' (OOC - Single Button Toogle ). */
      /* A l'exception du type 'Selector', la valeur 1 tourne l'indicateur ON et la valeur 0 tourne l'indicateur OFF. */

      /* Si l'usage est de type 'Variable' */
      if ( ( p_usage->last->value & K_MK_HID_ITEM_VARIABLE ) == K_MK_HID_ITEM_VARIABLE )
      {
         /* Une led de type OOC est codée sur 1 bit non signé. L'état ON est codé par la valeur 1, l'état OFF est codé par la valeur 0. */

         /* Si la led est de type 'ON-OFF' (OOC) - NO_PREFERRED_MAIN, ABSOLUTE */
         if ( ( ( p_usage->last->value & ( K_MK_HID_ITEM_NO_PREFERRED | K_MK_HID_ITEM_RELATIVE ) ) == K_MK_HID_ITEM_NO_PREFERRED ) &&
                ( p_table->global.logicalMinimum == 0 ) && ( p_table->global.logicalMaximum == 1 ) )
         {
            /* Cet indicateur est à double état, la valeur 1 réprésente l'état ON, la valeur 0 génére l'état OFF. */

            /* Actualisation de l'état de la LED */
            p_led->layer.type = K_MK_LED_ON_OFF_CONTROL;
         }

         /* Sinon */
         else
         {
            /* Le type de la LED n'est pas identifié, aucun événement ne doit être généré. */
            /* Actualisation de l'état de la LED */
            p_led->layer.type = K_MK_LED_UNKNOWN_CONTROL;
         }
      }

      /* Sinon */
      else
      {
         /* L'état de la led est exprimée sous forme d'un sélecteur de type 'ARRAY'. */
         /* Ce type permet permet de coder des états complexe comme 'INDICATOR_ON', 'INDICATOR_SLOW_BLINK', ... */
         /* Actualisation de l'état de la LED */
         p_led->layer.type = K_MK_LED_SELECTOR_CONTROL;
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



