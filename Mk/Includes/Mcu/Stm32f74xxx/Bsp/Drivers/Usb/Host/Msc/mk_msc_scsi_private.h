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
* @file mk_msc_scsi_private.h
* @brief Déclaration des fonctions privées dédiées aux protocoles SCSI des périphériques de stockage.
* @date 20 mai 2020
*
*/

#ifndef MK_MSC_SCSI_PRIVATE_H
#define MK_MSC_SCSI_PRIVATE_H

/**
 * @fn T_mkCode mk_msc_postInquiryRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_InquiryPacket** p_inquiryPacket, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "Inquiry" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice         Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out]    p_inquiryPacket     Ce paramètre contient l'adresse d'un pointeur de type \ref T_mkSCSI_InquiryPacket.
 * @param[in]     p_logicalUnitNumber Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postInquiryRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_InquiryPacket** p_inquiryPacket, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postTestUnitReadyRequest ( T_mkMSCDevice* p_mscDevice, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "TestUnitReady" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice         Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]     p_logicalUnitNumber Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postTestUnitReadyRequest ( T_mkMSCDevice* p_mscDevice, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postReadFormatCapacitiesRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ReadFormatCapacitiesPacket** p_readFormatCapacities, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "ReadFormatCapacities" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice            Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out]    p_readFormatCapacities Ce paramètre contient l'adresse d'un pointeur de type \ref T_mkSCSI_ReadFormatCapacitiesPacket.
 * @param[in]     p_logicalUnitNumber    Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postReadFormatCapacitiesRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ReadFormatCapacitiesPacket** p_readFormatCapacities, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postReadCapacityRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ReadCapacityPacket** p_readCapacityPacket, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "ReadCpacity" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice          Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out]    p_readCapacityPacket Ce paramètre contient l'adresse d'un pointeur de type \ref T_mkSCSI_ReadCapacityPacket.
 * @param[in]     p_logicalUnitNumber  Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postReadCapacityRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ReadCapacityPacket** p_readCapacityPacket, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postModeSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ModeSensePacket** p_modeSensePacket, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "ModeSense" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice         Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out]    p_modeSensePacket   Ce paramètre contient l'adresse d'un pointeur de type \ref T_mkSCSI_ModeSensePacket.
 * @param[in]     p_logicalUnitNumber Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postModeSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_ModeSensePacket** p_modeSensePacket, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postRequestSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_RequestSensePacket** p_requestSensePacket, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "RequestSense" à un périphérique MSC.
 *
 * @param[in,out] p_mscDevice          Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out]    p_requestSensePacket Ce paramètre contient l'adresse d'un pointeur de type \ref T_mkSCSI_InquiryPacket.
 * @param[in]     p_logicalUnitNumber  Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postRequestSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_RequestSensePacket** p_requestSensePacket, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postReadRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "Read" à un périphérique MSC (adressage 32 bits).
 *
 * @param[in,out] p_mscDevice           Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]     p_block               Ce paramètre contient l'adresse d'une structure de type \ref T_mkSCSIBlock
 * @param[in]     p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out]    p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus.
 * @param[in]     p_logicalUnitNumber   Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postReadRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postRead64Request ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "Read" à un périphérique MSC (adressage 64 bits).
 *
 * @param[in,out] p_mscDevice           Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]     p_block               Ce paramètre contient l'adresse d'une structure de type \ref T_mkSCSIBlock
 * @param[in]     p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out]    p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus.
 * @param[in]     p_logicalUnitNumber   Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postRead64Request ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postWriteRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "Write" à un périphérique MSC (adressage 32 bits).
 *
 * @param[in,out] p_mscDevice            Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]     p_block                Ce paramètre contient l'adresse d'une structure de type \ref T_mkSCSIBlock
 * @param[in]     p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out]    p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits.
 * @param[in]     p_logicalUnitNumber    Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postWriteRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, uint32_t p_logicalUnitNumber );

/**
 * @fn T_mkCode mk_msc_postWrite64Request ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, uint32_t p_logicalUnitNumber );
 * @brief Cette fonction envoie une requête SCSI de type "Write" à un périphérique MSC (adressage 64 bits).
 *
 * @param[in,out] p_mscDevice            Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[in]     p_block                Ce paramètre contient l'adresse d'une structure de type \ref T_mkSCSIBlock
 * @param[in]     p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out]    p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits.
 * @param[in]     p_logicalUnitNumber    Ce paramètre contient le numéro de l'unité logique adressée.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la requête a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la requête a échoué  car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la requête a échoué car le périphérique cible n'a pas répondu suite à une requête USB.
 *         \li \ref K_MK_ERROR_COMM    : la requête a échoué car une erreur de communication s'est produite suite à une requête USB.
 */

T_mkCode mk_msc_postWrite64Request ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, uint32_t p_logicalUnitNumber );

/**
 *
 */

#endif

