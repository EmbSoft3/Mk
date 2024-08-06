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
* @file mk_peripheral_rtc_setTime.c
* @brief Définition de la fonction rtc_setTime.
* @date 6 sept. 2021
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void rtc_setTime ( T_str8 p_hhmmss )
{
   /* Récupération du format de l'heure */
   uint32_t l_format = _getField ( K_RTC_CR, 0x01, 6 );

   /* Configuration du format */
   _putField ( K_RTC_TR, 0x00000001, l_format, 22 ); /* Format */

   /* Eciture de l'heure au format hh:mm:ss */
   _putField ( K_RTC_TR, 0x00000003, ( uint32_t ) ( p_hhmmss[0] - 0x30 ), 20 ); /* Heure - dizaine (BCD) */
   _putField ( K_RTC_TR, 0x0000000F, ( uint32_t ) ( p_hhmmss[1] - 0x30 ), 16 ); /* Heure - unité (BCD) */
   _putField ( K_RTC_TR, 0x00000007, ( uint32_t ) ( p_hhmmss[3] - 0x30 ), 12 ); /* Minute - dizaine (BCD) */
   _putField ( K_RTC_TR, 0x0000000F, ( uint32_t ) ( p_hhmmss[4] - 0x30 ), 8 );  /* Minute - unité (BCD) */
   _putField ( K_RTC_TR, 0x00000007, ( uint32_t ) ( p_hhmmss[6] - 0x30 ), 4 );  /* Seconde - dizaine (BCD) */
   _putField ( K_RTC_TR, 0x0000000F, ( uint32_t ) ( p_hhmmss[7] - 0x30 ), 0 );  /* Seconde - unité (BCD) */

   /* Retour */
   return;
}


