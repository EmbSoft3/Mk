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
* @file mk_display_tasks_constants.h
* @brief Déclaration des constantes relatives aux tâches du module 'Display'.
* @date 24 mars 2019
*
*/

#ifndef K_MK_DISPLAY_TASKS_CONSTANTS_H
#define K_MK_DISPLAY_TASKS_CONSTANTS_H

/**
 * @def K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE
 * @brief Définition de la taille de la stack du gestionnaire de requêtes [en multiple de mots 32bits].\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_TASK_HANDLER_STACK_SIZE 1024

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE
 * @brief Définition de la taille de la stack de peinture privilégiée [en multiple de mots 32bits].\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_STACK_SIZE 1024

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE
 * @brief Définition de la taille de la stack de peinture non privilégiée [en multiple de mots 32bits].\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE 1024

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE
 * @brief Définition de la taille de la stack d'écoute privilégiée [en multiple de mots 32bits].\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_STACK_SIZE 512

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE
 * @brief Définition de la taille de la stack d'écoute non privilégiée [en multiple de mots 32bits].\n
 *        Cette constante peut être modifiée par l'utilisateur.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE 1024

/**
 *
 */

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT
 * @brief Définition de la durée d'activité maximale de la tâche de peinture non priviligiée [en sec/frame].
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_TASK_TIMEOUT 10000

/**
 *
 */

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_PRIORITY
 * @brief Définition de la priorité de la tâche de peinture privilégiée.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_PRIORITY 5

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_PRIORITY
 * @brief Définition de la priorité de la tâche de peinture non privilégiée.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_PRIORITY 4

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_PRIORITY
 * @brief Définition de la priorité de la tâche d'écoute privilégiée.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_PRIORITY 7

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_PRIORITY
 * @brief Définition de la priorité de la tâche d'écoute non privilégiée.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_PRIORITY 6

/**
 * @def K_MK_DISPLAY_TASK_HANDLER_PRIORITY
 * @brief Définition de la priorité du gestionnaire de requêtes.
 */

#define K_MK_DISPLAY_TASK_HANDLER_PRIORITY 8

/**
 *
 */

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG
 * @brief Définition de l'identifiant de la tâche de peinture privilégiée dans le registre d'événements.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_PAINTER_EVENT_FLAG 0x00000001

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_EVENT_FLAG
 * @brief Définition de l'identifiant de la tâche de peinture non-privilégiée dans le registre d'événements.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_EVENT_FLAG 0x0000002

/**
 *
 */

/**
 * @def K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_EVENT_FLAG
 * @brief Définition de l'identifiant de la tâche d'écoute privilégiée dans le registre d'événements.
 */

#define K_MK_DISPLAY_TASK_PRIVILEGED_LISTENER_EVENT_FLAG 0x00000001

/**
 * @def K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_EVENT_FLAG
 * @brief Définition de l'identifiant de la tâche d'écoute non-privilégiée dans le registre d'événements.
 */

#define K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_EVENT_FLAG 0x0000002

/**
 *
 */

/**
 * @def K_MK_DISPLAY_TASK_CHROMART_EVENT_FLAG
 * @brief Définition de l'identifiant de l'accélérateur graphique dans le registre d'événements matériels.
 */

#define K_MK_DISPLAY_TASK_CHROMART_EVENT_FLAG 0x00000001

/**
 *
 */

#endif

