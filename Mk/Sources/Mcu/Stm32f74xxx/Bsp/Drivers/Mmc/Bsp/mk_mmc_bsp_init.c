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
* @file mk_mmc_initGPIO.c
* @brief Définition de la fonction mk_mmc_initGPIO.
* @date 1 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_bsp_initCardDetect ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure de configuration */
   T_mkGPIOSetting l_setting = {
      K_MK_GPIO_INPUT, K_MK_GPIO_ENABLE_PULL, K_MK_GPIO_PULLUP
   };

   /* Configuration de la broche CARD_DETECT */
   l_result = mk_gpio_setup ( K_MK_GPIO_SYSID, K_MK_GPIO_PIN_SDCARD_DETECT, &l_setting, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/* Si carte EVAL2 ou DISCO_REV_C */
#if ( defined ( MK_BOARD_EVAL2 ) || defined ( MK_BOARD_DISCO_REV_C ) )

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_bsp_init ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;
   
   /* Configuration du mode de fonctionnement des broches GPIO */
   gpio_setMode ( K_GPIOD, K_GPIO_ALTERNATE, 2 );           /* MMC_CMD */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 12 );          /* MMC_CLK */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 8 );           /* MMC_D0 */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 9 );           /* MMC_D1 */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 10 );          /* MMC_D2 */
   gpio_setMode ( K_GPIOC, K_GPIO_ALTERNATE, 11 );          /* MMC_D3 */
   
   /* Multiplexage des broches GPIO */
   gpio_alternate ( K_GPIOD, K_GPIO_AF12, 2 );              /* MMC_CMD */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 12 );             /* MMC_CLK */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 8 );              /* MMC_D0 */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 9 );              /* MMC_D1 */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 10 );             /* MMC_D2 */
   gpio_alternate ( K_GPIOC, K_GPIO_AF12, 11 );             /* MMC_D3 */
   
   /* Configuration de la vitesse des broches GPIO */
   /* La configuration des broches en vitesse 'MEDIUM' semble être un bon compromis */
   /* pour faire fonctionner tous les modèles de cartes disponibles lors du codage du driver */
   gpio_speed ( K_GPIOD, K_GPIO_MEDIUM_SPEED, 2 );          /* MMC_CMD */
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 12 );         /* MMC_CLK */
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 8 );          /* MMC_D0 */
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 9 );          /* MMC_D1 */
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 10 );         /* MMC_D2 */
   gpio_speed ( K_GPIOC, K_GPIO_MEDIUM_SPEED, 11 );         /* MMC_D3 */

   /* Configuration des résistances de tirage des broches GPIO */
   gpio_resistor ( K_GPIOD, K_GPIO_PULL_OFF, 2 );           /* MMC_CMD */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 12 );          /* MMC_CLK */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 8 );           /* MMC_D0 */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 9 );           /* MMC_D1 */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 10 );          /* MMC_D2 */
   gpio_resistor ( K_GPIOC, K_GPIO_PULL_OFF, 11 );          /* MMC_D3 */

   /* Configuration du type de sortie des broches du périphérique MMC */
   gpio_pushPull ( K_GPIOD, 2 );                            /* MMC_CMD */
   gpio_pushPull ( K_GPIOC, 12 );                           /* MMC_CLK */
   gpio_pushPull ( K_GPIOC, 8 );                            /* MMC_D0 */
   gpio_pushPull ( K_GPIOC, 9 );                            /* MMC_D1 */
   gpio_pushPull ( K_GPIOC, 10 );                           /* MMC_D2 */
   gpio_pushPull ( K_GPIOC, 11 );                           /* MMC_D3 */

   /* Initialisation de la broche CARD-DETECT */
   l_result = mk_mmc_bsp_initCardDetect ( );

   /* Retour */
   return ( l_result ) ;
}

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif

