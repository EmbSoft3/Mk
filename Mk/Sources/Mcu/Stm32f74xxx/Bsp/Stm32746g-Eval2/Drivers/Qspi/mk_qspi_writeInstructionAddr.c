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
* @file mk_qspi_writeInstructionAddr.c
* @brief Définition de la fonction mk_qspi_writeInstructionAddr.
* @date 9 août 2024
*
*/

#include "mk_qspi_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_qspi_writeInstructionAddr ( uint32_t p_instruction, uint32_t p_addr, uint32_t p_mode )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération du statut du périphérique */
    uint32_t l_ret = qspi_getStatus ( K_QSPI_BUSY_STATUS );

   /* Si aucune opération n'est en cours */
   if ( l_ret == K_QSPI_IDLE )
   {
      /* Configuration du nombre de données à récupérer */
      qspi_setTransferSize ( 0 );

      /* Si la transmission de l'instruction est en mode 'SINGLE' */
      if ( p_mode == K_MK_QSPI_MODE_SINGLE )
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_SINGLE_MODE, K_QSPI_ADDRESS_SINGLE_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Sinon si la transmission de l'instruction est en mode 'DUAL' */
      else if ( p_mode == K_MK_QSPI_MODE_DUAL )
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_DUAL_MODE, K_QSPI_ADDRESS_DUAL_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Sinon (mode QUAD) */
      else
      {
         /* Transmission de l'instruction 'WriteEnable' */
         qspi_write ( K_QSPI_SDR_MODE, K_MK_MICRON_N25Q512A_REGISTER_DUMMY_CYCLE, p_instruction |
                      K_QSPI_INSTRUCTION_QUAD_MODE, K_QSPI_ADDRESS_QUAD_MODE | K_QSPI_ADDRESS_SIZE_32BITS,
                      K_QSPI_ALTERNATE_BYTES_NO_LINE_MODE | K_QSPI_ALTERNATE_BYTES_SIZE_8BITS, K_QSPI_DATA_NO_LINE_MODE );
      }

      /* Configuration de l'adresse QSPI */
      /* L'instruction est envoyée sur le bus suite à l'écriture du registre. */
      qspi_writeAddress ( p_addr );

      /* Attendre tant que le nombre d'octets demandés n'a pas été reçu */
      l_result = mk_qspi_wait ( );

      /* Si l'opération a échoué */
      if ( l_result != K_MK_OK )
      {
         /* Arrêt du transfert */
         ( void ) mk_qspi_abort ( );
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
      l_result = K_MK_ERROR_NOT_AVAILABLE;
   }

   /* Réinitialisation du drapeau indiquant la fin du transfert */
   qspi_clearStatus ( K_QSPI_TRANSFER_COMPLETE_STATUS );

   /* Réinitialisation du drapeau indiquant une erreur de transfert */
   qspi_clearStatus ( K_QSPI_TRANSFER_ERROR_STATUS );

   /* Retour */
   return ( l_result );
}


