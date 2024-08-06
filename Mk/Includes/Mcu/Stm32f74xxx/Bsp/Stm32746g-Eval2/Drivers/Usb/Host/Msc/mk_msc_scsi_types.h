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
* @file mk_msc_scsi_types.h
* @brief Déclaration des types dédiés aux protocoles SCSI des périphériques de stockage.
* @date 19 mai 2020
*
*/

#ifndef MK_MSC_SCSI_TYPES_H
#define MK_MSC_SCSI_TYPES_H

/**
 * @enum T_mkSCSI_OPCode
 * @brief Déclaration de la structure T_mkSCSI_OPCode.
 *
 */

typedef enum T_mkSCSI_OPCode
{
   K_MK_SCSI_OPCODE_TEST_UNIT_READY = 0x00,
   K_MK_SCSI_OPCODE_REQUEST_SENSE = 0x03,
   K_MK_SCSI_OPCODE_INQUIRY = 0x12,
   K_MK_SCSI_OPCODE_MODE_SENSE = 0x1A,
   K_MK_SCSI_OPCODE_READ_FORMAT_CAPACITIES = 0x23,
   K_MK_SCSI_OPCODE_READ_CAPACITY = 0x25,
   K_MK_SCSI_OPCODE_READ10 = 0x28,
   K_MK_SCSI_OPCODE_READ16 = 0x88,
   K_MK_SCSI_OPCODE_WRITE10 = 0x2A,
   K_MK_SCSI_OPCODE_WRITE16 = 0x8A
} T_mkSCSI_OPCode;

/**
 * @enum T_mkSCSI_DeviceType
 * @brief Déclaration de la structure T_mkSCSI_DeviceType.
 *
 */

typedef enum T_mkSCSI_DeviceType
{
   K_MK_SCSI_TYPE_DIRECT_ACCESS_BLOCK_DEVICE = 0x00,
   K_MK_SCSI_TYPE_SEQUENTIAL_ACCESS_DEVICE = 0x01,
   K_MK_SCSI_TYPE_PRINTER_DEVICE = 0x02,
   K_MK_SCSI_TYPE_PROCESSOR_DEVICE = 0x03,
   K_MK_SCSI_TYPE_WRITE_ONCE_DEVICE = 0x04,
   K_MK_SCSI_TYPE_CD_DVD_DEVICE = 0x05,
   K_MK_SCSI_TYPE_SCANNER_DEVICE = 0x06,
   K_MK_SCSI_TYPE_OPTICAL_MEMORY_DEVICE = 0x07,
   K_MK_SCSI_TYPE_MEDIUM_CHANGER_DEVICE = 0x08,
   K_MK_SCSI_TYPE_COMMUNICATION_DEVICE = 0x09,
   K_MK_SCSI_TYPE_OBSOLETE_DEVICE_1 = 0x0A,
   K_MK_SCSI_TYPE_OBSOLETE_DEVICE_2 = 0x0B,
   K_MK_SCSI_TYPE_MSC_ARRAY_CONTROLLER_DEVICE = 0x0C,
   K_MK_SCSI_TYPE_ENCLOSURE_SERVICES_DEVICE = 0x0D,
   K_MK_SCSI_TYPE_SIMPLIFIED_DIRECT_ACESS_DEVICE = 0x0E,
   K_MK_SCSI_TYPE_OPTICAL_CARD_READER_WRITER_DEVICE = 0x0F,
   K_MK_SCSI_TYPE_BRIDGE_CONTROLLER_COMMANDS = 0x10,
   K_MK_SCSI_TYPE_OBJECT_BASED_MSC_DEVICE = 0x11,
   K_MK_SCSI_TYPE_AUTOMATION_DRIVE_INTERFACE = 0x12,
   K_MK_SCSI_TYPE_WELL_KNOWN_LOGICAL_UNIT = 0x1E,
   K_MK_SCSI_TYPE_UNKNOWN = 0x1F
} T_mkSCSI_DeviceType;

/**
 * @enum T_mkSCSI_DeviceQualifier
 * @brief Déclaration de la structure T_mkSCSI_DeviceQualifier.
 *
 */

typedef enum T_mkSCSI_DeviceQualifier
{
   K_MK_SCSI_DEVICE_QUALIFIER_CONNECTED = 0x00,
   K_MK_SCSI_DEVICE_QUALIFIER_NOT_CONNECTED = 0x01,
   K_MK_SCSI_DEVICE_QUALIFIER_NOT_SUPPORTED = 0x03
} T_mkSCSI_DeviceQualifier;

/**
 * @enum T_mkSCSI_SenseKey
 * @brief Déclaration de la structure T_mkSCSI_SenseKey.
 *
 */

typedef enum T_mkSCSI_SenseKey
{
   K_MK_SCSI_NO_SENSE = 0x00,
   K_MK_SCSI_SOFT_ERROR = 0x01,
   K_MK_SCSI_NOT_READY = 0x02,
   K_MK_SCSI_MEDIUM_ERROR = 0x03,
   K_MK_SCSI_HARDWARE_ERROR = 0x04,
   K_MK_SCSI_ILLEGAL_REQUEST = 0x05,
   K_MK_SCSI_UNIT_ATTENTION = 0x06,
   K_MK_SCSI_DATA_PROTECT = 0x07,
   K_MK_SCSI_ABORTED_COMMAND = 0x0B,
   K_MK_SCSI_OTHER = 0x0E
} T_mkSCSI_SenseKey;

/**
 * @enum T_mkSCSI_SenseKey
 * @brief Déclaration de la structure T_mkSCSI_SenseKey.
 *
 */

typedef enum T_mkSCSI_SenseCode_NotReady
{
   K_MK_SCSI_SENSE_CODE_MEDIA_NOT_PRESENT = 0x3A00
} T_mkSCSI_SenseCode_NotReady;

/**
 *
 */

/**
 * @struct T_mkSCSI_InquiryRequest
 * @brief Déclaration de la structure T_mkSCSI_InquiryRequest.
 *
 */

typedef struct T_mkSCSI_InquiryRequest T_mkSCSI_InquiryRequest;
struct T_mkSCSI_InquiryRequest
{
   unsigned_t opcode:8;
   unsigned_t evpd:1;
   unsigned_t obsolete:1;
   unsigned_t reserved:6;
   unsigned_t pageCode:8;
   unsigned_t msbLength:8;
   unsigned_t lsbLength:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_InquiryPacket
 * @brief Déclaration de la structure T_mkSCSI_InquiryPacket.
 *
 */

typedef struct T_mkSCSI_InquiryPacket T_mkSCSI_InquiryPacket;
struct T_mkSCSI_InquiryPacket
{
   unsigned_t peripheralDeviceType:5;
   unsigned_t peripheralQualifier:3;
   unsigned_t reserved:7;
   unsigned_t rmb:1;
   unsigned_t version:8;
   unsigned_t responseDataFormat:4;
   unsigned_t hisup:1;
   unsigned_t normaca:1;
   unsigned_t obsolete1:2;
   unsigned_t additionalLength:8;
   unsigned_t protect:1;
   unsigned_t reserved1:2;
   unsigned_t pc:1;
   unsigned_t tpgs:2;
   unsigned_t acc:1;
   unsigned_t sccs:1;
   unsigned_t obsolete2:4;
   unsigned_t multip:1;
   unsigned_t vs1:1;
   unsigned_t encserv:1;
   unsigned_t obsolete3:1;
   unsigned_t vs2:1;
   unsigned_t cmsque:1;
   unsigned_t obsolete4:6;
   char8_t  vid  [8];
   char8_t  pid  [16];
   char8_t  prev [4];
};

/**
 *
 */

/**
 * @struct T_mkSCSI_ReadFormatCapacitiesRequest
 * @brief Déclaration de la structure T_mkSCSI_ReadFormatCapacitiesRequest.
 *
 */

typedef struct T_mkSCSI_ReadFormatCapacitiesRequest T_mkSCSI_ReadFormatCapacitiesRequest;
struct T_mkSCSI_ReadFormatCapacitiesRequest
{
   unsigned_t opcode:8;
   unsigned_t reserved1:8;
   unsigned_t reserved2:16;
   unsigned_t reserved3:24;
   unsigned_t msbLength:8;
   unsigned_t lsbLength:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_ReadFormatCapacitiesPacket
 * @brief Déclaration de la structure T_mkSCSI_ReadFormatCapacitiesRequest.
 *
 */

typedef struct T_mkSCSI_ReadFormatCapacitiesPacket T_mkSCSI_ReadFormatCapacitiesPacket;
struct T_mkSCSI_ReadFormatCapacitiesPacket
{
   unsigned_t reserved1:24;
   unsigned_t capacityListLength:8;
   unsigned_t numberOfBlocks;
   unsigned_t desciptorType:2;
   unsigned_t reserved2:6;
   unsigned_t blockLength:24;
};

/**
 *
 */

/**
 * @struct T_mkSCSI_ReadCapacityRequest
 * @brief Déclaration de la structure T_mkSCSI_ReadCapacityRequest.
 *
 */

typedef struct T_mkSCSI_ReadCapacityRequest T_mkSCSI_ReadCapacityRequest;
struct T_mkSCSI_ReadCapacityRequest
{
   unsigned_t opcode:8;
   unsigned_t reserved:8;
   unsigned_t highLogicalBlockAdress:16;
   unsigned_t lowLogicalBlockAdress:16;
   unsigned_t reserved1:16;
   unsigned_t pmi:1;
   unsigned_t reserved2:7;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_ReadCapacityPacket
 * @brief Déclaration de la structure T_mkSCSI_ReadCapacityPacket.
 *
 */

typedef struct T_mkSCSI_ReadCapacityPacket T_mkSCSI_ReadCapacityPacket;
struct T_mkSCSI_ReadCapacityPacket
{
   uint32_t logicalBlockAdress;
   uint32_t blockLength;
};

/**
 *
 */

/**
 * @struct T_mkSCSI_TestUnitReadyRequest
 * @brief Déclaration de la structure T_mkSCSI_TestUnitReadyRequest.
 *
 */

typedef struct T_mkSCSI_TestUnitReadyRequest T_mkSCSI_TestUnitReadyRequest;
struct T_mkSCSI_TestUnitReadyRequest
{
   unsigned_t opcode:8;
   unsigned_t reserved1:8;
   unsigned_t reserved2:8;
   unsigned_t reserved3:8;
   unsigned_t reserved4:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 *
 */

/**
 * @struct T_mkSCSI_ModeSenseRequest
 * @brief Déclaration de la structure T_mkSCSI_ModeSenseRequest.
 *
 */

typedef struct T_mkSCSI_ModeSenseRequest T_mkSCSI_ModeSenseRequest;
struct T_mkSCSI_ModeSenseRequest
{
   unsigned_t opcode:8;
   unsigned_t reserved1:3;
   unsigned_t dbd:1;
   unsigned_t reserved2:4;
   unsigned_t pageCode:6;
   unsigned_t pc:2;
   unsigned_t subPageCode:8;
   unsigned_t length:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_ModeSensePacket
 * @brief Déclaration de la structure T_mkSCSI_ModeSensePacket.
 *
 */

typedef struct T_mkSCSI_ModeSensePacket T_mkSCSI_ModeSensePacket;
struct T_mkSCSI_ModeSensePacket
{
   unsigned_t modeDataLength:8;
   unsigned_t mediumType:8;
   unsigned_t reserved1:4;
   unsigned_t dpofua:1;
   unsigned_t reserved2:2;
   unsigned_t wp:1;
   unsigned_t blockDescriptorLength:8;
};

/**
 *
 */

/**
 * @struct T_mkSCSI_RequestSenseRequest
 * @brief Déclaration de la structure T_mkSCSI_RequestSenseRequest.
 *
 */

typedef struct T_mkSCSI_RequestSenseRequest T_mkSCSI_RequestSenseRequest;
struct T_mkSCSI_RequestSenseRequest
{
   unsigned_t opcode:8;
   unsigned_t desc:1;
   unsigned_t reserved:23;
   unsigned_t length:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_RequestSensePacket
 * @brief Déclaration de la structure T_mkSCSI_RequestSensePacket.
 *
 */

typedef struct T_mkSCSI_RequestSensePacket T_mkSCSI_RequestSensePacket;
struct T_mkSCSI_RequestSensePacket
{
   unsigned_t responseCode:4;
   unsigned_t valid:1;
   unsigned_t segmentNumber:8;
   unsigned_t senseKey:4;
   unsigned_t reserved:1;
   unsigned_t incorrectLength:1;
   unsigned_t endOfMedia:1;
   unsigned_t fileMark:1;
   unsigned_t highInformation:8;
   unsigned_t lowInformation:24;
   unsigned_t additionalSenseLength:8;
   unsigned_t cmdSpecificInformation:32;
   unsigned_t additionalSenseCode:8;
   unsigned_t additionalSenseCodeQualifier:8;
   unsigned_t fieldReplaceableUnitCode:8;
   unsigned_t lowSensKeySpecific:8;
   unsigned_t highSensKeySpecific:16;
   unsigned_t padding:16;
};

/**
 *
 */

/**
 * @struct T_mkSCSI_ReadRequest
 * @brief Déclaration de la structure T_mkSCSI_ReadRequest.
 *
 */

typedef struct T_mkSCSI_ReadRequest T_mkSCSI_ReadRequest;
struct T_mkSCSI_ReadRequest
{
   unsigned_t opcode:8;
   unsigned_t obsolete:2;
   unsigned_t rarc:1;
   unsigned_t fua:1;
   unsigned_t dpo:1;
   unsigned_t rdProtect:3;
   unsigned_t highMsbLogicalBlockAddress:8;
   unsigned_t lowMsbLogicalBlockAddress:8;
   unsigned_t highLsbLogicalBlockAddress:8;
   unsigned_t lowLsbLogicalBlockAddress:8;
   unsigned_t groupNumber:5;
   unsigned_t reserved:3;
   unsigned_t highTransferLength:8;
   unsigned_t lowTransferLength:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_Read64Request
 * @brief Déclaration de la structure T_mkSCSI_Read64Request.
 *
 */

typedef struct T_mkSCSI_Read64Request T_mkSCSI_Read64Request;
struct T_mkSCSI_Read64Request
{
   unsigned_t opcode:8;
   unsigned_t dld2:1;
   unsigned_t obsolete:1;
   unsigned_t rarc:1;
   unsigned_t fua:1;
   unsigned_t dpo:1;
   unsigned_t rdProtect:3;
   unsigned_t highMsbExtendedLogicalBlockAddress:8;
   unsigned_t lowMsbExtendedLogicalBlockAddress:8;
   unsigned_t highLsbExtendedLogicalBlockAddress:8;
   unsigned_t lowLsbExtendedLogicalBlockAddress:8;
   unsigned_t highMsbLogicalBlockAddress:8;
   unsigned_t lowMsbLogicalBlockAddress:8;
   unsigned_t highLsbLogicalBlockAddress:8;
   unsigned_t lowLsbLogicalBlockAddress:8;
   unsigned_t highMsbTransferLength:8;
   unsigned_t lowMsbTransferLength:8;
   unsigned_t highLsbTransferLength:8;
   unsigned_t lowLsbTransferLength:8;
   unsigned_t groupNumber:6;
   unsigned_t dld0:1;
   unsigned_t dld1:1;
   unsigned_t control:8;
};

/**
 * @struct T_mkSCSI_WriteRequest
 * @brief Déclaration de la structure T_mkSCSI_WriteRequest.
 *
 */

typedef struct T_mkSCSI_WriteRequest T_mkSCSI_WriteRequest;
struct T_mkSCSI_WriteRequest
{
   unsigned_t opcode:8;
   unsigned_t obsolete:2;
   unsigned_t reserved:1;
   unsigned_t fua:1;
   unsigned_t dpo:1;
   unsigned_t wrProtect:3;
   unsigned_t highMsbLogicalBlockAddress:8;
   unsigned_t lowMsbLogicalBlockAddress:8;
   unsigned_t highLsbLogicalBlockAddress:8;
   unsigned_t lowLsbLogicalBlockAddress:8;
   unsigned_t groupNumber:5;
   unsigned_t reserved2:3;
   unsigned_t highTransferLength:8;
   unsigned_t lowTransferLength:8;
   unsigned_t control:8;
   unsigned_t padding:16;
};

/**
 * @struct T_mkSCSI_Write64Request
 * @brief Déclaration de la structure T_mkSCSI_Write64Request.
 *
 */

typedef struct T_mkSCSI_Write64Request T_mkSCSI_Write64Request;
struct T_mkSCSI_Write64Request
{
   unsigned_t opcode:8;
   unsigned_t dld2:1;
   unsigned_t obsolete:1;
   unsigned_t reserved:1;
   unsigned_t fua:1;
   unsigned_t dpo:1;
   unsigned_t wrProtect:3;
   unsigned_t highMsbExtendedLogicalBlockAddress:8;
   unsigned_t lowMsbExtendedLogicalBlockAddress:8;
   unsigned_t highLsbExtendedLogicalBlockAddress:8;
   unsigned_t lowLsbExtendedLogicalBlockAddress:8;
   unsigned_t highMsbLogicalBlockAddress:8;
   unsigned_t lowMsbLogicalBlockAddress:8;
   unsigned_t highLsbLogicalBlockAddress:8;
   unsigned_t lowLsbLogicalBlockAddress:8;
   unsigned_t highMsbTransferLength:8;
   unsigned_t lowMsbTransferLength:8;
   unsigned_t highLsbTransferLength:8;
   unsigned_t lowLsbTransferLength:8;
   unsigned_t groupNumber:6;
   unsigned_t dld0:1;
   unsigned_t dld1:1;
   unsigned_t control:8;
};

/**
 *
 */

/**
 * @struct T_mkSCSIBlock
 * @brief Déclaration de la structure T_mkSCSIBlock.
 *
 */

typedef struct T_mkSCSIBlock T_mkSCSIBlock;
struct T_mkSCSIBlock
{
   T_mkAddr buf;
   uint32_t lowAddr;
   uint32_t highAddr;
   uint32_t length;
};

/**
 *
 */

#endif

