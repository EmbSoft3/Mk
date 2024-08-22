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
* @file mk_hid_dispatchOutput.c
* @brief Définition de la fonction mk_hid_dispatchOutput.
* @date 5 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkHIDDevice* mk_hid_searchReportByAddr ( T_mkHIDDevice* p_hidDevice, T_mkHIDReport** p_report, T_mkAddr p_addr )
{
   /* Déclaration d'un pointeur de périphérique HID */
   T_mkHIDDevice *l_result = K_MK_NULL;

   /* Déclaration des pointeurs de Report */
   T_mkHIDReport *l_report, *l_resultReport = K_MK_NULL;

   /* Pour l'ensemble des périphériques HID dans la liste */
   for ( ; ( p_hidDevice != K_MK_NULL ) && ( l_resultReport == K_MK_NULL ) ; p_hidDevice = p_hidDevice->next )
   {
      /* Pour le nombre de reports dans le périphérique */
      for ( l_report = p_hidDevice->report ; ( l_report != K_MK_NULL ) && ( l_resultReport == K_MK_NULL ) ; l_report = l_report->next )
      {
         /* Si le 'Report' à actualiser a été trouvé */
         if ( l_report->addr == p_addr )
         {
            /* Mise à jour du pointeur de périphérique */
            l_result = p_hidDevice;

            /* Mise à jour du pointeur de report */
            l_resultReport = l_report;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }
      }
   }

   /* Enregistrement de l'adresse du 'Report' trouvé */
   ( *p_report ) = l_resultReport;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_dispatchOutput ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pipe */
   T_mkHCDPipe l_pipe;

   /* Déclaration d'un 'Report' */
   T_mkHIDReport* l_report;

   /* Déclaration d'un message */
   T_mkDispatcherMessage l_message;

   /* Déclaration d'un gestionnaire de dispatcher */
   T_mkDispatcherHandler* l_dispatcherHandler = K_MK_NULL;

   /* Si le paramètre est valide */
   if ( p_hidDevice != K_MK_NULL )
   {
      /* Récupération de l'adresse du dispatcher */
      l_result = mk_termio_getChild ( g_mkTermioHandler.dispatcher, ( void** ) &l_dispatcherHandler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si une sortie d'un périphérique HID doit être configurée */
         l_result = mk_mail_pend ( K_MK_NULL, l_dispatcherHandler->hidArea->mail, &l_message, 0 );

         /* Si un message est disponible */
         if ( l_result == K_MK_OK )
         {
            /* Une commande de mise à jour des sorties du périphérique HID a été reçue. */
            /* Les données ont été écrites directement dans les adresses de routage. Les terminal HID doit juste formater les données */
            /* à destination du périphérique. */

            /* Récupération de l'adresse du périphérique HID et de l'adresse du 'Report' correspondant au contrôle applicatif */
            p_hidDevice = mk_hid_searchReportByAddr ( p_hidDevice, &l_report, l_message.appCtrl );

            /* Si un périphérique HID et un 'Report' ont été trouvés */
            if ( ( p_hidDevice != K_MK_NULL ) && ( l_report != K_MK_NULL ) )
            {
               /* Il est temps d'ouvrir un 'Pipe'. Dans le cas où aucune terminaison de type INTERRUPT_OUT n'est définie */
               /* alors la terminaison de contrôle doit être utilisée */
               if ( p_hidDevice->outEndpoint != K_MK_NULL )
               {
                  /* Ouverture du pipe en mode INTERRUPT */
                  l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe, K_MK_HCD_ENDPOINT_INTERRUPT, p_hidDevice->outEndpoint->bEndpointAddress & 0xF,
                                               p_hidDevice->outEndpoint->wMaxPacketSize, K_MK_HCD_TIMEOUT );
               }

               /* Sinon */
               else
               {
                  /* Ouverture du pipe en mode CONTROL */
                  l_result = mk_hcd_openPipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe, K_MK_HCD_ENDPOINT_CONTROL, K_MK_HCD_ENDPOINT0,
                                               p_hidDevice->device->deviceDescriptor.bMaxPacketSize0, K_MK_HCD_TIMEOUT );
               }

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Mise en forme des données puis transmission de celle-ci vers le périphérique HID */
                  l_result = mk_hid_setDeviceReport ( p_hidDevice, &l_pipe, l_report );

                  /* Fermeture du pipe */
                  l_result |= mk_hcd_closePipe ( ( T_mkHCDHandler* ) p_hidDevice->device->handler, &l_pipe );
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
               /* Une erreur grave vient de se produire */
               /* Il est préférable d'arrêter le terminal */
               l_result = K_MK_ERROR_UNEXPECTED;
            }
         }

         /* Sinon si aucun message n'est disponible */
         else if ( l_result == K_MK_ERROR_TIMEOUT )
         {
            /* Actualisation de la variable de retour */
            l_result = K_MK_OK;
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
