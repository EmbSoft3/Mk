/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
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
* @file mk_shell_fileSystem_ls.c
* @brief Définition de la fonction mk_shell_fileSystem_ls.
* @date 15 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_fileSystem_ls ( T_mkShell* p_shell, T_mkConsole* p_console )
{
   /* Prototype de la commande */
   /* ls */

   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des instances de fichiers */
   T_mkFile* l_directory = K_MK_NULL, *l_file = K_MK_NULL;

   /* Déclaration d'une variable stockant un nom de fichier */
   uint8_t l_fileName [ K_MK_FILE_MAX_NAME_LENGTH + 1 ] = { 0 };

   /* Déclaration des variables de travail */
   uint16_t l_counter = 0;

   /* Affichage d'un saut de ligne */
   l_result = mk_console_puts  ( p_console, ( T_str8 ) "\r\n" );

   /* Si aucune erreur ne s'est produite et si le répertoire courant est valide */
   if ( ( l_result == K_MK_OK ) && ( p_shell->currentDirectory != K_MK_NULL ) )
   {
      /* Ouverture du répertoire courant */
      l_result = mk_file_open ( K_MK_NULL, &l_directory, ( T_str8 ) p_shell->currentDirectory, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Effectue */
         do
         {
            /* Ouverture d'un fichier présent dans le répertoire */
            l_result = mk_file_openDirectory ( &l_file, l_directory, l_counter, K_MK_FS_OPEN_READ, K_MK_NULL );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Récupération du nom du fichier */
               l_result = mk_file_getName ( l_file, ( T_str8 ) l_fileName, K_MK_NULL );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Affichage du nom du fichier dans la console */
                  l_result  = mk_console_puts  ( p_console, ( T_str8 ) l_fileName );
                  l_result |= mk_console_puts  ( p_console, ( T_str8 ) "\r\n" );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Fermeture du fichier */
               l_result |= mk_file_close ( l_file, K_MK_NULL );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Passage au prochain fichier du répertoire */
            l_counter = ( uint16_t ) ( l_counter + 1 );
         }

         /* Tant que l'ensemble des fichiers du répertoire n'ont pas été affichés */
         while ( l_result == K_MK_OK );

         /* Bypass de l'état "NOT_FOUND" */
         /* Ce code erreur est renvoyé lorsque tous les fichiers du répertoire ont été récupérés. */
         l_result = ( T_mkCode ) ( l_result & ( T_mkCode ) ( ~K_MK_ERROR_NOT_FOUND ) );

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_NOT_FOUND ) )
         {
            /* Déclenchement d'un rafraichissement graphique */
            l_result = mk_console_print ( p_console, ( T_str8 ) "\r\n" );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Fermeture du répertoire */
         l_result |= mk_file_close ( l_directory, K_MK_NULL );
      }

      /* Sinon si le répertoire courant n'existe pas */
      else if ( l_result == K_MK_ERROR_NOT_FOUND )
      {
         /* Affichage d'un message d'erreur dans la console et déclenchement d'un rafraichissement graphique */
         l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_LS_DIRECTORY_NOT_FOUND );
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


