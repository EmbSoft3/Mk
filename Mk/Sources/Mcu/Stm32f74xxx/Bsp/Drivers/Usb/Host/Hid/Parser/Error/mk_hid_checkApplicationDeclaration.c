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
* @file mk_hid_checkApplicationDeclaration.c
* @brief Définition de la fonction mk_hid_checkApplicationDeclaration.
* @date 13 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_checkApplicationDeclaration ( T_mkHIDDevice* p_hidDevice, T_mkHIDReportError* p_error )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_item;

   /* Déclaration d'une variable d'état */
   uint32_t l_collection = 0;

   /* Si les paramètres sont valides */
   if ( ( p_hidDevice != K_MK_NULL ) && ( p_error != K_MK_NULL ) )
   {
      /* Récupération de l'adresse du premier item du 'Report Descriptor' */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que le 'Report Descriptor' n'a pas été analysé et tant qu'aucune erreur n'est détectée */
      while ( ( l_item != K_MK_NULL ) && ( ( *p_error ) == K_MK_HID_NO_ERROR ) )
      {
         /* Si l'item est de type 'Collection' */
         if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_COLLECTION )
         {
            /* Si le niveau d'imbrication est le niveau principal */
            if ( l_collection == 0 )
            {
               /* Si la collection n'est pas du type 'Application' */
               if ( l_item->value != K_MK_HID_COLLECTION_TYPE_APPLICATION )
               {
                  /* Actualisation du registre d'erreur */
                  ( *p_error ) = K_MK_HID_ERROR_INVALID_DECLARATION_COLLECTION;
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

            /* Actualisation de la variable d'état */
            l_collection++;
         }

         /* Sinon si l'item est de type 'End Collection' */
         else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_END_COLLECTION )
         {
            /* Actualisation de la variable d'état */
            l_collection--;
         }

         /* Sinon si l'item est de type 'Delimiter' */
         else if ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_DELIMITER )
         {
            /* Si le niveau d'imbrication n'est pas le niveau principal */
            if ( l_collection == 0 )
            {
               /* Actualisation du registre d'erreur */
               ( *p_error ) = K_MK_HID_ERROR_INVALID_DECLARATION_DELIMITER;
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


