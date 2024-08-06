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
* @file mk_graph2D_init.c
* @brief Définition de la fonction mk_graph2D_init.
* @date 25 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_graph2D_init ( T_mkGraph2D* p_graph2D )
{
   /* Si le paramètre est valide */
   if ( p_graph2D != K_MK_NULL )
   {
      /* Réinitialisation de la structure */
      _writeWords ( p_graph2D, 0, sizeof ( T_mkGraph2D ) >> 2 );

      /* Initialisation du champ */
      mk_field_init ( &p_graph2D->field );

      /* Configuration de l'adresse du descendant (héritage) */
      mk_field_setChild ( &p_graph2D->field, ( T_mkGraph2D* ) p_graph2D );

      /* Configuration du layer */
      mk_field_setLayer ( &p_graph2D->field, K_MK_GRAPHICS_FOREGROUND );

      /* Configuration de la position du champ */
      mk_field_setPosition ( &p_graph2D->field, 0, 0 );

      /* Configuration des dimensions du champ */
      mk_field_setDimension ( &p_graph2D->field, K_MK_GRAPH2D_DEFAULT_WIDTH, K_MK_GRAPH2D_DEFAULT_HEIGHT );

      /* Configuration de l'adresse de la fonction de peinture */
      mk_field_setPainter ( &p_graph2D->field, mk_graph2D_defaultPainter );

      /* Configuration de la couleur de l'arrière plan */
      mk_graph2D_setBackgroundVisibility ( p_graph2D, K_MK_FIELD_VISIBLE );
      mk_graph2D_setBackgroundColor ( p_graph2D, K_MK_COLOR_ARGB_BLACK );

      /* Configuration de la couleur du premier plan */
      mk_graph2D_setBackgroundVisibility ( p_graph2D, K_MK_FIELD_INVISIBLE );
      mk_graph2D_setBackgroundColor ( p_graph2D, K_MK_COLOR_ARGB_BLACK );

      /* Configuration de la couleur de la bordure */
      mk_graph2D_setBorderVisibility ( p_graph2D, K_MK_FIELD_VISIBLE );
      mk_graph2D_setBorderColor ( p_graph2D, K_MK_COLOR_ARGB_BLACK );

      /* Configuration du rafraichissement de la grille et des textes */
      mk_graph2D_setGridRefresh ( p_graph2D, K_MK_FIELD_REFRESH_ENABLED );
      mk_graph2D_setTextRefresh ( p_graph2D, K_MK_FIELD_REFRESH_ENABLED );

      /* Configuration des layers de la grille et des textes */
      mk_graph2D_setGridLayer ( p_graph2D, K_MK_GRAPHICS_FOREGROUND );
      mk_graph2D_setTextLayer ( p_graph2D, K_MK_GRAPHICS_FOREGROUND );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}
