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
* @file mk_gpio_handleRequest.c
* @brief Définition de la fonction mk_gpio_handleRequest.
* @date 23 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_handleSetupRequest ( T_mkGPIOHandler* p_handler, uint32_t p_port, T_mkGPIOSetting* p_setting, uint32_t p_pinNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une table de configuration */
   T_mkAddr l_addrTable [ ] = { 0, K_GPIOA, K_GPIOB, K_GPIOC,
         K_GPIOD, K_GPIOE, K_GPIOF, K_GPIOG, K_GPIOH, K_GPIOI, K_GPIOJ, K_GPIOK };

   /* Si les paramètres de configuration sont valides */
   if ( ( p_port <= K_MK_GPIO_PORTK ) && ( p_setting != K_MK_NULL ) && ( p_setting->direction <= K_MK_GPIO_OUTPUT ) &&
         ( p_setting->type <= K_MK_GPIO_OPENDRAIN ) && ( p_setting->resistor <= K_MK_GPIO_PULLUP ) )
   {
      /* Si une broche du périphérique MFX doit être configurée */
      if ( p_port == K_MK_GPIO_EXPANDER )
      {
         /* Si le numéro de la broche est valide */
         if ( p_pinNumber < MK_GPIO_EXPANDER_NUMBER_OF_PINS )
         {
            /* Configuration de la broche GPIO */
            l_result  = mk_gpio_expander_direction ( p_handler, p_pinNumber, p_setting->direction );
            l_result |= mk_gpio_expander_type ( p_handler, p_pinNumber, p_setting->type );
            l_result |= mk_gpio_expander_resistor ( p_handler, p_pinNumber, p_setting->resistor );
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }
      }

      /* Sinon (port classique) */
      else
      {
         /* Si le numéro de la broche est valide */
         if ( p_pinNumber < K_GPIO_NUMBER_OF_PINS_PER_PORT )
         {
            /* Configuration de la direction de broche d'entrée-sortie */
            gpio_setMode ( l_addrTable [ p_port ], p_setting->direction, p_pinNumber );

            /* Si la broche est configurée en entrée */
            if ( p_setting->direction == K_MK_GPIO_INPUT )
            {
               /* Mode push-pull par défaut dans le cas d'une entrée */
               gpio_pushPull ( l_addrTable [ p_port ], p_pinNumber );

               /* Si la résitance de tirage doit être désactivée */
               if ( p_setting->type == K_MK_GPIO_DISABLE_PULL )
               {
                  /* Désactivation de la résitance de tirage */
                  gpio_resistor ( l_addrTable [ p_port ], K_GPIO_PULL_OFF, p_pinNumber );
               }

               /* Sinon */
               else
               {
                  /* Si la résitance de pullup doit être activée */
                  if ( p_setting->resistor == K_MK_GPIO_PULLUP )
                  {
                     /* Activation de la résitance de pullup */
                     gpio_resistor ( l_addrTable [ p_port ], K_GPIO_PULL_UP, p_pinNumber );
                  }

                  /* Sinon */
                  else
                  {
                     /* Activation de la résitance de pulldown */
                     gpio_resistor ( l_addrTable [ p_port ], K_GPIO_PULL_DOWN, p_pinNumber );
                  }
               }
            }

            /* Sinon (sortie) */
            else
            {
               /* Désactivation de la résitance de tirage */
               gpio_resistor ( l_addrTable [ p_port ], K_GPIO_PULL_OFF, p_pinNumber );

               /* Si la résitance de tirage doit être désactivée */
               if ( p_setting->type == K_MK_GPIO_OPENDRAIN )
               {
                  /* Configuration de la broche en mode opendrain */
                  gpio_openDrain ( l_addrTable [ p_port ], p_pinNumber );
               }

               /* Sinon */
               else
               {
                  /* Configuration de la broche en mode push-pull */
                  gpio_pushPull ( l_addrTable [ p_port ], p_pinNumber );
               }
            }
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_handleSetRequest ( T_mkGPIOHandler* p_handler, uint32_t p_port, uint32_t p_pinNumber, uint32_t p_value )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une table de configuration */
   T_mkAddr l_addrTable [ ] = { 0, K_GPIOA, K_GPIOB, K_GPIOC,
         K_GPIOD, K_GPIOE, K_GPIOF, K_GPIOG, K_GPIOH, K_GPIOI, K_GPIOJ, K_GPIOK };

   /* Si les paramètres de configuration sont valides */
   if ( p_port <= K_MK_GPIO_PORTK )
   {
      /* Si une broche du périphérique MFX doit être configurée */
      if ( p_port == K_MK_GPIO_EXPANDER )
      {
         /* Si le numéro de la broche est valide */
         if ( p_pinNumber < MK_GPIO_EXPANDER_NUMBER_OF_PINS )
         {
            /* Si la broche doit être positionnée à l'état haut */
            if ( p_value != 0 )
            {
               /* Configuration du niveau de la broche à la valeur HIGH */
               l_result = mk_gpio_expander_set ( p_handler, p_pinNumber );
            }

            /* Sinon */
            else
            {
               /* Configuration du niveau de la broche à la valeur LOW */
               l_result = mk_gpio_expander_clear ( p_handler, p_pinNumber );
            }
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }
      }

      /* Sinon (port GPIO classique) */
      else
      {
         /* Si le numéro de la broche est valide */
         if ( p_pinNumber < K_GPIO_NUMBER_OF_PINS_PER_PORT )
         {
            /* Si la broche doit être positionnée à l'état haut */
            if ( p_value != 0 )
            {
               /* Configuration du niveau de la broche à la valeur HIGH */
               gpio_setHigh ( l_addrTable [ p_port ], p_pinNumber );
            }

            /* Sinon */
            else
            {
               /* Configuration du niveau de la broche à la valeur LOW */
               gpio_setLow ( l_addrTable [ p_port ], p_pinNumber );
            }
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_handleRequest ( T_mkTask* p_task, T_mkGPIOHandler* p_handler, T_mkGPIOMessage* p_message, uint32_t p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) )
   {
      /* Si une tâche non privilégiée tente d'accéder à une broche protégée */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) &&
         ( ( g_mkGPIOProtectionTable [ p_message->port ] & ( uint32_t ) ( 1 << p_message->pinNumber ) ) > 0 ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }

      /* Sinon */
      else
      {
         /* Si une requête de type SETUP doit être exécutée */
         if ( p_request == K_MK_GPIO_SETUP )
         {
            /* Configuration de la broche GPIO demandée par l'utilisateur */
            l_result = mk_gpio_handleSetupRequest ( p_handler, p_message->port, p_message->setting, p_message->pinNumber );
         }

         /* Sinon si une requête de type SET doit être exécutée */
         else if ( p_request == K_MK_GPIO_SET )
         {
            /* Configuration de l'état de la broche GPIO demandée par l'utilisateur */
            l_result =  mk_gpio_handleSetRequest ( p_handler, p_message->port, p_message->pinNumber, ( uint32_t ) p_message->setting );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



