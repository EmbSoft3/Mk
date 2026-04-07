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
* @file mk_supervisor_graphics_constants.h
* @brief Déclaration des constantes graphiques dédiées au superviseur.
* @date 23 mars 2026
*
*/

#ifndef MK_SUPERVISOR_GRAPHICS_CONSTANTS_H
#define MK_SUPERVISOR_GRAPHICS_CONSTANTS_H

/* Si compilation pour la carte EVAL2 (résolution 640x480) */
#if defined ( MK_BOARD_EVAL2 )

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_X
 * @brief Définition du message d'introduction affiché dans la console 
          du superviseur au démarrage.
 */

#define K_MK_SUPERVISOR_PROMPT "\nMkSoft for STM32746g-Eval2 board.\n"

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_X
 * @brief Définition de la position X de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_Y
 * @brief Définition de la position Y de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_Y 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH
 * @brief Définition de la largeur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH 629

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT
 * @brief Définition de la hauteur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT 436

/**
 * @def K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE
 * @brief Définition de la taille du cache de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE ( 4 * K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH * K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT )

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_X
 * @brief Définition de la position X du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_Y
 * @brief Définition de la position Y du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_Y 447

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH
 * @brief Définition de la largeur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH 629

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT
 * @brief Définition de la hauteur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT 30

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_X
 * @brief Définition de la position X de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_X 610

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_Y
 * @brief Définition de la position Y de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_Y 10

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_WIDTH
 * @brief Définition de la largeur de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_WIDTH 30

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_HEIGHT
 * @brief Définition de la hauteur de la figure affichant le framerate.
*/

#define K_MK_SUPERVISOR_FRAMERATE_HEIGHT 35

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_X
 * @brief Définition de la position X de la figure affichant la charge CPU.
 */

#define K_MK_SUPERVISOR_CPU_LOAD_X 610

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_Y
 * @brief Définition de la position Y de la figure affichant la charge CPU.
 */

#define K_MK_SUPERVISOR_CPU_LOAD_Y 50

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_WIDTH
 * @brief Définition de la largeur de la figure affichant la charge CPU.
*/

#define K_MK_SUPERVISOR_CPU_LOAD_WIDTH 30

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_HEIGHT
 * @brief Définition de la hauteur de la figure affichant la charge CPU.
*/

#define K_MK_SUPERVISOR_CPU_LOAD_HEIGHT 35

/**
 *
 */

/* Sinon si compilation pour la carte DISCO_REV_C (résolution 480x272) */
#elif defined ( MK_BOARD_DISCO_REV_C )

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_X
 * @brief Définition du message d'introduction affiché dans la console
          du superviseur au démarrage.
 */

#define K_MK_SUPERVISOR_PROMPT "\nMkSoft for STM32746g-DISCO (REV.C) board.\n"

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_X
 * @brief Définition de la position X de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_Y
 * @brief Définition de la position Y de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_Y 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH
 * @brief Définition de la largeur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH 469

/**
 * @def K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT
 * @brief Définition de la hauteur de la fenêtre de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT 228

/**
 * @def K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE
 * @brief Définition de la taille du cache de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE ( 4 * K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH * K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT )

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_X
 * @brief Définition de la position X du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_X 5

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_Y
 * @brief Définition de la position Y du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_Y 238

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH
 * @brief Définition de la largeur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH 469

/**
 * @def K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT
 * @brief Définition de la hauteur du prompt de la console.
 */

#define K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT 30
/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_X
 * @brief Définition de la position X de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_X 450

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_Y
 * @brief Définition de la position Y de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_Y 0

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_WIDTH
 * @brief Définition de la largeur de la figure affichant le framerate.
 */

#define K_MK_SUPERVISOR_FRAMERATE_WIDTH 30

/**
 * @def K_MK_SUPERVISOR_FRAMERATE_HEIGHT
 * @brief Définition de la hauteur de la figure affichant le framerate.
*/

#define K_MK_SUPERVISOR_FRAMERATE_HEIGHT 25

/**
 *
 */

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_X
 * @brief Définition de la position X de la figure affichant la charge CPU.
 */

#define K_MK_SUPERVISOR_CPU_LOAD_X 450

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_Y
 * @brief Définition de la position Y de la figure affichant la charge CPU.
 */

#define K_MK_SUPERVISOR_CPU_LOAD_Y 25

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_WIDTH
 * @brief Définition de la largeur de la figure affichant la charge CPU.
*/

#define K_MK_SUPERVISOR_CPU_LOAD_WIDTH 30

/**
 * @def K_MK_SUPERVISOR_CPU_LOAD_HEIGHT
 * @brief Définition de la hauteur de la figure affichant la charge CPU.
*/

#define K_MK_SUPERVISOR_CPU_LOAD_HEIGHT 25

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

/**
 *
 */

#endif
