/**
*
* @copyright Copyright (C) 2018 RENARD Mathieu. All rights reserved.
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
* @file mk_utils_itoa.c
* @brief Définition de la fonction mk_utils_itoa.
* @date 14 oct. 2018
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_str8 mk_utils_itoa ( uint32_t p_number, T_str8 p_result, uint8_t p_base, uint8_t p_digit )
{
   /* Déclaration des variables de travail */
   uint32_t l_offset = 0;
   uint32_t l_remainder = 0;

   /* Si l'entier à convertir est nul */
   if ( p_number == 0 )
   {
      /* Gestion de la valeur nulle */
      p_result [ l_offset++ ] = '0';
   }

   /* Sinon */
   else
   {
      /* Conversion des digits en ASCII tant que le nombre n'est pas nul */
      while ( p_number != 0 )
      {
         /* Actualisation du reste */
         l_remainder = p_number % p_base;

         /* Si le reste est supérieur à 9 */
         if ( l_remainder > 0x09 )
         {
            /* Ecriture du caractère */
            p_result [ l_offset++ ] = ( int8_t ) ( 'a' + ( l_remainder - 0x0A ) );
         }

         /* Sinon */
         else
         {
            /* Ecriture du chiffre */
            p_result [ l_offset++ ] = ( int8_t ) ( '0' + l_remainder ) ;
         }

         /* Actualisation du nombre à convertir */
         p_number = p_number / p_base;
      }
   }

   /* Pour le nombre de digit à afficher */
   for ( ; l_offset < p_digit ; l_offset++ )
   {
      /* Ecriture des digits de poids fort */
      p_result [ l_offset ] = '0';
   }

   /* Permutation de la chaine */
   mk_utils_reverse ( p_result, l_offset );

   /* Ajout du caractère de délimitation */
   p_result [ l_offset ] = '\0';

   /* Retour */
   return ( p_result );
}




