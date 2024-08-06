/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_norflash_psram.h
* @brief Déclaration des fonctions dédiées aux contrôleurs NORFLASH, PSRAM, SRAM et ROM.
* @date 16 oct. 2022
*
*/

#ifndef MK_PERIPHERAL_NORFLASH_PSRAM_H
#define MK_PERIPHERAL_NORFLASH_PSRAM_H

/**
 * @fn void norflash_psram_enableBank ( void_t p_bank );
 * @brief Cette fonction active une bank de mémoire.
 *
 * @param[in] p_bank Ce paramètre contient l'adresse de la bank à activer. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 *
 * @return Sans objet.
 * @note Après le reset, la bank 1 est activée, les autres désactivées. Une bank désactivée ne peut pas être accédée.
 *
 */

void norflash_psram_enableBank ( void_t p_bank );

/**
 * @fn void norflash_psram_disableBank ( void_t p_bank );
 * @brief Cette fonction désactive une bank de mémoire.
 *
 * @param[in] p_bank Ce paramètre contient l'adresse de la bank à désactiver. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 *
 * @return Sans objet.
 * @note Après le reset, la bank 1 est activée, les autres désactivées. Une bank désactivée ne peut pas être accédée.
 *
 */

void norflash_psram_disableBank ( void_t p_bank );

/**
 * @fn void norflash_psram_setMemoryType ( void_t p_bank );
 * @brief Cette fonction configure le type de mémoire relié à une bank de mémoire.
 *
 * @param[in] p_bank Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type Ce paramètre contient le type de la mémoire reliée à la bank. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_SRAM, \ref K_NORFLASH_PSRAM_PSRAM, \ref K_NORFLASH_PSRAM_NORFLASH et \ref K_NORFLASH_PSRAM_ONENANDFLASH
 *
 * @return Sans objet.
 *
 */

void norflash_psram_setMemoryType ( void_t p_bank, uint32_t p_type );

/**
 * @fn void norflash_psram_setMemoryBus ( void_t p_bank, uint32_t p_dataBusWidth, uint32_t p_multiplexedMode );
 * @brief Cette fonction configure le format du bus de données.
 *
 * @param[in] p_bank            Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                              \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_dataBusWidth    Ce paramètre contient la taille du bus de données. Une des constantes suivantes peut être utilisées : \n
 *                              \ref K_NORFLASH_PSRAM_8BITS, \ref K_NORFLASH_PSRAM_16BITS et \ref K_NORFLASH_PSRAM_32BITS
 * @param[in] p_multiplexedMode Ce paramètre indique si le mode multiplexé doit être activé :
 *                              \li \ref K_NORFLASH_PSRAM_ENABLE_MULTIPLEXED_MODE : les lignes d'adresses [15:0] sont multiplexées avec les lignes de données [15:0].
 *                              \li \ref K_NORFLASH_PSRAM_DISABLE_MULTIPLEXED_MODE : les lignes d'adresses [15:0] ne sont pas multiplexées avec les lignes de données [15:0].
 *
 * @return Sans objet.
 * @note Le mode multiplexé est dédié aux mémoires de type PSRAM et NORFLASH.
 *
 */

void norflash_psram_setMemoryBus ( void_t p_bank, uint32_t p_dataBusWidth, uint32_t p_multiplexedMode );

/**
 * @fn void norflash_psram_setPageSize ( void_t p_bank, uint32_t p_pageSize );
 * @brief Cette fonction configure la taille d'une page de donnée d'une mémoire CRAM.
 *
 * @param[in] p_bank     Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                       \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_pageSize Ce paramètre contient la taille d'une page de données. Une des constantes suivantes peut être utilisées : \n
 *                       \ref K_NORFLASH_PSRAM_PAGE_SIZE_DISABLED, \ref K_NORFLASH_PSRAM_PAGE_SIZE_128_BYTES, \ref K_NORFLASH_PSRAM_PAGE_SIZE_256_BYTES,
 *                       \ref K_NORFLASH_PSRAM_PAGE_SIZE_512_BYTES et \ref K_NORFLASH_PSRAM_PAGE_SIZE_1024_BYTES
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mémoire CRAM. Le paramètre \ref K_NORFLASH_PSRAM_PAGE_SIZE_DISABLED doit être sélectionné pour les autres types de mémoires.
 *
 */

void norflash_psram_setPageSize ( void_t p_bank, uint32_t p_pageSize );

/**
 * @fn void norflash_psram_setNWaitPolarity ( void_t p_bank, uint32_t p_polarity );
 * @brief Cette fonction configure la polarité et le timing du signal NWAIT.
 *
 * @param[in] p_bank     Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                       \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_polarity Ce paramètre contient la polarité du signal NWAIT. Une des constantes suivantes peut être utilisées : \n
 *                       \ref K_NORFLASH_PSRAM_NWAIT_ACTIVE_LOW, \ref K_NORFLASH_PSRAM_NWAIT_ACTIVE_HIGH.
 *
 * @return Sans objet.
 *
 */

void norflash_psram_setNWaitPolarity ( void_t p_bank, uint32_t p_polarity );

/**
 * @fn void norflash_psram_setReadOperation ( void_t p_bank, uint32_t p_type );
 * @brief Cette fonction configure le type des accès en lecture (synchrone ou asynchrone).
 *
 * @param[in] p_bank Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type Ce paramètre contient la méthode de réalisation des accès en lecture. Une des constantes suivantes peut être utilisées :
 *                   \li \ref K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS : les opérations de lecture sont réalisées de manière asynchrone, le mode burst est désactivé.
 *                   \li \ref K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS  : les opérations de lecture sont réalisées de manière synchrone, le mode burst est activé.
 *
 * @return Sans objet.
 * @note Le paramètre \ref K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS ne doit être utilisé que pour les mémoires synchrones fonctionnement en mode burst.
 *
 */

void norflash_psram_setReadOperation ( void_t p_bank, uint32_t p_type );

/**
 * @fn void norflash_psram_setWriteOperation ( void_t p_bank, uint32_t p_writeEnabled, uint32_t p_type, uint32_t p_writeFifoEnabled );
 * @brief Cette fonction configure le type des accès en écriture (synchrone ou asynchrone).
 *
 * @param[in] p_bank             Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_writeEnabled     Ce paramètre permet d'activer ou désactiver les opérations d'écritures. Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_ENABLE_WRITE_OPERATION et \ref K_NORFLASH_PSRAM_DISABLE_WRITE_OPERATION.
 * @param[in] p_type             Ce paramètre contient la méthode de réalisation des accès en écriture. Une des constantes suivantes peut être utilisées :
 *                               \li \ref K_NORFLASH_PSRAM_ASYNCHRONOUS_ACCESS : les opérations d'écriture sont réalisées de manière asynchrone, le mode burst est désactivé.
 *                               \li \ref K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS  : les opérations de lecture sont réalisées de manière synchrone, le mode burst est activé.
 * @param[in] p_writeFifoEnabled Ce paramètre permet d'activer ou désactiver les FIFOs d'écriture de TOUTES les banques. Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_ENABLE_WRITE_FIFO et \ref K_NORFLASH_PSRAM_DISABLE_WRITE_FIFO.\n
 *                               La configuration du FIFO avec les paramètres \ref K_NORFLASH_PSRAM_BANK2 à \ref K_NORFLASH_PSRAM_BANK4 est sans effet.
 *
 * @return Sans objet.
 * @note Le paramètre \ref K_NORFLASH_PSRAM_SYNCHRONOUS_ACCESS ne doit être utilisé que pour les mémoires synchrones fonctionnement en mode burst.
 *
 */

void norflash_psram_setWriteOperation ( void_t p_bank, uint32_t p_writeEnabled, uint32_t p_type, uint32_t p_writeFifoEnabled );

/**
 * @fn void norflash_psram_setAsynchronousConfiguration ( void_t p_bank, uint32_t p_nwaitEnabled, uint32_t p_clockEnabled, uint32_t p_extendedTimingEnabled );
 * @brief Cette fonction configure les caractéristiques du mode asynchrone.
 *
 * @param[in] p_bank                  Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                                    \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_nwaitEnabled          Ce paramètre permet d'activer ou désactiver l'utilisation du signal NWAIT en mode asynchrone. Une des constantes suivantes peut être utilisées : \n
 *                                    \ref K_NORFLASH_PSRAM_ENABLE_NWAIT et \ref K_NORFLASH_PSRAM_DISABLE_NWAIT.
 * @param[in] p_clockEnabled          Ce paramètre permet d'activer ou désactiver la génération de l'horloge pour les accès asynchrones. Une des constantes suivantes peut être utilisées : \n
 *                                    \ref K_NORFLASH_PSRAM_ENABLE_CLOCK et \ref K_NORFLASH_PSRAM_DISABLE_CLOCK.
 *                                    La configuration de l'horloge avec les paramètres \ref K_NORFLASH_PSRAM_BANK2 à \ref K_NORFLASH_PSRAM_BANK4 est sans effet.
 * @param[in] p_extendedTimingEnabled Ce paramètre permet de programmer les timings de lecture et d'écriture du mode asynchrone indépendemment. Une des constantes suivantes peut être utilisées :
 *                                    \li \ref K_NORFLASH_PSRAM_ENABLE_EXTENDED_TIMING  : les timings d'écriture et de lecture sont indépendant et programmé à l'aide
 *                                    des constantes \ref K_NORFLASH_PSRAM_TYPE_READ et \ref K_NORFLASH_PSRAM_TYPE_WRITE.
 *                                    \li \ref K_NORFLASH_PSRAM_DISABLE_EXTENDED_TIMING : les timings d'écriture et de lecture sont identiques et programmé à l'aide
 *                                    de la constante \ref K_NORFLASH_PSRAM_TYPE_READ.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode asynchrone.
 *
 */

void norflash_psram_setAsynchronousConfiguration ( void_t p_bank, uint32_t p_nwaitEnabled, uint32_t p_clockEnabled, uint32_t p_extendedTimingEnabled );

/**
 * @fn void norflash_psram_setSynchronousConfiguration ( void_t p_bank, uint32_t p_nwaitTiming, uint32_t p_waitStateEnabled )
 * @brief Cette fonction configure les caractéristiques du mode synchrone.
 *
 * @param[in] p_bank             Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_nwaitTiming      Ce paramètre contient le mode de pilotage du signal NWAIT. Une des constantes suivantes peut être utilisées :
 *                               \li \ref K_NORFLASH_PSRAM_NWAIT_ASSERTED_BEFORE_WAITSTATE : le signal NWAIT est activé un cycle avant la phase d'attente.
 *                               \li \ref K_NORFLASH_PSRAM_NWAIT_ASSERTED_DURING_WAITSTATE : le signal NWAIT est activé en même temps que  la phase d'attente.
 * @param[in] p_waitStateEnabled Ce paramètre permet d'activer ou désactiver l'insertion d'un ou plusieurs WaitState après la période de latence.
 *                               Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_ENABLE_WAITSTATE et \ref K_NORFLASH_PSRAM_DISABLE_WAITSTATE.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode synchrone.
 *       Le paramètre \ref K_NORFLASH_PSRAM_NWAIT_ASSERTED_DURING_WAITSTATE ne doit pas être utilisé pour les mémoires PSRAM.
 *
 */

void norflash_psram_setSynchronousConfiguration ( void_t p_bank, uint32_t p_nwaitTiming, uint32_t p_waitStateEnabled );

/**
 * @fn void norflash_psram_setAccessMode ( void_t p_bank, uint32_t p_type, uint32_t p_mode );
 * @brief Cette fonction configure les modes d'accès étendu de la mémoire. La description de ces modes est disponible dans le datasheet du composant (§13.5.4).\n
 *        Si le mode étendu est désactivé, la mémoire fonctionne en mode 1 ou 2 :
 *        \li Mode 1 : mode par défaut pour les mémoires SRAM/PSRAM.
 *        \li Mode 2 : mode par défaut pour les mémoires NOR.
 *
 * @param[in] p_bank Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                   \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type Ce paramètre contient le type de registre à configurer. Une des constantes suivantes peut être utilisées :
 *                   \li \ref K_NORFLASH_PSRAM_TYPE_READ : configuration du registre de lecture.
 *                   \li \ref K_NORFLASH_PSRAM_TYPE_WRITE : configuration du registre d'écriture.
 * @param[in] p_mode Ce paramètre configure le mode d'accès de la mémoire. Une des constantes suivantes peut être utilisées :
 *                   \li \ref K_NORFLASH_PSRAM_MODE_A : le mode d'accès A est activé (SRAM/PSRAM (CRAM), les activations de OE sont indépendantes des timing d'écriture et de lecture).
 *                   \li \ref K_NORFLASH_PSRAM_MODE_B : le mode d'accès B est activé (NOR Flash, les activations de NWE sont indépendantes des timing d'écriture et de lecture).
 *                   \li \ref K_NORFLASH_PSRAM_MODE_C : le mode d'accès C est activé (NOR Flash, les activations de NOE sont indépendantes des timing d'écriture et de lecture).
 *                   \li \ref K_NORFLASH_PSRAM_MODE_D : le mode d'accès D est activé (Accès asynchrone).
 *
 * @return Sans objet.
 * @note Le mode B correspond au mode 2.
 *
 */

void norflash_psram_setAccessMode ( void_t p_bank, uint32_t p_type, uint32_t p_mode );

/**
 * @fn void norflash_psram_setClockSpeed ( void_t p_bank, uint32_t p_clockPrescaler );
 * @brief Cette fonction configure la fréquence de l'horloge du bus FMC_CLK.
 *
 * @param[in] p_bank           Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                             \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_clockPrescaler Ce paramètre contient le rapport de division entre les horloges HCLK (périphérique) et FMC_CLK (bus). Il évolue de [1 à 15] avec :
 *                             \li Valeur 1 : FMC_CLK = 2.HCLK période
 *                             \li Valeur 2 : FMC_CLK = 3.HCLK période
 *                             \li ...
 *                             \li Valeur 15 : FMC_CLK = 16.HCLK période
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée au mode synchrone.
 *
 */

void norflash_psram_setClockSpeed ( void_t p_bank, uint32_t p_clockPrescaler );

/**
 * @fn void norflash_psram_setDataLatency ( void_t p_bank, uint32_t p_clockCycles );
 * @brief Cette fonction configure le nombre de cycles d'horloge FMC_CLK (+2) nécessaires avant de lire ou écrire les premières données sur le bus.
 *
 * @param[in] p_bank        Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                          \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_clockCycles Ce paramètre contient le nombre de cycles d'horloge (en multiple de l'horloge FMC_CLK) à insérer avant de lire ou écrire les premières données sur le bus.
 *                          Il évolue de [0 à 15] avec :
 *                          \li Valeur 0 : 2 cycles FMC_CLK de latence,
 *                          \li Valeur 1 : 3 cycles FMC_CLK de latence,
 *                          \li ...
 *                          \li Valeur 15 : 17 cycles FMC_CLK de latence.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux transferts en mode synchrone (écriture et lecture).
 * @warning Pour les mémoires de types PSRAM (CSRAM), le paramètre p_clockCycles doit obligatoirement être configurée à 0.
 *
 */

void norflash_psram_setDataLatency ( void_t p_bank, uint32_t p_clockCycles );

/**
 * @fn void norflash_psram_setTurnaroundPhase ( void_t p_bank, uint32_t p_type, uint32_t p_clockCycles );
 * @brief Cette fonction configure le nombre de cycles d'horloge HCLK inséré entre 2 lectures/écritures consécutives (ou inversement). Ce délai est inséré entre :
 *        \li  une lecture asynchrone (mode D ou mode multiplexé) et une autre lecture/écriture synchrone ou asynchrone.
 *        \li  une écriture et une autre lecture/écriture synchrone ou asynchrone.
 *        La bank peut être différente sauf pour les écritures en modes D ou en mode multiplexé.
 *
 * @param[in] p_bank        Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                          \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type        Ce paramètre contient le type de registre à configurer. Une des constantes suivantes peut être utilisées :
 *                          \li \ref K_NORFLASH_PSRAM_TYPE_READ : configuration du registre de lecture.
 *                          \li \ref K_NORFLASH_PSRAM_TYPE_WRITE : configuration du registre d'écriture.
 * @param[in] p_clockCycles Ce paramètre contient le nombre de cycles d'horloge (en multiple de l'horloge HCLK) constituant la phase de turnaround. Il évolue de [0 à 15] avec :
 *                          \li Valeur 0 : 0 cycle HCLK ajouté
 *                          \li Valeur 1 : 1 cycle HCLK ajouté
 *                          \li ...
 *                          \li Valeur 15 : 15 cycles HCLK ajouté
 *
 * @return Sans objet.
 * @warning Dans certaine situation, le délai est fixe. Cf. bit BUSTRUN[3:0] du registre FMC_BTR1..4.
 *
 */

void norflash_psram_setTurnaroundPhase ( void_t p_bank, uint32_t p_type, uint32_t p_clockCycles );

/**
 * @fn void norflash_psram_setDataPhase ( void_t p_bank, uint32_t p_type, uint32_t p_clockCycles );
 * @brief Cette fonction configure la durée de la phase de données en mode asynchrone.
 *
 * @param[in] p_bank        Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                          \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type        Ce paramètre contient le type de registre à configurer. Une des constantes suivantes peut être utilisées :
 *                          \li \ref K_NORFLASH_PSRAM_TYPE_READ : configuration du registre de lecture.
 *                          \li \ref K_NORFLASH_PSRAM_TYPE_WRITE : configuration du registre d'écriture.
 * @param[in] p_clockCycles Ce paramètre contient le nombre de cycles d'horloge (en multiple de l'horloge HCLK) constituant la phase de donnée. Il évolue de [1 à 255] avec :
 *                          \li Valeur 1 : durée de 1 cycle HCLK en lecture, 2 cycles en écriture
 *                          \li Valeur 2 : durée 2 cycles HCLK en lecture, 3 cycles en écriture
 *                          \li ...
 *                          \li Valeur 255 : durée de 255 cycles HCLK en lecture, 256 en écriture.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux transferts en mode asynchrone.
 *
 */

void norflash_psram_setDataPhase ( void_t p_bank, uint32_t p_type, uint32_t p_clockCycles );

/**
 * @fn void norflash_psram_setAddressPhases ( void_t p_bank, uint32_t p_type, uint32_t p_setupPhaseCycles, uint32_t p_holdPhaseCycles );
 * @brief Cette fonction configure la durée des phases de configuration (setup) et de maintien (hold) des lignes d'adresse.
 *
 * @param[in] p_bank             Ce paramètre contient l'adresse de la bank à configurer. Une des constantes suivantes peut être utilisées : \n
 *                               \ref K_NORFLASH_PSRAM_BANK1, \ref K_NORFLASH_PSRAM_BANK2, \ref K_NORFLASH_PSRAM_BANK3 et \ref K_NORFLASH_PSRAM_BANK4.
 * @param[in] p_type             Ce paramètre contient le type de registre à configurer. Une des constantes suivantes peut être utilisées :
 *                               \li \ref K_NORFLASH_PSRAM_TYPE_READ : configuration du registre de lecture.
 *                               \li \ref K_NORFLASH_PSRAM_TYPE_WRITE : configuration du registre d'écriture.
 * @param[in] p_setupPhaseCycles Ce paramètre contient le nombre de cycles d'horloge (en multiple de l'horloge HCLK) constituant la phase de configuration. Il évolue de [0 à 15] avec :
 *                               \li Valeur 0 : durée de 0 cycle HCLK
 *                               \li Valeur 1 : durée 1 cycles HCLK
 *                               \li ...
 *                               \li Valeur 15 : durée de 15 cycles HCLK.
 * @param[in] p_holdPhaseCycles  Ce paramètre contient le nombre de cycles d'horloge (en multiple de l'horloge HCLK) constituant la phase de maintien. Il évolue de [1 à 15] avec :
 *                               \li Valeur 1 : durée de 1 cycle HCLK
 *                               \li Valeur 2 : durée 1 cycles HCLK
 *                               \li ...
 *                               \li Valeur 15 : durée de 15 cycles HCLK.
 *
 * @return Sans objet.
 * @note Cette fonction est dédiée aux transferts en mode asynchrone.
 * @warning En modes D ou en mode multiplexé, la valeur minimale du paramètre p_setupPhaseCycles est 1 HCLK.
 *
 */

void norflash_psram_setAddressPhases ( void_t p_bank, uint32_t p_type, uint32_t p_setupPhaseCycles, uint32_t p_holdPhaseCycles );

/**
 *
 */

#endif

