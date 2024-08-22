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
* @file mk_display_editField_private.h
* @brief Déclaration des fonctions privées dédiées à l'objet 'EditField'.
* @date 12 déc. 2022
*
*/

#ifndef MK_DISPLAY_EDITFIELD_PRIVATE_H
#define MK_DISPLAY_EDITFIELD_PRIVATE_H

/**
 * @fn T_mkCode mk_editField_setAttribute ( T_mkEditField* p_editField, T_mkVect2D p_v1, T_mkVect2D p_v2, T_mkVect2Di* p_topLeft, T_mkVect2Di* p_downRight, T_str8 p_windowBaseAddr );
 * @brief Cette fonction configure la valeur des attributs suivants d'une boite d'édition :
 *        \li p_topLeft : coordonnée actualisée en fonction des marges et des vecteur p_v1 et p_v2
 *        \li p_downRight : coordonnée actualisée en fonction des marges et des vecteur p_v1 et p_v2
 *        \li p_editField->windowNumberOfRow : nombre de lignes pouvant être affichés dans la fenêtre.
 *        \li p_editField->windowCurrentNumberOfRow : nombre de lignes actuellement occupées dans la fenêtre
 *
 * @param[in,out] p_editField      Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in]     p_v1             Ce paramètre contient la coordonnée 'p_v1' de la boite d'édition.
 * @param[in]     p_v2             Ce paramètre contient la coordonnée 'p_v2' de la boite d'édition.
 * @param[out]    p_topLeft        Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[out]    p_downRight      Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in]     p_windowBaseAddr Ce paramètre contient l'adresse du début de la fenêtre dans la chaine de caractères.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les attributs ont été configurés correctement.
 *         \li \ref K_MK_ERROR_PARAM : un ou plusieurs attributs n'ont pas été configurés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_editField_setAttribute ( T_mkEditField* p_editField, T_mkVect2D p_v1, T_mkVect2D p_v2, T_mkVect2Di* p_topLeft, T_mkVect2Di* p_downRight, T_str8 p_windowBaseAddr );

/**
 * @fn void mk_editField_setCursorVector ( T_mkEditField* p_editField, T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_str8 p_windowBaseAddr );
 * @brief Cette fonction configure les coordonnées [x, y] du vecteur 'p_editField->cursorVect' d'une boite d'édition.
 *
 * @param[in,out] p_editField      Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in]     p_v1             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[in]     p_v2             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in]     p_windowBaseAddr Ce paramètre contient l'adresse du début de la fenêtre dans la chaine de caractères.
 *
 * @return Sans objet.
 *
 */

void mk_editField_setCursorVector ( T_mkEditField* p_editField, T_mkVect2Di* p_v1, T_mkVect2Di* p_v2, T_str8 p_windowBaseAddr );

/**
 * @fn uint32_t mk_editField_inside ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_str8 p_windowBaseAddr, uint32_t p_cursorPointer );
 * @brief Cette fonction indique si le curseur est à l'intérieur de la fenêtre ou non.
 *
 * @param[in] p_editField      Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in] p_v1             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[in] p_v2             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in] p_windowBaseAddr Ce paramètre contient l'adresse du début de la fenêtre dans la chaine de caractères.
 * @param[in] p_cursorPointer  Ce paramètre contient l'offset du curseur dans la fenêtre affichée [en caractères].
 *
 * @return Cette fonction retourne la valeur 1 si le curseur est situé dans la fenêtre, sinon la valeur 0.
 *
 */

uint32_t mk_editField_inside ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_str8 p_windowBaseAddr, uint32_t p_cursorPointer );

/**
 * @fn T_str8 mk_editField_getWindowAddr ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_str8 p_strAddr, uint32_t p_row, uint32_t* p_cursorOffset );
 * @brief Cette fonction retourne l'adresse marquant le début de la fenêtre dans la chaine de caractères.
 *
 * @param[in]  p_editField     Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in]  p_v1            Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[in]  p_v2            Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in]  p_strAddr       Ce paramètre contient l'adresse du début de la chaine de caractères.
 * @param[in]  p_row           Ce paramètre contient l'index de la première ligne de la fenêtre dans la chaine de caractères [en ligne].
 * @param[out] p_cursorOffset  Ce paramètre contient la nouvelle offset de curseur [en caractères]. Celui-ci est placé au début de la fenêtre.
 *
 * @return Cette fonction retourne l'adresse marquant le début de la fenêtre dans la chaine de caractères.
 *
 */

T_str8 mk_editField_getWindowAddr ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_str8 p_strAddr, uint32_t p_row, uint32_t* p_cursorOffset );


/**
 * @fn uint32_t mk_editField_getCursorOffsetUp ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_mkVect2Di p_cursorVector, T_str8 p_strAddr, uint32_t p_row );
 * @brief Cette fonction retourne l'offset [en caractères] du curseur suite à l'appui sur la touche 'UpArrow'.
 *
 * @param[in] p_editField    Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in] p_v1           Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[in] p_v2           Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in] p_cursorVector Ce paramètre contient les coordonnées [x, y] du curseur.
 * @param[in] p_strAddr      Ce paramètre contient l'adresse du début de la chaine de caractères.
 * @param[in] p_row          Ce paramètre contient l'index de la première ligne de la fenêtre dans la chaine de caractères [en ligne].
 *
 * @return Cette fonction retourne la nouvelle valeur de l'offset du curseur dans la fenêtre [en caractères].
 *
 */

uint32_t mk_editField_getCursorOffsetUp ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_mkVect2Di p_cursorVector, T_str8 p_strAddr, uint32_t p_row );

/**
 * @fn uint32_t mk_editField_getCursorOffsetDown ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_mkVect2Di p_cursorVector, T_str8 p_windowBaseAddr );
 * @brief Cette fonction retourne l'offset [en caractères] du curseur suite à l'appui sur la touche 'BottomArrow'.
 *
 * @param[in] p_editField      Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 * @param[in] p_v1             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'TopLeft'.
 * @param[in] p_v2             Ce paramètre contient l'adresse d'un vecteur contenant la coordonnée 'BottomRight'.
 * @param[in] p_cursorVector   Ce paramètre contient les coordonnées [x, y] du curseur.
 * @param[in] p_windowBaseAddr Ce paramètre contient l'adresse du début de la chaine de caractères.
 *
 * @return Cette fonction retourne la nouvelle valeur de l'offset du curseur dans la fenêtre [en caractères].
 *
 */

uint32_t mk_editField_getCursorOffsetDown ( T_mkEditField* p_editField, T_mkVect2Di p_v1, T_mkVect2Di p_v2, T_mkVect2Di p_cursorVector, T_str8 p_windowBaseAddr );

/**
 * @fn T_mkCode mk_editField_handleEnd ( T_mkEditField* p_editField );
 * @brief Cette fonction configure les attributs de la boite d'édition afin d'afficher la fin de la chaine de caractères.
 *        Le curseur est déplacé au début de la fenêtre.
 * @param[in,out] p_editField Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les attributs ont été configurés.
 *         \li \ref K_MK_ERROR_PARAM : les attributs n'ont pas été configurés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_editField_handleEnd ( T_mkEditField* p_editField );

/**
 * @fn T_mkCode mk_editField_handleScrolling ( T_mkEditField* p_editField );
 * @brief Cette fonction configure les attributs de la boite d'édition afin d'afficher la fin de la chaine de caractères.
 *        Le curseur est déplacé à la fin de la fenêtre.
 * @param[in,out] p_editField Ce paramètre contient l'adresse d'une structure de type \ref T_mkEditField.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : les attributs ont été configurés.
 *         \li \ref K_MK_ERROR_PARAM : les attributs n'ont pas été configurés car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_editField_handleScrolling ( T_mkEditField* p_editField );

/**
 *
 */

#endif

