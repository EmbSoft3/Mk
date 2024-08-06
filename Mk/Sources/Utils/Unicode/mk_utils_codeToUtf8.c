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
* @file mk_utils_codeToUtf8.c
* @brief Définition de la fonction mk_utils_codeToUtf8.
* @date 25 déc. 2019
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_codeToUtf8 ( uint32_t p_codepoint )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si le code est dans la plage [0:7F] */
   if ( p_codepoint <= 0x0000007F )
   {
      /* Le caractère UTF-8 est égale au point de codage */
      l_result = p_codepoint;
   }

   /* Sinon si le code est dans la plage [80:7FF] */
   else if ( p_codepoint <= 0x000007FF )
   {
      /* Code = yyy yyxxxxxx ; Utf8 = 110yyyyy  10xxxxxx */
      l_result = ( 0xC080 | ( ( p_codepoint & 0x7C0 ) << 2 ) | ( p_codepoint & 0x3F ) );
   }

   /* Sinon si le code est dans la plage [800:FFFF] */
   else if ( p_codepoint <= 0x0000FFFF )
   {
      /* Code = zzzzyyyy yyxxxxxx ; Utf8 = 1110zzzz 10yyyyyy  10xxxxxx */
      l_result = ( 0xE08080 | ( ( p_codepoint & 0xF000 ) << 4 ) | ( ( p_codepoint & 0x0FC0 ) << 2 ) | ( p_codepoint & 0x3F ) );
   }

   /* Sinon si le code est dans la plage [10000:10FFFF] */
   else if ( p_codepoint <= 0x0010FFFF )
   {
      /* Code = uuuzz zzzzyyyy yyxxxxxx ; Utf8 = 11110uuu 10zzzzzz 10yyyyyy  10xxxxxx */
      l_result = ( 0xF0808080 | ( ( p_codepoint & 0x1C0000 ) << 6 ) | ( ( p_codepoint & 0x3F000 ) << 4 ) | ( ( p_codepoint & 0x0FC0 ) << 2 ) | ( p_codepoint & 0x3F ) );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



