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
* @file mk_display_parser_types.h
* @brief Déclaration des types dédiés au module 'Parser'.
* @date 22 févr. 2020
*
*/

#ifndef MK_DISPLAY_PARSER_TYPES_H
#define MK_DISPLAY_PARSER_TYPES_H

/**
 * @struct T_mkAndresParser
 * @brief Déclaration de la structure T_mkAndresParser (cercle).
 */

typedef struct T_mkAndresParser T_mkAndresParser;
struct T_mkAndresParser
{
   int32_t d;                    /*!< Ce membre contient le résultat de l'équation permettant de localiser le prochain pixel à dessiner. */
   uint32_t x;                   /*!< Ce membre contient la position x du pixel à dessiner. */
   uint32_t y;                   /*!< Ce membre contient la position y du pixel à dessiner. */
   uint32_t dx;                  /*!< Ce membre contient la longueur des droites à dessiner sur l'axe x (dédié au cercle plein). */
   uint32_t dy;                  /*!< Ce membre contient la longueur des droites à dessiner sur l'axe y (dédié au cercle plein). */
   uint32_t cx;                  /*!< Ce membre contient la position x de début des droites horizontales à dessiner (dédié au rectangle arrondi). */
   uint32_t cy;                  /*!< Ce membre contient la position y de début des droites horizontales à dessiner (dédié au cercle localisé en haut du rectangle arrondi). */
   uint32_t by;                  /*!< Ce membre contient la position y de début des droites horizontales à dessiner (dédié au cercle localisé en bas du rectangle arrondi). */
};

/**
 * @struct T_mkBresenhamParser
 * @brief Déclaration de la structure T_mkBresenhamParser (droite).
 */

typedef struct T_mkBresenhamParser T_mkBresenhamParser;
struct T_mkBresenhamParser
{
   int32_t dx;                   /*!< Ce membre contient le delta sur l'axe x existant entre le début et la fin de la droite (coef. directeur). */
   int32_t dy;                   /*!< Ce membre contient le delta sur l'axe y existant entre le début et la fin de la droite (coef. directeur). */
   int32_t x;                    /*!< Ce membre contient la position x du pixel à dessiner. */
   int32_t y;                    /*!< Ce membre contient la position y du pixel à dessiner. */
   int32_t xi;                   /*!< Ce membre contient le pas d'incrémentation [en pixel] de l'algorithme sur l'axe des abscisses. */
   int32_t yi;                   /*!< Ce membre contient le pas d'incrémentation [en pixel] de l'algorithme sur l'axe des ordonnées. */
   int32_t d;                    /*!< Ce membre contient la valeur de l'erreur. */
};

/**
 * @struct T_mkTriangleParser
 * @brief Déclaration de la structure T_mkTriangleParser (triangle).
 */

typedef struct T_mkTriangleParser T_mkTriangleParser;
struct T_mkTriangleParser
{
   real32_t slope1;              /*!< Ce membre contient le coeficient directeur de la première pente du triangle. */
   real32_t slope2;              /*!< Ce membre contient le coeficient directeur de la deuxième pente du triangle. */
   real32_t x1;                  /*!< Ce membre contient la position x des points présents sur la première pente du triangle. */
   real32_t x2;                  /*!< Ce membre contient la position x des points présents sur la deuxième pente du triangle. */
   int32_t xstart;               /*!< Ce membre contient la position x des points présents sur la première pente du triangle. */
   int32_t xend;                 /*!< Ce membre contient la position x des points présents sur le deuxième pente du triangle. */
   int32_t ystart;               /*!< Ce membre contient la position y de la base du triangle. */
   int32_t yend;                 /*!< Ce membre contient la position y du sommet du triangle. */
   int32_t width;                /*!< Ce membre contient la longueur des droites dessinée (valeur absolue de la différence 'xend' - 'xstart'). */
   int32_t counter;              /*!< Ce membre contient la position y des droites dessinées. Il évolue de [ystart à yend[. */
};

/**
 *
 */

#endif

