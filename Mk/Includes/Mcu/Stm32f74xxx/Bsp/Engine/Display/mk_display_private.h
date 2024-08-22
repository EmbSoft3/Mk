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
* @file mk_display_private.h
* @brief Déclaration des fonctions privées dédiées au module 'Display'.
* @date 23 mars 2019
*
*/

#ifndef MK_DISPLAY_PRIVATE_H
#define MK_DISPLAY_PRIVATE_H

/**
 * @fn void mk_display_init ( void );
 * @brief Cette fonction initialise le matériel du moteur graphique (hors DMA2D).
 * @return Sans objet.
 *
 */

void mk_display_init ( void );

/**
 * @fn void mk_display_initGPIO ( void );
 * @brief Cette fonction initialise les broches GPIO du périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_initGPIO ( void );

/**
 * @fn void mk_display_initLTDC ( void );
 * @brief Cette fonction initialise le périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_initLTDC ( void );

/**
 * @fn void mk_display_initLayer1 ( void );
 * @brief Cette fonction initialise le layer 1 du périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_initLayer1 ( void );

/**
 * @fn void mk_display_initLayer2 ( void );
 * @brief Cette fonction initialise le layer 2 du périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_initLayer2 ( void );

/**
 * @fn void mk_display_initChromArt ( void );
 * @brief Cette fonction initialise l'accélérateur graphique ChromArt (DMA2D).
 * @return Sans objet.
 *
 */

void mk_display_initChromArt ( void );

/**
 * @fn void mk_display_painter ( T_mkAddr p_unused );
 * @brief Cette tâche exécute les fonctions de peintures privilégiées du moteur graphique.
 *        Elle est séquencée par le gestionnaire d'interruption \ref mk_display_frameInterrupt.
 * @param[in] p_unused Ce paramètre n'est pas utilisé.
 * @return Sans objet.
 *
 */

void mk_display_painter ( T_mkAddr p_unused );

/**
 * @fn void mk_display_userPainter ( T_mkAddr p_unused );
 * @brief Cette tâche exécute les fonctions de peintures non-privilégiées du moteur graphique.
 *        Elle est séquencée par la fonction \ref mk_display_painter.
 * @param[in] p_unused Ce paramètre n'est pas utilisé.
 * @return Sans objet.
 *
 */

void mk_display_userPainter ( T_mkAddr p_unused );

/**
 * @fn void mk_display_listener ( T_mkAddr p_unused );
 * @brief Cette tâche exécute les fonctions d'écoutes privilégiées du moteur graphique.
 * @param[in] p_unused Ce paramètre n'est pas utilisé.
 * @return Sans objet.
 *
 */

void mk_display_listener ( T_mkAddr p_unused );

/**
 * @fn void mk_display_userListener ( T_mkAddr p_unused );
 * @brief Cette tâche exécute les fonctions d'écoutes non-privilégiées du moteur graphique.
 *        Elle est séquencée par la fonction \ref mk_display_listener.
 * @param[in] p_unused Ce paramètre n'est pas utilisé.
 * @return Sans objet.
 *
 */

void mk_display_userListener ( T_mkAddr p_unused );

/**
 * @fn void mk_display_handler ( T_mkAddr p_unused );
 * @brief Cette tâche exécute les requêtes envoyées au moteur graphique.
 * @param[in] p_unused Ce paramètre n'est pas utilisé.
 * @return Sans objet.
 *
 */

void mk_display_handler ( T_mkAddr p_unused );

/**
 * @fn void mk_display_frameInterrupt ( void );
 * @brief Cette interruption est déclenchée lorsqu'une frame a été dessinée par le périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_frameInterrupt ( void );

/**
 * @fn void mk_display_frameInterrupt ( void );
 * @brief Cette interruption est déclenchée lorsqu'une erreur ou une underflow a été détectée par le périphérique LTDC.
 * @return Sans objet.
 *
 */

void mk_display_frameErrorsInterrupt ( void );

/**
 * @fn void mk_display_chromartInterrupt ( void );
 * @brief Cette interruption est déclenchée lorsqu'un transfert est terminée ou lorsqu'une erreur est détectée par
 *        l'accélérateur graphique.
 * @return Sans objet.
 *
 */

void mk_display_chromartInterrupt ( void );

/**
 * @fn void mk_display_enableFactory ( void );
 * @brief Cette fonction autorise l'exécution des fonctions de peintures et d'écoutes présentes dans les factory privilégiées
 *        et non privilégiées.
 * @return Sans objet.
 *
 */

void mk_display_enableFactory ( void );

/**
 * @fn void mk_display_disableFactory ( void );
 * @brief Cette fonction interdit l'exécution des fonctions de peintures et d'écoutes présentes dans les factory privilégiées
 *        et non privilégiées.
 *
 * @return Sans objet.
 *
 */
void mk_display_disableFactory ( void );

/**
 * @fn T_mkCode mk_display_report ( T_mkCode p_code );
 * @brief Cette fonction envoie un code erreur de type \ref K_MK_SUPERVISOR_TASKFAULT au superviseur.
 * @param[in] p_code Ce paramètre contient un code erreur de type \ref T_mkCode.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le code erreur a été envoyé au superviseur.
 *         \li \ref K_MK_ERROR_PARAM   : le code erreur n'a pas été envoyé au superviseur car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le code erreur n'a pas été envoyé au superviseur car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : le code erreur n'a pas été envoyé au superviseur car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le code erreur n'a pas été envoyé au superviseur car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_report ( T_mkCode p_code );

/**
 * @fn T_mkCode mk_display_reportTimeout ( void );
 * @brief Cette fonction envoie un code erreur de type \ref K_MK_SUPERVISOR_TIMEOUTFAULT au superviseur.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le code erreur a été envoyé au superviseur.
 *         \li \ref K_MK_ERROR_PARAM   : le code erreur n'a pas été envoyé au superviseur car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le code erreur n'a pas été envoyé au superviseur car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : le code erreur n'a pas été envoyé au superviseur car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le code erreur n'a pas été envoyé au superviseur car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_reportTimeout ( void );

/**
 * @fn T_mkCode mk_display_handleEngineFaults ( T_mkTask* p_task, uint32_t p_fault );
 * @brief Cette fonction redémarre une ou plusieurs tâches du moteur graphique suite à une erreur.
 *        L'ensemble du moteur graphique est rédémarré si une tâches privilégiées est en erreur. Sinon, seule la tâche en erreur est rédémarrée.
 *
 * @param[in] p_task  Ce paramètre contient l'adresse de la tâche en erreur.
 * @param[in] p_fault Ce paramètre n'est pas utilisé.
 *
 * @return Cette fonction retourne un des codes suivants:
 *         \li \ref K_MK_OK            : le redémarrage du moteur graphique a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : le redémarrage du moteur graphique a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : le redémarrage du moteur graphique a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_MALLOC  : le redémarrage du moteur graphique a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : le redémarrage du moteur graphique a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : le redémarrage du moteur graphique a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_display_handleEngineFaults ( T_mkTask* p_task, uint32_t p_fault );

/**
 *
 */

#endif



