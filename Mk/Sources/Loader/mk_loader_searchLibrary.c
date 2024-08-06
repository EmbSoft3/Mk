/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_loader_searchLibrary.c
* @brief Définition de la fonction mk_loader_searchLibrary.
* @date 20 janv. 2024
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_loader_searchLibrary ( T_mkExternalLibrariesList* p_list, T_mkExternalLibraryItem** p_item, T_str8 p_libraryName )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_NOT_AVAILABLE;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 0;

   /* Déclaration d'un pointeur de bibliothèques */
   T_mkExternalLibraryItem* l_item = p_list->first;

   /* Si les paramètres sont valides */
   if ( ( p_list != K_MK_NULL ) && ( p_item != K_MK_NULL ) )
   {
      /* Tant que la liste n'a pas été entièrement parcourue */
      while ( ( l_item != K_MK_NULL ) && ( l_result == K_MK_ERROR_NOT_AVAILABLE ) )
      {
         /* Analyse du nom de la bibliothèque */
         l_ret = mk_utils_strcomp ( l_item->fileName, p_libraryName, 0, 0 );

         /* Si la bibliothèque recherchée a été trouvée */
         if ( l_ret == 1 )
         {
            /* Enregistrement de l'adresse de la bibliothèque */
            *p_item = l_item;

            /* Actualisation de la variable de retour */
            /* Arrêt de la boucle */
            l_result = K_MK_OK;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Passage à la prochaine bibliothèque */
         l_item = l_item->next;
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



