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
* @file mk_display_graphics_constants.h
* @brief Déclaration des constantes dédiées au module 'Graphics'.
* @date 9 mars 2019
*
*/

#ifndef MK_DISPLAY_GRAPHICS_CONSTANTS_H
#define MK_DISPLAY_GRAPHICS_CONSTANTS_H

/**
 * @def K_MK_GRAPHICS_SOLID
 * @brief Constantes dédiées aux fonctions du module 'Graphics'.\n
 *        Définition du mode de remplissage SOLID (plein).\n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 *
 */

#define K_MK_GRAPHICS_SOLID 0

/**
 * @def K_MK_GRAPHICS_EMPTY
 * @brief Constantes dédiées aux fonctions du modules 'Graphics'.\n
 *        Définition du mode de remplissage EMPTY (vide).\n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 *
 */

#define K_MK_GRAPHICS_EMPTY 1

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_INVISIBLE
 * @brief Constantes dédiées aux fonctions du modules 'Graphics'.\n
 *        Définition d'une constante générique permettant d'inhiber
 *        la fonction de peinture (dessin bordure, ...).
 */

#define K_MK_GRAPHICS_INVISIBLE 0

/**
 * @def K_MK_GRAPHICS_VISIBLE
 * @brief Constantes dédiées aux fonctions du modules 'Graphics'.\n
 *        Définition d'une constante générique permettant d'activer
 *        la fonction de peinture (dessin bordure, ...).
 */

#define K_MK_GRAPHICS_VISIBLE 1

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT
 * @brief Constantes dédiées aux dessins de chaines de caractères.\n
 *        Définition de la valeur par défaut de la marge gauche.
 */

#define K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT 0

/**
 * @def K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT
 * @brief Constantes dédiées aux dessins de chaines de caractères.\n
 *        Définition de la valeur par défaut de la marge droite.
 */

#define K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT 0

/**
 * @def K_MK_GRAPHICS_DEFAULT_MARGIN_TOP
 * @brief Constantes dédiées aux dessins de chaines de caractères.\n
 *        Définition de la valeur par défaut de la marge haute.
 */

#define K_MK_GRAPHICS_DEFAULT_MARGIN_TOP 0

/**
 * @def K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM
 * @brief Constantes dédiées aux dessins de chaines de caractères.\n
 *        Définition de la valeur par défaut de la marge basse.
 */

#define K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM 0

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_DEFAULT_TEXT_COLOR
 * @brief Constantes dédiées aux dessins des chaines de caractères.\n
 *        Définition de la couleur par défaut de la chaine (ARGB 32BITS).
 */

#define K_MK_GRAPHICS_DEFAULT_TEXT_COLOR { 0xFF, 0xFF, 0xFF, 0xFF }

/**
 * @def K_MK_GRAPHICS_CURSOR_TYPE_PRIMARY
 * @brief Constantes dédiées aux dessins du curseur d'une chaine de caractères.\n
 *        Définition du type primaire d'un curseur (vertical avant le caractère).
 */

#define K_MK_GRAPHICS_CURSOR_TYPE_PRIMARY 0

/**
 * @def K_MK_GRAPHICS_CURSOR_TYPE_SECONDARY
 * @brief Constantes dédiées aux dessins du curseur d'une chaine de caractères.\n
 *        Définition du type secondaire d'un curseur (horizontal sous le caractère).
 */

#define K_MK_GRAPHICS_CURSOR_TYPE_SECONDARY 1

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_FOREGROUND
 * @brief Constantes dédiées aux fonctions du module 'Graphics'.\n
 *        Définition de l'offset du buffer graphique dédié au 'layer' de premier plan.\n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 *
 */

#define K_MK_GRAPHICS_FOREGROUND 0

/**
 * @def K_MK_GRAPHICS_BACKGROUND
 * @brief Constantes dédiées aux fonctions du module 'Graphics'.\n
 *        Définition de l'offset du buffer graphique dédié au 'layer' d'arrière plan.\n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 *
 */

#define K_MK_GRAPHICS_BACKGROUND 1

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_FRAME_TO_ADDR
 * @brief Constantes dédiées à la copie d'une figure graphique.\n
 *        Définition de la direction du transfert (buffer graphique vers adresse mémoire).
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_FRAME_TO_ADDR 0x00000000

/**
 * @def K_MK_GRAPHICS_ADDR_TO_FRAME
 * @brief Constantes dédiées aux dessins de zone graphique.\n
 *        Définition de la direction du transfert (adresse mémoire vers buffer graphique).
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_ADDR_TO_FRAME 0x00010000

/**
 *
 */

/**
 * @def K_MK_GRAPHICS_ARGB8888
 * @brief Définition du format ARGB8888.
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_ARGB8888 0x00000000

/**
 * @def K_MK_GRAPHICS_RGB888
 * @brief Définition du format ARGB8888.
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_RGB888 0x00000001

/**
 * @def K_MK_GRAPHICS_RGB565
 * @brief Définition du format ARGB8888.
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_RGB565 0x00000002

/**
 * @def K_MK_GRAPHICS_ARGB1555
 * @brief Définition du format ARGB8888.
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_GRAPHICS_ARGB1555 0x00000003

/**
 * @def K_MK_GRAPHICS_ARGB4444
 * @brief Définition du format ARGB8888.
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */
#define K_MK_GRAPHICS_ARGB4444 0x00000004

/**
 *
 */

#endif

