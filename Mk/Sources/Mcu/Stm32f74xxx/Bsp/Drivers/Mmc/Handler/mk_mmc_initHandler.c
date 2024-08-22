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
* @file mk_mmc_initHandler.c
* @brief Définition de la fonction mk_mmc_initHandler.
* @date 6 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_handleSignal ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_event = 0;

   /* Positionnement de l'événement MMC */
   l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_MMC );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Attente de l'intialisation du dispatcher et du terminal GPIO */
      l_result = mk_event_wait ( g_mkTermioSync.event, K_MK_EVENT_AND | K_MK_TERMIO_FLAG_GPIO | K_MK_TERMIO_FLAG_DISPATCHER, &l_event, K_MK_TERMIO_INIT_TIMEOUT );
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

static T_mkCode mk_mmc_initPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des périphériques MMC */
   l_result = mk_pool_initArea ( &g_mkMMCPool.area, g_mkMMCPool.heap, K_MK_MMC_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des périphérique MMC */
      l_result = mk_pool_create ( &g_mkMMCPool.area, &g_mkMMCPool.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkMMCDevice ) >> 2, K_MK_MMC_MAX_DEVICE_NUMBER );
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

static T_mkCode mk_mmc_initRequest ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du terminal MMC. */
   p_handler->requestArea = &g_mkMMCRequestArea;

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

T_mkCode mk_mmc_initHandler ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( p_handler != K_MK_NULL )
   {
      /* Initialisation de la pool permettant d'allouer les périphériques MMC */
      l_result = mk_mmc_initPool ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation de la boite de messages */
         l_result = mk_mmc_initRequest ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation du champ d'événements du terminal MMC */
            l_result = mk_event_create ( &p_handler->portEvent, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Transmission d'un événement pour signaler que l'initialisation du terminal a réussi. */
               /* Attente de la fin de l'initialisation des autres terminaux. */
               l_result = mk_mmc_handleSignal ( );
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
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_PARAM;
   }

   /* Retour */
   return ( l_result );
}


