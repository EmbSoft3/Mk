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
* @file mk_loader_flushLibraries.c
* @brief Définition de la fonction mk_loader_flushLibraries.
* @date 20 janv. 2024
*
*/

#include "mk_loader_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_loader_flushLibraries ( T_mkExternalLibrariesList* p_list )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de bibliothèques */
   T_mkExternalLibraryItem* l_item = p_list->first;

   /* Si le paramètre est valide */
   if ( p_list != K_MK_NULL )
   {
      /* Tant que la liste n'a pas été entièrement parcourue */
      while ( ( l_item != K_MK_NULL ) && ( l_result == K_MK_OK ) )
      {
         /* Si une page mémoire a été allouée */
         if ( l_item->baseAddr != K_MK_NULL )
         {
            /* Désallocation de la page mémoire */
            l_result |= mk_application_free ( l_item->baseAddr );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désallocation de la bibliothèque */
         l_result = mk_pool_freeSafe ( g_mkExternalLibraryItemPool.pool, l_item );

         /* Passage à la prochaine bibliothèque */
         l_item = l_item->next;
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Réinitialisation du pointeur de début de liste */
         p_list->first = K_MK_NULL;
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


