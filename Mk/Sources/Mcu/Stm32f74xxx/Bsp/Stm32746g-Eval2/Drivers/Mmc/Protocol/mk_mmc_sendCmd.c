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
* @file mk_mmc_sendCmd.c
* @brief Définition de la fonction mk_mmc_sendCmd.
* @date 6 juin 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_mmc_setTransferStream ( T_mkMMCHandler* p_handler, T_mkMMCCommand* p_command, T_mkAddr p_buf )
{
   /* Désactivation du flux DMA */
   dma_disableStream ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Si le transfert est une requête de lecture */
   if ( p_command->direction == K_MMC_DIRECTION_CONTROLLER_TO_CARD )
   {
      /* Configuration de la direction du flux DMA */
      dma_setDirection ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_DIRECTION_MEMORY_TO_PERIPHERAL );
   }

   /* Sinon (écriture) */
   else
   {
      /* Configuration de la direction du flux DMA */
      dma_setDirection ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_DIRECTION_PERIPHERAL_TO_MEMORY );

   }

   /* Configuration de l'adresse mémoire source (ou de destination) */
   dma_setMemoryAddr1 ( p_handler->pipe->addr, p_handler->pipe->stream, ( uint32_t ) p_buf );

   /* Activation des interruptions DMA */
   dma_enableInterrupt ( p_handler->pipe->addr, p_handler->pipe->stream, K_DMA_INTERRUPT_TRANSFERT_COMPLETE | K_DMA_INTERRUPT_TRANSFERT_ERROR );

   /* Réinitialisation du drapeau d'interruption DMA indiquant la fin de transfert */
   dma_clearTransferCompleteInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Réinitialisation du drapeau d'interruption DMA indiquant la présence d'une erreur */
   dma_clearTransferErrorInterruptFlag ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Activation du flux DMA */
   dma_enableStream ( p_handler->pipe->addr, p_handler->pipe->stream );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_mmc_setupTransfer ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCCommand* p_command, T_mkAddr p_buf )
{
   /* Réinitialisation des drapeaux d'interruption SD/MMC */
   mmc_clearStatus ( K_MMC_FLAG_ALL );

   /* Si un transfert de données doit être réalisé */
   if ( ( p_buf != K_MK_NULL ) && ( p_command->length != 0 ) )
   {
      /* Configuration de la taille d'un bloc de donnée */
      mmc_setBlockSize ( p_device->layer.blockLength );

      /* Configuration de la largeur du bus de données */
      mmc_setDataBusSize ( p_device->layer.busWidth );

      /* Configuration du flux DMA */
      mk_mmc_setTransferStream ( p_handler, p_command, p_buf );

      /* Si le transfert est un transfert entrant */
      if ( p_command->direction == K_MMC_DIRECTION_CARD_TO_CONTROLLER )
      {
         /* Activation du transfert des données */
         mmc_enableTransfer ( );
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
      /* Désactivation du transfert des données */
      mmc_disableTransfer ( );
   }

   /* Activation des interruptions MMC */
   mmc_enableInterrupt ( K_MMC_FLAG_CMD_TRANSMITTED | K_MMC_FLAG_CMD_RESPONSE_RECEIVED );

   /* Configuration et transmission de la commande MMC */
   mmc_setCommand ( p_command->opcode, p_command->argument, p_command->responseLength, K_MMC_OPT_STATE_MACHINE );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_handleResponse ( T_mkMMCCommand* p_command, T_mkAddr p_response, T_mkMMCPortStatus p_portStatus )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si la réponse doit être enregistrée */
   if ( p_response != K_MK_NULL )
   {
      /* Lecture de la réponse */
      mmc_getResponseByType ( p_response, p_command->responseLength );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si une erreur s'est produite */
   if ( ( ( p_portStatus & K_MK_MMC_TRANSFER_ABORTED ) > 0 ) ||
      ( ( ( p_portStatus & K_MK_MMC_TRANSFER_ERROR   ) > 0 ) && ( p_command->bypassCRC == K_MK_MMC_CRC_BYPASS_DISABLED ) ) )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_COMM;
   }

   /* Sinon si une erreur de timeout s'est produite */
   else if ( ( p_portStatus & K_MK_MMC_TRANSFER_TIMEOUT ) > 0 )
   {
      /* Actualisation de la variable de retour */
      l_result = K_MK_ERROR_TIMEOUT;
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

static T_mkCode mk_mmc_startTransfer ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCCommand* p_command, T_mkAddr p_response, T_mkAddr p_buf, T_mkMMCPortStatus* p_portStatus )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Effectue */
   do
   {
      /* Initialisation du statut de la communication */
      *p_portStatus = K_MK_MMC_NO_FLAG;

      /* Finalisation de la configuration du transfert */
      mk_mmc_setupTransfer ( p_handler, p_device, p_command, p_buf );

      /* Détection de la fin du transfert de la commande */
      /* La constante K_MMC_FLAG_ALL est présente afin de réinitialiser automatiquement tous les drapeaux */
      l_result = mk_event_wait ( p_handler->portEvent, K_MK_EVENT_OR | K_MK_EVENT_CLEAR | K_MMC_FLAG_ALL |
                                 K_MK_MMC_TRANSFER_ABORTED | K_MK_MMC_TRANSFER_DONE | K_MK_MMC_TRANSFER_ERROR | K_MK_MMC_TRANSFER_TIMEOUT, ( uint32_t* ) p_portStatus, K_MK_MMC_TIMEOUT );

      /* Si le transfert a réussi */
      if ( l_result == K_MK_OK )
      {
         /* Lecture de la réponse de la carte */
         l_result = mk_mmc_handleResponse ( p_command, p_response, *p_portStatus );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }

      /* Si un transfert de données doit être réalisé */
      if ( ( l_result == K_MK_OK ) && ( p_buf != K_MK_NULL ) && ( p_command->length != 0 ) )
      {
         /* Si le transfert est un transfert sortant */
         if ( p_command->direction == K_MMC_DIRECTION_CONTROLLER_TO_CARD )
         {
            /* Activation du transfert des données */
            mmc_enableTransfer ( );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Détection de la fin du transfert de données */
         l_result = mk_event_wait ( p_handler->pipe->event, K_MK_EVENT_OR | K_MK_EVENT_CLEAR |
                                    K_MK_DMA_STATUS_TRANSFER_COMPLETED | K_MK_DMA_STATUS_TRANSFER_ERROR, ( uint32_t* ) &p_handler->pipe->status, p_command->timeout );

         /* Si une erreur s'est produite */
         if ( ( l_result == K_MK_OK ) && ( p_handler->pipe->status != K_MK_DMA_STATUS_TRANSFER_COMPLETED ) )
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

      /* Actualisation du compteur */
      l_counter++;

   /* Tant qu'une erreur se produit ou que le nombre d'émissions maximals n'a pas été atteind */
   } while ( ( *p_portStatus == K_MK_MMC_TRANSFER_ERROR ) && ( p_command->bypassCRC == K_MK_MMC_CRC_BYPASS_DISABLED ) && ( l_counter < K_MK_MMC_TIMEOUT_COUNT ) );

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_sendCmd ( T_mkMMCHandler* p_handler, T_mkMMCDevice* p_device, T_mkMMCCommand* p_command, T_mkAddr p_response, T_mkAddr p_buf, T_mkMMCPortStatus* p_portStatus )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_handler != K_MK_NULL ) && ( p_command != K_MK_NULL ) && ( p_portStatus != K_MK_NULL ) )
   {
      /* Si les attributs de la commande sont invalides */
      if ( ( p_command->length != 0 ) && ( ( p_buf == K_MK_NULL ) || ( p_device == K_MK_NULL ) ) )
      {
         /* Actualisation de la variable de retour */
         l_result = K_MK_ERROR_PARAM;
      }

      /* Sinon */
      else
      {
         /* Configuration de la taille du transfert MMC */
         mmc_setTransferSize ( p_command->length );

         /* Configuration du timeout du transfert MMC */
         /* Celui-ci est exprimé en nombre de cycles */
         mmc_setTimeout ( p_command->timeout * K_MK_MMC_FREQUENCY_MULTIPLIER );

         /* Configuration de la direction du transfert MMC */
         mmc_setDirection ( p_command->direction );

         /* Déclenchement du transfert MMC */
         l_result = mk_mmc_startTransfer ( p_handler, p_device, p_command, p_response, p_buf, p_portStatus );
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

