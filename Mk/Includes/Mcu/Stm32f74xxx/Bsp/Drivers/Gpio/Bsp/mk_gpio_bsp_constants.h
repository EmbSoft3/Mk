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
* @file mk_gpio_bsp_constants.h
* @brief Déclaration des constantes dédiées aux GPIO de chaque BSP.
* @date 17 mars 2026
*
*/

#ifndef MK_GPIO_BSP_CONSTANTS_H
#define MK_GPIO_BSP_CONSTANTS_H

/* Si compilation pour la carte EVAL2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @def K_MK_GPIO_TERMIO_LIST
 * @brief Liste de tous les termio dont l'initialisation doit être terminée avant le démarrage du terminal GPIO.
 */

#define K_MK_GPIO_TERMIO_LIST ( K_MK_TERMIO_FLAG_I2C1 | K_MK_TERMIO_FLAG_DISPATCHER )

/* Sinon si compilation pour la carte DISCO_REV_C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @def K_MK_GPIO_TERMIO_LIST
 * @brief Liste de tous les termio dont l'initialisation doit être terminée avant le démarrage du terminal GPIO.
 */

#define K_MK_GPIO_TERMIO_LIST ( K_MK_TERMIO_FLAG_DISPATCHER )

/**
 *
 */

/* Sinon si compilation d'une application externe */
#elif defined ( MK_EXTERNAL_APPS )

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif

/**
 *
 */

#endif
