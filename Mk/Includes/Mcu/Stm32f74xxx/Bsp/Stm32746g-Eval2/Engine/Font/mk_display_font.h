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
* @file mk_display_font.h
* @brief Déclaration des fonctions publiques dédiées aux polices de caractères.
* @date 1 juil. 2023
*
*/

#ifndef MK_DISPLAY_FONT_H
#define MK_DISPLAY_FONT_H

/**
 * @fn void mk_font_init ( T_mkFont* p_font );
 * @brief Cette fonction initialise une police de caractères de type \ref T_mkFont.
 * @param[out] p_font Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 *
 * @return Sans objet.
 *
 */

void mk_font_init ( T_mkFont* p_font );

/**
 * @fn void mk_font_setHeight ( T_mkFont* p_font, uint16_t p_height );
 * @brief Cette fonction configure la hauteur de la police de caractères.
 *
 * @param[in,out] p_font   Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_height Ce paramètre contient la hauteur de la police de caractères [en pxl].
 *
 * @return Sans objet.
 *
 */

void mk_font_setHeight ( T_mkFont* p_font, uint16_t p_height );

/**
 * @fn void mk_font_setTabulationNumberOfPixels ( T_mkFont* p_font, uint8_t p_tabulationNumberOfPixels );
 * @brief Cette fonction configure le nombre de pixels du caractère tabulation.
 *
 * @param[in,out] p_font                     Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_tabulationNumberOfPixels Ce paramètre contient la largeur du caractère tabulation [en pxl].
 *
 * @return Sans objet.
 *
 */

void mk_font_setTabulationNumberOfPixels ( T_mkFont* p_font, uint8_t p_tabulationNumberOfPixels );

/**
 * @fn void mk_font_setNumberOfPixelsBetweenChars ( T_mkFont* p_font, uint8_t p_numberOfPixels );
 * @brief Cette fonction configure la distance minimale entre 2 caractères [en pxl].
 *
 * @param[in,out] p_font           Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_numberOfPixels Ce paramètre contient la distance minimale entre 2 caractères [en pxl].
 *
 * @return Sans objet.
 *
 */

void mk_font_setNumberOfPixelsBetweenChars ( T_mkFont* p_font, uint8_t p_numberOfPixels );

/**
 * @fn void mk_font_setNumberOfPixelsBetweenRows ( T_mkFont* p_font, uint8_t p_numberOfPixelsBetweenRows );
 * @brief Cette fonction configure la distance minimale entre 2 lignes [en pxl].
 *
 * @param[in,out] p_font                      Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_numberOfPixelsBetweenRows Ce paramètre contient la distance minimale entre 2 lignes [en pxl].
 *
 * @return Sans objet.
 *
 */

void mk_font_setNumberOfPixelsBetweenRows ( T_mkFont* p_font, uint8_t p_numberOfPixelsBetweenRows );

/**
 * @fn void mk_font_addPage ( T_mkFont* p_font, T_mkFontPage* p_page );
 * @brief Cette fonction ajoute une nouvelle page dans une police de caractères.
 *
 * @param[in,out] p_font Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_page Ce paramètre contient l'adresse d'un descripteur de page de type \ref T_mkFontPage.
 *
 * @return Sans objet.
 *
 */

void mk_font_addPage ( T_mkFont* p_font, T_mkFontPage* p_page );

/**
 * @fn void mk_font_removePage ( T_mkFont* p_font, T_mkFontPage* p_page );
 * @brief Cette fonction supprime une page dans une police de caractères de type \ref T_mkFont.
 *
 * @param[in,out] p_font Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]     p_page Ce paramètre contient l'adresse d'un descripteur de page de type \ref T_mkFontPage.
 *
 * @return Sans objet.
 *
 */

void mk_font_removePage ( T_mkFont* p_font, T_mkFontPage* p_page );

/**
 * @fn void mk_font_setPage ( T_mkFontPage* p_page, uint32_t p_firstCodePoint, uint32_t p_lastCodePoint, uint16_t* p_glyphDescriptorAddr, uint8_t* p_glyphTableAddr );
 * @brief Cette fonction configure un descripteur de page de type \ref T_mkFontPage.
 *
 * @param[in,out] p_page                Ce paramètre contient l'adresse d'un descripteur de page de type \ref T_mkFontPage.
 * @param[in]     p_firstCodePoint      Ce paramètre contient la valeur du premier point de codage (codepoint) de la page. Par exemple \ref K_MK_FONT_PAGE_BASIC_LATIN.
 * @param[in]     p_lastCodePoint       Ce paramètre contient la valeur du dernier point de codage (codePoint) de la page. Par exemple \ref K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1.
 * @param[in]     p_glyphDescriptorAddr Ce paramètre contient l'adresse du descripteur de glyphes. Le descripteur est une table regroupant la largeur et l'offset de tous
 *                                      les caractères contenus dans la page (ex: \ref g_mkFontArialUnicodeMS12ptBasicLatinPageDescriptor). Il possède les caractéristiques
 *                                      suivantes :
 *                                      \li Type : uint16_t ['taille'] [2]
 *                                      \li Taille : [p_lastCodePoint - p_firstCodePoint + 1 ]
 *                                      \li Format : {'largeur_caractère', 'offset_caractere'}
 * @param[in]     p_glyphTableAddr      Ce paramètre contient l'adresse d'une table stockant les bitmaps de tous les caractères présents dans la page. Les bitmaps sont
 *                                      stockés les uns à la suite des autres conformément au descripteur p_glyphDescriptorAddr (ex: \ref g_mkFontArialUnicodeMS12ptBasicLatinPage).
 *                                      La hauteur des bitmaps est commune entre chaque caractère.
 *
 * @return Sans objet.
 *
 */

void mk_font_setPage ( T_mkFontPage* p_page, uint32_t p_firstCodePoint, uint32_t p_lastCodePoint, uint16_t* p_glyphDescriptorAddr, uint8_t* p_glyphTableAddr );

/**
 * @fn T_mkFont* mk_font_getDefault ( void );
 * @brief Cette fonction retourne l'adresse de la police de caractères par défault du moteur.
 * @return Cette fonction retourne l'adresse d'une instance de type \ref T_mkFont.
 *
 */

T_mkFont* mk_font_getDefault ( void );

/**
 *
 */

#endif


