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
* @file mk_fat_expand.c
* @brief Définition de la fonction mk_fat_expand.
* @date 14 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_fat_setFileSize ( T_mkFile* p_file, T_mkFATEntryDescriptor* p_descriptor, uint32_t p_firstCluster, uint32_t p_size )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le fichier est vide */
   if ( p_file->descriptor.fat.size == 0 )
   {
      /* Ecriture de l'adresse du premier cluster dans l'entrée */
      p_descriptor->firstClusterHigh = ( uint16_t ) ( ( p_firstCluster >> 16 ) & 0x0FFF );
      p_descriptor->firstClusterLow = ( uint16_t ) ( p_firstCluster & 0xFFFF );

      /* Actualisation des attributs du fichier */
      p_file->descriptor.fat.size = p_size;
      p_file->descriptor.fat.firstCluster = p_firstCluster;
      p_file->descriptor.fat.currentCluster = p_firstCluster;
      p_file->descriptor.fat.currentPointer = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Actualisation de la taille du fichier */
      p_descriptor->fileSize = p_size;
      p_file->descriptor.fat.size = p_size;

      /* Ecriture de la nouvelle taille sur le disque */
      l_result = mk_fat_utils_setFileEntryDescriptor ( p_file, p_descriptor );
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

static T_mkCode mk_fat_addCluster ( T_mkFile* p_file, uint32_t* p_firstCluster, uint32_t p_clusterNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_lastCluster = 0;

   /* Si le fichier est vide */
   if ( p_file->descriptor.fat.size == 0 )
   {
      /* Création d'un nouveau cluster */
      l_result = mk_fat_utils_appendCluster ( p_file, 0, p_firstCluster, 1 );

      /* Actualisation du nombre de clusters à ajouter */
      p_clusterNumber = ( uint32_t ) ( p_clusterNumber - 1 );

      /* Configuration de la valeur du dernier cluster du fichier */
      l_lastCluster = ( *p_firstCluster );
   }

   /* Sinon */
   else
   {
      /* Récupération de l'index du dernier cluster présent dans le fichier */
      l_result = mk_fat_utils_findCluster ( p_file, p_file->descriptor.fat.firstCluster, &l_lastCluster, K_MK_FAT_LAST_CLUSTER );
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ajout d'une chaine de clusters dans le fichier */
      l_result = mk_fat_utils_appendCluster ( p_file, l_lastCluster, &l_lastCluster, p_clusterNumber );
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

T_mkCode mk_fat_expand ( T_mkFile* p_file, uint32_t p_newFileSize )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un descripteur de fichier */
   T_mkFATEntryDescriptor l_fileEntryDescriptor;

   /* Déclaration des variables de travail */
   uint32_t l_currentClusterNumber = 0, l_newClusterNumber = 0, l_firstCluster = 0;

   /* Si le paramètre est valide */
   if ( ( p_file != K_MK_NULL ) )
   {
      /* Si le fichier peut être accédé en écriture */
      if ( p_file->flag.write == 1 )
      {
         /* Si la taille demandée par l'utilisateur est supérieure à la taille du fichier */
         if ( p_newFileSize > p_file->descriptor.fat.size )
         {
            /* Si le fichier n'est pas vide */
            if ( p_file->descriptor.fat.size != 0 )
            {
               /* Détermination du nombre de clusters pour la taille actuelle du fichier */
               l_currentClusterNumber = ( uint32_t ) ( 1 + ( ( p_file->descriptor.fat.size - 1 ) >> p_file->volume->partition.fat.sClusterSize ) );

               /* Détermination du nombre de clusters pour la nouvelle taille du fichier */
               l_newClusterNumber = ( uint32_t ) ( 1 + ( ( p_newFileSize - 1 ) >> p_file->volume->partition.fat.sClusterSize ) );

               /* Détermination du nombre de cluster à ajouter au fichier */
               l_currentClusterNumber = ( uint32_t ) ( l_newClusterNumber - l_currentClusterNumber );
            }

            /* Sinon */
            else
            {
               /* Détermination du nombre de clusters pour la nouvelle taille du fichier */
               l_currentClusterNumber = ( uint32_t ) ( 1 + ( ( p_newFileSize - 1 ) >> p_file->volume->partition.fat.sClusterSize ) );
            }

            /* Si le nombre de clusters à allouer est inférieur au nombre de clusters disponibles */
            if ( l_currentClusterNumber <= p_file->volume->partition.fat.numberOfFreeCluster )
            {
               /* Récupération du descripteur de fichier */
               l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_fileEntryDescriptor );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Si au moins un cluster doit être ajouté au fichier */
                  if ( l_currentClusterNumber != 0 )
                  {
                     /* Ajout d'un groupe de clusters à la fin du fichier */
                     l_result = mk_fat_addCluster ( p_file, &l_firstCluster, l_currentClusterNumber );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

                  /* Si aucune erreur ne s'est produite */
                  if ( l_result == K_MK_OK )
                  {
                     /* Configuration de la nouvelle taille du fichier */
                     l_result = mk_fat_setFileSize ( p_file, &l_fileEntryDescriptor, l_firstCluster, p_newFileSize );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

                  /* Si aucune erreur ne s'est produite */
                  if ( l_result == K_MK_OK )
                  {
                     /* Mise à jour du cluster courant */
                     /* Nécessaire lorsque le pointeur de fichier est à la fin de celui en limite de cluster */
                     l_result = mk_fat_seek ( p_file, p_file->descriptor.fat.currentPointer );
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
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_FULL;
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



