/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_utils_string.h
* @brief Déclaration des fonctions utilitaires relatives aux chaines de caractères.
* @date 30 juin 2024
*
*/

#ifndef MK_UTILS_STRING_H
#define MK_UTILS_STRING_H

/**
 * @fn T_str8 mk_utils_strchr ( T_str8 p_str, uint8_t p_char );
 * @brief Cette fonction recherche la première occurence d'un caractère dans une chaine.
 *
 * @param[in] p_str  Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_char Ce paramètre contient la valeur du caractère recherché.
 *
 * @return Cette fonction retourne l'adresse du caractère ou la valeur \ref K_MK_NULL s'il n'a pas
 *         été trouvé.
 *
 */

T_str8 mk_utils_strchr ( T_str8 p_str, uint8_t p_char );

/**
 * @fn uint32_t mk_utils_strlen ( T_str8 p_str )
 * @brief Cette fonction retourne la longueur d'une chaine de caractères. La fonction teste la
 *        présence du caractère '\0' pour déterminer la fin d'une chaine.
 * @param[in] p_str Ce paramètre contient l'adresse d'une chaine de caractères.
 *
 * @return Cette fonction retourne la longueur de la chaine de caractères ou la valeur 0 si
 *         le paramètre est invalide.
 *
 */

uint32_t mk_utils_strlen ( T_str8 p_str );

/**
 * @fn uint32_t mk_utils_strcat ( T_str8 p_str, T_str8 p_str1, T_str8 p_str2 )
 * @brief Cette fonction concatène deux chaines de caractères. Le caractère de fin de chaine est
 *        ajouté à la fin de la nouvelle chaine.
 *
 * @param[out] p_str  Ce paramètre contient l'adresse de la chaine de caractères à créer.
 * @param[in]  p_str1 Ce paramètre contient l'adresse de la première chaine à concaténer.
 * @param[in]  p_str2 Ce paramètre contient l'adresse de la deuxième chaine à concaténer.
 *
 * @return Cette fonction retourne la valeur 1 si aucune erreur ne s'est produite ou la valeur 0 si
 *         au moins un paramètre est invalide.
 *
 */

uint32_t mk_utils_strcat ( T_str8 p_str, T_str8 p_str1, T_str8 p_str2 );

/**
 * @fn uint32_t mk_utils_strcount ( T_str8 p_addr, uint8_t p_char )
 * @brief Cette fonction retourne le nombre d'occurences d'un caractère dans une chaine. La fonction teste la
 *        présence du caractère '\0' pour déterminer la fin d'une chaine.
 *
 * @param[in] p_addr Ce paramètre contient l'adresse de la chaine de caractères.
 * @param[in] p_char Ce paramètre contient la valeur dt caractère à tester.
 *
 * @return Cette fonction retourne le nombre d'occurences trouvées dans la chaine ou la valeur 0 si
 *         le paramètre est invalide.
 *
 */

uint32_t mk_utils_strcount ( T_str8 p_addr, uint8_t p_char );

/**
 * @fn uint32_t mk_utils_strsplit ( T_str8 p_str, T_str8 p_result, uint16_t p_index, uint8_t p_delimiter )
 * @brief Cette fonction retourne le segment d'une chaine de caractères présent entre deux séparateurs.
 *        Les séparateurs sont définis par le paramètre p_delimiter ou le caractère de fin de chaine.
 *
 * @param[in]  p_str       Ce paramètre contient l'adresse de la chaine de caractères à analyser.
 * @param[out] p_result    Ce paramètre contient l'adresse de la chaine de caractères trouvée.
 * @param[in]  p_index     Ce paramètre contient l'index du segment à récupérer.
 * @param[in]  p_delimiter Ce paramètre contient la valeur du séparateur.
 *
 * @return Cette fonction retourne la valeur 1 en cas de succès ou la valeur 0 si au moins un
 *         paramètre est invalide.
 *
 */

uint32_t mk_utils_strsplit ( T_str8 p_str, T_str8 p_result, uint16_t p_index, uint8_t p_delimiter );

/**
 * @fn uint32_t mk_utils_strcomp ( T_str8 p_str1, T_str8 p_str2, uint32_t p_bypass, uint32_t p_length )
 * @brief Cette fonction compare deux chaines de caractères.
 *
 * @param[in] p_str1   Ce paramètre contient l'adresse de la première chaine de caractères.
 * @param[in] p_str2   Ce paramètre contient l'adresse de la seconde chaine de caractères.
 * @param[in] p_bypass Ce paramètre permet d'ignorer la casse. Lorsqu'il est nul, la comparaison
 *                     d'un caractère minuscule avec le même caractère majuscule échoue. Sinon
 *                     lorsque le paramètre est non nul, la comparaison réussie.
 * @param[in] p_length Ce paramètre contient le nombre de caractères à comparer. Lorsqu'il est nul
 *                     la comparaison s'arrête lorsque le caractère de fin de chaine est rencontré.
 *
 * @return Cette fonction retourne la valeur '1' si les chaines sont identiques ou la valeur 0 si
 *         les chaines sont différentes (ou lorsqu'un paramètre est invalide).
 *
 */

uint32_t mk_utils_strcomp ( T_str8 p_str1, T_str8 p_str2, uint32_t p_bypass, uint32_t p_length );

/**
 * @fn uint32_t mk_utils_strglob ( T_str8 p_str, T_str8 p_pattern );
 * @brief Cette fonction compare une chaine de caractères avec un pattern. Le pattern peut être
 *        constitué des méta-caractères suivants : \n
 *        '*' : zéro ou plus caractères quelconques.\n
 *        '?' : un seul caractère quelconque.\n
 *        '#' : un seul digit (0 à 9).\n
 *        [charlist]  : un seul caractère de la liste 'charlist'.\n
 *        [!charlist] : un seul caractère qui n'est pas dans la liste 'charlist'.
 *
 * @param[in] p_str     Ce paramètre contient l'adresse de la chaine de caractères.
 * @param[in] p_pattern Ce paramètre contient l'adresse du pattern.
 *
 * @return Cette fonction retourne la valeur '1' si la chaine correspond au pattern sinon la
 *         valeur 0.
 *
 * @note Le caractère '-' peut être utilisé dans une liste pour spécifier une plage de caractères
 *       (par exemple [A-Z]). Les caractères d'une plage doivent être positionné dans un ordre croissant
 *       (par exemple [a-zA-Z0-9]). Le caractère '-' peut être positionné en première ou en dernière position
 *       pour lancer une recherche sur lui-même (ex. [-0-9], [0-9-] ou [!-0-9]).
 */

uint32_t mk_utils_strglob ( T_str8 p_str, T_str8 p_pattern );

/**
 * @fn T_str8 mk_utils_itoa ( uint32_t p_number, T_str8 p_result, uint8_t p_base );
 * @brief Cette fonction convertie un entier en chaine de caractères.
 *
 * @param[in] p_number Ce paramètre contient la valeur de l'entier à convertir.
 * @param[in] p_result Ce paramètre contient le buffer où le résultat de la convertion est
 *                     stocké. Le buffer n'est pas alloué dynamiquement par la fonction.
 * @param[in] p_base   Ce paramètre contient la base numérique du résultat.
 * @param[in] p_digit  Ce paramètre contient le nombre de digit minimal de la chaine de caractères.
 *
 * @return Cette fonction retourne l'adresse du buffer où est présent le résultat de la conversion.
 *
 */

T_str8 mk_utils_itoa ( uint32_t p_number, T_str8 p_result, uint8_t p_base, uint8_t p_digit );

/**
 * @fn uint32_t mk_utils_atoi ( T_str8 p_buf, uint32_t p_base );
 * @brief Cette fonction convertie une chaine de caractères en entier (positif ou négatif).
 *
 * @param[in] p_buf  Ce paramètre contient l'adresse de la chaine de caractères à convertir en entier.
 * @param[in] p_base Ce paramètre contient la base numérique du résultat.
 *
 * @return Cette fonction retourne le résultat de la conversion.
 *
 */

int32_t mk_utils_atoi ( T_str8 p_buf, uint32_t p_base );

/**
 *
 */

#endif


