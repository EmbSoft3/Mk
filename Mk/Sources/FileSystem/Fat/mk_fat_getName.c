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
* @file mk_fat_getName.c
* @brief Définition de la fonction mk_fat_getName.
* @date 4 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_updateCluster ( T_mkFile* p_file, uint32_t* p_cluster, uint32_t* p_block )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_block = ( *p_block );
   uint32_t l_cluster = ( *p_cluster );

   /* Récupération de l'adresse du prochain cluster */
   l_result = mk_fat_utils_getCluster ( p_file, l_cluster, &l_cluster, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le cluster courant n'est pas le dernier cluster du répertoire */
      if ( l_cluster < K_MK_FAT_VALID_CLUSTER )
      {
         /* Détermination de l'adresse du secteur de la nouvelle entrée */
         l_block = p_file->volume->partition.fat.addressOfRootDirectory +
               ( ( l_cluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

         /* Lecture du secteur où est localisé l'entrée */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_block ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation des variables de retour */
            *p_block = l_block;
            *p_cluster = l_cluster;
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
         l_result = K_MK_ERROR_CORRUPTED;
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_getLongFileName ( T_mkFile* p_file, T_str8 p_fileName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_cluster = 0, l_block = 0, l_entryIndex = 0, l_sectorIndex = 0;
   uint32_t l_numberOfEntries = 0, l_counter = 0, l_length = 1, l_totalLength = 0;

   /* Déclaration d'un buffer stockant le nom présent dans l'entrée */
   uint8_t l_partialName [ 2 * K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY + 1 ] = { 0 } ;

   /* Déclaration d'un pointeur d'entrées */
   T_mkFATEntryDescriptor* l_entry = K_MK_NULL;

   /* Détermination de l'index du secteur par rapport au cluster */
   l_sectorIndex = ( uint32_t ) ( p_file->descriptor.fat.virtualEntryIndex >> p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Détermination de l'index de l'entrée par rapport au secteur */
   l_entryIndex = _math_mod2 ( p_file->descriptor.fat.virtualEntryIndex, p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Enregistrement de l'adresse du cluster de l'entrée virtuelle */
   l_cluster = p_file->descriptor.fat.virtualEntryCluster;

   /* Détermination de l'adresse du secteur de l'entrée virtuelle */
   l_block = p_file->volume->partition.fat.addressOfRootDirectory + ( ( p_file->descriptor.fat.virtualEntryCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) *
             p_file->volume->partition.fat.sectorsPerCluster ) + l_sectorIndex;

   /* Lecture du secteur où est localisé l'entrée */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_block ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration de la valeur initiale du pointeur d'entrée */
      l_entry = ( T_mkFATEntryDescriptor* ) ( T_mkAddr ) &p_file->buf [ l_entryIndex * K_MK_FAT_ENTRY_SIZE ];

      /* Récupération du nombre d'entrées stockant le nom du fichier */
      l_numberOfEntries = l_entry->name [ 0 ] & K_MK_FAT_EXTENDED_ENTRY_COUNT_MASK;

      /* Pour le nombre d'entrées récupérées */
      for ( l_counter = 0 ; ( l_result == K_MK_OK ) && ( l_counter < l_numberOfEntries ) ; l_counter++ )
      {
         /* Configuration du pointeur d'entrées */
         l_entry = ( T_mkFATEntryDescriptor* ) ( T_mkAddr ) &p_file->buf [ l_entryIndex * K_MK_FAT_ENTRY_SIZE ];

         /* Récupération d'un segment du nom du fichier */
         l_result = mk_fat_utils_getName ( l_entry, ( T_str8 ) l_partialName, K_MK_FAT_ENTRY_EX );

         /* Récupération de la taille du segment de la chaine de caractères */
         l_length = ( uint32_t ) ( l_length +  mk_utils_utfsize ( ( T_str8 ) l_partialName, ( uint32_t ) K_MK_FONT_UTF8 ) );

         /* Décalage de la chaine de caractères afin d'acceuillir les nouvelles données */
         _invcopy ( &p_fileName [ l_length ], p_fileName, l_totalLength );

         /* Copie du segment dans la variable de retour */
         _copy ( p_fileName, l_partialName, l_length );

         /* Actualisation de la longueur totale de la chaine de caractères */
         l_totalLength = ( uint32_t ) ( l_totalLength + l_length );

         /* Réinitialisation de la longueur du morceau de chaine */
         l_length = 0;

         /* Actualisation de l'index de l'entrée */
         l_entryIndex = ( uint32_t ) ( l_entryIndex + 1 );

         /* Si la prochaine entrée est localisée sur un autre secteur */
         if ( l_entryIndex == p_file->volume->partition.fat.numberOfEntriesPerSector )
         {
            /* Actualisation de l'index de la prochaine entrée */
            l_entryIndex = K_MK_FAT_FIRST_ENTRY_OFFSET;

            /* Actualisation de l'index du secteur */
            l_sectorIndex = ( uint32_t ) ( l_sectorIndex + 1 );

            /* Si la prochaine entrée est localisée sur un autre cluster */
            if ( l_sectorIndex == p_file->volume->partition.fat.sectorsPerCluster )
            {
               /* Actualisation de l'adresse du nouveau cluster et du nouveau bloc */
               l_result = mk_fat_updateCluster ( p_file, &l_cluster, &l_block );

               /* Actualisation de l'index du secteur */
               l_sectorIndex = 0;
            }

            /* Sinon */
            else
            {
               /* Actualisation de l'adresse du nouveau bloc de données */
               l_block = ( uint32_t ) ( l_block + 1 );

               /* Lecture du secteur où est localisé la prochaine entrée */
               l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_block ) );
            }
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
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_getShortFileName ( T_mkFile* p_file, T_str8 p_fileName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_block = 0, l_entryIndex = 0;

   /* Déclaration d'un pointeur d'entrée */
   T_mkFATEntryDescriptor* l_entry = K_MK_NULL;

   /* Détermination de l'adresse de l'entrée */
   l_block = p_file->volume->partition.fat.addressOfRootDirectory +
         ( ( p_file->descriptor.fat.entryCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster ) +
         ( uint32_t ) ( p_file->descriptor.fat.entryIndex >> p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Détermination de l'index de l'entrée par rapport au secteur */
   l_entryIndex = _math_mod2 ( p_file->descriptor.fat.entryIndex, p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Lecture du secteur où est localisé l'entrée */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( l_block ) );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration du pointeur d'entrée */
      l_entry = ( T_mkFATEntryDescriptor* ) ( T_mkAddr ) &p_file->buf [ l_entryIndex * K_MK_FAT_ENTRY_SIZE ];

      /* Récupération du nom du fichier au format standard */
      l_result = mk_fat_utils_getName ( l_entry, p_fileName, K_MK_FAT_ENTRY_ST );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_getName ( T_mkFile* p_file, T_str8 p_fileName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) )
   {
      /* Si le nom du fichier est étendu */
      if ( p_file->descriptor.fat.virtualEntryIndex != K_MK_FAT_VIRTUAL_ENTRY_DEFAULT )
      {
         /* Récupération du nom du fichier au format étendu */
         l_result = mk_fat_getLongFileName ( p_file, p_fileName );
      }

      /* Sinon */
      else
      {
         /* Récupération du nom du fichier au format 8.3 */
         l_result = mk_fat_getShortFileName ( p_file, p_fileName );
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



