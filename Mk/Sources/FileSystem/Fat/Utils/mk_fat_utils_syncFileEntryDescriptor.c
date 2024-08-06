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
* @file mk_fat_utils_syncFileEntryDescriptor.c
* @brief Définition de la fonction mk_fat_utils_syncFileEntryDescriptor.
* @date 2 sept. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_synchFileEntryDescriptor ( T_mkFile* p_file )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un descripteur de fichier */
   T_mkFATEntryDescriptor l_descriptor;

   /* Récupération du descripteur de fichier */
   l_result = mk_fat_utils_getFileEntryDescriptor ( p_file, &l_descriptor );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le fichier n'a pas été supprimé */
      if ( l_descriptor.name [ 0 ] != K_MK_FAT_DELETED_ENTRY )
      {
         /* Actualisation de la taille du fichier */
         p_file->descriptor.fat.size = l_descriptor.fileSize;

         /* Si le pointeur de fichier est supérieur à la taille du fichier */
         if ( p_file->descriptor.fat.currentPointer > l_descriptor.fileSize )
         {
            /* Positionnement du pointeur de fichier à la fin de celui-ci */
            l_result = mk_fat_seek ( p_file, l_descriptor.fileSize );
         }

         /* Sinon si la taille du fichier est nulle */
         else if ( l_descriptor.fileSize == 0 )
         {
            p_file->descriptor.fat.currentCluster = 0;
            p_file->descriptor.fat.currentPointer = 0;
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
         /* Le fichier a été supprimée */
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_NOT_FOUND;
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


