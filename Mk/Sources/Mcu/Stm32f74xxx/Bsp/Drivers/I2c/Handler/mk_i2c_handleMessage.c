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
* @file mk_i2c_handleMessage.c
* @brief Définition de la fonction mk_i2c_handleMessage.
* @date 15 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_handleMessage ( T_mkTask* p_task, T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_status )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de travail */
   uint32_t l_area = 0, l_counter = 0;

   /* Déclaration d'une trame I2C */
   T_mkI2CFrame l_frame;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) && ( p_frame != K_MK_NULL ) )
   {
      /* Vérification de la validité du port présent en paramètre */
      l_result = mk_i2c_checkDevice ( p_handler, p_device );

      /* Si l'instance est valide */
      if ( l_result == K_MK_OK )
      {
         /* Récupération du niveau de privilège de la zone mémoire */
         l_area  = _mk_memory_isPrivilegedArea ( ( uint8_t* ) p_frame->data );
         l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) p_frame->data + p_frame->dataLength - 1 );
         l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) p_status );
         l_area |= _mk_memory_isPrivilegedArea ( ( uint8_t* ) p_status + sizeof ( T_mkI2CTransferStatus ) );

         /* Si la tâche qui souhaite envoyer une trame possède un niveau de droits suffisants */
         if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_ERROR_RIGHT;
         }

         /* Sinon */
         else
         {
            /* Si le périphérique courant doit être actualisé */
            if ( p_handler->currentDevice != p_device )
            {
               /* Reconfiguration du bus I2C selon les caractéristiques du nouveau périphérique */
               mk_i2c_init ( p_handler, &p_device->setting );

               /* Actualisation du périphérique courant */
               p_handler->currentDevice = p_device;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Effectue */
            do
            {
               /* Copie de la trame I2C utilisateur dans une variable de travail */
               _copy ( &l_frame, p_frame, sizeof ( T_mkI2CFrame ) );

               /* Transmission de la trame sur le port I2C */
               l_result = mk_i2c_send ( p_handler, p_device, &l_frame, p_status );

               /* Note : présence d'erreur ponctuelle (1/50) au démarrage du système. */
               /* Le périphérique ne répond pas (NAK - cf. mk_i2c_handleMasterInterrupt). Une réinitialisation du port est nécessaire. */
               /* Réalisation d'un cortex_resetSystem au démarrage pour mettre en évidence le problème. */

               /* Si une erreur s'est produite */
               if ( l_result != K_MK_OK )
               {
                  /* Réinitialisation du bus I2C */
                  mk_i2c_init ( p_handler, &p_device->setting );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Actualisation du compteur */
               l_counter++;
            }

            /* Tant que le quota de ré-émission n'a pas été atteint ou tant que la transmission n'a pas réussie. */
            while ( ( l_result != K_MK_OK ) && ( l_counter < K_MK_I2C_TIMEOUT_COUNT ) );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

