/**
*
* @copyright Copyright (C) 2021-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_fat_openDirectory.c
* @brief Définition de la fonction mk_fat_openDirectory.
* @date 5 sept. 2021
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
   /* Récupération de l'adresse du disque */
   T_mkDisk* l_disk = ( T_mkDisk* ) p_file->volume->disk;

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

   /* Si le disque stockant le fichier est protégé en écriture */
   if ( ( l_disk->status.main & K_MK_DISK_WRITE_PROTECT ) == K_MK_DISK_WRITE_PROTECT )
   {
      /* Actualisation du flag "writeProtect" */
      p_file->flag.writeProtect = 1;
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

T_mkCode mk_fat_openDirectory ( T_mkVolume* p_volume, T_mkFile* p_file, uint32_t p_baseCluster, uint16_t p_entry, T_mkFileMode p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un descripteur de fichier */
   T_mkFATEntryDescriptor l_fileEntryDescriptor;

   /* Déclaration d'un buffer de travail */
   uint8_t l_fileName [ K_MK_FILE_MAX_NAME_LENGTH + 1 ] = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_volume != K_MK_NULL ) )
   {
      /* Si l'adresse de base du cluster est valide */
      if ( ( l_result == K_MK_OK ) && ( p_baseCluster >= p_volume->partition.fat.firstRootDirectoryCluster ) )
      {
         /* Référencement du volume dans le fichier */
         p_file->volume = p_volume;

         /* Réinitialisation de la structure T_mkFile */
         _writeWords ( &p_file->descriptor, 0, sizeof ( T_mkFileDescriptor ) >> 2 );

         /* Configuration des droits d'accès */
         p_mode = mk_fat_setAccessMode ( p_file, p_mode );

         /* Recherche du fichier */
         l_result = mk_fat_utils_findFile ( p_file, ( T_str8 ) "", ( T_str8 ) l_fileName, p_baseCluster, p_entry );

         /* Si le fichier a été trouvé */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du descripteur de fichier */
            l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_fileEntryDescriptor );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Si l'utilisateur souhaite ouvrir le répertoire en écriture alors qu'il est en lecture seule */
               if ( ( ( l_fileEntryDescriptor.attribute & K_MK_FAT_READ_ONLY ) == K_MK_FAT_READ_ONLY ) && ( p_file->flag.write == 1 ) )
               {
                  /* Actualisation de la variable de retour */
                  l_result = K_MK_ERROR_DENIED;
               }

               /* Sinon si le disque est protégé en écriture */
               else if ( ( p_file->flag.writeProtect == 1 ) && ( p_file->flag.write == 1 ) )
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



