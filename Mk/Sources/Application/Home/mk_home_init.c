/**
*
* @copyright Copyright (C) 2023-2024 RENARD Mathieu. All rights reserved.
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
* @file mk_home_init.c
* @brief Définition de la fonction mk_home_init.
* @date 20 août 2023
*
*/

#include "mk_home_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_initVariables ( T_mkHomeApplication* p_home )
{
   /* Initialisation du pointeur de page mémoire */
   p_home->page.pointer = ( T_mkAddr ) p_home->application->page.gfxAddr;
   p_home->page.background = K_MK_NULL;

   /* Initialisation des données de la vue principale */
   p_home->view.main.applicationList.shiftIndex = 0;
   p_home->view.main.applicationList.appIndex = 0;

   /* Initialisation des données du manager */
   p_home->view.manager.index = 0;
   p_home->view.manager.current = ( T_mkHomeManagerApplicationButton* ) &p_home->view.manager.applicationList.app [ 0 ];
   p_home->view.manager.status.appsNumber = 0;
   p_home->view.manager.status.taskNumber = 0;
   p_home->view.manager.status.sdramPageNumber = 0;
   p_home->view.manager.status.sramPageNumber = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_home_initManagerFields ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration et configuration des styles */
   /* Bouton image : nom */
   T_mkTextStyle l_nameStyle = { &p_home->view.manager.applicationList.font, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED,
                             0, 0, 0, 0, { 0xFF, 0x9B, 0x63, 0xFF } }; /* Blue */
   /* Bouton image : droit de l'application */
   T_mkTextStyle l_rightStyle = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
                             0, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */
   /* Bouton image : défaut */
   T_mkTextStyle l_defaultStyle = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED,
                             0, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */
   /* Status : défaut */
   T_mkTextStyle l_statusDefaultStyle = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_TOP_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED,
                             0, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */

   /* Copie des styles dans des variables persistantes. */
   _copy ( &p_home->view.manager.applicationList.nameStyle, &l_nameStyle, sizeof ( T_mkTextStyle ) );
   _copy ( &p_home->view.manager.applicationList.defaultStyle, &l_defaultStyle, sizeof ( T_mkTextStyle ) );
   _copy ( &p_home->view.manager.applicationList.rightStyle, &l_rightStyle, sizeof ( T_mkTextStyle ) );
   _copy ( &p_home->view.manager.status.defaultStyle, &l_statusDefaultStyle, sizeof ( T_mkTextStyle ) );

   /* Configuration d'une police de caractères personalisée */
   mk_font_init ( &p_home->view.manager.applicationList.font );
   mk_font_setHeight ( &p_home->view.manager.applicationList.font, 25 );
   mk_font_setNumberOfPixelsBetweenChars ( &p_home->view.manager.applicationList.font, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_CHARS );
   mk_font_setNumberOfPixelsBetweenRows ( &p_home->view.manager.applicationList.font, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS );
   mk_font_setTabulationNumberOfPixels ( &p_home->view.manager.applicationList.font, K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER );
   mk_font_setPage ( &p_home->view.manager.applicationList.page, K_MK_FONT_PAGE_BASIC_LATIN, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1 ), &g_mkFontComicSansMS16ptBasicLatinPageDescriptor [ 0 ] [ 0 ], g_mkFontComicSansMS16ptBasicLatinPage );
   mk_font_addPage ( &p_home->view.manager.applicationList.font, &p_home->view.manager.applicationList.page );

   /* Initialisation du premier-plan */
   mk_screen_init ( &p_home->view.manager.screen );
   mk_screen_setColor ( &p_home->view.manager.screen, K_MK_COLOR_ARGB_TRANSPARENT );
   mk_screen_setLayer ( &p_home->view.manager.screen, K_MK_GRAPHICS_FOREGROUND );
   mk_screen_setActivity ( &p_home->view.manager.screen, K_MK_FIELD_ACTIF );
   mk_screen_setVisibility ( &p_home->view.manager.screen, K_MK_FIELD_INVISIBLE );
   mk_screen_setListener ( &p_home->view.manager.screen, mk_home_manager_listenScreen );
   mk_screen_setPainter ( &p_home->view.manager.screen, mk_home_manager_paintScreen );

   /* Initialisation de l'arrière-plan */
   mk_screen_init ( &p_home->view.manager.background );
   mk_screen_setColor ( &p_home->view.manager.background, K_MK_COLOR_ARGB_BLACK );
   mk_screen_setLayer ( &p_home->view.manager.background, K_MK_GRAPHICS_BACKGROUND );
   mk_screen_setActivity ( &p_home->view.manager.background, K_MK_FIELD_INACTIF );
   mk_screen_setVisibility ( &p_home->view.manager.background, K_MK_FIELD_INVISIBLE );
   mk_screen_setPainter ( &p_home->view.manager.background, mk_home_manager_paintBackground );

   mk_figure_init ( &p_home->view.manager.backgroundFigure );
   mk_figure_setPosition ( &p_home->view.manager.backgroundFigure, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y );
   mk_figure_setDimension ( &p_home->view.manager.backgroundFigure, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_WIDTH, ( K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BOTTOMRIGHT_Y - K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y ) + 1 );
   mk_figure_setVisibility ( &p_home->view.manager.backgroundFigure, K_MK_FIELD_INVISIBLE );
   mk_figure_setLayer ( &p_home->view.manager.backgroundFigure, K_MK_GRAPHICS_BACKGROUND );
   mk_figure_setPainter ( &p_home->view.manager.backgroundFigure, mk_home_manager_paintApplicationListBackground );

   /* Initialisation des graphiques */
   /* CPU Load */
   mk_graph2D_init ( &p_home->view.manager.cpuLoad.graph );
   mk_graph2D_setPainter ( &p_home->view.manager.cpuLoad.graph, mk_home_manager_paintGraphics );
   mk_graph2D_setType ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_TYPE_LINE );
   mk_graph2D_setCache ( &p_home->view.manager.cpuLoad.graph, p_home->page.pointer );
   mk_graph2D_setPosition ( &p_home->view.manager.cpuLoad.graph, K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X + K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_X, K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y + K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_Y );
   mk_graph2D_setDimension ( &p_home->view.manager.cpuLoad.graph, K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH, K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT );
   mk_graph2D_setArea (  &p_home->view.manager.cpuLoad.graph, p_home->view.manager.cpuLoad.graph.field.position.x, p_home->view.manager.cpuLoad.graph.field.position.y, p_home->view.manager.cpuLoad.graph.field.dimension.width, p_home->view.manager.cpuLoad.graph.field.dimension.height );
   mk_graph2D_setLayer ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPHICS_FOREGROUND );
   mk_graph2D_setVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setActivity ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_INACTIF );
   mk_graph2D_setPixelBuf ( &p_home->view.manager.cpuLoad.graph, p_home->view.manager.cpuLoad.buf, 64 );
   mk_graph2D_setBorderVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_VISIBLE );
   mk_graph2D_setBorderColor ( &p_home->view.manager.cpuLoad.graph, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setBackgroundVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setBackgroundColor ( &p_home->view.manager.cpuLoad.graph, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setForegroundVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_FIELD_VISIBLE );
   mk_graph2D_setForegroundColor ( &p_home->view.manager.cpuLoad.graph, K_MK_COLOR_ARGB_BLACK );
   mk_graph2D_setColor ( &p_home->view.manager.cpuLoad.graph, K_MK_COLOR_ARGB_YELLOW );
   mk_graph2D_setGrid ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_PRIMARY, 40, 40 );
   mk_graph2D_setGridLayer ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPHICS_BACKGROUND );
   mk_graph2D_setGridColor ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_PRIMARY, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setGridVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_PRIMARY, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setGrid ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_SECONDARY, 10, 10 );
   mk_graph2D_setGridColor ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_SECONDARY, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setGridVisibility ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_GRID_SECONDARY, K_MK_FIELD_VISIBLE );
   mk_graph2D_setText ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, ( T_str8 ) "CPU");
   mk_graph2D_setTextLayer ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPHICS_BACKGROUND );
   mk_graph2D_setTextArea ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, p_home->view.manager.cpuLoad.graph.field.position.x, p_home->view.manager.cpuLoad.graph.field.position.y + K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT + 10, K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH, 40 );
   mk_graph2D_setTextStyle ( &p_home->view.manager.cpuLoad.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, K_MK_NULL );

   /* FrameRate */
   mk_graph2D_init ( &p_home->view.manager.frameRate.graph );
   mk_graph2D_setPainter ( &p_home->view.manager.frameRate.graph, mk_home_manager_paintGraphics );
   mk_graph2D_setType ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_TYPE_LINE );
   mk_graph2D_setCache ( &p_home->view.manager.frameRate.graph, p_home->page.pointer + ( K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH * K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT ) );
   mk_graph2D_setPosition ( &p_home->view.manager.frameRate.graph, K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_X + ( 2 * K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_X ) + K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH, K_MK_HOME_MANAGERVIEW_GRAPH2DAREA_TOPLEFT_Y + K_MK_HOME_MANAGERVIEW_GRAPH2D_OFFSET_Y );
   mk_graph2D_setDimension ( &p_home->view.manager.frameRate.graph, K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH, K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT );
   mk_graph2D_setArea (  &p_home->view.manager.frameRate.graph, p_home->view.manager.frameRate.graph.field.position.x, p_home->view.manager.frameRate.graph.field.position.y, p_home->view.manager.frameRate.graph.field.dimension.width, p_home->view.manager.frameRate.graph.field.dimension.height );
   mk_graph2D_setLayer ( &p_home->view.manager.frameRate.graph, K_MK_GRAPHICS_FOREGROUND );
   mk_graph2D_setVisibility ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setActivity ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_INACTIF );
   mk_graph2D_setPixelBuf ( &p_home->view.manager.frameRate.graph, p_home->view.manager.frameRate.buf, 64 );
   mk_graph2D_setBorderVisibility ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_VISIBLE );
   mk_graph2D_setBorderColor ( &p_home->view.manager.frameRate.graph, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setBackgroundVisibility ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setBackgroundColor ( &p_home->view.manager.frameRate.graph, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setForegroundVisibility ( &p_home->view.manager.frameRate.graph, K_MK_FIELD_VISIBLE );
   mk_graph2D_setForegroundColor ( &p_home->view.manager.frameRate.graph, K_MK_COLOR_ARGB_BLACK );
   mk_graph2D_setColor ( &p_home->view.manager.frameRate.graph, K_MK_COLOR_ARGB_YELLOW );
   mk_graph2D_setGrid ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_PRIMARY, 40, 40 );
   mk_graph2D_setGridLayer ( &p_home->view.manager.frameRate.graph, K_MK_GRAPHICS_BACKGROUND );
   mk_graph2D_setGridColor ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_PRIMARY, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setGridVisibility ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_PRIMARY, K_MK_FIELD_INVISIBLE );
   mk_graph2D_setGrid ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_SECONDARY, 10, 10 );
   mk_graph2D_setGridColor ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_SECONDARY, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_graph2D_setGridVisibility ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_GRID_SECONDARY, K_MK_FIELD_VISIBLE );
   mk_graph2D_setText ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, ( T_str8 ) "Framerate");
   mk_graph2D_setTextLayer ( &p_home->view.manager.frameRate.graph, K_MK_GRAPHICS_BACKGROUND );
   mk_graph2D_setTextArea ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, p_home->view.manager.frameRate.graph.field.position.x, p_home->view.manager.frameRate.graph.field.position.y + K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT + 10, K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH, 40 );
   mk_graph2D_setTextStyle ( &p_home->view.manager.frameRate.graph, K_MK_GRAPH2D_IDENTIFIER_TITLE, K_MK_NULL );

   /* Initialisation du bouton image */
   mk_buttonImage_init ( &p_home->view.manager.status.button );
   mk_buttonImage_setPosition ( &p_home->view.manager.status.button, K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_X , K_MK_HOME_MANAGERVIEW_STATUSAREA_TOPLEFT_Y );
   mk_buttonImage_setDimension ( &p_home->view.manager.status.button, K_MK_HOME_MANAGERVIEW_STATUSAREA_WIDTH, K_MK_HOME_MANAGERVIEW_STATUSAREA_HEIGHT );
   mk_buttonImage_setLayer ( &p_home->view.manager.status.button, K_MK_GRAPHICS_BACKGROUND );
   mk_buttonImage_setZIndex ( &p_home->view.manager.status.button, 2 );
   mk_buttonImage_setBorderColor ( &p_home->view.manager.status.button, K_MK_COLOR_ARGB_DARKEST_GRAY );
   mk_buttonImage_setBorderVisibility ( &p_home->view.manager.status.button, K_MK_FIELD_VISIBLE );
   mk_buttonImage_setVisibility ( &p_home->view.manager.status.button, K_MK_FIELD_INVISIBLE );
   mk_buttonImage_setActivity ( &p_home->view.manager.status.button, K_MK_FIELD_INACTIF );
   mk_buttonImage_setImage ( &p_home->view.manager.status.button, &p_home->view.ressources.managerSystemStatusLogo );
   mk_buttonImage_setTextBuffer ( &p_home->view.manager.status.button, K_MK_NULL );
   mk_buttonImage_setTextStyle ( &p_home->view.manager.status.button, &p_home->view.manager.status.defaultStyle );
   mk_buttonImage_setListener ( &p_home->view.manager.status.button, K_MK_NULL );
   mk_buttonImage_setPainter ( &p_home->view.manager.status.button, mk_home_manager_paintStatus );

   /* Configuration de la liste de boutons applicatifs */
   for ( l_counter = 0 ; l_counter < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_counter++ )
   {
      /* Configuration du bouton image */
      mk_buttonImage_init ( &p_home->view.manager.applicationList.app [ l_counter ].button );
      mk_buttonImage_setPosition ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_X,
                                   K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_TOPLEFT_Y + ( real32_t ) ( l_counter * K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT ) );
      mk_buttonImage_setDimension ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_WIDTH, K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_HEIGHT );
      mk_buttonImage_setLayer ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_GRAPHICS_BACKGROUND );
      mk_buttonImage_setZIndex ( &p_home->view.manager.applicationList.app [ l_counter ].button, 2 );
      mk_buttonImage_setBorderColor ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_COLOR_ARGB_DARKEST_GRAY );
      mk_buttonImage_setBorderVisibility ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_FIELD_VISIBLE );
      mk_buttonImage_setVisibility ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_FIELD_INVISIBLE );
      mk_buttonImage_setActivity ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_FIELD_INACTIF );
      mk_buttonImage_setImage ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setTextBuffer ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setTextStyle ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setListener ( &p_home->view.manager.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setPainter ( &p_home->view.manager.applicationList.app [ l_counter ].button, mk_home_manager_paintButtonImage );
      mk_buttonImage_setChild ( &p_home->view.manager.applicationList.app [ l_counter ].button, ( T_mkHomeManagerApplicationButton* ) &p_home->view.manager.applicationList.app [ l_counter ] );

      /* Configuration de l'élément enfant et des styles de chaque bouton */
      p_home->view.manager.applicationList.app [ l_counter ].nameStyle = &p_home->view.manager.applicationList.nameStyle;
      p_home->view.manager.applicationList.app [ l_counter ].defaultStyle = &p_home->view.manager.applicationList.defaultStyle;
      p_home->view.manager.applicationList.app [ l_counter ].rightStyle = &p_home->view.manager.applicationList.rightStyle;
   }

   /* Actualisation du pointeur mémoire */
   p_home->page.pointer += ( 2 * ( K_MK_HOME_MANAGERVIEW_GRAPH2D_WIDTH * K_MK_HOME_MANAGERVIEW_GRAPH2D_HEIGHT ) );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_initManagerView ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Initialisation du container du manager */
   l_result = mk_container_create ( &p_home->view.manager.container, 0xFFFFFFFF, K_MK_NULL, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des objets du manager */
      mk_home_initManagerFields ( p_home );

      /* Ajout des objets dans le container */
      l_result  = mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.background.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.backgroundFigure.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.status.button.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.screen.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.cpuLoad.graph.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.frameRate.graph.field, K_MK_NULL );

      for ( l_counter = 0 ; l_counter < K_MK_HOME_MANAGERVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_counter++ )
      {
         l_result |= mk_container_addField ( p_home->view.manager.container, &p_home->view.manager.applicationList.app [ l_counter ].button.field, K_MK_NULL );
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

static void mk_home_initMainFields ( T_mkHomeApplication* p_home )
{
   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Déclaration d'une variable de travail */
   uint32_t l_dx = 25;

   /* Déclaration et configuration des styles */
   /* Défaut */
   T_mkTextStyle l_nameStyle = { &p_home->view.main.applicationList.font, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
                             20, 0, 0, 0, { 0xFF, 0xFF, 0xFF, 0xFF } }; /* White */
   /* Bouton sélectionné */
   T_mkTextStyle l_focusStyle = { &p_home->view.main.applicationList.font, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
                             20, 0, 0, 0, { 0xFF, 0x9B, 0x63, 0xFF } }; /* Blue */

   /* Copie des styles dans des variables persistantes. */
   _copy ( &p_home->view.main.applicationList.nameStyle, &l_nameStyle, sizeof ( T_mkTextStyle ) );
   _copy ( &p_home->view.main.applicationList.focusStyle, &l_focusStyle, sizeof ( T_mkTextStyle ) );

   /* Configuration d'une police de caractères personalisée */
   mk_font_init ( &p_home->view.main.applicationList.font );
   mk_font_setHeight ( &p_home->view.main.applicationList.font, 25 );
   mk_font_setNumberOfPixelsBetweenChars ( &p_home->view.main.applicationList.font, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_CHARS );
   mk_font_setNumberOfPixelsBetweenRows ( &p_home->view.main.applicationList.font, K_MK_FONT_DEFAULT_NUMBER_OF_PIXELS_BETWEEN_ROWS );
   mk_font_setTabulationNumberOfPixels ( &p_home->view.main.applicationList.font, K_MK_FONT_DEFAULT_TABULATION_PIXELS_NUMBER );
   mk_font_setPage ( &p_home->view.main.applicationList.page, K_MK_FONT_PAGE_BASIC_LATIN, ( uint32_t ) ( K_MK_FONT_PAGE_LATIN_1_SUPPLEMENT - 1 ), &g_mkFontComicSansMS16ptBasicLatinPageDescriptor [ 0 ] [ 0 ], g_mkFontComicSansMS16ptBasicLatinPage );
   mk_font_addPage ( &p_home->view.main.applicationList.font, &p_home->view.main.applicationList.page );

   /* Initialisation du premier-plan */
   mk_screen_init ( &p_home->view.main.screen );
   mk_screen_setColor ( &p_home->view.main.screen, K_MK_COLOR_ARGB_TRANSPARENT );
   mk_screen_setLayer ( &p_home->view.main.screen, K_MK_GRAPHICS_FOREGROUND );
   mk_screen_setVisibility ( &p_home->view.main.screen, K_MK_FIELD_INVISIBLE );
   mk_screen_setActivity ( &p_home->view.main.screen, K_MK_FIELD_INACTIF );
   mk_screen_setListener ( &p_home->view.main.screen, mk_home_main_listenScreen );
   mk_screen_setPainter ( &p_home->view.main.screen, mk_home_main_paintForeground );

   /* Initialisation de l'image d'arrière plan */
   mk_buttonImage_init ( &p_home->view.main.background );
   mk_buttonImage_setPosition ( &p_home->view.main.background, K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_X , K_MK_HOME_MANAGERVIEW_WORKINGAREA_TOPLEFT_Y );
   mk_buttonImage_setDimension ( &p_home->view.main.background, mk_display_getWidth ( ), mk_display_getHeight ( ) );
   mk_buttonImage_setLayer ( &p_home->view.main.background, K_MK_GRAPHICS_BACKGROUND );
   mk_buttonImage_setBorderColor ( &p_home->view.main.background, K_MK_COLOR_ARGB_BLACK );
   mk_buttonImage_setBorderVisibility ( &p_home->view.main.background, K_MK_FIELD_INVISIBLE );
   mk_buttonImage_setVisibility ( &p_home->view.main.background, K_MK_FIELD_VISIBLE );
   mk_buttonImage_setActivity ( &p_home->view.main.background, K_MK_FIELD_INACTIF );
   mk_buttonImage_setImage ( &p_home->view.main.background, &p_home->view.ressources.background );
   mk_buttonImage_setPainter ( &p_home->view.main.background, mk_home_main_paintBackground );

   /* Configuration des boutons de la vue principale */
   for ( l_counter = 0 ; l_counter < K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_counter++ )
   {
      /* Initialisation du bouton image */
      mk_buttonImage_init ( &p_home->view.main.applicationList.app [ l_counter ].button );
      mk_buttonImage_setPosition ( &p_home->view.main.applicationList.app [ l_counter ].button, ( real32_t ) ( K_MK_HOME_MAINVIEW_APPLICATIONLIST_AREA_TOPLEFT_X + l_dx ), ( real32_t ) ( K_MK_HOME_MAINVIEW_APPLICATIONLIST_AREA_TOPLEFT_Y + 10 ) );
      mk_buttonImage_setDimension ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_WIDTH, K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_HEIGHT );
      mk_buttonImage_setLayer ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_GRAPHICS_FOREGROUND );
      mk_buttonImage_setZIndex ( &p_home->view.main.applicationList.app [ l_counter ].button, 2 );
      mk_buttonImage_setBorderColor ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_COLOR_ARGB_DARKEST_GRAY );
      mk_buttonImage_setBorderVisibility ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_FIELD_VISIBLE );
      mk_buttonImage_setVisibility ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_FIELD_INVISIBLE );
      mk_buttonImage_setActivity ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_FIELD_INACTIF );
      mk_buttonImage_setImage ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setTextBuffer ( &p_home->view.main.applicationList.app [ l_counter ].button, K_MK_NULL );
      mk_buttonImage_setTextStyle ( &p_home->view.main.applicationList.app [ l_counter ].button, &p_home->view.main.applicationList.nameStyle );
      mk_buttonImage_setListener ( &p_home->view.main.applicationList.app [ l_counter ].button, mk_home_main_listenApplicationButton );
      mk_buttonImage_setPainter ( &p_home->view.main.applicationList.app [ l_counter ].button, mk_home_main_paintApplicationButton );
      mk_buttonImage_setChild ( &p_home->view.main.applicationList.app [ l_counter ].button,  ( T_mkHomeMainApplicationButton* ) &p_home->view.main.applicationList.app [ l_counter ] );

      /* Configuration de l'élément enfant et du style par défaut du bouton */
      p_home->view.main.applicationList.app [ l_counter ].nameStyle = &p_home->view.manager.applicationList.nameStyle;

      /* Actualisation de la position du prochain bouton */
      l_dx = ( uint32_t ) ( l_dx + K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_WIDTH );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_home_initMainView ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Initialisation du container de la vue principale */
   l_result = mk_container_create ( &p_home->view.main.container, 0xFFFFFFFF, mk_home_main_listenApplication, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des objets de la vue principale */
      mk_home_initMainFields ( p_home );

      /* Ajout des objets dans le container */
      l_result  = mk_container_addField ( p_home->view.main.container, &p_home->view.main.background.field, K_MK_NULL );
      l_result |= mk_container_addField ( p_home->view.main.container, &p_home->view.main.screen.field, K_MK_NULL );

      for ( l_counter = 0 ; l_counter < K_MK_HOME_MAINVIEW_APPLICATIONLIST_BUTTON_NUMBER ; l_counter++ )
      {
         l_result |= mk_container_addField ( p_home->view.main.container, &p_home->view.main.applicationList.app [ l_counter ].button.field, K_MK_NULL );
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

static T_mkCode mk_home_initLayer ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du container du manager */
   l_result = mk_container_create ( &p_home->view.layer.container, 0xFFFFFFFF, K_MK_NULL, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des layers */
      mk_layer_init ( &p_home->view.layer.layers );
      mk_layer_set ( &p_home->view.layer.layers, K_MK_LAYER_BOTH_VISIBLE );
      mk_layer_setAlpha ( &p_home->view.layer.layers, 255, 255 );

      /* Ajout du layer dans le container */
      l_result = mk_container_addField ( p_home->view.layer.container, &p_home->view.layer.layers.field, K_MK_NULL );
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

static T_mkCode mk_home_initRessourcesPool ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiée au stockage des logos des applications */
   l_result = mk_pool_initArea ( &p_home->view.ressources.area, p_home->page.pointer,
                                 K_MK_DISPLAY_APPLICATION_NUMBER * K_MK_APPLICATION_LOGO_WIDTH * K_MK_APPLICATION_LOGO_HEIGHT );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique */
      l_result = mk_pool_create ( &p_home->view.ressources.area, &p_home->view.ressources.pool,
                                  K_MK_AREA_PROTECTED, K_MK_APPLICATION_LOGO_WIDTH * K_MK_APPLICATION_LOGO_HEIGHT, K_MK_DISPLAY_APPLICATION_NUMBER );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation du pointeur mémoire */
   p_home->page.pointer += ( K_MK_DISPLAY_APPLICATION_NUMBER * K_MK_APPLICATION_LOGO_WIDTH * K_MK_APPLICATION_LOGO_HEIGHT );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_home_init ( T_mkHomeApplication* p_home )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des variables de l'application */
   mk_home_initVariables ( p_home );

   /* Initialisation des vues de l'application */
   l_result  = mk_home_initManagerView ( p_home );
   l_result |= mk_home_initMainView ( p_home );
   l_result |= mk_home_initLayer ( p_home );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ajout des container dans une factory du moteur graphique */
      l_result = mk_factory_addContainer ( p_home->view.layer.container, K_MK_NULL );
      l_result |= mk_factory_addContainer ( p_home->view.manager.container, K_MK_NULL );
      l_result |= mk_factory_addContainer ( p_home->view.main.container, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Installation des applications par défaut */
      l_result |= mk_home_install ( );

      /* Initialisation des ressources de l'application */
      l_result |= mk_home_initRessourcesPool ( p_home );
      l_result |= mk_home_loadRessources ( p_home );

      /* Attente de la fin du chargement des ressources */
      l_result |= mk_task_delay ( 1500 );

      /* Configuration de la visibilité de la vue principale */
      mk_container_setVisibility ( p_home->view.main.container, K_MK_FIELD_VISIBLE );
      mk_container_setActivity ( p_home->view.main.container, K_MK_FIELD_ACTIF );
      mk_home_main_setVisibility ( p_home );

      /* Il est nécessaire de désactiver le container critique */
      mk_container_setVisibility ( g_mkDisplay.criticalContainer, K_MK_FIELD_INVISIBLE );
      mk_container_setActivity ( g_mkDisplay.criticalContainer, K_MK_FIELD_INACTIF );

      /* Réactivation du rafraichissement de l'arrière plan */
      mk_buttonImage_setRefresh ( &p_home->view.main.background, K_MK_FIELD_REFRESH_ENABLED );

      /* Dans la situation où une ressource n'a pas été trouvée, une erreur de type K_MK_ERROR_NOT_FOUND */
      /* peut être renvoyée. */
      /* On la masque car cette erreur n'est pas critique. */
      l_result = l_result & ( T_mkCode ) ( ~ K_MK_ERROR_NOT_FOUND );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

