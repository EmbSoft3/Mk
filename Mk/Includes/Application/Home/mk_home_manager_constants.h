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
* @file mk_home_manager_constants.h
* @brief Déclaration des constantes dédiées à la vue de gestion des ressources du système.
* @date 10 déc. 2023
*
*/

#ifndef MK_HOME_MANAGER_CONSTANTS_H
#define MK_HOME_MANAGER_CONSTANTS_H

/**
 * @def K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_X
 * @brief Définition de la position TOP_LEFT [x] de la zone de travail.
 */

#define K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_X 0

/**
 * @def K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_Y
 * @brief Définition de la position TOP_LEFT [y] de la zone de travail.
 */

#define K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_Y 0

/**
 * @def K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X
 * @brief Définition de la position BOTTOM_RIGHT [x] de la zone de travail.
 */

#define K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X 479

/**
 * @def K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_Y
 * @brief Définition de la position BOTTOM_RIGHT [y] de la zone de travail.
 */

#define K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_Y 255

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X
 * @brief Définition de la position TOP_LEFT [x] de la zone d'affichage des applications.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y
 * @brief Définition de la position TOP_LEFT [y] de la zone d'affichage des applications.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_Y

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X
 * @brief Définition de la position BOTTOM_RIGHT [x] de la zone d'affichage des applications.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X + ( 1 * ( K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X - K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_X ) / 2 ) )

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_Y
 * @brief Définition de la position BOTTOM_RIGHT [y] de la zone d'affichage des applications.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_Y K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_Y

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER
 * @brief Définition du nombre de boutons pouvant être dessinés dans la zone d'affichage des applications.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER 3

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_WIDTH
 * @brief Définition de la largeur des boutons présents dans la zone d'affichage des applications [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_WIDTH ( 1 + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X )

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT
 * @brief Définition de la hauteur des boutons présents dans la zone d'affichage des applications [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT 85

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH
 * @brief Définition de la largeur des icônes de chaque application [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH 62

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT
 * @brief Définition de la hauteur des icônes de chaque application [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT 60

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_APPLICATION_ICON_PATH
 * @brief Définition du chemin de l'icône APPLICATION présente dans la vue.
 */

#define K_MK_HOME_MANAGERVIEW_APPLICATION_ICON_PATH ( T_str8 ) "mk/apps/home/mk_home_application.bmp"

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUS_ICON_PATH
 * @brief Définition du chemin de l'icône STATUS présente dans la vue.
 */

#define K_MK_HOME_MANAGERVIEW_STATUS_ICON_PATH ( T_str8 ) "mk/apps/home/mk_home_status.bmp"

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUS_ICON_WIDTH
 * @brief Définition de la largeur de l'icône présente dans la vue [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_STATUS_ICON_WIDTH 25

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUS_ICON_HEIGHT
 * @brief Définition de la hauteur de l'icône présente dans la vue [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_STATUS_ICON_HEIGHT 25

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_X
 * @brief Définition de la position TOP_LEFT [x] de la zone d'affichage des status.
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_X ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X + 1 )

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_Y
 * @brief Définition de la position TOP_LEFT [y] de la zone d'affichage des status.
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_Y K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUSAREA_BOTTOMRIGHT_X
 * @brief Définition de la position BOTTOM_RIGHT [x] de la zone d'affichage des status.
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_BOTTOMRIGHT_X K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUSAREA_BOTTOMRIGHT_Y
 * @brief Définition de la position BOTTOM_RIGHT [y] de la zone d'affichage des status.
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_BOTTOMRIGHT_Y K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_Y

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_WIDTH
 * @brief Définition de la largeur de la zone d'affichage des status [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_WIDTH ( 1 + K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_X - K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X )

/**
 * @def K_MK_HOME_MANAGERVIEW_STATUSAREA_HEIGHT
 * @brief Définition de la hauteur de la zone d'affichage des status [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_STATUSAREA_HEIGHT ( 1 + K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_Y - K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y )

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH
 * @brief Définition de la largeur des graphiques [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH 90

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT
 * @brief Définition de la hauteur des graphiques [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT 75

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_X
 * @brief Définition de la position relative du graphique [x] par rapport à l'origine de la zone.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_X 20

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_Y
 * @brief Définition de la position relative du graphique [y] par rapport à l'origine de la zone.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_Y 40

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X
 * @brief Définition de la position TOP_LEFT [x] de la zone d'affichage des graphiques.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y
 * @brief Définition de la position TOP_LEFT [y] de la zone d'affichage des graphiques.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_Y

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_X
 * @brief Définition de la position BOTTOM_RIGHT [x] de la zone d'affichage des graphiques.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_X K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X
 * @brief Définition de la position BOTTOM_RIGHT [y] de la zone d'affichage des graphiques.
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_Y ( K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_Y + K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT + K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_Y + 10 )

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_WIDTH
 * @brief Définition de la largeur de la zone d'affichage des graphiques [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_WIDTH ( 1 + K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_X - K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X )

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_HEIGHT
 * @brief Définition de la hauteur de la zone d'affichage des graphiques [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_HEIGHT ( 1 + K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_Y - K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y )

/**
 *
 */

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X
 * @brief Définition de la position TOP_LEFT [x] de la zone d'affichage des instances.
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y
 * @brief Définition de la position TOP_LEFT [y] de la zone d'affichage des instances.
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y ( K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_Y + 1 )

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_X
 * @brief Définition de la position BOTTOM_RIGHT [x] de la zone d'affichage des instances.
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_X K_MK_HOME_MANAGERVIEW_WORKINGAREA_BOTTOMRIGHT_X

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_Y
 * @brief Définition de la position BOTTOM_RIGHT [y] de la zone d'affichage des instances.
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_Y ( K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_BOTTOMRIGHT_Y + 140 )

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_WIDTH
 * @brief Définition de la largeur de la zone d'affichage des instances [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_WIDTH ( K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_X - K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X )

/**
 * @def K_MK_HOME_MANAGERVIEW_HANDLEAREA_WIDTH
 * @brief Définition de la hauteur de la zone d'affichage des instances [en pixels].
 */

#define K_MK_HOME_MANAGERVIEW_HANDLEAREA_HEIGHT ( K_MK_HOME_MANAGERVIEW_HANDLEAREA_BOTTOMRIGHT_Y - K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y )

/**
 *
 */

#endif


