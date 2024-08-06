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
* @file mk_editField_getCursorOffsetDown.c
* @brief Définition de la fonction mk_editField_getCursorOffsetDown.
* @date 18 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_editField_getCursorOffsetDown ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_mkVect2Di p_cursorVector, T_str8 p_windowBaseAddr )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = p_editField->windowBaseOffset;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 0;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = p_windowBaseAddr;

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
   mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, p_windowBaseAddr, p_editField->windowCurrentNumberOfRow, &p_editField->style );

   /* Initialisation du vecteur courant */
   mk_vect2d_setCoord2Di ( &l_currentVect, l_rowVect.x, l_rowVect.y );

   /* Récupération de la valeur du premier caractère de la chaine */
   l_str = mk_font_parseString ( p_windowBaseAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );

   /* Tant que les traitements ne sont pas terminés */
   while ( ( l_currentChar != 0 ) && ( l_ret == 0 ) )
   {
      /* Récupération des informations relatives au caractère courant */
      mk_font_selectPage ( p_editField->style.font, l_currentChar, &l_charBaseAddr, &l_charLength );

      /* Test si l'ajout d'un nouveau caractère produit un chevauchement */
      ( void ) mk_display_utils_getNewLineOverlap ( &p_editField->style, &l_currentVect, l_charLength, &l_endOfRow, p_v2.x, p_v2.y );

      /* Si le caractère courant est le caractère '\n' ou si une ligne a été complétement remplie */
      /* Réalisation d'un retour à la ligne */
      if ( ( l_currentChar == '\n' ) || ( l_endOfRow == 1 ) )
      {
         /* Si la fin de ligne n'a pas été causé par un retour à la ligne explicite */
         if ( l_endOfRow == 0 )
         {
            /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
            mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, l_str, p_editField->windowCurrentNumberOfRow, &p_editField->style );
         }

         /* Sinon */
         else
         {
            /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
            mk_display_utils_getFirstLinePosition ( &p_v1, &p_v2, &l_rowVect, p_windowBaseAddr, p_editField->windowCurrentNumberOfRow, &p_editField->style );
         }

         /* Cas particulier pour la justification à droite (\n) */
         /* Gestion du cas où la taille de la prochaine ligne du curseur est inférieure     __________   */
         /* à la taille de la ligne actuelle.                                                    ____|   */
         if ( ( l_endOfRow == 0 ) && ( p_cursorVector.x < l_rowVect.x ) &&
              ( ( l_currentVect.y + p_editField->style.font->height + p_editField->style.font->numberOfPixelsBetweenRows ) == p_cursorVector.y ) && ( l_currentVect.x > p_cursorVector.x ) )
         {
            /* Actualisation du compteur de caractères */
            l_result = ( uint32_t ) ( l_result + 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
 
         /* Initialisation du vecteur courant en début de ligne */
         mk_vect2d_setCoord2Di ( &l_currentVect, l_rowVect.x, l_rowVect.y );

         /* Actualisation du compteur de lignes */
         l_rowCounter = ( uint32_t ) ( l_rowCounter + 1 );

         /* Actualisation de la ccoordonnée 'y' du vecteur courant */
         l_currentVect.y += ( uint32_t ) ( l_rowCounter * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) );

         /* Cas particulier pour la justification à gauche */
         /* Gestion du cas où la taille de la prochaine ligne du curseur est inférieure     __________   */
         /* à la taille de la ligne actuelle.                                               ____|        */
         if ( ( l_endOfRow == 1 ) && ( l_currentVect.y > p_cursorVector.y ) )
         {
            /* Actualisation du compteur de caractères */
            l_result = ( uint32_t ) ( l_result - 1 );
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

      /* Si le caractère courant est le caractère '\r' */
      if ( l_currentChar == '\r' )
      {
         /* Ne rien faire */
      }

      /* Sinon si le caractère courant est le caractère '\t' */
      else if ( l_currentChar == '\t' )
      {
         /* Insertion d'une tabulation */
         l_currentVect.x += ( uint32_t ) p_editField->style.font->tabulationNumberOfPixels;
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

      /* Si la prochaine position du curseur a été atteinte */
      if ( ( ( l_currentVect.y == p_cursorVector.y ) && ( l_currentVect.x > p_cursorVector.x ) ) ||
           ( l_currentVect.y == ( p_cursorVector.y + ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) ) ) )
      {
         /* Arrêt de la boucle */
         l_ret = 1;
      }

      /* Sinon */
      else
      {
         /* Actualisation du compteur de caractères */
         l_result = ( uint32_t ) ( l_result + 1 );
      }

      /* Actualisation de la valeur du pointeur de chaine de caractères */
      p_windowBaseAddr = l_str;

      /* Récupération de la valeur du prochain caractère de la chaine */
      l_str = mk_font_parseString ( p_windowBaseAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );
   }

   /* Retour */
   return ( l_result );
}



