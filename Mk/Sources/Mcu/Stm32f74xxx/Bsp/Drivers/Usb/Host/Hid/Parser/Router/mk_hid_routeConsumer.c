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
* @file mk_hid_routeConsumer.c
* @brief Définition de la fonction mk_hid_routeConsumer.
* @date 11 avr. 2020
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_routeConsumerUsage ( T_mkConsumerControl* p_consumer, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur de bouton */
   T_mkConsumerCode** l_consumerCode;

   /* Si les valeurs des usages sont codées au maximum sur 4 octets */
   if ( p_table->global.reportSize <= K_MK_HID_MAX_USAGE_SIZE )
   {
      /* Récupération de l'adresse du dernier usage de type 'Consumer' présent dans la chaine */
      l_consumerCode = mk_hid_button_getLast ( &p_consumer->control );

      /* Si aucun contrôle n'a été assigné à l'usage */
      if ( ( *l_consumerCode ) == K_MK_NULL )
      {
         /* Création d'une table d'usages de type 'Consumer' (la taille de destination est configurée dans cette fonction) */
         l_result = mk_hid_button_create ( p_table, p_usage, 1 );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement de l'adresse mémoire de l'usage */
            ( *l_consumerCode ) = p_usage->first->addr;

            /* Modification de l'adresse de base de l'usage */
            p_usage->first->addr = &(*l_consumerCode)->state.value;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Une erreur grave s'est produite, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
            /* les usages alternatifs */
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
      /* La taille de l'usage est incompatible avec le driver, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
      /* les usages alternatifs car ils possèdent tous la même taille. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_routeMultipleConsumerUsage ( T_mkConsumerControl* p_consumer, T_mkHIDReportTable* p_table, T_mkHIDUsage* p_usage, uint32_t p_consumerNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un usage de type 'Consumer' */
   T_mkConsumerCode** l_consumerCode;

   /* Si les valeurs des usages sont codées au maximum sur 32bits */
   if ( p_table->global.reportSize <= K_MK_HID_MAX_USAGE_SIZE )
   {
      /* Récupération de l'adresse du dernier usage de type 'Consumer' présent dans la chaine */
      l_consumerCode = mk_hid_button_getLast ( &p_consumer->control );

      /* Si aucun contrôle n'a été assigné à l'usage */
      if ( ( *l_consumerCode ) == K_MK_NULL )
      {
         /* Création d'une table d'usage de type 'Consumer' (la taille de destination est configurée dans cette fonction) */
         l_result = mk_hid_button_create ( p_table, p_usage, p_consumerNumber );

         /* Si aucune erreur ne s'est produite */
         if ( l_result == K_MK_OK )
         {
            /* Enregistrement de l'adresse mémoire de l'usage */
            ( *l_consumerCode ) = p_usage->first->addr;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
            /* Une erreur grave s'est produite, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
            /* les usages alternatifs */
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
      /* La taille de l'usage est incompatible avec le driver, il n'est pas nécessaire d'actualiser la variable d'état permettant de gérer */
      /* les usages alternatifs car ils possèdent tous la même taille. */
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_routeConsumer ( T_mkHIDReportTable* p_table, T_mkHIDReport* p_report, T_mkHIDUsage* p_usage, uint32_t p_page, uint32_t* p_usageUsed )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un contrôle de type 'Consumer' */
   T_mkConsumerControl* l_consumer;

   /* Déclaration d'une variable de travail */
   uint32_t l_counter;

   /* Déclaration d'une variable stockant l'identifiant de l'usage */
   uint32_t l_usageId;

   /* Si les paramètres sont valides */
   if ( ( p_table != K_MK_NULL ) && ( p_report != K_MK_NULL ) && ( p_usage != K_MK_NULL ) && ( p_usageUsed != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du contrôle de type 'Consumer' */
      l_consumer = p_report->addr;

      /* Actualisation de la variable d'état */
      /* Cette variable permet de savoir si l'intégralité des usages alternatifs doivent être analysés ou non */
      ( *p_usageUsed ) = 1;

      /* Si l'item courant est un item de type USAGE_MINIMUM */
      if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
      {
         /* Si la page courante est une page de type CONSUMER */
         if ( p_page == K_MK_HID_CONSUMER_PAGE )
         {
            /* Si l'usage se présente sous la forme d'un tableau */
            if ( ( p_usage->last->value & K_MK_HID_ITEM_VARIABLE ) == 0 )
            {
               /* Récupération du nombre maximal de sélecteurs */
               l_counter = p_table->global.reportCount;
            }

            /* Sinon */
            else
            {
               /* Récupération du nombre total d'usages */
               l_counter = ( p_table->local->usageMaximum - p_table->local->usageMinimum ) + 1;
            }

            /* Allocation puis routage des usages de type Consumer */
            l_result = mk_hid_routeMultipleConsumerUsage ( l_consumer, p_table, p_usage, l_counter );
         }

         /* Sinon */
         else
         {
            /* L'usage courant (alternatif ou principal) n'est pas utilisé */
            /* On bascule la variable pour continuer l'analyse des usages alternatifs */
            ( *p_usageUsed ) = 0;
         }
      }

      /* Sinon si l'item courant est un item de type USAGE */
      else if ( p_usage->first->head.field.tag == K_MK_HID_ITEM_TAG_USAGE )
      {
         /* Détermination de la valeur de l'usage */
         l_usageId = p_usage->first->value & 0x0000FFFF;

         /* Si la page courante est une page de type CONSUMER */
         if ( p_page == K_MK_HID_CONSUMER_PAGE )
         {
            /* Si l'usage n'est pas une collection ou un tableau */
            if ( ( l_usageId > K_MK_HID_CONSUMER_PAGE_GRAPHIC_EQUALIZER ) && ( l_usageId < K_MK_HID_CONSUMER_PAGE_SPEAKER_SYSTEM ) && ( l_usageId < K_MK_HID_CONSUMER_PAGE_CHANNEL_UNKNOWN ) &&
                 ( l_usageId != K_MK_HID_CONSUMER_PAGE_FUNCTION_BUTTONS ) && ( l_usageId != K_MK_HID_CONSUMER_PAGE_SELECTION ) &&
                 ( l_usageId != K_MK_HID_CONSUMER_PAGE_MEDIA_SELECTION ) && ( l_usageId != K_MK_HID_CONSUMER_PAGE_SELECT_DISC ) && ( l_usageId != K_MK_HID_CONSUMER_PAGE_PLAYBACK_SPEED ) &&
                 ( l_usageId != K_MK_HID_CONSUMER_PAGE_APPLICATION_LAUNCH_BUTTONS ) && ( l_usageId != K_MK_HID_CONSUMER_PAGE_GENERIC_GUI_APPLICATION_CONTOLS ) )
            {
               /* Allocation puis routage des usages de type Consumer */
               l_result = mk_hid_routeConsumerUsage ( l_consumer, p_table, p_usage );
            }

            /* Sinon */
            else
            {
               /* L'usage courant (alternatif ou principal) n'est pas utilisé */
               /* On bascule la variable pour continuer l'analyse des usages alternatifs */
               ( *p_usageUsed ) = 0;
            }
         }

         /* Sinon */
         else
         {
            /* L'usage courant (alternatif ou principal) n'est pas utilisé */
            /* On bascule la variable pour continuer l'analyse des usages alternatifs */
            ( *p_usageUsed ) = 0;
         }
      }

      /* Sinon */
      else
      {
         /* Ne rien faire */
         /* L'item courant n'est pas un usage */
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

