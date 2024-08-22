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
* @file mk_hcd_initPort.c
* @brief Définition de la fonction mk_hcd_initPort.
* @date 6 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_resetPort ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t p_portNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter = 0; T_mkHCDPortEvent l_status = K_MK_HCD_PORT_EVENT_NOT_DETECTED;

   /* Déclaration d'une variable de statut */
   T_mkHCDPipeStatus l_pipeStatus = K_MK_HCD_NO_FLAG;

   /* Réinitialisation du port USB */
   l_result = mk_hcd_setPortFeature ( p_hub, p_pipe, ( uint16_t ) K_MK_HCD_PORT_RESET, ( uint16_t ) p_portNumber );

   /* Tant que le reset n'est pas terminé */
   while ( ( l_result == K_MK_OK ) && ( l_status == K_MK_HCD_PORT_EVENT_NOT_DETECTED ) && ( l_counter < K_HCD_HUB_PORT_RESET_TIMEOUT ) )
   {
      /* Attente 50 ms */
      l_result = mk_task_sleep ( 50 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération du registre d'interruption du Hub */
         l_result = mk_hcd_getHubInterrupt ( p_hub, p_pipe, p_hub->hubDescriptor->bStatusBuf, &l_pipeStatus, sizeof ( p_hub->hubDescriptor->bStatusBuf ) );

         /* Analyse du statut renvoyé */
         l_status = mk_hcd_getPortEvent ( p_hub->hubDescriptor->bStatusBuf, p_portNumber, l_pipeStatus );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation de la variable de comptage */
      l_counter++;
   }

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si un événement est survenu sur le hub */
      if ( l_status == K_MK_HCD_PORT_EVENT_DETECTED )
      {
         /* Récupération du registre de statut du port */
         l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, p_portNumber, &p_hub->hubDescriptor->hPortStatus );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Si le reset s'est correctement déroulé */
            if ( ( p_hub->hubDescriptor->hPortStatus.portPower == 1 ) && ( p_hub->hubDescriptor->hPortStatus.currentConnectStatus == 1 ) &&
                 ( p_hub->hubDescriptor->hPortStatus.resetChange == 1 ) && ( p_hub->hubDescriptor->hPortStatus.reset == 0 ) )
            {
               /* Réinitialisation du registre de statut */
               l_result = mk_hcd_clearPortFeature ( p_hub, p_pipe, K_MK_HCD_CHANGE_PORT_RESET, p_portNumber );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Récupération du registre de statut du port */
                  /* L'état du port USB est stocké dans la structure 'hPortStatus'. */
                  l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, p_portNumber, &p_hub->hubDescriptor->hPortStatus );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
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
         /* Actualisation de l'état du dispositif */
         p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
      }
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_checkPortState ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t p_portNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération du registre de statut du port */
   l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, ( uint16_t ) ( p_portNumber ), &p_hub->hubDescriptor->hPortStatus );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Vérification de la valeur du registre de status */
      if ( ( p_hub->hubDescriptor->hPortStatus.portPower == 1 ) && ( p_hub->hubDescriptor->hPortStatus.currentConnectStatus == 1 ) )
      {
         /* Si le bit de connexion est à réinitialiser */
         /* Lorsque le port passe dans l'état désactivé durant le runtime, ce bit n'est pas positionné au niveau logique '1' */
         if ( p_hub->hubDescriptor->hPortStatus.connectStatusChange == 1 )
         {
            /* Réinitialisation du registre de statut */
            l_result = mk_hcd_clearPortFeature ( p_hub, p_pipe, K_MK_HCD_CHANGE_PORT_CONNECTION, ( uint16_t ) ( p_portNumber ) );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Récupération du registre de statut du port */
            l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, ( uint16_t ) ( p_portNumber ), &p_hub->hubDescriptor->hPortStatus );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Vérification de la valeur du registre de status */
               if ( ( p_hub->hubDescriptor->hPortStatus.portPower != 1 ) || ( p_hub->hubDescriptor->hPortStatus.currentConnectStatus != 1 ) ||
                    ( p_hub->hubDescriptor->hPortStatus.connectStatusChange != 0 ) )
               {
                  /* Actualisation de l'état du dispositif */
                  p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
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
         /* Actualisation de l'état du dispositif */
         p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
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

T_mkCode mk_hcd_initPort ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint8_t p_portNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des variables de statut */
   T_mkHCDPipeStatus l_pipeStatus = K_MK_HCD_NO_FLAG;
   T_mkHCDPortEvent l_status = K_MK_HCD_PORT_EVENT_NOT_DETECTED;

   /* Si les paramètres sont valide */
   if ( ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_portNumber != 0 ) )
   {
      /* Récupération du statut du Hub */
      l_result = mk_hcd_getHubInterrupt ( p_hub, p_pipe, p_hub->hubDescriptor->bStatusBuf, &l_pipeStatus, sizeof ( p_hub->hubDescriptor->bStatusBuf ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Analyse du de l'état du port USB */
         l_status = mk_hcd_getPortEvent ( p_hub->hubDescriptor->bStatusBuf, ( uint32_t ) p_portNumber, l_pipeStatus );

         /* Si un périphérique est connecté sur le port */
         if ( l_status == K_MK_HCD_PORT_EVENT_DETECTED )
         {
            /* Analyse de l'état du port USB */
            l_result = mk_hcd_checkPortState ( p_hub, p_pipe, p_portNumber );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( p_hub->state == K_MK_HCD_DEVICE_DISPATCHED_STATE ) )
            {
               /* Lançement de la séquence de réinitialisation du port */
               l_result = mk_hcd_resetPort ( p_hub, p_pipe, p_portNumber );
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
            /* Actualisation du statut du port */
            p_hub->hubDescriptor->hPortStatus.currentConnectStatus = 0;
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


