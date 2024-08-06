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
* @file mk_hid_setItemStateTable.c
* @brief Définition de la fonction mk_hid_setItemStateTable.
* @date 2 nov. 2019
*
*/

#include "mk_hid_api.h"

/**
 * @internal
 * @brief
 * @endinternal
 */

static int32_t mk_hid_signed ( T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   int32_t l_result = 0;

   /* Si la taille de l'item est de 1 octet */
   if ( p_item->head.field.size == 1 )
   {
      /* Conversion de la valeur 8bits en 32bits */
      l_result = ( int32_t ) ( l_result + ( int8_t ) ( p_item->value ) );
   }

   /* Sinon si la taille de l'item est de 2 octets */
   else if ( p_item->head.field.size == 2 )
   {
      /* Conversion de la valeur 16bits en 32bits */
      l_result = ( int32_t ) ( l_result + ( int16_t ) ( p_item->value ) );
   }

   /* Sinon si la taille de l'item est de 3 octets */
   else if ( p_item->head.field.size == 3 )
   {
      /* Conversion de la valeur 24bits en 32bits */
      l_result = ( int32_t ) ( p_item->value ) ;
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

static void mk_hid_setLogicalMinimum ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Actualisation de la valeur de l'attribut courant */
   p_table->global.logicalMinimum = mk_hid_signed ( p_item );

   /* Si les items physical n'ont pas été déclaré */
   if ( p_table->global.physical == 0 )
   {
      /* Attribution de la valeur logicalMinimum à l'attribut physicalMinimum */
      p_table->global.physicalMinimum = p_table->global.logicalMinimum;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setLogicalMaximum ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Actualisation de la valeur de l'attribut courant */
   p_table->global.logicalMaximum = mk_hid_signed ( p_item );

   /* Si les items physical n'ont pas été déclaré */
   if ( p_table->global.physical == 0 )
   {
      /* Attribution de la valeur logicalMaximum à l'attribut physicalMaximum */
      p_table->global.physicalMaximum = p_table->global.logicalMaximum;
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setPhysicalMinimum ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Actualisation de la valeur de l'attribut courant */
   p_table->global.physicalMinimum = mk_hid_signed ( p_item );
   p_table->global.physical = 1;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_setPhysicalMaximum ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Actualisation de la valeur de l'attribut courant */
   p_table->global.physicalMaximum = mk_hid_signed ( p_item );
   p_table->global.physical = 1;

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_refreshLocalItem ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Si l'item est de type K_MK_HID_ITEM_TAG_USAGE */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->usage = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_USAGE_MINIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MINIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->usageMinimum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_USAGE_MAXIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_MAXIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->usageMaximum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_DESIGNATOR_INDEX */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DESIGNATOR_INDEX )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->designatorIndex = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_DESIGNATOR_MINIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DESIGNATOR_MINIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->designatorMinimum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_DESIGNATOR_MAXIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DESIGNATOR_MAXIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->designatorMaximum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_STRING_INDEX */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_STRING_INDEX )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->stringIndex = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_STRING_MINIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_STRING_MINIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->stringMinimum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_STRING_MAXIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_STRING_MAXIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->stringMaximum = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_DELIMITER */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_DELIMITER )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->local->delimiter = p_item->value;
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static uint32_t mk_hid_refreshGlobalItem ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   uint32_t l_result = 1;

   /* Si l'item est de type K_MK_HID_ITEM_TAG_USAGE_PAGE */
   if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_USAGE_PAGE )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.usagePage = p_item->value;
   }

   /* Sinon si l'item est de type de type K_MK_HID_ITEM_TAG_LOGICAL_MINIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_LOGICAL_MINIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      mk_hid_setLogicalMinimum ( p_table, p_item );
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_LOGICAL_MAXIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_LOGICAL_MAXIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      mk_hid_setLogicalMaximum ( p_table, p_item );
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_PHYSICAL_MINIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_PHYSICAL_MINIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      mk_hid_setPhysicalMinimum ( p_table, p_item );
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_PHYSICAL_MAXIMUM */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_PHYSICAL_MAXIMUM )
   {
      /* Actualisation de la valeur de l'attribut courant */
      mk_hid_setPhysicalMaximum ( p_table, p_item );
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_UNIT_EXPONENT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_UNIT_EXPONENT )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.unitExponent = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_UNIT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_UNIT )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.unit = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_REPORT_SIZE */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_SIZE )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.reportSize = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_REPORT_ID */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_ID )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.reportID = p_item->value;
   }

   /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_REPORT_COUNT */
   else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_REPORT_COUNT )
   {
      /* Actualisation de la valeur de l'attribut courant */
      p_table->global.reportCount = p_item->value;
   }

   /* Sinon */
   else
   {
      /* Actualisation de la variable de retour */
      l_result = 0;
   }

   /* Retour */
   return ( l_result );
}

/**
 * @internal
 * @brief
 * @endinternal
 */

static void mk_hid_refreshTable ( T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Déclaration d'une variable de travail */
   uint32_t l_result;

   /* Mise à jour de la table d'item local */
   l_result = mk_hid_refreshLocalItem ( p_table, p_item );

   /* Si l'item n'était pas de type local */
   if ( l_result == 0 )
   {
      /* Mise à jour de la table d'item global */
      ( void ) mk_hid_refreshGlobalItem ( p_table, p_item );
   }

   /* Sinon */
   else
   {
      /* Ne rien faire */
   }

   /* Retour */
   return;
}

/**
 * @internal
 * @brief
 * @endinternal
 */

T_mkCode mk_hid_setItemStateTable ( T_mkHIDReportStack* p_stack, T_mkHIDReportTable* p_table, T_mkHIDItem* p_item )
{
   /* Déclaration de la variable de retour */
   T_mkCode l_result = K_MK_OK;

   /* Si les paramètres sont valides */
   if ( ( p_stack != K_MK_NULL ) && ( p_table != K_MK_NULL ) && ( p_item != K_MK_NULL ) )
   {
      /* Si l'item est de type K_MK_HID_ITEM_TAG_PUSH */
      if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_PUSH )
      {
         /* Ajout de la table d'item dans la stack */
         p_table->local->previous = p_stack->top;

         /* Actualisation du pointeur de stack */
         p_stack->top = p_table->local;

         /* Allocation d'une nouvelle table d'item */
         l_result = mk_pool_allocSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr* ) &p_table->local, K_MK_POOL_CLEAR, 0 );
      }

      /* Sinon si l'item est de type K_MK_HID_ITEM_TAG_POP */
      else if ( p_item->head.field.tag == K_MK_HID_ITEM_TAG_POP )
      {
         /* Désallocation de la table d'item courante */
         l_result = mk_pool_freeSafe ( g_mkHIDPool.itemStatePool, ( T_mkAddr ) p_table->local );

         /* Actualisation de la valeur du pointeur courant */
         p_table->local = p_stack->top;

         /* Actualisation du pointeur de stack */
         p_stack->top = p_stack->top->previous;
      }

      /* Sinon */
      else
      {
         /* Rafraichissement de la table d'item */
         mk_hid_refreshTable ( p_table, p_item );
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


