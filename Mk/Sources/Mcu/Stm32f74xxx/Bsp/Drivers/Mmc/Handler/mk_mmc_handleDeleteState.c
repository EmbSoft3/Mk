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
* @file mk_mmc_handleDeleteState.c
* @brief Définition de la fonction mk_mmc_handleDeleteState.
* @date 18 sept. 2021
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_handleDeleteState ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphérique SD/MMC. */
   T_mkMMCDevice* l_device;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Actualisation de l'adresse du périphérique courant */
      p_handler->current = K_MK_NULL;

      /* Si au moins un périphérique est présent sur le bus */
      if ( p_handler->list.first != K_MK_NULL )
      {
         /* Pour chaque périphériques SD/MMC présents sur le bus */
         for ( l_device = p_handler->list.first ; l_device != K_MK_NULL ; l_device = l_device->next )
         {
            /* Suppression du périphérique */
            l_result |= mk_mmc_deleteDevice ( p_handler, l_device, 1 );
         }

         /* Actualisation de l'état du bus */
         p_handler->state = K_MK_MMC_STATE_DISCONNECTED;
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'état du bus */
         p_handler->state = K_MK_MMC_STATE_INACTIVE;
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
