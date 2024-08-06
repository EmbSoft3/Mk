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
* @file mk_hid_axis_types.h
* @brief Déclaration des types dédiés aux objets 'Axis'.
* @date 11 nov. 2019
*
*/

#ifndef MK_HID_AXIS_TYPES_H
#define MK_HID_AXIS_TYPES_H

/**
 * @struct T_mkMouseLayer
 * @brief Déclaration de la structure T_mkMouseLayer.
 *
 */

typedef struct T_mkAxisRect T_mkAxisRect;
struct T_mkAxisRect
{
   real32_t x;                                  /*!< Ce membre contient la position 'x' de l'origine du rectangle. */
   real32_t y;                                  /*!< Ce membre contient la position 'y' de l'origine du rectangle. */
   real32_t width;                              /*!< Ce membre contient la largeur du rectangle. */
   real32_t height;                             /*!< Ce membre contient la hauteur du rectangle. */
};

/**
 * @struct T_mkAxis2
 * @brief Déclaration de la structure T_mkAxis2.
 *
 */

typedef struct T_mkAxis2 T_mkAxis2;
struct T_mkAxis2
{
   T_mkAxisRect rectangle;                      /*!< Ce membre contient les dimensions d'un plan. */
   int32_t dx;                                  /*!< Ce membre contient la variation sur l'axe X d'un pointeur ou d'un stick. */
   int32_t dy;                                  /*!< Ce membre contient la variation sur l'axe Y d'un pointeur ou d'un stick. */
   real32_t x;                                  /*!< Ce membre contient la position courante sur l'axe X d'un pointeur ou d'un stick. La position doit être bornée par rapport à une constante. */
   real32_t y;                                  /*!< Ce membre contient la position courante sur l'axe Y d'un pointeur ou d'un stick. La position doit être bornée par rapport à une constante. */
   real32_t resolution;                         /*!< Ce membre contient la résolution des axes X et Y. */
};

/**
 *
 */

#endif

