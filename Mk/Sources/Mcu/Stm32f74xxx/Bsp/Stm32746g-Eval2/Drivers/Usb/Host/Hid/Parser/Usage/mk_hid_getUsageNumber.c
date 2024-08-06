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
* @file mk_hid_getUsageNumber.c
* @brief Définition de la fonction mk_hid_getUsageNumber.
* @date 2 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_getUsageNumber ( T_mkHIDReport* p_report, uint32_t* p_usageNumber )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un item */
   T_mkHIDItem* l_item;

   /* Si les paramètres sont valides */
   if ( p_usageNumber != K_MK_NULL )
   {
      /* Initialisation du compteur de 'Report' */
      *p_usageNumber = 0;

      /* Récupération de l'adresse du premier item contenu dans le report */
      l_item = p_report->first;

      /* Tant que tout les items n'ont pas été analysés */
      while ( ( l_item != K_MK_NULL ) && ( l_item != p_report->last->nextItem ) )
      {
         /* Si l'item courant marque la fin d'un usage */
         if ( ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_INPUT ) || ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_OUTPUT) ||
              ( l_item->head.field.tag == K_MK_HID_ITEM_TAG_FEATURE ) )
         {
            /* Actualisation du nombre d'usage */
            *p_usageNumber = ( *p_usageNumber ) + 1;
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Actualisation de l'adresse de l'item courant */
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


