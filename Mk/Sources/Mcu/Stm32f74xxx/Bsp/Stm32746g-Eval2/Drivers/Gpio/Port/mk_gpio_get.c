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
* @file mk_gpio_get.c
* @brief Définition de la fonction mk_gpio_get.
* @date 22 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_get ( uint32_t p_port, uint32_t p_pinNumber, uint32_t* p_value )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = g_mkTermioHandler.gpio;

   /* Déclaration d'une variable pointant sur l'adresse du gestionnaire GPIO */
   T_mkGPIOHandler* l_handler;

   /* Déclaration d'une variable de travail */
   T_mkAddr l_addrTable [ ] = { 0, K_GPIOA, K_GPIOB, K_GPIOC,
         K_GPIOD, K_GPIOE, K_GPIOF, K_GPIOG, K_GPIOH, K_GPIOI, K_GPIOJ, K_GPIOK };

   /* Si les paramètres sont valides */
   if ( ( p_value != K_MK_NULL ) && ( p_port <= K_MK_GPIO_PORTK ) )
   {
      /* Récupération de l'adresse du gestionnaire GPIO */
      l_result = mk_termio_getChild ( l_termio, ( T_mkAddr* ) &l_handler );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_handler != K_MK_NULL ) )
      {
         /* Si une broche du périphérique MFX doit être configurée */
         if ( p_port == K_MK_GPIO_EXPANDER )
         {
            /* Si le numéro de la broche est valide */
            if ( p_pinNumber < MK_GPIO_EXPANDER_NUMBER_OF_PINS )
            {
               /* Récupération de la valeur de la broche */
               *p_value = ( uint32_t ) ( ( ( l_handler->ctrl.expander.current ) >> ( p_pinNumber ) ) & 0x1 );
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_PARAM;
            }
         }

         /* Sinon */
         else
         {
            /* Si le numéro de la broche est valide */
            if ( p_pinNumber < K_GPIO_NUMBER_OF_PINS_PER_PORT )
            {
               /* Récupération de la valeur de la broche */
               *p_value = gpio_get ( l_addrTable [ p_port ], p_pinNumber );
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_PARAM;
            }
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



