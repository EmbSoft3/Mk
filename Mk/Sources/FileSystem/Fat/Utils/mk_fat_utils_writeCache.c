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
* @file mk_fat_utils_writeCache.c
* @brief Définition de la fonction mk_fat_utils_writeCache.
* @date 8 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_writeCache ( T_mkFile* p_file, uint64_t p_blockAddress )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable indiquant le nombre d'octets écrits dans le secteur */
   uint64_t l_numberOfByteWrite = 0;

   /* Si le secteur à écrire est déjà présent dans le cache */
   if ( ( p_blockAddress >= p_file->cacheCurrentAddress ) &&
        ( p_blockAddress < ( p_file->cacheCurrentAddress + p_file->volume->partition.fat.numberOfBlocksPerWindow ) ) )
   {
      /* Positionnement d'un drapeau indiquant que le cache doit être mis à jour */
      p_file->cacheFlushFlag = 1;
   }

   /* Sinon */
   else
   {
      /* Si le cache doit être actualisé */
      if ( p_file->cacheFlushFlag == 1 )
      {
         /* Ecriture d'un groupe de secteurs sur le disque */
         l_result = mk_disk_write ( ( T_mkDisk* ) p_file->volume->disk, p_file->cacheCurrentAddress,
                                    p_file->cacheBaseAddress, p_file->volume->partition.fat.numberOfBlocksPerWindow, &l_numberOfByteWrite );

         /* Si une erreur s'est produite */
         if ( ( l_result != K_MK_OK ) || ( l_numberOfByteWrite != ( p_file->volume->partition.fat.numberOfBlocksPerWindow * p_file->volume->partition.fat.bytesPerSector ) ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_COMM;
         }

         /* Sinon */
         else
         {
            /* Positionnement d'un drapeau indiquant que le cache est à jour */
            p_file->cacheFlushFlag = 0;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de l'adresse du cache */
      p_file->cacheCurrentAddress = ( uint32_t ) p_blockAddress;
   }

   /* Retour */
   return ( l_result );
}


