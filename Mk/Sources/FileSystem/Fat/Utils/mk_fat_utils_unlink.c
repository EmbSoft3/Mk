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
* @file mk_fat_utils_unlink.c
* @brief Définition de la fonction mk_fat_utils_unlink.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getFirstBlock ( T_mkFile* p_file, uint32_t* p_currentCluster, uint32_t* p_entryClusterIndex, uint32_t* p_currentBlock )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si le nom du fichier est étendu */
   if ( p_file->descriptor.fat.virtualEntryIndex != K_MK_FAT_VIRTUAL_ENTRY_DEFAULT )
   {
      /* Actualisation de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = p_file->descriptor.fat.virtualEntryIndex;

      /* Actualisation de la valeur du cluster courant */
      /* Le cluster de base n'est pas forcément le cluster du répertoire car un nombre important d'entrées peut être présent. */
      *p_currentCluster = p_file->descriptor.fat.virtualEntryCluster;

      /* Détermination de l'adresse de la première entrée étendue du fichier */
      *p_currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
         ( ( p_file->descriptor.fat.virtualEntryCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster ) +
         ( uint32_t ) ( p_file->descriptor.fat.virtualEntryIndex >> p_file->volume->partition.fat.sNumberOfEntriesPerSector );
   }

   /* Sinon */
   else
   {
      /* Actualisation de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = p_file->descriptor.fat.entryIndex;

      /* Actualisation de la valeur du cluster courant */
      /* Le cluster de base n'est pas forcément le cluster du répertoire car un nombre important d'entrées peut être présent. */
      *p_currentCluster = p_file->descriptor.fat.entryCluster;

      /* Détermination de l'adresse de la l'entrée du fichier */
      *p_currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
         ( ( p_file->descriptor.fat.entryCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster ) +
         ( uint32_t ) ( p_file->descriptor.fat.entryIndex >> p_file->volume->partition.fat.sNumberOfEntriesPerSector );
   }

   /* Lecture du secteur où est localisé l'entrée */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_currentBlock ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getNextBlock ( T_mkFile* p_file, uint32_t* p_currentCluster, uint32_t* p_entryClusterIndex, uint32_t* p_currentBlock )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si un nouveau cluster doit être lu */
   if ( ( *p_entryClusterIndex ) == ( p_file->volume->partition.fat.sectorsPerCluster * p_file->volume->partition.fat.numberOfEntriesPerSector ) )
   {
      /* Récupération de l'adresse du prochain cluster */
      /* Si le dernier cluster du fichier a été atteint, on considére que la fin du répertoire a été atteinte */
      l_result = mk_fat_utils_getCluster ( p_file, *p_currentCluster, p_currentCluster, 1 );

      /* Réinitialisation de la valeur de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite et si le cluster trouvé n'est pas le dernier cluster du fichier */
   if ( ( l_result == K_MK_OK ) && ( ( *p_currentCluster ) < K_MK_FAT_VALID_CLUSTER ) )
   {
      /* Détermination de l'adresse de la première entrée étendue du fichier */
      *p_currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
         ( ( ( *p_currentCluster ) - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster ) +
         ( ( *p_entryClusterIndex ) >> p_file->volume->partition.fat.sNumberOfEntriesPerSector );

      /* Lecture du secteur où est localisé l'entrée */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( *p_currentBlock ) );
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

static T_mkCode mk_fat_utils_deleteEntry ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entry, uint32_t p_currentBlock, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_firstFileCluster = 0;

   /* Si l'entrée n'est pas de type étendue */
   if ( p_entry->attribute != K_MK_FAT_EXTENDED )
   {
      /* Enregistrement de la valeur du premier caractère du fichier */
      p_entry->creationTime = ( uint16_t ) ( ( p_entry->creationTime & 0xFF00 ) | p_entry->name [ 0 ] );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression de l'entrée */
   p_entry->name [ 0 ] = K_MK_FAT_DELETED_ENTRY;

   /* Actualisation de l'entrée sur le disque */
   l_result = mk_fat_utils_writeCache ( p_file, ( uint64_t ) ( p_currentBlock ) );

   /* Si l'entrée n'est pas de type étendu */
   if ( ( l_result == K_MK_OK ) && ( p_entry->attribute != K_MK_FAT_EXTENDED ) )
   {
      /* Détermination de la valeur du premier cluster du fichier */
      l_firstFileCluster = ( uint32_t ) ( ( ( p_entry->firstClusterHigh << 16 ) | p_entry->firstClusterLow ) & K_MK_FAT_CLUSTER_MASK );

      /* Si le fichier à supprimer n'est pas un répertoire et si au moins un cluster a été alloué */
      if ( ( p_mode == K_MK_FAT_RELEASE_CLUSTERS ) && ( l_firstFileCluster != 0 ) && ( ( p_entry->attribute & K_MK_FAT_SUBDIRECTORY ) == 0 ) )
      {
         /* Suppression de la chaine de cluster */
         l_result = mk_fat_utils_releaseCluster ( p_file, l_firstFileCluster );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_unlinkCurrentFile ( T_mkFile* p_file, uint32_t* p_entryClusterIndex, uint32_t* p_baseDirectoryCluster, uint32_t* p_currentDirectoryCluster, uint32_t* p_previousDirectoryCluster, uint32_t p_currentBlock )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry = K_MK_NULL;

   /* Détermination de l'index de l'entrée dans le secteur */
   uint32_t l_index = _math_mod2 ( *p_entryClusterIndex, p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Récupération du contenu de l'entrée */
   l_entry = ( T_mkAddr ) &p_file->buf [ l_index * K_MK_FAT_ENTRY_SIZE ];

   /* Si l'entrée est la dernière entrée du répertoire */
   if ( ( l_entry->name [ 0 ] == K_MK_FAT_NO_ENTRY ) ||
      ( ( *p_currentDirectoryCluster ) >= K_MK_FAT_VALID_CLUSTER ) )
   {
      /* Suppression de la chaine de cluster du répertoire courant */
      l_result = mk_fat_utils_releaseCluster ( p_file, *p_baseDirectoryCluster );

      /* Actualisation de la valeur du prochain répertoire à analyser */
      *p_baseDirectoryCluster = *p_previousDirectoryCluster;

      /* Actualisation de la valeur du cluster courant */
      *p_currentDirectoryCluster = *p_baseDirectoryCluster;

      /* Actualisation de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = ( K_MK_FAT_FIRST_DIRECTORY_ENTRY - 1 );

      /* Si retour au premier répertoire analysé */
      if ( ( *p_baseDirectoryCluster ) == p_file->descriptor.fat.directoryCluster )
      {
         /* Arrêt de la boucle */
         *p_baseDirectoryCluster = 0;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si l'entrée est la seconde entrée du répertoire ('..') */
   else if ( ( ( *p_entryClusterIndex ) == ( K_MK_FAT_FIRST_DIRECTORY_ENTRY - 1 ) ) && ( ( *p_baseDirectoryCluster ) == ( *p_currentDirectoryCluster ) ) )
   {
      /* Enregistrement de l'adresse du répertoire parent */
      *p_previousDirectoryCluster = ( uint32_t ) ( ( ( l_entry->firstClusterHigh << 16 ) | l_entry->firstClusterLow ) & K_MK_FAT_CLUSTER_MASK );

      /* Actualisation de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = ( uint32_t ) ( *p_entryClusterIndex + 1 );
   }

   /* Sinon si l'entrée est une entrée valide */
   else if ( l_entry->name [ 0 ] != K_MK_FAT_DELETED_ENTRY )
   {
      /* Si le fichier est un répertoire */
      if ( ( l_entry->attribute & K_MK_FAT_SUBDIRECTORY ) == K_MK_FAT_SUBDIRECTORY )
      {
         /* Actualisation de la valeur du prochain répertoire à analyser */
         *p_baseDirectoryCluster = ( uint32_t ) ( ( ( l_entry->firstClusterHigh << 16 ) | l_entry->firstClusterLow ) & K_MK_FAT_CLUSTER_MASK );

         /* Actualisation de la valeur du cluster courant */
         *p_currentDirectoryCluster = *p_baseDirectoryCluster;

         /* Actualisation de l'index de l'entrée dans le cluster */
         *p_entryClusterIndex = ( K_MK_FAT_FIRST_DIRECTORY_ENTRY - 1 );
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'index de l'entrée dans le cluster */
         *p_entryClusterIndex = ( uint32_t ) ( *p_entryClusterIndex + 1 );
      }

      /* Suppression de l'entrée courante */
      l_result = mk_fat_utils_deleteEntry ( p_file, l_entry, p_currentBlock, K_MK_FAT_RELEASE_CLUSTERS );
   }

   /* Sinon */
   else
   {
      /* Actualisation de l'index de l'entrée dans le cluster */
      *p_entryClusterIndex = ( uint32_t ) ( *p_entryClusterIndex + 1 );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_unlinkFirstFile ( T_mkFile* p_file, uint32_t* p_entryClusterIndex, uint32_t p_currentBlock )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry = K_MK_NULL;

   /* Détermination de l'index de l'entrée dans le secteur */
   uint32_t l_index = _math_mod2 ( *p_entryClusterIndex, p_file->volume->partition.fat.sNumberOfEntriesPerSector );

   /* Récupération du contenu de l'entrée */
   l_entry = ( T_mkAddr ) &p_file->buf [ l_index * K_MK_FAT_ENTRY_SIZE ];

   /* Suppression de l'entrée courante */
   l_result = mk_fat_utils_deleteEntry ( p_file, l_entry, p_currentBlock, K_MK_FAT_KEEP_CLUSTERS );

   /* Actualisation de l'index de l'entrée dans le cluster */
   *p_entryClusterIndex = ( uint32_t ) ( *p_entryClusterIndex + 1 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_unlink ( T_mkFile* p_file, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant l'adresse du premier cluster du répertoire */
   uint32_t l_directoryIsNotEmpty = 1, l_currentDirectoryCluster = 0, l_previousDirectoryCluster = 0, l_baseDirectoryCluster = 0;
   uint32_t l_entryClusterIndex = 0, l_currentBlock = 0;

   /* Si le paramètre est valide */
   if ( p_file != K_MK_NULL )
   {
      /* Actualisation de la valeur du cluster de base */
      l_baseDirectoryCluster = p_file->descriptor.fat.directoryCluster;

      /* Actualisation de la valeur du cluster courant */
      l_currentDirectoryCluster = p_file->descriptor.fat.directoryCluster;

      /* Actualisation de la valeur du cluster précédent */
      l_previousDirectoryCluster = p_file->descriptor.fat.directoryCluster;

      /* Actualisation du secteur courant */
      l_result = mk_fat_utils_getFirstBlock ( p_file, &l_currentDirectoryCluster, &l_entryClusterIndex, &l_currentBlock );

      /* Tant que le processus de suppression n'est pas terminé */
      while ( ( l_result == K_MK_OK ) && ( l_directoryIsNotEmpty == 1 ) )
      {
         /* Si les clusters associés au fichier doivent être libérés */
         if ( p_mode == K_MK_FAT_RELEASE_CLUSTERS )
         {
            /* Suppression des répertoires dans le fichier */
            l_result = mk_fat_utils_unlinkCurrentFile ( p_file, &l_entryClusterIndex, &l_baseDirectoryCluster, &l_currentDirectoryCluster, &l_previousDirectoryCluster, l_currentBlock );
         }

         /* Sinon */
         else
         {
            /* Suppression de l'entrée du fichier */
            l_result = mk_fat_utils_unlinkFirstFile ( p_file, &l_entryClusterIndex, l_currentBlock );
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si le processus est terminé */
            if ( ( ( l_baseDirectoryCluster == p_file->descriptor.fat.directoryCluster ) && ( l_entryClusterIndex > p_file->descriptor.fat.entryIndex ) ) || ( l_currentDirectoryCluster == 0 ) )
            {
               /* Arrêt de la boucle */
               l_directoryIsNotEmpty = 0;
            }

            /* Sinon */
            else
            {
               /* Actualisation du secteur courant */
               l_result = mk_fat_utils_getNextBlock ( p_file, &l_currentDirectoryCluster, &l_entryClusterIndex, &l_currentBlock );
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Synchronisation du cache avec le disque */
         l_result = mk_fat_utils_sync ( p_file );
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


