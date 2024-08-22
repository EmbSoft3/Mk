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
* @file mk_display_field_constants.h
* @brief Déclaration des constantes dédiées au module 'Field'.
* @date 5 mai 2019
*
*/

#ifndef MK_DISPLAY_FIELD_CONSTANTS_H
#define MK_DISPLAY_FIELD_CONSTANTS_H

/**
 * @def K_MK_FIELD_VISIBLE
 * @brief Définition d'une valeur indiquant que le champ est visible. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_VISIBLE 1

/**
 * @def K_MK_FIELD_INVISIBLE
 * @brief Définition d'une valeur indiquant que le champ est invisible. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_INVISIBLE 0

/**
 * @def K_MK_FIELD_VISIBLE
 * @brief Définition d'une valeur indiquant que le champ est actif. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_ACTIF 1

/**
 * @def K_MK_FIELD_INACTIF
 * @brief Définition d'une valeur indiquant que le champ est inactif. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_INACTIF 0

/**
 * @def K_MK_FIELD_STATE_IDLE
 * @brief Définition d'une valeur indiquant que le champ est au repos. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_STATE_IDLE 0

/**
 * @def K_MK_FIELD_STATE_FOCUS
 * @brief Définition d'une valeur indiquant que le champ est ciblé. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_STATE_FOCUS 1

/**
 * @def K_MK_FIELD_CURSOR_OUTSIDE
 * @brief Définition d'une valeur indiquant que le curseur de la souris est à l'extérieur du champ. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_CURSOR_OUTSIDE 0

/**
 * @def K_MK_FIELD_CURSOR_INSIDE
 * @brief Définition d'une valeur indiquant que le curseur de la souris est à l'intérieur du champ. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_CURSOR_INSIDE 1

/**
 * @def K_MK_FIELD_REFRESH_DISABLED
 * @brief Définition d'une valeur indiquant que le rafraichissement du champ est désactivé. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_REFRESH_DISABLED 0

/**
 * @def K_MK_FIELD_REFRESH_ENABLED
 * @brief Définition d'une valeur indiquant que le rafraichissement du champ est activé. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_FIELD_REFRESH_ENABLED K_MK_DISPLAY_FRAME_BUFFER_NUMBER

/**
 *
 */

#endif
