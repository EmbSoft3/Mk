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
* @file mk_utils_utfget.c
* @brief Définition de la fonction mk_utils_utfget.
* @date 11 déc. 2022
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_str8 mk_utils_utfget ( T_str8 p_str, uint32_t p_index, uint32_t p_font, uint32_t* p_length )
{
   /* Déclaration des variable de travail */
   uint32_t l_counter = 0, l_currentChar = 0;

   /* Déclaration d'un pointeur de chaine */
   T_str8 l_str = p_str;

   /* Si le paramètre est valide */
   if ( p_str != K_MK_NULL )
   {
      /* Récupération de la valeur du premier caractère de la chaine */
      l_str = mk_font_parseString ( p_str, &l_currentChar, p_font );

      /* Tant que la chaine de caractères n'a pas été entièrement analysée */
      while ( ( l_currentChar != 0x00 ) && ( p_index != l_counter ) )
      {
         /* Actualisation du nombre de caractères */
         l_counter = ( uint32_t ) ( l_counter + 1 );

         /* Actualisation du pointeur de chaine */
         p_str = l_str;

         /* Récupération de la valeur du prochain caractère à analyser */
         l_str = mk_font_parseString ( p_str, &l_currentChar, p_font );
      }

      /* Récupération de la taille du caractère */
      *p_length = ( uint32_t ) ( l_str - p_str );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( p_str );
}




