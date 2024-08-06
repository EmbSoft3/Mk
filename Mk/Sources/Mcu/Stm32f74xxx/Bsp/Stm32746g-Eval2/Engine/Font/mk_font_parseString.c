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
* @file mk_font_parseString.c
* @brief Définition de la fonction mk_font_parseString.
* @date 1 janv. 2020
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_font_parseUTF8String ( T_str8 p_string, uint32_t* p_result )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_copy = 0;

   /* Si le caractère courant est codé sur 32 bits */
   if ( ( ( *p_string ) & 0xF8 ) == 0xF0 )
   {
      /* Copie de la chaine de caractères */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      _copy ( &l_copy, p_string, 4 );

      /* Rotation de la chaine de caractères */
      /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
      mk_utils_reverse ( ( T_str8 ) &l_copy, 4 );

      /* Conversion du caractère UTF8 en UTF32 */
      *p_result = mk_utils_utf8ToUtf32 ( l_copy );

      /* Actualisation du pointeur de chaine */
      p_string += 4;
   }

   /* Si le caractère courant est codé sur 24 bits */
   else if ( ( ( *p_string ) & 0xF0 ) == 0xE0 )
   {
      /* Copie de la chaine de caractères */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      _copy ( &l_copy, p_string, 3 );

      /* Rotation de la chaine de caractères */
      /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
      mk_utils_reverse ( ( T_str8 ) &l_copy, 3 );

      /* Conversion du caractère UTF8 en UTF32 */
      *p_result = mk_utils_utf8ToUtf32 ( l_copy & 0xFFFFFF );

      /* Actualisation du pointeur de chaine */
      p_string += 3;
   }

   /* Si le caractère courant est codé sur 16 bits */
   else if ( ( ( *p_string ) & 0xE0 ) == 0xC0 )
   {
      /* Copie de la chaine de caractères */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      _copy ( &l_copy, p_string, 2 );

      /* Rotation de la chaine de caractères */
      /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
      mk_utils_reverse ( ( T_str8 ) &l_copy, 2 );

      /* Conversion du caractère UTF8 en UTF32 */
      *p_result = mk_utils_utf8ToUtf32 ( l_copy & 0xFFFF );

      /* Actualisation du pointeur de chaine */
      p_string += 2;
   }

   /* Sinon */
   else
   {
      /* Conversion du caractère UTF8 en UTF32 */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      *p_result = mk_utils_utf8ToUtf32 ( ( uint32_t ) ( uint8_t ) ( *p_string ) );

      /* Actualisation du pointeur de chaine */
      p_string += 1;
   }

   /* Retour */
   return ( p_string );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_font_parseUTF16String ( T_str8 p_string, uint32_t* p_result )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_copy = 0;

   /* Déclaration d'un pointeur 16 bits */
   T_str16 l_pnt16 = ( T_mkAddr ) p_string;

   /* Si le caractère courant est codé sur 32 bits */
   if ( ( ( *l_pnt16 ) & 0x00FC ) == 0x00FC )
   {
      /* Copie de la chaine de caractères */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      _copy ( &l_copy, p_string, 4 );

      /* Rotation de la chaine de caractères */
      /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
      mk_utils_reverse ( ( T_str8 ) &l_copy, 4 );

      /* Conversion du caractère UTF16 en UTF32 */
      *p_result = mk_utils_utf16ToUtf32 ( l_copy );

      /* Actualisation du pointeur de chaine */
      p_string += 4;
   }

   /* Sinon le caractère est codé sur 16 bits */
   else
   {
      /* Copie de la chaine de caractères */
      /* Travail en 8 bits en raison de l'alignement des pointeurs */
      _copy ( &l_copy, p_string, 2 );

      /* Rotation de la chaine de caractères */
      /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
      mk_utils_reverse ( ( T_str8 ) &l_copy, 2 );

      /* Conversion du caractère UTF16 en UTF32 */
      *p_result = mk_utils_utf16ToUtf32 ( l_copy & 0xFFFF );

      /* Actualisation du pointeur de chaine */
      p_string += 2;
   }

   /* Retour */
   return ( p_string );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_font_parseUTF32String ( T_str8 p_string, uint32_t* p_result )
{
   /* Déclaration d'un pointeur de mots */
   T_str32 l_pnt32 = ( T_mkAddr ) p_string;

   /* Réalisation d'une copie locale de la chaine de caractères */
   uint32_t l_copy = ( uint32_t ) *l_pnt32;

   /* Rotation de la chaine de caractères */
   /* Requis car l'octet de poid fort est localisé sur l'adresse la plus faible */
   mk_utils_reverse ( ( T_str8 ) &l_copy, 4 );

   /* Conversion du caractère UTF32 */
   *p_result = l_copy;

   /* Actualisation du pointeur de chaine */
   p_string += 4;

   /* Retour */
   return ( p_string );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_str8 mk_font_parseASCIIString ( T_str8 p_string, uint32_t* p_result )
{
   /* Actualisation de la variable de retour */
   *p_result = ( uint32_t ) ( uint8_t ) ( *p_string );

   /* Actualisation du pointeur de chaine */
   p_string += 1;

   /* Retour */
   return ( p_string );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_str8 mk_font_parseString ( T_str8 p_string, uint32_t* p_result, uint32_t p_font )
{
   /* Si l'encodage de la chaine est de type UTF-8 */
   if ( p_font == K_MK_FONT_UTF8 )
   {
      /* Décodage d'un caractère UTF8 */
      p_string = mk_font_parseUTF8String ( p_string, p_result );
   }

   /* Sinon si l'encodage de la chaine est de type UTF-16 */
   else if ( p_font == K_MK_FONT_UTF16 )
   {
      /* Décodage d'un caractère UTF16 */
      p_string = mk_font_parseUTF16String ( p_string, p_result );
   }

   /* Sinon si l'encodage de la chaine est de type UTF-32 */
   else if ( p_font == K_MK_FONT_UTF32 )
   {
      /* Décodage d'un caractère UTF32 */
      p_string = mk_font_parseUTF32String ( p_string, p_result );
   }

   /* Sinon */
   else
   {
      /* Décodage d'un caractère ASCII */
      p_string = mk_font_parseASCIIString ( p_string, p_result );
   }

   /* Retour */
   return ( p_string );
}
