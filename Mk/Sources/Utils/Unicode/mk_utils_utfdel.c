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
* @file mk_utils_utfdel.c
* @brief Définition de la fonction mk_utils_utfdel.
* @date 26 déc. 2022
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_utfdel ( T_str8 p_str, uint32_t p_index, uint32_t p_encoding )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = p_str;

   /* Déclaration des compteurs */
   uint32_t l_counter = 0, l_utfCounter = 0;

   /* Déclaration d'une variable stockant la valeur du prochain caractère unicode */
   uint32_t l_currentChar = 0;

   /* Déclaration d'une variable stockant la taille du caractère unicode */
   uint32_t l_length = 0;

   /* Si le paramètre est valide */
   if ( p_str != K_MK_NULL )
   {
      /* Effectue */
      do
      {
         /* Récupération de la valeur du prochain caractère de la chaine */
         l_str = mk_font_parseString ( p_str, &l_currentChar, p_encoding );

         /* Si index de suppression a été atteint */
         if ( l_counter >= p_index )
         {
            /* Détermination de la longueur du prochain caractère */
            l_length = ( uint32_t ) l_str - ( uint32_t ) p_str;

            /* Pour le nombre d'octets à copier dans la chaine (0 pour le  premier cas) */
            for ( l_utfCounter = 0 ; l_utfCounter < l_length ; l_utfCounter++  )
            {
               /* Décalage des caractères de la chaine */
               p_str [ l_utfCounter ] = l_str [ l_utfCounter ];
            }

            /* Actualisation de l'index */
            p_index = ( uint32_t ) ( p_index + 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du compteur */
         l_counter = ( uint32_t ) ( l_counter + 1 );

         /* Actualisation du pointeur de chaine */
         p_str = l_str;

      /* Tant que l'intégralité de la chaine n'a pas été parcourue */
      } while ( l_currentChar != 0 );
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




