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
* @file mk_msc_selectInterface.c
* @brief Définition de la fonction mk_msc_selectInterface.
* @date 19 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_checkBulkOnlyDescriptor ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe, T_mkHCDInterfaceDescriptor* p_interface )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Le protocole BBB demande la présence de deux terminaisons de type BULK */
   /* Recherche de la terminaison BULK de type IN */
   l_result = mk_hcd_searchEndpoint ( p_interface, &p_mscDevice->inEndpoint, K_USB_BULK_ENDPOINT, K_USB_IN_ENDPOINT );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Recherche de la terminaison BULK de type OUT */
      l_result = mk_hcd_searchEndpoint ( p_interface, &p_mscDevice->outEndpoint, K_USB_BULK_ENDPOINT, K_USB_OUT_ENDPOINT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Vérification de la présence des terminaisons BULK IN et BULK OUT */
         if ( ( p_mscDevice->outEndpoint != K_MK_NULL ) && ( p_mscDevice->inEndpoint != K_MK_NULL ) )
         {
            /* Si l'interface est une interface de type alternative */
            if ( p_interface->bAlternateSetting != 0 )
            {
               /* Activation de l'interface alternative */
               l_result = mk_hcd_setInterface ( p_mscDevice->device, p_pipe, ( uint16_t ) p_interface->bInterfaceNumber,
                          ( uint16_t ) p_interface->bAlternateSetting );
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

T_mkCode mk_msc_selectInterface ( T_mkMSCDevice* p_mscDevice, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'interface */
   T_mkHCDInterfaceDescriptor* l_interface = p_mscDevice->interface;

   /* Basculement de l'état du périphérique */
   p_mscDevice->state |= K_MK_MSC_DEVICE_NOT_SUPPORTED;

   /* Pour la première interface et toute les interfaces alternatives */
   do
   {
      /* Recherche d'une interface supportant le protocole 'BULK-ONLY' */
      if ( l_interface->bInterfaceProtocol == K_MK_MSC_PROTOCOL_BBB )
      {
         /* Analyse de la validité de l'interface */
         l_result = mk_msc_checkBulkOnlyDescriptor ( p_mscDevice, p_pipe, l_interface );

         /* Si l'interface est valide */
         if ( ( l_result == K_MK_OK ) && ( p_mscDevice->outEndpoint != K_MK_NULL ) && ( p_mscDevice->inEndpoint != K_MK_NULL ) )
         {
            /* On arrête le processus et on bascule l'état du périphérique sans condition */
            /* Si la fonction précédente a échoué, la cause de l'erreur est interne et n'est pas induite par le périphérique. */
            /* Le terminal va donc s'arrêter. */

            /* Enregistrement de l'adresse de l'interface à utiliser */
            p_mscDevice->interface = l_interface;

            /* Basculement de l'état du périphérique */
            p_mscDevice->state &= ( T_mkStorageDeviceState ) ( ~K_MK_MSC_DEVICE_NOT_SUPPORTED );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }

      /* Note */
      /* Cette section peut être étendue dans le cas où d'autres protocoles sont supportés. */

      /* Sinon */
      else
      {
         /* Actualisation de l'interface courante */
         l_interface = l_interface->nextInterface;
      }
   }

   /* Pour chaque interface du périphérique (nominale et alternative) */
   while ( ( l_interface->bAlternateSetting != 0 ) && ( l_interface != K_MK_NULL ) && ( ( p_mscDevice->state & K_MK_MSC_DEVICE_NOT_SUPPORTED ) == K_MK_MSC_DEVICE_NOT_SUPPORTED ) );

   /* Retour */
   return ( l_result );
}
