/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_peripheral_exti.h
* @brief Déclaration des fonctions dédiées au périphérique EXTI.
* @date 19 déc. 2020
*
*/

#ifndef MK_PERIPHERAL_EXTI_H
#define MK_PERIPHERAL_EXTI_H

/**
 * @fn void exti_enableInterrupt ( uint32_t p_line );
 * @brief Cette fonction active une ou plusieurs broches d'interruption externes.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_enableInterrupt ( uint32_t p_line );

/**
 * @fn void exti_disableInterrupt ( uint32_t p_line );
 * @brief Cette fonction désactive une ou plusieurs broches d'interruption externes.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_disableInterrupt ( uint32_t p_line );

/**
 * @fn void exti_enableEvent ( uint32_t p_line );
 * @brief Cette fonction active la génération d'un événement (WAKEUP) sur une ou plusieurs broches d'interruption
 *        externes.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_enableEvent ( uint32_t p_line );

/**
 * @fn void exti_disableEvent ( uint32_t p_line );
 * @brief Cette fonction désactive la génération d'un événement (WAKEUP) sur une ou plusieurs broches d'interruption
 *        externes.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_disableEvent ( uint32_t p_line );

/**
 * @fn void exti_enableRisingEdge ( uint32_t p_line );
 * @brief Cette fonction active la génération d'une interruption ou d'un événement lors de la détection d'un front montant
 *        sur une broche d'interruption externe.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_enableRisingEdge ( uint32_t p_line );

/**
 * @fn void exti_disableRisingEdge ( uint32_t p_line );
 * @brief Cette fonction désactive la génération d'une interruption ou d'un événement lors de la détection d'un front montant
 *        sur une broche d'interruption externe.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_disableRisingEdge ( uint32_t p_line );

/**
 * @fn void exti_enableFallingEdge ( uint32_t p_line );
 * @brief Cette fonction active la génération d'une interruption ou d'un événement lors de la détection d'un front descendant
 *        sur une broche d'interruption externe.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_enableFallingEdge ( uint32_t p_line );

/**
 * @fn void exti_disableFallingEdge ( uint32_t p_line );
 * @brief Cette fonction désactive la génération d'une interruption ou d'un événement lors de la détection d'un front descendant
 *        sur une broche d'interruption externe.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_disableFallingEdge ( uint32_t p_line );

/**
 * @fn void exti_generateRequest ( uint32_t p_line );
 * @brief Cette fonction déclenche une requête d'interruption externe.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_generateRequest ( uint32_t p_line );

/**
 * @fn void exti_clearRequest ( uint32_t p_line );
 * @brief Cette fonction réinitialise le registre de statut du périphérique EXTI.
 * @param[in] p_line Ce paramètre contient l'identifiant d'une ou plusieurs broches d'interruption. Une
 *                   combinaison des constantes suivantes peut être utilisée : \n
 *                   \ref K_EXTI_LINE0 à \ref K_EXTI_LINE23.
 *
 * @return Sans objet.
 *
 */

void exti_clearRequest ( uint32_t p_line );

/**
 * @fn void exti_getStatus ( void );
 * @brief Cette fonction retourne la valeur du registre de statut du périphérique EXTI.
 * @return La valeur du registre de statut du périphérique EXTI.
 *
 */

uint32_t exti_getStatus ( void );

/**
 *
 */

#endif

