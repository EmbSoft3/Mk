/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_supervisor_fault_types.h
* @brief Déclaration des types dédiés aux traitements des erreurs.
* @date 11 nov. 2023
*
*/

#ifndef MK_SUPERVISOR_FAULT_TYPES_H
#define MK_SUPERVISOR_FAULT_TYPES_H

/**
 * @enum T_mkSupervisorCode
 * @brief Déclaration de l'énumération T_mkSupervisorCode.
 * @note Les codes 1 à 262143 sont provisionnés pour l'initialisation.
 *
 */

typedef enum T_mkSupervisorCode
{
   K_MK_SUPERVISOR_ERROR_CODE10 = 10,                          /*!< Identifiant du code d'erreur n°10. */
   K_MK_SUPERVISOR_ERROR_CODE20 = 20,                          /*!< Identifiant du code d'erreur n°20. */
   K_MK_SUPERVISOR_ERROR_CODE30 = 30,                          /*!< Identifiant du code d'erreur n°30. */
   K_MK_SUPERVISOR_ERROR_CODE100 = 100,                        /*!< Identifiant du code d'erreur n°100. */
   K_MK_SUPERVISOR_ERROR_CODE110 = 110                         /*!< Identifiant du code d'erreur n°110. */
} T_mkSupervisorCode;

/**
 * @enum T_mkSupervisorFault
 * @brief Déclaration de l'énumération T_mkSupervisorFault.
 * @warning Ne pas modifier l'ordre des attributs.
 *
 */

typedef enum T_mkSupervisorFault
{
   K_MK_SUPERVISOR_NMIFAULT = 0x01,                            /*!< Identifiant d'une erreur matérielle de type NMI_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_HARDFAULT = 0x02,                           /*!< Identifiant d'une erreur matérielle de type HARD_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_MEMFAULT = 0x03,                            /*!< Identifiant d'une erreur matérielle de type MEM_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_BUSFAULT = 0x04,                            /*!< Identifiant d'une erreur matérielle de type BUS_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_USAGEFAULT = 0x05,                          /*!< Identifiant d'une erreur matérielle de type USAGE_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_HANDLEFAULT = 0x06,                         /*!< Identifiant d'une erreur logicielle de type HANDLE_FAULT (déclenché suite à la détection d'une instance invalide). */
   K_MK_SUPERVISOR_SVCFAULT = 0x07,                            /*!< Identifiant d'une erreur logicielle de type SVC_FAULT (déclenché suite à une erreur critique dans le noyau). */
   K_MK_SUPERVISOR_RIGHTFAULT = 0x08,                          /*!< Identifiant d'une erreur logicielle de type RIGHT_FAULT (déclenché suite un accès non autorisé sur une ressource protégée). */
   K_MK_SUPERVISOR_STACKFAULT = 0x09,                          /*!< Identifiant d'une erreur logicielle de type STACK_FAULT (déclenché suite à un débordement de la stack d'une tâche). */
   K_MK_SUPERVISOR_FPUFAULT = 0x0A,                            /*!< Identifiant d'une erreur matérielle de type FPU_FAULT (déclenché suite à un événement matériel). */
   K_MK_SUPERVISOR_TASKFAULT = 0x0B,                           /*!< Identifiant d'une erreur logicielle de type TASK_FAULT (déclenché suite à une valeur de retour incorecte durant l'exécution d'une tâche). */
   K_MK_SUPERVISOR_TIMEOUTFAULT = 0x0C                         /*!< Identifiant d'une erreur logicielle de type TIMEOUT_FAULT (déclenché suite à un timeout des tâches non privilégiées du moteur graphique). */
} T_mkSupervisorFault;


/**
 * @struct T_mkSupervisorDumpRegister
 * @brief Déclaration de la structure T_mkSupervisorDumpRegister.
 *
 */

typedef struct T_mkSupervisorDumpRegister T_mkSupervisorDumpRegister;
struct T_mkSupervisorDumpRegister
{
   uint32_t msp;                                               /*!< Ce membre contient la valeur du registre MSP.*/
   uint32_t psp;                                               /*!< Ce membre contient la valeur du registre PSP.*/
   uint32_t sp;                                                /*!< Ce membre contient la valeur du registre SP.*/
   uint32_t psr;                                               /*!< Ce membre contient la valeur du registre PSR.*/
   uint32_t primask;                                           /*!< Ce membre contient la valeur du registre PRIMASK.*/
   uint32_t faultmask;                                         /*!< Ce membre contient la valeur du registre FAULTMASK.*/
   uint32_t basepri;                                           /*!< Ce membre contient la valeur du registre BASEPRI.*/
   uint32_t control;                                           /*!< Ce membre contient la valeur du registre CONTROL.*/
   uint32_t reserved1;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t reserved2;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t actlr;                                             /*!< Ce membre contient la valeur du registre ACTLR.*/
   uint32_t cpuid;                                             /*!< Ce membre contient la valeur du registre CPUID.*/
   uint32_t icsr;                                              /*!< Ce membre contient la valeur du registre ICSR.*/
   uint32_t vtor;                                              /*!< Ce membre contient la valeur du registre VTOR.*/
   uint32_t aircr;                                             /*!< Ce membre contient la valeur du registre AIRCR.*/
   uint32_t scr;                                               /*!< Ce membre contient la valeur du registre SCR.*/
   uint32_t ccr;                                               /*!< Ce membre contient la valeur du registre CCR.*/
   uint32_t shpr1;                                             /*!< Ce membre contient la valeur du registre SHPR1.*/
   uint32_t shpr2;                                             /*!< Ce membre contient la valeur du registre SHPR2.*/
   uint32_t shpr3;                                             /*!< Ce membre contient la valeur du registre SHPR3.*/
   uint32_t shcrs;                                             /*!< Ce membre contient la valeur du registre SHCRS.*/
   uint32_t cfsr;                                              /*!< Ce membre contient la valeur du registre CFSR.*/
   uint32_t hfsr;                                              /*!< Ce membre contient la valeur du registre HFSR.*/
   uint32_t mmar;                                              /*!< Ce membre contient la valeur du registre MMAR.*/
   uint32_t bfar;                                              /*!< Ce membre contient la valeur du registre BFAR.*/
   uint32_t afsr;                                              /*!< Ce membre contient la valeur du registre AFSR.*/
   uint32_t reserved3;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t reserved4;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t reserved5;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t r4;                                                /*!< Ce membre contient la valeur du registre R4.*/
   uint32_t r5;                                                /*!< Ce membre contient la valeur du registre R5.*/
   uint32_t r6;                                                /*!< Ce membre contient la valeur du registre R6.*/
   uint32_t r7;                                                /*!< Ce membre contient la valeur du registre R7.*/
   uint32_t r8;                                                /*!< Ce membre contient la valeur du registre R8.*/
   uint32_t r9;                                                /*!< Ce membre contient la valeur du registre R9.*/
   uint32_t r10;                                               /*!< Ce membre contient la valeur du registre R10.*/
   uint32_t r11;                                               /*!< Ce membre contient la valeur du registre R11.*/
   uint32_t r12;                                               /*!< Ce membre contient la valeur du registre R12.*/
   uint32_t reserved6;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t reserved7;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t reserved8;                                         /*!< Ce membre est reservé pour un usage ultérieur. */
   uint32_t fpscr;                                             /*!< Ce membre contient la valeur du registre FPSCR.*/
   real32_t s16;                                               /*!< Ce membre contient la valeur du registre S16.*/
   real32_t s17;                                               /*!< Ce membre contient la valeur du registre S17.*/
   real32_t s18;                                               /*!< Ce membre contient la valeur du registre S18.*/
   real32_t s19;                                               /*!< Ce membre contient la valeur du registre S19.*/
   real32_t s20;                                               /*!< Ce membre contient la valeur du registre S20.*/
   real32_t s21;                                               /*!< Ce membre contient la valeur du registre S21.*/
   real32_t s22;                                               /*!< Ce membre contient la valeur du registre S22.*/
   real32_t s23;                                               /*!< Ce membre contient la valeur du registre S23.*/
   real32_t s24;                                               /*!< Ce membre contient la valeur du registre S24.*/
   real32_t s25;                                               /*!< Ce membre contient la valeur du registre S25.*/
   real32_t s26;                                               /*!< Ce membre contient la valeur du registre S26.*/
   real32_t s27;                                               /*!< Ce membre contient la valeur du registre S27.*/
   real32_t s28;                                               /*!< Ce membre contient la valeur du registre S28.*/
   real32_t s29;                                               /*!< Ce membre contient la valeur du registre S29.*/
   real32_t s30;                                               /*!< Ce membre contient la valeur du registre S30.*/
   real32_t s31;                                               /*!< Ce membre contient la valeur du registre S31.*/
};

/**
 * @struct T_mkSupervisorSVCFault
 * @brief Déclaration de la structure T_mkSupervisorSVCFault.
 *
 */

typedef struct T_mkSupervisorSVCFault T_mkSupervisorSVCFault;
struct T_mkSupervisorSVCFault
{
   T_mkSVCError fault;                                         /*!< Ce membre contient l'identifiant d'une erreur de type SVC (\ref K_MK_SUPERVISOR_SVCFAULT).*/
   T_mkSVCObject object;                                       /*!< Ce membre contient le contenu de la requête qui a provoqué l'erreur SVC.*/
   uint32_t isr;                                               /*!< Ce membre contient un registre indiquant si la requête SVC a été déclenchée par un vecteur d'interruption (1) ou non (0).*/
};

/**
 * @struct T_mkSupervisorMessage
 * @brief Déclaration de la structure T_mkSupervisorMessage.
 *
 */

typedef struct T_mkSupervisorMessage T_mkSupervisorMessage;
struct T_mkSupervisorMessage
{
   T_mkSupervisorFault fault;                                  /*!< Ce membre contient l'identifiant principal d'une erreur (\ref T_mkSupervisorFault). */
   T_mkTask* task;                                             /*!< Ce membre contient l'enregistrement de l'adresse de la tâche courante au moment où l'erreur a été détectée. */
   T_mkScheduler scheduler;                                    /*!< Ce membre contient l'enregistrement des registres de l'ordonnanceur au moment où l'erreur a été détectée. */
   T_mkSupervisorDumpRegister dump;                            /*!< Ce membre contient l'enregistrement des registres principaux du CPU au moment où l'erreur a été détectée. */
   T_mkSupervisorSVCFault svc;                                 /*!< Ce membre contient les caractéristiques d'une erreur SVC. Il est dédié aux erreurs de type \ref K_MK_SUPERVISOR_SVCFAULT. */
   T_mkCode returnValue;                                       /*!< Ce membre contient la valeur d'un code de retour. Il est dédié aux erreurs de type \ref K_MK_SUPERVISOR_TASKFAULT. */
};

/**
 *
 */

#endif


