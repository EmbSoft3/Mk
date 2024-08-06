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
* @file mk_fat_utils_setCluster.c
* @brief Définition de la fonction mk_fat_utils_setCluster.
* @date 11 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_setCluster ( T_mkFile* p_file, uint32_t p_cluster, uint32_t* p_nextCluster, uint32_t p_value )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de buffer */
   uint32_t* l_buf = K_MK_NULL;

   /* Déclaration des variables de travail */
   uint32_t l_offset = 0, l_counter = 0, l_numberOfBytesWrite = 0;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) &&
      ( ( p_cluster >= p_file->volume->partition.fat.firstRootDirectoryCluster ) && ( p_cluster < K_MK_FAT_VALID_CLUSTER ) ) )
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
         *p_nextCluster = ( uint32_t ) l_buf [ l_offset ];

         /* Ecriture de la nouvelle valeur dans le cluster */
         l_buf [ l_offset ] = ( uint32_t ) ( ( l_buf [ l_offset ] & ( uint32_t ) ( ~ K_MK_FAT_CLUSTER_MASK ) ) | ( p_value & K_MK_FAT_CLUSTER_MASK ) );

         /* Ecriture de la première FAT */
         l_result = mk_fat_utils_writeCache ( p_file,  ( uint64_t ) ( p_file->volume->partition.fat.addressOfFAT + ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) ) );

         /* Pour le nombre de FAT restant à mettre à jour */
         for ( l_counter = 1 ; ( l_result == K_MK_OK ) && ( l_counter < p_file->volume->partition.fat.numberOfFAT ) && ( l_counter < K_MK_FAT_NUMBER_OF_FAT_TO_UPDATE ); l_counter++ )
         {
            /* Ecriture du secteur de données */
            /* La cache d'écriture n'est pas utilisé car deux appels consécutifs de la fonction d'écriture provoque une corruption */
            l_result = mk_fat_utils_write ( p_file,  ( uint64_t ) ( p_file->volume->partition.fat.addressOfFAT +
                  ( l_counter * p_file->volume->partition.fat.sectorsPerFAT ) + ( p_cluster >> p_file->volume->partition.fat.sNumberOfClusterEntriesPerSector ) ), p_file->buf, 1, &l_numberOfBytesWrite );
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         *p_nextCluster = K_MK_FAT_LAST_CLUSTER;
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



