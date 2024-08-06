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
* @file mk_display_color_types.h
* @brief Définition des types dédiés au module 'Color'.
* @date 7 avr. 2019
*
*/

#ifndef MK_DISPLAY_COLOR_TYPES_H
#define MK_DISPLAY_COLOR_TYPES_H

/**
 * @struct T_mkARGB
 * @brief Déclaration de la structure T_mkARGB.
 * @note Ne pas modifier l'ordre des champs de la structure.
 */

typedef struct T_mkARGB T_mkARGB;
struct T_mkARGB
{
   uint8_t blue;           /*!< Ce membre contient la composante bleue de la couleur.  La valeur évolue entre 0 et 255. */
   uint8_t green;          /*!< Ce membre contient la composante verte de la couleur. La valeur évolue entre 0 et 255. */
   uint8_t red;            /*!< Ce membre contient la composante rouge de la couleur. La valeur évolue entre 0 et 255. */
   uint8_t alpha;          /*!< Ce membre contient la composante alpha de la couleur. La valeur évolue entre 0 et 255. */
};

/**
 * @struct T_mkAHSV
 * @brief Déclaration de la structure T_mkAHSV.
 */

typedef struct T_mkAHSV T_mkAHSV;
struct T_mkAHSV
{
   real32_t hue;           /*!< Ce membre contient la composante teinte. La valeur évolue entre 0 et 360°. */
   real32_t saturation;    /*!< Ce membre contient la composante saturation. La valeur évolue entre 0 et 1. */
   real32_t value;         /*!< Ce membre contient la composante valeur. La valeur évolue entre 0 et 1. */
   real32_t alpha;         /*!< Ce membre contient la composante alpha. La valeur évolue entre 0 et 1. */
};

/**
 * @struct T_mkAHSVLite
 * @brief Déclaration de la structure T_mkAHSVLite.
 */

typedef struct T_mkAHSVLite T_mkAHSVLite;
struct T_mkAHSVLite
{
   uint16_t hue;           /*!< Ce membre contient la composante teinte. La valeur évolue entre 0 et 1535. */
   uint8_t  saturation;    /*!< Ce membre contient la composante saturation. La valeur évolue entre 0 et 255. */
   uint8_t  value;         /*!< Ce membre contient la composante valeur. La valeur évolue entre 0 et 255. */
   uint8_t  alpha;         /*!< Ce membre contient la composante alpha. La valeur évolue entre 0 et 255. */
   uint8_t  rsv1;          /*!< Ce membre est reservé. */
   uint8_t  rsv2;          /*!< Ce membre est reservé. */
   uint8_t  rsv3;          /*!< Ce membre est reservé. */
};

/**
 *
 */

#endif

