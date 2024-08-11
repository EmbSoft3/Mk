/**
*
* @copyright Copyright (C) 2024 RENARD Mathieu. All rights reserved.
*
* This file is part of mk.
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
* @file mk_qspi_erase.c
* @brief Définition de la fonction mk_qspi_erase.
* @date 9 août 2024
*
*/

#include "mk_qspi_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_erase ( uint32_t p_mode, uint32_t p_addr )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_counter = 0;

   /* Déclaration d'un registre de statut */
   T_MicronN25Q512A_StatusRegister l_statusRegister = { 0 };

   /* Autorisation d'une écriture */
   l_result = mk_qspi_writeInstruction ( K_MK_MICRON_N25Q512A_OPCODE_WRITE_ENABLE, p_mode );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Ecriture de l'instruction sur le bus QSPI */
      l_result = mk_qspi_writeInstructionAddr ( K_MK_MICRON_N25Q512A_OPCODE_SECTOR_ERASE, p_addr, p_mode );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Effectue */
      do
      {
         /* Lecture du registre de statut pour savoir si l'écriture est terminée */
         l_result = mk_qspi_readRegister ( &l_statusRegister, K_MK_MICRON_N25Q512A_OPCODE_READ_STATUS, 1, p_mode );

         /* Attente */
         mk_utils_waitus ( 100 );

         /* Actualisation d'un compteur */
         l_counter = ( uint32_t ) ( l_counter + 1 );

      /* Tant que le secteur est en cours d'effacement */
      } while ( ( l_statusRegister.field.writeInProgress == 1 ) && ( l_counter < K_MK_MICRON_N25Q512A_MEMORY_TIMEOUT ) );

      /* Si un timeout s'est produit */
      if ( l_statusRegister.field.writeInProgress == 1 )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_TIMEOUT;
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

   /* Retour */
   return ( l_result );
}
