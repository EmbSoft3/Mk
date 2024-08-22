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
* @file mk_console_open.c
* @brief Définition de la fonction mk_console_open.
* @date 7 févr. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_console_openFiles ( T_mkConsole* p_console, T_mkVolume* p_volume, T_str8 p_stdinPath, T_str8 p_stdoutPath )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Ouverture du fichier de sortie */
   l_result = mk_file_open ( p_volume, &p_console->window.file, p_stdoutPath, K_MK_FS_OPEN_TRUNCATE | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE | K_MK_FS_OPEN_SHARED, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ouverture du fichier d'entrée */
      l_result = mk_file_open ( p_volume, &p_console->prompt.file, p_stdinPath, K_MK_FS_OPEN_TRUNCATE | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE | K_MK_FS_OPEN_SHARED, K_MK_NULL );
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

static T_mkCode mk_console_flush ( T_mkConsole* p_console )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_numberOfBytesToWrite = 0, l_numberOfBytesWrite;

   /* Déclaration d'un pointeur de chaine */
   T_str8 l_str = K_MK_NULL;

   /* Récupération de l'adresse de la chaine de caractères */
   l_str = ( T_str8 ) p_console->window.buf;

   /* Si une chaine de caractères est présente dans fenêtre de la console */
   /* Il faut la stocker dans le fichier */
   if ( l_str [ 0 ] != 0 )
   {
      /* Récupération de la longueur de la chaine de caractères */
      l_numberOfBytesToWrite = mk_utils_utfsize ( p_console->window.buf, K_MK_FONT_ASCII );

      /* Ecriture de la chaine de caractères dans le fichier */
      l_result = mk_file_write ( p_console->window.file, l_str, l_numberOfBytesToWrite, &l_numberOfBytesWrite, K_MK_NULL );

      /* Si une erreur d'écriture s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_numberOfBytesToWrite != l_numberOfBytesWrite) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_UNEXPECTED;
      }

      /* Sinon */
      else
      {
         /* Entrée en section critique */
         l_result = mk_display_enterCritical ( );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Réinitialisation du buffer de la boite d'édition */
            _writeBytes ( p_console->window.buf, 0, p_console->window.bufSize );
            mk_editField_setTextBuffer ( &p_console->foreground.window, p_console->window.buf, p_console->window.bufSize );

            /* Sortie de la section crique */
            l_result |= mk_display_exitCritical ( );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_open ( T_mkConsole* p_console, T_mkVolume* p_volume, T_str8 p_stdinPath, T_str8 p_stdoutPath )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_console != K_MK_NULL ) && ( p_console->semaphore != K_MK_NULL ) &&
        ( p_console->window.file == K_MK_NULL ) && ( p_console->prompt.file == K_MK_NULL ) && ( p_console->foreground.window.strAddr != K_MK_NULL ) &&
        ( p_stdinPath != K_MK_NULL ) && ( p_stdoutPath != K_MK_NULL ) )
   {
      /* Ouverture des fichiers d'entrées et de sortie */
      l_result = mk_console_openFiles ( p_console, p_volume, p_stdinPath, p_stdoutPath );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transfert des caractères présents dans la boite d'édition vers le fichier puis vidange du buffer */
         l_result = mk_console_flush ( p_console );

         /* Si le fichier n'est pas vide */
         if ( l_result == K_MK_OK )
         {
            /* Rafraichissement de la console */
            l_result = mk_console_refresh ( p_console );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}



