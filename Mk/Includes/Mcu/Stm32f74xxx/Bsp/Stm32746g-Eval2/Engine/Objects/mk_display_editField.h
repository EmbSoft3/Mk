/**
*
* @copyright Copyright (C) 2022 RENARD Mathieu. All rights reserved.
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
* @file mk_display_editField.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'EditField'.
* @date 1 déc. 2022
*
*/

#ifndef MK_DISPLAY_EDITFIELD_H
#define MK_DISPLAY_EDITFIELD_H

/**
 * @fn void mk_editField_init ( T_mkEditField* p_editField );
 * @brief Cette fonction initialise une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Sans objet.
 *
 */

void mk_editField_init ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_setChild ( T_mkEditField* p_editField, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_child     Ce paramètre contient l'adresse du descendant de la boite d'édition (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Dans l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_editField_setChild ( T_mkEditField* p_editField, T_mkAddr p_child );

/**
 * @fn void mk_editField_setPosition ( T_mkEditField* p_editField, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_x         Ce paramètre contient la coordonnée x de la boite d'édition [en pixel].
 *                         Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y         Ce paramètre contient la coordonnée y de la boite d'édition [en pixel].
 *                         Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_editField_setPosition ( T_mkEditField* p_editField, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_editField_setDimension ( T_mkEditField* p_editField, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_width     Ce paramètre contient la largeur de la boite d'édition [en pixel].
 *                         Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height    Ce paramètre contient la hauteur de la boite d'édition [en pixel].
 *                         Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_editField_setDimension ( T_mkEditField* p_editField, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_editField_setLayer ( T_mkEditField* p_editField, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_layer     Ce paramètre contient le layer où la boite d'édition doit être dessinée.
 *                         Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setLayer ( T_mkEditField* p_editField, uint32_t p_layer );

/**
 * @fn void mk_editField_setVisibility ( T_mkEditField* p_editField, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'une boite d'édition.
 *
 * @param[out] p_editField  Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_visibility Ce paramètre contient l'état de la boite d'édition.
 *                          Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setVisibility ( T_mkEditField* p_editField, uint32_t p_visibility );

/**
 * @fn void mk_editField_setActivity ( T_mkEditField* p_editField, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_activity  Ce paramètre contient l'état de la boite d'édition.
 *                         Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_INACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setActivity ( T_mkEditField* p_editField, uint32_t p_activity );

/**
 * @fn void mk_editField_setBorderVisibility ( T_mkEditField* p_editField, uint32_t p_borderVisibility );
 * @brief Cette fonction configure la visibilité de la bordure d'une boite d'édition.
 *
 * @param[out] p_editField        Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_borderVisibility Ce paramètre contient l'état de la bordure de la boite d'édition.
 *                                Il peut prendre les valeurs \ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setBorderVisibility ( T_mkEditField* p_editField, uint32_t p_borderVisibility );

/**
 * @fn void mk_editField_setBorderColor ( T_mkEditField* p_editField, uint32_t p_color );
 * @brief Cette fonction configure la couleur de la bordure d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_color     Ce paramètre contient la couleur de la bordure au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setBorderColor ( T_mkEditField* p_editField, uint32_t p_color );

/**
 * @fn void mk_editField_setBackgroundVisibility ( T_mkEditField* p_editField, uint32_t p_backgroundVisibility );
 * @brief Cette fonction configure la visibilité de l'arrière plan d'une boite d'édition.
 *
 * @param[out] p_editField            Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_backgroundVisibility Ce paramètre contient l'état de l'arrière plan de la boite d'édition.
 *                                    Il peut prendre les valeurs \ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setBackgroundVisibility ( T_mkEditField* p_editField, uint32_t p_backgroundVisibility );

/**
 * @fn void mk_editField_setBackgroundColor ( T_mkEditField* p_editField, uint32_t p_color );
 * @brief Cette fonction configure la couleur de l'arrière plan d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_color     Ce paramètre contient la couleur de l'arrière plan au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setBackgroundColor ( T_mkEditField* p_editField, uint32_t p_color );

/**
 * @fn void mk_editField_setCursorVisibility ( T_mkEditField* p_editField, uint32_t p_cursorVisibility );
 * @brief Cette fonction configure la visibilité du curseur d'une boite d'édition.
 *
 * @param[out] p_editField        Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_cursorVisibility Ce paramètre contient l'état du curseur de la boite d'édition.
 *                                Il peut prendre les valeurs \ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setCursorVisibility ( T_mkEditField* p_editField, uint32_t p_cursorVisibility );

/**
 * @fn void mk_editField_setCursorColor ( T_mkEditField* p_editField, uint32_t p_color );
 * @brief Cette fonction configure la couleur du curseur d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_color     Ce paramètre contient la couleur du curseur au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setCursorColor ( T_mkEditField* p_editField, uint32_t p_color );

/**
 * @fn void mk_editField_setTextBuffer ( T_mkEditField* p_editField, T_mkAddr p_buffer, uint32_t p_bufferSize );
 * @brief Cette fonction configure le buffer d'une boite d'édition.
 *
 * @param[out] p_editField  Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_buffer     Ce paramètre contient l'adresse d'un buffer.
 * @param[in]  p_bufferSize Ce paramètre contient la taille du buffer [en octets]. La taille minimale est de 1 octet.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setTextBuffer ( T_mkEditField* p_editField, T_mkAddr p_buffer, uint32_t p_bufferSize );

/**
 * @fn T_mkAddr mk_editField_getText ( T_mkEditField* p_editField );
 * @brief Cette fonction retourne l'adresse du buffer d'une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Cette fonction retourne l'adresse du buffer de la boite d'édition.
 *
 */

T_mkAddr mk_editField_getText ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_setTextColor ( T_mkEditField* p_editField, uint32_t p_color );
 * @brief Cette fonction configure la couleur du texte d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_color     Ce paramètre contient la couleur du texte au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setTextColor ( T_mkEditField* p_editField, uint32_t p_color );

/**
 * @fn void mk_editField_setFont ( T_mkTextField* p_textField, T_mkFont* p_font );
 * @brief Cette fonction configure la police de caractères d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_font      Ce paramètre contient l'adresse d'une police de caractères de type \ref T_mkFont.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setFont ( T_mkEditField* p_editField, T_mkFont* p_font );

/**
 * @fn void mk_editField_setTextEncoding ( T_mkEditField* p_editField, T_mkFontUnicode p_encoding );
 * @brief Cette fonction configure l'encodage des caractères d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_encoding  Ce paramètre contient l'encodage de la chaine de caractères.
 *                         Il peut prendre les valeurs \ref K_MK_FONT_ASCII, \ref K_MK_FONT_UTF8 à \ref K_MK_FONT_UTF32
 *
 * @return Sans objet.
 *
 */

void mk_editField_setTextEncoding ( T_mkEditField* p_editField, T_mkFontUnicode p_encoding );

/**
 * @fn void mk_editField_setTextAlignment ( T_mkEditField* p_editField, T_mkTextAlignment p_verticalAlignment, T_mkTextAlignment p_horizontalAlignment );
 * @brief Cette fonction configure la justification du texte d'une boite d'édition.
 *
 * @param[out] p_editField           Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_verticalAlignment   Ce paramètre contient la justification verticale du texte.
 *                                   Il peut prendre les valeurs \ref K_MK_TEXT_TOP_JUSTIFIED, \ref K_MK_TEXT_CENTER_JUSTIFIED et \ref K_MK_TEXT_DOWN_JUSTIFIED
 * @param[in]  p_horizontalAlignment Ce paramètre contient la justification horizontale du texte.
 *                                   Il peut prendre les valeurs \ref K_MK_TEXT_LEFT_JUSTIFIED, \ref K_MK_TEXT_CENTER_JUSTIFIED et \ref K_MK_TEXT_RIGHT_JUSTIFIED
 *
 * @return Sans objet.
 *
 */

void mk_editField_setTextAlignment ( T_mkEditField* p_editField, T_mkTextAlignment p_verticalAlignment, T_mkTextAlignment p_horizontalAlignment );

/**
 * @fn void mk_editField_setMargin ( T_mkEditField* p_editField, uint32_t p_marginTop, uint32_t p_marginBottom, uint32_t p_marginRight, uint32_t p_marginLeft );
 * @brief Cette fonction configure la valeur des 4 marges d'une boite d'édition.
 *
 * @param[out] p_editField    Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_marginTop    Ce paramètre contient la valeur de la marge haute [en pixel].
 * @param[in]  p_marginBottom Ce paramètre contient la valeur de la marge basse [en pixel].
 * @param[in]  p_marginRight  Ce paramètre contient la valeur de la marge droite [en pixel].
 * @param[in]  p_marginLeft   Ce paramètre contient la valeur de la marge gauche [en pixel].
 *
 * @return Sans objet.
 *
 * @note Les sommes 'p_marginRight + p_marginLeft' et 'p_marginTop + p_marginBottom' ne doivent pas être supérieure à la taille de la boite d'édition
 *       (largeur et hauteur).
 *
 */

void mk_editField_setMargin ( T_mkEditField* p_editField, uint32_t p_marginTop, uint32_t p_marginBottom, uint32_t p_marginRight, uint32_t p_marginLeft );

/**
 * @fn void mk_editField_enableScrolling ( T_mkEditField* p_editField );
 * @brief Cette fonction active le scrolling vertical d'une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Sans objet.
 *
 */

void mk_editField_enableScrolling ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_disableScrolling ( T_mkEditField* p_editField );
 * @brief Cette fonction désactive le scrolling vertical d'une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Sans objet.
 *
 */

void mk_editField_disableScrolling ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_enableWriteProtect ( T_mkEditField* p_editField );
 * @brief Cette fonction active la protection en écriture d'une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Sans objet.
 *
 */

void mk_editField_enableWriteProtect ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_disableWriteProtect ( T_mkEditField* p_editField );
 * @brief Cette fonction désactive la protection en écriture d'une boite d'édition.
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 *
 * @return Sans objet.
 *
 */

void mk_editField_disableWriteProtect ( T_mkEditField* p_editField );

/**
 * @fn void mk_editField_setCache ( T_mkEditField* p_editField, T_mkAddr p_addr );
 * @brief Cette fonction configure l'adresse du cache d'une boite d'édition. Le cache est un buffer
 *        stockant les pixels des objets de la boite. Son utilisation peut réduire le temps de traitement de la
 *        fonction de peinture. En effet, si les données contenues dans la boite n'ont pas été modifiées, une copie de pixels
 *        est réalisée du cache vers le buffer graphique. Les traitements longs de la boite d'édition ne sont pas
 *        réalisés.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_addr      Ce paramètre contient l'adresse du cache de la boite d'édition.
 *                         Sa taille est définie de la manière suivante : width * height * 32 [BitsPerPixel].
 *
 * @return Sans objet.
 *
 */

void mk_editField_setCache ( T_mkEditField* p_editField, T_mkAddr p_addr );

/**
 * @fn void mk_editField_setPainter ( T_mkEditField* p_editField, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_painter   Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                         T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_editField_setPainter ( T_mkEditField* p_editField, T_mkPainter p_painter );

/**
 * @fn void mk_editField_setListener ( T_mkEditField* p_editField, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute d'une boite d'édition.
 *
 * @param[out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]  p_listener  Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                         T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_editField_setListener ( T_mkEditField* p_editField, T_mkListener p_listener );

/**
 * @fn void mk_editField_setRefresh ( T_mkEditField* p_editField, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'une boite d'édition.
 *
 * @param[in,out] p_editField Ce paramètre contient l'adresse d'une boite d'édition de type \ref T_mkEditField.
 * @param[in]     p_refresh   Ce paramètre contient l'état de rafraichissement de la boite d'édition. Les valeurs suivantes peuvent être utilisées :
 *                            \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement de la boite d'édition pendant au moins 'n'
 *                            frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                            \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement de la boite d'édition. Le compteur de
 *                            rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                            le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setRefresh ( T_mkEditField* p_editField, uint32_t p_refresh );

/**
 * @fn T_mkCode mk_editField_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut d'une boite d'édition. Elle est exécutée à intervalle régulier par le moteur graphique.
 *
 * @param[in] p_container   Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field       Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de type \ref T_mkEditField.
 *                          L'adresse de la boite d'édition peut être récupérée en utilisant l'attribut 'child'.
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

T_mkCode mk_editField_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_editField_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 * @brief Cette fonction est la fonction d'écoute par défaut d'une boite d'édition. Elle est exécutée par le moteur graphique lorsqu'un événement se produit.\n
 *        Cette fonction actualise la boite d'édition en fonction des entrées clavier et souris réalisées par l'utilisateur.
 *
 * @param[in] p_mkContainer Ce paramètre contient l'adresse du container propriétaire du champ p_mkField.
 * @param[in] p_mkField     Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la boite d'édition.
 *                          L'adresse de la boite peut être récupérée en utilisant les attributs child.
 * @param[in] p_mkAppCtrlId Ce paramètre contient l'identifiant du contrôle applicatif ayant déclenché l'événement (\ref T_mkCtrlId).
 * @param[in] p_mkAppCtrl   Ce paramètre contient l'adresse du contrôle applicatif ayant déclenché l'événement (\ref T_mkMouse, \ref T_mkKeyboard, ...). Celui-ci peut être nul.
 * @param[in] p_mkEvtCtrl   Ce paramètre contient le type de l'événement (\ref T_mkCtrlEvent).
 * @param[in] p_mkCtrlId    Ce paramètre contient l'identifiant de l'événement.
 *
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction d'écoute a été exécutée correctement.
 *         \li \ref K_MK_ERROR_PARAM : l'exécution de la fonction d'écoute a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_editField_defaultListener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );

/**
 *
 */

#endif



