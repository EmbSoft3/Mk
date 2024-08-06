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
* @file mk_home_manager_paintButtonImage.c
* @brief Définition de la fonction mk_home_manager_paintButtonImage.
* @date 5 nov. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_manager_paintButtonImageField ( T_mkContainer* p_container, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs de travail */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Déclaration d'une variable stockant une couleur */
   uint32_t l_color = 0;

   /* Récupération de l'adresse du bouton image */
   T_mkButtonImage* l_buttonImage = ( T_mkButtonImage* ) p_field->child;

   /* Récupération de l'adresse du bouton applicatif */
   T_mkHomeManagerApplicationButton* l_applicationButton = ( T_mkHomeManagerApplicationButton* ) l_buttonImage->child;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application 'Home' */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Configuration du vecteur */
   mk_vect2d_setCoord ( &l_bottomRight, p_field->position.x + ( real32_t ) p_field->dimension.width - 1, p_field->position.y + ( real32_t ) p_field->dimension.height - 1 );

   /* Si une bordure doit être dessinée */
   if ( l_buttonImage->borderVisibility == K_MK_GRAPHICS_VISIBLE )
   {
      /* Récupération de la valeur de la couleur */
      l_color = mk_color_getARGB32 ( &l_buttonImage->borderColor );

      /* Si l'application est l'application courante */
      if ( l_home->view.manager.current == l_applicationButton )
      {
         /* Dessin de la bordure */
         l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, p_field->position, l_bottomRight, K_MK_COLOR_ARGB_SILVER );
      }

      /* Sinon */
      else
      {
         /* Dessin de la bordure */
         l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, p_field->position, l_bottomRight, l_color );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs */
      /* TopLeft */
      mk_vect2d_setCoord ( &l_topLeft, p_field->position.x + 15.0f,
                                       p_field->position.y + ( real32_t ) ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT - 1 ) / 2 );

      /* BottomRight */
      mk_vect2d_setCoord ( &l_bottomRight, l_topLeft.x + K_MK_APPLICATION_LOGO_WIDTH - 1,
                                           l_topLeft.y + K_MK_APPLICATION_LOGO_HEIGHT - 1 );

      /* Si une image a été configurée */
      if ( ( l_buttonImage->bitmap != K_MK_NULL ) && ( l_buttonImage->bitmap->file != K_MK_NULL ) && ( l_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
      {
         /* Dessin de l'image */
         l_result = mk_graphics_invcopy ( l_buttonImage->bitmap->baseAddr, l_topLeft, K_MK_GRAPHICS_ADDR_TO_FRAME, l_buttonImage->field.layer, l_buttonImage->bitmap->width, l_buttonImage->bitmap->height );
      }

      /* Sinon, on affiche un rectangle si l'image n'a pas été chargée */
      else
      {
         /* Dessin d'un rectangle */
         l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, l_color );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs */
      /* TopLeft */
      mk_vect2d_setCoord ( &l_topLeft,
                           p_field->position.x + 15.0f + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH + 25.0f,
                           p_field->position.y + ( real32_t ) ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT - 1 ) / 2 );
      /* BottomRight */
      mk_vect2d_setCoord ( &l_bottomRight,
                           4 * ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X ) / 5,
                           l_topLeft.y + 30.0f );

      /* Si les pointeurs d'application ont été configurés */
      if ( ( l_applicationButton->application != K_MK_NULL ) &&
           ( l_applicationButton->application->metadata.description != K_MK_NULL ) )
      {
         /* Dessin du nom de l'application */
         /*l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, l_topLeft, l_bottomRight, K_MK_COLOR_ARGB_RED );*/
         l_result = mk_graphics_drawString ( p_field->layer, l_topLeft, l_bottomRight, l_applicationButton->application->metadata.name, l_applicationButton->nameStyle, K_MK_NULL );
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

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs */
      /* TopLeft */
      mk_vect2d_setCoord ( &l_topLeft, l_bottomRight.x + 1, l_topLeft.y );
      /* BottomRight */
      mk_vect2d_setCoord ( &l_bottomRight, ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X - 1 ),
                           l_topLeft.y + 30.0f );

      /* Si les pointeurs d'application ont été configurés */
      if ( l_applicationButton->application != K_MK_NULL )
      {
         /* Debug */
         /*l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, l_topLeft, l_bottomRight, K_MK_COLOR_ARGB_BLUE );*/

         /* Si l'application est de type privilégiée */
         if ( ( l_applicationButton->application != K_MK_NULL ) &&
              ( l_applicationButton->application->descriptor.taskType & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
         {
            /* Dessin des droits de l'application */
            l_result = mk_graphics_drawString ( p_field->layer, l_topLeft, l_bottomRight, ( T_str8 ) "(-p)", l_applicationButton->rightStyle, K_MK_NULL );
         }

         /* Sinon */
         else
         {
            /* Dessin des droits de l'application */
            l_result = mk_graphics_drawString ( p_field->layer, l_topLeft, l_bottomRight, ( T_str8 ) "(-d)", l_applicationButton->rightStyle, K_MK_NULL );
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

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs */
      /* TopLeft */
      mk_vect2d_setCoord ( &l_topLeft, p_field->position.x + 15.0f + K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_WITDH + 25.0f,
                                       30.0f + p_field->position.y + ( real32_t ) ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_ICON_HEIGHT - 1 ) / 2 );
      /* BottomRight */
      mk_vect2d_setCoord ( &l_bottomRight, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_X, l_topLeft.y + 30 );

      /* Si les pointeurs d'application ont été configurés */
      if ( ( l_applicationButton->application != K_MK_NULL ) &&
           ( l_applicationButton->application->metadata.author != K_MK_NULL ) )
      {
         /* Dessin de l'auteur de l'application */
         /*l_result = mk_graphics_drawRect ( l_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, l_topLeft, l_bottomRight, K_MK_COLOR_ARGB_GREEN );*/
         l_result = mk_graphics_drawString ( p_field->layer, l_topLeft, l_bottomRight, l_applicationButton->application->metadata.author, l_applicationButton->defaultStyle, K_MK_NULL );
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

T_mkCode mk_home_manager_paintButtonImage ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK; 

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Exécution de la fonction de peinture */
      l_result = mk_home_manager_paintButtonImageField ( p_container, p_field );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Désactivation du rafraichissement */
         mk_field_setRefresh ( p_field, K_MK_FIELD_REFRESH_DISABLED );
      }

      /* Sinon */
      else
      {         /* Ne rien faire */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Suppression warning */
   ( void ) p_frameNumber;

   /* Retour */
   return ( l_result );
}

