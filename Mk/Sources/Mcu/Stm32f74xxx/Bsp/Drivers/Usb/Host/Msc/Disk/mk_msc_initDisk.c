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
* @file mk_msc_initDisk.c
* @brief Définition de la fonction mk_msc_initDisk.
* @date 19 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_msc_setDiskIdentifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de l'identifiant unique du disque */
   *p_identifier = ( uint16_t ) ( ( K_MK_DISK_MAX_NUMBER - 1 ) - ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_sendRequestSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk, uint32_t p_statusFlag )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable stockant le statut complémentaire renvoyé par le périphérique SCSI */
   uint32_t l_senseCode;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_RequestSensePacket* l_requestSensePacket;

   /* Transmission d'une commande SCSI afin de récupérer la cause de l'erreur */
   l_result = mk_msc_postRequestSenseRequest ( p_mscDevice, &l_requestSensePacket, p_disk->attribute.logicalUnit );

   /* Si la commande a été acceptée */
   if ( ( l_result == K_MK_OK ) &&
        ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED ) )
   {
      /* Récupération du code erreur */
      l_senseCode = ( ( uint32_t ) l_requestSensePacket->additionalSenseCode << 8 ) | l_requestSensePacket->additionalSenseCodeQualifier;

      /* Si un événement de type 'Not Ready' est présent */
      if ( l_requestSensePacket->senseKey == K_MK_SCSI_NOT_READY )
      {
         /* Si la requête a été rejetée parce que le média n'est pas présent */
         if ( l_senseCode == K_MK_SCSI_SENSE_CODE_MEDIA_NOT_PRESENT )
         {
            /* Actualisation du statut du disque */
            p_disk->status.main |= K_MK_DISK_NOT_PRESENT;

            /* Actualisation du statut de l'initialisation */
            p_disk->status.init = K_MK_MSC_DISK_INQUIRY_DONE;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Sinon si la commande a été rejetée car elle n'est pas supportée */
      else if ( l_requestSensePacket->senseKey == K_MK_SCSI_ILLEGAL_REQUEST )
      {
         /* Actualisation du statut de l'initialisation */
         p_disk->status.init |= p_statusFlag;
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

static T_mkCode mk_msc_sendInquiryRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_InquiryPacket* l_inquiryPacket;

   /* Transmission d'une requête de type 'Inquiry' afin de récupérer les informations de base du disque */
   /* Le statut du disque n'a pas besoin d'être vérifié pour cette requête */
   l_result = mk_msc_postInquiryRequest ( p_mscDevice, &l_inquiryPacket, p_disk->attribute.logicalUnit );

   /* Si aucune erreur ne s'et produite */
   if ( ( l_result == K_MK_OK ) &&
        ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED ) )
   {
      /* Enregistrement du type du périphérique */
      p_disk->attribute.type = l_inquiryPacket->peripheralDeviceType;

      /* Enregistrement des l'identifiants du périphérique */
      _copy ( p_disk->info.productIdentifier, l_inquiryPacket->pid, 16 );
      _copy ( p_disk->info.vendorIdentifier, l_inquiryPacket->vid, 8 );
      _copy ( p_disk->info.productRevision, l_inquiryPacket->prev, 4 );

      /* On vérifie cependant que le périphérique est bien un périphérique de stockage. */
      if ( l_inquiryPacket->peripheralQualifier == K_MK_SCSI_DEVICE_QUALIFIER_CONNECTED )
      {
         /* Actualisation du statut de l'initialisation */
         p_disk->status.init = K_MK_MSC_DISK_INQUIRY_DONE;
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

static T_mkCode mk_msc_sendTestUnitReadyRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Transmission d'une requête de type 'TestUnitReady' */
   l_result = mk_msc_postTestUnitReadyRequest ( p_mscDevice, p_disk->attribute.logicalUnit );

   /* Si aucune ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la commande a été acceptée */
      if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
      {
         /* Actualisation du statut de l'intialisation */
         p_disk->status.init |= K_MK_MSC_DISK_TEST_UNIT_READY_DONE;

         /* Actualisation du statut du disque */
         p_disk->status.main &= ( uint32_t ) ( ~K_MK_DISK_NOT_PRESENT );
      }

      /* Sinon */
      else
      {
         /* Analyse de la cause de l'erreur */
         l_result = mk_msc_sendRequestSenseRequest ( p_mscDevice, p_disk, K_MK_MSC_DISK_TEST_UNIT_READY_DONE );
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

static T_mkCode mk_msc_sendReadCapacityRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_local = 0;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_ReadCapacityPacket* l_readCapacityPacket;

   /* Si le média est connecté */
   if ( ( p_disk->status.main & K_MK_DISK_NOT_PRESENT ) != K_MK_DISK_NOT_PRESENT )
   {
      /* Transmission d'une requête de type 'ReadCapacity' afin de récupérer la taille du disque */
      l_result = mk_msc_postReadCapacityRequest ( p_mscDevice, &l_readCapacityPacket, p_disk->attribute.logicalUnit );

      /* Si aucune ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si la commande a été acceptée */
         if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
         {
            /* Enregistrement des données en relation avec la taille du disque */
            p_disk->attribute.blockLength = _revertWord ( &l_readCapacityPacket->blockLength );
            p_disk->attribute.logicalBlockAdress = _revertWord ( &l_readCapacityPacket->logicalBlockAdress );

            /* Actualisation du statut de l'initialisation */
            p_disk->status.init |= K_MK_MSC_DISK_READ_CAPACITY_DONE;

            /* Analyse de la taille du disque */
            l_local = mk_utils_check2 ( p_disk->attribute.blockLength, K_MK_FILE_MIN_BLOCK_LENGTH, K_MK_FILE_MAX_BLOCK_LENGTH );

            /* Si la taille des blocs de données est invalide ou supérieure à la limite */
            if ( l_local != 0 )
            {
               /* Actualisation du statut du disque */
               p_disk->status.main |= K_MK_DISK_NOT_SUPPORTED;
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
            /* Analyse de la cause de l'erreur */
            l_result = mk_msc_sendRequestSenseRequest ( p_mscDevice, p_disk, K_MK_MSC_DISK_READ_CAPACITY_DONE );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_sendReadFormatCapacitiesRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_ReadFormatCapacitiesPacket* l_readFormatCapacitiesPacket;

   /* Transmission d'une requête de type 'ReadFormatCapacities' afin de récupérer l'organisation mémoire du disque */
   l_result = mk_msc_postReadFormatCapacitiesRequest ( p_mscDevice, &l_readFormatCapacitiesPacket, p_disk->attribute.logicalUnit );

   /* Si le média est connecté */
   if ( ( p_disk->status.main & K_MK_DISK_NOT_PRESENT ) != K_MK_DISK_NOT_PRESENT )
   {
      /* Si aucune ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si la commande a été acceptée */
         if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
         {
            /* Enregistrement des données en relation avec la taille du disque */
            p_disk->attribute.numberOfBlocks = _revertWord ( &l_readFormatCapacitiesPacket->numberOfBlocks );

            /* Actualisation du statut de l'initialisation */
            p_disk->status.init |= K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE;
         }

         /* Sinon */
         else
         {
            /* Analyse de la cause de l'erreur */
            l_result = mk_msc_sendRequestSenseRequest ( p_mscDevice, p_disk, K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_sendModeSenseRequest ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de données SCSI */
   T_mkSCSI_ModeSensePacket* l_modeSensePacket;

   /* Si le média est connecté */
   if ( ( p_disk->status.main & K_MK_DISK_NOT_PRESENT ) != K_MK_DISK_NOT_PRESENT )
   {
      /* Transmission d'une requête de type 'ModeSense' afin de récupérer l'état de la protection en écriture */
      l_result = mk_msc_postModeSenseRequest ( p_mscDevice, &l_modeSensePacket, p_disk->attribute.logicalUnit );

      /* Si aucune ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si la commande a été acceptée */
         if ( p_mscDevice->status == K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
         {
            /* Enregistrement de l'état du bit WRITE_PROTECT */
            p_disk->status.main |= ( uint32_t ) ( l_modeSensePacket->wp << ( K_MK_DISK_WRITE_PROTECT >> 1 ) );

            /* Actualisation du statut de l'initialisation */
            p_disk->status.init |= K_MK_MSC_DISK_MODE_SENSE_DONE;
         }

         /* Sinon */
         else
         {
            /* Analyse de la cause de l'erreur */
            l_result = mk_msc_sendRequestSenseRequest ( p_mscDevice, p_disk, K_MK_MSC_DISK_MODE_SENSE_DONE );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_initDiskBySCSICommandSet ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la requête INQUIRY a été rejetée */
   if ( ( p_disk->status.init & K_MK_MSC_DISK_INQUIRY_DONE ) != K_MK_MSC_DISK_INQUIRY_DONE )
   {
      /* Transmission de la requête 'Inquiry' */
      l_result = mk_msc_sendInquiryRequest ( p_mscDevice, p_disk );
   }

   /* Sinon si la requête TEST_UNIT_READY a été rejetée */
   else if ( ( p_disk->status.init & K_MK_MSC_DISK_TEST_UNIT_READY_DONE ) != K_MK_MSC_DISK_TEST_UNIT_READY_DONE )
   {
      /* Transmission d'une requête 'TestUnitReady' */
      l_result = mk_msc_sendTestUnitReadyRequest ( p_mscDevice, p_disk );
   }

   /* Sinon */
   else
   {
      /* Si la requête READ_FORMAT_CAPCITIES a été rejetée */
      if ( ( ( p_disk->status.init & K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE ) != K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE ) &&
         ( ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) ) )
      {
         /* Transmission d'une requête 'ReadFormatCapacities' */
         l_result |= mk_msc_sendReadFormatCapacitiesRequest ( p_mscDevice, p_disk );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la requête READ_CAPACITY a été rejetée */
      if ( ( ( p_disk->status.init & K_MK_MSC_DISK_READ_CAPACITY_DONE ) != K_MK_MSC_DISK_READ_CAPACITY_DONE ) &&
         ( ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) ) )
      {
         /* Transmission d'une requête 'ReadyCapacity' */
         l_result |= mk_msc_sendReadCapacityRequest ( p_mscDevice, p_disk );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si la requête MODE_SENSE a été rejetée */
      if ( ( ( p_disk->status.init & K_MK_MSC_DISK_MODE_SENSE_DONE ) != K_MK_MSC_DISK_MODE_SENSE_DONE ) &&
         ( ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) ) )
      {
         /* Transmission d'une requête 'ModeSense' */
         l_result |= mk_msc_sendModeSenseRequest ( p_mscDevice, p_disk );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Si toutes les étapes de l'intialisation ont été réalisées */
   if ( ( p_disk->status.init == ( K_MK_MSC_DISK_INQUIRY_DONE | K_MK_MSC_DISK_TEST_UNIT_READY_DONE | K_MK_MSC_DISK_READ_CAPACITY_DONE |
         K_MK_MSC_DISK_READ_FORMAT_CAPACITIES_DONE | K_MK_MSC_DISK_MODE_SENSE_DONE ) ) )
   {
      /* Si le disque est supporté par le système */
      if ( ( p_disk->status.main & K_MK_DISK_NOT_SUPPORTED ) != K_MK_DISK_NOT_SUPPORTED )
      {
         /* Actualisation du statut du disque */
         p_disk->status.main |= K_MK_DISK_READY;

         /* Transmission d'un événement au dispatcher. Un disque valide a été connecté. */
         l_result |= mk_disk_dispatch ( p_disk, K_MK_EVENT_CONNECT );
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

static T_mkCode mk_msc_initDiskByProtocol ( T_mkMSCDevice* p_mscDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk;

   /* Pour le nombre de disques à initialiser. */
   /* Un média peut contenir plusieurs disques. On rencontre parfois cette situation avec un hub possédant un lecture MMC, CF, SD, ... */
   for ( l_disk = p_mscDevice->disk ; ( l_disk != K_MK_NULL ) && ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_COMM ) || ( l_result == K_MK_ERROR_TIMEOUT ) ) ; l_disk = l_disk->nextDisk )
   {
      /* Si le disque n'a pas été intialisé */
      if ( ( l_disk->status.main == K_MK_DISK_NOT_ENUMERATED ) || ( ( l_disk->status.main & K_MK_DISK_NOT_PRESENT ) == K_MK_DISK_NOT_PRESENT ) )
      {
         /* Ouverture des pipes de communication */
         l_result = mk_msc_openPipe ( p_mscDevice );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si le protocole de transport est de type 'Bulk-Only' */
            if ( p_mscDevice->interface->bInterfaceProtocol == K_MK_MSC_PROTOCOL_BBB )
            {
               /* Si le protocole de communication est de type SCSI */
               if ( p_mscDevice->interface->bInterfaceSubClass == K_MK_MSC_SUBCLASS_SCSI_TRANSPARENT_COMMAND_SET )
               {
                  /* Initialisation du disque avec le jeu de commande SCSI. */
                  l_result = mk_msc_initDiskBySCSICommandSet ( p_mscDevice, l_disk );
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

            /* Fermeture des pipe de communication */
            l_result |= mk_msc_closePipe ( p_mscDevice );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_initDisk ( T_mkMSCDevice* p_mscDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk** l_disk;

   /* Déclaration des variables stockant le nom du disque */
   char8_t l_str [ 4 ] = "dsk";
   char8_t l_strIdentifier [ 4 ] = "";

   /* Déclaration d'une variable de travail */
   uint32_t l_logicalUnitNumber;

   /* Si le paramètre est valide */
   if ( p_mscDevice != K_MK_NULL )
   {
      /* Initialisation du pointeur de disque */
      l_disk = &p_mscDevice->disk;

      /* Allocation d'un disque pour chaque unité logique */
      /* Un média peut contenir plusieurs disques. On rencontre parfois cette situation avec un hub possédant un lecture MMC, CF, SD, ... */
      for ( l_logicalUnitNumber = 0 ; l_logicalUnitNumber < ( uint32_t ) ( p_mscDevice->layer.numberOfLUN + 1 ) && ( l_result == K_MK_OK ) ; l_logicalUnitNumber++)
      {
         /* Si le disque analysé n'a pas été alloué */
         if ( *l_disk == K_MK_NULL )
         {
            /* Allocation d'un nouveau disque */
            l_result = mk_pool_allocSafe ( g_mkDiskPool.pool, ( T_mkAddr* ) l_disk, K_MK_POOL_CLEAR, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration du type applicatif */
               (*l_disk)->layer.type = K_MK_CONTROL_DISK;

               /* Configuration de l'identifiant unique du disque */
               mk_msc_setDiskIdentifier ( &(*l_disk)->layer.id, *l_disk, g_mkDiskPool.heap, sizeof ( T_mkDisk ) );

               /* Conversion et stockage de l'identifiant du disque en chaine de caractères */
               mk_utils_itoa ( ( uint32_t ) (*l_disk)->layer.id, ( T_str8 ) l_strIdentifier, 10, 1 );
               mk_utils_strcat ( ( T_str8 ) (*l_disk)->name.id, ( T_str8 ) l_str, ( T_str8 ) l_strIdentifier );

               /* Configuration du type d'accès */
               (*l_disk)->layer.peripheralAccess = K_MK_DISK_ACCESS_TYPE_ALIGNED;

               /* Enregistrement du numéro de l'unité logique du disque */
               ( *l_disk )->attribute.logicalUnit = l_logicalUnitNumber;

               /* Enregistrement de l'adresse mémoire du périphérique dans le disque */
               ( *l_disk )->device = p_mscDevice;

               /* Création d'un sémaphore. Les disques seront utilisés par plusieurs tâches du système. */
               l_result = mk_semaphore_create ( &( *l_disk )->semaphore, K_MK_AREA_PROTECTED, 1, 0 );

               /* Si une erreur s'est produite */
               if ( l_result != K_MK_OK )
               {
                  /* Suppression du disque */
                  l_result |= mk_pool_freeSafe ( g_mkDiskPool.pool, *l_disk );
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
            /* Ne rien faire */
         }

         /* Actualisation du pointeur de disque */
         l_disk = &(*l_disk)->nextDisk;
      }

      /* On ne vérifie pas si une erreur d'allocation s'est produite afin d'initialiser les disques ayant été alloués */
      /* Lancement de la séquence d'intialisation des disques */
      l_result |= mk_msc_initDiskByProtocol ( p_mscDevice );
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


