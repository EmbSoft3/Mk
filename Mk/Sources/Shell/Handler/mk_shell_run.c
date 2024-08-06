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
* @file mk_shell_run.c
* @brief Définition de la fonction mk_shell_run.
* @date 4 août 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */


T_mkCode mk_shell_run ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str )
{
   /* Déclaration des variables de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_currentDirectoryLength = 0, l_pathLength = 0;

   /* Déclaration d'une variable stockant le chemin de l'application à installer */
   uint8_t l_path [ K_MK_FILE_MAX_NAME_LENGTH + 1 ] = { 0 };

   /* Le gestionnaire d'application est plus prioritaire que le gestionnaire de commandes, il n'est donc pas nécessaire */
   /* de copier les chaines de caractères dans un buffer. */
   T_str8 l_fileName = K_MK_NULL, l_appParams = K_MK_NULL;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application;

   /* Récupération de l'adresse de la chaine de caractères contenant le nom et le chemin de l'application */
   l_fileName = p_str;

   /* Récupération de l'adresse des arguments de la ligne de commandes */
   l_result = mk_application_getArgv ( p_str, &p_str, p_str, K_MK_FILE_MAX_NAME_LENGTH + 1, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
   l_appParams = p_str;

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le chemin fourni est un chemin absolu */
      if ( l_fileName [ 0 ] == '/' )
      {
         /* Installation de l'application saisie par l'utilisateur */
         l_result = mk_application_installDynamic ( &l_application, l_fileName, ( T_str8 ) l_appParams, K_MK_NULL, K_MK_NULL );
      }

      /* Sinon */
      else
      {
         /* Récupération de la longueur des chaines de caractères [en octets] */
         /* CurrentDirectory et Path */
         l_currentDirectoryLength = mk_utils_utfsize ( ( T_str8 ) p_shell->currentDirectory, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
         l_pathLength = mk_utils_utfsize ( l_fileName, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

         /* Si la longueur cumulée des chaines de caractères est valides (+1 pour le caractère '/') */
         if ( ( l_currentDirectoryLength + l_pathLength + 1 ) < K_MK_FILE_MAX_NAME_LENGTH )
         {
            /* Création d'un chemin absolu */
            _copy ( &l_path [ 0 ], &p_shell->currentDirectory [ 0 ], l_currentDirectoryLength );
            _copy ( &l_path [ l_currentDirectoryLength ], ( T_str8 ) "/", 1 );
            _copy ( &l_path [ l_currentDirectoryLength + 1 ], l_fileName, l_pathLength + 1 );

            /* Installation de l'application saisie par l'utilisateur */
            l_result = mk_application_installDynamic ( &l_application, ( T_str8 ) l_path, ( T_str8 ) l_appParams, K_MK_NULL, K_MK_NULL );
         }

         /* Sinon */
         else
         {
            /* Affichage d'un message d'erreur */
            l_result = mk_console_print ( p_console, ( T_str8 ) "Error: invalid path length.\n\n" );
         }
      }

      /* Si l'application n'a pas été trouvée */
      if ( l_result == K_MK_ERROR_NOT_FOUND )
      {
         /* Affichage d'un message d'erreur dans la console */
         l_result = mk_console_print ( p_console, ( T_str8 ) "Error: file not found.\n\n" );
      }

      /* Sinon si l'application a été installée */
      else if ( l_result == K_MK_OK )
      {
         /* Lancement de l'application */
         l_result = mk_application_launch ( l_application, K_MK_NULL );

         /* Si aucune erreur ne s'est produite */
         if ( l_result != K_MK_OK )
         {
            /* Affichage d'un message d'erreur dans la console */
            l_result = mk_console_print ( p_console, ( T_str8 ) "Unexpected: could not launch the application.\n\n" );
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
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}

