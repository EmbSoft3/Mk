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
* @file mk_hcd_handleHostMode.c
* @brief Définition de la fonction mk_hcd_handleHostMode.
* @date 24 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleHostMode ( T_mkAddr p_termio, T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Désactivation de l'alimentation du bus */
   usb_disablePower ( p_handler->bus );

   /* Désactivation des interruptions USB */
   usb_maskInterrupts ( p_handler->bus );

   /* Si le terminal est le terminal HS */
   if (  p_handler->bus == K_USB_OTGHS )
   {
      /* Suppression du lien existant entre le terminal et le gestionnaire d'interruption USB */
      l_result = mk_termio_unlink ( K_MK_TERMIO_HCD_OTGHS_ID );

      /* Création d'un nouveau terminal (gestion mode device) */
      l_result |= mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HCD_OTGHS_ID, K_MK_TERMIO_TASK_PRIORITY,
                                      mk_usbhs_taskDeviceMode, g_mkUSBHSDeviceStackAddr, K_MK_USBHS_DEVICE_STACK_SIZE );
   }

   /* Sinon (FS) */
   else
   {
      /* Suppression du lien existant entre le terminal et le gestionnaire d'interruption USB */
      l_result = mk_termio_unlink ( K_MK_TERMIO_HCD_OTGFS_ID );

      /* Création d'un nouveau terminal (gestion mode device) */
      l_result |= mk_termio_create ( K_MK_NULL, K_MK_TERMIO_HCD_OTGFS_ID, K_MK_TERMIO_TASK_PRIORITY,
                                      mk_usbfs_taskDeviceMode, g_mkUSBFSDeviceStackAddr, K_MK_USBFS_DEVICE_STACK_SIZE );
   }

   /* Destruction du terminal */
   /* Les données internes seront automatiquement libérées car elles sont allouées dans la stack du terminal. */
   /* Les pool seront réinitialisées si le terminal est relancé. */
   /* Le résultat n'est pas vérifié car la tâche est terminée après cette fonction. */
   l_result |= mk_termio_delete ( ( T_mkTermio* ) p_termio );

   /* Retour */
   return ( l_result );
}


