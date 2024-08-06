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
* @file mk_dispatcher_handleMouse.c
* @brief Définition de la fonction mk_dispatcher_handleMouse.
* @date 18 nov. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_handleMouseButton ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message, T_mkMouse* p_mouse )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du premier bouton de la souris */
   T_mkButton* l_button = p_mouse->button;

   /* Traitement des boutons de la souris */
   while ( ( l_result == K_MK_OK ) && ( l_button != K_MK_NULL ) )
   {
      /* Gestion du bouton courant */
      l_result = mk_dispatcher_handleButton ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_MOUSE, ( T_mkAddr ) p_mouse, ( T_mkAddr ) l_button );

      /* Actualisation du pointeur de bouton */
      l_button = l_button->nextButton;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleMouse ( T_mkDispatcherHandler* p_handler, T_mkDispatcherMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de souris */
   T_mkMouse* l_mouse = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_message != K_MK_NULL ) && ( p_message->appCtrl != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du contrôle */
      l_mouse = p_message->appCtrl;

      /* Si un événement a été configuré */
      if ( p_message->ctrlEvt != K_MK_EVENT_NO )
      {
         /* Transmission d'un message à la tâche d'écoute */
         l_result = mk_dispatcher_postEvent ( p_handler, p_message, l_mouse, K_MK_CONTROL_MOUSE, l_mouse->layer.id );
      }

      /* Sinon */
      else
      {
         /* Génération des événements relatifs aux boutons de la souris */
         l_result = mk_dispatcher_handleMouseButton ( p_handler, p_message, l_mouse );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Génération des événements relatifs au pointeur de la souris */
            l_result = mk_dispatcher_handlePointer ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_MOUSE, ( T_mkAddr ) l_mouse, ( T_mkAddr ) &l_mouse->axis );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Génération des événements relatifs à la molette de la souris */
               l_result = mk_dispatcher_handleWheel ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_MOUSE, ( T_mkAddr ) l_mouse, ( T_mkAddr ) &l_mouse->wheel );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Génération des événements relatifs à la molette horizontale de la souris */
                  l_result = mk_dispatcher_handleACPan ( p_handler, p_message, ( uint16_t ) K_MK_CONTROL_MOUSE, ( T_mkAddr ) l_mouse, ( T_mkAddr ) &l_mouse->acPan );
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
               /* Ne rien faire */
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
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


