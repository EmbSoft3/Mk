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
* @file mk_hid_mouse.h
* @brief Déclaration des fonctions publiques dédiées aux objets 'Mouse'.
* @date 1 déc. 2019
*
*/

#ifndef MK_HID_MOUSE_H
#define MK_HID_MOUSE_H

/**
 * @fn T_mkCode mk_hid_mouse_getID ( T_mkMouse* p_mouse, uint16_t* p_id );
 * @brief Cette fonction retourne l'identifiant d'une souris de type \ref T_mkMouse.
 *
 * @param[in]  p_mouse Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[out] p_id    Ce paramètre contient l'identifiant de la souris.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_mouse_getID ( T_mkMouse* p_mouse, uint16_t* p_id );

/**
 * @fn T_mkCode mk_hid_mouse_getCoord ( T_mkMouse* p_mouse, real32_t* p_x, real32_t* p_y );
 * @brief Cette fonction retourne la position du curseur d'une souris de type \ref T_mkMouse.
 *
 * @param[in]  p_mouse Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[out] p_x     Ce paramètre contient la coordonnées 'x' d'une souris.
 * @param[out] p_y     Ce paramètre contient la coordonnées 'y' d'une souris.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_mouse_getCoord ( T_mkMouse* p_mouse, real32_t* p_x, real32_t* p_y );

/**
 * @fn T_mkCode mk_hid_mouse_getWheel ( T_mkMouse* p_mouse, int32_t* p_wheel );
 * @brief Cette fonction retourne la valeur de la molette d'une souris de type \ref T_mkMouse.
 *
 * @param[in]  p_mouse Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[out] p_wheel Ce paramètre contient la valeur de la molette d'une souris.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_mouse_getWheel ( T_mkMouse* p_mouse, int32_t* p_wheel );

/**
 * @fn T_mkCode mk_hid_mouse_getACPan ( T_mkMouse* p_mouse, int32_t* p_acPan );
 * @brief Cette fonction retourne la valeur horizontal de la molette d'une souris de type \ref T_mkMouse.
 *
 * @param[in]  p_mouse Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[out] p_acPan Ce paramètre contient la valeur horizontale de la molette d'une souris.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_mouse_getACPan ( T_mkMouse* p_mouse, int32_t* p_acPan );

/**
 * @fn T_mkCode mk_hid_mouse_setRectangle ( T_mkMouse* p_mouse, real32_t p_x, real32_t p_y, real32_t p_width, real32_t p_height );
 * @brief Cette fonction configure l'espace où peut évoluer le curseur de la souris. Il est conseillé d'exécuter cette fonction lors
 *        de la réception de l'événement \ref K_MK_EVENT_CONNECT.
 *
 * @param[in] p_mouse  Ce paramètre contient l'adresse d'un objet de type \ref T_mkMouse.
 * @param[in] p_x      Ce paramètre contient l'origine 'x' du plan (habituellement 0).
 * @param[in] p_y      Ce paramètre contient l'origine 'y' du plan (habituellement 0)..
 * @param[in] p_width  Ce paramètre contient la largeur du plan (habituellement la largeur de l'écran).
 * @param[in] p_height Ce paramètre contient la hauteur du plan (habituellement la hauteur de l'écran).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la fonction s'est exécutée sans rencontrer d'erreur.
 *         \li \ref K_MK_ERROR_PARAM : la fonction ne s'est pas exécutée correctement car au moins un paramètre est invalide.
 */

T_mkCode mk_hid_mouse_setRectangle ( T_mkMouse* p_mouse, real32_t p_x, real32_t p_y, real32_t p_width, real32_t p_height );

/**
 *
 */

#endif

