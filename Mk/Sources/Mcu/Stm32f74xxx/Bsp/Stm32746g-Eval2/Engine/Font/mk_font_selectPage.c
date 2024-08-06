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
* @file mk_font_selectPage.c
* @brief Définition de la fonction mk_font_selectPage.
* @date 1 janv. 2020
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_font_searchCharacterPage ( T_mkFont* p_font, uint32_t p_codepoint, uint32_t* p_baseAddr, uint32_t* p_width )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration d'un pointeur de page */
   T_mkFontPage* l_page = p_font->firstPageAddr;

   /* Pour le nombre de pages de la police */
   while ( ( l_page != K_MK_NULL ) && ( l_result == 0 ) )
   {
      /* Si la page du caractère est la page en cours d'analyse */
      if ( ( p_codepoint >= l_page->firstCodePoint ) && ( p_codepoint <= l_page->lastCodePoint ) )
      {
         /* Récupération de la largeur du caractère */
         ( *p_width ) = ( uint32_t ) ( l_page->glyphDescriptorAddr [ ( p_codepoint - l_page->firstCodePoint ) << 1 ] );

         /* Récupération de l'adresse du caractère dans la table */
         ( *p_baseAddr ) = ( uint32_t ) ( l_page->glyphTableAddr + l_page->glyphDescriptorAddr [ ( ( p_codepoint - l_page->firstCodePoint ) << 1 ) + 1 ] );

         /* Actualisation de la variable de retour */
         l_result = 1;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Passage à la prochaine page */
      l_page = l_page->next;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_font_selectDefaultCharacter ( T_mkFont* p_font, uint32_t p_codepoint, uint32_t* p_baseAddr, uint32_t* p_width )
{
   /* Si le caractère est un caractère spécial */
   if ( ( p_codepoint == ( uint32_t ) '\n' ) || ( p_codepoint == ( uint32_t ) '\r' ) )
   {
      /* Configuration de la largeur par défaut */
      ( *p_width ) = p_font->numberOfPixelsBetweenChars;
   }

   /* Sinon si le caractère est une tabulation */
   else if ( p_codepoint == ( uint32_t ) '\t' )
   {
      /* Configuration de la largeur de la tabulation */
      ( *p_width ) = p_font->tabulationNumberOfPixels;
   }

   /* Sinon */
   else
   {
      /* Configuration de la largeur du caractère */
      ( *p_width ) = ( uint32_t ) ( p_font->firstPageAddr->glyphDescriptorAddr [ 0 ] );
   }

   /* Configuration de l'adresse du caractère dans la table */
   ( *p_baseAddr ) = ( uint32_t ) ( p_font->firstPageAddr->glyphTableAddr );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_font_selectPage ( T_mkFont* p_font, uint32_t p_codepoint, uint32_t* p_baseAddr, uint32_t* p_width )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Recherche du caractère parmis les pages de la police */
   l_result = mk_font_searchCharacterPage ( p_font, p_codepoint, p_baseAddr, p_width );

   /* Si le caractère n'a pas été trouvé */
   if ( l_result == 0 )
   {
      /* Si au moins une page est configurée dans la police de caractères */
      if ( p_font->firstPageAddr != K_MK_NULL )
      {
         /* Sélection d'un caractère par défaut */
         mk_font_selectDefaultCharacter ( p_font, p_codepoint, p_baseAddr, p_width );
      }

      /* Sinon */
      else
      {
         /* Sélection d'un caractère par défaut en utilisant la police par défaut */
         mk_font_selectDefaultCharacter ( &g_mkDisplay.defaultFont.handle, p_codepoint, p_baseAddr, p_width );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


