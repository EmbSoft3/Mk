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
* @file mk_disk_types.h
* @brief Déclaration des types dédiés aux disques.
* @date 15 juin 2020
*
*/

#ifndef MK_DISK_TYPES_H
#define MK_DISK_TYPES_H

/**
 * @enum T_mkDiskMainStatusField
 * @brief Déclaration de la structure T_mkDiskMainStatusField.
 *
 */

typedef enum T_mkDiskMainStatusField
{
   K_MK_DISK_NOT_ENUMERATED = 0x0,                       /*!< Ce code indique que le disque n'a pas été énuméré. */
   K_MK_DISK_READY = 0x1,                                /*!< Ce code indique que le disque est prêt à être utilisé. */
   K_MK_DISK_NOT_VALID = 0x2,                            /*!< Ce code indique que le disque est invalide. */
   K_MK_DISK_WRITE_PROTECT = 0x4,                        /*!< Ce code indique que le disque est protégé en écriture. */
   K_MK_DISK_NOT_PRESENT = 0x8,                          /*!< Ce code indique que le disque n'est plus présent. */
   K_MK_DISK_MBR_CORRUPTED = 0x10,                       /*!< Ce code indique que le secteur MBR du disque est corrompu. */
   K_MK_DISK_NOT_SUPPORTED = 0x20,                       /*!< Ce code indique que le disque n'est pas supportés par le système. */
   K_MK_DISK_VOLUME_MOUNTED = 0x40,                      /*!< Ce code indique que les partitions présentes sur le disque ont été montées. */
   K_MK_DISK_LOCKED = 0x80,                              /*!< Ce code indique que le disque est vérrouillé. */
   K_MK_DISK_USED = 0x100                                /*!< Ce code indique que le disque est en utilisation. */
} T_mkDiskMainStatusField;

/**
 * @enum T_mkDiskInitStatusField
 * @brief Déclaration de la structure T_mkDiskInitStatusField.
 *
 */

typedef enum T_mkDiskInitStatusField
{
   K_MK_MSC_DISK_INQUIRY_DONE = 0x1,                     /*!< Ce code indique que la commande INQUIRY du protocole SCSI a été transmise et acceptée. */
   K_MK_MSC_DISK_READ_CAPACITY_DONE = 0x2,               /*!< Ce code indique que la commande READ_CAPACITY du protocole SCSI a été transmise et acceptée. */
   K_MK_MSC_DISK_MODE_SENSE = 0x4,                       /*!< Ce code indique que la commande MODE_SENSE du protocole SCSI a été transmise et acceptée. */
   K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE = 0x8,      /*!< Ce code indique que la commande READ_FORMAT_CAPACITIES du protocole SCSI a été transmise et acceptée. */
   K_MK_MSC_DISK_TEST_UNIT_READY_DONE = 0x10,            /*!< Ce code indique que la commande TEST_UNIT_READY du protocole SCSI a été transmise et acceptée. */
   K_MK_MSC_DISK_MODE_SENSE_DONE = 0x20                  /*!< Ce code indique que la commande MODE_SENSE du protocole SCSI a été transmise et acceptée. */
} T_mkDiskInitStatusField;

/**
 * @enum T_mkDiskType
 * @brief Déclaration de la structure T_mkDiskType.
 *
 */

typedef enum T_mkDiskType
{
   K_MK_DISK_TYPE_MSC_DEVICE = 0x1,                      /*!< Ce code indique que le disque est un disque USB. */
   K_MK_DISK_TYPE_MMC_DEVICE = 0x2                       /*!< Ce code indique que le disque est un disque SD/MMC. */
} T_mkDiskType;

/**
 * @enum T_mkDiskPeripheralAccess
 * @brief Déclaration de la structure T_mkDiskPeripheralAccess.
 *
 */

typedef enum T_mkDiskPeripheralAccess
{
   K_MK_DISK_ACCESS_TYPE_UNALIGNED = 0x1,                /*!< Ce code indique que le périphérique de contrôle du disque supporte les accès non alignés. */
   K_MK_DISK_ACCESS_TYPE_ALIGNED = 0x2                   /*!< Ce code indique que le périphérique de contrôle du disque ne supporte pas les accès non alignés. */
} T_mkDiskPeripheralAccess;

/**
 * @struct T_mkDiskStatus
 * @brief Déclaration de la structure T_mkDiskStatus.
 *
 */

typedef struct T_mkDiskStatus T_mkDiskStatus;
struct T_mkDiskStatus
{
   T_mkDiskMainStatusField main;                         /*!< Ce membre contient le statut principale du disque. */
   T_mkDiskInitStatusField init;                         /*!< Ce membre contient le statut d'initialisation du disque. */
};

/**
 * @struct T_mkDiskSCSIError
 * @brief Déclaration de la structure T_mkDiskSCSIError.
 *
 */

typedef struct T_mkDiskSCSIError T_mkDiskSCSIError;
struct T_mkDiskSCSIError
{
   unsigned_t responseCode:8;                            /*!< Ce membre contient l'attribut 'responseCode' du protocole SCSI. */
   unsigned_t segmentNumber:8;                           /*!< Ce membre contient l'attribut 'segmentNumber' du protocole SCSI. */
   unsigned_t senseKey:4;                                /*!< Ce membre contient l'attribut 'senseKey' du protocole SCSI. */
   unsigned_t reserved:1;                                /*!< Reservé */
   unsigned_t incorrectLength:1;                         /*!< Ce membre contient l'attribut 'incorrectLength' du protocole SCSI. */
   unsigned_t endOfMedia:1;                              /*!< Ce membre contient l'attribut 'endOfMedia' du protocole SCSI. */
   unsigned_t fileMark:1;                                /*!< Ce membre contient l'attribut 'fileMark' du protocole SCSI. */
   unsigned_t lowInformation:8;                          /*!< Ce membre contient l'attribut 'lowInformation' du protocole SCSI. */
   unsigned_t highInformation:24;                        /*!< Ce membre contient l'attribut 'highInformation' du protocole SCSI. */
   unsigned_t additionalSenseLength:8;                   /*!< Ce membre contient l'attribut 'additionalSenseLength' du protocole SCSI. */
   unsigned_t cmdSpecificInformation:32;                 /*!< Ce membre contient l'attribut 'cmdSpecificInformation' du protocole SCSI. */
   unsigned_t additionalSenseCode:8;                     /*!< Ce membre contient l'attribut 'additionalSenseCode' du protocole SCSI. */
   unsigned_t additionalSenseCodeQualifier:8;            /*!< Ce membre contient l'attribut 'additionalSenseCodeQualifier' du protocole SCSI. */
   unsigned_t fieldReplaceableUnitCode:8;                /*!< Ce membre contient l'attribut 'fieldReplaceableUnitCode' du protocole SCSI. */
   unsigned_t lowSensKeySpecific:8;                      /*!< Ce membre contient l'attribut 'lowSensKeySpecific' du protocole SCSI. */
   unsigned_t highSensKeySpecific:16;                    /*!< Ce membre contient l'attribut 'highSensKeySpecific' du protocole SCSI. */
   unsigned_t padding:16;                                /*!< Padding */
};

/**
 * @struct T_mkDiskATAError
 * @brief Déclaration de la structure T_mkDiskATAError.
 *
 */

typedef struct T_mkDiskATAError T_mkDiskATAError;
struct T_mkDiskATAError
{
   uint32_t reserved;                                    /*!< Ce membre contient la valeur du registre d'erreur du protocole ATA (non implémenté). */
};

/**
 * @struct T_mkDiskError
 * @brief Déclaration de la structure T_mkDiskError.
 *
 */

typedef struct T_mkDiskError T_mkDiskError;
struct T_mkDiskError
{
   T_mkDiskSCSIError scsi;                               /*!< Ce membre contient un registre d'erreur (protocole SCSI). */
   T_mkDiskATAError ata;                                 /*!< Ce membre contient un registre d'erreur (protocole ATA). */
};

/**
 * @struct T_mkDiskGeometry
 * @brief Déclaration de la structure T_mkDiskGeometry.
 *
 */

typedef struct T_mkDiskGeometry T_mkDiskGeometry;
struct T_mkDiskGeometry
{
   uint32_t tracksPerCylinder;                           /*!< Ce membre contient le nombre de têtes par cyclindre. */
   uint32_t sectorsPerTrack;                             /*!< Ce membre contient le nombre de secteurs par tête. */
   uint32_t bytesPerSector;                              /*!< Ce membre contient le nombre d'octets par secteur. */
};

/**
 * @struct T_mkDiskAttribute
 * @brief Déclaration de la structure T_mkDiskAttribute.
 *
 */

typedef struct T_mkDiskAttribute T_mkDiskAttribute;
struct T_mkDiskAttribute
{
   uint32_t type;                                        /*!< Ce membre contient le type du disque (\ref T_mkSCSI_DeviceType). */
   uint32_t logicalUnit;                                 /*!< Ce membre contient le numéro de l'unité logique. */
   uint32_t blockLength;                                 /*!< Ce membre contient la longueur d'un bloc de données. */
   uint32_t numberOfBlocks;                              /*!< Ce membre contient le nombre de blocs de données. */
   uint32_t logicalBlockAdress;                          /*!< Ce membre contient l'adresse du dernier bloc de données. */
};

/**
 * @struct T_mkDiskInfo
 * @brief Déclaration de la structure T_mkDiskInfo.
 *
 */

typedef struct T_mkDiskInfo T_mkDiskInfo;
struct T_mkDiskInfo
{
   char8_t  vendorIdentifier  [8];                       /*!< Ce membre contient la chaine de caractères qui stocke l'identifiant du fabricant. */
   char8_t  productIdentifier [16];                      /*!< Ce membre contient la chaine de caractères qui stocke l'identifiant du disque. */
   char8_t  productRevision   [4];                       /*!< Ce membre contient la chaine de caractères qui stocke la révision du disque. */
};

/**
 * @struct T_mkDiskName
 * @brief Déclaration de la structure T_mkDiskName.
 *
 */

typedef struct T_mkDiskName T_mkDiskName;
struct T_mkDiskName
{
   char8_t id [12];                                      /*!< Ce membre contient la chaine de caractères qui stocke l'identifiant système du disque. */
};

/**
 * @struct T_mkDiskLayer
 * @brief Déclaration de la structure T_mkDiskLayer.
 *
 */

typedef struct T_mkDiskLayer T_mkDiskLayer;
struct T_mkDiskLayer
{
   uint16_t type;                                        /*!< Ce membre contient le type du contrôle applicatif (\ref K_MK_CONTROL_DISK). La position de cet attribut ne doit pas être modifiée. */
   uint16_t id;                                          /*!< Ce membre contient l'identifiant unique du contrôle applicatif \ref T_mkDisk. La position de cet attribut ne doit pas être modifiée. */
   uint32_t peripheralAccess;                            /*!< Ce champ indique si le périphérique de contrôle du disque peut réaliser des accès non alignés ou non (\ref T_mkDiskPeripheralAccess). */
};

/**
 * @struct T_mkDisk
 * @brief Déclaration de la structure T_mkDisk.
 *
 */

typedef struct T_mkDisk T_mkDisk;
struct T_mkDisk
{
   T_mkDiskLayer layer;                                  /*!< Ce membre contient le registre d'identification du disque de type \ref T_mkDiskLayer. La position de cet attribut ne doit pas être modifiée. */
   T_mkAddr device;                                      /*!< Ce membre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice ou \ref T_mkMSCDevice. */
   T_mkDiskAttribute attribute;                          /*!< Ce membre contient les caractéristiques du disque (au format absolu). */
   T_mkDiskGeometry geometry;                            /*!< Ce membre contient les caractéristiques du disque (au format cyclindrique). */
   T_mkDiskInfo info;                                    /*!< Ce membre contient la dénomination du fabricant et de la version du disque. */
   T_mkDiskName name;                                    /*!< Ce membre contient la dénomination système du disque. */
   T_mkDiskStatus status;                                /*!< Ce membre contient le statut de fonctionnement du disque. */
   T_mkDiskError lastError;                              /*!< Ce membre contient l'identifiant de la dernière erreur détectée sur le disque. */
   T_mkSemaphore* semaphore;                             /*!< Ce membre contient le sémaphore gérant les accès concurrents sur le disque. */
   T_mkVolume* volume;                                   /*!< Ce membre contient l'adresse de la première partition du disque (ou \ref K_MK_NULL si aucune partition n'est présente). */
   T_mkDisk* nextDisk;                                   /*!< Ce membre contient l'adresse du prochain disque (ou la valeur \ref K_MK_NULL si un seul disque est présent). */
};

/**
 *
 */

#endif

