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
* @file mk_peripheral_rtc_enableAlarm.c
* @brief Définition de la fonction rtc_enableAlarm.
* @date 7 sept. 2021
*
*/

#include "mk_peripheral_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void rtc_enableAlarm ( uint32_t p_alarm, T_str8 p_ddhhmmss, uint32_t p_bypass )
{
   /* Récupération du format de l'heure */
   uint32_t l_format = _getField ( K_RTC_CR, 0x01, 6 );

   /* Configuration du format */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x00000001, l_format, 22 );

   /* Ecriture des registres RTC_ALRMAR et RTC_ALRMBR */
   _writeField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0xC0808080, p_bypass );

   /* Eciture de la date de l'alarme au format dd-hh:mm:ss */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x00000003, ( uint32_t ) ( p_ddhhmmss[0] - 0x30 ), 28 ); /* Date - dizaine (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x0000000F, ( uint32_t ) ( p_ddhhmmss[1] - 0x30 ), 24 ); /* Date - unité (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x00000003, ( uint32_t ) ( p_ddhhmmss[3] - 0x30 ), 20 ); /* Heure - dizaine (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x0000000F, ( uint32_t ) ( p_ddhhmmss[4] - 0x30 ), 16 ); /* Heure - unité (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x00000007, ( uint32_t ) ( p_ddhhmmss[6] - 0x30 ), 12 ); /* Minute - dizaine (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x0000000F, ( uint32_t ) ( p_ddhhmmss[7] - 0x30 ), 8 ); /* Minute - unité (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x00000007, ( uint32_t ) ( p_ddhhmmss[9] - 0x30 ), 4 ); /* Seconde - dizaine (BCD) */
   _putField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x0000000F, ( uint32_t ) ( p_ddhhmmss[10] - 0x30 ), 0 ); /* Seconde - unité (BCD) */
   _writeField ( ( addr_t ) ( K_RTC_ALRMAR + p_alarm ), 0x0F007FFF, 0x00000000 );

   /* Ecriture du registre RTC_CR */
   _or ( K_RTC_CR, ( uint32_t ) ( 0x00000100 << p_alarm ) );

   /* Retour */
   return;
}


