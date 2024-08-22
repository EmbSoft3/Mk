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
* @file mk_utils_getRandomString.c
* @brief Définition de la fonction mk_utils_getRandomString.
* @date 13 août 2024
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

int32_t mk_utils_getRandomString ( T_str8 p_randomString, T_str8 p_prefix, T_str8 p_suffix )
{
   /* Déclaration de la variable de retour */
   int32_t l_result = 0;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'un ensemble de variables contenant les nombres aléatoires brutes */
   /* et leurs conversions en ASCII */
   char8_t  l_randString [ 4 ] [ 9 ] = { { 0 } };
   uint32_t l_randNumber [ 4 ] = { 0, 0, 0, 0 };

   /* Pour le nombre de données aléatoires à générer */
   for ( l_counter = 0 ; ( l_counter < 4 ) && ( l_result != ( -2 ) ) ; l_counter++ )
   {
      /* Effectue */
      do
      {
         /* Récupération d'un nombre aléatoire */
         l_result = mk_utils_rand ( &l_randNumber [ l_counter ] );

      /* Tant que la conversion n'est pas terminée et tant qu'aucune erreur ne s'est produite */
      } while ( l_result == ( -3 ) );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == 0 )
   {
      /* Conversion des nombres aléatoires en chaine de caractères */
      ( void ) mk_utils_itoa ( l_randNumber [ 0 ], ( T_str8 ) &l_randString [ 0 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 1 ], ( T_str8 ) &l_randString [ 1 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 2 ], ( T_str8 ) &l_randString [ 2 ] [ 0 ], 16, 8 );
      ( void ) mk_utils_itoa ( l_randNumber [ 3 ], ( T_str8 ) &l_randString [ 3 ] [ 0 ], 16, 8 );

      /* Création de la chaine de caractères de sortie */
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomString, ( T_str8 ) p_prefix, ( T_str8 ) &l_randString [ 0 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomString, ( T_str8 ) p_randomString, ( T_str8 ) &l_randString [ 1 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomString, ( T_str8 ) p_randomString, ( T_str8 ) &l_randString [ 2 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomString, ( T_str8 ) p_randomString, ( T_str8 ) &l_randString [ 3 ] [ 0 ] );
      ( void ) mk_utils_strcat ( ( T_str8 ) p_randomString, ( T_str8 ) p_randomString, ( T_str8 ) p_suffix );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


