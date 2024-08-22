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
* @file mk_mmc_data.h
* @brief Déclaration des données SD/MMC.
* @date 20 juin 2020
*
*/

#ifndef MK_MMC_DATA_H
#define MK_MMC_DATA_H

/**
 * @fn T_mkMMCPool g_mkMMCPool;
 * @brief Déclaration du gestionnaire d'allocation dynamique des périphériques de type \ref T_mkMMCDevice.
 *
 */

extern T_mkMMCPool g_mkMMCPool;

/**
 * @fn T_mkMMCRequestArea g_mkMMCRequestArea;
 * @brief Déclaration des données relatives à la messagerie du terminal MMC.
 *
 */

extern T_mkMMCRequestArea g_mkMMCRequestArea;

/**
 * @fn uint32_t g_mkMMCStackAddr;
 * @brief Déclaration de la stack du terminal MMC.
 *
 */

extern uint32_t g_mkMMCStackAddr [ K_MK_MMC_STACK_SIZE ];

/**
 * @fn uint8_t g_mkMMCPacketBuf;
 * @brief Déclaration du buffer de données du terminal MMC.
 *
 */

extern uint8_t g_mkMMCPacketBuf [ K_MK_MMC_MAX_PACKET_SIZE ];

/**
 *
 */

#endif


