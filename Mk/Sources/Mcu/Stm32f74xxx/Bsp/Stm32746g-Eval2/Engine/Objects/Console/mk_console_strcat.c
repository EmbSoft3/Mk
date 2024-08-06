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
* @file mk_console_strcat.c
* @brief Définition de la fonction mk_console_strcat.
* @date 12 mars 2023
* @todo Analyser si l'attribut cursorBaseOffset peut être utilisé car la valeur
*       de celui-ci peut évoluer lors d'un clic ou d'un scrolling de la souris.
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_strcat ( T_mkConsole* p_console, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères */
   uint32_t l_length = 0;

   /* Récupération de l'adresse de la chaine de caractères */
   T_str8 l_baseAddr = p_console->foreground.window.strAddr;

   /* Si les paramètres sont valides */
   if ( ( p_console != K_MK_NULL ) && ( p_console->semaphore != K_MK_NULL ) && ( p_str != K_MK_NULL ) )
   {
      /* Récupération de la longueur de la chaine de caractères */
      l_length = mk_utils_utfsize ( p_str, p_console->foreground.window.style.fontEncoding );

      /* Si la longueur de la chaine est invalide */
      if ( l_length == 0 )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Sinon, si la chaine de caractères peut être concaténée dans le buffer */
      else if ( ( p_console->foreground.window.cursorBaseOffset + l_length ) < ( uint32_t ) ( p_console->window.bufSize - 1 ) )
      {
         /* Réalisation de la copie */
         /* On utilise cursorBaseOffset car la fenêtre est protégée en écriture */
         _copy ( &l_baseAddr [ p_console->foreground.window.cursorBaseOffset ], p_str, l_length );

         /* Actualisation de l'adresse du prochain caractère à stocker */
         /* Cette fonction peut être exécutée en parallèle du painter (pas besoin d'allouer une section critique) */
         p_console->foreground.window.cursorBaseOffset += l_length;
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_FULL;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


