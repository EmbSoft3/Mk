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
* @file mk_fat_utils_findFile.c
* @brief Définition de la fonction mk_fat_utils_findFile.
* @date 28 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_updateCluster ( T_mkFile* p_file, T_mkFATHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'adresse du prochain cluster */
   l_result = mk_fat_utils_getCluster ( p_file, p_handler->currentCluster, &p_handler->currentCluster, 1 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le cluster courant n'est pas le dernier cluster du répertoire */
      if ( p_handler->currentCluster < K_MK_FAT_VALID_CLUSTER )
      {
         /* Actualisation de la valeur du cluster de l'entrée */
         p_handler->entryCluster = p_handler->currentCluster;

         /* Détermination de l'adresse du nouveau bloc de recherche */
         p_handler->currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
               ( ( p_handler->currentCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

         /* Lecture du secteur de données */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_FOUND;
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_updateDirectory ( T_mkFile* p_file, T_mkFATHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Récupération de la valeur de l'entrée courante */
   l_entry = ( T_mkAddr ) &p_file->buf [ ( p_handler->entryBlockIndex - 1 ) * K_MK_FAT_ENTRY_SIZE ];

   /* Actualisation de la valeur du cluster de base */
   p_handler->directoryCluster = ( uint32_t ) ( l_entry->firstClusterHigh << 16 );
   p_handler->directoryCluster = ( uint32_t ) ( p_handler->directoryCluster | l_entry->firstClusterLow );
   p_handler->directoryCluster = ( uint32_t ) ( p_handler->directoryCluster & K_MK_FAT_CLUSTER_MASK );

   /* Actualisation de la valeur du cluster courant */
   p_handler->currentCluster = p_handler->directoryCluster;

   /* Détermination de l'adresse du nouveau bloc de recherche */
   p_handler->currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
         ( ( p_handler->directoryCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

   /* Actualisation des variables de travail */
   p_handler->flag = ( K_MK_FAT_ENTRY_FOUND + 1 );
   p_handler->entryVirtualClusterIndex = K_MK_FAT_VIRTUAL_ENTRY_DEFAULT;
   p_handler->entryVirtualCluster = K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT;

   /* Lecture du secteur de données */
   l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );

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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_getFileInformation ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_mkFATEntryDescriptor* p_entry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Initialisation des attributs du fichier */
   p_handler->firstDataCluster = ( uint32_t ) ( ( ( p_entry->firstClusterHigh << 16 ) | p_entry->firstClusterLow ) & K_MK_FAT_CLUSTER_MASK );
   l_result = mk_fat_utils_setFile ( p_file, p_handler, p_entry->fileSize );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_checkDirectoryIndex ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_mkFATEntryDescriptor* p_entry, uint32_t p_numberOfDirectory )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Si le fichier recherché a été trouvé */
   if ( p_handler->directoryIndex == ( p_numberOfDirectory - 1 ) )
   {
      /* Initialisation de la structure p_file */
      l_result = mk_fat_utils_getFileInformation ( p_file, p_handler, p_entry );
   }

   /* Sinon */
   else
   {
      /* Actualisation du drapeau afin d'indiquer qu'un des répertoire du chemin a été trouvé */
      p_handler->flag = K_MK_FAT_ENTRY_FOUND;

      /* Arrêt de la boucle de lecture des blocs de données */
      p_handler->blockIndex = p_file->volume->partition.fat.sectorsPerCluster;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_checkEntryIndex ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_mkFATEntryDescriptor* p_entry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Si l'entrée recherchée a été trouvée */
   if ( p_handler->entrySearched == K_MK_FAT_ENTRY_FOUND )
   {
      /* Initialisation de la structure p_file */
      l_result = mk_fat_utils_getFileInformation ( p_file, p_handler, p_entry );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la valeur de l'entrée virtuel */
      p_handler->entryVirtualClusterIndex = K_MK_FAT_VIRTUAL_ENTRY_DEFAULT;

      /* Actualisation de la valeur du secteur virtuel */
      p_handler->entryVirtualCluster = K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT;

      /* Actualisation de l'indeice de l'entrée recherchée */
      p_handler->entrySearched = ( uint16_t ) ( p_handler->entrySearched - 1 );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_checkEntryST ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entry, T_str8 p_directoryName, T_mkFATHandler* p_handler, uint32_t p_numberOfDirectory )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'un buffer stockant le nom présent dans l'entrée ('.' + '\0') */
   char8_t l_name [ K_MK_FAT_ENTRY_NAME_SIZE + K_MK_FAT_ENTRY_EXTENSION_SIZE + 2 ] = { 0 } ;

   /* Déclaration des variables de travail */
   uint32_t l_local = 0;

   /* Enregistrement du cluster de l'entrée standard */
   p_handler->entryCluster = p_handler->currentCluster;

   /* Enregistrement de l'index dans le cluster de l'entrée standard */
   p_handler->entryClusterIndex = ( uint16_t ) ( ( p_handler->blockIndex * p_file->volume->partition.fat.numberOfEntriesPerSector ) + p_handler->entryBlockIndex );

   /* Si la recherche du fichier dans le répertoire cible est terminé */
   if ( ( p_handler->flag == K_MK_FAT_LONG_NAME_FOUND ) )
   {
      /* Analyse de l'état de la recherche en fonction du nom du fichier */
      /* Si dernier fichier du chemin, arrêt, sinon on continu l'analyse avec le prochain répertoire */
      l_result = mk_fat_utils_checkDirectoryIndex ( p_file, p_handler, p_entry, p_numberOfDirectory );
   }

   /* Sinon */
   else
   {
      /* Si la recherche a été effectuée à partir d'une chaine de caractères */
      if ( p_directoryName [ 0 ] != '\0' )
      {
         /* Récupération du nom du fichier au format 8.3 */
         l_result = mk_fat_utils_getName ( p_entry, ( T_str8 ) l_name, K_MK_FAT_ENTRY_ST );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_NOT_AVAILABLE;

            /* Comparaison des deux chaines de caractères */
            l_local = mk_utils_strcomp ( ( T_str8 ) p_directoryName, ( T_str8 ) l_name, 1, 0 );

            /* Si le fichier recherché a été trouvé */
            if ( l_local == 1 )
            {
               /* Analyse de l'état de la recherche en fonction du nom du fichier */
               /* Si dernier fichier du chemin, arrêt, sinon on continu l'analyse avec le prochain répertoire */
               l_result = mk_fat_utils_checkDirectoryIndex ( p_file, p_handler, p_entry, p_numberOfDirectory );
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

      /* Sinon, la recherche a été effectuée à partir d'un index uniquement */
      else
      {
         /* Analyse de l'état de la recherche en fonction de l'index de l'entrée */
         /* Si l'entrée est trouvée, arrêt, sinon on continu l'analyse avec la prochaine entrée */
         l_result = mk_fat_utils_checkEntryIndex ( p_file, p_handler, p_entry );
      }
   }

   /* Réinitialisation du cluster de l'entrée virtuelle */
   p_handler->entryVirtualCluster = K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT;

   /* Réinitialisation de l'index de l'entrée virtuelle */
   p_handler->entryVirtualClusterIndex = K_MK_FAT_VIRTUAL_ENTRY_DEFAULT;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_checkEntryEX ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_entry, T_str8 p_directoryName, T_mkFATHandler* p_handler, uint32_t p_numberOfEntries, uint32_t p_searchFileLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'un buffer stockant le nom présent dans l'entrée */
   uint8_t l_partialName [ 2 * K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY + 1 ] = { 0 } ;

   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_local = 0;

   /* Si l'entrée est une entête étendue */
   if ( ( p_entry->name [ 0 ] & K_MK_FAT_EXTENDED_ENTRY_MASK ) > 0 )
   {
      /* Enregistrement du cluster de l'entrée virtuelle */
      p_handler->entryVirtualCluster = p_handler->currentCluster;

      /* Enregistrement de la valeur du checksum */
      p_handler->entryChecksum = ( uint32_t ) p_entry->checksum;

      /* Enregistrement de l'index de l'entrée virtuelle */
      p_handler->entryVirtualClusterIndex = ( uint16_t ) ( ( p_handler->blockIndex * p_file->volume->partition.fat.numberOfEntriesPerSector ) + p_handler->entryBlockIndex );

      /* Enregistrement du nombre d'entrées étendues */
      p_handler->entryVirtualNumber = ( uint32_t ) ( p_entry->name [ 0 ] & K_MK_FAT_EXTENDED_ENTRY_COUNT_MASK );

      /* Enregistrement du nombre d'entrées à analyser avant la récupération totale du nom du fichier */
      p_handler->flag = p_handler->entryVirtualNumber;

      /* Réinitialisation de la longueur de la chaine de caractères analysée */
      p_handler->fileNameLength = p_searchFileLength;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si la recherche a été effectuée à partir d'une chaine de caractères */
   if ( p_directoryName [ 0 ] != '\0' )
   {
      /* Récupération d'un segment du nom */
      l_result = mk_fat_utils_getName ( p_entry, ( T_str8 ) l_partialName, K_MK_FAT_ENTRY_EX );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Détermination de la longueur de la portion de la chaine de caractères */
         l_length = mk_utils_utfsize ( ( T_str8 ) l_partialName, K_MK_FONT_UTF8 );

         /* Si la comparaison peut être réalisée */
         if ( p_handler->fileNameLength >= l_length )
         {
            /* Détermination de l'offet du segment dans la chaine de caractères */
            p_handler->fileNameLength = ( uint32_t ) ( p_handler->fileNameLength - l_length );

            /* Comparaison des deux chaines de caractères */
            l_local = mk_utils_strcomp ( ( T_str8 ) &p_directoryName [ p_handler->fileNameLength ], ( T_str8 ) l_partialName, 0, l_length );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si l'analyse des entrées étendues est terminée et si l'entrée analysée est l'entrée recherchée */
         if ( ( l_local == 1 ) && ( p_handler->entryChecksum == p_entry->checksum ) && ( p_handler->entryVirtualNumber == p_numberOfEntries ) )
         {
            /* Si le fichier a été trouvé */
            if ( p_handler->flag == ( K_MK_FAT_ENTRY_FOUND + 1 ) )
            {
               /* Si les chaines de caractères ont la même longueur */
               if ( p_handler->fileNameLength == 0 )
               {
                  /* On signale que le fichier a été trouvé */
                  p_handler->flag = K_MK_FAT_LONG_NAME_FOUND;
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
               /* Actualisation du compteur de fichiers */
               p_handler->flag = ( uint32_t ) ( p_handler->flag - 1 );
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_checkDirectory ( T_mkFile* p_file, T_str8 p_directoryName, T_mkFATHandler* p_handler, uint32_t p_numberOfDirectory, uint32_t p_numberOfEntries )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'un pointeur d'entrée */
   T_mkFATEntryDescriptor* l_entry;

   /* Déclaration d'une variable de travail */
   uint32_t l_length = mk_utils_utfsize ( p_directoryName, K_MK_FONT_UTF8 );

   /* Pour le nombre de secteurs dans un cluster */
   for ( p_handler->blockIndex = 0 ; ( p_handler->blockIndex < p_file->volume->partition.fat.sectorsPerCluster ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) ; p_handler->blockIndex++ )
   {
      /* Pour le nombre d'entrées dans un secteur */
      for ( p_handler->entryBlockIndex = 0 ; ( p_handler->entryBlockIndex < p_file->volume->partition.fat.numberOfEntriesPerSector )
               && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) && ( p_handler->flag != K_MK_FAT_ENTRY_FOUND ); p_handler->entryBlockIndex++ )
      {
         /* Actualisation de l'adresse de l'entrée courante */
         l_entry = ( T_mkAddr ) &p_file->buf [ p_handler->entryBlockIndex * K_MK_FAT_ENTRY_SIZE ];

         /* Si l'analyse du répertoire est terminée */
         if ( l_entry->name [ 0 ] == K_MK_FAT_NO_ENTRY )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_NOT_FOUND;
         }

         /* Sinon si l'entrée est valide */
         else if ( l_entry->name [ 0 ] != K_MK_FAT_DELETED_ENTRY )
         {
            /* Si l'entrée est de type étendue */
            if ( l_entry->attribute == K_MK_FAT_EXTENDED )
            {
               /* Analyse d'une entrée étendue */
               l_result = mk_fat_utils_checkEntryEX ( p_file, l_entry, p_directoryName, p_handler, p_numberOfEntries, l_length );
            }

            /* Sinon si l'entrée n'est pas un volume */
            else if ( l_entry->attribute != K_MK_FAT_VOLUME_LABEL )
            {
               /* Analyse d'une entrée standard */
               l_result = mk_fat_utils_checkEntryST ( p_file, l_entry, p_directoryName, p_handler, p_numberOfDirectory );
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

      /* Si un nouveau bloc de données doit être lu */
      if ( ( l_result == K_MK_ERROR_NOT_AVAILABLE ) && ( p_handler->blockIndex != p_file->volume->partition.fat.sectorsPerCluster ) )
      {
         /* Actualisation de l'adresse du bloc de données */
         p_handler->currentBlock = ( uint32_t ) ( p_handler->currentBlock + 1 );

         /* Actualisation du secteur de recherche */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) p_handler->currentBlock );

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

T_mkCode mk_fat_utils_findFile ( T_mkFile* p_file, T_str8 p_filePath, T_str8 p_fileBuf, uint32_t p_baseCluster, uint16_t p_entry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'une variable stockant le nombre de répertoires dans le chemin */
   uint32_t l_numberOfDirectory = 0;

   /* Déclaration d'un gestionnaire de travail */
   T_mkFATHandler l_handler = {
         p_entry,                                     /* Index de l'entrée recherchée */
         0,                                           /* Checksum contenu dans l'entrée courante. */
         0,                                           /* Padding */
         0,                                           /* Index de l'entrée courante par rapport au secteur. */
         0,                                           /* Index de l'entrée courante par rapport au début du cluster. */
         K_MK_FAT_VIRTUAL_ENTRY_DEFAULT,              /* Index de l'entrée virtuelle par rapport au début du cluster. */
         0,                                           /* Nombre d'entrées étendues du fichier. */
         0,                                           /* Bloc de données où est localisé l'entrée. */
         p_baseCluster,                               /* Cluster où est localisé l'entrée. */
         K_MK_FAT_VIRTUAL_CLUSTER_DEFAULT,            /* Cluster où est localisé l'entrée virtuelle. */
         0,                                           /* Adresse du premier cluster de données du fichier. */
         0,                                           /* Index du secteur dans le cluster. */
         0,                                           /* Index du répertoire analysé. */
         p_baseCluster,                               /* Cluster de la première entrée du répertoire. */
         0,                                           /* Adresse du secteur courant. */
         p_baseCluster,                               /* Adresse du cluster courant. */
         0,                                           /* Longueur courante du nom de fichier en cours d'analyse. */
         ( K_MK_FAT_ENTRY_FOUND + 1 )                 /* Variable d'état générale. */
   };

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfEntries = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Détermination de l'adresse du bloc de recherche */
      l_handler.currentBlock = p_file->volume->partition.fat.addressOfRootDirectory +
               ( ( p_baseCluster - p_file->volume->partition.fat.firstRootDirectoryCluster ) * p_file->volume->partition.fat.sectorsPerCluster );

      /* Récupération du nombre de répertoires à analyser */
      l_numberOfDirectory =  ( uint32_t ) ( mk_utils_utfcount ( p_filePath, '/', K_MK_FONT_UTF8 ) + 1 );

      /* Lecture du premier secteur de recherche */
      l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) l_handler.currentBlock );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Réactualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_AVAILABLE;

         /* Pour le nombre de répertoires à analyser */
         for ( l_handler.directoryIndex = 0 ; ( l_handler.directoryIndex < l_numberOfDirectory ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) ; l_handler.directoryIndex++ )
         {
            /* Récupération du nom du répertoire courant */
            mk_utils_utfsplit ( p_filePath, ( T_str8 ) p_fileBuf, ( uint16_t ) l_handler.directoryIndex, '/', K_MK_FONT_UTF8 );

            /* Détermination du nombre d'entrées étendues nécessaires pour coder le nom de fichier */
            l_numberOfEntries = mk_fat_utils_getNumberOfEntries ( ( T_str8 ) p_fileBuf );

            /* Tant que l'analyse du répertoire n'est pas terminée */
            while ( ( l_handler.currentCluster < K_MK_FAT_VALID_CLUSTER ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) && ( l_handler.flag != K_MK_FAT_ENTRY_FOUND ) )
            {
               /* Parcours du chemin jusqu'au dernier répertoire */
               l_result = mk_fat_utils_checkDirectory ( p_file, ( T_str8 ) p_fileBuf, &l_handler, l_numberOfDirectory, l_numberOfEntries );

               /* Si un nouveau cluster doit être lu */
               if ( ( l_result == K_MK_ERROR_NOT_AVAILABLE ) && ( l_handler.flag != K_MK_FAT_ENTRY_FOUND ) )
               {
                  /* Actualisatin du cluster courant */
                  l_result = mk_fat_utils_updateCluster ( p_file, &l_handler );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Si le fichier n'a pas été trouvé et si aucune erreur ne s'est produite */
            if ( l_result == K_MK_ERROR_NOT_AVAILABLE )
            {
               /* Récupération des informations sur le prochain répertoire */
               l_result = mk_fat_utils_updateDirectory ( p_file, &l_handler );
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

