/**
*
* @copyright Copyright (C) 2019-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_display_field_types.h
* @brief Déclaration des types dédiés au module "Field".
* @date 3 mai 2019
*
*/

#ifndef MK_DISPLAY_FIELD_TYPES_H
#define MK_DISPLAY_FIELD_TYPES_H

/**
 *
 */

typedef struct T_mkContainer T_mkContainer;
typedef struct T_mkField T_mkField;

/**
 * @struct T_mkPainter
 * @brief Déclaration du type T_mkPainter.
 */

typedef T_mkCode ( *T_mkPainter ) ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @struct T_mkListener
 * @brief Déclaration du type T_mkListener.
 */

typedef T_mkCode ( *T_mkListener ) ( T_mkContainer* p_container, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );

/**
 *
 */

/**
 * @struct T_mkFieldDimension
 * @brief Déclaration de la structure T_mkFieldDimension.
 */

typedef struct T_mkFieldDimension T_mkFieldDimension;
struct T_mkFieldDimension
{
   uint32_t width;                     /*!< Ce membre contient la largeur du champ [en pixel]. */
   uint32_t height;                    /*!< Ce membre contient la hauteur du champ [en pixel]. */
};

/**
 * @struct T_mkField
 * @brief Déclaration de la structure T_mkField.
 */

struct T_mkField
{
   uint32_t focus;                     /*!< Ce membre contient l'état du focus (\ref K_MK_FIELD_STATE_IDLE et \ref K_MK_FIELD_STATE_FOCUS). Un champ possède le focus lors qu'un clic de la souris est réalisé à l'intérieur. */
   uint32_t cursor;                    /*!< Ce membre contient l'état du curseur. Il prend les valeurs \ref K_MK_FIELD_CURSOR_OUTSIDE et \ref K_MK_FIELD_CURSOR_INSIDE lorsque le curseur de la souris entre ou sort du champ. */
   uint32_t refresh;                   /*!< Ce membre contient l'état de rafraichissement du champ (\ref K_MK_FIELD_REFRESH_ENABLED et \ref K_MK_FIELD_REFRESH_DISABLED). Ce membre est dédié au moteur graphique. */
   uint32_t userRefresh;               /*!< Ce membre contient l'état de rafraichissement du champ (\ref K_MK_FIELD_REFRESH_ENABLED et \ref K_MK_FIELD_REFRESH_DISABLED). Ce membre est dédié à l'utilisateur. */
   uint32_t visibility;                /*!< Ce membre contient la visibilité du champ (\ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE). Il permet d'activer ou désactiver l'exécution de la fonction de peinture. Ce membre est dédié au moteur graphique. */
   uint32_t userVisibility;            /*!< Ce membre contient la visibilité du champ (\ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE). Il permet d'activer ou désactiver l'exécution de la fonction de peinture. Ce membre est dédié à l'utilisateur. */
   uint32_t activity;                  /*!< Ce membre contient l'activité du champ (\ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF). Il permet d'activer ou désactiver l'exécution de la fonction d'écoute. */
   uint32_t layer;                     /*!< Ce membre contient le layer où le champ est dessiné (\ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND). */
   uint32_t zIndex;                    /*!< Ce membre contient la valeur de l'indice de profondeur du champ dans son container. Il évolue de [0 à 0xFFFFFFFF]. */
   uint32_t frameNumber;               /*!< Ce membre contient l'index de la frame en cours de dessin. Il évolue entre [0 et \ref K_MK_DISPLAY_FRAMERATE - 1]. */
   T_mkVect2D position;                /*!< Ce membre contient les coordonnées [x, y] du champ [en pixel]. */
   T_mkFieldDimension dimension;       /*!< Ce membre contient les dimensions [width, height] du champ [en pixel]. */
   T_mkListener listener;              /*!< Ce membre contient l'adresse de la fonction d'écoute du champ. */
   T_mkPainter painter;                /*!< Ce membre contient l'adresse de la fonction de peinture du champ. */
   T_mkAddr child;                     /*!< Ce membre contient l'adresse du descendant du champ (héritage). */
   T_mkField* next;                    /*!< Ce membre contient l'adresse du champ suivant le champ actuel dans un container de type \ref T_mkContainer. */
   T_mkField* previous;                /*!< Ce membre contient l'adresse du champ précédent le champ actuel dans un container de type \ref T_mkContainer. */
};

/**
 *
 */

#endif


