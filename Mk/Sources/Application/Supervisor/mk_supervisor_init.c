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
* @file mk_supervisor_init.c
* @brief Définition de la fonction mk_supervisor_init.
* @date 4 nov. 2023
*
*/

#include "mk_supervisor_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_supervisor_initKernelHandler ( void )
{
   /* Déclaration d'une variable de travail */
   T_mkKernelCallback l_kernelCallback;

   /* Configuration des fonctions de rappel du noyau */
   l_kernelCallback.nmiFault = mk_supervisor_nmiFault;
   l_kernelCallback.hardFault = mk_supervisor_hardFault;
   l_kernelCallback.busFault = mk_supervisor_busFault;
   l_kernelCallback.usageFault = mk_supervisor_usageFault;
   l_kernelCallback.memFault = mk_supervisor_memFault;
   l_kernelCallback.fpuFault = mk_supervisor_fpuFault;
   l_kernelCallback.handleFault = mk_supervisor_handleFault;
   l_kernelCallback.svcFault = mk_supervisor_svcFault;
   l_kernelCallback.rightFault = mk_supervisor_rightFault;
   l_kernelCallback.stackFault = mk_supervisor_stackFault;
   mk_handler_set ( &l_kernelCallback );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initMail ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_supervisor->message.area, p_supervisor->message.heap, K_MK_SUPERVISOR_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_supervisor->message.mail, K_MK_AREA_PROTECTED, &p_supervisor->message.area, K_MK_SUPERVISOR_MESSAGE_SIZE, K_MK_SUPERVISOR_MESSAGE_NUMBER );
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

static T_mkCode mk_supervisor_initMemoryPage ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Allocation des pages mémoire */
   l_result  = mk_page_alloc ( K_MK_PAGE_ID_SDRAM, &p_supervisor->page.baseAddr, 0 );
   l_result |= mk_page_alloc ( K_MK_PAGE_ID_SDRAM, &p_supervisor->page.reportAddr, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des pointeurs mémoires */
      /* Attention à la taille de la page mémoire */
      /* Taille = 1 228 800 octets */
      /* Taille cache = 1 096 976 */
      /* Taille buffer fenêtre : 16384 */
      /* Taille buffer prompt : 16384 */
      /* Reste : 99 056 octets */
      p_supervisor->page.promptCache = K_MK_NULL;
      p_supervisor->page.windowCache = ( uint8_t* ) p_supervisor->page.baseAddr;
      p_supervisor->page.windowAddr = ( uint8_t* ) p_supervisor->page.windowCache + K_MK_SUPERVISOR_CONSOLE_CACHE_SIZE;
      p_supervisor->page.promptAddr = ( uint8_t* ) p_supervisor->page.windowAddr + K_MK_SUPERVISOR_CONSOLE_WINDOW_SIZE;
      /*p_supervisor->page.reportAddr = ( uint8_t* ) p_supervisor->page.promptAddr + K_MK_SUPERVISOR_CONSOLE_PROMPT_SIZE;*/
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

static void mk_supervisor_getConsoleFileName ( T_str8 p_str, T_str8 p_suffix )
{
   /* Déclaration d'une variable contenant le TID de la tâche courante */
   char8_t l_tid [ 11 ] = { 0 };

   /* Conversion du TID de la tâche en ASCII */
   ( void ) mk_utils_itoa ( g_mkScheduler.currentTask->attribute.identifier, ( T_str8 ) l_tid, 16, 0 );

   /* Création de la chaine de caractères */
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) K_MK_SUPERVISOR_PATH, ( T_str8 ) "TID_" );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) l_tid );
   ( void ) mk_utils_strcat ( ( T_str8 ) p_str, ( T_str8 ) p_str, ( T_str8 ) p_suffix );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_openConsole ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables contenant les noms des fichiers d'entrées et de sorties */
   char8_t l_strIn [ 48 ] = { 0 }, l_strOut [ 48 ] = { 0 };

   /* Création du nom de fichier de sortie */
   mk_supervisor_getConsoleFileName ( ( T_str8 ) l_strOut, ( T_str8 ) "h_console_out.log" );

   /* Création du nom de fichier d'entrée */
   mk_supervisor_getConsoleFileName ( ( T_str8 ) l_strIn, ( T_str8 ) "h_console_in.log" );

   /* Ouverture de la console */
   l_result = mk_console_open ( &p_supervisor->console, p_supervisor->volume, ( T_str8 ) l_strIn, ( T_str8 ) l_strOut );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initLayers ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des layers */
   mk_layer_init ( &p_supervisor->layer.layers );
   mk_layer_set ( &p_supervisor->layer.layers, K_MK_LAYER_FOREGROUND_VISIBLE );
   mk_layer_setAlpha ( &p_supervisor->layer.layers, 255, 255 );

   /* Ajout du layer dans le container */
   l_result = mk_container_addField ( g_mkDisplay.criticalContainer, &p_supervisor->layer.layers.field, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initFigures ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un style */
   T_mkTextStyle l_loadStyle = { K_MK_NULL, K_MK_FONT_UTF8, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_CENTER_JUSTIFIED,
                             0, 0, 0, 0, { 0x00, 0x00, 0xFF, 0xFF } }; /* Red */

   /* Copie des styles dans une variable persistante. */
   _copy ( &p_supervisor->load.style, &l_loadStyle, sizeof ( T_mkTextStyle ) );

   /* Initialisation des variables d'état */
   /* On affiche le framerate et la charge CPU uniquement sur le premier plan */
   p_supervisor->load.foregroundEnabled = K_MK_TRUE;
   p_supervisor->load.backgroundEnabled = K_MK_FALSE;

   /* Initialisation de la figure affichant le framerate */
   mk_figure_init ( &p_supervisor->load.frameRate );
   mk_figure_setPosition ( &p_supervisor->load.frameRate, 610, 10 );
   mk_figure_setDimension ( &p_supervisor->load.frameRate, 30, 35 );
   mk_figure_setVisibility ( &p_supervisor->load.frameRate, K_MK_FIELD_VISIBLE );
   mk_figure_setPainter ( &p_supervisor->load.frameRate, mk_supervisor_paintFrameRate );

   /* Initialisation de la figure affichant la charge CPU */
   mk_figure_init ( &p_supervisor->load.cpu );
   mk_figure_setPosition ( &p_supervisor->load.cpu, 610, 50 );
   mk_figure_setDimension ( &p_supervisor->load.cpu, 30, 35 );
   mk_figure_setVisibility ( &p_supervisor->load.cpu, K_MK_FIELD_VISIBLE );
   mk_figure_setPainter ( &p_supervisor->load.cpu, mk_supervisor_paintCpuLoad );

   /* Ajout des figures dans le container du superviseur */
   l_result = mk_container_addField ( g_mkDisplay.frontendContainer, &p_supervisor->load.cpu.field, K_MK_NULL );
   l_result |= mk_container_addField ( g_mkDisplay.frontendContainer, &p_supervisor->load.frameRate.field, K_MK_NULL );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_supervisor_initConsole ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Configuration des attributs du container dédié aux objets critiques */
   g_mkDisplay.criticalContainer->owner = ( T_mkApplication* ) &p_supervisor->application;
   g_mkDisplay.criticalContainer->listener = mk_supervisor_listenApplication;

   /* Initialisation de la console */
   mk_console_init ( &p_supervisor->console, p_supervisor->page.promptAddr, K_MK_SUPERVISOR_CONSOLE_PROMPT_SIZE, p_supervisor->page.windowAddr, K_MK_SUPERVISOR_CONSOLE_WINDOW_SIZE );
   mk_console_setLocalEcho ( &p_supervisor->console, K_MK_CONSOLE_LOCALECHO_DISABLED );
   mk_console_setPosition ( &p_supervisor->console, K_MK_CONSOLE_WINDOW, K_MK_SUPERVISOR_CONSOLE_WINDOW_X, K_MK_SUPERVISOR_CONSOLE_WINDOW_Y );
   mk_console_setDimension ( &p_supervisor->console, K_MK_CONSOLE_WINDOW, K_MK_SUPERVISOR_CONSOLE_WINDOW_WIDTH, K_MK_SUPERVISOR_CONSOLE_WINDOW_HEIGHT );
   mk_console_setPosition ( &p_supervisor->console, K_MK_CONSOLE_PROMPT, K_MK_SUPERVISOR_CONSOLE_PROMPT_X, K_MK_SUPERVISOR_CONSOLE_PROMPT_Y );
   mk_console_setDimension ( &p_supervisor->console, K_MK_CONSOLE_PROMPT, K_MK_SUPERVISOR_CONSOLE_PROMPT_WIDTH, K_MK_SUPERVISOR_CONSOLE_PROMPT_HEIGHT );
   mk_console_setCache ( &p_supervisor->console, K_MK_CONSOLE_WINDOW, p_supervisor->page.windowCache );
   mk_console_setCache ( &p_supervisor->console, K_MK_CONSOLE_PROMPT, p_supervisor->page.promptCache );
   mk_console_setBackgroundColor ( &p_supervisor->console, K_MK_CONSOLE_WINDOW, K_MK_COLOR_ARGB_BLACK );
   mk_console_setBackgroundColor ( &p_supervisor->console, K_MK_CONSOLE_PROMPT, K_MK_COLOR_ARGB_BLACK );
   mk_console_setBackgroundColor ( &p_supervisor->console, K_MK_CONSOLE_SCREEN, K_MK_COLOR_ARGB_BLACK );
   mk_console_setVisibility ( &p_supervisor->console, K_MK_FIELD_VISIBLE );
   mk_console_setActivity ( &p_supervisor->console, K_MK_FIELD_ACTIF );
   mk_console_setFocus ( &p_supervisor->console, K_MK_FIELD_STATE_FOCUS );
   mk_console_setListener ( &p_supervisor->console, mk_supervisor_listenConsole );

   /* On s'assure que la console est bien en UTF8 */
   mk_console_setTextColor ( &p_supervisor->console, K_MK_COLOR_ARGB_ORANGE );
   mk_console_setTextEncoding ( &p_supervisor->console, K_MK_FONT_UTF8 );

   /* Ajout de la console dans le container du superviseur */
   l_result = mk_console_addContainer ( &p_supervisor->console, g_mkDisplay.criticalContainer );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_supervisor_init ( T_mkSupervisor* p_supervisor )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la boite de messages du superviseur */
   l_result = mk_supervisor_initMail ( p_supervisor );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des pages mémoires */
      l_result = mk_supervisor_initMemoryPage ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration des layers graphiques */
      l_result = mk_supervisor_initLayers ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la console du superviseur */
      l_result = mk_supervisor_initConsole ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des figures (cpuLoad et frameRate) */
      /* Doit être réalisé suite à l'initialisation de la console car un changement de contexte */
      /* se produit après l'ajout des objets dans le container */
      l_result = mk_supervisor_initFigures ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du système de fichiers */
      l_result = mk_supervisor_mount ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ouverture de la console du superviseur */
      l_result = mk_supervisor_openConsole ( p_supervisor );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des gestionnaires d'interruption du noyau */
      mk_supervisor_initKernelHandler ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire de commandes */
      l_result = mk_shell_create ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}



