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
* @file mk_termio_unlink.c
* @brief Définition de la fonction mk_termio_unlink.
* @date 10 juin 2019
*
*/

#include "mk_termio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_termio_unlink ( T_mkTermioIdentifier p_id )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le terminal est assigné au périphérique USB_OTGHS */
   if ( p_id == K_MK_TERMIO_HCD_OTGHS_ID )
   {
      /* Désactivation de la requête d'interruption USB_OTGHS */
      nvic_disableRequest ( K_NVIC_USB_OTGHS );

      /* Suppression du lien */
      g_mkTermioHandler.usbhs = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné au périphérique USB_OTGHS */
   else if ( p_id == K_MK_TERMIO_HCD_OTGFS_ID )
   {
      /* Désactivation de la requête d'interruption USB_OTGHS */
      nvic_disableRequest ( K_NVIC_USB_OTGFS );

      /* Suppression du lien */
      g_mkTermioHandler.usbfs = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche USB_HID */
   else if ( p_id == K_MK_TERMIO_HID_ID )
   {
      /* Suppression du lien */
      g_mkTermioHandler.usbhid = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche USB_MSC */
   else if ( p_id == K_MK_TERMIO_MSC_ID )
   {
      /* Suppression du lien */
      g_mkTermioHandler.msc = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche MMC */
   else if ( p_id == K_MK_TERMIO_MMC_ID )
   {
      /* Désactivation de la requête d'interruption MMC */
      nvic_disableRequest ( K_NVIC_SDMMC1 );

      /* Suppression du lien */
      g_mkTermioHandler.mmc = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche GPIO */
   else if ( p_id == K_MK_TERMIO_GPIO_ID )
   {
      /* Suppression du lien */
      g_mkTermioHandler.gpio = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche I2C1 */
   else if ( p_id == K_MK_TERMIO_I2C1_ID )
   {
      /* Désactivation de la requête d'interruption I2C */
      nvic_disableRequest ( K_NVIC_I2C1_EVENT );
      nvic_disableRequest ( K_NVIC_I2C1_ERROR );

      /* Suppression du lien */
      g_mkTermioHandler.i2c1 = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche I2C2 */
   else if ( p_id == K_MK_TERMIO_I2C2_ID )
   {
      /* Désactivation de la requête d'interruption I2C */
      nvic_disableRequest ( K_NVIC_I2C2_EVENT );
      nvic_disableRequest ( K_NVIC_I2C2_ERROR );

      /* Suppression du lien */
      g_mkTermioHandler.i2c2 = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche I2C3 */
   else if ( p_id == K_MK_TERMIO_I2C3_ID )
   {
      /* Désactivation de la requête d'interruption I2C */
      nvic_disableRequest ( K_NVIC_I2C3_EVENT );
      nvic_disableRequest ( K_NVIC_I2C3_ERROR );

      /* Suppression du lien */
      g_mkTermioHandler.i2c3 = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche I2C4 */
   else if ( p_id == K_MK_TERMIO_I2C4_ID )
   {
      /* Désactivation de la requête d'interruption I2C */
      nvic_disableRequest ( K_NVIC_I2C4_EVENT );
      nvic_disableRequest ( K_NVIC_I2C4_ERROR );

      /* Suppression du lien */
      g_mkTermioHandler.i2c4 = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné au système de fichier */
   else if ( p_id == K_MK_TERMIO_FILESYSTEM_ID )
   {
      /* Suppression du lien */
      g_mkTermioHandler.fileManager [ p_id - K_MK_TERMIO_FILESYSTEM_ID ] = K_MK_NULL;
   }

   /* Sinon si le terminal est assigné à la tâche DISPATCHER */
   else if ( p_id == K_MK_TERMIO_DISPATCHER_ID )
   {
      /* Suppression du lien */
      g_mkTermioHandler.dispatcher = K_MK_NULL;
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



