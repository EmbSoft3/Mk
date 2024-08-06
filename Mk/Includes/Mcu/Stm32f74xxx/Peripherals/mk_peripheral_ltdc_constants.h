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
* @file mk_peripheral_ltdc_constants.h
* @brief Déclaration des constantes dédiées au périphérique LTDC.
* @date 17 févr. 2019
*
*/

#ifndef MK_PERIPHERAL_LTDC_CONSTANTS_H
#define MK_PERIPHERAL_LTDC_CONSTANTS_H

/**
 * @def K_LTDC_SSCR
 * @brief Adresse du registre LTDC_SSCR.
 */

#define K_LTDC_SSCR ( addr_t ) 0x40016808

/**
 * @def K_LTDC_BPCR
 * @brief Adresse du registre LTDC_BPCR.
 */

#define K_LTDC_BPCR ( addr_t ) 0x4001680C

/**
 * @def K_LTDC_AWCR
 * @brief Adresse du registre LTDC_AWCR.
 */

#define K_LTDC_AWCR ( addr_t ) 0x40016810

/**
 * @def K_LTDC_TWCR
 * @brief Adresse du registre LTDC_TWCR.
 */

#define K_LTDC_TWCR ( addr_t ) 0x40016814

/**
 * @def K_LTDC_GCR
 * @brief Adresse du registre LTDC_GCR.
 */

#define K_LTDC_GCR ( addr_t ) 0x40016818

/**
 * @def K_LTDC_SRCR
 * @brief Adresse du registre LTDC_SRCR.
 */

#define K_LTDC_SRCR ( addr_t ) 0x40016824

/**
 * @def K_LTDC_BCCR
 * @brief Adresse du registre LTDC_BCCR.
 */

#define K_LTDC_BCCR ( addr_t ) 0x4001682C

/**
 * @def K_LTDC_IER
 * @brief Adresse du registre LTDC_IER.
 */

#define K_LTDC_IER ( addr_t ) 0x40016834

/**
 * @def K_LTDC_ISR
 * @brief Adresse du registre LTDC_ISR.
 */

#define K_LTDC_ISR ( addr_t ) 0x40016838

/**
 * @def K_LTDC_ICR
 * @brief Adresse du registre LTDC_ICR.
 */

#define K_LTDC_ICR ( addr_t ) 0x4001683C

/**
 * @def K_LTDC_LIPCR
 * @brief Adresse du registre LTDC_LIPCR.
 */

#define K_LTDC_LIPCR ( addr_t ) 0x40016840

/**
 * @def K_LTDC_CPSR
 * @brief Adresse du registre LTDC_CPSR.
 */

#define K_LTDC_CPSR ( addr_t ) 0x40016844

/**
 * @def K_LTDC_CDSR
 * @brief Adresse du registre LTDC_CDSR.
 */

#define K_LTDC_CDSR ( addr_t ) 0x40016848

/**
 * @def K_LTDC_LAYER1
 * @brief Adresse de base des registres du layer 1.
 */

#define K_LTDC_LAYER1 ( addr_t ) 0x40016884

/**
 * @def K_LTDC_LAYER2
 * @brief Adresse de base des registres du layer 2.
 */

#define K_LTDC_LAYER2 ( addr_t ) 0x40016904

/**
 *
 */

/**
 * @def K_LTDC_HSYNC
 * @brief Constante dédiée à la fonction ltdc_setPolarity(). \n
 *        Identifiant du signal HSYNC.
 */

#define K_LTDC_HSYNC 0x80000000

/**
 * @def K_LTDC_VSYNC
 * @brief Constante dédiée à la fonction ltdc_setPolarity(). \n
 *        Identifiant du signal VSYNC.
 */

#define K_LTDC_VSYNC 0x40000000

/**
 * @def K_LTDC_DATA_ENABLE
 * @brief Constante dédiée à la fonction ltdc_setPolarity(). \n
 *        Identifiant du signal NOT_DATA_ENABLE.
 */

#define K_LTDC_DATA_ENABLE 0x20000000

/**
 * @def K_LTDC_PIXEL_CLOCK
 * @brief Constante dédiée à la fonction ltdc_setPolarity(). \n
 *        Identifiant du signal K_LTDC_PIXEL_CLOCK.
 */

#define K_LTDC_PIXEL_CLOCK 0x10000000

/**
 * @def K_LTDC_VERTICAL_BLANKING
 * @brief Constante dédiée à la fonction ltdc_loadLayers(). \n
 *        Les registres configurant les layers sont mis à jour au début d'une
 *        nouvelle ligne, après le dessin de la zone active.
 */

#define K_LTDC_VERTICAL_BLANKING 0x00000002

/**
 * @def K_LTDC_IMMEDIATE
 * @brief Constante dédiée à la fonction ltdc_loadLayers(). \n
 *        Les registres configurant les layers sont mis à jour immédiatement.
 */

#define K_LTDC_IMMEDIATE 0x00000001

/**
 * @def K_LTDC_ARGB8888
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels.
 */

#define K_LTDC_ARGB8888 0x00000000

/**
 * @def K_LTDC_RGB888
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels.
 */

#define K_LTDC_RGB888 0x00000001

/**
 * @def K_LTDC_RGB565
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels.
 */

#define K_LTDC_RGB565 0x00000002

/**
 * @def K_LTDC_ARBG1555
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels.
 */

#define K_LTDC_ARBG1555 0x00000003

/**
 * @def K_LTDC_ARGB4444
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels.
 */

#define K_LTDC_ARGB4444 0x00000004

/**
 * @def K_LTDC_L8
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels (8 bits luminance).
 */

#define K_LTDC_L8 0x00000005

/**
 * @def K_LTDC_AL44
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels (4 bits alpha et 4 bits luminance).
 */

#define K_LTDC_AL44 0x00000006

/**
 * @def K_LTDC_AL88
 * @brief Constante dédiée à la fonction ltdc_setPixelFormat(). \n
 *        Configuration du format des pixels (8 bits alpha et 8 bits luminance).
 */

#define K_LTDC_AL88 0x00000007

/**
 * @def K_LTDC_BLENDING_FACTOR1_CONSTANT_ALPHA
 * @brief Constante dédiée à la fonction ltdc_setBlendingFactors(). \n
 *        Configuration du facteur alpha 1 à la valeur DEFAULT_ALPHA du layer.
 */

#define K_LTDC_BLENDING_FACTOR1_CONSTANT_ALPHA 0x00000400

/**
 * @def K_LTDC_BLENDING_FACTOR1_PXL_ALPHA_x_CONSTANT_ALPHA
 * @brief Constante dédiée à la fonction ltdc_setBlendingFactors(). \n
 *        Configuration du facteur alpha 1 à la valeur (PIXEL_ALPHA x DEFAULT_ALPHA).
 */

#define K_LTDC_BLENDING_FACTOR1_PXL_ALPHA_x_CONSTANT_ALPHA 0x00000600

/**
 * @def K_LTDC_BLENDING_FACTOR2_1_DIFF_CONSTANT_ALPHA
 * @brief Constante dédiée à la fonction ltdc_setBlendingFactors(). \n
 *        Configuration du facteur alpha 2 à la valeur (255-DEFAULT_ALPHA) du layer.
 */

#define K_LTDC_BLENDING_FACTOR2_1_DIFF_CONSTANT_ALPHA 0x00000005

/**
 * @def K_LTDC_BLENDING_FACTOR1_PXL_ALPHA_x_CONSTANT_ALPHA
 * @brief Constante dédiée à la fonction ltdc_setBlendingFactors(). \n
 *        Configuration du facteur alpha 2 à la valeur (255-(PIXEL_ALPHA x DEFAULT_ALPHA)).
 */

#define K_LTDC_BLENDING_FACTOR2_1_DIFF_PXL_ALPHA_x_CONSTANT_ALPHA 0x00000007

/**
 *
 */

#endif
