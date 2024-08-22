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
* @file mk_color_hsv2rgb.c
* @brief Définition de la fonction mk_color_hsv2rgb.
* @date 14 avr. 2019
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_color_hsv2rgb ( T_mkAHSV* p_ahsv, T_mkARGB* p_argb )
{
   /* Déclaration d'une variable stockant la composante chroma */
   real32_t l_chroma = p_ahsv->value * p_ahsv->saturation;

   /* Déclaration d'une variable stockant la valeur de modulation */
   real32_t l_mod = p_ahsv->value - l_chroma;

   /* Déclaration des variables de travail */
   uint32_t l_m = _math_mod2 ( ( uint32_t ) ( p_ahsv->hue / 60.0f ), 1 );
   real32_t l_x = l_chroma * ( 1.0f - _math_vabs ( ( real32_t ) l_m - 1.0f ) );

   /* Copie de la composante alpha */
   p_argb->alpha = ( uint8_t ) _math_floor ( p_ahsv->alpha * 255.0f );

   /* Conversion de la couleur HSV */
   /* Région 1 */
   if ( ( p_ahsv->hue >= 0.0f ) && ( p_ahsv->hue < 60.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
   }

   /* Région 2 */
   else if ( ( p_ahsv->hue >= 60.0f && p_ahsv->hue < 120.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
   }

   /* Région 3 */
   else if ( ( p_ahsv->hue >= 120.0f && p_ahsv->hue < 180.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
   }

   /* Région 4 */
   else if ( ( p_ahsv->hue >= 180.0f && p_ahsv->hue < 240.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
   }

   /* Région 5 */
   else if ( ( p_ahsv->hue >= 240.0f && p_ahsv->hue < 300.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
   }

   /* Région 6 */
   else if ( ( p_ahsv->hue >= 300.0f && p_ahsv->hue < 360.0f ) )
   {
      p_argb->red   = ( uint8_t ) _math_ceil ( ( l_chroma + l_mod ) * 255.0f );
      p_argb->green = ( uint8_t ) _math_ceil ( ( l_mod ) * 255.0f );
      p_argb->blue  = ( uint8_t ) _math_ceil ( ( l_x + l_mod ) * 255.0f );
   }

   /* Région non définie */
   else
   {
      p_argb->red   = 0;
      p_argb->green = 0;
      p_argb->blue  = 0;
   }

   /* Retour */
   return;
}
