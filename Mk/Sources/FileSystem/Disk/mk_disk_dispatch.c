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
* @file mk_disk_dispatch.c
* @brief Définition de la fonction mk_disk_dispatch.
* @date 14 juil. 2020
*
*/

#include "mk_file_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_disk_dispatch ( T_mkDisk* p_disk, uint16_t p_ctrlEvt )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un message */
   T_mkDispatcherMessage l_message;

   /* Déclaration d'un pointeur de gestionnaire (dispatcher) */
   T_mkDispatcherHandler* l_dispatcherHandler = K_MK_NULL;

   /* Si le paramètre est valide */
   if ( p_disk != K_MK_NULL )
   {
      /* Récupération de l'adresse du dispatcher */
      l_result = mk_termio_getChild ( g_mkTermioHandler.dispatcher, ( void** ) &l_dispatcherHandler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Pré-configuration du message */
         l_message.ctrlEvt = p_ctrlEvt;
         l_message.tick = mk_getTick ( );

         /* Si un message concernant un disque est à transmettre */
         if ( p_disk != K_MK_NULL )
         {
            /* Configuration de l'adresse du contrôle applicatif */
            l_message.appCtrl = p_disk;

            /* Etant donné que la priorité du dispatcher est supérieure à la priorité des terminaux, les informations */
            /* du contrôle peuvent être transmise par référence. Il n'est pas nécessaire de transmettre une copie de */
            /* l'attribut. */

            /* Transmission d'un message */
            l_result = mk_mail_post ( l_dispatcherHandler->mailArea->mail, ( T_mkAddr ) &l_message, K_MK_STATE_READY, K_MK_TASK_WAIT_FOREVER );
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


