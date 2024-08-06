/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_fat_utils_checkInvalidName.c
* @brief Définition de la fonction mk_fat_utils_checkInvalidName.
* @date 4 sept. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_checkInvalidName ( T_str8 p_filePath )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_utf16 = 0;
   uint32_t l_counter = 0, l_charCounter = 0, l_currentChar = 0;

   /* Déclaration d'un buffer contenant les caractères invalides */
   uint8_t l_buf [ 8 ] = { '\\', ':', '*', '?', '"', '<', '>', '|' };

   /* Effectue */
   do
   {
      /* Récupération de la valeur du prochain caractère de la chaine */
      p_filePath = mk_font_parseString ( p_filePath, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );
      /* Conversion du point de codage en UTF-16 */
      l_utf16 = mk_utils_codeToUtf16 ( l_currentChar );

      /* Si le caractère est incompatible avec le système de fichiers */
      if ( l_utf16 > 0xFFFF )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Pour le nombre de caractères invalides à analyser */
      for ( l_charCounter = 0 ; l_charCounter < 8 ; l_charCounter++ )
      {
         if ( l_currentChar == l_buf [ l_charCounter ] )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Actualisation du compteur */
      l_counter++;
   }

   /* Tant que l'analyse de la chaine n'est pas terminée */
   while ( ( l_counter < K_MK_FILE_MAX_NAME_LENGTH ) && ( l_currentChar != '\0' ) && ( l_result == K_MK_OK ) );

   /* Si la chaine de caractères est trop longue */
   if ( ( l_counter > K_MK_FILE_MAX_NAME_LENGTH ) || ( l_counter == 0 ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}
