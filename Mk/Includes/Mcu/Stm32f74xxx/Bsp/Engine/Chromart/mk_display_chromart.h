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
* @file mk_display_chromart.h
* @brief Déclaration des fonctions publiques dédiées au module 'Chromart'.
* @date 21 févr. 2020
*
*/

#ifndef MK_DISPLAY_CHROMART_H
#define MK_DISPLAY_CHROMART_H

/**
 * @fn void mk_chromart_setPlane ( T_mkChromartPlane* p_plane, uint32_t p_x, uint32_t p_y, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure une structure de type \ref T_mkChromartPlane.
 *
 * @param[out] p_plane  Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartPlane.
 * @param[in]  p_x      Ce paramètre contient la coordonnée 'x' du plan.
 * @param[in]  p_y      Ce paramètre contient la coordonnée 'y' du plan.
 * @param[in]  p_width  Ce paramètre contient la largeur du plan [en pxl].
 * @param[in]  p_height Ce paramètre contient la hauteur du plan [en pxl].
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setPlane ( T_mkChromartPlane* p_plane, uint32_t p_x, uint32_t p_y, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_chromart_setFill ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_offset, uint32_t p_color );
 * @brief Cette fonction configure une requête de type 'Fill'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_offset  Ce paramètre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte.
 * @param[in]  p_color   Ce paramètre contient la couleur de la figure (ARGB8888).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setFill ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_offset, uint32_t p_color );

/**
 * @fn void mk_chromart_setAlpha ( T_mkChromartRequest* p_request, uint8_t p_layer, uint8_t p_alpha );
 * @brief Cette fonction configure une requête de type 'Alpha'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_alpha   Ce paramètre contient la valeur alpha du layer.
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setAlpha ( T_mkChromartRequest* p_request, uint8_t p_layer, uint8_t p_alpha );

/**
 * @fn void mk_chromart_setCopy ( T_mkChromartRequest* p_request, T_mkAddr p_source, uint32_t p_sourceOffset, uint32_t p_destinationLayer, uint32_t p_destinationOffset, uint32_t p_dirOrResolution );
 * @brief Cette fonction configure une requête de type 'Copy'.
 *
 * @param[out] p_request           Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_source            Ce paramètre contient contient la valeur de l'adresse source.
 * @param[in]  p_sourceOffset      Ce paramètre contient la valeur de l'offset ajouté à l'adresse source lorsque la fin d'une ligne est atteinte.
 * @param[in]  p_destinationLayer  Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_destinationOffset Ce paramètre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte.
 * @param[in]  p_dirOrResolution   Ce paramètre contient la direction du transfert (\ref K_MK_GRAPHICS_FRAME_TO_ADDR ou \ref K_MK_GRAPHICS_ADDR_TO_FRAME) et la résolution de sortie
 *                                 du transfert (\ref K_MK_GRAPHICS_ARGB8888, \ref K_MK_GRAPHICS_RGB888, \ref K_MK_GRAPHICS_RGB565, \ref K_MK_GRAPHICS_ARGB1555, \ref K_MK_GRAPHICS_ARGB4444).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setCopy ( T_mkChromartRequest* p_request, T_mkAddr p_source, uint32_t p_sourceOffset, uint32_t p_destinationLayer, uint32_t p_destinationOffset, uint32_t p_dirOrResolution );

/**
 * @fn void mk_chromart_setBlend ( T_mkChromartRequest* p_request, T_mkAddr p_foreground, T_mkAddr p_background, uint32_t p_layer );
 * @brief Cette fonction configure une requête de type 'Blend'.
 *
 * @param[out] p_request    Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_foreground Ce paramètre contient la valeur de la première adresse source (premier plan).
 * @param[in]  p_background Ce paramètre contient la valeur de la seconde adresse source (arrière plan).
 * @param[in]  p_layer      Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setBlend ( T_mkChromartRequest* p_request, T_mkAddr p_foreground, T_mkAddr p_background, uint32_t p_layer );

/**
 * @fn void mk_chromart_setBlendOffset ( T_mkChromartRequest* p_request, uint32_t p_foregroundOffset, uint32_t p_backgroundOffset, uint32_t p_destinationOffset );
 * @brief Cette fonction configure une requête de type 'Blend'.
 *
 * @param[out] p_request           Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_foregroundOffset  Ce paramètre contient la valeur de l'offset ajouté à l'adresse source (premier plan) lorsque la fin d'une ligne est atteinte.
 * @param[in]  p_backgroundOffset  Ce paramètre contient la valeur de l'offset ajouté à l'adresse source (arrière plan) lorsque la fin d'une ligne est atteinte.
 * @param[in]  p_destinationOffset Ce paramètre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte.
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setBlendOffset ( T_mkChromartRequest* p_request, uint32_t p_foregroundOffset, uint32_t p_backgroundOffset, uint32_t p_destinationOffset );

/**
 * @fn void mk_chromart_setString ( T_mkChromartRequest* p_request, T_mkAddr p_stringAddr, T_mkAddr p_styleAddr, T_mkAddr p_cursorAddr, uint32_t p_layer );
 * @brief Cette fonction configure une requête de type 'String'.
 *
 * @param[out] p_request    Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_stringAddr Ce paramètre contient l'adresse de base de la chaine de caractères.
 * @param[in]  p_styleAddr  Ce paramètre contient l'adresse d'une structure de type \ref T_mkTextStyle.
 * @param[in]  p_cursorAddr Ce paramètre contient l'adresse d'une structure de type \ref T_mkTextCursor.
 * @param[in]  p_layer      Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setString ( T_mkChromartRequest* p_request, T_mkAddr p_stringAddr, T_mkAddr p_styleAddr, T_mkAddr p_cursorAddr, uint32_t p_layer );

/**
 * @fn void mk_chromart_setCircle ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_state, uint32_t radius, uint32_t p_argb );
 * @brief Cette fonction configure une requête de type 'Circle'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_state   Ce paramètre contient le mode de remplissage du cercle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY).
 * @param[in]  radius    Ce paramètre contient le rayon du cercle [en pxl].
 * @param[in]  p_argb    Ce paramètre contient la couleur de la figure (ARGB8888).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setCircle ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_state, uint32_t radius, uint32_t p_argb );

/**
 * @fn void mk_chromart_setLine ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_argb );
 * @brief Cette fonction configure une requête de type 'Line'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_x       Ce paramètre contient la valeur de la coordonnée 'x2' de la droite.
 * @param[in]  p_y       Ce paramètre contient la valeur de la coordonnée 'y2' de la droite.
 * @param[in]  p_argb    Ce paramètre contient la couleur de la figure (ARGB8888).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setLine ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_argb );

/**
 * @fn void mk_chromart_setTriangle ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_argb );
 * @brief Cette fonction configure une requête de type 'Triangle'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_x       Ce paramètre contient la valeur de la coordonnée 'x3' du triangle.
 * @param[in]  p_y       Ce paramètre contient la valeur de la coordonnée 'y3' du triangle.
 * @param[in]  p_argb    Ce paramètre contient la couleur de la figure (ARGB8888).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setTriangle ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_x, uint32_t p_y, uint32_t p_argb );

/**
 * @fn void mk_chromart_setRoundRect ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_state, uint32_t p_radius, uint32_t p_argb );
 * @brief Cette fonction configure une requête de type 'RoundRect'.
 *
 * @param[out] p_request Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer   Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_state   Ce paramètre contient le mode de remplissage du rectangle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY).
 * @param[in]  p_radius  Ce paramètre contient le rayon de courbure des angles [en pxl].
 * @param[in]  p_argb    Ce paramètre contient la couleur de la figure (ARGB8888).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setRoundRect ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_state, uint32_t p_radius, uint32_t p_argb );

/**
 * @fn void mk_chromart_setLoad ( T_mkChromartRequest* p_request, T_mkAddr p_bitmapAddr, T_mkAddr p_destinationAddr, uint8_t p_alpha );
 * @brief Cette fonction configure une requête de type 'Load'.
 *
 * @param[out] p_request         Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_bitmapAddr      Ce paramètre contient l'adresse d'une structure de type \ref T_mkBMPFile.
 * @param[in]  p_destinationAddr Ce paramètre contient l'adresse de destination où le bitmap doit être déployé.
 * @param[in]  p_bytesPerPixel   Ce paramètre contient la résolution du buffer graphique où l'image doit être déployée (\ref K_MK_DISPLAY_RGB888 ou \ref K_MK_DISPLAY_ARGB8888).
 * @param[in]  p_alpha           Ce paramètre contient la valeur de la composante alpha des images 24 bits.
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setLoad ( T_mkChromartRequest* p_request, T_mkAddr p_bitmapAddr, T_mkAddr p_destinationAddr, uint32_t p_bytesPerPixel, uint8_t p_alpha );

/**
 * @fn void mk_chromart_setPlot ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_type, T_mkAddr p_baseAddr );
 * @brief Cette fonction configure une requête de type 'Plot'.
 *
 * @param[out] p_request   Ce paramètre contient l'adresse d'une structure de type \ref T_mkChromartRequest.
 * @param[in]  p_layer     Ce paramètre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND).
 * @param[in]  p_type      Ce paramètre contient le type de l'objet 'p_baseAddr' (\ref T_mkGraphType).
 * @param[in]  p_baseAddr  Ce paramètre contient l'adresse d'un objet graphique (\ref T_mkGraph2D, ...).
 *
 * @return Sans objet.
 *
 */

void mk_chromart_setPlot ( T_mkChromartRequest* p_request, uint32_t p_layer, uint32_t p_type, T_mkAddr p_baseAddr );

/**
 *
 */

#endif

