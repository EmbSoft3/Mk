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
* @file mk_fat_utils_setName.c
* @brief Définition de la fonction mk_fat_utils_setName.
* @date 27 déc. 2020
* @todo Modifier l'algorithme de la fonction mk_fat_utils_ckecksum16bits.
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_toUpperCase ( T_str8 p_str, uint8_t p_maxSize, uint8_t p_mode, uint8_t* p_caseType )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter;

   /* Pour le nombre de caractères dans la chaine */
   for ( l_counter = 0 ; l_counter < p_maxSize ; l_counter++ )
   {
      /* Si la chaine de caractères est en minuscule */
      if ( ( ( uint8_t ) p_str [ l_counter ] >= 'a' ) && ( ( uint8_t ) p_str [ l_counter ] <= 'z' ) )
      {
         /* Conversion en majuscule */
         p_str [ l_counter ] = ( int8_t ) ( p_str [ l_counter ] & 0xDF );

         /* Actualisation du type de casse */
         *p_caseType |= ( uint8_t ) ( ( *p_caseType ) | p_mode );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la longueur de la chaine est inférieure à la longueur maximale */
      if ( p_str [ l_counter ] == '\0' )
      {
         /* Ajout d'un caractère espace dans le nom */
         p_str [ l_counter ] = ( int8_t ) ' ';
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
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

static void mk_fat_utils_16bToASCII ( uint16_t p_value, T_str8 p_str, uint8_t* p_length )
{
   /* Déclaration des variables de travail */
   uint32_t l_counter, l_char;

   /* Conversion en chaine de caractères */
   for ( l_counter = 0 ; l_counter < 4 ; l_counter++ )
   {
      /* Récupération de la valeur du caractère courant */
      l_char = ( p_value >> ( ( 3 - l_counter ) << 2 ) ) & 0x0F;

      /* Si caractère est entre 10 et 15 */
      if ( l_char > 0x09 )
      {
         /* Conversion en chaine de caractères (digit [A-F]) */
         p_str [ l_counter ] = ( int8_t ) ( l_char + 0x37 );
      }

      /* Sinon */
      else
      {
         /* Conversion en chaine de caractères (digit [0-9]) */
         p_str [ l_counter ] = ( int8_t ) ( l_char + 0x30 );
      }
   }

   /* Si la longueur de la chaine de caractères doit être récupérée */
   if ( p_length != K_MK_NULL )
   {
      /* Si la chaine est sur 4 caractères */
      if ( ( p_value & 0xF000 ) != 0 )
      {
         /* Actualisation de la longueur de la chaine */
         *p_length = 4;
      }

      /* Sinon si la chaine est sur 3 caractères */
      else if ( ( p_value & 0x0F00 ) != 0 )
      {
         /* Actualisation de la longueur de la chaine */
         *p_length = 3;
      }

      /* Sinon si la chaine est sur 2 caractères */
      else if ( ( p_value & 0x00F0 ) != 0 )
      {
         /* Actualisation de la longueur de la chaine */
         *p_length = 2;
      }

      /* Sinon si la chaine est sur 2 caractères */
      else if ( ( p_value & 0x000F ) != 0 )
      {
         /* Actualisation de la longueur de la chaine */
         *p_length = 1;
      }

      /* Sinon */
      else
      {
         /* Actualisation de la longueur de la chaine */
         *p_length = 0;
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_ckecksum8bits ( T_str8 p_str, uint8_t* p_checksum )
{
   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Déclaration d'une variable stockant la valeur du checksum */
   uint8_t l_checksum = 0;

   /* Pour les 11 caractères du nom de fichier */
   for ( l_counter = 0 ; l_counter < ( K_MK_FAT_ENTRY_EXTENSION_SIZE + K_MK_FAT_ENTRY_NAME_SIZE ) ; l_counter++ )
   {
      l_checksum = ( uint8_t ) ( ( ( l_checksum & 0x1 ) << 7 ) + ( l_checksum >> 1 ) + ( uint8_t ) ( *p_str ) );
      p_str++;
   }

   /* Actualisation de la variable de retour */
   *p_checksum = l_checksum;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_ckecksum16bits ( T_str8 p_str, T_str8 p_checksum )
{
   /* Ce CRC est utilisé lors de la détermination d'un nom de fichiers court. */
   /* Il n'y a aucune contrainte, l'algorithme peut être modifié si nécessaire. Notamment pour en trouver un qui est beaucoup plus optimisé. */

   /* Déclaration des variables de travail */
   uint16_t l_checksum = 0;
   int32_t  l_tmp = 0;
   uint32_t l_currentChar = 0;

   /* Effectue */
   do
   {
      /* Récupération de la valeur du prochain caractère de la chaine */
      p_str = mk_font_parseString ( p_str, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

      /* Génération de la valeur initiale du checksum */
      l_checksum = ( uint16_t ) ( ( l_checksum * 0x25 ) + ( uint16_t ) l_currentChar );
   }

   /* Tant que la chaine de caractères n'a pas été entièrement parcourue ou tant que le travail n'est pas terminé */
   while ( l_currentChar != 0 );

   /* Initialisation de la variable temporaire */
   l_tmp = l_checksum * 314159269;

   /* Récupération de la valeur absolue */
   /* Mis en commentaire suite à warning [-Wstrict-overflow] */
   /*
   if ( l_tmp < 0 )
   {
      l_tmp = ( -1 ) * l_tmp;
   }
   */

   /* Génération du checksum */
   l_checksum = ( uint16_t ) ( ( uint64_t ) l_tmp - ( ( uint64_t ) ( ( int64_t ) l_tmp * 1152921497 ) >> 60 ) * 1000000007 );
   l_checksum = ( uint16_t ) ( ( ( l_checksum & 0xF000 ) >> 12 ) | ( ( l_checksum & 0x0F00 ) >> 4 ) | ( ( l_checksum & 0x00F0 ) << 4 ) | ( ( l_checksum & 0x000F ) << 12 ) );

   /* Conversion en chaine de caractères */
   mk_fat_utils_16bToASCII ( l_checksum, p_checksum, K_MK_NULL );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_createExtensionEX ( T_str8 p_fileName, T_str8 p_result )
{
   /*  Déclaration de la variable de retour */
   uint8_t l_extension [ K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ] = { ' ', ' ', ' ', '\0' };

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_currentChar = 0, l_index = 0, l_offset = 0xFFFF;

   /* Déclaration d'un pointeur de chaine */
   T_str8 l_str = p_fileName;

   /* Récupération de l'offset du dernier caractère '.' dans le nom du fichier */
   do
   {
      /* Récupération de la valeur du prochain caractère de la chaine */
      l_str = mk_font_parseString ( l_str, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

      /* Si le caractère '.' est présent */
      if ( l_currentChar == '.' )
      {
         /* Actualisation de l'offset du dernier caractère '.' trouvé */
         l_offset = ( uint32_t ) ( l_counter + 1 );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la variable de comptage */
      l_counter++;
   }

   /* Tant que la chaine n'a pas été entièrement parcourue */
   while ( l_currentChar != 0 );

   /* Si le nom de fichier possède au moins un caractère '.' */
   if ( l_offset != 0xFFFF )
   {
      /* Récupération de l'offset du dernier caractère '.' dans le nom du fichier */
      do
      {
         /* Récupération de la valeur du prochain caractère de la chaine */
         p_fileName = mk_font_parseString ( p_fileName, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

         /* Si la chaine de caractères est en minuscule */
         if ( ( ( uint8_t ) l_currentChar >= 'a' ) && ( ( uint8_t ) l_currentChar <= 'z' ) )
         {
            /* Conversion en majuscule */
            l_extension [ l_index ] = ( uint8_t ) ( l_currentChar & 0xDF );
         }

         /* Sinon */
         else
         {
            /* Conversion en majuscule */
            l_extension [ l_index ] = ( uint8_t ) ( l_currentChar );
         }

         /* Actualisation du compteur */
         l_index++;

         /* Actualisation de l'offset */
         l_offset++;
      }

      /* Tant que la chaine de caractères n'a pas été entièrement parcourue ou tant que le travail n'est pas terminé */
      while ( ( l_currentChar != 0 ) && ( l_index < K_MK_FAT_ENTRY_EXTENSION_SIZE ) );

   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation de la variable de retour */
   _copy ( p_result, l_extension, K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_createNameEX ( T_str8 p_fileName, T_str8 p_result, uint16_t p_number )
{
   /* Déclaration d'une table stockant le paramètr 'p_number' en chaine de caractères */
   char8_t l_number [ 5 ] = { '~', '~', '~', '~', '~' };

   /* Déclaration d'une table stockant la valeur du checksum 16bits */
   char8_t l_checksum [ 4 ] = { 0 };

   /*  Déclaration de la variable de retour */
   char8_t l_name [ K_MK_FAT_ENTRY_NAME_SIZE + 1 ] = { 0 };

   /* Déclaration d'une variable stockant la longueur de la chaine de caractères "l_number" */
   /* Le caractère '~' n'est pas pris en compte. */
   uint8_t l_length = 1;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_index = 0, l_currentChar = 0;

   /* Récupération de la valeur du checksum 16 bits */
   mk_fat_utils_ckecksum16bits ( p_fileName, ( T_str8 ) l_checksum );

   /* Ecriture de la valeur par défaut des deux premiers caractères */
   _copy ( l_name, l_checksum, 2 );

   /* Effectue */
   do
   {
      /* Récupération de la valeur du prochain caractère de la chaine */
      p_fileName = mk_font_parseString ( p_fileName, &l_currentChar, ( uint32_t ) K_MK_FONT_UTF8 );

      /* Si la chaine de caractères est en minuscule */
      if ( ( ( uint8_t ) l_currentChar >= 'a' ) && ( ( uint8_t ) l_currentChar <= 'z' ) )
      {
         /* Conversion en majuscule */
         l_name [ l_index ] = ( char8_t ) ( l_currentChar & 0xDF );
      }

      /* Sinon */
      else
      {
         /* Conversion en majuscule */
         l_name [ l_index ] = ( char8_t ) ( l_currentChar );
      }

      /* Actualisation des compteurs */
      l_index++;
      l_counter++;
   }

   /* Tant que la chaine de caractères n'a pas été entièrement parcourue ou tant que le travail n'est pas terminé */
   while ( ( l_currentChar != 0 ) && ( l_index < 2 ) );

   /* Ecriture de la valeur du checksum dans la chaine de retour */
   _copy ( &l_name [ 2 ], l_checksum, 4 );

   /* Conversion du numéro en chaine de caractères */
   mk_fat_utils_16bToASCII ( p_number, ( T_str8 ) &l_number [ 1 ], &l_length );

   /* Ecriture du caractère '~' */
   l_number [ 5 - ( l_length + 1 ) ] = '~';

   /* Ecriture du numéro dans la chaine de caractères */
   _copy ( &l_name [ K_MK_FAT_ENTRY_NAME_SIZE - ( l_length + 1 ) ], &l_number [ 5 - ( l_length + 1 ) ], ( uint32_t ) ( l_length + 1 ) );

   /* Actualisation de la variable de retour */
   _copy ( p_result, l_name, K_MK_FAT_ENTRY_NAME_SIZE + 1 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_setNameEX ( T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_checksum, uint16_t p_fileIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_local = 0;

   /* Déclaration de deux chaines de caractères au format 8.3 + '\0', obligatoirement initialisé à 0. */
   int8_t l_fatName [ K_MK_FAT_ENTRY_NAME_SIZE + 1 ] = { '\0' };
   int8_t l_fatExtension [ K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ] = { '\0' };

   /* Si le paramètre est valide */
   if ( ( p_checksum != K_MK_NULL ) && ( p_fileIndex != 0 ) )
   {
      /* Création d'une extension au format court */
      mk_fat_utils_createExtensionEX ( p_fileName, ( T_str8 ) l_fatExtension );

      /* Création d'un nom au format court */
      mk_fat_utils_createNameEX ( p_fileName, ( T_str8 ) l_fatName, p_fileIndex );

      /* Concaténation des deux chaines de caractères */
      l_local = mk_utils_strcat ( p_fatEntryName, ( T_str8 ) l_fatName, ( T_str8 ) l_fatExtension );

      /* Si aucune erreur ne s'est produite */
      if ( l_local != 0 )
      {
         /* Détermination de la valeur du CRC 8bits */
         mk_fat_utils_ckecksum8bits ( p_fatEntryName, p_checksum );

         /* Concaténation des chaines de caractères au format 8.3 */
         l_local = mk_utils_strcat ( &p_fatEntryName [ 0 ], ( T_str8 ) l_fatName, ( T_str8 ) "." );

         /* Si une erreur s'est produite */
         if ( l_local == 0 )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }

         /* Sinon */
         else
         {
            /* Concaténation des chaines de caractères au format 8.3 */
            l_local = mk_utils_strcat ( &p_fatEntryName [ K_MK_FAT_ENTRY_NAME_SIZE + 1 ], ( T_str8 ) l_fatExtension, ( T_str8 ) "" );

            /* Si une erreur s'est produite */
            if ( l_local == 0 )
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_setNameST ( T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_caseType )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable locale */
   uint32_t l_local;

   /* Déclaration de deux chaines de caractères au format 8.3 + '\0', obligatoirement initialisé à 0. */
   int8_t l_fatName [ K_MK_FAT_ENTRY_NAME_SIZE + 1 ] = { '\0' };
   int8_t l_fatExtension [ K_MK_FAT_ENTRY_EXTENSION_SIZE + 1 ] = { '\0' };

   /* Si le paramètre est valide */
   if ( p_caseType != K_MK_NULL )
   {
      /* Si le premier caractère est non valide */
      if ( p_fileName [ 0 ] == ( int8_t ) K_MK_FAT_DELETED_ENTRY )
      {
         /* Modification de la valeur du premier caractère */
         p_fileName [ 0 ] = K_MK_FAT_E5_ENTRY;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Récupération du nom du fichier */
      l_local  = mk_utils_strsplit ( p_fileName, ( T_str8 ) l_fatName, 0, '.' );
      l_local |= mk_utils_strsplit ( p_fileName, ( T_str8 ) l_fatExtension, 1, '.' );

      /* Si aucune erreur ne s'est produite */
      if ( l_local != 0 )
      {
         /* Initialisation de la variable de retour */
         *p_caseType = 0;

         /* Conversion des chaines de caractères au format FAT */
         mk_fat_utils_toUpperCase ( ( T_str8 ) l_fatName, K_MK_FAT_ENTRY_NAME_SIZE, K_MK_FAT_NAME_LOWER_CASE_FLAG, p_caseType );
         mk_fat_utils_toUpperCase ( ( T_str8 ) l_fatExtension, K_MK_FAT_ENTRY_EXTENSION_SIZE, K_MK_FAT_EXTENSION_LOWER_CASE_FLAG, p_caseType );

         /* Concaténation des deux chaines de caractères */
         l_local = mk_utils_strcat ( p_fatEntryName, ( T_str8 ) l_fatName, ( T_str8 ) l_fatExtension );

         /* Si une erreur s'est produite */
         if ( l_local == 0 )
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_setName ( T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_caseType, uint8_t* p_checksum, T_mkFATEntryType p_type, uint16_t p_fileIndex )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_fileName != K_MK_NULL ) && ( p_fatEntryName != K_MK_NULL ) )
   {
      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si un nom au format 8.3 doit être créé */
         if ( p_type == K_MK_FAT_ENTRY_ST )
         {
            /* Création d'un nom d'entrée standard */
            l_result = mk_fat_utils_setNameST ( p_fileName, p_fatEntryName, p_caseType );
         }

         /* Sinon si un nom au format étendu doit être créé */
         else if ( p_type == K_MK_FAT_ENTRY_EX )
         {
            /* Création d'un nom d'entrée étendu */
            l_result = mk_fat_utils_setNameEX ( p_fileName, p_fatEntryName, p_checksum, p_fileIndex );
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


