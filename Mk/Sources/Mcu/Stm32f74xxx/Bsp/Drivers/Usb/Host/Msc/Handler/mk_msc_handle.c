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
* @file mk_msc_handle.c
* @brief Définition de la fonction mk_msc_handle.
* @date 17 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_handleCallback ( T_mkTask* p_task, T_mkDiskRequest* p_message, T_mkCode p_code )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams;

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
      /* Si une tache privilégiée a réalisée la requête */
      if ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
      {
         /* Actualisation de la structure de retour */
         *p_message->result = p_code;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
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

static T_mkCode mk_msc_handleRequest ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task;

   /* Déclaration d'un message */
   T_mkDiskRequest l_message;

   /* Déclaration des variables de travail */
   uint64_t l_blockAddress = 0;
   uint64_t* l_numberOfBytesTransfered = K_MK_NULL;

   /* Attendre tant qu'un message n'a pas été reçu */
   l_result = mk_mail_pend ( &l_task, p_handler->requestArea->request, ( T_mkAddr ) &l_message, K_MK_MSC_REFRESH_TIMEOUT );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
   {
      /* Si une tache privilégiée a réalisée la requête */
      if ( ( l_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_PRIVILEGED )
      {
         /* Récupération de l'adresse du bloc de données */
         l_blockAddress = ( uint64_t ) ( ( uint64_t ) l_message.highBlockAddress << 32 | ( uint64_t ) l_message.lowBlockAddress );

         /* Récupération de l'adresse où doit être stocké le nombre d'octets transférés */
         l_numberOfBytesTransfered = ( T_mkAddr ) l_message.lowNumberOfBytesTransfered;

         /* Si une requête de lecture a été reçue */
         if ( l_message.requestIdentifier == K_MK_DISK_IO_READ )
         {
            /* Lecture d'un ou plusieurs blocs de données */
            l_result = mk_msc_readSector ( l_message.disk, l_blockAddress, l_message.buf, l_message.numberOfBlock, ( uint64_t* ) l_numberOfBytesTransfered );
         }

         /* Sinon si une requête d'écriture a été reçue */
         else if ( l_message.requestIdentifier == K_MK_DISK_IO_WRITE )
         {
            /* Ecriture d'un ou plusieurs blocs de données */
            l_result = mk_msc_writeSector ( l_message.disk, l_blockAddress, l_message.buf, l_message.numberOfBlock, ( uint64_t* ) l_numberOfBytesTransfered );
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
      l_result = mk_msc_handleCallback ( l_task, &l_message, l_result );
   }

   /* Sinon si un timeout s'est produit */
   else if ( l_result == K_MK_ERROR_TIMEOUT )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_OK;
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

static T_mkCode mk_msc_swapToDeletedList ( T_mkMSCHandler* p_handler, T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphérique MSC */
   T_mkMSCDevice* l_mscDevice = K_MK_NULL;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface;

   /* Récupération de l'adresse de la première interface */
   l_interface = p_device->interfaceDescriptor;

   /* Pour chaque interface du périphérique */
   /* Il est possible qu'un dispositif soit détruit alors qu'il ne possède aucune interface. */
   /* Ce cas peut se produire lorsqu'une interface invalide a été détectée puis désallouer avant la déconnection */
   /* du périphérique. */
   while ( l_interface != K_MK_NULL )
   {
      /* Si l'interface est une interface de type MSC */
      if ( p_device->interfaceDescriptor->bInterfaceClass == K_MK_HCD_CLASS_MASS_STORAGE )
      {
         /* Récupération de l'adresse du périphérique MSC */
         l_mscDevice = ( T_mkMSCDevice* ) l_interface->child;

         /* Suppression du périphérique de la liste des périphériques en cours d'utilisation. */
         l_result |= mk_msc_remove ( &p_handler->list, ( T_mkMSCDevice* ) l_mscDevice );

         /* Ajout du périphérique dans les listes des périphériques en cours de suppression. */
         l_result |= mk_msc_add ( &p_handler->deletedList, ( T_mkMSCDevice* ) l_mscDevice );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la valeur du pointeur d'interface */
      l_interface = l_interface->nextInterface;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_handleDeletedList ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphériques */
   T_mkMSCDevice* l_currentDevice = p_handler->deletedList.first;

   /* Si au moins un périphérique est présent dans la liste */
   if ( l_currentDevice != K_MK_NULL )
   {
      /* Effectue */
      do
      {
         /* Suppression du périphérique */
         l_result |= mk_msc_deleteDevice ( p_handler, l_currentDevice );

         /* Actualisation du pointeur de périphérique */
         l_currentDevice = l_currentDevice->next;

      /* Tant que l'intégralité des périphériques n'ont pas analysés */
      } while ( l_currentDevice != K_MK_NULL );
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

static T_mkCode mk_msc_handleDevice ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphériques */
   T_mkMSCDevice* l_currentDevice = p_handler->list.first;

   /* Si au moins un périphérique MSC est présent dans la liste */
   if ( l_currentDevice != K_MK_NULL )
   {
      /* Effectue */
      do
      {
         /* Si le périphérique a été déconnecté du bus */
         if ( ( l_currentDevice->device->state & K_MK_HCD_DEVICE_DISCONNECTED ) == K_MK_HCD_DEVICE_DISCONNECTED )
         {
            /* Ajout des périphériques MSC déconnectés dans la liste des périphériques à supprimer */
            mk_msc_swapToDeletedList ( p_handler, l_currentDevice->device );
         }

         /* Sinon si le périphérique n'est pas initialisé */
         else if ( ( l_currentDevice->state & K_MK_MSC_DEVICE_CONFIGURED_STATE ) != K_MK_MSC_DEVICE_CONFIGURED_STATE )
         {
            /* Initialisation du périphérique MSC */
            l_result = mk_msc_initDevice ( p_handler, l_currentDevice );
         }

         /* Sinon */
         else
         {
            /* Les périphériques SCSI ne possèdent pas d'interruption indiquant que le disque a été déconnecté */
            /* On scrute donc de manière périodique les statuts renvoyés par l'unité logique. */
            /* Un disque déconnecté possède le statut K_MK_DISK_NOT_PRESENT */
            l_result = mk_msc_checkDiskStatus ( l_currentDevice );

            /* Déclenchement de la séquence d'initialisation pour les nouveaux disques connectés au système. */
            l_result |= mk_msc_initDisk ( l_currentDevice );

            /* Déclenchement de la séquence d'analyse des volumes présents sur les disques */
            l_result |= mk_volume_init ( l_currentDevice->disk, g_mkMSCPacketBuf );
         }

         /* Actualisation du pointeur de périphérique */
         l_currentDevice = l_currentDevice->next;

      /* Tant que l'intégralité des périphériques MSC n'ont pas analysés */
      } while ( l_currentDevice != K_MK_NULL );
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

T_mkCode mk_msc_handle ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le paramètre est valide */
   if ( p_handler != K_MK_NULL )
   {
      /* Exécution de la routine de traitement des disques et des périphériques MSC */
      l_result = mk_msc_handleDevice ( p_handler );

      /* Suppression des périphériques MSC déconnectés */
      l_result |= mk_msc_handleDeletedList ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Exécution de la routine de traitement des requêtes utilisateur */
         l_result = mk_msc_handleRequest ( p_handler );
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



