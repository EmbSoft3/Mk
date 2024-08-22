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
* @file mk_msc_wrapper_types.h
* @brief Déclaration des types dédiés aux wrappers des périphériques de stockage.
* @date 18 mai 2020
*
*/

#ifndef MK_MSC_WRAPPER_TYPES_H
#define MK_MSC_WRAPPER_TYPES_H

/**
 * @struct T_mkMSCCommandBlockWrapper
 * @brief Déclaration de la structure T_mkMSCCommandBlockWrapper.
 *
 */

typedef enum T_mkMSCommandBlockWrapperFlag
{
   K_MK_MSC_CMD_BLOC_WRAPPER_HOST_TO_DEVICE = 0x00,      /*!< Définition d'une valeur indiquant que le transfert de type "Bulk-Only" s'effectue du maitre vers l'esclave. */
   K_MK_MSC_CMD_BLOC_WRAPPER_DEVICE_TO_HOST = 0x80       /*!< Définition d'une valeur indiquant que le transfert de type "Bulk-Only" s'effectue de l'esclave vers le maitre. */
} T_mkMSCommandBlockWrapperFlag;

/**
 * @struct T_mkMSCCommandBlockWrapper
 * @brief Déclaration de la structure T_mkMSCCommandBlockWrapper.
 *
 */

typedef struct T_mkMSCCommandBlockWrapper T_mkMSCCommandBlockWrapper;
struct T_mkMSCCommandBlockWrapper
{
   uint32_t dCBWSignature;                               /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. Il prend la valeur \ref K_MK_MSC_CMD_BLOC_WRAPPER_SIGNATURE ($43425355). */
   uint32_t dCBWTag;                                     /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint32_t dCBWDataTransferLength;                      /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bmCBWFlags;                                  /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bCBWLUN;                                     /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bCBWCBLength;                                /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  CBWCB[16];                                   /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bPadding8;                                   /*!< Octet de padding. */
};

/**
 * @struct T_mkMSCCommandStatusWrapper
 * @brief Déclaration de la structure T_mkMSCCommandStatusWrapper.
 *
 */

typedef struct T_mkMSCCommandStatusWrapper T_mkMSCCommandStatusWrapper;
struct T_mkMSCCommandStatusWrapper
{
   uint32_t dCSWSignature;                               /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. Il prend la valeur \ref K_MK_MSC_CMD_STATUS_WRAPPER_SIGNATURE ($53425355). */
   uint32_t dCSWTag;                                     /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint32_t dCSWDataResidue;                             /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bCSWStatus;                                  /*!< Champ défini par la spécification 'Bulk-Only Transport' Rev 1.0. */
   uint8_t  bPadding24[3];                               /*!< Octets de padding. */
};

/**
 *
 */

#endif

