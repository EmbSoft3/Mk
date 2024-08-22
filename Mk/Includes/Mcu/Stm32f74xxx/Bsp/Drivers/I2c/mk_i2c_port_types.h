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
* @file mk_i2c_port_types.h
* @brief Déclaration des types dédiés aux port I2C.
* @date 1 nov. 2020
*
*/

#ifndef MK_I2C_PORT_TYPES_H
#define MK_I2C_PORT_TYPES_H

/**
 * @struct T_mkI2CStatus
 * @brief Déclaration de l'énumération T_mkI2CStatus.
 *
 */

typedef enum T_mkI2CStatus
{
   K_MK_I2C_NO_FLAG = 0,                              /*!< Définition d'un code indiquant l'absence de statut. */
   K_MK_I2C_FLAG_ADDRESS_MATCHED = 0x08,              /*!< Définition d'un code indiquant la réception d'une trame à destination du périphérique esclave. */
   K_MK_I2C_ERROR_NACK = 0x10,                        /*!< Définition d'un code indiquant l'absence d'acquittement d'une trame. */
   K_MK_I2C_FLAG_STOP = 0x20,                         /*!< Définition d'un code indiquant la présence d'un bit de stop. */
   K_MK_I2C_FLAG_TRANSFER_COMPLETED = 0x40,           /*!< Définition d'un code indiquant le succès du transfert. */
   K_MK_I2C_FLAG_TRANSFER_RELOAD_COMPLETED = 0x80,    /*!< Définition d'un code indiquant le succès du transfert (mode 'Reload'). */
   K_MK_I2C_ERROR_BUS = 0x100,                        /*!< Définition d'un code indiquant la détection d'une erreur. */
   K_MK_I2C_FLAG_ARBITRATION_LOST = 0x200,            /*!< Définition d'un code indiquant la détection d'un conflit d'arbitration. */
   K_MK_I2C_ERROR_OVERRUN_UNDERRUN = 0x400,           /*!< Définition d'un code indiquant la présence d'une erreur de débordement. */
   K_MK_SMBUS_ERROR_PEC = 0x800,                      /*!< Définition d'un code indiquant la présence d'une erreur de type PEC. */
   K_MK_I2C_ERROR_TIMEOUT = 0x1000,                   /*!< Définition d'un code indiquant la présence d'une erreur de timeout. */
   K_MK_SMBUS_FLAG_ALERT = 0x2000,                    /*!< Définition d'un code indiquant la présence d'une alerte SMBUS. */
   K_MK_I2C_FLAG_BUSY = 0x8000,                       /*!< Définition d'un code indiquant la présence d'une communication sur le bus. */

   K_MK_I2C_DMA_ERROR = 0x04000000,                   /*!< Définition d'un code indiquant la détection d'une erreur DMA suite au déclenchement d'un transfert. */
   K_MK_I2C_TRANSFER_ABORTED = 0x08000000,            /*!< Définition d'un code indiquant l'arrêt d'un transfert suite à une erreur de communication. */
   K_MK_I2C_TRANSFER_END = 0x10000000,                /*!< Définition d'un code indiquant la fin d'un transfert (bit de stop). */
   K_MK_I2C_TRANSFER_DONE = 0x20000000                /*!< Définition d'un code indiquant la complétude d'un transfert. */
} T_mkI2CStatus;

/**
 * @struct T_mkI2CFrame
 * @brief Déclaration de la structure T_mkI2CFrame.
 *
 */

typedef struct T_mkI2CFrame T_mkI2CFrame;
struct T_mkI2CFrame
{
  uint32_t direction;                                 /*!< Ce membre contient la direction du transfert ( \ref K_I2C_WRITE et \ref K_I2C_READ ). */
  uint8_t* reg;                                       /*!< Ce membre contient l'adresse du buffer d'écriture. */
  uint32_t regLength;                                 /*!< Ce membre contient le nombre d'octets à écrire sur le bus (phase d'écriture). */
  uint32_t regTimeout;                                /*!< Ce membre contient le timeout de transmission des données (valable pour chaque paquet de \ref K_MK_I2C_MAX_SIZE octets). */

  uint8_t* data;                                      /*!< Ce membre contient l'adresse du buffer de lecture. */
  uint32_t dataLength;                                /*!< Ce membre contient le nombre d'octets à lire sur le bus (phase de lecture). */
  uint32_t dataTimeout;                               /*!< Ce membre contient le le timeout de réception des données (valable pour chaque paquet de \ref K_MK_I2C_MAX_SIZE octets). */
};

/**
 * @struct T_mkI2CStatus
 * @brief Déclaration de la structure T_mkI2CStatus.
 *
 */

typedef struct T_mkI2CTransferStatus T_mkI2CTransferStatus;
struct T_mkI2CTransferStatus
{
   T_mkI2CStatus status;                              /*!< Ce membre contient le statut de la communication I2C après le déclenchement d'un transfert. */
   uint32_t numberOfBytesWrite;                       /*!< Ce membre contient le nombre d'octets écrits sur le bus I2C après déclenchement d'un transfert. */
   uint32_t numberOfBytesRead;                        /*!< Ce membre contient le nombre d'octets lus sur le bus I5C suite au déclenchement d'un transfert. */
   uint8_t* incomingBuf;                              /*!< Ce membre contient l'adresse du buffer de réception où ont été stockées les données reçues. */
};

/**
 *
 */

#endif


