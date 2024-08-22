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
* @file mk_hid_checkUnkwnownDeclaration.c
* @brief Définition de la fonction mk_hid_checkUnkwnownDeclaration.
* @date 13 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_isGlobalItem ( T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si l'item n'est pas de type 'Global' */
   if ( ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_USAGE_PAGE ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_LOGICAL_MINIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_LOGICAL_MAXIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_PHYSICAL_MINIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_PHYSICAL_MAXIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_UNIT_EXPONENT ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_UNIT ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_REPORT_SIZE ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_REPORT_ID ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_REPORT_COUNT ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_PUSH ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_POP ) )
   {
      /* Actualisation de la variable de retour */
      l_result = 1;
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

static uint32_t mk_hid_isLocalItem ( T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si l'item n'est pas de type 'Local' */
   if ( ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_USAGE ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_USAGE_MINIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_USAGE_MAXIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_DESIGNATOR_INDEX ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_DESIGNATOR_MINIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_DESIGNATOR_MAXIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_STRING_INDEX ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_STRING_MINIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_STRING_MAXIMUM ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_DELIMITER ) )
   {
      /* Actualisation de la variable de retour */
      l_result = 1;
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

static uint32_t mk_hid_isMainItem ( T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 0;

   /* Si l'item n'est pas de type 'Main' */
   if ( ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_COLLECTION ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_END_COLLECTION ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_INPUT ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_OUTPUT ) &&
        ( p_item->head.field.tag != K_MK_HID_ITEM_TAG_FEATURE ) )
   {
      /* Actualisation de la variable de retour */
      l_result = 1;
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

T_mkCode mk_hid_checkUnkwnownDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration des variables d'usage générale */
   uint32_t l_mainItem, l_localItem, l_globalItem;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
      while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         l_mainItem   = mk_hid_isMainItem ( l_item );
         l_localItem  = mk_hid_isLocalItem ( l_item );
         l_globalItem = mk_hid_isGlobalItem ( l_item );

         /* Si l'item est inconnu */
         if ( ( l_mainItem == 0 ) && ( l_localItem == 0 ) && ( l_globalItem == 0 ) )
         {
            /* Actualisation du registre d'erreur */
            ( *p_error ) = K_MK_HID_ERROR_INVALID_DECLARATION_ITEM;
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
