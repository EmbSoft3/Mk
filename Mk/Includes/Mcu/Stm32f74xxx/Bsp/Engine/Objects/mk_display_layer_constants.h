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
* @file mk_display_layer_constants.h
* @brief Déclaration des constantes dédiées à l'objet 'Layer'.
* @date 27 juil. 2024
*
*/

#ifndef MK_DISPLAY_LAYER_CONSTANTS_H
#define MK_DISPLAY_LAYER_CONSTANTS_H

/**
 * @def K_MK_LAYER_BOTH_VISIBLE
 * @brief Définition d'une valeur indiquant que les layers de premier plan et
 *        d'arrière plan sont visibles. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_LAYER_BOTH_VISIBLE 3

/**
 * @def K_MK_LAYER_FOREGROUND_VISIBLE
 * @brief Définition d'une valeur indiquant que le layer de premier plan est visible. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_LAYER_FOREGROUND_VISIBLE 2

/**
 * @def K_MK_LAYER_BACKGROUND_VISIBLE
 * @brief Définition d'une valeur indiquant que le layer d'arrière plan est visible. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_LAYER_BACKGROUND_VISIBLE 1

/**
 * @def K_MK_LAYER_INVISIBLE
 * @brief Définition d'une valeur indiquant que le layer est invisible. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_LAYER_INVISIBLE 0

/**
 *
 */

#endif

