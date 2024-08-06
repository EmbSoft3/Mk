/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_utils_utf.h
* @brief Déclaration des fonctions utilitaires relatives aux chaines de caractères UTF.
* @date 30 juin 2024
*
*/

#ifndef MK_UTILS_UTF_H
#define MK_UTILS_UTF_H

/**
 * @fn T_str8 mk_utils_utfchr ( T_str8 p_str, uint32_t p_codepoint, uint32_t p_encoding )
 * @brief Cette fonction recherche la première occurence d'un caractère UTF dans une chaine.
 *
 * @param[in] p_str       Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_codepoint Ce paramètre contient la valeur du caractère recherché.
 * @param[in] p_encoding  Ce paramètre contient le format de la chaine de caractères.
 *                        Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                        \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne l'adresse du caractère ou la valeur \ref K_MK_NULL s'il n'a pas été trouvé.
 *
 */

T_str8 mk_utils_utfchr ( T_str8 p_str, uint32_t p_codepoint, uint32_t p_encoding );

/**
 * @fn T_str8 mk_utils_utfget ( T_str8 p_str, uint32_t p_index, uint32_t p_encoding );
 * @brief Cette fonction retourne l'adresse du caractère UTF8, UTF16, UTF32 ou ASCII à la position p_index.
 *
 * @param[in] p_str      Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_index    Ce paramètre contient l'index du caractère à retourner.
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 * @param[out] p_length Ce paramètre contient la longueur du caractère UTF. Elle varie de 1 à 4.
 *
 * @return Cette fonction retourne l'adresse du caractère ou la valeur \ref K_MK_NULL s'il n'a pas été trouvé.
 *
 */

T_str8 mk_utils_utfget ( T_str8 p_str, uint32_t p_index, uint32_t p_encoding, uint32_t* p_length );

/**
 * @fn uint32_t mk_utils_utflen ( T_str8 p_str, uint32_t p_encoding );
 * @brief Cette fonction retourne le nombre de caractères d'une chaine de caractères de type UTF8, UTF16,
 *        UTF32 ou ASCII . La fonction teste la présence du caractère '\0' pour déterminer la
 *        fin d'une chaine.
 *
 * @param[in] p_str      Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne le nombre de caractères de la chaine ou la valeur 0 si au moins un paramètre
 *         est invalide.
 *
 */

uint32_t mk_utils_utflen ( T_str8 p_str, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfsize ( T_str8 p_str, uint32_t p_encoding );
 * @brief Cette fonction retourne la taille [en octet] d'une chaine de caractères de type UTF8, UTF16,
 *        UTF32 ou ASCII . La fonction teste la présence du caractère '\0' pour déterminer la
 *        fin d'une chaine.
 *
 * @param[in] p_str      Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la taille de la chaine de caractères [en octets] ou la valeur 0 si au
 *         moins un paramètre est invalide.
 *
 */

uint32_t mk_utils_utfsize ( T_str8 p_str, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfnull ( uint32_t p_encoding );
 * @brief Cette fonction retourne la taille du caractère de fin de chaine [en octet].
 *
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la taille du caractère de fin de chaine (1, 2, 4) ou la valeur 0 si le
 *         paramètre est invalide.
 *
 */

uint32_t mk_utils_utfnull ( uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfinsert ( T_str8 p_str, uint32_t p_index, T_str8 p_utf, uint32_t p_length, uint32_t p_encoding );
 * @brief Cette fonction insère un caractère de taille p_length dans une chaine de caractères.
 *
 * @param[in, out] p_str Ce paramètre contient l'adresse de la chaine de caractères où le caractère unicode doit
 *                       être inséré. Cette chaine doit se terminer par le caractère \0.
 * @param[in] p_index    Ce paramètre contient l'index où le caractère doit être inséré.
 * @param[in] p_utf      Ce paramètre contient les digits du caractère unicode.
 * @param[in] p_length   Ce paramètre contient la taille du caractère unicode. Elle varie de 1 à 4 octets.
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la valeur 1 si aucune erreur ne s'est produite ou la valeur 0 si
 *         au moins un paramètre est invalide.
 *
 */

uint32_t mk_utils_utfinsert ( T_str8 p_str, uint32_t p_index, T_str8 p_utf, uint32_t p_length, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfcopy ( T_str8 p_inAddr, T_str8 p_outAddr, uint32_t p_encoding )
 * @brief Cette fonction copie une chaine de caractères dans une autre chaine.
 *
 * @param[in] p_inAddr   Ce paramètre contient l'adresse de la chaine de caractères à copier.
 *                       Cette chaine doit se terminer par le caractère \0.
 * @param[out] p_outAddr Ce paramètre contient l'adresse de la chaine de caractères où les données doivent être copiées.
 * @param[in] p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                       Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                       \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la taille de la chaine de caractères [en octet] ou la valeur 0 si la copie a échoué.
 *
 */

uint32_t mk_utils_utfcopy ( T_str8 p_inAddr, T_str8 p_outAddr, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfdel ( T_str8 p_str, uint32_t p_index, uint32_t p_encoding )
 * @brief Cette fonction supprime un caractère d'une chaine de caractères.
 *
 * @param[in, out] p_str     Ce paramètre contient l'adresse de la chaine de caractères où le caractère unicode doit
 *                           être supprimée. Cette chaine doit se terminer par le caractère \0.
 * @param[in]     p_index    Ce paramètre contient l'index du caractère à supprimer.
 * @param[in]     p_encoding Ce paramètre contient le format de la chaine de caractères.
 *                           Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                           \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la valeur 1 si aucune erreur ne s'est produite ou la valeur 0 si
 *         au moins un paramètre est invalide.
 *
 */

uint32_t mk_utils_utfdel ( T_str8 p_str, uint32_t p_index, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfcount ( T_str8 p_str, uint32_t p_codepoint, uint32_t p_encoding )
 * @brief Cette fonction retourne le nombre d'occurences d'un caractère dans une chaine. La fonction teste la
 *        présence du caractère '\0' pour déterminer la fin d'une chaine.
 *
 * @param[in] p_str       Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_codepoint Ce paramètre contient la valeur du caractère recherché.
 * @param[in] p_encoding  Ce paramètre contient le format de la chaine de caractères.
 *                        Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                        \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne le nombre d'occurences trouvées dans la chaine ou la valeur 0 si au moins un paramètre
 *         est invalide.
 *
 */

uint32_t mk_utils_utfcount ( T_str8 p_str, uint32_t p_codepoint, uint32_t p_encoding );

/**
 * @fn uint32_t mk_utils_utfsplit ( T_str8 p_str, T_str8 p_result, uint16_t p_index, uint32_t p_delimiter, uint32_t p_encoding );
 * @brief Cette fonction retourne le segment d'une chaine de caractères présent entre deux séparateurs.
 *        Les séparateurs sont définis par le paramètre p_delimiter ou le caractère de fin de chaine.
 *
 * @param[in]  p_str       Ce paramètre contient l'adresse de la chaine de caractères à analyser.
 * @param[out] p_result    Ce paramètre contient l'adresse de la chaine de caractères trouvée.
 * @param[in]  p_index     Ce paramètre contient l'index du segment à récupérer.
 * @param[in]  p_delimiter Ce paramètre contient la valeur du séparateur.
 * @param[in]  p_encoding  Ce paramètre contient le format de la chaine de caractères.
 *                         Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                         \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne la valeur 1 en cas de succès ou la valeur 0 si au moins un paramètre est invalide.
 *
 */

uint32_t mk_utils_utfsplit ( T_str8 p_str, T_str8 p_result, uint16_t p_index, uint32_t p_delimiter, uint32_t p_encoding );

/**
 *
 */

/**
 * @fn uint32_t mk_utils_codeToString ( uint32_t p_codepoint, T_str8 p_string, uint32_t p_format );
 * @brief Cette fonction écrit la valeur unicode d'un caractère dans un buffer.
 *
 * @param[in]  p_codepoint Ce paramètre contient la valeur d'un caractère unicode.
 * @param[out] p_string    Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in]  p_format    Ce paramètre contient le format de la chaine de caractères.
 *                         Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et
 *                         \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return La valeur nulle si la chaine de caractères est invalide ou le nombre d'octets copiés (1, 2, 3 ou 4).
 * @note Les octets de poids fort ayant la valeur nulle ne sont pas écrit dans le buffer.
 *
 */

uint32_t mk_utils_codeToString ( uint32_t p_codepoint, T_str8 p_string, uint32_t p_format );

/**
 * @fn uint32_t mk_utils_codeToUtf32 ( uint32_t p_codepoint );
 * @brief Cette fonction convertit un caractère unicode en caractère UTF-32.
 * @param[in] p_codepoint Ce paramètre contient la valeur d'un caractère unicode.
 *
 * @return Cette fonction retourne un caractère UTF-32.
 *         Si le caractère unicode est invalide, alors la valeur nulle est renvoyée.
 *
 */

uint32_t mk_utils_codeToUtf32 ( uint32_t p_codepoint );

/**
 * @fn uint32_t mk_utils_codeToUtf16 ( uint32_t p_codepoint );
 * @brief Cette fonction convertit un caractère unicode en caractère UTF-16.
 * @param[in] p_codepoint Ce paramètre contient la valeur d'un caractère unicode.
 *
 * @return Cette fonction retourne un caractère UTF-16.
 *         Si le caractère unicode est invalide, alors la valeur nulle est renvoyée.
 *
 */

uint32_t mk_utils_codeToUtf16 ( uint32_t p_codepoint );

/**
 * @fn uint32_t mk_utils_codeToUtf8 ( uint32_t p_codepoint );
 * @brief Cette fonction convertit un caractère unicode en caractère UTF-8.
 * @param[in] p_codepoint Ce paramètre contient la valeur d'un caractère unicode.
 *
 * @return Cette fonction retourne un caractère UTF-8.
 *         Si le caractère unicode est invalide, alors la valeur nulle est renvoyée.
 *
 */

uint32_t mk_utils_codeToUtf8 ( uint32_t p_codepoint );

/**
 * @fn uint32_t mk_utils_utf8ToUtf32 ( uint32_t p_utf8Value );
 * @brief Cette fonction convertit un caractère UTF-8 en caractère UTF-32.
 * @param[in] p_utf8Value Ce paramètre contient la valeur d'un caractère UTF-8.
 *
 * @return Cette fonction retourne la valeur du caractère UTF-32.
 *
 */

uint32_t mk_utils_utf8ToUtf32 ( uint32_t p_utf8Value );

/**
 * @fn uint32_t mk_utils_utf16ToUtf32 ( uint32_t p_utf16Value );
 * @brief Cette fonction convertit un caractère UTF-16 en caractère UTF-32.
 * @param[in] p_utf16Value Ce paramètre contient la valeur d'un caractère UTF-16.
 *
 * @return Cette fonction retourne la valeur du caractère UTF-32.
 *
 */

uint32_t mk_utils_utf16ToUtf32 ( uint32_t p_utf16Value );

/**
 *
 */

#endif

