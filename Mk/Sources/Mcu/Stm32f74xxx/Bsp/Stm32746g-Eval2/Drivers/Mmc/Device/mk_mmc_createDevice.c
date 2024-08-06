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
* @file mk_mmc_createDevice.c
* @brief Définition de la fonction mk_mmc_createDevice.
* @date 20 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_mmc_setDiskIdentifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de la valeur de l'identifiant en fonction de son adresse */
   *p_identifier = ( uint16_t ) ( ( K_MK_DISK_MAX_NUMBER - 1 ) - ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_createDevice ( T_mkMMCHandler* p_handler, T_mkMMCDevice** p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de travail */
   char8_t l_strIdentifier [ 4 ] = "";

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Allocation d'un nouveau périphérique MMC */
      l_result = mk_pool_allocSafe ( g_mkMMCPool.pool, ( T_mkAddr* ) p_device, K_MK_POOL_CLEAR, 0 );

      /* Si l'allocation a réussi */
      if ( ( l_result == K_MK_OK ) && ( ( *p_device ) != K_MK_NULL ) )
      {
         /* Enregistrement de l'adresse du gestionnaire de périphériques */
         (*p_device)->handler = p_handler;

         /* Configuration du type de périphérique */
         (*p_device)->layer.type = K_MK_DISK_TYPE_MMC_DEVICE;

         /* Ajout du nouveau périphérique dans la liste des périphériques */
         l_result = mk_mmc_add ( &p_handler->list, ( *p_device ) );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Allocation d'un disque */
            l_result = mk_pool_allocSafe ( g_mkDiskPool.pool, ( T_mkAddr* ) &(*p_device)->disk, K_MK_POOL_CLEAR, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Configuration du contrôle applicatif */
               ( *p_device )->disk->layer.type = K_MK_CONTROL_DISK;

               /* Enregistrement de l'adresse du périphérique */
               ( *p_device )->disk->device = *p_device;

               /* Configuration du type d'accès supporté */
               ( *p_device )->disk->layer.peripheralAccess = K_MK_DISK_ACCESS_TYPE_UNALIGNED;

               /* Configuration de l'identifiant du disque */
               mk_mmc_setDiskIdentifier ( &( *p_device )->disk->layer.id, ( *p_device )->disk, g_mkDiskPool.heap, sizeof ( T_mkDisk ) );

               /* Conversion et stockage de l'identifiant en chaine de caractères */
               mk_utils_itoa ( ( uint32_t ) ( *p_device )->disk->layer.id, ( T_str8 ) l_strIdentifier, 10, 1 );
               mk_utils_strcat ( ( T_str8 ) ( *p_device )->disk->name.id, ( T_str8 ) "dsk", ( T_str8 ) l_strIdentifier );

               /* Allocation d'un sémaphore */
               l_result = mk_semaphore_create ( &( *p_device )->disk->semaphore, K_MK_AREA_PROTECTED, 1, 0 );

               /* Si une erreur s'est produite */
               if ( l_result != K_MK_OK )
               {
                  /* Suppression du disque */
                  l_result |= mk_pool_freeSafe ( g_mkDiskPool.pool, ( *p_device )->disk );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}

