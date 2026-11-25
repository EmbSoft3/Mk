/**
*
* @copyright Copyright (C) 2026 RENARD Mathieu. All rights reserved.
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
* @file linker.ld
* @brief Fichier d'édition de lien des MCU STM32F745xx et STM32F746xx.
* @date 17/09/2026
*
*/

INCLUDE linker.ld

/**
 *
 */

/* Définition de l'adresse de base de la zone contenant les symboles */
K_MK_INTERNAL_SYMBOLS_BASE_ADDR = 0x002C0000 ;

/* Définition de l'adresse de base des banques de mémoire externes (BANK1) */
K_MK_BANK_SIZE = 0x10000000;
K_MK_BANK1_START_ADDR = 0x60000000 ;
K_MK_BANK1_END_ADDR = K_MK_BANK1_START_ADDR + K_MK_BANK_SIZE - 1 ;
K_MK_BANK5_START_ADDR = 0xC0000000 ;
K_MK_BANK5_END_ADDR = K_MK_BANK5_START_ADDR + K_MK_BANK_SIZE - 1 ;

/**
 *
 */

/* Définition des sections */
SECTIONS
{
   /* Mapping de la section "mk_privileged_font_memory" */
   .mk_privileged_font_memory : ALIGN ( 4 )
   {
      *( .mk_privileged_font_memory )
   } > K_FLASH_ITCM
}




