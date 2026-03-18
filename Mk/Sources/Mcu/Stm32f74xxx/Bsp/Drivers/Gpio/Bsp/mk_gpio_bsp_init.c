/**
*
* @copyright Copyright (C) 2026 RENARD Mathieu. All rights reserved.
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
* @file mk_gpio_bsp_init.c
* @brief Définition de la fonction mk_gpio_bsp_init.
* @date 17 mars 2026
*
*/

#include "mk_gpio_api.h"

/* Constantes dédiées à la carte STM32F746G-Eval2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_bsp_init ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Configuration du voyant lumineux (K_MK_GPIO_PIN_LED1) */
   gpio_setMode ( K_GPIOF, K_GPIO_OUTPUT, 10 );
   gpio_setHigh ( K_GPIOF, 10 );

   /* Configuration du voyant lumineux (K_MK_GPIO_PIN_LED2) */
   gpio_setMode ( K_GPIOF, K_GPIO_OUTPUT, 10 );
   gpio_setHigh ( K_GPIOB, 7 );

   /* Effectue */
   do
   {
      /* Tentative d'initialisation du périphérique MFX */
      l_result = mk_gpio_expander_mfxv3_init ( p_handler );

      /* Attente 10 ms */
      l_result |= mk_task_sleep ( K_MK_GPIO_REQUEST_TIMEOUT );

      /* Tant que l'initialisation n'est pas terminée et tant qu'aucune erreur critique ne s'est produite */
   } while ( ( l_result == K_MK_ERROR_TIMEOUT ) || ( l_result == K_MK_ERROR_COMM ) );

   /* Retour */
   return ( l_result );
}

/* On inclut les constantes dédiées à la carte STM32F746G-DISCO REV.C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_bsp_init ( T_mkGPIOHandler* p_handler )
{
   /* Suppression Warning */
   ( void ) p_handler;
   
   /* Initialisation de la broche MMC_DETECT (K_MK_GPIO_SDCARD_DETECT) */
   gpio_setMode ( K_GPIOC, K_GPIO_INPUT, 13 );
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 13 );
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_UP, 13 );

   /* Initialisation de la broche B_USER (K_MK_GPIO_USER_PUSHBUTTON) */
   gpio_setMode ( K_GPIOI, K_GPIO_INPUT, 11 );
   gpio_speed ( K_GPIOI, K_GPIO_MEDIUM_SPEED, 11 );
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_OFF, 11 );

   /* Retour */
   return ( K_MK_OK );
}

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif

/**
 *
 */


