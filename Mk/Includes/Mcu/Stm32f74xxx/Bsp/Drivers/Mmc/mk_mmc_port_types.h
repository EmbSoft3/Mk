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
* @file mk_mmc_port_types.h
* @brief Déclaration des types dédiés au port SD/MMC.
* @date 5 juil. 2020
*
*/

#ifndef MK_MMC_PORT_TYPES_H
#define MK_MMC_PORT_TYPES_H

/**
 * @struct T_mkMMCPortStatus
 * @brief Déclaration de l'énumération T_mkMMCPortStatus.
 *
 */

typedef enum T_mkMMCPortStatus
{
   K_MK_MMC_NO_FLAG                       = 0x00000000,                    /*!< Définition d'un code indiquant l'absence de statut. */
   K_MK_MMC_FLAG_CMD_RESPONSE_FAILED      = 0x00000001,                    /*!< Définition d'un code indiquant une différence entre les CRC calculés et transportés d'une réponse. */
   K_MK_MMC_FLAG_DATA_BLOCK_FAILED        = 0x00000002,                    /*!< Définition d'un code indiquant une différence entre les CRC calculés et transportés d'un bloc de données. */
   K_MK_MMC_FLAG_CMD_RESPONSE_TIMEOUT     = 0x00000004,                    /*!< Définition d'un code indiquant la détection d'un timeout suite à la transmission d'une commande. */
   K_MK_MMC_FLAG_TXFIFO_UNDERRUN          = 0x00000010,                    /*!< Définition d'un code indiquant la détection d'un underrun dans le FIFO de transmission. */
   K_MK_MMC_FLAG_RXFIFO_OVERRUN           = 0x00000020,                    /*!< Définition d'un code indiquant la détection d'un overrun dans le FIFO de réception. */
   K_MK_MMC_FLAG_CMD_RESPONSE_RECEIVED    = 0x00000040,                    /*!< Définition d'un code indiquant qu'une réponse a été reçue. */
   K_MK_MMC_FLAG_CMD_SENT                 = 0x00000080,                    /*!< Définition d'un code indiquant qu'une commande a été transmise. */
   K_MK_MMC_START_BIT_NOT_DETECTED        = 0x00000200,                    /*!< Définition d'un code indiquant l'absence des bits de start sur les lignes de données. */
   K_MK_MMC_FLAG_DATA_BLOCK_TRANSFERED    = 0x00000400,                    /*!< Définition d'un code indiquant le transfert d'un bloc de données (entrant ou sortant). */

   K_MK_MMC_TRANSFER_TIMEOUT              = 0x01000000,                    /*!< Définition d'un code indiquant l'arrêt d'un transfert suite à un timeout. */
   K_MK_MMC_TRANSFER_ABORTED              = 0x02000000,                    /*!< Définition d'un code indiquant l'arrêt d'un transfert suite à une erreur de communication. */
   K_MK_MMC_TRANSFER_DONE                 = 0x04000000,                    /*!< Définition d'un code indiquant la complétude d'un transfert. */
   K_MK_MMC_TRANSFER_ERROR                = 0x08000000                     /*!< Définition d'un code indiquant l'arrêt d'un transfert suite à une erreur de communication de type CRC. */
} T_mkMMCPortStatus;

/**
 *
 */

#endif

