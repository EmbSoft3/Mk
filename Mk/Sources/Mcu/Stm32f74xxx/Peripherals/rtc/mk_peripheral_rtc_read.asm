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
* @file mk_peripheral_rtc_read.asm
* @brief Définition de la fonction _rtc_read.
* @date 8 sept. 2021
*
*/

.cpu cortex-m7
.syntax unified

/**
 * @internal
 * @brief
 * @endinternal
 */

.equ K_RTC_TR, 0x40002800

/**
 * @internal
 * @brief
 * @endinternal
 */

.thumb
.thumb_func

.align 4
.global _rtc_read
_rtc_read:

    /* Première lecture */
    LDR R1,=#K_RTC_TR
    LDR R2, [R1, #0x28] /* K_RTC_SSR*/
    LDR R3, [R1, #0x00] /* K_RTC_TR */
    LDR R1, [R1, #0x04] /* K_RTC_DR */
    STR R1, [R0, #0x00]
    STR R3, [R0, #0x04]
    STR R2, [R0, #0x08]

    /* Deuxième lecture */
    LDR R1,=#K_RTC_TR
    LDR R2, [R1, #0x28] /* K_RTC_SSR*/
    LDR R3, [R1, #0x00] /* K_RTC_TR */
    LDR R1, [R1, #0x04] /* K_RTC_DR */
    STR R1, [R0, #0x0C]
    STR R3, [R0, #0x10]
    STR R2, [R0, #0x14]

    BX LR



