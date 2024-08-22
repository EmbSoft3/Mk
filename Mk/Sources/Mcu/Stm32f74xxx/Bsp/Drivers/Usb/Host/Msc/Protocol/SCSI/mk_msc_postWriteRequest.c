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
* @file mk_msc_postWriteRequest.c
* @brief Définition de la fonction mk_msc_postWriteRequest.
* @date 3 janv. 2021
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_postWriteRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToWrite, uint64_t* p_numberOfBytesWrite, uint32_t p_logicalUnitNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des structures de données dédiées au protocole de transport 'Bulk-Only' */
   T_mkMSCCommandBlockWrapper l_wrapper;
   T_mkMSCCommandStatusWrapper* l_status = ( T_mkAddr ) g_mkMSCCommandStatusWrapper;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_WriteRequest l_writeRequest = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_mscDevice != K_MK_NULL ) && ( p_block != K_MK_NULL ) && ( p_numberOfBytesWrite != K_MK_NULL ) && ( p_numberOfBlockToWrite != 0 ) && ( p_logicalUnitNumber < K_MK_MSC_MAX_LUN ) )
   {
      /* Configuration de la requête SCSI */
      l_writeRequest.opcode = K_MK_SCSI_OPCODE_WRITE10;
      l_writeRequest.highTransferLength = ( uint8_t ) ( ( p_numberOfBlockToWrite >> 8 ) & 0xFF );
      l_writeRequest.lowTransferLength = ( uint8_t ) ( p_numberOfBlockToWrite & 0xFF );
      l_writeRequest.highMsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 24 ) & 0xFF );
      l_writeRequest.lowMsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 16 ) & 0xFF );
      l_writeRequest.highLsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 8 ) & 0xFF );
      l_writeRequest.lowLsbLogicalBlockAddress = ( uint8_t ) ( p_block->lowAddr & 0xFF );

      /* Encapsulation de la requête SCSI dans un 'CommandBlockWrapper' */
      l_result = mk_msc_wrap ( &l_wrapper, ( T_mkAddr ) &l_writeRequest, 0x0A, K_MK_MSC_CMD_BLOC_WRAPPER_HOST_TO_DEVICE, ( uint8_t ) p_logicalUnitNumber, ( uint32_t ) ( p_numberOfBlockToWrite * p_block->length ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de la requête sur le bus USB */
         l_result = mk_msc_post ( p_mscDevice, &p_mscDevice->ctrlPipe, &l_wrapper, l_status, p_block->buf );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la requête a réussi intégralement ou partiellement */
      if ( ( l_result == K_MK_OK ) && ( ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED ) || ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_REQUEST_NOT_COMPLETED ) ) )
      {
         /* Actualisation du nombre d'octet lu */
         *p_numberOfBytesWrite = ( uint64_t ) ( ( ( uint64_t ) p_numberOfBlockToWrite * p_block->length ) - l_status->dCSWDataResidue );
      }

      /* Sinon */
      else
      {
         /* Actualisation du nombre d'octet lu */
         *p_numberOfBytesWrite = 0;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
   }

   /* Retour */
   return ( l_result );
}



