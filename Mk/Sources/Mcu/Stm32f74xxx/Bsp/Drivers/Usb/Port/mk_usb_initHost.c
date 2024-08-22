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
* @file mk_usb_initHost.c
* @brief Définition de la fonction mk_usb_initHost.
* @date 9 juin 2019
*
*/

#include "mk_usb_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_usb_initHost ( T_mkAddr p_usb )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de comptage */
   uint32_t l_counter;

   /* Activation des interruptions relatives aux canaux de communication */
   for ( l_counter = K_USB_CHANNEL0 ; l_counter <= K_USB_CHANNEL15 ; l_counter++ )
   {
      /* Note : */
      /* La configuration du registre d'interruption a un grand impact sur le déclenchement des interruptions USB */
      /* L'intégralité des interruptions d'erreurs sont activées ainsi que l'interruption CHH marquant la fin du transfert */

      /* Remarque : */
      /* Si l'interruption CHH n'est pas active, il se produit un bug lors de l'émission d'un token SSPLIT, il est émis */
      /* 5 fois de manière consécutive. */
      usb_unmaskChannelInterrupt ( p_usb, l_counter, K_USB_CHANNEL_GROUP_INTERRUPTS );
   }

   /* Activation du drapeau d'interruption globale */
   usb_unmaskGlobalChannelInterrupt ( p_usb, K_USB_MASK_CHANNEL_ALL );

   /* Activation des interruptions du mode 'Host' */
   usb_unmaskCoreInterrupts ( p_usb, K_USB_PORT_INTERRUPT | K_USB_CHANNELS_INTERRUPT );

   /* En fonction du périphérique en aval, une attente avant l'activation de l'alimentation USB est nécessaire */
   /* Dans le cas d'un hub 2x4 ports, il a été observé que les hubs s'initialisés correctement aux détriments des périphériques */
   /* connectés desssus. La première commande 'GetDeviceDescriptor' échouée systèmatiquement durant l'énumération. */
   /* Les hubs étaient de type 'HS' et les périphériques de type 'LS', la communication de type SPLIP. */
   /* Le problème se présente quand au moins deux périphériques étaient connectés sur le bus. */
   l_result = mk_task_sleep ( 1000 );

   /* Activation de l'alimentation du port USB */
   usb_enablePower ( p_usb );

   /* Ajout d'un délai pour que le périphérique s'initialise */
   l_result |= mk_task_sleep ( 100 );

   /* Retour */
   return ( l_result );
}

