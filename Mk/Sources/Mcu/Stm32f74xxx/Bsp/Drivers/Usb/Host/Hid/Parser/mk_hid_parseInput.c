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
* @file mk_hid_parseInput.c
* @brief Définition de la fonction mk_hid_parseInput.
* @date 11 janv. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_parseInputContent ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le champ à parser est une entrée */
   if ( p_usage->last->head.field.tag == K_MK_HID_ITEM_TAG_INPUT )
   {
      /* Tant que tous les items de l'entrée courante n'ont pas été analysé */
      while ( p_usage->first != p_usage->last->nextItem )
      {
         /* Si l'item courant est un item de type 'Usage' ou si l'item courant est une entrée de padding */
         if ( ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE ) ||
            ( ( ( p_usage->last->value & K_MK_HID_ITEM_CONSTANT ) == K_MK_HID_ITEM_CONSTANT ) && ( p_usage->first == p_usage->last ) ) ) )
         {
            /* Récupération de la valeur de l'usage */
            l_result = mk_hid_readUsage ( p_hidDevice, p_pipe, p_parser, p_table, p_usage );
         }

         /* Sinon si l'item courant est un item de type 'Usage Minimum' */
         else if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
         {
            /* Récupération de la valeur d'un ensemble d'usage */
            l_result = mk_hid_readMultipleUsage ( p_hidDevice, p_pipe, p_parser, p_table, p_usage );
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

static T_mkCode mk_hid_parseInputUsage ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDUsageParser* p_parser, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un usage */
   T_mkHIDUsage l_usage;

   /* Déclaration d'une variable de comptage et d'une variable contenant le nombre d'usage dans le 'report' */
   uint32_t l_counter, l_usageNumber;

   /* Récupération du nombre d'entrées sorties dans le 'Report' courant */
   /* La fonction compte le nombre de balises 'Input', 'Output' et 'Feature'. */
   l_result = mk_hid_getUsageNumber ( p_report, &l_usageNumber );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Pour l'intégralité des balises 'Input', 'Output' et 'Feature' contenues dans le 'Report' courant */
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
               /* Récupération de la valeur de l'ensemble des usages au périphérique HID */
               l_result = mk_hid_parseInputContent ( p_hidDevice, p_pipe, p_parser, p_stack, p_table, &l_usage );
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

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Transmission d'un message au dispatcher */
         l_result = mk_hid_dispatchMessage ( p_report, K_MK_EVENT_NO );
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

static T_mkCode mk_hid_parseInputReport ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, uint16_t p_endpointType )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de report */
   T_mkHIDReport* l_unusedReport;

   /* Déclaration d'un parser HID */
   T_mkHIDUsageParser l_parser = { 0 };

   /* Déclaration d'un stack stockant les items locaux */
   T_mkHIDReportStack l_itemStack = { K_MK_NULL };

   /* Dans le cas où l'identifiant est nul, il n'y a qu'un seul 'Report'. */
   /* Si les données correspondent au 'Report' courant */
   if ( ( p_report->id == 0 ) || ( p_report->id == g_mkHIDPacketBuf [ 0 ] ) )
   {
      /* Si la taille du 'Report' est supérieure au 'MaxPacketSize' */
      if ( p_report->inputSize > p_hidDevice->inEndpoint->wMaxPacketSize )
      {
         /* Configuration du nombre de bits disponibles pour l'analyse de la transaction */
         l_parser.bitNumber = ( uint32_t ) ( p_hidDevice->inEndpoint->wMaxPacketSize << 3 );

         /* Actualisation du nombre d'octets restant à récupérer */
         /* Ce nombre est non nul car le transfert est constitué de plusieurs transactions. */
         l_parser.byteRemaining = ( uint32_t ) p_report->inputSize - p_hidDevice->inEndpoint->wMaxPacketSize;
      }

      /* Sinon */
      else
      {
         /* Configuration du nombre de bits disponibles pour l'analyse de la transaction */
         l_parser.bitNumber = ( uint32_t ) ( p_report->inputSize << 3 );

         /* Actualisation du nombre d'octets restant à récupérer. */
         /* Ce nombre est nul car le transfert est constitué d'une seule transaction. */
         l_parser.byteRemaining = 0;
      }

      /* Configuration du nombre initial de bits disponibles (1 octet) */
      /* Entant donné que les données sont alignées sur 8 bits, le nombre minimal de bits est obligatoirement 8. */
      l_parser.bitAvailable = 8;

      /* Configuration du type de terminaison */
      l_parser.endpointType = p_endpointType;

      /* Le report à récupérer est contenu dans la structure 'p_report'. */
      /* Il faut mettre à jour la table d'item locale des 'Report' non traités. */
      for ( l_unusedReport = p_hidDevice->report ; ( l_unusedReport != p_report ) && ( l_result == K_MK_OK ) ; l_unusedReport = l_unusedReport->next )
      {
         /* Actualisation des tables locale et globale */
         l_result = mk_hid_setItemStateTableByReport ( &l_itemStack, p_table, l_unusedReport );
      }

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Analyse des usages présents dans le 'Report' */
         /* On transmet la taille restante à récupérer afin de connaitre la taille des prochaines transactions. */
         l_result = mk_hid_parseInputUsage ( p_hidDevice, p_pipe, &l_parser, &l_itemStack, p_table, p_report );
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

static T_mkCode mk_hid_postEmptyMessage ( T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant le type du 'Report' */
   uint16_t l_type;

   /* Si un contrôle applicatif est associé au 'Report' */
   if ( p_report != K_MK_NULL )
   {
      /* Récupération du type du contrôle */
      l_type = ( uint16_t ) ( * ( uint16_t* ) p_report->addr );

      /* Si le controle est de type 'Keyboard' ou 'Keypad' */
      if ( l_type == K_MK_CONTROL_KEYBOARD )
      {
         /* Transmission d'un message au dispatcher */
         l_result = mk_hid_dispatchMessage ( p_report, K_MK_EVENT_NO );
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

T_mkCode mk_hid_parseInput ( T_mkHIDDevice* p_hidDevice, T_mkHCDPipe* p_pipe, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de 'Report' */
   T_mkHIDReport *l_report;

   /* Déclaration d'une table d'items */
   T_mkHIDReportTable l_itemTable = { { 0 }, K_MK_NULL };

   /* Déclaration d'une variable stockant la taille d'une transaction lorsque le 'Pipe' de contrôle est utilisé */
   uint16_t l_packetLength = p_hidDevice->device->deviceDescriptor.bMaxPacketSize0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_pipe != K_MK_NULL ) )
   {
      /* Allocation d'une table d'items locale */
      l_result = mk_pool_allocSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr* ) &l_itemTable.local, K_MK_POOL_CLEAR, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Si l'intégralité des reports doivent être récupérés */
         if ( p_report == K_MK_NULL )
         {
            /* La spécification HID impose qu'un seul 'Report' soit contenu dans un transfert USB. Cependant, un report peut être constitué de plusieurs */
            /* transactions USB. */

            /* Pour le nombre de reports contenus dans le descripteur */
            for ( p_report = p_hidDevice->report ; ( p_report != K_MK_NULL ) && ( l_result == K_MK_OK) ; p_report = p_report->next )
            {
               /* Transmission d'une requête d'interruption */
               /* Dans le cas d'une requête d'interruption, le parser ne peut pas connaitre l'identifiant et la taille du 'Report' qui va être envoyé. */
               /* Il est donc obligatoire de configurer la taille du paquet à 'MaxPacketSize'. */
               l_result = mk_hid_getInterrupt ( p_hidDevice, p_pipe, g_mkHIDPacketBuf, p_hidDevice->inEndpoint->wMaxPacketSize );

               /* Si la requête a été acquitée */
               if ( ( l_result == K_MK_OK ) && ( ( p_pipe->status & K_MK_HCD_FLAG_ACK ) == K_MK_HCD_FLAG_ACK ) )
               {
                  /* La spécification HID n'impose pas que l'ordre des reports transmis lors d'une requête d'interruption soit conforme au descripteur de 'Report' */
                  /* Une comparaison des identifiants de chaque 'Report' est donc réalisée pour s'assurer que les données sont correctement routées. */

                  /* On parcourt les reports de la structure 'ReportDescriptor' afin d'identifier le report à partir de son identifiant */
                  for ( l_report = p_hidDevice->report ; ( l_report != K_MK_NULL ) && ( l_result == K_MK_OK) ; l_report = l_report->next )
                  {
                     /* Récupération et transmission des informations du report vers le dispatcher */
                     l_result = mk_hid_parseInputReport ( p_hidDevice, p_pipe, &l_itemTable, l_report, K_USB_INTERRUPT_ENDPOINT );
                  }
               }

               /* Sinon */
               else
               {
                  /* Aucune nouvelle donnée n'est disponible. */
                  /* Cependant, pour certain contrôle de type applicatif, il est nécessaire de transmettre un message au dispatcher pour la gestion de certains */
                  /* événements (cf. événement HOLD du clavier). */
                  l_result = mk_hid_postEmptyMessage ( p_report );
               }
            }
         }

         /* Sinon */
         else
         {
            /* Si la taille de la transaction est inférieure à la taille maximale d'un paquet */
            if ( p_report->inputSize < p_hidDevice->device->deviceDescriptor.bMaxPacketSize0 )
            {
               /* Actualisation de la taille de la transaction */
               l_packetLength = ( uint16_t ) p_report->inputSize;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }

            /* Transmissin d'une requête */
            /* Le première transaction est obligatoirement égale à la taille maximale d'un paquet. */
            /* Une transaction supplémentaire sera réémise si la taille du 'Report' est supérieure à la taille maximale d'un paquet. */
            l_result = mk_hcd_sendPipe ( p_hidDevice->device, K_MK_NULL, p_pipe, ( uint8_t* ) g_mkHIDPacketBuf,
                                         ( uint32_t ) ( K_MK_HCD_ENDPOINT_IN | K_MK_HCD_PID_DATA1 ), l_packetLength );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( ( p_pipe->status & K_MK_HCD_FLAG_ACK ) == K_MK_HCD_FLAG_ACK ) )
            {
               /* Récupération et transmission des informations du 'Report' vers la tâche de traitement */
               l_result = mk_hid_parseInputReport ( p_hidDevice, p_pipe, &l_itemTable, p_report, K_USB_CONTROL_ENDPOINT );
            }

            /* Sinon */
            else
            {
               /* Aucune nouvelle donnée n'est disponible. */
               /* Cependant, pour certain contrôle de type applicatif, il est nécessaire de transmettre un message au dispatcher pour la gestion de certains */
               /* événements (cf. événement HOLD du clavier). */
               l_result = mk_hid_postEmptyMessage ( p_report );
            }
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

