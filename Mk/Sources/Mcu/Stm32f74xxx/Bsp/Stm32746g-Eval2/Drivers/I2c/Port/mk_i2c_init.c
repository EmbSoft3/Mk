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
* @file mk_i2c_init.c
* @brief Définition de la fonction mk_i2c_init.
* @date 10 oct. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_i2c_init ( T_mkI2CHandler* p_handler, T_mkI2CSetting* p_setting )
{
   /* Désactivation du périphérique I2C */
   i2c_disable ( p_handler->bus );

   /* Désactivation de la couche protocolaire SMBUS */
   i2c_disablePacketErrorChecking ( p_handler->bus );
   i2c_disableAlert ( p_handler->bus );
   i2c_disableAddress ( p_handler->bus, K_I2C_SMBUS_DEFAULT_ADDRESS | K_I2C_SMBUS_HOST_ADDRESS | K_I2C_BROADCAST_ADDRESS );
   i2c_disableTimeout ( p_handler->bus );

   /* Désactivation des fonctionnalités dédiées au mode esclave */
   i2c_disableByteCounter ( p_handler->bus );

   /* Configuration des addresses du périphérique escalve */
   i2c_disableSlaveAddress ( p_handler->bus, p_setting->deviceAddr1 );
   i2c_disableSlaveAddress ( p_handler->bus, p_setting->deviceAddr1 );

   /* Activation des filtres numérique et analogique */
   i2c_enableAnalogNoiseFilter ( p_handler->bus );
   i2c_enableDigitalNoiseFilter ( p_handler->bus, 15 );

   /* Si le mode 'Stretching' doit être activé */
   if ( p_setting->enableStretching != 0 )
   {
      /* Activation du Stretching I2C */
      i2c_enableStretching ( p_handler->bus );
   }

   /* Sinon */
   else
   {
      /* Déactivation du Stretching I2C */
      i2c_disableStretching ( p_handler->bus );
   }

   /* Si le mode d'adressage 10 bits doit être activé */
   if ( p_setting->addressLength == K_I2C_10BITS_MODE )
   {
      /* Activation de l'adressage 10 bits */
      i2c_enable10BitsAddressingMode ( p_handler->bus );
   }

   /* Sinon */
   else
   {
      /* Activation de l'adressage 7 bits */
      i2c_enable7BitsAddressingMode ( p_handler->bus );
   }

   /* Activation des interruptions I2C */
   i2c_enableInterrupt ( p_handler->bus, K_I2C_ERROR_INTERRUPTS | K_I2C_STOP_DETECTION_INTERRUPT | K_I2C_NACK_INTERRUPT | K_I2C_ADDRESS_MATCHED_INTERRUPT );

   /* Activation de la gestion automatique des bits de stop */
   i2c_disableEndMode ( p_handler->bus );

   /* Configuration du type de l'entête I2C */
   i2c_enableShortHeader ( p_handler->bus );

   /* Configuration des timing I2C */
   i2c_setPrescaler ( p_handler->bus, p_setting->mainPrescaler );
   i2c_setClock ( p_handler->bus, p_setting->clockLowPrescaler, p_setting->clockHighPrescaler );
   i2c_setDataSetupTime ( p_handler->bus, p_setting->dataSetupTime );
   i2c_setDataHoldTime ( p_handler->bus, p_setting->dataHoldTime );

   /* T(Timeout) = T(Périph) * 2048 * 25 ~ 1ms */
   i2c_disableExtendedClockTimeout ( p_handler->bus );

   /* Activation du périphérique I2C */
   i2c_enable ( p_handler->bus );

   /* Retour */
   return;
}
