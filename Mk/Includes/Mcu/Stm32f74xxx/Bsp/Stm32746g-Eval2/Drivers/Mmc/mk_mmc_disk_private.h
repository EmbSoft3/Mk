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
* @file mk_mmc_disk_private.h
* @brief Déclaration des fonctions privées dédiées aux disques SD/MMC.
* @date 6 juin 2020
*
* @todo Adapter les fonctions pour supporter les périphériques MMC et SDIO.
*
*/

#ifndef MK_MMC_DISK_PRIVATE_H
#define MK_MMC_DISK_PRIVATE_H

/**
 * @fn T_mkCode mk_mmc_initDisk ( T_mkMMCDevice* p_device );
 * @brief Cette fonction initialise un périphérique de type SD/MMC. Les événements \ref K_MK_EVENT_CONNECT ou \ref K_MK_EVENT_LOCK sont envoyés au dispatcher
 *        lorsque l'initialisation du média est terminée.
 *
 * @param[in] p_device Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMMCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'initialisation du disque a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'initialisation du disque a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'initialisation du disque a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'initialisation du disque a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : l'initialisation du disque a échoué en raison d'une erreur de communication.
 *
 */

T_mkCode mk_mmc_initDisk ( T_mkMMCDevice* p_device );

/**
 * @fn T_mkCode mk_mmc_readSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );
 * @brief Cette fonction lit un ou plusieurs blocs de données d'un disque.
 *
 * @param[in]  p_disk                Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress        Ce paramètre contient l'adresse du premier bloc de données à lire.
 * @param[out] p_buf                 Ce paramètre contient l'adresse du buffer de données.
 * @param[in]  p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out] p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la lecture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la lecture des blocs de données a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : la lecture des blocs de données a échoué en raison d'une erreur de communication.
 *
 * @warning Les 32 bits de poids fort de l'adresse sont ignorées.
 *
 */

T_mkCode mk_mmc_readSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );

/**
 * @fn T_mkCode mk_mmc_writeSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );
 * @brief Cette fonction écrit un ou plusieurs secteurs de données d'un disque.
 *
 * @param[in]  p_disk                 Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress         Ce paramètre contient l'adresse du premier bloc de données à écrire.
 * @param[out] p_buf                  Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]  p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out] p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué en raison d'une erreur de communication.
 *
 * @warning Les 32 bits de poids fort de l'adresse sont ignorées.
 *
 */

T_mkCode mk_mmc_writeSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );

/**
 *
 */

#endif


