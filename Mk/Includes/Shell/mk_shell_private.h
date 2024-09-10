/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_shell_private.h
* @brief Déclaration des fonctions privées dédiées au shell.
* @date 11 nov. 2023
*
*/

#ifndef MK_SHELL_PRIVATE_H
#define MK_SHELL_PRIVATE_H

/**
 * @fn void mk_shell ( T_mkAddr p_unused );
 * @brief Cette fonction est la fonction de démarrage des gestionnaires de commandes.
 * @param[in] p_unused Ce paramètre n'est pas utilisé. Il prend la valeur \ref K_MK_NULL.
 *
 * @return Sans objet.
 *
 */

void mk_shell ( T_mkAddr p_unused );

/**
 * @fn T_mkCode mk_shell_create ( void );
 * @brief Cette fonction initialise puis démarre le gestionnaire de commandes du système.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : l'initialisation des gestionnaires de commandes a réussi.
 *         \li \ref K_MK_ERROR_PARAM  : l'initialisation des gestionnaires de commandes a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : l'initialisation des gestionnaires de commandes a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR    : l'initialisation des gestionnaires de commandes a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : l'initialisation des gestionnaires de commandes a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_shell_create ( void );

/**
 * @fn T_mkCode mk_shell_init ( T_mkShell* p_shell );
 * @brief Cette fonction initialise les données internes (boite de messages, page et pointeur mémoire) d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[out] p_shell Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : l'initialisation du gestionnaire de commandes a réussi.
 *         \li \ref K_MK_ERROR_PARAM  : l'initialisation du gestionnaire de commandes a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC : l'initialisation du gestionnaire de commandes a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR    : l'initialisation du gestionnaire de commandes a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : l'initialisation du gestionnaire de commandes a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_shell_init ( T_mkShell* p_shell );

/**
 * @fn T_mkCode mk_shell_delete ( T_mkShell* p_shell );
 * @brief Cette fonction supprime les données allouées par un gestionnaire de commandes de type \ref T_mkShell.
 * @param[out] p_shell Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK           : la désallocation du gestionnaire de commandes a réussi.
 *         \li \ref K_MK_ERROR_PARAM  : la désallocation du gestionnaire de commandes a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR    : la désallocation du gestionnaire de commandes a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT  : la désallocation du gestionnaire de commandes a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_shell_delete ( T_mkShell* p_shell );

/**
 * @fn T_str8 mk_shell_removeDoubleQuote ( T_str8 p_str, T_mkFontUnicode p_fontEncoding );
 * @brief Cette fonction retire les guillemets de début et de fin d'une chaine de caractères.
 *
 * @param[in] p_str          Ce paramètre contient l'adresse d'une chaine de caractères.
 * @param[in] p_fontEncoding Ce paramètre contient l'encodage de la chaine de caractères.
 *                           Les constantes \ref K_MK_FONT_UTF32, \ref K_MK_FONT_UTF16, \ref K_MK_FONT_UTF8 et \ref K_MK_FONT_ASCII peuvent être utilisées.
 *
 * @return Cette fonction retourne l'adresse de début de la chaine de caractères sans les guillemets.
 *
 */

T_str8 mk_shell_removeDoubleQuote ( T_str8 p_str, T_mkFontUnicode p_fontEncoding );

/**
 * @fn T_mkCode mk_shell_handle ( T_mkShell* p_shell, T_mkShellMessage* p_message );
 * @brief Cette fonction exécute les commandes transmises au gestionnaire de commandes.
 *
 * @param[in] p_shell   Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_message Ce paramètre contient l'adresse d'un message de type \ref T_mkShellMessage.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_shell_handle ( T_mkShell* p_shell, T_mkShellMessage* p_message );

/**
 * @fn T_mkCode mk_shell_run ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str );
 * @brief Cette fonction recherche, installe et exécute une application présente sur le système de fichier.
 *        Le prototype de la ligne de commande est : path/fileName.elf [options].\n
 *
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_shell_run ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str );

/**
 * @fn T_mkCode mk_shell_abort ( T_mkShell* p_shell, T_mkConsole* p_console );
 * @brief Cette fonction abondonne l'exécution d'une commande.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_ABORT_HELP_MESSAGE.
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_shell_abort ( T_mkShell* p_shell, T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_shell_help ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction affiche le mode d'emploi des commandes.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_HELP_LIST.
 *
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_shell_help ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_restart ( T_mkShell* p_shell, T_mkConsole* p_console, T_mkAddr p_addr, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction redémarre le système sur confirmation.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_RESTART_HELP_MESSAGE.
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_addr      Ce paramètre contient l'adresse la valeur \ref K_MK_NULL si la première phase de la commande doit être exécutée (confirmation), sinon la valeur
 *                        \ref K_MK_NOT_NULL.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).

 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *
 */

T_mkCode mk_shell_restart ( T_mkShell* p_shell, T_mkConsole* p_console, T_mkAddr p_addr, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_application_getApps ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction affiche dans la console l'ensemble des applications installées.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_GETAPPS_HELP_MESSAGE.
 *
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de sortie est corrompu.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *
 */

T_mkCode mk_shell_application_getApps ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_application_install ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction installe une nouvelle application.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_INSTALL_HELP_MESSAGE.
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_MALLOC        : l'exécution de la commande a échoué car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_application_install ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_application_uninstall ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction désinstalle une application.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_UNINSTALL_HELP_MESSAGE.
 *
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_application_uninstall ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_application_launch ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction démarre une application installée.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_LAUNCH_HELP_MESSAGE.
 *
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_application_launch ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_application_terminate ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction termine l'exécution d'une application.
 *        Le prototype de la ligne de commande est défini par la constante \ref MK_SHELL_MESSAGE_TERMINATE_HELP_MESSAGE.
 *
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_application_terminate ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_fileSystem_cd ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction modifie la valeur du répertoire courant.
 *        Le prototype de la ligne de commande est : cd path
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 * @param[in] p_str       Ce paramètre contient l'adresse de la chaine de caractères qui stocke la ligne de commandes saisies par l'utilisateur.
 * @param[in] p_cmdLength Ce paramètre contient la longueur de la ligne de commandes saisies par l'utilisateur (en octets).
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_fileSystem_cd ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );

/**
 * @fn T_mkCode mk_shell_fileSystem_cd ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength );
 * @brief Cette fonction affiche la valeur du répertoire courant. Le prototype de la ligne de commande est : pwd
 *
 * @param[in] p_shell   Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_fileSystem_pwd ( T_mkShell* p_shell, T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_shell_fileSystem_ls ( T_mkShell* p_shell, T_mkConsole* p_console );
 * @brief Cette fonction affiche les fichiers du répertoire courant. Le prototype de la ligne de commande est : ls
 *
 * @param[in] p_shell     Ce paramètre contient l'adresse d'un gestionnaire de commandes de type \ref T_mkShell.
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_fileSystem_ls ( T_mkShell* p_shell, T_mkConsole* p_console );

/**
 * @fn T_mkCode mk_shell_fileSystem_lsdsk ( T_mkConsole* p_console );
 * @brief Cette fonction liste l'ensemble des disques du système. Le prototype de la ligne de commande est : lsdsk
 * @param[in] p_console   Ce paramètre contient l'adresse d'une console de type \ref T_mkConsole.
 *
 * @return Cette fonction retourne un des codes suivants :
 *         \li \ref K_MK_OK                  : l'exécution de la commande a réussi.
 *         \li \ref K_MK_ERROR_PARAM         : l'exécution de la commande a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_NOT_AVAILABLE : l'exécution de la commande a échoué car au moins un argument est absent de la ligne de commande.
 *         \li \ref K_MK_ERROR_ISR           : l'exécution de la commande a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT       : l'exécution de la commande a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM          : l'exécution de la commande a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_CORRUPTED     : l'exécution de la commande a échoué car le fichier de programmation de l'application est corrompu (table des clusters).
 *         \li \ref K_MK_ERROR_UNEXPECTED    : l'exécution de la commande a échoué car une erreur inattendue s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT         : l'exécution de la commande a échoué car une tâche non privilégiée ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_DENIED        : l'exécution de la commande a échoué car le fichier de sortie n'a pas été ouvert avec les droits en écriture.
 *         \li \ref K_MK_ERROR_FULL          : l'exécution de la commande a échoué car l'espace disponible sur le disque (ou dans le buffer) n'est pas suffisant.
 *
 */

T_mkCode mk_shell_fileSystem_lsdsk ( T_mkConsole* p_console );

/**
 *
 */

#endif

