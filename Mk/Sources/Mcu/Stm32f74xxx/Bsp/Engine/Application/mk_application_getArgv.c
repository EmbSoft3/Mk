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
* @file mk_application_getArgv.c
* @brief Définition de la fonction mk_application_getArgv.
* @date 23 févr. 2024
*
*/

#include "mk_engine_api.h"


/**
 * @internal
 * @brief
 * @endinternal
 */


T_mkCode mk_application_getArgv ( T_str8 p_chain, T_str8* p_nextChain, T_str8 p_arg, uint32_t p_argLength, T_mkFontUnicode p_fontEncoding )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de chaines de caractères */
   T_str8 l_startAddr = p_chain, l_previous = p_chain;

   /* Déclaration d'une variable stockant la valeur du caractère courant, d'une variable permettant  */
   /* de filtrer les espaces entre guillements et d'une variable de comptage */
   uint32_t l_currentChar = 0, l_bypass = 0, l_length = 0, l_utfNull = 0, l_utfCount = 0;

   /* Si les paramètres sont valides */
   if ( ( p_chain != K_MK_NULL ) && ( ( p_arg != K_MK_NULL ) || ( p_argLength == 0 ) ) )
   {
      /* Récupération de la valeur du prochain caractère de la chaine. */
      ( void ) mk_font_parseString ( p_chain, &l_currentChar, ( uint32_t ) p_fontEncoding );

      /* Si la chaine de caractères est terminée */
      if ( l_currentChar == 0 )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_AVAILABLE;
      }

      /* Sinon */
      else
      {
         /* Effectue */
         do
         {
            /* Actualisation du pointeur de chaine */
            l_previous = p_chain;

            /* Récupération de la valeur du prochain caractère de la chaine. */
            p_chain = mk_font_parseString ( l_previous, &l_currentChar, ( uint32_t ) p_fontEncoding );

            /* Si un autre caractère '"' est présent */
            if ( l_currentChar == '"' )
            {
               /* Commutation de la variable de bypass */
               l_bypass = ( uint32_t ) ( ( ~l_bypass ) & 0x01 );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

         /* Tant que les caractères ' ' ou '\0' n'ont pas été rencontré */
         } while ( ( ( l_currentChar != ' ' ) || ( l_bypass == 1 ) ) && ( l_currentChar != 0 ) );

         /* Actualisation de la variable de retour */
         *p_nextChain = l_previous;

         /* Si l'argument doit être récupéré */
         if ( p_argLength != 0 )
         {
            /* Récupération de la longueur de l'argument */
            l_length = ( uint32_t ) p_chain - ( uint32_t ) l_startAddr - 1;
            l_utfCount = mk_utils_utfnull ( p_fontEncoding );

            /* Si le buffer utilisateur ne peut pas stocker l'intégralité de l'argument */
            if ( ( l_length + l_utfCount ) <= p_argLength )
            {
               /* Copie d'une partie de l'argument dans le buffer utilisateur */
               _copy ( p_arg, l_startAddr, l_length );

               /* Copie du caractère de fin */
               _copy ( &p_arg [ l_length ], &l_utfNull, l_utfCount );
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_PARAM;
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* On regarde si les plusieurs caractères ' ' consécutifs sont présents */
         /* On les supprime pour qu'il ne soit pas présent lors du prochain appel de la fonction. */
         while ( l_currentChar == ' ' )
         {
            /* Actualisation de la variable de retour */
             *p_nextChain = p_chain;

            /* Récupération de la valeur du prochain caractère de la chaine. */
            p_chain = mk_font_parseString ( p_chain, &l_currentChar, ( uint32_t ) p_fontEncoding );
         }
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

