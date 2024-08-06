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
* @file mk_fat_utils_getNumberOfEntries.c
* @brief Définition de la fonction mk_fat_utils_getNumberOfEntries.
* @date 27 déc. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_fat_utils_getNumberOfEntries ( T_str8 p_fileName )
{
   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_entriesNumber = 0, l_remainder = 0;

   /* Récupération de la taille de la chaine de caractères */
   l_length = mk_utils_utfsize ( p_fileName, K_MK_FONT_UTF8 );

   /* Si la chaine de caractères est valide */
   if ( l_length != 0 )
   {
      /* Détermination du nombre d'entrées */
      l_entriesNumber = l_length / K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY;

      /* Détermination du reste */
      l_remainder = _math_mod ( l_length, K_MK_FAT_NUMBER_OF_CHARACTER_PER_ENTRY );

      /* Si un reste est présent */
      if ( l_remainder != 0 )
      {
         /* Actualisation du nombre d'entrées */
         l_entriesNumber++;
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
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_entriesNumber );
}


