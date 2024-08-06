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
* @file mk_home_main_setVisibility.c
* @brief Définition de la fonction mk_home_main_setVisibility.
* @date 23 sept. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_home_main_setVisibility ( T_mkHomeApplication* p_home )
{
   /* Déclaration des compteurs */
   /* La valeur de rCounter est à 1 pour ne pas prendre en compte l'application principale. */
   uint32_t l_counter = 0, l_rCounter = 1;

   /* Déclaration des variables de travail */
   uint32_t l_dx = 0, l_x = 0, l_index = 0;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = mk_application_getFirst ( );

   /* Bypass de l'application principale, celle-ci ne doit pas être affichée */
   l_application = l_application->next;

   /* Parcours de la liste d'applications */
   while ( ( l_application != K_MK_NULL ) &&
           ( l_counter < ( uint32_t ) ( p_home->view.main.applicationList.shiftIndex + K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER ) ) )
   {
      /* Si l'application doit être affichée */
      if ( l_counter >= p_home->view.main.applicationList.shiftIndex )
      {
         /* Détermination de l'index du bouton image */
         l_index = ( uint32_t ) ( l_counter - p_home->view.main.applicationList.shiftIndex );

         /* Configuration de l'adresse de l'application */
         p_home->view.main.applicationList.app [ l_index ].application = l_application;

         /* Si l'application possède un logo */
         if ( l_application->metadata.iconPath != K_MK_NULL )
         {
            /* Configuration de l'image du bouton */
            mk_buttonImage_setImage ( &p_home->view.main.applicationList.app [ l_index ].button, &p_home->view.ressources.applicationLogo [ l_application->layer.id ] );
         }

         /* Sinon */
         else
         {
            /* L'application ne possède pas de logo */
            mk_buttonImage_setImage ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_NULL );
         }

         /* Configuration de la visibilité du bouton image */
         mk_buttonImage_setVisibility ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_FIELD_VISIBLE );
         mk_buttonImage_setActivity ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_FIELD_ACTIF );

         /* Si l'application possède un nom */
         if ( l_application->metadata.name != K_MK_NULL )
         {
            /* Configuration du nom de l'application */
            mk_buttonImage_setTextBuffer ( &p_home->view.main.applicationList.app [ l_index ].button, l_application->metadata.name );
         }

         /* Sinon */
         else
         {
            /* L'application ne possède pas de nom */
            mk_buttonImage_setTextBuffer ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_NULL );
         }

         /* Configuration de la position du bouton image */
         mk_buttonImage_setPosition ( &p_home->view.main.applicationList.app [ l_index ].button, ( real32_t ) ( l_x + l_dx ),
                                      ( real32_t ) ( p_home->view.main.applicationList.app [ l_index ].button.field.position.y ) );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation des compteurs */
      l_counter++;
      l_rCounter++;

      /* Passage à la prochaine application */
      l_application = l_application->next;
   }

   /* Détermination de l'index du prochain bouton */
   l_index = ( uint32_t ) ( l_counter - p_home->view.main.applicationList.shiftIndex );

   /* Calcul de l'origine des boutons applicatifs */
   /* On centre les boutons sur l'axe horizontal de l'écran */
   l_x = K_MK_HOME_MAINVIEW_APPLICATIONLIST_AREA_TOPLEFT_X +
         ( ( ( K_MK_HOME_MAINVIEW_APPLICATIONLIST_AREA_BOTTOMRIGHT_X - K_MK_HOME_MAINVIEW_APPLICATIONLIST_AREA_TOPLEFT_X ) -
         ( l_index * K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_WIDTH ) ) >> 1 );

   /* Configuration de la position des boutons applicatifs */
   for ( l_counter = 0 ; l_counter < l_index ; l_counter++ )
   {
      mk_buttonImage_setPosition ( &p_home->view.main.applicationList.app [ l_counter ].button, ( real32_t ) ( l_x + l_dx ),
                                   ( real32_t ) ( p_home->view.main.applicationList.app [ l_counter ].button.field.position.y ) );
      l_dx = ( uint32_t ) ( l_dx + K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_WIDTH );
   }

   /* Configuration de la visibilité des boutons non utilisés */
   for ( ; l_index < K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_index++ )
   {
      mk_buttonImage_setVisibility ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_FIELD_INVISIBLE );
      mk_buttonImage_setActivity ( &p_home->view.main.applicationList.app [ l_index ].button, K_MK_FIELD_INACTIF );
   }

   /* Retour */
   return;
}




