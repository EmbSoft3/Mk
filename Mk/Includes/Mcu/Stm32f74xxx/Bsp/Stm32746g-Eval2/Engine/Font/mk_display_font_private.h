/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_display_font_private.h
* @brief Déclaration des fonctions privées dédiées aux polices de caractères.
* @date 1 janv. 2020
*
*/

#ifndef MK_DISPLAY_FONT_PRIVATE_H
#define MK_DISPLAY_FONT_PRIVATE_H

/**
 * @fn void mk_font_initDefault ( void );
 * @brief Cette fonction initialise les polices de caractères par défaut du moteur graphique.
 *
 * @return Sans objet.
 *
 */

void mk_font_initDefault ( void );

/**
 * @fn uint32_t mk_font_selectPage ( T_mkFont* p_font, uint32_t p_codepoint, uint32_t* p_baseAddr, uint32_t* p_width );
 * @brief Cette fonction récupére les informations d'un glyphe présent dans une police de caractères de type \ref T_mkFont.
 *        Si le glyphe n'est pas connu, la fonction retourne les valeurs de défaut.
 *
 * @param[in]  p_font      Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 * @param[in]  p_codepoint Ce paramètre contient le point de codage 32 bits du glyphe (codepoint).
 * @param[out] p_baseAddr  Ce paramètre contient l'adresse du bitmap du glyphe.
 * @param[out] p_width     Ce paramètre contient la largeur du glyphe [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_font_selectPage ( T_mkFont* p_font, uint32_t p_codepoint, uint32_t* p_baseAddr, uint32_t* p_width );

/**
 * @fn T_str8 mk_font_parseString ( T_str8 p_string, uint32_t* p_result, uint32_t p_font );
 * @brief Cette fonction retourne la valeur du point de codage du premier caractère d'une chaine.
 *
 * @param[in]  p_string Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[out] p_result Ce paramètre contient le point de codage 32 bits du premier caractère de la chaine.
 * @param[in]  p_font   Ce paramètre contient l'encodage de la chaine de caractères. Une des valeurs suivantes
 *                      peut être utilisée : \ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8, \ref K_MK_FONT_UTF16 et
 *                      \ref K_MK_FONT_UTF32.
 *
 * @return Ce paramètre retourne l'adresse du prochain caractère de la chaine.
 *
 */

T_str8 mk_font_parseString ( T_str8 p_string, uint32_t* p_result, uint32_t p_font );

/**
 *
 */

#endif
