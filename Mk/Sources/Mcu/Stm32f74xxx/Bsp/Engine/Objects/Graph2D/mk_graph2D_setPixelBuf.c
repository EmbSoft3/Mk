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
* @file mk_graph2D_setPixelBuf.c
* @brief Définition de la fonction mk_graph2D_setPixelBuf.
* @date 26 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_graph2D_setPixelBuf ( T_mkGraph2D* p_graph2D, real32_t* p_buf, uint32_t p_length )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Si les paramètres sont valides */
   if ( ( p_graph2D != K_MK_NULL ) && ( p_buf != K_MK_NULL ) && ( p_length != 0 ) )
   {
      /* Configuration des attributs du graphique */
      p_graph2D->attribute.pixelBuf = p_buf;
      p_graph2D->attribute.lengthOfPixelBuf = p_length;
      p_graph2D->attribute.lengthOfBuf = p_length;
      p_graph2D->attribute.firstPixel = &p_buf [ 0 ];
      p_graph2D->attribute.lastPixel = &p_buf [ p_length - 1 ];

      /* Réinitialisation du buffer */
      for ( l_counter = 0 ; l_counter < p_length ; l_counter++ )
      {
         /* On borne la valeur courante à la valeur ymin */
         p_graph2D->attribute.pixelBuf [ l_counter ] = p_graph2D->position.y + ( real32_t ) p_graph2D->height - 2.0f;
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



