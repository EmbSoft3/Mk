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
* @file mk_msc_checkDiskStatus.c
* @brief Définition de la fonction mk_msc_checkDiskStatus.
* @date 22 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_checkDiskStatusBySCSICommandSet ( T_mkMSCDevice* p_mscDevice, T_mkDisk* p_disk )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_senseCode;

   /* Déclaration des structures de données SCSI */
   T_mkSCSI_RequestSensePacket* l_requestSensePacket;

   /* Transmission d'une requête de type 'TestUnitReady' */
   l_result = mk_msc_postTestUnitReadyRequest ( p_mscDevice, p_disk->attribute.logicalUnit );

   /* Si aucune ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si la commande n'a pas été acceptée */
      if ( p_mscDevice->status != K_MK_MSC_DEVICE_STATUS_CMD_PASSED )
      {
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
                  p_disk->status.main = ( K_MK_DISK_NOT_PRESENT | K_MK_DISK_NOT_ENUMERATED );

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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_checkDiskStatus ( T_mkMSCDevice* p_mscDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de disque */
   T_mkDisk* l_disk;

   /* Si le paramètre est valide */
   if ( p_mscDevice != K_MK_NULL )
   {
      /* Pour le nombre de disques à initialiser */
      /* Un média peut contenir plusieurs disques. On rencontre parfois cette situation avec un hub possédant un lecture MMC, CF, SD, ... */
      for ( l_disk = p_mscDevice->disk ; ( l_disk != K_MK_NULL ) && ( l_result == K_MK_OK ) ; l_disk = l_disk->nextDisk )
      {
         /* Si le disque n'est pas intialisé */
         if ( ( l_disk->status.main & K_MK_DISK_READY ) == K_MK_DISK_READY )
         {
            /* Ouverture d'un ou plusieurs pipe de communication */
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
                     l_result = mk_msc_checkDiskStatusBySCSICommandSet ( p_mscDevice, l_disk );
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

               /* Fermeture des pipes de communication */
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

         /* Si le disque a été retiré et qu'il n'est pas en utilisation */
         if ( ( l_disk->status.main & ( K_MK_DISK_NOT_PRESENT | K_MK_DISK_USED ) ) == K_MK_DISK_NOT_PRESENT )
         {
            /* Suppression du disque */
            l_result |= mk_disk_delete ( &p_mscDevice->disk, l_disk, 1 );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


