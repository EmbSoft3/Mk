/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_display_progressBar_types.h
* @brief Déclaration des types dédiés à l'objet 'ProgressBar'.
* @date 14 oct. 2023
*
*/

#ifndef MK_DISPLAY_PROGRESSBAR_TYPES_H
#define MK_DISPLAY_PROGRESSBAR_TYPES_H

/**
 * @struct T_mkProgressBar
 * @brief Déclaration de la structure T_mkProgressBar.
 */

typedef struct T_mkProgressBar T_mkProgressBar;
struct T_mkProgressBar
{
   T_mkField field;                 /*!< Ce membre contient un champ de type \ref T_mkField (héritage). */
   T_mkAddr child;                  /*!< Ce membre contient l'adresse du descendant de la barre de progression (héritage). */
   uint32_t value;                  /*!< Ce membre contient le pourcentage de la barre de progression [entre 0 et 100]. */
   T_mkTextStyle* style;            /*!< Ce membre contient le style de la chaine de caractères. */
   uint32_t textVisibility;         /*!< Ce membre contient l'état du texte (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   uint32_t backgroundVisibility;   /*!< Ce membre contient l'état de l'arrière plan (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB backgroundColor;        /*!< Ce membre contient la couleur de l'arrière plan. */
   uint32_t foregroundVisibility;   /*!< Ce membre contient l'état du premier plan (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB foregroundColor;        /*!< Ce membre contient la couleur du premier plan. */
   uint32_t borderVisibility;       /*!< Ce membre contient l'état de la bordure (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   uint32_t borderWidth;            /*!< Ce membre contient la largeur de la bordure. */
   T_mkARGB borderColor;            /*!< Ce membre contient la couleur de la bordure. */
   T_str8 text;                     /*!< Ce membre contient l'adresse de la chaine de caractères de la barre de progression. */
   char8_t defaultText [ 8 ];       /*!< Ce membre contient le texte par défaut affiché dans une barre de progression. */
};

/**
 *
 */

#endif


