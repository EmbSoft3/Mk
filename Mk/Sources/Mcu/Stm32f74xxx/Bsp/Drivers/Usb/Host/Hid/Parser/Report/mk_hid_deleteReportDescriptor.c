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
* @file mk_hid_deleteReportDescriptor.c
* @brief Définition de la fonction mk_hid_deleteReportDescriptor.
* @date 30 oct. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static T_mkCode mk_hid_deleteAlternate ( T_mkHIDItem* p_alternateItem )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration d'un pointeur d'item */
   T_mkHIDItem* l_nextAlternate;

   /* Tant que tous les items alternatifs n'ont pas été désalloué */
   while ( p_alternateItem != K_MK_NULL )
   {
      /* Enregistrement de l'adresse du prochain item */
      l_nextAlternate = p_alternateItem->nextItem;

      /* Désallocation de l'item courant */
      l_result |= mk_pool_freeSafe ( g_mkHIDPool.itemPool, ( T_mkAddr ) p_alternateItem );

      /* Actualisation de l'adresse de l'item courant */
      p_alternateItem = l_nextAlternate;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_deleteReportDescriptor ( T_mkHIDDevice* p_hidDevice )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Déclaration des pointeurs d'item */
   T_mkHIDItem *l_item, *l_nextItem;

   /* Si le paramètre est valide */
   if ( p_hidDevice != K_MK_NULL )
   {
      /* Initialisation du pointeur d'item */
      l_item = p_hidDevice->reportDescriptor.item;

      /* Tant que l'intégralité des 'Items' n'ont pas été supprimés */
      while ( l_item != K_MK_NULL )
      {
         /* Enregistrement de l'adresse du prochain item */
         l_nextItem = l_item->nextItem;

         /* Si l'item possède un ou plusieurs usages alternatifs */
         if ( l_item->nextAlternate != K_MK_NULL )
         {
            /* Désallocation de la liste d'usages alternatifs */
            l_result |= mk_hid_deleteAlternate ( l_item->nextAlternate );
         }

         /* Sinon */
         else
         {
            /* Ne rien faire */
         }

         /* Désallocation de l'item courant */
         l_result |= mk_pool_freeSafe ( g_mkHIDPool.itemPool, ( T_mkAddr ) l_item );

         /* Actualisation de l'adresse de l'item courant */
         l_item = l_nextItem;
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


