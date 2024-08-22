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
* @file mk_display_field.h
* @brief Déclaration des fonctions publiques dédiées au module 'Field'.
* @date 9 mai 2019
*
*/

#ifndef MK_DISPLAY_FIELD_H
#define MK_DISPLAY_FIELD_H

/**
 * @fn void mk_field_init ( T_mkField* p_field );
 * @brief Cette fonction initialise un champ.
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 *
 * @return Sans objet.
 *
 */

void mk_field_init ( T_mkField* p_field );

/**
 * @fn void mk_field_setChild ( T_mkField* p_field, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'un champ.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_child Ce paramètre contient l'adresse du descendant du champ (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_field_setChild ( T_mkField* p_field, T_mkAddr p_child );

/**
 * @fn void mk_field_setPosition ( T_mkField* p_field, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'un champ.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_x     Ce paramètre contient la coordonnée x du champ [en pixel].
 *                     Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y     Ce paramètre contient la coordonnée y du champ [en pixel].
 *                     Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_field_setPosition ( T_mkField* p_field, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_field_setDimension ( T_mkField* p_field, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'un champ.
 *
 * @param[out] p_field  Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_width  Ce paramètre contient la largeur du champ [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height Ce paramètre contient la hauteur du champ [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_field_setDimension ( T_mkField* p_field, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_field_setLayer ( T_mkField* p_field, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'un champ.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_layer Ce paramètre contient le layer où le champ doit être dessiné.
 *                     Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_field_setLayer ( T_mkField* p_field, uint32_t p_layer );

/**
 * @fn void mk_field_setZIndex ( T_mkField* p_field, uint32_t p_zIndex );
 * @brief Cette fonction configure l'indice de profondeur d'un champ.
 *
 * @param[out] p_field  Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_zIndex Ce paramètre contient l'indice de profondeur du champ. Il évolue de [0 à 0xFFFFFFFF].
 *                      La valeur 0 indique que le champ doit être dessiné en premier, la valeur 0xFFFFFFFF indique
 *                      qu'il doit être dessiné en dernier.
 *                      Si deux objets dans un container possèdent le même indice de profondeur, l'objet dessiné
 *                      en premier est le dernier objet ajouté dans le container.
 *
 * @return Sans objet.
 *
 */

void mk_field_setZIndex ( T_mkField* p_field, uint32_t p_zIndex );

/**
 * @fn void mk_field_setActivity ( T_mkField* p_field, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'un champ.
 *
 * @param[out] p_field    Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_activity Ce paramètre contient l'état du champ.
 *                        Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_field_setActivity ( T_mkField* p_field, uint32_t p_activity );

/**
 * @fn void mk_field_setVisibility ( T_mkField* p_field, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'un champ.
 *
 * @param[out] p_field      Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_visibility Ce paramètre contient l'état du champ.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_field_setVisibility ( T_mkField* p_field, uint32_t p_visibility );

/**
 * @fn void mk_field_setPainter ( T_mkField* p_field, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture d'un champ.
 *
 * @param[out] p_field   Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_painter Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                       T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_field_setPainter ( T_mkField* p_field, T_mkPainter p_painter );

/**
 * @fn void mk_field_setListener ( T_mkField* p_field, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute d'un champ.
 *
 * @param[out] p_field    Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_listener Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                        T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_field_setListener ( T_mkField* p_field, T_mkListener p_listener );

/**
 * @fn void mk_field_setRefresh ( T_mkField* p_field, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'un champ.
 *
 * @param[in,out] p_field    Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]     p_refresh  Ce paramètre contient l'état de rafraichissement du champ. Les valeurs suivantes peuvent être utilisées :
 *                           \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement du champ pendant au moins 'n'
 *                           frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                           \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement du champ. Le compteur de
 *                           rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                           le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_field_setRefresh ( T_mkField* p_field, uint32_t p_refresh );

/**
 * @fn uint32_t mk_field_inside ( T_mkField* p_field, real32_t p_x, real32_t p_y );
 * @brief Cette fonction indique si un point de coordoonée [x, y] est situé à l'intérieur ou à l'extérieur d'un champ.
 *
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 * @param[in]  p_x     Ce paramètre contient la coordonnée x du point à tester [en pixel].
 * @param[in]  p_y     Ce paramètre contient la coordonnée y du point à tester [en pixel].
 *
 * @return Cette fonction retourne la valeur 1 si le point est situé à l'intérieur du champ, sinon la valeur 0.
 *
 */

uint32_t mk_field_inside ( T_mkField* p_field, real32_t p_x, real32_t p_y );

/**
 * @fn uint32_t mk_field_isFocus ( T_mkField* p_field );
 * @brief Cette fonction retourne la valeur de l'attribut focus indiquant si le champ est sélectionné ou non.
 * @param[out] p_field Ce paramètre contient l'adresse d'un champ de type \ref T_mkField.
 *
 * @return Cette fonction retourne les valeurs \ref K_MK_FIELD_STATE_FOCUS ou \ref K_MK_FIELD_STATE_IDLE.
 *
 */

uint32_t mk_field_isFocus ( T_mkField* p_field );

/**
 *
 */

#endif

