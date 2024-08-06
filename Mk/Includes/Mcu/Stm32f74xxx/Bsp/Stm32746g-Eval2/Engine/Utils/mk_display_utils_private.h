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
* @file mk_display_utils_private.h
* @brief Déclaration des fonctions utilitaires privées.
* @date 12 déc. 2022
*
*/

#ifndef MK_DISPLAY_UTILS_PRIVATE_H
#define MK_DISPLAY_UTILS_PRIVATE_H

/**
 * @fn void mk_display_utils_getFirstLinePosition ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_mkVect2Di* p_out, T_str8 p_string, uint32_t p_rowNumber, T_mkTextStyle* p_style );
 * @brief Cette fonction détermine la valeur des coordonnées [x, y] du début de la première ligne d'une chaine de caractères.
 *        Les coordonnées sont fonctions du mode de justification configuré dans la structure \ref T_mkTextStyle, du nombre de lignes présentes dans la fenêtre d'affichage et
 *        du nombre de caractères présents dans la chaine.
 *
 * @param[in]  p_v1        Ce paramètre contient les coordonnées du vecteur 'TopLeft' de la fenêtre.
 * @param[in]  p_v2        Ce paramètre contient les coordonnées du vecteur 'BottomRight' de la fenêtre.
 * @param[out] p_out       Ce paramètre contient les coordonnées du début de la ligne.
 * @param[in]  p_string    Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in]  p_rowNumber Ce paramètre contient le nombre de lignes présentes dans la fenêtre d'affichage.
 * @param[in]  p_style     Ce paramètre contient l'adresse d'une structure de type \ref T_mkTextStyle.
 *
 * @return Sans objet.
 *
 */

void mk_display_utils_getFirstLinePosition ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_mkVect2Di* p_out, T_str8 p_string, uint32_t p_rowNumber, T_mkTextStyle* p_style );

/**
 * @fn uint32_t mk_display_utils_getNewLineOverlap ( T_mkTextStyle* p_style, T_mkVect2Di* p_currentVect, uint32_t p_width, uint32_t* p_row, uint32_t p_x2, uint32_t p_y2 );
 * @brief Cette fonction est dédiée au dessin d'une chaine de caractères dans une fenêtre rectangulaire. Elle détermine si l'ajout d'un nouveau caractère de taille
 *        {p_with, p_style->font->height) produit un retour à la ligne ou produit un dépassement de de la fenêtre.
 *
 * @param[in]  p_style       Ce paramètre contient l'adresse d'une structure de type \ref T_mkTextStyle. Elle permet de connaitre la hauteur de la police de caractères.
 * @param[in]  p_currentVect Ce paramètre contient les coordonnées de dessin [x, y] du nouveau caractère.
 * @param[in]  p_width       Ce paramètre contient la largeur du caractère [en pixel].
 * @param[out] p_row         Ce paramètre contient la valeur 0 si un retour à ligne s'est produit sinon la valeur 1.
 * @param[in]  p_x2          Ce paramètre contient la valeur sur l'axe 'x' de la coordonnée 'BottomRight' de la fenêtre.
 * @param[in]  p_y2          Ce paramètre contient la valeur sur l'axe 'y' de la coordonnée 'BottomRight' de la fenêtre.
 *
 * @return Cette fonction retourne la valeur 0 si un dépassement s'est produit dans la fenêtre, sinon la valeur 1.
 *
 */

uint32_t mk_display_utils_getNewLineOverlap ( T_mkTextStyle* p_style, T_mkVect2Di* p_currentVect, uint32_t p_width, uint32_t* p_row, uint32_t p_x2, uint32_t p_y2 );

/**
 * @fn uint32_t mk_display_utils_getWindowMaxNumberOfLines ( T_mkTextStyle* p_style, uint32_t p_height );
 * @brief Cette fonction retourne le nombre maximal de lignes pouvant être dessinées dans une fenêtre de hauteur 'p_height'.
 *
 * @param[in] p_style  Ce paramètre contient l'adresse d'une structure de type \ref T_mkTextStyle.
 * @param[in] p_height Ce paramètre contient la hauteur de la fenêtre [en pixel].
 *
 * @return Cette fonction retourne le nombre de lignes maximal pouvant être dessinées dans une fenêtre.
 *
 */

uint32_t mk_display_utils_getWindowMaxNumberOfLines ( T_mkTextStyle* p_style, uint32_t p_height );

/**
 * @fn uint32_t mk_display_utils_getWindowCurrentNumberOfLines ( T_mkFont* p_font, T_str8 p_string, uint32_t p_maxNumberOfLine, T_mkFontUnicode p_fontEncoding, uint32_t p_width );
 * @brief Cette fonction retourne le nombre de lignes actuellement dessinées dans une fenêtre de largeur 'p_width'. Ce nombre évolue de 1 à 'p_maxNumberOfLine'.
 *
 * @param[in] p_font            Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in] p_string          Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_maxNumberOfLine Ce paramètre contient le nombre maximal de lignes pouvant être dessinées dans la fenêtre.
 * @param[in] p_fontEncoding    Ce paramètre contient l'encodage de la chaine de caractères. Il peut prendre les valeurs \ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8 à \ref K_MK_FONT_UTF32
 * @param[in] p_width           Ce paramètre contient la largeur de la fenêtre [en pixel].
 *
 * @return Cette fonction retourne le nombre de lignes actuellement dessinées dans une fenêtre (de 1 à 'p_maxNumberOfLine').
 *
 */

uint32_t mk_display_utils_getWindowCurrentNumberOfLines ( T_mkFont* p_font, T_str8 p_string, uint32_t p_maxNumberOfLine, T_mkFontUnicode p_fontEncoding, uint32_t p_width );

/**
 * @fn uint32_t mk_display_utils_getFirstLineNumberOfPixels ( T_mkFont* p_font, T_str8 p_string, T_mkFontUnicode p_fontEncoding, uint32_t p_width );
 * @brief Cette fonction retourne le nombre de pixels constituant la première ligne d'une chaine de caractères.
 *
 * @param[in]  p_font         Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]  p_string       Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in]  p_fontEncoding Ce paramètre contient l'encodage de la chaine de caractères. Il peut prendre les valeurs \ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8 à \ref K_MK_FONT_UTF32
 * @param[out] p_width        Ce paramètre contient le nombre de pixel dans la ligne.
 *
 * @return Cette fonction retourne la valeur 0 si un dépassement s'est produit dans la fenêtre, sinon la valeur 1.
 *
 */

uint32_t mk_display_utils_getFirstLineNumberOfPixels ( T_mkFont* p_font, T_str8 p_string, T_mkFontUnicode p_fontEncoding, uint32_t p_width );

/**
 * @fn T_mkCode mk_display_utils_setMargin ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_mkTextStyle* p_style );
 * @brief Cette fonction modifie les vecteurs positions 'TopLeft' et 'BottomRight' d'une fenêtre en fonction de la valeur des marges définies dans un style.
 *
 * @param[in,out] p_v1    Ce paramètre contient les coordonnées du vecteur 'TopLeft' de la fenêtre.
 * @param[in,out] p_v2    Ce paramètre contient les coordonnées du vecteur 'BottomRight' de la fenêtre.
 * @param[in]     p_style Cette fonction contient l'adresse d'un style de type \ref T_mkTextStyle.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les valeurs des vecteurs position ont été modifiées.
 *         \li \ref K_MK_ERROR_PARAM   : les valeurs des vecteurs position n'ont pas été modifiées car au moins un des paramètres est invalide (marge).
 *
 */

T_mkCode mk_display_utils_setMargin ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_mkTextStyle* p_style );

/**
 *
 */

#endif

