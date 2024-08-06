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
* @file mk_msc_initHandler.c
* @brief Définition de la fonction mk_massStorage_initHandler.
* @date 16 mai 2020
*
*/

#include "mk_msc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_msc_handleSignal ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Positionnement de l'événement MSC */
   l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_MSC );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Attente de l'intialisation du dispatcher et du terminal USB */
      l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_USBHS | K_MK_TERMIO_FLAG_DISPATCHER, &l_event, K_MK_TERMIO_INIT_TIMEOUT );
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

static T_mkCode mk_msc_initPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des périphériques MSC */
   l_result = mk_pool_initArea ( &g_mkMSCPool.area, g_mkMSCPool.heap, K_MK_MSC_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des périphérique MSC */
      l_result = mk_pool_create ( &g_mkMSCPool.area, &g_mkMSCPool.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkMSCDevice ) >> 2, K_MK_MSC_MAX_DEVICE_NUMBER );
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

static T_mkCode mk_msc_initMessagePool ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du terminal MSC (depuis le terminal HCD). */
   p_handler->messageArea = &g_mkMSCMessageArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->messageArea->area, p_handler->messageArea->heap, K_MK_MSC_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->messageArea->mail, K_MK_AREA_PROTECTED, &p_handler->messageArea->area, K_MK_MSC_MESSAGE_SIZE, K_MK_HCD_MAX_DEVICE_NUMBER );
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

static T_mkCode mk_msc_initRequest ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du terminal MSC (depuis le système de fichiers). */
   p_handler->requestArea = &g_mkMSCRequestArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->requestArea->area, p_handler->requestArea->heap, K_MK_DISK_REQUEST_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->requestArea->request, K_MK_AREA_UNPROTECTED, &p_handler->requestArea->area, K_MK_DISK_REQUEST_SIZE, K_MK_DISK_REQUEST_NUMBER );
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

T_mkCode mk_msc_initHandler ( T_mkMSCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la pool permettant d'allouer les périphériques MSC */
   l_result = mk_msc_initPool ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages permettant la réception des requêtes utilisateur */
      l_result = mk_msc_initRequest ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation de la boite de messages permettant la réception des requêtes HCD */
         l_result = mk_msc_initMessagePool ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Transmission d'un événement pour signaler que l'initialisation du terminal a réussi. */
            /* Attente de la fin de l'initialisation des autres terminaux. */
            l_result = mk_msc_handleSignal ( );
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

   /* Retour */
   return ( l_result );
}

