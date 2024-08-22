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
* @file mk_display_vect2d.h
* @brief Déclaration des fonctions publiques du module 'Vect2D'.
* @date 7 avr. 2019
*
*/

#ifndef MK_DISPLAY_VECT2D_H
#define MK_DISPLAY_VECT2D_H

/**
 * @fn void mk_vect2d_setCoord ( T_mkVertex* p_vertex, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure les coordonnées [x,y] d'un vecteur de type \ref T_mkVect2D.
 *
 * @param[out] p_vertex Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 * @param[in]  p_x      Ce paramètre contient la valeur de composante 'x'.
 * @param[in]  p_y      Ce paramètre contient la valeur de la composante 'y'.
 *
 * @return Sans objet.
 *
 */

void mk_vect2d_setCoord ( T_mkVect2D* p_vertex, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_vect2d_setCoord2Di ( T_mkVect2Di* p_vertex, uint32_t p_x, uint32_t p_y );
 * @brief Cette fonction configure les coordonnées [x,y] d'un vecteur de type \ref T_mkVect2Di.
 *
 * @param[out] p_vertex Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 * @param[in]  p_x      Ce paramètre contient la valeur de composante 'x'.
 * @param[in]  p_y      Ce paramètre contient la valeur de la composante 'y'.
 *
 * @return Sans objet.
 *
 */

void mk_vect2d_setCoord2Di ( T_mkVect2Di* p_vertex, uint32_t p_x, uint32_t p_y );

/**
 * @fn void mk_vect2d_sort ( T_mkVect2D* p_v1, T_mkVect2D* p_v2 );
 * @brief Cette fonction trie les coordonnées des vecteurs présents en paramètres. Suite à l'appel de cette
 *        fonction, le vecteur 'p_v1' contient le pixel 'TopLeft' et le vecteur 'p_v2' contient le pixel 'BottomRight'.
 *
 * @param[out] p_v1 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 * @param[out] p_v2 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 *
 * @return Sans objet.
 * @todo Reprendre la description de cette fonction.
 *
 */

void mk_vect2d_sort ( T_mkVect2D* p_v1, T_mkVect2D* p_v2 );

/**
 * @fn void mk_vect2d_sort2Di ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2 );
 * @brief Cette fonction trie les coordonnées des vecteurs présents en paramètres. Suite à l'appel de cette
 *        fonction, le vecteur 'p_v1' contient le pixel 'TopLeft' et le vecteur 'p_v2' contient le pixel 'BottomRight'.
 *
 * @param[out] p_v1 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 * @param[out] p_v2 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 *
 * @return Sans objet.
 * @todo Reprendre la description de cette fonction.
 *
 */

void mk_vect2d_sort2Di ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2 );

/**
 * @fn real32_t mk_vect2d_shift ( real32_t p_value );
 * @brief Cette fonction retourne la valeur du plus petit entier supérieur ou égale à 'p_value'.
 * @param[in] p_value Ce paramètre contient la valeur à approximer.
 *
 * @return Cette fonction retourne la valeur du plus petit entier supérieur ou égale à 'p_value'.
 *
 */

real32_t mk_vect2d_shift ( real32_t p_value );

/**
 * @fn real32_t _mk_vect2d_module ( real32_t p_x, real32_t p_y );
 * @brief Cette fonction calcule le module d'un vecteur 2 dimensions.
 *
 * @param[in] p_vect2D Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 *
 * @return Cette fonction retourne le module du vecteur.
 * @warning La FPU doit être activée pour utiliser cette fonction.
 *
 */

real32_t _mk_vect2d_module ( T_mkVect2D* p_vect2D );

/**
 * @fn real32_t _mk_vect2d_dot ( T_mkVect2D* p_v1, T_mkVect2D* p_v2 );
 * @brief Cette fonction calcule le produit scalaire de deux vecteurs.
 *
 * @param[in] p_v1 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 * @param[in] p_v2 Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D.
 *
 * @return Cette fonction retourne la valeur du produit scalaire.
 * @warning La FPU doit être activée pour utiliser cette fonction.
 *
 */

real32_t _mk_vect2d_dot ( T_mkVect2D* p_v1, T_mkVect2D* p_v2 );

/**
 * @fn void _mk_vect2d_scale ( T_mkVect2D* p_addrIn, T_mkVect2D* p_addrOut, real32_t p_scalar );
 * @brief Cette fonction calcule le produit d'un vecteur par un scalaire.
 *
 * @param[in]  p_addrIn  Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D (entrée).
 * @param[out] p_addrOut Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D (sortie).
 * @param[in]  p_scalar  Ce paramètre contient la valeur du scalaire.
 *
 * @return Sans objet.
 * @warning La FPU doit être activée pour utiliser cette fonction.
 *
 */

void _mk_vect2d_scale ( T_mkVect2D* p_addrIn, T_mkVect2D* p_addrOut, real32_t p_scalar );

/**
 * @fn void _mk_vect2d_rotation ( T_mkVect2D* p_addrIn, T_mkVect2D* p_addrOut, real32_t p_teta );
 * @brief Cette fonction réalise une rotation entre un vecteur et un scalaire.
 *
 * @param[in]  p_addrIn  Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D (entrée).
 * @param[out] p_addrOut Ce paramètre contient l'adresse d'un vecteur de type \ref T_mkVect2D (sortie).
 * @param[in]  p_teta    Ce paramètre contient la valeur d'un angle [en radian].
 *
 * @return Sans objet.
 * @warning La FPU doit être activée pour utiliser cette fonction.
 *
 */

void _mk_vect2d_rotation ( T_mkVect2D* p_addrIn, T_mkVect2D* p_addrOut, real32_t p_teta );

/**
 *
 */

#endif
