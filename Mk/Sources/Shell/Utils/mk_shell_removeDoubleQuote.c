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
* @file mk_shell_removeDoubleQuote.c
* @brief Définition de la fonction mk_shell_removeDoubleQuote.
* @date 7 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_str8 mk_shell_removeDoubleQuote ( T_str8 p_str, T_mkFontUnicode p_fontEncoding )
{
   /* Déclaration de la variable de retour */
   T_str8 l_result = p_str;

   /* Récupération de la longueur de la chaine de caractères */
   uint32_t l_length = mk_utils_utflen ( p_str, p_fontEncoding );

   /* Si un couple de guillemets est présent en début et en fin de chaine */
   if ( ( p_str [ 0 ] == '"' ) && ( p_str [ l_length - 1 ] == '"' ) )
   {
      /* Suppression du guillement de fin de chaine */
      p_str [ l_length - 1 ] = '\0';

      /* Actualisation de la variable de retour */
      l_result = &p_str[ 1 ];
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}
