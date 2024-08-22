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
* @file mk_console_gets.c
* @brief Définition de la fonction mk_console_gets.
* @date 18 mai 2023
* @todo Tester cette fonction (surement nécessité de configurer le pointeur de fonction) et adapter là pour
*       gérer l'absence de fichiers attribué à la console (cf. mk_console_strcat).
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_console_gets ( T_mkConsole* p_console, T_str8 p_str, uint32_t p_length )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_numberOfBytesRead = 0;

   /* Si les paramètres sont valides */
   if ( ( p_console != K_MK_NULL ) && ( p_console->semaphore != K_MK_NULL ) && ( p_console->prompt.file != K_MK_NULL ) && ( p_str != K_MK_NULL ) && ( p_length > 1 ) )
   {
      /* Prise du sémaphore */
      l_result = mk_semaphore_take ( p_console->semaphore, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Lecture de la chaine de caractères dans le fichier d'entrée */
         l_result = mk_file_read ( p_console->prompt.file, p_str, ( p_length - 1 ), &l_numberOfBytesRead, K_MK_NULL );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Ajout du caractère de fin */
            p_str [ l_numberOfBytesRead ] = 0;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
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


