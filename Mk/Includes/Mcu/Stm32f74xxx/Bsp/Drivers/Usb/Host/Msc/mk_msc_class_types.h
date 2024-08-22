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
* @file mk_msc_class_types.h
* @brief Définition des classes dédiés aux périphériques de stockage.
* @date 18 mai 2020
*
*/

#ifndef MK_MSC_CLASS_TYPES_H
#define MK_MSC_CLASS_TYPES_H

/**
 * @struct T_mkMSCSubClass
 * @brief Déclaration de la structure T_mkMSCSubClass.
 *
 */

typedef enum T_mkMSCSubClass
{
   K_MK_MSC_SUBCLASS_SCSI_COMMAND_SET = 0x00,                             /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole SCSI. */
   K_MK_MSC_SUBCLASS_RBC = 0x01,                                          /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole RBC. */
   K_MK_MSC_SUBCLASS_MMC5 = 0x02,                                         /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole MMC5 (ATAPI). */
   K_MK_MSC_SUBCLASS_QIC157 = 0x03,                                       /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole QIC-157 (Obsolète). */
   K_MK_MSC_SUBCLASS_UFI = 0x04,                                          /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole UFI (Floppy Disk). */
   K_MK_MSC_SUBCLASS_SFF8070i = 0x05,                                     /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole SFF-8070i (Obsolète). */
   K_MK_MSC_SUBCLASS_SCSI_TRANSPARENT_COMMAND_SET = 0x06,                 /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole SCSI Transparent Command Set. */
   K_MK_MSC_SUBCLASS_LSDFS = 0x07,                                        /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole LSFS. */
   K_MK_MSC_SUBCLASS_IEEE1667 = 0x08,                                     /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole IEEE-1667. */
   K_MK_MSC_SUBCLASS_VENDOR_SPECIFIC = 0xFF                               /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise un protocole spécifique. */
} T_mkMSCSubClass;

/**
 * @struct T_mkMSCProtocolCode
 * @brief Déclaration de la structure T_mkMSCProtocolCode.
 *
 */

typedef enum T_mkMSCProtocolCode
{
   K_MK_MSC_PROTOCOL_CBI_WITH_COMPLETION = 0x00,                          /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole CBI (Contol/Bulk/Interrupt - With Command Completion Interrupt) . */
   K_MK_MSC_PROTOCOL_CBI_WITH_NO_COMPLETION = 0x01,                       /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole CBI (Contol/Bulk/Interrupt - With No Command Completion Interrupt) . */
   K_MK_MSC_PROTOCOL_BBB = 0x50,                                          /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole BBB (Bulk Only Transport). */
   K_MK_MSC_PROTOCOL_UAS = 0x62,                                          /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise le protocole UAS (USB Attached SCSI). */
   K_MK_MSC_PROTOCOL_VENDOR_SPECIFIC = 0xFF                               /*!< Définition d'un code indiquant que le périphérique 'MassStorage' utilise un protocole spécifique. */
} T_mkMSCProtocolCode;

/**
 *
 */

#endif


