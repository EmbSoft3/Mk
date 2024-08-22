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
* @file mk_font_addPage.c
* @brief Définition de la fonction mk_font_addPage.
* @date 1 juil. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_font_addPage ( T_mkFont* p_font, T_mkFontPage* p_page )
{
   /* Si les paramètres sont valides */
   if ( ( p_font != K_MK_NULL ) && ( p_page != K_MK_NULL ) )
   {
      /* La page est ajoutée en fin de liste */
      p_page->next = K_MK_NULL;

      /* Si la liste est vide */
      if ( p_font->firstPageAddr == K_MK_NULL )
      {
         /* La liste contient un seul élement, les pointeurs 'next' et */
         /* 'previous' doivent pointer sur la valeur nulle. */
         p_page->previous = K_MK_NULL;

         /* Configuration des pointeurs de début et de fin de liste */
         p_font->firstPageAddr = p_page;
         p_font->lastPageAddr = p_page;
      }

      /* Sinon */
      else
      {
         /* Actualisation du pointeur 'previous' du nouvel élément */
         p_page->previous = p_font->lastPageAddr;
         /* Actualisation du pointeur 'next' de l'élement précédent */
         p_font->lastPageAddr->next = p_page;

         /* Le nouvel élément est situé en fin de liste */
         p_font->lastPageAddr = p_page;
      }
   }

   /* Sinon */
   else
   {
      /*Ne rien faire */
   }

   /* Retour */
   return;
}


