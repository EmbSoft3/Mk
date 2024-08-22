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
* @file mk_graph2D_defaultPainter.c
* @brief Définition de la fonction mk_graph2D_defaultPainter.
* @date 26 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graph2D_plotVector ( T_mkGraph2D* p_graph2D, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Détermination des coordonnées du vecteur 'BottomRight' de l'arrière plan et de la bordure */
   T_mkVect2D l_bottomRight = {
         ( real32_t ) ( p_graph2D->position.x + ( real32_t ) p_graph2D->width - 1.0f ),
         ( real32_t ) ( p_graph2D->position.y + ( real32_t ) p_graph2D->height - 1.0f )
   };

   /* Dessin du graphique */
   l_result = mk_graphics_plot ( p_field->layer,
                                 p_graph2D->position, l_bottomRight, K_MK_GRAPH_TYPE_GRAPH2D, ( T_mkGraph2D* ) p_graph2D );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graph2D_drawText ( T_mkGraph2D* p_graph2D )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Détermination d'un vecteur position  */
   T_mkVect2D l_bottomRight;

   /* Pour le nombre de chaines de caractères à dessiner */
   for ( l_counter = 0 ; ( l_counter < K_MK_GRAPH2D_NUMBER_OF_IDENTIFIER ) && ( l_result == K_MK_OK ) ; l_counter++ )
   {
      /* Si l'utilisateur a configuré une chaine de caractères */
      if ( p_graph2D->text [ l_counter ].str != K_MK_NULL )
      {
         /* Détermination des coordonnées du vecteur 'BottomRight' */
         mk_vect2d_setCoord ( &l_bottomRight, p_graph2D->text [ l_counter ].position.x + ( real32_t ) p_graph2D->text [ l_counter ].width - 1.0f,
                              p_graph2D->text [ l_counter ].position.y + ( real32_t ) p_graph2D->text [ l_counter ].height - 1.0f );

         /* Dessin de la chaine de caractères */
         l_result = mk_graphics_drawString ( p_graph2D->textLayer, p_graph2D->text [ l_counter ].position, l_bottomRight,
                                             p_graph2D->text [ l_counter ].str, p_graph2D->text [ l_counter ].style, K_MK_NULL );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graph2D_drawGrid ( T_mkGraph2D* p_graph2D, T_mkGraph2DGridAttributes* p_grid )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant une couleur au format ARGB8888 */
   uint32_t l_color = 0;

   /* Déclaration des variables de travail */
   uint32_t l_number = 0, l_counter = 0;

   /* Déclaration des vecteurs de travail */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Si la grille secondaire doit être dessinée */
   if ( p_grid->visibility == K_MK_FIELD_VISIBLE )
   {
      /* Récupération de la valeur de la couleur */
      l_color = mk_color_getARGB32 ( &p_grid->color );

      /* Si le dessin sur l'axe vertical est activé */
      if ( ( p_grid->dx != 0 ) && ( p_graph2D->height >= 2 ) )
      {
         /* Détermination du nombre de lignes à dessiner */
         l_number = ( uint32_t ) ( p_graph2D->width / p_grid->dx );

         /* Détermination de la position des vecteurs 'TopLeft' et 'BottomRight' */
         mk_vect2d_setCoord ( &l_topLeft, p_graph2D->position.x, p_graph2D->position.y + 1.0f );
         mk_vect2d_setCoord ( &l_bottomRight, p_graph2D->position.x, p_graph2D->position.y + ( real32_t ) p_graph2D->height - 2.0f );

         /* Pour le nombre de lignes à dessiner et tant qu'aucune erreur ne s'est produite  */
         for ( l_counter = 1 ; ( l_counter < l_number ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Actualisation des positions */
            l_topLeft.x = l_topLeft.x + ( real32_t ) p_grid->dx;
            l_bottomRight.x = l_bottomRight.x +( real32_t ) p_grid->dx;

            /* Dessin des lignes de la grille */
            l_result = mk_graphics_drawRect ( p_graph2D->gridLayer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le dessin sur l'axe horizontal est activé */
      if ( ( l_result == K_MK_OK ) && ( p_grid->dy != 0 ) && ( p_graph2D->width >= 2 ) )
      {
         /* Détermination du nombre de lignes à dessiner */
         l_number = ( uint32_t ) ( p_graph2D->height / p_grid->dy );

         /* Détermination de la position des vecteurs 'TopLeft' et 'BottomRight' */
         mk_vect2d_setCoord ( &l_topLeft, p_graph2D->position.x + 1.0f, p_graph2D->position.y );
         mk_vect2d_setCoord ( &l_bottomRight, p_graph2D->position.x + ( real32_t ) p_graph2D->width - 2.0f, p_graph2D->position.y );

         /* Pour le nombre de lignes à dessiner et tant qu'aucune erreur ne s'est produite  */
         for ( l_counter = 1 ; ( l_counter < l_number ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Actualisation des positions */
            l_topLeft.y = l_topLeft.y + ( real32_t ) p_grid->dy;
            l_bottomRight.y = l_bottomRight.y + ( real32_t ) p_grid->dy;

            /* Dessin des lignes de la grille */
            l_result = mk_graphics_drawRect ( p_graph2D->gridLayer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );
         }
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_graph2D_drawField ( T_mkGraph2D* p_graph2D, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant une couleur au format ARGB8888 */
   uint32_t l_color = 0;

   /* Déclaration d'un vecteur de travail */
   T_mkVect2D l_bottomRight = {
         ( real32_t ) ( p_field->position.x + ( real32_t ) p_field->dimension.width - 1.0f ),
         ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - 1.0f )
   };

   /* Si l'arrière plan doit être dessiné */
   if ( p_graph2D->backgroundVisibility == K_MK_FIELD_VISIBLE )
   {
      /* Récupération de la valeur de la couleur */
      l_color = mk_color_getARGB32 ( &p_graph2D->backgroundColor );

      /* Dessin du rectangle de l'arrière plan */
      l_result = mk_graphics_drawRect ( p_graph2D->gridLayer, K_MK_GRAPHICS_SOLID, p_field->position, l_bottomRight, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le premier plan doit être dessiné */
   if ( p_graph2D->foregroundVisibility == K_MK_FIELD_VISIBLE )
   {
      /* Détermination de la position du vecteur 'BottomRight' */
      mk_vect2d_setCoord ( &l_bottomRight, ( real32_t ) ( p_graph2D->position.x + ( real32_t ) p_graph2D->width - 1.0f ),
         ( real32_t ) ( p_graph2D->position.y + ( real32_t ) p_graph2D->height - 1.0f ) );

      /* Récupération de la valeur de la couleur */
      l_color = mk_color_getARGB32 ( &p_graph2D->foregroundColor );

      /* Dessin du rectangle de premier plan */
      l_result = mk_graphics_drawRect ( p_graph2D->gridLayer, K_MK_GRAPHICS_SOLID, p_graph2D->position, l_bottomRight, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite et si la bordure doit être dessiné */
   if ( ( l_result == K_MK_OK ) && ( p_graph2D->borderVisibility == K_MK_FIELD_VISIBLE ) )
   {
      /* Détermination de la position du vecteur 'BottomRight' */
      mk_vect2d_setCoord ( &l_bottomRight, ( real32_t ) ( p_field->position.x + ( real32_t ) p_field->dimension.width - 1.0f ),
         ( real32_t ) ( p_field->position.y + ( real32_t ) p_field->dimension.height - 1.0f) );

      /* Récupération de la valeur de la couleur */
      l_color = mk_color_getARGB32 ( &p_graph2D->borderColor );

      /* Dessin de la bordure */
      l_result = mk_graphics_drawRect ( p_graph2D->gridLayer, K_MK_GRAPHICS_EMPTY, p_field->position, l_bottomRight, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_graph2D_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du graphique */
   T_mkGraph2D* l_graph2D = ( T_mkGraph2D* ) p_field->child;

   /* Si le graphique doit être rafraichi */
   if ( ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED ) &&
        ( p_field->dimension.width != 0 ) && ( p_field->dimension.height != 0 ) )
   {
      /* Si la grille doit être rafraichie */
      if ( l_graph2D->refreshGrid != K_MK_FIELD_REFRESH_DISABLED )
      {
         /* Si le cache n'est pas activé ou doit être actualisé */
         if ( ( l_graph2D->cache == K_MK_NULL ) || ( l_graph2D->refreshCache == K_MK_FIELD_REFRESH_ENABLED ) )
         {
            /* Dessin de la bordure, du premier plan et de l'arrière plan du graphique */
            l_result = mk_graph2D_drawField ( l_graph2D, p_field );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Dessin de la grille secondaire */
               l_result = mk_graph2D_drawGrid ( l_graph2D, &l_graph2D->grid.secondary );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Dessin de la grille principale */
               l_result = mk_graph2D_drawGrid ( l_graph2D, &l_graph2D->grid.main );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si aucune erreur ne s'est produite et si un cache est configuré */
            if ( ( l_result == K_MK_OK ) && ( l_graph2D->cache != K_MK_NULL ) )
            {
               /* Copie du buffer graphique vers le cache */
               l_result |= mk_graphics_copy ( l_graph2D->cache, p_field->position, K_MK_GRAPHICS_FRAME_TO_ADDR, l_graph2D->gridLayer, p_field->dimension.width, p_field->dimension.height );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Désactivation du rafraichissement */
            l_graph2D->refreshCache = K_MK_FIELD_REFRESH_DISABLED;
         }

         /* Sinon */
         else
         {
            /* Copie du cache vers le buffer graphique */
            l_result |= mk_graphics_copy ( l_graph2D->cache, p_field->position, K_MK_GRAPHICS_ADDR_TO_FRAME, l_graph2D->gridLayer, p_field->dimension.width, p_field->dimension.height );
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le texte doit être rafraichi */
      if ( l_graph2D->refreshText != K_MK_FIELD_REFRESH_DISABLED )
      {
         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Dessin des chaines de caractères */
            l_result = mk_graph2D_drawText ( l_graph2D );
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

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Dessin de la courbe du graphique */
         l_result = mk_graph2D_plotVector ( l_graph2D, p_field );
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

   /* Suppression warning */
   ( void ) p_container; ( void ) p_frameNumber;

   /* Retour */
   return ( l_result );
}
