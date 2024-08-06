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
* @file mk_display_chromart_types.h
* @brief Déclaration des types dédiés au module 'Chromart'.
* @date 21 févr. 2020
*
*/

#ifndef MK_DISPLAY_CHROMART_TYPES_H
#define MK_DISPLAY_CHROMART_TYPES_H

/**
 * @enum T_mkChromartRequestType
 * @brief Déclaration de la structure T_mkChromartRequestType.
 */

typedef enum T_mkChromartRequestType
{
   K_MK_DISPLAY_REQUEST_CHROMART_FILL = 0x0,                /*!< Définition de l'identifiant de la requête de type Fill. */
   K_MK_DISPLAY_REQUEST_CHROMART_COPY = 0x1,                /*!< Définition de l'identifiant de la requête de type Copy. */
   K_MK_DISPLAY_REQUEST_CHROMART_INVCOPY = 0x2,             /*!< Définition de l'identifiant de la requête de type InvCopy. */
   K_MK_DISPLAY_REQUEST_CHROMART_BLEND = 0x3,               /*!< Définition de l'identifiant de la requête de type Blend. */
   K_MK_DISPLAY_REQUEST_CHROMART_WRITE = 0x4,               /*!< Définition de l'identifiant de la requête de type Write. */
   K_MK_DISPLAY_REQUEST_CHROMART_STRING = 0x5,              /*!< Définition de l'identifiant de la requête de type String. */
   K_MK_DISPLAY_REQUEST_CHROMART_LOAD = 0x6,                /*!< Définition de l'identifiant de la requête de type Load. */
   K_MK_DISPLAY_REQUEST_CHROMART_CIRCLE = 0x7,              /*!< Définition de l'identifiant de la requête de type Circle. */
   K_MK_DISPLAY_REQUEST_CHROMART_LINE = 0x8,                /*!< Définition de l'identifiant de la requête de type Line. */
   K_MK_DISPLAY_REQUEST_CHROMART_TRIANGLE = 0x9,            /*!< Définition de l'identifiant de la requête de type Triangle. */
   K_MK_DISPLAY_REQUEST_CHROMART_ROUNDRECT = 0xA,           /*!< Définition de l'identifiant de la requête de type RoundRect. */
   K_MK_DISPLAY_REQUEST_CHROMART_ALPHA = 0xB,               /*!< Définition de l'identifiant de la requête de type Alpha. */
   K_MK_DISPLAY_REQUEST_CHROMART_PLOT = 0xC                 /*!< Définition de l'identifiant de la requête de type Plot. */
} T_mkChromartRequestType;

/**
 * @struct T_mkChromartPlane
 * @brief Déclaration de la structure T_mkChromartPlane.
 */

typedef struct T_mkChromartPlane T_mkChromartPlane;
struct T_mkChromartPlane
{
   uint32_t x;                                              /*!< Ce membre contient la coordonnée x de la figure à dessiner. */
   uint32_t y;                                              /*!< Ce membre contient la coordonnée y de la figure à dessiner. */
   uint32_t width;                                          /*!< Ce membre contient la largeur de l'objet à dessiner [en pxl] ou la valeur d'une coordonnée 'x'. */
   uint32_t height;                                         /*!< Ce membre contient la hauteur de l'objet à dessiner [en pxl] ou la valeur d'une coordonnée 'y'. */
};

/**
 * @struct T_mkChromartFillRequest
 * @brief Déclaration de la structure T_mkChromartFillRequest.
 * @note Structure de taille 8 octets.
 */

typedef struct T_mkChromartFillRequest T_mkChromartFillRequest;
struct T_mkChromartFillRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t offset;                                         /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte. */
   uint32_t color;                                          /*!< Ce membre contient la couleur de la figure (ARGB8888). */
};

/**
 * @struct T_mkChromartAlphaRequest
 * @brief Déclaration de la structure T_mkChromartAlphaRequest.
 * @note Structure de taille 4 octets.
 */

typedef struct T_mkChromartAlphaRequest T_mkChromartAlphaRequest;
struct T_mkChromartAlphaRequest
{
   uint8_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint8_t value;                                          /*!< Ce membre contient la valeur alpha du layer. */
   uint16_t padding;                                       /*!< Padding pour alignement. */
};

/**
 * @struct T_mkChromartCopyRequest
 * @brief Déclaration de la structure T_mkChromartCopyRequest.
 * @note Structure de taille 12 octets.
 */

typedef struct T_mkChromartCopyRequest T_mkChromartCopyRequest;
struct T_mkChromartCopyRequest
{
   T_mkAddr sourceAddr;                                     /*!< Ce membre contient la valeur de l'adresse source. */
   uint16_t sourceOffset;                                   /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse source lorsque la fin d'une ligne est atteinte. */
   uint16_t destinationOffset;                              /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte. */
   uint16_t destinationLayer;                               /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t padding16;                                      /*!< Padding pour alignement. */
   uint32_t dirOrResolution;                                /*!< Ce membre contient la direction du transfert (\ref K_MK_GRAPHICS_FRAME_TO_ADDR ou \ref K_MK_GRAPHICS_ADDR_TO_FRAME) et la résolution du transfert (\ref K_MK_GRAPHICS_ARGB8888, \ref K_MK_GRAPHICS_RGB888, \ref K_MK_GRAPHICS_RGB565, \ref K_MK_GRAPHICS_ARGB1555, \ref K_MK_GRAPHICS_ARGB4444). */
};

/**
 * @struct T_mkChromartBlendRequest
 * @brief Déclaration de la structure T_mkChromartBlendRequest.
 * @note Structure de taille 16 octets.
 */

typedef struct T_mkChromartBlendRequest T_mkChromartBlendRequest;
struct T_mkChromartBlendRequest
{
   T_mkAddr foregroundAddr;                                 /*!< Ce membre contient la valeur de l'adresse source (premier plan). */
   T_mkAddr backgroundAddr;                                 /*!< Ce membre contient la valeur de l'adresse source (arrière plan). */
   uint16_t foregroundOffset;                               /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse source (premier plan) lorsque la fin d'une ligne est atteinte. */
   uint16_t backgroundOffset;                               /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse source (arrière plan) lorsque la fin d'une ligne est atteinte. */
   uint16_t destinationOffset;                              /*!< Ce membre contient la valeur de l'offset ajouté à l'adresse de destination lorsque la fin d'une ligne est atteinte. */
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
};

/**
 * @struct T_mkChromartLoadRequest
 * @brief Déclaration de la structure T_mkChromartLoadRequest.
 * @note Structure de taille 12 octets.
 */

typedef struct T_mkChromartLoadRequest T_mkChromartLoadRequest;
struct T_mkChromartLoadRequest
{
   T_mkAddr bitmapAddr;                                     /*!< Ce membre contient l'adresse d'une structure de type \ref T_mkBMPFile. */
   T_mkAddr destinationAddr;                                /*!< Ce membre contient la valeur de l'adresse de destination où le bitmap doit être déployé. */
   uint16_t padding16;                                      /*!< Padding pour alignement. */
   uint8_t  bytesPerPixel;                                  /*!< Ce membre contient la résolution du buffer graphique où l'image doit être déployée (\ref K_MK_DISPLAY_RGB888 ou \ref K_MK_DISPLAY_ARGB8888). */
   uint8_t  alpha;                                          /*!< Ce membre contient la valeur de la composante alpha des images 24 bits. */
};

/**
 * @struct T_mkChromartStringRequest
 * @brief Déclaration de la structure T_mkChromartStringRequest.
 * @note Structure de taille 16 octets.
 */

typedef struct T_mkChromartStringRequest T_mkChromartStringRequest;
struct T_mkChromartStringRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t padding;                                        /*!< Padding pour alignement. */
   T_mkAddr baseAddr;                                       /*!< Ce membre contient l'adresse de base de la chaine de caractères. */
   T_mkAddr styleAddr;                                      /*!< Ce membre contient l'adresse d'une structure de type \ref T_mkTextStyle. */
   T_mkAddr cursorAddr;                                     /*!< Ce membre contient l'adresse d'une structure de type \ref T_mkTextCursor. */
};

/**
 * @struct T_mkChromartCircleRequest
 * @brief Déclaration de la structure T_mkChromartCircleRequest.
 * @note Structure de taille 12 octets.
 */

typedef struct T_mkChromartCircleRequest T_mkChromartCircleRequest;
struct T_mkChromartCircleRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t state;                                          /*!< Ce membre contient le mode de remplissage du cercle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY). */
   uint32_t radius;                                         /*!< Ce membre contient le rayon du cerle. */
   uint32_t color;                                          /*!< Ce membre contient la couleur de la figure (ARGB8888). */
};

/**
 * @struct T_mkChromartLineRequest
 * @brief Déclaration de la structure T_mkChromartLineRequest.
 * @note Structure de taille 8 octets.
 */

typedef struct T_mkChromartLineRequest T_mkChromartLineRequest;
struct T_mkChromartLineRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t padding16;                                      /*!< Padding pour alignement. */
   uint32_t color;                                          /*!< Ce membre contient la couleur de la figure (ARGB8888). */
   uint32_t x;                                              /*!< Ce membre contient contient la valeur de la coordonnée 'x2' de la droite. */
   uint32_t y;                                              /*!< Ce membre contient contient la valeur de la coordonnée 'y2' de la droite. */
};

/**
 * @struct T_mkChromartRoundRectRequest
 * @brief Déclaration de la structure T_mkChromartRoundRectRequest.
 * @note Structure de taille 8 octets.
 */

typedef struct T_mkChromartRoundRectRequest T_mkChromartRoundRectRequest;
struct T_mkChromartRoundRectRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t state;                                          /*!< Ce membre contient le mode de remplissage du rectangle (\ref K_MK_GRAPHICS_SOLID ou \ref K_MK_GRAPHICS_EMPTY). */
   uint32_t radius;                                         /*!< Ce membre contient le rayon de courbure des angles du rectangle. */
   uint32_t color;                                          /*!< Ce membre contient la couleur de la figure (ARGB8888). */
};

/**
 * @struct T_mkChromartTriangleRequest
 * @brief Déclaration de la structure T_mkChromartTriangleRequest.
 * @note Structure de taille 16 octets.
 */

typedef struct T_mkChromartTriangleRequest T_mkChromartTriangleRequest;
struct T_mkChromartTriangleRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t padding;                                        /*!< Padding pour alignement. */
   uint32_t x;                                              /*!< Ce membre contient contient la valeur de la coordonnée 'x3' du triangle. */
   uint32_t y;                                              /*!< Ce membre contient contient la valeur de la coordonnée 'y3' du triangle. */
   uint32_t color;                                          /*!< Ce membre contient la couleur de la figure (ARGB8888). */
};

/**
 * @struct T_mkChromartPlotRequest
 * @brief Déclaration de la structure T_mkChromartPlotRequest.
 * @note Structure de taille 8 octets.
 */

typedef struct T_mkChromartPlotRequest T_mkChromartPlotRequest;
struct T_mkChromartPlotRequest
{
   uint16_t layer;                                          /*!< Ce membre contient l'identifiant du layer de destination (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint16_t padding;                                        /*!< Padding pour alignement. */
   uint32_t type;                                           /*!< Ce membre contient le type de l'objet graphique (\ref T_mkGraphType). */
   T_mkAddr baseAddr;                                       /*!< Ce membre contient l'adresse d'un objet graphique (\ref T_mkGraph2D). */
};

/**
 * @union T_mkChromartRequestContent
 * @brief Déclaration de la structure T_mkChromartRequestContent.
 */

typedef union T_mkChromartRequestContent T_mkChromartRequestContent;
union T_mkChromartRequestContent
{
   T_mkChromartFillRequest fill;                            /*!< Ce membre contient les paramètres d'une requête de type 'Fill'. */
   T_mkChromartCopyRequest copy;                            /*!< Ce membre contient les paramètres d'une requête de type 'Copy'. */
   T_mkChromartBlendRequest blend;                          /*!< Ce membre contient les paramètres d'une requête de type 'Blend'. */
   T_mkChromartBlendRequest write;                          /*!< Ce membre contient les paramètres d'une requête de type 'Write'. */
   T_mkChromartStringRequest string;                        /*!< Ce membre contient les paramètres d'une requête de type 'String'. */
   T_mkChromartPlotRequest plot;                            /*!< Ce membre contient les paramètres d'une requête de type 'Plot'. */
   T_mkChromartLoadRequest load;                            /*!< Ce membre contient les paramètres d'une requête de type 'Load'. */
   T_mkChromartCircleRequest circle;                        /*!< Ce membre contient les paramètres d'une requête de type 'Circle'. */
   T_mkChromartLineRequest line;                            /*!< Ce membre contient les paramètres d'une requête de type 'Line'. */
   T_mkChromartTriangleRequest triangle;                    /*!< Ce membre contient les paramètres d'une requête de type 'Triangle'. */
   T_mkChromartRoundRectRequest roundRect;                  /*!< Ce membre contient les paramètres d'une requête de type 'RoundRect'. */
   T_mkChromartAlphaRequest alpha;                          /*!< Ce membre contient les paramètres d'une requête de type 'Alpha'. */
};

/**
 * @struct T_mkChromartRequest
 * @brief Déclaration de la structure T_mkChromartRequest.
 */

typedef struct T_mkChromartRequest T_mkChromartRequest;
struct T_mkChromartRequest
{
   uint32_t id;                                             /*!< Ce membre contient l'identifiant de la requête (\ref T_mkChromartRequestType). */
   T_mkChromartPlane plane;                                 /*!< Ce membre contient les paramètres génériques de la requête. */
   T_mkChromartRequestContent content;                      /*!< Ce membre contient les paramètres spécifiques de la requête. */
};

/**
 *
 */

#endif

