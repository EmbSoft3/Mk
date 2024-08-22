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
* @file mk_editField_getWindowAddr.c
* @brief Définition de la fonction mk_editField_getWindowAddr.
* @date 16 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_str8 mk_editField_getWindowAddr ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_str8 p_strAddr, uint32_t p_row, uint32_t* p_cursorOffset )
{
   /* Déclaration de la variable de retour */
   T_str8 l_result = p_strAddr;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = p_strAddr;

   /* Déclaration d'un pointeur de caractères */
   uint32_t l_currentCounter = 0;

   /* Déclaration d'un lot de variables stockant la valeur unicode du caractère courant, */
   /* ainsi que la largeur et l'offset du caractère courant */
   uint32_t l_currentChar = 0, l_charLength = 0, l_charBaseAddr = 0;

   /* Déclaration d'un lot de variables stockant l'offset de la première ligne à dessiner */
   /* et l'état de remplissage d'une ligne (entièrement remplie ou non) */
   uint32_t l_rowCounter = 0, l_endOfRow = 0;

   /* Déclaration des vecteurs de travail qui stockent les coordonnées du caractère courant */
   /* et les coordonnées de début de ligne. */
   T_mkVect2Di l_currentVect = { 0, 0 }, l_rowVect = { 0, 0 };

   /* Détermination des coordonnées du vecteur position pour la première ligne */
   mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, p_strAddr, p_editField->windowCurrentNumberOfRow, &p_editField->style );

   /* Initialisation du vecteur courant */
   mk_vect2d_setCoord2Di ( &l_currentVect, l_rowVect.x, l_rowVect.y );

   /* Récupération de la valeur du premier caractère de la chaine */
   l_str = mk_font_parseString ( p_strAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );

   /* Si l'offset du curseur doit être récupérée */
   if ( p_cursorOffset != K_MK_NULL )
   {
      /* Enregistrement de la position du curseur */
      *p_cursorOffset = 0;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Tant que les traitements ne sont pas terminés */
   while ( ( l_rowCounter != p_row ) && ( l_currentChar != 0 ) )
   {
      /* Récupération des informations relatives au caractère courant */
      mk_font_selectPage ( p_editField->style.font, l_currentChar, &l_charBaseAddr, &l_charLength );

      /* Test si l'ajout d'un nouveau caractère produit un chevauchement */
      ( void ) mk_display_utils_getNewLineOverlap ( &p_editField->style, &l_currentVect, l_charLength, &l_endOfRow, p_v2.x, p_v2.y );

      /* Si le caractère courant est le caractère '\n' ou si une ligne a été complétement remplie */
      /* Réalisation d'un retour à la ligne */
      if ( ( l_currentChar == '\n' ) || ( l_endOfRow == 1 ) )
      {
         /* Actualisation du compteur de ligne */
         l_rowCounter = ( uint32_t ) ( l_rowCounter + 1 );

         /* Si la fin de ligne n'a pas été causé par un retour à la ligne explicite */
         if ( l_endOfRow == 0 )
         {
            /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
            mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, l_str, p_editField->windowCurrentNumberOfRow, &p_editField->style );

            /* Enregistrement de l'adresse de la prochaine ligne */
            l_result = l_str;
         }

         /* Sinon */
         else
         {
            /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
            mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, p_strAddr, p_editField->windowCurrentNumberOfRow, &p_editField->style );

            /* Enregistrement de l'adresse de la prochaine ligne */
            l_result = p_strAddr;
         }

         /* Si l'offset du curseur doit être récupérée */
         if ( p_cursorOffset != K_MK_NULL )
         {
            /* Enregistrement de la position du curseur */
            *p_cursorOffset = ( l_currentCounter + 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Initialisation du vecteur courant en début de ligne */
         mk_vect2d_setCoord2Di ( &l_currentVect, l_rowVect.x, l_rowVect.y );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le caractère courant est le caractère '\r' */
      if ( l_currentChar == '\r' )
      {
         /* Ne rien faire */
      }

      /* Sinon si le caractère courant est le caractère '\t' */
      else if ( l_currentChar == '\t' )
      {
         /* Insertion d'une tabulation */
         l_currentVect.x += ( uint32_t ) p_editField->style.font->tabulationNumberOfPixels;;
      }

      /* Sinon si le caractère courant est le caractère '\n' */
      else if ( l_currentChar != '\n' )
      {
         /* Actualisation de l'abscisse */
         l_currentVect.x += l_charLength + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenChars;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du compteur de caractères */
      l_currentCounter = ( uint32_t ) ( l_currentCounter + 1 );

      /* Actualisation de la valeur du pointeur de chaine de caractères */
      p_strAddr = l_str;

      /* Récupération de la valeur du prochain caractère de la chaine */
      l_str = mk_font_parseString ( p_strAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );
   }

   if ( ( ( p_editField->cursorBaseOffset ) == l_currentCounter ) && ( l_rowCounter != p_row ) )
   {
      /* Test si l'ajout d'un nouveau caractère produit un chevauchement */
      ( void ) mk_display_utils_getNewLineOverlap ( &p_editField->style, &l_currentVect, ( l_charLength + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenChars + p_editField->cursor->width ), &l_endOfRow, p_v2.x, p_v2.y );

      /* Si le curseur est situé sur une autre ligne */
      if ( l_endOfRow == 1 )
      {
         /* Enregistrement de l'adresse de la prochaine ligne */
         l_result = p_strAddr;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Retour */
   return ( l_result );
}



