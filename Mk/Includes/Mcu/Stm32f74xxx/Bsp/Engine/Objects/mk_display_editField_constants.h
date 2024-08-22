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
* @file mk_display_editField_constants.h
* @brief Déclaration des constantes dédiées à l'objet 'EditField'.
* @date 1 déc. 2022
*
*/

#ifndef MK_DISPLAY_EDITFIELD_CONSTANTS_H
#define MK_DISPLAY_EDITFIELD_CONSTANTS_H

/**
 * @def K_MK_EDITFIELD_DEFAULT_WIDTH
 * @brief Définition de la largeur par défaut de la boite d'édition (en pixel). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_DEFAULT_WIDTH 48

/**
 * @def K_MK_EDITFIELD_DEFAULT_HEIGHT
 * @brief Définition de la hauteur par défaut de la boite d'édition (en pixel). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_DEFAULT_HEIGHT 17

/**
 *
 */

/**
 * @def K_MK_EDITFIELD_INHIBITION_TIME
 * @brief Définition de la durée d'inhibition du clignotement du curseur [en frame]
 *        suite au traitement d'une entrée utilisateur.
 *
 */

#define K_MK_EDITFIELD_INHIBITION_TIME 60

/**
 *
 */

/**
 * @def K_MK_EDITFIELD_SCROLLING_DISABLED
 * @brief Constante dédiée à la fonction \ref mk_editField_disableScrolling.
 *        Valeur indiquant que le défilement vertical de la boite d'édition est désactivé.
 */

#define K_MK_EDITFIELD_SCROLLING_DISABLED 0

/**
 * @def K_MK_EDITFIELD_SCROLLING_ENABLED
 * @brief Constante dédiée à la fonction \ref mk_editField_enableScrolling.
 *        Valeur indiquant que le défilement vertical de la boite d'édition est activé.
 */

#define K_MK_EDITFIELD_SCROLLING_ENABLED 1

/**
 * @def K_MK_EDITFIELD_WRITE_PROTECT_DISABLED
 * @brief Constante dédiée à la fonction \ref mk_editField_disableWriteProtect.
 *        Valeur indiquant que la protection en écriture de la boite d'édition est désactivée.
 */

#define K_MK_EDITFIELD_WRITE_PROTECT_DISABLED 0

/**
 * @def K_MK_EDITFIELD_WRITE_PROTECT_ENABLED
 * @brief Constante dédiée à la fonction \ref mk_editField_enableWriteProtect.
 *        Valeur indiquant que la protection en écriture de la boite d'édition est activée.
 */

#define K_MK_EDITFIELD_WRITE_PROTECT_ENABLED 1

/**
 *
 */

/**
 * @def K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_WIDTH
 * @brief Définition de la largeur [en pixel] du curseur primaire (mode vertical avant le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_WIDTH 2

/**
 * @def K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_HEIGHT
 * @brief Définition de la hauteur [en pixel] du curseur primaire (mode vertical avant le caractère).\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_HEIGHT 15

/**
 * @def K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETX
 * @brief Définition de l'offset sur l'axe x [en pixel] du curseur primaire (mode vertical avant le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETX 0

/**
 * @def K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETY
 * @brief Définition de l'offset sur l'axe y [en pixel] du curseur primaire (mode vertical avant le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_PRIMARY_CURSOR_DEFAULT_OFFSETY 3

/**
 *
 */

/**
 * @def K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_HEIGHT
 * @brief Définition de la hauteur [en pixel] du curseur auxiliaire (mode horizontal sous le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 * @note  La largeur du curseur auxilaire est égale à la taille du caractère possédant le focus.
 */

#define K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_HEIGHT 3

/**
 * @def K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETX
 * @brief Définition de l'offset sur l'axe x [en pixel] du curseur auxilaire (mode horizontal sous le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETX 0

/**
 * @def K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETY
 * @brief Définition de l'offset sur l'axe y [en pixel] du curseur auxilaire (mode horizontal sous le caractère). \n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_EDITFIELD_SECONDARY_CURSOR_DEFAULT_OFFSETY 17

/**
 *
 */

/**
 * @def K_MK_EDITFIELD_REFRESH
 * @brief Définition d'une constante indiquant que la boite d'édition doit être rafraichie.
 *
 */

#define K_MK_EDITFIELD_REFRESH 0xFFFFFFFF

/**
 *
 */

#endif

