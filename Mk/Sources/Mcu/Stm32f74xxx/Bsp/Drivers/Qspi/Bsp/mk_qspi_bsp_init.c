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
* @file mk_qspi_bsp_init.c
* @brief Définition de la fonction mk_qspi_bsp_init.
* @date 23 mars 2026
*
*/

#include "mk_qspi_api.h"

/* Si carte EVAL2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_bsp_init ( uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;
   
   /* Configuration du mode des broches de pilotage du périphérique QSPI<1>. */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 2 );           /* CLK */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 6 );           /* CS  */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 8 );           /* IO0 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 9 );           /* IO1 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 7 );           /* IO2 */
   gpio_setMode ( K_GPIOF, K_GPIO_ALTERNATE, 6 );           /* IO3 */

   /* Multiplexage des broches de pilotage du périphérique QSPI<1>. */
   gpio_alternate ( K_GPIOB, K_GPIO_AF9, 2 );               /* CLK */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 6 );              /* CS  */
   gpio_alternate ( K_GPIOF, K_GPIO_AF10, 8 );              /* IO0 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF10, 9 );              /* IO1 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF9, 7 );               /* IO2 */
   gpio_alternate ( K_GPIOF, K_GPIO_AF9, 6 );               /* IO3 */

   /* Configuration de la vitesse des broches de pilotage du périphérique QSPI<1> */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 2 );       /* CLK */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 6 );       /* CS  */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 8 );       /* IO0 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 9 );       /* IO1 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 7 );       /* IO2 */
   gpio_speed ( K_GPIOF, K_GPIO_VERY_HIGH_SPEED, 6 );       /* IO3 */

   /* Configuration du type de résistance des broches de pilotage du périphérique QSPI<1> */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_UP, 2 );            /* CLK */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_UP, 6 );            /* CS */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 8 );            /* IO0 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 9 );            /* IO1 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 7 );            /* IO2 */
   gpio_resistor ( K_GPIOF, K_GPIO_PULL_UP, 6 );            /* IO3 */

   /* Initialisation de la mémoire N25Q512A */
   l_result = mk_qspi_n25q512a_init ( p_mode );

   /* Retour */
   return ( l_result ) ;
}

/* Si carte DISCO_REV_C */
#elif defined ( MK_BOARD_DISCO_REV_C )

T_mkCode mk_qspi_bsp_init ( uint32_t p_mode )
{
   /* Suppression warning */
   ( void ) p_mode;
   
   /* Configuration du mode des broches de pilotage du périphérique QSPI<1>. */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 2 );           /* CLK */
   gpio_setMode ( K_GPIOB, K_GPIO_ALTERNATE, 6 );           /* CS  */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 11 );          /* IO0 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 12 );          /* IO1 */
   gpio_setMode ( K_GPIOE, K_GPIO_ALTERNATE, 2 );           /* IO2 */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 13 );          /* IO3 */

   /* Multiplexage des broches de pilotage du périphérique QSPI<1>. */
   gpio_alternate ( K_GPIOB, K_GPIO_AF9, 2 );               /* CLK */
   gpio_alternate ( K_GPIOB, K_GPIO_AF10, 6 );              /* CS  */
   gpio_alternate ( K_GPIOD, K_GPIO_AF9, 11 );              /* IO0 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF9, 12 );              /* IO1 */
   gpio_alternate ( K_GPIOE, K_GPIO_AF9, 2 );               /* IO2 */
   gpio_alternate ( K_GPIOD, K_GPIO_AF9, 13 );              /* IO3 */

   /* Configuration de la vitesse des broches de pilotage du périphérique QSPI<1> */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 2 );       /* CLK */
   gpio_speed ( K_GPIOB, K_GPIO_VERY_HIGH_SPEED, 6 );       /* CS  */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 11 );      /* IO0 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 12 );      /* IO1 */
   gpio_speed ( K_GPIOE, K_GPIO_VERY_HIGH_SPEED, 2 );       /* IO2 */
   gpio_speed ( K_GPIOD, K_GPIO_VERY_HIGH_SPEED, 13 );      /* IO3 */

   /* Configuration du type de résistance des broches de pilotage du périphérique QSPI<1> */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_UP, 2 );            /* CLK */
   gpio_resistor ( K_GPIOB, K_GPIO_PULL_UP, 6 );            /* CS */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 11 );           /* IO0 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 12 );           /* IO1 */
   gpio_resistor ( K_GPIOE, K_GPIO_PULL_UP, 2 );            /* IO2 */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_UP, 13 );           /* IO3 */

   /* Retour */
   return ( K_MK_OK );
}

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif
