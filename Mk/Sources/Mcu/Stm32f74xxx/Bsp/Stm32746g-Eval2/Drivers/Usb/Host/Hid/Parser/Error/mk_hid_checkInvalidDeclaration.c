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
* @file mk_hid_checkInvalidDeclaration.c
* @brief Définition de la fonction mk_hid_checkInvalidDeclaration.
* @date 13 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_checkInvalidDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration d'une variable d'état */
   uint32_t l_delimiter = 0;

   /* Déclaration des variables de statut */
   uint32_t l_usageMinimum = 0, l_usageMaximum = 0, l_usage = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
      while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         /* Si l'item est de type 'Delimiter' */
         if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_DELIMITER )
         {
            /* Si ouverture */
            if ( l_item->value == 0 )
            {
               /* Actualisation de la variable d'état */
               l_delimiter = 1;
            }

            /* Si fermeture */
            else if ( l_item->value == 1 )
            {
               /* Détermination de l'uniformité des usages */
               l_delimiter = l_usage + l_usageMinimum + l_usageMaximum;

               /* Si les usages déclarés dans le délimiter ne sont pas uniforme */
               if ( l_delimiter != 1 )
               {
                  /* Actualisation du registre d'erreur */
                  ( *p_error ) = K_MK_HID_ERROR_INVALID_DECLARATION_DELIMITER;
               }

               /* Sinon */
               else
               {
                  /* Ne rien faire */
               }

               /* Actualisation des variables d'état */
               l_delimiter = 0; l_usage = 0; l_usageMinimum = 0; l_usageMaximum = 0;
            }

            /* Sinon */
            else
            {
               /* Ne rien faire */
               /* L'erreur est remontée dans la fonction mk_hid_checkInvalidValue */
            }
         }

         /* Sinon si un delimiter a été ouvert */
         else if ( l_delimiter == 1 )
         {
            /* Si l'item est de type 'Usage' */
            if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE )
            {
               /* Actualisation de la variable d'état */
               l_usage = 1;
            }

            /* Sinon si l'item est de type 'UsageMinimum' */
            else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
            {
               /* Actualisation de la variable d'état */
               l_usageMinimum = 1;
            }

            /* Sinon si l'item est de type 'UsageMaximum' */
            else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MAXIMUM )
            {
               /* Actualisation de la variable d'état */
               l_usageMaximum = 1;
            }

            /* Sinon */
            else
            {
               /* Actualisation du registre d'erreur */
               ( *p_error ) = K_MK_HID_ERROR_INVALID_DECLARATION_DELIMITER;
            }
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation du pointeur d'item */
         l_item = l_item->nextItem;
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
