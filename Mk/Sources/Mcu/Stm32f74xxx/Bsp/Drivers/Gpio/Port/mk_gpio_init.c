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
* @file mk_gpio_init.c
* @brief Définition de la fonction mk_gpio_init.
* @date 20 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_gpio_init ( void )
{
   /* Initialisation de la broche PI8 (Expander Interruption) */
   gpio_pushPull ( K_GPIOI, 8 );
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_OFF, 8 );
   gpio_speed ( K_GPIOI, K_GPIO_HIGH_SPEED, 8 );
   gpio_setMode ( K_GPIOI, K_GPIO_INPUT, 8 );

   /* Initialisation de la broche d'interruption externe */
   exti_enableInterrupt ( K_EXTI_LINE8 );
   exti_enableRisingEdge ( K_EXTI_LINE8 );
   nvic_enableRequest ( K_NVIC_EXTI9_TO_EXTI5 );

   /* Routage de la broche d'interruption externe sur le port PI8 */
   syscfg_setMultiplexer ( K_SYSCFG_EXTI8, K_SYSCFG_PORTI );

   /* Retour */
   return;
}
