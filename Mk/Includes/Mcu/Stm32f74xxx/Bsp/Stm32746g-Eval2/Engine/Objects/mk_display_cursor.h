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
* @file mk_display_cursor.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'Cursor'.
* @date 2 déc. 2019
*
*/

#ifndef MK_DISPLAY_CURSOR_H
#define MK_DISPLAY_CURSOR_H

/**
 * @fn void mk_cursor_init ( T_mkCursor* p_cursor );
 * @brief Cette fonction initialise un curseur.
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_init ( T_mkCursor* p_cursor );

/**
 * @fn void mk_cursor_setChild ( T_mkCursor* p_cursor, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'un curseur.
 *
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_child  Ce paramètre contient l'adresse du descendant du curseur (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_cursor_setChild ( T_mkCursor* p_cursor, T_mkAddr p_child );

/**
 * @fn void mk_cursor_setPosition ( T_mkCursor* p_cursor, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'un curseur.
 *
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_x      Ce paramètre contient la coordonnée x du curseur [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y      Ce paramètre contient la coordonnée y du curseur [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setPosition ( T_mkCursor* p_cursor, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_cursor_setDimension ( T_mkCursor* p_cursor, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'un curseur.
 *
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_width  Ce paramètre contient la largeur du curseur [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height Ce paramètre contient la hauteur du curseur [en pixel].
 *                      Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setDimension ( T_mkCursor* p_cursor, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_cursor_setLayer ( T_mkCursor* p_cursor, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'un curseur.
 *
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_layer  Ce paramètre contient le layer où le curseur doit être dessiné.
 *                      Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setLayer ( T_mkCursor* p_cursor, uint32_t p_layer );

/**
 * @fn void mk_cursor_setVisibility ( T_mkCursor* p_cursor, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'un curseur.
 *
 * @param[out] p_cursor     Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_visibility Ce paramètre contient l'état du curseur.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setVisibility ( T_mkCursor* p_cursor, uint32_t p_visibility );

/**
 * @fn void mk_cursor_setActivity ( T_mkCursor* p_cursor, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'un curseur.
 *
 * @param[out] p_cursor   Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_activity Ce paramètre contient l'état du curseur.
 *                        Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setActivity ( T_mkCursor* p_cursor, uint32_t p_activity );

/**
 * @fn void mk_cursor_setBitmap ( T_mkCursor* p_cursor, T_mkAddr p_bitmap );
 * @brief Cette fonction configure le bitmap d'un curseur. Le bitmap doit être au format ARGB8888.
 *
 * @param[out] p_cursor Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_bitmap Ce paramètre contient l'adresse du bitmap (format ARGB8888) à configurer.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setBitmap ( T_mkCursor* p_cursor, T_mkAddr p_bitmap );

/**
 * @fn void mk_cursor_setPainter ( T_mkCursor* p_cursor, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture d'un curseur.
 *
 * @param[out] p_cursor  Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]  p_painter Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                       T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setPainter ( T_mkCursor* p_cursor, T_mkPainter p_painter );

/**
 * @fn void mk_cursor_setRefresh ( T_mkCursor* p_cursor, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'un curseur.
 *
 * @param[in,out] p_cursor  Ce paramètre contient l'adresse d'un curseur de type \ref T_mkCursor.
 * @param[in]     p_refresh Ce paramètre contient l'état de rafraichissement du curseur. Les valeurs suivantes peuvent être utilisées :
 *                          \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement du curseur pendant au moins 'n'
 *                          frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                          \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement du curseur. Le compteur de
 *                          rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                          le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_cursor_setRefresh ( T_mkCursor* p_cursor, uint32_t p_refresh );

/**
 * @fn T_mkCode mk_cursor_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut d'un curseur. Elle est exécutée à intervalle régulier par le moteur graphique.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkCursor.
 *                          L'adresse du curseur peut être récupérée en utilisant l'attribut 'child'.
 * @param[in] p_frameNumber Ce paramètre contient l'index de la frame en cours de rafraichissement.
 *                          Il évolue entre [0 à \ref K_MK_DISPLAY_FRAMERATE - 1].
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le traitement de la fonction de peinture a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le traitement de la fonction de peinture a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le traitement de la fonction de peinture a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : le traitement de la fonction de peinture a échoué car un timeout s'est produit.
 *
 */

T_mkCode mk_cursor_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif

