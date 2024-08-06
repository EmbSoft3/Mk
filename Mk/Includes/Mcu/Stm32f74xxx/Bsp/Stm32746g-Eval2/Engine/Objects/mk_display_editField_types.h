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
* @file mk_display_editField_types.h
* @brief Déclaration des types dédiés à l'objet 'EditField'.
* @date 1 déc. 2022
*
*/

#ifndef MK_DISPLAY_EDITFIELD_TYPES_H
#define MK_DISPLAY_EDITFIELD_TYPES_H

/**
 * @struct T_mkEditField
 * @brief Déclaration de la structure T_mkEditField.
 */

typedef struct T_mkEditField T_mkEditField;
struct T_mkEditField
{
   T_mkField field;                          /*!< Ce membre contient un champ de type \ref T_mkField (héritage). */
   T_mkAddr child;                           /*!< Ce membre contient l'adresse du descendant de la boite d'édition (héritage). */
   T_mkAddr strAddr;                         /*!< Ce membre contient l'adresse du buffer stockant la chaine de caractères à afficher dans la boite d'édition. */
   uint32_t maxStrSize;                      /*!< Ce membre contient la taille du buffer stockant la chaine de caractères à afficher dans la boite d'édition. */
   T_mkAddr cache;                           /*!< Ce membre contient l'adresse du cache de la boite d'édition. */
   T_mkTextStyle style;                      /*!< Ce membre contient le style du texte contenu dans la boite d'édition. */
   uint32_t scrolling;                       /*!< Ce membre contient le registre permettant d'activer ou désactiver le défilement vertical de de la boite d'édition (\ref K_MK_EDITFIELD_SCROLLING_ENABLED ou \ref K_MK_EDITFIELD_SCROLLING_DISABLED). */
   uint32_t writeProtect;                    /*!< Ce membre contient le registre permettant d'activer ou désactiver la protection en écriture de la boite d'édition. */
   uint32_t backgroundVisibility;            /*!< Ce membre contient l'état de l'arrière plan de la boite d'édition (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB backgroundColor;                 /*!< Ce membre contient la couleur de l'arrière plan de la boite d'édition. */
   uint32_t borderVisibility;                /*!< Ce membre contient l'état de la bordure de la boite d'édition (\ref K_MK_GRAPHICS_VISIBLE ou \ref K_MK_GRAPHICS_INVISIBLE). */
   T_mkARGB borderColor;                     /*!< Ce membre contient la couleur de la bordure de la boite d'édition. */
   T_mkTextCursor* cursor;                   /*!< Ce membre contient l'adresse du curseur utilisé (primaryCursor ou secondaryCursor). */
   T_mkTextCursor primaryCursor;             /*!< Ce membre privé contient les attributs du curseur primaire de la boite d'édition (vertical, avant le caractère).  */
   T_mkTextCursor secondaryCursor;           /*!< Ce membre privé contient les attributs du curseur secondaire de la boite d'édition (horizontal, sous le caractère). */
   T_mkVect2Di cursorVect;                   /*!< Ce membre privé contient les coordonnées [x, y] du curseur de la boite d'édition. */
   uint32_t cursorInhibitionCounter;         /*!< Ce membre privé contient le compteur permettant d'inhiber le clignotement du curseur [en frame]. */
   uint32_t cursorBaseOffset;                /*!< Ce membre privé contient l'offset du curseur dans la fenêtre affichée [en caractères]. Il est dédié à la fonction d'écoute. */
   uint32_t cursorPainterOffset;             /*!< Ce membre privé contient l'offset du curseur dans la fenêtre affichée [en caractères]. Il est dédié à la fonction de peinture. */
   T_mkAddr windowBaseAddr;                  /*!< Ce membre privé contient l'adresse marquant le début de la fenêtre dans la chaine de caractères. Il est dédié à la fonction d'écoute. */
   T_mkAddr painterBaseAddr;                 /*!< Ce membre privé contient l'adresse marquant le début de la fenêtre dans la chaine de caractères. Il est dédié à la fonction de peinture. */
   uint32_t windowBaseOffset;                /*!< Ce membre privé contient l'offset marquant le début de la fenêtre dans la chaine de caractères [en caractères]. */
   uint32_t windowFirstRowIndex;             /*!< Ce membre privé contient l'index de la première ligne de la fenêtre dans la chaine de caractères [en ligne]. */
   uint32_t windowNumberOfRow;               /*!< Ce membre privé contient le nombre maximal de lignes pouvant être affichés dans la fenêtre. */
   uint32_t windowCurrentNumberOfRow;        /*!< Ce membre privé contient le nombre de lignes actuellement occupées dans la fenêtre. */
};

/**
 *
 */

#endif


