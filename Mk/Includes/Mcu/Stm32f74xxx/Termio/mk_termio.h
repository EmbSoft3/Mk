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
* @file mk_termio.h
* @brief Déclaration des fonctions publiques dédiées aux terminaux d'entrées-sorties.
* @date 9 juin 2019
*
*/

#ifndef MK_TERMIO_H
#define MK_TERMIO_H

/**
 * @fn T_mkCode mk_termio_createHeap ( void );
 * @brief Cette fonction initialise le gestionnaire d'allocation dynamique dédié aux terminaux.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le gestionnaire d'allocation dynamique a été correctement initialisé.
 *         \li \ref K_MK_ERROR_MALLOC : le gestionnaire d'allocation dynamique n'a pas été initialisé car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le gestionnaire d'allocation dynamique n'a pas été initialisé car la fonction a été exécutée depuis un vecteur d'interruption.
 *
 */

T_mkCode mk_termio_createHeap ( void );

/**
 * @fn T_mkCode mk_termio_create ( void );
 * @brief Cette fonction réalise l'initialisation de tous les terminaux devant être lancés à l'intialisation du système.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : les terminaux ont été correctement initialisés.
 *         \li \ref K_MK_ERROR_MALLOC : les terminaux n'ont pas été initialisés car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : les terminaux n'ont pas été initialisés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_INIT   : les terminaux n'ont pas été initialisés car le noyau n'a pas été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : les terminaux n'ont pas été intialisées car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_termio_init ( void );

/**
 * @fn T_mkCode mk_termio_create ( T_mkTermio** p_termio, uint32_t p_identifier, uint32_t p_priority, T_mkAddress p_function );
 * @brief Cette fonction initialise la stack et démarre la tâche d'un terminal.
 *
 * @param[in, out] p_termio     Ce paramètre contient l'adresse d'une structure \ref T_mkTermio allouée.
 * @param[in]      p_identifier Ce paramètre contient l'identifiant de la tâche du terminal.
 * @param[in]      p_priority   Ce paramètre contient la priorité de la tâche du terminal.
 * @param[in]      p_function   Ce paramètre contient l'adresse de la routine principale du terminal.
 * @param[in]      p_stackAddr  Ce paramètre contient l'adresse de la stack du terminal.
 * @param[in]      p_stackSize  Ce paramètre contient la taille [en multiple de mots 32bits] de la stack du terminal.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le terminal a été correctement démarré.
 *         \li \ref K_MK_ERROR_MALLOC : le terminal n'a pas été démarré car la taille de la zone mémoire définie par la structure \ref T_mkPoolArea est insuffisante.
 *         \li \ref K_MK_ERROR_ISR    : le terminal n'a pas été démarré car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_INIT   : le terminal n'a pas été démarré car le noyau n'a pas été initialisé.
 *         \li \ref K_MK_ERROR_PARAM  : le terminal n'a pas été démarré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_RIGHT  : le terminal n'a pas été démarré car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_termio_create ( T_mkTermio** p_termio, uint32_t p_identifier, uint32_t p_priority, T_mkAddress p_function, uint32_t* p_stackAddr, uint32_t p_stackSize );

/**
 * @fn T_mkCode mk_termio_delete ( T_mkTermio* p_termio );
 * @brief Cette fonction détruit un terminal.
 * @param[in, out] p_termio Ce paramètre contient l'adresse d'une structure de type \ref T_mkTermio.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK          : le terminal a été correctement détruit.
 *         \li \ref K_MK_ERROR_ISR   : le terminal n'a pas été détruit car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_PARAM : le terminal n'a pas été démarré car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_RIGHT : le terminal n'a pas été détruit car une tâche non privilégiée ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_termio_delete ( T_mkTermio* p_termio );

/**
 * @fn T_mkCode mk_termio_link ( T_mkTermio* p_termio, T_mkTermioIdentifier p_id );
 * @brief Cette fonction établit un lien entre un terminal et un gestionnaire d'interruption. Elle indique au gestionnaire d'interruption l'adresse du
 *        terminal à utiliser pour transférer ses données. Le gestionnaire d'interruption est activé si cette fonction réussie.
 *
 * @param[in] p_termio Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 * @param[in] p_id     Ce paramètre contient l'identifiant d'un terminal.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le lien a été correctement réalisé.
 *         \li \ref K_MK_ERROR_PARAM  : le lien n'a pas été réalisé car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_termio_link ( T_mkTermio* p_termio, T_mkTermioIdentifier p_id );

/**
 * @fn T_mkCode mk_termio_unlink ( T_mkTermioIdentifier p_id );
 * @brief Cette fonction supprime le lien existant entre un terminal et un gestionnaire d'interruption. Le gestionnaire d'interruption est
 *        désactivé si cette fonction réussie.
 * @param[in] p_id Ce paramètre contient l'identifiant d'un terminal.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : le lien a été correctement supprimé.
 *         \li \ref K_MK_ERROR_PARAM  : le lien n'a pas été supprimé car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_termio_unlink ( T_mkTermioIdentifier p_id );

/**
 * @fn T_mkCode mk_termio_create ( void );
 * @brief Cette fonction configure l'adresse de la structure de données d'un terminal.
 *
 * @param[in, out] p_termio Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 * @param[in]      p_child  Ce paramètre contient l'adresse d'une structure de données.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : l'adresse de la structure de données du terminal a été correctement configurée.
 *         \li \ref K_MK_ERROR_PARAM  : l'adresse de la structure de données du terminal n'a pas été configurée car au moins un des
 *                                      paramètres d'entrée est invalide.
 *
 */

T_mkCode mk_termio_setChild ( T_mkTermio* p_termio, T_mkAddr p_child );

/**
 * @fn T_mkCode mk_termio_getChild ( T_mkTermio* p_termio, T_mkAddr* p_child );
 * @brief Cette fonction retourne l'adresse de la structure de données d'un terminal.
 *
 * @param[in]  p_termio Ce paramètre contient l'adresse d'un terminal de type \ref T_mkTermio.
 * @param[out] p_child  Ce paramètre contient l'adresse d'une structure de données.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : l'adresse de la structure de données est disponible dans le paramètre p_child.
 *         \li \ref K_MK_ERROR_PARAM  : l'adresse de la structure de données n'est pas disponible car au moins un des paramètres
 *                                      d'entrée est invalide.
 *
 */

T_mkCode mk_termio_getChild ( T_mkTermio* p_termio, T_mkAddr* p_child );

/**
 * @fn T_mkCode mk_termio_log ( T_str8 p_str );
 * @brief Cette fonction permet d'enregistrer une chaine de caractères dans le fichier de log du superviseur.
 * @param[in]  p_str Ce paramètre contient l'adresse d'une chaine de caractères terminée par '\0'.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK              : le message a été correctement enregistré dans le fichier de log.
 *         \li \ref K_MK_ERROR_TIMEOUT   : le message n'a pas été enregistré dans le fichier de log en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM      : le message n'a pas été enregistré dans le fichier de log en raison d'une erreur de communication.
 *         \li \ref K_MK_ERROR_ISR       : le message n'a pas été enregistré dans le fichier de log car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_PARAM     : le message n'a pas été enregistré dans le fichier de log car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_CORRUPTED : le message n'a pas été enregistré dans le fichier de log car la table des clusters (FAT) est corrompue.
 *         \li \ref K_MK_ERROR_DENIED    : le message n'a pas été enregistré dans le fichier de log car le fichier n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL      : le message n'a pas été enregistré dans le fichier de log car l'espace disponible sur le disque n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT     : le message n'a pas été enregistré dans le fichier de log car une tâche de type non privilégié ne peut pas accéder une messagerie protégée.
 *
 */

T_mkCode mk_termio_log ( T_str8 p_str );

/**
 *
 */

#endif


