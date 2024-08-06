/**
*
* @copyright Copyright (C) 2020 RENARD Mathieu. All rights reserved.
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
* @file mk_gpio_setup.c
* @brief Définition de la fonction mk_gpio_setup.
* @date 22 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_gpio_setup ( uint32_t p_port, uint32_t p_pinNumber, T_mkGPIOSetting* p_setting, T_mkCallback* p_callback )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_state = K_MK_STATE_SUSPENDED;

   /* Déclaration de la variable de retour de la requête */
   T_mkCode l_requestResult = K_MK_ERROR_RIGHT;

   /* Déclaration du pointeur de terminal */
   T_mkTermio* l_termio = g_mkTermioHandler.gpio;

   /* Déclaration du pointeur de gestionnaire GPIO */
   T_mkGPIOHandler* l_handler;

   /* Déclaration d'un message GPIO */
   T_mkGPIOMessage l_message = {
         K_MK_GPIO_SETUP,
         p_port,
         p_pinNumber,
         p_setting,
         ( T_mkAddr ) &l_requestResult,
         p_callback
   };

   /* Si le paramètre est valide */
   if ( ( p_setting != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du gestionnaire GPIO */
      l_result = mk_termio_getChild ( l_termio, ( T_mkAddr* ) &l_handler );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_handler != K_MK_NULL ) )
      {
         /* Si une fonction de rappel a été référencée */
         if ( p_callback != K_MK_NULL )
         {
            /* Actualisation de la variable d'état */
            /* La fonction n'est pas bloquante */
            l_state = K_MK_STATE_READY;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Envoi d'un message au terminal GPIO */
         l_result = mk_mail_post ( l_handler->requestArea->request, ( T_mkAddr ) &l_message, l_state, K_MK_TASK_WAIT_FOREVER );

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

