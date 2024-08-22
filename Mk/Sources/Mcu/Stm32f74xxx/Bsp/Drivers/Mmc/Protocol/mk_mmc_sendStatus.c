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
* @file mk_mmc_sendStatus.c
* @brief Définition de la fonction mk_mmc_sendStatus.
* @date 1 juil. 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_sendStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCExtendedStatus* p_status )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t* l_status = ( uint32_t* ) &p_device->status;

   /* Memorisation de la taille des blocs de données de la carte */
   uint32_t l_blockLength = p_device->layer.blockLength;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_SEND_STATUS,                 /* Code de la commande */
         0,                                           /* Argument de la commande */
         K_MMC_DIRECTION_CARD_TO_CONTROLLER,          /* Direction du transfert */
         ( 1 << K_MK_MMC_STATUS_BLOCK_SIZE ),         /* Nombre de données */
         K_MK_MMC_TIMEOUT,                            /* Timeout du transfert de données */
         K_MMC_SHORT_RESPONSE,                        /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED                 /* Bypass CRC désactivé */
   };

   /* Si les paramètres sont valides et si le périphérique est sélectionné */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_status != K_MK_NULL ) && ( p_device == p_handler->current ) )
   {
      /* Configuration de la taille du bloc de données */
      p_device->layer.blockLength = K_MK_MMC_STATUS_BLOCK_SIZE;

      /* Activation du mode applicatif (ACMD) */
      l_result = mk_mmc_setApplicationMode ( p_handler, &p_device->status, p_device->layer.addr );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( ( ( *l_status ) & K_MK_MMC_ERROR_MASK ) == 0 ) )
      {
         /* Transmission de la commande (ACMD13) */
         l_result = mk_mmc_sendCmd ( p_handler, p_device, &l_command, &p_device->status, p_status, &p_device->portStatus );

         /* Si une erreur est remontée par la carte */
         if ( ( l_result == K_MK_OK ) && ( ( ( *l_status ) & K_MK_MMC_ERROR_MASK ) > 0 ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_COMM;
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
         l_result = K_MK_ERROR_COMM;
      }

      /* Configuration de la taille du bloc de données */
      p_device->layer.blockLength = l_blockLength;
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



