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
* @file mk_usb_initGPIO.c
* @brief Définition de la fonction mk_usb_initGPIO.
* @date 8 juin 2019
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOHSMode( void )
{
   /* Configuration du mode de fonctionnement des broches de contrôle du PHY ULPI */
   /* [NXT, DIR, CLK, STP et D0 à D7]. */
   gpio_setMode ( K_GPIOH, K_GPIO_ALTERNATE, 4 );              /* ULPI_NXT */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 2 );              /* ULPI_DIR */
   gpio_setMode ( K_GPIOA, K_GPIO_ALTERNATE, 5 );              /* ULPI_CLK */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 0 );              /* ULPI_STP */
   gpio_setMode ( K_GPIOA, K_GPIO_ALTERNATE, 3 );              /* ULPI_D0 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 0 );              /* ULPI_D1 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 1 );              /* ULPI_D2 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 10 );             /* ULPI_D3 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 11 );             /* ULPI_D4 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 12 );             /* ULPI_D5 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 13 );             /* ULPI_D6 */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 5 );              /* ULPI_D7 */

   /* Configuration du mode de fonctionnement de la broche HS_Overcurrent */
   /* [USB_HS_Overcurrent] */
   gpio_setMode ( K_GPIOE, K_GPIO_INPUT, 3 );                  /* USB_HS_Overcurrent */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOHSModeAlternate( void )
{
   /* Multiplexage des broches de contrôle du PHY ULPI */
   /* [NXT, DIR, CLK, STP et D0 à D7]. */
   gpio_alternate ( K_GPIOH, K_GPIO_AF10, 4 );                 /* ULPI_NXT */
   gpio_alternate ( K_GPIOC, K_GPIO_AF10, 2 );                 /* ULPI_DIR */
   gpio_alternate ( K_GPIOA, K_GPIO_AF10, 5 );                 /* ULPI_CLK */
   gpio_alternate ( K_GPIOC, K_GPIO_AF10, 0 );                 /* ULPI_STP */
   gpio_alternate ( K_GPIOA, K_GPIO_AF10, 3 );                 /* ULPI_D0 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 0 );                 /* ULPI_D1 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 1 );                 /* ULPI_D2 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 10 );                /* ULPI_D3 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 11 );                /* ULPI_D4 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 12 );                /* ULPI_D5 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 13 );                /* ULPI_D6 */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 5 );                 /* ULPI_D7 */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOHSSpeed( void )
{
   /* Configuration de la vitesse des broches de contrôle du PHY ULPI */
   /* [NXT, DIR, CLK, STP et D0 à D7]. */
   gpio_speed ( K_GPIOH, K_GPIO_VERY_HIGH_SPEED, 4 );          /* ULPI_NXT */
   gpio_speed ( K_GPIOC, K_GPIO_VERY_HIGH_SPEED, 2 );          /* ULPI_DIR */
   gpio_speed ( K_GPIOA, K_GPIO_VERY_HIGH_SPEED, 5 );          /* ULPI_CLK */
   gpio_speed ( K_GPIOC, K_GPIO_VERY_HIGH_SPEED, 0 );          /* ULPI_STP */
   gpio_speed ( K_GPIOA, K_GPIO_VERY_HIGH_SPEED, 3 );          /* ULPI_D0 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 0 );          /* ULPI_D1 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 1 );          /* ULPI_D2 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 10 );         /* ULPI_D3 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 11 );         /* ULPI_D4 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 12 );         /* ULPI_D5 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 13 );         /* ULPI_D6 */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 5 );          /* ULPI_D7 */

   /* Configuration de la vitesse de la broche HS_Overcurrent */
   /* [USB_HS_Overcurrent] */
   gpio_speed ( K_GPIOE, K_GPIO_LOW_SPEED, 3 );                /* USB_HS_Overcurrent */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOHSResistor( void )
{
   /* Configuration des résistances de tirage du PHY ULPI */
   /* [NXT, DIR, CLK, STP et D0 à D7]. */
   gpio_resistor ( K_GPIOH, K_GPIO_PULL_OFF, 4 );              /* ULPI_NXT */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 2 );              /* ULPI_DIR */
   gpio_resistor ( K_GPIOA, K_GPIO_PULL_OFF, 5 );              /* ULPI_CLK */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 0 );              /* ULPI_STP */
   gpio_resistor ( K_GPIOA, K_GPIO_PULL_OFF, 3 );              /* ULPI_D0 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 0 );              /* ULPI_D1 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 1 );              /* ULPI_D2 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 10 );             /* ULPI_D3 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 11 );             /* ULPI_D4 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 12 );             /* ULPI_D5 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 13 );             /* ULPI_D6 */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_OFF, 5 );              /* ULPI_D7 */

   /* Configuration des résistances de tirage de la broche HS_Overcurrent */
   /* [USB_HS_Overcurrent] */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_OFF, 3 );             /* USB_HS_Overcurrent */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOFSMode ( void )
{
   /* Configuration du mode de fonctionnement des broches USB_OTGFS */
   /* [POWER, OVERCURRENT, VBUS, DM, DP et ID]. */
   gpio_setMode ( K_GPIOD, K_GPIO_OUTPUT, 5 );                 /* POWER */
   gpio_setMode ( K_GPIOD, K_GPIO_INPUT, 4 );                  /* OVERCURRENT */
   gpio_setMode ( K_GPIOJ, K_GPIO_INPUT, 12 );                 /* VBUS */
   gpio_setMode ( K_GPIOA, K_GPIO_ALTERNATE, 11 );             /* DM */
   gpio_setMode ( K_GPIOA, K_GPIO_ALTERNATE, 12 );             /* DP */
   gpio_setMode ( K_GPIOA, K_GPIO_ALTERNATE, 10 );             /* ID */

   /* Configuration de l'étage de sortie des broches USB_OTGFS */
   /* [POWER, OVERCURRENT, VBUS, DM, DP et ID]. */
   gpio_pushPull ( K_GPIOD, 5 );                               /* POWER */
   gpio_pushPull ( K_GPIOD, 4 );                               /* OVERCURRENT */
   gpio_pushPull ( K_GPIOJ, 12 );                              /* VBUS */
   gpio_pushPull ( K_GPIOA, 11 );                              /* DM */
   gpio_pushPull ( K_GPIOA, 12 );                              /* DP */
   gpio_pushPull ( K_GPIOA, 10 );                              /* ID */

   /* Configuration du niveau de sortie de la broche USB_POWER */
   gpio_setHigh ( K_GPIOD, 5 );                                 /* POWER */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOFSModeAlternate ( void )
{
   /* Multiplexage des broches USB_OTGFS */
   /* [DM, DP et ID]. */
   gpio_alternate ( K_GPIOA, K_GPIO_AF10, 11 );                /* DM */
   gpio_alternate ( K_GPIOA, K_GPIO_AF10, 12 );                /* DP */
   gpio_alternate ( K_GPIOA, K_GPIO_AF10, 10 );                /* ID */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOFSSpeed ( void )
{
   /* Configuration de la vitesse des broches USB_OTGFS */
   /* [POWER, OVERCURRENT, VBUS, DM, DP et ID]. */
   gpio_speed ( K_GPIOD, K_GPIO_LOW_SPEED, 5 );                /* POWER */
   gpio_speed ( K_GPIOD, K_GPIO_LOW_SPEED, 4 );                /* OVERCURRENT */
   gpio_speed ( K_GPIOJ, K_GPIO_LOW_SPEED, 12 );               /* VBUS */
   gpio_speed ( K_GPIOA, K_GPIO_HIGH_SPEED, 11 );              /* DM */
   gpio_speed ( K_GPIOA, K_GPIO_HIGH_SPEED, 12 );              /* DP */
   gpio_speed ( K_GPIOA, K_GPIO_HIGH_SPEED, 10 );              /* ID */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_usb_initGPIOFSResistor ( void )
{
   /* Configuration des résistances de tirage des broches USB_OTGFS */
   /* [POWER, OVERCURRENT, VBUS, DM, DP et ID]. */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_OFF, 5 );              /* POWER */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_OFF, 4 );              /* OVERCURRENT */
   gpio_resistor ( K_GPIOJ, K_GPIO_PULL_OFF, 12 );             /* VBUS */
   gpio_resistor ( K_GPIOA, K_GPIO_PULL_OFF, 11 );             /* DM */
   gpio_resistor ( K_GPIOA, K_GPIO_PULL_OFF, 12 );             /* DP */
   gpio_resistor ( K_GPIOA, K_GPIO_PULL_OFF, 10 );             /* ID */

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_usb_initGPIO ( T_mkAddr p_usb )
{
   /* Si le périphérique USB_OTGHS doit être initialisé */
   if ( p_usb == K_USB_OTGHS )
   {
      /* Initialisation des broches du périphérique USB_OTGHS */
      mk_usb_initGPIOHSMode ( );
      mk_usb_initGPIOHSModeAlternate ( );
      mk_usb_initGPIOHSSpeed ( );
      mk_usb_initGPIOHSResistor ( );
   }

   /* Sinon */
   else
   {
      /* Initialisation des broches du périphérique USB_OTGFS */
      mk_usb_initGPIOFSMode ( );
      mk_usb_initGPIOFSModeAlternate ( );
      mk_usb_initGPIOFSSpeed ( );
      mk_usb_initGPIOFSResistor ( );
   }

   /* Retour */
   return;
}


