/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_graphics_types.h
* @brief Déclaration des types dédiés au module 'Graphics'.
* @date 27 nov. 2022
*
*/

#ifndef MK_DISPLAY_GRAPHICS_TYPES_H
#define MK_DISPLAY_GRAPHICS_TYPES_H

/**
 * @enum T_mkTextAlignment
 * @brief Déclaration de l'énumération T_mkTextAlignment.
 */

typedef enum T_mkTextAlignment
{
   K_MK_TEXT_RIGHT_JUSTIFIED = 0x0,          /* Définition de l'identifiant permettant de justifier le texte à droite. */
   K_MK_TEXT_CENTER_JUSTIFIED = 0x01,        /* Définition de l'identifiant permettant de justifier le texte au centre. */
   K_MK_TEXT_LEFT_JUSTIFIED = 0x02,          /* Définition de l'identifiant permettant de justifier le texte à gauche. */
   K_MK_TEXT_TOP_JUSTIFIED = 0x03,           /* Définition de l'identifiant permettant de justifier le texte en haut. */
   K_MK_TEXT_DOWN_JUSTIFIED = 0x04           /* Définition de l'identifiant permettant de justifier le texte en bas. */
} T_mkTextAlignment;

/**
 * @struct T_mkTextCursor
 * @brief Déclaration de la structure T_mkTextCursor.
 */

typedef struct T_mkTextCursor T_mkTextCursor;
struct T_mkTextCursor
{
   uint32_t mode;                            /*!< Ce membre contient le mode de fonctionnement du curseur (insertion ou écrasement). */
   uint32_t baseOffset;                      /*!< Ce membre contient l'offset du premier caractère affiché d'une chaine de caractères. */
   uint32_t currentOffset;                   /*!< Ce membre contient l'offset du curseur par rapport au premier caractère affiché de la chaine de caractères (baseOffset). */
   uint32_t xoffset;                         /*!< Ce membre contient l'offset du curseur sur l'axe x [en pxl]. Il permet d'ajuster la position du curseur afin de s'adapter au style de la police de caractères. */
   uint32_t yoffset;                         /*!< Ce membre contient l'offset du curseur sur l'axe y [en pxl]. Il permet d'ajuster la position du curseur afin de s'adapter au style de la police de caractères. */
   uint32_t width;                           /*!< Ce membre contient la largeur du curseur [en pxl]. */
   uint32_t height;                          /*!< Ce membre contient la hauteur du curseur [en pxl]. */
   uint32_t visibility;                      /*!< Ce membre contient l'état du curseur (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB color;                           /*!< Ce membre contient la couleur du curseur. */
   uint32_t blink;                           /*!< Ce membre contient le registre de clignotement du curseur. */
};

/**
 * @struct T_mkTextStyle
 * @brief Déclaration de la structure T_mkTextStyle.
 */

typedef struct T_mkTextStyle T_mkTextStyle;
struct T_mkTextStyle
{
   T_mkFont* font;                           /*!< Ce membre contient l'adresse d'une police de caractères. */
   T_mkFontUnicode fontEncoding;             /*!< Ce membre contient l'encodage du texte (\ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8, \ref K_MK_FONT_UTF16 et \ref K_MK_FONT_UTF32). */
   T_mkTextAlignment verticalAlignment;      /*!< Ce membre contient le type d'alignement vertical de la chaine de caractères (\ref K_MK_TEXT_TOP_JUSTIFIED, \ref K_MK_TEXT_CENTER_JUSTIFIED, \ref K_MK_TEXT_DOWN_JUSTIFIED). */
   T_mkTextAlignment horizontalAlignment;    /*!< Ce membre contient le type d''alignement horizontal de la chaine de caractères (\ref K_MK_TEXT_RIGHT_JUSTIFIED, \ref K_MK_TEXT_CENTER_JUSTIFIED, \ref K_MK_TEXT_LEFT_JUSTIFIED). */
   uint32_t marginTop;                       /*!< Ce membre contient la valeur de la marge haute. */
   uint32_t marginBottom;                    /*!< Ce membre contient la valeur de la marge basse. */
   uint32_t marginRight;                     /*!< Ce membre contient la valeur de la marge droite. */
   uint32_t marginLeft;                      /*!< Ce membre contient la valeur de la marge gauche. */
   T_mkARGB color;                           /*!< Ce membre contient la couleur du texte. */
};

/**
 *
 */

#endif

