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
* @file mk_shell_help.c
* @brief Définition de la fonction mk_shell_help.
* @date 16 mars 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_help ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Prototype de la commande */
   /* help [cmdKeyword] */

   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK, l_localReturn;

   /* Déclaration des variables de travail */
   uint32_t l_counter = 0, l_commandNotFound = 1;

   /* Déclaration d'une table stockant les arguments de la commande */
   T_str8 l_cmdTable [ 9 ] [ 2 ] =
   {
         { ( T_str8 ) "install", ( T_str8 ) MK_SHELL_MESSAGE_INSTALL_HELP_MESSAGE },
         { ( T_str8 ) "uninstall", ( T_str8 ) MK_SHELL_MESSAGE_UNINSTALL_HELP_MESSAGE },
         { ( T_str8 ) "launch", ( T_str8 ) MK_SHELL_MESSAGE_LAUNCH_HELP_MESSAGE },
         { ( T_str8 ) "terminate", ( T_str8 ) MK_SHELL_MESSAGE_TERMINATE_HELP_MESSAGE },
         { ( T_str8 ) "get-apps", ( T_str8 ) MK_SHELL_MESSAGE_GETAPPS_HELP_MESSAGE },
         { ( T_str8 ) "abort", ( T_str8 ) MK_SHELL_MESSAGE_ABORT_HELP_MESSAGE },
         { ( T_str8 ) "cls", ( T_str8 ) MK_SHELL_MESSAGE_CLS_HELP_MESSAGE },
         { ( T_str8 ) "reset", ( T_str8 ) MK_SHELL_MESSAGE_RESET_HELP_MESSAGE },
         { ( T_str8 ) "restart", ( T_str8 ) MK_SHELL_MESSAGE_RESTART_HELP_MESSAGE }

   };

   /* Déclaration d'un pointeur de chaines de caractères */
   T_str8 l_arg = K_MK_NULL;

   /* Bypass de la commande 'help' */
   l_localReturn = mk_application_getArgv ( p_str, &p_str, 0, 0, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

   /* Si aucune erreur ne s'est produite */
   if ( l_localReturn == K_MK_OK )
   {
      /* Récupération de l'adresse de la chaine de caractères contenant le mot clé de la commande */
      l_arg = p_str;

      /* Récupération du mot clé de la commande */
      l_localReturn = mk_application_getArgv ( l_arg, &p_str, p_str, p_cmdLength, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si la commande a été saisie avec un paramètre  */
   if ( l_localReturn == K_MK_OK )
   {
      /* Pour le nombre de commande à afficher */
      for ( l_counter = 0 ; ( l_counter < 9 ) && ( l_commandNotFound == 1 ) ; l_counter++ )
      {
         /* Si le mode d'emploi des commandes applicatives est demandé */
         if ( mk_utils_strcomp ( l_cmdTable [ l_counter ] [ 0 ], l_arg, 0, 0 ) == 1 )
         {
            /* Affichage du mode d'emploi de la commande dans la console */
            l_result = mk_console_print ( p_console, ( T_str8 ) l_cmdTable [ l_counter ] [ 1 ] );

            /* Arrêt de la boucle, l_commande a été trouvée */
            l_commandNotFound = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Si le mode d'emploi des commandes applicatives est demandé */
      if ( l_commandNotFound == 1 )
      {
         /* Affichage d'un message dans la console */
         l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_HELP_LIST );
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
      /* Affichage d'un message dans la console */
      l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_HELP_LIST );
   }

   /* Retour */
   return ( l_result );
}

