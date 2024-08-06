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
* @file mk_usbhs_taskDeviceMode.c
* @brief Définition de la fonction mk_usbhs_taskDeviceMode.
* @date 24 août 2019
*
* @todo Modifier cet algorithme lors de l'implémentation du mode device.
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_usbhs_initUSBOTGHS ( T_mkTermio* p_termio, T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire USB */
   _writeWords ( p_handler, 0, sizeof ( T_mkHCDHandler ) >> 2 );

   /* Configuration de la structure de données du terminal */
   l_result = mk_termio_setChild ( p_termio, ( T_mkHCDHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire USB */
      l_result = mk_hcd_initHandler ( p_handler, K_USB_OTGHS );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation des broches GPIO du bus USB */
         mk_usb_initGPIO ( K_USB_OTGHS );

         /* Initialisation du coeur USB_OTGHS */
         l_result = mk_usb_initCore ( K_USB_OTGHS );
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
/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_usbhs_taskDeviceMode ( T_mkAddr p_param )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire de périphériques USB */
   T_mkHCDHandler l_handler;

   /* Déclaration d'une variable de travail */
   uint32_t l_usbEvent;

   /* Initialisation du gestionnaire USB et du périphérique USB_OTGHS */
   l_result = mk_usbhs_initUSBOTGHS ( ( T_mkTermio* ) p_param, &l_handler );

   /* Si l'intialisation du gestionnaire a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Tant que la broche ID_PIN n'a pas changé d'état, laisser */
      /* la main à une autre tâche. */
      ( void ) mk_event_wait ( l_handler.portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR |
                               K_MK_HCD_ID_PIN_EVENT, &l_usbEvent, K_MK_TASK_WAIT_FOREVER );

      /* Désactivation des interruptions USB */
      usb_maskInterrupts ( K_USB_OTGHS);

      /* Suppression du lien existant entre le terminal et le gestionnaire d'interruption USB */
      ( void ) mk_termio_unlink ( K_MK_TERMIO_HCD_OTGHS_ID );

      /* Création du terminal de gestion du mode host */
      ( void ) mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HCD_OTGHS_ID, K_MK_TERMIO_TASK_PRIORITY,
                                   mk_usbhs_taskHostMode, g_mkUSBHSHostStackAddr, K_MK_USBHS_HOST_STACK_SIZE );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Destruction du terminal */
   /* Les données internes seront automatiquement libérées car elles sont allouées dans la stack du terminal. */
   /* Les pool seront réinitialisées si le terminal est relancé. */
   /* Le résultat n'est pas vérifié car la tâche est terminée après cette fonction. */
   ( void ) mk_termio_delete ( ( T_mkTermio* ) p_param );

   /* Retour */
   return;
}
