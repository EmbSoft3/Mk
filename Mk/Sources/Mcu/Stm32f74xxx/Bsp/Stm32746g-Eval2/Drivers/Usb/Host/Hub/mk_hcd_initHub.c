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
* @file mk_hcd_initHub.c
* @brief Définition de la fonction mk_hcd_initHub.
* @date 4 août 2019
*
*/

#include "mk_hcd_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_enableTTInterface ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Activation de l'interface MULTIPLE_TT */
   l_result = mk_hcd_setInterface ( p_hub, p_pipe, ( uint16_t ) p_hub->interfaceDescriptor->nextInterface->bInterfaceNumber,
              ( uint16_t ) p_hub->interfaceDescriptor->nextInterface->bAlternateSetting );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Désallocation de l'interface non utilisée */
      l_result = mk_hcd_deleteUnusedInterfaces ( p_hub, p_hub->interfaceDescriptor->nextInterface );
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

static void mk_hcd_checkLSInterface ( T_mkHCDDevice* p_hub )
{
   /* Si l'interface par défaut et la terminaison ne sont pas conforme */
   if ( ( p_hub->interfaceDescriptor->nextInterface != K_MK_NULL ) || ( p_hub->interfaceDescriptor->bNumEndpoints != 1 ) ||
        ( p_hub->interfaceDescriptor->endpoint == K_MK_NULL ) || ( ( p_hub->interfaceDescriptor->endpoint->bmAttributes & 0x3 ) != K_USB_INTERRUPT_ENDPOINT ) ||
        ( p_hub->interfaceDescriptor->endpoint->bInterval == 0 ) || ( ( p_hub->layer.speed == K_USB_HIGH_SPEED ) && ( p_hub->interfaceDescriptor->endpoint->bInterval > 16 ) ) )
   {
      /* Actualisation de l'état du périphérique */
      p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon, on ne fait rien car l'interface est sélectionnée par défaut */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hcd_checkHSInterface ( T_mkHCDDevice* p_hub )
{
   /* Si l'interface alternative et la terminaison ne sont pas conforme */
   if ( ( p_hub->interfaceDescriptor->nextInterface == K_MK_NULL ) || ( p_hub->interfaceDescriptor->nextInterface->bNumEndpoints != 1 ) ||
        ( p_hub->interfaceDescriptor->nextInterface->endpoint == K_MK_NULL ) || ( p_hub->interfaceDescriptor->nextInterface->nextInterface != K_MK_NULL ) ||
        ( ( p_hub->interfaceDescriptor->nextInterface->endpoint->bmAttributes & 0x3 ) != K_USB_INTERRUPT_ENDPOINT ) ||
        ( p_hub->interfaceDescriptor->endpoint->bInterval == 0 ) || ( ( p_hub->layer.speed == K_USB_HIGH_SPEED ) && ( p_hub->interfaceDescriptor->endpoint->bInterval > 16 ) ) )
   {
      /* Actualisation de l'état du périphérique */
      p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_checkSelectHubInterface ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si 'bDeviceProtocol' égale 0 (ou 1) alors le hub est de type LS/FS (ou HS) et fonctionne en SINGLE_TT, il ne possède pas d'interface alternative */
   if ( ( ( p_hub->deviceDescriptor.bDeviceProtocol == 0 ) && ( p_hub->interfaceDescriptor->bInterfaceProtocol == 0 ) ) ||
        ( ( p_hub->deviceDescriptor.bDeviceProtocol == 1 ) && ( p_hub->interfaceDescriptor->bInterfaceProtocol == 0 ) ) )
   {
      /* Vérification de la conformité de l'interface LS/FS */
      mk_hcd_checkLSInterface ( p_hub );
   }

   /* Sinon si 'bDeviceProtocol' égale 2 alors le hub est de type HS et fonctionne en SINGLE_TT ou MULTIPLE_TT, il possède une interface alternative permettant */
   /* la sélection de la configuration MULTIPLE_TT. */
   else if ( ( p_hub->deviceDescriptor.bDeviceProtocol == 2 ) && ( p_hub->interfaceDescriptor->bInterfaceProtocol == 1 ) )
   {
      /* Vérification de la conformité de l'interface LS/FS */
      mk_hcd_checkHSInterface ( p_hub );

      /* Si l'interface HS est conforme */
      if ( p_hub->state != K_MK_HCD_DEVICE_NOT_VALID )
      {
         /* Activation de l'interface 'MULTIPLE_TT' */
         l_result = mk_hcd_enableTTInterface ( p_hub, p_pipe );
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
      /* Actualisation de l'état du périphérique */
      p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_selectHubInterface ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le descripteur de périphérique est valide */
   if ( ( p_hub->deviceDescriptor.bDeviceProtocol == 0 ) || ( p_hub->deviceDescriptor.bDeviceProtocol == 1 ) ||
        ( p_hub->deviceDescriptor.bDeviceProtocol == 2 ) )
   {
      /* Vérification de la valeur du champ 'bDeviceProtocol' en fonction de la vitesse du périphérique */
      if ( ( ( ( p_hub->deviceDescriptor.bDeviceProtocol == 1 ) || ( p_hub->deviceDescriptor.bDeviceProtocol == 2 ) ) && ( p_hub->layer.speed == K_USB_HIGH_SPEED ) ) ||
             ( ( p_hub->deviceDescriptor.bDeviceProtocol == 0 ) && ( ( p_hub->layer.speed == K_USB_LOW_SPEED ) || ( p_hub->layer.speed == K_USB_FULL_SPEED ) ) ) )
      {
         /* Vérification du nombre d'interfaces du hub */
         if ( ( p_hub->configurationDescriptor.bNumInterfaces == 1 ) && ( p_hub->interfaceDescriptor != K_MK_NULL ) )
         {
            /* Sélection de l'interface adéquate (SINGLE_TT, MULTIPLE_TT) et suppression des interfaces non utilisées */
            l_result = mk_hcd_checkSelectHubInterface ( p_hub, p_pipe );
         }

         /* Sinon */
         else
         {
            /* Actualisation de l'état du périphérique */
            p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
         }
      }

      /* Sinon */
      else
      {
         /* Actualisation de l'état du périphérique */
         p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
      }
   }

   /* Sinon */
   else
   {
      /* Actualisation de l'état du périphérique */
      p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_checkPowerSource ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Cette fonction vérifie la validité de la combinaison 'bMaxPower','bmAttribute' et'selfPowered' */
   /* Ces 3 champs permettent de connaitre la méthode d'alimentation du périphérique selon la table de vérité suivante. */

   /* Si bMaxPower  = 0, bmAttribute = 1 et selfPowered = 1   alors le périphérique est de type 'SelfPoweredOnly' */
   /* Si bMaxPower >= 0, bmAttribute = 0 et selfPowered = n/a alors le périphérique est de type 'BusPoweredOnly' */

   /* Si bMaxPower >= 0, bmAttribute = 1 alors le périphérique peut fonctionner en 'SelfAndBusPowered'. La valeur du champ 'SelfPowered' */
   /* indique la source courante d'alimentation. Si selfPowered = 0 alors le bus alimente le périphérique, sinon le périphérique est alimentée */
   /* de manière externe. */

   /* De manière générale, cette logique n'est pas respectée par tous les périphériques USB sur le marché. */

   /* Récupération du status du Hub */
   l_result = mk_hcd_getDeviceStatus ( p_hub, p_pipe, &p_hub->status );

   /* Si une combinaison invalide est présente */
   if ( ( ( p_hub->configurationDescriptor.bMaxPower == 0 ) && ( ( p_hub->configurationDescriptor.bmAttributes & 0x40 ) == 0 ) ) ||
        ( ( p_hub->configurationDescriptor.bMaxPower == 0 ) && ( ( p_hub->configurationDescriptor.bmAttributes & 0x40 ) == 0x40 ) && ( p_hub->status.selfPowered == 0 ) ) )
   {
      /* Actualisation de l'état du périphérique */
      p_hub->state = K_MK_HCD_DEVICE_NOT_VALID;
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

static T_mkCode mk_hcd_enablePower ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable de comptage */
   uint32_t l_port;

   /* Pour le nombre de port sur le hub */
   for ( l_port = 1 ; ( l_port <= p_hub->hubDescriptor->bNbrPorts ) && ( l_result == K_MK_OK ) ; l_port++ )
   {
      /* Activation de l'alimentation sur le port USB */
      l_result = mk_hcd_setPortFeature ( p_hub, p_pipe, ( uint16_t ) K_MK_HCD_PORT_POWER, ( uint16_t ) ( l_port ) );
   }

   /* Attente de la stabilisation de l'alimentation */
   l_result |= mk_task_sleep ( ( uint32_t ) ( ( uint32_t ) ( p_hub->hubDescriptor->bPwrOn2PwrGood ) * 2 ) + 200 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hcd_setHub ( T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Récupération du descripteur de Hub */
   l_result = mk_hcd_getHubDescriptor ( p_hub, p_pipe );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Activation de l'alimentation sur chaque port du hub */
      l_result = mk_hcd_enablePower ( p_hub, p_pipe );
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

T_mkCode mk_hcd_initHub ( T_mkHCDHandler* p_handler, T_mkHCDDevice* p_hub, T_mkHCDPipe* p_pipe )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_hub != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Vérification et configuration d'une interface pour le hub */
      l_result = mk_hcd_selectHubInterface ( p_hub, p_pipe );

      /* Si aucune erreur ne s'est produite et si le périphérique est valide */
      if ( ( l_result == K_MK_OK ) && ( p_hub->state == K_MK_HCD_DEVICE_CONFIGURED_STATE ) )
      {
         /* Vérification des caractéristiques d'alimentation */
         l_result = mk_hcd_checkPowerSource ( p_hub, p_pipe );

         /* Si aucune erreur ne s'est produite et si le périphérique est valide */
         if ( ( l_result == K_MK_OK ) && ( p_hub->state == K_MK_HCD_DEVICE_CONFIGURED_STATE ) )
         {
            /* Configuration du hub */
            l_result = mk_hcd_setHub ( p_hub, p_pipe );
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

      /* Si le périphérique est invalide */
      if ( p_hub->state == K_MK_HCD_DEVICE_NOT_VALID )
      {
         /* Désallocation de tous les descripteurs allouées pour le périphérique */
         /* On ne conserve que la structure T_mkHCDDevice afin de savoir que le dispositif est non valide */
         l_result = mk_hcd_deleteTree ( &p_handler->hubList, p_hub, K_MK_HCD_DELETE_PARTIAL );
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


