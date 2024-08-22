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
* @file mk_display_graphics_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Graphics'.
* @date 6 avr. 2019
*
*/

#ifndef MK_DISPLAY_GRAPHICS_PRIVATE_H
#define MK_DISPLAY_GRAPHICS_PRIVATE_H

/**
 * @fn T_mkCode mk_graphics_checkVertex ( T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_mkVect2D* p_v3, real32_t p_width, real32_t p_height );
 * @brief Cette fonction vérifie la validité des trois vecteurs présents en paramètres. Un résultat OK est renvoyé si les coordonnées [ x, y ] sont
 *        strictement supérieures à zéro et strictement inférieures à p_width (x) et p_height (y).
 *
 * @param[in] p_v1 Ce paramètre contient l'adresse d'un vecteur deux dimensions de type \ref T_mkVect2D.
 * @param[in] p_v2 Ce paramètre contient l'adresse d'un vecteur deux dimensions de type \ref T_mkVect2D.
 * @param[in] p_v3 Ce paramètre contient l'adresse d'un vecteur deux dimensions de type \ref T_mkVect2D.
 *
 * @param[in] p_width  Ce paramètre contient la valeur maximale de la composante x de chaque vecteur.
 * @param[in] p_height Ce paramètre contient la valeur maximale de la composante y ce chaque vecteur.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : les 3 vecteurs présents en paramètre sont valides.
 *         \li \ref K_MK_ERROR_PARAM : au moins un des 3 vecteurs présents en paramètre est invalide.
 *
 */

T_mkCode mk_graphics_checkVertex ( T_mkVect2D* p_v1, T_mkVect2D* p_v2, T_mkVect2D* p_v3, real32_t p_width, real32_t p_height );

/**
 *
 */

#endif

