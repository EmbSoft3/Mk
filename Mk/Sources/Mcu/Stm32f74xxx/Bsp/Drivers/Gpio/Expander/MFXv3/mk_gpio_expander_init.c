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
* @file mk_gpio_expander_init.c
* @brief Définition de la fonction mk_gpio_expander_init.
* @date 20 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_expander_setup ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Pour le nombre de broches à configurer */
   for ( l_counter = 0 ; ( l_counter < MK_GPIO_EXPANDER_NUMBER_OF_PINS ) && ( l_result == K_MK_OK ) ; l_counter++ )
   {
      /* Configuration du type de broche GPIO */
      l_result |= mk_gpio_expander_type ( p_handler, l_counter, g_expanderSettingTable [ l_counter ] [ 1 ] );

      /* Configuration de la résistance de tirage de la broche GPIO */
      l_result |= mk_gpio_expander_resistor ( p_handler, l_counter, g_expanderSettingTable [ l_counter ] [ 2 ] );

      /* Si la broche doit être configurée à l'état bas */
      if ( g_expanderSettingTable [ l_counter ] [ 3 ] == 0 )
      {
         /* Configuration de la broche GPIO à l'état bas */
         l_result |= mk_gpio_expander_clear ( p_handler, l_counter );
      }

      /* Sinon */
      else
      {
         /* Configuration de la broche GPIO à l'état haut */
         l_result |= mk_gpio_expander_set ( p_handler, l_counter );
      }

      /* Configuration de la direction de la broche GPIO */
      l_result |= mk_gpio_expander_direction ( p_handler, l_counter, g_expanderSettingTable [ l_counter ] [ 0 ] );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_expander_start ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Définition du contenu de la trame I2C */
   uint8_t l_buf [ 2 ] = {
      MK_GPIO_EXPANDER_SYSCTRL_REGISTER_ADDR,
      MK_GPIO_EXPANDER_SYSCTRL_ENABLE_GPIO | MK_GPIO_EXPANDER_SYSCTRL_ENABLE_ALTERNATE_GPIO
   };

   /* Déclaration d'une trame I2C */
   T_mkI2CFrame l_frame = {
      K_I2C_WRITE,
      l_buf, 2, MK_GPIO_EXPANDER_TIMEOUT,
      K_MK_NULL, 0, MK_GPIO_EXPANDER_TIMEOUT
   };

   /* Déclaration d'un registre de statut */
   T_mkI2CTransferStatus l_status = {
      0, 0, 0, K_MK_NULL
   };

   /* Transfert de la trame I2C */
   l_result = mk_i2c_postMessage ( p_handler->device, &l_frame, &l_status, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_expander_openPort ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure de configuration d'un port I2C */
   T_mkI2CSetting l_setting = {
         K_MK_I2C1,
         MK_GPIO_EXPANDER_ADDR, 0, 0, K_I2C_7BITS_MODE, 1,
         0x04, 0x32, 0x27, 0x09, 0x01
   };

   /* Ouverture d'un port de communication I2C */
   l_result = mk_i2c_open ( &p_handler->device, &l_setting, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_expander_init ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si le paramètre est valide */
   if ( ( p_handler != K_MK_NULL ) && ( p_handler->device == K_MK_NULL ) )
   {
      /* Ouverture d'un port de communication I2C */
      l_result = mk_gpio_expander_openPort ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Réinitialisation du périphérique MFX */
         l_result = mk_gpio_expander_reset ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Activation des broches GPIO */
            l_result = mk_gpio_expander_start ( p_handler );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration des broches GPIO */
               l_result = mk_gpio_expander_setup ( p_handler );
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



