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
* @file mk_msc_deleteDevice.c
* @brief Définition de la fonction mk_msc_deleteDevice.
* @date 17 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_msc_checkDeviceEmpty ( T_mkHCDDevice* p_device, uint32_t* p_state )
{
   /* Déclaration d'un pointeur de périphérique MSC */
   T_mkMSCDevice* l_mscDevice = K_MK_NULL;

   /* Récupération de l'adresse de la première interface du périphérique */
   T_mkHCDInterfaceDescriptor* l_interface = p_device->interfaceDescriptor;

   /* Pour chaque interface du périphérique */
   /* Il est possible qu'un périphérique soit détruit alors qu'il ne possède aucune interface. */
   /* Ce cas peut se produire lorsqu'une interface invalide a été détectée puis désallouer avant la déconnexion */
   /* du périphérique. */
   while ( l_interface != K_MK_NULL )
   {
      /* Si l'interface est une interface de type MSC */
      if ( p_device->interfaceDescriptor->bInterfaceClass == K_MK_HCD_CLASS_MASS_STORAGE )
      {
         /* Récupération de l'adresse du périphérique MSC */
         l_mscDevice = ( T_mkMSCDevice* ) l_interface->child;

         /* Si au moins un disque est présent sur l'interface */
         if ( ( l_mscDevice != K_MK_NULL ) && ( l_mscDevice->disk != K_MK_NULL ) )
         {
            /* Actualisation de la valeur de la variable d'état */
            /* L'interface HCD ne peut pas encore être supprimée */
            *p_state = 0;
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

      /* Actualisation de la valeur du pointeur d'interface */
      l_interface = l_interface->nextInterface;
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_deleteDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable d'état */
   uint32_t l_state = 1;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Ne pas modifier l'ordre de suppression, la fonction mk_disk_delete transmet un événement */
      /* indiquant la déconnexion du périphérique aux Dispatcher. */
      l_result = mk_disk_delete ( &p_device->disk, K_MK_NULL, 1 );

      /* Si aucune erreur ne s'est produite et si la liste de disques est vide */
      if ( ( l_result == K_MK_OK ) && ( p_device->disk == K_MK_NULL ) )
      {
         /* On teste si le périphérique HCD peut être supprimé suite à la suppression du périphérique MSC */
         /* Si non, la variable state prend la valeur 0. */
         mk_msc_checkDeviceEmpty ( p_device->device, &l_state );

         /* Suppression du périphérique de la liste des périphériques MSC */
         l_result  = mk_msc_remove ( &p_handler->deletedList, p_device );

         /* Désallocation du périphérique MSC */
         l_result |= mk_pool_freeSafe ( g_mkMSCPool.pool, p_device );

         /* Si aucune erreur ne s'est produtie */
         if ( l_result == K_MK_OK )
         {
            /* Réinitialisation du pointeur de périphérique */
            p_device->device->interfaceDescriptor->child = K_MK_NULL;
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

      /* Si le périphérique HCD et ses interfaces peuvent être supprimés */
      if ( l_state == 1 )
      {
         /* Réinitialisation du drapeau de déconnexion */
         l_result = mk_event_clear ( p_device->device->flag.event, K_MK_HCD_CLASS_FLAG_MASS_STORAGE );
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


