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
* @file mk_gpio_initHandler.c
* @brief Définition de la fonction mk_gpio_initHandler.
* @date 21 déc. 2020
*
*/

#include "mk_gpio_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_handleSignal ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Attente de l'intialisation du dispatcher et du terminal I2C1 */
   l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_DISPATCHER, &l_event, K_MK_TERMIO_INIT_TIMEOUT );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_gpio_initRequest ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la stucture contenant les données relatives à la messagerie */
   p_handler->requestArea = &g_mkGPIORequestArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->requestArea->area, p_handler->requestArea->heap, K_MK_GPIO_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->requestArea->request, K_MK_AREA_UNPROTECTED, &p_handler->requestArea->area, K_MK_GPIO_MESSAGE_SIZE, K_MK_GPIO_MESSAGE_NUMBER );
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

T_mkCode mk_gpio_initHandler ( T_mkGPIOHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des identifiants de contrôle applicatif */
   p_handler->ctrl.layer.type = K_MK_CONTROL_GPIO;
   p_handler->ctrl.layer.id = 0;

   /* Initialisation des champs d'événements */
   p_handler->ctrl.currentEvent = 0;
   p_handler->ctrl.lastEvent = ( uint32_t ) ( g_mkGPIOSettingTable [ K_MK_GPIO_SDCARD_DETECT ] << K_MK_GPIO_SDCARD_DETECT ) |
                               ( uint32_t ) ( g_mkGPIOSettingTable [ K_MK_GPIO_USER_PUSHBUTTON ] << K_MK_GPIO_USER_PUSHBUTTON );

   /* Initialisation de la messagerie du terminal */
   l_result = mk_gpio_initRequest ( p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Attente de la fin de l'initialisation des autres terminaux (I2C1 et DISPATCHER) */
      l_result = mk_gpio_handleSignal ( );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( l_result );
}
