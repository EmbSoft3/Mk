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
* @file mk_gpio_expander_data.c
* @brief Définition de la fonction mk_gpio_expander_data.
* @date 21 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @fn const uint8_t g_expanderSettingTable [ MK_GPIO_EXPANDER_NUMBER_OF_PINS ] [ 4 ];
 * @brief Déclaration de la table de configuration du périphérique MFX.
 *
 * @note La dernière colonne contient le niveau à configurer sur une sortie ou dans le cas
 *       d'une entrée, le niveau de repos de celle-ci.
 *
 */

const uint8_t g_expanderSettingTable [ MK_GPIO_EXPANDER_NUMBER_OF_PINS ] [ 4 ] = {

      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* Joystick Sel */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* Joystick Down */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* Joystick Left */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* Joystick Right */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* Joystick Up */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* Audio Interrupt */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* OTG FS1 Overcurrent */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 0 },         /* OTG FS1 Power Switch On */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* OTG FS2 Overcurrent */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 0 },         /* OTG FS2 Power Switch On */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 0 },         /* Camera XSDN */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 0 },         /* Camera RSTI */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* Camera Plug */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* MII Interrupt */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* LCD Interrupt */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_ENABLE_PULL,  K_MK_GPIO_PULLUP,   1 },         /* SDCARD Detect */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 1 },         /* LED1 */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 1 },         /* LED2 */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 1 },         /* LED3 */
      { K_MK_GPIO_OUTPUT, K_MK_GPIO_PUSHPULL,     K_MK_GPIO_PULLDOWN, 1 },         /* LED4 */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* RESERVED1 */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* RESERVED2 */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* RESERVED3 */
      { K_MK_GPIO_INPUT,  K_MK_GPIO_DISABLE_PULL, K_MK_GPIO_PULLDOWN, 0 },         /* RESERVED4 */
};


