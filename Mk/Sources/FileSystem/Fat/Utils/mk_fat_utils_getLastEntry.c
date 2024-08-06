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
* @file mk_fat_utils_getLastEntry.c
* @brief Définition de la fonction mk_fat_utils_getLastEntry.
* @date 2 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_appendEntry ( T_mkFile* p_file, uint32_t p_lastCluster, T_mkFATEntryAddress* p_address )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Configuration de l'index de l'entrée */
   p_address->entryIndex = K_MK_FAT_FIRST_ENTRY_OFFSET;

   /* Création et ajout d'un nouveau cluster */
   l_result = mk_fat_utils_appendCluster ( p_file, p_lastCluster, &p_address->currentCluster, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Détermination de l'adresse du bloc de données */
      p_address->currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
            ( ( p_address->currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );
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

static T_mkCode mk_fat_utils_searchLastEntry ( T_mkFile* p_file, T_mkFATEntryAddress* p_address )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'un pointeur d'entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Déclaration des variables de travail */
   uint16_t l_blockIndex = 0, l_entryIndex = 0;

   /* Pour le nombre de secteurs dans un cluster */
   for ( l_blockIndex = 0 ; ( l_blockIndex < p_file->volume->partition.fat.sectorsPerCluster ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) ; l_blockIndex++ )
   {
      /* Enregistrement de l'index du secteur */
      p_address->blockIndex = l_blockIndex;

      /* Pour le nombre d'entrées dans un secteur */
      for ( l_entryIndex = K_MK_FAT_FIRST_ENTRY_OFFSET ; ( l_entryIndex < p_file->volume->partition.fat.numberOfEntriesPerSector ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) ; l_entryIndex++ )
      {
         /* Actualisation de l'adresse de l'entrée courante */
         l_entry = ( T_mkAddr ) &p_file->buf [ l_entryIndex * K_MK_FAT_ENTRY_SIZE ];

         /* Si la dernière entrée du répertoire a été trouvée */
         if ( l_entry->name [ 0 ] == K_MK_FAT_NO_ENTRY )
         {
            /* Enregistrement de l'index de l'entrée */
            p_address->entryIndex = l_entryIndex;

            /* Arrêt de la boucle */
            l_result = K_MK_OK;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si l'entrée n'a pas été trouvée */
      if ( l_result == K_MK_ERROR_NOT_AVAILABLE )
      {
         /* Actualisation de l'adresse du prochain bloc de données */
         p_address->currentBlock = ( uint32_t ) ( p_address->currentBlock + 1 );

         /* Lecture du bloc de données */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_address->currentBlock );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_NOT_AVAILABLE;
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_getLastEntry ( T_mkFile* p_file, uint32_t p_baseCluster, T_mkFATEntryAddress* p_address )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_address != K_MK_NULL ) )
   {
      /* Récupération de l'index du dernier cluster */
      l_result = mk_fat_utils_findCluster ( p_file, p_baseCluster, &p_address->currentCluster, K_MK_FAT_LAST_CLUSTER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Détermination de l'adresse du bloc de données */
         p_address->currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
               ( ( p_address->currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

         /* Lecture du bloc de données */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_address->currentBlock );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Recherche de la dernière entrée */
            l_result = mk_fat_utils_searchLastEntry ( p_file, p_address );

            /* Si l'entrée n'a pas été trouvée */
            if ( l_result == K_MK_ERROR_NOT_AVAILABLE )
            {
               /* Le répertoire est plein, il faut ajouter un nouveau cluster à celui-ci */
               l_result = mk_fat_utils_appendEntry ( p_file, p_address->currentCluster, p_address );
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


