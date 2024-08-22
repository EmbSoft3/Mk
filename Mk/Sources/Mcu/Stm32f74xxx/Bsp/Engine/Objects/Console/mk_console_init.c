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
* @file mk_console_init.c
* @brief Définition de la fonction mk_console_init.
* @date 30 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_init ( T_mkConsole* p_console, T_mkAddr p_promptBuf, uint32_t p_promptSize, T_mkAddr p_windowBuf, uint32_t p_windowSize )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du sémaphore */
   p_console->semaphore = K_MK_NULL;

   /* Initialisation du fichier */
   p_console->window.file = K_MK_NULL;
   p_console->window.filePointer = 0;

   /* Configuration des pointeurs de buffer */
   p_console->prompt.buf = p_promptBuf;
   p_console->window.buf = p_windowBuf;
   p_console->prompt.bufSize = p_promptSize;
   p_console->window.bufSize = p_windowSize;

   /* Configuration de l'echo local */
   p_console->window.localEcho = K_MK_CONSOLE_LOCALECHO_ENABLED;

   /* Initialisation des chaines de caractères */
   _writeBytes ( p_promptBuf, 0, p_promptSize );
   _writeBytes ( p_windowBuf, 0, p_windowSize );

   /* Initialisation du premier plan */
   mk_screen_init ( &p_console->foreground.screen );
   mk_screen_setColor ( &p_console->foreground.screen, 0xFF211F32 );
   mk_screen_setVisibility ( &p_console->foreground.screen, K_MK_FIELD_VISIBLE );
   mk_screen_setLayer ( &p_console->foreground.screen, K_MK_GRAPHICS_FOREGROUND );
   mk_screen_setChild ( &p_console->foreground.screen, ( T_mkConsole* ) p_console );

   /* Initialisation de la boite d'édition dédiée au prompt */
   mk_editField_init ( &p_console->foreground.prompt );
   mk_editField_setChild ( &p_console->foreground.prompt, ( T_mkConsole* ) p_console );
   mk_editField_setTextAlignment ( &p_console->foreground.prompt, K_MK_TEXT_CENTER_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED );
   mk_editField_setVisibility ( &p_console->foreground.prompt, K_MK_FIELD_VISIBLE );
   mk_editField_setLayer ( &p_console->foreground.prompt, K_MK_GRAPHICS_FOREGROUND );
   mk_editField_disableScrolling ( &p_console->foreground.prompt );
   mk_editField_disableWriteProtect ( &p_console->foreground.prompt );
   mk_editField_setBackgroundVisibility ( &p_console->foreground.prompt, K_MK_FIELD_INVISIBLE );
   mk_editField_setBackgroundColor ( &p_console->foreground.prompt, 0xFF181421 );
   mk_editField_setCursorVisibility ( &p_console->foreground.prompt, K_MK_GRAPHICS_VISIBLE );
   mk_editField_setCursorColor ( &p_console->foreground.prompt, K_MK_COLOR_ARGB_LIME );
   mk_editField_setTextBuffer ( &p_console->foreground.prompt, p_promptBuf, p_promptSize );
   mk_editField_setTextColor ( &p_console->foreground.prompt, K_MK_COLOR_ARGB_LIME );
   mk_editField_setTextEncoding ( &p_console->foreground.prompt, K_MK_FONT_UTF8 );
   mk_editField_setFont ( &p_console->foreground.prompt, &g_mkDisplay.defaultFixedFont.handle );
   mk_editField_setListener ( &p_console->foreground.prompt, mk_console_defaultListener );

   /* Initialisation de la boite d'édition dédiée à la fenêtre */
   mk_editField_init ( &p_console->foreground.window );
   mk_editField_setChild ( &p_console->foreground.window, ( T_mkConsole* ) p_console );
   mk_editField_setTextAlignment ( &p_console->foreground.window, K_MK_TEXT_TOP_JUSTIFIED, K_MK_TEXT_LEFT_JUSTIFIED );
   mk_editField_setVisibility ( &p_console->foreground.window, K_MK_FIELD_VISIBLE );
   mk_editField_setLayer ( &p_console->foreground.window, K_MK_GRAPHICS_FOREGROUND );
   mk_editField_disableScrolling ( &p_console->foreground.window );
   mk_editField_enableWriteProtect ( &p_console->foreground.window );
   mk_editField_setBackgroundVisibility ( &p_console->foreground.window, K_MK_FIELD_INVISIBLE );
   mk_editField_setBackgroundColor ( &p_console->foreground.window, 0xFF181421 );
   mk_editField_setCursorVisibility ( &p_console->foreground.window, K_MK_GRAPHICS_INVISIBLE );
   mk_editField_setCursorColor ( &p_console->foreground.window, K_MK_COLOR_ARGB_LIME );
   mk_editField_setTextBuffer ( &p_console->foreground.window, p_windowBuf, p_windowSize );
   mk_editField_setTextColor ( &p_console->foreground.window, K_MK_COLOR_ARGB_LIME );
   mk_editField_setTextEncoding ( &p_console->foreground.window, K_MK_FONT_UTF8 );
   mk_editField_setFont ( &p_console->foreground.window, &g_mkDisplay.defaultFixedFont.handle );

   /* Déclenchement d'un rafraichissement de la console */
   mk_console_setRefresh ( p_console, K_MK_FIELD_REFRESH_ENABLED );

   /* Initialisation du sémaphore */
   l_result = mk_semaphore_create ( &p_console->semaphore, K_MK_AREA_PROTECTED, 1, 0 );

   /* Retour */
   return ( l_result );
}


