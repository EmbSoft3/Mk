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
* @file mk_page_bsp_constants.h
* @brief Déclaration des constantes dédiées aux boards EVAL2 & DISCO_REV_C.
* @date 18 mars 2026
*
*/

#ifndef MK_PAGE_BSP_CONSTANTS_H
#define MK_PAGE_BSP_CONSTANTS_H

/**
 *
 */

/* Si compilation pour la carte EVAL2 */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @def K_MK_BSP_PAGE_SMALL_START_ADDR
 * @brief Définition de l'adresse de début de la mémoire stockant les petites pages mémoire (SRAM, SDRAM, ...).
 */

#define K_MK_BSP_PAGE_SMALL_START_ADDR 0x68000000

/**
 * @def K_MK_BSP_PAGE_SMALL_SIZE
 * @brief Définition de la taille de la mémoire permettant d'allouer les petites pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_SMALL_SIZE 0x200000

/**
 * @def K_MK_BSP_PAGE_SMALL_BLOCK_SIZE
 * @brief Définition de la taille des petites pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_SMALL_BLOCK_SIZE 0x10000

/**
 * @def K_MK_BSP_PAGE_LARGE_START_ADDR
 * @brief Définition de l'adresse de début de la mémoire stockant les grandes page mémoire (SDRAM).
 */

#define K_MK_BSP_PAGE_LARGE_START_ADDR ( K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR + ( 2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) + K_MK_DISPLAY_FRAME_BUFFER_SIZE )

/**
 * @def K_MK_BSP_PAGE_LARGE_SIZE
 * @brief Définition de la taille de la mémoire permettant d'allouer les grandes pages mémoire [en octets].
 *        2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE => buffers graphiques.
 *        1 * K_MK_DISPLAY_FRAME_BUFFER_SIZE => mémoire dédiées à l'allocation des applications.
 */

#define K_MK_BSP_PAGE_LARGE_SIZE ( ( ( uint32_t ) 0x800000 - ( ( 2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) + K_MK_DISPLAY_FRAME_BUFFER_SIZE ) ) * 4 )

/**
 * @def K_MK_BSP_PAGE_LARGE_BLOCK_SIZE
 * @brief Définition de la taille des grandes pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_LARGE_BLOCK_SIZE ( K_MK_DISPLAY_FRAME_BUFFER_SIZE * 4 )

/**
 *
 */

/* Sinon si compilation pour la carte DISCO_REV_C */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @def K_MK_BSP_PAGE_SMALL_START_ADDR
 * @brief Définition de l'adresse de début de la mémoire stockant les petites pages mémoire (SRAM, SDRAM, ...).
 */

#define K_MK_BSP_PAGE_SMALL_START_ADDR ( K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR + ( 2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) + K_MK_DISPLAY_FRAME_BUFFER_SIZE )

/**
 * @def K_MK_BSP_PAGE_SMALL_SIZE
 * @brief Définition de la taille de la mémoire permettant d'allouer les petites pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_SMALL_SIZE ( K_MK_DISPLAY_FRAME_BUFFER_SIZE * 4 )

/**
 * @def K_MK_BSP_PAGE_SMALL_BLOCK_SIZE
 * @brief Définition de la taille des petites pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_SMALL_BLOCK_SIZE 0x10000

/**
 * @def K_MK_BSP_PAGE_LARGE_START_ADDR
 * @brief Définition de l'adresse de début de la mémoire stockant les grandes page mémoire (SDRAM).
 */

#define K_MK_BSP_PAGE_LARGE_START_ADDR ( K_MK_BSP_PAGE_SMALL_START_ADDR + K_MK_DISPLAY_FRAME_BUFFER_SIZE )

/**
 * @def K_MK_BSP_PAGE_LARGE_SIZE
 * @brief Définition de la taille de la mémoire permettant d'allouer les grandes pages mémoire [en octets].
 *        2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE => buffers graphiques.
 *        1 * K_MK_DISPLAY_FRAME_BUFFER_SIZE => mémoire dédiées à l'allocation des applications.
 */

#define K_MK_BSP_PAGE_LARGE_SIZE ( ( ( uint32_t ) 0x200000 - ( ( 2 * K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) + ( 2 * K_MK_DISPLAY_FRAME_BUFFER_SIZE ) ) ) * 4 )

/**
 * @def K_MK_BSP_PAGE_LARGE_BLOCK_SIZE
 * @brief Définition de la taille des grandes pages mémoire [en octets].
 */

#define K_MK_BSP_PAGE_LARGE_BLOCK_SIZE ( K_MK_DISPLAY_FRAME_BUFFER_SIZE * 4 )

/**
 *
 */

/* Sinon si compilation d'une application externe */
#elif defined ( MK_EXTERNAL_APPS )

/**
 *
 */

/* Sinon erreur de compilation */
#else
#error "No board defined. Use BOARD=EVAL2 or BOARD=DISCO_REV_C in the Makefile"
#endif

#endif
