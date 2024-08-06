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
* @file mk_display_buttonImage.h
* @brief Déclaration des fonctions publiques dédiées à l'objet 'ButtonImage'.
* @date 10 nov. 2022
*
*/

#ifndef MK_BUTTON_IMAGE_H
#define MK_BUTTON_IMAGE_H

/**
 * @fn void mk_buttonImage_init ( T_mkButtonImage* p_buttonImage );
 * @brief Cette fonction initialise un bouton image.
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 *
 * @return Sans objet.
 * @note La configuration de la fonction d'écoute est de la responsabilité de l'utilisateur (\ref mk_buttonImage_setListener).
 *
 */

void mk_buttonImage_init ( T_mkButtonImage* p_buttonImage );

/**
 * @fn void mk_buttonImage_setChild ( T_mkButtonImage* p_buttonImage, T_mkAddr p_child );
 * @brief Cette fonction configure le descendant d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_child       Ce paramètre contient l'adresse du descendant du bouton image (cf. nota).
 *
 * @return Sans objet.
 *
 * @note Lors de l'héritage, chaque structure configure son pointeur 'child' pour pointer sur son descendant direct.
 *       Une chaine est ainsi formée. Il est alors possible de récupérer l'adresse d'un objet de plus haut niveau
 *       dans les fonctions d'écoutes et de peintures n'ayant accès qu'à une structure \ref T_mkField.
 *
 */

void mk_buttonImage_setChild ( T_mkButtonImage* p_buttonImage, T_mkAddr p_child );

/**
 * @fn void mk_buttonImage_setPosition ( T_mkButtonImage* p_buttonImage, real32_t p_x, real32_t p_y );
 * @brief Cette fonction configure la position d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_x           Ce paramètre contient la coordonnée x du bouton image [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH - 1].
 * @param[in]  p_y           Ce paramètre contient la coordonnée y du bouton image [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT - 1].
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setPosition ( T_mkButtonImage* p_buttonImage, real32_t p_x, real32_t p_y );

/**
 * @fn void mk_buttonImage_setDimension ( T_mkButtonImage* p_buttonImage, uint32_t p_width, uint32_t p_height );
 * @brief Cette fonction configure la hauteur et la largeur d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_width       Ce paramètre contient la largeur du bouton image [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_WIDTH].
 * @param[in]  p_height      Ce paramètre contient la hauteur du bouton image [en pixel].
 *                           Il évolue entre [0 et \ref K_MK_DISPLAY_HEIGHT].
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setDimension ( T_mkButtonImage* p_buttonImage, uint32_t p_width, uint32_t p_height );

/**
 * @fn void mk_buttonImage_setLayer ( T_mkButtonImage* p_buttonImage, uint32_t p_layer );
 * @brief Cette fonction configure le layer d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_layer       Ce paramètre contient le layer où le bouton image doit être dessiné.
 *                           Il peut prendre les valeurs \ref K_MK_GRAPHICS_FOREGROUND ou \ref K_MK_GRAPHICS_BACKGROUND.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setLayer ( T_mkButtonImage* p_buttonImage, uint32_t p_layer );

/**
 * @fn void mk_buttonImage_setVisibility ( T_mkButtonImage* p_buttonImage, uint32_t p_visibility );
 * @brief Cette fonction configure la visibilité d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_visibility  Ce paramètre contient l'état du bouton image.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_VISIBLE ou \ref K_MK_FIELD_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setVisibility ( T_mkButtonImage* p_buttonImage, uint32_t p_visibility );

/**
 * @fn void mk_buttonImage_setActivity ( T_mkButtonImage* p_buttonImage, uint32_t p_activity );
 * @brief Cette fonction configure l'activité d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_activity    Ce paramètre contient l'état du bouton image.
 *                           Il peut prendre les valeurs \ref K_MK_FIELD_ACTIF ou \ref K_MK_FIELD_ACTIF.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setActivity ( T_mkButtonImage* p_buttonImage, uint32_t p_activity );

/**
 * @fn void mk_buttonImage_setBorderVisibility ( T_mkButtonImage* p_buttonImage, uint32_t p_borderVisibility );
 * @brief Cette fonction configure la visibilité de la bordure d'un bouton image.
 *
 * @param[out] p_buttonImage      Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_borderVisibility Ce paramètre contient l'état de la bordure du bouton image.
 *                                Il peut prendre les valeurs \ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setBorderVisibility ( T_mkButtonImage* p_buttonImage, uint32_t p_borderVisibility );

/**
 * @fn void mk_buttonImage_setBorderColor ( T_mkButtonImage* p_buttonImage, uint32_t p_color );
 * @brief Cette fonction configure la couleur de la bordure d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_color       Ce paramètre contient la couleur de la bordure au format ARGB8888.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setBorderColor ( T_mkButtonImage* p_buttonImage, uint32_t p_color );

/**
 * @fn void mk_buttonImage_setImage ( T_mkButtonImage* p_buttonImage, T_mkBMPFile* p_bitmap );
 * @brief Cette fonction configure le fichier image d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_bitmap      Ce paramètre contient l'adresse d'un fichier image de type \ref T_mkBMPFile.
 *                           Le fichier doit être ouvert et déployé en mémoire en utilisant les fonctions
 *                           \ref mk_bmp_open, \ref mk_bmp_load ou \ref mk_bmp_load2D.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setImage ( T_mkButtonImage* p_buttonImage, T_mkBMPFile* p_bitmap );

/**
 * @fn void mk_buttonImage_setTextBuffer ( T_mkButtonImage* p_buttonImage, uint32_t p_buffer );
 * @brief Cette fonction configure la chaine de caractères d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_buffer      Ce paramètre contient l'adresse de la chaine de caractères à afficher.
 *                           Le format de la chaine de caractères (\ref K_MK_FONT_ASCII, ...) dépend de la
 *                           fonction de peinture.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setTextBuffer ( T_mkButtonImage* p_buttonImage, T_str8 p_buffer );

/**
 * @fn void mk_buttonImage_setTextStyle ( T_mkButtonImage* p_buttonImage, T_mkTextStyle* p_style );
 * @brief Cette fonction configure le style de la chaine de caractères d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_style       Ce paramètre contient l'adresse d'un style de type \ref T_mkTextStyle.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setTextStyle ( T_mkButtonImage* p_buttonImage, T_mkTextStyle* p_style );

/**
 * @fn void mk_buttonImage_setPainter ( T_mkButtonImage* p_buttonImage, T_mkPainter p_painter );
 * @brief Cette fonction configure la fonction de peinture d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_painter     Ce paramètre contient l'adresse d'une fonction de peinture possédant le prototype suivant :
 *                           T_mkCode painter ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, uint32_t p_mkFrameNumber );
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setPainter ( T_mkButtonImage* p_buttonImage, T_mkPainter p_painter );

/**
 * @fn void mk_buttonImage_setListener ( T_mkButtonImage* p_buttonImage, T_mkListener p_listener );
 * @brief Cette fonction configure la fonction d'écoute d'un bouton image.
 *
 * @param[out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]  p_listener    Ce paramètre contient l'adresse d'une fonction d'écoute possédant le prototype suivant :
 *                           T_mkCode listener ( T_mkContainer* p_mkContainer, T_mkField* p_mkField, T_mkCtrlId p_mkAppCtrlId, T_mkAddr p_mkAppCtrl, T_mkCtrlEvent p_mkEvtCtrl, uint32_t p_mkCtrlId );
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setListener ( T_mkButtonImage* p_buttonImage, T_mkListener p_listener );

/**
 * @fn void mk_buttonImage_setRefresh ( T_mkButtonImage* p_buttonImage, uint32_t p_refresh );
 * @brief Cette fonction active ou désactive le rafraichissement d'un bouton image.
 *
 * @param[in,out] p_buttonImage Ce paramètre contient l'adresse d'un bouton image de type \ref T_mkButtonImage.
 * @param[in]     p_refresh     Ce paramètre contient l'état de rafraichissement du bouton image. Les valeurs suivantes peuvent être utilisées :
 *                              \li \ref K_MK_FIELD_REFRESH_ENABLED : active le rafraichissement du bouton image pendant au moins 'n'
 *                              frames. La valeur 'n' est le nombre de buffers graphiques utilisés par le moteur.
 *                              \li \ref K_MK_FIELD_REFRESH_DISABLED : désactive le rafraichissement du bouton image. Le compteur de
 *                              rafraichissement est décrémenté d'une unité à chaque appel de la fonction. Lorsque
 *                              le compteur atteint la valeur nulle, la désactivation est effective.
 *
 * @return Sans objet.
 *
 */

void mk_buttonImage_setRefresh ( T_mkButtonImage* p_buttonImage, uint32_t p_refresh );

/**
 * @fn T_mkCode mk_buttonImage_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture par défaut d'un bouton image. Elle est exécutée à intervalle régulier par le moteur graphique.
 *        Elle affiche l'image et la bordure du bouton.
 *
 * @param[in] p_container    Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field        Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de
 *                           type \ref T_mkButtonImage. L'adresse du bouton image peut être récupérée en utilisant l'attribut 'child'.
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

T_mkCode mk_buttonImage_defaultPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 * @fn T_mkCode mk_buttonImage_defaultTextPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );
 * @brief Cette fonction est la fonction de peinture d'un bouton image. Elle est exécutée à intervalle régulier par le moteur graphique.
 *        Elle affiche l'image, la bordure et le texte du bouton.
 *
 * @param[in] p_container    Ce paramètre contient l'adresse du container propriétaire du champ p_field.
 * @param[in] p_field        Ce paramètre contient l'adresse du champ \ref T_mkField présent dans la structure de
 *                           type \ref T_mkButtonImage. L'adresse du bouton image peut être récupérée en utilisant l'attribut 'child'.
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

T_mkCode mk_buttonImage_defaultTextPainter ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber );

/**
 *
 */

#endif


