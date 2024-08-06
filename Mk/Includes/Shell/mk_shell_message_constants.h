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
* @file mk_shell_message_constants.h
* @brief Définition des messages de sorties de chaque commandes.
* @date 25 févr. 2024
*
*/

#ifndef MK_SHELL_MESSAGE_CONSTANTS_H
#define MK_SHELL_MESSAGE_CONSTANTS_H

/**
 * @def MK_SHELL_MESSAGE_INSTALL_HELP_MESSAGE
 * @brief Définition du message "HELP_INSTALL" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_HELP_MESSAGE \
"\n\
Descr: installs an application on the system\n\
Usage: install elf-file <option(s)>\n\
Option(s) are:\n\
\t -s set arguments of the application\n\
\t -l launch the application after installation\n\n"

/**
 * @def MK_SHELL_MESSAGE_INSTALL_INVALID_CMD_LINE
 * @brief Définition du message "INVALID_CMD_LINE" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_INVALID_CMD_LINE \
"\n\
install: Warning: Nothing to do.\n\
Usage: install elf-file <option(s)>\n\
Option(s) are:\n\
\t -s set arguments of the application\n\
\t -l launch the application after installation\n\n"

/**
 * @def MK_SHELL_MESSAGE_INSTALL_FILE_NOT_FOUND
 * @brief Définition du message "FILE_NOT_FOUND" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_FILE_NOT_FOUND \
"\n\
install: Warning: File not found.\n\
Usage: install elf-file <option(s)>\n\
Option(s) are:\n\
\t -s set arguments of the application\n\
\t -l launch the application after installation\n\n"

/**
 * @def MK_SHELL_MESSAGE_INSTALL_FAIL_TO_LAUNCH
 * @brief Définition du message "FAIL_TO_LAUNCH" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_FAIL_TO_LAUNCH \
"\n\
install: Unexpected: Could not launch the application.\n\n"

/**
 * @def MK_SHELL_MESSAGE_INSTALL_INVALID_PATH_LENGTH
 * @brief Définition du message "INVALID_PATH_LENGTH" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_INVALID_PATH_LENGTH \
"\n\
install: Warning: invalid path length.\n\n"

/**
 * @def MK_SHELL_MESSAGE_INSTALL_FILE_NOT_FOUND
 * @brief Définition du message "SUCCESS" de la commande "install".
 */

#define MK_SHELL_MESSAGE_INSTALL_SUCCEES \
"\n\
install: the application has been installed successfully.\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_UNINSTALL_HELP_MESSAGE
 * @brief Définition du message "HELP_UNINSTALL" de la commande "uninstall".
 */

#define MK_SHELL_MESSAGE_UNINSTALL_HELP_MESSAGE \
"\n\
Descr: uninstalls an application on the system\n\
Usage: uninstall <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to uninstall\n\n"

/**
 * @def MK_SHELL_MESSAGE_UNINSTALL_APP_NOT_FOUND
 * @brief Définition du message "APP_NOT_FOUND" de la commande "uninstall".
 */

#define MK_SHELL_MESSAGE_UNINSTALL_APP_NOT_FOUND \
"\n\
uninstall: Warning: Application not found.\n\
Usage: uninstall <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to uninstall\n\n"

/**
 * @def MK_SHELL_MESSAGE_UNINSTALL_APP_STATIC
 * @brief Définition du message "APPS_STATIC" de la commande "uninstall".
 */

#define MK_SHELL_MESSAGE_UNINSTALL_APP_STATIC \
"\n\
uninstall: Warning: Application type not valid (static).\n\
Usage: uninstall <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to uninstall\n\n"

/**
 * @def MK_SHELL_MESSAGE_UNINSTALL_SUCCEES
 * @brief Définition du message "SUCCESS" de la commande "uninstall".
 */

#define MK_SHELL_MESSAGE_UNINSTALL_SUCCEES \
"\n\
uninstall: the application has been uninstalled successfully.\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_LAUNCH_HELP_MESSAGE
 * @brief Définition du message "HELP_LAUNCH" de la commande "launch".
 */

#define MK_SHELL_MESSAGE_LAUNCH_HELP_MESSAGE \
"\n\
Descr: run an installed application\n\
Usage: launch <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to launch\n\n"

/**
 * @def MK_SHELL_MESSAGE_LAUNCH_APP_NOT_FOUND
 * @brief Définition du message "APP_NOT_FOUND" de la commande "launch".
 */

#define MK_SHELL_MESSAGE_LAUNCH_APP_NOT_FOUND \
"\n\
launch: Warning: Application not found.\n\
Usage: launch <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to launch\n\n"

/**
 * @def MK_SHELL_MESSAGE_LAUNCH_ALREADY_RUNNING
 * @brief Définition du message "ALREADY_RUNNING" de la commande "launch".
 */

#define MK_SHELL_MESSAGE_LAUNCH_ALREADY_RUNNING \
"\n\
launch: Warning: Application already ready.\n\
Usage: launch <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to launch\n\n"

/**
 * @def MK_SHELL_MESSAGE_LAUNCH_SUCCEES
 * @brief Définition du message "SUCCESS" de la commande "launch".
 */

#define MK_SHELL_MESSAGE_LAUNCH_SUCCEES \
"\n\
launch: the application has been launch successfully.\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_TERMINATE_HELP_MESSAGE
 * @brief Définition du message "HELP_TERMINATE" de la commande "terminate".
 */

#define MK_SHELL_MESSAGE_TERMINATE_HELP_MESSAGE \
"\n\
Descr: ends the execution of an application\n\
Usage: terminate <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to terminate\n\n"

/**
 * @def MK_SHELL_MESSAGE_TERMINATE_APP_NOT_FOUND
 * @brief Définition du message "APP_NOT_FOUND" de la commande "terminate".
 */

#define MK_SHELL_MESSAGE_TERMINATE_APP_NOT_FOUND \
"\n\
terminate: Warning: Application not found.\n\
Usage: terminate <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to terminate\n\n"

/**
 * @def MK_SHELL_MESSAGE_TERMINATE_NOT_RUNNING
 * @brief Définition du message "NOT_RUNNING" de la commande "terminate".
 */

#define MK_SHELL_MESSAGE_TERMINATE_NOT_RUNNING \
"\n\
terminate: Warning: Application not running.\n\
Usage: terminate <pid>\n\
Parameter(s) are:\n\
\t <PID> pid of the application to terminate\n\n"

/**
 * @def MK_SHELL_MESSAGE_TERMINATE_SUCCEES
 * @brief Définition du message "SUCCESS" de la commande "terminate".
 */

#define MK_SHELL_MESSAGE_TERMINATE_SUCCEES \
"\n\
terminate: the application has been terminate successfully.\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_GETAPPS_HELP_MESSAGE
 * @brief Définition du message "HELP_GETAPPS" de la commande "get-apps".
 */

#define MK_SHELL_MESSAGE_GETAPPS_HELP_MESSAGE \
"\n\
Descr: list all installed applications\n\
Usage: get-apps <option(s)>\n\
Option(s) are:\n\
\t <PID> pid of the application to display\n\
\t       omit this parameter to list all applications\n\n"

/**
 * @def MK_SHELL_MESSAGE_GETAPPS_APP_NOT_FOUND
 * @brief Définition du message "APP_NOT_FOUND" de la commande "get-apps".
 */

#define MK_SHELL_MESSAGE_GETAPPS_APP_NOT_FOUND \
"\n\
get-apps: Warning: Application not found.\n\
Usage: get-apps <option(s)>\n\
Option(s) are:\n\
\t <PID> pid of the application to display\n\
\t       omit this parameter to list all applications\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_ABORT_HELP_MESSAGE
 * @brief Définition du message "HELP_ABORT" de la commande "abort".
 */

#define MK_SHELL_MESSAGE_ABORT_HELP_MESSAGE \
"\n\
Descr: abort a command\n\
Usage: abort\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_CLS_HELP_MESSAGE
 * @brief Définition du message "HELP_CLS" de la commande "cls".
 */

#define MK_SHELL_MESSAGE_CLS_HELP_MESSAGE \
"\n\
Descr: clear the console\n\
Usage: cls\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_RESET_HELP_MESSAGE
 * @brief Définition du message "HELP_RESET" de la commande "reset".
 */

#define MK_SHELL_MESSAGE_RESET_HELP_MESSAGE \
"\n\
Descr: restart the system\n\
Usage: reset\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_RESTART_HELP_MESSAGE
 * @brief Définition du message "HELP_RESET" de la commande "restart".
 */

#define MK_SHELL_MESSAGE_RESTART_HELP_MESSAGE \
"\n\
Descr: restart the system\n\
Usage: restart\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_HELP_LIST
 * @brief Définition du message "HELP_LIST" de la commande "help".
 */

#define MK_SHELL_MESSAGE_HELP_LIST \
"\n\
Usage: help <option>\n\
Option is:\n\n\
\t install   installs an application on the system\n\
\t uninstall uninstalls an application on the system\n\
\t launch    run an installed application\n\
\t terminate ends the execution of an application\n\
\t get-apps  list all installed applications\n\n\
\t abort     abort command\n\
\t cls       clear the console\n\
\t reset     restart the system\n\
\t restart   restart the system with confirmation\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_CMD_LINE
 * @brief Définition du message "INVALID_CMD_LINE" de la commande "cd".
 */

#define MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_CMD_LINE \
"\n\
cd: Warning: nothing to do.\n\
Usage: cd <path>\n\n"

/**
 * @def MK_SHELL_MESSAGE_FILESYSTEM_CD_DIRECTORY_NOT_FOUND
 * @brief Définition du message "DIRECTORY_NOT_FOUND" de la commande "cd".
 */

#define MK_SHELL_MESSAGE_FILESYSTEM_CD_DIRECTORY_NOT_FOUND \
"\n\
cd: Warning: directory not found.\n\
Usage: cd <path>\n\n"

/**
 * @def MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_PATH_LENGTH
 * @brief Définition du message "INVALID_PATH_LENGTH" de la commande "cd".
 */

#define MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_PATH_LENGTH \
"\n\
cd: Warning: invalid path length.\n\
Usage: cd <path>\n\n"

/**
 * @def MK_SHELL_MESSAGE_FILESYSTEM_CD_NOT_DIRECTORY
 * @brief Définition du message "NOT_DIRECTORY" de la commande "cd".
 */

#define MK_SHELL_MESSAGE_FILESYSTEM_CD_NOT_DIRECTORY \
"\n\
cd: Warning: not a directory.\n\
Usage: cd <path>\n\n"

/**
 *
 */

/**
 * @def MK_SHELL_MESSAGE_FILESYSTEM_LS_DIRECTORY_NOT_FOUND
 * @brief Définition du message "DIRECTORY_NOT_FOUND" de la commande "ls".
 */

#define MK_SHELL_MESSAGE_FILESYSTEM_LS_DIRECTORY_NOT_FOUND \
"ls: Warning: directory not found.\n\
Usage: cd <path>\n\n"

/**
 *
 */

#endif


