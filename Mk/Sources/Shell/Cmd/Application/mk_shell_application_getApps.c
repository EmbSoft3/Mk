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
* @file mk_shell_application_getApps.c
* @brief Définition de la fonction mk_shell_application_getApps.
* @date 15 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_application_getApps ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Prototype de la commande */
   /* get-apps [apps-id] */

   /* Déclaration des variables de retour */
   T_mkCode l_result = K_MK_OK, l_localReturn;

   /* Déclaration d'un pointeur d'application */
   T_mkApplication* l_application = mk_application_getFirst ( );

   /* Déclaration d'un pointeur de chaines de caractères */
   T_str8 l_arg = K_MK_NULL;

   /* Déclaration d'un buffer stockant le nom des applications */
   char8_t l_baseStr [ 56 ] = "\n\t[PID-000]\t[DYN]\tDefault Program Name             [..]", l_currentStr [ 56 ] = { 0 }, l_pid [ 4 ] = { 0 };

   /* Déclaration des variables de travail */
   uint32_t l_show = 0, l_id = 0, l_length = 0;

   /* Bypass de la commande 'apps' */
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
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Parcours de la liste d'applications */
   while ( ( l_result == K_MK_OK ) && ( l_application != K_MK_NULL ) )
   {
      /* Si les données relatives à l'application en cours d'analyse doivent être affichées */
      if ( ( l_localReturn == K_MK_ERROR_NOT_AVAILABLE ) || ( l_application->layer.id == l_id ) )
      {
         /* Copie du modèle de chaine de caractères dans la variable de travail  */
         _copy ( l_currentStr, l_baseStr, 43 );

         /* Conversion du PID de l'application en chaine de caractères */
         mk_utils_itoa ( l_application->layer.id, ( T_str8 ) l_pid, 10, 3 );

         /* Configuration du type de l'application */
         _copy ( &l_currentStr [ 7 ], l_pid, 3 );

         /* Si l'application est de type statique */
         if ( ( l_application->descriptor.type & K_MK_APPLICATION_TYPE_DYNAMIC ) == K_MK_APPLICATION_TYPE_STATIC )
         {
            /* Le nom de l'application doit pointer sur la métadonnée 'name' */
            l_arg = l_application->metadata.name;

            /* Configuration du type de l'application */
            _copy ( &l_currentStr [ 13 ], ( T_str8 ) "STA", 3 );
         }

         /* Sinon */
         else
         {
            /* Le nom de l'application doit pointer sur le fichier 'elf' */
            l_arg = l_application->dynamic.fileName;
         }

         /* Récupération de la longeur du nom de l'application */
         l_length = mk_utils_utfsize ( l_arg, K_MK_FONT_UTF8 );

         /* Si le nom est trop long, on copie juste une portion dans le buffer */
         if ( l_length > 32 )
         {
            /* Copie du nom de l'application dans le buffer */
            /* Le caractère de fin de chaine est déjà présent dans la chaine de base */
            _copy ( &l_currentStr [ 18 ], l_arg, 32 );
         }

         /* Sinon */
         else
         {
            /* On copie la totalité du nom */
            _copy ( &l_currentStr [ 18 ], l_arg, l_length );
            /* Ecriture du caractère de fin de chaine */
            l_currentStr [ 18 + l_length ] = 0;
         }

         /* Basculement de la variable 'l_show' afin d'indiquer qu'au moins une application */
         /* a été affichée */
         l_show = 1;

         /* Affichage d'un message dans la console */
         l_result = mk_console_puts ( p_console, ( T_str8 ) l_currentStr );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Passage à la prochaine application */
      l_application = l_application->next;
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si aucune application n'a été affichée */
      if ( l_show == 0 )
      {
         /* Affichage d'un message d'erreur dans la console et déclenchement d'un rafraichissement graphique */
         l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_GETAPPS_APP_NOT_FOUND );
      }

      /* Sinon */
      else
      {
         /* Ajout d'un saut de ligne et déclenchement d'un rafraichissement graphique */
         l_result = mk_console_print ( p_console, ( T_str8 ) "\n\n" );
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



