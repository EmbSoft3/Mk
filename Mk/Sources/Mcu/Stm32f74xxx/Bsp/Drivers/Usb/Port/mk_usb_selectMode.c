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
* @file mk_usb_selectMode.c
* @brief Définition de la fonction mk_usb_selectMode.
* @date 11 juin 2019
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_usb_selectMode ( T_mkAddr p_usb, uint32_t* p_status )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Désactivation de l'alimentation */
   usb_disablePower ( p_usb );

   /* Attente 50 ms */
   l_result = mk_task_sleep ( 50 );

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_status != K_MK_NULL ) )
   {
      /* Récupération du mode de fonctionnement du */
      /* coeur USB */
      *p_status = usb_getMode ( p_usb );

      /* Si le périphérique doit être initialisé en mode 'Host' */
      if ( ( *p_status ) == K_USB_HOST_MODE )
      {
         /* Configuration du mode host */
         l_result = mk_usb_initHost ( p_usb );
      }

      /* Sinon */
      else
      {
         /* Configuration du mode device */
         l_result = mk_usb_initDevice ( p_usb );
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


