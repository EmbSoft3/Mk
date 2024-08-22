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
* @file mk_editField_setCursorVector.c
* @brief Définition de la fonction mk_editField_setCursorVector.
* @date 7 mars 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_editField_setCursorVector ( T_mkEditField* p_editField, T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_str8 p_windowBaseAddr )
{
   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 1;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = p_windowBaseAddr;

   /* Déclaration d'un pointeur de caractères */
   uint32_t l_currentCounter = p_editField->windowBaseOffset;

   /* Déclaration d'un lot de variables stockant la valeur unicode du caractère courant, */
   /* ainsi que la largeur et l'offset du caractère courant */
   uint32_t l_currentChar = 0, l_charLength = 0, l_charBaseAddr = 0;

   /* Déclaration d'un lot de variables stockant l'offset de la première ligne à dessiner */
   /* et l'état de remplissage d'une ligne (entièrement remplie ou non) */
   uint32_t l_rowCounter = 0, l_endOfRow = 0;

   /* Déclaration des vecteurs de travail */
   /* Ref : vecteur stockant les coordonnées du début de ligne */
   /* Current : vecteur stockant les coordonnées du caractère en court de dessin */
   T_mkVect2Di l_refVect = { 0, 0 }, l_currentVect = { 0, 0 };

   /* Adaptation du nombre de lignes à dessiner à la taille de la zone de dessin */
   uint32_t l_rowNumber = mk_display_utils_getWindowMaxNumberOfLines ( &p_editField->style, ( uint32_t ) ( p_v2->y - p_v1->y ) );

   /* Récupération du nombre total de lignes dans la chaine à dessiner */
   l_rowNumber = mk_display_utils_getWindowCurrentNumberOfLines ( p_editField->style.font, p_windowBaseAddr, l_rowNumber, ( uint32_t ) p_editField->style.fontEncoding, ( uint32_t ) ( p_v2->x - p_v1->x ) );

   /* Détermination des coordonnées du vecteur position pour la première ligne */
   mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, p_windowBaseAddr, l_rowNumber, &p_editField->style );

   /* Initialisation du vecteur courant */
   mk_vect2d_setCoord2Di ( &l_currentVect, l_refVect.x, l_refVect.y );

   /* Récupération de la valeur du premier caractère de la chaine */
   l_str = mk_font_parseString ( p_windowBaseAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );

   /* Tant qu'aucune erreur ne s'est produite et tant que la chaine de caractères n'a pas été entièrement déssinée */
   while ( ( l_ret == 1 ) && ( l_currentChar != 0 ) )
   {
      /* Récupération des informations relatives au caractère courant */
      mk_font_selectPage ( p_editField->style.font, l_currentChar, &l_charBaseAddr, &l_charLength );

      /* Test si l'ajout d'un nouveau caractère produit un chevauchement */
      l_ret = mk_display_utils_getNewLineOverlap ( &p_editField->style, &l_currentVect, l_charLength, &l_endOfRow, p_v2->x, p_v2->y );

      /* Si aucune erreur ne s'est produite (pas de débordement en dehors de la zone autorisée) */
      if ( l_ret == 1 )
      {
         /* Si le caractère courant est un caractère affichable */
         if ( ( p_editField->cursorBaseOffset == l_currentCounter ) && ( p_editField->cursor != K_MK_NULL ) && ( l_endOfRow == 0 ) )
         {
            /* Enregistrement de la position du curseur */
            mk_vect2d_setCoord2Di ( &p_editField->cursorVect, l_currentVect.x, l_currentVect.y );

            /* Arrêt de la boucle */
            l_ret = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

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
               mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, l_str, l_rowNumber, &p_editField->style );
            }

            /* Sinon */
            else
            {
               /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
               mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, p_windowBaseAddr, l_rowNumber, &p_editField->style );
            }

            /* Initialisation du vecteur courant en début de ligne */
            mk_vect2d_setCoord2Di ( &l_currentVect, l_refVect.x, l_refVect.y );

            /* Actualisation de la ccoordonnée 'y' du vecteur courant */
            l_currentVect.y += ( uint32_t ) ( l_rowCounter * ( ( uint32_t ) p_editField->style.font->height + ( uint32_t ) p_editField->style.font->numberOfPixelsBetweenRows ) );

            /* Si le caractère courant est un caractère affichable */
            if ( ( p_editField->cursorBaseOffset == l_currentCounter ) && ( p_editField->cursor != K_MK_NULL ) && ( l_endOfRow == 1 ) )
            {
               /* Enregistrement de la position du curseur */
               mk_vect2d_setCoord2Di ( &p_editField->cursorVect, l_currentVect.x, l_currentVect.y );

               /* Arrêt de la boucle */
               l_ret = 0;
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

         /* Actualisation du compteur de caractères */
         l_currentCounter = ( uint32_t ) ( l_currentCounter + 1 );

         /* Actualisation de la valeur du pointeur de chaine de caractères */
         p_windowBaseAddr = l_str;

         /* Récupération de la valeur du prochain caractère de la chaine */
         l_str = mk_font_parseString ( p_windowBaseAddr, &l_currentChar, ( uint32_t ) p_editField->style.fontEncoding );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si le caractère courant est un caractère affichable */
   if ( ( p_editField->cursorBaseOffset == l_currentCounter ) && ( p_editField->cursor != K_MK_NULL ) && ( l_currentChar == 0 ) )
   {
      /* Enregistrement de la position du curseur */
      mk_vect2d_setCoord2Di ( &p_editField->cursorVect, l_currentVect.x, l_currentVect.y );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


