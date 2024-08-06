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
* @file mk_mmc_handleReadyState.c
* @brief Définition de la fonction mk_mmc_handleReadyState.
* @date 1 juil. 2020
*
*/

#include "mk_mmc_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_mmc_post_sendIfCmd ( T_mkMMCHandler* p_handler, uint8_t p_supplyVoltage, uint8_t p_checkPattern )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable de travail */
   uint32_t l_response;

   /* Déclaration d'un registre de statuts */
   T_mkMMCPortStatus l_status = K_MK_MMC_NO_FLAG;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_SEND_IF_COND,                                           /* Code de la commande */
         ( uint32_t ) ( p_checkPattern | ( ( p_supplyVoltage & 0xF ) << 8 ) ),   /* Argument de la commande */
         K_MMC_DIRECTION_CONTROLLER_TO_CARD,                                     /* Direction du transfert */
         0,                                                                      /* Nombre de données */
         0,                                                                      /* Timeout du transfert de données */
         K_MMC_SHORT_RESPONSE,                                                   /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_DISABLED                                            /* Bypass CRC désactivé */
   };

   /* Transmission de la commande (CMD8) */
   l_result = mk_mmc_sendCmd ( p_handler, K_MK_NULL, &l_command, &l_response, K_MK_NULL, &l_status );

   /* Si la carte n'est pas supportée */
   if ( ( l_result == K_MK_OK ) &&
        ( l_response != ( uint32_t ) ( p_checkPattern | ( ( p_supplyVoltage & 0xF ) << 8 ) ) ) )
   {
      /* On bascule la carte dans l'état inactif, elle n'est pas utilisable */
      p_handler->state = K_MK_MMC_STATE_INACTIVE;
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

static T_mkCode mk_mmc_post_sendSDCOpCond ( T_mkMMCHandler* p_handler, T_mkMMCOCRRegister* p_ocr, uint32_t p_arg )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre de statuts */
   T_mkMMCPortStatus l_status = K_MK_MMC_NO_FLAG;

   /* Initialisation de la commande MMC */
   T_mkMMCCommand l_command = {
         K_MK_MMC_OPCODE_SDC_SEND_OP_COND,      /* Code de la commande */
         p_arg,                                 /* Argument de la commande */
         K_MMC_DIRECTION_CONTROLLER_TO_CARD,    /* Direction du transfert */
         0,                                     /* Nombre de données */
         0,                                     /* Timeout du transfert de données */
         K_MMC_SHORT_RESPONSE,                  /* Longueur de la réponse */
         K_MK_MMC_CRC_BYPASS_ENABLED            /* Bypass CRC activé (le registre OCR ne transporte pas de CRC) */
   };

   /* Activation du mode applicatif (ACDM) */
   /* A cette instant de l'initialisation, la carte ne possède pas d'adresse relative. */
   l_result = mk_mmc_setApplicationMode ( p_handler, K_MK_NULL, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Transmission de la commande (ACDM41) */
      l_result = mk_mmc_sendCmd ( p_handler, K_MK_NULL, &l_command, p_ocr, K_MK_NULL, &l_status );
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

static T_mkCode mk_mmc_waitReadyState ( T_mkMMCHandler* p_handler, uint32_t p_argument )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un registre OCR */
   T_mkMMCOCRRegister l_ocr = { 0 };

   /* Déclaration d'un compteur */
   uint32_t l_counter = 0;

   /* Transfert de la commande "SEND_OP_COND" (ACMD41) en boucle tant que la carte n'a pas */
   /* finie son initialisation interne. */
   /* Le bit HCS doit être positionné à la valeur haute pour les cartes de grande capacité (>2GB). */
   do
   {
      /* Transmission de la commande "SEND_OP_COND" (ACDM41) */
      l_result = mk_mmc_post_sendSDCOpCond ( p_handler, &l_ocr, p_argument );

      /* Attente */
      l_result |= mk_task_sleep ( 5 );

      /* Actualisation du compteur */
      l_counter++;

   /* Tant que la carte n'a pas basculée de l'état 'IDLE' et 'READY' */
   } while ( ( l_ocr.busy == 0 ) && ( l_counter < K_MK_MMC_IDLE_TO_READY_TIMEOUT ) );

   /* Si la carte n'est pas prête au bout du timeout */
   if ( l_ocr.busy == 0 )
   {
      /* Actualisation de l'état du périphérique */
      p_handler->state = K_MK_MMC_STATE_INACTIVE;
   }

   /* Sinon */
   else
   {
      /* Actualisation de l'état du périphérique */
      p_handler->state = K_MK_MMC_STATE_READY;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_mmc_handleReadyState ( T_mkMMCHandler* p_handler )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Si les paramètres sont valides */
   if ( p_handler != K_MK_NULL )
   {
      /* Un périphérique SD ne peut supporter qu'une carte à la fois à l'initialisation */
      /* On transmet la commande "GO_IDLE_STATE" pour le faire basculer à l'état de repos. */

      /* Transmission de la commande "GO_IDLE_STATE (CMD0)" */
      l_result = mk_mmc_setIdleState ( p_handler );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Actualisation de l'état du bus */
         p_handler->state = K_MK_MMC_STATE_IDLE;

         /* Transmission de la commande "SEND_IF_COND (CMD8)" */
         /* Cette commande est supportée uniquement par les cartes SD de version supérieure à 2. */
         /* Elle permet de vérifier si la carte supporte la tension d'alimentation du maitre. */
         /* La plage est transmise dans le champ VHS (une plage à la fois), le pattern est arbitraire. */
         l_result = mk_mmc_post_sendIfCmd ( p_handler, K_MK_MMC_VOLTAGE_RANGE_2V7_TO_3V6, K_MK_MMC_ARBITRARY_PATTERN );

         /* Si une réponse a été reçue */
         /* La carte est alors une carte de version 2.0 ou supérieure */
         if ( l_result == K_MK_OK )
         {
            /* Si la carte est compatible avec la plage d'alimentation */
            if ( p_handler->state == K_MK_MMC_STATE_IDLE )
            {
               /* Transmission de la commande  "SEND_OP_COND" (ACMD41) en boucle tant que la carte n'est pas initialisée */
               l_result = mk_mmc_waitReadyState ( p_handler, K_MK_MMC_BUSY_BIT | K_MK_MMC_HCS_BIT | K_MK_MMC_VOLTAGE_RANGE );
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
               /* Il n'est pas nécessaire de continuer l'initialisation. */
            }
         }

         /* Sinon si aucune réponse n'a été reçue */
         /* La carte est une carte de version 1.x */
         else if ( l_result == K_MK_ERROR_TIMEOUT )
         {
            /* Transmission de la commande  "SEND_OP_COND" (ACMD41) en boucle tant que la carte n'est pas initialisée */
            /* Les cartes de version 1 ne sont pas de type 'High Capacity'. */
            l_result = mk_mmc_waitReadyState ( p_handler, K_MK_MMC_BUSY_BIT | K_MK_MMC_VOLTAGE_RANGE );
         }

         /* Sinon */
         else
         {
            /* Une erreur de communication s'est produite */
            /* On actualise l'état du bus */
            p_handler->state = K_MK_MMC_STATE_INACTIVE;
         }
      }

      /* Sinon */
      else
      {
         /* Il est probable qu'aucune carte ne soit présente sur le bus */
         /* L'état du bus est déjà inactif, on n'actualise donc pas le status. */
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



