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
* @file mk_fat_utils_createFile.c
* @brief Définition de la fonction mk_fat_utils_createFile.
* @date 2 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_fat_utils_setHandler ( T_mkFATHandler* p_handler, T_mkFATEntryAddress* p_entry, uint32_t p_baseCluster, uint32_t p_firstDataCluster )
{
   /* Réinitialion du gestionnaire */
   _writeWords ( p_handler, 0, sizeof ( T_mkFATHandler ) >> 2 );

   /* Adresse du bloc de données où est situé l'entrée */
   p_handler->currentBlock = p_entry->currentBlock;

   /* Adresse du cluster où est situé l'entrée */
   p_handler->currentCluster = p_entry->currentCluster;

   /* Index de l'entrée dans le secteur */
   p_handler->entryBlockIndex = p_entry->entryIndex;

   /* Index du secteur dans le cluster */
   p_handler->blockIndex = p_entry->blockIndex;

   /* Adresse du cluster du répertoire de base */
   p_handler->directoryCluster = p_baseCluster;

   /* Adresse du cluster du premier secteur de données */
   p_handler->firstDataCluster = p_firstDataCluster;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_createDirectory ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, uint32_t* p_directoryFirstCluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire */
   T_mkFATHandler l_handler;

   /* Déclaration d'une variable de travail */
   T_mkFATEntryAddress l_currentEntry = { 0, 0, 0, 0 };

   /* Allocation d'un nouveau cluster */
   l_result = mk_fat_utils_appendCluster ( p_file, K_MK_FAT_CREATE_CLUSTER_CHAIN, &l_currentEntry.currentCluster, 1 );

   /* Si l'allocation du nouveau cluster a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Détermination de l'adresse du bloc de données */
      l_currentEntry.currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
            ( ( l_currentEntry.currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

      /* Initialisation du gestionnaire */
      mk_fat_utils_setHandler ( &l_handler, &l_currentEntry, p_baseCluster, l_currentEntry.currentCluster );

      /* Création d'une nouvelle entrée marquant la fin du répertoire */
      l_result = mk_fat_utils_writeEntry ( p_file, p_fileName, K_MK_FAT_NO_ATTRIBUTE, K_MK_FAT_ENTRY_SP, &l_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisatoion de la variable de retour */
         *p_directoryFirstCluster = l_currentEntry.currentCluster;
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

static T_mkCode mk_fat_utils_createEmptyFile ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, uint32_t p_directoryFirstCluster, uint8_t p_fileAttribute, T_mkFATEntryType p_fileNameType )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire */
   T_mkFATHandler l_handler;

   /* Déclaration d'une variable de travail */
   T_mkFATEntryAddress l_currentEntry = { 0 };

   /* Détermination de l'adresse de la dernière entrée du répertoire */
   l_result = mk_fat_utils_getLastEntry ( p_file, p_baseCluster, &l_currentEntry );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire */
      mk_fat_utils_setHandler ( &l_handler, &l_currentEntry, p_baseCluster, p_directoryFirstCluster );

      /* Création d'une nouvelle entrée marquant la fin du répertoire */
      l_result = mk_fat_utils_writeEntry ( p_file, p_fileName, p_fileAttribute, p_fileNameType, &l_handler );
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

T_mkCode mk_fat_utils_createFile ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, uint8_t p_fileAttribute )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant le type de l'entrée à créer */
   T_mkFATEntryType l_fileNameType = K_MK_FAT_ENTRY_ST;

   /* Déclaration d'une variable stockant l'adresse du premier cluster du répertoire */
   uint32_t l_directoryFirstCluster = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) )
   {
      /* Vérification de l'existence du fichier */
      l_result = mk_fat_utils_findFile ( p_file, p_fileName, p_fileName, p_baseCluster, K_MK_FAT_FIRST_ENTRY_OFFSET );

      /* Si le fichier n'existe pas */
      if ( l_result == K_MK_ERROR_NOT_FOUND )
      {
         /* Si au moins un cluster est disponible */
         if ( p_file->volume->partition.fat.numberOfFreeCluster > 0 )
         {
            /* Récupération du type du nom de fichier */
            l_result = mk_fat_utils_getNameType ( p_fileName, &l_fileNameType );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Si l'utilisateur souhaite créer un répertoire */
               if ( ( p_fileAttribute & K_MK_FAT_SUBDIRECTORY ) == K_MK_FAT_SUBDIRECTORY )
               {
                  /* Allocation d'un nouveau cluster puis création des entrées '.', '..' et '\0' */
                  /* L'adresse du cluster est stockée dans la variable l_directoryFirstCluster */
                  l_result = mk_fat_utils_createDirectory ( p_file, p_fileName, p_baseCluster, &l_directoryFirstCluster );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Création d'une entrée */
                  l_result = mk_fat_utils_createEmptyFile ( p_file, p_fileName, p_baseCluster, l_directoryFirstCluster, p_fileAttribute, l_fileNameType );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
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
               /* Ne rien faire */
            }
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
         l_result = K_MK_ERROR_ALREADY_EXIST;
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
