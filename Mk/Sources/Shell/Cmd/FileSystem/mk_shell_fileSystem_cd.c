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
* @file mk_shell_fileSystem_cd.c
* @brief Définition de la fonction mk_shell_fileSystem_cd.
* @date 15 avr. 2024
*
*/

#include "mk_shell_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_shell_fileSystem_handleSpecialCharacters ( T_str8 p_path, T_mkFontUnicode p_font )
{
   /* Déclaration d'une variable stockant le nombre de répertoires dans le chemin */
   uint32_t l_numberOfDirectory = 0;

   /* Déclaration des variables de travail */
   uint32_t l_length = 0, l_counter = 0, l_tmp = 0;
   T_str8 l_previous = K_MK_NULL, l_current = K_MK_NULL, l_next = K_MK_NULL;

   /* Récupération du nombre de répertoires dans le chemin */
   l_numberOfDirectory = mk_utils_utfcount ( p_path, '/', ( uint32_t ) p_font );

   /* Si au moins 3 répertoires sont présents dans le chemin (/dsk0/vol0/<path>) */
   if ( l_numberOfDirectory > 3 )
   {
      /* Actualisation du nombre de répertoires */
      l_numberOfDirectory = ( uint32_t ) ( l_numberOfDirectory - 1 );

      /* Configuration des 3 pointeurs de chaines */
      /* l_previous = "dsk0", l_current = "vol0", l_next = "<path>" or "" */
      l_previous = ( T_str8 ) ( mk_utils_utfchr ( p_path, '/', ( uint32_t ) p_font ) + 1 );
      l_current = ( T_str8 ) ( mk_utils_utfchr ( l_previous, '/', ( uint32_t ) p_font ) + 1 );
      l_next = ( T_str8 ) ( mk_utils_utfchr ( l_current, '/', ( uint32_t ) p_font ) + 1 );

      /* Parcours de la chaine de caractères afin de supprimer les caractères '.' et '..' */
      while ( l_counter < l_numberOfDirectory )
      {
         /* Si le répertoire 'current' pointe sur le répertoire actuel ('.') */
         if ( ( l_current [ 0 ] == '.' ) && ( l_current [ 1 ] == '/' ) )
         {
            /* Le répertoire 'next' devient le répertoire 'current' */
            _copy ( l_current, l_next, mk_utils_utfsize ( l_next, ( uint32_t ) p_font ) + 1 );

            /* Les pointeurs 'current' et 'previous' restent identiques. */
            l_next = ( T_str8 ) ( mk_utils_utfchr ( l_current, '/', ( uint32_t ) p_font ) + 1 );
         }

         /* Sinon si le répertoire 'current' pointe sur le répertoire actuel ('.') et si le répertoire 'current' */
         /* est le dernier de la chaine. */
         else if ( ( l_current [ 0 ] == '.' ) && ( l_current [ 1 ] == '\0' ) )
         {
            /* Arrêt de la chaine */
            l_current [ 0 ] = '\0';
         }

         /* Sinon si le répertoire 'current' pointe sur le répertoire précédent ('..') */
         else if ( ( l_current [ 0 ] == '.' ) && ( l_current [ 1 ] == '.' ) && ( l_current [ 2 ] == '/' ) )
         {
            /* Le répertoire 'previous' devient le répertoire 'next' */
            _copy ( l_previous, l_next, mk_utils_utfsize ( l_next, ( uint32_t ) p_font ) + 1 );

            /* Il faut recalculer l'offset des pointeurs 'previous', 'current' et 'next' */
            l_current = l_previous;
            l_next = ( T_str8 ) ( mk_utils_utfchr ( l_current, '/', ( uint32_t ) p_font ) + 1 );
            l_previous = p_path;
            /* On parcours la chaine depuis le début pour trouver l'offset du pointeur previous */
            for ( l_tmp = 0 ; l_tmp < l_length ; l_tmp++ )
            {
               l_previous = ( T_str8 ) ( mk_utils_utfchr ( l_previous, '/', ( uint32_t ) p_font ) + 1 );
            }

            /* Actualisation du nombre de répertoires analysés */
            l_length = ( uint32_t ) ( l_length - 1 );
         }

         /* Sinon si le répertoire 'current' pointe sur le répertoire précédent ('..') et si le répertoire 'current' */
         /* est le dernier de la chaine. */
         else if ( ( l_current [ 0 ] == '.' ) && ( l_current [ 1 ] == '.' ) && ( l_current [ 2 ] == '\0' ) )
         {
            /* Arrêt de la chaine */
            l_previous [ 0 ] = '\0';
         }

         /* Sinon */
         else
         {
            /* Actualisation du nombre de répertoires analysés */
            l_length = ( uint32_t ) ( l_length + 1 );

            /* Actualisation des pointeurs (glissement) */
            l_previous = l_current;
            l_current = l_next;
            l_next = ( T_str8 ) ( mk_utils_utfchr ( l_next, '/', ( uint32_t ) p_font ) + 1 );
         }

         /* Actualisation du nombre de répertoires analysés */
         l_counter = ( uint32_t ) ( l_counter + 1 );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Récupération de la longueur de la chaine de caractères */
   l_length = mk_utils_utfsize ( p_path, ( uint32_t ) p_font );

   /* Tant que le dernier caractère de la chaine est le caractère '/' */
   while ( ( l_length != 0 ) && ( p_path [ l_length - 1 ] == '/' ) )
   {
      /* Suppression du caractère '/' */
      p_path [ l_length - 1 ] = '\0';
      l_length = ( uint32_t ) ( l_length - 1 );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_shell_fileSystem_cd ( T_mkShell* p_shell, T_mkConsole* p_console, T_str8 p_str, uint32_t p_cmdLength )
{
   /* Prototype de la commande */
   /* cd path */

   /* Déclaration des variables de retour */
   T_mkCode l_result = K_MK_OK, l_localReturn;

   /* Déclaration des variables de travail */
   uint32_t l_currentDirectoryLength = 0, l_pathLength = 0, l_type = 0;

   /* Déclaration d'une instance de fichiers */
   T_mkFile* l_file = K_MK_NULL;

   /* Déclaration d'une variable stockant le chemin du répertoire à accéder */
   T_str8 l_directoryPath = K_MK_NULL;

   /* Déclaration d'une variable stockant le chemin du répertoire à accéder */
   uint8_t l_path [ K_MK_FILE_MAX_NAME_LENGTH + 1 ] = { 0 };

   /* Bypass de la commande 'cd' */
   l_localReturn = mk_application_getArgv ( p_str, &p_str, 0, 0, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

   /* Si aucune erreur ne s'est produite */
   if ( l_localReturn == K_MK_OK )
   {
      /* Récupération de l'adresse de la chaine de caractères contenant le chemin du répertoire à accéder */
      l_directoryPath = p_str;

      /* Détermination de l'adresse du prochain argument */
      l_localReturn = mk_application_getArgv ( l_directoryPath, &p_str, p_str, p_cmdLength, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

      /* Si aucun paramètre n'est présent */
      if ( l_localReturn == K_MK_ERROR_NOT_AVAILABLE )
      {
         /* Affichage d'un message d'erreur dans la console */
         l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_CMD_LINE );
      }

      /* Sinon */
      else
      {
         /* Suppression des guillements de part et d'autre du chemin (si présent) */
         l_directoryPath = mk_shell_removeDoubleQuote ( l_directoryPath, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_localReturn == K_MK_OK ) && ( l_directoryPath != K_MK_NULL ) )
   {
      /* Si le chemin d'accès au répertoire est un chemin absolue */
      if ( l_directoryPath [ 0 ] == '/' )
      {
         /* Gestion des caractères spéciaux '.' et '..' */
         mk_shell_fileSystem_handleSpecialCharacters ( l_directoryPath, p_console->foreground.prompt.style.fontEncoding );

         /* Ouverture du répertoire */
         l_result = mk_file_open ( K_MK_NULL, &l_file, l_directoryPath, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );

         /* Si le répertoire existe */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du type du fichier */
            l_result = mk_file_getType ( l_file, &l_type, K_MK_NULL );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Si le fichier est un répertoire */
               if ( l_type == K_MK_FS_TYPE_DIRECTORY )
               {
                  /* Actualisation de la valeur du répertoire courant */
                  _copy ( p_shell->currentDirectory, l_directoryPath, K_MK_FILE_MAX_NAME_LENGTH + 1 );
               }

               /* Sinon */
               else
               {
                  /* Affichage d'un message d'erreur dans la console */
                  l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_NOT_DIRECTORY );
               }
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
            /* Affichage d'un message d'erreur dans la console */
            l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_DIRECTORY_NOT_FOUND );
         }
      }

      /* Sinon (chemin relatif) */
      else
      {
         /* Récupération de la longueur des chaines de caractères [en octets] */
         /* CurrentDirectory et Path */
         l_currentDirectoryLength = mk_utils_utfsize ( ( T_str8 ) p_shell->currentDirectory, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );
         l_pathLength = mk_utils_utfsize ( l_directoryPath, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

         /* Si la longueur cumulée des chaines de caractères est valides (+1 pour le caractère '/') */
         if ( ( l_currentDirectoryLength + l_pathLength + 1 ) < K_MK_FILE_MAX_NAME_LENGTH )
         {
            /* Création d'un chemin absolu */
            _copy ( &l_path [ 0 ], &p_shell->currentDirectory [ 0 ], l_currentDirectoryLength );
            _copy ( &l_path [ l_currentDirectoryLength ], ( T_str8 ) "/", 1 );
            _copy ( &l_path [ l_currentDirectoryLength + 1 ], l_directoryPath, l_pathLength + 1 );

            /* Gestion des caractères spéciaux '.' et '..' */
            mk_shell_fileSystem_handleSpecialCharacters ( ( T_str8 ) l_path, p_console->foreground.prompt.style.fontEncoding );

            /* Ouverture du répertoire */
            l_result = mk_file_open ( K_MK_NULL, &l_file, ( T_str8 ) l_path, K_MK_FS_OPEN_EXISTING | K_MK_FS_OPEN_READ, K_MK_NULL );

            /* Si le répertoire existe */
            if ( l_result == K_MK_OK )
            {
               /* Récupération du type du fichier */
               l_result = mk_file_getType ( l_file, &l_type, K_MK_NULL );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Si le fichier est un répertoire */
                  if ( l_type == K_MK_FS_TYPE_DIRECTORY )
                  {
                     /* Récupération de la longueur du chemin */
                     l_pathLength = mk_utils_utfsize ( ( T_str8 ) l_path, ( uint32_t ) p_console->foreground.prompt.style.fontEncoding );

                     /* Actualisation de la valeur du répertoire courant */
                     _copy ( &p_shell->currentDirectory, l_path, l_pathLength + 1 );
                  }

                  /* Sinon */
                  else
                  {
                     /* Affichage d'un message d'erreur dans la console */
                     l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_NOT_DIRECTORY );
                  }
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
               /* Affichage d'un message d'erreur dans la console */
               l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_DIRECTORY_NOT_FOUND );
            }
         }

         /* Sinon */
         else
         {
            /* Affichage d'un message d'erreur dans la console */
            l_result = mk_console_print ( p_console, ( T_str8 ) MK_SHELL_MESSAGE_FILESYSTEM_CD_INVALID_PATH_LENGTH );
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




