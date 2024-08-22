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
* @file mk_msc_postReadRequest.c
* @brief Définition de la fonction mk_msc_postReadRequest.
* @date 24 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_postReadRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSIBlock* p_block, uint16_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead, uint32_t p_logicalUnitNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des structures de données dédiées au protocole de transport 'Bulk-Only' */
   T_mkMSCCommandBlockWrapper l_wrapper;
   T_mkMSCCommandStatusWrapper* l_status = ( T_mkAddr ) g_mkMSCCommandStatusWrapper;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_ReadRequest l_readRequest = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_mscDevice != K_MK_NULL ) && ( p_block != K_MK_NULL ) && ( p_numberOfBytesRead != K_MK_NULL ) && ( p_numberOfBlockToRead != 0 ) && ( p_logicalUnitNumber < K_MK_MSC_MAX_LUN ) )
   {
      /* Configuration de la requête SCSI */
      l_readRequest.opcode = K_MK_SCSI_OPCODE_READ10;
      l_readRequest.highTransferLength = ( uint8_t ) ( ( p_numberOfBlockToRead >> 8 ) & 0xFF );
      l_readRequest.lowTransferLength = ( uint8_t ) ( p_numberOfBlockToRead & 0xFF );
      l_readRequest.highMsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 24 ) & 0xFF );
      l_readRequest.lowMsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 16 ) & 0xFF );
      l_readRequest.highLsbLogicalBlockAddress = ( uint8_t ) ( ( p_block->lowAddr >> 8 ) & 0xFF );
      l_readRequest.lowLsbLogicalBlockAddress = ( uint8_t ) ( p_block->lowAddr & 0xFF );

      /* Encapsulation de la requête SCSI dans un 'CommandBlockWrapper' */
      l_result = mk_msc_wrap ( &l_wrapper, ( T_mkAddr ) &l_readRequest, 0x0A, K_MK_MSC_CMD_BLOC_WRAPPER_DEVICE_TO_HOST, ( uint8_t ) p_logicalUnitNumber, ( uint32_t ) ( p_numberOfBlockToRead * p_block->length ) );

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
         /* Actualisation du nombre d'octets lus */
         *p_numberOfBytesRead = ( uint64_t ) ( ( ( uint64_t ) p_numberOfBlockToRead * p_block->length ) - l_status->dCSWDataResidue );
      }

      /* Sinon */
      else
      {
         /* La commande a échoué. Le nombre d'octets lus est nul */
         *p_numberOfBytesRead = 0;
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



