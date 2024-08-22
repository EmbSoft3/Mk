/**
*
* @copyright Copyright (C)  RENARD Mathieu. All rights reserved.
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
* @file mk_i2c_initGPIO.c
* @brief Définition de la fonction mk_i2c_initGPIO.
* @date 10 oct. 2020*
* @todo Broche SMBUS d'alarme non initialisée.
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_initGPIOMode ( T_mkAddr p_bus )
{
   /* Si le périphérique I2C1 doit être configuré */
   if ( p_bus == K_I2C1 )
   {
      /* Configuration du mode de fonctionnement des broches GPIO */
      gpio_setMode ( K_MK_I2C1_GPIO_CLOCK_ADDR, K_GPIO_ALTERNATE, K_MK_I2C1_GPIO_CLOCK_OFFSET );  /* I2C_SCL */
      gpio_setMode ( K_MK_I2C1_GPIO_DATA_ADDR, K_GPIO_ALTERNATE, K_MK_I2C1_GPIO_DATA_OFFSET );    /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C2 doit être configuré */
   else if ( p_bus == K_I2C2 )
   {
      /* Configuration du mode de fonctionnement des broches GPIO */
      gpio_setMode ( K_MK_I2C2_GPIO_CLOCK_ADDR, K_GPIO_ALTERNATE, K_MK_I2C2_GPIO_CLOCK_OFFSET );  /* I2C_SCL */
      gpio_setMode ( K_MK_I2C2_GPIO_DATA_ADDR, K_GPIO_ALTERNATE, K_MK_I2C2_GPIO_DATA_OFFSET );    /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C3 doit être configuré */
   else if ( p_bus == K_I2C3 )
   {
      /* Configuration du mode de fonctionnement des broches GPIO */
      gpio_setMode ( K_MK_I2C3_GPIO_CLOCK_ADDR, K_GPIO_ALTERNATE, K_MK_I2C3_GPIO_CLOCK_OFFSET );  /* I2C_SCL */
      gpio_setMode ( K_MK_I2C3_GPIO_DATA_ADDR, K_GPIO_ALTERNATE, K_MK_I2C3_GPIO_DATA_OFFSET );    /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C4 doit être configuré */
   else if ( p_bus == K_I2C4 )
   {
      /* Configuration du mode de fonctionnement des broches GPIO */
      gpio_setMode ( K_MK_I2C4_GPIO_CLOCK_ADDR, K_GPIO_ALTERNATE, K_MK_I2C4_GPIO_CLOCK_OFFSET );  /* I2C_SCL */
      gpio_setMode ( K_MK_I2C4_GPIO_DATA_ADDR, K_GPIO_ALTERNATE, K_MK_I2C4_GPIO_DATA_OFFSET );    /* I2C_SDA */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_initGPIOAlternate ( T_mkAddr p_bus )
{
   /* Si le périphérique I2C1 doit être configuré */
   if ( p_bus == K_I2C1 )
   {
      /* Multiplexage des broches GPIO */
      gpio_alternate ( K_MK_I2C1_GPIO_CLOCK_ADDR, K_MK_I2C1_GPIO_CLOCK_MULTIPLEXER, K_MK_I2C1_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_alternate ( K_MK_I2C1_GPIO_DATA_ADDR, K_MK_I2C1_GPIO_DATA_MULTIPLEXER, K_MK_I2C1_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C2 doit être configuré */
   else if ( p_bus == K_I2C2 )
   {
      /* Multiplexage des broches GPIO */
      gpio_alternate ( K_MK_I2C2_GPIO_CLOCK_ADDR, K_MK_I2C2_GPIO_CLOCK_MULTIPLEXER, K_MK_I2C2_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_alternate ( K_MK_I2C2_GPIO_DATA_ADDR, K_MK_I2C2_GPIO_DATA_MULTIPLEXER, K_MK_I2C2_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C3 doit être configuré */
   else if ( p_bus == K_I2C3 )
   {
      /* Multiplexage des broches GPIO */
      gpio_alternate ( K_MK_I2C3_GPIO_CLOCK_ADDR, K_MK_I2C3_GPIO_CLOCK_MULTIPLEXER, K_MK_I2C3_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_alternate ( K_MK_I2C3_GPIO_DATA_ADDR, K_MK_I2C3_GPIO_DATA_MULTIPLEXER, K_MK_I2C3_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C4 doit être configuré */
   else if ( p_bus == K_I2C4 )
   {
      /* Multiplexage des broches GPIO */
      gpio_alternate ( K_MK_I2C4_GPIO_CLOCK_ADDR, K_MK_I2C4_GPIO_CLOCK_MULTIPLEXER, K_MK_I2C4_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_alternate ( K_MK_I2C4_GPIO_DATA_ADDR, K_MK_I2C4_GPIO_DATA_MULTIPLEXER, K_MK_I2C4_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_initGPIOSpeed ( T_mkAddr p_bus )
{
   /* Si le périphérique I2C1 doit être configuré */
   if ( p_bus == K_I2C1 )
   {
      /* Configuration de la vitesse des broches GPIO */
      gpio_speed ( K_MK_I2C1_GPIO_CLOCK_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C1_GPIO_CLOCK_OFFSET );    /* I2C_SCL */
      gpio_speed ( K_MK_I2C1_GPIO_DATA_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C1_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C2 doit être configuré */
   else if ( p_bus == K_I2C2 )
   {
      /* Configuration de la vitesse des broches GPIO */
      gpio_speed ( K_MK_I2C2_GPIO_CLOCK_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C2_GPIO_CLOCK_OFFSET );    /* I2C_SCL */
      gpio_speed ( K_MK_I2C2_GPIO_DATA_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C2_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C3 doit être configuré */
   else if ( p_bus == K_I2C3 )
   {
      /* Configuration de la vitesse des broches GPIO */
      gpio_speed ( K_MK_I2C3_GPIO_CLOCK_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C3_GPIO_CLOCK_OFFSET );    /* I2C_SCL */
      gpio_speed ( K_MK_I2C3_GPIO_DATA_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C3_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C4 doit être configuré */
   else if ( p_bus == K_I2C4 )
   {
      /* Configuration de la vitesse des broches GPIO */
      gpio_speed ( K_MK_I2C4_GPIO_CLOCK_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C4_GPIO_CLOCK_OFFSET );    /* I2C_SCL */
      gpio_speed ( K_MK_I2C4_GPIO_DATA_ADDR, K_GPIO_HIGH_SPEED, K_MK_I2C4_GPIO_DATA_OFFSET );      /* I2C_SDA */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_initGPIOResistor ( T_mkAddr p_bus )
{
   /* Si le périphérique I2C1 doit être configuré */
   if ( p_bus == K_I2C1 )
   {
      /* Configuration des résistances de tirage des broches GPIO */
      gpio_resistor ( K_MK_I2C1_GPIO_CLOCK_ADDR, K_GPIO_PULL_OFF, K_MK_I2C1_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_resistor ( K_MK_I2C1_GPIO_DATA_ADDR, K_GPIO_PULL_OFF, K_MK_I2C1_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C2 doit être configuré */
   else if ( p_bus == K_I2C2 )
   {
      /* Configuration des résistances de tirage des broches GPIO */
      gpio_resistor ( K_MK_I2C2_GPIO_CLOCK_ADDR, K_GPIO_PULL_OFF, K_MK_I2C2_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_resistor ( K_MK_I2C2_GPIO_DATA_ADDR, K_GPIO_PULL_OFF, K_MK_I2C2_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C3 doit être configuré */
   else if ( p_bus == K_I2C3 )
   {
      /* Configuration des résistances de tirage des broches GPIO */
      gpio_resistor ( K_MK_I2C3_GPIO_CLOCK_ADDR, K_GPIO_PULL_OFF, K_MK_I2C3_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_resistor ( K_MK_I2C3_GPIO_DATA_ADDR, K_GPIO_PULL_OFF, K_MK_I2C3_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C4 doit être configuré */
   else if ( p_bus == K_I2C4 )
   {
      /* Configuration des résistances de tirage des broches GPIO */
      gpio_resistor ( K_MK_I2C4_GPIO_CLOCK_ADDR, K_GPIO_PULL_OFF, K_MK_I2C4_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_resistor ( K_MK_I2C4_GPIO_DATA_ADDR, K_GPIO_PULL_OFF, K_MK_I2C4_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_initGPIOType ( T_mkAddr p_bus )
{
   /* Si le périphérique I2C1 doit être configuré */
   if ( p_bus == K_I2C1 )
   {
      /* Configuration de l'étage de sortie des broches GPIO */
      gpio_openDrain ( K_MK_I2C1_GPIO_CLOCK_ADDR, K_MK_I2C1_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_openDrain ( K_MK_I2C1_GPIO_DATA_ADDR, K_MK_I2C1_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C2 doit être configuré */
   else if ( p_bus == K_I2C2 )
   {
      /* Configuration de l'étage de sortie des broches GPIO */
      gpio_openDrain ( K_MK_I2C2_GPIO_CLOCK_ADDR, K_MK_I2C2_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_openDrain ( K_MK_I2C2_GPIO_DATA_ADDR, K_MK_I2C2_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C3 doit être configuré */
   else if ( p_bus == K_I2C3 )
   {
      /* Configuration de l'étage de sortie des broches GPIO */
      gpio_openDrain ( K_MK_I2C3_GPIO_CLOCK_ADDR, K_MK_I2C3_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_openDrain ( K_MK_I2C3_GPIO_DATA_ADDR, K_MK_I2C3_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon si le périphérique I2C4 doit être configuré */
   else if ( p_bus == K_I2C4 )
   {
      /* Configuration de l'étage de sortie des broches GPIO */
      gpio_openDrain ( K_MK_I2C4_GPIO_CLOCK_ADDR, K_MK_I2C4_GPIO_CLOCK_OFFSET );   /* I2C_SCL */
      gpio_openDrain ( K_MK_I2C4_GPIO_DATA_ADDR, K_MK_I2C4_GPIO_DATA_OFFSET );     /* I2C_SDA */
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_i2c_initGPIO ( T_mkAddr p_bus )
{
   /* Configuration du mode de fonctionnement des broches GPIO */
   mk_i2c_initGPIOMode ( p_bus );

   /* Multiplexage des broches GPIO */
   mk_i2c_initGPIOAlternate ( p_bus );

   /* Configuration de la vitesse des broches GPIO */
   mk_i2c_initGPIOSpeed ( p_bus );

   /* Configuration des résistances de tirage des broches GPIO */
   mk_i2c_initGPIOResistor ( p_bus );

   /* Configuration de l'étage de sortie des broches GPIO */
   mk_i2c_initGPIOType ( p_bus );

   /* Retour */
   return;
}

