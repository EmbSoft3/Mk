/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_display_field_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Field'.
* @date 4 août 2023
*
*/

#ifndef MK_DISPLAY_FIELD_PRIVATE_H
#define MK_DISPLAY_FIELD_PRIVATE_H

/**
 * @fn void mk_field_setFocus ( T_mkField* p_field, uint32_t p_state );
 * @brief Cette fonction configure l'état de l'attribut 'focus' d'un champ de type \ref T_mkField.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_state Ce paramètre contient la valeur de l'attribut 'focus'. Un des constantes suivantes peut être utilisée :
 *                     \ref K_MK_FIELD_STATE_IDLE ou \ref K_MK_FIELD_STATE_FOCUS.
 *
 * @return Sans objet.
 *
 */

void mk_field_setFocus ( T_mkField* p_field, uint32_t p_state );

/**
 * @fn void mk_field_setCursor ( T_mkField* p_field, uint32_t p_state );
 * @brief Cette fonction configure l'état de l'attribut 'cursor' d'un champ de type \ref T_mkField.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_state Ce paramètre contient la valeur de l'attribut 'cursor'. Un des constantes suivantes peut être utilisée :
 *                     \ref K_MK_FIELD_CURSOR_OUTSIDE ou \ref K_MK_FIELD_CURSOR_INSIDE.
 *
 * @return Sans objet.
 *
 */

void mk_field_setCursor ( T_mkField* p_field, uint32_t p_state );

/**
 *
 */

#endif

