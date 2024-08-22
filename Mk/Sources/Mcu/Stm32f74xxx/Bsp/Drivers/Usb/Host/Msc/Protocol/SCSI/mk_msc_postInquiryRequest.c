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
* @file mk_msc_postInquiryRequest.c
* @brief Définition de la fonction mk_msc_postInquiryRequest.
* @date 20 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_postInquiryRequest ( T_mkMSCDevice* p_mscDevice, T_mkSCSI_InquiryPacket** p_inquiryPacket, uint32_t p_logicalUnitNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des structures de données dédiées au protocole de transport 'Bulk-Only' */
   T_mkMSCCommandBlockWrapper l_wrapper;
   T_mkMSCCommandStatusWrapper* l_status = ( T_mkAddr ) g_mkMSCCommandStatusWrapper;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_InquiryRequest l_inquiryRequest = { 0 };

   /* Si les paramètres sont valides */
   if ( ( p_mscDevice != K_MK_NULL ) && ( p_inquiryPacket != K_MK_NULL ) && ( p_logicalUnitNumber < K_MK_MSC_MAX_LUN ) )
   {
      /* Ecriture de l'adresse du buffer de réception dans le pointeur de retour */
      *p_inquiryPacket = ( T_mkAddr ) ( g_mkMSCPacketBuf );

      /* Configuration de la requête SCSI */
      l_inquiryRequest.opcode = K_MK_SCSI_OPCODE_INQUIRY;
      l_inquiryRequest.lsbLength = 0x24;

      /* Encapsulation de la requête SCSI dans un 'CommandBlockWrapper' */
      l_result = mk_msc_wrap ( &l_wrapper, ( T_mkAddr ) &l_inquiryRequest, 0x06, K_MK_MSC_CMD_BLOC_WRAPPER_DEVICE_TO_HOST, ( uint8_t ) p_logicalUnitNumber, ( uint32_t ) l_inquiryRequest.lsbLength );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission de la requête sur le bus USB */
         /* On utilise la variable global g_mkMSCPacketBuf par rapport aux caches de données */
         l_result = mk_msc_post ( p_mscDevice, &p_mscDevice->ctrlPipe, &l_wrapper, l_status, g_mkMSCPacketBuf );
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
   }

   /* Retour */
   return ( l_result );
}


