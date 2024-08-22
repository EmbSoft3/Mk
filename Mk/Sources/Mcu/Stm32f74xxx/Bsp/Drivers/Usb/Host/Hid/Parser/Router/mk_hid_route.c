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
* @file mk_hid_route.c
* @brief Définition de la fonction mk_hid_route.
* @date 30 oct. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setIdentifier ( uint16_t* p_identifier, T_mkAddr p_baseAddr, T_mkAddr p_poolAddr, uint32_t p_size )
{
   /* Détermination de l'identifiant unique de l'objet */
   *p_identifier = ( uint16_t ) ( ( ( uint32_t ) p_baseAddr - ( uint32_t ) p_poolAddr ) / p_size );

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_createControl ( T_mkHIDReport* p_report, T_mkCtrlId p_id, T_mkPool* p_pool, T_mkAddr p_heap, uint32_t p_chunkSize )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Enregistrement de l'adresse du contrôle */
   uint16_t** l_control = ( uint16_t** ) &p_report->addr;

   /* Enregistrement de l'adresse de la pool associée au contrôle */
   p_report->pool = p_pool;

   /* Allocation d'un nouveau contrôle */
   l_result = mk_pool_allocSafe ( p_pool, ( T_mkAddr* ) &p_report->addr, K_MK_POOL_CLEAR, 0 );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Configuration de l'identifiant du controle */
      **l_control = ( uint16_t ) p_id;
      mk_hid_setIdentifier ( ( ( uint16_t * ) p_report->addr + 1 ), p_report->addr, p_heap, p_chunkSize );
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

static T_mkCode mk_hid_routeUsage ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, uint32_t p_type )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'un usage */
   T_mkHIDUsage l_usage;

   /* Déclaration d'une variable de comptage et d'une variable contenant le nombre d'usage dans le 'Report' */
   uint32_t l_counter, l_usageNumber;

   /* Déclaration d'une variable de filtrage permettant d'exclure du processus de routage les usages présents entre */
   /* le début du 'Report' et l'identifiant de celui-ci.  */
   uint32_t l_bypass = p_report->id;

   /* Récupération du nombre total d'usage dans le 'Report' */
   l_result = mk_hid_getUsageNumber ( p_report, &l_usageNumber );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Pour l'intégralité des usages contenus dans le report */
      for ( l_counter = 0 ; ( l_counter < l_usageNumber ) && ( l_result == K_MK_OK ) ; l_counter++ )
      {
         /* Récupération de l'entrée courante */
         l_result = mk_hid_getUsage ( p_report, &l_usage, l_counter );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Réinitialisation de la table d'item local */
            _writeWords ( p_table->local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );

            /* Actualisation de la table d'item */
            /* On parcourt la table du début de l'usage jusqu'au prochain Item de type 'Main' afin de mettre */
            /* à jour la table des items global */
            /* La table est ensuite réactualisée dans la fonction de routage spécifique lorsqu'un item de type */
            /* 'Main' est rencontré */
            l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, &l_usage );

            /* Si aucune erreur ne s'est produite */
            if ( l_result == K_MK_OK )
            {
               /* Allocation d'une adresse mémoire pour chaque usage d'un controle */
               l_result = mk_hid_routeControl ( p_stack, p_table, p_report, &l_usage, &l_bypass, p_type );
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

static T_mkCode mk_hid_createControlByReport ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Déclaration d'une variable d'état */
   uint32_t l_routeEnabled = 1;

   /* Si le report est de type 'Mouse' */
   if ( p_table->local->usage == K_MK_HID_GENERIC_DESKTOP_PAGE_MOUSE )
   {
      /* Création du contole de type 'Mouse' */
      l_result = mk_hid_createControl ( p_report, K_MK_CONTROL_MOUSE, g_mkMousePool.pool, g_mkMousePool.heap, sizeof ( T_mkMouse ) );
   }

   /* Sinon si le report est de type 'Keyboard' */
   else if ( ( p_table->local->usage == K_MK_HID_GENERIC_DESKTOP_PAGE_KEYBOARD ) || ( p_table->local->usage == K_MK_HID_GENERIC_DESKTOP_PAGE_KEYPAD ) )
   {
      /* Création du contole de type 'Keyboard' */
      l_result = mk_hid_createControl ( p_report, K_MK_CONTROL_KEYBOARD, g_mkKeyboardPool.pool, g_mkKeyboardPool.heap, sizeof ( T_mkKeyboard ) );

      /* Si aucune erreur ne s'est produite */
      if ( l_result == K_MK_OK )
      {
         /* Configuration du type du clavier */
         l_result = mk_hid_keyboard_setCountryCode ( ( T_mkKeyboard* ) p_report->addr, p_hidDevice->hidDescriptor.bCountryCode );
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
      }
   }

   /* Sinon si le report est de type 'Joystick' */
   else if ( p_table->local->usage == K_MK_HID_GENERIC_DESKTOP_PAGE_JOYSTICK )
   {
      /* Création du contole de type 'Joystick' */
      l_result = mk_hid_createControl ( p_report, K_MK_CONTROL_JOYSTICK, g_mkJoystickPool.pool, g_mkJoystickPool.heap, sizeof ( T_mkJoystick ) );
   }

   /* Sinon si le report est de type 'Consumer' */
   else if ( p_table->local->usage == K_MK_HID_CONSUMER_PAGE_CONSUMER_CONTROL )
   {
      /* Création du contole de type 'Consumer' */
      l_result = mk_hid_createControl ( p_report, K_MK_CONTROL_CONSUMER, g_mkConsumerPool.pool, g_mkConsumerPool.heap, sizeof ( T_mkConsumerControl ) );
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable d'état */
      l_routeEnabled = 0;

      /* Le report n'est pas supporté */
      /* On actualise la table avec tous les items du report pour mettre à jour les items de type global. */
      l_result = mk_hid_setItemStateTableByReport ( p_stack, p_table, p_report );
   }

   /* Si aucune erreur ne s'est produite */
   if ( ( l_result == K_MK_OK ) && ( l_routeEnabled == 1 ) )
   {
      /* Routage des adresses dédiées au controle */
      l_result = mk_hid_routeUsage ( p_stack, p_table, p_report, p_table->local->usage );
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

static T_mkCode mk_hid_routeCollection ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result;

   /* Actualisation de la table d'item */
   /* On parcourt la table du début du 'Report' jusqu'au prochain Item de type 'Main' afin de mettre */
   /* à jour la table d'items. */
   /* La table est ensuite réactualisé dans la fonction de routage spécifique lorsqu'un item de type */
   /* 'Main' est rencontré */
   l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, ( T_mkHIDUsage* ) p_report );

   /* Si aucune erreur ne s'est produite */
   if ( l_result == K_MK_OK )
   {
      /* Création et routage du controle */
      l_result = mk_hid_createControlByReport ( p_hidDevice, p_stack, p_table, p_report );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Si aucune erreur ne s'est produite et si un événement de connexion doit être posté */
   if ( ( l_result == K_MK_OK ) && ( p_report->pool != K_MK_NULL ) )
   {
      /* Transmission d'un événement aux dispatcher */
      /* Etant donné que la priorité du dispatcher doit être supérieure à la priorité de la tâche HID, */
      /* le contrôle peut être transféré par référence. */
      l_result = mk_hid_dispatchMessage ( p_report, K_MK_EVENT_CONNECT );
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

T_mkCode mk_hid_route ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un compteur d'usage général et d'une variable stockant le nombre de report principale (application) */
   uint32_t l_counter = 0, l_reportNumber = 0;

   /* Déclaration d'un pointeur de report */
   T_mkHIDReport** l_report = &p_hidDevice->report;

   /* Déclaration d'une table d'item */
   T_mkHIDReportTable l_itemTable = { { 0 }, K_MK_NULL };

   /* Déclaration d'une stack stockant les items locaux */
   T_mkHIDReportStack l_itemStack;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_hidDevice->reportDescriptor.item != K_MK_NULL ) )
   {
      /* Initialisation de la stack */
      l_itemStack.top = K_MK_NULL;

      /* Allocation d'une table d'item local */
      l_result = mk_pool_allocSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr* ) &l_itemTable.local, K_MK_POOL_CLEAR, 0 );

      /* Si aucune erreur ne s'est produite */
      if ( ( l_result == K_MK_OK ) && ( l_itemTable.local != K_MK_NULL ) )
      {
         /* Récupération du nombre de reports */
         l_result = mk_hid_getReportNumber ( p_hidDevice, &l_reportNumber );

         /* Il ne peut y avoir qu'une application par 'Report'. Si plusieurs 'Report' sont présents alors un 'ReportID' doit être */
         /* associé à chaque application. */
         /* Si une seul application est présente, le Report ID est optionnel */

         /* Pour chaque 'Report' */
         for ( l_counter = 0 ; ( l_counter < l_reportNumber ) && ( l_result == K_MK_OK ) ; l_counter++ )
         {
            /* Allocation d'un 'Report' */
            l_result = mk_pool_allocSafe ( g_mkHIDPool.reportPool, ( T_mkAddr* ) l_report, K_MK_POOL_CLEAR, 0 );

            /* Si aucune erreur ne s'est produite */
            if ( ( l_result == K_MK_OK ) && ( l_report != K_MK_NULL ) )
            {
               /* Récupération du 'Report' courant */
               l_result = mk_hid_getReport ( p_hidDevice, *l_report, l_counter );

               /* Si aucune erreur ne s'est produite */
               if ( l_result == K_MK_OK )
               {
                  /* Routage des usages du report */
                  l_result = mk_hid_routeCollection ( p_hidDevice, &l_itemStack, &l_itemTable, *l_report );
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Actualisation de l'adresse du report */
               l_report = &( *l_report )->next;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
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


