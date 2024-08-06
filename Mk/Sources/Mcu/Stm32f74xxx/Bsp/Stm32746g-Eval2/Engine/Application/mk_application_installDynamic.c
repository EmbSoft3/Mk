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
* @file mk_application_installDynamic.c
* @brief Définition de la fonction mk_application_installDynamic.
* @date 3 janv. 2024
*
*/

#include "mk_engine_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_application_installDynamic ( T_mkApplication** p_application, T_str8 p_filePath, T_str8 p_cmdLineParam, T_mkVolume* p_volume, T_mkCallback* p_callback )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   T_mkCode l_requestResult = K_MK_ERROR_UNEXPECTED;

   /* Déclaration d'un message */
   T_mkDisplayRequest l_request = { K_MK_DISPLAY_REQUEST_TYPE_APPLICATION, {
         { K_MK_DISPLAY_REQUEST_APPLICATION_INSTALL, { 0, 0, 0, 0 }, { { 0 } } } } };

   /* Si le paramètre est valide */
   if ( ( p_application != K_MK_NULL ) && ( p_filePath != K_MK_NULL ) )
   {
      /* Réinitialisation du descripteur */
      _writeWords ( &l_request.content.application.content.descriptor, 0, sizeof ( T_mkApplicationDescriptor ) >> 2 );

      /* Initialisation des champs de la requête */
      l_request.content.application.application = ( T_mkAddr ) p_application;
      l_request.content.application.result = &l_requestResult;
      l_request.content.application.callback = p_callback;
      l_request.content.application.content.volume = p_volume;
      l_request.content.application.content.path = p_filePath;
      l_request.content.application.content.descriptor.arg = p_cmdLineParam;
      l_request.content.application.content.addr = K_MK_NULL;

      /* Si une fonction de rappel a été référencée */
      if ( p_callback != K_MK_NULL )
      {
         /* Transmission d'un message au gestionnaire */
         /* La fonction n'est pas bloquante */
         l_result = mk_mail_post ( g_mkDisplay.handler.mail, ( T_mkAddr ) &l_request, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
      }

      /* Sinon */
      else
      {
         /* Transmission d'un message au gestionnaire */
         /* La fonction est bloquante */
         l_result = mk_mail_post ( g_mkDisplay.handler.mail, ( T_mkAddr ) &l_request, K_MK_STATE_SUSPENDED, K_MK_TASK_WAIT_FOREVER );
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



