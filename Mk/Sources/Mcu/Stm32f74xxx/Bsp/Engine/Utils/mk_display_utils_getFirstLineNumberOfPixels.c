/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_utils_getFirstLineNumberOfPixels.c
* @brief Définition de la fonction mk_display_utils_getFirstLineNumberOfPixels.
* @date 12 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_display_utils_getFirstLineNumberOfPixels ( T_mkFont* p_font, T_str8 p_string, T_mkFontUnicode p_fontEncoding, uint32_t p_width )
{
   /* Déclaration d'un lot de variables stockant la valeur unicode du caractère courant, */
   /* ainsi que la largeur et l'offset du caractère courant */
   uint32_t l_currentChar = 0, l_charLength = 0, l_charBaseAddr = 0;

   /* Déclaration d'une variable stockant la longueur de la ligne en pixel */
   uint32_t l_pixelLength = 0;

   /* Déclaration d'un compteur stockant le nombre de caractères de la ligne */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable d'état permettant d'arrêter la boucle */
   uint32_t l_break = 0;

   /* Récupération de la valeur du premier caractère de la chaine */
   p_string = mk_font_parseString ( p_string, &l_currentChar, p_fontEncoding );

   /* Tant que le processus d'analyse n'est pas terminé (fin de ligne, fin de chaine ou ligne entièrement remplie) */
   while ( ( l_currentChar != ( uint32_t ) '\n' ) && ( l_currentChar != 0x00 ) && ( l_break == 0 ) )
   {
      /* Récupération des informations relatives au caractère courant */
      mk_font_selectPage ( p_font, l_currentChar, &l_charBaseAddr, &l_charLength );

      /* Si le caractère courant est le caractère '\t' */
      if ( l_currentChar == '\t' )
      {
         /* Insertion d'une tabulation */
         l_pixelLength = ( uint32_t ) ( l_pixelLength + ( uint32_t ) p_font->tabulationNumberOfPixels );
      }

      /* Sinon */
      else
      {
         /* Si un retour à la ligne doit être réalisé (ligne remplie) */
         if ( ( uint32_t ) ( l_pixelLength + l_charLength ) > p_width )
         {
            /* Arrêt de la boucle */
            l_break = 1;
         }

         /* Sinon */
         else
         {
            /* Actualisation de la taille de la ligne (en pixel) */
            l_pixelLength = ( uint32_t ) ( l_pixelLength + l_charLength + ( uint32_t ) p_font->numberOfPixelsBetweenChars );
         }
      }

      /* Actualisation du compteur de caractères */
      l_counter = ( uint32_t ) ( l_counter + 1 );

      /* Si l'analyse doit continuée (ligne non remplie) */
      if ( l_break == 0 )
      {
         /* Récupération de la valeur du prochain caractère de la chaine */
         p_string = mk_font_parseString ( p_string, &l_currentChar, p_fontEncoding );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si au moins un caractère était présent dans la chaine */
   if ( l_counter != 0 )
   {
      /* L'espace entre 2 caractères ne doit pas être ajouté sur le dernier caractère de la chaine */
      l_pixelLength = ( uint32_t ) ( l_pixelLength - ( uint32_t ) p_font->numberOfPixelsBetweenChars );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_pixelLength );
}

