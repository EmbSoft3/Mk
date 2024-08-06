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
* @file mk_mmc_readSector.c
* @brief Définition de la fonction mk_mmc_readSector.
* @date 25 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_checkSelectStatus ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le périphérique n'est pas le périphérique actif */
   if ( p_handler->current != p_device )
   {
      /* Sélection du périphérique */
      l_result = mk_mmc_select ( p_handler, p_device );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Tant que la carte n'est pas prête */
      while ( ( l_result == K_MK_OK ) && ( p_device->status.readyForData == 0 ) )
      {
         /* Récupération du statut de fonctionnement de la carte */
         l_result = mk_mmc_getStatus ( p_handler, p_device );

         /* Si la carte n'est pas prête */
         if ( ( l_result == K_MK_OK ) && ( p_device->status.readyForData == 0 ) )
         {
            /* Attente 1 ms */
            l_result = mk_task_sleep ( 1 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_post_multipleRead ( T_mkDisk* p_disk, T_mkMMCDevice* p_device, uint32_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération de l'adresse du gestionnaire MMC */
   T_mkMMCHandler* l_handler = ( T_mkMMCHandler* ) p_device->handler;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_READ_MULTIPLE_BLOCK,                              /* Code de la commande */
         ( p_blockAddress << p_device->layer.multiplier ),                 /* Argument de la commande */
         K_MMC_DIRECTION_CARD_TO_CONTROLLER,                               /* Direction du transfert */
         ( p_numberOfBlockToRead * p_disk->attribute.blockLength ),        /* Nombre de données */
         ( p_numberOfBlockToRead * K_MK_MMC_TIMEOUT),                      /* Timeout du transfert de données */
         K_MMC_SHORT_RESPONSE,                                             /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED                                      /* Bypass CRC désactivé */
   };

   /* Lecture de l'adresse du registre de statut du périphérique */
   uint32_t* l_status = ( uint32_t* ) &p_device->status;

   /* Transmission de la commande (CMD18) */
   l_result = mk_mmc_sendCmd ( l_handler, p_device, &l_command, &p_device->status, p_buf, &p_device->portStatus );

   /* Si une erreur est remontée par la carte */
   if ( ( l_result == K_MK_OK ) && ( ( ( *l_status ) & K_MK_MMC_ERROR_MASK ) > 0 ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COMM;
   }

   /* Sinon */
   else
   {
      /* Actualisation du nombre d'octets lus */
      /* La taille de transfert DMA est sur 32 bits, on réalise donc une multiplication par 4 pour obtenir le nombre d'octets. */
      *p_numberOfBytesRead = ( uint64_t ) ( *p_numberOfBytesRead ) +
                             ( 4 * dma_getNumberOfDataTransfered ( l_handler->pipe->addr, l_handler->pipe->stream ) );

      /* On stoppe le flux de lecture lorsque le processus est terminé ou qu'une erreur s'est produite */
      /* L'arrêt est réalisé sans condition. */
      l_result |= mk_mmc_stopTransmission ( l_handler, p_device );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_readSector ( T_mkDisk* p_disk, uint64_t p_blockAddress, T_mkAddr p_buf, uint32_t p_numberOfBlockToRead, uint64_t* p_numberOfBytesRead )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint8_t* l_buf = ( uint8_t* ) p_buf;

   /* Déclaration d'une variable contenant la taille maximale d'un transfert DMA */
   uint32_t l_maxTransferSize = ( 1 << K_MK_MMC_MAX_TRANSFER_SIZE );

   /* Déclaration d'une variable stockant le nombre d'octets à transférer */
   uint64_t l_transferSize = ( p_numberOfBlockToRead * p_disk->attribute.blockLength );

   /* Récupération de l'adresse du périphérique MMC */
   T_mkMMCDevice* l_device = ( T_mkMMCDevice* ) p_disk->device;

   /* Si les paramètres sont valides */
   if ( ( p_disk != K_MK_NULL ) && ( l_device != K_MK_NULL ) && ( p_buf != K_MK_NULL ) && ( p_numberOfBytesRead != K_MK_NULL ) && ( p_numberOfBlockToRead != 0 ) )
   {
      /* Initialisation du nombre d'octets lus */
      *p_numberOfBytesRead = 0;

      /* Sélection du périphérique */
      l_result = mk_mmc_checkSelectStatus ( l_device->handler, l_device );

      /* Tant que le transfert de données n'est pas terminé */
      while ( ( l_result == K_MK_OK ) && ( l_transferSize != 0 ) )
      {
         /* Note :  */
         /* Le flux DMA peut transférer un maximum de 65535 mots de 32 bits en une transaction. */
         /* On déclenche donc un flux DMA pour chaque morceau de 32768 mots ($20000 octets) */

         /* Si la taille de la transaction est inférieure à la taille limite */
         if ( l_transferSize <= l_maxTransferSize )
         {
            /* Réalisation du dernier transfert de données */
            l_result = mk_mmc_post_multipleRead ( p_disk, l_device, ( uint32_t ) p_blockAddress, l_buf, ( uint32_t ) ( l_transferSize >> l_device->layer.blockLength ), p_numberOfBytesRead );

            /* Actualisation du nombre d'octets à transférer */
            l_transferSize = 0;
         }

         /* Sinon */
         else
         {
            /* Réalisation d'un transfert de taille maximale */
            l_result = mk_mmc_post_multipleRead ( p_disk, l_device, ( uint32_t ) p_blockAddress, l_buf, ( uint32_t ) ( l_maxTransferSize >> l_device->layer.blockLength ), p_numberOfBytesRead );

            /* Actualisation du nombre d'octets à transférer et des adresses */
            l_transferSize -= ( uint64_t ) ( l_maxTransferSize );
            p_blockAddress += ( uint64_t ) ( l_maxTransferSize >> l_device->layer.blockLength );
            l_buf += l_maxTransferSize;
         }
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



