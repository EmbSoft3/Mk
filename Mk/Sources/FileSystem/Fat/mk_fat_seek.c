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
* @file mk_fat_seek.c
* @brief Définition de la fonction mk_fat_seek.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_seek ( T_mkFile* p_file, uint32_t p_filePointer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_cluster = 0, l_clusterNumber = 0;

   /* Si le paramètre est valide */
   if ( p_file != K_MK_NULL )
   {
      /* Si la nouvelle valeur du pointeur de fichier est supérieure à la taille du fichier */
      if ( p_filePointer > p_file->descriptor.fat.size )
      {
         /* Le pointeur doit être placé à la fin du fichier */
         p_filePointer = p_file->descriptor.fat.size;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si au moins un cluster a été alloué dans le fichier */
      if ( p_file->descriptor.fat.firstCluster != 0 )
      {
         /* Détermination de l'index du nouveau cluster courant */
         l_clusterNumber = ( p_filePointer >> p_file->volume->partition.fat.sClusterSize );

         /* Récupération de l'adresse du nouveau cluster */
         l_result = mk_fat_utils_findCluster ( p_file, p_file->descriptor.fat.firstCluster, &l_cluster, l_clusterNumber + 1 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation des attributs du fichier */
            p_file->descriptor.fat.currentCluster = l_cluster;
            p_file->descriptor.fat.currentPointer = p_filePointer;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le fichier est vide */
      else if ( ( p_file->descriptor.fat.firstCluster == 0 ) && ( p_file->descriptor.fat.size == 0 ) )
      {
         /* Le pointeur doit être placé à la fin du fichier */
         p_filePointer = 0;
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


