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
* @file mk_display_data.c
* @brief Déclaration des données globales du moteur graphique.
* @date 16 mars 2019
*
*/

#include "mk_engine_api.h"

/**
 * @fn T_mkDisplay g_mkDisplay;
 * @brief Déclaration de la structure de gestion du moteur graphique.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY T_mkDisplay g_mkDisplay;

/**
 *
 */

/**
 * @fn uint32_t g_mkUnprivilegedPainterStackBuf [ K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE ];
 * @brief Déclaration de la stack de la tâche de peinture non privilégiée (painter).
 *
 */

K_MK_UNPRIVILEGED_MEMORY uint32_t g_mkUnprivilegedPainterStackBuf [ K_MK_DISPLAY_TASK_UNPRIVILEGED_PAINTER_STACK_SIZE ];

/**
 * @fn uint32_t g_mkUnprivilegedListenerStackBuf [ K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE ];
 * @brief Déclaration de la stack de la tâche d'écoute non privilégiée (listener).
 *
 */

K_MK_UNPRIVILEGED_MEMORY uint32_t g_mkUnprivilegedListenerStackBuf [ K_MK_DISPLAY_TASK_UNPRIVILEGED_LISTENER_STACK_SIZE ];

/**
 * @fn uint32_t g_mkUnprivilegedHandlerMessageHeap [ K_MK_DISPLAY_REQUEST_AREA_SIZE ];
 * @brief Déclaration du buffer de données de la messagerie du moteur graphique.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY uint32_t g_mkUnprivilegedHandlerMessageHeap [ K_MK_DISPLAY_REQUEST_AREA_SIZE ];


