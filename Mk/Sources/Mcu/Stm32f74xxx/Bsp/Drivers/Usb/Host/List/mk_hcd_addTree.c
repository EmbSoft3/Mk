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
* @file mk_hcd_addTree.c
* @brief Définition de la fonction mk_hcd_addTree.
* @date 27 juil. 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_addTree ( T_mkHCDDevice* p_hub, T_mkHCDDevice* p_device )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_ERROR_PARAM;

   /* Si les paramètres sont valides */
   if ( ( p_hub != K_MK_NULL ) && ( p_device != K_MK_NULL ) )
   {
      /* Si l'arbre comprend au moins un périphérique */
      if ( p_hub != p_device )
      {
         /* Si le hub possède au moins un périphérique */
         if ( p_hub->nextHubDevice != K_MK_NULL )
         {
            /* Actualisation des pointeurs de périphérique */
            /* Le périphérique est ajouté en début de liste */
            p_device->previousDevice = K_MK_NULL;
            p_device->nextDevice = p_hub->nextHubDevice;

            /* Actualisation de la chaine */
            p_hub->nextHubDevice->previousDevice = p_device;
            p_hub->nextHubDevice = p_device;
         }

         /* Sinon */
         else
         {
            /* Actualisation des pointeurs de périphérique */
            p_device->previousDevice = K_MK_NULL;
            p_device->nextDevice = K_MK_NULL;

            /* Actualisation du pointeur de chaine */
            p_hub->nextHubDevice = p_device;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Mémorisation de l'adresse du hub où le périphérique est connecté */
      p_device->previousHubDevice = p_hub;

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


