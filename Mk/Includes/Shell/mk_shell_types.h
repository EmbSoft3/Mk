/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_shell_types.h
* @brief Déclaration des types dédiés au shell.
* @date 11 nov. 2023
*
*/

#ifndef MK_SUPERVISOR_CMD_TYPES_H
#define MK_SUPERVISOR_CMD_TYPES_H

/**
 * @enum T_mkShellCmdState
 * @brief Déclaration de l'énumération T_mkShellCmdState.
 *
 */

typedef enum T_mkShellCmdState
{
   K_MK_SHELL_CMD_IN_PROGRESS = 0,                                     /*!< Définition d'un identifiant indiquant que la commande courante est toujours en cours. */
   K_MK_SHELL_CMD_END = 1                                              /*!< Définition d'un identifiant indiquant que la commande courante est terminée. */
} T_mkShellCmdState;

/**
 *
 */

typedef struct T_mkShell T_mkShell;

/**
 * @struct T_mkShellMessage
 * @brief Déclaration de la structure T_mkShellMessage.
 *
 */

typedef struct T_mkShellMessage T_mkShellMessage;
struct T_mkShellMessage
{
   uint8_t fileName [ K_MK_SHELL_FILE_NAME_LENGTH ];                   /*!< Ce membre contient le nom du fichier où est stocké la commande à traiter. */
   T_mkConsole* console;                                               /*!< Ce membre contient l'adresse de la console qui a postée le message. */
};

/**
 * @struct T_mkShellTaskArea
 * @brief Déclaration de la structure T_mkShellTaskArea.
 *
 */

typedef struct T_mkShellTaskArea T_mkShellTaskArea;
struct T_mkShellTaskArea
{
   T_mkPool* pool;                                                     /*!< Ce membre contient le gestionnaire mémoire utilisé pour allouer dynamiquement les stacks des gestionnaires de commandes. */
   T_mkPoolArea area;                                                  /*!< Ce membre contient les caractéristiques mémoire du gestionnaire d'allocation dynamique. */
   uint32_t heap [ K_MK_SHELL_NUMBER * K_MK_SHELL_STACK_SIZE ];        /*!< Ce membre contient la mémoire dédiée aux stacks des gestionnaires de commandes. */
};

/**
 * @struct T_mkShellMessageArea
 * @brief Déclaration de la structure T_mkShellMessageArea.
 *
 */

typedef struct T_mkShellMessageArea T_mkShellMessageArea;
struct T_mkShellMessageArea
{
   T_mkMail* mail;                                                     /*!< Ce membre contient la boite de messages permettant l'émission de requêtes à destination des gestionnaires de commandes. */
   T_mkPoolArea area;                                                  /*!< Ce membre contient les caractéristiques mémoire de la boite de messages. */
   uint32_t heap [ K_MK_SHELL_INCOMING_MESSAGE_AREA_SIZE ];            /*!< Ce membre contient la mémoire dédiée à la boite de messages. */
};

/**
 * @struct T_mkShellMemoryPage
 * @brief Déclaration de la structure T_mkShellMemoryPage.
 *
 */

typedef struct T_mkShellMemoryPage T_mkShellMemoryPage;
struct T_mkShellMemoryPage
{
   T_mkAddr baseAddr;                                                  /*!< Ce membre contient l'adresse de base de la page mémoire allouée par le gestionnaire de commandes. */
   T_mkAddr bufferAddr;                                                /*!< Ce membre contient l'adresse du buffer de travail permettant de réaliser les accès en lecture/écriture dans le système de fichier. Il est instancié dans la page mémoire du gestionnaire de commandes. */
};

/**
 * @struct T_mkShellCallbackFunction
 * @brief Création du type T_mkShellCallbackFunction.
 */

typedef T_mkCode ( *T_mkShellCallbackFunction ) ( T_mkShell* p_shell, T_mkConsole* p_console, T_mkAddr p_addr, T_str8 p_str, uint32_t p_length );

/**
 * @struct T_mkShellMemoryRegister
 * @brief Déclaration de la structure T_mkShellMemoryRegister.
 *
 */

typedef struct T_mkShellMemoryRegister T_mkShellMemoryRegister;
struct T_mkShellMemoryRegister
{
   uint32_t cmdInProgress;                                             /*!< Ce membre indique que l'exécution de la commande courante est terminée ou non. */
   T_mkAddr addr;                                                      /*!< Ce membre contient l'adresse d'une structure de travail quelconque. */
   T_mkShellCallbackFunction callback;                                 /*!< Ce membre contient l'adresse de la fonction de rappel exécutée par les commandes à phases multiples. */
};

/**
 * @struct T_mkShell
 * @brief Déclaration de la structure T_mkShell.
 *        Cette stucture est allouée dans un contexte local.
 *
 */

struct T_mkShell
{
   T_mkShellMemoryPage page;                                           /*!< Ce membre contient l'adresse de base de la page mémoire allouée par le gestionnaire de commandes. */
   T_mkShellMemoryRegister reg;                                        /*!< Ce membre contient les registres de contrôle du shell. */
   uint8_t currentDirectory [ K_MK_FILE_MAX_NAME_LENGTH + 1 ];         /*!< Ce membre contient la chaine de caractères du répertoire courant (commande cd). */
};




/**
 *
 */

#endif

