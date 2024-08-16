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
* @file mk_fat_open.c
* @brief Définition de la fonction mk_fat_open.
* @date 26 déc. 2020
*
* @todo implémenter la fonction str est valide
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkFileMode mk_fat_setAccessMode ( T_mkFile* p_file, uint32_t p_mode )
{
   /* Si le fichier est partagé */
   if ( ( p_mode & K_MK_FS_OPEN_SHARED ) == K_MK_FS_OPEN_SHARED )
   {
      /* Actualisation du flag "shared" */
      p_file->flag.shared = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le fichier est accessible en lecture */
   if ( ( p_mode & K_MK_FS_OPEN_READ ) == K_MK_FS_OPEN_READ )
   {
      /* Actualisation du flag "read" */
      p_file->flag.read = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le fichier est accessible en écriture */
   if ( ( p_mode & K_MK_FS_OPEN_WRITE ) == K_MK_FS_OPEN_WRITE )
   {
      /* Actualisation du flag "write" */
      p_file->flag.write = 1;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression des attributs shared, read et write */
   p_mode = ( uint32_t ) ( ( uint32_t ) p_mode & ( uint32_t ) ( ~ ( K_MK_FS_OPEN_SHARED | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE ) ) );

   /* Retour */
   return ( ( T_mkFileMode ) p_mode );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_getRootDirectoryHandle ( T_mkFile* p_file, uint32_t p_baseCluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un gestionnaire de travail */
   T_mkFATHandler l_handler = {
         0,                                           /* Index de l'entrée recherchée */
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

   /* Initialisation des attributs du fichier */
   /* On retourne la première entrée de la rootDirectory */
   l_handler.firstDataCluster = p_baseCluster;
   l_result = mk_fat_utils_setFile ( p_file, &l_handler, 0 );

   /* Actualisation du registre de statut du fichier pour indiquer que */
   /* ce fichier est une instance du répertoire racine. */
   p_file->flag.rootDirectory = 1;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_open ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, T_mkFileMode p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une instance de disque */
   T_mkDisk* l_disk = K_MK_NULL;

   /* Déclaration d'un descripteur de fichier */
   T_mkFATEntryDescriptor l_fileEntryDescriptor;

   /* Déclaration des variables de travail */
   uint8_t l_attribute = K_MK_FAT_SUBDIRECTORY;
   uint32_t l_counter = 0, l_slashNumber = 0;

   /* Déclaration d'un buffer de travail */
   uint8_t l_fileName [ K_MK_FILE_MAX_NAME_LENGTH + 1 ];

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_volume != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Vérification de la validité de la chaine de caractères */
      l_result = mk_fat_utils_checkInvalidName ( p_filePath );

      /* Si l'adresse de base du cluster est valide */
      if ( ( l_result == K_MK_OK ) && ( p_baseCluster >= p_volume->partition.fat.firstRootDirectoryCluster ) )
      {
         /* Référencement du volume dans le fichier */
         p_file->volume = p_volume;

         /* Récupération de l'adresse du disque */
         l_disk = p_file->volume->disk;

         /* Réinitialisation de la structure T_mkFile */
         _writeWords ( &p_file->descriptor, 0, sizeof ( T_mkFileDescriptor ) >> 2 );

         /* Configuration des droits d'accès */
         p_mode = mk_fat_setAccessMode ( p_file, p_mode );

         /* Si le répertoire racine doit être renvoyé */
         if ( p_filePath [ 0 ] == 0 )
         {
            /* Récupération de l'instance du répertoire racine */
            l_result = mk_fat_getRootDirectoryHandle ( p_file, p_baseCluster );
         }

         /* Sinon */
         else
         {
            /* Recherche du fichier */
            l_result = mk_fat_utils_findFile ( p_file, p_filePath, ( T_str8 ) l_fileName, p_baseCluster, 0 );
         }

         /* Si le fichier a été trouvé */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du descripteur de fichier */
            l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_fileEntryDescriptor );

            /* Si l'utilisateur souhaite accéder le fichier en écriture */
            if ( ( l_result == K_MK_OK ) && ( p_file->flag.write == 1 ) )
            {
               /* Si le fichier est en lecture seule */
               if ( ( l_fileEntryDescriptor.attribute & K_MK_FAT_READ_ONLY ) == K_MK_FAT_READ_ONLY )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_MK_ERROR_DENIED;
               }

               /* Sinon si le disque est protégé en écriture */
               else if ( ( l_disk->status.main & K_MK_DISK_WRITE_PROTECT ) == K_MK_DISK_WRITE_PROTECT )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_MK_ERROR_WRITE_PROTECT;
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

         /* Si le mode d'ouverture est K_MK_FS_OPEN_EXISTING, la fonction retourne le résultat précédent. */
         if ( p_mode == K_MK_FS_OPEN_EXISTING )
         {
            /* Ne rien faire */
         }

         /* Sinon si le mode d'ouverture est K_MK_FS_OPEN_CREATE ou K_MK_FS_OPEN_CREATE_DIRECTORY et si le fichier existe alors */
         /* une erreur doit être renvoyée */
         else if ( ( ( p_mode == K_MK_FS_OPEN_CREATE ) || ( p_mode == K_MK_FS_OPEN_CREATE_DIRECTORY ) ) && ( l_result == K_MK_OK ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_ALREADY_EXIST;
         }

         /* Sinon si le mode d'ouverture est K_MK_FS_OPEN_TRUNCATE et si le fichier existe alors */
         /* le fichier doit être tronqué */
         else if ( ( p_mode == K_MK_FS_OPEN_TRUNCATE ) && ( l_result == K_MK_OK ) )
         {
            /* Tronquage du fichier, le pointeur est situé au début du fichier par défaut */
            /* Les droits d'écriture sont vérifié dans la fonction */
            l_result = mk_fat_truncate ( p_file );
         }

         /* Sinon si le mode d'ouverture est K_MK_FS_OPEN_APPEND, et si le fichier a été trouvé alors */
         /* on positionne le pointeur à la fin du fichier */
         else if ( ( p_mode == K_MK_FS_OPEN_APPEND ) && ( l_result == K_MK_OK ) )
         {
            /* Modification de la position du pointeur de fichier */
            l_result = mk_fat_seek ( p_file, p_file->descriptor.fat.size );
         }

         /* Sinon si le fichier n'a pas été trouvé */
         else if ( l_result == K_MK_ERROR_NOT_FOUND )
         {
            /* Si le disque n'est pas protégé en écriture */
            if ( ( l_disk->status.main & K_MK_DISK_WRITE_PROTECT ) != K_MK_DISK_WRITE_PROTECT )
            {
               /* Réinitialisation de la variable de retour */
               l_result = K_MK_OK;

               /* A ce stade, on gére la création du fichier pour les modes K_MK_FS_OPEN_ALWAYS, K_MK_FS_OPEN_APPEND, */
               /* K_MK_FS_OPEN_CREATE et K_MK_FS_OPEN_TRUNCATE */
               /* Suite à la création, aucune action supplémentaire n'est nécessaire car la taille du fichier est nulle. */

               /* Récupération du nombre de caractères '\' dans la chaine */
               /* On ajoute un pour avoir au moins une occurence dans la recherche. */
               l_slashNumber = mk_utils_strcount ( p_filePath, '/' ) + 1;

               /* Pour le nombre de slash présents dans le chemin */
               for ( l_counter = 0 ; ( l_counter < l_slashNumber ) && ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_ALREADY_EXIST ) ) ; l_counter++ )
               {
                  /* Récupération du nom du répertoire courant ou du fichier */
                  ( void ) mk_utils_strsplit ( p_filePath, ( T_str8 ) l_fileName, ( uint16_t ) l_counter, '/' );

                  /* Si le nom est un répertoire */
                  if ( ( l_counter != ( l_slashNumber - 1 ) ) || ( p_mode == K_MK_FS_OPEN_CREATE_DIRECTORY ) )
                  {
                     /* Configuration de l'attribut du fichier */
                     l_attribute = K_MK_FAT_SUBDIRECTORY;
                  }

                  /* Sinon */
                  else
                  {
                     /* Configuration de l'attribut du fichier */
                     l_attribute = 0;
                  }

                  /* Création du fichier courant */
                  /* Dans le cas où le répertoire courant existe, la fonction ci-dessous ne fait rien */
                  l_result = mk_fat_utils_createFile ( p_file, ( T_str8 ) l_fileName, p_baseCluster, l_attribute );

                  /* Actualisation de l'adresse de base du cluster */
                  p_baseCluster = p_file->descriptor.fat.firstCluster;
               }
            }

            /* Sinon */
            else
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_WRITE_PROTECT;
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



