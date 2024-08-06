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
* @file mk_display.h
* @brief Déclaration des fonctions publiques dédiées au module 'Display'.
* @date 9 mars 2019
*
*/

#ifndef MK_DISPLAY_H
#define MK_DISPLAY_H

/**
 * @fn T_mkCode mk_display_initEngine ( uint32_t p_orientation, uint32_t p_origin );
 * @brief Cette fonction intialise le moteur graphique.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le moteur graphique a été intialisé.
 *         \li \ref K_MK_ERROR_INIT   : le moteur graphique n'a pas été initialisé car le noyau n'a pas été configuré.
 *         \li \ref K_MK_ERROR_PARAM  : le moteur graphique n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : le moteur graphique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC : le moteur graphique n'a pas été initialisé car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT  : le moteur graphique n'a pas été initialisé car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_initEngine ( void );

/**
 * @fn T_mkCode mk_display_enableForeground ( void );
 * @brief Cette fonction active le layer de premier plan.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : l'activation du layer a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'activation du layer a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'activation du layer a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : l'activation du layer a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_enableForeground ( void );

/**
 * @fn T_mkCode mk_display_disableForeground ( void );
 * @brief Cette fonction désactive le layer de premier plan.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la désactivation du layer a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la désactivation du layer a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la désactivation du layer a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : la désactivation du layer a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_disableForeground ( void );

/**
 * @fn T_mkCode mk_display_enableBackground ( void );
 * @brief Cette fonction active le layer d'arrière plan.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : l'activation du layer a réussi.
 *         \li \ref K_MK_ERROR_PARAM : l'activation du layer a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : l'activation du layer a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : l'activation du layer a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_enableBackground ( void );

/**
 * @fn T_mkCode mk_display_disableBackground ( void );
 * @brief Cette fonction désactive le layer d'arrière plan.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : la désactivation du layer a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la désactivation du layer a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR   : la désactivation du layer a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT : la désactivation du layer a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_disableBackground ( void );

/**
 * @fn T_mkCode mk_display_enterCritical ( void );
 * @brief Cette fonction ouvre une section critique. Les objets graphiques partagés peuvent être actualisés à l'intérieur de celle-ci.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la section critique a été correctement.
 *         \li \ref K_MK_ERROR_PARAM   : la section critique n'a pas été ouverte car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la section critique n'a pas été ouverte car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la section critique n'a pas été ouverte car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la section critique n'a pas été ouverte car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 * @warning Suite à l'exécution de cette fonction, le rafraichissement des objets graphiques est bloqué tant que la section critique n'a pas été fermée
 *          (fonction \ref mk_display_exitCritical).
 *
 */

T_mkCode mk_display_enterCritical ( void );

/**
 * @fn T_mkCode mk_display_exitCritical ( void );
 * @brief Cette fonction ferme une section critique précédemment ouverte avec la fonction \ref mk_display_enterCritical.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : la section critique a été fermée correctement.
 *         \li \ref K_MK_ERROR_PARAM   : la section critique n'a pas été fermée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la section critique n'a pas été fermée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : la section critique n'a pas été fermée car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_exitCritical ( void );

/**
 * @fn T_mkCode mk_display_refreshFields ( void );
 * @brief Cette fonction rafraichie la valeur des champs 'visibility' et 'refresh' de l'ensemble des champs présents dans les containers du moteur
 *        graphique.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK            : le rafraichissement des champs a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le rafraichissement des champs a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le rafraichissement des champs a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_RIGHT   : le rafraichissement des champs a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_refreshFields ( void );

/**
 * @fn void mk_display_setWidth ( uint32_t p_width );
 * @brief Cette fonction configure la largeur de l'écran.
 * @param[in] p_width Ce paramètre contient la largeur de l'écran [en pixel]. Il évolue entre 0 et \ref K_MK_DISPLAY_WIDTH.
 * @return Sans objet.
 *
 */

void mk_display_setWidth ( uint32_t p_width );

/**
 * @fn void mk_display_setHeight ( uint32_t p_height );
 * @brief Cette fonction configure la hauteur de l'écran.
 * @param[in] p_height Ce paramètre définie la hauteur de l'écran [en pixel]. Il évolue entre 0 et \ref K_MK_DISPLAY_HEIGHT.
 * @return Sans objet.
 *
 */

void mk_display_setHeight ( uint32_t p_height );

/**
 * @fn uint32_t mk_display_getWidth ( void );
 * @brief Cette fonction retourne la largeur de l'écran [en pixel].
 * @return Cette fonction retourne la largeur de l'écran [en pixel].
 *
 */

uint32_t mk_display_getWidth ( void );

/**
 * @fn uint32_t mk_display_getHeight ( void );
 * @brief Cette fonction retourne la hauteur de l'écran [en pixel].
 * @return Cette fonction retourne la hauteur de l'écran [en pixel].
 *
 */

uint32_t mk_display_getHeight ( void );

/**
 * @fn uint32_t mk_display_getFramerate ( void );
 * @brief Cette fonction retourne la valeur du framerate [en frame/seconde].
 * @return Cette fonction retourne la valeur du framerate [en frame/seconde].
 *
 */

uint32_t mk_display_getFramerate ( void );

/**
 * @fn uint32_t* mk_display_getFrameBuffer ( uint32_t p_layer );
 * @brief Cette fonction retourne l'adresse du buffer graphique correpondant au layer 'p_layer'. Elle
 *        doit être exécutée dans une fonction de peinture.
 *
 * @param[in] p_layer Ce paramètre contient l'identifiant du layer. Il peut prendre une des valeurs
 *                    suivantes :\n \ref K_MK_GRAPHICS_BACKGROUND et \ref K_MK_GRAPHICS_FOREGROUND.
 *
 * @return Cette fonction retourne l'adresse d'un buffer graphique.
 *
 */

uint32_t* mk_display_getFrameBuffer ( uint32_t p_layer );

/**
 *
 */

#endif



