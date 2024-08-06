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
* @file mk_i2c_createDevice.c
* @brief Définition de la fonction mk_i2c_createDevice.
* @date 15 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_setIdentifier ( uint32_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de la valeur de l'identifiant en fonction de son adresse */
   *p_identifier = ( uint32_t ) ( ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_createDevice ( T_mkI2CHandler* p_handler, T_mkI2CDevice** p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Allocation d'un nouveau périphérique I2C */
      l_result = mk_pool_allocSafe ( g_mkI2CPool.pool, ( T_mkAddr* ) p_device, K_MK_POOL_CLEAR, 0 );

      /* Si l'allocation a réussi */
      if ( ( l_result == K_MK_OK ) && ( ( *p_device ) != K_MK_NULL ) )
      {
         /* Configuration de l'identifiant du périphérique */
         mk_i2c_setIdentifier ( &( *p_device )->identifier, ( *p_device ), g_mkI2CPool.heap, sizeof ( T_mkI2CDevice ) );

         /* Ajout du nouveau périphérique dans la liste des périphériques */
         l_result = mk_i2c_add ( &p_handler->list, ( *p_device ) );

         /* Si l'ajout du périphérique dans la liste a échoué */
         if ( l_result != K_MK_OK )
         {
            /* Désallocation du périphérique I2C */
            l_result = mk_pool_freeSafe ( g_mkI2CPool.pool, *p_device );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


