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
* @file mk_mmc_cmd_types.h
* @brief Définition des types dédiés aux commandes SD/MMC.
* @date 4 juil. 2020
*
*/

#ifndef MK_MMC_CMD_TYPES_H
#define MK_MMC_CMD_TYPES_H

/**
 * @struct T_mkMMCOPCode
 * @brief Déclaration de l'énumération T_mkMMCOPCode.
 *
 */

typedef enum T_mkMMCOPCode
{
   K_MK_MMC_OPCODE_GO_IDLE_STATE = 0,                   /*!< GO_IDLE_STATE          CMD0 */
   K_MK_MMC_OPCODE_SEND_OP_COND = 1,                    /*!< SEND_OP_COND(MMC)      CMD1 */
   K_MK_MMC_OPCODE_ALL_SEND_CID = 2,                    /*!< ALL_SEND_CID           CMD2 */
   K_MK_MMC_OPCODE_SEND_RELATIVE_ADDR = 3,              /*!< SEND_RELATIVE_ADD      CMD3 */
   K_MK_MMC_OPCODE_IO_SEND_OP_COND = 5,                 /*!< SEND_OP_COND(IO)       CMD5 */
   K_MK_MMC_OPCODE_SET_BUS_WIDTH = 6,                   /*!< SET_BUS_WIDTH          CMD6 */
   K_MK_MMC_OPCODE_SELECT_DESELECT = 7,                 /*!< SELECT_DESELECT        CMD7 */
   K_MK_MMC_OPCODE_SEND_IF_COND = 8,                    /*!< SEND_IF_COND           CMD8 */
   K_MK_MMC_OPCODE_SEND_CSD = 9,                        /*!< SEND_CSD               CMD9 */
   K_MK_MMC_OPCODE_STOP_TRANSMISSION = 12,              /*!< STOP_TRANSMISSION      CMD12 */
   K_MK_MMC_OPCODE_SEND_STATUS = 13,                    /*!< SEND_STATUS            ACMD13 */
   K_MK_MMC_OPCODE_SET_BLOCK_LENGTH = 16,               /*!< SET_BLOCK_LENGTH       CMD16 */
   K_MK_MMC_OPCODE_READ_SINGLE_BLOCK = 17,              /*!< READ_SINGLE_BLOCK      CMD17 */
   K_MK_MMC_OPCODE_READ_MULTIPLE_BLOCK = 18,            /*!< READ_MULTIPLE_BLOCK    CMD18 */
   K_MK_MMC_OPCODE_SET_BLOCK_COUNT = 23,                /*!< SET_BLOCK_COUNT        CMD23 */
   K_MK_MMC_OPCODE_WRITE_SINGLE_BLOCK = 24,             /*!< WRITE_SINGLE_BLOCK     CMD24 */
   K_MK_MMC_OPCODE_WRITE_MULTIPLE_BLOCK = 25,           /*!< WRITE_MULTIPLE_BLOCK   CMD25 */
   K_MK_MMC_OPCODE_LOCK_UNLOCK_CMD = 42,                /*!< LOCK_UNLOCK_CMD        CMD42 */
   K_MK_MMC_OPCODE_APP_CMD = 55,                        /*!< APPLICATION_CMD        CMD55 */
   K_MK_MMC_OPCODE_SDC_SEND_OP_COND = 41                /*!< SEND_OP_COND(SD)       ACMD41 */

} T_mkMMCOPCode;

/**
 * @struct T_mkMMCState
 * @brief Déclaration de l'énumération T_mkMMCState.
 *
 */

typedef enum T_mkMMCBusWidth
{
   K_MK_MMC_BUS_WIDTH_1BIT = 0,                         /*!< BUS_WIDTH_1BIT        Configuration du bus sur 1 bit. */
   K_MK_MMC_BUS_WIDTH_4BITS = 2                         /*!< BUS_WIDTH_4BITS       Configuration du bus sur 4 bits. */
} T_mkMMCBusWidth;

/**
 * @struct T_mkMMCOCRRegister
 * @brief Déclaration de la structure T_mkMMCOCRRegister.
 *
 */

typedef struct T_mkMMCOCRRegister T_mkMMCOCRRegister;
struct T_mkMMCOCRRegister
{
   unsigned_t reserved1:15;                             /*!< SDMMC_RESP1<14:0>     Reserved */
   unsigned_t voltage_2dot8To2dot7:1;                   /*!< SDMMC_RESP1<15>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_2dot9To2dot8:1;                   /*!< SDMMC_RESP1<16>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot0To2dot9:1;                   /*!< SDMMC_RESP1<17>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot1To3dot0:1;                   /*!< SDMMC_RESP1<18>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot2To3dot1:1;                   /*!< SDMMC_RESP1<19>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot3To3dot2:1;                   /*!< SDMMC_RESP1<20>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot4To3dot3:1;                   /*!< SDMMC_RESP1<21>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot5To3dot4:1;                   /*!< SDMMC_RESP1<22>       VCC Voltage - 1 = Supported */
   unsigned_t voltage_3dot6To3dot5:1;                   /*!< SDMMC_RESP1<23>       VCC Voltage - 1 = Supported */
   unsigned_t s18a:1;                                   /*!< SDMMC_RESP1<24>       Switching to 1.8V Accepted */
   unsigned_t reserved2:5;                              /*!< SDMMC_RESP1<29:25>    Reserved */
   unsigned_t hcs:1;                                    /*!< SDMMC_RESP1<30>       Host Capacity Support - 1 = SDHC */
   unsigned_t busy:1;                                   /*!< SDMMC_RESP1<31>       Busy bit - 1 = Not Busy */
};

/**
 * @struct T_mkMMCCIDRegister
 * @brief Déclaration de la structure T_mkMMCCIDRegister.
 * @warning Structure codée en modifiant la position de chaque octet des mots 32 bits :
 *          \li PNM <8> - OID <16> - MID <8> | PNM <32> | PSN <24> - PRV <8>  | RSV_CRC <8> - MONTH_YEARSLSB <8> - YEARSMSB_RSV <4> - PSN <8>
 *          \li MID <8> - OID <16> - PNM <8> | PNM <32> | PRV <8>  - PSN <24> | PSN <8> - YEARSMSB_RSV <8> - MONTH_YEARSLSB <8> - RSV_CRC <8>
 *          \n  Cette opération est réalisée pour simplifier la récupération des chaines de caractères.
 *
 */

typedef struct T_mkMMCCIDRegister T_mkMMCCIDRegister;
struct T_mkMMCCIDRegister
{
   uint8_t  vendorIdentifier;                           /*!< RV:SDMMC_RESP1<7:0>   Vendor ID */
   char8_t  oemIdentifier [2];                          /*!< RV:SDMMC_RESP1<23:8>  OEM Identifier */
   char8_t  productName [5];                            /*!< RV:SDMMC_RESP1<31:24> Product Name */
                                                        /*!< RV:SDMMC_RESP1<31:0>  Product Name */
   uint8_t  productRevision;                            /*!< RV:SDMMC_RESP3<7:0>   Product Revision */
   char8_t  productSerialNumber[4];                     /*!< RV:SDMMC_RESP3<31:8>  Product Serial Number */
                                                        /*!< RV:SDMMC_RESP3<7:0>   Product Serial Number */
   unsigned_t manufacturingYearMsb:4;                   /*!< RV:SDMMC_RESP4<11:8>  Manufacturing Years MSB */
   unsigned_t reserved2:4;                              /*!< RV:SDMMC_RESP4<15:12> Reserved */
   unsigned_t manufacturingMonth:4;                     /*!< RV:SDMMC_RESP4<19:16> Manufacturing Month */
   unsigned_t manufacturingYearLsb:4;                   /*!< RV:SDMMC_RESP4<23:20> Manufacturing Years LSB */
   unsigned_t reserved:1;                               /*!< RV:SDMMC_RESP4<24>    Reserved - always 1 */
   unsigned_t crc:7;                                    /*!< RV:SDMMC_RESP4<31:25> CRC7 */
};

/**
 * @struct T_mkMMCCStatusRegister
 * @brief Déclaration de la structure T_mkMMCCStatusRegister.
 * @note Le type de réponse est 'SHORT <32bits>'. Elle est stockée dans le registre
 *       SDMMC_RESP1.
 *
 */

typedef struct T_mkMMCCStatusRegister T_mkMMCCStatusRegister;
struct T_mkMMCCStatusRegister
{
   unsigned_t reserved:3;                               /*!< SDMMC_RESP1<2:0>      Reserved */
   unsigned_t akeSeqError:1;                            /*!< SDMMC_RESP1<3>        Authentification Sequence Error */
   unsigned_t reserved1:1;                              /*!< SDMMC_RESP1<4>        Reserved */
   unsigned_t appCmd:1;                                 /*!< SDMMC_RESP1<5>        Application Command */
   unsigned_t reserved2:2;                              /*!< SDMMC_RESP1<7:6>      Reserved */
   unsigned_t readyForData:1;                           /*!< SDMMC_RESP1<8>        Ready For Data */
   unsigned_t currentState:4;                           /*!< SDMMC_RESP1<12:9>     Current State */
   unsigned_t eraseReset:1;                             /*!< SDMMC_RESP1<13>       Erase Reset */
   unsigned_t cardEccDisabled:1;                        /*!< SDMMC_RESP1<14>       Card ECC Disabled */
   unsigned_t wpEraseSkip:1;                            /*!< SDMMC_RESP1<15>       Write Protected Erased Skip */
   unsigned_t csdOverwrite:1;                           /*!< SDMMC_RESP1<16>       CID/CSD Overwrite Error */
   unsigned_t reserved3:2;                              /*!< SDMMC_RESP1<18:17>    Reserved */
   unsigned_t error:1;                                  /*!< SDMMC_RESP1<19>       Generic Card Error */
   unsigned_t ccError:1;                                /*!< SDMMC_RESP1<20>       Card Error */
   unsigned_t cardEccFailed:1;                          /*!< SDMMC_RESP1<21>       Card ECC Failed */
   unsigned_t illegalCommand:1;                         /*!< SDMMC_RESP1<22>       Illegal Command */
   unsigned_t comCrcError:1;                            /*!< SDMMC_RESP1<23>       Command CRC Error */
   unsigned_t lockUnlockFailed:1;                       /*!< SDMMC_RESP1<24>       Lock Unlock Failed */
   unsigned_t cardIsLock:1;                             /*!< SDMMC_RESP1<25>       Card Is Locked */
   unsigned_t wpViolation:1;                            /*!< SDMMC_RESP1<26>       Write Protected Violation */
   unsigned_t eraseParam:1;                             /*!< SDMMC_RESP1<27>       Erase Param Error */
   unsigned_t eraseSeqError:1;                          /*!< SDMMC_RESP1<28>       Erase Sequence Error */
   unsigned_t blockLenError:1;                          /*!< SDMMC_RESP1<29>       Block Length Error */
   unsigned_t addressMisalign:1;                        /*!< SDMMC_RESP1<30>       Address Misalign */
   unsigned_t outOfRange:1;                             /*!< SDMMC_RESP1<31>       Address Out Of Range */
};

/**
 * @struct T_mkMMCAddr
 * @brief Déclaration de la structure T_mkMMCAddr.
 *
 */

typedef struct T_mkMMCRCARegister T_mkMMCRCARegister;
struct T_mkMMCRCARegister
{
   unsigned_t reserved:3;                               /*!< SDMMC_RESP1<2:0>      Reserved */
   unsigned_t akeSeqError:1;                            /*!< SDMMC_RESP1<3>        Authentification Sequence Error */
   unsigned_t reserved1:1;                              /*!< SDMMC_RESP1<4>        Reserved */
   unsigned_t appCmd:1;                                 /*!< SDMMC_RESP1<5>        Application Command */
   unsigned_t reserved2:2;                              /*!< SDMMC_RESP1<7:6>      Reserved */
   unsigned_t readyForData:1;                           /*!< SDMMC_RESP1<8>        Ready For Data */
   unsigned_t currentState:4;                           /*!< SDMMC_RESP1<12:9>     Current State */
   unsigned_t error:1;                                  /*!< SDMMC_RESP1<13>       General Error */
   unsigned_t illegalCommand:1;                         /*!< SDMMC_RESP1<14>       Illegal Command */
   unsigned_t comCrcError:1;                            /*!< SDMMC_RESP1<14>       Command CRC Error */
   unsigned_t addr:16;                                  /*!< SDMMC_RESP1<31:16>    NewPublishedRCA */
};

/**
 * @struct T_mkMMCExtendedStatus
 * @brief Déclaration de la structure T_mkMMCExtendedStatus.
 *
 */

typedef struct T_mkMMCExtendedStatus T_mkMMCExtendedStatus;
struct T_mkMMCExtendedStatus
{
   unsigned_t reserved:5;                               /*!< SDMMC_DATA1<4:0>      Reserved */
   unsigned_t securedMode:1;                            /*!< SDMMC_DATA1<5>        Secured Mode */
   unsigned_t busWidth:2;                               /*!< SDMMC_DATA1<7:6>      Bus Width */
   unsigned_t reserved2:8;                              /*!< SDMMC_DATA1<15:8>     Reserved */
   unsigned_t type:16;                                  /*!< SDMMC_DATA1<31:16>    SD Card Type */
   unsigned_t protectedAreaSize:32;                     /*!< SDMMC_DATA2<31:0>     Protected Area Size */
   unsigned_t speedClass:8;                             /*!< SDMMC_DATA3<15:8>     Speed Class */
   unsigned_t performanceMove:8;                        /*!< SDMMC_DATA3<15:8>     Performance of Move (1MBs Step) */
   unsigned_t auSize:4;                                 /*!< SDMMC_DATA3<19:16>    AU Size */
   unsigned_t reserved3:4;                              /*!< SDMMC_DATA3<23:20>    Reserved */
   unsigned_t eraseSizeHigh:8;                          /*!< SDMMC_DATA3<31:24>    Number of AUs to be erase */
   unsigned_t eraseSizeLow:8;                           /*!< SDMMC_DATA4<7:0>      Erase Size */
   unsigned_t eraseTimeout:6;                           /*!< SDMMC_DATA4<13:8>     Erase Timeout */
   unsigned_t eraseOffset:2;                            /*!< SDMMC_DATA4<15:14>    Erase Offset */
   unsigned_t reserved4:16;                             /*!< SDMMC_DATA4<31:16>    Reserved */
};

/**
 * @struct T_mkMMCCSDV1Register
 * @brief Déclaration de la structure T_mkMMCCSDV1Register.
 *
 */

typedef struct T_mkMMCCSDV1Register T_mkMMCCSDV1Register;
struct T_mkMMCCSDV1Register
{
   unsigned_t transferSpeed:8;                          /*!< SDMMC_RESP1<7:0>      Transfer Speed */
   unsigned_t nsac:8;                                   /*!< SDMMC_RESP1<15:8>     NSAC */
   unsigned_t taac:8;                                   /*!< SDMMC_RESP1<23:16>    TAAC */
   unsigned_t reserved:6;                               /*!< SDMMC_RESP1<29:24>    Reserved */
   unsigned_t version:2;                                /*!< SDMMC_RESP1<31:30>    CSD Structure */
   unsigned_t deviceSizeHigh:10;                        /*!< SDMMC_RESP2<9:0>      Device Size */
   unsigned_t reserved1:2;                              /*!< SDMMC_RESP2<11:10>    Reserved */
   unsigned_t dsrImplemented:1;                         /*!< SDMMC_RESP2<12>       DSR Implemented */
   unsigned_t readBlockMisalign:1;                      /*!< SDMMC_RESP2<13>       Read Block Misalign */
   unsigned_t writeBlockMisalign:1;                     /*!< SDMMC_RESP2<14>       Write Block Misalign */
   unsigned_t readBlockPartial:1;                       /*!< SDMMC_RESP2<15>       Read Block Partial */
   unsigned_t readBlockLength:4;                        /*!< SDMMC_RESP2<20:16>    Read Block Length */
   unsigned_t cardCmdClass:12;                          /*!< SDMMC_RESP2<31:20>    Card Command Class */
   unsigned_t wpGroupSize:7;                            /*!< SDMMC_RESP3<6:0>      Write Protect Group Size */
   unsigned_t eraseSectorSize:7;                        /*!< SDMMC_RESP3<13:7>     Erase Sector Size */
   unsigned_t eraseBlockEn:1;                           /*!< SDMMC_RESP3<14>       Erase Single Block Enabled */
   unsigned_t cSizeMult:3;                              /*!< SDMMC_RESP3<17:15>    Device Size Multiplier */
   unsigned_t vddWriteCurrMax:3;                        /*!< SDMMC_RESP3<20:18>    VDD_Write Current Max */
   unsigned_t vddWriteCurrMin:3;                        /*!< SDMMC_RESP3<23:21>    VDD Write Current Min */
   unsigned_t vddReadCurrMax:3;                         /*!< SDMMC_RESP3<26:24>    VDD Read Current Max */
   unsigned_t vddReadCurrMin:3;                         /*!< SDMMC_RESP3<29:27>    VDD Read Current Min */
   unsigned_t deviceSizeLow:2;                          /*!< SDMMC_RESP3<31:30>    Device Size */
   unsigned_t reserved5:1;                              /*!< SDMMC_RESP4<0>        Reserved */
   unsigned_t crc:7;                                    /*!< SDMMC_RESP4<7:1>      CSD CRC */
   unsigned_t reserved4:2;                              /*!< SDMMC_RESP4<9:8>      Reserved */
   unsigned_t fileFormat:2;                             /*!< SDMMC_RESP4<11:10>    File Format */
   unsigned_t tmpWriteProtect:1;                        /*!< SDMMC_RESP4<12>       Temporary Write Protect */
   unsigned_t permWriteProtect:1;                       /*!< SDMMC_RESP4<13>       Permanent Write Protect */
   unsigned_t copy:1;                                   /*!< SDMMC_RESP4<14>       Copy Flag */
   unsigned_t fileFormatGrp:1;                          /*!< SDMMC_RESP4<15>       File Format Group */
   unsigned_t reserved3:5;                              /*!< SDMMC_RESP4<20:16>    Reserved */
   unsigned_t writeBlockPartial:1;                      /*!< SDMMC_RESP4<21>       Write Block Partial */
   unsigned_t writeBlockLength:4;                       /*!< SDMMC_RESP4<25:22>    Write Block Length */
   unsigned_t r2wFactor:3;                              /*!< SDMMC_RESP4<28:26>    Write Speed Factor */
   unsigned_t reserved2:2;                              /*!< SDMMC_RESP4<30:29>    Reserved */
   unsigned_t wpGroupEnable:1;                          /*!< SDMMC_RESP4<31>       Write Protected Group Enable */
};

/**
 * @struct T_mkMMCCSDV2Register
 * @brief Déclaration de la structure T_mkMMCCSDV2Register.
 *
 */

typedef struct T_mkMMCCSDV2Register T_mkMMCCSDV2Register;
struct T_mkMMCCSDV2Register
{
   unsigned_t transferSpeed:8;                          /*!< SDMMC_RESP1<7:0>      Transfer Speed */
   unsigned_t nsac:8;                                   /*!< SDMMC_RESP1<15:8>     NSAC */
   unsigned_t taac:8;                                   /*!< SDMMC_RESP1<23:16>    TAAC */
   unsigned_t reserved:6;                               /*!< SDMMC_RESP1<29:24>    Reserved */
   unsigned_t version:2;                                /*!< SDMMC_RESP1<31:30>    CSD Structure */
   unsigned_t deviceSizeHigh:6;                         /*!< SDMMC_RESP2<6:0>      Device Size */
   unsigned_t reserved1:6;                              /*!< SDMMC_RESP2<11:6>     Reserved */
   unsigned_t dsrImplemented:1;                         /*!< SDMMC_RESP2<12>       DSR Implemented */
   unsigned_t readBlockMisalign:1;                      /*!< SDMMC_RESP2<13>       Read Block Misalign */
   unsigned_t writeBlockMisalign:1;                     /*!< SDMMC_RESP2<14>       Write Block Misalign */
   unsigned_t readBlockPartial:1;                       /*!< SDMMC_RESP2<15>       Read Block Partial */
   unsigned_t readBlockLength:4;                        /*!< SDMMC_RESP2<20:16>    Read Block Length */
   unsigned_t cardCmdClass:12;                          /*!< SDMMC_RESP2<31:20>    Card Command Class */
   unsigned_t wpGroupSize:7;                            /*!< SDMMC_RESP3<6:0>      Write Protect Group Size */
   unsigned_t eraseSectorSize:7;                        /*!< SDMMC_RESP3<13:7>     Erase Sector Size */
   unsigned_t eraseBlockEn:1;                           /*!< SDMMC_RESP3<14>       Erase Single Block Enabled */
   unsigned_t reserved2:1;                              /*!< SDMMC_RESP3<15>       Reserved */
   unsigned_t deviceSizeLow:16;                         /*!< SDMMC_RESP3<31:16>    Device Size */
   unsigned_t reserved6:1;                              /*!< SDMMC_RESP4<0>        Reserved */
   unsigned_t crc:7;                                    /*!< SDMMC_RESP4<7:1>      CSD CRC */
   unsigned_t reserved5:2;                              /*!< SDMMC_RESP4<9:8>      Reserved */
   unsigned_t fileFormat:2;                             /*!< SDMMC_RESP4<11:10>    File Format */
   unsigned_t tmpWriteProtect:1;                        /*!< SDMMC_RESP4<12>       Temporary Write Protect */
   unsigned_t permWriteProtect:1;                       /*!< SDMMC_RESP4<13>       Permanent Write Protect */
   unsigned_t copy:1;                                   /*!< SDMMC_RESP4<14>       Copy Flag */
   unsigned_t fileFormatGrp:1;                          /*!< SDMMC_RESP4<15>       File Format Group */
   unsigned_t reserved4:5;                              /*!< SDMMC_RESP4<20:16>    Reserved */
   unsigned_t writeBlockPartial:1;                      /*!< SDMMC_RESP4<21>       Write Block Partial */
   unsigned_t writeBlockLength:4;                       /*!< SDMMC_RESP4<25:22>    Write Block Length */
   unsigned_t r2wFactor:3;                              /*!< SDMMC_RESP4<28:26>    Write Speed Factor */
   unsigned_t reserved3:2;                              /*!< SDMMC_RESP4<30:29>    Reserved */
   unsigned_t wpGroupEnable:1;                          /*!< SDMMC_RESP4<31>       Write Protected Group Enable */
};

/**
 * @struct T_mkMMCCSDVersion
 * @brief Déclaration de l'énumération T_mkMMCCSDVersion.
 *
 */

typedef enum T_mkMMCCSDVersion
{
   K_MK_MMC_CSD_V1 = 0,                                  /*!< CSD_V1 Identifiant de la version 1 du CSD. */
   K_MK_MMC_CSD_V2 = 1                                   /*!< CSD_V2 Identifiant de la version 2 du CSD. */
} T_mkMMCCSDVersion;

/**
 * @struct T_mkMMCCSDV1Register
 * @brief Déclaration de la structure T_mkMMCCSDV1Register.
 *
 */

typedef union T_mkMMCCSDRegister T_mkMMCCSDRegister;
union T_mkMMCCSDRegister
{
   T_mkMMCCSDV1Register v1;                              /*!< Ce membre contient la version 1 du CSD */
   T_mkMMCCSDV2Register v2;                              /*!< Ce membre contient la version 2 du CSD */
};

/**
 * @struct T_mkMMCCommand
 * @brief Déclaration de la structure T_mkMMCCommand.
 *
 */

typedef struct T_mkMMCCommand T_mkMMCCommand;
struct T_mkMMCCommand
{
  uint32_t opcode;                                       /*!< Ce membre contient l'identifiant de la commande [sur 8 bits]. */
  uint32_t argument;                                     /*!< Ce membre contient l'argument de la commande [sur 32 bits]. */
  uint32_t direction;                                    /*!< Ce membre contient la direction du transfert (\ref K_MMC_DIRECTION_CONTROLLER_TO_CARD ou \ref K_MMC_DIRECTION_CARD_TO_CONTROLLER). */
  uint32_t length;                                       /*!< Ce membre contient la taille du transfert [en octets]. */
  uint32_t timeout;                                      /*!< Ce membre contient le timeout du transfert [en multiple de cycles d'horloge FREQ_MMC]. */
  uint32_t responseLength;                               /*!< Ce membre contient la taille de la réponse (\ref K_MMC_NO_RESPONSE, \ref K_MMC_SHORT_RESPONSE ou \ref K_MMC_LONG_RESPONSE). */
  uint32_t bypassCRC;                                    /*!< Ce membre contient un drapeau permettant d'empécher la réémission d'une commande dans le cas d'une erreur de CRC (\ref K_MK_MMC_CRC_BYPASS_DISABLED ou \ref K_MK_MMC_CRC_BYPASS_ENABLED). */
};

/**
 *
 */

#endif

