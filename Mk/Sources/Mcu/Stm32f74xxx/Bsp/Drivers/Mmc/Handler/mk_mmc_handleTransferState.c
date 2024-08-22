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
* @file mk_mmc_handleTransferState.c
* @brief Définition de la fonction mk_mmc_handleTransferState.
* @date 1 juil. 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_post_sendCsd ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre CSD */
   T_mkMMCCSDRegister l_csd = { { 0 } };

   /* Déclaration d'une variable de travail */
   uint32_t l_sizeMultiplier;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_SEND_CSD,                                /* Code de la commande */
         p_device->layer.addr,                                    /* Argument de la commande */
         K_MMC_DIRECTION_CONTROLLER_TO_CARD,                      /* Direction du transfert */
         0,                                                       /* Nombre de données */
         0,                                                       /* Timeout du transfert de données */
         K_MMC_LONG_RESPONSE,                                     /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED                             /* Bypass CRC désactivé */
   };

   /* Transmission de la commande (CMD2) */
   l_result = mk_mmc_sendCmd ( p_handler, K_MK_NULL, &l_command, &l_csd, K_MK_NULL, &p_device->portStatus );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si le CSD est de type V1 */
      if ( l_csd.v1.version == K_MK_MMC_CSD_V1 )
      {
         /* Détermination de la valeur du multiplicateur de taille */
         l_sizeMultiplier = ( uint32_t ) ( 1 << ( l_csd.v1.cSizeMult + 2 ) );

         /* Configuration du multiplicateur d'adresse */
         p_device->layer.multiplier = K_MK_MMC_DEFAULT_SDV1_ADDRESS_MULTIPLIER;

         /* Détermination de la longueur d'un bloc de données */
         p_device->layer.blockLength = l_csd.v1.readBlockLength;
         p_device->disk->attribute.blockLength = ( uint32_t ) ( 1 << ( l_csd.v1.readBlockLength ) );

         /* Détermination du nombre de bloc de données */
         p_device->disk->attribute.numberOfBlocks =
               ( uint32_t ) ( ( ( l_csd.v1.deviceSizeHigh << 2 ) | l_csd.v1.deviceSizeLow ) + 1 ) * l_sizeMultiplier;

         /* Détermination de la valeur de la dernière adresse logique */
         p_device->disk->attribute.logicalBlockAdress = ( uint32_t ) ( p_device->disk->attribute.numberOfBlocks - 1 );

         /* Si le disque est protégé en écriture */
         if ( ( l_csd.v1.permWriteProtect == 1 ) || ( l_csd.v1.tmpWriteProtect == 1 ) )
         {
            /* On signale que le disque est protégé en écriture */
            p_device->disk->status.main = ( uint32_t ) ( K_MK_DISK_WRITE_PROTECT );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si le CSD est de type V2 */
      else if ( l_csd.v1.version == K_MK_MMC_CSD_V2 )
      {
         /* Configuration du multiplicateur d'adresse */
         p_device->layer.multiplier = K_MK_MMC_DEFAULT_SDV2_ADDRESS_MULTIPLIER;

         /* Détemrination de la longueur d'un bloc de données */
         p_device->layer.blockLength = l_csd.v2.readBlockLength;
         p_device->disk->attribute.blockLength = ( uint32_t ) ( 1 << ( l_csd.v2.readBlockLength ) );

         /* Détermination du nombre de bloc de données */
         p_device->disk->attribute.numberOfBlocks = ( uint32_t ) ( ( ( l_csd.v2.deviceSizeHigh << 16 ) | l_csd.v2.deviceSizeLow ) + 1 ) *
               ( uint32_t ) ( K_MK_MMC_DEFAULT_SIZE_MULTIPLIER / p_device->disk->attribute.blockLength );

         /* Détermination de la valeur de la dernière adresse logique */
         p_device->disk->attribute.logicalBlockAdress = ( uint32_t ) ( p_device->disk->attribute.numberOfBlocks - 1 );

         /* Si le disque est protégé en écriture */
         if ( ( l_csd.v2.permWriteProtect == 1 ) || ( l_csd.v2.tmpWriteProtect == 1 ) )
         {
            /* On signale que le disque est protégé en écriture */
            p_device->disk->status.main = ( uint32_t ) ( K_MK_DISK_WRITE_PROTECT );
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
         /* Actualisation de l'état du périphérique */
         p_device->type = K_MK_MMC_TYPE_NOT_SUPPORTED;
      }

      /* Si la carte est en version 1 */
      if ( l_csd.v1.version == K_MK_MMC_CSD_V1 )
      {
         /* Les carte de version 1 ('Low Capacity') spécifie dans le CSD une taille de bloc maximale de 1024 octets. */
         /* Ce facteur est utilisé pour déterminer la taille maximale du média. */
         /* Cependant, la taille réélle des blocs de données est de 512 octets. */

         /* Configuration de la longueur d'un bloc de données */
         p_device->layer.blockLength = K_MK_MMC_DEFAULT_BLOCK_LENGTH;
         p_device->disk->attribute.blockLength = ( uint32_t ) ( 1 << K_MK_MMC_DEFAULT_BLOCK_LENGTH );
      }

      /* Sinon si la taille des blocs de données n'est pas supportée */
      else if ( ( p_device->disk->attribute.blockLength > K_MK_FILE_MAX_BLOCK_LENGTH ) )
      {
         /* Configuration de la longueur d'un bloc de données */
         p_device->layer.blockLength = K_MK_FILE_MAX_BLOCK_LENGTH_SHIFT;
         p_device->disk->attribute.blockLength = ( uint32_t ) ( 1 << K_MK_FILE_MAX_BLOCK_LENGTH_SHIFT );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_setBusLength ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un buffer de données */
   uint32_t l_block [ ( 1 << K_MK_MMC_STATUS_BLOCK_SIZE ) ];

   /* Déclaration d'une variable de travail */
   T_mkMMCExtendedStatus* l_status = ( T_mkMMCExtendedStatus* ) l_block;

   /* La carte est actuellement en mode 1 fil. */
   /* Dans la séquence ci-dessous, on essaye de la basculer en mode 4 fils. */

   /* Configuration de la taille du bus */
   l_result = mk_mmc_setBusWidth ( p_handler, p_device, K_MK_MMC_BUS_WIDTH_4BITS );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* On réalise une lecture du registre de statut de la carte afin de savoir */
      /* si la commande a été prise en compte. */

      /* Récupération du registre de statut de la carte */
      l_result = mk_mmc_sendStatus ( p_handler, p_device, l_status );

      /* La variable de retour n'est pas testée car le champ 'busWidth' n'est pas */
      /* actualisé en cas d'echec de la commande. */

      /* Si le mode 4 fils n'est pas actif */
      if ( l_status->busWidth != K_MK_MMC_BUS_WIDTH_4BITS )
      {
         /* Re-configuration de la taille du bus */
         l_result = mk_mmc_setBusWidth ( p_handler, p_device, K_MK_MMC_BUS_WIDTH_1BIT );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* On réalise une nouvelle lecture du registre de statut de la carte afin de savoir */
            /* si la commande a été prise en compte. */

            /* Récupération du registre de statut de la carte */
            l_result = mk_mmc_sendStatus ( p_handler, p_device, l_status );

            /* Si une erreur s'est produite */
            if ( ( l_result != K_MK_OK ) && ( l_status->busWidth != K_MK_MMC_BUS_WIDTH_1BIT ) )
            {
               /* Actualisation du type du périphérique */
               p_device->type = K_MK_MMC_TYPE_NOT_SUPPORTED;
            }
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
   }

   /* Sinon */
   else
   {
      /* La commande 4 fils a échoué, le système est toujours configuré en mode 1 fil. */
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

static T_mkCode mk_mmc_handleTransferReadyState ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* La carte est dans l'état 'STANDBY'. */
   /* Il est nécessaire de récupérer le CSD de la carte pour actualiser la structure 'T_mkDisk'. */

   /* Transmission de la commande 'SEND_CSD' (CMD2) */
   l_result = mk_mmc_post_sendCsd ( p_handler, p_device );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Le CSD a été récupéré et la structure 'T_mkDisk' actualisée */
      /* On bascule alors la carte dans l'état 'TRANSFER' pour la configurer */

      /* Sélection de la carte */
      l_result = mk_mmc_select ( p_handler, p_device );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* La carte est maintenant active, il est temps de configurer la taille du bus */
         /* et la taille d'un bloc de données */

         /* Si la carte n'est pas vérrouillée */
         if ( p_device->status.cardIsLock == 0 )
         {
            /* Configuration de la taille du bus */
            /* Cette fonction tente de basculer la carte en mode 4 fils. En cas d'échec, elle reconfigure la */
            /* carte en mode 1 fil. Une erreur est levée si le système échoue à réactiver ce mode. */
            l_result = mk_mmc_setBusLength ( p_handler, p_device );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( ( l_result == K_MK_OK ) && ( p_device->type != K_MK_MMC_TYPE_NOT_SUPPORTED ) )
         {
            /* Configuration de la taille du disque */
            /* Rien de particulier ici, on configure la taille des blocs à 512 ou 1024 octets en fonction du contenu du CSD. */
            l_result = mk_mmc_setBlockLength ( p_handler, p_device, ( uint32_t ) ( 1 << p_device->layer.blockLength ) );

            /* Si la modification de la taille du bloc n'a pas réussie */
            if ( l_result != K_MK_OK )
            {
               /* Actualisation du type du périphérique */
               p_device->type = K_MK_MMC_TYPE_NOT_SUPPORTED;
            }

            /* Sinon */
            else
            {
               /* Si la carte n'est pas vérrouillée */
               if ( p_device->status.cardIsLock == 0 )
               {
                  /* Actualisation du statut du disque */
                  p_device->disk->status.main |= K_MK_DISK_READY;

                  /* Transfert d'un événement CONNECT au dispatcher */
                  l_result = mk_disk_dispatch ( p_device->disk, K_MK_EVENT_CONNECT );
               }

               /* Sinon */
               else
               {
                  /* Actualisation du statut du disque */
                  p_device->disk->status.main |= K_MK_DISK_LOCKED;

                  /* Transfert d'un événement Lock au dispatcher */
                  l_result = mk_disk_dispatch ( p_device->disk, K_MK_EVENT_LOCK );
               }
            }
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

      /* Il n'est pas nécessaire de déselectionner le périphérique. Cela sera fait automatiquement lors */
      /* du prochain appel de la fonction mk_mmc_select() */
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

static T_mkCode mk_mmc_handleTransferLockedState ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Récupération de la valeur du registre de statut du média */
   l_result = mk_mmc_getStatus ( p_handler, p_device );

   /* Si aucune erreur ne s'est produite et si la carte n'est pas vérrouillée */
   if ( ( l_result == K_MK_OK ) && ( p_device->status.cardIsLock == 0 ) )
   {
      /* Configuration de la taille du bus */
      /* Cette fonction tente de basculer la carte en mode 4 fils. En cas d'échec, elle reconfigure la */
      /* carte en mode 1 fil. Une erreur est levée si le système échoue à réactiver ce mode. */
      l_result = mk_mmc_setBusLength ( p_handler, p_device );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( p_device->type != K_MK_MMC_TYPE_NOT_SUPPORTED ) )
      {
         /* Actualisation du statut du disque */
         p_device->disk->status.main |= K_MK_DISK_READY;
         p_device->disk->status.main &= ( T_mkDiskMainStatusField ) ( ~K_MK_DISK_LOCKED );

         /* Transfert d'un événement au dispatcher */
         l_result = mk_disk_dispatch ( p_device->disk, K_MK_EVENT_CONNECT );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_handleTransferState ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si le média est dans l'état vérrouillé */
   if ( ( p_device->disk->status.main & K_MK_DISK_LOCKED ) == K_MK_DISK_LOCKED )
   {
      /* La carte est dans l'état 'Transfer'. */
      /* Cette fonction s'assure que la carte n'est pas vérrouillée puis */
      /* configure la taille du bus de données sur 4 bits. */
      l_result = mk_mmc_handleTransferLockedState ( p_handler, p_device );
   }

   /* Sinon */
   else
   {
      /* La carte est dans l'état 'Standby'. */
      /* La fonction ci-dessous bascule la carte dans l'état 'Transfer'. */
      /* Après l'acquisition du CSD, cette fonction configure la longueur maximale des blocs de données et */
      /* si la carte n'est pas vérrouillée configure la taille du bus de données sur 4 bits. */
      l_result = mk_mmc_handleTransferReadyState ( p_handler, p_device );
   }

   /* Retour */
   return ( l_result );
}


