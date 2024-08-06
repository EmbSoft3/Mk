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
* @file mk_supervisor_dump.asm
* @brief Définition de la fonction mk_supervisor_dump.
* @date 27 mars 2023
*
*/

.cpu cortex-m7
.syntax unified

/**
 * @internal
 * @brief
 * @endinternal
 */

.equ K_MK_REG_ACTLR, 0xE000E008
.equ K_MK_REG_CPUID, 0xE000ED00
.equ K_MK_REG_ICSR,  0xE000ED04
.equ K_MK_REG_VTOR,  0xE000ED08
.equ K_MK_REG_AIRCR, 0xE000ED0C
.equ K_MK_REG_SCR,   0xE000ED10
.equ K_MK_REG_CCR,   0xE000ED14
.equ K_MK_REG_SHPR1, 0xE000ED18
.equ K_MK_REG_SHPR2, 0xE000ED1C
.equ K_MK_REG_SHPR3, 0xE000ED20
.equ K_MK_REG_SHCRS, 0xE000ED24
.equ K_MK_REG_CFSR,  0xE000ED28
.equ K_MK_REG_HFSR,  0xE000ED2C
.equ K_MK_REG_MMAR,  0xE000ED34
.equ K_MK_REG_BFAR,  0xE000ED38
.equ K_MK_REG_AFSR,  0xE000ED3C

/**
 * @internal
 * @brief
 * @endinternal
 */

.thumb
.thumb_func

.align 4
.global _mk_supervisor_dump
_mk_supervisor_dump:

    /* Récupération de la valeur du registre MSP */
    MRS R1, MSP
    STR R1, [ R0 ]

    /* Récupération de la valeur du registre PSP */
    MRS R1, PSP
    STR R1, [ R0, #0x04 ]

    /* Récupération de la valeur du registre SP */
    STR SP, [ R0, #0x08 ]

    /* Récupération de la valeur du registre PSR */
    MRS R1, PSR
    STR R1, [ R0, #0x0C ]

    /* Récupération de la valeur du registre PRIMASK */
    MRS R1, PRIMASK
    STR R1, [ R0, #0x10 ]

    /* Récupération de la valeur du registre FAULTMASK */
    MRS R1, FAULTMASK
    STR R1, [ R0, #0x14 ]

    /* Récupération de la valeur du registre BASEPRI */
    MRS R1, BASEPRI
    STR R1, [ R0, #0x18 ]

    /* Récupération de la valeur du registre CONTROL */
    MRS R2, CONTROL
    STR R2, [ R0, #0x1C ]

    /* Reserved1 : 0x20 */
    /* Reserved2 : 0x24 */

    /* Récupération de la valeur du registre ACTLR */
    LDR R1, =K_MK_REG_ACTLR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x28 ]

    /* Récupération de la valeur du registre CPUID */
    LDR R1, =K_MK_REG_CPUID
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x2C ]

    /* Récupération de la valeur du registre ICSR */
    LDR R1, =K_MK_REG_ICSR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x30 ]

    /* Récupération de la valeur du registre VTOR */
    LDR R1, =K_MK_REG_VTOR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x34 ]

    /* Récupération de la valeur du registre AIRCR */
    LDR R1, =K_MK_REG_AIRCR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x38 ]

    /* Récupération de la valeur du registre SCR */
    LDR R1, =K_MK_REG_SCR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x3C ]

    /* Récupération de la valeur du registre CCR */
    LDR R1, =K_MK_REG_CCR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x40 ]

    /* Récupération de la valeur du registre SHPR1 */
    LDR R1, =K_MK_REG_SHPR1
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x44 ]

    /* Récupération de la valeur du registre SHPR2 */
    LDR R1, =K_MK_REG_SHPR2
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x48 ]

    /* Récupération de la valeur du registre SHPR3 */
    LDR R1, =K_MK_REG_SHPR3
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x4C ]

    /* Récupération de la valeur du registre SHCRS */
    LDR R1, =K_MK_REG_SHCRS
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x50 ]

    /* Récupération de la valeur du registre CFSR */
    LDR R1, =K_MK_REG_CFSR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x54 ]

    /* Récupération de la valeur du registre HFSR */
    LDR R1, =K_MK_REG_HFSR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x58 ]

    /* Récupération de la valeur du registre MMAR */
    LDR R1, =K_MK_REG_MMAR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x5C ]

    /* Récupération de la valeur du registre BFAR */
    LDR R1, =K_MK_REG_BFAR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x60 ]

    /* Récupération de la valeur du registre AFSR */
    LDR R1, =K_MK_REG_AFSR
    LDR R1, [ R1 ]
    STR R1, [ R0, #0x64 ]

    /* Reserved3 : 0x68 */
    /* Reserved4 : 0x6C */
    /* Reserved5 : 0x70 */

    /* Récupération de la valeur du registre R4 */
    STR R4, [ R0, #0x74 ]

    /* Récupération de la valeur du registre R5 */
    STR R5, [ R0, #0x78 ]

    /* Récupération de la valeur du registre R6 */
    STR R6, [ R0, #0x7C ]

    /* Récupération de la valeur du registre R7 */
    STR R7, [ R0, #0x80 ]

     /* Récupération de la valeur du registre R8 */
    STR R8, [ R0, #0x84 ]

    /* Récupération de la valeur du registre R9 */
    STR R9, [ R0, #0x88 ]

    /* Récupération de la valeur du registre R10 */
    STR R10, [ R0, #0x8C ]

    /* Récupération de la valeur du registre R11 */
    STR R11, [ R0, #0x90 ]

    /* Récupération de la valeur du registre R12 */
    STR R12, [ R0, #0x94 ]

    /* Reserved6 : 0x98 */
    /* Reserved7 : 0x9C */
    /* Reserved8 : 0xA0 */

    /* Floating Register */

    /* Activation de la virgule flottante */
    MOV R1, #0x04
    MSR CONTROL, R1

    /* Récupération de la valeur du registre FPSCR */
    VMRS R1, FPSCR
    STR R1, [ R0, #0xA4 ]

    /* Récupération de la valeur du registre S16 */
    VSTR S16, [ R0, #0xA8 ]

    /* Récupération de la valeur du registre S17 */
    VSTR S17, [ R0, #0xAC ]

    /* Récupération de la valeur du registre S18 */
    VSTR S18, [ R0, #0xB0 ]

    /* Récupération de la valeur du registre S19 */
    VSTR S19, [ R0, #0xB4 ]

    /* Récupération de la valeur du registre S20 */
    VSTR S20, [ R0, #0xB8 ]

    /* Récupération de la valeur du registre S21 */
    VSTR S21, [ R0, #0xBC ]

    /* Récupération de la valeur du registre S22 */
    VSTR S22, [ R0, #0xC0 ]

    /* Récupération de la valeur du registre S23 */
    VSTR S23, [ R0, #0xC4 ]

    /* Récupération de la valeur du registre S24 */
    VSTR S24, [ R0, #0xC8 ]

    /* Récupération de la valeur du registre S25 */
    VSTR S25, [ R0, #0xCC ]

    /* Récupération de la valeur du registre S26 */
    VSTR S26, [ R0, #0xD0 ]

    /* Récupération de la valeur du registre S27 */
    VSTR S27, [ R0, #0xD4 ]

    /* Récupération de la valeur du registre S28 */
    VSTR S28, [ R0, #0xD8 ]

    /* Récupération de la valeur du registre S29 */
    VSTR S29, [ R0, #0xDC ]

    /* Récupération de la valeur du registre S30 */
    VSTR S30, [ R0, #0xE0 ]

    /* Récupération de la valeur du registre S31 */
    VSTR S31, [ R0, #0xE4 ]

    /* Restauration du registre de contrôle */
    MSR CONTROL, R2

    /* Retour */
    BX LR

