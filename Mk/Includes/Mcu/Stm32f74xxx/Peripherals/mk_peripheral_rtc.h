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
* @file mk_peripheral_rtc.h
* @brief Déclaration des fonctions dédiées au périphérique RTC.
* @date 6 sept. 2021
*
*
*/

#ifndef MK_PERIPHERAL_RTC_H
#define MK_PERIPHERAL_RTC_H

/**
 * @fn void rtc_enableWriteProtect ( void );
 * @brief Cette fonction réactive la protection en écriture suite à une désactivation (\ref rtc_disableWriteProtect).
 *
 * @return Sans objet.
 *
 */

void rtc_enableWriteProtect ( void );

/**
 * @fn void rtc_enableWriteProtect ( void );
 * @brief Cette fonction désactive la protection en écriture.
 *
 * @return Sans objet.
 *
 */

void rtc_disableWriteProtect ( void );

/**
 * @fn void rtc_enableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction active une plusieurs interruptions du périphérique RTC.
 *
 * @param[in] p_mask Ce paramètre contient les identifiants des interruptions à activer. Une combinaison des constantes suivantes
 *                   peut être utilisée : \n \ref K_RTC_INTERRUPT_TIMESTAMP, \ref K_RTC_INTERRUPT_WAKEUP, \ref K_RTC_INTERRUPT_ALARMA,
 *                   et \ref K_RTC_INTERRUPT_ALARMB.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableInterrupt ( uint32_t p_mask );

/**
 * @fn void rtc_disableInterrupt ( uint32_t p_mask );
 * @brief Cette fonction désactive une plusieurs interruptions du périphérique RTC.
 *
 * @param[in] p_mask Ce paramètre contient les identifiants des interruptions à activer. Une combinaison des constantes suivantes
 *                   peut être utilisée : \n \ref K_RTC_INTERRUPT_TIMESTAMP, \ref K_RTC_INTERRUPT_WAKEUP, \ref K_RTC_INTERRUPT_ALARMA,
 *                   et \ref K_RTC_INTERRUPT_ALARMB.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_disableInterrupt ( uint32_t p_mask );

/**
 * @fn uint32_t rtc_getStatus ( uint32_t p_mask );
 * @brief Cette fonction retourne un ou plusieurs statuts du périphérique RTC.
 *
 * @param[in] p_mask Ce paramètre contient la combinaison des identifiants de statuts à renvoyer. Une combinaison des constantes suivantes peut être
 *                   utilisée :\n \ref K_RTC_INTERNAL_TIMESTAMP_FLAG, \ref K_RTC_FLAG_RECALIBRATION_PENDING_FLAG, \ref K_RTC_TAMPER3_DETECTION_FLAG,
 *                   \ref K_RTC_TAMPER2_DETECTION_FLAG, \ref K_RTC_TAMPER1_DETECTION_FLAG, \ref K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG,
 *                   \ref K_RTC_EXTERNAL_TIMESTAMP_FLAG, \ref K_RTC_WAKEUP_TIMER_FLAG, \ref K_RTC_ALARMA_FLAG, \ref K_RTC_ALARMB_FLAG, \ref K_RTC_INIT_FLAG
 *                   \ref K_RTC_CALENDAR_SYNC_FLAG, \ref K_RTC_CALENDAR_INIT_FLAG, \ref K_RTC_SHIFT_OPERATION_PENDING_FLAG, \ref K_RTC_WAKEUP_TIMER_WRITE_FLAG,
 *                   \ref K_RTC_ALARMA_WRITE_FLAG et \ref K_RTC_ALARMB_WRITE_FLAG.
 *
 * @return La valeur des statuts identifiés en paramètre.
 *
 */

uint32_t rtc_getStatus ( uint32_t p_mask );

/**
 * @fn void rtc_clearStatus ( uint32_t p_mask );
 * @brief Cette fonction réinitialise un ou plusieurs statuts du périphérique RTC.
 *
 * @param[in] p_mask Ce paramètre contient la combinaison des identifiants de statuts à renvoyer. Une combinaison des constantes suivantes peut être
 *                   utilisée :\n \ref K_RTC_INTERNAL_TIMESTAMP_FLAG, \ref K_RTC_TAMPER3_DETECTION_FLAG,
 *                   \ref K_RTC_TAMPER2_DETECTION_FLAG, \ref K_RTC_TAMPER1_DETECTION_FLAG, \ref K_RTC_EXTERNAL_TIMESTAMP_OVERFLOW_FLAG,
 *                   \ref K_RTC_EXTERNAL_TIMESTAMP_FLAG, \ref K_RTC_WAKEUP_TIMER_FLAG, \ref K_RTC_ALARMA_FLAG, \ref K_RTC_ALARMB_FLAG et
 *                   \ref K_RTC_CALENDAR_SYNC_FLAG.
 *
 * @note Si le flag K_RTC_INTERNAL_TIMESTAMP_FLAG doit être réinitialiser, le flag K_RTC_EXTERNAL_TIMESTAMP_FLAG doit être réinitialisé en même temps.
 * @return Sans objet.
 *
 */

void rtc_clearStatus ( uint32_t p_mask );

/**
 * @fn void rtc_setPrescaler ( uint32_t p_mask );
 * @brief Cette fonction configure les deux prédiviseurs (synchrone et asynchrone) du périphérique RTC. Les sources du diviseur synchrone (RTCCLK)
 *        peuvent être les oscillateurs LSE (32.768kHz), HSE/32 et LSI. Les sources du prédiviseur synchrone peuvent être l'entrée RTC_REFIN (suite à
 *        l'exécution de la fonction \ref rtc_enableExternalSynchronisation) ou la sortie du diviseur asynchrone.\n
 *        Les fréquence en sortie des diviseur f_ckasync et f_cksync sont exprimés de la manière suivante :\n
 *        f_ckasync = F_RTCCLK / (p_asyncPrescaler + 1) et f_cksync = F_RTCCLK / ( ( p_asyncPrescaler + 1 ) * ( p_syncPrescaler + 1 ) ).\n
 *        Le but est d'obtenir une fréquence de 1Hz en sortie du diviseur synchrone.
 *
 * @param[in] p_syncPrescaler  Ce paramètre contient la valeur du prédiviseur synchrone. Il évolue de [0 à 32767].
 * @param[in] p_asyncPrescaler Ce paramètre contient la valeur du prédiviseur asynchrone. Il évolue de [0 à 127].
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @return Sans objet.
 *
 */

void rtc_setPrescaler ( uint32_t p_syncPrescaler, uint32_t p_asyncPrescaler );

/**
 * @fn void rtc_setCalendarSource ( uint32_t p_source );
 * @brief Cette fonction configure la source du calendrier.
 *
 * @param[in] p_source Ce paramètre contient la source du calendrier. Une des constantes suivantes peut être utilisée :
 *                     \li \ref K_RTC_SOURCE_SHADOW_REGISTER : les valeurs du calendrier sont issues des registres spécialisés mis à jour
 *                              tous les 2 RTCCLK cycles (configuration par défaut).
 *                     \li \ref K_RTC_SOURCE_COUNTER : les valeurs du calendrier sont directement issues des compteurs matériels. Lorsque
 *                              la fréquence de l'horloge APB est inférieure à 7 fois l'horloge RTCCLK, cette configuration doit être choisie.
 *                              Dans cette configuration, les registres d'horodatage ne sont pas réinitialisé lors d'un reset.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_setCalendarSource ( uint32_t p_source );

/**
 * @fn uint32_t rtc_enableInitMode ( uint32_t p_timeout );
 * @brief Cette fonction active le mode permettant l'initialisation de certain registre du périphérique.
 *
 * @param[in] p_timeout Ce paramètre contient la valeur du timeout d'initialisation. Le périphérique a besoin d'un maximum de
 *                      2.RTCCLOCK pour activer le mode.
 *
 * @return La valeur 1 si le périphérique est en mode initialisation, sinon 0.
 *
 */

uint32_t rtc_enableInitMode ( uint32_t p_timeout );

/**
 * @fn void rtc_disableInitMode ( void );
 * @brief Cette fonction désactive le mode permettant l'initialisation de certain registre du périphérique. Suite à l'exécution de cette fonction,
 *        les fonctions de comptage sont réactivées.
 *
 * @return Sans objet.
 *
 */

void rtc_disableInitMode ( void );

/**
 * @fn void rtc_setFormat ( uint32_t p_format );
 * @brief Cette fonction configure le format de l'heure du calendrier et des alarmes.
 * @param[in] p_format  Ce paramètre contient le format de l'heure du calendrier et des alarmes. Une des constantes suivantes peut être utilisée. \n
 *                      \ref K_RTC_24HOURS_FORMAT ou \ref K_RTC_AMPM_FORMAT
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @return Sans objet.
 *
 */

void rtc_setFormat ( uint32_t p_format );

/**
 * @fn uint32_t rtc_getFormat ( void );
 * @brief Cette fonction retourne le format de l'heure du calendrier.
 *
 * @return La valeur \ref K_RTC_24HOURS_FORMAT ou \ref K_RTC_AMPM_FORMAT en fonction du paramètrage du périphérique.
 *
 */

uint32_t rtc_getFormat ( void );

/**
 * @fn void rtc_setBackupBit ( void );
 * @brief Cette fonction positionne au niveau logique 1 le bit de backup réservé à l'utilisateur (bit non volatile).
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_setBackupBit ( void );

/**
 * @fn void rtc_resetBackupBit ( void );
 * @brief Cette fonction positionne au niveau logique 0 le bit de backup réservé à l'utilisateur (bit non volatile).
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_resetBackupBit ( void );

/**
 * @fn uint32_t rtc_getBackupBit ( void );
 * @brief Cette fonction retourne la valeur du bit de backup réservé à l'utilisateur (bit non volatile).
 *
 * @return La valeur 1 si le bit est positionné, sinon la valeur 0.
 *
 */

uint32_t rtc_getBackupBit ( void );

/**
 * @fn void rtc_enableWinter ( void );
 * @brief Cette fonction active l'heure d'hiver. Une heure est retranchée du calendrier (doit être effectuée à une heure du matin à minima).
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableWinter ( void );

/**
 * @fn void rtc_enableSummer ( void );
 * @brief Cette fonction active l'heure d'été. Une heure est ajoutée du calendrier.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableSummer ( void );

/**
 * @fn void rtc_setOutputMultiplexer ( uint32_t p_signal, uint32_t p_polarity );
 * @brief Cette fonction configure le signal routé sur la sortie RTC_OUT.
 *
 * @param[in] p_signal   Ce paramètre contient l'identifiant de la fonction routée sur la sortie RTC_OUT. Une des constantes suivantes peut être
 *                       utilisée : \n \ref K_RTC_CALIBRATION_OUTPUT_512Hz, \ref K_RTC_CALIBRATION_OUTPUT_1Hz, \ref K_RTC_ALARMA_OUTPUT,
 *                       \ref K_RTC_ALARMB_OUTPUT, \ref K_RTC_WAKEUP_OUTPUT ou \ref K_RTC_NO_OUTPUT.
 * @param[in] p_polarity Ce paramètre contient la polarité du signal RTC_OUT (valide uniquemnent avec les options \ref K_RTC_ALARMA_OUTPUT,
 *                       \ref K_RTC_ALARMB_OUTPUT ou \ref K_RTC_WAKEUP_OUTPUT. Une des constantes suivantes peut être utliisée :\n
 *                       \li \ref K_RTC_POLARITY_LOW : la sortie est au niveau logique bas lors du déclenchement de la fonction.
 *                       \li \ref K_RTC_POLARITY_HIGH : la sortie est au niveau logique haut lors du déclenchement de la fonction.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_setOutputMultiplexer ( uint32_t p_signal, uint32_t p_polarity );

/**
 * @fn void rtc_enableExternalSynchronisation ( void );
 * @brief Cette fonction active les mécanismes de correction de la dérive de l'horloge RTC à partir d'une source d'horloge externe plus stable.
 *        Pour fonctionner, la précision de l'horloge externe (50Hz ou 60Hz) doit être plus stable que l'oscillateur LSE (32.768kHz).
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @return Sans objet.
 *
 */

void rtc_enableExternalSynchronisation ( void );

/**
 * @fn void rtc_disableExternalSynchronisation ( void );
 * @brief Cette fonction désactive les mécanismes de correction de la dérive de l'horloge RTC à partir d'une source d'horloge externe ultra stable.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @return Sans objet.
 *
 */

void rtc_disableExternalSynchronisation ( void );

/**
 * @fn void rtc_setTime ( T_str8 p_hhmmss, uint32_t p_format );
 * @brief Cette fonction configure le temps au format hh:mm:ss. Le format doit être configuré avant d'exécuter cette fonction (\ref rtc_setFormat).
 *
 * @param[in] p_hhmmss Ce paramètre est une chaine de caractères contenant la valeur du temps système (ex. "13:45:12").
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @note Le paramètre \ref K_RTC_SOURCE_COUNTER doit être sélectionné pour configurer l'heure (fonction \ref rtc_setCalendarSource).
 * @return Sans objet.
 *
 */

void rtc_setTime ( T_str8 p_hhmmss );

/**
 * @fn void _rtc_read ( uint32_t* p_buf );
 * @brief Cette fonction retourne la valeur des registre RTC_DR (index 0 et 3), RTC_TR (index 1 et 4) et RTC_SSR (index 2 et 5).
 * @param[out] p_buf Ce paramètre contient l'adresse d'un buffer (taille 6 mots).
 *
 * @return Sans objet.
 *
 */

void _rtc_read ( uint32_t* p_buf );

/**
 * @fn uint32_t rtc_getCalendar ( T_str8 p_yymmddhhmmss000 );
 * @brief Cette fonction retourne le calendrier au format yy-mm-ddThh:mm:ss,000.
 * @param[out] p_yymmddhhmmss000 Ce paramètre est une chaine de caractères contenant la valeur du temps système (ex. "21-09-07T13:45:12,123").
 *                               Une taille de 22 octets est nécessaire (21 caractères + '\0').
 *
 * @return La valeur \ref K_RTC_MONDAY à \ref K_RTC_SUNDAY en fonction du jour de la semaine ou la valeur 0 si la fonction a échoué.
 *
 */

uint32_t rtc_getCalendar ( T_str8 p_yymmddhhmmss000 );

/**
 * @fn uint32_t rtc_encodeCalendar ( T_str8 p_yymmddhhmmss000, uint32_t* p_value );
 * @brief Cette fonction convertit les données binaires contenues dans p_value au format yy-mm-ddThh:mm:ss,000.
 * @param[out] p_yymmddhhmmss000 Ce paramètre est une chaine de caractères contenant la valeur du temps système (ex. "21-09-07T13:45:12,123").
 *                               Une taille de 22 octets est nécessaire (21 caractères + '\0').
 * @param[in]  p_value           Ce paramètre pointe sur la valeur des 3 registres du calendrier (indice 0 - RTC_(TS)DR, indice 1 - RTC_(TS)TR,
 *                               indice 2 - RTC_(TS)SSR).
 *
 * @return La valeur \ref K_RTC_MONDAY à \ref K_RTC_SUNDAY en fonction du jour de la semaine.
 *
 */

uint32_t rtc_encodeCalendar ( T_str8 p_yymmddhhmmss000, uint32_t* p_value );

/**
 * @fn void rtc_setDate ( T_str8 p_yymmdd, uint32_t p_weekday );
 * @brief Cette fonction configure la date au format yy-mm-dd.
 *
 * @param[in] p_weekday Ce paramètre contient la valeur du jour de la semaine. Les constantes \ref K_RTC_MONDAY à \ref K_RTC_SUNDAY peuvent être utilisées.
 * @param[in] p_yymmdd  Ce paramètre est une chaine de caractères contenant la valeur de la date système (ex. "20-12-01").
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @note Le périphérique doit être configuré en mode initialisation avant d'exécuter cette fonction (\ref rtc_enableInitMode).
 * @note Le paramètre \ref K_RTC_SOURCE_COUNTER doit être sélectionné pour configurer la date (fonction \ref rtc_setCalendarSource).
 * @return Sans objet.
 *
 */

void rtc_setDate ( uint32_t p_weekday, T_str8 p_yymmdd );

/**
 * @fn void rtc_enableTimestamp ( uint32_t p_type, uint32_t p_pin, uint32_t p_edge );
 * @brief Cette fonction active le mécanisme de sauvegarde des valeurs d'horodatage sur événement.
 *        Lors d'un événement (interne ou externe), les données d'horodatage sont sauvegardées dans des
 *        registres spécialisés (fonction \ref rtc_getPushedCalendar).\n
 *        L'événement interne est généré lorsque la source d'alimentation auxilaire VBAT est active. L'événement externe est généré lors d'une transition
 *        d'état d'une broche GPIO.\n
 *
 * @param[in] p_type Ce paramètre contient le type d'événement déclenchant l'horodatage. Une des constantes suivantes peut être utilisée : \n
 *                   \ref K_RTC_TIMESTAMP_INTERNAL et \ref K_RTC_TIMESTAMP_EXTERNAL.
 * @param[in] p_pin  Ce paramètre est dédié à l'événement \ref K_RTC_TIMESTAMP_EXTERNAL. Il contient l'identifiant de la broche GPIO à utiliser. Une des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_RTC_TIMESTAMP_PIN_PC13, \ref K_RTC_TIMESTAMP_PIN_PI8 et \ref K_RTC_TIMESTAMP_PIN_PC1.
 * @param[in] p_edge Ce paramètre est dédié à l'événement \ref K_RTC_TIMESTAMP_EXTERNAL. Il contient le type de front déclenchant l'événement. Une des constantes
 *                   suivantes peut être utilisée : \n
 *                   \ref K_RTC_TIMESTAMP_EDGE_RISING et \ref K_RTC_TIMESTAMP_EDGE_FALLING.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableTimestamp ( uint32_t p_type, uint32_t p_pin, uint32_t p_edge );

/**
 * @fn void rtc_disableTimestamp ( void );
 * @brief Cette fonction désactive le mécanisme de sauvegarde des valeurs d'horodatage sur événement.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_disableTimestamp ( void );

/**
 * @fn void rtc_shift ( uint32_t p_operation, uint32_t p_value );
 * @brief Cette fonction permet de corriger les dérives de l'horloge interne en apportant une correction (offset). Elle compare la valeur des registres
 *        RTC_SSR et RTC_TSTR (Timestamp) puis apporte une correction. Une horloge 1Hz de haute précision doit être appliqué sur la broche de gestion des timestamp.
 *
 * @note Cette fonction doit être exécutée suite à la sauvegarde d'au moins une valeur d'horodatage sur événement externe.
 * @warning Fonction non définie - ne pas utiliser.
 * @return Sans objet.
 *
 */

void rtc_shift ( void );

/**
 * @fn uint32_t rtc_getPushedCalendar ( T_str8 p_yymmddhhmmss000 );
 * @brief Cette fonction retourne le calendrier mémorisé lors d'un événement (au format yy-mm-ddThh:mm:ss,000).
 * @param[out] p_yymmddhhmmss000 Ce paramètre est une chaine de caractères contenant la valeur du temps système (ex. "21-09-07T13:45:12,123").
 *                               Une taille de 22 octets est nécessaire (22 caractères + '\0').
 *
 * @note La valeur de l'année 'yy' est fixe est vaut "00".
 * @return La valeur \ref K_RTC_MONDAY à \ref K_RTC_SUNDAY en fonction du jour de la semaine.
 *
 */

uint32_t rtc_getPushedCalendar ( T_str8 p_yymmddhhmmss000 );

/**
 * @fn void rtc_enableWakeupTimer ( uint32_t p_mask );
 * @brief Cette fonction active le Wakeup_Timer. Suite à l'activation, une interruption est générée périodiquement.
 *
 * @param[in] p_clock Ce paramètre contient la source d'horloge du timer. Une des constantes suivantes peut être utilisée : \n
 *                    \ref K_RTC_CLOCK_SOURCE_DIV16, \ref K_RTC_CLOCK_SOURCE_DIV8, \ref K_RTC_CLOCK_SOURCE_DIV4,
 *                    \ref K_RTC_CLOCK_SOURCE_DIV2, \ref K_RTC_CLOCK_1HZ et \ref K_RTC_CLOCK_1HZ_COUNTER_MAJOR.\n
 *                    Lorsque la valeur \ref K_RTC_CLOCK_1HZ_COUNTER_MAJOR est choisie, le périphérique ajoute 65536 à
 *                    la valeur du compteur (permet d'augmenter la durée d'occurence du timer).
 * @param[in] p_count Ce paramètre contient la valeur du compteur qui déclenche l'interruption (sur 16 bits). Une interruption est générée
 *                    lorsque le compteur interne atteint la valeur ( p_count + 1 ) ou ( p_count + 65537 ) en fonction de la configuration
 *                    définie dans p_clock.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableWakeupTimer ( uint32_t p_clock, uint32_t p_count );

/**
 * @fn void rtc_disableWakeupTimer ( void );
 * @brief Cette fonction désactive le Wakeup_Timer.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_disableWakeupTimer ( void );

/**
 * @fn void rtc_enableAlarm ( uint32_t p_alarm, uint32_t p_weekday, T_str8 p_ddhhmmss, uint32_t p_bypass );
 * @brief Cette fonction active une des deux alarmes. Le format de l'heure doit être configuré avant l'exécution de cette fonction (\ref rtc_setFormat).
 *
 * @param[in] p_alarm    Ce paramètre contient l'identifiant de l'alarme. Une des constantes suivantes peut être utilisée :\n
 *                       \ref K_RTC_ALARMA ou \ref K_RTC_ALARMB
 * @param[in] p_ddhhmmss Ce paramètre est une chaine de caractères contenant le jour et la date de déclenchement de l'alarme (ex. "20-02:12:30").
 * @param[in] p_mask     Ce paramètre contient un masque permettant de bypasser le résultat de la comparaison entre les attributs de l'alarme et
 *                       la valeur du calendrier. Une combinaison des constantes suivantes peut être utilisée :\n
 *                       \ref K_RTC_BYPASS_DISABLED, \ref K_RTC_BYPASS_DATE, \ref K_RTC_BYPASS_HOUR, \ref K_RTC_BYPASS_MINUTE et \ref K_RTC_BYPASS_SECOND.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableAlarm ( uint32_t p_alarm, T_str8 p_ddhhmmss, uint32_t p_bypass );

/**
 * @fn void rtc_enableAlarmByDay ( uint32_t p_alarm, uint32_t p_day, T_str8 p_hhmmss, uint32_t p_bypass );
 * @brief Cette fonction active une des deux alarmes. Le format de l'heure doit être configuré avant l'exécution de cette fonction (\ref rtc_setFormat).
 *
 * @param[in] p_alarm  Ce paramètre contient l'identifiant de l'alarme. Une des constantes suivantes peut être utilisée :\n
 *                     \ref K_RTC_ALARMA ou \ref K_RTC_ALARMB
 * @param[in] p_day    Ce paramètre contient le jour de la semaine. Une des constantes suivantes peut être utilisée :\n
 *                     \ref K_RTC_MONDAY à \ref K_RTC_SUNDAY
 * @param[in] p_hhmmss Ce paramètre est une chaine de caractères contenant l'heure de déclenchement de l'alarme (ex. "02:12:30").
 * @param[in] p_bypass Ce paramètre contient un masque permettant de bypasser le résultat de la comparaison entre les attributs de l'alarme et
 *                     la valeur du calendrier. Une combinaison des constantes suivantes peut être utilisée :\n
 *                     \ref K_RTC_BYPASS_DATE, \ref K_RTC_BYPASS_HOUR, \ref K_RTC_BYPASS_MINUTE et \ref K_RTC_BYPASS_SECOND;
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_enableAlarmByDay ( uint32_t p_alarm, uint32_t p_day, T_str8 p_hhmmss, uint32_t p_bypass );

/**
 * @fn void rtc_disableAlarm ( uint32_t p_alarm );
 * @brief Cette fonction désactive une des deux alarmes.
 * @param[in] p_alarm Ce paramètre contient l'identifiant de l'alarme. Une des constantes suivantes peut être utilisée :\n
 *                    \ref K_RTC_ALARMA ou \ref K_RTC_ALARMB
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_disableAlarm ( uint32_t p_alarm );

/**
 * @fn void rtc_setAlarmOutputType ( uint32_t p_outputType );
 * @brief Cette fonction configure le type de la broche de sortie signalant une alarme (PC13).
 * @param[in] p_outputType Ce paramètre contient le type de la broche. Un des constantes suivantes peut être utilisée : \n
 *                         \ref K_RTC_ALARM_OUTPUT_OPENDRAIN ou \ref K_RTC_ALARM_OUTPUT_PUSHPULL.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_setAlarmOutputType ( uint32_t p_outputType );

/**
 * @fn void rtc_calibrate ( uint32_t p_calibrationPeriod, uint32_t p_ppulse, uint32_t p_npulse );
 * @brief Cette fonction permet de corriger les dérives de l'horloge interne en apportant une calibration. Les valeurs de calibration sont vérifiées
 *        en routant le signal sur la sortie RTC_OUT (fonction \ref rtc_setOutputMultiplexer).
 *
 * @param[in] p_calibrationPeriod Ce paramètre contient la durée de la fenêtre de calibration. Une des constantes suivantes peut être utilisée :\n
 *                                \ref K_RTC_CALIBRATION_WINDOW_32SEC, \ref K_RTC_CALIBRATION_WINDOW_16SEC, \ref K_RTC_CALIBRATION_WINDOW_8SEC.
 * @param[in] p_ppulse            Ce paramètre permet d'augmenter la fréquence du calendrier de 488.5 ppm. Il évolue de [0 à 1].
 * @param[in] p_npulse            Ce paramètre permet de reduire la fréquence du calendrier de 0.9537 ppm. Il évolue de [0 à 511].
 *
 * @note Lorsqu'une fenêtre de durée \ref K_RTC_CALIBRATION_WINDOW_8SEC est utilisée, les bits D0 et D1 de p_npulse sont obligatoirement positionné à 0.
 *       De même pour la durée \ref K_RTC_CALIBRATION_WINDOW_16SEC, où uniquement le bit D0 est positionné à 0. \n
 *       La fonction rtc_getStatut doit être utilisée pour savoir si le périphérique peut être calibré.
 *
 * @note La protection en écriture doit être être désactivée avant d'exécuter cette fonction (\ref rtc_disableWriteProtect).
 * @return Sans objet.
 *
 */

void rtc_calibrate ( uint32_t p_calibrationPeriod, uint32_t p_ppulse, uint32_t p_npulse );

/**
 * @fn void rtc_setTamper ( uint32_t p_precharge, uint32_t p_prechargeDuration, uint32_t p_sampleNumber, uint32_t p_samplingFrequency, uint32_t p_enableTimestamp );
 * @brief Cette fonction paramètre la fonction Tamper du périphérique RTC. Cette fonction est utilisée pour réinitialiser les registres de backup accessibles
 *        au travers de la fonction \ref rtc_getBackupRegister, générer une interruption capable de réveiller le CPU depuis les modes STOP ou STANDBY ou
 *        générer un événement matériel pour les timers basses consommation.
 *
 * @param[in] p_precharge         Ce paramètre permet de cabler une résistance de pullup sur les entrées Tamper avant de réaliser l'acquisition. Une des constantes
 *                                suivantes peut être utilisée : \n \ref K_RTC_TAMPER_ENABLE_PRECHARGE ou \ref K_RTC_TAMPER_DISABLE_PRECHARGE.
 * @param[in] p_prechargeDuration Ce paramètre configure la durée pour laquel la résistance de pullup est activée avant de réaliser l'acquisition. Une des constantes
 *                                suivantes peut être utilisée : \n \ref K_RTC_TAMPER_PRECHARGE_1RTCCLK, \ref K_RTC_TAMPER_PRECHARGE_2RTCCLK,
 *                                \ref K_RTC_TAMPER_PRECHARGE_4RTCCLK ou \ref K_RTC_TAMPER_PRECHARGE_8RTCCLK.
 * @param[in] p_sampleNumber      Ce paramètre configure le nombre d'échantillons consécutifs à la même valeur générant un événement. Un des constantes suivantes peut être
 *                                utilisée : \n \ref K_RTC_TAMPER_FILTERING_DISABLE, \ref K_RTC_TAMPER_FILTERING_2SAMPLES, \ref K_RTC_TAMPER_FILTERING_4SAMPLES ou
 *                                \ref K_RTC_TAMPER_FILTERING_8SAMPLES.\n
 *                                Lorsque la constante \ref K_RTC_TAMPER_FILTERING_DISABLE est sélectionnée, la détection de l'événement est réalisée sur front.
 * @param[in] p_samplingFrequency Ce paramètre configure la fréquence d'échantillonage des entrées. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_32768, \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_16384, \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_8192,
 *                                \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_4096, \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_2048, \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_1024,
 *                                \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_512 ou \ref K_RTC_TAMPER_CLOCK_RTCCLK_DIV_256.
 * @param[in] p_enableTimestamp   Ce paramètre permet de sauvergarder les valeurs d'horodatage (accessible par la fonction \ref rtc_getPushedCalendar)
 *                                lors du déclenchement d'un événement. Une des constantes suivantes peut être utilisée : \n
 *                                \ref K_RTC_TAMPER_ENABLE_TIMESTAMP et \ref K_RTC_TAMPER_DISABLE_TIMESTAMP.
 * @return Sans objet.
 *
 */

void rtc_setTamper ( uint32_t p_precharge, uint32_t p_prechargeDuration, uint32_t p_sampleNumber, uint32_t p_samplingFrequency, uint32_t p_enableTimestamp );

/**
 * @fn void rtc_enableTamper ( uint32_t p_tamper, uint32_t p_interruptMode, uint32_t p_backupErase, uint32_t p_activeLevel );
 * @brief Cette fonction active un tamper. Elle doit être exécutée après l'appel de la fonction \ref rtc_setTamper.
 *
 * @param[in] p_tamper        Ce paramètre contient l'identifiant du tamper à activer. Une des constantes suivantes peut être utilisée : \n
 *                            \ref K_RTC_TAMPER1, \ref K_RTC_TAMPER2 ou \ref K_RTC_TAMPER3.
 * @param[in] p_interruptMode Ce paramètre permet de masquer les interruptions dédiés au tamper. Lorsque l'interruption est masqué, la gestion du drapeau d'interruption
 *                            est réalisée par le matériel. En outre, les registres de backup ne sont pas réinitialisés. Une des constantes suivantes peut être
 *                            utilisée : \n \ref K_RTC_TAMPER_ENABLE_INTERRUPT_MASK ou \ref K_RTC_TAMPER_DISABLE_INTERRUPT_MASK.
 * @param[in] p_backupErase   Ce paramètre permet d'activer la réinitialisation automatique des registres de backup lors de la détection d'un événement. Une des
 *                            constantes suivantes peut être utilisée : \n \ref K_RTC_TAMPER_ERASE_BACKUP_REGISTER ou \ref K_RTC_TAMPER_DO_NOT_ERASE_BACKUP_REGISTER.
 * @param[in] p_activeLevel   Ce paramètre contient le type (niveau/front) d'événement activant le tamper. Il est fonction de la valeur du paramètre p_sampleNumber
 *                            de la fonction \ref rtc_setTamper. \n
 *                            Dans la situation où p_sampleNumber est égale à K_RTC_TAMPER_FILTERING_DISABLE, une des constantes suivantes peut être utilisée : \n
 *                            \ref K_RTC_TAMPER_ENABLED_ON_RISING_EDGE ou K_RTC_TAMPER_ENABLED_ON_FALLING_EDGE.
 *                            Dans la situation où p_sampleNumber est différent de K_RTC_TAMPER_FILTERING_DISABLE, une des constantes suivantes peut être utilisée : \n
 *                            \ref K_RTC_TAMPER_ENABLED_ON_HIGH_LEVEL ou K_RTC_TAMPER_ENABLED_ON_LOW_LEVEL.
 *
 * @return Sans objet.
 *
 */

void rtc_enableTamper ( uint32_t p_tamper, uint32_t p_interruptMode, uint32_t p_backupErase, uint32_t p_activeLevel );

/**
 * @fn void rtc_disableTamper ( uint32_t p_tamper );
 * @brief Cette fonction désactive un tamper.
 * @param[in] p_tamper Ce paramètre contient l'identifiant du tamper à désactiver. Une des constantes suivantes peut être utilisée : \n
 *                     \ref K_RTC_TAMPER1, \ref K_RTC_TAMPER2 ou \ref K_RTC_TAMPER3.
 *
 * @return Sans objet.
 *
 */

void rtc_disableTamper ( uint32_t p_tamper );

/**
 * @fn uint32_t* rtc_getBackupRegister ( void );
 * @brief Cette fonction retourne l'adresse du premier registre 32bits de backup (total de 32 registres).
 *
 * @return L'adresse du premier registre de backup.
 *
 */

uint32_t* rtc_getBackupRegister ( void );

/**
 *
 */

#endif
