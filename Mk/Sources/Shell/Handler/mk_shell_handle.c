/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_shell_handle.c
* @brief Définition de la fonction mk_shell_handle.
* @date 4 août 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_log ( T_mkConsole* p_console, T_str8 p_str )
{
   /* Affichage de la ligne de commande dans la console */
   T_mkCode l_result = mk_console_log ( p_console, p_str );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ajout d'un retour à ligne */
      l_result = mk_console_print ( p_console, ( T_str8 ) "\n" );
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

static uint32_t mk_shell_getFirstOffset ( T_mkConsole* p_console, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Déclaration des variable de travail */
   uint32_t l_currentChar = 0;

   /* Récupération de la valeur du premier caractère de la chaine */
   p_str = mk_font_parseString ( p_str, &l_currentChar, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

   /* Tant que l'offset de fin du premier argument n'a pas été déterminé */
   while ( ( l_currentChar != 0x00 ) && ( l_currentChar != ' ' ) && ( l_currentChar != '\n' ) && ( l_currentChar != 0 )  )
   {
      /* Actualisation du nombre de caractères dans la chaine */
      l_result = ( uint32_t ) ( l_result + 1 );

      /* Récupération de la valeur du prochain caractère à analyser */
      p_str = mk_font_parseString ( p_str, &l_currentChar, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
   }

   /* Retour */
   return ( l_result);
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_execute ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de la taille de la commande */
   uint32_t l_length = mk_shell_getFirstOffset ( p_console, p_str );

   /* Si la commande 'reset' doit être exécutée (non sensible à la casse) */
   if ( ( l_length == 5 ) && ( mk_utils_strcomp ( ( T_str8 ) "reset", p_str, 0, 5 ) == 1 ) )
   {
      /* Reset du système */
      cortex_resetSystem ( );
   }

   /* Sinon si la commande 'restart' doit être exécutée */
   else if ( ( l_length == 5 ) && ( mk_utils_strcomp ( ( T_str8 ) "abort", p_str, 1, 5 ) == 1 ) )
   {
      /* Ne rien faire */
   }

   /* Sinon si la commande 'restart' doit être exécutée */
   else if ( ( l_length == 7 ) && ( mk_utils_strcomp ( ( T_str8 ) "restart", p_str, 1, 7 ) == 1 ) )
   {
      /* Exécution de la commande 'help' */
      l_result = mk_shell_restart ( p_shell, p_console, K_MK_NULL, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'cls' doit être exécutée */
   else if ( ( l_length == 3 ) && ( mk_utils_strcomp ( ( T_str8 ) "cls", p_str, 1, 3 ) == 1 ) )
   {
      /* Exécution de la commande 'cls' */
      l_result = mk_console_clear ( p_console );
   }

   /* Sinon si la commande 'help' doit être exécutée */
   else if ( ( l_length == 4 ) && ( mk_utils_strcomp ( ( T_str8 ) "help", p_str, 1, 4 ) == 1 ) )
   {
      /* Exécution de la commande 'help' */
      l_result = mk_shell_help ( p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'install' doit être exécutée */
   else if ( ( l_length == 7 ) && ( mk_utils_strcomp ( ( T_str8 ) "install", p_str, 1, 7 ) == 1 ) )
   {
      /* Exécution de la commande 'install' */
      l_result = mk_shell_application_install ( p_shell, p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'uninstall' doit être exécutée */
   else if ( ( l_length == 9 ) && ( mk_utils_strcomp ( ( T_str8 ) "uninstall", p_str, 1, 9 ) == 1 ) )
   {
      /* Exécution de la commande 'uninstall' */
      l_result = mk_shell_application_uninstall ( p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'get-apps' doit être exécutée */
   else if ( ( l_length == 8 ) && ( mk_utils_strcomp ( ( T_str8 ) "get-apps", p_str, 1, 8 ) == 1 ) )
   {
      /* Exécution de la commande 'get-apps' */
      l_result = mk_shell_application_getApps ( p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'launch' doit être exécutée */
   else if ( ( l_length == 6 ) && ( mk_utils_strcomp ( ( T_str8 ) "launch", p_str, 1, 6 ) == 1 ) )
   {
      /* Exécution de la commande 'launch' */
      l_result = mk_shell_application_launch ( p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'terminate' doit être exécutée */
   else if ( ( l_length == 9 ) && ( mk_utils_strcomp ( ( T_str8 ) "terminate", p_str, 1, 9 ) == 1 ) )
   {
      /* Exécution de la commande 'terminate' */
      l_result = mk_shell_application_terminate ( p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'lsdsk' doit être exécutée */
   else if ( ( l_length == 5 ) && ( mk_utils_strcomp ( ( T_str8 ) "lsdsk", p_str, 1, 5 ) == 1 ) )
   {
      /* Exécution de la commande 'lsdsk' */
      l_result = mk_shell_fileSystem_lsdsk ( p_console );
   }

   /* Sinon si la commande 'ls' doit être exécutée */
   else if ( ( l_length == 2 ) && ( mk_utils_strcomp ( ( T_str8 ) "ls", p_str, 1, 2 ) == 1 ) )
   {
      /* Exécution de la commande 'ls' */
      l_result = mk_shell_fileSystem_ls ( p_shell, p_console );
   }

   /* Sinon si la commande 'cd' doit être exécutée */
   else if ( ( l_length == 2 ) && ( mk_utils_strcomp ( ( T_str8 ) "cd", p_str, 1, 2 ) == 1 ) )
   {
      /* Exécution de la commande 'cd' */
      l_result = mk_shell_fileSystem_cd ( p_shell, p_console, p_str, p_cmdLength );
   }

   /* Sinon si la commande 'pwd' doit être exécutée */
   else if ( ( l_length == 3 ) && ( mk_utils_strcomp ( ( T_str8 ) "pwd", p_str, 1, 3 ) == 1 ) )
   {
      /* Gestion de la commande 'pwd' */
      l_result = mk_shell_fileSystem_pwd ( p_shell, p_console );
   }

   /* Sinon, la commande est peut être une commande externe */
   else
   {
      /* Recherche, installation et exécution de la commande externe */
      l_result = mk_shell_run ( p_shell, p_console, p_str );
   }

   /* Réinitialisation de la chaine */
   _writeBytes ( p_str, 0, p_cmdLength );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_shell_getUserInput ( T_mkShell* p_shell, T_mkShellMessage* p_message, uint32_t* p_cmdLength )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de fichiers */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration des variables stockant la taille du fichier */
   uint32_t l_lowFileSize = 0, l_numberOfBytesRead = 0;

   /* Ouverture du fichier contenant la commande */
   l_result = mk_file_open ( g_mkSupervisor.volume, &l_file, ( T_str8 ) p_message->fileName, K_MK_FS_OPEN_ALWAYS | K_MK_FS_OPEN_READ | K_MK_FS_OPEN_WRITE, K_MK_NULL );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération de la taille du fichier */
      l_result = mk_file_getSize ( l_file, &l_lowFileSize, &l_numberOfBytesRead, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si la taille du buffer est suffisante pour réaliser la lecture */
         if ( l_lowFileSize < K_MK_PAGE_SRAM_BLOCK_SIZE )
         {
            /* Lecture du contenu du fichier */
            /* On stocke la ligne de commande dans la page mémoire */
            l_result = mk_file_read ( l_file, p_shell->page.bufferAddr, l_lowFileSize, &l_numberOfBytesRead, K_MK_NULL );

            /* Si une erreur de lecture s'est produite */
            if ( ( l_result == K_MK_OK ) && ( l_lowFileSize != l_numberOfBytesRead ) )
            {
               /* Actualisation de la variable de retour */
               l_result = K_MK_ERROR_UNEXPECTED;
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
            /* Affichage d'un message d'erreur dans la console */
            l_result = mk_console_log ( p_message->console, ( T_str8 ) "Failed to process command. Increase buffer size." );
         }

         /* Suppression du fichier contenant la commande */
         l_result |= mk_file_unlink ( l_file, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Fermeture du fichier (sans condition) */
      l_result |= mk_file_close ( l_file, K_MK_NULL );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Récupération de la longueur de la ligne de commande (en octets) */
      *p_cmdLength = l_lowFileSize;

      /* Affichage de la ligne de commande dans la console */
      l_result = mk_shell_log ( p_message->console, p_shell->page.bufferAddr );
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

T_mkCode mk_shell_handle ( T_mkShell* p_shell, T_mkShellMessage* p_message )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant la longueur de la commande */
   uint32_t l_cmdLength = 0;

   /* Récupération du contenu de la ligne de commande */
   l_result = mk_shell_getUserInput ( p_shell, p_message, &l_cmdLength );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si une nouvelle commande doit être exécutée */
      if ( p_shell->reg.cmdInProgress == K_MK_SHELL_CMD_END )
      {
         /* Exécution de la commande */
         l_result = mk_shell_execute ( p_shell, p_message->console, p_shell->page.bufferAddr, l_cmdLength );
      }

      /* Sinon */
      else
      {
         /* Récupération de la taille de la commande */
         l_cmdLength = mk_shell_getFirstOffset ( p_message->console, p_shell->page.bufferAddr );

         /* Si la commande 'abort' a été saisie */
         if ( ( l_cmdLength == 5 ) && ( mk_utils_strcomp ( ( T_str8 ) "abort", p_shell->page.bufferAddr, 1, 5 ) == 1 ) )
         {
            /* Exécution de la commande 'help' */
            l_result = mk_shell_abort ( p_shell, p_message->console );
         }

         /* Sinon */
         else
         {
            /* Si une fonction de rappel a été configurée */
            if ( p_shell->reg.callback != K_MK_NULL )
            {
               /* Exécution de la fonction de rappel */
               l_result = p_shell->reg.callback ( p_shell, p_message->console, p_shell->reg.addr, p_shell->page.bufferAddr, l_cmdLength );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
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


