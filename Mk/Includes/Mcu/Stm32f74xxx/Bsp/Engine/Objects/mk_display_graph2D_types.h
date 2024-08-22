/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_display_graph2D_types.h
* @brief Déclaration des types dédiés à l'objet 'Graph2D'.
* @date 13 nov. 2023
*
*/

#ifndef MK_DISPLAY_GRAPH2D_TYPES_H
#define MK_DISPLAY_GRAPH2D_TYPES_H

/**
 * @struct T_mkGraphType
 * @brief Déclaration de la structure T_mkGraphType.
 */

typedef enum T_mkGraphType
{
   K_MK_GRAPH_TYPE_GRAPH2D = 0                                                /* Définition de l'identifiant d'une graphique 2D. */
} T_mkGraphType;

/**
 * @struct T_mkGraphType
 * @brief Déclaration de la structure T_mkGraph2DGridType.
 */

typedef enum T_mkGraph2DGridType
{
   K_MK_GRAPH2D_GRID_PRIMARY = 0,                                             /* Définition de l'identifiant de la grille principale. */
   K_MK_GRAPH2D_GRID_SECONDARY = 1                                            /* Définition de l'identifiant de la grille secondaire. */
} T_mkGraph2DGridType;

/**
 * @struct T_mkGraphType
 * @brief Déclaration de la structure T_mkGraph2DTextIdentifier.
 */

typedef enum T_mkGraph2DTextIdentifier
{
   K_MK_GRAPH2D_IDENTIFIER_TITLE = 0,                                         /* Définition de l'identifiant de la zone de texte contenant le titre du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_XLEGEND = 1,                                       /* Définition de l'identifiant de la zone de texte contenant la légende de l'axe x du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_YLEGEND = 2,                                       /* Définition de l'identifiant de la zone de texte contenant la légende de l'axe y du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_XMIN = 3,                                          /* Définition de l'identifiant de la zone de texte contenant la valeur minimale de l'axe x du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_XMAX = 4,                                          /* Définition de l'identifiant de la zone de texte contenant la valeur maximale de l'axe x du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_YMIN = 5,                                          /* Définition de l'identifiant de la zone de texte contenant la valeur minimale de l'axe y du graphique. */
   K_MK_GRAPH2D_IDENTIFIER_YMAX = 6,                                          /* Définition de l'identifiant de la zone de texte contenant la valeur maximale de l'axe y du graphique. */
   K_MK_GRAPH2D_NUMBER_OF_IDENTIFIER = 7                                      /* Définition de l'identifiant de la zone de texte contenant le nombre total de zone de texte dans le graphique. */
} T_mkGraph2DTextIdentifier;

/**
 * @struct T_mkGraph2DPlotMode
 * @brief Déclaration de la structure T_mkGraph2DPlotMode.
 */

typedef enum T_mkGraph2DPlotMode
{
   K_MK_GRAPH2D_TYPE_DOT = 0,                                                 /* Définition de l'identifiant permettant de dessiner les points de la courbe. */
   K_MK_GRAPH2D_TYPE_LINE = 1                                                 /* Définition de l'identifiant permettant de dessiner les lignes entre chaque point de la courbe. */
} T_mkGraph2DPlotMode;

/**
 * @struct T_mkGraph2DTextAttributes
 * @brief Déclaration de la structure T_mkGraph2DTextAttributes.
 */

typedef struct T_mkGraph2DTextAttributes T_mkGraph2DTextAttributes;
struct T_mkGraph2DTextAttributes
{
   T_mkVect2D position;                                                       /*!< Ce membre contient la position d'une zone de texte du graphique. */
   uint32_t width;                                                            /*!< Ce membre contient la largeur d'une zone de texte du graphique. */
   uint32_t height;                                                           /*!< Ce membre contient la hauteur d'une zone de texte du graphique. */
   T_str8 str;                                                                /*!< Ce membre contient l'adresse de la chaine de caractères d'une zone de texte du graphique. */
   T_mkTextStyle* style;                                                      /*!< Ce membre contient l'adresse du style de la chaine de caractères d'une zone de texte du graphique. */
};

/**
 * @struct T_mkGraph2DGridAttributes
 * @brief Déclaration de la structure T_mkGraph2DGridAttributes.
 */

typedef struct T_mkGraph2DGridAttributes T_mkGraph2DGridAttributes;
struct T_mkGraph2DGridAttributes
{
   uint32_t dx;                                                               /*!< Ce membre contient le nombre de pixels entre 2 colonnes de la grille. */
   uint32_t dy;                                                               /*!< Ce membre contient le nombre de pixels entre 2 lignes de la grille. */
   T_mkARGB color;                                                            /*!< Ce membre contient la couleur des lignes et des colonnes de la grille. */
   uint32_t visibility;                                                       /*!< Ce membre contient l'état de la grille (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
};

/**
 * @struct T_mkGraph2DGrid
 * @brief Déclaration de la structure T_mkGraph2DGrid.
 */

typedef struct T_mkGraph2DGrid T_mkGraph2DGrid;
struct T_mkGraph2DGrid
{
   T_mkGraph2DGridAttributes main;                                            /*!< Ce membre contient les attributs de la grille principale. */
   T_mkGraph2DGridAttributes secondary;                                       /*!< Ce membre contient les attributs de la grille secondaire. */
};

/**
 * @struct T_mkGraph2DAttributes
 * @brief Déclaration de la structure T_mkGraph2DAttributes.
 */

typedef struct T_mkGraph2DAttributes T_mkGraph2DAttributes;
struct T_mkGraph2DAttributes
{
   real32_t* pixelBuf;                                                        /*!< Ce membre contient les coordonnées Y des points du graphique [y0, y1, ..., yn ]. L'origine des points est relative à l'origine de l'écran. */
   real32_t* firstPixel;                                                      /*!< Ce membre contient l'adresse du premier pixel contenu dans le buffer de pixels. */
   real32_t* lastPixel;                                                       /*!< Ce membre contient l'adresse du dernier pixel contenu dans le buffer de pixels. */
   uint32_t  lengthOfPixelBuf;                                                /*!< Ce membre contient la longueur du buffer de pixels. */
   uint32_t  lengthOfUserBuf;                                                 /*!< Ce membre contient la longueur du buffer utilisateur. */
   uint32_t  lengthOfBuf;                                                     /*!< Ce membre contient le nombre de données à traiter dans le buffer de pixels. */
};

/**
 * @struct T_mkGraph2D
 * @brief Déclaration de la structure T_mkGraph2D.
 */

typedef struct T_mkGraph2D T_mkGraph2D;
struct T_mkGraph2D
{
   T_mkField field;                                                           /*!< Ce membre contient un champ de type \ref T_mkField (héritage). */
   T_mkAddr child;                                                            /*!< Ce membre contient l'adresse du descendant du graphique (héritage). */
   T_mkAddr cache;                                                            /*!< Ce membre contient l'adresse du cache du graphique. */
   T_mkVect2D position;                                                       /*!< Ce membre contient la position du plan de dessin de la courbe. */
   uint32_t width;                                                            /*!< Ce membre contient la largeur du plan de dessin de la courbe. */
   uint32_t height;                                                           /*!< Ce membre contient la hauteur du plan de dessin de la courbe. */
   T_mkARGB color;                                                            /*!< Ce membre contient la couleur de la courbe. */
   uint32_t refreshGrid;                                                      /*!< Ce membre contient le registre d'état qui indique si la grille doit être actualisée (\ref K_MK_FIELD_REFRESH_ENABLED) ou non (\ref K_MK_FIELD_REFRESH_DISABLED). */
   uint32_t refreshText;                                                      /*!< Ce membre contient le registre d'état qui indique si les textes du graphique doivent être actualisés (\ref K_MK_FIELD_REFRESH_ENABLED) ou non (\ref K_MK_FIELD_REFRESH_DISABLED). */
   uint32_t refreshCache;                                                     /*!< Ce membre contient le registre d'état qui indique si le cache doit être actualisé (\ref K_MK_FIELD_REFRESH_ENABLED) ou non (\ref K_MK_FIELD_REFRESH_DISABLED). */
   uint32_t textLayer;                                                        /*!< Ce membre contient le layer où les textes du graphique sont dessinés (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint32_t gridLayer;                                                        /*!< Ce membre contient le layer où la grille du graphique doit être dessinée (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint32_t backgroundVisibility;                                             /*!< Ce membre contient l'état de l'arrière plan du graphique (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB backgroundColor;                                                  /*!< Ce membre contient la couleur de l'arrière plan du graphique. */
   uint32_t foregroundVisibility;                                             /*!< Ce membre contient l'état du premier plan du graphique (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB foregroundColor;                                                  /*!< Ce membre contient la couleur du premier plan du graphique. */
   uint32_t borderVisibility;                                                 /*!< Ce membre contient l'état de la bordure du graphique (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB borderColor;                                                      /*!< Ce membre contient la couleur de la bordure du graphique. */
   T_mkGraph2DPlotMode type;                                                  /*!< Ce membre contient le mode de dessin du graphique (\ref T_mkGraph2DPlotMode). */
   T_mkGraph2DAttributes attribute;                                           /*!< Ce membre contient les attributs permettant de dessiner la courbe du graphique. */
   T_mkGraph2DGrid grid;                                                      /*!< Ce membre contient les caractéristiques des grilles du graphique. */
   T_mkGraph2DTextAttributes text [ K_MK_GRAPH2D_NUMBER_OF_IDENTIFIER ];      /*!< Ce membre contient les attributs des zones de texte du graphique. */
};


/**
 *
 */

#endif

