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
* @file mk_fmc_bsp_init.c
* @brief Définition de la fonction mk_fmc_bsp_init.
* @date 23 mars 2026
*
*/

#include "mk_fmc_api.h"

/* Si carte EVAL2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fmc_bsp_initGPIO ( void )
{
   /* Configuration du mode des broches de pilotage du contrôleur */
   /* SDRAM. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas */
   /* utilisées (en réserve pour une autre mémoire) */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 8 );           /* SDCLK */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 5 );           /* SDNWE */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 2 );           /* SDCKE<0> */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 3 );           /* SDNE<0> */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 11 );          /* SDNRAS */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 15 );          /* SDNCAS */

   /* Configuration du mode des broches de pilotage du contrôleur */
   /* SRAM. */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 7 );           /* NE1 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 10 );          /* NE3 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 4 );           /* NOE */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 5 );           /* NWE */

   /* Configuration du mode des broches partagées du périphérique */
   /* FMC. */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 5 );           /* NBL<3> */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 4 );           /* NBL<2> */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 1 );           /* NBL<1> */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 0 );           /* NBL<0> */

   /* Configuration du mode des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 14 );          /* D0 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 15 );          /* D1 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 0 );           /* D2 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 1 );           /* D3 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 7 );           /* D4 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 8 );           /* D5 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 9 );           /* D6 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 10 );          /* D7 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 11 );          /* D8 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 12 );          /* D9 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 13 );          /* D10 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 14 );          /* D11 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 15 );          /* D12 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 8 );           /* D13 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 9 );           /* D14 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 10 );          /* D15 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 8 );           /* D16 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 9 );           /* D17 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 10 );          /* D18 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 11 );          /* D19 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 12 );          /* D20 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 13 );          /* D21 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 14 );          /* D22 */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 15 );          /* D23 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 0 );           /* D24 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 1 );           /* D25 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 2 );           /* D26 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 3 );           /* D27 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 6 );           /* D28 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 7 );           /* D29 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 9 );           /* D30 */
   gpio_setMode ( K_GPIOI, K_GPIO_ALTERNATE, 10 );          /* D31 */

   /* Configuration du mode des broches d'adresse [A23:A0] du périphérique FMC */
   /* La broche A24 <PG13> n'est pas cablées sur les mémoires externes */
   /* */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 0 );           /* A0 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 1 );           /* A1 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 2 );           /* A2 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 3 );           /* A3 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 4 );           /* A4 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 5 );           /* A5 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 12 );          /* A6 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 13 );          /* A7 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 14 );          /* A8 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 15 );          /* A9 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 0 );           /* A10 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 1 );           /* A11 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 2 );           /* ->A12 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 3 );           /* ->A13 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 4 );           /* A14 - BA0 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 5 );           /* A15 - BA1 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 11 );          /* A16 - CLE */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 12 );          /* A17 - ALE */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 13 );          /* A18 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 3 );           /* A19 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 4 );           /* A20 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 5 );           /* A21 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 6 );           /* A22 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 2 );           /* A23 */

   /* Multiplexage des broches de pilotage du contrôleur SDRAM. */
   /* Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas */
   /* utilisées (en réserve pour une autre mémoire). */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 8 );              /* SDCLK */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 5 );              /* SDNWE */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 2 );              /* SDCKE<0> */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 3 );              /* SDNE<0> */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 11 );             /* SDNRAS */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 15 );             /* SDNCAS */

   /* Multiplexage du mode des broches de pilotage du contrôleur */
   /* SRAM. */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 7 );              /* NE1 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 10 );             /* NE3 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 4 );              /* NOE */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 5 );              /* NWE */

   /* Multiplexage des broches partagées du périphérique FMC. */
   /**/
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 5 );              /* NBL<3> */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 4 );              /* NBL<2> */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 1 );              /* NBL<1> */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 0 );              /* NBL<0> */

   /* Multiplexage des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 14 );             /* D0 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 15 );             /* D1 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 0 );              /* D2 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 1 );              /* D3 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 7 );              /* D4 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 8 );              /* D5 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 9 );              /* D6 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 10 );             /* D7 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 11 );             /* D8 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 12 );             /* D9 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 13 );             /* D10 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 14 );             /* D11 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 15 );             /* D12 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 8 );              /* D13 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 9 );              /* D14 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 10 );             /* D15 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 8 );              /* D16 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 9 );              /* D17 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 10 );             /* D18 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 11 );             /* D19 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 12 );             /* D20 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 13 );             /* D21 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 14 );             /* D22 */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 15 );             /* D23 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 0 );              /* D24 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 1 );              /* D25 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 2 );              /* D26 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 3 );              /* D27 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 6 );              /* D28 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 7 );              /* D29 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 9 );              /* D30 */
   gpio_alternate ( K_GPIOI, K_GPIO_AF12, 10 );             /* D31 */

   /* Multiplexage des broches d'adresse [A23:A0] du périphérique FMC */
   /* La broche A24 <PG13> n'est pas cablées sur les mémoires externes */
   /* */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 0 );              /* A0 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 1 );              /* A1 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 2 );              /* A2 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 3 );              /* A3 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 4 );              /* A4 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 5 );              /* A5 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 12 );             /* A6 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 13 );             /* A7 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 14 );             /* A8 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 15 );             /* A9 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 0 );              /* A10 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 1 );              /* A11 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 2 );              /* A12 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 3 );              /* A13 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 4 );              /* A14 - BA0 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 5 );              /* A15 - BA1 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 11 );             /* A16 - CLE */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 12 );             /* A17 - ALE*/
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 13 );             /* A18 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 3 );              /* A19 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 4 );              /* A20 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 5 );              /* A21 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 6 );              /* A22 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 2 );              /* A23 */

   /* Configuration de la vitesse des broches de pilotage du contrôleur */
   /* SDRAM. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas  */
   /* utilisées (en réserve pour une autre mémoire). */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 8 );       /* SDCLK */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 5 );       /* SDNWE */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 2 );       /* SDCKE<0> */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 3 );       /* SDNE<0> */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 11 );      /* SDNRAS */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 15 );      /* SDNCAS */

   /* Configuration de la vitesse des broches partagées du contrôleur */
   /* SDRAM. */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 7 );       /* NE1 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 10 );      /* NE3 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 4 );       /* NOE */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 5 );       /* NWE */

   /* Configuration de la vitesse des broches partagées du périphérique */
   /* FMC. */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 5 );       /* NBL<3> */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 4 );       /* NBL<2> */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 1 );       /* NBL<1> */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 0 );       /* NBL<0> */

   /* Configuration de la vitesse des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 14 );      /* D0 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 15 );      /* D1 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 0 );       /* D2 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 1 );       /* D3 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 7 );       /* D4 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 8 );       /* D5 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D6 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D7 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 11 );      /* D8 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 12 );      /* D9 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 13 );      /* D10 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 14 );      /* D11 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 15 );      /* D12 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 8 );       /* D13 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D14 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D15 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 8 );       /* D16 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D17 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D18 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 11 );      /* D19 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 12 );      /* D20 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 13 );      /* D21 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 14 );      /* D22 */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 15 );      /* D23 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 0 );       /* D24 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 1 );       /* D25 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 2 );       /* D26 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 3 );       /* D27 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 6 );       /* D28 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 7 );       /* D29 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D30 */
   gpio_speed ( K_GPIOI, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D31 */

   /* Configuration de la vitesse des broches d'adresse [A23:A0] */
   /* du périphérique FMC. La broche A24 <PG13> n'est pas cablées aux mémoires */
   /* externes */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 0 );       /* A0 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 1 );       /* A1 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 2 );       /* A2 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 3 );       /* A3 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 4 );       /* A4 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 5 );       /* A5 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 12 );      /* A6 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 13 );      /* A7 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 14 );      /* A8 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 15 );      /* A9 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 0 );       /* A10 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 1 );       /* A11 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 2 );       /* A12 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 3 );       /* A13 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 4 );       /* A14 - BA0 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 5 );       /* A15 - BA1 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 11 );      /* A16 - CLE */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 12 );      /* A17 - ALE*/
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 13 );      /* A18 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 3 );       /* A19 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 4 );       /* A20 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 5 );       /* A21 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 6 );       /* A22 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 2 );       /* A23 */

   /* Configuration de la résistance de sortie des broches de pilotage */
   /* du périphérique FMC. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 */
   /* ne sont pas utilisées (en réserve pour une autre mémoire). */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 8 );            /* SDCLK */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 5 );            /* SDNWE */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 2 );            /* SDCKE<0> */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 3 );            /* SDNE<0> */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 11 );           /* SDNRAS */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 15 );           /* SDNCAS */

   /* Configuration de la vitesse des broches partagées du contrôleur */
   /* SDRAM. */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 7 );            /* NE1 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 10 );           /* NE3 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 4 );            /* NOE */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 5 );            /* NWE */

   /* Configuration de la résistances de sortie des broches partagées */
   /* du périphérique FMC. */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 5 );            /* NBL<3> */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 4 );            /* NBL<2> */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 1 );            /* NBL<1> */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 0 );            /* NBL<0> */

   /* Configuration de la résistance de sortie des broches de données */
   /* [D31:D0] du périphérique FMC */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 14 );           /* D0 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 15 );           /* D1 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 0 );            /* D2 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 1 );            /* D3 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 7 );            /* D4 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 8 );            /* D5 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 9 );            /* D6 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 10 );           /* D7 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 11 );           /* D8 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 12 );           /* D9 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 13 );           /* D10 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 14 );           /* D11 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 15 );           /* D12 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 8 );            /* D13 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 9 );            /* D14 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 10 );           /* D15 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 8 );            /* D16 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 9 );            /* D17 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 10 );           /* D18 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 11 );           /* D19 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 12 );           /* D20 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 13 );           /* D21 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 14 );           /* D22 */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 15 );           /* D23 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 0 );            /* D24 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 1 );            /* D25 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 2 );            /* D26 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 3 );            /* D27 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 6 );            /* D28 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 7 );            /* D29 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 9 );            /* D30 */
   gpio_resistor ( K_GPIOI, K_GPIO_PULL_UP, 10 );           /* D31 */

   /* Configuration de la résistance de sortie des broches d'adresse */
   /* [A23:A0] du périphérique FMC. La broche A24 <PG13> n'est pas cablées */
   /* aux mémoires externes */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 0 );            /* A0 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 1 );            /* A1 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 2 );            /* A2 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 3 );            /* A3 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 4 );            /* A4 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 5 );            /* A5 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 12 );           /* A6 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 13 );           /* A7 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 14 );           /* A8 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 15 );           /* A9 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 0 );            /* A10 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 1 );            /* A11 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 2 );            /* A12 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 3 );            /* A13 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 4 );            /* A14 - BA0 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 5 );            /* A15 - BA1 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 11 );           /* A16 - CLE */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 12 );           /* A17 - ALE*/
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 13 );           /* A18 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 3 );            /* A19 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 4 );            /* A20 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 5 );            /* A21 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 6 );            /* A22 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 2 );            /* A23 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fmc_bsp_init ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;
   
   /* Initialisation des broches GPIO du FMC */
   mk_fmc_bsp_initGPIO ( );

   /* Initialisation de la mémoire IS61WV102416BLL */
   mk_fmc_sram_is61wv102416bll_init ( );

   /* Initialisation de la mémoire IS42S32800G */
   l_result = mk_fmc_sdram_is42s32800g_init ( );

   /* Retour */
   return ( l_result );
}

/* Si carte DISCO_REV_C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fmc_bsp_initGPIO ( void )
{
   /* Configuration du mode des broches de pilotage du contrôleur */
   /* SDRAM. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas */
   /* utilisées (en réserve pour une autre mémoire) */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 8 );           /* SDCLK */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 5 );           /* SDNWE */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 3 );           /* SDCKE<0> */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 3 );           /* SDNE<0> */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 11 );          /* SDNRAS */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 15 );          /* SDNCAS */

   /* Configuration du mode des broches partagées du périphérique */
   /* FMC. */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 1 );           /* NBL<1> */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 0 );           /* NBL<0> */

   /* Configuration du mode des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 14 );          /* D0 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 15 );          /* D1 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 0 );           /* D2 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 1 );           /* D3 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 7 );           /* D4 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 8 );           /* D5 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 9 );           /* D6 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 10 );          /* D7 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 11 );          /* D8 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 12 );          /* D9 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 13 );          /* D10 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 14 );          /* D11 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 15 );          /* D12 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 8 );           /* D13 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 9 );           /* D14 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 10 );          /* D15 */

   /* Configuration du mode des broches d'adresse [A23:A0] du périphérique FMC */
   /* La broche A24 <PG13> n'est pas cablées sur les mémoires externes */
   /* */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 0 );           /* A0 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 1 );           /* A1 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 2 );           /* A2 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 3 );           /* A3 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 4 );           /* A4 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 5 );           /* A5 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 12 );          /* A6 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 13 );          /* A7 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 14 );          /* A8 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 15 );          /* A9 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 0 );           /* A10 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 1 );           /* A11 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 4 );           /* A14 - BA0 */
   gpio_setMode ( K_GPIOG, K_GPIO_ALTERNATE, 5 );           /* A15 - BA1 */

   /* Multiplexage des broches de pilotage du contrôleur SDRAM. */
   /* Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas */
   /* utilisées (en réserve pour une autre mémoire). */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 8 );              /* SDCLK */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 5 );              /* SDNWE */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 3 );              /* SDCKE<0> */
   gpio_alternate ( K_GPIOH, K_GPIO_AF12, 3 );              /* SDNE<0> */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 11 );             /* SDNRAS */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 15 );             /* SDNCAS */

   /* Multiplexage des broches partagées du périphérique FMC. */
   /**/
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 1 );              /* NBL<1> */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 0 );              /* NBL<0> */

   /* Multiplexage des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 14 );             /* D0 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 15 );             /* D1 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 0 );              /* D2 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 1 );              /* D3 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 7 );              /* D4 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 8 );              /* D5 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 9 );              /* D6 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 10 );             /* D7 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 11 );             /* D8 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 12 );             /* D9 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 13 );             /* D10 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 14 );             /* D11 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF12, 15 );             /* D12 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 8 );              /* D13 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 9 );              /* D14 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 10 );             /* D15 */

   /* Multiplexage des broches d'adresse [A23:A0] du périphérique FMC */
   /* La broche A24 <PG13> n'est pas cablées sur les mémoires externes */
   /* */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 0 );              /* A0 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 1 );              /* A1 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 2 );              /* A2 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 3 );              /* A3 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 4 );              /* A4 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 5 );              /* A5 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 12 );             /* A6 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 13 );             /* A7 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 14 );             /* A8 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF12, 15 );             /* A9 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 0 );              /* A10 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 1 );              /* A11 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 4 );              /* A14 - BA0 */
   gpio_alternate ( K_GPIOG, K_GPIO_AF12, 5 );              /* A15 - BA1 */

   /* Configuration de la vitesse des broches de pilotage du contrôleur */
   /* SDRAM. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 ne sont pas  */
   /* utilisées (en réserve pour une autre mémoire). */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 8 );       /* SDCLK */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 5 );       /* SDNWE */
   gpio_speed ( K_GPIOC, K_GPIO_VERY_HIGH_SPEED, 3 );       /* SDCKE<0> */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 3 );       /* SDNE<0> */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 11 );      /* SDNRAS */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 15 );      /* SDNCAS */

   /* Configuration de la vitesse des broches partagées du périphérique */
   /* FMC. */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 1 );       /* NBL<1> */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 0 );       /* NBL<0> */

   /* Configuration de la vitesse des broches de données [D31:D0] du périphérique FMC */
   /* */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 14 );      /* D0 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 15 );      /* D1 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 0 );       /* D2 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 1 );       /* D3 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 7 );       /* D4 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 8 );       /* D5 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D6 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D7 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 11 );      /* D8 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 12 );      /* D9 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 13 );      /* D10 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 14 );      /* D11 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 15 );      /* D12 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 8 );       /* D13 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 9 );       /* D14 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 10 );      /* D15 */

   /* Configuration de la vitesse des broches d'adresse [A23:A0] */
   /* du périphérique FMC. La broche A24 <PG13> n'est pas cablées aux mémoires */
   /* externes */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 0 );       /* A0 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 1 );       /* A1 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 2 );       /* A2 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 3 );       /* A3 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 4 );       /* A4 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 5 );       /* A5 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 12 );      /* A6 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 13 );      /* A7 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 14 );      /* A8 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 15 );      /* A9 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 0 );       /* A10 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 1 );       /* A11 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 4 );       /* A14 - BA0 */
   gpio_speed ( K_GPIOG, K_GPIO_VERY_HIGH_SPEED, 5 );       /* A15 - BA1 */

   /* Configuration de la résistance de sortie des broches de pilotage */
   /* du périphérique FMC. Les broches SDCKE<1> - PH7 et SDNE<1> - PH6 */
   /* ne sont pas utilisées (en réserve pour une autre mémoire). */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 8 );            /* SDCLK */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 5 );            /* SDNWE */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_UP, 3 );            /* SDCKE<0> */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_UP, 3 );            /* SDNE<0> */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 11 );           /* SDNRAS */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 15 );           /* SDNCAS */

   /* Configuration de la résistances de sortie des broches partagées */
   /* du périphérique FMC. */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 1 );            /* NBL<1> */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 0 );            /* NBL<0> */

   /* Configuration de la résistance de sortie des broches de données */
   /* [D31:D0] du périphérique FMC */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 14 );           /* D0 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 15 );           /* D1 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 0 );            /* D2 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 1 );            /* D3 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 7 );            /* D4 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 8 );            /* D5 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 9 );            /* D6 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 10 );           /* D7 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 11 );           /* D8 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 12 );           /* D9 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 13 );           /* D10 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 14 );           /* D11 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 15 );           /* D12 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 8 );            /* D13 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 9 );            /* D14 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 10 );           /* D15 */

   /* Configuration de la résistance de sortie des broches d'adresse */
   /* [A23:A0] du périphérique FMC. La broche A24 <PG13> n'est pas cablées */
   /* aux mémoires externes */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 0 );            /* A0 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 1 );            /* A1 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 2 );            /* A2 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 3 );            /* A3 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 4 );            /* A4 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 5 );            /* A5 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 12 );           /* A6 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 13 );           /* A7 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 14 );           /* A8 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 15 );           /* A9 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 0 );            /* A10 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 1 );            /* A11 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 4 );            /* A14 - BA0 */
   gpio_resistor ( K_GPIOG, K_GPIO_PULL_UP, 5 );            /* A15 - BA1 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fmc_bsp_init ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;
   
   /* Initialisation des broches GPIO du FMC */
   mk_fmc_bsp_initGPIO ( );
   
   /* Initialisation de la mémoire IS42S32400F */
   l_result = mk_fmc_sdram_is42s32400f_init ( );

   /* Retour */
   return ( l_result ) ;
}

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif
