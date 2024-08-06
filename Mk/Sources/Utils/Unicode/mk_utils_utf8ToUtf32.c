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
* @file mk_utils_utf8ToUtf32.c
* @brief Définition de la fonction mk_utils_utf8ToUtf32.
* @date 27 déc. 2019
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_utf8ToUtf32 ( uint32_t p_utf8Value )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Si le code est dans la plage [0:7F] */
   if ( p_utf8Value < 0x100 )
   {
      /* Le code UTF8 et le code UTF32 sont identiques */
      l_result = p_utf8Value;
   }

   /* Sinon si le code est dans la plage [0x80:0x7FF] */
   else if ( p_utf8Value < 0x10000 )
   {
      /* UTF8 = 110yyyyy 10xxxxxx ; */
      l_result = ( 0x0000 | ( p_utf8Value & 0x3F ) | ( ( p_utf8Value & 0x1F00 ) >> 2 ) );
   }

   /* Sinon si le code est dans la plage [0x800:0x10000] */
   else if ( p_utf8Value < 0x1000000 )
   {
      /* Utf8 = 1110zzzz 10yyyyyy 10xxxxxx */
      l_result = ( 0x0000 | ( p_utf8Value & 0x3F ) | ( ( p_utf8Value & 0x3F00 ) >> 2 ) | ( ( p_utf8Value & 0xF0000 ) >> 4 ) );
   }

   /* Sinon si le code est dans la plage [0x800:0x10000] */
   else
   {
      /* Utf8 = 11110uuu 10zzzzzz 10yyyyyy  10xxxxxx */
      l_result = ( 0x00000 | ( p_utf8Value & 0x3F ) | ( ( p_utf8Value & 0x3F00 ) >> 2 ) | ( ( p_utf8Value & 0x3F0000) >> 4 ) | ( ( p_utf8Value & 0x7000000 ) >> 6 ) );
   }

   /* Retour */
   return ( l_result );
}
