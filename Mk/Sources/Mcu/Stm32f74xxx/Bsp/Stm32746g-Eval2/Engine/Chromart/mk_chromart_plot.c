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
* @file mk_chromart_plot.c
* @brief Définition de la fonction mk_chromart_plot.
* @date 26 nov. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_plotGraph2DLine ( T_mkChromartRequest* p_request, T_mkGraph2D* p_graph2D )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une requête chromart */
   T_mkChromartRequest l_request;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable d'état */
   uint32_t l_state = 0;

   /* Déclaration des variables de travail */
   real32_t l_realX1 = 0.0f, l_realY1 = 0.0f, l_realX2 = 0.0f, l_realY2 = 0.0f, l_realX3 = 0.0f, l_realY3 = 0.0f;

   /* Déclaration d'une variable stockant la position des points sur l'axe X */
   real32_t l_x = 0;

   /* Déclaration d'un pointeur stockant la position des points sur l'axe Y */
   real32_t* l_y = p_graph2D->attribute.firstPixel;

   /* Déclaration d'une variable contenant la distance entre 2 points sur l'axe X */
   real32_t l_dx = 0.0f;

   /* Récupération de la couleur du graphique */
   uint32_t l_color = mk_color_getARGB32 ( &p_graph2D->color );

   /* Si la taille du buffer est supérieur à 1 */
   if ( p_graph2D->attribute.lengthOfBuf > 1 )
   {
      /* Détermination de la distance entre 2 point sur l'axe X */
      l_dx = ( real32_t ) ( p_request->plane.width - 2 ) / ( ( real32_t ) p_graph2D->attribute.lengthOfBuf - 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Tant qu'aucune erreur ne s'est produite et tant que des points peuvent être tracés */
   while ( ( l_result == K_MK_OK ) && ( l_counter < ( uint32_t ) ( p_graph2D->attribute.lengthOfBuf - 1 ) ) )
   {
      /* Récupération des coordonnées X et Y du premier point */
      l_realX1 = mk_vect2d_shift ( ( real32_t ) p_request->plane.x + l_x + 1.0f );
      l_realY1 = mk_vect2d_shift ( ( real32_t ) *l_y );

      /* Si le pointeur doit être réinitialisé */
      if ( l_y == &p_graph2D->attribute.pixelBuf [ p_graph2D->attribute.lengthOfBuf - 1 ] )
      {
         /* Réinitialisation du pointeur */
         l_y = &p_graph2D->attribute.pixelBuf [ 0 ];
      }

      /* Sinon */
      else
      {
         /* Passage au prochain point */
         l_y = ( l_y + 1 );
      }

      /* Récupération des coordonnées X et Y du premier point */
      l_realX2 = mk_vect2d_shift ( ( real32_t ) p_request->plane.x + l_x + l_dx + 1.0f );
      l_realY2 = mk_vect2d_shift ( ( real32_t ) *l_y );

      /* Si les ordonnées des points 1 et 2 sont différentes */
      if ( ( uint32_t ) l_realY2 != ( uint32_t ) l_realY1 )
      {
         /* Si plusieurs points doivent être tracés */
         if ( l_state == 1 )
         {
            /* Configuration des attributs de la requête */
            mk_chromart_setPlane ( &l_request.plane, ( uint32_t ) l_realX3, ( uint32_t ) l_realY3, 0, 0 );
            mk_chromart_setLine ( &l_request, p_request->content.plot.layer, ( uint32_t ) l_realX1, ( uint32_t ) l_realY1, l_color );

            /* Dessin de la ligne */
            l_result = mk_chromart_drawLine ( &l_request );

            /* Réinitialisation de la variable d'état */
            l_state = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Configuration des attributs de la requête */
            mk_chromart_setPlane ( &l_request.plane, ( uint32_t ) l_realX2, ( uint32_t ) l_realY2, 0, 0 );
            mk_chromart_setLine ( &l_request, p_request->content.plot.layer, ( uint32_t ) l_realX1, ( uint32_t ) l_realY1, l_color );

            /* Dessin de la ligne */
            l_result = mk_chromart_drawLine ( &l_request );
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
         /* Si le mode de dessin multiple n'est pas actif */
         if ( l_state == 0 )
         {
            /* Enregistrement des coordonnées du premier point */
            l_realX3 = l_realX1;
            l_realY3 = l_realY1;

            /* Actualisation de la variable d'état */
            l_state = 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Actualisation de la position sur l'axe X. */
      l_x = ( l_x + l_dx );

      /* Actualisation du compteur */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Si plusieurs points doivent être tracés */
   if ( ( l_result == K_MK_OK ) && ( l_state == 1 ) )
   {
      /* Configuration des attributs de la requête */
      mk_chromart_setPlane ( &l_request.plane, ( uint32_t ) l_realX3, ( uint32_t ) l_realY3, 0, 0 );
      mk_chromart_setLine ( &l_request, p_request->content.plot.layer, ( uint32_t ) l_realX1, ( uint32_t ) l_realY1, l_color );

      /* Dessin de la ligne */
      l_result = mk_chromart_drawLine ( &l_request );
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

static T_mkCode mk_chromart_plotGraph2DDot ( T_mkChromartRequest* p_request, T_mkGraph2D* p_graph2D, uint32_t p_firstWindowAddr, uint32_t p_lastFrameAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant le nombre d'octets par pixel */
   uint32_t l_bytesPerPixel = 0;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Déclaration des variables de travail */
   real32_t l_realX = 0.0f, l_realY = 0.0f;

   /* Déclaration d'une variable stockant l'adresse des points dans le buffer graphique */
   uint32_t l_dotAddr = 0, *l_pnt = K_MK_NULL;

   /* Déclaration d'une variable stockant la position des points sur l'axe X */
   real32_t l_x = 0;

   /* Déclaration d'un pointeur stockant la position des points sur l'axe Y */
   real32_t* l_y = p_graph2D->attribute.firstPixel;

   /* Déclaration d'une variable contenant la distance entre 2 points sur l'axe X */
   real32_t l_dx = 0.0f;

   /* Récupération de la couleur du graphique */
   uint32_t l_color = mk_color_getARGB32 ( &p_graph2D->color );

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_request->content.plot.layer ];

   /* Si la taille du buffer est supérieur à 1 */
   if ( p_graph2D->attribute.lengthOfBuf > 1 )
   {
      /* Détermination de la distance entre 2 point sur l'axe X */
      l_dx = ( real32_t ) ( p_request->plane.width - 2 ) / ( ( real32_t ) p_graph2D->attribute.lengthOfBuf - 1 );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Tant qu'aucune erreur ne s'est produite et tant que des points peuvent être tracés */
   while ( l_counter < p_graph2D->attribute.lengthOfBuf )
   {
      /* Récupération des coordonnées X et Y du point */
      l_realX = mk_vect2d_shift ( ( real32_t ) p_request->plane.x + l_x + 1.0f );
      l_realY = mk_vect2d_shift ( ( real32_t ) *l_y );

      /* Détermination de l'adresse du point dans le buffer graphique */
      l_dotAddr = p_firstWindowAddr + l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) l_realY ) + ( uint32_t ) l_realX );

      /* Si l'adresse est valide */
      if ( l_dotAddr <= p_lastFrameAddr )
      {
         /* Récupération de l'adresse du pixel */
         l_pnt = ( uint32_t* ) l_dotAddr;

         /* Ecriture du pixel directement dans la mémoire graphique */
         if ( l_bytesPerPixel == K_MK_DISPLAY_RGB888 )
         {
            _copy ( l_pnt, &l_color, 3 );
         }

         /* Sinon */
         else
         {
            *l_pnt = l_color;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la position sur l'axe X. */
      l_x = ( l_x + l_dx );

      /* Si le pointeur doit être réinitialisé */
      if ( l_y == &p_graph2D->attribute.pixelBuf [ p_graph2D->attribute.lengthOfBuf - 1 ] )
      {
         /* Réinitialisation du pointeur */
         l_y = &p_graph2D->attribute.pixelBuf [ 0 ];
      }

      /* Sinon */
      else
      {
         /* Passage au prochain point */
         l_y = ( l_y + 1 );
      }

      /* Actualisation du compteur */
      l_counter = ( uint32_t ) ( l_counter + 1 );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_plotGraph2D ( T_mkChromartRequest* p_request, uint32_t p_firstWindowAddr, uint32_t p_lastFrameAddr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'objet graphique */
   T_mkGraph2D* l_graph2D = ( T_mkGraph2D* ) p_request->content.plot.baseAddr;

   /* Si les paramètre du graphique sont valides */
   if ( ( l_graph2D->attribute.pixelBuf != K_MK_NULL ) && ( l_graph2D->attribute.lengthOfBuf != 0 ) )
   {
      /* Si une ligne doit être tracée entre chaque point */
      if ( l_graph2D->type == K_MK_GRAPH2D_TYPE_LINE )
      {
         /* Dessin des 'n' lignes de la courbe */
         l_result = mk_chromart_plotGraph2DLine ( p_request, l_graph2D );
      }

      /* Sinon, on ne dessine que les points */
      else
      {
         /* Dessin des 'n' points de la courbe */
         l_result = mk_chromart_plotGraph2DDot ( p_request, l_graph2D, p_firstWindowAddr, p_lastFrameAddr );
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

T_mkCode mk_chromart_plot ( T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Détermination de l'adresse de départ de la zone à dessiner */
   uint32_t l_firstWindowAddr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.plot.layer ];

   /* Détermination de l'adresse de fin du buffer graphique */
   uint32_t l_lastFrameAddr = ( uint32_t ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_request->content.plot.layer ] +
         K_MK_DISPLAY_BYTE_PER_PIXEL * ( g_mkDisplay.screen.width * g_mkDisplay.screen.height ) ;

   /* Si le layer de dessin est valide */
   if ( p_request->content.plot.layer <= K_MK_GRAPHICS_BACKGROUND )
   {
      /* Si un objet de type 'Graph2D' doit être dessiné */
      if ( p_request->content.plot.type == K_MK_GRAPH_TYPE_GRAPH2D )
      {
         /* Dessin du graphique */
         l_result = mk_chromart_plotGraph2D ( p_request, l_firstWindowAddr, l_lastFrameAddr );
      }

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



