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
* @file mk_mmc_handle.c
* @brief Définition de la fonction mk_mmc_handle.
* @date 14 juil. 2020
* @todo Continuer l'implémentation (FileSystem/GPIO)*
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_initBus ( T_mkMMCHandler* p_handler )
{
   /* Topologie des bus */

   /* Pour le bus SD : */
   /*   - les signaux CMD et DATA[0:3] sont distincts pour chaque carte connectée sur le bus. */
   /*   - le signal CLK est commun à toutes les cartes. */
   /*   - la broche CMD est configurée en mode 'PushPull'. */

   /* Optionnellement, les signaux CMD de chaque cartes peuvent être mis en commun après l'initialisation. Dans cette situation : */
   /*   - il n'est pas nécessaire de réémettre les commandes de type "BC" (Broadcast Commands without response) */
   /*     sur chaque ligne de commande. */
   /*   - il n'est pas possible de transmettre les commandes de type "BCR" (Broadcast Commands with response= car la ligne CMD */
   /*     n'est pas de type 'OPEN-DRAIN'. */

   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Lancement de la séquence d'initialisation du bus. */
   /* A la fin de cette routine, les cartes compatibles avec le bus SD_MMC sont placées dans */
   /* l'état 'READY', les cartes incompatibles dans l'état 'INACTIVE'. */
   l_result = mk_mmc_handleReadyState ( p_handler );

   /* Si au moins un périphérique présents sur le bus est dans l'état 'READY' et si */
   /* aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_handler->state == K_MK_MMC_STATE_READY ) )
   {
      /* Lancement de la séquence d'identification des périphériques présents sur le bus. */
      /* A la fin de cette routine, les périphériques basculent de l'état 'READY' a 'STANDBY', la liste des périphériques */
      /* du gestionnaire SD/MMC est aussi mise à jour. */
      l_result = mk_mmc_handleStandbyState ( p_handler, K_MK_MMC_TYPE_SD );
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

static T_mkCode mk_mmc_handleDevice ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphérique SD/MMC. */
   T_mkMMCDevice* l_device;

   /* Déclaration d'une variable de travail */
   uint32_t l_pin = 0;

   /* On utilise l'état de la broche GPIO pour savoir si au moins une carte a été connectée / déconnectée */
   /* Si la GPIO indique la déconnexion d'une carte, on supprime l'intégralité de la liste des périphériques puis on recommence */
   /* le processus d'énumération. */
   /* La broche est initialisée par le gestionnaire GPIO. */

   /* Lecture du port GPIO associé à la broche SD/MMC_CONNECTED */
   l_result = mk_gpio_get ( K_MK_MMC_CARD_PORT_NUMBER, K_MK_MMC_CARD_PIN_NUMBER, &l_pin );

   /* Si une carte a été connectée */
   if ( ( l_pin == K_MK_MMC_CARD_CONNECTED_STATE ) && ( p_handler->state != K_MK_MMC_STATE_DISCONNECTED ) )
   {
      /* Si le bus est dans l'état inactif */
      if ( ( p_handler->state != K_MK_MMC_STATE_READY ) || ( p_handler->list.first == K_MK_NULL ) )
      {
         /* Initialisation du bus SD/MMC (récupération CID, ...) */
         l_result = mk_mmc_initBus ( p_handler );
      }

      /* Sinon */
      else
      {
         /* Pour le nombre de périphériques SD/MMC présents sur le bus */
         for ( l_device = p_handler->list.first ; l_device != K_MK_NULL ; l_device = l_device->next )
         {
            /* Si le CID du média a été récupéré */
            if ( l_device->status.currentState != 0 )
            {
               /* Sélection du média */
               l_result = mk_mmc_select ( p_handler, l_device );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Si le disque n'est pas initialisé */
               if ( ( l_device->disk->status.main & K_MK_DISK_READY ) != K_MK_DISK_READY )
               {
                  /* Initialisation du périphérique SD/MMC courant */
                  l_result = mk_mmc_initDisk ( l_device );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Si le volume n'a pas été initilialisé (le disque doit ne doit pas être vérrouillé) */
               if ( ( l_result == K_MK_OK ) &&
                  ( ( l_device->disk->status.main & K_MK_DISK_LOCKED ) != K_MK_DISK_LOCKED ) &&
                  ( ( l_device->disk->status.main & K_MK_DISK_VOLUME_MOUNTED ) != K_MK_DISK_VOLUME_MOUNTED ) )
               {
                  /* Initialisation du ou des volumes présents sur le disque */
                  l_result  = mk_volume_init ( l_device->disk, g_mkMMCPacketBuf );
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
      }
   }

   /* Sinon */
   else
   {
      /* La carte a été déconnectée. */
      /* Exécution de la séquence de suppression des disques */
      l_result = mk_mmc_handleDeleteState ( p_handler );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_handleCallback ( T_mkTask* p_task, T_mkDiskRequest* p_message, T_mkCode p_code )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Si une fonction de rappel a été configurée */
   if ( p_message->callback != K_MK_NULL )
   {
      /* Configuration des arguments de la fonction de rappel */
      l_callbackParams.param1 = ( T_mkAddr ) p_code;
      l_callbackParams.param2 = ( T_mkAddr ) p_message->buf;
      l_callbackParams.param3 = ( T_mkAddr ) p_message->numberOfBlock;
      l_callbackParams.param4 = ( T_mkAddr ) p_message->lowNumberOfBytesTransfered;

      /* Déclenchement de la fonction de rappel */
      l_result = mk_callback_trig ( p_message->callback->handler, p_message->callback, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Récupération du niveau de privilège de la zone mémoire */
      l_area = _mk_memory_isPrivilegedArea ( ( T_mkAddr ) p_message->result );

      /* Si la tâche émettrice de la requête possède un niveau de droits suffisants  */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         *p_message->result = p_code;
      }

      /* Si la tâche est suspendue */
      if ( p_task->attribute.state == K_MK_STATE_SUSPENDED )
      {
         /* Réactivation de la tâche */
         l_result = mk_task_resume ( p_task );
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

static T_mkCode mk_mmc_handleRequest ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task;

   /* Déclaration d'un message */
   T_mkDiskRequest l_message;

   /* Déclaration des variables de travail */
   T_mkDisk* l_disk = K_MK_NULL;
   uint64_t l_blockAddress = 0;
   uint64_t* l_numberOfBytesTransfered = K_MK_NULL;

   /* Attendre tant qu'un message n'a pas été reçu */
   l_result = mk_mail_pend ( &l_task, p_handler->requestArea->request, ( T_mkAddr ) &l_message, K_MK_MMC_REFRESH_TIMEOUT );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
   {
      /* Si une tache privilégiée a réalisé la requête */
      if ( ( l_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
      {
         /* Récupération de l'adresse du disque */
         l_disk = l_message.disk;

         /* Récupération de l'adresse du bloc de données */
         l_blockAddress = ( uint64_t ) ( ( uint64_t ) l_message.highBlockAddress << 32 | ( uint64_t ) l_message.lowBlockAddress );

         /* Récupération de l'adresse où doit être stocké le nombre d'octets transférés */
         l_numberOfBytesTransfered = ( T_mkAddr ) l_message.lowNumberOfBytesTransfered;

         /* Si une requête de lecture a été reçue */
         if ( l_message.requestIdentifier == K_MK_DISK_IO_READ )
         {
            /* Lecture d'un ou plusieurs blocs de données */
            l_result = mk_mmc_readSector ( l_disk, l_blockAddress, l_message.buf, l_message.numberOfBlock, ( uint64_t* ) l_numberOfBytesTransfered );
         }

         /* Sinon si une requête d'écriture a été reçue */
         else if ( l_message.requestIdentifier == K_MK_DISK_IO_WRITE )
         {
            /* Ecriture d'un ou plusieurs blocs de données */
            l_result = mk_mmc_writeSector ( l_disk, l_blockAddress, l_message.buf, l_message.numberOfBlock, ( uint64_t* ) l_numberOfBytesTransfered );
         }

         /* Sinon si une requête de configuration des options de sécurité a été reçue */
         else if ( l_message.requestIdentifier == K_MK_DISK_IO_SECURITY )
         {
            /* Configuration des options de sécurité */
            l_result = mk_mmc_setSecurity ( p_handler, l_disk->device, l_message.buf, l_message.highBlockAddress, l_message.lowBlockAddress );
         }

         /* Sinon */
         else
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_PARAM;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }

      /* Gestion de la fonction de rappel */
      l_result = mk_mmc_handleCallback ( l_task, &l_message, l_result );
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

T_mkCode mk_mmc_handle ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Exécution de la séquence d'initialisation des nouveaux disques */
      l_result = mk_mmc_handleDevice ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Exécution de la séquence de traitement des requêtes utilisateur */
         l_result = mk_mmc_handleRequest ( p_handler );
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
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


