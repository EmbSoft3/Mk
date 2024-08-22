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
* @file mk_hid_key_types.h
* @brief Déclaration des types dédiés aux objets 'Key'
* @date 25 déc. 2019
*
*/

#ifndef MK_HID_KEY_TYPES_H
#define MK_HID_KEY_TYPES_H

/**
 * @struct T_mkUTFKey
 * @brief Déclaration de la structure T_mkUTFKey.
 *
 */

typedef struct T_mkUTFKey T_mkUTFKey;
struct T_mkUTFKey
{
   uint16_t scancode;                           /*!< Ce membre contient le scancode d'une touche (cf. document HID Usage Tables Version 1.12 §10). */
   uint8_t  padding8;                           /*!< Padding 8bits. */
   uint8_t  ascii;                              /*!< Ce membre contient le code ASCII d'une touche (8bits). */
   uint32_t utf8;                               /*!< Ce membre contient le code UTF8 d'une touche. */
   uint32_t utf16;                              /*!< Ce membre contient le code UTF16 d'une touche. */
   uint32_t utf32;                              /*!< Ce membre contient le code UTF32 d'une touche. */
};

/**
 * @struct T_mkKey
 * @brief Déclaration de la structure T_mkKey.
 *
 */

typedef struct T_mkKey T_mkKey;
struct T_mkKey
{
   T_mkButton button;                           /*!< Ce membre contient les attributs d'un bouton de type \ref T_mkButton. */
   T_mkUTFKey key;                              /*!< Ce membre contient les attributs UTF8, UTF16, UTF32 et le SCANCODE de la touche. */
};

/**
 * @struct T_mkKeyPool
 * @brief Déclaration de la structure T_mkKeyPool.
 *
 */

typedef struct T_mkKeyPool T_mkKeyPool;
struct T_mkKeyPool
{
   T_mkPoolArea area;                           /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   T_mkPool* pool;                           /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les structures \ref T_mkKey. */
   T_mkKey heap [ K_MK_KEY_NUMBER ];       /*!< Ce membre contient la mémoire dédiée aux structures \ref T_mkKey. */
};

/**
 *
 */

#endif

