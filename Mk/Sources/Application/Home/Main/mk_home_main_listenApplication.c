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
* @file mk_home_main_listenApplication.c
* @brief Définition de la fonction mk_home_main_listenApplication.
* @date 5 nov. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_main_refresBackgroundManager ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Exécution des fonctions de rafraichissement du manager */
   mk_screen_setRefresh ( &p_home->view.manager.background, K_MK_FIELD_REFRESH_ENABLED );
   mk_buttonImage_setRefresh ( &p_home->view.manager.status.button, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setGridRefresh ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setGridRefresh ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setTextRefresh ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setTextRefresh ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_REFRESH_ENABLED );
   for ( l_counter = 0 ; l_counter < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_counter++ )
   {
      mk_buttonImage_setRefresh ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_FIELD_REFRESH_ENABLED );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_main_handleApplicationInputs ( T_mkHomeApplication* p_home, T_mkApplication* p_application, T_mkCtrlEvent p_evtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une application a été fermée ou désinstallée */
   if ( ( p_evtCtrl == K_MK_EVENT_CLOSE ) || ( p_evtCtrl == K_MK_EVENT_DELETE ) )
   {
      /* Réinitialisation des index du manager */
      p_home->view.manager.index = 0;
      p_home->view.manager.current = ( T_mkHomeManagerApplicationButton* ) &p_home->view.manager.applicationList.app [ 0 ];

      /* Réinitialisation des index de la barre applicative */
      p_home->view.main.applicationList.appIndex = 0;
      p_home->view.main.applicationList.shiftIndex = 0;

      /* Chargement des ressources */
      ( void ) mk_home_loadRessources ( p_home );

      /* Attention lors de la réception d'un message main, c'est l'instance de l'application principale qui est renvoyée. */
      /* Si l'application fermée était l'application courante, le gestionnaire d'application a reconfiguré le pointeur d'application avec l'application principale. */
      /* Si le manager d'application n'est pas affiché, le rafraichissement de la nouvelle application sera géré lors de la désactivation du manager. */
      if ( ( mk_application_getCurrent ( ) == mk_application_getMain ( ) ) &&
           ( p_home->view.manager.container->first->visibility == K_MK_FIELD_INVISIBLE ) )
      {
         /* On affiche la vue principale */
         mk_container_setVisibility ( p_home->view.manager.container, K_MK_FIELD_INVISIBLE );
         mk_container_setActivity ( p_home->view.manager.container, K_MK_FIELD_INACTIF );
         mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_VISIBLE );
         mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_ACTIF );
         mk_home_main_setVisibility ( p_home );

         /* Réactivation du rafraichissement de l'arrière plan */
         mk_buttonImage_setRefresh ( &p_home->view.main.background, K_MK_FIELD_REFRESH_ENABLED );

         /* Réactivation des layers */
         mk_container_setVisibility ( p_home->view.layer.container, K_MK_FIELD_VISIBLE );

         /* On recharge les attributs du dispatcher avec les attributs de l'application */
         l_result |= mk_application_loadDispatcherInputs ( p_home->application );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si une application a été détruite */
      if ( p_evtCtrl == K_MK_EVENT_DELETE )
      {
         /* Suite à la destruction d'une application, il est nécessaire de rafraichir les statistiques */
         /* mémoire (SDRAM, SRAM). */

         /* Si le manager est actif */
         if ( p_home->view.manager.background.field.visibility == K_MK_FIELD_VISIBLE )
         {
            /* Rafraichissement du manager */
            mk_home_main_refresBackgroundManager ( p_home );
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

   /* Sinon si une application a été lancée */
   else if ( p_evtCtrl == K_MK_EVENT_LAUNCH )
   {
      /* Si l'application lancée n'est pas une application d'arrière plan */
      if ( ( p_application->descriptor.type & K_MK_APPLICATION_TYPE_DAEMON ) != K_MK_APPLICATION_TYPE_DAEMON )
      {
         /* Si l'application n'est pas l'application 'Home' */
         if ( p_application != p_home->application )
         {
            /* Désactivation de la visibilité de l'application home */
            mk_container_setVisibility ( p_home->view.layer.container, K_MK_FIELD_INVISIBLE );
            mk_container_setActivity ( p_home->view.layer.container, K_MK_FIELD_INACTIF );
            mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_INVISIBLE );
            mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_INACTIF );
            mk_container_setVisibility ( p_home->view.manager.container, K_MK_FIELD_INVISIBLE );
            mk_container_setActivity ( p_home->view.manager.container, K_MK_FIELD_INACTIF );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* On recharge les attributs du dispatcher avec les attributs de l'application */
         l_result = mk_application_loadDispatcherInputs ( p_application );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si une application a été redémarrée */
   else if ( p_evtCtrl == K_MK_EVENT_RESUME )
   {
      /* Si l'application redémarrée n'est pas une application d'arrière plan */
      if ( ( p_application->descriptor.type & K_MK_APPLICATION_TYPE_DAEMON ) != K_MK_APPLICATION_TYPE_DAEMON )
      {
         /* Si l'application redémarrée est l'application 'Home' */
         if ( p_application == p_home->application )
         {
            /* Chargement des ressources */
            ( void ) mk_home_loadRessources ( p_home );

            /* Affichage de la vue principale */
            mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_VISIBLE );
            mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_ACTIF );
            mk_home_main_setVisibility ( p_home );
            mk_buttonImage_setRefresh ( &p_home->view.main.background, K_MK_FIELD_REFRESH_ENABLED );

            /* Réactivation des layers de l'application home */
            mk_container_setVisibility ( p_home->view.layer.container, K_MK_FIELD_VISIBLE );
            mk_container_setActivity ( p_home->view.layer.container, K_MK_FIELD_INACTIF );
         }

         /* Sinon */
         else
         {
            /* Désactivation des layers de l'application home */
            mk_container_setVisibility ( p_home->view.layer.container, K_MK_FIELD_INVISIBLE );
            mk_container_setActivity ( p_home->view.layer.container, K_MK_FIELD_INACTIF );
         }

         /* Désactivation de l'affichage du manager */
         mk_container_setVisibility ( p_home->view.manager.container, K_MK_FIELD_INVISIBLE );
         mk_container_setActivity ( p_home->view.manager.container, K_MK_FIELD_INACTIF );

         /* On recharge les attributs du dispatcher avec les attributs de l'application */
         l_result = mk_application_loadDispatcherInputs ( p_application );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si une application a été suspendue */
   else if ( p_evtCtrl == K_MK_EVENT_SUSPEND )
   {
      /* Activation de l'affichage du manager */
      mk_container_setVisibility ( p_home->view.manager.container, K_MK_FIELD_VISIBLE );
      mk_container_setActivity ( p_home->view.manager.container, K_MK_FIELD_ACTIF );
      mk_home_manager_setVisibility ( p_home );
      mk_home_main_refresBackgroundManager ( p_home );

      /* Si l'application suspendue est l'application 'Home' */
      if ( p_application == p_home->application )
      {
         /* Désactivation de l'affichage la vue principale */
         mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_INVISIBLE );
         mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_INACTIF );
      }

      /* Sinon */
      else
      {
         /* Réactivation des layers de l'application home */
         mk_container_setVisibility ( p_home->view.layer.container, K_MK_FIELD_VISIBLE );
         mk_container_setActivity ( p_home->view.layer.container, K_MK_FIELD_INACTIF );
      }

      /* On recharge les attributs du dispatcher avec les attributs de l'application */
      l_result = mk_application_loadDispatcherInputs ( p_home->application );
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

static T_mkCode mk_home_main_handleApplicationKeyboardInputs ( T_mkHomeApplication* p_home, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application courante */
   T_mkApplication* l_currentApplication = mk_application_getCurrent ( );

   /* Si une touche a été appuyée */
   if ( p_evtCtrl == K_MK_EVENT_KEY_DOWN )
   {
      /* Si le bouton GUI est appuyée */
      if ( p_ctrlId == K_MK_KEYBOARD_LEFTGUI )
      {
         /* Transmission d'un événement à l'application en cours d'exécution */
         l_result |= mk_application_post ( g_mkDisplay.application.current, K_MK_EVENT_SUSPEND );
      }

      /* Sinon si les boutons ALT+F4 sont appuyés */
      else if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTALT | K_MK_KEYBOARD_F4 ) )
      {
         /* Si l'application à fermer est différente de l'application principale */
         if ( l_currentApplication != mk_application_getMain ( ) )
         {
            /* Fermeture de l'application courante */
            l_result = mk_application_close ( l_currentApplication, K_MK_NULL );
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

   /* Si une touche a été relachée */
   else if ( p_evtCtrl == K_MK_EVENT_KEY_UP )
   {
      /* Si le bouton GUI est relaché */
      if ( p_ctrlId == K_MK_KEYBOARD_LEFTGUI )
      {
         /* Si l'application sélectionnée dans le manager n'est pas une application d'arrière plan */
         if ( ( p_home->view.manager.current->application->descriptor.type & K_MK_APPLICATION_TYPE_DAEMON ) != K_MK_APPLICATION_TYPE_DAEMON )
         {
            /* Modification de l'application courante par l'application sélectionnée */
            g_mkDisplay.application.current = p_home->view.manager.current->application;
         }

         /* Sinon */
         else
         {
            /* L'application courante n'est pas modifiée */
            /* Ne rien faire */
         }

         /* Transmission d'un événement à la nouvelle application sélectionnée */
         l_result = mk_application_post ( g_mkDisplay.application.current, K_MK_EVENT_RESUME );
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

T_mkCode mk_home_main_listenApplication ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application 'Home' */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si un événement système s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_SYSTEM )
   {
      /* Ne rien faire */
   }

   /* Sinon si un événement en relation avec les applications s'est produit */
   else if ( p_appCtrlId == K_MK_CONTROL_APPLICATION )
   {
      /* Gestion de l'événement relatif à la souris */
      l_result = mk_home_main_handleApplicationInputs ( l_home, p_appCtrl, p_evtCtrl );
   }

   /* Si un événement en relation avec le clavier s'est produit */
   else if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion de l'événement relatif au clavier */
      l_result = mk_home_main_handleApplicationKeyboardInputs ( l_home, p_evtCtrl, p_ctrlId );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression warning */
   ( void ) p_field;

   /* Retour */
   return ( l_result );
}


