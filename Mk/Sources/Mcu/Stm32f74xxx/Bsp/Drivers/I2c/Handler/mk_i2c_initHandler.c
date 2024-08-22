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
* @file mk_i2c_initHandler.c
* @brief Définition de la fonction mk_i2c_initHandler.
* @date 7 nov. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_initEvent ( T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation du champ d'événements du terminal I2C */
   l_result = mk_event_create ( &p_handler->portEvent, K_MK_ID_EVENT_FLAG, K_MK_AREA_PROTECTED, 0 );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_sendSignal ( T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si terminal I2C1 */
   if ( p_handler->bus == K_I2C1 )
   {
      /* Positionnement de l'événement I2C1 */
      l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_I2C1 );
   }

   /* Sinon si terminal I2C2 */
   else if ( p_handler->bus == K_I2C2 )
   {
      /* Positionnement de l'événement I2C2 */
      l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_I2C2 );
   }

   /* Sinon si terminal I2C3 */
   else if ( p_handler->bus == K_I2C3 )
   {
      /* Positionnement de l'événement I2C3 */
      l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_I2C3 );
   }

   /* Sinon */
   else
   {
      /* Positionnement de l'événement I2C4 */
      l_result = mk_event_set ( g_mkTermioSync.event, K_MK_TERMIO_FLAG_I2C4 );
   }

   /* Retour */
   return ( l_result );
}


/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_initPool ( void )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Initialisation de la zone mémoire dédiées à l'allocation des périphériques I2C */
   l_result = mk_pool_initArea ( &g_mkI2CPool.area, g_mkI2CPool.heap, K_MK_I2C_POOL_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation du gestionnaire d'allocation dynamique des périphériques I2C */
      l_result = mk_pool_create ( &g_mkI2CPool.area, &g_mkI2CPool.pool, K_MK_AREA_PROTECTED, sizeof ( T_mkI2CDevice ) >> 2, K_MK_I2C_MAX_DEVICE_NUMBER );
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

static T_mkCode mk_i2c_initRequest ( T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse de la structure contenant les données de la messagerie du terminal I2C. */
   p_handler->requestArea = &g_mkI2CRequestArea;

   /* Initialisation de la zone mémoire dédiées à la messagerie */
   l_result = mk_pool_initArea ( &p_handler->requestArea->area, p_handler->requestArea->heap, K_MK_I2C_MESSAGE_AREA_SIZE );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation de la boite de messages */
      l_result = mk_mail_create ( &p_handler->requestArea->request, K_MK_AREA_UNPROTECTED, &p_handler->requestArea->area, K_MK_I2C_MESSAGE_SIZE, K_MK_I2C_MESSAGE_NUMBER );
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

T_mkCode mk_i2c_initHandler ( T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) &&
      ( ( p_handler->bus == K_I2C1 ) || ( p_handler->bus == K_I2C2 ) || ( p_handler->bus == K_I2C3 ) || ( p_handler->bus == K_I2C4 ) ) )
   {
      /* Initialisation de la pool permettant d'allouer les périphériques I2C */
      l_result = mk_i2c_initPool ( );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation de la boite de messages */
         l_result = mk_i2c_initRequest ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation du champ d'événements */
            l_result = mk_i2c_initEvent ( p_handler );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Transmission d'un événement pour signaler que l'initialisation du terminal a réussi. */
               l_result = mk_i2c_sendSignal ( p_handler );
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
