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
* @file mk_graph2D_addFirstInt32.c
* @brief Définition de la fonction mk_graph2D_addFirstInt32.
* @date 29 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_graph2D_addFirstInt32 ( T_mkGraph2D* p_graph2D, int32_t p_userInt32, int32_t p_ymin, int32_t p_ymax )
{
   /* Déclaration d'une variable stockant la valeur de la coordonnée y */
   real32_t l_y = 0;

   /* Déclaration d'une variable stockant la distance entre deux points du graphique sur l'axe y */
   uint32_t l_deltaY = 0;

   /* Si les paramètres sont valides */
   if ( ( p_graph2D != K_MK_NULL ) &&
        ( p_graph2D->width > 0 ) && ( p_graph2D->height > 0 ) )
   {
      /* Détermination de la distance entre les bornes ymin et ymax du graphique */
      l_deltaY = ( uint32_t ) ( p_ymax - p_ymin );

      /* Si la valeur y courante est supérieure ou égale à la borne haute */
      if ( p_userInt32 >= p_ymax )
      {
         /* On borne la valeur courante à la valeur ymax */
         *p_graph2D->attribute.firstPixel = p_graph2D->position.y + 1.0f;
      }

      /* Sinon si la valeur y courante est inférieure ou égale à la borne basse */
      else if ( p_userInt32 <= p_ymin )
      {
         /* On borne la valeur courante à la valeur ymin */
         *p_graph2D->attribute.firstPixel = p_graph2D->position.y + ( real32_t ) p_graph2D->height - 1.0f;
      }

      /* Sinon */
      else
      {
         /* Conversion de la valeur courante en pixel */
         l_y = ( ( ( ( real32_t ) p_userInt32 - ( real32_t ) p_ymin ) / ( real32_t ) l_deltaY ) * ( real32_t ) p_graph2D->height - 2u );

         /* Réalisation du changement de plan (repère du plan en haut à gauche) */
         *p_graph2D->attribute.firstPixel = p_graph2D->position.y + ( ( real32_t ) p_graph2D->height - 1.0f - l_y );
      }

      /* Il est nécessaire de décaler les pointeurs de début et de fin d'une unité. */
      /* Si le pointeur du premier pixel doit être actualisé */
      if ( p_graph2D->attribute.firstPixel == &p_graph2D->attribute.pixelBuf [ p_graph2D->attribute.lengthOfBuf ] - 1 )
      {
         /* Réinitialisation du pointeur */
         p_graph2D->attribute.firstPixel = &p_graph2D->attribute.pixelBuf [ 0 ];
      }

      /* Sinon */
      else
      {
         /* Actualisation du pointeur */
         p_graph2D->attribute.firstPixel++;
      }

      /* Si le pointeur du dernier pixel doit être actualisé */
      if ( p_graph2D->attribute.lastPixel == &p_graph2D->attribute.pixelBuf [ p_graph2D->attribute.lengthOfBuf - 1 ] )
      {
         /* Réinitialisation du pointeur */
         p_graph2D->attribute.lastPixel = &p_graph2D->attribute.pixelBuf [ 0 ];
      }

      /* Sinon */
      else
      {
         /* Actualisation du pointeur */
         p_graph2D->attribute.lastPixel++;
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


