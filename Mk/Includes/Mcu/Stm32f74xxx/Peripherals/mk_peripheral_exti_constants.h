/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_exti_constants.h
* @brief Déclaration des constantes dédiées au périphérique EXTI.
* @date 19 déc. 2020
*
*/

#ifndef MK_PERIPHERAL_EXTI_CONSTANTS_H
#define MK_PERIPHERAL_EXTI_CONSTANTS_H

/**
 * @def K_EXTI_IMR
 * @brief Adresse de base du périphérique EXTI_IMR.
 */

#define K_EXTI_IMR ( addr_t ) 0x40013C00

/**
 * @def K_EXTI_EMR
 * @brief Adresse de base du périphérique EXTI_EMR.
 */

#define K_EXTI_EMR ( addr_t ) 0x40013C04

/**
 * @def K_EXTI_RTSR
 * @brief Adresse de base du périphérique EXTI_RTSR.
 */

#define K_EXTI_RTSR ( addr_t ) 0x40013C08

/**
 * @def K_EXTI_FTSR
 * @brief Adresse de base du périphérique EXTI_FTSR.
 */

#define K_EXTI_FTSR ( addr_t ) 0x40013C0C

/**
 * @def K_EXTI_SWIER
 * @brief Adresse de base du périphérique EXTI_SWIER.
 */

#define K_EXTI_SWIER ( addr_t ) 0x40013C10

/**
 * @def K_EXTI_PR
 * @brief Adresse de base du périphérique EXTI_PR.
 */

#define K_EXTI_PR ( addr_t ) 0x40013C14

/**
 *
 */

/**
 * @def K_EXTI_LINE_NUMBER
 * @brief Définition du nombre de ligne d'interruption.
 */

#define K_EXTI_LINE_NUMBER 24

/**
 * @def K_EXTI_LINE0
 * @brief Définition de l'identifiant de la ligne d'interruption 0.
 */

#define K_EXTI_LINE0 0x00000001

/**
 * @def K_EXTI_LINE1
 * @brief Définition de l'identifiant de la ligne d'interruption 1.
 */

#define K_EXTI_LINE1 0x00000002

/**
 * @def K_EXTI_LINE2
 * @brief Définition de l'identifiant de la ligne d'interruption 2.
 */

#define K_EXTI_LINE2 0x00000004

/**
 * @def K_EXTI_LINE3
 * @brief Définition de l'identifiant de la ligne d'interruption 3.
 */

#define K_EXTI_LINE3 0x00000008

/**
 * @def K_EXTI_LINE4
 * @brief Définition de l'identifiant de la ligne d'interruption 4.
 */

#define K_EXTI_LINE4 0x00000010

/**
 * @def K_EXTI_LINE5
 * @brief Définition de l'identifiant de la ligne d'interruption 5.
 */

#define K_EXTI_LINE5 0x00000020

/**
 * @def K_EXTI_LINE6
 * @brief Définition de l'identifiant de la ligne d'interruption 6.
 */

#define K_EXTI_LINE6 0x00000040

/**
 * @def K_EXTI_LINE7
 * @brief Définition de l'identifiant de la ligne d'interruption 7.
 */

#define K_EXTI_LINE7 0x00000080

/**
 * @def K_EXTI_LINE8
 * @brief Définition de l'identifiant de la ligne d'interruption 8.
 */

#define K_EXTI_LINE8 0x00000100

/**
 * @def K_EXTI_LINE9
 * @brief Définition de l'identifiant de la ligne d'interruption 9.
 */

#define K_EXTI_LINE9 0x00000200

/**
 * @def K_EXTI_LINE10
 * @brief Définition de l'identifiant de la ligne d'interruption 10.
 */

#define K_EXTI_LINE10 0x00000400

/**
 * @def K_EXTI_LINE11
 * @brief Définition de l'identifiant de la ligne d'interruption 11.
 */

#define K_EXTI_LINE11 0x00000800

/**
 * @def K_EXTI_LINE12
 * @brief Définition de l'identifiant de la ligne d'interruption 12.
 */

#define K_EXTI_LINE12 0x00001000

/**
 * @def K_EXTI_LINE13
 * @brief Définition de l'identifiant de la ligne d'interruption 13.
 */

#define K_EXTI_LINE13 0x00002000

/**
 * @def K_EXTI_LINE14
 * @brief Définition de l'identifiant de la ligne d'interruption 14.
 */

#define K_EXTI_LINE14 0x00004000

/**
 * @def K_EXTI_LINE15
 * @brief Définition de l'identifiant de la ligne d'interruption 15.
 */

#define K_EXTI_LINE15 0x00008000

/**
 * @def K_EXTI_LINE16
 * @brief Définition de l'identifiant de la ligne d'interruption 16.
 */

#define K_EXTI_LINE16 0x00010000

/**
 * @def K_EXTI_LINE17
 * @brief Définition de l'identifiant de la ligne d'interruption 17.
 */

#define K_EXTI_LINE17 0x00020000

/**
 * @def K_EXTI_LINE18
 * @brief Définition de l'identifiant de la ligne d'interruption 18.
 */

#define K_EXTI_LINE18 0x00040000

/**
 * @def K_EXTI_LINE19
 * @brief Définition de l'identifiant de la ligne d'interruption 19.
 */

#define K_EXTI_LINE19 0x00080000

/**
 * @def K_EXTI_LINE20
 * @brief Définition de l'identifiant de la ligne d'interruption 20.
 */

#define K_EXTI_LINE20 0x00100000

/**
 * @def K_EXTI_LINE21
 * @brief Définition de l'identifiant de la ligne d'interruption 21.
 */

#define K_EXTI_LINE21 0x00200000

/**
 * @def K_EXTI_LINE22
 * @brief Définition de l'identifiant de la ligne d'interruption 22.
 */

#define K_EXTI_LINE22 0x00400000

/**
 * @def K_EXTI_LINE23
 * @brief Définition de l'identifiant de la ligne d'interruption 23.
 */

#define K_EXTI_LINE23 0x00800000

/**
 * @def K_EXTI_LINE23
 * @brief Définition de l'identifiant de toutes les lignes d'interruption.
 */

#define K_EXTI_ALL_LINE 0x00FFFFFF

/**
 *
 */

#endif

