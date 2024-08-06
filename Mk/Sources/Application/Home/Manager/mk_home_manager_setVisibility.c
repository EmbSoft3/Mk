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
* @file mk_home_manager_setVisibility.c
* @brief Définition de la fonction mk_home_manager_setVisibility.
* @date 2 sept. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_home_manager_setVisibility ( T_mkHomeApplication* p_home )
{
   /* Déclaration des compteurs */
   uint32_t l_counter = 0, l_installedApps = 0;

   /* Déclaration d'une variable de travail */
   uint32_t l_index = 0;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = mk_application_getFirst ( );

   /* Parcours de la liste d'applications */
   while ( ( l_application != K_MK_NULL ) && ( l_index < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ) )
   {
      /* Si l'application courante a été lancée et si l'application doit être affichée */
      if ( ( l_application->state == K_MK_APPLICATION_STATE_RUNNING ) &&
         ( ( ( l_counter - l_installedApps ) + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ) > p_home->view.manager.index ) )
      {
         /* Configuration de l'adresse de l'application */
         p_home->view.manager.applicationList.app [ l_index ].application = l_application;

         /* Si un logo a été spécifié */
         if ( l_application->metadata.iconPath != K_MK_NULL )
         {
            /* Configuration de l'image du bouton */
            mk_buttonImage_setImage ( &p_home->view.manager.applicationList.app[ l_index ].button, &p_home->view.ressources.applicationLogo [ l_application->layer.id ] );
         }

         /* Sinon */
         else
         {
            /* L'application ne possède pas de logo */
            mk_buttonImage_setImage ( &p_home->view.manager.applicationList.app[ l_index ].button, K_MK_NULL );
         }

         /* Configuration de la visibilité du bouton image */
         mk_buttonImage_setVisibility ( &p_home->view.manager.applicationList.app [ l_index ].button, K_MK_FIELD_VISIBLE );

         /* Actualisation de l'index */
         l_index++;
      }

      /* Sinon si l'application est installée */
      else if ( l_application->state == K_MK_APPLICATION_STATE_INSTALLED )
      {
         /* Actualisation du nombre d'applications installées */
         l_installedApps++;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du compteur */
      l_counter++;

      /* Passage à la prochaine application */
      l_application = l_application->next;
   }

   /* Configuration de la visibilité des boutons non utilisés */
   for ( ; l_index < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_index++ )
   {
      mk_buttonImage_setVisibility ( &p_home->view.manager.applicationList.app [ l_index ].button, K_MK_FIELD_INVISIBLE );
      mk_buttonImage_setActivity ( &p_home->view.manager.applicationList.app [ l_index ].button, K_MK_FIELD_INACTIF );
   }

   /* Retour */
   return;
}



