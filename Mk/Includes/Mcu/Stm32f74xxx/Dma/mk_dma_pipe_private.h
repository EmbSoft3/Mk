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
* @file mk_dma_pipe_private.h
* @brief Déclaration des fonctions privées dédiées aux pipes DMA.
* @date 26 juin 2020
*
*/

#ifndef MK_DMA_PIPE_PRIVATE_H
#define MK_DMA_PIPE_PRIVATE_H

/**
 * @fn T_mkCode mk_dma_openPipe ( T_mkDMAPipe* p_pipe, T_mkAddr p_dma, uint32_t p_channel, uint32_t p_stream, uint32_t p_priority );
 * @brief Cette fonction ouvre un pipe de type \ref T_mkDMAPipe.
 *
 * @param[in, out] p_pipe     Ce paramètre contient l'adresse d'un pipe de type \ref T_mkDMAPipe.
 * @param[in]      p_callback Ce paramètre contient l'adresse de la fonction de rappel DMA dédiée au périphérique MMC.
 * @param[in]      p_dma      Ce paramètre contient l'adresse matérielle d'un périphérique DMA. Une des constantes suivantes peut être utlisée :\n
 *                            \ref K_DMA1 et \ref K_DMA2
 * @param[in]      p_channel  Ce paramètre contient le numéro du canal DMA à ouvrir. Une des constantes suivantes peut être utlisée :\n
 *                            \ref K_DMA_CHANNEL0 à \ref K_DMA_CHANNEL7
 * @param[in]      p_stream   Ce paramètre contient le numéro du flux DMA à ouvrir. Une des constantes suivantes peut être utlisée :\n
 *                            \ref K_DMA_STREAM0 à \ref K_DMA_STREAM7
 * @param[in]      p_priority Ce paramètre contient la priorité du flux DMA. Une des constantes suivantes peut être utilisée :\n
 *                            \ref K_DMA_PRIORITY_LOW, \ref K_DMA_PRIORITY_MEDIUM, \ref K_DMA_PRIORITY_HIGH, \ref K_DMA_PRIORITY_VERY_HIGH
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pipe a été correctement ouvert.
 *         \li \ref K_MK_ERROR_PARAM   : le pipe n'a pas été ouvert car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : le pipe n'a pas été ouvert car la fonction a été exécutée depuis un vecteur d'interruption.
 */

T_mkCode mk_dma_openPipe ( T_mkDMAPipe** p_pipe, T_mkDMACallback p_callback, T_mkAddr p_dma, uint32_t p_channel, uint32_t p_stream, uint32_t p_priority );

/**
 * @fn T_mkCode mk_dma_closePipe ( T_mkDMAPipe* p_pipe );
 * @brief Cette fonction ferme un pipe de type \ref T_mkDMAPipe.
 * @param[in, out] p_pipe Ce paramètre contient l'adresse d'un pipe de type \ref T_mkDMAPipe.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : le pipe a été fermé correctement.
 *         \li \ref K_MK_ERROR_PARAM   : le pipe n'a pas été fermé car au moins un paramètre est invalide.
 */

T_mkCode mk_dma_closePipe ( T_mkDMAPipe* p_pipe );

/**
 *
 */

#endif


