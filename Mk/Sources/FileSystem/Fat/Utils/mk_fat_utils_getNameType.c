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
* @file mk_fat_utils_getNameType.c
* @brief Définition de la fonction mk_fat_utils_getNameType.
* @date 3 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkFATEntryType mk_fat_utils_checkNameType ( T_str8 p_str, uint32_t* p_offset, uint32_t p_maxLength )
{
   /* Déclaration de la variable de retour */
   T_mkFATEntryType l_result = K_MK_FAT_ENTRY_ST;

   /* Déclaration des variable de travail */
   uint32_t l_counter = 0, l_uppercase = 0, l_lowercase = 0, l_currentChar = 0;

   /* Effectue */
   do
   {
      /* Récupération de la valeur du prochain caractère de la chaine */
      p_str = mk_font_parseString ( p_str, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

      /* Si le caractère courant est en majuscule */
      if ( ( l_currentChar >= 'A' ) && ( l_currentChar <= 'Z' ) )
      {
         /* Actualisation du nombre de caractères majuscules */
         l_uppercase = ( uint32_t ) ( l_uppercase + 1 );
      }

      /* Sinon si le caractère courant est en minuscule */
      else if ( ( l_currentChar >= 'a' ) && ( l_currentChar <= 'z' ) )
      {
         /* Actualisation du nombre de caractères minuscules */
         l_lowercase = ( uint32_t ) ( l_lowercase + 1 );
      }

      /* Sinon si le caractère courant est de type étendu */
      else if ( l_currentChar > '~' )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_FAT_ENTRY_EX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la variable de comptage */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Tant que la chaine n'a pas été parcourue ou tant que la chaine est de type standard */
   while ( ( l_result == K_MK_FAT_ENTRY_ST ) && ( l_currentChar != '\0' ) && ( l_currentChar != '.' ) );

   /* Si des majuscules et des minuscules sont présentes dans la chaine */
   if ( ( ( l_uppercase > 0 ) && ( l_lowercase > 0 ) ) || ( l_counter > p_maxLength ) )
   {
      /* Actualisation de la variable de retour */
      /* L'entrée est étendue */
      l_result = K_MK_FAT_ENTRY_EX;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation de l'offset de la prochaine chaine à analyser */
   *p_offset = ( l_counter + 1 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_getNameType ( T_str8 p_fileName, T_mkFATEntryType* p_nameType )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour local */
   T_mkFATEntryType l_local = K_MK_FAT_ENTRY_ST;

   /* Déclaration des variables de travail */
   uint32_t l_dotCount = 0, l_extensionOffset = 0;

   /* Si les paramètres sont valides */
   if ( ( p_fileName != K_MK_NULL ) && ( p_nameType != K_MK_NULL ) )
   {
      /* Détermination du nombre de caractères '.' dans le nom du fichier */
      l_dotCount = mk_utils_utfcount ( p_fileName, '.', K_MK_FONT_UTF8 );

      /* Si au moins 2 caractères '.' sont présents */
      if ( l_dotCount > 1 )
      {
         /* Actualisation de la variable de retour */
         /* L'entrée est étendue */
         l_local = K_MK_FAT_ENTRY_EX;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la chaine n'est pas de type étendue */
      if ( l_local == K_MK_FAT_ENTRY_ST )
      {
         /* Analyse du nom du fichier */
         l_local = mk_fat_utils_checkNameType ( &p_fileName [ 0 ], &l_extensionOffset, K_MK_FAT_ENTRY_NAME_SIZE );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la chaine n'est pas de type étendue */
      if ( l_local == K_MK_FAT_ENTRY_ST )
      {
         /* Si une extension est présente dans le nom du fichier */
         if ( l_dotCount == 1 )
         {
            /* Analyse du nom du fichier */
            l_local = mk_fat_utils_checkNameType ( &p_fileName [ l_extensionOffset ], &l_extensionOffset, K_MK_FAT_ENTRY_EXTENSION_SIZE );
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

      /* Actualisation de la variable de retour */
      ( *p_nameType ) = l_local;
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


