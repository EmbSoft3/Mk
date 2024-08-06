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
* @file mk_dispatcher_handleIndicator.c
* @brief Définition de la fonction mk_dispatcher_handleIndicator.
* @date 5 janv. 2020
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_handleIndicator ( T_mkDispatcherHandler* p_handler, T_mkKeyboard* p_keyboard, T_mkKey* p_key )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_state = 0;

   /* Déclaration d'un message */
   T_mkDispatcherMessage l_message = {
         p_keyboard, 0, 0, 0, 0
   };

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_keyboard != K_MK_NULL ) )
   {
      /* Les touches CAPSLOCK et NUMLOCK modifient le comportement du clavier. On récupére l'état de ces touches */
      /* pour réaliser les actions appropriées. */

      /* Les scancodes _LOCKING_FUNCTION définissent des touches verrouillables de certain clavier. Leur fréquence d'apparition et très faible. */
      /* Elles peuvent être supprimé du code si nécessaire. */

      /* Si l'adresse d'une touche est présente en paramètre */
      /* Les événement CONNECT ET DISCONNECT ne génére pas de touches */
      if ( p_key != K_MK_NULL )
      {
         /* Si la touche 'CapsLock' a été sélectionnée */
         if ( ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_CAPSLOCK ) || ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_LOCKING_CAPSLOCK ) )
         {
            /* Actualisation de l'état du clavier */
            p_keyboard->specialKey.capslock = ( ( ~ p_keyboard->specialKey.capslock ) & 0x1 );

            /* Basculement de l'état de la LED. */
            /* La valeur initiale est la valeur nulle. */
            mk_hid_led_toogle ( p_keyboard->indicator, K_MK_HID_LED_PAGE_CAPS_LOCK );
         }

         /* Sinon si la touche 'NumLock' a été sélectionnée */
         else if ( ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYPAD_NUMLOCK_CLEAR ) || ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_LOCKING_NUMLOCK ) )
         {
            /* Actualisation de l'état du clavier */
            p_keyboard->specialKey.numlock = ( ( ~ p_keyboard->specialKey.numlock ) & 0x1 );

            /* Basculement de l'état de la LED. */
            /* La valeur initiale est la valeur nulle. */
            mk_hid_led_toogle ( p_keyboard->indicator, K_MK_HID_LED_PAGE_NUM_LOCK );
         }

         /* Sinon si la touche 'ScrollLock' a été sélectionnée */
         else if ( ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_SCROLLLOCK ) || ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_LOCKING_SCROLLLOCK ) )
         {
            /* Actualisation de l'état du clavier */
            p_keyboard->specialKey.scrolllock = ( ( ~ p_keyboard->specialKey.scrolllock ) & 0x1 );

            /* Basculement de l'état de la LED. */
            /* La valeur initiale est la valeur nulle. */
            mk_hid_led_toogle ( p_keyboard->indicator, K_MK_HID_LED_PAGE_SCROLL_LOCK );
         }

         /* Sinon si la touche 'Compose' a été sélectionnée (cf. note 10 page 59 du document Universal Serial Bus HID Usage Tables) */
         else if ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_APPLICATION )
         {
            /* Basculement de l'état de la LED. */
            /* La valeur initiale est la valeur nulle. */
            mk_hid_led_toogle ( p_keyboard->indicator, K_MK_HID_LED_PAGE_COMPOSE );
         }

         /* Sinon si la touche 'Kana' a été sélectionnée (cf. note 30 page 60 du document Universal Serial Bus HID Usage Tables) */
         else if ( p_key->button.state.value == K_MK_HID_KEY_PAGE_KEYBOARD_LANG3 )
         {
            /* Basculement de l'état de la LED. */
            /* La valeur initiale est la valeur nulle. */
            mk_hid_led_toogle ( p_keyboard->indicator, K_MK_HID_LED_PAGE_KANA );
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable d'état */
            l_state = 1;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le clavier possède des indicateurs lumineux */
      if ( ( p_keyboard->indicator != K_MK_NULL ) && ( l_state == 0 ) )
      {
         /* Transmission d'un message au terminal HID */
         l_result = mk_mail_post ( p_handler->hidArea->mail, &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
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


