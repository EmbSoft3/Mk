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
* @file mk_msc_initDevice.c
* @brief Définition de la fonction mk_msc_initDevice.
* @date 17 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_initDevice ( T_mkMSCHandler* p_handler, T_mkMSCDevice* p_mscDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_mscDevice != K_MK_NULL ) )
   {
      /* Ouverture d'un pipe */
      l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler, &p_mscDevice->ctrlPipe, K_MK_HCD_ENDPOINT_CONTROL, K_MK_HCD_ENDPOINT0,
                                   p_mscDevice->device->deviceDescriptor.bMaxPacketSize0, K_MK_HCD_TIMEOUT );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Recherche et initialisation d'une interface supporté par le système */
         l_result = mk_msc_selectInterface ( p_mscDevice, &p_mscDevice->ctrlPipe );

         /* Récupération du nombre d'unités logiques */
         l_result |= mk_msc_getMaxLUN ( p_mscDevice, &p_mscDevice->ctrlPipe, &p_mscDevice->layer.numberOfLUN );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de l'état du périphérique */
            p_mscDevice->state = K_MK_MSC_DEVICE_CONFIGURED_STATE;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Fermeture du pipe (cette fonction ne modifie pas le statut du pipe */
         l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_mscDevice->device->handler, &p_mscDevice->ctrlPipe );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si le périphérique doit être supprimé */
      if ( p_mscDevice->state != K_MK_MSC_DEVICE_CONFIGURED_STATE )
      {
         /* Suppression du périphérique et de son interface */
         l_result |= mk_msc_deleteDeviceByInterface ( p_handler, p_mscDevice );
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
