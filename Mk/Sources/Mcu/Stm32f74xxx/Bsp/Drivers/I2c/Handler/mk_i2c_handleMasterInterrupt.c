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
* @file mk_i2c_handleMasterInterrupt.c
* @brief Définition de la fonction mk_i2c_handleMasterInterrupt.
* @date 23 déc. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_i2c_handleMasterInterrupt ( T_mkI2CHandler* p_handler )
{
   /* Récupération de la valeur du registre de statuts */
   uint32_t l_status = i2c_getStatus ( p_handler->bus, K_I2C_TRANSFER_COMPLETE_RELOAD_STATUS | K_I2C_TRANSFER_COMPLETE_STATUS |
                                       K_I2C_STOP_DETECTION_INTERRUPT | K_I2C_NACK_ERROR_INTERRUPT | K_I2C_ADDRESS_MATCHED_INTERRUPT |
                                       K_I2C_TRANSFER_DIRECTION_STATUS );

   /* Si un bit de stop a été détecté */
   if ( ( l_status & K_I2C_STOP_DETECTION_INTERRUPT ) > 0 )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_I2C_TRANSFER_END | l_status );
   }

   /* Sinon si le transfert est terminé */
   else if ( ( l_status & ( K_I2C_TRANSFER_COMPLETE_RELOAD_STATUS | K_I2C_TRANSFER_COMPLETE_STATUS ) ) > 0 )
   {
      /* Désactivation de l'interruption (Reload + Complete) */
      i2c_disableInterrupt ( p_handler->bus, K_I2C_TRANSFER_COMPLETE_INTERRUPT );

      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_I2C_TRANSFER_DONE | l_status );
   }

   /* Sinon si une erreur d'acquittement s'est produite */
   else if ( ( l_status & K_I2C_NACK_ERROR_INTERRUPT ) > 0 )
   {
      /* Désactivation de l'interruption */
      i2c_disableInterrupt ( p_handler->bus, K_I2C_TRANSFER_COMPLETE_INTERRUPT );

      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_I2C_TRANSFER_ABORTED | l_status );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une trame entrante a été détectée */
   if ( ( l_status & K_I2C_ADDRESS_MATCHED_INTERRUPT ) > 0 )
   {
      /* Transmission d'un événement au terminal (la direction du transfert est présente dans le statut */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_I2C_FLAG_ADDRESS_MATCHED | l_status );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Réinitialisation des statuts d'interruption */
   i2c_clearStatus ( p_handler->bus, K_I2C_STOP_DETECTION_INTERRUPT | K_I2C_NACK_ERROR_INTERRUPT | K_I2C_ADDRESS_MATCHED_INTERRUPT );

   /* Retour */
   return;
}
