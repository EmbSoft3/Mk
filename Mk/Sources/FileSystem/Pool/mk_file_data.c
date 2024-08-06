/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_data.c
* @brief Déclaration des données du gestionnaire de fichiers.
* @date 12 juin 2021
*
*/

#include "mk_file_api.h"

/**
 * @fn T_mkFileArea g_mkFileArea;
 * @brief Déclaration du gestionnaire d'allocation dynamique du système de fichiers (\ref T_mkFile).
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY T_mkFileArea g_mkFileArea;

/**
 * @fn T_mkFileMessageArea g_mkFileMessageArea;
 * @brief Déclaration des données relatives à la messagerie du système de fichiers.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY T_mkFileMessageArea g_mkFileMessageArea;

/**
 * @fn T_mkFileMessageArea g_mkFileMessageSharedArea;
 * @brief Déclaration des données relatives à la messagerie partagée du système de fichiers.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY T_mkFileMessageArea g_mkFileMessageSharedArea;

/**
 *
 */

/**
 * @fn uint8_t g_mkFileStackAddr [ K_MK_FILE_NUMBER_OF_TASKS ] [ K_MK_FILE_STACK_SIZE ];
 * @brief Déclaration des stacks dédiées aux tâches du système de fichiers.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY uint32_t g_mkFileStackAddr [ K_MK_FILE_NUMBER_OF_TASKS ] [ K_MK_FILE_STACK_SIZE ];

/**
 * @fn uint8_t g_mkFileBuf [ K_MK_FILE_NUMBER_OF_TASKS ] [ K_MK_FILE_CACHE_SIZE ];
 * @brief Déclaration de buffers stockant le cache du système de fichiers.
 *
 */

K_MK_PRIVILEGED_DMA_MEMORY uint8_t g_mkFileBuf [ K_MK_FILE_NUMBER_OF_TASKS ] [ K_MK_FILE_CACHE_SIZE ];


