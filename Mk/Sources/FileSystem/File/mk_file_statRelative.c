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
* @file mk_file_statRelative.c
* @brief Définition de la fonction mk_file_statRelative.
* @date 7 avr. 2024
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_file_statRelative ( T_mkVolume* p_volume, T_str8 p_directoryPath, T_str8 p_filePath, T_mkCallback* p_callback )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_state = K_MK_STATE_SUSPENDED;

   /* Déclaration de la variable de retour de la requête */
   T_mkCode l_requestResult = K_MK_ERROR_UNEXPECTED;

   /* Déclaration d'un message */
   T_mkFileMessage l_message = {
         K_MK_FS_STAT,
         ( T_mkAddr ) p_volume,
         K_MK_NULL,
         ( T_mkAddr ) p_directoryPath,
         ( T_mkAddr ) p_filePath,
         K_MK_NULL,
         ( T_mkAddr ) &l_requestResult,
         p_callback
   };

   /* Si les paramètres sont valides */
   if ( ( p_filePath != K_MK_NULL ) && ( p_directoryPath != K_MK_NULL ) )
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

      /* Transmission d'un message */
      l_result = mk_mail_post ( g_mkFileMessageArea.request, ( T_mkAddr ) &l_message, l_state, K_MK_TASK_WAIT_FOREVER );

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




