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
* @file mk_disk_request_types.h
* @brief Déclaration des types dédiés à la messagerie des disques.
* @date 7 févr. 2021
*
*/

#ifndef MK_DISK_REQUEST_TYPES_H
#define MK_DISK_REQUEST_TYPES_H

/**
 * @enum T_mkDiskRequestIdentifier
 * @brief Déclaration de la structure T_mkDiskRequestIdentifier.
 *
 */

typedef enum T_mkDiskRequestIdentifier
{
   K_MK_DISK_IO_READ = 1,                                   /*!< Définition de l'identifiant de la requête de lecture d'un ou plusieurs blocs de données. */
   K_MK_DISK_IO_WRITE = 2,                                  /*!< Définition de l'identifiant de la requête d'écriture d'un ou plusieurs blocs de données. */
   K_MK_DISK_IO_SECURITY = 3                                /*!< Définition de l'identifiant de la requête permettant de configurer les paramètres de sécurité d'un disque. */
} T_mkDiskRequestIdentifier;

/**
 * @enum T_mkDiskSecurityIdentifier
 * @brief Déclaration de la structure T_mkDiskSecurityIdentifier.
 *
 */

typedef enum T_mkDiskSecurityIdentifier
{
   K_MK_DISK_SD_UNLOCK = 0,                                 /*!< Définition de l'identifiant de la requête permettant de dévérrouiller un média SD. */
   K_MK_DISK_SD_SET_PASSWORD = 1,                           /*!< Définition de l'identifiant de la requête permettant de configurer la protection par mot de passe. */
   K_MK_DISK_SD_REMOVE_PASSWORD = 2,                        /*!< Définition de l'identifiant de la requête permettant de supprimer la protection par mot de passe. */
   K_MK_DISK_SD_LOCK = 4                                    /*!< Définition de l'identifiant de la requête permettant de vérrouiller un média SD. */
} T_mkDiskSecurityIdentifier;

/**
 * @struct T_mkDiskRequest
 * @brief Déclaration de la structure T_mkDiskRequest.
 *
 */

typedef struct T_mkDiskRequest T_mkDiskRequest;
struct T_mkDiskRequest
{
   uint32_t requestIdentifier;                              /*!< Ce membre contient l'identifiant d'une requête de type \ref T_mkDiskRequestIdentifier. */
   T_mkAddr disk;                                           /*!< Ce membre contient l'adresse d'un disque (\ref T_mkDisk). */
   T_mkAddr buf;                                            /*!< Ce membre contient l'adresse d'un buffer du données. */
   uint32_t lowBlockAddress;                                /*!< Ce membre contient l'adresse du premier bloc à lire ou écrire (LSB). */
   uint32_t highBlockAddress;                               /*!< Ce membre contient l'adresse du premier bloc à lire ou écrire (MSB). */
   uint32_t numberOfBlock;                                  /*!< Ce membre contient le nombre de blocs à lire ou écrire. */
   uint32_t* lowNumberOfBytesTransfered;                    /*!< Ce membre contient le nombre d'octets transférés (LSB) - alignement 64 bits. */
   uint32_t* highNumberOfBytesTransfered;                   /*!< Ce membre contient le nombre d'octets transférés (MSB). */
   T_mkCode* result;                                        /*!< Ce membre contient le résultat de la requête. */
   T_mkCallback* callback;                                  /*!< Ce membre contient l'adresse d'une fonction de rappel. */
};

/**
 *
 */

#endif
