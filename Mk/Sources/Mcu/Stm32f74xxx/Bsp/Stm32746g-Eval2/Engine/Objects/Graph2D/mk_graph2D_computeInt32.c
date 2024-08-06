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
* @file mk_graph2D_computeInt32.c
* @brief Définition de la fonction mk_graph2D_computeInt32.
* @date 26 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_graph2D_sortInt32 ( int32_t* p_ymin, int32_t* p_ymax )
{
   /* Déclaration d'une variable de travail */
   int32_t l_value = *p_ymax;

   /* Si ymin est supérieur à ymax */
   if ( *p_ymin > *p_ymax )
   {
      /* Permutation des paramètres */
      *p_ymax = *p_ymin;
      *p_ymin = l_value;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_graph2D_computeInt32 ( T_mkGraph2D* p_graph2D, int32_t* p_userInt32Buf, uint32_t p_bufLength, int32_t p_ymin, int32_t p_ymax )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable stockant la valeur de la coordonnée y */
   real32_t l_y = 0;

   /* Déclaration d'une variable stockant la distance entre deux points du graphique sur l'axe y */
   uint32_t l_deltaY = 0;

   /* Déclaration d'une variable stockant le nombre de données à traiter */
   uint32_t l_dataNumber = p_bufLength;

   /* Si les paramètres sont valides */
   if ( ( p_graph2D != K_MK_NULL ) && ( p_userInt32Buf != K_MK_NULL ) && ( p_bufLength != 0 ) &&
        ( p_graph2D->width > 0 ) && ( p_graph2D->height > 0 ) )
   {
      /* Tri des paramètres ymin et ymax */
      mk_graph2D_sortInt32 ( &p_ymin, &p_ymax );

      /* Enregistrement de la taille du buffer utilisateur */
      p_graph2D->attribute.lengthOfUserBuf = p_bufLength;

      /* Si la taille du buffer de pixels est inférieure à la taille du buffer de l'utilisateur */
      if ( p_graph2D->attribute.lengthOfPixelBuf < p_bufLength )
      {
         /* Actualisation du nombre de données à traiter */
         l_dataNumber = p_graph2D->attribute.lengthOfPixelBuf;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Initialisation des pointeurs de début et de fin*/
      p_graph2D->attribute.firstPixel = &p_graph2D->attribute.pixelBuf [ 0 ];
      p_graph2D->attribute.lastPixel = &p_graph2D->attribute.pixelBuf [ l_dataNumber - 1 ];

      /* Enregistrement du nombre de données à traiter */
      p_graph2D->attribute.lengthOfBuf = l_dataNumber;

      /* Détermination de la distance entre les bornes ymin et ymax du graphique */
      l_deltaY = ( uint32_t ) ( p_ymax - p_ymin );

      /* Pour le nombre de données à traiter */
      for ( l_counter = 0 ; l_counter < l_dataNumber ; l_counter++ )
      {
         /* Si la valeur y courante est supérieure ou égale à la borne haute */
         if ( p_userInt32Buf [ l_counter ] >= p_ymax )
         {
            /* On borne la valeur courante à la valeur ymax */
            p_graph2D->attribute.pixelBuf [ l_counter ] = p_graph2D->position.y + 1.0f;
         }

         /* Sinon si la valeur y courante est inférieure ou égale à la borne basse */
         else if ( p_userInt32Buf [ l_counter ] <= p_ymin )
         {
            /* On borne la valeur courante à la valeur ymin */
            p_graph2D->attribute.pixelBuf [ l_counter ] = p_graph2D->position.y + ( real32_t ) p_graph2D->height - 1.0f;
         }

         /* Sinon */
         else
         {
            /* Conversion de la valeur courante en pixel */
            l_y = ( ( ( ( real32_t ) p_userInt32Buf [ l_counter ] - ( real32_t ) p_ymin ) / ( real32_t ) l_deltaY ) * ( real32_t ) ( p_graph2D->height - 2u ) );

            /* Réalisation du changement de plan (repère du plan en haut à gauche) */
            p_graph2D->attribute.pixelBuf [ l_counter ] = p_graph2D->position.y + ( ( real32_t ) p_graph2D->height - 1.0f - l_y ) ;
         }
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



