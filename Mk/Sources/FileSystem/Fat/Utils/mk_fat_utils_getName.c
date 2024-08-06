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
* @file mk_fat_utils_getName.c
* @brief Définition de la fonction mk_fat_utils_getName.
* @date 30 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_copyST ( uint8_t* p_entry, T_str8 p_str, uint32_t p_offset, uint32_t p_length, uint32_t p_case )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0;

   /* Déclaration d'un pointeur d'entrée */
   T_mkFATEntryDescriptor* l_entry = ( T_mkAddr ) p_entry;

   /* Pour la longueur de la chaine de caractères */
   for ( l_counter = 0 ; l_counter < p_length ; l_counter++ )
   {
      /* Si le caractère courant est en majuscule et si l'octet de casse est actif */
      if ( ( p_entry [ p_offset + l_counter ] >= 'A' ) && ( p_entry [ p_offset + l_counter ] <= 'Z' ) &&
         ( ( l_entry->caseType & p_case ) > 0 ) )
      {
         /* Conversion en minuscule */
         p_str [ l_counter ] = ( int8_t ) ( p_entry [ p_offset + l_counter ] | 0x20 );
      }

      /* Sinon */
      else
      {
         p_str [ l_counter ] = ( int8_t ) ( p_entry [ p_offset + l_counter ] );
      }
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_fat_utils_getExtensionST ( uint8_t* p_entry, T_str8 p_fileExtension )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_offset = 1;

   /* Récupération de l'extension du fichier */
   mk_fat_utils_copyST ( p_entry, p_fileExtension, K_MK_FAT_ENTRY_NAME_SIZE, K_MK_FAT_ENTRY_EXTENSION_SIZE, K_MK_FAT_EXTENSION_LOWER_CASE_FLAG );

   /* Détermination de l'offset de fin de la chaine */
   for ( l_counter = 1 ; l_counter < ( K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ) ; l_counter++ )
   {
      /* Si le caractère courant n'est pas le dernier caractère du nom */
      if ( p_fileExtension [ K_MK_FAT_ENTRY_EXTENSION_SIZE - l_offset ] == ' ' )
      {
         /* Actualisation de l'indice du caractère analysé */
         l_offset = ( uint32_t ) ( l_offset + 1 );
      }

      /* Sinon */
      else
      {
         /* Arrêt de la boucle */
         l_counter = K_MK_FAT_ENTRY_EXTENSION_SIZE;
      }
   }

   /* Ajout du caractère de fin */
   p_fileExtension [ K_MK_FAT_ENTRY_EXTENSION_SIZE - ( l_offset - 1 ) ] = 0;

   /* Détermination de la longueur de la chaine de caractères */
   l_result = mk_utils_strlen ( p_fileExtension );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_getNameST ( uint8_t* p_entry, T_str8 p_fileName )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_offset = 1, l_length = 0;

   /* Déclaration d'un buffer stockant l'extension */
   uint8_t l_fileExtension [ K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ];

   /* Récupération du nom du fichier */
   mk_fat_utils_copyST ( p_entry, p_fileName, 0, K_MK_FAT_ENTRY_NAME_SIZE, K_MK_FAT_NAME_LOWER_CASE_FLAG );

   /* Détermination de l'offset de fin de la chaine */
   for ( l_counter = 1 ; ( l_counter < K_MK_FAT_ENTRY_NAME_SIZE + 1 ) ; l_counter++ )
   {
      /* Si le caractère courant n'est pas le dernier caractère du nom */
      if ( p_fileName [ K_MK_FAT_ENTRY_NAME_SIZE - l_offset ] == ' ' )
      {
         /* Actualisation de l'indice du caractère analysé */
         l_offset = ( uint32_t ) ( l_offset + 1 );
      }

      /* Sinon */
      else
      {
         /* Arrêt de la boucle */
         l_counter = K_MK_FAT_ENTRY_NAME_SIZE;
      }
   }

   /* Récupération de l'extension du fichier */
   l_length = mk_fat_utils_getExtensionST ( p_entry, ( T_str8 ) l_fileExtension );

   /* Si le fichier n'est pas un répertoire */
   if ( l_length != 0 )
   {
      /* Concaténation des chaines de caractères */
      ( void ) mk_utils_strcat ( &p_fileName [ K_MK_FAT_ENTRY_NAME_SIZE - ( l_offset - 1 ) ], ( T_str8 ) ".", ( T_str8 ) l_fileExtension );

      /* Actualisation de la longueur de la chaine (caractère '.') */
      l_length = ( uint32_t ) ( l_length + 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le premier caractère de la chaine est le caractère $05 */
   if ( p_fileName [ 0 ] == K_MK_FAT_E5_ENTRY )
   {
      /* Restitution du caractère d'origine */
      p_fileName [ 0 ] = ( int8_t ) K_MK_FAT_DELETED_ENTRY;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Ajout du caractère de fin */
   p_fileName [ ( K_MK_FAT_ENTRY_NAME_SIZE - ( l_offset - 1 ) ) + l_length ] = '\0';

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_getNameEX ( uint8_t* p_entry, T_str8 p_fileName )
{
   /* Déclaration d'un tableau contenant l'offset des caractères dans l'entrée */
   uint8_t l_location [ K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY ] = { 1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30 };

   /* Déclaration d'une variable stockant la valeur du caractère UTF-16 */
   uint32_t l_utfValue = 0;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_index = 0, l_length = 0;

   /* Pour le nombre de caractères dans l'entrée */
   for ( l_counter = 0 ; l_counter < K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY ; l_counter++ )
   {
      /* Si la chaine de caractères est terminée */
      if ( ( uint8_t ) p_entry [ l_location [ l_counter ] ] == K_MK_FAT_EXTENDED_PADDING )
      {
         /* Remplacement du caractère courant par le caractère de fin de chaine */
         p_fileName [ l_index ] = '\0';
      }

      /* Sinon */
      else
      {
         /* Récupération du caractère UTF-16 */
         l_utfValue  = ( uint32_t )  p_entry [ l_location [ l_counter ] ];
         l_utfValue |= ( ( uint32_t ) p_entry [ l_location [ l_counter ] + 1 ] << 8 );

         /* Conversion du caractère UTF-16 en UTF-8 */
         l_utfValue = mk_utils_utf16ToUtf32 ( l_utfValue );
         l_utfValue = mk_utils_codeToUtf8 ( l_utfValue );

         /* Ecriture du caractère UTF-8 dans la chaine */
         mk_utils_codeToString ( l_utfValue, ( T_str8 ) &p_fileName [ l_index ], K_MK_FONT_UTF8 );

         /* Récupération de la longueur du caractère écrit dans la chaine */
         mk_utils_utfget ( &p_fileName [ l_index ], 0, K_MK_FONT_UTF8, &l_length );

         /* Actualisation de l'offset du prochain caractère dans la chaine */
         l_index = ( uint32_t ) ( l_index + l_length );
      }
   }

   /* Ajout du caractère de fin */
   p_fileName [ l_index ] = '\0';

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_getName ( T_mkFATEntryDescriptor* p_entry, T_str8 p_fileName, T_mkFATEntryType p_type )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_entry != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) )
   {
      /* Si le nom d'une entrée au format 8.3 doit être lu */
      if ( p_type == K_MK_FAT_ENTRY_ST )
      {
         /* Récupération d'un nom de l'entrée */
         mk_fat_utils_getNameST ( ( uint8_t* ) p_entry, p_fileName );
      }

      /* Sinon si le nom d'une entrée étendue doit être lu */
      else if ( p_type == K_MK_FAT_ENTRY_EX )
      {
         /* Récupération d'un nom de l'entrée */
         mk_fat_utils_getNameEX ( ( uint8_t* ) p_entry, p_fileName );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}
