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
* @file mk_display_parser_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Parser'.
* @date 22 févr. 2020
*
*/

#ifndef MK_DISPLAY_PARSER_PRIVATE_H
#define MK_DISPLAY_PARSER_PRIVATE_H

/**
 * @fn void mk_parser_initAndresSolid ( T_mkAndresParser* p_parser, uint32_t p_radius );
 * @brief Cette fonction initialise les variables de l'algorithme d'Andres pour dessiner un cercle rempli.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 *
 * @return Sans objet.
 *
 */

void mk_parser_initAndresSolid ( T_mkAndresParser* p_parser, uint32_t p_radius );

/**
 * @fn void mk_parser_initAndresEmpty ( T_mkAndresParser* p_parser, uint32_t p_radius );
 * @brief Cette fonction initialise les variables de l'algorithme d'Andres pour dessiner un cercle vide.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 *
 * @return Sans objet.
 *
 */

void mk_parser_initAndresEmpty ( T_mkAndresParser* p_parser, uint32_t p_radius );

/**
 * @fn void mk_parser_refreshAndresSolid ( T_mkAndresParser* p_parser, uint32_t p_radius );
 * @brief Cette fonction actualise les variables de l'algorithme d'Andres. Elle détermine la position des prochains pixels à dessiner.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 *
 * @return Sans objet.
 *
 */

void mk_parser_refreshAndresSolid ( T_mkAndresParser* p_parser, uint32_t p_radius );

/**
 * @fn void mk_parser_refreshAndresEmpty ( T_mkAndresParser* p_parser, uint32_t p_radius );
 * @brief Cette fonction actualise les variables de l'algorithme d'Andres. Elle détermine la position des prochains pixels à dessiner.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 *
 * @return Sans objet.
 *
 */

void mk_parser_refreshAndresEmpty ( T_mkAndresParser* p_parser, uint32_t p_radius );

/**
 *
 */

/**
 * @fn void mk_parser_initSolidRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );
 * @brief Cette fonction initialise les variables de l'algorithme d'Andres pour dessiner un rectangle rempli avec les angles arrondis.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon de courbure des angles du rectangle.
 * @param[in]  p_width  Ce paramètre contient la largeur du rectangle arrondi [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_initSolidRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );

/**
 * @fn void mk_parser_initEmptyRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );
 * @brief Cette fonction initialise les variables de l'algorithme d'Andres pour dessiner un rectangle vide avec les angles arrondis.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon de courbure des angles du rectangle.
 * @param[in]  p_width  Ce paramètre contient la largeur du rectangle arrondi [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_initEmptyRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );

/**
 * @fn void mk_parser_initRoundRectCircleAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_x, uint32_t p_y, uint32_t p_height );
 * @brief Cette fonction initialise les variables spécifiques de l'algorithme d'Andres pour dessiner un rectangle avec les angles arrondis.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon de courbure des angles du rectangle.
 * @param[in]  p_x      Ce paramètre contient l'origine x du rectangle arrondi [en pixel].
 * @param[in]  p_y      Ce paramètre contient l'origine y du rectangle arrondi [en pixel].
 * @param[in]  p_height Ce paramètre contient la hauteur du rectangle arrondi [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_initRoundRectCircleAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_x, uint32_t p_y, uint32_t p_height );

/**
 * @fn void mk_parser_refreshSolidRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );
 * @brief Cette fonction actualise les variables de l'algorithme d'Andres. Elle détermine la position des prochains pixels à dessiner.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 * @param[in]  p_width  Ce paramètre contient la largeur du rectangle arrondi [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_refreshSolidRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );

/**
 * @fn void mk_parser_refreshEmptyRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );
 * @brief Cette fonction actualise les variables de l'algorithme d'Andres. Elle détermine la position des prochains pixels à dessiner.
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkAndresParser.
 * @param[in]  p_radius Ce paramètre contient le rayon du cercle.
 * @param[in]  p_width  Ce paramètre contient la largeur du rectangle arrondi [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_refreshEmptyRoundRectAndres ( T_mkAndresParser* p_parser, uint32_t p_radius, uint32_t p_width );

/**
 *
 */

/**
 * @fn void mk_parser_initBresenhamVertical ( T_mkBresenhamParser* p_parser, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2 );
 * @brief Cette fonction initialise les variables spécifiques de l'algorithme de Bresenham pour dessiner une droite (angle verticale).
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkBresenhamParser.
 * @param[in]  p_x1     Ce paramètre contient le position x du premier point de la droite [en pixel].
 * @param[in]  p_y1     Ce paramètre contient le position y du premier point de la droite [en pixel].
 * @param[in]  p_x2     Ce paramètre contient le position x du dernier point de la droite [en pixel].
 * @param[in]  p_y2     Ce paramètre contient le position y du dernier point de la droite [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_initBresenhamVertical ( T_mkBresenhamParser* p_parser, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2 );

/**
 * @fn void mk_parser_initBresenhamHorizontal ( T_mkBresenhamParser* p_parser, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2 );
 * @brief Cette fonction initialise les variables spécifiques de l'algorithme de Bresenham pour dessiner une droite (angle horizontal).
 *
 * @param[out] p_parser Ce paramètre contient l'adresse d'une structure de type \ref T_mkBresenhamParser.
 * @param[in]  p_x1     Ce paramètre contient le position x du premier point de la droite [en pixel].
 * @param[in]  p_y1     Ce paramètre contient le position y du premier point de la droite [en pixel].
 * @param[in]  p_x2     Ce paramètre contient le position x du dernier point de la droite [en pixel].
 * @param[in]  p_y2     Ce paramètre contient le position y du dernier point de la droite [en pixel].
 *
 * @return Sans objet.
 *
 */

void mk_parser_initBresenhamHorizontal ( T_mkBresenhamParser* p_parser, uint32_t p_x1, uint32_t p_y1, uint32_t p_x2, uint32_t p_y2 );

/**
 *
 */

#endif

