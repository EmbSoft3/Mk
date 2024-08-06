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
* @file mk_hid_deleteReport.c
* @brief Définition de la fonction mk_hid_deleteReport.
* @date 4 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_deleteControl ( T_mkAddr* p_control )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération du type du contrôle */
   uint16_t* l_type = ( uint16_t* ) ( p_control );

   /* Si le contrôle est de type 'Mouse' */
   if ( ( *l_type ) == K_MK_CONTROL_MOUSE )
   {
      /* Désallocation des attributs dynamiques de l'objet 'Mouse' */
      l_result = mk_hid_mouse_delete ( ( T_mkMouse* ) p_control );
   }

   /* Sinon si le contrôle est de type 'Joystick' */
   else if ( ( *l_type ) == K_MK_CONTROL_JOYSTICK )
   {
      /* Désallocation des attributs dynamiques de l'objet 'Joystick' */
      l_result = mk_hid_joystick_delete ( ( T_mkJoystick* ) p_control );
   }

   /* Sinon si le contrôle est de type 'Keyboard' ou 'Keypad' */
   else if ( ( *l_type ) == K_MK_CONTROL_KEYBOARD )
   {
      /* Désallocation des attributs dynamiques de l'objet 'Keyboard' */
      l_result = mk_hid_keyboard_delete ( ( T_mkKeyboard* ) p_control );
   }

   /* Sinon si le contôle est de type 'Consumer' */
   else if ( ( *l_type ) == K_MK_CONTROL_CONSUMER )
   {
      /* Désaloocation des attributs dynamiques de l'objet 'Consumer' */
      l_result = mk_hid_consumer_delete ( ( T_mkConsumerControl* ) p_control );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_deleteReport ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs de 'report' */
   T_mkHIDReport *l_report, *l_nextReport;

   /* Si le paramètre est valide */
   if ( p_hidDevice != K_MK_NULL )
   {
      /* Initialisation du pointeur de report */
      l_report = p_hidDevice->report;

      /* Tant que l'intégralité des reports n'ont pas été supprimés */
      while ( l_report != K_MK_NULL )
      {
         /* Enregistrement de l'adresse du prochain report */
         l_nextReport = l_report->next;

         /* Si un contrôle est associé au report */
         if ( l_report->addr != K_MK_NULL )
         {
            /* Transmission d'un événement aux dispatcher */
            /* Etant donné que la priorité du dispatcher doit être supérieure à la priorité de la tâche HID, */
            /* le contrôle peut être transféré par référence. */
            l_result |= mk_hid_dispatchMessage ( l_report, K_MK_EVENT_DISCONNECT );

            /* Suppression de la mémoire allouées dynamiquement pour les contrôles */
            l_result |= mk_hid_deleteControl ( l_report->addr );

            /* Désallocation du contrôle */
            l_result |= mk_pool_freeSafe ( l_report->pool, ( T_mkAddr ) l_report->addr );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désallocation du report */
         l_result |= mk_pool_freeSafe ( g_mkHIDPool.reportPool, ( T_mkAddr ) l_report );

         /* Actualisation de la valeur du report courant */
         l_report = l_nextReport;
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



