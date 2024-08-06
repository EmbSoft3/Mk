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
* @file mk_system_rtc_init.c
* @brief Définition de la fonction mk_system_rtc_init.
* @date 8 sept. 2021
*
*/

#include "mk_system_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_sysCode mk_system_rtc_init ( void )
{
   /* Déclaration de la variable de retour */
   T_sysCode l_result = K_SYS_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_value = rtc_getBackupBit ( );

   /* Si le bit de backup n'est pas positionné alors */
   /* une reconfiguration doit être effectuée */
   if ( l_value == 0 )
   {
      /* Désactivation de la protection en écriture */
      rtc_disableWriteProtect ( );

      /* Désactivation des interruptions RTC */
      rtc_disableInterrupt ( K_RTC_INTERRUPT_TIMESTAMP | K_RTC_INTERRUPT_WAKEUP | K_RTC_INTERRUPT_ALARMA | K_RTC_INTERRUPT_ALARMB );

      /* Activation du mode initialisation */
      /* Les compteurs du calendrier se figent */
      l_value = rtc_enableInitMode ( 0xFFF );

      /* Si aucune erreur ne s'est produite */
      if ( l_value == 1 )
      {
         /* Configuration de la valeur des pré-diviseurs */
         /* La source du RTC est l'oscillateur LSE (32.768kHz) */
         /* f_ckasyn = F_LSE / 128 = 256 Hz, f_cksync = f_ckasyn / 256 = 1Hz */
         rtc_setPrescaler ( 255, 127 );

         /* Désactivation de la broche RTC_OUT */
         rtc_setOutputMultiplexer ( K_RTC_NO_OUTPUT, K_RTC_POLARITY_HIGH );

         /* Désactivation de la synchronisation externe */
         rtc_disableExternalSynchronisation ( );

         /* Désactivation des 3 tampers */
         rtc_disableTamper ( K_RTC_TAMPER1 );
         rtc_disableTamper ( K_RTC_TAMPER2 );
         rtc_disableTamper ( K_RTC_TAMPER3 );

         /* Désactivation du timestamp */
         rtc_disableTimestamp ( );

         /* Désactivation du wakeup timer */
         rtc_disableWakeupTimer ( );

         /* Configuration du format de la date */
         rtc_setFormat ( K_RTC_24HOURS_FORMAT );

         /* Configuration de la source du calendrier */
         /* Note - Mode Counter obligatoire pour écrire les registres */
         rtc_setCalendarSource ( K_RTC_SOURCE_COUNTER );

         /* Configuration des valeurs initiales du calendrier */
         /* JAN 01 2000 (Saturday) */
         rtc_setDate ( K_RTC_SATURDAY, ( T_str8 ) "00-01-01" );
         rtc_setTime ( ( T_str8 ) "00:00:00" );

         /* Réinitialisation des drapeaux d'interruptions */
         rtc_clearStatus ( K_RTC_INTERNAL_TIMESTAMP_FLAG | K_RTC_TAMPER3_DETECTION_FLAG | K_RTC_TAMPER2_DETECTION_FLAG | K_RTC_TAMPER1_DETECTION_FLAG |
                           K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG | K_RTC_WAKEUP_TIMER_FLAG | K_RTC_ALARMA_FLAG | K_RTC_ALARMB_FLAG | K_RTC_CALENDAR_SYNC_FLAG );

         /* Désactivation du mode initialisation */
         rtc_disableInitMode ( );

         /* Le bit de backup est positionné quand l'utilisateur configure l'horloge à la vrai date */
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_SYS_ERROR_RTC;
      }

      /* Réactivation de la protection en écriture */
      rtc_enableWriteProtect ( );
   }

   /* Sinon, on conserve la configuration enregistrée dans les registres non volatiles */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


