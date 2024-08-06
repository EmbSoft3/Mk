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
* @file mk_home_manager_listenScreen.c
* @brief Définition de la fonction mk_home_manager_listenScreen.
* @date 20 août 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_manager_refreshApplicationButton ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Rafraichissement des boutons applicatifs */
   mk_figure_setRefresh ( &p_home->view.manager.backgroundFigure, K_MK_FIELD_REFRESH_ENABLED );
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

static void mk_home_manager_refreshBackgroundManager ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Rafraichissement de l'arrière plan du manager */
   mk_screen_setRefresh ( &p_home->view.manager.background, K_MK_FIELD_REFRESH_ENABLED );
   mk_buttonImage_setRefresh ( &p_home->view.manager.status.button, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setTextRefresh ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setTextRefresh ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setGridRefresh ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_REFRESH_ENABLED );
   mk_graph2D_setGridRefresh ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_REFRESH_ENABLED );
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

static T_mkCode mk_home_handleManagerKeyboardInputs ( T_mkHomeApplication* p_home, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_numberOfRunningApplication = 0;

   /* Si une touche a été appuyée */
   if ( ( p_evtCtrl == K_MK_EVENT_KEY_DOWN ) || ( p_evtCtrl == K_MK_EVENT_KEY_HOLD ) )
   {
      /* Si la fléche du haut est appuyée */
      if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTGUI | K_MK_KEYBOARD_UPARROW ) )
      {
         /* Si le pointeur d'application ne pointe pas sur la première application */
         if ( p_home->view.manager.index != 0 )
         {
            /* Si le pointeur d'application peut être décrémenté */
            if ( ( p_home->view.manager.current != &p_home->view.manager.applicationList.app [ 0 ] ) &&
                 ( p_home->view.manager.index < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ) )
            {
               /* Actualisation du pointeur d'application */
               p_home->view.manager.current--;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Décrémentation de l'index et du pointeur d'application */
            p_home->view.manager.index--;

            /* Rafraichissement de l'ensemble des boutons applicatifs */
            mk_home_manager_refreshApplicationButton ( p_home );

            /* Activation du rafraichissement graphique */
            mk_home_manager_setVisibility ( p_home );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si la flêche du bas est appuyée */
      else if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTGUI | K_MK_KEYBOARD_DOWNARROW ) )
      {
         /* Récupération du nombre d'application en cours d'exécution */
         l_numberOfRunningApplication = mk_application_getNumberOfRunningApps ( );

         /* Si le pointeur d'application ne pointe pas sur la dernière application */
         if ( ( p_home->view.manager.index + 1 ) < l_numberOfRunningApplication )
         {
            /* Si le pointeur d'application peut être incrémenté */
            if ( p_home->view.manager.current !=
                 &p_home->view.manager.applicationList.app [ K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER - 1 ] )
            {
               /* Actualisation du pointeur d'application */
               p_home->view.manager.current++;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Incrémentation de l'index et du pointeur d'application */
            p_home->view.manager.index++;

            /* Rafraichissement de l'ensemble des boutons applicatifs */
            mk_home_manager_refreshApplicationButton ( p_home );

            /* Configuration de la visibilité des champs du manager */
            mk_home_manager_setVisibility ( p_home );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le bouton 'Suppr' est appuyée */
      else if ( p_ctrlId == ( K_MK_KEYBOARD_LEFTGUI | K_MK_KEYBOARD_DELETE ) )
      {
         /* Si l'application à fermer est différente de l'application principale */
         if ( p_home->view.manager.current->application != mk_application_getMain ( ) )
         {
            /* Fermeture de l'application courante */
            l_result = mk_application_close ( p_home->view.manager.current->application, K_MK_NULL );

            /* Récupération du nombre d'application en cours d'exécution */
            l_numberOfRunningApplication = mk_application_getNumberOfRunningApps ( );

            /* Si le pointeur d'application pointe sur la dernière application */
            if ( ( p_home->view.manager.index == l_numberOfRunningApplication ) &&
                 ( p_home->view.manager.index < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ) )
            {
               /* Actualisation du pointeur d'application */
               p_home->view.manager.current--;

               /* Décrémentation de l'index et du pointeur d'application */
               p_home->view.manager.index--;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Activation du rafraichissement des champs du manager */
            mk_home_manager_refreshBackgroundManager ( p_home );

            /* Configuration de la visibilité des champs du gestionnaire */
            mk_home_manager_setVisibility ( p_home );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_home_manager_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application home */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si un événement système s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_SYSTEM )
   {
      /* Ne rien faire */
   }

   /* Sinon si un événement en relation avec le clavier s'est produit */
   else if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion de l'événement relatif au clavier */
      l_result = mk_home_handleManagerKeyboardInputs ( l_home, p_evtCtrl, p_ctrlId );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression warning */
   ( void ) p_field; ( void ) p_appCtrl;

   /* Retour */
   return ( l_result );
}



