/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_application_add.c
* @brief Définition de la fonction mk_application_add.
* @date 17 août 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_application_add ( T_mkApplicationList* p_list, T_mkApplication* p_application )
{
   /* L'application est ajouté en fin de liste */
   p_application->next = K_MK_NULL;

   /* Si la liste est vide */
   if ( p_list->first == K_MK_NULL )
   {
      /* La liste contient un seul élement, les pointeurs 'next' et */
      /* 'previous' doivent pointer sur la valeur nulle. */
      p_application->previous = K_MK_NULL;

      /* Configuration des pointeurs de début et de fin de liste */
      p_list->first = p_application;
      p_list->last = p_application;
   }

   /* Sinon */
   else
   {
      /* Actualisation du pointeur 'previous' du nouvel élément */
      p_application->previous = p_list->last;
      /* Actualisation du pointeur 'next' de l'élement précédent */
      p_list->last->next = p_application;

      /* Le nouvel élément est situé en fin de liste */
      p_list->last = p_application;
   }

   /* Retour */
   return;
}



