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
* @file mk_msc_private.h
* @brief Déclaration des fonctions privées dédiées aux périphériques de stockage.
* @date 17 mai 2020
*
*/

#ifndef MK_MSC_PRIVATE_H
#define MK_MSC_PRIVATE_H

/**
 * @fn void mk_msc_task ( T_mkAddr p_param );
 * @brief Cette fonction est la fonction de démarrage du terminal MSC.
 * @param[in] p_param Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 *
 * @return Sans objet.
 *
 */

void mk_msc_task ( T_mkAddr p_param );

/**
 * @fn T_mkCode mk_msc_initHandler ( T_mkMSCHandler* p_handler );
 * @brief Cette fonction initialise un gestionnaire MSC de type \ref T_mkMSCHandler.
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire MSC de type \ref T_mkMSCHandler.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le gestionnaire MSC a été initialisé.
 *         \li \ref K_MK_ERROR_TIMEOUT : le gestionnaire MSC n'a pas été initialisé car un événement n'a pas été positionnés dans le timeout imparti.
 *         \li \ref K_MK_ERROR_PARAM   : le gestionnaire MSC n'a pas été initialisé car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le gestionnaire MSC n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : le gestionnaire MSC n'a pas été initialisé en raison d'une erreur d'allocation dynamique.
 */

T_mkCode mk_msc_initHandler ( T_mkMSCHandler* p_handler );

/**
 * @fn T_mkCode mk_msc_handle ( T_mkMSCHandler* p_handler );
 * @brief Cette fonction est la fonction de gestion des périphériques MSC. Elle assure la connexion et la déconnexion des périphériques MSC ainsi que
 *        la lecture ou l'écriture des blocs de données. *
 * @param[in, out] p_handler Ce paramètre contient l'adresse d'un gestionnaire MSC.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la fonction a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la fonction a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_MALLOC  : la fonction a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_TIMEOUT : la fonction a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la fonction a échoué car une erreur de communication s'est produite.
 */

T_mkCode mk_msc_handle ( T_mkMSCHandler* p_handler );

/**
 *
 */

#endif

