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
* @file mk_utils_strcomp.c
* @brief Définition de la fonction mk_utils_strcomp.
* @date 28 mai 2020
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_utils_charcomp ( int8_t p_char1, int8_t p_char2, uint32_t p_bypass )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Si la casse doit être ignorée */
   if ( p_bypass > 0 )
   {
      /* Si le caractère 1 est en minuscule */
      if ( ( p_char1 >= 'a' ) && ( p_char1 <= 'z' ) )
      {
         /* Conversion du caractère en majuscule */
         p_char1 = ( int8_t ) ( p_char1 & 0xDF );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le caractère 1 est en minuscule */
      if ( ( p_char2 >= 'a' ) && ( p_char2 <= 'z' ) )
      {
         /* Conversion du caractère en majuscule */
         p_char2 = ( int8_t ) ( p_char2 & 0xDF );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si les caractères courant sont différents */
   if ( p_char1 != p_char2 )
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_strcomp ( T_str8 p_str1, T_str8 p_str2, uint32_t p_bypass, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_str1 != K_MK_NULL ) && ( p_str2 != K_MK_NULL ) )
   {
      /* Si la comparaison doit s'arrêter sur la fin de chaine */
      if ( p_length == 0 )
      {
         /* Tant que les chaines de caractères n'ont pas été parcourues */
         while ( ( ( *p_str1 ) != '\0' ) && ( ( *p_str2 ) != '\0' ) && ( l_result == 1 ) )
         {
            /* Réalisation de la comparaison des chaines */
            l_result = mk_utils_charcomp ( ( *p_str1 ), ( *p_str2 ), p_bypass );

            /* Actualisation des pointeurs */
            p_str1++;
            p_str2++;
         }

         /* Si les longueurs des chaines de caractères sont différentes */
         if ( ( l_result == 1 ) && ( ( *p_str1 ) != ( *p_str2 ) ) )
         {
            /* Actualisation de la variable de retour */
            l_result = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon, la comparaison s'effectue sur un nombre de caractères précis */
      else
      {
         /* Pour le nombre de caractères à comparer */
         for ( l_counter = 0 ; ( l_counter < p_length ) && ( l_result == 1 ) ; l_counter++ )
         {
            /* Réalisation de la comparaison des chaines */
            l_result = mk_utils_charcomp ( ( *p_str1 ), ( *p_str2 ), p_bypass );

            /* Actualisation des pointeurs */
            p_str1++;
            p_str2++;
         }
      }
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




