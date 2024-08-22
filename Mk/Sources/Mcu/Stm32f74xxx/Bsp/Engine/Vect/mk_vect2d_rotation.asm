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
* @file mk_vect2d_rotation.asm
* @brief Définition de la fonction _mk_vect2d_rotation.
* @date 1 mai 2019
*
*/

.cpu cortex-m7
.fpu fpv5-sp-d16
.syntax unified

/**
 * @internal
 * @brief
 * @endinternal
 */

.global _math_fcos
.global g_mkHalfPi

/**
 * @internal
 * @brief
 * @endinternal
 */

.thumb
.thumb_func

.align 4
.global _mk_vect2d_rotation
_mk_vect2d_rotation:

    /* Enregistrement des registres dans la stack */
    VPUSH { S4 }
    PUSH  { R0, R1, LR }
    VPUSH { S0 }

    /* Détermination de la valeur de cos ( Teta ) */
    BL _math_fcos
    VMOV S4, S0 /* S4 = cos */
    VPOP { S0 }
    /* Détermination de la valeur de sin ( Teta ) */
    LDR R2, =g_mkHalfPi
    VLDR.F32 S1, [R2]
    VSUB.F32 S0, S0, S1
    BL _math_fcos /* S0 = sin */

    /* Restitutation des registres */
    POP { R0, R1, LR }
    VLDR S1, [R0]
    VLDR S3, [R0, #0x04]

    /* x' = x.cos ( Teta ) - y.sin ( Teta ) */
    VMUL.F32 S2, S4, S1
    VMLS.F32 S2, S0, S3
    VSTR S2, [R1]

    /* y' = x.sin ( Teta ) + y.cos ( Teta ) */
    VMUL.F32 S2, S0, S1
    VMLA.F32 S2, S4, S3
    VSTR S2, [R1, #0x04]
    VPOP { S4 }

    /* Retour */
    BX LR







