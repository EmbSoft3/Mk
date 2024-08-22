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
* @file mk_display_font_types.h
* @brief Déclaration des types dédiés aux polices de caractères.
* @date 26 déc. 2019
*
*/

#ifndef MK_DISPLAY_FONT_TYPES_H
#define MK_DISPLAY_FONT_TYPES_H

/**
 * @enum T_mkFontUnicode
 * @brief Déclaration de l'énumération T_mkFontUnicode.
 */

typedef enum T_mkFontUnicode
{
   K_MK_FONT_ASCII = 0x00,                                                    /*!< Définition de l'identifiant de l'encodage ASCII (1 octet). */
   K_MK_FONT_UTF8  = 0x01,                                                    /*!< Définition de l'identifiant de l'encodage UTF8  (1 à 4 octets). */
   K_MK_FONT_UTF16 = 0x02,                                                    /*!< Définition de l'identifiant de l'encodage UTF16 (2 ou 4 octets). */
   K_MK_FONT_UTF32 = 0x03                                                     /*!< Définition de l'identifiant de l'encodage UTF32 (4 octets). */
} T_mkFontUnicode;

/**
 * @enum T_mkFontUnicodePage
 * @brief Déclaration de l'énumération T_mkFontUnicodePage.
 */

typedef enum T_mkFontUnicodePage
{
   K_MK_FONT_PAGE_BASIC_LATIN = 0x0020,                                       /*!< Définition du point de codage du début de la page de caractères 'BasicLatin'. */
   K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT = 0x0080,                                /*!< Définition du point de codage du début de la page de caractères 'Latin1Supplement'. */
   K_MK_FONT_PAGE_LATIN_EXTENDED_A = 0x0100,                                  /*!< Définition du point de codage du début de la page de caractères 'LatinExtentedA'. */
   K_MK_FONT_PAGE_LATIN_EXTENDED_B = 0x0180,                                  /*!< Définition du point de codage du début de la page de caractères 'LatinExtentedB'. */
   K_MK_FONT_PAGE_IPA_EXTENSIONS = 0x0250,                                    /*!< Définition du point de codage du début de la page de caractères 'IPAExtensions'. */
   K_MK_FONT_PAGE_SPACING_MODIFIER_LETTERS = 0x02B0,                          /*!< Définition du point de codage du début de la page de caractères 'SpacingModifierLetters'. */
   K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS = 0x0300,                       /*!< Définition du point de codage du début de la page de caractères 'CombiningDiacriticalMarks'. */
   K_MK_FONT_PAGE_GREEK_AND_COPTIC = 0x0370,                                  /*!< Définition du point de codage du début de la page de caractères 'GreekAndCoptic'. */
   K_MK_FONT_PAGE_GENERAL_PUNCTUATION = 0x2000,                               /*!< Définition du point de codage du début de la page de caractères 'GeneralPunctuation'. */
   K_MK_FONT_PAGE_SUPERSCRIPTS_AND_SUBSCRIPTS = 0x2070,                       /*!< Définition du point de codage du début de la page de caractères 'SuperscriptsAndSubscripts'. */
   K_MK_FONT_PAGE_CURRENCY_SYMBOLS = 0x20A0,                                  /*!< Définition du point de codage du début de la page de caractères 'CurrencySymbols'. */
   K_MK_FONT_PAGE_COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS = 0x20D0,           /*!< Définition du point de codage du début de la page de caractères 'CombiningDiacriticalMarksForSymbols'. */
   K_MK_FONT_PAGE_ARROWS = 0x2190,                                            /*!< Définition du point de codage du début de la page de caractères 'Arrows'. */
   K_MK_FONT_PAGE_MATHEMATICAL_OPERATORS = 0x2200,                            /*!< Définition du point de codage du début de la page de caractères 'MathematicalOperators'. */
   K_MK_FONT_PAGE_MISCELLANEOUS_TECHNICAL = 0x2300                            /*!< Définition du point de codage du début de la page de caractères 'MiscellaneousTechnical'. */
} T_mkFontUnicodePage;

/**
 * @struct T_mkFontPage
 * @brief Déclaration de la structure T_mkFontPage.
 */

typedef struct T_mkFontPage T_mkFontPage;
struct T_mkFontPage
{
   uint32_t firstCodePoint;                                                   /*!< Ce membre contient l'index du premier codePoint de la page. */
   uint32_t lastCodePoint;                                                    /*!< Ce membre contient l'index du premier codePoint de la prochaine page. */
   uint8_t* glyphTableAddr;                                                   /*!< Ce membre contient l'adresse de base des glyphes de la page. */
   uint16_t* glyphDescriptorAddr;                                             /*!< Ce membre contient l'adresse du descripteur des glyphes de la page. */
   T_mkFontPage* next;                                                        /*!< Ce membre contient l'adresse du prochain descripteur de page. */
   T_mkFontPage* previous;                                                    /*!< Ce membre contient l'adresse du précédent descripteur de page. */
};

/**
 * @struct T_mkFont
 * @brief Déclaration de la structure T_mkFont.
 */

typedef struct T_mkFont T_mkFont;
struct T_mkFont
{
   T_mkFontPage* firstPageAddr;                                               /*!< Ce membre contient l'adresse du premier descripteur de page. */
   T_mkFontPage* lastPageAddr;                                                /*!< Ce membre contient l'adresse du dernier descripteur de page. */
   uint16_t height;                                                           /*!< Ce membre contient la hauteur de la police de caractères. */
   uint16_t padding1;                                                         /*!< Padding pour alignement. */
   uint8_t padding2;                                                          /*!< Padding pour alignement. */
   uint8_t numberOfPixelsBetweenChars;                                        /*!< Ce membre contient le nombre de pixels entre chaque caractères. */
   uint8_t numberOfPixelsBetweenRows;                                         /*!< Ce membre contient le nombre de pixels entre chaque lignes. */
   uint8_t tabulationNumberOfPixels;                                          /*!< Ce membre contient le nombre de pixels du caractère tabulation. */
};

/**
 *
 */

#endif

