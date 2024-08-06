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
* @file mk_disk.h
* @brief Déclaration des fonctions publiques dédiées aux disques.
* @date 11 sept. 2021
*
*/

#ifndef MK_DISK_H
#define MK_DISK_H

/**
 * @fn T_mkCode mk_disk_getFirstVolume ( T_mkDisk* p_disk, T_mkVolume** p_volume );
 * @brief Cette fonction retourne l'adresse de la première partition d'un disque. La valeur \ref K_MK_NULL est renvoyée si le disque ne possède aucune partition.
 *
 * @param[in]  p_disk   Ce paramètre contient l'adresse d'un disque de type \ref T_mkDisk.
 * @param[out] p_volume Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_disk_getFirstVolume ( T_mkDisk* p_disk, T_mkVolume** p_volume );

/**
 * @fn T_mkCode mk_disk_getNextVolume ( T_mkVolume** p_volume, T_mkVolume* p_currentVolume );
 * @brief Cette fonction retourne l'adresse de la prochaine partition d'un disque. La valeur \ref K_MK_NULL est renvoyée si la partition p_volume est la dernière
 *        partition du disque.
 *
 * @param[out] p_volume        Ce paramètre contient l'adresse d'une partition de type \ref T_mkVolume.
 * @param[in]  p_currentVolume Ce paramètre contient l'adresse d'une partition d'un disque.
 *
 * @return Cette fonction retourne une des valeurs suivantes :
 *         \li \ref K_MK_OK          : la fonction a réussi.
 *         \li \ref K_MK_ERROR_PARAM : la fonction a échoué car au moins un paramètre est invalide.
 *
 */

T_mkCode mk_disk_getNextVolume ( T_mkVolume** p_volume, T_mkVolume* p_currentVolume );

/**
 * @fn T_mkCode mk_disk_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );
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

T_mkCode mk_disk_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead );

/**
 * @fn T_mkCode mk_disk_write ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );
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

T_mkCode mk_disk_write ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite );

/**
 *
 */

#endif

