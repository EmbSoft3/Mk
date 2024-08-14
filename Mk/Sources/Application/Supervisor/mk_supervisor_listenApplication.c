/**
*
* @copyright Copyright (C) 2023 RENARD Mathieu. All rights reserved.
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
* @file mk_supervisor_listenApplication.c
* @brief Définition de la fonction mk_supervisor_listenApplication.
* @date 5 nov. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_handleApplicationKeyboardInputs ( T_mkSupervisor* p_supervisor, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_currentApplication = K_MK_NULL;

   /* Si une touche a été appuyée */
   if ( p_evtCtrl == K_MK_EVENT_KEY_DOWN )
   {
      /* Si la console doit être masquée ou démasquée (ALT+S) */
      /* Cf. document HID Usage Tables Version 1.12 §10 pour la correspondance des codes */
      if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTALT | 0x16 ) )
      {
         /* Si la console est visible */
         if ( p_supervisor->console.foreground.prompt.field.visibility == K_MK_FIELD_VISIBLE )
         {
            /* Activation de l'exécution des fonctions d'écoutes et de peintures de tous */
            /* les containers privilégiés et non privilégiés */
            mk_display_enableFactory ( );

            /* Désactivation de l'activité et de la visibilité du container critique */
            mk_container_setVisibility ( g_mkDisplay.criticalContainer, K_MK_FIELD_INVISIBLE );
            mk_container_setActivity ( g_mkDisplay.criticalContainer, K_MK_FIELD_INACTIF );

            /* Activation du focus */
            mk_field_setFocus ( &p_supervisor->console.foreground.prompt.field, K_MK_FIELD_STATE_IDLE );

            /* Récupération de l'adresse de l'application principale */
            l_currentApplication = mk_application_getMain ( );

            /* Transmission d'un événement à l'application en cours d'exécution */
            l_result = mk_application_post ( l_currentApplication, K_MK_EVENT_RESUME );
         }

         /* Sinon */
         else
         {
            /* Désactivation de l'exécution des fonctions d'écoutes et de peintures de tous */
            /* les containers privilégiés et non privilégiés */
            mk_display_disableFactory ( );

            /* Activation de l'activité et de la visibilité du container critique */
            mk_container_setVisibility ( g_mkDisplay.criticalContainer, K_MK_FIELD_VISIBLE );
            mk_container_setActivity ( g_mkDisplay.criticalContainer, K_MK_FIELD_ACTIF );

            /* Activation du focus */
            mk_field_setFocus ( &p_supervisor->console.foreground.prompt.field, K_MK_FIELD_STATE_FOCUS );

            /* Configuration des attributs de l'application */
            l_result = mk_application_loadDispatcherInputs ( &p_supervisor->application );

            /* Déclenchement d'un rafraichissement graphique */
            mk_console_setRefresh ( &p_supervisor->console, K_MK_FIELD_REFRESH_ENABLED );
         }
      }

      /* Sinon si l'affiche du framerate ou de la charge CPU doit être activé ou désactivé sur le premier plan (ALT+F) */
      /* Cf. document HID Usage Tables Version 1.12 §10 pour la correspondance des codes */
      else if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTALT | 0x09 ) )
      {
         /* Commutation de la valeur de la variable foregroundEnabled */
         if ( p_supervisor->load.foregroundEnabled == K_MK_TRUE )
         {
            /* Désactivation de l'affichage */
            p_supervisor->load.foregroundEnabled = K_MK_FALSE;
         }

         /* Sinon */
         else
         {
            /* Activation de l'affichage */
            p_supervisor->load.foregroundEnabled = K_MK_TRUE;
         }
      }

      /* Sinon si l'affiche du framerate ou de la charge CPU doit être activé ou désactivé sur le premier plan (ALT+B) */
      /* Cf. document HID Usage Tables Version 1.12 §10 pour la correspondance des codes */
      else if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTALT | 0x05 ) )
      {
         /* Commutation de la valeur de la variable foregroundEnabled */
         if ( p_supervisor->load.backgroundEnabled == K_MK_TRUE )
         {
            /* Désactivation de l'affichage */
            p_supervisor->load.backgroundEnabled = K_MK_FALSE;
         }

         /* Sinon */
         else
         {
            /* Activation de l'affichage */
            p_supervisor->load.backgroundEnabled = K_MK_TRUE;
         }
      }

      /* Sinon si un screenshot doit être réalisé */
      else if ( ( p_ctrlId & 0xFF ) == K_MK_KEYBOARD_PRINTSCREEN )
      {
         /* Enregistrement d'un screenhot sur le système de stockage */
         l_result = mk_display_screenshot ( );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse du superviseur */
   T_mkSupervisor* l_supervisor = ( T_mkSupervisor* ) mk_application_getArg ( l_application );

   /* Si un événement en relation avec le clavier s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion des entrées relatives au clavier */
      l_result = mk_supervisor_handleApplicationKeyboardInputs ( l_supervisor, p_evtCtrl, p_ctrlId );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression warning */
   ( void ) p_appCtrl; ( void ) p_appCtrlId; ( void ) p_field;

   /* Retour */
   return ( l_result );
}

