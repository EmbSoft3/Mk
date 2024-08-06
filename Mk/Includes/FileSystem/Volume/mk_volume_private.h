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
* @file mk_volume_private.h
* @brief Déclaration des fonctions privées dédiées aux partitions.
* @date 15 juin 2020
*
*/

#ifndef MK_VOLUME_PRIVATE_H
#define MK_VOLUME_PRIVATE_H

/**
 * @fn T_mkCode mk_volume_init ( T_mkDisk* p_disk, uint8_t* p_buf );
 * @brief Cette fonction initialise les partitions présentes sur un disque. Seules les partitions supportées sont initialisées.
 *        Un événement \ref K_MK_EVENT_MOUNT est envoyé au dispatcher pour chaque partition supportée.
 *
 * @param[in,out] p_disk Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]     p_buf  Ce paramètre contient l'adresse d'un buffer de taille \ref K_MK_MMC_MAX_PACKET_SIZE ou \ref K_MK_MSC_MAX_PACKET_SIZE.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : les volumes ont été initialisés.
 *         \li \ref K_MK_ERROR_PARAM   : les volumes n'ont pas été initialisés car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : les volumes n'ont pas été initialisés car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : les volumes n'ont pas été initialisés car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NESTED  : les volumes n'ont pas été initialisés car la tâche appelante est propriétaire d'un autre objet de synchronisation de type \ref T_mkMutex.
 *         \li \ref K_MK_ERROR_TIMEOUT : les volumes n'ont pas été initialisés car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : les volumes n'ont pas été initialisés car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : les volumes n'ont pas été initialisés car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_volume_init ( T_mkDisk* p_disk, uint8_t* p_buf );

/**
 * @fn T_mkCode mk_volume_decodeFAT32 ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector );
 * @brief Cette fonction décode une partition FAT32 puis si elle est supportée, l'alloue et l'ajoute dans la liste des partitions d'un disque.
 *
 * @param[in,out] p_disk                 Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[out]    p_list                 Ce paramètre contient l'adresse d'un pointeur de partition de type \ref T_mkVolume.
 * @param[in]     p_buf                  Ce paramètre contient l'adresse d'un buffer de taille \ref K_MK_MMC_MAX_PACKET_SIZE ou \ref K_MK_MSC_MAX_PACKET_SIZE.
 * @param[in]     p_firstPartitionSector Ce paramètre contient l'adresse du premier secteur de la partition.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la partition a été décodée.
 *         \li \ref K_MK_ERROR_PARAM   : la partition n'a pas été décodée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : la partition n'a pas été décodée car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : la partition n'a pas été décodée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NESTED  : la partition n'a pas été décodée car la tâche appelante est propriétaire d'un autre objet de synchronisation de type \ref T_mkMutex.
 *         \li \ref K_MK_ERROR_TIMEOUT : la partition n'a pas été décodée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la partition n'a pas été décodée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : les volumes n'ont pas été initialisés car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_volume_decodeFAT32 ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector );

/**
 * @fn T_mkCode mk_volume_decodeNTFS ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector );
 * @brief Cette fonction décode une partition NTFS puis si elle est supportée, l'alloue et l'ajoute dans la liste des partitions d'un disque.
 *
 * @param[in,out] p_disk                 Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[out]    p_list                 Ce paramètre contient l'adresse d'un pointeur de partition de type \ref T_mkVolume.
 * @param[in]     p_buf                  Ce paramètre contient l'adresse d'un buffer de taille \ref K_MK_MMC_MAX_PACKET_SIZE ou \ref K_MK_MSC_MAX_PACKET_SIZE.
 * @param[in]     p_firstPartitionSector Ce paramètre contient l'adresse du premier secteur de la partition.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la partition a été décodée.
 *         \li \ref K_MK_ERROR_PARAM   : la partition n'a pas été décodée car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_MALLOC  : la partition n'a pas été décodée car une erreur d'allocation dynamique s'est produite.
 *         \li \ref K_MK_ERROR_ISR     : la partition n'a pas été décodée car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_NESTED  : la partition n'a pas été décodée car la tâche appelante est propriétaire d'un autre objet de synchronisation de type \ref T_mkMutex.
 *         \li \ref K_MK_ERROR_TIMEOUT : la partition n'a pas été décodée car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la partition n'a pas été décodée car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : les volumes n'ont pas été initialisés car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_volume_decodeNTFS ( T_mkDisk* p_disk, T_mkVolume** p_list, uint8_t* p_buf, uint32_t p_firstPartitionSector );

/**
 * @fn T_mkCode mk_volume_dispatch ( T_mkVolume* p_volume, uint16_t p_ctrlEvt );
 * @brief Cette fonction notifie le dispatcher qu'un événement s'est produit sur une partition.
 *
 * @param[in]  p_volume  Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in] p_ctrlEvt Ce paramètre contient l'identifiant de l'événement à notifier (\ref T_mkCtrlEvent).
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la notification a été transmise au dispatcher.
 *         \li \ref K_MK_ERROR_PARAM   : la notification n'a pas été transmise au dispatcher car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la notification n'a pas été transmise au dispatcher car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la notification n'a pas été transmise au dispatcher car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la notification n'a pas été transmise au dispatcher car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_volume_dispatch ( T_mkVolume* p_volume, uint16_t p_ctrlEvt );

/**
 *
 */

#endif


