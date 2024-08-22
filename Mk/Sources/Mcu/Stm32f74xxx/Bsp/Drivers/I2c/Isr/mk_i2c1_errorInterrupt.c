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
* @file mk_i2c1_errorInterrupt.c
* @brief Définition de la fonction mk_i2c1_errorInterrupt.
* @date 1 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_handleErrorInterrupt ( T_mkI2CHandler* p_handler )
{
   /* Récupération de la valeur du registre de statut */
   uint32_t l_status = i2c_getStatus ( K_I2C1, K_I2C_SMBUS_ALERT_INTERRUPT | K_I2C_TIMEOUT_INTERRUPT | K_I2C_PEC_ERROR_INTERRUPT |
                                       K_I2C_OVERRUN_UNDERRUN_INTERRUPT | K_I2C_ARBITRATION_LOST_INTERRUPT | K_I2C_BUS_ERROR_INTERRUPT );

   /* Si une alerte SMBUS est présente */
   if ( ( l_status & K_I2C_SMBUS_ALERT_INTERRUPT ) > 0 )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_SMBUS_FLAG_ALERT );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une erreur protocolaire SMBUS est présente */
   if ( ( l_status & K_I2C_PEC_ERROR_INTERRUPT ) > 0 )
   {
      /* Transmission d'un événement au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_SMBUS_ERROR_PEC );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une erreur s'est produite */
   if ( ( l_status & ( K_I2C_OVERRUN_UNDERRUN_INTERRUPT | K_I2C_ARBITRATION_LOST_INTERRUPT |
                       K_I2C_TIMEOUT_INTERRUPT | K_I2C_BUS_ERROR_INTERRUPT ) ) > 0 )
   {
      /* Transmission des événements au terminal */
      ( void ) mk_event_set ( p_handler->portEvent, K_MK_I2C_TRANSFER_ABORTED | l_status );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Réinitialisation des statuts d'interruption */
   i2c_clearStatus ( K_I2C1, K_I2C_SMBUS_ALERT_INTERRUPT | K_I2C_TIMEOUT_INTERRUPT | K_I2C_PEC_ERROR_INTERRUPT |
                     K_I2C_OVERRUN_UNDERRUN_INTERRUPT | K_I2C_ARBITRATION_LOST_INTERRUPT | K_I2C_BUS_ERROR_INTERRUPT  );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_i2c1_errorInterrupt ( void )
{
   /* Si la structure de données du terminal a été configurée */
   if ( g_mkTermioHandler.i2c1->child != K_MK_NULL )
   {
      /* Gestion des interruptions d'erreur I2C */
      mk_i2c_handleErrorInterrupt ( g_mkTermioHandler.i2c1->child );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;

   /* Retour */
   return;
}


