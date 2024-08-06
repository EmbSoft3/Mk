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
* @file mk_utils_atoi.c
* @brief Définition de la fonction mk_utils_atoi.
* @date 24 févr. 2024
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

int32_t mk_utils_atoi ( T_str8 p_buf, uint32_t p_base )
{
   /* Déclaration de la variable de retour */
   int32_t l_result = 0;

   /* Déclaration des variables de travail */
   int32_t l_sign = 1;
   uint32_t l_length = 0, l_counter = 0, l_index = 0, l_digit = 0, l_multiplier = 1;

   /* Si les paramètres sont valides */
   if ( ( p_buf != K_MK_NULL ) && ( p_base != 0 ) )
   {
      /* Récupération de la taille de la chaine de caractères */
      l_length = mk_utils_strlen ( p_buf );

      /* Si le nombre à convertir est un nombre négatif */
      if ( ( p_buf [ 0 ] == '-' ) && ( l_length > 0 ) )
      {
         /* Actualisation du signe */
         l_sign = ( -1 );

         /* Actualisation des variables de travail */
         p_buf++; l_length--;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Conversion de la chaine de caractères en entier */
      /* Pour le nombre de digits à traiter */
      for ( l_counter = 0 ; l_counter < l_length ; l_counter++ )
      {
         /* Détermination de la valeur de l'index */
         l_index = ( uint32_t ) ( l_length - l_counter - 1 );

         /* Conversion du caractère courant en entier */
         /* Si caractère numérique */
         if ( ( p_buf [ l_index ] >= '0' ) && ( p_buf [ l_index ] <= '9' ) )
         {
            l_digit = ( p_buf [ l_index ] - '0' ) & 0xF;
         }

         /* Sinon si caractère alphanumérique */
         else if ( p_buf [ l_index ] >= 'A' )
         {
            l_digit = ( 10 + ( p_buf [ l_index ] - 'A' ) ) & 0xF;
         }

         /* Sinon */
         else
         {
            l_digit = 0;
         }

         /* Actualisation du résultat */
         l_result = l_result + ( int32_t ) l_digit * ( int32_t ) l_multiplier;
         l_multiplier = ( uint32_t ) ( l_multiplier * p_base );
      }

      /* Conversion du nombre en entier négatif si nécessaire */
      l_result = ( int32_t ) ( l_sign * l_result );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

