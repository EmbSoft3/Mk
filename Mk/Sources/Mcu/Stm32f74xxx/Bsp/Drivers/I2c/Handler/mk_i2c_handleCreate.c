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
* @file mk_i2c_handleCreate.c
* @brief Définition de la fonction mk_i2c_handleCreate.
* @date 15 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_copyParam ( T_mkI2CDevice* p_device, T_mkI2CSetting* p_setting )
{
   /* Copie des paramètres de configuration dans la structure I2C */
   p_device->setting.portNumber = ( uint32_t ) ( p_setting->portNumber );
   p_device->setting.slaveAddr = ( uint32_t ) ( p_setting->slaveAddr & 0x3FF );
   p_device->setting.deviceAddr1 = ( uint32_t ) ( p_setting->deviceAddr1 & 0x3FF );
   p_device->setting.deviceAddr2 = ( uint32_t ) ( p_setting->deviceAddr2 & 0x3FF );
   p_device->setting.addressLength = ( uint32_t ) ( p_setting->addressLength & 0x1 );
   p_device->setting.mainPrescaler = ( uint32_t ) ( p_setting->mainPrescaler & 0xF );
   p_device->setting.clockLowPrescaler = ( uint32_t ) ( p_setting->clockLowPrescaler & 0xFF );
   p_device->setting.clockHighPrescaler = ( uint32_t ) ( p_setting->clockHighPrescaler & 0xFF );
   p_device->setting.dataSetupTime = ( uint32_t ) ( p_setting->dataSetupTime & 0xF );
   p_device->setting.dataHoldTime = ( uint32_t ) ( p_setting->dataHoldTime & 0xF );
   p_device->setting.enableStretching = ( uint32_t ) ( p_setting->enableStretching & 0x1 );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_handleCreate ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device, T_mkI2CSetting* p_setting )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Si les paramètre sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_setting != K_MK_NULL ) )
   {
      /* Récupération du niveau de privilège de la zone mémoire */
      l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) ( *p_device ) );

      /* Si la tâche qui souhaite ouvrir le port possède un niveau de droits suffisants */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( ( p_handler->right == K_MK_I2C_RIGHT_PROTECTED ) || ( l_area != K_MK_AREA_UNPROTECTED ) ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_RIGHT;
      }

      /* Sinon */
      else
      {
         /* Si le port de communication doit être ouvert en mode esclave */
         if ( ( p_setting->deviceAddr1 != 0 ) || ( p_setting->deviceAddr2 != 0 ) )
         {
            /* Si la liste des port I2C est vide */
            if ( p_handler->list.first == K_MK_NULL )
            {
               /* Création d'un nouveau périphérique I2C */
               l_result = mk_i2c_createDevice ( p_handler, p_device );
            }

            /* Sinon */
            else
            {
               /* La liste n'est pas vide */
               /* Au moins un port configuré en maitre/esclave est présent */
               l_result = K_MK_ERROR_NOT_SUPPORTED;
            }
         }

         /* Sinon (mode maitre) */
         else
         {
            /* Si la liste est non vide et si aucun port esclave n'a été créé */
            if ( ( p_handler->list.first == K_MK_NULL ) ||
               ( ( p_handler->list.first != K_MK_NULL ) &&
               ( ( p_handler->list.first->setting.deviceAddr1 == 0 ) && ( p_handler->list.first->setting.deviceAddr2 == 0 ) ) ) )
            {
               /* Création d'un nouveau périphérique I2C */
               l_result = mk_i2c_createDevice ( p_handler, p_device );
            }

            /* Sinon */
            else
            {
               /* La liste n'est pas vide */
               /* Un port configuré en esclave est présent */
               l_result = K_MK_ERROR_NOT_SUPPORTED;
            }
         }

         /* Si le périphérique I2C a été alloué */
         if ( l_result == K_MK_OK )
         {
            /* Copie des paramètres de configuration dans le périphérique alloué */
            mk_i2c_copyParam ( *p_device, p_setting );
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

