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
* @file mk_fat_utils_link.c
* @brief Définition de la fonction mk_fat_utils_link.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_utils_linkFile ( T_mkFile* p_file, T_str8 p_fileName, uint32_t p_baseCluster, T_mkFATEntryDescriptor* p_baseEntryDescriptor, T_mkFATEntryDescriptor* p_renamedEntryDescriptor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un fichier local */
   T_mkFile l_file = { 0 };

   /* Configuration du cache */
   l_file.cacheBaseAddress = p_file->cacheBaseAddress;

   /* Vérification de l'existence du fichier */
   l_result = mk_fat_search ( p_file->volume, &l_file, p_fileName, p_baseCluster, K_MK_FAT_FIRST_ENTRY_OFFSET );

   /* Si le fichier n'existe pas */
   if ( l_result == K_MK_ERROR_NOT_FOUND )
   {
      /* Récupération des attributs du fichier à copier */
      l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, p_baseEntryDescriptor );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Création du fichier */
         /* Le nouveau fichier créér est obligatoirement sur le même volume que le fichier à copier */
         l_result = mk_fat_open ( p_file->volume, &l_file, p_fileName, l_file.volume->partition.fat.firstRootDirectoryCluster, K_MK_FS_OPEN_CREATE );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération des attributs du nouveau fichier */
            l_result = mk_fat_utils_getFileEntryDescriptor ( &l_file, p_renamedEntryDescriptor );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration de la taille du fichier et configuration du numéro du premier cluster */
               p_renamedEntryDescriptor->firstClusterLow = p_baseEntryDescriptor->firstClusterLow;
               p_renamedEntryDescriptor->firstClusterHigh = p_baseEntryDescriptor->firstClusterHigh;
               p_renamedEntryDescriptor->fileSize = p_baseEntryDescriptor->fileSize;
               p_renamedEntryDescriptor->attribute = p_baseEntryDescriptor->attribute;

               /* Acutalisation des attributs du fichier créé */
               l_result = mk_fat_utils_setFileEntryDescriptor ( &l_file, p_renamedEntryDescriptor );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Fermeture du fichier ouvert */
            l_result |= mk_fat_close ( &l_file );
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
      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_ALREADY_EXIST;
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

T_mkCode mk_fat_utils_link ( T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables contenant les attributs du fichier à copier et les attributs du nouveau fichier */
   T_mkFATEntryDescriptor l_baseEntryDescriptor, l_renamedEntryDescriptor;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Si au moins un cluster est disponible */
      if ( p_file->volume->partition.fat.numberOfFreeCluster > 0 )
      {
         /* Création d'un nouveau lien à l'emplaçement désiré */
         l_result = mk_fat_utils_linkFile ( p_file, p_filePath, p_baseCluster, &l_baseEntryDescriptor, &l_renamedEntryDescriptor );
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
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

