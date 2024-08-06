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
* @file mk_disk_private.h
* @brief Déclaration des fonctions privées dédiés aux disques.
* @date 15 juin 2020
*
*/

#ifndef MK_DISK_PRIVATE_H
#define MK_DISK_PRIVATE_H

/**
 * @fn T_mkCode mk_disk_dispatch ( T_mkDisk* p_disk, uint16_t p_ctrlEvt );
 * @brief Cette fonction notifie le dispatcher qu'un événement s'est produit sur un disque.
 *
 * @param[in] p_disk    Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
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

T_mkCode mk_disk_dispatch ( T_mkDisk* p_disk, uint16_t p_ctrlEvt );

/**
 * @fn T_mkCode mk_disk_delete ( T_mkDisk** p_list, T_mkDisk* p_disk, uint32_t p_enableEvent );
 * @brief Cette fonction désalloue la mémoire disque s'il n'est pas en utilisation.
 *
 * @param[in, out] p_list        Ce paramètre contient l'adresse d'une liste de disques de type \ref T_mkDisk.
 * @param[in]      p_disk        Ce paramètre contient l'adresse du disque à supprimer.
 * @param[in]      p_enableEvent Ce paramètre contient un drapeau permettant de transmettre (valeur 1) ou non (valeur 0) l'événement \ref K_MK_EVENT_DISCONNECT
 *                               au dispatcher.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la suppression du disque a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la suppression du disque a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_TIMEOUT : la suppression du disque a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_ISR     : la suppression du disque a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la suppression du disque a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_disk_delete ( T_mkDisk** p_list, T_mkDisk* p_disk, uint32_t p_enableEvent );

/**
 * @fn T_mkCode mk_disk_readSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );
 * @brief Cette fonction lit un ou plusieurs blocs de données d'un disque. La taille du buffer doit être multiple de la taille d'un bloc de données.
 *
 * @param[in]  p_disk                Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress        Ce paramètre contient l'adresse du premier bloc de données à lire.
 * @param[out] p_buf                 Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]  p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out] p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus suite à l'exécution de cette fonction.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la lecture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : la lecture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : la lecture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : la lecture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_disk_readSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );

/**
 * @fn T_mkCode mk_disk_writeSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );
 * @brief Cette fonction écrit un ou plusieurs blocs de données. La taille du buffer doit être multiple de la taille d'un bloc de données.
 *
 * @param[in]  p_disk                 Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress         Ce paramètre contient l'adresse du premier bloc de données à écrire.
 * @param[in]  p_buf                  Ce paramètre contient l'adresse d'un buffer de données.
 * @param[in]  p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out] p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits suite à l'exécution de cette fonction.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué car un timeout s'est produit.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué car une erreur de communication s'est produite.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *
 */

T_mkCode mk_disk_writeSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );

/**
 *
 */

#endif



