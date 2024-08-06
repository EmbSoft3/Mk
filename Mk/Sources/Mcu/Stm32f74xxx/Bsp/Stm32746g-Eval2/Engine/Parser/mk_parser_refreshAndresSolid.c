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
* @file mk_parser_refreshAndresSolid.c
* @brief Définition de la fonction mk_parser_refreshAndresSolid.
* @date 22 févr. 2020
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_parser_refreshAndresSolid ( T_mkAndresParser* p_parser, uint32_t p_radius )
{
   /* Si l'abscisse doit être actualisée */
   if ( p_parser->d >= ( int32_t ) p_parser->dx )
   {
      p_parser->d -=  (int32_t ) p_parser->dx + 1;
      p_parser->x++;
   }

   /* Sinon si l'ordonnée doit être actualisée */
   else if ( p_parser->d < ( int32_t ) ( ( p_radius - p_parser->y ) << 1 ) )
   {
      p_parser->d += ( int32_t ) p_parser->dy - 2;
      p_parser->y--;
   }

   /* Sinon */
   else
   {
      p_parser->d += ( int32_t ) ( p_parser->y - p_parser->x - 1 ) << 1;
      p_parser->y--;
      p_parser->x++;
   }

   /* Détermination de la valeur des distances (ajout de 1 pixel pour le centre) */
   p_parser->dx = ( p_parser->x << 1 );
   p_parser->dy = ( p_parser->y << 1 ) + 1;

   /* Retour */
   return;
}

