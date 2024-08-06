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
* @file mk_display_color.h
* @brief Définition des fonctions publiques dédiées au module 'Color'.
* @date 7 avr. 2019
*
*/

#ifndef MK_DISPLAY_COLOR_H
#define MK_DISPLAY_COLOR_H

/**
 * @fn void mk_color_setARGB ( T_mkARGB* p_argb, uint8_t p_alpha, uint8_t p_red, uint8_t p_green, uint8_t p_blue );
 * @brief Cette fonction écrit les 4 composantes de couleurs dans une structure de type \ref T_mkARGB.
 *
 * @param[out] p_argb Ce paramètre contient un pointeur vers une structure de type \ref T_mkARGB.
 * @param[in] p_alpha Ce paramètre contient la valeur de composante alpha [entre 0 et 255].
 * @param[in] p_red   Ce paramètre contient la valeur de la composante rouge [entre 0 et 255].
 * @param[in] p_green Ce paramètre contient la valeur de la composante verte [entre 0 et 255].
 * @param[in] p_blue  Ce paramètre contient la valeur de la composante bleue [entre 0 et 255].
 *
 * @return Sans objet.
 *
 */

void mk_color_setARGB ( T_mkARGB* p_argb, uint8_t p_alpha, uint8_t p_red, uint8_t p_green, uint8_t p_blue );

/**
 * @fn void mk_color_setARGB32 ( T_mkARGB* p_argb, uint32_t p_color );
 * @brief Cette fonction écrit les composantes d'une couleur dans une structure de type \ref T_mkARGB.
 *
 * @param[in,out] p_argb  Ce paramètre contient l'adresse d'une structure de type \ref T_mkARGB.
 * @param[in]     p_color Ce paramètre contient une couleur au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_color_setARGB32 ( T_mkARGB* p_argb, uint32_t p_color );

/**
 * @fn void mk_color_setAHSV ( T_mkAHSV* p_ahsv, real32_t p_alpha, real32_t p_hue, real32_t p_saturation, real32_t p_value );
 * @brief Cette fonction écrit les 4 composantes de couleurs dans une structure de type \ref T_mkAHSV.
 *
 * @param[out] p_ahsv       Ce paramètre contient un pointeur vers une structure de type \ref T_mkAHSV.
 * @param[in]  p_hue        Ce paramètre contient la valeur de composante teinte [entre 0 et 360°].
 * @param[in]  p_saturation Ce paramètre contient la valeur de la composante saturation [entre 0 et 1].
 * @param[in]  p_value      Ce paramètre contient la valeur de la composante valeur [entre 0 et 1].
 * @param[in]  p_alpha      Ce paramètre contient la valeur de composante alpha [entre 0 et 1].
 *
 * @return Sans objet.
 *
 */

void mk_color_setAHSV ( T_mkAHSV* p_ahsv, real32_t p_hue, real32_t p_saturation, real32_t p_value, real32_t p_alpha );

/**
 * @fn void mk_color_setAHSVLite ( T_mkAHSVLite* p_ahsv, uint16_t p_hue, uint8_t p_saturation, uint8_t p_value, uint8_t p_alpha );
 * @brief Cette fonction écrit les 4 composantes de couleurs dans une structure de type \ref T_mkAHSVLite.
 *
 * @param[out] p_ahsv       Ce paramètre contient un pointeur vers une structure de type \ref T_mkAHSV.
 * @param[in]  p_hue        Ce paramètre contient la valeur de composante teinte [entre 0 et 1535].
 * @param[in]  p_saturation Ce paramètre contient la valeur de la composante saturation [entre 0 et 255].
 * @param[in]  p_value      Ce paramètre contient la valeur de la composante valeur [entre 0 et 255].
 * @param[in]  p_alpha      Ce paramètre contient la valeur de composante alpha [entre 0 et 255].
 *
 * @return Sans objet.
 *
 */

void mk_color_setAHSVLite ( T_mkAHSVLite* p_ahsv, uint16_t p_hue, uint8_t p_saturation, uint8_t p_value, uint8_t p_alpha );

/**
 * @fn void mk_color_rgb2hsv( T_mkARGB* p_argb, T_mkAHSV* p_ahsv );
 * @brief Cette fonction convertit une couleur au format ARGB vers une couleur au format AHSV.
 *
 * @param[in]  p_argb  Ce paramètre contient une couleur de type \ref T_mkARGB.
 * @param[out] p_ahsv  Ce paramètre contient une couleur de type \ref T_mkAHSV.
 *
 * @return Sans objet.
 *
 */

void mk_color_rgb2hsv ( T_mkARGB* p_argb, T_mkAHSV* p_ahsv );

/**
 * @fn void mk_color_hsv2rgb ( T_mkAHSV* p_ahsv, T_mkARGB* p_argb );
 * @brief Cette fonction convertit une couleur au format AHSV vers une couleur au format ARGB.
 *
 * @param[in]  p_ahsv Ce paramètre contient une couleur de type \ref T_mkAHSV.
 * @param[out] p_argb Ce paramètre contient une couleur de type \ref T_mkARGB.
 *
 * @return Sans objet.
 *
 */

void mk_color_hsv2rgb ( T_mkAHSV* p_ahsv, T_mkARGB* p_argb );

/**
 * @fn void _mk_color_hsv2rgbLite ( T_mkAHSVLite* p_ahsv, T_mkARGB* p_argb );
 * @brief Cette fonction convertit une couleur au format AHSVLite vers une couleur au format ARGB.
 *
 * @param[in]  p_ahsv Ce paramètre contient une couleur de type \ref T_mkAHSVLite.
 * @param[out] p_argb Ce paramètre contient une couleur de type \ref T_mkARGB.
 *
 * @return Cette fonction retourne la couleur au format ARGB8888.
 *
 */

uint32_t _mk_color_hsv2rgbLite ( T_mkAHSVLite* p_ahsv, T_mkARGB* p_argb );

/**
 * @fn uint32_t mk_color_getARGB32 ( T_mkARGB* p_argb );
 * @brief Cette fonction convertit une structure de type \ref T_mkARGB en mot 32bits ARGB8888.
 * @param[in] p_argb Ce paramètre contient l'adresse d'une structure de type \ref T_mkARGB.
 *
 * @return Cette fonction retourne un mot 32bits au format ARGB8888.
 *
 */

uint32_t mk_color_getARGB32 ( T_mkARGB* p_argb );

/**
 *
 */

#endif
