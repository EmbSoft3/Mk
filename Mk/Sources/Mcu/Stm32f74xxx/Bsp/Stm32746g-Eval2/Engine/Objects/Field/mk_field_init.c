/**
*
* @copyright Copyright (C) 2019-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_field_init.c
* @brief Définition de la fonction mk_field_init.
* @date 9 mai 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_field_init ( T_mkField* p_field )
{
   /* Si le paramètre est valide */
   if ( p_field != K_MK_NULL )
   {
      /* Configuration des attributs du champ */
      p_field->refresh = K_MK_FIELD_REFRESH_ENABLED;
      p_field->userRefresh = K_MK_FIELD_REFRESH_ENABLED;
      p_field->focus = K_MK_FIELD_STATE_IDLE;
      p_field->visibility = K_MK_FIELD_INVISIBLE;
      p_field->userVisibility = K_MK_FIELD_INVISIBLE;
      p_field->activity = K_MK_FIELD_INACTIF;
      p_field->layer = K_MK_GRAPHICS_FOREGROUND;
      p_field->zIndex = 0;

      /* Configuration de l'adresse des fonctions d'écoute et de peinture */
      p_field->listener = K_MK_NULL;
      p_field->painter = K_MK_NULL;

      /* Configuration de l'adresse du descendant (héritage) */
      p_field->child = K_MK_NULL;

      /* Configuration des pointeurs de liste */
      p_field->next = K_MK_NULL;
      p_field->previous = K_MK_NULL;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

