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
* @file mk_display_constants.h
* @brief Déclaration des constantes dédiées au module 'Display'.
* @date 24 mars 2019
*
*/

#ifndef MK_DISPLAY_CONSTANTS_H
#define MK_DISPLAY_CONSTANTS_H

/**
 * @def K_MK_DISPLAY_WIDTH
 * @brief Définition de la largeur de l'écran (en pixel). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_WIDTH 640

/**
 * @def K_MK_DISPLAY_HEIGHT
 * @brief Définition de la hauteur de l'écran (en pixel).\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_HEIGHT 480

/**
 * @def K_MK_DISPLAY_RESOLUTION_X
 * @brief Définition de la résolution X de l'écran (en pixel/m). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_RESOLUTION_X 5555

/**
 * @def K_MK_DISPLAY_RESOLUTION_Y
 * @brief Définition de la résolution Y de l'écran (en pixel/m).\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_RESOLUTION_Y 5555

/**
 *
 */

/**
 * @def K_MK_DISPLAY_LTDC_HSYNC_PULSE_WITDH
 * @brief Définition de la durée du pulse de synchronisation (en multiple de l'horloge pixel - ClockPixel).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_HSYNC_PULSE_WITDH 20

/**
 * @def K_MK_DISPLAY_LTDC_HBP_WIDTH
 * @brief Définition de la durée de l'Horizontal Blanck Porch (en multiple de l'horloge pixel - ClockPixel).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_HBP_WIDTH 114

/**
 * @def K_MK_DISPLAY_LTDC_HACTIVE_WIDTH
 * @brief Définition de la durée de de la zone active (en multiple de l'horloge pixel - ClockPixel).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_HACTIVE_WIDTH K_MK_DISPLAY_WIDTH

/**
 * @def K_MK_DISPLAY_LTDC_HFP_WIDTH
 * @brief Définition de la durée de l'Horizontal Front Porch (en multiple de l'horloge pixel - ClockPixel).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_HFP_WIDTH 4

/**
 * @def K_MK_DISPLAY_LTDC_VSYNC_PULSE_WITDH
 * @brief Définition de la durée du pulse de synchronisation (en multiple de l'horizontal ScanLine).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_VSYNC_PULSE_WITDH 3

/**
 * @def K_MK_DISPLAY_LTDC_VBP_WIDTH
 * @brief Définition de la durée du Vertical Blanck Porch (en multiple de l'horizontal ScanLine).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_VBP_WIDTH 2

/**
 * @def K_MK_DISPLAY_LTDC_VACTIVE_WIDTH
 * @brief Définition de la durée de la zone active (en multiple de l'horizontal ScanLine).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_VACTIVE_WIDTH K_MK_DISPLAY_HEIGHT

/**
 * @def K_MK_DISPLAY_LTDC_VFP_WIDTH
 * @brief Définition de la durée du Vertical Front Porch (en multiple de l'horizontal ScanLine).\n
 *        Constante propre au TFT AM-640480G5TNQW-T00H. Elle peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_VFP_WIDTH 2

/**
 * @def K_MK_DISPLAY_LTDC_DEFAULT_BACKGROUND
 * @brief Définition de la couleur d'arrière plan de l'écran. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_DEFAULT_BACKGROUND 0xFF000000

/**
 * @def K_MK_DISPLAY_LTDC_DEFAULT_LAYER_BACKGROUND
 * @brief Définition de la couleur d'arrière plan des layers. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_DEFAULT_LAYER_BACKGROUND 0x00000000

/**
 * @def K_MK_DISPLAY_LTDC_FREQUENCY
 * @brief Définition de la fréquence de l'horloge pixel (en Hz) - ClockPixel. La fréquence est issue de la PLL (cf. fonctions \ref mk_system_clock_setPrescaler et \ref mk_system_clock_setPLL).\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_LTDC_FREQUENCY 22750000

/**
 * @def K_MK_DISPLAY_SCANLINE
 * @brief Définition de la valeur du scanline pour le dessin d'une ligne (en multiple de l'horloge pixel - ClockPixel). \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_SCANLINE ( K_MK_DISPLAY_LTDC_HSYNC_PULSE_WITDH + K_MK_DISPLAY_LTDC_HBP_WIDTH + K_MK_DISPLAY_LTDC_HACTIVE_WIDTH + K_MK_DISPLAY_LTDC_HFP_WIDTH )

/**
 * @def K_MK_DISPLAY_FRAME
 * @brief Définition du temps pour dessiner une frame (en multiple de l'horizontal ScanLine). \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_FRAME ( ( K_MK_DISPLAY_LTDC_VSYNC_PULSE_WITDH + K_MK_DISPLAY_LTDC_VBP_WIDTH + K_MK_DISPLAY_LTDC_VACTIVE_WIDTH + K_MK_DISPLAY_LTDC_VFP_WIDTH ) * K_MK_DISPLAY_SCANLINE )

/**
 * @def K_MK_DISPLAY_FRAMERATE
 * @brief Définition de la valeur du FrameRate. \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_FRAMERATE ( K_MK_DISPLAY_LTDC_FREQUENCY / K_MK_DISPLAY_FRAME )

/**
 * @def K_MK_DISPLAY_BYTE_PER_PIXEL
 * @brief Définition de la taille maximale d'un pixel en octets (ARGB8888). \n
 *        Cette constante ne peut pas être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_BYTE_PER_PIXEL 4

/**
 * @def K_MK_DISPLAY_FRAME_BUFFER_SIZE
 * @brief Définition de la taille d'un buffer graphique (en multiple de mots 32 bits). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_FRAME_BUFFER_SIZE ( K_MK_DISPLAY_WIDTH * K_MK_DISPLAY_HEIGHT )

/**
 * @def K_MK_DISPLAY_FRAME_BUFFER_SIZE
 * @brief Définition du nombre de buffer graphique en multiple de 2 (foreground et background). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_FRAME_BUFFER_NUMBER 8

/**
 * @def K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR
 * @brief Définition de l'adresse de première banque du buffer graphique. \n
 *        Cette constante peut être modifiée par l'utilisateur selon les caractéristiques du composant.
 */

#define K_MK_DISPLAY_FRAME_BUFFER_BANK1_BASE_ADDR K_FMC_BANK5_BASE_ADDR

/**
 * @def K_MK_DISPLAY_FRAME_BUFFER_BANK2_BASE_ADDR
 * @brief Définition de l'adresse de deuxième banque du buffer graphique. \n
 *        Cette constante peut être modifiée par l'utilisateur.
 * @note  Pour optimiser les accès RW, les 2 buffers graphiques doivent être placés dans 2 banks
 *        différentes de la mémoire SDRAM.
 */

#define K_MK_DISPLAY_FRAME_BUFFER_BANK2_BASE_ADDR K_FMC_BANK5_BASE_ADDR + ( K_MK_DISPLAY_FRAME_BUFFER_NUMBER * K_MK_DISPLAY_FRAME_BUFFER_SIZE )

/**
 *
 */

#endif


