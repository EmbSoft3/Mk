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
* @file mk_display_initGPIO.c
* @brief Définition de la fonction mk_display_initGPIO.
* @date 22 févr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_setGPIOMode ( void )
{
   /* Configuration du mode des broches de contrôle de l'écran */
   /* [HSYNC, VSYNC, CLK, DE, LCD_DISP et LCD-BLCTRL]. */
   gpio_setMode ( K_GPIOK, K_GPIO_OUTPUT, 3 );                 /* LCD-BLCTRL */
   gpio_setMode ( K_GPIOI, K_GPIO_OUTPUT, 12 );                /* LCD_DISP */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 10 );             /* HSYNC */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 9 );              /* VSYNC */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 14 );             /* CLK */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 7 );              /* DE */

   /* Configuration du mode des broches [R0:R7] de l'écran */
   /* */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 15 );             /* R0 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 0 );              /* R1 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 1 );              /* R2 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 2 );              /* R3 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 3 );              /* R4 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 4 );              /* R5 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 5 );              /* R6 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 6 );              /* R7 */

   /* Configuration du mode des broches [G0: G7] de l'écran */
   /* */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 7 );              /* G0 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 8 );              /* G1 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 9 );              /* G2 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 10 );             /* G3 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 11 );             /* G4 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 0 );              /* G5 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 1 );              /* G6 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 2 );              /* G7 */

   /* Configuration du mode des broches [B0:B7] de l'écran. */
   /* */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 4 );              /* B0 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 13 );             /* B1 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 14 );             /* B2 */
   gpio_setMode ( K_GPIOJ, K_GPIO_ALTERNATE, 15 );             /* B3 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 12 );             /* B4 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 4 );              /* B5 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 5 );              /* B6 */
   gpio_setMode ( K_GPIOK, K_GPIO_ALTERNATE, 6 );              /* B7 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_setGPIOAlternateMode ( void )
{
   /* Multiplexage des broches de contrôle de l'écran */
   /* [HSYNC, VSYNC, CLK, DE]. */
   gpio_alternate ( K_GPIOI, K_GPIO_AF14, 10 );                /* HSYNC */
   gpio_alternate ( K_GPIOI, K_GPIO_AF14, 9 );                 /* VSYNC */
   gpio_alternate ( K_GPIOI, K_GPIO_AF14, 14 );                /* CLK */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 7 );                 /* DE */

   /* Multiplexage des broches de [R0:R7] de l'écran */
   /* */
   gpio_alternate ( K_GPIOI, K_GPIO_AF14, 15 );                /* R0 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 0 );                 /* R1 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 1 );                 /* R2 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 2 );                 /* R3 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 3 );                 /* R4 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 4 );                 /* R5 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 5 );                 /* R6 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 6 );                 /* R7 */

   /* Multiplexage des broches [G0:G7] de contrôle de l'écran */
   /* */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 7 );                 /* G0 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 8 );                 /* G1 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 9 );                 /* G2 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 10 );                /* G3 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 11 );                /* G4 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 0 );                 /* G5 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 1 );                 /* G6 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 2 );                 /* G7 */

   /* Multiplexage des broches [B0:B7] de l'écran. */
   /* */
   gpio_alternate ( K_GPIOE, K_GPIO_AF14, 4 );                 /* B0 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 13 );                /* B1 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 14 );                /* B2 */
   gpio_alternate ( K_GPIOJ, K_GPIO_AF14, 15 );                /* B3 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF9, 12 );                 /* B4 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 4 );                 /* B5 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 5 );                 /* B6 */
   gpio_alternate ( K_GPIOK, K_GPIO_AF14, 6 );                 /* B7 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_setGPIOSpeed ( void )
{
   /* Configuration de la vitesse des broches de contrôle */
   /* de l'écran [HSYNC, VSYNC, CLK, DE, LCD_DISP et LCD-BLCTRL]. */
   gpio_speed ( K_GPIOK, K_GPIO_LOW_SPEED, 3 );                     /* BLCTRL */
   gpio_speed ( K_GPIOI, K_GPIO_LOW_SPEED, 12 );                    /* LCD_DISP */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 10 );              /* HSYNC */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 9 );               /* VSYNC */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 14 );              /* CLK */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 7 );               /* DE */

   /* Configuration de la vitesse des broches [R0:R7] de */
   /* l'écran. */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 15 );              /* R0 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 0 );               /* R1 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 1 );               /* R2 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 2 );               /* R3 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 3 );               /* R4 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 4 );               /* R5 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 5 );               /* R6 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 6 );               /* R7 */

   /* Configuration de la vitesse des broches [G0:G7] de */
   /* l'écran. */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 7 );               /* G0 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 8 );               /* G1 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 9 );               /* G2 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 10 );              /* G3 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 11 );              /* G4 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 0 );               /* G5 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 1 );               /* G6 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 2 );               /* G7 */

   /* Configuration de la vitesse des broches [B0:B7] de */
   /* l'écran. */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 4 );               /* B0 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 13 );              /* B1 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 14 );              /* B2 */
   gpio_speed ( K_GPIOJ, K_GPIO_VERY_HIGH_SPEED, 15 );              /* B3 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 12 );              /* B4 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 4 );               /* B5 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 5 );               /* B6 */
   gpio_speed ( K_GPIOK, K_GPIO_VERY_HIGH_SPEED, 6 );               /* B7 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_display_setGPIOResistor ( void )
{
   /* Configuration de la résistance de tirage des broches de contrôle */
   /* de l'écran [HSYNC, VSYNC, CLK, LCD_DISP et LCD-BLCTRL]. */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 3 );              /* BLCTRL */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_OFF, 12 );             /* LCD_DISP */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 10 );              /* HSYNC */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 9 );               /* VSYNC */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 14 );              /* CLK */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_DOWN, 7 );             /* DE */

   /* Configuration de la résistance de tirage des broches [R0:R7] de */
   /* l'écran. */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_OFF, 15 );             /* R0 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 0 );              /* R1 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 1 );              /* R2 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 2 );              /* R3 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 3 );              /* R4 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 4 );              /* R5 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 5 );              /* R6 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 6 );              /* R7 */

   /* Configuration de la résistance de tirage des broches [G0:G7] de */
   /* l'écran. */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 7 );              /* G0 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 8 );              /* G1 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 9 );              /* G2 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 10 );             /* G3 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 11 );             /* G4 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 0 );              /* G5 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 1 );              /* G6 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 2 );              /* G7 */

   /* Configuration de la résistance de tirage des broches [B0:B7] de */
   /* l'écran. */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_OFF, 4 );              /* B0 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 13 );             /* B1 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 14 );             /* B2 */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 15 );             /* B3 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_OFF, 12 );             /* B4 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 4 );              /* B5 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 5 );              /* B6 */
   gpio_resistor ( K_GPIOK, K_GPIO_PULL_OFF, 6 );              /* B7 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_initGPIO ( void )
{
   /* Note : */
   /* Les deux bits de poids faibles R<1:0>, G<1:0> et B<1:0> de */
   /* chaque composante RGB ne sont pas reliées à l'écran. Il */
   /* resulte un total de 262k couleur possible. */

   /* Configuration des broches de l'interface LTDC */
   mk_display_setGPIOMode ( );
   mk_display_setGPIOAlternateMode ( );
   mk_display_setGPIOSpeed ( );
   mk_display_setGPIOResistor ( );

   /* Activation du rétro-éclairage et de l'écran */
   gpio_setHigh ( K_GPIOI, 12 );
   gpio_setHigh ( K_GPIOK, 3 );

   /* Retour */
   return;
}


