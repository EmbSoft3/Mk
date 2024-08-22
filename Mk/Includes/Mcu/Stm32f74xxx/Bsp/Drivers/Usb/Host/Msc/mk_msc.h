/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_msc.h
* @brief Déclaration des fonctions publiques dédiées aux périphériques de stockage.
* @date 24 mai 2021
*
*/

#ifndef MK_MSC_H
#define MK_MSC_H

/**
 * @fn T_mkCode mk_msc_getFirstDevice ( T_mkMSCDevice** p_device );
 * @brief Cette fonction retourne l'adresse du premier périphérique MSC d'une liste.
 *        La valeur \ref K_MK_NULL est renvoyée si aucun périphérique n'a été alloué.
 * @param[out] p_device Ce paramètre contient l'adresse d'un pointeur de périphérique de type \ref T_mkMSCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_msc_getFirstDevice ( T_mkMSCDevice** p_device );

/**
 * @fn T_mkCode mk_msc_getNextDevice ( T_mkMSCDevice** p_device, T_mkMSCDevice* p_currentDevice );
 * @brief Cette fonction retourne l'adresse du prochain périphérique MSC d'une liste.
 *        La valeur \ref K_MK_NULL est renvoyée si le périphérique p_currentDevice est le dernier de la liste.
 *
 * @param[out] p_device        Ce paramètre contient l'adresse d'un pointeur de périphérique de type \ref T_mkMSCDevice.
 * @param[in]  p_currentDevice Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_msc_getNextDevice ( T_mkMSCDevice** p_device, T_mkMSCDevice* p_currentDevice );

/**
 * @fn T_mkCode mk_msc_getFirstDisk ( T_mkMSCDevice* p_device, T_mkDisk** p_disk );
 * @brief Cette fonction retourne l'adresse du premier disque d'une liste.
 *        La valeur \ref K_MK_NULL est renvoyée si aucun disque n'a été alloué.
 *
 * @param[in]  p_device Ce paramètre contient l'adresse d'un périphérique de type \ref T_mkMSCDevice.
 * @param[out] p_disk   Ce paramètre contient l'adresse d'un pointeur de disque de type \ref T_mkDisk.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_msc_getFirstDisk ( T_mkMSCDevice* p_device, T_mkDisk** p_disk );

/**
 * @fn T_mkCode T_mkCode mk_msc_getNextDisk ( T_mkDisk** p_disk, T_mkDisk* p_currentDisk );
 * @brief Cette fonction retourne l'adresse du prochain disque d'une liste.
 *        La valeur \ref K_MK_NULL est renvoyée si le disque p_currentDisk est le dernier de la liste.
 *
 * @param[out] p_disk        Ce paramètre contient l'adresse d'un pointeur de disque de type \ref T_mkDisk.
 * @param[in]  p_currentDisk Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_msc_getNextDisk ( T_mkDisk** p_disk, T_mkDisk* p_currentDisk );

/**
 * @fn T_mkCode mk_msc_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, T_mkCallback* p_callback );
 * @brief Cette fonction lit un ou plusieurs blocs de données d'un disque.
 *
 * @param[in]  p_disk                Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress        Ce paramètre contient l'adresse du premier bloc de données à lire.
 * @param[out] p_buf                 Ce paramètre contient l'adresse d'un buffer de données. La taille du buffer doit être multiple de la taille d'un bloc de données.
 * @param[in]  p_numberOfBlockToRead Ce paramètre contient le nombre de blocs de données à lire.
 * @param[out] p_numberOfBytesRead   Ce paramètre contient le nombre d'octets lus.
 * @param[in]  p_callback            Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : la lecture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : la lecture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : la lecture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : la lecture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : la lecture des blocs de données a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : la lecture des blocs de données a échoué en raison d'une erreur de communication.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_msc_callback ( T_mkCode p_result, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );
 *
 */

T_mkCode mk_msc_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, T_mkCallback* p_callback );

/**
 * @fn T_mkCode mk_msc_write ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, T_mkCallback* p_callback );
 * @brief  * @brief Cette fonction écrit un ou plusieurs blocs de données d'un disque.
 *
 * @param[in]  p_disk                 Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[in]  p_blockAddress         Ce paramètre contient l'adresse du premier bloc de données à écrire.
 * @param[out] p_buf                  Ce paramètre contient l'adresse d'un buffer de données. La taille du buffer doit être multiple de la taille d'un bloc de données.
 * @param[in]  p_numberOfBlockToWrite Ce paramètre contient le nombre de blocs de données à écrire.
 * @param[out] p_numberOfBytesWrite   Ce paramètre contient le nombre d'octets écrits.
 * @param[in]  p_callback             Ce paramètre contient l'adresse d'une fonction de rappel.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK            : l'écriture des blocs de données a réussi.
 *         \li \ref K_MK_ERROR_PARAM   : l'écriture des blocs de données a échoué car au moins un paramètre est invalide.
 *         \li \ref K_MK_ERROR_ISR     : l'écriture des blocs de données a échoué car la fonction a été exécutée depuis un vecteur d'interruption.
 *         \li \ref K_MK_ERROR_RIGHT   : l'écriture des blocs de données a échoué car une tâche de type non privilégié ne possède pas suffisamment de droits.
 *         \li \ref K_MK_ERROR_TIMEOUT : l'écriture des blocs de données a échoué en raison d'une erreur de timeout.
 *         \li \ref K_MK_ERROR_COMM    : l'écriture des blocs de données a échoué en raison d'une erreur de communication.
 *
 * @note Lorsque le paramètre p_callback est \ref K_MK_NULL, la requête est réalisée de manière bloquante. Le résultat est disponible
 *       dans la variable de retour de la fonction.\n
 *       Lorsque le paramètre p_callback est différent de \ref K_MK_NULL, la requête est traitée de manière non-bloquante. Le résultat de la requête
 *       est récupéré en utilisant la fonction de rappel suivante : void mk_mmc_callback ( T_mkCode p_result, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );
 *
 */

T_mkCode mk_msc_write ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, T_mkCallback* p_callback );

/**
 *
 */

#endif

