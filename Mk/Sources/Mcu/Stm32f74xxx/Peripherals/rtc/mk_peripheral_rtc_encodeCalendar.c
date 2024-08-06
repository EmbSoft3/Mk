/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_rtc_encodeCalendar.c
* @brief Définition de la fonction rtc_encodeCalendar.
* @date 8 sept. 2021
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t rtc_encodeCalendar ( T_str8 p_yymmddhhmmss000, uint32_t* p_value )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result;

   /* Déclaration d'un buffer stockant une chaine de caractères */
   uint32_t l_units, l_tens, l_syncDivisor, l_millisecond;

   /* Récupération de la valeur du prédiviseur synchrone */
   l_syncDivisor = _getField ( K_RTC_PRER, 0x00007FFF, 0 );
   l_millisecond = ( uint32_t ) ( ( ( l_syncDivisor - p_value [ 2 ] ) * 999 ) / ( l_syncDivisor + 1 ) );
   l_tens = _math_mod ( l_millisecond, 100 );
   l_units = _math_mod ( l_tens, 10 );

   /* Enregistrement du jour de la semaine */
   l_result = _getField ( p_value, 0x00000007, 13 );

   /* Encodage de la chaine de caractères yy-mm-ddThh:mm:ss,000 */
   p_yymmddhhmmss000 [0] = ( int8_t ) ( _getField ( &p_value [0], 0x0000000F, 20 ) + 0x30 );
   p_yymmddhhmmss000 [1] = ( int8_t ) ( _getField ( &p_value [0], 0x0000000F, 16 ) + 0x30 );
   p_yymmddhhmmss000 [2] = '-';
   p_yymmddhhmmss000 [3] = ( int8_t ) ( _getField ( &p_value [0], 0x00000001, 12 ) + 0x30 );
   p_yymmddhhmmss000 [4] = ( int8_t ) ( _getField ( &p_value [0], 0x0000000F, 8  ) + 0x30 );
   p_yymmddhhmmss000 [5] = '-';
   p_yymmddhhmmss000 [6] = ( int8_t ) ( _getField ( &p_value [0], 0x00000003, 4 ) + 0x30 );
   p_yymmddhhmmss000 [7] = ( int8_t ) ( _getField ( &p_value [0], 0x0000000F, 0 ) + 0x30 );
   p_yymmddhhmmss000 [8] = 'T';
   p_yymmddhhmmss000 [9]  = ( int8_t ) ( _getField ( &p_value [1], 0x00000003, 20 ) + 0x30 );
   p_yymmddhhmmss000 [10] = ( int8_t ) ( _getField ( &p_value [1], 0x0000000F, 16 ) + 0x30 );
   p_yymmddhhmmss000 [11] = ':';
   p_yymmddhhmmss000 [12] = ( int8_t ) ( _getField ( &p_value [1], 0x00000007, 12 ) + 0x30 );
   p_yymmddhhmmss000 [13] = ( int8_t ) ( _getField ( &p_value [1], 0x0000000F, 8  ) + 0x30 );
   p_yymmddhhmmss000 [14] = ':';
   p_yymmddhhmmss000 [15] = ( int8_t ) ( _getField ( &p_value [1], 0x00000007, 4 ) + 0x30 );
   p_yymmddhhmmss000 [16] = ( int8_t ) ( _getField ( &p_value [1], 0x0000000F, 0 ) + 0x30 );
   p_yymmddhhmmss000 [17] = ',';
   p_yymmddhhmmss000 [18] = ( int8_t ) ( ( l_millisecond / 100 ) + 0x30 );
   p_yymmddhhmmss000 [19] = ( int8_t ) ( ( l_tens / 10 ) + 0x30 );
   p_yymmddhhmmss000 [20] = ( int8_t ) ( ( l_units ) + 0x30 );
   p_yymmddhhmmss000 [21] = '\0';

   /* Retour */
   return ( l_result );
}
