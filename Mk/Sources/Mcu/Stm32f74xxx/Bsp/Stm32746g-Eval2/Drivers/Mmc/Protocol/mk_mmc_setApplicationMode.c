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
* @file mk_mmc_setApplicationMode.c
* @brief Définition de la fonction mk_mmc_setApplicationMode.
* @date 24 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_setApplicationMode ( T_mkMMCHandler* p_handler, T_mkMMCCStatusRegister* p_status, uint32_t p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   T_mkMMCPortStatus l_status = K_MK_MMC_NO_FLAG;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_APP_CMD,               /* Code de la commande */
         p_addr,                                /* Argument de la commande */
         K_MMC_DIRECTION_CONTROLLER_TO_CARD,    /* Direction du transfert */
         0,                                     /* Nombre de données */
         0,                                     /* Timeout du transfert de données */
         K_MMC_SHORT_RESPONSE,                  /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED           /* Bypass CRC désactivé */
   };

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Transmission de la commande (CMD55) */
      l_result = mk_mmc_sendCmd ( p_handler, K_MK_NULL, &l_command, p_status, K_MK_NULL, &l_status );

      /* Si aucune erreur ne s'est produite et si le mode ACMD n'est pas actif */
      /* Note : le paramètre 'p_status' peut être nul lors de l'exécution de cette fonction. */
      if ( ( l_result == K_MK_OK ) && ( p_status != K_MK_NULL ) && ( p_status->appCmd != 1 ) )
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
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}
