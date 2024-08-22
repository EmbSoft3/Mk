/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_chromart_drawCharacterFast24BPP.asm
* @brief Définition de la fonction mk_chromart_drawCharacterFast24BPP.
* @date 22 juil. 2024
*
*/


.cpu cortex-m7
.syntax unified

/**
 * @internal
 * @brief
 * @endinternal
 */

.thumb
.thumb_func

.align 4
.global _mk_chromart_drawCharacterFast24BPP
_mk_chromart_drawCharacterFast24BPP:

    /* R0 -> destinationAddr (graphical buffer) */
    /* R1 -> char baseAddr (bitmap) */
    /* R2 -> char argb */
    /* R3 -> char width */
    /* R4 -> screen width */

    /* R5 -> char height */
    /* R6 -> registre de travail - bitmap line current value */
    /* R7 -> registre de travail - clz value */
    /* R8 -> registre de travail */
    /* R9 -> incrément du bitmap entre les lignes */
    /* R10 -> bytesPerPixel */
    /* R11 -> memo */

    PUSH { R4-R11 }

    /* Enregistrement du nombre d'octets par pixel */
    MOV R10, #0x3
    /* Enregistrement du MSB de la valeur du pixel */
    MOV R11, R2, LSR #0x10

    /* Récupération du paramètre présent dans la stack (screen width) */
    LDR R4, [ sp, #36 ]
    MUL R4, R4, R10 /* Multiplication par le nombre d'octets par pixel */

    /* Création de la valeur de l'incrément */
    /* R9 = 1 + ( ( width - 1 ) / 8 ) */
    MOV R5, 0x01
    SUB R6, R3, #0x01
    ADD R9, R5, R6, LSR #0x03

    /* Pour chaque ligne de la police de caractère */
    LDR R5, [ sp, #32 ]
    ADD R5, #0x01
    1:
    SUBS R5, R5, #0x01
    BEQ 4f

    /* Attention à l'alignement sur 8 bits des tables de FONT */
    /* Si width < 8 pxl : dest = xx000000 */
    /* Sinon si width < 16 pxl : dest = xxyy0000 */
    /* Sinon si width < 24 pxl : dest= xxyyww00 */
    /* Sinon dest = xxyywwzz */
    MOV R6, #0x00
    MOV R7, #0x00

    /* Caractère sur 8 bits */
    LDRB R6, [ R1 ]
    LSL R6, #0x18

    /* Test de la taille du caractère */
    CMP R3, #0x08
    BLE 2f

    /* Caractère sur 16 bits */
    LDRB R7, [ R1, #0x01 ]
    LSL R7, #0x10
    /* Création de la destination (stockée dans R5) */
    ORR R6, R7, R6

    /* Test de la taille du caractère */
    CMP R3, #0x10
    BLE 2f

    /* Caractère sur 24 bits */
    LDRB R7, [ R1, #0x02 ]
    LSL R7, #0x8
    /* Création de la destination (stockée dans R5) */
    ORR R6, R7, R6

    /* Test de la taille du caractère */
    CMP R3, #0x18
    BLE 2f

    /* Caractère sur 32 bits */
    LDRB R7, [ R1, #0x03 ]
    /* Création de la destination (stockée dans R5) */
    ORR R6, R7, R6

    2:
    /* Récupération de la position du premier 1 dans le bitmap (résultat entre 1 et 32) */
    CLZ R7, R6
    SUBS R8, R7, #0x20
    BEQ 3f

    /* Ecriture du pixel (R4 - offset de celui-ci)  */
    SUB R8, R7, #0x00 /* Offset entre 0 et 16 */
    MUL R8, R8, R10
    ADD R8, R0, R8
    STRB R2, [ R8 ]
    STRBT R2, [ R8, #0x01 ]
    STRB R11, [ R8, #0x02 ]

    /* Détermination de la valeur du décalage */
    MOV R8, #0x1F
    SUB R7, R8, R7

    /* Réinitialisation du bit */
    MOV R8, #0x01
    LSL R7, R8, R7
    BICS R6, R6, R7

    /* Boucle */
    BNE 2b

    3:
    /* BaseAddr = BaseAddr + 1 + ( ( width - 1 ) / 8  ) */
    ADD R1, R1, R9
    /* DestinationAddr = DestinationAddr + screen_width */
    ADD R0, R0, R4

    /* Branchement vers la prochaine ligne */
    B 1b

    4:
    /* Restitution des registres */
    POP { R4-R11 }

    /* Retour */
    BX LR


