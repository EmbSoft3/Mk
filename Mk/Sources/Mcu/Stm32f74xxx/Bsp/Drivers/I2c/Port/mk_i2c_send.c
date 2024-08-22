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
* @file mk_i2c_send.c
* @brief Définition de la fonction mk_i2c_send.
* @date 31 oct. 2020
*
*/

#include "mk_i2c_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_setTransferStream ( T_mkDMAPipe* p_pipe, uint32_t p_direction )
{
   /* Désactivation du flux */
   dma_disableStream ( p_pipe->addr, p_pipe->stream );

   /* Activation des interruptions DMA */
   dma_enableInterrupt ( p_pipe->addr, p_pipe->stream, K_DMA_INTERRUPT_TRANSFERT_COMPLETE | K_DMA_INTERRUPT_TRANSFERT_ERROR );

   /* Réinitialisation du drapeau d'interruption DMA indiquant la fin de transfert */
   dma_clearTransferCompleteInterruptFlag ( p_pipe->addr, p_pipe->stream );

   /* Réinitialisation du drapeau d'interruption DMA indiquant la présence d'une erreur */
   dma_clearTransferErrorInterruptFlag ( p_pipe->addr, p_pipe->stream );

   /* Si une lecture doit être réalisée */
   if ( p_direction == K_I2C_READ )
   {
      /* Configuration de la direction du flux DMA */
      dma_setDirection ( p_pipe->addr, p_pipe->stream, K_DMA_DIRECTION_PERIPHERAL_TO_MEMORY );
   }

   /* Sinon */
   else
   {
      /* Configuration de la direction du flux DMA */
      dma_setDirection ( p_pipe->addr, p_pipe->stream, K_DMA_DIRECTION_MEMORY_TO_PERIPHERAL );
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_i2c_setTransfer ( T_mkI2CHandler* p_handler, T_mkDMAPipe* p_pipe, uint8_t** p_buf, uint32_t* p_length )
{
   /* Configuration de l'adresse mémoire source (ou de destination) */
   dma_setMemoryAddr1 ( p_pipe->addr, p_pipe->stream, ( uint32_t ) *p_buf );

   /* Si le nombre de données est supérieur à la limite */
   if ( *p_length > K_MK_I2C_MAX_SIZE )
   {
      /* Activation du mode 'Reload' */
      i2c_enableReload ( p_handler->bus );

      /* Configuration de la taille du transfert */
      i2c_setTransferLength ( p_handler->bus, K_MK_I2C_MAX_SIZE );

      /* Configuration de la taille du transfert DMA */
      dma_setCount ( p_pipe->addr, p_pipe->stream, K_MK_I2C_MAX_SIZE );

      /* Acualisation de l'adresse du buffer et du nombre d'octets restants */
      /* à envoyer */
      *p_buf = ( uint8_t* ) ( *p_buf + K_MK_I2C_MAX_SIZE );
      *p_length = ( uint32_t ) ( *p_length - K_MK_I2C_MAX_SIZE );
   }

   /* Sinon */
   else
   {
      /* Désactivation du mode 'Reload' */
      i2c_disableReload ( p_handler->bus );

      /* Configuration de la taille du transfert */
      i2c_setTransferLength ( p_handler->bus, *p_length );

      /* Configuration de la taille du transfert DMA */
      dma_setCount ( p_pipe->addr, p_pipe->stream, *p_length );

      /* Actualisation du nombre d'octets restants à envoyer */
      *p_length = 0;
   }

   /* Activation de l'interruption 'TransferComplete' */
   i2c_enableInterrupt ( p_handler->bus, K_I2C_TRANSFER_COMPLETE_INTERRUPT );

   /* Activation du flux DMA */
   dma_enableStream ( p_pipe->addr, p_pipe->stream );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_stopTransfer ( T_mkI2CHandler* p_handler, T_mkI2CTransferStatus* p_transfer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Transfert du bit de stop sans condition */
   i2c_stop ( p_handler->bus );

   /* Attendre tant que le bit de stop n'a pas été positionné */
   l_result = mk_event_wait ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_I2C_FLAG_ALL | K_MK_I2C_TRANSFER_DONE |
                              K_MK_I2C_TRANSFER_ABORTED | K_MK_I2C_TRANSFER_END, ( uint32_t* ) ( &p_handler->portStatus ), K_MK_I2C_TIMEOUT );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Si une erreur protocolaire s'est produite */
      if ( ( p_handler->portStatus & ( uint32_t ) ( ~K_I2C_FLAG_ALL ) ) != K_MK_I2C_TRANSFER_END )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_COMM;
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

   /* Actualisation du registre de statut */
   p_transfer->status |= p_handler->portStatus;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_startTransfer ( T_mkI2CHandler* p_handler, T_mkI2CTransferStatus* p_transfer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Transfert du bit de start sans condition */
   i2c_start ( p_handler->bus );

   /* Détection de la présence d'un événement "Arbitration Lost" */
   l_result = mk_event_wait ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_I2C_ARBITRATION_LOST_INTERRUPT |
                              K_MK_I2C_TRANSFER_ABORTED, ( uint32_t* ) ( &p_handler->portStatus ), 0 );

   /* Si une erreur est présente sur le bus (un conflit d'arbitration vient de se produire) */
   if ( l_result == K_MK_OK )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COMM;
   }

   /* Sinon si un timeout s'est produit */
   else if ( l_result == K_MK_ERROR_TIMEOUT )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_OK;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Actualisation du registre de statut */
   p_transfer->status |= p_handler->portStatus;

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_waitUntilTransferDone ( T_mkI2CHandler* p_handler, T_mkDMAPipe* p_pipe, T_mkI2CTransferStatus* p_transfer, uint32_t p_timeout )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Détection de la fin du transfert DMA */
   l_result = mk_event_wait ( p_pipe->event, K_MK_EVENT_OR | K_MK_EVENT_CLEAR |
                              K_MK_DMA_STATUS_TRANSFER_COMPLETED | K_MK_DMA_STATUS_TRANSFER_ERROR, ( uint32_t* ) &p_pipe->status, p_timeout );

   /* Si une erreur s'est produite */
   if ( ( l_result == K_MK_OK ) && ( p_pipe->status != K_MK_DMA_STATUS_TRANSFER_COMPLETED ) )
   {
      /* Actualisation du registre de statut */
      p_transfer->status |= K_MK_I2C_DMA_ERROR;

      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COMM;
   }

   /* Sinon si un timeout s'est produit */
   else if ( l_result == K_MK_ERROR_TIMEOUT )
   {
      /* Désactivation du flux DMA */
      dma_disableStream ( p_pipe->addr, p_pipe->stream );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur DMA ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Détection de la fin du transfert I2C */
      l_result = mk_event_wait ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_I2C_FLAG_ALL | K_MK_I2C_TRANSFER_DONE |
                                 K_MK_I2C_TRANSFER_END | K_MK_I2C_TRANSFER_ABORTED, ( uint32_t* ) ( &p_handler->portStatus ), p_timeout );

      /* Si une erreur s'est produite */
      if ( ( l_result == K_MK_OK ) && ( ( p_handler->portStatus & ( uint32_t ) ( ~K_I2C_FLAG_ALL ) ) != K_MK_I2C_TRANSFER_DONE ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_COMM;
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Actualisation du registre de statut */
      p_transfer->status |= p_handler->portStatus;
   }

   /* Sinon */
   else
   {
      /* Réinitialisation du champ d'événements I2C */
      l_result |= mk_event_clear ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_I2C_FLAG_ALL |
                                   K_MK_I2C_TRANSFER_DONE | K_MK_I2C_TRANSFER_ABORTED | K_MK_I2C_TRANSFER_END );
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_transmit ( T_mkI2CHandler* p_handler, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_transfer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_frame->reg != K_MK_NULL ) && ( p_frame->regLength != 0 ) )
   {
      /* Ouverture d'un pipe de communication I2C (transmission) */
      l_result = mk_i2c_openPipe ( p_handler, &p_handler->transmit.pipe, p_handler->transmit.channel,
                                   p_handler->transmit.stream, p_handler->transmit.callback, ( uint32_t ) ( ( uint32_t* ) p_handler->bus + 10 ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de la direction du transfert */
         i2c_setReadWrite ( p_handler->bus, K_I2C_WRITE );

         /* Configuration du flux DMA de transmission */
         mk_i2c_setTransferStream ( p_handler->transmit.pipe, K_I2C_WRITE );

         /* Configuration de la taille du transfert */
         mk_i2c_setTransfer ( p_handler, p_handler->transmit.pipe, &p_frame->reg, &p_frame->regLength );

         /* Activation de la DMA */
         i2c_enableDMA ( p_handler->bus, K_I2C_DMA_TRANSMITTER );

         /* Déclenchement d'un bit de start puis transfert de l'adresse (Write) */
         l_result = mk_i2c_startTransfer ( p_handler, p_transfer );

         /* Si aucune erreur d'arbitration ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Attendre tant que le transfert n'est pas terminé */
            l_result = mk_i2c_waitUntilTransferDone ( p_handler, p_handler->transmit.pipe, p_transfer, p_frame->regTimeout );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Effectue */
               do
               {
                  /* Si l'intégralité des octets n'ont pas été envoyés */
                  if ( p_frame->regLength != 0 )
                  {
                     /* Reconfiguration du transfert */
                     mk_i2c_setTransfer ( p_handler, p_handler->transmit.pipe, &p_frame->reg, &p_frame->regLength );

                     /* Attendre tant que le transfert n'est pas terminé */
                     l_result = mk_i2c_waitUntilTransferDone ( p_handler, p_handler->transmit.pipe, p_transfer, p_frame->regTimeout );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

               /* Tant qu'aucune erreur ne s'est produite et tant que l'intégralité des données n'ont pas été transmises sur le bus */
               } while ( ( p_frame->regLength != 0 ) && ( l_result == K_MK_OK ) );

               /* Désactivation de la DMA */
               i2c_disableDMA ( p_handler->bus, K_I2C_DMA_TRANSMITTER );
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

         /* Fermeture du pipe */
         l_result |= mk_i2c_closePipe ( p_handler, &p_handler->transmit.pipe );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_i2c_receive ( T_mkI2CHandler* p_handler, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_transfer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( ( p_frame->data != K_MK_NULL ) && ( p_frame->dataLength != 0 ) )
   {
      /* Ouverture du pipe de communication (réception) */
      l_result = mk_i2c_openPipe ( p_handler, &p_handler->receive.pipe, p_handler->receive.channel,
                                   p_handler->receive.stream, p_handler->receive.callback, ( uint32_t ) ( ( uint32_t* ) p_handler->bus + 9 ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration de la direction du transfert */
         i2c_setReadWrite ( p_handler->bus, K_I2C_READ );

         /* Configuration du flux DMA de reception */
         mk_i2c_setTransferStream ( p_handler->receive.pipe, K_I2C_READ );

         /* Configuration de la taille du transfert */
         mk_i2c_setTransfer ( p_handler, p_handler->receive.pipe, &p_frame->data, &p_frame->dataLength );

         /* Activation de la DMA */
         i2c_enableDMA ( p_handler->bus, K_I2C_DMA_RECEIVER );

         /* Déclenchement d'un bit de restart */
         i2c_start ( p_handler->bus );

         /* Attendre tant que la reception des données n'est pas terminé */
         l_result = mk_i2c_waitUntilTransferDone ( p_handler, p_handler->receive.pipe, p_transfer, p_frame->dataTimeout );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Effectue */
            do
            {
               /* Si l'intégralité des octets n'ont pas été reçus */
               if ( p_frame->dataLength != 0 )
               {
                  /* Reconfiguration du transfert */
                  mk_i2c_setTransfer ( p_handler, p_handler->receive.pipe, &p_frame->data, &p_frame->dataLength );

                  /* Attendre tant que le transfert n'est pas terminé */
                  l_result = mk_i2c_waitUntilTransferDone ( p_handler, p_handler->receive.pipe, p_transfer, p_frame->dataTimeout );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

            /* Tant qu'aucune erreur ne s'est produite et tant que l'intégralité des données n'ont pas été transmises */
            } while ( ( p_frame->dataLength != 0 ) && ( l_result == K_MK_OK ) );

            /* Désactivation de la DMA */
            i2c_disableDMA ( p_handler->bus, K_I2C_DMA_RECEIVER );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Fermeture du pipe */
         l_result |= mk_i2c_closePipe ( p_handler, &p_handler->receive.pipe );
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

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_i2c_send ( T_mkI2CHandler* p_handler, T_mkI2CDevice* p_device, T_mkI2CFrame* p_frame, T_mkI2CTransferStatus* p_transfer )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_handler->bus != K_MK_NULL ) && ( p_frame != K_MK_NULL ) && ( p_transfer != K_MK_NULL ) )
   {
      /* Initialisation de la structure de retour */
      p_transfer->status = K_MK_I2C_NO_FLAG;
      p_transfer->incomingBuf = p_frame->data;
      p_transfer->numberOfBytesWrite = p_frame->regLength;
      p_transfer->numberOfBytesRead = p_frame->dataLength;

      /* Configuration de l'adresse de l'escalve */
      i2c_setAddress ( p_handler->bus, p_device->setting.addressLength, p_device->setting.slaveAddr );

      /* Déclenchement de la première partie du transfert (écriture) */
      l_result = mk_i2c_transmit ( p_handler, p_frame, p_transfer );

      /* Si une lecture doit être réalisée */
      if ( ( l_result == K_MK_OK ) && ( p_frame->direction == K_I2C_READ ) )
      {
         /* Déclenchement de la seconde partie du transfert (lecture) */
         l_result = mk_i2c_receive ( p_handler, p_frame, p_transfer );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Arrêt du transfert */
      l_result |= mk_i2c_stopTransfer ( p_handler, p_transfer );

      /* Actualisation du nombre de données transmises et reçues */
      p_transfer->numberOfBytesRead = ( uint32_t ) ( p_transfer->numberOfBytesRead - p_frame->dataLength );
      p_transfer->numberOfBytesWrite = ( uint32_t ) ( p_transfer->numberOfBytesWrite - p_frame->regLength );
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

