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
* @file mk_disk_read.c
* @brief Définition de la fonction mk_disk_read.
* @date 27 juin 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_disk_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant le type du périphérique */
   T_mkDiskType* l_device = p_disk->device;

   /* Si le paramètre est valide */
   if ( p_disk != K_MK_NULL )
   {
      /* Si le périphérique est de type 'MSC' */
      if  ( *l_device == K_MK_DISK_TYPE_MSC_DEVICE )
      {
         /* Lecture d'un ou plusieurs secteurs du périphérique MSC */
         l_result = mk_msc_read ( p_disk, p_blockAddress, p_buf, p_numberOfBlockToRead, p_numberOfBytesRead, K_MK_NULL );
      }

      /* Sinon si le périphérique est de type 'MMC' */
      else if ( *l_device == K_MK_DISK_TYPE_MMC_DEVICE )
      {
         /* Lecture d'un ou plusieurs secteurs du périphérique MMC */
         l_result = mk_mmc_read ( p_disk, p_blockAddress, p_buf, p_numberOfBlockToRead, p_numberOfBytesRead, K_MK_NULL );
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

   /* Retour */
   return ( l_result );
}
