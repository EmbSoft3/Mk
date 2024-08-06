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
* @file mk_display_progressBar.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'ProgressBar'.
* @date 14 oct. 2023
*
*/

#ifndef MK_DISPLAY_PROGRESSBAR_H
#define MK_DISPLAY_PROGRESSBAR_H

/**
 * @fn void mk_progressBar_init ( T_mkProgressBar* p_progressBar );
 * @brief Cette fonction initialise une barre de progression.
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_init ( T_mkProgressBar* p_progressBar );

/**
 * @fn void mk_progressBar_setChild ( T_mkProgressBar* p_progressBar, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_child       Ce paramètre contient l'adresse du descendant de la barre de progression (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_progressBar_setChild ( T_mkProgressBar* p_progressBar, T_mkAddr p_child );

/**
 * @fn void mk_progressBar_setPosition ( T_mkProgressBar* p_progressBar, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_x           Ce paramètre contient la coordonnée x de la barre de progression [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y           Ce paramètre contient la coordonnée y de la barre de progression [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setPosition ( T_mkProgressBar* p_progressBar, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_progressBar_setDimension ( T_mkProgressBar* p_progressBar, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_width       Ce paramètre contient la largeur de la barre de progression [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height      Ce paramètre contient la hauteur de la barre de progression [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setDimension ( T_mkProgressBar* p_progressBar, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_progressBar_setLayer ( T_mkProgressBar* p_progressBar, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_layer       Ce paramètre contient le layer où la barre de progression doit être dessinée.
 *                           Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setLayer ( T_mkProgressBar* p_progressBar, uint32_t p_layer );

/**
 * @fn void mk_progressBar_setVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_visibility  Ce paramètre contient la visibilité de la barre de progression.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );

/**
 * @fn void mk_progressBar_setActivity ( T_mkProgressBar* p_progressBar, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_activity    Ce paramètre contient l'état de la barre de progression.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setActivity ( T_mkProgressBar* p_progressBar, uint32_t p_activity );

/**
 * @fn void mk_progressBar_setPainter ( T_mkProgressBar* p_progressBar, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_painter     Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                           T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setPainter ( T_mkProgressBar* p_progressBar, T_mkPainter p_painter );

/**
 * @fn void mk_progressBar_setListener ( T_mkProgressBar* p_progressBar, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_listener    Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                           T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setListener ( T_mkProgressBar* p_progressBar, T_mkListener p_listener );

/**
 * @fn void mk_progressBar_setRefresh ( T_mkProgressBar* p_progressBar, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'une barre de progression.
 *
 * @param[in,out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]     p_refresh     Ce paramètre contient l'état de rafraichissement de la barre de progression. Les valeurs suivantes peuvent être utilisées :
 *                              \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement de la barre de progression pendant au moins 'n'
 *                              frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                              \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement de la barre de progression. Le compteur de
 *                              rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                              le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setRefresh ( T_mkProgressBar* p_progressBar, uint32_t p_refresh );

/**
 * @fn void mk_progressBar_setBackgroundColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );
 * @brief Cette fonction configure la couleur d'arrière plan d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_color       Ce paramètre contient la couleur de l'arrière plan au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setBackgroundColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );

/**
 * @fn void mk_progressBar_setBackgroundVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de l'arrière plan d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_visibility  Ce paramètre contient l'état de l'arrière plan d'une barre de progression.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setBackgroundVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );

/**
 * @fn void mk_progressBar_setForegroundColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );
 * @brief Cette fonction configure la couleur du premier plan d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_color       Ce paramètre contient la couleur du premier plan au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setForegroundColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );

/**
 * @fn void mk_progressBar_setForegroundVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité du premier plan d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_visibility  Ce paramètre contient l'état du premier plan d'une barre de progression.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setForegroundVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );

/**
 * @fn void mk_progressBar_setBorderColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );
 * @brief Cette fonction configure la couleur de la bordure d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_color       Ce paramètre contient la couleur de la bordure au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setBorderColor ( T_mkProgressBar* p_progressBar, uint32_t p_color );

/**
 * @fn void mk_progressBar_setBorderVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de la bordure d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_visibility  Ce paramètre contient l'état de la bordure d'une barre de progression.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setBorderVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );

/**
 * @fn void mk_progressBar_setBorderWidth ( T_mkProgressBar* p_progressBar, uint32_t p_width );
 * @brief Cette fonction configure la largeur de la bordure d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_width       Ce paramètre contient la largeur de la bordure [en pixel].
 *                           La largeur et la hauteur de la barre de progression doit être supérieure ou égale à 2
 *                           fois la largeur de la bordure.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setBorderWidth ( T_mkProgressBar* p_progressBar, uint32_t p_width );

/**
 * @fn void mk_progressBar_setTextBuffer ( T_mkProgressBar* p_progressBar, T_str8 p_buffer );
 * @brief Cette fonction configure l'adresse du buffer stockant la chaine de caractères à afficher dans une barre
 *        de progression. Si aucun buffer n'est spécifié, la fonction de peinture par défaut affiche le pourcentage
 *        de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_buffer      Ce paramètre contient l'adresse d'un buffer stockant une chaine de caractères.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setTextBuffer ( T_mkProgressBar* p_progressBar, T_str8 p_buffer );

/**
 * @fn void mk_progressBar_setTextVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité de la chaine de caractères d'une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_visibility  Ce paramètre contient la visibilité de la chaine de caractères.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setTextVisibility ( T_mkProgressBar* p_progressBar, uint32_t p_visibility );

/**
 * @fn void mk_progressBar_setTextStyle ( T_mkProgressBar* p_progressBar, T_mkTextStyle* p_style );
 * @brief Cette fonction configure le style de la chaine de caractères affichée dans une barre de progression.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_style       Ce paramètre contient l'adresse d'un style de type \ref T_mkTextStyle.
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setTextStyle ( T_mkProgressBar* p_progressBar, T_mkTextStyle* p_style );

/**
 * @fn void mk_progressBar_setValue ( T_mkProgressBar* p_progressBar, uint32_t p_value );
 * @brief Cette fonction configure le pourcentage de progression de la barre.
 *
 * @param[out] p_progressBar Ce paramètre contient l'adresse d'une barre de progression de type \ref T_mkProgressBar.
 * @param[in]  p_value       Ce paramètre contient le pourcentage de progression de la barre. Il évolue entre [0 et 100].
 *
 * @return Sans objet.
 *
 */

void mk_progressBar_setValue ( T_mkProgressBar* p_progressBar, uint32_t p_value );

/**
 * @fn T_mkCode mk_progressBar_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut d'une barre de progression de type \ref T_mkProgressBar. Elle est exécutée
 *        à intervalle régulier par le moteur graphique.
 *
 * @param[in] p_container    Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field        Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkProgressBar.
 *                           L'adresse de la barre de progression peut être récupérée en utilisant l'attribut 'child'.
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

T_mkCode mk_progressBar_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif




