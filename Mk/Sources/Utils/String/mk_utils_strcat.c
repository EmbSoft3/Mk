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
* @file mk_utils_strcat.c
* @brief Définition de la fonction mk_utils_strcat.
* @date 27 déc. 2020
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_strcat ( T_str8 p_str, T_str8 p_str1, T_str8 p_str2 )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration des variables de travail */
   int32_t l_counter = 0, l_offset1 = 0, l_offset2 = 0;

   /* Si le paramètre est valide */
   if ( ( p_str != K_MK_NULL ) && ( p_str1 != K_MK_NULL ) && ( p_str2 != K_MK_NULL ) )
   {
      /* Tant que la première chaine n'a pas été entièrement copiée */
      while ( p_str1 [ l_offset1 ] != 0 )
      {
         /* Copie de la première chaine de caractères */
         p_str [ l_counter ] = p_str1 [ l_offset1 ];

         /* Actualisation des variables */
         l_counter++;
         l_offset1++;
      }

      /* Tant que la seconde chaines n'a pas été entièrement copiée */
      while ( p_str2 [ l_offset2 ] != 0 )
      {
         /* Copie de la deuxième chaine de caractères */
         p_str [ l_counter ] = p_str2 [ l_offset2 ];

         /* Actualisation des variables */
         l_counter++;
         l_offset2++;
      }

      /* Ajout du caractère de fin de chaine */
      p_str [ l_counter ] = 0;
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Retour */
   return ( l_result );
}


