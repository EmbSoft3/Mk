/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_hcd_handleOvercurrent.c
* @brief Définition de la fonction mk_hcd_handleOvercurrent.
* @date 24 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleOvercurrent ( T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Désactivation de l'alimentation */
   usb_disablePower ( p_handler->bus );

   /* Si au moins un dispositif est connecté sur le bus */
   if ( p_handler->device != K_MK_NULL )
   {
      /* L'alimentation est automatiquement désactivée par le périphérique OTG */

      /* Transmission du signal de déconnection */
      l_result = mk_hcd_signalDisconnectEvent ( p_handler->device );

      /* Suppresssion de l'arborescence de périphériques au complet */
      l_result |= mk_hcd_resetTree ( p_handler );

      /* Réinitialisation du pointeur de périphérique principal */
      p_handler->device = K_MK_NULL;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Attente de 5 sec */
   l_result |= mk_task_sleep ( K_MK_HCD_OVERCURRENT_TIMEOUT );

   /* Réactivation de l'alimentation */
   /* La nouvelle énumération sera effectuée lors de la réception de l'événement de connexion */
   usb_enablePower ( p_handler->bus );

   /* Retour */
   return ( l_result );
}



