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
* @file mk_display_color_constants.h
* @brief Déclaration des constantes dédiées au module 'Color'.
* @date 7 avr. 2019
*
*/

#ifndef MK_DISPLAY_COLOR_CONSTANTS_H
#define MK_DISPLAY_COLOR_CONSTANTS_H

/**
 * @def K_MK_COLOR_ARGB_TRANSPARENT
 * @brief Définition de la couleur transparente. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_TRANSPARENT 0x00000000

/**
 * @def K_MK_COLOR_ARGB_TRANSPARENT_BLACK
 * @brief Définition de la couleur noire transparente. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_TRANSPARENT_BLACK 0x80000000

/**
 * @def K_MK_COLOR_ARGB_BLACK
 * @brief Définition de la couleur noire. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_BLACK 0xFF000000

/**
 * @def K_MK_COLOR_ARGB_WHITE
 * @brief Définition de la couleur blanche. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_WHITE 0xFFFFFFFF

/**
 * @def K_MK_COLOR_ARGB_RED
 * @brief Définition de la couleur rouge. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_RED 0xFFFF0000

/**
 * @def K_MK_COLOR_ARGB_ORANGE
 * @brief Définition de la couleur orange. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_ORANGE 0xFFFFA500

/**
 * @def K_MK_COLOR_ARGB_LIME
 * @brief Définition de la couleur verte. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_LIME 0xFF00FF00

/**
 * @def K_MK_COLOR_ARGB_BLUE
 * @brief Définition de la couleur bleue. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_BLUE 0xFF0000FF

/**
 * @def K_MK_COLOR_ARGB_YELLOW
 * @brief Définition de la couleur jaune. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_YELLOW 0xFFFFFF00

/**
 * @def K_MK_COLOR_ARGB_CYAN
 * @brief Définition de la couleur cyan. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_CYAN 0xFF00FFFF

/**
 * @def K_MK_COLOR_ARGB_MAGENTA
 * @brief Définition de la couleur magenta. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_MAGENTA 0xFFFF00FF

/**
 * @def K_MK_COLOR_ARGB_SILVER
 * @brief Définition de la couleur argentée. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_SILVER 0xFFC0C0C0

/**
 * @def K_MK_COLOR_ARGB_GRAY
 * @brief Définition de la couleur grise. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_GRAY 0xFF808080

/**
 * @def K_MK_COLOR_ARGB_DARKEST_GRAY
 * @brief Définition de la valeur de la couleur gris sombre.
 */

#define K_MK_COLOR_ARGB_DARKEST_GRAY 0xFF101010

/**
 * @def K_MK_COLOR_ARGB_MAROON
 * @brief Définition de la couleur marron. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_MAROON 0xFF800000

/**
 * @def K_MK_COLOR_ARGB_OLIVE
 * @brief Définition de la couleur olive. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_OLIVE 0xFF808000

/**
 * @def K_MK_COLOR_ARGB_GREEN
 * @brief Définition de la couleur verte. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_GREEN 0xFF008000

/**
 * @def K_MK_COLOR_ARGB_DARKEST_GREEN
 * @brief Définition de la couleur verte sombre. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_DARKEST_GREEN 0xFF001500

/**
 * @def K_MK_COLOR_ARGB_PURPLE
 * @brief Définition de la couleur violette. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_PURPLE 0xFF800080

/**
 * @def K_MK_COLOR_ARGB_TEAL
 * @brief Définition de la couleur bleu sarcelle. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_TEAL 0xFF008080

/**
 * @def K_MK_COLOR_ARGB_NAVY
 * @brief Définition de la couleur océan. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_COLOR_ARGB_NAVY 0xFF000080

/**
 *
 */

#endif

