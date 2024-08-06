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
* @file mk_fat_utils_read.c
* @brief Définition de la fonction mk_fat_utils_read.
* @date 27 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_read ( T_mkFile* p_file, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint32_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint64_t l_numberOfBytesRead = 0;

   /* Si le secteur à lire est présent dans le cache */
   if ( ( ( p_blockAddress >= p_file->cacheCurrentAddress ) && ( p_blockAddress < ( p_file->cacheCurrentAddress + p_file->volume->partition.fat.numberOfBlocksPerWindow ) ) ) ||
      ( ( ( p_blockAddress + p_numberOfBlockToRead ) >= p_file->cacheCurrentAddress ) && ( ( p_blockAddress + p_numberOfBlockToRead ) < ( p_file->cacheCurrentAddress + p_file->volume->partition.fat.numberOfBlocksPerWindow ) ) ) )
   {
      /* Ecriture du groupe de secteurs présents dans le cache sur le disque */
      l_result = mk_fat_utils_sync ( p_file );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Lecture d'un secteur sur le disque */
      l_result = mk_disk_read ( ( T_mkDisk* ) p_file->volume->disk, p_blockAddress, p_buf, p_numberOfBlockToRead, &l_numberOfBytesRead );

      /* Si aucune erreur ne s'est produtie */
      if ( ( l_result != K_MK_OK ) || ( l_numberOfBytesRead != ( ( uint64_t ) p_numberOfBlockToRead * ( uint64_t ) p_file->volume->partition.fat.bytesPerSector ) ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_COMM;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du nombre d'octets lus */
      *p_numberOfBytesRead = ( uint32_t ) ( l_numberOfBytesRead );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


