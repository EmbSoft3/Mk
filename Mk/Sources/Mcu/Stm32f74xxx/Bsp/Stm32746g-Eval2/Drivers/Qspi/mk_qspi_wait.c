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
* @file mk_qspi_wait.c
* @brief Définition de la fonction mk_qspi_wait.
* @date 9 août 2024
*
*/

#include "mk_qspi_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_wait ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration de la variable de retour locale */
   uint32_t l_ret;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0;

   /* Effectue */
   do
   {
      /* Récupération du statut du FIFO */
      l_ret = qspi_getStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

      /* Actualisation du compteur */
      l_counter++;

   /* Tant que le nombre d'octets demandés n'a pas été reçu */
   } while ( ( l_ret != K_QSPI_TRANSFER_COMPLETE ) && ( l_counter < K_MK_MICRON_N25Q512A_TIMEOUT ) );

   /* Si une erreur s'est produite */
   if ( l_ret != K_QSPI_TRANSFER_COMPLETE )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_TIMEOUT;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}


