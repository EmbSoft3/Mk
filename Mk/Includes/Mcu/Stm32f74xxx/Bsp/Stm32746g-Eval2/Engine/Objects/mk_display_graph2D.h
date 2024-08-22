/**
*
* @copyright Copyright (C) 2023-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_display_graph2d.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'Graph2D'.
* @date 13 nov. 2023
*
*/

#ifndef MK_DISPLAY_GRAPH2D_H
#define MK_DISPLAY_GRAPH2D_H

/**
 * @fn void mk_graph2D_init ( T_mkGraph2D* p_graph2D );
 * @brief Cette fonction initialise un graphique.
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_init ( T_mkGraph2D* p_graph2D );

/**
 * @fn void mk_graph2D_setChild ( T_mkGraph2D* p_graph2D, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_child   Ce paramètre contient l'adresse du descendant du graphique (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_graph2D_setChild ( T_mkGraph2D* p_graph2D, T_mkAddr p_child );

/**
 * @fn void mk_graph2D_setPosition ( T_mkGraph2D* p_graph2D, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_x       Ce paramètre contient la coordonnée x du graphique [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y       Ce paramètre contient la coordonnée y du graphique [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setPosition ( T_mkGraph2D* p_graph2D, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_graph2D_setDimension ( T_mkGraph2D* p_graph2D, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_width   Ce paramètre contient la largeur du graphique [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height  Ce paramètre contient la hauteur du graphique [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setDimension ( T_mkGraph2D* p_graph2D, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_graph2D_setLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_layer   Ce paramètre contient le layer où la courbe du graphique doit être dessinée.
 *                       Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );

/**
 * @fn void mk_graph2D_setZIndex ( T_mkGraph2D* p_graph2D, uint32_t p_zIndex );
 * @brief Cette fonction configure l'indice de profondeur d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_zIndex  Ce paramètre contient l'indice de profondeur du graphique. Il évolue de [0 à 0xFFFFFFFF].
 *                       La valeur 0 indique que le graphique doit être dessiné en premier, la valeur 0xFFFFFFFF indique
 *                       qu'il doit être dessiné en dernier.
 *                       Si deux objets dans un container possèdent le même indice de profondeur, l'objet dessiné
 *                       en premier est le dernier objet ajouté dans le container.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setZIndex ( T_mkGraph2D* p_graph2D, uint32_t p_zIndex );

/**
 * @fn void mk_graph2D_setVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'un graphique.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_visibility Ce paramètre contient l'état du graphique.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );

/**
 * @fn void mk_graph2D_setActivity ( T_mkGraph2D* p_graph2D, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'un graphique.
 *
 * @param[out] p_graph2D  Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_activity Ce paramètre contient l'état du graphique.
 *                        Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setActivity ( T_mkGraph2D* p_graph2D, uint32_t p_activity );

/**
 * @fn void mk_graph2D_setPainter ( T_mkGraph2D* p_graph2D, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_painter Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                       T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setPainter ( T_mkGraph2D* p_graph2D, T_mkPainter p_painter );

/**
 * @fn void mk_graph2D_setListener ( T_mkGraph2D* p_graph2D, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute d'un graphique.
 *
 * @param[out] p_graph2D  Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_listener Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                        T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setListener ( T_mkGraph2D* p_graph2D, T_mkListener p_listener );

/**
 * @fn void mk_graph2D_setRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'un graphique.
 *
 * @param[in,out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]     p_refresh Ce paramètre contient l'état de rafraichissement du graphique. Les valeurs suivantes peuvent être utilisées :
 *                          \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement du graphique pendant au moins 'n'
 *                          frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                          \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement du graphique. Le compteur de
 *                          rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                          le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );

/**
 * @fn void mk_graph2D_setColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );
 * @brief Cette fonction configure la couleur de la courbe du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_color   Ce paramètre contient la couleur de la courbe au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );

/**
 * @fn void mk_graph2D_setBackgroundColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );
 * @brief Cette fonction configure la couleur de l'arrière plan d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_color   Ce paramètre contient la couleur de l'arrière plan au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setBackgroundColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );

/**
 * @fn void mk_graph2D_setBackgroundVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de l'arrière plan d'un graphique.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_visibility Ce paramètre contient l'état de l'arrière plan d'un graphique.
 *                          Il peut prendre les valeurs \ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setBackgroundVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );

/**
 * @fn void mk_graph2D_setForegroundColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );
 * @brief Cette fonction configure la couleur du premier plan d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_color   Ce paramètre contient la couleur du premier plan au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setForegroundColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );

/**
 * @fn void mk_graph2D_setForegroundVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité du premier plan d'un graphique.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_visibility Ce paramètre contient l'état du premier plan d'un graphique.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setForegroundVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );

/**
 * @fn void mk_graph2D_setBorderColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );
 * @brief Cette fonction configure la couleur de la bordure d'un graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_color   Ce paramètre contient la couleur de la bordure au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setBorderColor ( T_mkGraph2D* p_graph2D, uint32_t p_color );

/**
 * @fn void mk_graph2D_setBorderVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de la bordure d'un graphique.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_visibility Ce paramètre contient l'état de la bordure d'un graphique.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setBorderVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_visibility );

/**
 * @fn void mk_graph2D_setCache ( T_mkGraph2D* p_graph2D, T_mkAddr p_cache );
 * @brief Cette fonction configure l'adresse du cache d'un graphique. Le cache est un buffer
 *        stockant les pixels du graphique. Son utilisation peut réduire le temps de traitement de la
 *        fonction de peinture. En effet, si les données contenues dans le graphique n'ont pas été modifiées, une copie de pixels
 *        est réalisée du cache vers le buffer graphique. Les traitements longs de la boite de texte ne sont pas réalisés.
 *        Les dessins de la courbe et des zones de texte ne sont pas inclus dans le cache.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_cache   Ce paramètre contient l'adresse du cache du graphique.
 *                       Sa taille est définie de la manière suivante : width * height * 32 [BitsPerPixel].
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setCache ( T_mkGraph2D* p_graph2D, T_mkAddr p_cache );

/**
 * @fn void mk_graph2D_setType ( T_mkGraph2D* p_graph2D, uint32_t p_type );
 * @brief Cette fonction configure le type de la courbe du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_type    Ce paramètre contient le type de la courbe (\ref T_mkGraph2DPlotMode).
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setType ( T_mkGraph2D* p_graph2D, uint32_t p_type );

/**
 * @fn void mk_graph2D_refreshCache ( T_mkGraph2D* p_graph2D );
 * @brief Cette fonction déclenche un rafraichissement du cache.
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_refreshCache ( T_mkGraph2D* p_graph2D );

/**
 * @fn void mk_graph2D_setText ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, T_str8 p_text );
 * @brief Cette fonction configure le texte de la zone identifiée par p_identifier.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_identifier Ce paramètre contient l'identifiant de la zone de texte à configurer (\ref T_mkGraph2DTextIdentifier).
 * @param[in]  p_text       Ce paramètre contient l'adresse d'une chaine de caractères.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setText ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, T_str8 p_text );

/**
 * @fn void mk_graph2D_setTextLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );
 * @brief Cette fonction configure le layer des textes du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_layer   Ce paramètre contient le layer où les textes du graphique doivent être dessinés.
 *                       Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setTextLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );

/**
 * @fn void mk_graph2D_setTextRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement des textes d'un graphique.
 *
 * @param[in,out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]     p_refresh Ce paramètre contient l'état de rafraichissement du graphique. Les valeurs suivantes peuvent être utilisées :
 *                          \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement des texte du graphique pendant au moins 'n'
 *                          frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                          \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement des textes du graphique. Le compteur de
 *                          rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                          le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setTextRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );

/**
 * @fn void mk_graph2D_setTextArea ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, real32_t p_x, real32_t p_y, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la position et la taille de la zone de texte identifiée par p_identifier.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_identifier Ce paramètre contient l'identifiant de la zone de texte à configurer (\ref T_mkGraph2DTextIdentifier).
 * @param[in]  p_x          Ce paramètre contient la coordonnée x de la zone de texte [en pixel].
 *                          Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y          Ce paramètre contient la coordonnée y de la zone de texte [en pixel].
 *                          Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 * @param[in]  p_width      Ce paramètre contient la largeur de la zone de texte [en pixel].
 *                          Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height     Ce paramètre contient la hauteur de la zone de texte [en pixel].
 *                          Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setTextArea ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, real32_t p_x, real32_t p_y, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_graph2D_setTextStyle ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, T_mkTextStyle* p_style );
 * @brief Cette fonction configure le style de la zone de texte identifiée par p_identifier.
 *
 * @param[out] p_graph2D    Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_identifier Ce paramètre contient l'identifiant de la zone de texte à configurer (\ref T_mkGraph2DTextIdentifier).
 * @param[in]  p_style      Ce paramètre contient l'adresse d'un style de type \ref T_mkTextStyle. Il peut prendre la valeur \ref K_MK_NULL.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setTextStyle ( T_mkGraph2D* p_graph2D, uint32_t p_identifier, T_mkTextStyle* p_style );

/**
 * @fn void mk_graph2D_setArea ( T_mkGraph2D* p_graph2D, real32_t p_x, real32_t p_y, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la position et les dimensions du plan où la courbe du graphique est dessinée.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_x       Ce paramètre contient la coordonnée x du plan [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y       Ce paramètre contient la coordonnée y du plan [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 * @param[in]  p_width   Ce paramètre contient la largeur du plan [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height  Ce paramètre contient la hauteur du plan [en pixel].
 *                       Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setArea ( T_mkGraph2D* p_graph2D, real32_t p_x, real32_t p_y, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_graph2D_setGrid ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_dx, uint32_t p_dy );
 * @brief Cette fonction configure les dimensions d'une des grilles du graphique.
 *
 * @param[out] p_graph2D        Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_gridIdentifier Ce paramètre contient l'identifiant de la grille à configurer (\ref K_MK_GRAPH2D_GRID_PRIMARY ou \ref K_MK_GRAPH2D_GRID_SECONDARY).
 * @param[in]  p_dx             Ce paramètre contient le nombre de pixels entre deux colonnes de la grille.
 * @param[in]  p_dy             Ce paramètre contient le nombre de pixels entre deux lignes de la grille.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setGrid ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_dx, uint32_t p_dy );

/**
 * @fn void mk_graph2D_setGridLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );
 * @brief Cette fonction configure le layer de la grille du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_layer   Ce paramètre contient le layer où la grille doit être dessinée.
 *                       Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setGridLayer ( T_mkGraph2D* p_graph2D, uint32_t p_layer );

/**
 * @fn void mk_graph2D_setGridRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement de la grille d'un graphique.
 *
 * @param[in,out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]     p_refresh Ce paramètre contient l'état de rafraichissement du graphique. Les valeurs suivantes peuvent être utilisées :
 *                          \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement de la grille du graphique pendant au moins 'n'
 *                          frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                          \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement de la grille du graphique. Le compteur de
 *                          rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                          le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setGridRefresh ( T_mkGraph2D* p_graph2D, uint32_t p_refresh );

/**
 * @fn void mk_graph2D_setGridVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'une des grilles du graphique.
 *
 * @param[out] p_graph2D        Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_gridIdentifier Ce paramètre contient l'identifiant de la grille à configurer (\ref K_MK_GRAPH2D_GRID_PRIMARY ou \ref K_MK_GRAPH2D_GRID_SECONDARY).
 * @param[in]  p_visibility     Ce paramètre contient l'état de la grille.
 *                              Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setGridVisibility ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_visibility );

/**
 * @fn void mk_graph2D_setGridColor ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_color );
 * @brief Cette fonction configure la couleur d'une des grilles du graphique.
 *
 * @param[out] p_graph2D        Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_gridIdentifier Ce paramètre contient l'identifiant de la grille à configurer (\ref K_MK_GRAPH2D_GRID_PRIMARY ou \ref K_MK_GRAPH2D_GRID_SECONDARY).
 * @param[in]  p_color          Ce paramètre contient la couleur de la grille au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setGridColor ( T_mkGraph2D* p_graph2D, uint32_t p_gridIdentifier, uint32_t p_color );

/**
 * @fn void mk_graph2D_setPixelBuf ( T_mkGraph2D* p_graph2D, real32_t* p_buf, uint32_t p_length );
 * @brief Cette fonction configure l'adresse du buffer de pixels de la courbe d'un graphique. Le buffer stocke les coordonnées y du graphique.
 *
 * @param[out] p_graph2D Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_buf     Ce paramètre contient l'adresse d'un buffer une dimension de type float32.
 * @param[in]  p_length  Ce paramètre contient la longueur du buffer.
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_setPixelBuf ( T_mkGraph2D* p_graph2D, real32_t* p_buf, uint32_t p_length );

/**
 * @fn void mk_graph2D_computeInt32 ( T_mkGraph2D* p_graph2D, int32_t* p_userInt32Buf, uint32_t p_bufLength, int32_t p_ymin, int32_t p_ymax );
 * @brief Cette fonction ajoute un buffer d'entiers de longueur p_bufLength dans un graphique. Le buffer est ajouté depuis le début du buffer de pixels (indice 0).
 *
 * @param[out] p_graph2D      Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_userInt32Buf Ce paramètre contient l'adresse d'un buffer une dimension de type int32.
 * @param[in]  p_bufLength    Ce paramètre contient la longueur du buffer.
 * @param[in]  p_ymin         Ce paramètre contient la valeur de la borne ymin du graphique. Il est utilisé pour la mise à l'échelle des données (ymax = position->y).
 * @param[in]  p_ymax         Ce paramètre contient la valeur de la borne ymax du graphique. Il est utilisé pour la mise à l'échelle des données (ymin = position->y + dimension->height - 1).
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_computeInt32 ( T_mkGraph2D* p_graph2D, int32_t* p_userInt32Buf, uint32_t p_bufLength, int32_t p_ymin, int32_t p_ymax );

/**
 * @fn void mk_graph2D_addFirstInt32 ( T_mkGraph2D* p_graph2D, int32_t p_userInt32, int32_t p_ymin, int32_t p_ymax );
 * @brief Cette fonction ajoute un entier dans un graphique. L'entier est ajouté au début du buffer de pixels (indice 0).
 *        Les pointeurs de début et de fin du buffer sont décalés d'une unité.
 *
 * @param[out] p_graph2D   Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_userInt32 Ce paramètre contient la valeur d'un entier de type int32.
 * @param[in]  p_ymin      Ce paramètre contient la valeur de la borne ymin du graphique. Il est utilisé pour la mise à l'échelle des données (ymax = position->y).
 * @param[in]  p_ymax      Ce paramètre contient la valeur de la borne ymax du graphique. Il est utilisé pour la mise à l'échelle des données (ymin = position->y + dimension->height - 1).
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_addFirstInt32 ( T_mkGraph2D* p_graph2D, int32_t p_userInt32, int32_t p_ymin, int32_t p_ymax );

/**
 * @fn void mk_graph2D_addLastInt32 ( T_mkGraph2D* p_graph2D, int32_t p_userInt32, int32_t p_ymin, int32_t p_ymax );
 * @brief Cette fonction ajoute un entier dans un graphique. L'entier est ajouté à la fin du buffer de pixels (indice lengthOfBuf - 1).
 *        Les pointeurs de début et de fin du buffer sont décalés d'une unité.
 *
 * @param[out] p_graph2D   Ce paramètre contient l'adresse d'un graphique de type \ref T_mkGraph2D.
 * @param[in]  p_userInt32 Ce paramètre contient la valeur d'un entier de type int32.
 * @param[in]  p_ymin      Ce paramètre contient la valeur de la borne ymin du graphique. Il est utilisé pour la mise à l'échelle des données (ymax = position->y).
 * @param[in]  p_ymax      Ce paramètre contient la valeur de la borne ymax du graphique. Il est utilisé pour la mise à l'échelle des données (ymin = position->y + dimension->height - 1).
 *
 * @return Sans objet.
 *
 */

void mk_graph2D_addLastInt32 ( T_mkGraph2D* p_graph2D, int32_t p_userInt32, int32_t p_ymin, int32_t p_ymax );

/**
 * @fn T_mkCode mk_graph2D_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut d'un graphique. Elle est exécutée à intervalle régulier par le moteur graphique.
 *
 * @param[in] p_container    Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field        Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkGraph2D.
 *                           L'adresse du graphique peut être récupérée en utilisant l'attribut 'child'.
 * @param[in]  p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                           Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le traitement de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le traitement de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le traitement de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le traitement de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_graph2D_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif

