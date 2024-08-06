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
* @file mk_utils_codeToString.c
* @brief Définition de la fonction mk_utils_codeToString.
* @date 1 janv. 2020
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_utf8ToString ( uint32_t p_codepoint, T_str8 p_string )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Si le code est sur 1 octet */
   if ( ( p_codepoint & 0xFFFFFF00 ) == 0 )
   {
      /* Copie d'un octet */
      _writeByte ( p_string, ( uint8_t ) p_codepoint );

      /* Actualisation de la variable de retour */
      l_result = 1;
   }

   /* Sinon si le code est sur 2 octets */
   else if ( ( p_codepoint & 0xFFFF0000 ) == 0 )
   {
      /* Copie d'un mot 16 bits (MSB en premier pour faciliter le décodage) */
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8 ) );
      _writeByte ( p_string,   ( uint8_t ) ( p_codepoint      ) );

      /* Actualisation de la variable de retour */
      l_result = 2;
   }

   /* Sinon si le code est sur 3 octets */
   else if ( ( p_codepoint & 0xFF000000 ) == 0 )
   {
      /* Copie d'un mot 24 bits (MSB en premier pour faciliter le décodage) */
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 16 ) );
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8  ) );
      _writeByte ( p_string,   ( uint8_t ) ( p_codepoint       ) );

      /* Actualisation de la variable de retour */
      l_result = 3;
   }

   /* Sinon */
   else
   {
      /* Copie d'un mot 32 bits (MSB en premier pour faciliter le décodage) */
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 24 ) );
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 16 ) );
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8  ) );
      _writeByte ( p_string,   ( uint8_t ) ( p_codepoint       ) );

      /* Actualisation de la variable de retour */
      l_result = 4;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_utf16ToString ( uint32_t p_codepoint, T_str8 p_string )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Si le code est sur 2 octets */
   if ( ( p_codepoint & 0xFFFF0000 ) == 0 )
   {
      /* Copie d'un mot 16 bits (MSB en premier pour faciliter le décodage) */
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8 ) );
      _writeByte ( p_string,   ( uint8_t ) ( p_codepoint      ) );

      /* Actualisation de la variable de retour */
      l_result = 2;
   }

   /* Sinon */
   else
   {
      /* Copie d'un mot 32 bits (MSB en premier pour faciliter le décodage) */
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 24 ) );
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 16 ) );
      _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8  ) );
      _writeByte ( p_string,   ( uint8_t ) ( p_codepoint       ) );

      /* Actualisation de la variable de retour */
      l_result = 4;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_utf32ToString ( uint32_t p_codepoint, T_str8 p_string )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 4;

   /* Copie d'un mot 32 bits (MSB en premier pour faciliter le décodage) */
   _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 24 ) );
   _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 16 ) );
   _writeByte ( p_string++, ( uint8_t ) ( p_codepoint >> 8  ) );
   _writeByte ( p_string,   ( uint8_t ) ( p_codepoint       ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_asciiToString ( uint32_t p_codepoint, T_str8 p_string )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Copie d'un octet */
   _writeByte ( p_string, ( uint8_t ) p_codepoint );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_codeToString ( uint32_t p_codepoint, T_str8 p_string, uint32_t p_format )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration d'un pointeur de chaine 32bits */
   T_str32 l_str = ( T_mkAddr ) p_string;

   /* Si le pointeur de chaine est valide */
   if ( l_str != K_MK_NULL )
   {
      /* Si format UTF-8 */
      if ( p_format == K_MK_FONT_UTF8 )
      {
         /* Ecriture du caractère UTF8 dans le buffer */
         l_result = mk_utils_utf8ToString ( p_codepoint, p_string );
      }

      /* Sinon si format UTF-16 */
      else if ( p_format == K_MK_FONT_UTF16 )
      {
         /* Ecriture du caractère UTF16 dans le buffer */
         l_result = mk_utils_utf16ToString ( p_codepoint, p_string );
      }

      /* Sinon si format UTF-32 */
      else if ( p_format == K_MK_FONT_UTF32 )
      {
         /* Ecriture du caractère UTF32 dans le buffer */
         l_result = mk_utils_utf32ToString ( p_codepoint, p_string );
      }

      /* Sinon si format ASCII */
      else
      {
         /* Ecriture du caractère ASCII dans le buffer */
         l_result = mk_utils_asciiToString ( p_codepoint, p_string );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

