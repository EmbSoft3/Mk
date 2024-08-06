/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_container_paint.c
* @brief Définition de la fonction mk_container_paint.
* @date 5 mai 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_container_paint ( T_mkContainer* p_container, T_mkField** p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   T_mkField* l_tmp = p_container->first;

   /* Pour tous les champs présents dans le container */
   while ( ( l_tmp != K_MK_NULL ) && ( l_result == K_MK_OK) )
   {
      /* Si le champ possède une fonction de peinture et si le champ doit être rafraichi */
      if ( ( l_tmp->painter != K_MK_NULL ) && ( l_tmp->visibility == K_MK_FIELD_VISIBLE ) )
      {
         /* Si un pointeur a été référencé */
         if ( p_field != K_MK_NULL )
         {
            /* Enregistrement de l'adresse du champ en cours de traitement */
            *p_field = l_tmp;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Déclenchement de la fonction de peinture du champ */
         l_result = l_tmp->painter ( p_container, l_tmp, l_tmp->frameNumber );

         /* On actualise la valeur du compteur de frame d'une unité. */
         l_tmp->frameNumber = ( uint32_t ) ( l_tmp->frameNumber + 1 );

         /* Si le compteur de frame doit être réinitialisé */
         if ( l_tmp->frameNumber == K_MK_DISPLAY_FRAMERATE )
         {
            /* Réinitialisation de la valeur de l'index */
            l_tmp->frameNumber = 0;
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

      /* Passage au champ suivant */
      l_tmp = l_tmp->next;
   }

   /* Retour */
   return ( l_result );
}


