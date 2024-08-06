/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_color_hsv2rgbLite.asm
* @brief Définition de la fonction mk_color_hsv2rgbLite.
* @date 22 avr. 2019
*
*/

.cpu cortex-m7
.syntax unified

/**
 * @internal
 * @brief http://www.vagrearg.org/content/hsvrgb
 * @endinternal
 */

.thumb
.thumb_func

/* void _mk_color_hsv2rgbLite ( T_mkAHSVLite* p_ahsv, T_mkARGB* p_argb ); */

.align 4
.global _mk_color_hsv2rgbLite
_mk_color_hsv2rgbLite:

    /* Copie de la composante alpha */
    LDRB R2, [R0, #0x4]
    STRB R2, [R1, #0x3]

    /* Si la composante saturation est nulle -> R2 = S */
    LDRB R2, [R0, #0x2]
    SUBS R2, R2, #0x0
    BNE 1f

    /* Les composantes RGB sont égale à la */
    /* composante V */
    LDRB R2, [R0, #0x3]
    STRB R2, [R1, #0x0]
    STRB R2, [R1, #0x1]
    STRB R2, [R1, #0x2]

    /* Retour */
    BX LR

    1:
    /* Enregistrement des registres R4 à R8 dans la stack. */
    PUSH { R4-R8 }

    /* R3 = V, R4 = LOW_BYTE ( H ) */
    LDRB R3, [R0, #0x3]
    LDRH R4, [R0, #0x0]
    AND R4, R4, #0xFF

    /* Détermination de la valeur des variables intermédiaires */
    /* R2 = S, R3 = V, R4 = LOW_BYTE ( H ) */

    /* Level_bottom (R5) */
    MOV R5, #0xFF
    SUB R5, R5, R2
    MUL R5, R5, R3
    ADD R5, R5, #0x1
    ADD R5, R5, R5, LSR #0x8
    LSR R5, R5, #0x8

    /* Slope_down (R6) */
    MUL R6, R2, R4
    MOV R8, #0xFF00
    SUB R6, R8, R6
    MUL R6, R3, R6
    ADD R6, R6, R6, LSR #0x8
    ADD R6, R6, R3
    LSR R6, R6, #0x10

    /* Slope_up (R7) */
    MOV R7, #0x100
    SUB R7, R7, R4
    MUL R7, R7, R2
    SUB R7, R8, R7
    MUL R7, R7, R2
    ADD R7, R7, R7, LSR #0x8
    ADD R7, R7, R3
    LSR R7, R7, #0x10

    /* Mapping des variables intermédiaires en fonction du sextant */
    /* R3 = Value, R5 = bottom_level, R6 = slope_down, R7 = slope_up */
    LDRH R4, [R0, #0x0]
    LSR R4, R4, #0x8

    /* Sextant 0 */
    SUBS R0, R4, #0x00
    BNE 1f
    STRB R3, [R1, #0x2] /* RED */
    STRB R7, [R1, #0x1] /* GREEN */
    STRB R5, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant 1 */
    SUBS R0, R4, #0x01
    BNE 1f
    STRB R6, [R1, #0x2] /* RED */
    STRB R3, [R1, #0x1] /* GREEN */
    STRB R5, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant 2 */
    SUBS R0, R4, #0x02
    BNE 1f
    STRB R5, [R1, #0x2] /* RED */
    STRB R3, [R1, #0x1] /* GREEN */
    STRB R7, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant 3 */
    SUBS R0, R4, #0x03
    BNE 1f
    STRB R5, [R1, #0x2] /* RED */
    STRB R6, [R1, #0x1] /* GREEN */
    STRB R3, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant 4 */
    SUBS R0, R4, #0x04
    BNE 1f
    STRB R7, [R1, #0x2] /* RED */
    STRB R5, [R1, #0x1] /* GREEN */
    STRB R3, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant 5 */
    SUBS R0, R4, #0x05
    BNE 1f
    STRB R3, [R1, #0x2] /* RED */
    STRB R5, [R1, #0x1] /* GREEN */
    STRB R6, [R1, #0x0] /* BLUE */
    B 2f

    1:
    /* Sextant supérieur à 5 */
    STRB R3, [R1, #0x2] /* RED */
    STRB R5, [R1, #0x1] /* GREEN */
    STRB R6, [R1, #0x0] /* BLUE */

    2:
    /* Restitution des registres R4 à R8 dans la stack. */
    POP { R4-R8 }

    /* Actualisation du résultat */
    LDR R0, [R1]

    /* Retour */
    BX LR



