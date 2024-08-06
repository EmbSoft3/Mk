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
* @file mk_hid_stick_types.h
* @brief Déclaration des types dédiés aux objets 'Stick'.
* @date 25 avr. 2020
*
*/

#ifndef MK_HID_STICK_TYPES_H
#define MK_HID_STICK_TYPES_H

/**
 * @struct T_mkStickCoord
 * @brief Déclaration de la structure T_mkStickCoord.
 *
 */

typedef struct T_mkStickCoord T_mkStickCoord;
struct T_mkStickCoord
{
   int32_t x;                                   /*!< Ce membre contient la position sur l'axe X d'un stick. */
   int32_t y;                                   /*!< Ce membre contient la position sur l'axe Y d'un stick. */
   int32_t z;                                   /*!< Ce membre contient la position sur l'axe Z d'un stick. */

   int32_t rx;                                  /*!< Ce membre contient la rotation sur l'axe X d'un stick. */
   int32_t ry;                                  /*!< Ce membre contient la rotation sur l'axe Y d'un stick. */
   int32_t rz;                                  /*!< Ce membre contient la rotation sur l'axe Z d'un stick. */
};

/**
 * @struct T_mkStick3
 * @brief Déclaration de la structure T_mkStick3.
 *
 */

typedef struct T_mkStick3 T_mkStick3;
struct T_mkStick3
{
   T_mkStickCoord current;                      /*!< Ce membre contient les coordonnées actuelles d'un stick. */
   T_mkStickCoord last;                         /*!< Ce membre contient les coordonnées précédentes d'un stick. */

   real32_t x;                                  /*!< Ce membre contient la position modulée sur l'axe X d'un stick. */
   real32_t y;                                  /*!< Ce membre contient la position modulée sur l'axe Y d'un stick. */
   real32_t z;                                  /*!< Ce membre contient la position modulée sur l'axe Z d'un stick. */

   real32_t dx;                                 /*!< Ce membre contient la variation sur l'axe X d'un stick. */
   real32_t dy;                                 /*!< Ce membre contient la variation sur l'axe Y d'un stick. */
   real32_t dz;                                 /*!< Ce membre contient la variation sur l'axe Z d'un stick. */

   real32_t rx;                                 /*!< Ce membre contient la rotation modulée sur l'axe X d'un stick. */
   real32_t ry;                                 /*!< Ce membre contient la rotation modulée sur l'axe Y d'un stick. */
   real32_t rz;                                 /*!< Ce membre contient la rotation modulée sur l'axe Z d'un stick. */
};

/**
 *
 */

#endif

