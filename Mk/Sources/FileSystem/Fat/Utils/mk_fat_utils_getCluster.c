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
* @file mk_fat_utils_getCluster.c
* @brief Définition de la fonction mk_fat_utils_getCluster.
* @date 30 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_getCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_clusterNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = K_MK_NULL;

   /* Déclaration d'une variable de travail */
   uint32_t l_offset = 0, l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_nextCluster != K_MK_NULL ) &&
      ( ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_cluster < K_MK_FAT_VALID_CLUSTER ) ) )
   {
      /* Ecriture d'une valeur par défaut dans la variable de retour */
      p_nextCluster [ 0 ] = K_MK_FAT_VALID_CLUSTER;

      /* Pour le nombre de clusters à rechercher */
      for ( l_counter = 0 ; ( l_result == K_MK_OK ) && ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) &&
          ( p_cluster < K_MK_FAT_VALID_CLUSTER ) && ( l_counter < p_clusterNumber ) ;
          l_counter++ )
      {
         /* Lecture du secteur de données */
         l_result = mk_fat_utils_readCache ( p_file, ( uint64_t ) ( p_file->volume->partition.fat.addressOfFAT +
               ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Conversion du buffer du fichier en 32 bits (cast) */
            l_buf = ( T_mkAddr ) p_file->buf;

            /* Détermination de l'offset du cluster dans la buffer */
            l_offset = ( uint32_t ) ( _math_mod2 ( p_cluster, p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) );

            /* Détermination de l'adresse du prochain cluster */
            p_nextCluster [ l_counter ] = ( uint32_t ) ( l_buf [ l_offset ] & K_MK_FAT_CLUSTER_MASK );

            /* Si le cluster est invalide */
            if ( p_nextCluster [ l_counter ] < p_file->volume->partition.fat.firstRootDirectoryCluster )
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_CORRUPTED;
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
            /* Arrêt de la boucle */
            p_nextCluster [ l_counter ] = K_MK_FAT_VALID_CLUSTER;
         }

         /* Actualisation de l'adresse du cluster courant */
         p_cluster = p_nextCluster [ l_counter ];
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


