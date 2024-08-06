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
* @file mk_shell_application_launch.c
* @brief Définition de la fonction mk_shell_application_launch.
* @date 15 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_application_launch ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Prototype de la commande */
   /* launch pid */

   /* Déclaration des variables de retour */
   T_mkCode l_result = K_MK_OK, l_localReturn;

   /* Déclaration d'une variable de travail */
   uint32_t l_id = 0;

   /* Déclaration d'un pointeur de chaines de caractères */
   T_str8 l_arg = K_MK_NULL;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = K_MK_NULL;

   /* Bypass de la commande 'launch' */
   l_localReturn = mk_application_getArgv ( p_str, &p_str, 0, 0, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

   /* Si aucune erreur ne s'est produite */
   if ( l_localReturn == K_MK_OK )
   {
      /* Récupération de l'adresse de la chaine de caractères contenant l'identifiant de l'application */
      l_arg = p_str;

      /* Détermination de l'adresse du prochain argument */
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
      /* Conversion du PID de l'application en entier */
      l_id = ( uint32_t ) mk_utils_atoi ( ( T_str8 ) l_arg, 10 );

      /* Récupération de l'adresse de l'application demandée par l'utilisateur */
      l_application = mk_application_getById ( l_id );

      /* Si l'application a été trouvée */
      if ( l_application != K_MK_NULL )
      {
         /* Si l'application a été installée et n'est pas déjà en cours d'exécution */
         if ( l_application->state == K_MK_APPLICATION_STATE_INSTALLED )
         {
            /* Démarrage de l'application */
            l_result = mk_application_launch ( l_application, K_MK_NULL );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Affichage d'un message dans la console */
               l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_LAUNCH_SUCCEES );
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
            l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_LAUNCH_ALREADY_RUNNING );
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

   /* Si une erreur s'est produite */
   if ( ( l_result == K_MK_OK ) && ( ( l_localReturn == K_MK_ERROR_NOT_AVAILABLE ) || ( l_application == K_MK_NULL ) ) )
   {
      /* Affichage d'un message d'erreur dans la console */
      l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_LAUNCH_APP_NOT_FOUND );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


