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
* @file mk_msc_eraseSector.c
* @brief Définition de la fonction mk_msc_eraseSector.
* @date 3 janv. 2021
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_post_scsiEraseCommand ( T_mkMSCDevice* p_device, T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToErase, uint64_t* p_numberOfBytesErased )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSIBlock l_block;

   /* Déclaration des variables de travail */
   uint32_t l_lowBlockAddress  = ( uint32_t ) ( p_blockAddress & 0xFFFFFFFF );
   uint32_t l_highBlockAddress = ( uint32_t ) ( ( p_blockAddress >> 32 ) & 0xFFFFFFFF ) ;
   uint64_t l_numberOfBytesErased = 0;

   /* Configuration du bloc de données */
   l_block.lowAddr =  _revertWord ( &l_lowBlockAddress );
   l_block.highAddr = _revertWord ( &l_highBlockAddress );
   l_block.length = p_disk->attribute.blockLength;
   l_block.buf = p_buf;

   /* Si l'adressage est sur 64 bits */
   if ( ( l_highBlockAddress != 0 ) )
   {
      /* Déclenchement d'une opération d'écriture 64 bits */
      l_result = mk_msc_postWrite64Request ( p_device, &l_block, ( uint16_t ) p_numberOfBlockToErase, &l_numberOfBytesErased, p_disk->attribute.logicalUnit );
   }

   /* Sinon */
   else
   {
      /* Déclenchement d'une opération d'écriture 32 bits */
      l_result = mk_msc_postWriteRequest ( p_device, &l_block, ( uint16_t ) p_numberOfBlockToErase, &l_numberOfBytesErased, p_disk->attribute.logicalUnit );
   }

   /* Actualisation du nombre d'octets effacés */
   *p_numberOfBytesErased = ( uint64_t ) ( ( *p_numberOfBytesErased ) + l_numberOfBytesErased );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_eraseSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, uint32_t p_numberOfBlockToErase, uint64_t* p_numberOfBytesErased, uint32_t p_pattern )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant l'adresse du périphérique MSC */
   T_mkMSCDevice* l_device = ( T_mkMSCDevice* ) p_disk->device;

   /* Déclaration d'un pointeur de buffer */
   uint8_t* l_buf = ( uint8_t* ) g_mkMSCPacketBuf;

   /* Si les paramètres sont valides */
   if ( ( p_disk != K_MK_NULL ) && ( p_numberOfBytesErased != K_MK_NULL ) && ( p_numberOfBlockToErase != 0 ) )
   {
      /* Réinitialisation du buffer */
      _writeWords ( g_mkMSCPacketBuf, p_pattern, ( p_disk->attribute.blockLength >> 2 ) );

      /* Si le protocole de transport est de type 'Bulk-Only' */
      if ( l_device->interface->bInterfaceProtocol == K_MK_MSC_PROTOCOL_BBB )
      {
         /* Si le protocole de communication est de type SCSI */
         if ( l_device->interface->bInterfaceSubClass == K_MK_MSC_SUBCLASS_SCSI_TRANSPARENT_COMMAND_SET )
         {
            /* Actualisation du nombre d'octets effacés */
            *p_numberOfBytesErased = 0;

            /* Tant que le transfert de données n'est pas terminé */
            while ( ( l_result == K_MK_OK ) && ( p_numberOfBlockToErase != 0 ) )
            {
               /* Effacement d'un bloc de données */
               l_result = mk_msc_post_scsiEraseCommand ( l_device, p_disk, p_blockAddress, l_buf, 1, p_numberOfBytesErased );

               /* Actualisation de l'adresse */
               p_blockAddress = ( uint64_t ) ( p_blockAddress + p_disk->attribute.blockLength );

               /* Actualisation du nombre de blocs restant à transférer */
               p_numberOfBlockToErase = ( uint32_t ) ( p_numberOfBlockToErase - 1 );
            }
         }

         /* Note */
         /* Insérer la séquence d'intialisation des autres protocoles ici ... */

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Note */
      /* Insérer la séquence d'intialisation des autres protocoles ici ... */

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



