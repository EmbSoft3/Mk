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
* @file mk_utils_strsplit.c
* @brief Définition de la fonction mk_utils_strsplit.
* @date 26 déc. 2020
*
*/

#include "mk_utils_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_utils_strsplit ( T_str8 p_str, T_str8 p_result, uint16_t p_index, uint8_t p_delimiter )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_counter = 0, l_numberOfDelimiter = 0;

   /* Si le paramètre est valide */
   if ( ( p_str != K_MK_NULL ) && ( p_result != K_MK_NULL ) )
   {
      /* Récupération de la longueur de la chaine de caractères */
      l_length = mk_utils_strlen ( p_str );

      /* Si aucune erreur ne s'est produite */
      if ( l_length != 0 )
      {
         /* Récupération du nombre d'occurences du séparateur */
         l_numberOfDelimiter = mk_utils_strcount ( p_str, p_delimiter );

         /* Si au moins un séparateur est présent */
         if ( l_numberOfDelimiter != 0 )
         {
            /* Si l'index demandé par l'utilisateur est conforme */
            if ( p_index <= l_numberOfDelimiter )
            {
               /* Tant que l'index de la chaine à récupérer n'a pas été atteint */
               while ( p_index != 0 )
               {
                  /* Tant que le compteur de caractères n'est pas à l'index recherché */
                  while ( p_str [ l_counter++ ] != p_delimiter )
                  {
                     /* Ne rien faire */
                  }

                  /* Actualisation du nombre de séparateur */
                  p_index = ( uint16_t ) ( p_index - 1 );
               }

               /* Tant que la chaine à récupérer n'a pas été entièrement copiée */
               while ( ( p_str [ l_counter ] != p_delimiter ) && ( p_str [ l_counter] != 0 ) )
               {
                  /* Copie du caractère courant */
                  *p_result = p_str [ l_counter ];

                  /* Actualisation des variables */
                  p_result++;
                  l_counter++;
               }

               /* Ajout du caractère de fin de chaine */
               *p_result = 0;
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = 0;
            }
         }

         /* Sinon */
         else
         {
            /* Si le premier index doit être récupéré */
            if ( p_index == 0 )
            {
               /* Copie de la chaine entrante dans la chaine sortante */
               /* Un caractère est ajouté pour copier le caractère de fin de chaine. */
               _copy ( p_result, p_str, ( uint32_t ) ( l_length + 1 ) );
            }

            /* Sinon */
            else
            {
               /* Insertion d'un caractère indiquant la fin de chaine */
               p_result [ 0 ] = 0;
            }
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
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




