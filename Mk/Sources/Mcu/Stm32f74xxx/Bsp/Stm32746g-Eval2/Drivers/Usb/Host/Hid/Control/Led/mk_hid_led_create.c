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
* @file mk_hid_led_create.c
* @brief Définition de la fonction mk_hid_led_create.
* @date 4 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_led_setDefaultState ( T_mkLed* p_led )
{
   /* Si l'identifiant de la LED est de type NUM_LOCK */
   if ( p_led->layer.id == K_MK_HID_LED_PAGE_NUM_LOCK )
   {
      /* Configuration de l'état initial de la LED */
      /* Elle est allumée par défaut */
      p_led->state.value = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_led_create ( T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_ledNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de led */
   T_mkLed** l_led = K_MK_NULL;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_table != K_MK_NULL ) && ( p_usage != K_MK_NULL ) )
   {
      /* Si les 'n' led peuvent être allouées */
      if ( ( p_ledNumber <= K_MK_LED_NUMBER ) )
      {
         /* Récupération de l'adresse d'allocation de l'objet */
         l_led = ( T_mkLed** ) &p_usage->first->addr;

         /* Configuration de la taille de destination */
         p_usage->first->head.field.destinationSize = 8;

         /* Pour le nombre de led à allouer */
         for ( l_counter = 0 ; ( l_counter < p_ledNumber ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Allocation d'une led */
            l_result = mk_pool_allocSafe ( g_mkLedPool.pool, ( T_mkAddr* ) l_led, K_MK_POOL_CLEAR, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( ( *l_led ) != K_MK_NULL ) )
            {
               /* Si plusieurs leds ont été allouées */
               if ( p_ledNumber != 1 )
               {
                  /* L'allocation a été provoqué par la détection des balises 'Usage Minimum' et 'Usage Maximum' */
                  /* L'identifiant de départ est donc égale à 'Usage Minimum' */

                  /* Configuration de l'identifiant de la led */
                  ( *l_led )->layer.id = ( uint16_t ) ( ( uint16_t ) ( p_table->local->usageMinimum ) + ( uint16_t ) l_counter );

                  /* Configuration des valeurs minimales et maximales de la Led */
                  ( *l_led )->layer.min = p_table->global.logicalMinimum;
                  ( *l_led )->layer.max = p_table->global.logicalMaximum;

                  /* Configuration de l'état initial de la LED */
                  mk_hid_led_setDefaultState ( *l_led );
               }

               /* Sinon */
               else
               {
                  /* L'allocation a été provoqué par la détection d'une balise 'Usage' */
                  /* L'identifiant est donc contenu dans la valeur de la structure p_usage */

                  /* Configuration de l'identifiant de la led */
                  ( *l_led )->layer.id = ( uint16_t ) ( p_usage->first->value & 0xFFFF );
               }

               /* Configuration du type de la led */
               l_result = mk_hid_led_setType ( *l_led, p_table, p_usage );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Actualisation du pointeur de led */
            l_led = &( *l_led )->nextLed;
         }

         /* Si l'allocation des leds a échoué */
         if ( l_result != K_MK_OK )
         {
            /* Récupération de l'adresse d'allocation du premier objet */
            l_led = ( T_mkLed** ) &p_usage->first->addr;

            /* Pour l'ensemble des leds à désallouer */
            while ( ( l_counter != 0 ) && ( ( *l_led ) != K_MK_NULL ) )
            {
               /* Désallocation de la led courante */
               l_result |= mk_pool_freeSafe ( g_mkLedPool.pool, ( *l_led ) );

               /* Actualisation du pointeur de led */
               l_led = &( *l_led )->nextLed;

               /* Actualisation du compteur de led */
               l_counter = l_counter - 1;
            }

            /* L'intégralité des leds ne peuvent pas être allouée */
            /* Il est nécessaire d'actualiser l'adresse de l'usage */
            p_usage->first->addr = K_MK_NULL;
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
         /* L'intégralité des leds ne peuvent pas être allouée */
         /* Ceci n'est pas une erreur, on actualise donc le champ 'addr' pour ignorer l'usage */
         p_usage->first->addr = K_MK_NULL;
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



