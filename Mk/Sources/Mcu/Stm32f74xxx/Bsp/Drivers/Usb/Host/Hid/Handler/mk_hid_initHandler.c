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
* @file mk_hid_initHandler.c
* @brief Définition de la fonction mk_hid_initHandler.
* @date 3 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_handleSignal ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Positionnement de l'événement HID */
   l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_HID );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Attente de l'intialisation du dispatcher et du terminal USB */
      l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_DISPATCHER, &l_event, K_MK_TERMIO_INIT_TIMEOUT );
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

static T_mkCode mk_hid_initPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des objets HID */
   l_result = mk_pool_initArea ( &g_mkHIDPool.area, g_mkHIDPool.heap, K_MK_HID_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des périphériques HID */
      l_result = mk_pool_create ( &g_mkHIDPool.area, &g_mkHIDPool.devicePool, K_MK_AREA_PROTECTED, sizeof ( T_mkHIDDevice ) >> 2, K_MK_HID_MAX_DEVICE_NUMBER );

      /* Si l'initialisation a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire d'allocation dynamique des objets T_mkHIDItem */
         l_result = mk_pool_create ( &g_mkHIDPool.area, &g_mkHIDPool.itemPool, K_MK_AREA_PROTECTED, sizeof ( T_mkHIDItem ) >> 2, K_MK_HID_POOL_MAX_ITEM_NUMBER );

         /* Si l'initialisation a réussi */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation du gestionnaire d'allocation dynamique des objets T_mkHIDReport */
            l_result = mk_pool_create ( &g_mkHIDPool.area, &g_mkHIDPool.reportPool, K_MK_AREA_PROTECTED, sizeof ( T_mkHIDReport ) >> 2, K_MK_HID_POOL_MAX_REPORT_NUMBER );

            /* Si l'initialisation a réussi */
            if ( l_result == K_MK_OK )
            {
               /* Initialisation du gestionnaire d'allocation dynamique des objets T_mkHIDLocalTable */
               l_result = mk_pool_create ( &g_mkHIDPool.area, &g_mkHIDPool.itemStatePool, K_MK_AREA_PROTECTED, sizeof ( T_mkHIDLocalTable ) >> 2, K_MK_HID_POOL_MAX_LOCAL_TABLE_NUMBER );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_initMessagePool ( T_mkHIDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du terminal HID. */
   p_handler->mailArea = &g_mkHIDMailArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->mailArea->area, p_handler->mailArea->heap, K_MK_HID_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->mailArea->mail, K_MK_AREA_PROTECTED, &p_handler->mailArea->area, K_MK_HID_MESSAGE_SIZE, K_MK_HCD_MAX_DEVICE_NUMBER );
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

static T_mkCode mk_hid_initControlPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkButton */
   l_result = mk_hid_button_initPool ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkMouse */
      l_result = mk_hid_mouse_initPool ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkJoystick */
         l_result = mk_hid_joystick_initPool ( );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkKey */
            l_result = mk_hid_key_initPool ( );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkLed */
               l_result = mk_hid_led_initPool ( );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkKeyboard */
                  l_result = mk_hid_keyboard_initPool ( );

                  /* Si aucune erreur ne s'est produite */
                  if ( l_result == K_MK_OK )
                  {
                     /* Initialisation du gestionnaire d'allocation dynamique des objets de type T_mkConsumerControl */
                     l_result = mk_hid_consumer_initPool ( );
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

T_mkCode mk_hid_initHandler ( T_mkHIDHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation des gestionnaires d'allocation des périphériques et des objets HID. */
   l_result = mk_hid_initPool ( );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la messagerie HID. */
      /* Les allocations sont réalisées dans la stack du terminal. */
      l_result = mk_hid_initMessagePool ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation des gestionnaires d'allocation des contrôles HID. */
         l_result = mk_hid_initControlPool ( );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Transmission d'un événement pour signaler que l'initialisation du terminal a réussi. */
            /* Attente de la fin de l'initialisation des autres terminaux. */
            l_result = mk_hid_handleSignal ( );
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
