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
* @file mk_home_manager_paintStatus.c
* @brief Définition de la fonction mk_home_manager_paintStatus.
* @date 8 déc. 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_manager_getStr ( T_str8 p_result, uint32_t p_count, uint32_t p_total )
{
   /* Déclaration des variables de travail */
   char8_t strCount [ 8 ];
   char8_t strTotal [ 8 ];

   /* Si la variable 'total' est supérieure ou égale au nombre d'instances disponibles */
   if ( p_total >= p_count )
   {
      /* Conversion des entiers en chaine de caractères */
      ( void ) mk_utils_itoa ( ( uint32_t ) ( p_total - p_count ), ( T_str8 ) strCount, 10, 0 );
      ( void ) mk_utils_itoa ( p_total, ( T_str8 ) strTotal, 10, 0 );

      /* Création de la chaine de caractères à afficher */
      ( void ) mk_utils_strcat ( ( T_str8 ) strCount, ( T_str8 ) strCount, ( T_str8 ) "/" );
      ( void ) mk_utils_strcat ( p_result, ( T_str8 ) strCount, ( T_str8 ) strTotal );
   }

   /* Sinon */
   else
   {
      /* Affichage d'une erreur */
      ( void ) mk_utils_strcat ( p_result, ( T_str8 ) "Err.", ( T_str8 ) "" );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_manager_paintGroupName ( T_mkButtonImage* p_buttonImage, T_str8 p_string, real32_t p_x, real32_t p_y, uint32_t p_color )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs position */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Configuration de position de la bordure haute */
   mk_vect2d_setCoord ( &l_topLeft, p_x + 125.0f, p_y + 18 );
   mk_vect2d_setCoord ( &l_bottomRight, p_x + ( real32_t ) p_buttonImage->field.dimension.width - 15.0f, p_y + 18 );

   /* Dessin de la bordure haute */
   l_result = mk_graphics_drawLine ( p_buttonImage->field.layer, l_topLeft, l_bottomRight, p_color );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs position */
      mk_vect2d_setCoord ( &l_topLeft, p_x + 10.0f, p_y + 5.0f );
      mk_vect2d_setCoord ( &l_bottomRight, p_x + 40.0f, p_y + 25.0f );

      /* Si le groupe possède une image */
      if ( ( p_buttonImage->bitmap != K_MK_NULL ) && ( p_buttonImage->bitmap->file != K_MK_NULL ) && ( p_buttonImage->bitmap->baseAddr != K_MK_NULL ) )
      {
         /* Dessin de l'image du groupe */
         l_result = mk_bmp_draw ( p_buttonImage->bitmap, p_buttonImage->field.layer, l_topLeft );
      }

      /* Sinon */
      else
      {
         /* Dessin d'un rectangle pour combler l'absence d'image */
         l_result = mk_graphics_drawRect ( p_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, p_color );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le groupe possède un texte */
   if ( ( l_result == K_MK_OK ) && ( p_string != K_MK_NULL ) )
   {
      /* Configuration de la position du texte */
      mk_vect2d_setCoord ( &l_topLeft, p_x + 50.0f, p_y + 5.0f );
      mk_vect2d_setCoord ( &l_bottomRight, p_x + ( real32_t ) p_buttonImage->field.dimension.width - 1.0f, p_y + 35.0f );

      /* Dessin du texte */
      l_result = mk_graphics_drawString ( p_buttonImage->field.layer, l_topLeft, l_bottomRight, p_string, p_buttonImage->style, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result);
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_manager_paintGroup ( T_mkButtonImage* p_buttonImage, T_str8 p_string, T_str8 p_strcount, real32_t p_x, real32_t p_y, uint32_t p_color )
{
   /* Déclaration d'un style (défaut) */
   K_MK_PRIVILEGED_STATIC_MEMORY T_mkTextStyle l_style = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_TOP_JUSTIFIED, K_MK_TEXT_RIGHT_JUSTIFIED,
                             0, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des vecteurs position */
   T_mkVect2D l_topLeft, l_bottomRight;

   /* Configuration des vecteurs position */
   mk_vect2d_setCoord ( &l_topLeft, p_x, p_y + 5.0f );
   mk_vect2d_setCoord ( &l_bottomRight, p_x + 17.0f, p_y + 20.0f );

   /* Dessin d'un rectangle arrondi */
   l_result = mk_graphics_drawRoundRect ( p_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, 3, 0xFF505050 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs position */
      mk_vect2d_setCoord ( &l_topLeft, p_x, p_y + 5.0f );
      mk_vect2d_setCoord ( &l_bottomRight, p_x + 35.0f, p_y + 20.0f );

      /* Dessin d'un rectangle arrondi */
      l_result = mk_graphics_drawRoundRect ( p_buttonImage->field.layer, K_MK_GRAPHICS_EMPTY, l_topLeft, l_bottomRight, 3, p_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si un texte doit être dessiné */
   if ( ( l_result == K_MK_OK ) && ( p_string != K_MK_NULL ) )
   {
      /* Configuration des vecteurs position */
      mk_vect2d_setCoord ( &l_topLeft, p_x + 55.0f, p_y );
      mk_vect2d_setCoord ( &l_bottomRight, p_x + 140.0f, p_y + 25.0f );

      /* Dessin du premier texte du groupe (statut) */
      l_result = mk_graphics_drawString ( p_buttonImage->field.layer, l_topLeft, l_bottomRight, p_string, p_buttonImage->style, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des vecteurs position */
      mk_vect2d_setCoord ( &l_topLeft, p_x + 140.0f, p_y );
      mk_vect2d_setCoord ( &l_bottomRight, p_x + 200.0f, p_y + 25.0f );

      /* Effacement de la valeur précédente */
      l_result = mk_graphics_drawRect ( p_buttonImage->field.layer, K_MK_GRAPHICS_SOLID, l_topLeft, l_bottomRight, K_MK_COLOR_ARGB_BLACK );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Dessin du second texte du groupe (valeur) */
         l_result = mk_graphics_drawString ( p_buttonImage->field.layer, l_topLeft, l_bottomRight, p_strcount, &l_style, K_MK_NULL );
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
   return ( l_result);
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_manager_paintStatusField ( T_mkHomeApplication* p_home, T_mkField* p_field )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une couleur */
   uint32_t l_color;

   /* Récupération de l'adresse du bouton image */
   T_mkButtonImage* l_buttonImage = ( T_mkButtonImage* ) p_field->child;

   /* Récupération de la valeur de la couleur */
   l_color = mk_color_getARGB32 ( &l_buttonImage->borderColor );

   /* Dessin du groupe "System" */
   l_result = mk_home_manager_paintGroupName ( l_buttonImage, ( T_str8 ) "System", K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X, K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y, l_color );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Dessin du groupe "Handle" */
      l_result = mk_home_manager_paintGroupName ( l_buttonImage, ( T_str8 ) "Handle", K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération du nombre d'applications allouées */
      p_home->view.manager.status.appsNumber = g_mkDisplay.handler.applicationPool->count;

      /* Conversion en chaine de caractères */
      mk_home_manager_getStr ( ( T_str8 ) p_home->view.manager.status.strApps, p_home->view.manager.status.appsNumber, K_MK_DISPLAY_APPLICATION_NUMBER );

      /* Dessin du nombre d'application dans le groupe Handle */
      l_result = mk_home_manager_paintGroup ( l_buttonImage, ( T_str8 ) "Apps", ( T_str8 ) p_home->view.manager.status.strApps, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X + 15.0f, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y + 40.0f, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération du nombre de tâches allouées */
      p_home->view.manager.status.taskNumber = g_mkTaskPool.pool.count;

      /* Conversion en chaine de caractères */
      mk_home_manager_getStr ( ( T_str8 ) p_home->view.manager.status.strTask, p_home->view.manager.status.taskNumber, K_MK_SCHEDULER_MAX_NUMBER_OF_TASKS );

      /* Dessin du nombre de tâches dans le groupe Handle */
      l_result |= mk_home_manager_paintGroup ( l_buttonImage, ( T_str8 ) "Task", ( T_str8 ) p_home->view.manager.status.strTask, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X + 15.0f, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y + 65.0f, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération du nombre de pages mémoire SDRAM allouées */
      p_home->view.manager.status.sdramPageNumber = g_mkSDRAMHandler.pool->count;

      /* Conversion en chaine de caractères */
      mk_home_manager_getStr ( ( T_str8 ) p_home->view.manager.status.strSdram, p_home->view.manager.status.sdramPageNumber, K_MK_PAGE_SDRAM_SIZE / K_MK_PAGE_SDRAM_BLOCK_SIZE );

      /* Dessin du nombre de pages allouées dans le groupe Memory */
      l_result |= mk_home_manager_paintGroup ( l_buttonImage, ( T_str8 ) "Sdram", ( T_str8 ) p_home->view.manager.status.strSdram, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_X + 15.0f, K_MK_HOME_MANAGERVIEW_HANDLEAREA_TOPLEFT_Y + 100.0f, l_color );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result);
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_home_manager_paintStatus ( T_mkContainer* p_container, T_mkField* p_field, uint32_t p_frameNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de l'adresse de l'application propriétaire du container */
   T_mkApplication* l_application = mk_container_getOwner ( p_container );

   /* Récupération de l'adresse de l'application home */
   T_mkHomeApplication* l_home = ( T_mkHomeApplication* ) mk_application_getArg ( l_application );

   /* Si le contenu du champ doit être actualisé */
   if ( ( l_home->view.manager.status.sdramPageNumber != g_mkSDRAMHandler.pool->count ) ||
        ( l_home->view.manager.status.taskNumber != g_mkTaskPool.pool.count ) ||
        ( l_home->view.manager.status.appsNumber != g_mkDisplay.handler.applicationPool->count ) )
   {
      /* Réactivation du rafraichissement */
      mk_field_setRefresh ( p_field, K_MK_FIELD_REFRESH_ENABLED );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si le champ doit être rafraichi */
   if ( p_field->refresh != K_MK_FIELD_REFRESH_DISABLED )
   {
      /* Exécution de la fonction de peinture */
      l_result = mk_home_manager_paintStatusField ( l_home, p_field );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Désactivation du rafraichissement */
         mk_field_setRefresh ( p_field, K_MK_FIELD_REFRESH_DISABLED );
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

   /* Suppression warning */
   ( void ) p_frameNumber;

   /* Retour */
   return ( l_result);
}

