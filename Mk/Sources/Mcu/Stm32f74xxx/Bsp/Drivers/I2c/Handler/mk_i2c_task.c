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
* @file mk_i2c_task.c
* @brief Définition de la fonction mk_i2c_task.
* @date 3 oct. 2020
* @todo Libérer la mémoire allouée par le terminal à la destruction de celui-ci.
* @todo Implémenter les fonctionnalité du mode esclave.
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_setI2CAddr ( T_mkTermio* p_termio, T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le terminal est dédié au bus I2C1 */
   if ( p_termio->task->attribute.identifier == K_MK_TERMIO_I2C1_ID )
   {
      /* Configuration de l'adresse du bus I2C1 */
      p_handler->bus = K_I2C1;

      /* Configuration des attributs des canaux DMA (transmission et réception) */
      p_handler->transmit.channel = K_DMA_CHANNEL1;
      p_handler->transmit.stream = K_DMA_STREAM6;
      p_handler->transmit.callback = mk_i2c1_transmitCallback;
      p_handler->receive.channel = K_DMA_CHANNEL1;
      p_handler->receive.stream = K_DMA_STREAM5;
      p_handler->receive.callback = mk_i2c1_receiveCallback;

      /* Configuration du niveau de protection du bus */
      p_handler->right = K_MK_I2C1_RIGHT;
   }

   /* Sinon si le terminal est dédié au bus I2C2 */
   else if ( p_termio->task->attribute.identifier == K_MK_TERMIO_I2C2_ID )
   {
      /* Configuration de l'adresse du bus I2C2 */
      p_handler->bus = K_I2C2;

      /* Configuration des attributs des canaux DMA (transmission et réception) */
      p_handler->transmit.channel = K_DMA_CHANNEL7;
      p_handler->transmit.stream = K_DMA_STREAM7;
      p_handler->transmit.callback = mk_i2c2_transmitCallback;
      p_handler->receive.channel = K_DMA_CHANNEL7;
      p_handler->receive.stream = K_DMA_STREAM2;
      p_handler->receive.callback = mk_i2c2_receiveCallback;

      /* Configuration du niveau de protection du bus */
      p_handler->right = K_MK_I2C2_RIGHT;
   }

   /* Sinon si le terminal est dédié au bus I2C3 */
   else if ( p_termio->task->attribute.identifier == K_MK_TERMIO_I2C3_ID )
   {
      /* Configuration de l'adresse du bus I2C3 */
      p_handler->bus = K_I2C3;

      /* Configuration des attributs des canaux DMA (transmission et réception) */
      p_handler->transmit.channel = K_DMA_CHANNEL3;
      p_handler->transmit.stream = K_DMA_STREAM4;
      p_handler->transmit.callback = mk_i2c3_transmitCallback;
      p_handler->receive.channel = K_DMA_CHANNEL3;
      p_handler->receive.stream = K_DMA_STREAM2;
      p_handler->receive.callback = mk_i2c3_receiveCallback;

      /* Configuration du niveau de protection du bus */
      p_handler->right = K_MK_I2C3_RIGHT;
   }

   /* Sinon si le terminal est dédié au bus I2C4 */
   else if ( p_termio->task->attribute.identifier == K_MK_TERMIO_I2C4_ID )
   {
      /* Configuration de l'adresse du bus I2C4 */
      p_handler->bus = K_I2C4;

      /* Configuration des attributs des canaux DMA (transmission et réception) */
      p_handler->transmit.channel = K_DMA_CHANNEL2;
      p_handler->transmit.stream = K_DMA_STREAM5;
      p_handler->transmit.callback = mk_i2c4_transmitCallback;
      p_handler->receive.channel = K_DMA_CHANNEL2;
      p_handler->receive.stream = K_DMA_STREAM2;
      p_handler->receive.callback = mk_i2c4_receiveCallback;

      /* Configuration du niveau de protection du bus */
      p_handler->right = K_MK_I2C4_RIGHT;
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_initI2CHandler ( T_mkTermio* p_termio, T_mkI2CHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Réinitialisation du gestionnaire I2C */
   _writeWords ( p_handler, 0, sizeof ( T_mkI2CHandler ) >> 2 );

   /* Configuration de la structure de données du terminal */
   l_result = mk_termio_setChild ( p_termio, ( T_mkI2CHandler* ) p_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Initialisation des données I2C assignées au terminal */
      l_result = mk_i2c_setI2CAddr ( p_termio, p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Initialisation du gestionnaire I2C */
         l_result = mk_i2c_initHandler ( p_handler );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Initialisation des broches GPIO du bus I2C */
            mk_i2c_initGPIO ( p_handler->bus );
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

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a réussi. */
      l_result = mk_termio_log ( ( T_str8 ) "[I2C] ready;\n" );
   }

   /* Sinon */
   else
   {
      /* Affichage d'un message dans la console du superviseur pour indiquer */
      /* que l'initialisation a échoué. */
      l_result = mk_termio_log ( ( T_str8 ) "[I2C] failed;\n" );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_handleCallbackFunction ( T_mkTask* p_task, T_mkI2CMessage* p_message, T_mkCode p_code, T_mkAddr p_deviceParam, T_mkAddr p_statusParam )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une structure de rappel */
   T_mkCallbackParam l_callbackParams;

   /* Déclaration d'une variable de travail */
   uint32_t l_area = 0;

   /* Si une fonction de rappel a été configurée */
   if ( p_message->callback != K_MK_NULL )
   {
      /* Configuration des arguments de la fonction de rappel */
      l_callbackParams.param1 = ( T_mkAddr ) p_code;
      l_callbackParams.param2 = ( T_mkAddr ) p_deviceParam;
      l_callbackParams.param3 = ( T_mkAddr ) p_statusParam;

      /* Déclenchement de la fonction de rappel */
      l_result = mk_callback_trig ( p_message->callback->handler, p_message->callback, &l_callbackParams );
   }

   /* Sinon */
   else
   {
      /* Récupération du niveau de privilège de la zone mémoire */
      l_area = _mk_memory_isPrivilegedArea ( ( T_mkAddr ) p_message->result );

      /* Si la tâche émettrice de la requête possède un niveau de droits suffisants  */
      if ( ( ( p_task->attribute.type & K_MK_TYPE_PRIVILEGED ) == K_MK_TYPE_DEFAULT ) && ( l_area != K_MK_AREA_UNPROTECTED ) )
      {
         /* Ne rien faire */
      }

      /* Sinon */
      else
      {
         /* Actualisation de la variable de retour */
         *p_message->result = p_code;
      }

      /* Si la tâche est suspendue */
      if ( p_task->attribute.state == K_MK_STATE_SUSPENDED )
      {
         /* Réactivation de la tâche */
         l_result = mk_task_resume ( p_task );
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

static T_mkCode mk_i2c_handleEvent ( T_mkI2CHandler* p_handler )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de tâche */
   T_mkTask* l_task;

   /* Déclaration d'un message */
   T_mkI2CMessage l_message;

   /* Déclaration des variables de travail */
   T_mkAddr l_deviceParam = K_MK_NULL, l_statusParam = K_MK_NULL;

   /* Tant qu'aucune erreur non critique ne s'est produite */
   while ( ( l_result == K_MK_OK ) || ( l_result == K_MK_ERROR_TIMEOUT ) || ( l_result == K_MK_ERROR_COMM ) )
   {
      /* Analyse de la messagerie afin de récupérer les requêtes envoyées par l'utilisateur */
      l_result = mk_mail_pend ( &l_task, p_handler->requestArea->request, ( T_mkAddr ) &l_message, K_MK_TASK_WAIT_FOREVER );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_task != K_MK_NULL ) )
      {
         /* Si un nouveau port I2C doit être ouvert */
         if ( l_message.requestIdentifier == K_MK_I2C_OPEN_PORT )
         {
            /* Création d'un nouveau port de communication */
            l_result = mk_i2c_handleCreate ( l_task, p_handler, ( T_mkI2CDevice** ) l_message.device, l_message.setting );

            /* Enregistrement de l'adresse du périphérique dans l'argument de la fonction de rappel */
            l_deviceParam = * ( T_mkI2CDevice** ) l_message.device;
         }

         /* Sinon si un message doit être envoyé sur le bus */
         else if ( l_message.requestIdentifier == K_MK_I2C_POST_PORT )
         {
            /* Transfert de la trame sur le bus */
            l_result = mk_i2c_handleMessage ( l_task, p_handler, l_message.device, l_message.setting, l_message.status );

            /* Actualisation de la valeur des arguments de la fonction de rappel */
            l_deviceParam = l_message.device;
            l_statusParam = l_message.status;
         }

         /* Sinon si un port I2C doit être fermé */
         else if ( l_message.requestIdentifier == K_MK_I2C_CLOSE_PORT )
         {
            /* Fermeture d'un port de communication */
            l_result = mk_i2c_handleDelete ( l_task, p_handler, ( T_mkI2CDevice* ) l_message.device );

            /* Enregistrement de l'adresse du périphérique dans l'argument de la fonction de rappel */
            l_deviceParam = ( T_mkI2CDevice* ) l_message.device;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Gestion et déclenchement de la fonction de rappel si nécessaire */
         l_result = mk_i2c_handleCallbackFunction ( l_task, &l_message, l_result, l_deviceParam, l_statusParam );
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

void mk_i2c_task ( T_mkAddr p_param )
{
   /* Déclaration d'une variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de terminal */
   T_mkTermio* l_termio = ( T_mkTermio* ) p_param;

   /* Déclaration d'un gestionnaire de périphériques I2C */
   T_mkI2CHandler l_handler;

   /* Initialisation du gestionnaire I2C */
   l_result = mk_i2c_initI2CHandler ( l_termio, &l_handler );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Gestion des événements du terminal */
      l_result = mk_i2c_handleEvent ( &l_handler );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Le résultat de la fonction n'est pas vérifié car l'intégrité du système n'est plus garantie. */
   /* Une erreur grave vient de se produire */
   /* La destruction du terminal est de la responsabilité du superviseur. */
   ( void ) mk_termio_report ( l_result );

   /* Blocage */
   while ( 1 );

   /* Retour */
   return;
}
