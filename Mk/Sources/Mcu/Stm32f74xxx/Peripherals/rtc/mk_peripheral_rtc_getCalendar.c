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
* @file mk_peripheral_rtc_getCalendar.c
* @brief Définition de la fonction rtc_getCalendar.
* @date 7 sept. 2021
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

uint32_t rtc_getCalendar ( T_str8 p_yymmddhhmmss000 )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration d'uneRTC_DR, RTC_TR, RTC_SSR  */
   uint32_t l_value [ 6 ]; /* 2* ( RTC_DR, RTC_TR, RTC_SSR )  */

   /* Récupération de la valeur des registres du calendrier */
   /* On réalise deux lectures pour garantir la synchronisation entre les registres */
   _rtc_read ( l_value );

   /* On compare ensuite la valeur des registres RTC_SSR et RTC_TR lors */
   /* des deux séquences de lecture */
   if ( ( l_value [ 2 ] == l_value [ 5 ] ) && ( l_value [ 1 ] == l_value [ 4 ] ) )
   {
      /* Encodage de la chaine de caractères yy-mm-ddThh:mm:ss,000 */
      l_result = rtc_encodeCalendar ( p_yymmddhhmmss000, l_value );
   }

   /* Sinon */
   else
   {
      /* Récupération de la valeur des registres du calendrier */
      /* On réalise deux lectures pour garantir la synchronisation entre les registres */
      _rtc_read ( l_value );

      /* On compare ensuite la valeur des registres RTC_SSR et RTC_TR lors */
      /* des deux séquences de lecture */
      if ( ( l_value [ 2 ] == l_value [ 5 ] ) && ( l_value [ 1 ] == l_value [ 4 ] ) )
      {
         /* Encodage de la chaine de caractères yy-mm-ddThh:mm:ss,000 */
         l_result = rtc_encodeCalendar ( p_yymmddhhmmss000, l_value );
      }

      /* Sinon */
      else
      {
         p_yymmddhhmmss000 [ 0 ] = '\0';
      }

   }

   /* Retour */
   return ( l_result );
}




