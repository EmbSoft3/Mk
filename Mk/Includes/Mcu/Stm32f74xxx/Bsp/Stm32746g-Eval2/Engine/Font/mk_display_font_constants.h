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
* @file mk_display_font_constants.h
* @brief Déclaration des constantes dédiées aux polices de caractères.
* @date 20 avr. 2019
*
*/

#ifndef MK_DISPLAY_FONT_CONSTANTS_H
#define MK_DISPLAY_FONT_CONSTANTS_H

/**
 * @def K_MK_FONT_DEFAULT_NUMBER_OF_PAGES
 * @brief Définition du nombre de pages présentes dans la police de caractères par défaut.
 *
 */

#define K_MK_FONT_DEFAULT_NUMBER_OF_PAGES 10

/**
 * @def K_MK_FONT_DEFAULT_HEIGHT
 * @brief Définition de la hauteur [en pixel] de la police de caractères par défaut.
 *
 */

#define K_MK_FONT_DEFAULT_HEIGHT 21

/**
 * @def K_MK_FONT_DEFAULT_FIXED_HEIGHT
 * @brief Définition de la hauteur [en pixel] de la police de caractères de taille fixe par défaut.
 *
 */

#define K_MK_FONT_DEFAULT_FIXED_HEIGHT 18

/**
 * @def K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS
 * @brief Définition de la distance minimale entre deux lignes [en pixel].
 *
 */

#define K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS 2

/**
 * @def K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_CHARS
 * @brief Définition de la distance minimale entre deux caractères [en pixel].
 *
 */

#define K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_CHARS 3

/**
 * @def K_MK_FONT_DEFAULT_SPACE_PIXELS_NUMBER
 * @brief Définition de la largeur du caractère espace [en pixel].
 *
 */

#define K_MK_FONT_DEFAULT_SPACE_PIXELS_NUMBER 5

/**
 * @def K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER
 * @brief Définition de la largeur du caractère tabulation [en pixel].
 *
 */

#define K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER ( 3 * K_MK_FONT_DEFAULT_SPACE_PIXELS_NUMBER )

/**
 *
 */

#endif

