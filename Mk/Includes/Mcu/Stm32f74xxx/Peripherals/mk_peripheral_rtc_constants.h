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
* @file mk_peripheral_rtc_constants.h
* @brief Déclaration des constantes dédiées au périphérique RTC.
* @date 6 sept. 2021
*
*/

#ifndef MK_PERIPHERAL_RTC_CONSTANTS_H
#define MK_PERIPHERAL_RTC_CONSTANTS_H

/**
 * @def K_RTC_TR
 * @brief Adresse du registre RTC_TR.
 */

#define K_RTC_TR ( addr_t ) 0x40002800

/**
 * @def K_RTC_DR
 * @brief Adresse du registre RTC_DR.
 */

#define K_RTC_DR ( addr_t ) 0x40002804

/**
 * @def K_RTC_CR
 * @brief Adresse du registre RTC_CR.
 */

#define K_RTC_CR ( addr_t ) 0x40002808

/**
 * @def K_RTC_ISR
 * @brief Adresse du registre RTC_ISR.
 */

#define K_RTC_ISR ( addr_t ) 0x4000280C

/**
 * @def K_RTC_PRER
 * @brief Adresse du registre RTC_PRER.
 */

#define K_RTC_PRER ( addr_t ) 0x40002810

/**
 * @def K_RTC_WUTR
 * @brief Adresse du registre RTC_WUTR.
 */

#define K_RTC_WUTR ( addr_t ) 0x40002814

/**
 * @def K_RTC_ALRMAR
 * @brief Adresse du registre RTC_ALRMAR.
 */

#define K_RTC_ALRMAR ( addr_t ) 0x4000281C

/**
 * @def K_RTC_ALRMBR
 * @brief Adresse du registre RTC_ALRMBR.
 */

#define K_RTC_ALRMBR ( addr_t ) 0x40002820

/**
 * @def K_RTC_WPR
 * @brief Adresse du registre RTC_WPR.
 */

#define K_RTC_WPR ( addr_t ) 0x40002824

/**
 * @def K_RTC_SSR
 * @brief Adresse du registre RTC_SSR.
 */

#define K_RTC_SSR ( addr_t ) 0x40002828

/**
 * @def K_RTC_SHIFTR
 * @brief Adresse du registre RTC_SHIFTR.
 */

#define K_RTC_SHIFTR ( addr_t ) 0x4000282C

/**
 * @def K_RTC_TSTR
 * @brief Adresse du registre RTC_TSTR.
 */

#define K_RTC_TSTR ( addr_t ) 0x40002830

/**
 * @def K_RTC_TSDR
 * @brief Adresse du registre RTC_TSDR.
 */

#define K_RTC_TSDR ( addr_t ) 0x40002834

/**
 * @def K_RTC_TSSSR
 * @brief Adresse du registre RTC_TSSSR.
 */

#define K_RTC_TSSSR ( addr_t ) 0x40002838

/**
 * @def K_RTC_CALR
 * @brief Adresse du registre RTC_CALR.
 */

#define K_RTC_CALR ( addr_t ) 0x4000283C

/**
 * @def K_RTC_TAMPCR
 * @brief Adresse du registre RTC_TAMPCR.
 */

#define K_RTC_TAMPCR ( addr_t ) 0x40002840

/**
 * @def K_RTC_ALRMASSR
 * @brief Adresse du registre RTC_ALRMASSR.
 */

#define K_RTC_ALRMASSR ( addr_t ) 0x40002844

/**
 * @def K_RTC_ALRMBSSR
 * @brief Adresse du registre RTC_ALRMBSSR.
 */

#define K_RTC_ALRMBSSR ( addr_t ) 0x40002848

/**
 * @def K_RTC_OR
 * @brief Adresse du registre RTC_OR.
 */

#define K_RTC_OR ( addr_t ) 0x4000284C

/**
 * @def K_RTC_BKR
 * @brief Adresse de base des registres de backup.
 */

#define K_RTC_BKR ( addr_t ) 0x40002850

/**
 *
 */

/**
 * @def K_RTC_INTERNAL_TIMESTAMP_FLAG
 * @brief Constante dédiée aux fonctions rtc_enableInterrupt() et rtc_disableInterrupt().\n
 *        Définition de l'identifiant des interruptions TIMESTAMP (interne et externe).
 */

#define K_RTC_INTERRUPT_TIMESTAMP 0x00008000

/**
 * @def K_RTC_INTERRUPT_WAKEUP
 * @brief Constante dédiée aux fonctions rtc_enableInterrupt() et rtc_disableInterrupt().\n
 *        Définition de l'identifiant de l'interruption WAKEUP.
 */

#define K_RTC_INTERRUPT_WAKEUP 0x00004000

/**
 * @def K_RTC_INTERRUPT_ALARMA
 * @brief Constante dédiée aux fonctions rtc_enableInterrupt() et rtc_disableInterrupt().\n
 *        Définition de l'identifiant de l'interruption ALARMA.
 */

#define K_RTC_INTERRUPT_ALARMA 0x00001000

/**
 * @def K_RTC_INTERRUPT_ALARMB
 * @brief Constante dédiée aux fonctions rtc_enableInterrupt() et rtc_disableInterrupt().\n
 *        Définition de l'identifiant de l'interruption ALARMB.
 */

#define K_RTC_INTERRUPT_ALARMB 0x00002000

/**
 *
 */

/**
 * @def K_RTC_INTERNAL_TIMESTAMP_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau INTERNAL_TIMESTAMP.
 */

#define K_RTC_INTERNAL_TIMESTAMP_FLAG 0x00020000

/**
 * @def K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau EXTERNAL_TIMESTAMP_OVERFLOW.
 */

#define K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG 0x00001000

/**
 * @def K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau EXTERNAL_TIMESTAMP.
 */

#define K_RTC_EXTERNAL_TIMESTAMP_FLAG 0x00000800

/**
 * @def K_RTC_TAMPER3_DETECTION_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau RECALIBRATION_PENDING_FLAG.
 */

#define K_RTC_FLAG_RECALIBRATION_PENDING_FLAG 0x00010000

/**
 * @def K_RTC_TAMPER1_DETECTION_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau TAMPER1_DETECTION.
 */

#define K_RTC_TAMPER1_DETECTION_FLAG 0x00002000

/**
 * @def K_RTC_TAMPER2_DETECTION_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau TAMPER2_DETECTION.
 */

#define K_RTC_TAMPER2_DETECTION_FLAG 0x00004000

/**
 * @def K_RTC_TAMPER3_DETECTION_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau TAMPER3_DETECTION.
 */

#define K_RTC_TAMPER3_DETECTION_FLAG 0x00008000

/**
 * @def K_RTC_WAKEUP_TIMER_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau WAKEUP_TIMER.
 */

#define K_RTC_WAKEUP_TIMER_FLAG 0x00000400

/**
 * @def K_RTC_WAKEUP_TIMER_WRITE_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau WAKEUP_WRITE_ALLOWED.
 */

#define K_RTC_WAKEUP_TIMER_WRITE_FLAG 0x00000004

/**
 * @def K_RTC_ALARMA_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau ALARMA.
 */

#define K_RTC_ALARMA_FLAG 0x00000100

/**
 * @def K_RTC_ALARMB_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau ALARMB.
 */

#define K_RTC_ALARMB_FLAG 0x00000200

/**
 * @def K_RTC_ALARMA_WRITE_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau ALARMA_WRITE_ALLOWED.
 */

#define K_RTC_ALARMA_WRITE_FLAG 0x00000001

/**
 * @def K_RTC_ALARMB_WRITE_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau ALARMB_WRITE_ALLOWED.
 */

#define K_RTC_ALARMB_WRITE_FLAG 0x00000002

/**
 * @def K_RTC_INIT_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau INIT_MODE.
 */

#define K_RTC_INIT_FLAG 0x00000040

/**
 * @def K_RTC_CALENDAR_SYNC_FLAG
 * @brief Constante dédiée aux fonctions rtc_clearStatus() et rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau CALENDAR_SYNC.
 *
 * @note Permet de savoir si les données des shadow-registers peuvent être
 *       lues.
 */

#define K_RTC_CALENDAR_SYNC_FLAG 0x00000020

/**
 * @def K_RTC_CALENDAR_INIT_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau CALENDAR_INIT.
 *
 * @note Permet de savoir si le calendrier a été configuré (champ année
 *       différent de 0).
 */

#define K_RTC_CALENDAR_INIT_FLAG 0x00000010

/**
 * @def K_RTC_SHIFT_OPERATION_PENDING_FLAG
 * @brief Constante dédiée à la fonction rtc_getStatus().\n
 *        Définition de l'identifiant du drapeau SHIFT_OPERATION_PENDING.
 */

#define K_RTC_SHIFT_OPERATION_PENDING_FLAG 0x00000008

/**
 *
 */

/**
 * @def K_RTC_24HOURS_FORMAT
 * @brief Constante dédiée aux fonctions rtc_getFormat() et rtc_setFormat().\n
 *        Définition de l'identifiant du format 24h.
 */

#define K_RTC_24HOURS_FORMAT 0x00000000

/**
 * @def K_RTC_AMPM_FORMAT
 * @brief Constante dédiée aux fonctions rtc_getFormat() et rtc_setFormat().\n
 *        Définition de l'identifiant du format AM-PM.
 */

#define K_RTC_AMPM_FORMAT 0x00000001

/**
 *
 */

/**
 * @def K_RTC_SOURCE_SHADOW_REGISTER
 * @brief Constante dédiée à la fonction rtc_setCalendarSource().\n
 *        Définition d'un identifiant permettant de sélectionner les
 *        shadow-registers comme source du calendrier.
 */

#define K_RTC_SOURCE_SHADOW_REGISTER 0x00000000

/**
 * @def K_RTC_SOURCE_COUNTER
 * @brief Constante dédiée à la fonction rtc_setCalendarSource().\n
 *        Définition d'un identifiant permettant de sélectionner les
 *        compteurs matériels comme source du calendrier.
 */

#define K_RTC_SOURCE_COUNTER 0x00000020

/**
 *
 */

/**
 * @def K_RTC_ALARMA
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_disableAlarm().\n
 *        Définition de l'identifiant de l'alarme A.
 */

#define K_RTC_ALARMA 0x00000000

/**
 * @def K_RTC_ALARMB
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_disableAlarm().\n
 *        Définition de l'identifiant de l'alarme B.
 */

#define K_RTC_ALARMB 0x00000001

/**
 * @def K_RTC_MONDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Lundi".
 */

#define K_RTC_MONDAY 0x00000001

/**
 * @def K_RTC_TUESDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Mardi".
 */

#define K_RTC_TUESDAY 0x00000002

/**
 * @def K_RTC_WEDNESDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Mercredi".
 */

#define K_RTC_WEDNESDAY 0x00000003

/**
 * @def K_RTC_THURSDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Jeudi".
 */

#define K_RTC_THURSDAY 0x00000004

/**
 * @def K_RTC_FRIDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Vendredi".
 */

#define K_RTC_FRIDAY 0x00000005

/**
 * @def K_RTC_SATURDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Samedi".
 */

#define K_RTC_SATURDAY 0x00000006

/**
 * @def K_RTC_SUNDAY
 * @brief Constante dédiée aux fonctions rtc_getCalendar(), rtc_setDate(), rtc_getPushedCalendar(),
 *        et rtc_enableAlarmByDay().\n
 *        Définition de l'identifiant du "Dimanche".
 */

#define K_RTC_SUNDAY 0x00000007

/**
 * @def K_RTC_BYPASS_DATE
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_enableAlarmByDay().
 *        Définition de l'identifiant du masque permettant d'ignorer la date lors de la
 *        comparaison du calendrier avec une alarme.
 */

#define K_RTC_BYPASS_DATE 0x80000000

/**
 * @def K_RTC_BYPASS_HOUR
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_enableAlarmByDay().
 *        Définition de l'identifiant du masque permettant d'ignorer l'heure lors de la
 *        comparaison du calendrier avec une alarme.
 */

#define K_RTC_BYPASS_HOUR 0x00800000

/**
 * @def K_RTC_BYPASS_MINUTE
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_enableAlarmByDay().
 *        Définition de l'identifiant du masque permettant d'ignorer les minutes lors de la
 *        comparaison du calendrier avec une alarme.
 */

#define K_RTC_BYPASS_MINUTE 0x00008000

/**
 * @def K_RTC_BYPASS_SECOND
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_enableAlarmByDay().
 *        Définition de l'identifiant du masque permettant d'ignorer les secondes lors de la
 *        comparaison du calendrier avec une alarme.
 */

#define K_RTC_BYPASS_SECOND 0x00000080

/**
 * @def K_RTC_BYPASS_DISABLED
 * @brief Constante dédiée aux fonctions rtc_enableAlarm() et rtc_enableAlarmByDay().
 *        Définition de l'identifiant du masque permettant de comparer l'intégralité du
 *        calendrier avec une alarme.
 */

#define K_RTC_BYPASS_DISABLED 0x00000000

/**
 *
 */

/**
 * @def K_RTC_ALARM_OUTPUT_OPENDRAIN
 * @brief Constante dédiée à la fonction rtc_setAlarmOutputType().\n
 *        Définition d'un identifiant permettant de configurer la broche
 *        RTC_OUT (avec l'alarme routée dessus) en OPENDRAIN.
 */

/* Fonction rtc_setAlarmOutputType */
#define K_RTC_ALARM_OUTPUT_OPENDRAIN 0x00000000

/**
 * @def K_RTC_ALARM_OUTPUT_PUSHPULL
 * @brief Constante dédiée à la fonction rtc_setAlarmOutputType().\n
 *        Définition d'un identifiant permettant de configurer la broche
 *        RTC_OUT (avec l'alarme routée dessus) en PUSHPULL.
 */

#define K_RTC_ALARM_OUTPUT_PUSHPULL 0x00000008

/**
 *
 */

/**
 * @def K_RTC_TAMPER1
 * @brief Constante dédiée aux fonctions rtc_enableTamper() et rtc_disableTamper().
 *        Définition de l'identifiant du TAMPER1.
 */

#define K_RTC_TAMPER1 0x00000000

/**
 * @def K_RTC_TAMPER2
 * @brief Constante dédiée aux fonctions rtc_enableTamper() et rtc_disableTamper().
 *        Définition de l'identifiant du TAMPER2.
 */

#define K_RTC_TAMPER2 0x00000001

/**
 * @def K_RTC_TAMPER3
 * @brief Constante dédiée aux fonctions rtc_enableTamper() et rtc_disableTamper().
 *        Définition de l'identifiant du TAMPER3.
 */

#define K_RTC_TAMPER3 0x00000002

/**
 *
 */

/**
 * @def K_RTC_TAMPER_ENABLE_INTERRUPT_MASK
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de déléguer la gestion des
 *        interruptions de type TAMPER au matériel.
 */

#define K_RTC_TAMPER_ENABLE_INTERRUPT_MASK 0x00040000

/**
 * @def K_RTC_TAMPER_DISABLE_INTERRUPT_MASK
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant d'activer les interruptions
 *        de type TAMPER (gestion logiciel).
 */

#define K_RTC_TAMPER_DISABLE_INTERRUPT_MASK 0x00010000

/**
 * @def K_RTC_TAMPER_ERASE_BACKUP_REGISTER
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant d'activer la réinitialisation
 *        des registres de backup lors de la détection d'un événement de type
 *        TAMPER.
 */

#define K_RTC_TAMPER_ERASE_BACKUP_REGISTER 0x00000000

/**
 * @def K_RTC_TAMPER_DO_NOT_ERASE_BACKUP_REGISTER
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de désactiver la réinitialisation
 *        des registres de backup lors de la détection d'un événement de type
 *        TAMPER.
 */

#define K_RTC_TAMPER_DO_NOT_ERASE_BACKUP_REGISTER 0x00020000

/**
 * @def K_RTC_TAMPER_ENABLED_ON_RISING_EDGE
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement de type TAMPER sur front montant.
 */

#define K_RTC_TAMPER_ENABLED_ON_RISING_EDGE 0x00000000

/**
 * @def K_RTC_TAMPER_ENABLED_ON_FALLING_EDGE
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement de type TAMPER sur front descendant.
 */

#define K_RTC_TAMPER_ENABLED_ON_FALLING_EDGE 0x00000001

/**
 * @def K_RTC_TAMPER_ENABLED_ON_HIGH_LEVEL
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement de type TAMPER sur niveau haut.
 */

#define K_RTC_TAMPER_ENABLED_ON_HIGH_LEVEL 0x00000001

/**
 * @def K_RTC_TAMPER_ENABLED_ON_LOW_LEVEL
 * @brief Constante dédiée à la fonction rtc_enableTamper().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement de type TAMPER sur niveau bas.
 */

#define K_RTC_TAMPER_ENABLED_ON_LOW_LEVEL 0x00000000

/**
 *
 */

/**
 * @def K_RTC_TAMPER_ENABLE_PRECHARGE
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de pré-charger les entrées TAMPER.
 *        En précharge, une résistance de pullup est insérée pendant une durée
 *        une durée définie (1RTCCLK à 8RTCCKL) puis l'acquisition de l'entrée est
 *        réalisée.
 */

#define K_RTC_TAMPER_ENABLE_PRECHARGE 0x00000000

/**
 * @def K_RTC_TAMPER_DISABLE_PRECHARGE
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de désactiver le mode précharge.
 *        En précharge, une résistance de pullup est insérée pendant une durée
 *        une durée définie (1RTCCLK à 8RTCCKL) puis l'acquisition de l'entrée est
 *        réalisée.
 */

#define K_RTC_TAMPER_DISABLE_PRECHARGE 0x00008000

/**
 * @def K_RTC_TAMPER_PRECHARGE_1RTCCLK
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de sélectionner une durée de
 *        1RTCCKL en mode précharge (cf. \ref K_RTC_TAMPER_ENABLE_PRECHARGE).
 */

#define K_RTC_TAMPER_PRECHARGE_1RTCCLK 0x00000000

/**
 * @def K_RTC_TAMPER_PRECHARGE_2RTCCLK
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de sélectionner une durée de
 *        2RTCCKL en mode précharge (cf. \ref K_RTC_TAMPER_ENABLE_PRECHARGE).
 */

#define K_RTC_TAMPER_PRECHARGE_2RTCCLK 0x00002000

/**
 * @def K_RTC_TAMPER_PRECHARGE_4RTCCLK
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de sélectionner une durée de
 *        4RTCCKL en mode précharge (cf. \ref K_RTC_TAMPER_ENABLE_PRECHARGE).
 */

#define K_RTC_TAMPER_PRECHARGE_4RTCCLK 0x00004000

/**
 * @def K_RTC_TAMPER_PRECHARGE_8RTCCLK
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de sélectionner une durée de
 *        8RTCCKL en mode précharge (cf. \ref K_RTC_TAMPER_ENABLE_PRECHARGE).
 */

#define K_RTC_TAMPER_PRECHARGE_8RTCCLK 0x00006000

/**
 * @def K_RTC_TAMPER_FILTERING_DISABLE
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de désactiver l'étage de
 *        filtrage des entrées TAMPERS.
 */

#define K_RTC_TAMPER_FILTERING_DISABLE 0x00000000

/**
 * @def K_RTC_TAMPER_FILTERING_2SAMPLES
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant d'activer l'étage de filtrage
 *        des entrées TAMPERS.\n
 *        Un maximum de 2 échantillons à la même valeur est nécessaire pour
 *        déclencher un événement.
 */

#define K_RTC_TAMPER_FILTERING_2SAMPLES 0x00000800

/**
 * @def K_RTC_TAMPER_FILTERING_4SAMPLES
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant d'activer l'étage de filtrage
 *        des entrées TAMPERS.\n
 *        Un maximum de 4 échantillons à la même valeur est nécessaire pour
 *        déclencher un événement.
 */

#define K_RTC_TAMPER_FILTERING_4SAMPLES 0x00001000

/**
 * @def K_RTC_TAMPER_FILTERING_8SAMPLES
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant d'activer l'étage de filtrage
 *        des entrées TAMPERS.\n
 *        Un maximum de 8 échantillons à la même valeur est nécessaire pour
 *        déclencher un événement.
 */

#define K_RTC_TAMPER_FILTERING_8SAMPLES 0x00001800

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_32768
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 32768.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_32768 0x00000000

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_16384
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 16384.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_16384 0x00000100

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_8192
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 8192.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_8192 0x00000200

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_4096
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 4096.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_4096 0x00000300

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_2048
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 2048.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_2048 0x00000400

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_1024
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 1024.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_1024 0x00000500

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_512
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 512.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_512 0x00000600

/**
 * @def K_RTC_TAMPER_CLOCK_RTCCLK_DIV_256
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage des entrées TAMPER.
 *        La fréquence d'échantillonnage est RTC_CLK / 256.
 */

#define K_RTC_TAMPER_CLOCK_RTCCLK_DIV_256 0x00000700

/**
 * @def K_RTC_TAMPER_ENABLE_TIMESTAMP
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant d'activer la mémorisation
 *        du calendrier lors du déclenchement d'un événement de type TAMPER.
 */

#define K_RTC_TAMPER_ENABLE_TIMESTAMP 0x00000080

/**
 * @def K_RTC_TAMPER_DISABLE_TIMESTAMP
 * @brief Constante dédiée à la fonction rtc_setTamper().\n
 *        Définition d'un identifiant permettant de désactiver la mémorisation
 *        du calendrier lors du déclenchement d'un événement de type TAMPER.
 */

#define K_RTC_TAMPER_DISABLE_TIMESTAMP 0x00000000

/**
 *
 */

/**
 * @def K_RTC_CLOCK_SOURCE_DIV16
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est RTC_CLK / 16.
 */

#define K_RTC_CLOCK_SOURCE_DIV16 0x00000000

/**
 * @def K_RTC_CLOCK_SOURCE_DIV16
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est RTC_CLK / 8.
 */

#define K_RTC_CLOCK_SOURCE_DIV8 0x00000001

/**
 * @def K_RTC_CLOCK_SOURCE_DIV4
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est RTC_CLK / 4.
 */

#define K_RTC_CLOCK_SOURCE_DIV4 0x00000002

/**
 * @def K_RTC_CLOCK_SOURCE_DIV2
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est RTC_CLK / 2.
 */

#define K_RTC_CLOCK_SOURCE_DIV2 0x00000003

/**
 * @def K_RTC_CLOCK_1HZ
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est 1Hz (horloge synchrone - ck_spre).
 */

#define K_RTC_CLOCK_1HZ 0x00000004

/**
 * @def K_RTC_CLOCK_1HZ
 * @brief Constante dédiée à la fonction rtc_enableWakeupTimer().\n
 *        Définition d'un identifiant permettant de configurer la fréquence
 *        d'échantillonnage du compteur WAKEUP.
 *        La fréquence du compteur est 1Hz (horloge synchrone - ck_spre).
 *        Le matériel ajoute 65536 à la valeur du compteur.
 */

#define K_RTC_CLOCK_1HZ_COUNTER_MAJOR 0x00000005

/**
 *
 */

/**
 * @def K_RTC_TIMESTAMP_INTERNAL
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant d'activer la mémorisation
 *        du calendrier suite une commutation d'alimentation (source principale
 *        vers la source auxiliaire).
 */

#define K_RTC_TIMESTAMP_INTERNAL 0x01000000

/**
 * @def K_RTC_TIMESTAMP_EXTERNAL
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant d'activer la mémorisation
 *        du calendrier suite à un événement externe.
 */

#define K_RTC_TIMESTAMP_EXTERNAL 0x00000800

/**
 * @def K_RTC_TIMESTAMP_PIN_PC13
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant de sélectionner la broche
 *        PC13 comme source externe.
 */

#define K_RTC_TIMESTAMP_PIN_PC13 0x00000000

/**
 * @def K_RTC_TIMESTAMP_PIN_PI8
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant de sélectionner la broche
 *        PI8 comme source externe.
 */

#define K_RTC_TIMESTAMP_PIN_PI8 0x00000002

/**
 * @def K_RTC_TIMESTAMP_PIN_PC1
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant de sélectionner la broche
 *        PC1 comme source externe.
 */

#define K_RTC_TIMESTAMP_PIN_PC1 0x00000004

/**
 * @def K_RTC_TIMESTAMP_EDGE_RISING
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement Timestamp externe sur front montant.
 */

#define K_RTC_TIMESTAMP_EDGE_RISING 0x00000000

/**
 * @def K_RTC_TIMESTAMP_EDGE_FALLING
 * @brief Constante dédiée à la fonction rtc_enableTimestamp().\n
 *        Définition d'un identifiant permettant de configurer le déclenchement
 *        d'un événement Timestamp externe sur front descendant.
 */

#define K_RTC_TIMESTAMP_EDGE_FALLING 0x00000008

/**
 *
 */

/**
 * @def K_RTC_CALIBRATION_OUTPUT_512Hz
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de router le signal
 *        CALIB_512Hz sur la broche RTC_OUT.
 */

#define K_RTC_CALIBRATION_OUTPUT_512Hz 0x00800000

/**
 * @def K_RTC_CALIBRATION_OUTPUT_1Hz
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de router le signal
 *        CALIB_1Hz sur la broche RTC_OUT.
 */

#define K_RTC_CALIBRATION_OUTPUT_1Hz 0x00880000

/**
 * @def K_RTC_ALARMA_OUTPUT
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de router le signal
 *        ALARMA sur la broche RTC_OUT.
 */

#define K_RTC_ALARMA_OUTPUT 0x00200000

/**
 * @def K_RTC_ALARMB_OUTPUT
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de router le signal
 *        ALARMB sur la broche RTC_OUT.
 */

#define K_RTC_ALARMB_OUTPUT 0x00400000

/**
 * @def K_RTC_WAKEUP_OUTPUT
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de router le signal
 *        WAKEUP sur la broche RTC_OUT.
 */

#define K_RTC_WAKEUP_OUTPUT 0x00600000

/**
 * @def K_RTC_NO_OUTPUT
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de désactiver le routage
 *        d'un signal sur la broche RTC_OUT.
 */

#define K_RTC_NO_OUTPUT 0x00000000

/**
 * @def K_RTC_POLARITY_LOW
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de configurer la polarité
 *        de la broche RTC_OUT.
 *        Le niveau actif est le niveau bas.
 */

#define K_RTC_POLARITY_LOW 0x00100000

/**
 * @def K_RTC_POLARITY_HIGH
 * @brief Constante dédiée à la fonction rtc_setOutputMultiplexer().\n
 *        Définition d'un identifiant permettant de configurer la polarité
 *        de la broche RTC_OUT.
 *        Le niveau actif est le niveau haut.
 */

#define K_RTC_POLARITY_HIGH 0x00000000

/**
 *
 */

/**
 * @def K_RTC_CALIBRATION_WINDOW_32SEC
 * @brief Constante dédiée à la fonction rtc_calibrate().\n
 *        Définition de la durée d'une fenêtre de calibration (32 secondes).
 */

#define K_RTC_CALIBRATION_WINDOW_32SEC 0x00000000

/**
 * @def K_RTC_CALIBRATION_WINDOW_16SEC
 * @brief Constante dédiée à la fonction rtc_calibrate().\n
 *        Définition de la durée d'une fenêtre de calibration (16 secondes).
 */


#define K_RTC_CALIBRATION_WINDOW_16SEC 0x00002000

/**
 * @def K_RTC_CALIBRATION_WINDOW_8SEC
 * @brief Constante dédiée à la fonction rtc_calibrate().\n
 *        Définition de la durée d'une fenêtre de calibration (8 secondes).
 */

#define K_RTC_CALIBRATION_WINDOW_8SEC  0x00004000

/**
 *
 */

#endif

