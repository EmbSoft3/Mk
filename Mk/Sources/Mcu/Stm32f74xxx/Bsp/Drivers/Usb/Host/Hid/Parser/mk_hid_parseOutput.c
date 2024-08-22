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
* @file mk_hid_parseOutput.c
* @brief Définition de la fonction mk_hid_parseOutput.
* @date 11 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_parseOutputContent ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le champ à parser est une sortie */
   if ( p_usage->last->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT )
   {
      /* Tant que tous les items de la sortie courante n'ont pas été analysés */
      while ( p_usage->first != p_usage->last->nextItem )
      {
         /* Si l'item courant est un item de type 'Usage' ou si l'item courant est une entrée de padding */
         if ( ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE ) ||
            ( ( ( p_usage->last->value & K_MK_HID_ITEM_CONSTANT ) == K_MK_HID_ITEM_CONSTANT ) && ( p_usage->first == p_usage->last ) ) ) )
         {
            /* Récupération et transmission de la valeur de l'usage au périphérique HID */
            l_result = mk_hid_writeUsage ( p_hidDevice, p_pipe, p_parser, p_table, p_usage );
         }

         /* Sinon si l'item courant est un item de type 'Usage Minimum' */
         else if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
         {
            /* Récupération et transmission de la valeur de l'ensemble des usages au périphérique HID */
            l_result = mk_hid_writeMultipleUsage ( p_hidDevice, p_pipe, p_parser, p_table, p_usage );
         }

         /* La table d'item local doit être réinitialisée lorsqu'un item de type 'Main' est rencontré */
         /* Etant donné que chaque usage est déterminé en fonction des items 'input', 'output' et 'feature', on ne réinitialise la table que */
         /* lorsqu'on rencontre des items 'Collection' et 'End Collection'. */
         else if ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION ) )
         {
            /* Réinitialisation de la table d'item local */
            _writeWords ( p_table->local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );

            /* Actualisation des tables globale et locale jusqu'au prochain item de type 'Main' */
            l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, p_usage );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du pointeur d'usage */
         p_usage->first = p_usage->first->nextItem;
      }
   }

   /* Sinon */
   else
   {
      /* Tant que tous les items de l'entrée courante n'ont pas été analysé */
      while ( p_usage->first != p_usage->last->nextItem )
      {
         /* Si l'item est un item de type 'Main' */
         if ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION ) ||
              ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
         {
            /* Réinitialisation de la table d'item local */
            _writeWords ( p_table->local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );

            /* Actualisation des tables globale et locale jusqu'au prochain item de type 'Main' */
            l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, p_usage );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du pointeur d'usage */
         p_usage->first = p_usage->first->nextItem;
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

static T_mkCode mk_hid_parseOutputUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un usage */
   T_mkHIDUsage l_usage;

   /* Déclaration d'une variable de comptage et d'une variable contenant le nombre d'usages dans le 'report' */
   uint32_t l_counter, l_usageNumber;

   /* Récupération du nombre d'entrées sorties dans le 'Report' courant */
   /* La fonction compte le nombre de balises 'Input', 'Output' et 'Feature'. */
   l_result = mk_hid_getUsageNumber ( p_report, &l_usageNumber );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Pour l'intégralité des balises 'Input', 'Output' et 'Feature' contenues dans le report */
      for ( l_counter = 0 ; l_counter < l_usageNumber ; l_counter++ )
      {
         /* Récupération de l'entrée/sortie courante */
         /* Le dernier 'Item' est obligatoirement un item de type 'Input', 'Output' ou 'Feature' */
         l_result = mk_hid_getUsage ( p_report, &l_usage, l_counter );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Actualisation de la table d'item */
            l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, &l_usage );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Récupération et transmission de la valeur de l'ensemble des usages au périphérique HID */
               l_result = mk_hid_parseOutputContent ( p_hidDevice, p_pipe, p_parser, p_stack, p_table, &l_usage );
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

T_mkCode mk_hid_parseOutput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un pointeur de report */
   T_mkHIDReport* l_report;

   /* Déclaration d'un parser HID */
   T_mkHIDUsageParser l_parser = { 0 };

   /* Déclaration d'un stack stockant les items locaux */
   T_mkHIDReportStack l_itemStack = { K_MK_NULL };

   /* Déclaration d'une table d'items */
   T_mkHIDReportTable l_itemTable = { { 0 }, K_MK_NULL };

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) && ( p_report != K_MK_NULL ) )
   {
      /* Allocation d'une table d'items locale */
      l_result = mk_pool_allocSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr* ) &l_itemTable.local, K_MK_POOL_CLEAR, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Le parser des sorties HID ne s'occupe que d'un seul 'Report'. */
         /* Il est juste nécessaire mettre à jour la table d'item locale des 'Report' non traités. */
         for ( l_report = p_hidDevice->report ; ( l_report != p_report ) && ( l_result == K_MK_OK ) ; l_report = l_report->next )
         {
            /* Actualisation des tables locale et globale */
            l_result = mk_hid_setItemStateTableByReport ( &l_itemStack, &l_itemTable, l_report );
         }

         /* La table étant à jour, le formatage des sorties du report peut être réalisé sous condition qu'aucune erreur */
         /* ne se soit produite. */
         if ( l_result == K_MK_OK )
         {
            /* Il est temps d'initialiser les attributs initiaux du parser. */

            /* Si la taille du 'Report' est supérieure au 'MaxPacketSize' */
            if ( p_report->outputSize > p_hidDevice->inEndpoint->wMaxPacketSize )
            {
               /* Configuration du nombre de bits total à écrire dans la transaction */
               l_parser.bitNumber = ( uint32_t ) ( p_hidDevice->inEndpoint->wMaxPacketSize << 3 );

               /* Détermination du nombre d'octets restants à écrire dans la transaction */
               /* Ce nombre est non nul car le transfert est constitué de plusieurs transactions. */
               l_parser.byteRemaining = ( uint32_t ) p_report->outputSize - p_hidDevice->inEndpoint->wMaxPacketSize;
            }

            /* Sinon */
            else
            {
               /* Configuration du nombre de bits total à écrire dans la transaction */
               l_parser.bitNumber = ( uint32_t ) ( p_report->outputSize << 3 );

               /* Détermination du nombre d'octets totals à écrire dans la transaction. */
               /* Ce nombre est nul car le transfert est constitué d'une seule transaction. */
               l_parser.byteRemaining = 0;
            }

            /* Configuration du nombre initial de bits disponibles (1 octet) */
            /* Entant donné que les données sont alignées sur 8 bits, le nombre minimal de bits est obligatoirement 8. */
            l_parser.bitAvailable = 8;

            /* Réalisation du formatage des sorties */
            l_result = mk_hid_parseOutputUsage ( p_hidDevice, p_pipe, &l_parser, &l_itemStack, &l_itemTable, p_report );

            /* Le buffer USB vient d'être écrit avec la valeur du 'Report'. Il est temps d'envoyer sur le bus la dernière */
            /* transaction du transfert. */

            /* Si la transaction doit s'effectuer via une interruption */
            if ( p_hidDevice->outEndpoint != K_MK_NULL )
            {
               /* Réalisation d'une transaction USB via la requête d'interruption */
               /* Le nombre d'octets écrit dans le buffer de données HID est stocké dans la variable 'byteOffset' */
               /* Les données sont alignées sur 1 octet, il n'est pas nécessaire d'incrémenter la variable. */
               l_result |= mk_hid_setInterrupt ( p_hidDevice, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf, ( uint16_t ) l_parser.byteOffset );
            }

            /* Sinon */
            else
            {
               /* Réalisation d'une transaction USB via une requête de contrôle */
               /* Le nombre d'octet écrit dans le buffer de données HID est stocké dans la variable 'byteOffset' */
               /* Les données sont alignées sur 1 octet, il n'est pas nécessaire d'incrémenter la variable. */
               l_result |= mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf,
                                            ( uint32_t ) ( K_MK_HCD_ENDPOINT_OUT | K_MK_HCD_PID_DATA1 ), l_parser.byteOffset );
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désallocation de la table d'item local */
         l_result |= mk_pool_freeSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr ) l_itemTable.local );
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


