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
* @file mk_application_removeDeletedList.c
* @brief Définition de la fonction mk_application_removeDeletedList.
* @date 5 août 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_removeDeletedList ( T_mkApplicationGarbageItem* p_garbageItem )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_garbageItem != K_MK_NULL )
   {
      /* Si l'élément à supprimer n'est pas en tête de liste */
      if ( p_garbageItem->previous != K_MK_NULL )
      {
         /* Actualisation du périphérique précédent */
         p_garbageItem->previous->next = p_garbageItem->next;
      }

      /* Sinon */
      else
      {
         /* Actualisation du pointeur de liste */
         g_mkDisplay.application.list.deleted = p_garbageItem->next;
      }

      /* Si le périphérique à supprimer n'est pas en fin de liste */
      if ( p_garbageItem->next != K_MK_NULL )
      {
         /* Actualisation du prochain périphérique */
         p_garbageItem->next->previous = p_garbageItem->previous;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Suppression de l'élément */
      l_result = mk_pool_freeSafe ( g_mkDisplay.application.deletedPool, p_garbageItem );
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

