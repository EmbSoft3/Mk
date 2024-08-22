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
* @file mk_application_addDeletedList.c
* @brief Définition de la fonction mk_application_addDeletedList.
* @date 5 août 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_addDeletedList ( T_mkApplication* p_application, uint32_t p_elapseCounter )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'élément */
   T_mkApplicationGarbageItem* l_newGarbageItem = K_MK_NULL;

   /* Si le paramètre est valide */
   if ( p_application != K_MK_NULL )
   {
      /* Allocation d'un nouvel élément */
      l_result = mk_pool_allocSafe ( g_mkDisplay.application.deletedPool, ( T_mkAddr* ) &l_newGarbageItem, K_MK_POOL_NO_CLEAR, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Le nouvelle élément est ajouté en tête de liste */
         l_newGarbageItem->previous = K_MK_NULL;
         l_newGarbageItem->application = p_application;
         l_newGarbageItem->elapseCounter = p_elapseCounter;

         /* Si la liste est vide */
         if ( g_mkDisplay.application.list.deleted == K_MK_NULL )
         {
            /* Initialisation des attributs de la liste */
            /* Le pointeur "Next" indique la fin de liste */
            g_mkDisplay.application.list.deleted = l_newGarbageItem;
            l_newGarbageItem->next = K_MK_NULL;
         }

         /* Sinon */
         else
         {
            /* Le pointeur "next" pointe sur le premier élément de la liste */
            l_newGarbageItem->next = g_mkDisplay.application.list.deleted;
            g_mkDisplay.application.list.deleted->previous = l_newGarbageItem;

            /* Actualisation du pointeur de liste */
            g_mkDisplay.application.list.deleted = l_newGarbageItem;
         }
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


