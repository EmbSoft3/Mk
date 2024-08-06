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
* @file mk_utils_utfsize.c
* @brief Définition de la fonction mk_utils_utfsize.
* @date 12 mars 2023
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_utfsize ( T_str8 p_str, uint32_t p_encoding )
{
   /* Déclaration des variable de travail */
   uint32_t l_currentChar = 0, l_length = 0;

   /* Déclaration des pointeurs de chaines */
   T_str8 l_str = p_str, l_next = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( p_str != K_MK_NULL )
   {
      /* Récupération de la valeur du premier caractère de la chaine */
      l_next = mk_font_parseString ( p_str, &l_currentChar, p_encoding );

      /* Tant que la chaine de caractères n'a pas été entièrement parcourue */
      while ( l_currentChar != 0x00 )
      {
         /* Actualisation des pointeurs */
         l_str = l_next;

         /* Récupération de la valeur du premier caractère de la chaine */
         l_next = mk_font_parseString ( l_str, &l_currentChar, p_encoding );
      }

      /* Détermination de la taille de la chaine de caractères */
      l_length = ( uint32_t ) ( l_str - p_str );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_length = 0;
   }

   /* Retour */
   return ( l_length );
}


