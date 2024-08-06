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
* @file mk_mmc_read.c
* @brief Définition de la fonction mk_mmc_read.
* @date 7 févr. 2021
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_read ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, T_mkCallback* p_callback )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_state = K_MK_STATE_SUSPENDED;

   /* Déclaration de la variable de retour de la requête */
   T_mkCode l_requestResult = K_MK_ERROR_RIGHT;

   /* Déclaration d'un pointeur de gestionnaire MMC */
   T_mkMMCHandler* l_handler = K_MK_NULL;

   /* Déclaration d'un message MMC */
   T_mkDiskRequest l_message = {
         K_MK_DISK_IO_READ,
         p_disk,
         p_buf,
         ( uint32_t ) ( p_blockAddress ),
         ( uint32_t ) ( p_blockAddress >> 32 ),
         p_numberOfBlockToRead,
         ( uint32_t* ) ( p_numberOfBytesRead ),
         K_MK_NULL,
         ( T_mkAddr ) &l_requestResult,
         p_callback
   };

   /* Si les paramètres sont valides */
   if ( ( p_disk != K_MK_NULL ) && ( p_numberOfBytesRead != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du gestionnaire MMC */
      l_result = mk_termio_getChild ( g_mkTermioHandler.mmc, ( T_mkAddr* ) &l_handler );

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

         /* Envoi d'un message au terminal MMC */
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

