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
* @file mk_display_console_types.h
* @brief Déclaration des types dédiés à l'objet 'Console'.
* @date 5 févr. 2023
*
*/

#ifndef MK_DISPLAY_CONSOLE_TYPES_H
#define MK_DISPLAY_CONSOLE_TYPES_H

/**
 * @enum T_mkConsoleField
 * @brief Déclaration de la structure T_mkConsoleField.
 */

typedef enum T_mkConsoleField
{
   K_MK_CONSOLE_WINDOW = 0,            /*!< Définition de l'identifiant de la fenêtre de la console. */
   K_MK_CONSOLE_PROMPT = 1,            /*!< Définition de l'identifiant du prompt de la console. */
   K_MK_CONSOLE_SCREEN = 2             /*!< Définition de l'identifiant de la zone de titre de la console. */
} T_mkConsoleField;

/**
 * @struct T_mkConsoleForeground
 * @brief Déclaration de la structure T_mkConsoleForeground.
 */

typedef struct T_mkConsoleForeground T_mkConsoleForeground;
struct T_mkConsoleForeground
{
   T_mkScreen screen;                  /*!< Ce membre contient un fond d'écran de type \ref T_mkScreen. */
   T_mkEditField window;               /*!< Ce membre contient une boite d'édition de type \ref T_mkEditField ('Window'). */
   T_mkEditField prompt;               /*!< Ce membre contient une boite d'édition de type \ref T_mkEditField ('Prompt'). */
};

/**
 * @struct T_mkConsoleWindow
 * @brief Déclaration de la structure T_mkConsoleWindow.
 */

typedef struct T_mkConsoleWindow T_mkConsoleWindow;
struct T_mkConsoleWindow
{
   T_mkFile* file;                     /*!< Ce membre contient l'adresse d'un fichier de type \ref T_mkFile. Il constitue la sortie standard de la console (STDOUT). */
   uint32_t  filePointer;              /*!< Ce membre contient la valeur du pointeur de fichier de la console. */
   T_mkAddr  buf;                      /*!< Ce membre contient l'adresse du buffer stockant les données de la boite d'édition ('Window'). */
   uint32_t  bufSize;                  /*!< Ce membre contient la taille du buffer stockant les données de la boite d'édition ('Window'). */
   uint32_t  localEcho;                /*!< Ce membre contient le registre permettant d'activer l'echo local (\ref K_MK_CONSOLE_LOCALECHO_ENABLED ou \ref K_MK_CONSOLE_LOCALECHO_DISABLED). */
};

/**
 * @struct T_mkConsolePrompt
 * @brief Déclaration de la structure T_mkConsolePrompt.
 */

typedef struct T_mkConsolePrompt T_mkConsolePrompt;
struct T_mkConsolePrompt
{
   T_mkFile* file;                     /*!< Ce membre contient l'adresse d'un fichier de type \ref T_mkFile. Il constitue l'entrée standard de la console (STDIN). */
   T_mkAddr  buf;                      /*!< Ce membre contient l'adresse du buffer stockant les données de la boite d'édition ('Prompt'). */
   uint32_t  bufSize;                  /*!< Ce membre contient la taille du buffer stockant les données de la boite d'édition ('Prompt'). */
};

/**
 * @struct T_mkConsole
 * @brief Déclaration de la structure T_mkConsole.
 */

typedef struct T_mkConsole T_mkConsole;
struct T_mkConsole
{
   T_mkAddr child;                     /*!< Ce membre contient l'adresse du descendant de la console (héritage). */
   T_mkSemaphore* semaphore;           /*!< Ce membre contient l'adresse du sémaphore de la console. */
   T_mkConsoleWindow window;           /*!< Ce membre contient les attributs de la boite d'édition ('Window'). */
   T_mkConsolePrompt prompt;           /*!< Ce membre contient les attributs de la boite d'édition ('Prompt'). */
   T_mkConsoleForeground foreground;   /*!< Ce membre contient les objets graphiques de la console. */
};

/**
 *
 */

#endif


