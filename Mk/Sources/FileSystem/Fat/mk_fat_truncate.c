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
* @file mk_fat_truncate.c
* @brief Définition de la fonction mk_fat_truncate.
* @date 11 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_setFileSize ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_descriptor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Actualisation de la taille du fichier */
   p_descriptor->fileSize = p_file->descriptor.fat.currentPointer;
   p_file->descriptor.fat.size = p_file->descriptor.fat.currentPointer;

   /* Si le pointeur de fichier est nul */
   if ( p_file->descriptor.fat.currentPointer == 0 )
   {
      /* Actualisation du premier cluster du fichier */
      p_descriptor->firstClusterLow = 0;
      p_descriptor->firstClusterHigh = 0;

      /* Actualisation des attributs du fichier */
      p_file->descriptor.fat.currentCluster = 0;
      p_file->descriptor.fat.currentPointer = 0;
      p_file->descriptor.fat.firstCluster = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Ecriture de la nouvelle taille sur le disque */
   l_result = mk_fat_utils_setFileEntryDescriptor ( p_file, p_descriptor );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_truncateFile ( T_mkFile* p_file, uint32_t* p_cluster )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_clusterNumber = 0;

   /* Initialisation de la variable de travail */
   *p_cluster = p_file->descriptor.fat.firstCluster;

   /* Si un segment de la chaine de cluster doit être supprimé */
   if ( p_file->descriptor.fat.currentPointer != 0 )
   {
      /* Détermination de l'index du nouveau cluster de fin */
      l_clusterNumber = ( ( p_file->descriptor.fat.currentPointer - 1 ) >> p_file->volume->partition.fat.sClusterSize );

      /* Recherche de l'indentifiant du premier cluster à supprimer */
      l_result = mk_fat_utils_findCluster ( p_file, p_file->descriptor.fat.firstCluster, p_cluster, l_clusterNumber + 1 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de la valeur du cluster courant */
         p_file->descriptor.fat.currentCluster = *p_cluster;

         /* Ecriture de la valeur de fin de chaine dans le dernier cluster du fichier */
         l_result = mk_fat_utils_setCluster ( p_file, *p_cluster, p_cluster, K_MK_FAT_LAST_CLUSTER );

         /* Si aucune erreur ne s'est produite et si le cluster n'est pas le dernier cluster du fichier */
         if ( ( l_result == K_MK_OK ) && ( ( *p_cluster ) != K_MK_FAT_LAST_CLUSTER ) )
         {
            /* Suppression de la chaine de clusters à désallouer */
            l_result = mk_fat_utils_releaseCluster ( p_file, *p_cluster );
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
      /* Suppression de la chaine de clusters à désallouer */
      l_result = mk_fat_utils_releaseCluster ( p_file, *p_cluster );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_truncate ( T_mkFile* p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un descripteur de fichier */
   T_mkFATEntryDescriptor l_fileEntryDescriptor;

   /* Déclaration d'une variable de travail */
   uint32_t l_cluster = 0;

   /* Si le paramètre est valide */
   if ( ( p_file != K_MK_NULL ) )
   {
      /* Si le fichier peut être accédé en écriture */
      if ( p_file->flag.write == 1 )
      {
         /* Si le pointeur ne pointe pas sur la fin du fichier */
         if ( p_file->descriptor.fat.currentPointer < p_file->descriptor.fat.size )
         {
            /* Récupération du descripteur de fichier */
            l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_fileEntryDescriptor );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Désallocation de la chaine de clusters */
               l_result = mk_fat_truncateFile ( p_file, &l_cluster );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Actualisation de la taille du fichier et mise à jour du pointeur de fichier */
                  l_result = mk_fat_setFileSize ( p_file, &l_fileEntryDescriptor );
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

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Commutation du drapeau indiquant que le fichier a été modifié */
               p_file->flag.modified = 1;

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
         l_result = K_MK_ERROR_DENIED;
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



