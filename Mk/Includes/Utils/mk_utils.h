/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_utils.h
* @brief Déclaration des fonctions utilitaires.
* @date 14 oct. 2018
*
*/

#ifndef MK_UTILS_H
#define MK_UTILS_H

/**
 * @fn void mk_utils_waitus ( uint32_t p_wait );
 * @brief Cette fonction effectue une attente active de p_wait micro-secondes.
 * @param[in] p_wait Ce paramètre contient le nombre de micro-secondes à attendre.
 * @return Sans objet.
 *
 * @warning Fonction non calibrée (cf. \ref K_UTILS_WAIT_MICRO_VALUE).
 *
 */

void mk_utils_waitus ( uint32_t p_wait );

/**
 * @fn void mk_utils_swap ( uint32_t* p_addr1, uint32_t* p_addr2 );
 * @brief Cette fonction échange la valeur de deux variables.
 *
 * @param[in] p_addr1 Ce paramètre contient l'adresse de la première variable.
 * @param[in] p_addr2 Ce paramètre contient l'adresse de la seconde variable.
 *
 * @return Sans objet.
 *
 */

void mk_utils_swap ( uint32_t* p_addr1, uint32_t* p_addr2 );

/**
 * @fn void mk_utils_reverse ( T_str8 p_str, uint32_t p_length );
 * @brief Cette fonction permute les éléments d'une chaine de caractères.
 *        Le premier caractère devient le dernier et inversement.
 *
 * @param[in] p_str    Ce paramètre contient l'adresse de la chaine de caractères à permuter.
 * @param[in] p_length Ce paramètre contient la taille de la chaine de caractères [en octets].
 *
 * @return Sans objet.
 *
 */

void mk_utils_reverse ( T_str8 p_str, uint32_t p_length );

/**
 * @fn uint32_t mk_utils_check2 ( uint32_t p_value, uint32_t p_minValue, uint32_t p_maxValue );
 * @brief Cette fonction compare la valeur p_value aux valeurs p_minValue, 2*p_minValue, 4*p_minValue, ...
 *        jusqu'au dépassement de p_maxValue.
 *
 * @param[in] p_value    Ce paramètre contient la valeur d'un entier 32bits.
 * @param[in] p_minValue Ce paramètre contient la valeur initiale de la comparaison.
 * @param[in] p_maxValue Ce paramètre contient la valeur maximale de la comparaison.
 *
 * @return Cette fonction retourne la valeur 0 si le paramètre p_value est égale à une des valeurs de comparaison,
 *         sinon la fonction retourne la valeur 1.
 *
 */

uint32_t mk_utils_check2 ( uint32_t p_value, uint32_t p_minValue, uint32_t p_maxValue );

/**
 * @fn uint32_t mk_utils_tick ( uint32_t p_refTick, uint32_t p_tick );
 * @brief Cette fonction retourne le nombre de ticks s'étant écoulés entre la valeur de référence
 *        'p_refTick' et la valeur 'p_tick'.
 *
 * @param[in] p_refTick Ce paramètre contient la valeur du tick de référence.
 * @param[in] p_tick    Ce paramètre contient la valeur de comparaison.
 *
 * @return Cette fonction retourne le nombre de tick s'étant écoulés entre le tick de référence
 *         et le tick présent en paramètre. L'overflow du compteur de tick est pris en considération
 *         par la fonction.
 *
 */

uint32_t mk_utils_tick ( uint32_t p_refTick, uint32_t p_tick );

/**
 * @fn int32_t mk_utils_rand ( uint32_t* randomNumber );
 * @brief Cette fonction retourne un nombre aléatoire codé sur 32 bits.
 * @param[in] randomNumber Ce paramètre contient l'adresse où doit être stocké le nombre aléatoire.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li (  0 ) : la fonction s'est exécutée sans rencontrée d'erreur.
 *         \li ( -1 ) : la fonction ne s'est pas exécutée car au moins un paramètre est invalide.
 *         \li ( -2 ) : la fonction ne peut pas fournir de nombre aléatoire car une erreur inattendue s'est produite.
 *         \li ( -3 ) : la fonction ne peut pas fournir de nombre aléatoire car le périphérique RNG est en cours de génération d'un nombre.
 *
 */

int32_t mk_utils_rand ( uint32_t* randomNumber );

/**
 * @fn int32_t mk_utils_getRandomString ( T_str8 p_randomString, T_str8 p_prefix, T_str8 p_suffix );
 * @brief Cette fonction retourne une chaine de caractères aléatoire au format suivant : [p_prefix][p_ramdomString<4words>][p_suffix].
 *
 * @param[out] p_randomString Ce paramètre contient l'adresse d'une chaine de caractères ASCII de taille : \n
 *                            strlen ( p_prefix ) + strlen ( p_suffix ) + 16 octets + 1 octets ('\0')
 * @param[in]  p_prefix       Ce paramètre contient l'adresse de la chaine de caractères ASCII contenant le préfix à insérer
 *                            dans la chaine de destination.
 * @param[in]  p_suffix       Ce paramètre contient l'adresse de la chaine de caractères ASCII contenant le suffix à insérer
 *                            dans la chaine de destination.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li (  0 ) : la fonction s'est exécutée sans rencontrée d'erreur.
 *         \li ( -1 ) : la fonction ne s'est pas exécutée car au moins un paramètre est invalide.
 *         \li ( -2 ) : la fonction ne peut pas fournir de nombre aléatoire car une erreur inattendue s'est produite.
 *         \li ( -3 ) : la fonction ne peut pas fournir de nombre aléatoire car le périphérique RNG est en cours de génération d'un nombre.
 *
 */

int32_t mk_utils_getRandomString ( T_str8 p_randomString, T_str8 p_prefix, T_str8 p_suffix );

/**
 *
 */

#endif
