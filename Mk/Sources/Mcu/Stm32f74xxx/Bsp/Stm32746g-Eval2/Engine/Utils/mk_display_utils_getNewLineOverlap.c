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
* @file mk_display_utils_getNewLineOverlap.c
* @brief Définition de la fonction mk_display_utils_getNewLineOverlap.
* @date 12 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t mk_display_utils_getNewLineOverlap ( T_mkTextStyle* p_style, T_mkVect2Di* p_currentVect, uint32_t p_width, uint32_t* p_row, uint32_t p_x2, uint32_t p_y2 )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Initialisation du pointeur indiquant que la fin de ligne a été atteinte */
   *p_row = 0;

   /* Si un retour à la ligne doit être effectué */
   if ( ( p_currentVect->x + p_width ) > p_x2 )
   {
      /* Signalisation de la fin de ligne */
      *p_row = 1;

      /* Si la fenêtre a été entièrement remplie */
      if ( ( p_currentVect->y + ( 2 * ( uint32_t ) p_style->font->height ) ) > p_y2 )
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
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
      /* Si la figure a été entièrement remplie */
      if ( ( p_currentVect->y + p_style->font->height ) > p_y2 )
      {
         /* Actualisation de la variable de retour */
         l_result = 0;
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


