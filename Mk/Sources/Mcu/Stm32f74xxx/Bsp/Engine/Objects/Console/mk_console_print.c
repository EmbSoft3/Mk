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
* @file mk_console_print.c
* @brief Définition de la fonction mk_console_print.
* @date 30 janv. 2023
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_print ( T_mkConsole* p_console, T_str8 p_str )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_length = 0;

   /* Si les paramètres sont valides */
   if ( ( p_console != K_MK_NULL ) && ( p_console->semaphore != K_MK_NULL ) && ( p_str != K_MK_NULL ) )
   {
      /* Prise du sémaphore */
      l_result = mk_semaphore_take ( p_console->semaphore, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si un fichier a été ouvert */
         if ( p_console->window.file != K_MK_NULL )
         {
            /* Récupération de la longueur de la chaine de caractères */
            l_length = mk_utils_utfsize ( ( T_str8 ) p_str, p_console->foreground.window.style.fontEncoding );

            /* Si la longueur de la chaine est non nulle */
            if ( l_length != 0 )
            {
               /* Ecriture de la chaine dans le fichier */
               l_result = mk_console_writeFile ( p_console, p_console->window.file, p_str, l_length );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Rafraichissement de la boite d'édition */
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
            /* Concaténation de la chaine de caractères dans la boite d'édition */
            l_result = mk_console_strcat ( p_console, p_str );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Déclenchement d'un rafraichissement graphique */
               mk_console_setRefresh ( p_console, K_MK_FIELD_REFRESH_ENABLED );

               /* Actualisation du pointeur de scrolling */
               /* Cette fonction peut être exécutée en parallèle du painter (pas besoin d'allouer une section critique) */
               l_result = mk_editField_handleScrolling ( &p_console->foreground.window );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Libération du sémaphore (sans condition) */
         l_result |= mk_semaphore_release ( p_console->semaphore );
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



