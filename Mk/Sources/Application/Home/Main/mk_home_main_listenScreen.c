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
* @file mk_home_main_listenScreen.c
* @brief Définition de la fonction mk_home_main_listenScreen.
* @date 17 sept. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_main_shiftWindowRight ( T_mkHomeApplication* p_home )
{
   /* Si l'index peut être actualisé */
   /* On retranche la valeur 1 car on ne prend pas en compte l'application principale. */
   if ( ( p_home->view.main.applicationList.shiftIndex + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ) < ( mk_application_getNumberOfInstalledApps ( ) - 1 ) )
   {
      /* Mise à jour de l'index de décalage */
      p_home->view.main.applicationList.shiftIndex = ( uint32_t ) ( p_home->view.main.applicationList.shiftIndex + 1 );

      /* Configuration de la visibilité des boutons de la liste d'applications */
      mk_home_main_setVisibility ( p_home );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_main_shiftWindowLeft ( T_mkHomeApplication* p_home )
{
   /* Si l'index peut être actualisé */
   if ( p_home->view.main.applicationList.shiftIndex != 0 )
   {
      /* Mise à jour de l'index de décalage */
      p_home->view.main.applicationList.shiftIndex = ( uint32_t ) ( p_home->view.main.applicationList.shiftIndex - 1 );

      /* Configuration de la visibilité des boutons de la liste d'applications */
      mk_home_main_setVisibility ( p_home );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_main_handleMouseInputs ( T_mkHomeApplication* p_home, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de la souris */
   T_mkMouse* l_mouse = ( T_mkMouse* ) p_appCtrl;

   /* Si la molette de la souris est utilisée */
   if ( p_evtCtrl == K_MK_EVENT_VSCROLL )
   {
      /* Avec une souris, le focus est obtenu en positionnant le curseur sur le bouton image */
      /* Il n'est pas obtenu en utilisant la molette. */

      /* Si mouvement de la molette vers le haut */
      if ( l_mouse->wheel.delta < 0 )
      {
         /* Décalage de la fenêtre d'un pas vers la droite */
         mk_home_main_shiftWindowRight ( p_home );
      }

      /* Sinon si mouvement de la molette vers le bas */
      else if ( l_mouse->wheel.delta > 0 )
      {
         /* Décalage de la fenêtre d'un pas vers la gauche */
         mk_home_main_shiftWindowLeft ( p_home );
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

static T_mkCode mk_home_main_handleKeyboardInputs ( T_mkHomeApplication* p_home, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si une touche a été appuyée */
   if ( ( p_evtCtrl == K_MK_EVENT_KEY_DOWN ) || ( p_evtCtrl == K_MK_EVENT_KEY_HOLD ) )
   {
      /* Si la fléche de droite a été appuyée */
      if ( p_ctrlId == K_MK_KEYBOARD_RIGHTARROW )
      {
         /* Si un décalage du focus doit être effectué */
         if ( p_home->view.main.applicationList.appIndex == ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER - 1 ) )
         {
            /* Décalage de la fenêtre d'un pas vers la droite */
            mk_home_main_shiftWindowRight ( p_home );
         }

         /* Sinon */
         else
         {
            /* Si l'index peut être actualisé */
            /* On retranche la valeur 2 car on ne prend pas en compte l'application principale (la première de la liste). */
            if ( p_home->view.main.applicationList.appIndex < ( mk_application_getNumberOfInstalledApps ( ) - 2 ) )
            {
               /* Configuration du style de la police de caractères */
               /* Ancien bouton avec le focus */
               mk_buttonImage_setTextStyle ( &p_home->view.main.applicationList.app[ p_home->view.main.applicationList.appIndex ].button,
                                             &p_home->view.main.applicationList.nameStyle );

               /* Configuration du style de la police de caractères */
               /* Nouveau bouton qui a le focus */
               mk_buttonImage_setTextStyle ( &p_home->view.main.applicationList.app[ p_home->view.main.applicationList.appIndex + 1 ].button,
                                             &p_home->view.main.applicationList.focusStyle );

               /* Mise à jour de l'index de décalage */
               p_home->view.main.applicationList.appIndex = ( uint32_t ) ( p_home->view.main.applicationList.appIndex + 1 );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }
      }

      /* Sinon si la fléche de gauche est appuyée */
      else if ( p_ctrlId == K_MK_KEYBOARD_LEFTARROW )
      {
         /* Si un décalage peut être effectué */
         if ( ( p_home->view.main.applicationList.shiftIndex != 0 ) &&
              ( p_home->view.main.applicationList.appIndex == 0 ) )
         {
            /* Décalage de la fenêtre d'un pas vers la gauche */
            mk_home_main_shiftWindowLeft ( p_home );
         }

         /* Sinon */
         else
         {
            /* Si l'index peut être actualisé */
            if ( p_home->view.main.applicationList.appIndex != 0 )
            {
               /* Configuration du style de la police de caractères */
               /* Ancien bouton avec le focus */
               mk_buttonImage_setTextStyle ( &p_home->view.main.applicationList.app[ p_home->view.main.applicationList.appIndex ].button,
                                             &p_home->view.main.applicationList.nameStyle );

               /* Configuration du style de la police de caractères */
               /* Nouveau bouton qui a le focus */
               mk_buttonImage_setTextStyle ( &p_home->view.main.applicationList.app[ p_home->view.main.applicationList.appIndex - 1 ].button,
                                             &p_home->view.main.applicationList.focusStyle );

               /* Mise à jour de l'index */
               p_home->view.main.applicationList.appIndex = ( uint32_t ) ( p_home->view.main.applicationList.appIndex - 1 );
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

T_mkCode mk_home_main_listenScreen ( T_mkContainer* p_container, T_mkField* p_field, T_mkCtrlId p_appCtrlId, T_mkAddr p_appCtrl, T_mkCtrlEvent p_evtCtrl, uint32_t p_ctrlId )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application 'Home' */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si un événement en relation avec la souris s'est produit */
   if ( p_appCtrlId == K_MK_CONTROL_MOUSE )
   {
      /* Gestion de l'événement relatif à la souris */
      l_result = mk_home_main_handleMouseInputs ( l_home, p_appCtrl, p_evtCtrl );
   }

   /* Sinon si un événement en relation avec le clavier s'est produit */
   else if ( p_appCtrlId == K_MK_CONTROL_KEYBOARD )
   {
      /* Gestion de l'événement relatif au clavier */
      l_result = mk_home_main_handleKeyboardInputs ( l_home, p_evtCtrl, p_ctrlId );
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


