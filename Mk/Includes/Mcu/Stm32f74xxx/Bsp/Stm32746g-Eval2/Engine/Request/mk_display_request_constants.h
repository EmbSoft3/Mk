/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_request_constants.h
* @brief Déclaration des constantes dédiées au module 'Request'.
* @date 30 oct. 2022
*
*/

#ifndef MK_DISPLAY_REQUEST_CONSTANTS_H
#define MK_DISPLAY_REQUEST_CONSTANTS_H

/**
 * @def K_MK_DISPLAY_REQUEST_SIZE
 * @brief Définition de la taille d'un message (\ref T_mkDisplayRequest) du moteur graphique [en multiple de mots 32 bits].
 */

#define K_MK_DISPLAY_REQUEST_SIZE 12

/**
 * @def K_MK_DISPLAY_REQUEST_NUMBER
 * @brief Définition du nombre maximal de messages du moteur graphique.
 */

#define K_MK_DISPLAY_REQUEST_NUMBER 256

/**
 * @def K_MK_DISPLAY_REQUEST_AREA_SIZE
 * @brief Définition de la taille de la messagerie du moteur graphique [en multiple de mots 32bits].
 */

#define K_MK_DISPLAY_REQUEST_AREA_SIZE ( ( MK_MAIL_ITEM_SIZE + K_MK_DISPLAY_REQUEST_SIZE ) * K_MK_DISPLAY_REQUEST_NUMBER )

/**
 *
 */

#endif


