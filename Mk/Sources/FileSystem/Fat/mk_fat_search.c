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
* @file mk_fat_search.c
* @brief Définition de la fonction mk_fat_search.
* @date 10 janv. 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_fat_search ( T_mkVolume* p_volume, T_mkFile* p_file, T_str8 p_filePath, uint32_t p_baseCluster, uint16_t p_entry )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un buffer de travail */
   uint8_t l_filePath [ K_MK_FILE_MAX_NAME_LENGTH + 1 ];

   /* Si les paramètres sont valides */
   if ( ( p_volume != K_MK_NULL ) && ( p_file != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Actualisation de l'adresse de la partition du fichier */
      p_file->volume = p_volume;

      /* Recherche du fichier demandé par l'utilisateur */
      l_result = mk_fat_utils_findFile ( p_file, p_filePath, ( T_str8 ) l_filePath, p_baseCluster, p_entry );
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


