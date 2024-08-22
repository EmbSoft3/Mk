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
* @file mk_hid_getReport.c
* @brief Définition de la fonction mk_hid_getReport.
* @date 11 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_getDeviceReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une requête */
   T_mkHCDRequest l_request;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Si l'utilisateur souhaite récupérer un 'Report' spécifique */
      if ( p_report != K_MK_NULL )
      {
         /* Création d'une requête de type 'GET_REPORT' */
         l_result = mk_hcd_createRequest ( &l_request, ( T_mkHCDRequestCode ) K_MK_HID_GET_REPORT, K_MK_HCD_DEVICE_TO_HOST | K_MK_HCD_CLASS | K_MK_HCD_INTERFACE,
                                         ( K_MK_HID_REPORT_INPUT | ( uint16_t ) p_report->id ), p_hidDevice->interface->bInterfaceNumber, ( uint16_t ) p_report->inputSize );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Transmission de la requête HID */
            l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_SETUP, 8 );
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
         /* La terminaison de contrôle ne doit pas être utilisée, il est inutile d'envoyer un paquet de type 'SETUP'. */
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération et des décodage du ou des reports du périphérique HID */
         l_result = mk_hid_parseInput ( p_hidDevice, p_pipe, p_report );

         /* Si aucune erreur ne s'est produite et si l'utilisateur souhaite récupérer un seul report. */
         if ( ( l_result == K_MK_OK ) && ( p_report != K_MK_NULL ) )
         {
            /* Transmission du paquet d'acquittement (ZLP) */
            l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) &l_request, K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1, 0 );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* La terminaison de contrôle ne doit pas être utilisée, il est inutile d'envoyer un paquet de type 'ZLP'. */
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


