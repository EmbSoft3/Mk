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
* @file mk_hcd_handleHubStatus.c
* @brief Définition de la fonction mk_hcd_handleHubStatus.
* @date 13 oct. 2019
*
* @todo Rajouter la gestion des surcharges.
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkHCDDevice* mk_hcd_getDeviceByPort ( T_mkHCDDevice* p_hub, uint8_t p_port )
{
   /* Déclaration de la variable de retour */
   T_mkHCDDevice* l_result = K_MK_NULL;

   /* Déclaration d'un pointeur de périphérique */
   T_mkHCDDevice* l_device = p_hub->nextHubDevice;

   /* Pour le nombre de périphérique connecté sur le hub */
   while ( l_device != K_MK_NULL )
   {
      /* Si le périphérique analysé est le périphérique recherché */
      if ( l_device->layer.portNumber == p_port )
      {
         /* Actualisation de la variable de retour */
         l_result = l_device;

         /* Arrêt de la boucle */
         l_device = K_MK_NULL;
      }

      /* Sinon */
      else
      {
         /* Actualisation du pointeur de périphérique */
         l_device = l_device->nextDevice;
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

static T_mkCode mk_hcd_handlePortEvent ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe, uint32_t p_portNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de périphérique */
   T_mkHCDDevice* l_device;

   /* Récupération de l'intance du périphérique correspondant au port */
   l_device = mk_hcd_getDeviceByPort ( p_hub, ( uint8_t ) ( p_portNumber ) );

   /* Récupération du registre de statut du port */
   l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, ( uint16_t ) ( p_portNumber ), &p_hub->hubDescriptor->hPortStatus );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si une surcharge s'est produite sur le bus */
      if ( p_hub->hubDescriptor->hPortStatus.overCurrentIndicatorChange == 1 )
      {
         /* Désactivation de l'alimentation et gestion de la surcharge */
         l_result = mk_hcd_handlePortOvercurrentStatus ( p_hub, l_device, p_pipe, p_portNumber );
      }

      /* Sinon si un état intermédiaire non valide est présent */
      else if ( ( p_hub->hubDescriptor->hPortStatus.resetChange == 1 ) ||
              ( ( p_hub->hubDescriptor->hPortStatus.portEnableDisableChange == 1 ) && ( p_hub->hubDescriptor->hPortStatus.portEnabledDisabled == 1 ) ) )
      {
         /* Désactivation de l'alimentation du port */
         l_result = mk_hcd_handleInvalidStatus ( p_hub, l_device, p_pipe, p_portNumber );
      }

      /* Sinon si un périphérique a été connecté ou déconnecté */
      else if ( ( p_hub->hubDescriptor->hPortStatus.connectStatusChange == 1 ) || ( p_hub->hubDescriptor->hPortStatus.portEnableDisableChange == 1 ) )
      {
         /* Gestion du changement d'état */
         l_result = mk_hcd_handleConnectStatus ( p_handler, p_hub, l_device, p_pipe, p_portNumber );
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

static T_mkCode mk_hcd_handleHubEvent ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération du registre de statut du port */
   l_result = mk_hcd_getHubStatus ( p_hub, p_pipe, &p_hub->hubDescriptor->hHubStatus );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Dans le cas où le hub ne peut pas retourner le statut de surcharge au niveau du port, il actualise */
      /* le champ "overCurrent" du registre de statut du hub puis désactive l'alimentation de */
      /* tous les ports. */
      /* Dans le cas contraire, il actualise le registre de statut du port incriminé et ne modifie pas */
      /* le statut du hub */

      /* Si une surcharge s'est produite */
      if ( p_hub->hubDescriptor->hHubStatus.overCurrentChange == 1 )
      {
         /* Gestion de la surcharge */
         l_result = mk_hcd_handleHubOvercurrentStatus ( p_hub, p_pipe );
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

static T_mkCode mk_hcd_checkPowerStatus ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un variable de travail */
   uint32_t l_portNumber;

   /* Déclaration des registres de statut */
   T_mkHCDPipeStatus l_status = K_MK_HCD_FLAG_ACK; T_mkHCDPortEvent l_event;

   /* Déclaration d'un pointeur de périphérique */
   T_mkHCDDevice* l_device;

   /* Pour chaque de ports du hub */
   for ( l_portNumber = 1 ; ( l_portNumber <= p_hub->hubDescriptor->bNbrPorts ) && ( l_result == K_MK_OK ) ; l_portNumber++ )
   {
      /* Analyse du registre d'interruption pour le port courant */
      l_event = mk_hcd_getPortEvent ( p_hub->hubDescriptor->bStatusBuf, l_portNumber, l_status );

      /* Si une événement s'est produit ou s'il est temps de lire le registre de statut du port */
      if ( l_event == K_MK_HCD_PORT_EVENT_DETECTED )
      {
         /* Récupération de l'intance du périphérique correspondant au port */
         l_device = mk_hcd_getDeviceByPort ( p_hub, ( uint8_t ) ( l_portNumber ) );

         /* Récupération du registre de statut du port */
         l_result = mk_hcd_getPortStatus ( p_hub, p_pipe, ( uint16_t ) ( l_portNumber ), &p_hub->hubDescriptor->hPortStatus );

         /* Si le port n'est pas alimenté */
         if ( ( l_result == K_MK_OK ) && ( p_hub->hubDescriptor->hPortStatus.portPower == 0 ) )
         {
            /* Activation de l'alimentation du port */
            l_result = mk_hcd_handlePowerStatus ( p_hub, l_device, p_pipe, l_portNumber );
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

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hcd_handleHubStatus ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration des variables de travail */
   uint32_t l_portNumber;

   /* Déclaration des registres de statut */
   T_mkHCDPipeStatus l_status; T_mkHCDPortEvent l_event;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Lancement de la séquence de réactivation de l'alimentation des ports */
      l_result = mk_hcd_checkPowerStatus ( p_hub, p_pipe );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Récupération du registre d'interruption du hub */
         l_result = mk_hcd_getHubInterrupt ( p_hub, p_pipe, p_hub->hubDescriptor->bStatusBuf, &l_status, sizeof ( p_hub->hubDescriptor->bStatusBuf ) );

         /* Si un statut est disponible */
         if ( ( l_result == K_MK_OK ) && ( ( l_status & K_MK_HCD_FLAG_ACK ) == K_MK_HCD_FLAG_ACK ) )
         {
            /* Pour chaque de ports du hub */
            for ( l_portNumber = 1 ; ( l_portNumber <= p_hub->hubDescriptor->bNbrPorts ) && ( l_result == K_MK_OK ) ; l_portNumber++ )
            {
               /* Analyse du registre d'interruption pour le port courant */
               l_event = mk_hcd_getPortEvent ( p_hub->hubDescriptor->bStatusBuf, l_portNumber, l_status );

               /* Si une événement s'est produit ou s'il est temps de lire le registre de statut du port */
               if ( l_event == K_MK_HCD_PORT_EVENT_DETECTED )
               {
                  /* Lancement de la séquence d'analyse et de traitement des événements */
                  l_result = mk_hcd_handlePortEvent ( p_handler, p_hub, p_pipe, l_portNumber );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }
            }

            /* Analyse du registre d'interruption du hub */
            l_event = mk_hcd_getPortEvent ( p_hub->hubDescriptor->bStatusBuf, 0, l_status );

            /* Si une événement s'est produit */
            if ( l_event == K_MK_HCD_PORT_EVENT_DETECTED )
            {
               /* Lancement de la séquence d'analyse et de traitement des événements */
               l_result = mk_hcd_handleHubEvent ( p_hub, p_pipe );
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


