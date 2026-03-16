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
* @file mk_gpio_expander_types.h
* @brief Déclaration des types dédiés au périphérique MFX.
* @date 21 déc. 2020
*
*/

#ifndef MK_GPIO_EXPANDER_TYPES_H
#define MK_GPIO_EXPANDER_TYPES_H

/**
 * @enum T_mkGPIOExpanderPin
 * @brief Déclaration de l'énumération T_mkGPIOExpanderPin.
 *
 */

typedef enum T_mkGPIOExpanderPin
{
   K_MK_EXPANDER_JOYSTICK_SEL = 0,                    /*!< Définition du numéro de la broche JOY_SEL. */
   K_MK_EXPANDER_JOYSTICK_DOWN = 1,                   /*!< Définition du numéro de la broche JOY_DOWN. */
   K_MK_EXPANDER_JOYSTICK_LEFT = 2,                   /*!< Définition du numéro de la broche JOY_LEFT. */
   K_MK_EXPANDER_JOYSTICK_RIGHT = 3,                  /*!< Définition du numéro de la broche JOY_RIGHT. */
   K_MK_EXPANDER_JOYSTICK_UP = 4,                     /*!< Définition du numéro de la broche JOY_UP. */
   K_MK_EXPANDER_AUDIO_INTERRUPT = 5,                 /*!< Définition du numéro de la broche AUDIO_INT. */
   K_MK_EXPANDER_OTGFS1_OVERCURRENT = 6,              /*!< Définition du numéro de la broche OTGFS1_OVERCURRENT. */
   K_MK_EXPANDER_OTGFS1_POWERSWITCHON = 7,            /*!< Définition du numéro de la broche OTGFS1_POWERSWITCHON. */
   K_MK_EXPANDER_OTGFS2_OVERCURRENT = 8,              /*!< Définition du numéro de la broche OTGFS2_OVERCURRENT. */
   K_MK_EXPANDER_OTGFS2_POWERSWITCHON = 9,            /*!< Définition du numéro de la broche OTGFS2_POWERSWITCHON. */
   K_MK_EXPANDER_CAMERA_XSDN = 10,                    /*!< Définition du numéro de la broche CAMERA_XSDN. */
   K_MK_EXPANDER_CAMERA_RSTI = 11,                    /*!< Définition du numéro de la broche CAMERA_RSTI. */
   K_MK_EXPANDER_CAMERA_PLUG = 12,                    /*!< Définition du numéro de la broche CAMERA_PLUG. */
   K_MK_EXPANDER_MII_INTERRUPT = 13,                  /*!< Définition du numéro de la broche MII_INT. */
   K_MK_EXPANDER_LCD_INTERRUPT = 14,                  /*!< Définition du numéro de la broche LDC_INT. */
   K_MK_EXPANDER_SDCARD_DETECT = 15,                  /*!< Définition du numéro de la broche SDCARD_DETECT. */
   K_MK_EXPANDER_LED1 = 16,                           /*!< Définition du numéro de la broche LED1 (non routée au MFX) */
   K_MK_EXPANDER_LED2 = 17,                           /*!< Définition du numéro de la broche LED2. */
   K_MK_EXPANDER_LED3 = 18,                           /*!< Définition du numéro de la broche LED3 (non routée au MFX) */
   K_MK_EXPANDER_LED4 = 19,                           /*!< Définition du numéro de la broche LED4. */
   K_MK_EXPANDER_RESERVED1 = 20,                      /*!< Broche réservée - aucun signal de connecté. */
   K_MK_EXPANDER_RESERVED2 = 21,                      /*!< Broche réservée - aucun signal de connecté. */
   K_MK_EXPANDER_RESERVED3 = 22,                      /*!< Broche réservée - aucun signal de connecté. */
   K_MK_EXPANDER_RESERVED4 = 23                       /*!< Broche réservée - aucun signal de connecté. */
} T_mkGPIOExpanderPin;

/**
 *
 */

#endif

