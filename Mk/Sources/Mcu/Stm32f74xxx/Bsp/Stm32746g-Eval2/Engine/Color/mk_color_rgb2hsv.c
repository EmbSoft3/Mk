/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_color_rgb2hsv.c
* @brief Définition de la fonction mk_color_rgb2hsv.
* @date 14 avr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_color_rgb2hsv ( T_mkARGB* p_argb, T_mkAHSV* p_ahsv )
{
   /* Déclaration d'une couleur RGB */
   real32_t l_red   = ( real32_t ) p_argb->red   / 255.0f;
   real32_t l_green = ( real32_t ) p_argb->green / 255.0f;
   real32_t l_blue  = ( real32_t ) p_argb->blue  / 255.0f;

   /* Récupération des valeurs minimale et maximale de la couleur RGB */
   real32_t l_rgbMin = _math_vmin3 ( l_red, l_green, l_blue );
   real32_t l_rgbMax = _math_vmax3 ( l_red, l_green, l_blue );

   /* Détermination du différentiel min-max */
   real32_t l_delta = ( l_rgbMax - l_rgbMin );

   /* La composante "value" du format HSV est égale à la valeur MAX du format RGB */
   p_ahsv->value = l_rgbMax;

   /* Copie de la composante alpha */
   p_ahsv->alpha = p_argb->alpha / 255.0f;

   /* Si la composante "value" est nulle */
   if ( p_ahsv->value <= 0.0f )
   {
      p_ahsv->hue = 0.0f;
      p_ahsv->saturation = 0.0f;
   }

   /* Sinon */
   else
   {
      /* Détermination de la valeur de la composante "saturation" */
      p_ahsv->saturation = ( l_delta ) / l_rgbMax;

      /* Si la composante "saturation" est nulle */
      if ( p_ahsv->saturation <= 0.0f )
      {
         /* La composante teinte est nulle */
         p_ahsv->hue = 0.0f;
      }

      /* Sinon */
      else
      {
         /* Si la composante RGB de plus haute valeur est la composante rouge */
         if ( l_red >= l_rgbMax )
         {
            /* Détermination de la valeur de la composante "hue" */
            p_ahsv->hue = 60.0f * ( l_green - l_blue ) / l_delta;
         }

         /* Sinon si la composante RGB de plus haute valeur est la composante verte */
         else if ( l_green >= l_rgbMax )
         {
            /* Détermination de la valeur de la composante "hue" */
            p_ahsv->hue = 60.0f * ( 2.0f + ( l_blue - l_red ) / l_delta );
         }

         /* Sinon */
         else
         {
            /* Détermination de la valeur de la composante "hue" */
            p_ahsv->hue = 60.0f * ( 4.0f + ( l_red - l_green ) / l_delta );
         }
      }
   }

   /* Si une translation doit être effectuée */
   if ( p_ahsv->hue < 0 )
   {
      p_ahsv->hue += 360.0f;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}


