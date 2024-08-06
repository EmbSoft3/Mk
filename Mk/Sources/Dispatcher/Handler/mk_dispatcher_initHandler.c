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
* @file mk_dispatcher_initHandler.c
* @brief Définition de la fonction mk_dispatcher_initHandler.
* @date 17 nov. 2019
*
*/

#include "mk_dispatcher_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_sendSignal ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Positionnement de l'événement signalant la fin de l'initialisation du dispatcher */
   l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_DISPATCHER );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_dispatcher_initIncomingMessageArea ( T_mkDispatcherHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du dispatcher. */
   p_handler->mailArea = &g_mkDispatcherMailArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->mailArea->area, p_handler->mailArea->heap, K_MK_DISPATCHER_INCOMING_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->mailArea->mail, K_MK_AREA_PROTECTED, &p_handler->mailArea->area, K_MK_DISPATCHER_INCOMING_MESSAGE_SIZE, K_MK_DISPATCHER_MESSAGE_NUMBER );
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

static T_mkCode mk_dispatcher_initHIDMessageArea ( T_mkDispatcherHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie HID. */
   p_handler->hidArea = &g_mkDispatcherHidArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->hidArea->area, p_handler->hidArea->heap, K_MK_DISPATCHER_HID_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->hidArea->mail, K_MK_AREA_PROTECTED, &p_handler->hidArea->area, K_MK_DISPATCHER_HID_MESSAGE_SIZE, K_MK_DISPATCHER_MESSAGE_NUMBER );
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

static T_mkCode mk_dispatcher_initListenerPool ( T_mkDispatcherHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie de la tâche d'écoute. */
   p_handler->listenerArea = &g_mkDispatcherListenerArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->listenerArea->area, p_handler->listenerArea->heap, K_MK_DISPATCHER_LISTENER_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->listenerArea->mail, K_MK_AREA_PROTECTED, &p_handler->listenerArea->area, K_MK_DISPATCHER_LISTENER_MESSAGE_SIZE, K_MK_DISPATCHER_MESSAGE_NUMBER );
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

static T_mkCode mk_dispatcher_initDiskPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des disques */
   l_result = mk_pool_initArea ( &g_mkDiskPool.area, g_mkDiskPool.heap, K_MK_DISK_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des disques */
      l_result = mk_pool_create ( &g_mkDiskPool.area, &g_mkDiskPool.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkDisk ) >> 2, K_MK_DISK_MAX_NUMBER );
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

static T_mkCode mk_dispatcher_initVolumePool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des partitions */
   l_result = mk_pool_initArea ( &g_mkVolumePool.area, g_mkVolumePool.heap, K_MK_VOLUME_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des partitions */
      l_result = mk_pool_create ( &g_mkVolumePool.area, &g_mkVolumePool.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkVolume ) >> 2, K_MK_VOLUME_MAX_NUMBER );
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

static void mk_dispatcher_initAttributes ( T_mkDispatcherHandler* p_handler )
{
   /* Initialisation des attributs de configuration du dispatcher */
   p_handler->attribute.stickResolution = K_MK_STICK_DEFAULT_RESOLUTION;
   p_handler->attribute.pointerResolution = K_MK_POINTER_DEFAULT_RESOLUTION;
   p_handler->attribute.keyboardHoldRate = K_MK_KEYBOARD_HOLD_RATE;
   p_handler->attribute.keyboardInhibitionDuration = K_MK_KEYBOARD_HOLD_INHIBITION_DURATION;
   p_handler->attribute.mouseCursorLayer = K_MK_GRAPHICS_FOREGROUND;
   p_handler->attribute.mouseCursorVisibility = K_MK_FIELD_VISIBLE;
   p_handler->attribute.mouseCursorBitmap = K_MK_NULL;
   p_handler->attribute.mouseCursorWidth = 0;
   p_handler->attribute.mouseCursorHeight = 0;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_dispatcher_initHandler ( T_mkDispatcherHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des attributs du gestionnaire */
   mk_dispatcher_initAttributes ( p_handler );

   /* Initialisation de la messagerie permettant l'émission de requêtes à destination du dispatcher */
   l_result = mk_dispatcher_initIncomingMessageArea ( p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la messagerie permettant l'émission de requêtes à destination du terminal HID */
      l_result = mk_dispatcher_initHIDMessageArea ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation de la messagerie permettant l'émission de requêtes à destination de la tâche d'écoute */
         l_result = mk_dispatcher_initListenerPool ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation de la pool permettant d'allouer les disques */
            l_result = mk_dispatcher_initDiskPool ( );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Initialisation de la pool permettant d'allouer les partitions */
               l_result = mk_dispatcher_initVolumePool ( );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Transmission d'une événement pour indiquer que l'initialisation a réussi */
                  l_result = mk_dispatcher_sendSignal ( );
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


