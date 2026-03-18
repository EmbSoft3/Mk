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
* @file mk_gpio_bsp_data.c
* @brief Définition des types dédiés au BSP du module GPIO.
* @date 17 mars 2026
*
*/

#include "mk_gpio_api.h"

/**
 *
 */

/* Constantes dédiées à la carte STM32F746G-Eval2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @fn uint32_t g_mkGPIOPinTable [ K_MK_GPIO_NUMBER_OF_PINS ];
 * @brief Déclaration de la table de correspondance des broches génériques pour la carte EVAL_2.
 *
 */

T_mkGPIOPinHandler g_mkGPIOPinTable [ K_MK_GPIO_NUMBER_OF_PINS ] = {

   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_JOYSTICK_SEL,         K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_RELEASE,    K_MK_EVENT_PRESS,   K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_JOYSTICK_DOWN,        K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_RELEASE,    K_MK_EVENT_PRESS,   K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_JOYSTICK_DOWN */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_JOYSTICK_LEFT,        K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_RELEASE,    K_MK_EVENT_PRESS,   K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_JOYSTICK_LEFT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_JOYSTICK_RIGHT,       K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_RELEASE,    K_MK_EVENT_PRESS,   K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_JOYSTICK_RIGHT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_JOYSTICK_UP,          K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_RELEASE,    K_MK_EVENT_PRESS,   K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_JOYSTICK_UP */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_AUDIO_INTERRUPT,      K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_AUDIO_INTERRUPT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_OTGFS1_OVERCURRENT,   K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_OTGFS1_OVERCURRENT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_OTGFS1_POWERSWITCHON, K_MK_GPIO_OUTPUT, 0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_OTGFS1_POWERSWITCHON */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_OTGFS2_OVERCURRENT,   K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_OTGHS_OVERCURRENT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_OTGFS2_POWERSWITCHON, K_MK_GPIO_OUTPUT, 0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_OTGHS_POWERSWITCHON */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_CAMERA_XSDN,          K_MK_GPIO_OUTPUT, 0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_CAMERA_XSDN */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_CAMERA_RSTI,          K_MK_GPIO_OUTPUT, 0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_CAMERA_RSTI */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_CAMERA_PLUG,          K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_CAMERA_PLUG */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_MII_INTERRUPT,        K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_MII_INTERRUPT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_LCD_INTERRUPT,        K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_LCD_INTERRUPT */
   { K_MK_GPIO_EXTERNAL, K_MK_EXPANDER_MFXV3_SDCARD_DETECT,        K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_DISCONNECT, K_MK_EVENT_CONNECT, K_MK_GPIO_PROTECTED,   { mk_gpio_expander_mfxv3_get, mk_gpio_expander_mfxv3_direction, mk_gpio_expander_mfxv3_type, mk_gpio_expander_mfxv3_resistor, mk_gpio_expander_mfxv3_set, mk_gpio_expander_mfxv3_clear } },   /* K_MK_GPIO_PIN_SDCARD_DETECT */
   { K_MK_GPIO_PORTF,    10,                                       K_MK_GPIO_OUTPUT, 1, 1, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },   /* K_MK_GPIO_PIN_LED1 */
   { K_MK_GPIO_PORTB,    7,                                        K_MK_GPIO_OUTPUT, 1, 1, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_UNPROTECTED, { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },   /* K_MK_GPIO_PIN_LED2 */
   
};

/* On inclut les constantes dédiées à la carte STM32F746G-DISCO REV.C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @fn uint32_t g_mkGPIOPinTable [ K_MK_GPIO_NUMBER_OF_PINS ];
 * @brief Déclaration de la table de correspondance des broches génériques pour la carte DISCO_REV_C.
 *
 */

T_mkGPIOPinHandler g_mkGPIOPinTable [ K_MK_GPIO_NUMBER_OF_PINS ] = {

   { K_MK_GPIO_PORTD, 6,  K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_AUDIO_INTERRUPT */
   { K_MK_GPIO_PORTD, 4,  K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_OTGFS1_OVERCURRENT */
   { K_MK_GPIO_PORTD, 5,  K_MK_GPIO_OUTPUT, 0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_OTGFS1_POWERSWITCHON */
   { K_MK_GPIO_PORTE, 3,  K_MK_GPIO_INPUT,  0, 0, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_OTGHS_OVERCURRENT */
   { K_MK_GPIO_PORTC, 13, K_MK_GPIO_INPUT,  1, 1, 0, K_MK_EVENT_DISCONNECT, K_MK_EVENT_CONNECT, K_MK_GPIO_PROTECTED,   { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_SDCARD_DETECT */
   { K_MK_GPIO_PORTI, 1,  K_MK_GPIO_OUTPUT, 1, 1, 0, K_MK_EVENT_NO,         K_MK_EVENT_NO,      K_MK_GPIO_UNPROTECTED, { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_LED1 */
   { K_MK_GPIO_PORTI, 11, K_MK_GPIO_INPUT,  0, 0, 0, K_MK_GPIO_UNPROTECTED, K_MK_EVENT_RELEASE, K_MK_EVENT_PRESS,      { K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL, K_MK_NULL } },    /* K_MK_GPIO_PIN_PUSHBUTTON1 */
};

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif

