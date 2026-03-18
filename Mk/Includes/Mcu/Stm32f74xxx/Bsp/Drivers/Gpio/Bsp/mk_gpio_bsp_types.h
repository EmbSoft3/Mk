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
* @file mk_gpio_bsp_types.h
* @brief Déclaration des types dédiés aux GPIO de chaque BSP.
* @date 17 mars 2026
*
*/

#ifndef MK_GPIO_BSP_TYPES_H
#define MK_GPIO_BSP_TYPES_H

/**
 *
 */

/* Types dédiées à la carte STM32F746G-Eval2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @enum T_mkGPIOPinID
 * @brief Déclaration de l'énumération T_mkGPIOPinID.
 *
 */

typedef enum T_mkGPIOPinID
{
   K_MK_GPIO_PIN_JOYSTICK_SEL = 0,                                   /*!< Définition de l'identifiant de la broche JOY_SEL. */
   K_MK_GPIO_PIN_JOYSTICK_DOWN = 1,                                  /*!< Définition de l'identifiant de la broche JOY_DOWN. */
   K_MK_GPIO_PIN_JOYSTICK_LEFT = 2,                                  /*!< Définition de l'identifiant de la broche JOY_LEFT. */
   K_MK_GPIO_PIN_JOYSTICK_RIGHT = 3,                                 /*!< Définition de l'identifiant de la broche JOY_RIGHT. */
   K_MK_GPIO_PIN_JOYSTICK_UP = 4,                                    /*!< Définition de l'identifiant de la broche JOY_UP. */
   K_MK_GPIO_PIN_AUDIO_INTERRUPT = 5,                                /*!< Définition de l'identifiant de la broche AUDIO_INT. */
   K_MK_GPIO_PIN_OTGFS1_OVERCURRENT = 6,                             /*!< Définition de l'identifiant de la broche OTGFS1_OVERCURRENT. */
   K_MK_GPIO_PIN_OTGFS1_POWERSWITCHON = 7,                           /*!< Définition de l'identifiant de la broche OTGFS1_POWERSWITCHON. */
   K_MK_GPIO_PIN_OTGFS2_OVERCURRENT = 8,                             /*!< Définition de l'identifiant de la broche OTGFS2_OVERCURRENT. */
   K_MK_GPIO_PIN_OTGFS2_POWERSWITCHON = 9,                           /*!< Définition de l'identifiant de la broche OTGFS2_POWERSWITCHON. */
   K_MK_GPIO_PIN_OTGHS_OVERCURRENT = 8,                              /*!< Définition de l'identifiant de la broche OTGHS_OVERCURRENT (alias de OTGFS2_OVERCURRENT). */
   K_MK_GPIO_PIN_OTGHS_POWERSWITCHON = 9,                            /*!< Définition de l'identifiant de la broche OTGHS_POWERSWITCHON (alias de OTGFS2_POWERSWITCHON). */
   K_MK_GPIO_PIN_CAMERA_XSDN = 10,                                   /*!< Définition de l'identifiant de la broche CAMERA_XSDN. */
   K_MK_GPIO_PIN_CAMERA_RSTI = 11,
   K_MK_GPIO_PIN_CAMERA_PLUG = 12,
   K_MK_GPIO_PIN_MII_INTERRUPT = 13,                                 /*!< Définition de l'identifiant de la broche MII_INT. */
   K_MK_GPIO_PIN_LCD_INTERRUPT = 14,                                 /*!< Définition de l'identifiant de la broche LDC_INT. */
   K_MK_GPIO_PIN_SDCARD_DETECT = 15,                                 /*!< Définition de l'identifiant de la broche SDCARD_DETECT. */
   K_MK_GPIO_PIN_LED1 = 16,                                          /*!< Définition de l'identifiant de la broche PTF10. */
   K_MK_GPIO_PIN_LED2 = 17,                                          /*!< Définition de l'identifiant de la broche LED2. */
   K_MK_GPIO_NUMBER_OF_PINS = 22                                     /*!< Définition du nombre d'identifiants. */
} T_mkGPIOPinID;

/* On inclut les types dédiés à la carte STM32F746G-DISCO REV.C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @enum T_mkGPIOPinID
 * @brief Déclaration de l'énumération T_mkGPIOPinID.
 *
 */

typedef enum T_mkGPIOPinID
{
   K_MK_GPIO_PIN_AUDIO_INTERRUPT = 0,                                /*!< Définition de l'identifiant de la broche AUDIO_INT. */
   K_MK_GPIO_PIN_OTGFS1_OVERCURRENT = 1,                             /*!< Définition de l'identifiant de la broche OTGFS1_OVERCURRENT. */
   K_MK_GPIO_PIN_OTGFS1_POWERSWITCHON = 2,                           /*!< Définition de l'identifiant de la broche OTGFS1_POWERSWITCHON. */
   K_MK_GPIO_PIN_OTGHS_OVERCURRENT = 3,                              /*!< Définition de l'identifiant de la broche OTGHS_OVERCURRENT (alias de OTGFS2_OVERCURRENT). */
   K_MK_GPIO_PIN_SDCARD_DETECT = 4,                                  /*!< Définition de l'identifiant de la broche SDCARD_DETECT. */
   K_MK_GPIO_PIN_LED1 = 5,                                           /*!< Définition de l'identifiant de la broche LED1. */
   K_MK_GPIO_PIN_PUSHBUTTON = 6,                                     /*!< Définition de l'identifiant de la broche PUSHBUTTON1. */
   K_MK_GPIO_NUMBER_OF_PINS = 7                                      /*!< Définition du nombre d'identifiants. */
} T_mkGPIOPinID;

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif


/**
 *
 */



/**
 *
 */

#endif

