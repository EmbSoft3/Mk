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
* @file mk_usbfs_taskHostMode.c
* @brief Définition de la fonction mk_usbfs_taskHostMode.
* @date 25 août 2019
*
* @todo Modifier cet algorithme lors de l'implémentation du mode host sur le périphérique FS.
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_usbfs_initUSBOTGFS ( T_mkTermio* p_termio, T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire USB */
   _writeWords ( p_handler, 0, sizeof ( T_mkHCDHandler ) >> 2 );

   /* Initialisation du gestionnaire USB */
   l_result = mk_hcd_initHandler ( p_handler, K_USB_OTGFS );

   /* Si l'initialisation a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Configuration de la structure de données du terminal */
      l_result = mk_termio_setChild ( p_termio, ( T_mkHCDHandler* ) p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation des broches GPIO du bus USB */
         mk_usb_initGPIO ( K_USB_OTGFS );

         /* Initialisation du coeur USB_OTGFS */
         l_result = mk_usb_initCore ( K_USB_OTGFS );
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

static T_mkCode mk_usbfs_handleHost ( T_mkTermio* p_termio, T_mkHCDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pipe */
   T_mkHCDPipe l_pipe;

   /* Ouverture du pipe de gestion des périphériques */
   /* Ce pipe ne sera jamais fermé pour conserver un canal disponible lors de l'énumération. */
   /* Les canaux peuvent être ouvert par d'autres tâches */
   l_result = mk_hcd_openPipe ( p_handler, &l_pipe, K_MK_HCD_ENDPOINT_CONTROL, K_MK_HCD_ENDPOINT0, K_MK_HCD_DEFAULT_MAX_PACKET_SIZE, K_MK_HCD_TIMEOUT );

   /* Boucle tant qu'une erreur critique n'est détectée */
   while ( ( l_result & ( T_mkCode ) ( ~ ( K_MK_ERROR_TIMEOUT | K_MK_ERROR_COMM ) ) ) == K_MK_OK )
   {
      /* Gestion des événements de type host */
      l_result = mk_hcd_handleHostEvent ( p_termio, p_handler, &l_pipe );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

void mk_usbfs_taskHostMode ( T_mkAddr p_param )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un gestionnaire de périphériques USB */
   T_mkHCDHandler l_handler;

   /* Déclaration des variables de travail */
   uint32_t l_mode, l_usbEvent;

   /* Initialisation du gestionnaire USB et du périphérique USB_OTGFS */
   l_result = mk_usbfs_initUSBOTGFS ( ( T_mkTermio* ) p_param, &l_handler );

   /* Si l'intialisation du gestionnaire a réussi */
   if ( l_result == K_MK_OK )
   {
      /* Tant que la broche ID_PIN n'a pas changé d'état, laisser */
      /* la main à une autre tâche. */
      l_result = mk_event_wait ( l_handler.portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR |
                                 K_MK_HCD_ID_PIN_EVENT, &l_usbEvent, K_MK_TASK_WAIT_FOREVER );

      /* Si au moins un événement est disponible et si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_usbEvent == K_MK_HCD_ID_PIN_EVENT ) )
      {
         /* Sélection du mode de fonctionnnement (host ou device ) puis initialisation du périphérique */
         l_result = mk_usb_selectMode ( K_USB_OTGFS, &l_mode );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si le mode host a été activé */
            if ( l_mode == K_USB_HOST_MODE )
            {
               /* Exécution de l'algorithme de gestion du mode host */
               /* Le résultat de la fonction n'est pas vérifié car l'intégrité du système n'est plus garantie. */
               ( void ) mk_usbfs_handleHost ( ( T_mkTermio* ) p_param, &l_handler );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
               /* Une erreur critique s'est produite, le mode attendu était le mode 'Host', le terminal va */
               /* s'auto-détruire */
               /* Il n'y a donc aucun traitement particulier à réaliser. */
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Une erreur critique s'est produite. */
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* Une erreur critique s'est produite. */
      }
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
      /* Le coeur USB n'a pas été initialisé. */
   }

   /* Désactivation de l'alimentation du bus */
   usb_disablePower ( K_USB_OTGFS );

   /* Désactivation des interruptions USB */
   usb_maskInterrupts ( K_USB_OTGFS );

   /* Une erreur grave vient de se produire. */
   /* La destruction du terminal est de la responsabilité du superviseur. */
   /* Les données internes seront automatiquement libérées car elles sont allouées dans la stack du terminal. */
   /* Les pool seront réinitialisées si le terminal est relancé. */
   ( void ) mk_termio_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Retour */
   return;
}



