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
* @file mk_home_main_listenApplicationButton.c
* @brief Définition de la fonction mk_home_main_listenApplicationButton.
* @date 30 sept. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_main_handleApplication ( T_mkHomeApplication* p_home, T_mkHomeMainApplicationButton* p_applicationButton )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une application a été configurée dans le bouton applicatif */
   if ( p_applicationButton->application != K_MK_NULL )
   {
      /* Si l'application n'est pas une application d'arrière plan */
      if ( ( p_applicationButton->application->descriptor.type & K_MK_APPLICATION_TYPE_DAEMON ) != K_MK_APPLICATION_TYPE_DAEMON )
      {
         /* Désactivation des layers de l'application home */
         mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_INVISIBLE );
         mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_INACTIF );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si l'application n'a pas déjà été lancée */
      if ( p_applicationButton->application->state == K_MK_APPLICATION_STATE_INSTALLED )
      {
         /* Lancement de l'application */
         l_result = mk_application_launch ( p_applicationButton->application, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Modification de l'application courante */
         g_mkDisplay.application.current = p_applicationButton->application;

         /* On bascule sur l'application demandée */
         l_result = mk_application_post ( p_applicationButton->application, K_MK_EVENT_RESUME );
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

static T_mkCode mk_home_main_handleApplicationButtonMouseInputs ( T_mkContainer* p_container, T_mkButtonImage* p_buttonImage, T_mkHomeMainApplicationButton* p_applicationButton, T_mkCtrlEvent p_evtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application home */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si le curseur de la souris est entré dans la champ */
   if ( p_evtCtrl == K_MK_EVENT_ENTER )
   {
      /* Configuration du style de la police de caractères du bouton applicatif */
      mk_buttonImage_setTextStyle ( p_buttonImage, &l_home->view.main.applicationList.focusStyle );
   }

   /* Sinon si le curseur de la souris est sorti du champ */
   else if ( p_evtCtrl == K_MK_EVENT_EXIT )
   {
      /* Configuration du style de la police de caractères du bouton applicatif */
      mk_buttonImage_setTextStyle ( p_buttonImage, &l_home->view.main.applicationList.nameStyle );
   }

   /* Sinon si l'utilisateur a réalisé un clic à l'intérieur du bouton */
   else if ( p_evtCtrl == K_MK_EVENT_XCLICK )
   {
      /* Démarrage de l'application associée au bouton */
      l_result = mk_home_main_handleApplication ( l_home, p_applicationButton );
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

static T_mkCode mk_home_main_handleApplicationButtonKeyboardInputs ( T_mkContainer* p_container, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application home */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si la touche entrée a été appuyée */
   if ( p_ctrlId == K_MK_KEYBOARD_ENTER )
   {
      /* Démarrage de l'application associée au bouton */
      l_result = mk_home_main_handleApplication ( l_home, &l_home->view.main.applicationList.app [ l_home->view.main.applicationList.appIndex ] );
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

T_mkCode mk_home_main_listenApplicationButton ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse du bouton image */
   T_mkButtonImage* l_buttonImage = ( T_mkButtonImage* ) p_field->child;

   /* Récupération de l'adresse du bouton applicatif */
   T_mkHomeMainApplicationButton* l_applicationButton = ( T_mkHomeMainApplicationButton* ) l_buttonImage->child;

   /* Si un événement en relation avec la souris s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_MOUSE )
   {
      /* Gestion de l'événement relatif à la souris */
      l_result = mk_home_main_handleApplicationButtonMouseInputs ( p_container, l_buttonImage, l_applicationButton, p_evtCtrl );
   }

   /* Sinon si un événement en relation avec le clavier s'est produit */
   else if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion de l'événement relatif au clavier */
      l_result = mk_home_main_handleApplicationButtonKeyboardInputs ( p_container, p_ctrlId );
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



