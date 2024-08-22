/**
*
* @copyright Copyright (C) 2019 RENARD Mathieu. All rights reserved.
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
* @file mk_hcd_initArea.c
* @brief Définition de la fonction mk_hcd_initArea.
* @date 28 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_initArea ( void )
{
   /* Initialisation de la zone mémoire dédiées à l'allocation des objets USB */
   T_mkCode l_result = mk_pool_initArea ( &g_mkHCDPool.area, g_mkHCDPool.buf, K_MK_HCD_POOL_SIZE );

   /* Si l'initialisation a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des périphériques USB */
      l_result = mk_pool_create ( &g_mkHCDPool.area, &g_mkHCDPool.devicePool, K_MK_AREA_PROTECTED, sizeof ( T_mkHCDDevice) >> 2, K_MK_HCD_MAX_DEVICE_NUMBER );

      /* Si l'initialisation a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire d'allocation dynamique des interfaces USB */
         l_result = mk_pool_create ( &g_mkHCDPool.area, &g_mkHCDPool.interfacePool, K_MK_AREA_PROTECTED, sizeof ( T_mkHCDInterfaceDescriptor ) >> 2, K_MK_HCD_MAX_INTERFACE_NUMBER );

         /* Si l'initialisation a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation du gestionnaire d'allocation dynamique des terminaisons USB */
            l_result = mk_pool_create ( &g_mkHCDPool.area, &g_mkHCDPool.endpointPool, K_MK_AREA_PROTECTED, sizeof ( T_mkHCDEndpointDescriptor ) >> 2, K_MK_HCD_MAX_ENDPOINT_NUMBER );

            /* Si l'initialisation a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Initialisation du gestionnaire d'allocation dynamique des hub USB */
               l_result = mk_pool_create ( &g_mkHCDPool.area, &g_mkHCDPool.hubPool, K_MK_AREA_PROTECTED, sizeof ( T_mkHCDHubDescriptor ) >> 2, K_MK_HCD_MAX_HUB_NUMBER );
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


