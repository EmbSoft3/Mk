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
* @file mk_peripheral_rtc_setDate.c
* @brief Définition de la fonction rtc_setDate.
* @date 6 sept. 2021
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void rtc_setDate ( uint32_t p_weekday, T_str8 p_yymmdd )
{
   /* Ecriture du registre RTC_DR */
   _putField ( K_RTC_DR, 0x00000007, p_weekday, 13 ); /* Année - dizaine (BCD) */

   /* Eciture de la date au format yy-mm-dd */
   _putField ( K_RTC_DR, 0x0000000F, ( uint32_t ) ( p_yymmdd[0] - 0x30 ), 20 ); /* Année - dizaine (BCD) */
   _putField ( K_RTC_DR, 0x0000000F, ( uint32_t ) ( p_yymmdd[1] - 0x30 ), 16 ); /* Année - unité (BCD) */
   _putField ( K_RTC_DR, 0x00000001, ( uint32_t ) ( p_yymmdd[3] - 0x30 ), 12 ); /* Mois - dizaine (BCD) */
   _putField ( K_RTC_DR, 0x0000000F, ( uint32_t ) ( p_yymmdd[4] - 0x30 ), 8 );  /* Mois - unité (BCD) */
   _putField ( K_RTC_DR, 0x00000003, ( uint32_t ) ( p_yymmdd[6] - 0x30 ), 4 );  /* Jour - dizaine (BCD) */
   _putField ( K_RTC_DR, 0x0000000F, ( uint32_t ) ( p_yymmdd[7] - 0x30 ), 0 );  /* Jour - unité (BCD) */

   /* Retour */
   return;
}



