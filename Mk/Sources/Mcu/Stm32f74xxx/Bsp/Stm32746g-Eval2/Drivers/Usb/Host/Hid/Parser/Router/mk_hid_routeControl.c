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
* @file mk_hid_routeControl.c
* @brief Définition de la fonction mk_hid_routeControl.
* @date 10 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_get32bitsUsagePage ( T_mkHIDUsage* p_usage, uint32_t p_page )
{
   /* Si l'item est un usage 32 bits */
   if ( ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MAXIMUM ) ||
          ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE ) ) && ( p_usage->first->head.field.size == 3 ) )
   {
      /* Le parser a vérifié précédemment que la valeur de les pages de 'Usage minimal' et 'Usage Maximal' sont identiques. */
      /* Récupération de la valeur de la page courante */
      p_page = p_usage->first->value >> 16;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return ( p_page );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_routeUsageToControl ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_type, uint32_t p_page, uint32_t* p_usageUsed )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si le contrôle est de type 'Mouse' */
   if ( p_type == K_MK_HID_GENERIC_DESKTOP_PAGE_MOUSE )
   {
      /* Allocation des données mémoires dédiées à une souris */
      l_result = mk_hid_routeMouse ( p_table, p_report, p_usage, p_page, p_usageUsed );
   }

   /* Sinon si le contrôle est de type 'Keyboard' */
   else if ( ( p_type == K_MK_HID_GENERIC_DESKTOP_PAGE_KEYBOARD ) || ( p_type == K_MK_HID_GENERIC_DESKTOP_PAGE_KEYPAD ) )
   {
      /* Allocation des données mémoires dédiées à un clavier */
      l_result = mk_hid_routeKeyboard ( p_table, p_report, p_usage, p_page, p_usageUsed );
   }

   /* Sinon si le contrôle est de type 'Joystick' */
   else if ( p_type == K_MK_HID_GENERIC_DESKTOP_PAGE_JOYSTICK )
   {
      /* Allocation des données mémoires dédiées à un joystick */
      l_result = mk_hid_routeJoystick ( p_table, p_report, p_usage, p_page, p_usageUsed );
   }

   /* Sinon si le contrôle est de type 'Consumer' */
   else if ( p_type == K_MK_HID_CONSUMER_PAGE_CONSUMER_CONTROL )
   {
      /* Allocation des données mémoires dédiées au objet de type 'Consumer' */
      l_result = mk_hid_routeConsumer ( p_table, p_report, p_usage, p_page, p_usageUsed );
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

static T_mkCode mk_hid_routeAlternateUsage ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_type, uint32_t p_page, uint32_t* p_usageUsed )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un usage */
   T_mkHIDUsage l_usage;

   /* Enregistrement de l'adresse du premier usage alternatif */
   l_usage.first = p_usage->first->nextAlternate;

   /* En fonction du 'Report Descriptor', plusieurs utilisations (usage) peuvent être assignées à un contrôle. Il est donc */
   /* nécessaire de vérifier qu'une utilisation reconnue n'est pas référencée dans les usages alternatifs. */
   /* Toutes les utilisations partagent la même adresse mémoire. Le processus peut donc être stoppé si au moins un 'Usage' */
   /* est reconnue. */

   /* Tant que des usages alternatifs sont à analyser */
   while ( ( l_result == K_MK_OK ) && ( l_usage.first != K_MK_NULL ) && ( ( *p_usageUsed ) == 0 ) )
   {
      /* Routage de l'usage alternatif courant */
      l_result = mk_hid_routeUsageToControl ( p_table, p_report, &l_usage, p_type, p_page, p_usageUsed );

      /* Passage au prochain item */
      l_usage.first = l_usage.first->nextItem;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_routeControl ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t* p_bypass, uint32_t p_type )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'une variable stockant la page courante */
   uint32_t l_page;

   /* Déclaration d'une variable indiquant si l'usage est reconnu ou non */
   uint32_t l_usageUsed = 0 ;

   /* Si les paramètres sont valides */
   if ( ( p_stack != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_report != K_MK_NULL ) && ( p_usage != K_MK_NULL ) && ( p_bypass != K_MK_NULL ) )
   {
      /* Actualisation de la valeur de la page courante */
      l_page = p_table->global.usagePage;

      /* Tant que l'intégralité des usages du report n'ont pas été traités */
      while ( ( l_result == K_MK_OK ) && ( p_usage->first != p_usage->last->nextItem ) )
      {
         /* La table d'item local doit être réinitialée lorsqu'un item de type 'Main' est rencontré */
         /* Etant donné que chaque usage est déterminé en fonction des items 'Input', 'output' et 'feature', on ne réinitialise la table que */
         /* lorsqu'on rencontre des items 'Collection' et 'End Collection'. */

         /* Si l'item est de type 'Main' */
         if ( ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION ) || ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION ) )
         {
            /* Réinitialisation de la table d'item local */
            _writeWords ( p_table->local, 0, sizeof ( T_mkHIDLocalTable ) >> 2 );

            /* Réinitialisation de table d'item jusqu'au prochain item de type 'Main' */
            l_result = mk_hid_setItemStateTableByUsage ( p_stack, p_table, p_usage );

            /* Actualisation de la valeur de la page courante */
            l_page = p_table->global.usagePage;
         }

         /* Sinon si l'item est un 'Report ID' */
         else if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID )
         {
            /* Si l'identifiant est le premier du 'Report' */
            if ( ( *p_bypass ) != 0 )
            {
               /* Le 'Report ID' doit être parsé mais n'est pas routé */
               /* Il prend donc une adresse nulle */
               p_usage->first->addr = K_MK_NULL;
            }

            /* Sinon */
            else
            {
               /* Le 'Report ID' doit être parsé mais n'est pas routé */
               /* Il prend donc une adresse invalide */
               p_usage->first->addr = K_MK_INVALID_HANDLE;
            }

            /* Basculement de la variable de filtrage */
            *p_bypass = 0;
         }

         /* Sinon */
         else
         {
            /* Si l'usage n'est pas de type constant */
            if ( ( p_usage->last->value & K_MK_HID_ITEM_CONSTANT ) != K_MK_HID_ITEM_CONSTANT )
            {
               /* Si l'usage est de type fonctionnel */
               if ( ( p_table->global.reportSize != 0 ) && ( ( *p_bypass ) == 0 ) )
               {
                  /* Dans le cas où l'usage est de type 32bits, la page HID est contenu dans le mot 16bits de poids fort. */
                  l_page = mk_hid_get32bitsUsagePage ( p_usage, l_page );

                  /* Routage de l'usage principal */
                  l_result = mk_hid_routeUsageToControl ( p_table, p_report, p_usage, p_type, l_page, &l_usageUsed );

                  /* Si aucune erreur ne s'est produite */
                  if ( l_result == K_MK_OK )
                  {
                     /* Réalisation du processus de routage des usages alternatifs */
                     l_result = mk_hid_routeAlternateUsage ( p_table, p_report, p_usage, p_type, l_page, &l_usageUsed );
                  }

                  /* Sinon */
                  else
                  {
                     /* Ne rien faire */
                  }

                  /* Actualisation de la valeur de la page courante */
                  l_page = p_table->global.usagePage;
               }

               /* Sinon */
               else
               {
                  /* Enregistrement d'une adresse invalide pour ignorer l'usage */
                  p_usage->first->addr = K_MK_INVALID_HANDLE;
               }
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
            }
         }

         /* Actualisation de l'item courant */
         p_usage->first = p_usage->first->nextItem;
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



