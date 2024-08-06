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
* @file mk_fat_utils_findName.c
* @brief Définition de la fonction mk_fat_utils_findName.
* @date 27 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_utils_findName ( T_mkFile* p_file, T_mkFATHandler* p_handler, T_str8 p_fileName, T_str8 p_fatEntryName, uint8_t* p_checksum )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint16_t l_fileIndex = 1;

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_handler != K_MK_NULL ) && ( p_fileName != K_MK_NULL ) && ( p_fatEntryName != K_MK_NULL ) && ( p_checksum != K_MK_NULL ) )
   {
      /* Tant que le nom du fichier à générer n'est pas unique ou tant que le nombre de collisions n'a pas été atteint */
      while ( ( l_result != K_MK_ERROR_NOT_FOUND ) && ( l_fileIndex < K_MK_FAT_COLLISION_NUMBER ) )
      {
         /* Récupération d'un nom au format 8.3 à partir d'un nom de fichier long */
         l_result = mk_fat_utils_setName ( p_fileName, p_fatEntryName, K_MK_NULL, p_checksum, K_MK_FAT_ENTRY_EX, l_fileIndex );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Analyse de l'existence du fichier */
            l_result = mk_fat_utils_findFile ( p_file, p_fatEntryName, p_fatEntryName, p_handler->currentCluster, 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de l'index du fichier */
         l_fileIndex++;
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
