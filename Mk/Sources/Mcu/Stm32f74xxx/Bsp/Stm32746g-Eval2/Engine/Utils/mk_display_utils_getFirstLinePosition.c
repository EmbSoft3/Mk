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
* @file mk_display_utils_getFirstLinePosition.c
* @brief Définition de la fonction mk_display_utils_getFirstLinePosition.
* @date 12 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_display_utils_getFirstLinePosition ( T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_mkVect2Di* p_out, T_str8 p_string, uint32_t p_rowNumber, T_mkTextStyle* p_style )
{
   /* Récupération de longueur (en pixel) de la prochaine ligne de la chaine de caractères */
   uint32_t l_pixelNumber = mk_display_utils_getFirstLineNumberOfPixels ( p_style->font, p_string, ( uint32_t ) p_style->fontEncoding, ( uint32_t ) ( p_v2->x - p_v1->x ) );

   /* Si la chaine de caractères doit être centrée sur l'axe horizontal */
   if ( p_style->horizontalAlignment == K_MK_TEXT_CENTER_JUSTIFIED )
   {
      /* Détermination de la valeur de la coordonnée x */
      p_out->x = ( uint32_t ) ( p_v1->x + ( ( 1 + ( p_v2->x - p_v1->x ) - l_pixelNumber ) >> 1 ) );
   }

   /* Sinon si la chaine de caractères doit être justifiée à droite sur l'axe horizontal */
   else if ( p_style->horizontalAlignment == K_MK_TEXT_RIGHT_JUSTIFIED )
   {
      /* Détermination de la valeur de la coordonnée x */
      p_out->x = ( uint32_t ) ( p_v2->x - l_pixelNumber );
   }

   /* Sinon (équivalent K_MK_TEXT_LEFT_JUSTIFIED) */
   else
   {
      /* Détermination de la valeur de la coordonnée x */
      p_out->x = ( uint32_t ) ( p_v1->x );
   }

   /* Si la chaine de caractères doit être centrée sur l'axe verticale */
   if ( p_style->verticalAlignment == K_MK_TEXT_CENTER_JUSTIFIED )
   {
      /* Détermination de la valeur de la coordonnée y */
      p_out->y = ( uint32_t ) ( p_v1->y + ( ( 1 + ( p_v2->y - p_v1->y ) -
            ( p_rowNumber * ( ( uint32_t ) p_style->font->height + ( uint32_t ) p_style->font->numberOfPixelsBetweenRows ) ) - ( uint32_t ) p_style->font->numberOfPixelsBetweenRows ) >> 1 ) );
   }

   /* Sinon si la chaine de caractères doit être justifiée en bas de l'axe vertical */
   else if ( p_style->verticalAlignment == K_MK_TEXT_DOWN_JUSTIFIED )
   {
      /* Détermination de la valeur de la coordonnée y */
      p_out->y = ( uint32_t ) ( p_v2->y - ( p_rowNumber * ( ( uint32_t ) p_style->font->height + ( uint32_t ) p_style->font->numberOfPixelsBetweenRows ) ) + ( uint32_t ) p_style->font->numberOfPixelsBetweenRows );
   }

   /* Sinon (équivalent K_MK_TEXT_TOP_JUSTIFIED) */
   else
   {
      /* Détermination de la valeur de la coordonnée y */
      p_out->y = ( uint32_t ) ( p_v1->y );
   }

   /* Retour */
   return;
}



