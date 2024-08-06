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
* @file mk_fat_utils_setFile.c
* @brief Définition de la fonction mk_fat_utils_setFile.
* @date 27 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_setFile ( T_mkFile* p_file, T_mkFATHandler* p_handler, uint32_t p_size )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_handler != K_MK_NULL ) )
   {
      /*  Enregistrement du cluster du répertoire où est localisé le fichier */
      p_file->descriptor.fat.directoryCluster = p_handler->directoryCluster;

      /*  Enregistrement du cluster de l'entrée standard où est localisé le fichier */
      p_file->descriptor.fat.entryCluster = p_handler->entryCluster;

      /*  Enregistrement du cluster de l'entrée virtuelle où est localisé le fichier */
      p_file->descriptor.fat.virtualEntryCluster = p_handler->entryVirtualCluster;

      /*  Enregistrement du premier cluster du fichier */
      p_file->descriptor.fat.firstCluster = ( uint32_t ) ( p_handler->firstDataCluster & K_MK_FAT_CLUSTER_MASK );

      /*  Enregistrement du cluster courant (par défaut pointe sur le premier cluster du fichier) */
      p_file->descriptor.fat.currentCluster = p_file->descriptor.fat.firstCluster;

      /*  Enregistrement de l'index de l'entrée dans le cluster */
      p_file->descriptor.fat.entryIndex = p_handler->entryClusterIndex;

      /*  Enregistrement de l'index de l'entrée étendue */
      p_file->descriptor.fat.virtualEntryIndex = p_handler->entryVirtualClusterIndex;

      /*  Enregistrement de la taille du fichier */
      p_file->descriptor.fat.size = p_size;

      /*  Remise à zéro du pointeur de cluster */
      p_file->descriptor.fat.currentPointer = 0;
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
