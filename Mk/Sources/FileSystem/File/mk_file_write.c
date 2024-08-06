/**
*
* @copyright Copyright (C) 2021 RENARD Mathieu. All rights reserved.
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
* @file mk_file_write.c
* @brief Définition de la fonction mk_file_write.
* @date 6 juin 2021
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_file_write ( T_mkFile* p_file, T_mkAddr p_buf, uint32_t p_numberOfBytesToWrite, uint32_t* p_numberOfBytesWrite, T_mkCallback* p_callback )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_state = K_MK_STATE_SUSPENDED;

   /* Déclaration de la variable de retour de la requête */
   T_mkCode l_requestResult = K_MK_ERROR_UNEXPECTED;

   /* Déclaration d'un message */
   T_mkFileMessage l_message = {
         K_MK_FS_WRITE,
         K_MK_NULL,
         ( T_mkAddr ) p_file,
         ( T_mkAddr ) p_buf,
         ( T_mkAddr ) p_numberOfBytesToWrite,
         ( T_mkAddr ) p_numberOfBytesWrite,
         ( T_mkAddr ) &l_requestResult,
         p_callback
   };

   /* Si les paramètres sont valides */
   if ( ( p_file != K_MK_NULL ) && ( p_numberOfBytesWrite != K_MK_NULL ) )
   {
      /* Si une fonction de rappel a été référencée */
      if ( p_callback != K_MK_NULL )
      {
         /* Actualisation de la variable d'état */
         l_state = K_MK_STATE_READY;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le fichier doit être ouvert en mode partagé */
      if ( p_file->flag.shared == 1 )
      {
         /* Transmission d'un message à la tâche de gestion des fichiers partagés */
         l_result = mk_mail_post ( g_mkFileMessageSharedArea.request, ( T_mkAddr ) &l_message, l_state, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Transmission d'un message aux tâches de gestion des fichiers non partagés */
         l_result = mk_mail_post ( g_mkFileMessageArea.request, ( T_mkAddr ) &l_message, l_state, K_MK_TASK_WAIT_FOREVER );
      }

      /* Si aucune erreur ne s'est produite et si la requête s'est exécutée de manière synchrone */
      if ( ( l_result == K_MK_OK ) && ( p_callback == K_MK_NULL ) )
      {
         /* Ecriture du résultat de la requête dans la variable de retour */
         l_result = l_requestResult;
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




