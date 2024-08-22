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
* @file mk_chromart_drawString.c
* @brief Définition de la fonction mk_chromart_drawString.
* @date 28 déc. 2022
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_graphics_revert ( uint8_t* p_addr )
{
   /* Revert du mot 32bits */
   uint32_t l_result = ( uint32_t ) ( ( ( *p_addr + 0 ) << 24 ) | ( *( p_addr + 1 ) << 16 ) | ( *( p_addr + 2 ) << 8 ) | ( *( p_addr + 3 ) << 0 ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_chromart_drawCharacter ( uint8_t* p_destinationAddr, uint8_t* p_baseAddr, uint32_t p_bytesPerPixel, uint32_t p_color, uint32_t p_fontWidth, uint32_t p_fontHeight )
{
   /* Déclaration d'une variable stockant le champ de bits du caractères */
   uint32_t l_bitmap;

   /* Déclaration des variables de travail */
   uint32_t l_hCounter, l_wCounter, l_bCounter = 0, l_bOffset = 0;

   /* Déclaration d'un pointeur */
   uint8_t* l_destinationAddr = ( uint8_t* ) ( p_destinationAddr );

   /* Pour la hauteur de la police de caractères */
   for ( l_hCounter = 0 ; ( l_hCounter < p_fontHeight ) ; l_hCounter++ )
   {
      /* Revert du mot courant, le MSB devient le LSB et vise versa */
      /* Attention à l'alignement des données */
      l_bitmap = mk_graphics_revert ( p_baseAddr );

      /* Pour la largeur de la chaine de caractères */
      for ( l_wCounter = 0 ; ( l_wCounter < p_fontWidth ) ; l_wCounter++ )
      {
         /* Si le pixel doit être dessiné */
         if ( ( ( l_bitmap >> ( 31 - l_bCounter ) ) & 0x1 ) > 0x0 )
         {
            /* Dessin du pixel */
            _copy ( ( uint8_t* ) l_destinationAddr + ( l_wCounter * p_bytesPerPixel ), &p_color, p_bytesPerPixel );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du compteur */
         l_bCounter++;

         /* Si un mot 32 vient d'être analysé */
         if ( l_bCounter == 32 )
         {
            /* Actualisation de la valeur de l'offset (ajout d'un mot 32 bits) */
            l_bOffset += ( uint32_t ) 4;

            /* Revert du mot courant, le MSB devient le LSB et vise versa */
            /* Attention à l'alignement des données */
            l_bitmap = mk_graphics_revert ( ( uint8_t* ) ( p_baseAddr + l_bOffset ) );

            /* Réinitialisation du compteur de bits */
            l_bCounter = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Réinitialisation du compteur de bits et de l'offset */
      l_bCounter = 0;
      l_bOffset = 0;

      /* Actualisation de la l'adresse de la prochaine ligne */
      l_destinationAddr = ( uint8_t* ) ( l_destinationAddr + ( g_mkDisplay.screen.width * p_bytesPerPixel ) );

      /* Acutalisation de la rangée */
      p_baseAddr += 1 + ( ( p_fontWidth - 1 ) >> 3 );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_drawCursorGlyph ( T_mkTextStyle* p_style, T_mkTextCursor* p_cursor, uint8_t* p_destinationAddr, uint32_t p_bytesPerPixel, T_mkVect2Di* p_start, T_mkVect2Di* p_end, uint32_t p_x, uint32_t p_width )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des compteurs de travail */
   uint32_t l_hCounter = p_cursor->yoffset;
   uint32_t l_wCounter = 0;

   /* Déclaration d'une variable stockant la couleur du curseur */
   uint32_t l_color = 0;

   /* Déclaration d'une variable stockant l'adresse du pixel à écrire */
   uint8_t* l_addr = K_MK_NULL;

   /* Si le mode courant est le mode par défaut (curseur vertical) */
   if ( p_cursor->mode != K_MK_GRAPHICS_CURSOR_TYPE_SECONDARY )
   {
      /* Actualisation de la largeur du curseur */
      p_width = p_cursor->width;
   }

   /* Sinon (curseur horizontal) */
   else
   {
      /* Si la position du curseur peut être décalée vers la gauche */
      if ( p_x > ( p_start->x + ( uint32_t ) p_style->font->numberOfPixelsBetweenChars ) )
      {
         /* Actualisation de l'offset du curseur */
         p_x = ( uint32_t ) ( p_x - ( uint32_t ) p_style->font->numberOfPixelsBetweenChars );

         /* Actualisation de la taille du curseur */
         p_width = ( uint32_t ) ( p_width + ( uint32_t ) p_style->font->numberOfPixelsBetweenChars );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la longueur du curseur peut être augmenté vers la droite */
      if ( ( p_x + p_width + ( uint32_t ) p_style->font->numberOfPixelsBetweenChars ) < p_end->x )
      {
         /* Actualisation de la taille du curseur */
         p_width = ( uint32_t ) ( p_width + ( uint32_t ) p_style->font->numberOfPixelsBetweenChars );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Conversion de la couleur en entier 32 bits */
   l_color = mk_color_getARGB32 ( &p_cursor->color );

   /* Configuration de l'adresse du premier pixel */
   l_addr = ( uint8_t* ) ( p_destinationAddr + p_bytesPerPixel * ( ( p_cursor->yoffset * g_mkDisplay.screen.width ) + p_x ) );

   /* Dessin du curseur */
   for ( l_hCounter = 0 ; l_hCounter < p_cursor->height ; l_hCounter++ )
   {
      /* Pour la largeur du curseur */
      for ( l_wCounter = p_cursor->xoffset ; l_wCounter < p_width ; l_wCounter++ )
      {
         /* Dessin du pixel */
         _copy ( ( uint8_t* ) ( l_addr + ( p_bytesPerPixel * l_wCounter ) ), &l_color, p_bytesPerPixel );
      }

      /* Actualisation de l'adresse de destination (prochaine ligne) */
      l_addr += ( p_bytesPerPixel * g_mkDisplay.screen.width );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_chromart_parseString ( uint32_t p_layer, T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_str8 p_string, T_mkTextStyle* p_style, T_mkTextCursor* p_cursor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de retour locale */
   uint32_t l_ret = 1;

   /* Déclaration d'un pointeur de chaine de caractères */
   T_str8 l_str = p_string;

   /* Déclaration d'un compteur de caractères */
   uint32_t l_currentCounter = p_cursor->baseOffset;

   /* Déclaration d'une variable stockant le nombre d'octets par pixel */
   uint32_t l_bytesPerPixel = 0;

   /* Déclaration d'un lot de variables stockant la valeur unicode du caractère courant, */
   /* ainsi que la largeur et l'offset du caractère courant */
   uint32_t l_currentChar = 0, l_charLength = 0, l_charBaseAddr = 0;

   /* Déclaration d'un lot de variables stockant l'offset de la ligne à dessiner et */
   /* l'état de remplissage d'une ligne (entièrement remplie ou non). */
   uint32_t l_rowCounter = 0, l_endOfRow = 0;

   /* Déclaration d'une variable stockant la couleur du texte */
   uint32_t l_color = mk_color_getARGB32 ( &p_style->color );

   /* Déclaration des vecteurs de travail */
   /* Ref : vecteur stockant les coordonnées du début de ligne */
   /* Current : vecteur stockant les coordonnées du caractère en court de dessin */
   T_mkVect2Di l_refVect = { 0, 0 }, l_currentVect = { 0, 0 };

   /* Déclaration d'une variable stockant l'adresse de destination du bitmap */
   uint8_t* l_destAddr = K_MK_NULL;

   /* Adaptation du nombre de lignes à dessiner à la taille de la zone de dessin */
   uint32_t l_rowNumber = mk_display_utils_getWindowMaxNumberOfLines ( p_style, ( uint32_t ) ( p_v2->y - p_v1->y ) );

   /* Récupération du nombre total de lignes dans la chaine à dessiner */
   l_rowNumber = mk_display_utils_getWindowCurrentNumberOfLines ( p_style->font, p_string, l_rowNumber, ( uint32_t ) p_style->fontEncoding, ( uint32_t ) ( p_v2->x - p_v1->x ) );

   /* Récupération du nombre d'octets par pixels */
   l_bytesPerPixel = g_mkDisplay.screen.bytesPerPixel [ p_layer ];

   /* Détermination des coordonnées du vecteur position de la première ligne */
   mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, p_string, l_rowNumber, p_style );

   /* Initialisation du vecteur courant */
   mk_vect2d_setCoord2Di ( &l_currentVect, l_refVect.x, l_refVect.y );

   /* Actualisation de l'adresse de destination */
   l_destAddr = ( uint8_t* ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_layer ] +
         ( l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) l_currentVect.y ) ) );

   /* Récupération de la valeur du premier caractère de la chaine */
   l_str = mk_font_parseString ( p_string, &l_currentChar, ( uint32_t ) p_style->fontEncoding );

   /* Tant qu'aucune erreur ne s'est produite et tant que la chaine de caractères n'a pas été entièrement déssinée */
   while ( ( l_ret == 1 ) && ( l_currentChar != 0 ) )
   {
      /* Récupération des informations relatives au caractère courant */
      mk_font_selectPage ( p_style->font, l_currentChar, &l_charBaseAddr, &l_charLength );

      /* Test si l'ajout d'un nouveau caractère produit un chevauchement */
      l_ret = mk_display_utils_getNewLineOverlap ( p_style, &l_currentVect, l_charLength, &l_endOfRow, p_v2->x, p_v2->y );

      /* Si aucune erreur ne s'est produite (pas de débordement en dehors de la zone autorisée) */
      if ( l_ret == 1 )
      {
         /* Si le curseur doit être affiché (pas de gestion du retour à la ligne) */
         if ( ( p_cursor != K_MK_NULL ) && ( p_cursor->blink == K_MK_GRAPHICS_VISIBLE ) && ( p_cursor->currentOffset == l_currentCounter ) && ( l_endOfRow == 0 ) )
         {
            /* Dessin du curseur */
            l_result = mk_chromart_drawCursorGlyph ( p_style, p_cursor, l_destAddr, l_bytesPerPixel, &l_refVect, p_v2, l_currentVect.x, l_charLength );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le caractère courant est le caractère '\n' ou si une ligne a été complétement remplie */
         /* Réalisation d'un retour à la ligne */
         if ( ( l_currentChar == '\n' ) || ( l_endOfRow == 1 ) )
         {
            /* Actualisation du compteur de ligne */
            l_rowCounter = ( uint32_t ) ( l_rowCounter + 1 );

            /* Si la fin de ligne n'a pas été causé par un retour à la ligne explicite */
            if ( l_endOfRow == 0 )
            {
               /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
               mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, l_str, l_rowNumber, p_style );
            }

            /* Sinon */
            else
            {
               /* Détermination des coordonnées du vecteur position pour la prochaine ligne */
               mk_display_utils_getFirstLinePosition ( p_v1, p_v2, &l_refVect, p_string, l_rowNumber, p_style );
            }

            /* Initialisation du vecteur courant en début de la nouvelle ligne */
            mk_vect2d_setCoord2Di ( &l_currentVect, l_refVect.x, l_refVect.y );

            /* Actualisation de la coordonnée 'y' du vecteur courant */
            l_currentVect.y += ( uint32_t ) ( l_rowCounter * ( ( uint32_t ) p_style->font->height + ( uint32_t ) p_style->font->numberOfPixelsBetweenRows ) );

            /* Actualisation de l'adresse de destination */
            l_destAddr = ( uint8_t* ) g_mkDisplay.pnt.currentBufferUpdated->addr [ p_layer ] + ( l_bytesPerPixel * ( ( g_mkDisplay.screen.width * ( uint32_t ) l_currentVect.y ) ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le caractère courant est un caractère affichable */
         if ( ( p_cursor != K_MK_NULL ) && ( p_cursor->blink == K_MK_GRAPHICS_VISIBLE ) && ( p_cursor->currentOffset == l_currentCounter ) && ( l_endOfRow == 1 ) )
         {
            /* Dessin du curseur */
            l_result = mk_chromart_drawCursorGlyph ( p_style, p_cursor, l_destAddr, l_bytesPerPixel, &l_refVect, p_v2, l_currentVect.x, l_charLength );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si le caractère courant est le caractère '\r' */
         if ( l_currentChar == '\r' )
         {
            /* Ne rien faire */
         }

         /* Sinon si le caractère courant est le caractère '\t' */
         else if ( l_currentChar == '\t' )
         {
            /* Insertion d'une tabulation */
            l_currentVect.x += ( uint32_t ) p_style->font->tabulationNumberOfPixels;
         }

         /* Sinon si le caractère courant est un caractère affichable */
         else if ( l_currentChar != '\n' )
         {
            /* Si la longueur du caractère est inférieure à 32 bits */
            if ( l_charLength <= 32 )
            {
               /* Si les pixels sont codés sur 4 octets */
               if ( l_bytesPerPixel == K_MK_DISPLAY_ARGB8888 )
               {
                  /* Dessin du caractère courant en utilisant une instruction assembleur spécifique */
                  _mk_chromart_drawCharacterFast ( ( l_destAddr + ( l_bytesPerPixel * l_currentVect.x ) ), ( uint8_t* ) l_charBaseAddr, l_color, l_charLength, ( uint32_t ) p_style->font->height, g_mkDisplay.screen.width );
               }

               /* Sinon, les pixels sont codés sur 3 octets */
               else
               {
                  _mk_chromart_drawCharacterFast24BPP ( ( l_destAddr + ( l_bytesPerPixel * l_currentVect.x ) ), ( uint8_t* ) l_charBaseAddr, l_color, l_charLength, ( uint32_t ) p_style->font->height, g_mkDisplay.screen.width );
               }
            }

            /* Sinon */
            else
            {
               /* Dessin du caractère courant (fonction lente) */
               mk_chromart_drawCharacter ( ( l_destAddr + ( l_bytesPerPixel * l_currentVect.x ) ), ( uint8_t* ) l_charBaseAddr, l_bytesPerPixel, l_color, l_charLength, ( uint32_t ) p_style->font->height );
            }

            /* Actualisation de l'abscisse du vecteur courant */
            l_currentVect.x += l_charLength + ( uint32_t ) p_style->font->numberOfPixelsBetweenChars;
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

      /* Actualisation du compteur de caractères */
      l_currentCounter = ( uint32_t ) ( l_currentCounter + 1 );

      /* Actualisation de la valeur du pointeur de chaine de caractères */
      p_string = l_str;

      /* Récupération de la valeur du prochain caractère de la chaine */
      l_str = mk_font_parseString ( p_string, &l_currentChar, ( uint32_t ) p_style->fontEncoding );
   }

   /* Si le caractère courant est un caractère affichable */
   if ( ( p_cursor != K_MK_NULL ) && ( p_cursor->blink == K_MK_GRAPHICS_VISIBLE ) && ( p_cursor->currentOffset == l_currentCounter ) && ( l_currentChar == 0 ) )
   {
      /* Dessin du curseur */
      l_result = mk_chromart_drawCursorGlyph ( p_style, p_cursor, l_destAddr, l_bytesPerPixel, &l_refVect, p_v2, l_currentVect.x, l_charLength );
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

T_mkCode mk_chromart_drawString ( T_mkChromartRequest* p_request )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs de travail flottant */
   T_mkVect2D  l_r1, l_r2;

   /* Déclaration des vecteurs de travail non flottant */
   T_mkVect2Di l_v1, l_v2;

   /* Déclaration d'une structure contenant le style par défaut de la chaine de caractères */
   T_mkTextStyle l_style = {
        K_MK_NULL,
        K_MK_FONT_ASCII, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
        K_MK_GRAPHICS_DEFAULT_MARGIN_TOP, K_MK_GRAPHICS_DEFAULT_MARGIN_BOTTOM,
        K_MK_GRAPHICS_DEFAULT_MARGIN_RIGHT, K_MK_GRAPHICS_DEFAULT_MARGIN_LEFT,
        K_MK_GRAPHICS_DEFAULT_TEXT_COLOR
   };

   /* Si l'utilisateur a spécifié un style */
   if ( p_request->content.string.styleAddr != K_MK_NULL )
   {
      /* Copie du style utilisateur */
      _copy ( &l_style, p_request->content.string.styleAddr, sizeof ( T_mkTextStyle ) );
   }

   /* Sinon */
   else
   {
     /* Ne rien faire */
   }

   /* Si aucune police n'a été spécifiée par l'utilisateur */
   if ( l_style.font == K_MK_NULL )
   {
      /* Configuration de la police par défaut */
      l_style.font = &g_mkDisplay.defaultFont.handle;
   }

   /* Sinon */
   else
   {
     /* Ne rien faire */
   }

   /* Récupération des couples de coordonnées */
   mk_vect2d_setCoord2Di ( &l_v1, p_request->plane.x, p_request->plane.y );
   mk_vect2d_setCoord2Di ( &l_v2, ( uint32_t ) ( p_request->plane.x + p_request->plane.width ), ( uint32_t ) ( p_request->plane.y + p_request->plane.height ) );

   /* Modification des vecteurs de coordonnées selon les valeurs de marges */
   l_result = mk_display_utils_setMargin ( &l_v1, &l_v2, &l_style );

   /* Si les paramètres sont conformes */
   if ( l_result == K_MK_OK )
   {
      /* Conversion des vecteur v1 et v2 en flottant pour la vérification des paramètres */
      mk_vect2d_setCoord ( &l_r1, ( real32_t ) l_v1.x, ( real32_t ) l_v1.y );
      mk_vect2d_setCoord ( &l_r2, ( real32_t ) l_v2.x, ( real32_t ) l_v2.y );

      /* Détermination de la validité des paramètres */
      /* Bypass du paramètre 3 */
      l_result = mk_graphics_checkVertex ( &l_r1, &l_r2, &l_r1, ( real32_t ) g_mkDisplay.screen.width, ( real32_t ) g_mkDisplay.screen.height );

      /* Si les paramètres sont conformes */
      if ( ( l_result == K_MK_OK ) && ( p_request->content.string.layer <= K_MK_GRAPHICS_BACKGROUND ) )
      {
         /* Permutation des coordonnées pour que le vecteur p_v1 pointe sur le pixel TOP_LEFT et pour que le */
         /* vecteur p_v2 pointe sur le pixel BOTTOM_RIGHT. */
         mk_vect2d_sort2Di ( &l_v1, &l_v2 );

         /* Exécution de la requête de dessin */
         l_result = mk_chromart_parseString ( p_request->content.string.layer, &l_v1, &l_v2,
                              ( T_str8 ) p_request->content.string.baseAddr, &l_style, ( T_mkTextCursor* ) p_request->content.string.cursorAddr );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


