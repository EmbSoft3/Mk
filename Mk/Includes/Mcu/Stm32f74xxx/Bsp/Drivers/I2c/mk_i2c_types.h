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
* @file mk_i2c_types.h
* @brief Déclaration des types I2C.
* @date 1 nov. 2020
*
*/

#ifndef MK_I2C_TYPES_H
#define MK_I2C_TYPES_H

/**
 * @enum T_mkI2CRight
 * @brief Déclaration de l'énumération T_mkI2CRight.
 *
 */

typedef enum T_mkI2CRight
{
   K_MK_I2C_RIGHT_DEFAULT = 0,                                 /*!< Définition d'un code indiquant qu'un bus I2C n'est pas utilisé par le système. */
   K_MK_I2C_RIGHT_PROTECTED = 1                                /*!< Définition d'un code indiquant que le bus I2C est protégé (utilisé par le système). Il ne peut pas être accédé par les tâches non privilégié. */
} T_mkI2CRight;

/**
 * @enum T_mkI2CRequest
 * @brief Déclaration de la structure T_mkI2CRequest.
 *
 */

typedef enum T_mkI2CRequest
{
   K_MK_I2C_OPEN_PORT  = 1,                                    /*!< Définition de l'identifiant de la requête permettant d'ouvrir un port de communication (\ref mk_i2c_open). */
   K_MK_I2C_CLOSE_PORT = 2,                                    /*!< Définition de l'identifiant de la requête permettant de fermer un port de communication (\ref mk_i2c_close). */
   K_MK_I2C_POST_PORT  = 3                                     /*!< Définition de l'identifiant de la requête permettant d'envoyer une message sur un port de communication (\ref mk_i2c_postMessage). */
} T_mkI2CRequest;

/**
 * @struct T_mkI2CMessage
 * @brief Déclaration de la structure T_mkI2CMessage.
 *
 */

typedef struct T_mkI2CMessage T_mkI2CMessage;
struct T_mkI2CMessage
{
   uint32_t requestIdentifier;                                 /*!< Ce membre contient l'identifiant d'une requête (\ref T_mkI2CRequest). */
   T_mkAddr device;                                            /*!< Ce membre contient l'adresse d'un périphérique I2C de type \ref T_mkI2CDevice. */
   T_mkAddr setting;                                           /*!< Ce membre contient l'adresse de la structure de configuration de la requête (\ref T_mkI2CSetting pour la fonction \ref mk_i2c_open, \ref T_mkI2CFrame pour la fonction \ref mk_i2c_postMessage, sinon \ref K_MK_NULL). */
   T_mkAddr status;                                            /*!< Ce membre contient l'adresse de la structure le statut de la requête (\ref T_mkI2CTransferStatus pour la fonction \ref mk_i2c_postMessage, sinon \ref K_MK_NULL) */
   T_mkCode* result;                                           /*!< Ce membre contient le résultat de la requête. */
   T_mkCallback* callback;                                     /*!< Ce membre contient l'adresse d'une fonction de rappel. */
};

/**
 * @struct T_mkI2CDMAHandler
 * @brief Déclaration de la structure T_mkI2CDMAHandler.
 *
 */

typedef struct T_mkI2CDMAHandler T_mkI2CDMAHandler;
struct T_mkI2CDMAHandler
{
   uint32_t channel;                                           /*!< Ce membre contient le numéro du canal d'un gestionnaire DMA. */
   uint32_t stream;                                            /*!< Ce membre contient le numéro du flux d'un gestionnaire DMA. */
   T_mkDMAPipe* pipe;                                          /*!< Ce membre contient l'adresse du pipe de communication d'un gestionnaire DMA. */
   T_mkDMACallback callback;                                   /*!< Ce membre contient l'adresse de la fonction de rappel d'un gestionnaire DMA. */
};

/**
 * @struct T_mkI2CHandler
 * @brief Déclaration de la structure T_mkI2CHandler.
 *
 */

typedef struct T_mkI2CHandler T_mkI2CHandler;
struct T_mkI2CHandler
{
   T_mkAddr bus;                                               /*!< Ce membre contient l'identifiant d'un bus I2C (\ref K_I2C1 à \ref K_I2C4). */
   T_mkI2CDMAHandler transmit;                                 /*!< Ce membre contient le gestionnaire de transmission DMA. */
   T_mkI2CDMAHandler receive;                                  /*!< Ce membre contient le gestionnaire de réception DMA. */
   T_mkI2CDevice* currentDevice;                               /*!< Ce membre contient l'adresse du dernier périphérique I2C utilisé. */
   T_mkI2CList list;                                           /*!< Ce membre contient la liste de tous les périphériques I2C du gestionnaire. */
   uint32_t right;                                             /*!< Ce membre contient le niveau de protection du bus I2C. */
   T_mkEvent* portEvent;                                       /*!< Ce membre contient le registre d'événements du gestionnaire I2C (gestion des interruptions). */
   uint32_t portStatus;                                        /*!< Ce membre contient les statuts de la communication matérielle lors d'un transfert. */
   T_mkI2CRequestArea* requestArea;                            /*!< Ce membre contient l'adresse de la structure contenant les données de la messagerie du terminal I2C. */
};

/**
 *
 */

#endif

