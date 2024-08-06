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
* @file mk_dispatcher_postEvent.c
* @brief Définition de la fonction mk_dispatcher_postEvent.
* @date 18 déc. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_postEvent ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkAddr p_ctrlAddr, uint16_t p_appId, uint16_t p_id )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Configuration du message de sortie */
   l_message.appCtrlID = p_appId;                     /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
   l_message.appCtrl   = p_ctrlAddr;                  /* Adresse du contrôle applicatif */
   l_message.ctrlId    = p_id;                        /* Identifiant du contrôle */
   l_message.ctrlEvt   = p_message->ctrlEvt;          /* Identifiant de l'événement généré */
   l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

   /* Transmission d'un message */
   l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );

   /* Retour */
   return ( l_result );
}




