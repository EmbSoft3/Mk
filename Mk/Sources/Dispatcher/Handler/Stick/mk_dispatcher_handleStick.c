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
* @file mk_dispatcher_handleStick.c
* @brief Définition de la fonction mk_dispatcher_handleStick.
* @date 25 avr. 2020
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleStick ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, uint16_t p_appCtrlId, T_mkAddr p_appCtrl, T_mkAddr p_axis )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message à destination de la tâche d'écoute */
   T_mkListenerMessage l_message;

   /* Déclaration d'un pointeur de bouton */
   T_mkStick3* l_stick = ( T_mkStick3* ) p_axis;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_message != K_MK_NULL ) && ( p_axis != K_MK_NULL ) )
   {
      /* Configuration du message de sortie */
      l_message.ctrlEvt   = K_MK_EVENT_MOVE;             /* Identifiant de l'événement généré */
      l_message.ctrlId    = 0;                           /* Identifiant du contrôle */
      l_message.appCtrlID = p_appCtrlId;                 /* Identifiant du contrôle applicatif (Mouse, Keyboard, Joystick, ...) */
      l_message.appCtrl   = p_appCtrl;                   /* Adresse du contrôle applicatif */
      l_message.tick      = p_message->tick;             /* Numéro du tick enregistré lors de la détection de l'événement */

      /* Si un déplacement du curseur s'est produit */
      if ( ( l_stick->current.x != l_stick->last.x ) || ( l_stick->current.y != l_stick->last.y ) || ( l_stick->current.z != l_stick->last.z ) ||
           ( l_stick->current.rx != l_stick->last.rx ) || ( l_stick->current.ry != l_stick->last.ry ) || ( l_stick->current.rz != l_stick->last.rz ) )
      {
         /* Détermination de la valeur des coordonnées */
         l_stick->x = ( ( real32_t ) l_stick->current.x * p_handler->attribute.stickResolution );
         l_stick->y = ( ( real32_t ) l_stick->current.y * p_handler->attribute.stickResolution );
         l_stick->z = ( ( real32_t ) l_stick->current.z * p_handler->attribute.stickResolution );
         l_stick->dx = ( ( real32_t ) ( l_stick->last.x - l_stick->current.x ) * p_handler->attribute.stickResolution );
         l_stick->dy = ( ( real32_t ) ( l_stick->last.y - l_stick->current.y ) * p_handler->attribute.stickResolution );
         l_stick->dz = ( ( real32_t ) ( l_stick->last.z - l_stick->current.z ) * p_handler->attribute.stickResolution );
         l_stick->rx = ( ( real32_t ) l_stick->current.rx * p_handler->attribute.stickResolution );
         l_stick->ry = ( ( real32_t ) l_stick->current.ry * p_handler->attribute.stickResolution );
         l_stick->rz = ( ( real32_t ) l_stick->current.rz * p_handler->attribute.stickResolution );

         /* Actualisation des valeurs précédentes */
         l_stick->last.x = l_stick->current.x;
         l_stick->last.y = l_stick->current.y;
         l_stick->last.z = l_stick->current.z;
         l_stick->last.rx = l_stick->current.rx;
         l_stick->last.ry = l_stick->current.ry;
         l_stick->last.rz = l_stick->current.rz;

         /* Transmission d'un message */
         l_result = mk_mail_post ( p_handler->listenerArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

