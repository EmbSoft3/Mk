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
* @file mk_msc_createDevice.c
* @brief Définition de la fonction mk_msc_createDevice.
* @date 17 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_msc_createDevice ( T_mkMSCHandler* p_handler, T_mkHCDDevice* p_device, T_mkHCDInterfaceDescriptor* p_interface )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de périphériques de type MSC */
   T_mkMSCDevice* l_mscDevice = K_MK_NULL;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Allocation d'un nouveau périphérique de type MSC */
      l_result = mk_pool_allocSafe ( g_mkMSCPool.pool, ( T_mkAddr* ) &l_mscDevice, K_MK_POOL_CLEAR, 0 );

      /* Si l'allocation a réussi */
      if ( ( l_result == K_MK_OK ) && ( l_mscDevice != K_MK_NULL ) )
      {
         /* Configuration de l'adresse du périphérique enfant */
         p_interface->child = ( T_mkMSCDevice* ) l_mscDevice;

         /* Configuration du type de périphérique */
         l_mscDevice->layer.type = K_MK_DISK_TYPE_MSC_DEVICE;

         /* Enregistrement de l'adresse du périphérique USB */
         l_mscDevice->device = p_device;

         /* Enregistrement de l'adresse de l'interface */
         l_mscDevice->interface = p_interface;

         /* Ajout du nouveau périphérique dans la liste des périphériques MSC */
         l_result = mk_msc_add ( &p_handler->list, l_mscDevice );
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



