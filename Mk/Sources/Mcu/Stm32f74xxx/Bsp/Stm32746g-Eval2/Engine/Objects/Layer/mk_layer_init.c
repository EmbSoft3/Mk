/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_layer_init.c
* @brief Définition de la fonction mk_layer_init.
* @date 27 juil. 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_layer_init ( T_mkLayer* p_layer )
{
   /* Si le paramètre est valide */
   if ( p_layer != K_MK_NULL )
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_layer, 0, sizeof ( T_mkLayer ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_layer->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_layer->field, ( T_mkLayer* ) p_layer );

      /* Configuration de la fonction de peinture */
      mk_field_setPainter ( &p_layer->field, mk_layer_defaultPainter );

      /* Configuration de la visibilité du champ */
      mk_field_setVisibility ( &p_layer->field, K_MK_FIELD_VISIBLE );

      /* Configuration de la variable d'état */
      p_layer->state = K_MK_LAYER_BOTH_VISIBLE;

      /* Configuration de la valeur des composantes alpha */
      p_layer->foregroundAlpha = 255;
      p_layer->backgroundAlpha = 255;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}



